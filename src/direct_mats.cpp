#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectMATS : public Integrator {
public:
    DirectMATS(const PropertyList& props) {}

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        Color3f result = Color3f(0.f);
        
        Frame localFrame = its.shFrame.n;
        Vector3f normal = its.shFrame.n / its.shFrame.n.norm();
        normal = localFrame.toLocal(normal);

        Vector3f wo = Vector3f(-ray.d.x(), -ray.d.y(), -ray.d.z());
        wo = localFrame.toLocal(wo);
        
        BSDFQueryRecord BQR = BSDFQueryRecord(wo);
        BQR.uv = its.uv;
        Color3f BSDF = its.mesh->getBSDF()->sample(BQR, sampler->next2D());
        Vector3f wi = BQR.wo;

        //wi = localFrame.toLocal(wi);
        Ray3f ray2 = Ray3f(its.p,localFrame.toWorld(wi));
        
        
        
        Intersection its2;
        if(scene->rayIntersect(ray2,its2) && its2.mesh->isEmitter()){
            
            Frame localFrame2 = its2.shFrame.n;
            Vector3f normal2 = its2.shFrame.n / its2.shFrame.n.norm();
            EmitterQueryRecord EQR_second = EmitterQueryRecord(its.p, its2.p, normal2);
            Color3f li = its2.mesh->getEmitter()->eval(EQR_second);
            Intersection its3;
            result = Color3f(result.r() + li.r() * BSDF.r() ,
                result.g() + li.g() * BSDF.g() ,
                result.b() + li.b() * BSDF.b() );
            
        }
        
        if (its.mesh->isEmitter()) {
            EmitterQueryRecord EQR_le = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
            Color3f res = its.mesh->getEmitter()->eval(EQR_le);
            result = Color3f(result.r() + res.r(), result.g() + res.g(), result.b() + res.b());
        }
        return result;
    }

    std::string toString() const {
        return "DirectMATS[]";
    }
};

NORI_REGISTER_CLASS(DirectMATS, "direct_mats");
NORI_NAMESPACE_END