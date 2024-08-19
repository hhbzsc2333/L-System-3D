#include "GeometryObjects.h"

Cone::Cone(float r, float h)
{
    float vertices[10][5] = { {0} };
    for (int i = 0; i < 5; i++) {
        float temp = i * 72 * M_PI / 180;
        vertices[i][0] = r * cos(temp);
        vertices[i][1] = 0;
        vertices[i][2] = r * sin(temp);
        vertices[i][3] = (float)i / 5;
        vertices[i][4] = 0;

        vertices[i + 5][0] = r * cos(temp);
        vertices[i + 5][1] = h;
        vertices[i + 5][2] = r * sin(temp);
        vertices[i + 5][3] = (float)i / 5;
        vertices[i + 5][4] = 1;
    }
    unsigned int indices[10][3] = {
        {0,1,6},{0,5,6},{1,2,7},{1,6,7},{2,3,8},{2,7,8},{3,4,9},{3,8,9},{4,0,5},{4,9,5}
    };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 50 * sizeof(float), vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 30 * sizeof(float), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
}

Cone::~Cone()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Cone::acquireInstanceBuffer(const float* modelMatrices, const unsigned int amount)
{
    glGenBuffers(1, &ins);
    glBindBuffer(GL_ARRAY_BUFFER, ins);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Mat4), modelMatrices, GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(2 * 4 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(3 * 4 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);
}

void Cone::draw(const Shader& shader, const Texture& tex, const Mat4& model, const Camera& camera) const
{
    shader.useprogram();
    shader.setUniformMat4x4f("_projection", 1, (const float*)camera.getProjection().val);
    shader.setUniformMat4x4f("_view", 1, (const float*)camera.getView().val);
    shader.setUniformMat4x4f("_model", 1, (const float*)model.val);
    tex.bind(0);
    shader.setUniform1i("_tex", 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    tex.unbind();
}

void Cone::drawInstanced(const Shader& shader, const Texture& tex, const unsigned int amount, const Camera& camera) const
{
    shader.useprogram();
    shader.setUniformMat4x4f("_projection", 1, (const float*)camera.getProjection().val);
    shader.setUniformMat4x4f("_view", 1, (const float*)camera.getView().val);
    tex.bind(0);
    shader.setUniform1i("_tex", 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 30, GL_UNSIGNED_INT, NULL, amount);
    glBindVertexArray(0);
    tex.unbind();
}

Square::Square(float r)
{
    float vertices[4][5] = {
        {  0.5 * r, r, 0, 1, 1 },
        { -0.5 * r, r, 0, 0, 1 },
        { -0.5 * r, 0, 0, 0, 0 },
        {  0.5 * r, 0, 0, 1, 0 }
    };
    unsigned int indices[2][3] = {
        { 0, 1, 2 }, { 0, 2, 3 }
    };
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));
}

Square::~Square()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void Square::acquireInstanceBuffer(const float* modelMatrices, const unsigned int amount)
{
    glGenBuffers(1, &ins);
    glBindBuffer(GL_ARRAY_BUFFER, ins);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(Mat4), modelMatrices, GL_STATIC_DRAW);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)0);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(2 * 4 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Mat4), (const void*)(3 * 4 * sizeof(float)));

    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);

    glBindVertexArray(0);
}

void Square::draw(const Shader& shader, const Texture& tex, const Mat4& model, const Camera& camera) const
{
    shader.useprogram();
    shader.setUniformMat4x4f("_projection", 1, (const float*)camera.getProjection().val);
    shader.setUniformMat4x4f("_view", 1, (const float*)camera.getView().val);
    shader.setUniformMat4x4f("_model", 1, (const float*)model.val);
    tex.bind(0);
    shader.setUniform1i("_tex", 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    tex.unbind();
}

void Square::drawInstanced(const Shader& shader, const Texture& tex, const unsigned int amount, const Camera& camera) const
{
    shader.useprogram();
    shader.setUniformMat4x4f("_projection", 1, (const float*)camera.getProjection().val);
    shader.setUniformMat4x4f("_view", 1, (const float*)camera.getView().val);
    tex.bind(0);
    shader.setUniform1i("_tex", 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, amount);
    glBindVertexArray(0);
    tex.unbind();
}
