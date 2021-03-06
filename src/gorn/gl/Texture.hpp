#ifndef __gorn__Texture__
#define __gorn__Texture__

#include <gorn/gl/Base.hpp>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>

namespace gorn
{
    class Image;

    class Texture
    {
    private:
        static std::unordered_map<GLenum, GLuint> s_currentIds;
        static std::unordered_map<size_t, GLuint> s_activeIds;
        GLuint _id;
        GLenum _target;
        glm::vec2 _size;
        void cleanup();
    public:
        Texture(GLenum target=GL_TEXTURE_2D);
        ~Texture();

        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;

        Texture(Texture&& other);
        Texture& operator=(Texture&& other);

        GLuint getId() const;
        void setImage(const Image& img, GLint lodLevel=0);
        void setParameter(GLenum name, GLint value);
        void setParameter(GLenum name, GLfloat value);
        void setParameter(GLenum name, const std::vector<GLint>& value);
        void setParameter(GLenum name, const std::vector<GLfloat>& value);
        void bind();
        void attachToFrameBuffer(GLenum type);
        void activate(size_t pos);
        const glm::vec2& getSize() const;
    };
}

#endif
