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

#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/emitter.h>
#include <nori/bsdf.h>
#include <nori/scene.h>
#include <nori/photon.h>

NORI_NAMESPACE_BEGIN

class PhotonMapper : public Integrator {
public:
    /// Photon map data structure
    typedef PointKDTree<Photon> PhotonMap;

    PhotonMapper(const PropertyList &props) {
        /* Lookup parameters */
        m_photonCount  = props.getInteger("photonCount", 1000000);
        m_photonRadius = props.getFloat("photonRadius", 0.0f /* Default: automatic */);
    }

    virtual void preprocess(const Scene *scene) override {
        cout << "Gathering " << m_photonCount << " photons .. ";
        cout.flush();

        /* Create a sample generator for the preprocess step */
        Sampler *sampler = static_cast<Sampler *>(
            NoriObjectFactory::createInstance("independent", PropertyList()));

        /* Allocate memory for the photon map */
        m_photonMap = std::unique_ptr<PhotonMap>(new PhotonMap());
        m_photonMap->reserve(m_photonCount);

		/* Estimate a default photon radius */
		if (m_photonRadius == 0)
			m_photonRadius = scene->getBoundingBox().getExtents().norm() / 500.0f;

		// put your code to trace photons here
        int count = 0;
        while (count < m_photonCount) {
            em_count++;
            Ray3f traced_ray;
            Color3f result = Color3f(0.0f);
            const Emitter* em = scene->getRandomEmitter(sampler->next1D());
            result = em->samplePhoton(traced_ray, sampler->next2D(), sampler->next2D());
            result *= scene->getLights().size();
            while (count < m_photonCount) {
                Intersection its;
                if (!scene->rayIntersect(traced_ray, its))
                    break;
                Frame localFrame = its.shFrame.n;

                if (its.mesh->getBSDF()->isDiffuse()) {
                    m_photonMap->push_back(Photon(its.p, -traced_ray.d, result));
                    count++;
                }

                float success_prob = std::min(result.maxCoeff(), .99f);
                if (sampler->next1D() > success_prob) {
                    break;
                }
                result /= success_prob;

                BSDFQueryRecord BQR_mats = BSDFQueryRecord(localFrame.toLocal(-traced_ray.d));
                BQR_mats.uv = its.uv;
                Color3f BSDF_mats = its.mesh->getBSDF()->sample(BQR_mats, sampler->next2D());
                result *= BSDF_mats;
                traced_ray = Ray3f(its.p, localFrame.toWorld(BQR_mats.wo));
            }
        }


		/* Build the photon map */
        m_photonMap->build();
    }

    virtual Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &_ray) const override {
		// put your code for path tracing with photon gathering here
        Color3f t = Color3f(1.0f);
        Ray3f traced_ray = _ray;
        Color3f result = Color3f(0.0f);
        while (true) {
            Intersection its;
            if (!scene->rayIntersect(traced_ray, its))
                break;
            if (its.mesh->isEmitter()) {
                EmitterQueryRecord EQR_le = EmitterQueryRecord(traced_ray.o, its.p, its.shFrame.n);
                Color3f Le = its.mesh->getEmitter()->eval(EQR_le);
                Le *= t;
                result += Le;
            }
            Frame localFrame = its.shFrame.n;

            if (its.mesh->getBSDF()->isDiffuse()) {
                std::vector<uint32_t> results;
                m_photonMap->search(its.p, m_photonRadius, results);
                Color3f photonDensityEstimation = Color3f(0.0f);
                for (uint32_t i : results) {
                    const Photon& photon = (*m_photonMap)[i];
                    Vector3f incident_direction = localFrame.toLocal(-traced_ray.d);
                    Vector3f outgoing_direction = localFrame.toLocal(photon.getDirection());

                    BSDFQueryRecord BQR_ems = BSDFQueryRecord(incident_direction, outgoing_direction, ESolidAngle);
                    BQR_ems.uv = its.uv;
                    Color3f BSDF_ems = its.mesh->getBSDF()->eval(BQR_ems);
                    BSDF_ems *= photon.getPower();
                    photonDensityEstimation += BSDF_ems;
                }
                photonDensityEstimation *= t;
                photonDensityEstimation /= (M_PI * m_photonRadius * m_photonRadius * em_count);
                result += photonDensityEstimation;
                break;
            }
            float success_prob = std::min(t.maxCoeff(), .99f);
            if (sampler->next1D() > success_prob) {
                break;
            }
            t /= success_prob;

            BSDFQueryRecord BQR_mats = BSDFQueryRecord(localFrame.toLocal(-traced_ray.d));
            BQR_mats.uv = its.uv;
            Color3f BSDF_mats = its.mesh->getBSDF()->sample(BQR_mats, sampler->next2D());
            t *= BSDF_mats;
            traced_ray = Ray3f(its.p, localFrame.toWorld(BQR_mats.wo));
        }
		return result;
    }

    virtual std::string toString() const override {
        return tfm::format(
            "PhotonMapper[\n"
            "  photonCount = %i,\n"
            "  photonRadius = %f\n"
            "]",
            m_photonCount,
            m_photonRadius
        );
    }
private:
    /* 
     * Important: m_photonCount is the total number of photons deposited in the photon map,
     * NOT the number of emitted photons. You will need to keep track of those yourself.
     */ 
    int m_photonCount;
    int em_count=0;
    float m_photonRadius;
    std::unique_ptr<PhotonMap> m_photonMap;
};

NORI_REGISTER_CLASS(PhotonMapper, "photonmapper");
NORI_NAMESPACE_END
