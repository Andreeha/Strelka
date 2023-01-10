#pragma once

#include <optix.h>

#include "OptixRenderParams.h"

#include <iostream>
#include <iomanip>

#include <scene/scene.h>

#include "common.h"
#include "buffer.h"

#include <materialmanager.h>

namespace oka
{

static void context_log_cb(unsigned int level, const char* tag, const char* message, void* /*cbdata */)
{
    std::cerr << "[" << std::setw(2) << level << "][" << std::setw(12) << tag << "]: " << message << "\n";
}

static inline void optixCheck(OptixResult res, const char* call, const char* file, unsigned int line)
{
    if (res != OPTIX_SUCCESS)
    {
        std::stringstream ss;
        ss << "Optix call '" << call << "' failed: " << file << ':' << line << ")\n";
        std::cerr << ss.str() << std::endl;
        // throw Exception(res, ss.str().c_str());
        assert(0);
    }
}

static inline void optixCheckLog(OptixResult res,
                                 const char* log,
                                 size_t sizeof_log,
                                 size_t sizeof_log_returned,
                                 const char* call,
                                 const char* file,
                                 unsigned int line)
{
    if (res != OPTIX_SUCCESS)
    {
        std::stringstream ss;
        ss << "Optix call '" << call << "' failed: " << file << ':' << line << ")\nLog:\n"
           << log << (sizeof_log_returned > sizeof_log ? "<TRUNCATED>" : "") << '\n';
        std::cerr << ss.str() << std::endl;
        // throw Exception(res, ss.str().c_str());
        assert(0);
    }
}

//------------------------------------------------------------------------------
//
// OptiX error-checking
//
//------------------------------------------------------------------------------
#define OPTIX_CHECK(call) optixCheck(call, #call, __FILE__, __LINE__)

#define OPTIX_CHECK_LOG(call) optixCheckLog(call, log, sizeof(log), sizeof_log, #call, __FILE__, __LINE__)

enum RayType
{
    RAY_TYPE_RADIANCE = 0,
    RAY_TYPE_OCCLUSION = 1,
    RAY_TYPE_COUNT
};

struct ParallelogramLight
{
    float3 corner;
    float3 v1, v2;
    float3 normal;
    float3 emission;
};

struct PathTracerState
{
    OptixDeviceContext context = 0;

    OptixTraversableHandle ias_handle;
    CUdeviceptr d_instances = 0;

    OptixTraversableHandle gas_handle = 0; // Traversable handle for triangle AS
    CUdeviceptr d_gas_output_buffer = 0; // Triangle AS memory
    CUdeviceptr d_vertices = 0;

    OptixModuleCompileOptions module_compile_options = {};
    OptixModule ptx_module = 0;
    OptixPipelineCompileOptions pipeline_compile_options = {};
    OptixPipeline pipeline = 0;
    OptixModule m_catromCurveModule = 0;

    OptixProgramGroup raygen_prog_group = 0;
    OptixProgramGroup radiance_miss_group = 0;
    OptixProgramGroup occlusion_miss_group = 0;
    OptixProgramGroup radiance_default_hit_group = 0;
    std::vector<OptixProgramGroup> radiance_hit_groups;
    OptixProgramGroup occlusion_hit_group = 0;
    OptixProgramGroup light_hit_group = 0;
    CUstream stream = 0;
    Params params = {};
    CUdeviceptr d_params = 0;

    OptixShaderBindingTable sbt = {};
};

class OptiXRender
{
private:
    struct Mesh
    {
        OptixTraversableHandle gas_handle = 0;
        CUdeviceptr d_gas_output_buffer = 0;
    };

    struct Curve
    {
        OptixTraversableHandle gas_handle = 0;
        CUdeviceptr d_gas_output_buffer = 0;
    };

    struct Instance
    {
        OptixInstance instance;
    };

    // optix material
    struct Material
    {
        OptixProgramGroup programGroup;
        CUdeviceptr d_argData = 0;
        size_t d_argDataSize = 0;
        CUdeviceptr d_roData = 0;
        size_t d_roSize = 0;
    };

    struct View
    {
        oka::Camera::Matrices mCamMatrices;
    };

    View mPrevView;

    PathTracerState mState;

    Mesh* createMesh(const oka::Mesh& mesh);
    Curve* createCurve(const oka::Curve& curve);

    SharedContext* mSharedCtx;
    oka::Scene* mScene = nullptr;

    std::vector<Mesh*> mOptixMeshes;
    std::vector<Curve*> mOptixCurves;

    CUdeviceptr d_vb = 0;
    CUdeviceptr d_ib = 0;
    CUdeviceptr d_lights = 0;
    CUdeviceptr d_points = 0;
    CUdeviceptr d_widths = 0;

    CUdeviceptr d_materialRoData = 0;
    CUdeviceptr d_materialArgData = 0;

    CUdeviceptr d_param = 0;

    void createVertexBuffer();
    void createIndexBuffer();

    // curve utils
    void createPointsBuffer();
    void createWidthsBuffer();

    void createLightBuffer();

    bool createOptixMaterials();
    Material& getMaterial(int id);

    MaterialManager mMaterialManager;
    std::vector<Material> mMaterials;

    void updatePathtracerParams(const uint32_t width, const uint32_t height);

public:
    OptiXRender(/* args */);
    ~OptiXRender();

    void init();

    void createContext();
    void createAccelerationStructure();
    void createModule();
    void createProgramGroups();
    void createPipeline();
    void createSbt();

    OptixProgramGroup createRadianceClosestHitProgramGroup(PathTracerState& state,
                                                           char const* module_code,
                                                           size_t module_size);

    void launch(CUDAOutputBuffer<uchar4>& output_buffer);

    void setSharedContext(SharedContext* ctx)
    {
        mSharedCtx = ctx;
    }

    SharedContext& getSharedContext()
    {
        return *mSharedCtx;
    }

    void setScene(Scene* scene)
    {
        mScene = scene;
    }

    Scene* getScene()
    {
        return mScene;
    }
};

} // namespace oka