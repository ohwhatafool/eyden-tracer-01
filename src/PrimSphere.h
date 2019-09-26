// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f center, float radius)
		: CPrim(), m_center(center), m_radius(radius)
	{
	}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		//Methods referenced from slides and scratchapixel.com

		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(ray.org - m_center);
		float c = (ray.org - m_center).dot(ray.org - m_center) - m_radius * m_radius;

		float test_val = b * b - (4 * a * c);

		//Solution doesn't exist
		if (test_val < 0)
		{
			return false;
		}

		//t has 2 solutions according to quadratic formula
		float t1 = ((-b) + sqrt(test_val)) / (a * 2);

		float t2 = ((-b) - sqrt(test_val)) / (a * 2);

		float t;

		//we take the smallest t as our final value of t
		if (t1 < t2)
			t = t1;
		else
			t = t2;

		//Range Check -validity check
		if ((t > Epsilon) && (t < ray.t))
		{
			ray.t = t;
			return true;
		}
		else
			return false;
	}

private:
	Vec3f m_center; ///< Position of the center of the sphere
	float m_radius; ///< Radius of the sphere
};
