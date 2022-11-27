#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/warp.h>
#include <nori/common.h>

NORI_NAMESPACE_BEGIN

class PathMultipleImportanceSampling : public Integrator{

public:
    PathMultipleImportanceSampling(const PropertyList &props) {
        /* No parameters this time */ 
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        Color3f radiance_result = Color3f(0.0f);
        Color3f t = Color3f(1.0f); //throughput
        float wMat = 1.0f;
        Ray3f pathRay = ray;

        while(true){
            
            Intersection its;
            if (!scene->rayIntersect(pathRay, its))
                break;

            Color3f Le = Color3f(0.0f);
            if (its.mesh->isEmitter()){
			    EmitterQueryRecord eRec = EmitterQueryRecord(pathRay.o, its.p, its.shFrame.n);
                Le = its.mesh->getEmitter()->eval(eRec);
                Le *= t;
                Le *= wMat;
		    }

            radiance_result += Le;

            float successProbability = std::min(t.maxCoeff(), 0.99f);
            
            if(sampler->next1D() > successProbability)
                break;
            
            t /= successProbability;

            //EMS sampling
            EmitterQueryRecord eRec = EmitterQueryRecord(its.p);
            std::vector<Emitter*> lights = scene->getLights();
            Frame local_frame = Frame(its.shFrame.n);

            for (int i = 0; i < lights.size(); i++){
                Emitter* emitter = lights[i];

                Point2f sp = sampler->next2D();

                Color3f lr = emitter->sample(eRec, sp);

                Intersection its_shadow;
                if (scene->rayIntersect(eRec.shadowRay, its_shadow))
                    continue;

                BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(- pathRay.d), local_frame.toLocal(eRec.wi), ESolidAngle);
                bRec.uv = its.uv;
                float cos = its.shFrame.n.dot(eRec.wi);

                float ems = emitter->pdf(eRec);
                float mats = its.mesh->getBSDF()->pdf(bRec);

                if(ems + mats > 0){
                    float weight = ems/(ems + mats);
                    radiance_result += Color3f(
                        its.mesh->getBSDF()->eval(bRec).r() * cos * lr.r() * weight * t.r(),
                        its.mesh->getBSDF()->eval(bRec).g() * cos * lr.g() * weight * t.g(),
                        its.mesh->getBSDF()->eval(bRec).b() * cos * lr.b() * weight * t.b()
                    );
                }                       
            }

            //new iteration

            Point2f sp = Point2f(sampler->next1D(), sampler->next1D());
            BSDFQueryRecord bRec = BSDFQueryRecord(local_frame.toLocal(-pathRay.d));
            bRec.uv = its.uv;
            Color3f bsdf = its.mesh->getBSDF()->sample(bRec, sp);
            t *= bsdf;
            pathRay = Ray3f(its.p, local_frame.toWorld(bRec.wo));

            if(bRec.measure == EDiscrete){
                wMat = 1.0f;
            }else{
                Intersection its_n;
                if (scene->rayIntersect(pathRay, its_n)) {
                    if (its_n.mesh->isEmitter()) {
                        EmitterQueryRecord eRec(its.p, its_n.p, its_n.shFrame.n);
                        float mat = its.mesh->getBSDF()->pdf(bRec);
                        float ems = its_n.mesh->getEmitter()->pdf(eRec);
                        if (ems + mat > 0)
                            wMat = mat / (ems + mat);
                    }
                }
            }
        }

        return radiance_result;

    }

    std::string toString() const {
        return "PathMultipleImportanceSampling[]";
    }

};

NORI_REGISTER_CLASS(PathMultipleImportanceSampling, "path_mis")

NORI_NAMESPACE_END