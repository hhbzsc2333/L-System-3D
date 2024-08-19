#version 330 core

in vec2 TexCoord; // 从顶点着色器传递过来的纹理坐标

out vec4 FragColor; // 输出的颜色

uniform sampler2D texture1; // 纹理采样器

void main()
{
    FragColor = texture(texture1, TexCoord); // 从纹理中获取颜色并输出
}
