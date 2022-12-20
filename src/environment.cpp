#include <nori/emitter.h>
#include <nori/warp.h>
#include <nori/shape.h>
#include <nori/bitmap.h>
#include <nori/color.h>

NORI_NAMESPACE_BEGIN

class EnvironmentEmitter : public Emitter {

public:
    explicit EnvironmentEmitter(const PropertyList& props) {
        std::string path = props.getString("filename");
        map = Bitmap(path);
        rows = map.rows();
        cols = map.cols();
        conditionalPdfPhi = Eigen::MatrixXf(rows, cols);
        conditionalCdfPhi = Eigen::MatrixXf(rows, cols);
        preCompute();
    }

    // Bilinear interpolation
    static Color3f bilinear(const Color3f& q11, const Color3f& q12, const Color3f& q21, const Color3f& q22, const float& t1, const float& t2) {
        Color3f temp1 = (1 - t1) * q11 + t1 * q21;
        Color3f temp2 = (1 - t2) * q12 + t2 * q22;
        return (1 - t2) * temp1 + t2 * temp2;
    }
    void preCompute() {
        // Luminance * sinTheta
        pdfTheta = Eigen::VectorXf(rows);
        Eigen::MatrixXf luminance(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                float theta = M_PI * i / rows;
                luminance(i, j) = map(i, j).getLuminance() * sin(theta);
                pdfTheta(i) += luminance(i, j);
            }
        }
        pdfTheta /= pdfTheta.sum();
        computeCdf(pdfTheta, cdfTheta);
        for (int i = 0; i < rows; ++i) {
            conditionalPdfPhi.row(i) = luminance.row(i) / luminance.row(i).sum();
            Eigen::VectorXf cdf;
            computeCdf(conditionalPdfPhi.row(i).transpose(), cdf);
            conditionalCdfPhi.row(i) = cdf;
        }
    }

    static void computeCdf(const Eigen::VectorXf& pdf, Eigen::VectorXf& cdf) {
        int n = pdf.size();
        cdf = Eigen::VectorXf(n);
        cdf(0) = pdf(0);
        for (int i = 1; i < n; ++i) {
            cdf(i) = cdf(i - 1) + pdf(i - 1);
        }
    }

    static int binarySearch(const Eigen::VectorXf& cdf, const double& sample) {
        int n = cdf.size();
        int left = 0;
        int right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (cdf(mid) == sample) {
                return mid;
            }
            else if (cdf(mid) < sample) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1;
    }

    Color3f eval(const EmitterQueryRecord& lRec) const override {
        Point2f uv = get_uv(lRec);
        float u = uv.x();
        float v = uv.y();
        
        int x1 = floor(u);
        int y1 = floor(v);
        int x2 = x1 + 1;
        int y2 = y1 + 1;

        Color3f q11 = (x1 >= 0 && x1 < rows && y1 >= 0 && y1 < cols) ? map(x1, y1) : Color3f(0.0f);
        Color3f q12 = (x1 >= 0 && x1 < rows && y2 >= 0 && y2 < cols) ? map(x1, y2) : Color3f(0.0f);
        Color3f q21 = (x2 >= 0 && x2 < rows && y1 >= 0 && y1 < cols) ? map(x2, y1) : Color3f(0.0f);
        Color3f q22 = (x2 >= 0 && x2 < rows && y2 >= 0 && y2 < cols) ? map(x2, y2) : Color3f(0.0f);

        float a = u - x1;
        float b = v - y1;

        return abs(bilinear(q11, q12, q21, q22, a, b));
    }

    Color3f sample(EmitterQueryRecord& lRec, const Point2f& sample) const override {

        int i = binarySearch(cdfTheta, sample.x());
        int j = binarySearch(conditionalCdfPhi.row(i), sample.y());

        float theta = M_PI * i / rows;
        float phi = 2 * M_PI * j / cols;

        lRec.wi = sphericalDirection(theta, phi);
        Ray3f ray(lRec.ref, lRec.wi);

        float pdfValue = pdf(lRec);
        if (pdfValue == 0) {
            return 0;
        }

        float Jacobian = cols * rows / (2 * M_PI * M_PI * Frame::sinTheta(lRec.wi));
        return eval(lRec) / (Jacobian * pdfValue);
    }

    float pdf(const EmitterQueryRecord& lRec) const override {
        Point2f uv = get_uv(lRec);
        int u = round(uv.x());
        int v = round(uv.y());

        if (pdfTheta(u) == 0) {
            return 0;
        }
        return pdfTheta(u) * conditionalPdfPhi(u, v);
    }

    Point2f get_uv(const EmitterQueryRecord& lRec) const {
        Point2f uv = sphericalCoordinates(lRec.wi);
        float u = uv.x() * rows / M_PI;
        float v = uv.y() * cols / (2 * M_PI);
        return Point2f(u, v);
    }

    std::string toString() const override {
        return tfm::format(
            "EnvironmentEmitter[]"
        );
    }
private:
    Bitmap map;
    int rows;
    int cols;
    Eigen::VectorXf pdfTheta;
    Eigen::VectorXf cdfTheta;
    Eigen::MatrixXf conditionalPdfPhi;
    Eigen::MatrixXf conditionalCdfPhi;
};

NORI_REGISTER_CLASS(EnvironmentEmitter, "environment")
NORI_NAMESPACE_END