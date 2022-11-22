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
        if (lRec.n.dot(-lRec.wi) >= 0)
            return m_radiance;
        return Color3f(0.0f);
    }

    virtual Color3f sample(EmitterQueryRecord & lRec, const Point2f & sample) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        ShapeQueryRecord sRec = ShapeQueryRecord(lRec.ref);
        m_shape->sampleSurface(sRec, sample);

        lRec.n = sRec.n;
        lRec.pdf = sRec.pdf;
        lRec.p = sRec.p;
        lRec.wi = (lRec.p - lRec.ref)/((lRec.p - lRec.ref).norm());
        lRec.shadowRay = Ray3f(lRec.ref, lRec.wi, Epsilon, (lRec.p - lRec.ref).norm() - Epsilon);

        if (pdf(lRec) > 0.0f){
            Color3f lr = eval(lRec);
            lr /= pdf(lRec);
            return lr;
        }
            
        return Color3f(0.0f);
        
    }

    virtual float pdf(const EmitterQueryRecord &lRec) const override {
        if(!m_shape)
            throw NoriException("There is no shape attached to this Area light!");

        if (lRec.n.dot(-lRec.wi) <= 0)
            return 0.0f;

        ShapeQueryRecord sRec = ShapeQueryRecord(lRec.ref, lRec.p);
		float pdf = m_shape->pdfSurface(sRec);
        
        float cos = abs((lRec.wi.dot(lRec.n)));
        float distance = (lRec.p - lRec.ref).norm();

        if ((distance * distance) / cos > __FLT_MAX__)
            return pdf * __FLT_MAX__;
        
        return (pdf * distance * distance) / cos;
    }


    virtual Color3f samplePhoton(Ray3f &ray, const Point2f &sample1, const Point2f &sample2) const override {

        ShapeQueryRecord sRec;
        m_shape->sampleSurface(sRec, sample1);
        
        Vector3f d = Frame(sRec.n).toWorld(Warp::squareToCosineHemisphere(sample2));
        ray = Ray3f(sRec.p, d);

        if (sRec.pdf == 0) {
            return Color3f(0.0f);
        }

        EmitterQueryRecord eRec(sRec.p + d, sRec.p, sRec.n);
        Color3f Le = eval(eRec);

        Le *= M_PI;
        Le /= sRec.pdf;

        return Le;

    }


protected:
    Color3f m_radiance;
};

NORI_REGISTER_CLASS(AreaEmitter, "area")
NORI_NAMESPACE_END