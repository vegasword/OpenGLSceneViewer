#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vector3.h>
#include <Matrix.h>

namespace Renderer
{
	struct CameraInputs
    {
        // Camera directions booleans.
        bool backward, forward, right, left, up ,down;

        // Mouse input related.
        bool firstFrame;
        double deltaX, deltaY, lastX, lastY;
    };

	class Camera
	{
	public:
        CameraInputs inputs;

        Camera();
        Camera(const unsigned int& width, const unsigned int& height,
               const float& fov, const float& near, const float& far, 
               const float& acceleration);
        
        void operator=(const Camera& cam);

		void Update(GLFWwindow* window, const float& deltaTime, CameraInputs* inputs);

        float GetFOV()            const;
        float GetAspect()         const;
        float GetPitch()          const;
        float GetYaw()            const;
        float GetNearDistance()   const;
        float GetFarDistance()    const;
        float GetAcceleration()   const;
        float GetLookAtDistance() const;

        void SetPosition (const Core::Maths::Vector3& _pos);
        void SetRotation (const float& _pitch, const float& _yaw);

        Core::Maths::Vector3 GetPosition()    const;
        Core::Maths::Vector3 GetDirection()   const;
        Core::Maths::Vector3 GetLookAtPoint() const;

        Core::Maths::Matrix4 GetWorldTransform() const;
        Core::Maths::Matrix4 GetPerspective()    const;
        Core::Maths::Matrix4 GetViewMat()        const;
        Core::Maths::Matrix4 GetVPMat()          const;
        Core::Maths::Matrix4 GetLookAtMat()      const;

	private:
        float m_deltaTime;
		float m_fov, m_aspect;
        float m_near, m_far;
        float m_pitch, m_yaw;
        float m_speed, m_acceleration;
        float m_lookAtDist = 2;

        Core::Maths::Vector3 m_position, m_direction, m_lookAtPoint;
	};
}