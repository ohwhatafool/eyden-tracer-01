// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution), m_pos(pos), m_dir(dir), m_up(up)
	{
		// --- PUT YOUR CODE HERE ---

		//define axis
		m_yAxis = -m_up;
		m_xAxis = m_dir.cross(m_up);
		m_aspect = resolution.width / float(resolution.height);

		// opening angle:
		float angleInRad = angle * (float)M_PI / 180.f;
		m_focus = 1.f / tan(angleInRad / 2.f);

		//Checking method: printf("Width is %d ", resolution.width);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		//From the slides
		ray.org = m_pos;
		ray.dir = (m_xAxis * (2.0f * ((x / (float)getResolution().width - .5f) * m_aspect))) + (m_yAxis * (2.0f * (y / (float)getResolution().height - .5f))) + (m_dir * m_focus);
		ray.dir = normalize(ray.dir);

		//putting limit
		ray.t = std::numeric_limits<float>::max();

		return true;
	}

private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};
