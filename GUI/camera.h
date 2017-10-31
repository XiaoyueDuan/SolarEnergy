#pragma once

#include <QVector3D>
#include <QMatrix4x4>
#include <QtMath>
#include <vector>

// Defines several possible options for camera movement.
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

//default camera value
const float YAW   = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 25.0f;
const float SENSITIVTY = 0.001f;
const float ZOOM = 45.0f;

// An abstract camera class that processes input 
class Camera
{
public:
	// Camera Attributes
	QVector3D position_;
	QVector3D front_;
	QVector3D up_;
	QVector3D right_;
	QVector3D worldUp_;
	// Eular Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	// Constructor with vectors
	Camera(QVector3D position = QVector3D(0.0f, 3.0f, 30.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : front_(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		position_ = position;
		worldUp_ = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front_(QVector3D(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		position_ = QVector3D(posX, posY, posZ);
		worldUp_ = QVector3D(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	QMatrix4x4 GetViewMatrix()
	{
		QMatrix4x4 view;
		view.lookAt(position_, position_ + front_, up_);
		return view;
	}

	QMatrix4x4 GetRotated()
	{
		QMatrix4x4 view;
		view.lookAt( QVector3D(0.0f,0.0f,0.0f),  front_, up_);
		QMatrix3x3 view2 = view.normalMatrix();
		QMatrix4x4 newView(view2);
		return newView;
	}
	
	void setPosition(QVector3D position) {
		position_ = position;
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			position_ += front_ * velocity;
		else if (direction == BACKWARD)
			position_ -= front_ * velocity;
		else if (direction == LEFT)
			position_ -= right_ * velocity;
		else if (direction == RIGHT)
			position_ += right_ * velocity;
		else if (direction == UP)
			position_ += up_ * velocity;
		else if (direction == DOWN)
			position_ -= up_ * velocity;

		//y must over the land
		if (position_.y() <= 3) {
			position_.setY(3.0f);
		}
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		// negetive
		Yaw += yoffset;
		Pitch -= xoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		QVector3D front;
		front.setX(cos(qRadiansToDegrees(Yaw))*cos(qRadiansToDegrees(Pitch)));
		front.setY(sin(qRadiansToDegrees(Yaw)));
		front.setZ(cos(qRadiansToDegrees(Yaw))*sin(qRadiansToDegrees(Pitch)));
		front_ = front.normalized();
		// Also re-calculate the Right and Up vector
		// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		right_ = QVector3D::crossProduct(front_, worldUp_).normalized();
		up_ = QVector3D::crossProduct(right_, front_).normalized(); 
	}
};