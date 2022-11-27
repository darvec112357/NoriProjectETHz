#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class MicrofacetIntegrator : public Integrator{

public:
    MicrofacetIntegrator(const PropertyList &props) {
        /* No parameters this time */
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        Color3f radiance_result = Color3f(0.0f);

        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return radiance_result;

        if (its.mesh->isEmitter()){
			EmitterQueryRecord eRec = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
			radiance_result += its.mesh->getEmitter()->eval(eRec);
		}

        Frame local_frame = Frame(its.shFrame.n);
        Point2f sp = Point2f(sampler->next1D(), sampler->next1D());
        BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(-ray.d));
        bRec.uv = its.uv;
        Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sp);

        Vector3f wi = local_frame.toWorld(bRec.wo);
        Ray3f rayIn = Ray3f(its.p, wi);

        
        Intersection its_shadow;
        if (!scene->rayIntersect(rayIn, its_shadow))
            return radiance_result;
        
        if (its_shadow.mesh->isEmitter()){
            EmitterQueryRecord eRec = EmitterQueryRecord(its.p);
            eRec.wi = wi;
            radiance_result += its_shadow.mesh->getEmitter()->eval(eRec) * bsdf;
        }

        return radiance_result;

    }

    std::string toString() const {
        return "MicrofacetIntegrator[]";
    }

};

NORI_REGISTER_CLASS(MicrofacetIntegrator, "direct_mats")

NORI_NAMESPACE_END