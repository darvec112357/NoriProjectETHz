#include <nori/medium.h>

NORI_NAMESPACE_BEGIN

Medium::Medium(const PropertyList& props) {
    sigmaT = (props.getColor("sigma_t", Color3f(0.2f)));
    albedo = props.getColor("albedo", Color3f(0.2f));
    density_function = props.getInteger("density_function", 0);
    Vector3f dimensions = props.getVector3("dimensions", Vector3f(0.4)).cwiseAbs();
    Vector3f origin = props.getVector3("origin", Vector3f(0.f));
    bounds = BoundingBox3f(origin - dimensions, origin + dimensions);
}

////Homogeneous transmission
//Color3f Medium::Tr(const Ray3f& ray) const {
//    return exp(-sigmaT * ray.d.norm());
//}

//Heterogeneous transmission
Color3f Medium::Tr(const Ray3f& ray, Sampler* sampler, MediumQueryRecord& mi) const {
    float t = Epsilon;
    float transmission = 1;
    while (true) {
        t -= log(1 - sampler->next1D()) / sigmaT.maxCoeff();
        if (t >= mi.tMax || !bounds.rayIntersect(Ray3f(ray(t), ray.d)))
            break;

        float density = Density(ray(t));
        transmission *= 1 - density;
    }
    return Color3f(transmission);
}

//sample a heterogeneous medium interaction
Color3f Medium::sample(const Ray3f& ray, Sampler* sampler, MediumQueryRecord& mi) const {
    float t = Epsilon;
    //delta tracking iterations to sample a medium interaction
    while (true) {
        t -= log(1 - sampler->next1D()) / sigmaT.maxCoeff();
        if (t >= mi.tMax || !bounds.rayIntersect(Ray3f(ray(t), ray.d))) {
            mi.hasinteraction = false;
            break;
        }
        float density = Density(ray(t));
        if (density > sampler->next1D()) {
            mi.hasinteraction = true;
            mi.p = ray(t);
            return albedo;
        }
    }
    return Color3f(1);
}

void Medium::addChild(NoriObject* obj) {
    switch (obj->getClassType()) {
    case EPhaseFunction:
        if (phaseFunction) {
            throw NoriException("Medium: trying to register multiple phaseFunctions!");
        }
        phaseFunction = static_cast<PhaseFunction*>(obj);
        break;
    default:
        throw NoriException("Medium::addChild(<%s>) is not supported!",
            classTypeName(obj->getClassType()));
    }
}


float Medium::Density(const Point3f& p) const {
    if (bounds.contains(p)) {
        if (density_function == 1) {
            //return exp(-abs(p.y()));
            //std::cout << bounds.min.y() << " " << p.y() << std::endl;
            float a = bounds.max.y() - p.y();
            float b = bounds.max.y() - bounds.min.y();
            return a/b;
        }
        
            
        else {
            return 0.5;
        }
            
        
    }
    else {
        return 0.0f;
    }
}

std::string Medium::toString() const {
    return "medium";
}

NORI_REGISTER_CLASS(Medium, "medium")
NORI_NAMESPACE_END