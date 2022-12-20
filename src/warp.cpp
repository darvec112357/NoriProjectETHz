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

#include <nori/warp.h>
#include <nori/vector.h>
#include <nori/frame.h>
#include <random>

NORI_NAMESPACE_BEGIN

Vector3f Warp::sampleUniformHemisphere(Sampler *sampler, const Normal3f &pole) {
    // Naive implementation using rejection sampling
    Vector3f v;
    do {
        v.x() = 1.f - 2.f * sampler->next1D();
        v.y() = 1.f - 2.f * sampler->next1D();
        v.z() = 1.f - 2.f * sampler->next1D();
    } while (v.squaredNorm() > 1.f);

    if (v.dot(pole) < 0.f)
        v = -v;
    v /= v.norm();

    return v;
}

Point2f Warp::squareToUniformSquare(const Point2f &sample) {
    return sample;
}

float Warp::squareToUniformSquarePdf(const Point2f &sample) {
    return ((sample.array() >= 0).all() && (sample.array() <= 1).all()) ? 1.0f : 0.0f;
}

Point2f Warp::squareToUniformDisk(const Point2f &sample) {
    float r = sqrt(sample.x());
    float theta = 2 * M_PI * sample.y();
    return Point2f(r * cos(theta), r * sin(theta));
}

float Warp::squareToUniformDiskPdf(const Point2f &p) {
    if (p.dot(p) <= 1) {
        return 1 / M_PI;
    }
    return 0.0f;
}

Vector3f Warp::squareToUniformSphereCap(const Point2f &sample, float cosThetaMax) {
    float z = sample.x() * (1 - cosThetaMax) + cosThetaMax;
    float r = sqrt(1 - z * z);
    float phi = 2 * M_PI * sample.y();
    return Vector3f(cos(phi) * r, sin(phi) * r, z);
}

float Warp::squareToUniformSphereCapPdf(const Vector3f &v, float cosThetaMax) {
    if (v.norm() <= 1 && v.z()>= cosThetaMax) {
        return 1 / (2 * M_PI * (1 - cosThetaMax));
    }
    return 0;
}

Vector3f Warp::squareToUniformSphere(const Point2f &sample) {
    float z = 2 * sample.x() - 1;
    float r = sqrt(1 - z * z);
    float theta = 2 * M_PI * sample.y();
    return Vector3f(cos(theta) * r, sin(theta) * r, z);
}

float Warp::squareToUniformSpherePdf(const Vector3f &v) {
    if (v.dot(v) <= 1) {
        return 1 / (4 * M_PI);
    }
    return 0;
}

Vector3f Warp::squareToUniformHemisphere(const Point2f &sample) {
    /*float z = sample.x();
    float r = sqrt(1 - z * z);
    float theta = 2 * M_PI * sample.y();
    return Vector3f(cos(theta) * r, sin(theta) * r, z);*/
    float theta = acos(sample.x());
    float phi = 2 * M_PI * sample.y();
    return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

float Warp::squareToUniformHemispherePdf(const Vector3f &v) {
    if (v.norm() <= 1 && v.z()>=0) {
        return 1 / (2 * M_PI);
    }
    return 0;
}



Vector3f Warp::squareToCosineHemisphere(const Point2f &sample) {
    Point2f p = squareToUniformDisk(sample);
    float z = sqrt(1 - p.dot(p));
    return Vector3f(p.x(), p.y(), z);
}

float Warp::squareToCosineHemispherePdf(const Vector3f &v) {
    Vector3f n = Vector3f(0, 0, 1);
    if (v.norm() <= 1 && v.z() >= 0) {
        return (n.dot(v))/M_PI;
    }
    return 0;
}

Vector3f Warp::squareToBeckmann(const Point2f &sample, float alpha) {
    float theta = atan(sqrt(-pow(alpha, 2) * log(1 - sample.x())));
    float phi = 2 * M_PI * sample.y();
    return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

float Warp::squareToBeckmannPdf(const Vector3f &m, float alpha) {
    float theta = acos(m.z()/m.norm());
    if (m.norm() <= 1 && m.z()>=0) {
        return exp(-pow(tan(theta), 2) / pow(alpha, 2)) / (M_PI * pow(alpha, 2) * pow(cos(theta), 3));
    }
    return 0;
}

Vector3f Warp::squareToUniformTriangle(const Point2f &sample) {
    float su1 = sqrtf(sample.x());
    float u = 1.f - su1, v = sample.y() * su1;
    return Vector3f(u,v,1.f-u-v);
}

NORI_NAMESPACE_END
