#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class AverageVisibilityIntegrator : public Integrator {
public: 
    AverageVisibilityIntegrator(const PropertyList &props) {
        ray_length = props.getFloat("length");
    }

    Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {

        /* First find the surface intersected by the camera ray */
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(1.0f);
        Vector3f v = Warp::sampleUniformHemisphere(sampler, its.shFrame.n);

        /*Generate New Ray*/
        Ray3f new_ray = Ray3f(its.p, v, Epsilon, ray_length);

        /* When there is no intersection, return Color3f(1.0f) */
        Intersection its2;
        if (!scene->rayIntersect(new_ray, its2)){
            return Color3f(1.0f);
        }

        /* Otherwise compute the average visibility */
        return Color3f(0.0f);
           
    };
    
    std::string toString() const {
        return "AverageVisibilityIntegrator[]";
    }

protected:
    float ray_length;
};

NORI_REGISTER_CLASS(AverageVisibilityIntegrator, "av");

NORI_NAMESPACE_END