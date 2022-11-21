#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class DirectMIS : public Integrator {
public:
    DirectMIS(const PropertyList& props) {}

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(0.0f);

        Color3f le = Color3f(0.f);
        EmitterQueryRecord EQR_le = EmitterQueryRecord(ray.o, its.p, its.shFrame.n);
        if (its.mesh->isEmitter()) {
            le = its.mesh->getEmitter()->eval(EQR_le);
        }

        Color3f result_ems = Color3f(0.0f);

        Frame localFrame = its.shFrame.n;
        Vector3f normal = its.shFrame.n / its.shFrame.n.norm();
        normal = localFrame.toLocal(normal);
        Vector3f wo = Vector3f(-ray.d.x(), -ray.d.y(), -ray.d.z());
        wo = localFrame.toLocal(wo);

        float pdf_ems = 0;
        float pdf_mats = 0;
        std::vector<Emitter*> lights = scene->getLights();
        EmitterQueryRecord EQR = EmitterQueryRecord(its.p);
        for (int i = 0; i < lights.size(); i++)
        {
            Emitter* emitter = lights[i];

            Point2f samplePoint = sampler->next2D();
            Color3f L_in = emitter->sample(EQR, samplePoint);
            pdf_ems= emitter->pdf(EQR);
            Intersection itsShadow;
            if (scene->rayIntersect(EQR.shadowRay, itsShadow))
                continue;

            Vector3f wi1 = localFrame.toLocal(EQR.wi);

            BSDFQueryRecord BQR = BSDFQueryRecord(wo, wi1, ESolidAngle);
            BQR.uv = its.uv;
            Color3f BSDF_ems = its.mesh->getBSDF()->eval(BQR);
            pdf_mats = its.mesh->getBSDF()->pdf(BQR);

            float coswi = abs(wi1.dot(normal));
            if (pdf_ems + pdf_mats > 0) {
                float ratio = pdf_ems / (pdf_ems + pdf_mats);
                result_ems = Color3f(result_ems.r() + L_in.r() * BSDF_ems.r() * coswi * ratio,
                    result_ems.g() + L_in.g() * BSDF_ems.g() * coswi * ratio,
                    result_ems.b() + L_in.b() * BSDF_ems.b() * coswi * ratio);
            }
            
        }

        Color3f result_mats = Color3f(0.0f);

        
        BSDFQueryRecord BQR_mats = BSDFQueryRecord(wo);
        BQR_mats.uv = its.uv;
        Color3f BSDF_mats = its.mesh->getBSDF()->sample(BQR_mats, sampler->next2D());
        pdf_mats = its.mesh->getBSDF()->pdf(BQR_mats);

        Vector3f wi = BQR_mats.wo;
        Ray3f ray2 = Ray3f(its.p, localFrame.toWorld(wi));
        Intersection its2;
        if (scene->rayIntersect(ray2, its2)) {
            if (its2.mesh->isEmitter())
            {
                EmitterQueryRecord EQR_mats = EmitterQueryRecord(its.p, its2.p, its2.shFrame.n);
                Color3f li = its2.mesh->getEmitter()->eval(EQR_mats);
                pdf_ems = its2.mesh->getEmitter()->pdf(EQR_mats);
                if (pdf_ems + pdf_mats > 0) {
                    float ratio = pdf_mats / (pdf_ems + pdf_mats);
                    result_mats = Color3f(result_mats.r() + li.r() * BSDF_mats.r() * ratio,
                        result_mats.g() + li.g() * BSDF_mats.g() * ratio,
                        result_mats.b() + li.b() * BSDF_mats.b() * ratio);
                }
                
            }

        }
        
        Color3f result = Color3f(le.r() + result_ems.r() + result_mats.r(),
            le.g() + result_ems.g() + result_mats.g(),
            le.b() + result_ems.b() + result_mats.b());
        return result;
    
    }

    std::string toString() const {
        return "DirectMIS[]";
    }
};

NORI_REGISTER_CLASS(DirectMIS, "direct_mis");
NORI_NAMESPACE_END