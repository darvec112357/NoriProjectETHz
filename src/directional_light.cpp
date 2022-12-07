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

class DirectionalLight : public Emitter {
public:
    DirectionalLight(const PropertyList &props) {
        radiance = props.getColor("radiance");
        direction = props.getVector3("direction");
        //radius = props.getFloat("radius");
    }

    virtual std::string toString() const override {
        return "DirectionalLight[]";
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        //if (lRec.n.dot(lRec.wi) < 0) {
        //    return radiance;
        //}
        return radiance;
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        lRec.wi = -direction.normalized();
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi);
		return eval(lRec);
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        return 1;
    }


protected:
    Color3f radiance;
    Vector3f direction;
};

NORI_REGISTER_CLASS(DirectionalLight, "directional")
NORI_NAMESPACE_END