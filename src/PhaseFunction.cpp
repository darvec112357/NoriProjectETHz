//
// Created by Niklaus on 11.12.19.
//

#include <nori/PhaseFunction.h>

NORI_NAMESPACE_BEGIN

PhaseFunction::PhaseFunction() = default;
PhaseFunction::PhaseFunction(const PropertyList &props) {}

float PhaseFunction::sample(const Vector3f &wo, Vector3f &wi, const Point2f &sample) const {
    wi = Warp::squareToUniformSphere(sample);
    return INV_FOURPI;
}

std::string PhaseFunction::toString() const {
    return tfm::format("[ Isotropic ]");
}

HenyeyGreenstein::HenyeyGreenstein(const PropertyList &props)  {
    g = props.getFloat("g", 0.0f);
}

float HenyeyGreenstein::sample(const Vector3f &wo, Vector3f &wi, const Point2f &sample) const {
    float cosTheta;
    float g2 = g * g;
    if (abs(g) < 1e-3) {
        cosTheta = 1.f - 2.f * sample.x();
    }
    else {
        float t = (1.f - g2) / (1.f - g + 2.f * g * sample.x());
        cosTheta = -(1.f + g2 - t * t) / abs(2.f * g);
    }

    Vector3f v1;
    if (abs(wo.x()) > abs(wo.y()))
        v1 = Vector3f(-wo.z(), 0, wo.x() / sqrt(wo.x() * wo.x() + wo.z() * wo.z()));
    else
        v1 = Vector3f(0, wo.z(), -wo.y() / sqrt(wo.y() * wo.y() + wo.z() * wo.z()));

    Vector3f v2 = wo.cross(v1);

    float phi = 2.f * M_PI * sample.y();
    float sinTheta = sqrt(1.f - cosTheta * cosTheta);
    wi = sinTheta * cos(phi) * v1 + sinTheta * sin(phi) * v2 + cosTheta * -wo;

    return INV_FOURPI * (1.f - g2) / pow(1.f + g2 - 2.f * g * cosTheta, 1.5);
}

std::string HenyeyGreenstein::toString() const {
    return tfm::format("[ HenyeyGreenstein g: %f ]", g);
}

NORI_REGISTER_CLASS(PhaseFunction, "iso");
NORI_REGISTER_CLASS(HenyeyGreenstein, "henyey");
NORI_NAMESPACE_END


