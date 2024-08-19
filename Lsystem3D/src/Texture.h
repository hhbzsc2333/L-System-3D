#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

enum TextureType
{
    DIFFUSE, SPECULAR, AMBIENT
};

class Texture {
public:
    unsigned int texid;
    TextureType type;

    Texture(const std::string& filepath, TextureType type);
    ~Texture();

    void bind(unsigned int channel) const;
    void unbind() const;

    void deleteTexture();

    Texture& operator=(const Texture& tex);
};