
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#include <JniObject.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/asset/Image.hpp>
#include <android/log.h>

namespace gorn
{

	JniObject& GraphicsImageLoader::getJniObject()
	{
		static JniObject obj = JniObject::findSingleton("me.ibero.gorn.NativeBridge");
		return obj;
	}

    bool GraphicsImageLoader::validate(const Data& input) const NOEXCEPT
    {
        return true;
    }

    Image GraphicsImageLoader::load(const Data& input) const
    {
		try
		{
            auto data = Data(getJniObject().call("loadImage",
                std::vector<uint8_t>(), input.mem()));
            if(data.empty())
            {
    			throw Exception("Could not decode image data.");        
            }
            auto info = getJniObject().call("getImageInfo", std::vector<int>());
            bool withAlpha = info[2] != 0;
            auto size = glm::vec2(info[0], info[1]);
			return Image(std::move(data), size, withAlpha, BasicType::UnsignedByte);
		}
		catch(const JniException& e)
		{
			throw Exception(std::string("JNI Error loading image: ")+e.what());
		}
	}

}
