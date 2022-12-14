#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/warp.h>
#include <nori/texture.h>
#include <nori/shape.h>

NORI_NAMESPACE_BEGIN

class DisneyBSDF : public BSDF {
public:
    DisneyBSDF(const PropertyList &propList) : m_albedo(nullptr) {

        if(propList.has("albedo")) {
            PropertyList l;
            l.setColor("value", propList.getColor("albedo"));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
        }else{
            basecolor = propList.getColor("basecolor",Color3f(0.5f));
        }
        // Normal Mapping
        ifnormalmap = propList.getBoolean("ifNormalMap", false);
        // Disney BSDF
        subsurface = propList.getFloat("subsurface", 0.0f);
        metallic = propList.getFloat("metallic", 0.0f);
        specular = propList.getFloat("specular", 0.5f);
        roughness = propList.getFloat("roughness", 0.5f);
        sheen = propList.getFloat("sheen", 0.0f);
        clearcoat = propList.getFloat("clearcoat", 0.0f);
        sheentint = propList.getFloat("sheentint",0.5f);
        speculartint = propList.getFloat("speculartint",0.0f);
        clearcoatgloss = propList.getFloat("clearcoatgloss", 1.0f);
    }

    virtual ~DisneyBSDF() {
        delete m_albedo;
        ifnormalmap = false;
    }
    
    virtual void addChild(NoriObject *obj) override {
        switch (obj->getClassType()) {
            case ETexture:
                if(obj->getIdName() == "albedo") {
                    if (m_albedo)
                        throw NoriException("There is already an albedo defined!");
                    m_albedo = static_cast<Texture<Color3f> *>(obj);
                }
                else {
                    throw NoriException("The name of this texture does not match any field!");
                }
                break;

            default:
                throw NoriException("DisneyBSDF::addChild(<%s>) is not supported!",
                                    classTypeName(obj->getClassType()));
        }
    }

    virtual void activate() override {
        if(!m_albedo) {
            PropertyList l;
            l.setColor("value", Color3f(0.5f));
            m_albedo = static_cast<Texture<Color3f> *>(NoriObjectFactory::createInstance("constant_color", l));
            m_albedo->activate();
        }
    }

    float lerp(float t, float v1, float v2) const {
        return ((float) 1 - t) * v1 + t * v2;
    }

    Color3f lerp(const Color3f& a, const Color3f& b, const float& ratio) const { 
        return Color3f(
            (1 - ratio) * a.r() + ratio * b.r(),
            (1 - ratio) * a.g() + ratio * b.g(),
            (1 - ratio) * a.b() + ratio * b.b()
        ); 
    }

    float SchlickWeight(float x) const {
        x = clamp(1-x, 0.0f, 1.0f);
        return std::pow(x, 5);
    }


    float squareToGTR1Pdf(const Vector3f & m, float alpha) const {
        float cosTheta = m.z() / m.norm();
        if (alpha >= 1)
            return INV_PI;
        return (abs(m.norm() - 1) < Epsilon && m.z() >= 0) * cosTheta * (pow(alpha, 2) - 1)*INV_PI/(2*std::log(alpha) * (1 + pow(cosTheta, 2) * (pow(alpha, 2) - 1)));
    }

    float squareToGTR2Pdf(const Vector3f & m, float alpha) const{
        float cosTheta = m.z() / m.norm();
        return (abs(m.norm() - 1) < Epsilon && m.z() >= 0) * pow(alpha, 2) * cosTheta * INV_PI / pow(1 + pow(cosTheta, 2) * (pow(alpha, 2) - 1), 2);
    }

    Vector3f squareToGTR1Sample(const Point2f & sample, float alpha) const{
        float phi = 2 * M_PI * sample[0];
        float theta = 0;
        if (alpha < 1)
            theta = acos(std::sqrt((1 - std::pow(std::pow(alpha, 2), 1 - sample[1])) / (1 - std::pow(alpha, 2))));
        return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    }

    Vector3f squareToGTR2Sample(const Point2f & sample, float alpha) const {
        float phi = 2 * M_PI * sample[0];
        float theta = acos(std::sqrt((1 - sample[1]) / (1 + (std::pow(alpha, 2) - 1) * sample[1])));
        return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
    }

    float SmithGGX(float cT, float a) const {
        return 1 / (cT + std::sqrt(pow(cT, 2) + std::pow(a, 2) - std::pow(cT * a, 2)));
    }

