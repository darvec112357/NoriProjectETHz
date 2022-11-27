#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class MultipleImportanceSampling : public Integrator{
public:
    MultipleImportanceSampling(const PropertyList &props) {
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

        EmitterQueryRecord eRec = EmitterQueryRecord(its.p);
        std::vector<Emitter*> lights = scene->getLights();
        Frame local_frame = Frame(its.shFrame.n);
        
        for (int i = 0; i < lights.size(); i++){
            Emitter* emitter = lights[i];

            Point2f sp = Point2f(sampler->next1D(), sampler->next1D());

            Color3f lr = emitter->sample(eRec, sp);

            Intersection its_shadow;
            if (scene->rayIntersect(eRec.shadowRay, its_shadow))
                continue;

            BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(- ray.d), local_frame.toLocal(eRec.wi), ESolidAngle);
            bRec.uv = its.uv;
            float cos = its.shFrame.n.dot(eRec.wi);

            float ems = emitter->pdf(eRec);
            float mats = its.mesh->getBSDF()->pdf(bRec);

            if(ems + mats == 0)
                continue;
            
            float weight = ems/(ems + mats);
            radiance_result += its.mesh->getBSDF()->eval(bRec) * cos * lr * weight;                         
        }

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
            eRec.n = its_shadow.shFrame.n;
            eRec.p = its_shadow.p;

            float ems = its_shadow.mesh->getEmitter()->pdf(eRec);
			float mats = its.mesh->getBSDF()->pdf(bRec);

            if (ems + mats == 0)
                return radiance_result;

            float weight = mats/(ems + mats);
            radiance_result += its_shadow.mesh->getEmitter()->eval(eRec) * bsdf * weight;
        }

        return radiance_result;
    }

    std::string toString() const {
        return "MultipleImportanceSampling[]";
    }
};


NORI_REGISTER_CLASS(MultipleImportanceSampling, "direct_mis")

NORI_NAMESPACE_END