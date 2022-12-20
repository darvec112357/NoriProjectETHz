/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2015 by Wenzel Jakob

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

#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>
#include <nori/common.h>
#include <nori/texture.h>

NORI_NAMESPACE_BEGIN

class BumpMapping : public BSDF {
public:
    BumpMapping(const PropertyList &propList) {
        if (propList.has("albedo")) {
            PropertyList l;
            l.setColor("value", propList.getColor("albedo"));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
        }
    }

    /// Add texture for the albedo
    virtual void addChild(NoriObject* obj) override {
        switch (obj->getClassType()) {
        case ETexture:
            if (obj->getIdName() == "albedo") {
                if (m_albedo)
                    throw NoriException("There is already an albedo defined!");
                m_albedo = static_cast<Texture<Color3f> *>(obj);
            }
            else {
                throw NoriException("The name of this texture does not match any field!");
            }
            break;

        default:
            throw NoriException("Diffuse::addChild(<%s>) is not supported!",
                classTypeName(obj->getClassType()));
        }
    }

    virtual void activate() override {
        if (!m_albedo) {
            PropertyList l;
            l.setColor("value", Color3f(0.5f));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
            m_albedo->activate();
        }
    }

    virtual Color3f eval(const BSDFQueryRecord& bRec) const override {
        if (bRec.measure != ESolidAngle
            || Frame::cosTheta(bRec.wi) <= 0
            || Frame::cosTheta(bRec.wo) <= 0)
            return Color3f(0.0f);
        return m_albedo->eval(bRec.uv) * INV_PI;
    }

    virtual float pdf(const BSDFQueryRecord& bRec) const override {
        if (bRec.measure != ESolidAngle
            || Frame::cosTheta(bRec.wi) <= 0
            || Frame::cosTheta(bRec.wo) <= 0)
            return 0.0f;
        return INV_PI * Frame::cosTheta(bRec.wo);
    }

    virtual Color3f sample(BSDFQueryRecord& bRec, const Point2f& sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);
        bRec.measure = ESolidAngle;
        bRec.wo = Warp::squareToCosineHemisphere(sample);
        bRec.eta = 1.0f;
        Vector3f wh = (bRec.wi + bRec.wo).normalized();
        bRec.p += 0.1 * wh;
        return m_albedo->eval(bRec.uv);
    }

    virtual std::string toString() const override {
        return "BumpMapping:[]";
    }
private:
    Texture<Color3f>* m_albedo;
};

NORI_REGISTER_CLASS(BumpMapping, "bump");
NORI_NAMESPACE_END
