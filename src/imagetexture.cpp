#include <nori/texture.h>
#include <nori/object.h>
#include <nori/lodepng.h>
#include <filesystem/resolver.h>

NORI_NAMESPACE_BEGIN

class ImageTexture : public Texture<Color3f> {
public:

    ImageTexture(const PropertyList &props){
        imName = props.getString("ImageName", "");
        imScale = props.getVector2("scale", Vector2f(1));
        filesystem::path filePath = getFileResolver()->resolve(imName);
        lodepng::decode(image, width, height, filePath.str());
    };

    Color3f eval(const Point2f & uv) {

        int v = int((uv.x() * width) / imScale.x());
        int u = int((uv.y() * height) / imScale.y());

        long index = (v * width + u)*4;
        index = index % image.size();

        float r = image[index] / 255.0;
        float g = image[index + 1] / 255.0;
        float b = image[index + 2] / 255.0;

        return Color3f(r, g, b);
    }

    std::string toString() const {
        return tfm::format(
                "ImageTexture[\n"
                "  imName = %s,\n"
                "  scale = %s,\n"
                "]",
                imName,
                imScale.toString()
        );
    }



protected:
    std::string imName;
    Vector2f imScale;
    unsigned width;
    unsigned height;
    std::vector<unsigned char> image;
};

NORI_REGISTER_CLASS(ImageTexture, "imagetexture");

NORI_NAMESPACE_END