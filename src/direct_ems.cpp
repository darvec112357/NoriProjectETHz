#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>


NORI_NAMESPACE_BEGIN

class DirectIlluminationIntegrator : public Integrator {
public:
    DirectIlluminationIntegrator(const PropertyList &props) {
        /* No parameters this time */
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        Color3f radiance_result = Color3f(0.0f);
    
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return radiance_result;

        if (its.mesh->isEmitter()) {
            EmitterQueryRecord eRec = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
            radiance_result += its.mesh->getEmitter()->eval(eRec);
        }
        
        EmitterQueryRecord eRec = EmitterQueryRecord(its.p);
        std::vector<Emitter*> lights = scene->getLights();
   
        for (int i = 0; i < lights.size(); i++){

            Emitter* emitter = lights[i];

            Point2f sp = Point2f(sampler->next1D(), sampler->next1D());

            Color3f lr = emitter->sample(eRec, sp);

            Frame local_frame = Frame(its.shFrame.n);
            Intersection its_shadow;
            if (scene->rayIntersect(eRec.shadowRay, its_shadow))
                continue;

            BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(- ray.d), local_frame.toLocal(eRec.wi), ESolidAngle);
            bRec.uv = its.uv;
            float cos = its.shFrame.n.dot(eRec.wi);
            
            radiance_result += Color3f(its.mesh->getBSDF()->eval(bRec).r() * cos * lr.r(),
                                    its.mesh->getBSDF()->eval(bRec).g() * cos * lr.g(),
                                    its.mesh->getBSDF()->eval(bRec).b() * cos * lr.b());
                    
        }
        return radiance_result;
    }

    std::string toString() const {
        return "DirectIlluminationIntegrator[]";
    }

protected:

};

NORI_REGISTER_CLASS(DirectIlluminationIntegrator, "direct_ems");

NORI_NAMESPACE_END