/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Romain Prévost

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

class SpotLight : public Emitter {
public:
    SpotLight(const PropertyList &props) {
        power = props.getColor("power");
        TotalWidth = props.getFloat("TotalWidth") * M_PI / 180;
        FallOffStart = props.getFloat("FallOffStart") * M_PI / 180;
        origin = props.getPoint3("origin");
        lookat = props.getPoint3("lookat");
        direction = Vector3f(lookat.x() - origin.x(), lookat.y() - origin.y(), lookat.z() - origin.z());
        cosFalloffStart = cos(FallOffStart);
        cosTotalWidth = cos(TotalWidth);
    }

    virtual std::string toString() const override {
        return "SpotLight[]";
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        float costheta = lRec.n.dot(-lRec.wi);
        return power * fallout(costheta) / 2 * (1 - 0.5f * (cosFalloffStart + cosTotalWidth));
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        Point3f ref = lRec.ref;
        lRec.p = origin;
        lRec.wi = (origin - ref).normalized();
        lRec.n = direction.normalized();
		float distance = (origin - ref).norm();
		lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, distance - Epsilon);
        return eval(lRec);
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {        
        return 1.0f;
    }

    virtual float fallout(float costheta) const{
        if (costheta > cosFalloffStart) return 1;
        else if (costheta < cosTotalWidth) return 0;
        return (TotalWidth - std::acos(costheta)) / (TotalWidth - FallOffStart);
    }


protected:
    Color3f power;
    float TotalWidth, FallOffStart;
    float cosTotalWidth, cosFalloffStart;
    Point3f origin;
    Point3f lookat;
    Vector3f direction;
};

NORI_REGISTER_CLASS(SpotLight, "spot")
NORI_NAMESPACE_END