#include <nori/integrator.h>
#include <nori/scene.h>
#include <nori/warp.h>

NORI_NAMESPACE_BEGIN

class AverageVisibility : public Integrator {
public:
    AverageVisibility(const PropertyList& props) {
        ray_length = props.getFloat("length");

    }

    Color3f Li(const Scene* scene, Sampler* sampler, const Ray3f& ray) const {
        Intersection its;
        if (!scene->rayIntersect(ray, its))
            return Color3f(1.0f);

        Normal3f n = its.shFrame.n;
        Vector3f v = Warp::sampleUniformHemisphere(sampler, n);
        Ray3f& ray2 = Ray3f(its.p, v, Epsilon, ray_length);
        Intersection its2;

        /*if (its2.t > ray_length)
            return Color3f(1.0f);*/
        if (!scene->rayIntersect(ray2, its2))
            return Color3f(1.0f);
        return Color3f(0.0f);
    }

    std::string toString() const {
        return tfm::format("AverageVisibility[\n"
            "  ray_length = \"%s\"\n"
            "]",
            ray_length
        );
    }
protected:
    float ray_length;
};

NORI_REGISTER_CLASS(AverageVisibility, "av");
NORI_NAMESPACE_END