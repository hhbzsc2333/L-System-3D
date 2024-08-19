#include "Camera.h"


void Camera::updateProjectionMat()
{
	projection = perspective(Radians(fieldView), WHRatio, near, far);
}

void Camera::updateViewMat()
{
	view = lookAtRH(position, Vector3(position + direct), Vector3(0, 1, 0));
}


Camera::Camera(int width, int height) : WHRatio((float)width / (float)height), size(5), position(-5, 15, 15), direct(0.6, -0.5, -1), fieldView(45), speed(0.2f), backgroundColor(0)
{
	near = 0.1f;
	far = 100.0f;
	pixelPerUnit = size / (height >> 1);
	updateProjectionMat();
	updateViewMat();
}

Mat4 Camera::getProjection() const
{
	return projection;
}

Mat4 Camera::getView() const
{
	return view;
}

void Camera::setSize(float size)
{
	this->size = size;
	updateProjectionMat();
}

void Camera::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	backgroundColor = Vector4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f);
}

void Camera::forward()
{
	Vector3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast.normalize();
	position = position + dir_cast * speed;
}

void Camera::backward()
{
	Vector3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast.normalize();
	position = position - dir_cast * speed;
}

void Camera::turnleft()
{
	Vector3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast.normalize();
	dir_cast = Vector3(dir_cast.z, 0.0f, -dir_cast.x);
	position = position + dir_cast * speed;
}

void Camera::turnright()
{
	Vector3 dir_cast(direct.x, 0.0f, direct.z);
	dir_cast.normalize();
	dir_cast = Vector3(-dir_cast.z, 0.0f, dir_cast.x);
	position = position + dir_cast * speed;
}

void Camera::upward()
{
	position.y += speed;
}

void Camera::downward()
{
	position.y -= speed;
}
