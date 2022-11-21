#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class PathMATS : public Integrator {
public:
    PathMATS(const PropertyList& props) {}

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Color3f result = Color3f(0.f);
        Color3f t = Color3f(1.0f);
        Ray3f traced_ray = ray;
        while (true) {
            Intersection its;
            
            if (!scene->rayIntersect(traced_ray, its))
                return result;

            if (its.mesh->isEmitter()) {
                EmitterQueryRecord EQR_le = EmitterQueryRecord(traced_ray.o, its.p, its.shFrame.n);
                Color3f Le = its.mesh->getEmitter()->eval(EQR_le);
                Le *= t;
                result += Le;
            }

            Frame localFrame = its.shFrame.n;
            Vector3f normal = its.shFrame.n / its.shFrame.n.norm();
            normal = localFrame.toLocal(normal);

            BSDFQueryRecord BQR = BSDFQueryRecord(localFrame.toLocal(-traced_ray.d));
            BQR.uv = its.uv;
            Color3f BSDF = its.mesh->getBSDF()->sample(BQR, sampler->next2D());
            t *= BSDF;
            float success_prob = std::min(t.maxCoeff(), .99f);
            if (sampler->next1D() > success_prob) {
                break;
            }
            t /= success_prob;
            
            traced_ray = Ray3f(its.p, localFrame.toWorld(BQR.wo));
        }
        
        return result;
    }

    std::string toString() const {
        return "PathMATS[]";
    }
};

NORI_REGISTER_CLASS(PathMATS, "path_mats");
NORI_NAMESPACE_END