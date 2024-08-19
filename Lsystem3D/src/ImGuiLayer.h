#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <GLFW/glfw3.h>

void InitImGui(GLFWwindow* window);  // 初始化 ImGui
void BeginImGuiFrame();              // 开始新的 ImGui 帧
void RenderImGui();                  // 渲染 ImGui 内容
void CleanupImGui();                 // 清理 ImGui 相关资源

#endif
