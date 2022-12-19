#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Constants.h>
#include <Arithmetic.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Vector4.h>
#include <Matrix.h>
#include <ResourceManager.h>
#include <Camera.h>

using namespace std;
using namespace Core;
using namespace Renderer;

// ===================================================================
// Camera constructors.
// ===================================================================

Camera::Camera()
{
    inputs.backward = 0;
    inputs.forward  = 0;
    inputs.right    = 0;
    inputs.left     = 0; 
    inputs.down     = 0;
    inputs.deltaX   = 0;
    inputs.deltaY   = 0;
    inputs.lastX    = 0;
    inputs.lastY    = 0; 
    inputs.up       = 0;
    inputs.down     = 0;
    inputs.firstFrame = 1;
     
    m_fov = m_near = m_far = m_acceleration = 
        m_pitch = m_yaw = m_speed  = m_lookAtDist = m_aspect = 0;

    m_position  = Maths::Vector3();
    m_direction = Maths::Vector3();
}

Camera::Camera(const unsigned int& width, const unsigned int& height,
              const float& fov, const float& near, const float& far, 
              const float& acceleration)
    : m_fov(fov), m_near(near), m_far(far), m_acceleration(acceleration)
{
    inputs.backward = 0;
    inputs.forward  = 0;
    inputs.right    = 0;
    inputs.left     = 0; 
    inputs.down     = 0;
    inputs.deltaX   = 0;
    inputs.deltaY   = 0;
    inputs.lastX    = 0;
    inputs.lastY    = 0; 
    inputs.up       = 0;
    inputs.down     = 0;
    inputs.firstFrame = 1;

    m_lookAtDist = 2;
    m_pitch = m_yaw = m_speed = 0;
    m_aspect = (float) width / height;

    m_position  = Maths::Vector3();
    m_direction = Maths::Vector3();
}

// ===================================================================
// Camera operator.
// ===================================================================

void Camera::operator=(const Camera& cam)
{
	m_fov          = cam.GetFOV();
    m_aspect       = cam.GetAspect();
    m_near         = cam.GetNearDistance();
    m_far          = cam.GetFarDistance();
    m_pitch        = cam.GetPitch();
    m_yaw          = cam.GetYaw();
    m_acceleration = cam.GetAcceleration();
    m_lookAtDist   = cam.GetLookAtDistance();
    m_position     = cam.GetPosition();
    m_direction    = cam.GetDirection();
    m_lookAtPoint  = cam.GetLookAtPoint();
}

// ===================================================================
// Camera constructor.
// ===================================================================

void Camera::Update(GLFWwindow* window, const float& deltaTime, CameraInputs* inputs)
{
    // Update camera only when the window is focused.
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED))
    {
        // Set speed according to deltatime.
        m_speed = deltaTime * m_acceleration;

        // Inputs to camera values.
        m_direction = Maths::Vector3();
        if (inputs->backward) m_direction.z +=  1;
        if (inputs->forward)  m_direction.z += -1;
        if (inputs->right)    m_direction.x +=  1;
        if (inputs->left)     m_direction.x += -1;
        if (inputs->up)       m_direction.y +=  1;
        if (inputs->down)     m_direction.y += -1;

        // Update movements according to camera type.
        // Rotate camera (Yaw locked between -90° and 90°, Pitch reset to 0 when it reaches 360°).
        SetRotation(fmodf(m_pitch - (float)inputs->deltaX / 180, 2 * PI), 
                    Clamp(m_yaw   + (float)inputs->deltaY / 180, -PI / 2 + 0.001f, PI / 2 - 0.001f));

        // Move according to the camera's pitch by spherical coordinates system.
        m_position += GetSphericalCoords(m_speed, PI / 2, 2 * PI - m_pitch)          * m_direction.x
                   +  GetSphericalCoords(m_speed, PI / 2, 2 * PI - m_pitch - PI / 2) * m_direction.z;
        m_position.y += m_direction.y * m_speed;
    }

    // Bind camera position to fragment shader.
	glUniform3fv(glGetUniformLocation(ResourceManager::shaderProgram, "viewPos"), 1, &m_position.x);
}

// ===================================================================
// Camera public methods.
// ===================================================================

float Camera::GetFOV()            const { return m_fov;          }
float Camera::GetAspect()         const { return m_aspect;       }
float Camera::GetPitch()          const { return m_pitch;        }
float Camera::GetYaw()            const { return m_yaw;          }
float Camera::GetNearDistance()   const { return m_near;         }
float Camera::GetFarDistance()    const { return m_far;          }
float Camera::GetAcceleration()   const { return m_acceleration; }
float Camera::GetLookAtDistance() const { return m_lookAtDist;   }

Maths::Vector3 Camera::GetPosition()    const { return m_position;    }
Maths::Vector3 Camera::GetDirection()   const { return m_direction;   }
Maths::Vector3 Camera::GetLookAtPoint() const { return m_lookAtPoint; }

void Camera::SetPosition(const Maths::Vector3& pos)                   { m_position = pos;             }
void Camera::SetRotation(const float& pitch, const float& yaw) { m_pitch = pitch; m_yaw = yaw; }

Matrix4 Camera::GetWorldTransform() const
{
    Matrix4 viewMat = GetViewMat();
    return viewMat.Inv4();
}

Matrix4 Camera::GetPerspective() const
{
    float yScale = 1 / tan(DegToRad(m_fov) / 2);
    float xScale = yScale / m_aspect;

    return Matrix4(
        xScale, 0,      0,                                 0,
        0,      yScale, 0,                                 0,
        0,      0,      m_far / (m_far - m_near),          1,
        0,      0,    - m_far * m_near / (m_far - m_near), 0
    );
}

Matrix4 Camera::GetViewMat() const
{
    Matrix4 output(true);
    return output * GetTransformMatrix(-m_position, { m_yaw, m_pitch, 0 }, { 1, 1, 1 }, true);
}

Matrix4 Camera::GetVPMat() const
{
    return GetViewMat() * GetPerspective();
}

Matrix4 Camera::GetLookAtMat() const
{
    Maths::Vector3 zAxis =  Maths::Vector3(m_position, m_lookAtPoint).GetNormalized();
    Maths::Vector3 xAxis = (Maths::Vector3{0, 1, 0} ^ zAxis).GetNormalized();
    Maths::Vector3 yAxis = (zAxis ^ xAxis).GetNormalized();

    return Matrix4(
        xAxis.x,             yAxis.x,             zAxis.x,             0,
        xAxis.y,             yAxis.y,             zAxis.y,             0,
        xAxis.z,             yAxis.z,             zAxis.z,             0,
        xAxis & -m_position, yAxis & -m_position, zAxis & -m_position, 1
    );
}

