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

class AreaEmitter : public Emitter {
public:
    AreaEmitter(const PropertyList &props) {
        m_radiance = props.getColor("radiance");
    }

    virtual std::string toString() const override {
        return tfm::format(
                "AreaLight[\n"
                "  radiance = %s,\n"
                "]",
                m_radiance.toString());
    }

    virtual Color3f eval(const EmitterQueryRecord & lRec) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        if (lRec.n.dot(lRec.wi) < 0) {
            return m_radiance;
        }
        return Color3f(0.0f);
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");
        ShapeQueryRecord SQR = ShapeQueryRecord(lRec.ref);
        m_shape->sampleSurface(SQR, sample);
        lRec.p = SQR.p;
        lRec.pdf = SQR.pdf;
        lRec.n = SQR.n;
		float distance = (lRec.p - lRec.ref).norm();
        lRec.wi = (lRec.p - lRec.ref) / distance;
		lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, distance - Epsilon);
        float p = pdf(lRec);
		Color3f L = eval(lRec); //L is radiance. 
        if (p > 0) {
            return Color3f(L.r() / p, L.g() / p, L.b() / p);
        }

		return Color3f(0.0f);
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");
        
        if (lRec.n.dot(lRec.wi) < 0) {
            ShapeQueryRecord SQR = ShapeQueryRecord(lRec.ref, lRec.p);
            float pdf = m_shape->pdfSurface(SQR);
            float coswi = abs(lRec.n.dot(lRec.wi));
            float square_distance = (lRec.p - lRec.ref).squaredNorm();
            float temp = square_distance / coswi;
            if (temp > FLT_MAX)
                temp = FLT_MAX;
            return pdf * temp;
        }
        return 0;
    }


    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {
        ShapeQueryRecord SQR;
        m_shape->sampleSurface(SQR, sample1);
        Vector3f direction = Warp::squareToCosineHemisphere(sample2);
        Frame frame = SQR.n;
        direction = frame.toWorld(direction);
        ray = Ray3f(SQR.p, direction);
        
        float pdf = SQR.pdf;
        if (pdf > 0) {
            EmitterQueryRecord EQR = EmitterQueryRecord(SQR.p + direction, SQR.p, SQR.n);
            Color3f Le = eval(EQR);
            Le *= (M_PI / pdf);
            return Le;
        }
        return Color3f(0.0f);
    }


protected:
    Color3f m_radiance;
};

NORI_REGISTER_CLASS(AreaEmitter, "area")
NORI_NAMESPACE_END