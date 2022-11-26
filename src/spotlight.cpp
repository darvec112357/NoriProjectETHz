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
        TotalWidth = props.getFloat("TotalWidth");
        FalloffStart = props.getFloat("FalloffStart");
        origin = props.getPoint3("origin");
        lookat = props.getPoint3("lookat");
        direction = Vector3f(lookat.x() - origin.x(), lookat.y() - origin.y(), lookat.z() - origin.z());
        cosFalloffStart = cos(FalloffStart * M_PI / 180);
        cosTotalWidth = cos(TotalWidth * M_PI / 180);
        //std::cout << cosFalloffStart << std::endl;
        //std::cout << cosTotalWidth << std::endl;
    }

    virtual std::string toString() const override {
        return "SpotLight[]";
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        return power / 2 * (1 - 0.5 * (cosFalloffStart + cosTotalWidth));
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        Point3f ref = lRec.ref;
        lRec.p = origin;
        lRec.wi = (origin - ref).normalized();
        lRec.n = direction.normalized();
		float distance = (origin - ref).norm();
		lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, distance - Epsilon);
        float costheta = lRec.n.dot(-lRec.wi);
        Color3f intensity = power / (4 * M_PI);
       
        return intensity*fallout(costheta);
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {        
        return lRec.pdf;
    }

    virtual float fallout(float costheta) const{
        if (costheta > cosFalloffStart) return 1;
        if (costheta < cosTotalWidth) return 0;
        float TotalWidth_r = TotalWidth * M_PI / 180;
        float FalloffStart_r = FalloffStart * M_PI / 180;
        float m_invTransitionWidth = 1 ;
        return (TotalWidth_r - std::acos(costheta)) / (TotalWidth_r - FalloffStart_r);
    }


protected:
    Color3f power;
    float TotalWidth, FalloffStart;
    float cosTotalWidth, cosFalloffStart;
    Point3f origin;
    Point3f lookat;
    Vector3f direction;
};

NORI_REGISTER_CLASS(SpotLight, "spot")
NORI_NAMESPACE_END