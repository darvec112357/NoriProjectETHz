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

#include <nori/shape.h>
#include <nori/bsdf.h>
#include <nori/emitter.h>
#include <nori/warp.h>




NORI_NAMESPACE_BEGIN

class Sphere : public Shape {
public:
    Sphere(const PropertyList & propList) {
        m_position = propList.getPoint3("center", Point3f());
        m_radius = propList.getFloat("radius", 1.f);

        m_bbox.expandBy(m_position - Vector3f(m_radius));
        m_bbox.expandBy(m_position + Vector3f(m_radius));
        //root_of_intersection = 0;
    }

    virtual BoundingBox3f getBoundingBox(uint32_t index) const override { return m_bbox; }

    virtual Point3f getCentroid(uint32_t index) const override { return m_position; }

    virtual bool rayIntersect(uint32_t index, const Ray3f &ray, float &u, float &v, float &t) const override {
        float a = ray.d.dot(ray.d);
        float b = 2 * (ray.o.dot(ray.d)- ray.d.dot(m_position));
        float c = (ray.o-m_position).dot(ray.o - m_position) - m_radius*m_radius;
        float delta = b * b - 4 * a * c;
        if (delta < 0) return false;
        float root1 = (-b + sqrt(delta)) / (2*a);
        float root2 = (-b - sqrt(delta)) / (2*a);
        if (ray.mint <= root2 && root2 <= ray.maxt) {
            t = root2;
            return true;
        }
        /*if (ray.mint <= root2 && root1 > ray.maxt) {
            t = root2;
            return true;
        }*/
        if (ray.mint > root2 && root1> ray.mint && root1 <= ray.maxt) {
            t = root1;
            return true;
        }
                
        return false;
    }

    virtual void setHitInformation(uint32_t index, const Ray3f &ray, Intersection & its) const override {
        its.p = ray.o+its.t*ray.d;
        Vector3f v = its.p - m_position;
        v = v / v.norm();
        its.geoFrame = Frame(v);
        its.shFrame = Frame(v);
        //its.uv = Point2f(1.0, 1.0);
        Point2f uv_coordinates = sphericalCoordinates(v);
        float x = uv_coordinates.x() / (2*M_PI);
        float y= (uv_coordinates.y()-M_PI)/ M_PI;
        its.uv = Point2f(x, y);
        
    }

    virtual void sampleSurface(ShapeQueryRecord & sRec, const Point2f & sample) const override {
        Vector3f q = Warp::squareToUniformSphere(sample);
        sRec.p = m_position + m_radius * q;
        sRec.n = q;
        sRec.pdf = std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }
    virtual float pdfSurface(const ShapeQueryRecord & sRec) const override {
        return std::pow(1.f/m_radius,2) * Warp::squareToUniformSpherePdf(Vector3f(0.0f,0.0f,1.0f));
    }


    virtual std::string toString() const override {
        return tfm::format(
                "Sphere[\n"
                "  center = %s,\n"
                "  radius = %f,\n"
                "  bsdf = %s,\n"
                "  emitter = %s\n"
                "]",
                m_position.toString(),
                m_radius,
                m_bsdf ? indent(m_bsdf->toString()) : std::string("null"),
                m_emitter ? indent(m_emitter->toString()) : std::string("null"));
    }

protected:
    Point3f m_position;
    float m_radius;
    float *root_of_intersection;
};

NORI_REGISTER_CLASS(Sphere, "sphere");
NORI_NAMESPACE_END