    virtual Color3f eval(const BSDFQueryRecord &bRec) const override {

        float ci =  Frame::cosTheta(bRec.wi);
        float co =  Frame::cosTheta(bRec.wo);
        Normal3f wh = (bRec.wo + bRec.wi).normalized();

        if (ci <= 0 || co <= 0)
            return Color3f(0.0f);

        Color3f Cdlin = basecolor.pow(2.2);
        float Cdlum = 0.3f * Cdlin.x() + 0.6f*Cdlin.y() + 0.1f*Cdlin.z();
        Color3f Ctint = (Cdlum > 0) ? Color3f(Cdlin.x() / Cdlum, Cdlin.y() / Cdlum, Cdlin.z() / Cdlum) : Color3f(1.0f);
        Color3f Ctintmix = 0.08f * specular * lerp(Color3f(1,1,1), Ctint, speculartint);
        Color3f Cspec = lerp(Ctintmix, Cdlin, metallic);

        float fd90 = 0.5 + 2 * pow(bRec.wo.dot(wh), 2) * roughness;
		float fl = SchlickWeight(co);
		float fv = SchlickWeight(ci);
		float fd = lerp(fl, 1, fd90) * lerp(fv, fd90, 1);

        float fss90 = pow(bRec.wo.dot(wh), 2) * roughness;
		float fss = lerp(fl, 1.0, fss90) * lerp(fv, 1.0, fss90);
		float ss = 1.25f * (fss * (1 / (co + ci) - 0.5f) + 0.5f);

        float alpha = std::max(0.01, pow(roughness, 2));
		float ds = squareToGTR2Pdf(wh, alpha);
		float fh = SchlickWeight(bRec.wo.dot(wh));
		Color3f fs = lerp(Cspec, Color3f(1,1,1), fh);
		float gs = SmithGGX(co, alpha) * SmithGGX(ci, alpha);

        Color3f Csheen = lerp(Color3f(1, 1, 1), Ctint, sheentint);
		Color3f fsheen = fh * sheen * Csheen;

        float dr = squareToGTR1Pdf(wh, lerp(clearcoatgloss, 0.1f, 0.001f));
		float fr = lerp(fh, 0.04f, 1.0f);
		float Gr = SmithGGX(co, 0.25f) * SmithGGX(ci, 0.25f);

        Color3f result = Color3f(
            (1 - metallic) * (INV_PI * lerp(subsurface, fd, ss) * Cdlin.r() + fsheen.r()),
            (1 - metallic) * (INV_PI * lerp(subsurface, fd, ss) * Cdlin.g() + fsheen.g()),
            (1 - metallic) * (INV_PI * lerp(subsurface, fd, ss) * Cdlin.b() + fsheen.b())
        );

        result += (gs * fs * ds);
        result.r() += (clearcoat * Gr * fr * dr);
        result.g() += (clearcoat * Gr * fr * dr);
        result.b() += (clearcoat * Gr * fr * dr);
        result /= 4;

        return result;
    }

    virtual float pdf(const BSDFQueryRecord &bRec) const override {
        
        if (bRec.measure != ESolidAngle
            || Frame::cosTheta(bRec.wi) <= 0
            || Frame::cosTheta(bRec.wo) <= 0)
            return 0.0f;

        Normal3f wh = (bRec.wo + bRec.wi).normalized();
        float gtr2r = 1 / (1 + clearcoat);
		float pdiffuse = (1 - metallic) / 2;
        float alpha = std::max(0.01, pow(roughness, 2));
        return pdiffuse * Frame::cosTheta(bRec.wo) * INV_PI
				+ (1 - pdiffuse) * (gtr2r * squareToGTR2Pdf(wh, alpha) + 
                (1 - gtr2r) * squareToGTR1Pdf(wh, lerp(clearcoatgloss, 0.1f, 0.001f)));
    }

    virtual Color3f sample(BSDFQueryRecord &bRec, const Point2f& _sample) const override {
        if (Frame::cosTheta(bRec.wi) <= 0)
            return Color3f(0.0f);
        bRec.measure = ESolidAngle;
        float pdiffuse = (1 - metallic) / 2;
        Point2f sample = _sample;
        if (sample.x() < pdiffuse) {
            sample.x() /= pdiffuse;
            bRec.wo = Warp::squareToCosineHemisphere(sample);
        }else{
            sample.x() = (sample.x() - pdiffuse) / (1 - pdiffuse);
            float gtr2r = 1 / (1 + clearcoat);

            if (sample.x() < gtr2r) {
                sample.x() /= gtr2r;
				Vector3f wh = squareToGTR2Sample(sample, std::max(0.01, std::pow(roughness, 2)));
				bRec.wo = ((2.0f * wh.dot(bRec.wi) * wh) - bRec.wi).normalized();
			} else {
                sample.x() = (sample.x() - gtr2r) / (1 - gtr2r);
				Vector3f wh = squareToGTR1Sample(sample, lerp(clearcoatgloss, 0.1f, 0.001f));
				bRec.wo = ((2.0f * wh.dot(bRec.wi) * wh) - bRec.wi).normalized();
			}
        }

        if (Frame::cosTheta(bRec.wo) <= 0 || pdf(bRec) <= 0 || eval(bRec).minCoeff() <= 0) {
            bRec.wo *= 0;
            return Color3f(0.0f);
        }else
            return eval(bRec) * Frame::cosTheta(bRec.wo) / pdf(bRec);
    }

    bool isDisneyBSDF() const {
        return true;
    }

    virtual bool ifNormalMap(Texture<Color3f>* &normalMap) const override {
        if (ifnormalmap) {
            normalMap = m_albedo;
            return true;
        }
        return false;
    }

    virtual std::string toString() const override {
        return tfm::format(
            "DisneyBSDF[\n"
            "  albedo = %s\n"
            "  subsurface = %f,\n"
            "  metallic = %f,\n"
            "  specular = %f,\n"
            "  speculartint = %f,\n"
            "  roughness = %f\n"
            "  sheen = %f\n"
            "  sheentint = %f\n"
            "  clearcoat = %f\n"
            "  clearcoatgloss = %f\n"
            "]",
            m_albedo ? indent(m_albedo->toString()) : std::string("null"),
            subsurface,
            metallic,
            specular,
            speculartint,
            roughness,
            sheen,
            sheentint,
            clearcoat,
            clearcoatgloss
        );
    }

    virtual EClassType getClassType() const override { return EBSDF; }

    

private:
    Texture<Color3f> * m_albedo;
    bool ifnormalmap;
    Color3f basecolor;
    float subsurface;
    float metallic;
    float specular;
    float roughness;
    float sheen;
    float clearcoat;
    float sheentint;
    float speculartint;
    float clearcoatgloss;
};

NORI_REGISTER_CLASS(DisneyBSDF, "disney_bsdf");
NORI_NAMESPACE_END