#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <GLFW/glfw3.h>

void InitImGui(GLFWwindow* window);  // ��ʼ�� ImGui
void BeginImGuiFrame();              // ��ʼ�µ� ImGui ֡
void RenderImGui();                  // ��Ⱦ ImGui ����
void CleanupImGui();                 // ���� ImGui �����Դ

#endif
