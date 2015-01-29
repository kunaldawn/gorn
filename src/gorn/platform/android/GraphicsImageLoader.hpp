
#ifndef __gorn__GraphicsImageLoader__
#define __gorn__GraphicsImageLoader__

#include <gorn/asset/DataAssetLoader.hpp>

class JniObject;

namespace gorn {

    class Image;

    class GraphicsImageLoader : public DataAssetLoader<Image>
    {
    private:
        static JniObject& getJniObject();
    public:
        bool validate(const Data& input) const;
        Image load(Data&& input) const;
    };
}

#endif
