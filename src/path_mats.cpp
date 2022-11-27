#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>
#include <nori/common.h>

NORI_NAMESPACE_BEGIN

class PathMicrofacetIntegrator : public Integrator{

public:
    PathMicrofacetIntegrator(const PropertyList &props) {
        /* No parameters this time */
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        Color3f radiance_result = Color3f(0.0f);
        Color3f t = Color3f(1.0f); //throughput
        Ray3f pathRay = ray;

        while(true){
            
            Intersection its;
            if (!scene->rayIntersect(pathRay, its))
                break;

            if (its.mesh->isEmitter()){
			    EmitterQueryRecord eRec = EmitterQueryRecord(pathRay.o, its.p, its.shFrame.n);
			    radiance_result += its.mesh->getEmitter()->eval(eRec) * t;
		    }

            float successProbability = std::min(t.maxCoeff(), 0.99f);
            
            if(sampler->next1D() > successProbability)
                break;
            t /= successProbability;

            Frame local_frame = Frame(its.shFrame.n);
            Point2f sp = sampler->next2D();
            BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(-pathRay.d));
            bRec.uv = its.uv;
            Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sp);

            t *= bsdf;
            
            pathRay = Ray3f(its.p, local_frame.toWorld(bRec.wo));
            
        }

        return radiance_result;

    }

    std::string toString() const {
        return "PathMicrofacetIntegrator[]";
    }

};

NORI_REGISTER_CLASS(PathMicrofacetIntegrator, "path_mats")

NORI_NAMESPACE_END