#pragma once

#include "Mat4.h"


class Camera
{
private:
	Mat4 projection;
	Mat4 view;

	
public:
	Vector3 position;
	Vector3 direct;

	// Width / Height
	float WHRatio;

	// units vertical
	float size;

	// size / height / 2
	float pixelPerUnit;

	float near;
	float far;

	float fieldView; // degree
	float speed;
	
	Vector4 backgroundColor;


	Camera(int width, int height);

	void updateProjectionMat();
	void updateViewMat();
	Mat4 getProjection() const;
	Mat4 getView() const;

	void setSize(float size);
	void setBackgroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	void forward();
	void backward();
	void turnleft();
	void turnright();
	void upward();
	void downward();
};

