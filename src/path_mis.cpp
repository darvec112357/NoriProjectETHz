#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/bsdf.h>

NORI_NAMESPACE_BEGIN

class PathMIS : public Integrator {
public:
    PathMIS(const PropertyList& props) {}

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Vector3f wi = ray.d;
        Color3f result = Color3f(0.f);
        Color3f t = Color3f(1.0f);
        Ray3f traced_ray = ray;

        float pdf_ems = 1;
        float pdf_mats = 1;
        float w_mats = 1;
        float ratio = 0;
        while (true) {
            Intersection its;

            if (!scene->rayIntersect(traced_ray, its))
                return result;

            Frame localFrame = its.shFrame.n;
            Vector3f normal = its.shFrame.n / its.shFrame.n.norm();
            normal = localFrame.toLocal(normal);

            
            if (its.mesh->isEmitter()) {
                EmitterQueryRecord EQR_le = EmitterQueryRecord(traced_ray.o, its.p, its.shFrame.n);
                Color3f Le = its.mesh->getEmitter()->eval(EQR_le);
                Le *= w_mats;
                Le *= t;
                result += Le;
            }
            
            float success_prob = std::min(t.maxCoeff(), .99f);
            if (sampler->next1D() > success_prob) {
                break;
            }
            t /= success_prob;

            std::vector<Emitter*> lights = scene->getLights();
            EmitterQueryRecord EQR_ems = EmitterQueryRecord(its.p);
            Color3f result_ems = Color3f(0.0f);
            
            for (int i = 0; i < lights.size(); i++)
            {
                Emitter* emitter = lights[i];

                Point2f samplePoint = sampler->next2D();
                Color3f L_in = emitter->sample(EQR_ems, samplePoint);
                pdf_ems = emitter->pdf(EQR_ems);
                Intersection itsShadow;
                if (scene->rayIntersect(EQR_ems.shadowRay, itsShadow))
                    continue;

                Vector3f incident_direction = localFrame.toLocal(-traced_ray.d);
                Vector3f wi1 = localFrame.toLocal(EQR_ems.wi);

                BSDFQueryRecord BQR_ems = BSDFQueryRecord(incident_direction, wi1, ESolidAngle);
                BQR_ems.uv = its.uv;
                Color3f BSDF_ems = its.mesh->getBSDF()->eval(BQR_ems);
                pdf_mats = its.mesh->getBSDF()->pdf(BQR_ems);

                float coswi = abs(wi1.dot(normal));
                if (pdf_ems + pdf_mats > 0 && BQR_ems.measure != EDiscrete) {
                    float ratio = pdf_ems / (pdf_ems + pdf_mats);
                    Color3f adder=Color3f(L_in.r() * BSDF_ems.r() * coswi * ratio,
                        L_in.g() * BSDF_ems.g() * coswi * ratio,
                        L_in.b() * BSDF_ems.b() * coswi * ratio);
                    adder *= t;
                    result_ems += adder;
                }
            }
            result += result_ems;

            BSDFQueryRecord BQR_mats = BSDFQueryRecord(localFrame.toLocal(-traced_ray.d));
            BQR_mats.uv = its.uv;
            Color3f BSDF_mats = its.mesh->getBSDF()->sample(BQR_mats, sampler->next2D());

            traced_ray = Ray3f(its.p, localFrame.toWorld(BQR_mats.wo));
            t *= BSDF_mats;
            if (BQR_mats.measure == EDiscrete) {
                w_mats = 1;
            }
            else {
                Intersection its2;
                if (scene->rayIntersect(traced_ray, its2) && its2.mesh->isEmitter()) {
                    EmitterQueryRecord EQR_mats = EmitterQueryRecord(its.p, its2.p, its2.shFrame.n);
                    pdf_ems = its2.mesh->getEmitter()->pdf(EQR_mats);
                    //assert(pdf_ems != 0);
                    pdf_mats = its.mesh->getBSDF()->pdf(BQR_mats);
                    if (pdf_ems + pdf_mats > 0) {
                        w_mats = pdf_mats / (pdf_ems + pdf_mats);
                    }
                }
            }
            
        }

        return result;
    }

    std::string toString() const {
        return "PathMIS[]";
    }
};

NORI_REGISTER_CLASS(PathMIS, "path_mis");
NORI_NAMESPACE_END