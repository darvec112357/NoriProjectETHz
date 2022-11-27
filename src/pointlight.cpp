#include <nori/emitter.h>

NORI_NAMESPACE_BEGIN

class PointLight : public Emitter{

public: 
    PointLight(const PropertyList & propList) {

        position = propList.getPoint3("position");
        power = propList.getColor("power");

    }

    Color3f sample(EmitterQueryRecord &lRec, const Point2f &sample) const {
        Point3f ref = lRec.ref;
        lRec.p = position;
        lRec.wi = position-ref;
        lRec.wi = lRec.wi / lRec.wi.norm();
        lRec.shadowRay = Ray3f(lRec.ref,lRec.wi,Epsilon,(position - ref).norm()-Epsilon);
        return eval(lRec);
    }; 

    Color3f eval(const EmitterQueryRecord &lRec) const {
        Point3f ref = lRec.ref;
        Point3f p = lRec.p;
        float area = (ref - p).dot(ref - p) * 4 * M_PI;
        return Color3f(power.x() / area, power.y() / area, power.z() / area);
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