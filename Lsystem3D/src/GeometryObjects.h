#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mat4.h"


class Cone
{
public:
    Cone(float r, float h);
    ~Cone();
    
    void acquireInstanceBuffer(const float* modelMatrices, const unsigned int amount);
    void draw(const Shader& shader, const Texture& tex, const Mat4& model, const Camera& camera) const;
    void drawInstanced(const Shader& shader, const Texture& tex, const unsigned int amount, const Camera& camera) const;

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
    unsigned int ins;
};


class Square
{
public:
    Square(float r = 0);
    ~Square();

    void acquireInstanceBuffer(const float* modelMatrices, const unsigned int amount);
    void draw(const Shader& shader, const Texture& tex, const Mat4& model, const Camera& camera) const;
    void drawInstanced(const Shader& shader, const Texture& tex, const unsigned int amount, const Camera& camera) const;

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;
    unsigned int ins;
};
