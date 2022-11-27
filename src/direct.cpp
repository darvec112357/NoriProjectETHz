#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class DirectIntegrator : public Integrator {
public:
    DirectIntegrator(const PropertyList &props) {
        /* No parameters this time */
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        Color3f radiance_result = Color3f(0.0f);
        EmitterQueryRecord eRec = EmitterQueryRecord(its.p);
        std::vector<Emitter*> pointlights = scene->getLights(); 

        for (int i = 0; i< pointlights.size(); i++){
            
            Color3f lr = pointlights[i]->sample(eRec, Point2f(0.0f, 0.0f));
            Frame local_frame = Frame(its.shFrame.n);
            Intersection its_shadow;
            if (scene->rayIntersect(eRec.shadowRay, its_shadow)){
                continue;
            }
            BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(eRec.wi), local_frame.toLocal(- ray.d), ESolidAngle);
            bRec.uv = its.uv;
            float cos = abs(its.shFrame.n.dot(eRec.wi));
            radiance_result += Color3f(its.mesh->getBSDF()->eval(bRec).r() * cos * lr.r(),
                                    its.mesh->getBSDF()->eval(bRec).g() * cos * lr.g(),
                                    its.mesh->getBSDF()->eval(bRec).b() * cos * lr.b());
        }
    
        

        return radiance_result;
    
    }

    std::string toString() const {
        return "DirectIntegrator[]";
    }
protected:

};

NORI_REGISTER_CLASS(DirectIntegrator, "direct");

NORI_NAMESPACE_END