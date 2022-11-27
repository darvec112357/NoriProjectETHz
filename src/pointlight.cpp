#include <nori/emitter.h>

NORI_NAMESPACE_BEGIN

class PointLight : public Emitter{

public: 
    PointLight(const PropertyList & propList) {

        position = propList.getPoint3("position", Point3f());
        power = propList.getColor("power", Color3f());

    }
 
    Color3f sample(EmitterQueryRecord &lRec, const Point2f &sample) const {

        lRec.p = position;
        lRec.wi = (lRec.p - lRec.ref)/((lRec.p - lRec.ref).norm());
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, (lRec.p - lRec.ref).norm() - Epsilon);
        return eval(lRec);
    }; 

    Color3f eval(const EmitterQueryRecord &lRec) const {
        return power / (4 * M_PI * (lRec.ref - lRec.p).dot(lRec.ref - lRec.p));
    };

    float pdf(const EmitterQueryRecord &lRec) const {
        return 1.0f;
    };

    std::string toString() const {
        return "PointLight[]";
    }

protected:
    Point3f position;
    Color3f power;
};

NORI_REGISTER_CLASS(PointLight, "point");

NORI_NAMESPACE_END