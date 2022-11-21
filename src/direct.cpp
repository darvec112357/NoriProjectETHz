#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/bsdf.h>


NORI_NAMESPACE_BEGIN

class DirectIntegrator : public Integrator {
public:
    DirectIntegrator(const PropertyList &props) {
        /* No parameters this time */
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
        Color3f result = Color3f(0.0f);

        Intersection its;
        if (!scene->rayIntersect(ray, its)) return Color3f(0.0f);
        Normal3f n = its.shFrame.n;
        Frame local = Frame(n);
        
        EmitterQueryRecord lRec = EmitterQueryRecord(its.p);

        std::vector<Emitter*> lights=scene->getLights();

        Vector3f wo = local.toLocal(Vector3f(-ray.d.x(), -ray.d.y(), -ray.d.z()));

        for (int i = 0; i < lights.size(); i++) {
            Color3f radiance = lights[i]->sample(lRec, Point2f(0, 0));
            Intersection its2;
            if (scene->rayIntersect(lRec.shadowRay, its2)) {
                continue;
            }
            
            
            BSDFQueryRecord bRec = BSDFQueryRecord(local.toLocal(lRec.wi), wo, ESolidAngle);
            bRec.uv = its.uv;

            Color3f bsdf = its.mesh->getBSDF()->eval(bRec);

            
            float cosine = abs(n.dot(lRec.wi) / (lRec.wi.norm() * n.norm()));

            /*std::cout << "cosine:" << cosine << std::endl;
            std::cout << "wo:" << wo.x() << "\t" << wo.y() << "\t" << wo.z() << std::endl;
            std::cout << "wi:" << lRec.wi.x() << "\t" << lRec.wi.y() << "\t" << lRec.wi.z() << std::endl;
            std::cout << "bsdf:" << bsdf.r() << "\t" << bsdf.g() << "\t" << bsdf.b() << std::endl;*/
            result = Color3f(result.r() + bsdf.r() * radiance.r() * cosine, result.g() + bsdf.g() * radiance.g() * cosine, result.b() + bsdf.b() * radiance.b() * cosine);
        }
        

        return result;
        
    }

    std::string toString() const {
        return "DirectIntegrator[]";
    }

    
};

NORI_REGISTER_CLASS(DirectIntegrator, "direct");

NORI_NAMESPACE_END