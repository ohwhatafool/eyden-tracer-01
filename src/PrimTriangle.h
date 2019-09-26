// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f a, Vec3f b, Vec3f c)
		: CPrim(), m_a(a), m_b(b), m_c(c)
	{
	}
	virtual ~CPrimTriangle(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		//Referenced from the slides:
		Vec3f nAB = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f nBC = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f nCA = (m_a - ray.org).cross(m_c - ray.org);

		float s_area = nAB.dot(ray.dir) + nBC.dot(ray.dir) + nCA.dot(ray.dir);
		float lambda1 = nAB.dot(ray.dir) / s_area;
		float lambda2 = nBC.dot(ray.dir) / s_area;
		float lambda3 = nCA.dot(ray.dir) / s_area;

		//Edges check
		if (lambda1 < 0 || lambda2 < 0 || lambda3 < 0)
		{
			return false;
		}

		Vec3f p = lambda1 * m_a + lambda2 * m_b + lambda3 * m_c;

		float t = p[0] / ray.dir[0];

		//range Check
		if (t < Epsilon || t > ray.t)
		{
			return false;
		}

		ray.t = t;

		return true;
	}

private:
	Vec3f m_a; ///< Position of the first vertex
	Vec3f m_b; ///< Position of the second vertex
	Vec3f m_c; ///< Position of the third vertex
};
