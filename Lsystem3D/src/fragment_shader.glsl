#version 330 core

in vec2 TexCoord; // �Ӷ�����ɫ�����ݹ�������������

out vec4 FragColor; // �������ɫ

uniform sampler2D texture1; // ���������

void main()
{
    FragColor = texture(texture1, TexCoord); // �������л�ȡ��ɫ�����
}
