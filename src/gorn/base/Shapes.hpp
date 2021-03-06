#ifndef __gorn__Shapes__
#define __gorn__Shapes__

#include <glm/glm.hpp>
#include <array>

namespace gorn
{
	class Rect;
	class QuadShape;

    class PlaneShape
    {
    public:
        typedef std::array<glm::vec3, 4> Corners;

        glm::vec3 xaxis;
        glm::vec3 yaxis;
        glm::vec3 center;

        PlaneShape();
        PlaneShape(const glm::vec3& x,
            const glm::vec3& y,
            const glm::vec3& center);
        PlaneShape(const Corners& cs);

        PlaneShape& withXAxis(const glm::vec3& x);
        PlaneShape& withYAxis(const glm::vec3& y);
        PlaneShape& withCenter(const glm::vec3& center);

        Corners corners() const;
        glm::vec3 normal() const;
		QuadShape quad() const;
    };

	class QuadShape
	{
	public:
		typedef std::array<glm::vec3, 4> Corners;
		Corners corners;

		QuadShape();
		QuadShape(const Corners& cs);

		PlaneShape plane() const;
		glm::vec3 normal() const;
	};

    class CubeShape
    {
    public:
		typedef std::array<glm::vec3, 8> Corners;
		typedef std::array<QuadShape, 6> Sides;

		Corners corners;

        CubeShape();
        CubeShape(const Corners& cs);
		CubeShape(const PlaneShape& front, const PlaneShape& back);

		Sides sides() const;
    };

    class SphereShape
    {
    public:
        typedef unsigned int idx_t;
        idx_t rings;
        idx_t sectors;
        glm::vec3 center;

        SphereShape();
        SphereShape& withRings(idx_t rings);
        SphereShape& withSectors(idx_t sectors);
        SphereShape& withCenter(const glm::vec3& center);
    };

}

#endif
