// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 */
	CPrimPlane(Vec3f origin, Vec3f normal)
		: CPrim(), m_normal(normal), m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		//referenced from the slides
		float numerator = m_normal.dot(m_origin - ray.org);
		float denominator = m_normal.dot(ray.dir);
		float t;

		//invalid solution
		if (denominator == 0)
		{
			return 0;
		}
		else
		{
			t = numerator / denominator;
		}

		//Range Check

		if (t < Epsilon || t > ray.t)
		{
			return false;
		}
		//Finalise ray.t
		ray.t = t;

		return true;
	}

private:
	Vec3f m_normal; ///< Point on the plane
	Vec3f m_origin; ///< Normal to the plane
};
