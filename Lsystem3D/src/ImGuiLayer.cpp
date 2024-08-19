#include "ImGuiLayer.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

void InitImGui(GLFWwindow* window) {
    // ��� ImGui �汾������������
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // ���� ImGui ��ʽ
    ImGui::StyleColorsDark(); // ʹ����ɫ����

    // ��ʼ�� ImGui ʵ��
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130"); // OpenGL 3.0 + GLSL 130
}

void BeginImGuiFrame() {
    // �����µ� ImGui ֡
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void RenderImGui() {
    // ��Ⱦ ImGui ����
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void CleanupImGui() {
    // ���� ImGui �����Դ
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
