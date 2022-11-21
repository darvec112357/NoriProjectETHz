#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectEMS : public Integrator {
public:
    DirectEMS(const PropertyList& props) {}

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        

        Frame localFrame = its.shFrame.n;
        Normal3f n = its.shFrame.n / its.shFrame.n.norm();
        n = localFrame.toLocal(n);

        Vector3f wo = Vector3f(-ray.d.x(), -ray.d.y(), -ray.d.z());
        wo = localFrame.toLocal(wo);

        EmitterQueryRecord EQR = EmitterQueryRecord(its.p);
        Color3f result = Color3f(0.f);
        

        std::vector<Emitter*> lights = scene->getLights();
        for (int i = 0; i < lights.size(); i++)
        {
            Color3f L_in = lights[i]->sample(EQR, sampler->next2D());
            Intersection its2;
            if (scene->rayIntersect(EQR.shadowRay, its2))
                continue;
            
            Vector3f wi1 = localFrame.toLocal(EQR.wi);
            
            BSDFQueryRecord BQR = BSDFQueryRecord(wo, wi1, ESolidAngle);
            BQR.uv = its.uv;
            Color3f BSDF = its.mesh->getBSDF()->eval(BQR);
            float coswi = abs(wi1.dot(n));
            result = Color3f(result.r() + L_in.r() * BSDF.r() * coswi,
                result.g() + L_in.g() * BSDF.g() * coswi,
                result.b() + L_in.b() * BSDF.b() * coswi);
        }
        if (its.mesh->isEmitter()) {
            EmitterQueryRecord EQR_le = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
            Color3f res = its.mesh->getEmitter()->eval(EQR_le);
            result = Color3f(result.r() + res.r(), result.g() + res.g(), result.b() + res.b());
        }
        
        return result;
    }

    std::string toString() const {
        return "DirectEMS[]";
    }
};

NORI_REGISTER_CLASS(DirectEMS, "direct_ems");
NORI_NAMESPACE_END