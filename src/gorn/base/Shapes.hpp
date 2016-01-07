#ifndef __gorn__Shapes__
#define __gorn__Shapes__

#include <glm/glm.hpp>
#include <array>

namespace gorn
{
    class PlaneShape
    {
    public:
        typedef std::array<glm::vec3,4> Corners;

        glm::vec3 topright;
        glm::vec3 topleft;
        glm::vec3 bottomleft;
        glm::vec3 bottomright;

        PlaneShape();
        PlaneShape(const glm::vec3& topright,
            const glm::vec3& topleft,
            const glm::vec3& bottomleft,
            const glm::vec3& bottomright);
        PlaneShape(const Corners& corners);

        PlaneShape& withTopLeft(const glm::vec3& p);
        PlaneShape& withTopRight(const glm::vec3& p);
        PlaneShape& withBottomLeft(const glm::vec3& p);
        PlaneShape& withBottomRight(const glm::vec3& p);

        Corners corners() const;
    };

    class CubeShape
    {
    public:
        typedef std::array<glm::vec3,8> Corners;
        PlaneShape front;
        PlaneShape back;

        CubeShape();
        CubeShape(const PlaneShape& front, const PlaneShape& back);
        CubeShape(const Corners& corners);

        CubeShape& withFront(const PlaneShape& front);
        CubeShape& withBack(const PlaneShape& back);

        Corners corners() const;
    };

    class SphereShape
    {
    public:
        size_t rings;
        size_t sectors;
        glm::vec3 center;

        SphereShape();
        SphereShape& withRings(size_t rings);
        SphereShape& withSectors(size_t sectors);
        SphereShape& withCenter(const glm::vec3& center);
    };

}

#endif
