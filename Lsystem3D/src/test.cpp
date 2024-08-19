#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mat4.h"
#include "GeometryObjects.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"
#include "ImGuiLayer.h"


#define M_PI 3.14159265358979323846

using namespace std;


// Define the TrunkPosition and LeafPosition structures
struct TrunkPosition {
    Vector3 posstar;
    Vector3 posend;
    float radius;
};

struct LeafPosition {
    Vector3 posstarl;
    Vector3 posendl;
    float radius;
};

vector<TrunkPosition> trunks; 
vector<LeafPosition> leaves; 

unsigned int texTrunk;
unsigned int texLeaf;

class Grammar {
public:
    string start;
    string result;
    unordered_map<char, string> generations;

    void Iteration(const unordered_map<char, string>& rules, int level);
};

class LSystem {
public:
    LSystem(Grammar& g) : grammar(g) {
        lengthFactor = 0.6f;  
        radiusFactor = 0.7f;  
    }
    void generateFractal();

private:
    struct State {
        Vector3 pos;  
        Vector3 dir;  
        float length;
        float radius;
        int level;
    };

    State curState; 
    Grammar& grammar;
    float lengthFactor;
    float radiusFactor; 
};

// Syntax parser
void Grammar::Iteration(const unordered_map<char, string>& rules, int level) {
    generations = rules; 
    result = start;
    for (int i = 0; i < level; i++) {
        string tmpstr = "";
        for (int j = 0; j < result.size(); j++) {
            char current_char = result[j];
            if (generations.find(current_char) != generations.end()) {
                tmpstr += generations[current_char];
            }
            else {
                tmpstr += current_char;
            }
        }
        result = tmpstr; 
    }
}

// Transformation matrix
Vector3 Rotate(Vector3 vec, char axis, float angle) {
    
    float rad = angle * M_PI / 180.0;
    Vector3 result = vec;

    Mat4 r(1);
    if (axis == 'X') {
        r.rotate(Radians(angle), Vector3(1, 0, 0));
    }
    else if (axis == 'Y') {
        r.rotate(Radians(angle), Vector3(0, 1, 0));
    }
    else if (axis == 'Z') {
        r.rotate(Radians(angle), Vector3(0, 0, 1));
    }

    result.x = r.val[0][0] * vec.x + r.val[1][0] * vec.y + r.val[2][0] * vec.z + r.val[3][0] * 1;
    result.y = r.val[0][1] * vec.x + r.val[1][1] * vec.y + r.val[2][1] * vec.z + r.val[3][1] * 1;
    result.z = r.val[0][2] * vec.x + r.val[1][2] * vec.y + r.val[2][2] * vec.z + r.val[3][2] * 1;

    result.normalize();
    return result;
}

Mat4 generateTrunk(Vector3 start, Vector3 end, double r)
{
    Vector3 d = end - start;
    float distance = d.module();
    Vector3 s(0, 1, 0);
    Vector3 f = s.cross(d);
    if (f.module() == 0) f = Vector3(0, 0, 1); // When d coincides with the Y-axis, this causes the cross product f to be 0
    float angle = acos(d.dot(Vector3(0, 1, 0)) / distance);

    Mat4 model;
    model.translate({ start.x, start.y, start.z });
    model.rotate(angle, { f.x, f.y, f.z });
    model.scale({ (float)r, distance, (float)r });
    return model;
}

Mat4 generateLeaf(Vector3 start, Vector3 end, double r)
{
    Vector3 d = end - start;
    float distance = d.module();
    Vector3 b = start - Vector3(0, distance, 0);
    Vector3 s = b - start;
    Vector3 f = s.cross(d);
    if (f.module() == 0) f = Vector3(0, 0, 1); 
    GLfloat length = (end - b).module();

    
    GLfloat angle = acos((distance * distance * 2 - length * length) / (2 * distance * distance)) * 180.0f / M_PI;
    Mat4 model;
    model.translate({ start.x, start.y, start.z });
    model.rotate(angle, { f.x, f.y, f.z });
    model.scale({ (float)r, (float)r, 0 });
    return model;
}


// L-System
void LSystem::generateFractal() {
    trunks.clear();
    leaves.clear();
    curState.pos = { 0, 0, 0 };
    curState.dir = { 0, 1, 0 }; 

    curState.length = 0.2f; 
    curState.level = 1;
    curState.radius = 0.2f; 

    float leafRadius = 0.7f; 
    float dx = 37.0f;
    float dy = 37.0f; 
    float dz = 37.0f; 

    stack<State> stack;

    for (size_t i = 0; i < grammar.result.length(); i++) {
        TrunkPosition tmp_trunk; 
        LeafPosition tmp_leaf;

        switch (grammar.result[i]) {
        case 'F': {
            tmp_trunk.posstar = curState.pos;
            curState.pos = curState.pos + curState.length * curState.dir;
            tmp_trunk.posend = curState.pos;
            tmp_trunk.radius = curState.radius;
            trunks.push_back(tmp_trunk);
            break;
        }
        case 'X': {
            tmp_leaf.posstarl = curState.pos;
            tmp_trunk.posstar = curState.pos;
            curState.pos = curState.pos + curState.length * curState.dir;
            tmp_trunk.posend = curState.pos;
            tmp_leaf.posendl = curState.pos;
            tmp_leaf.radius = leafRadius;
            tmp_trunk.radius = curState.radius;
            trunks.push_back(tmp_trunk);
            leaves.push_back(tmp_leaf);
            break;
        }
        case 'A': {
            curState.length = curState.length * lengthFactor;
            curState.radius = curState.radius * radiusFactor;
            break;
        }
        case 'B': {
            curState.length = curState.length / lengthFactor;
            curState.radius = curState.radius / radiusFactor;
            break;
        }
        case '+': { // Y
            curState.dir = Rotate(curState.dir, 'Y', dy);
            break;
        }
        case '-': { // Y
            curState.dir = Rotate(curState.dir, 'Y', -dy);
            break;
        }
        case '&': { // Z
            curState.dir = Rotate(curState.dir, 'Z', dz);
            break;
        }
        case '^': { // Z
            curState.dir = Rotate(curState.dir, 'Z', -dz);
            break;
        }
        case '/': { // X
            curState.dir = Rotate(curState.dir, 'X', dx);
            break;
        }
        case '@': { // X
            curState.dir = Rotate(curState.dir, 'X', -dx);
            break;
        }
        case '[': { 
            stack.push(curState);
            break;
        }
        case ']': { 
            if (!stack.empty()) {
                curState = stack.top();
                stack.pop();
            }
            break;
        }
        }
    }
}



Camera camera(1600, 1600);

unsigned int currentTrunkTexture = 0;
unsigned int currentLeafTexture = 0;
std::vector<Texture*> trunkTextures;
std::vector<Texture*> leafTextures;

void KeyEventHandle(GLFWwindow* window, int key, int code, int act, int modifier)
{
    if (act == GLFW_PRESS || act == GLFW_REPEAT) {

        // 
        //          E| /W
        //           |/
        //    A------/-------D
        //         /|
        //       S/ |Q
        //
        //      |
        //   <-   ->
        //      |  
        if (key == GLFW_KEY_W) {
            camera.forward();
        }
        else if (key == GLFW_KEY_S) {
            camera.backward();
        }
        else if (key == GLFW_KEY_A) {
            camera.turnleft();
        }
        else if (key == GLFW_KEY_D) {
            camera.turnright();
        }
        else if (key == GLFW_KEY_E) {
            camera.upward();
        }
        else if (key == GLFW_KEY_Q) {
            camera.downward();
        }
        else if (key == GLFW_KEY_UP) {
            camera.direct.y += 0.1f;
        }
        else if (key == GLFW_KEY_DOWN) {
            camera.direct.y -= 0.1f;
        }
        else if (key == GLFW_KEY_LEFT) {
            camera.direct.x -= 0.1f;
        }
        else if (key == GLFW_KEY_RIGHT) {
            camera.direct.x += 0.1f;
        }

        // 
        //  <- 0 P ->
        else if (key == GLFW_KEY_O) {
            currentLeafTexture = (--currentLeafTexture + leafTextures.size()) % leafTextures.size();
        }
        else if (key == GLFW_KEY_P) {
            currentLeafTexture = (++currentLeafTexture + leafTextures.size()) % leafTextures.size();
        }
        //  <- U I ->
        else if (key == GLFW_KEY_U) {
            currentTrunkTexture = (--currentTrunkTexture + trunkTextures.size()) % trunkTextures.size();
        }
        else if (key == GLFW_KEY_I) {
            currentTrunkTexture = (++currentTrunkTexture + trunkTextures.size()) % trunkTextures.size();
        }
    }
}


int main() {
    Grammar grammar;
    grammar.start = "FA[+/X][X][@-&X][+^X]B";

    unordered_map<char, string> rules = {
        {'F', "FF"},  
        {'X', "FA[+&X]F[-^X]FX"}   
    };
    int level = 8; 

    grammar.Iteration(rules, level);
    cout << "Result: " << grammar.result << endl;

    
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(2000, 1600, "L-System Tree", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

 
    glfwSetKeyCallback(window, KeyEventHandle);
    
    glEnable(GL_DEPTH_TEST); 

   
    InitImGui(window);



 

    LSystem lsystem(grammar);
    lsystem.generateFractal();


    
    Shader shader("./src/base.shader");
    Shader instanceShader("./src/instance.shader");

   
    Texture tex1("../picture/trunk2.png", DIFFUSE);
    Texture tex2("../picture/trunk3.png", DIFFUSE);
    trunkTextures.push_back(&tex1);
    trunkTextures.push_back(&tex2);

    Texture tex3("../picture/leaf2.png", DIFFUSE);
    Texture tex4("../picture/leaf3.png", DIFFUSE);
    leafTextures.push_back(&tex3);
    leafTextures.push_back(&tex4);

    
    std::vector<Mat4> trunkModelMatrices;
    std::vector<Mat4> leafModelMatrices;

    for (const auto& trunk : trunks) {
        trunkModelMatrices.push_back(generateTrunk(trunk.posstar, trunk.posend, trunk.radius));
    }
    for (const auto& leaf : leaves) {
        leafModelMatrices.push_back(generateLeaf(leaf.posstarl, leaf.posendl, leaf.radius));
    }

    Cone cone(1, 1);        
    Square square(1);       

    cone.acquireInstanceBuffer((const float*)trunkModelMatrices.data(), trunkModelMatrices.size());
    square.acquireInstanceBuffer((const float*)leafModelMatrices.data(), leafModelMatrices.size());

    
    camera.setBackgroundColor(245, 245, 245, 255);

    
    char startInput[128] = "FA[+/X][X][@-&X][+^X]B";
    char ruleInputF[128] = "FF";
    char ruleInputX[128] = "FA[+&X]F[-^X]FX";


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

       
        BeginImGuiFrame();

        // ImGui 
        ImGui::Begin("L-System Controls");

        
        ImGui::SliderInt("Iteration Level", &level, 1, 10); 
        
       
        ImGui::InputText("Start String", startInput, IM_ARRAYSIZE(startInput));
        ImGui::InputText("Rule F", ruleInputF, IM_ARRAYSIZE(ruleInputF));
        ImGui::InputText("Rule X", ruleInputX, IM_ARRAYSIZE(ruleInputX));
        
        
        if (ImGui::Button("Regenerate")) {
            grammar.start = std::string(startInput);
            rules['F'] = std::string(ruleInputF);
            rules['X'] = std::string(ruleInputX);
            grammar.Iteration(rules, level);
            lsystem.generateFractal();
        }

        ImGui::End();

       
        glClearColor(camera.backgroundColor.x, camera.backgroundColor.y, camera.backgroundColor.z, camera.backgroundColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.updateProjectionMat();
        camera.updateViewMat();

        cone.drawInstanced(instanceShader, *trunkTextures[currentTrunkTexture], trunks.size(), camera);
        square.drawInstanced(instanceShader, *leafTextures[currentLeafTexture], leaves.size(), camera);


        RenderImGui();

        glfwSwapBuffers(window);
    }

    CleanupImGui();

    glfwTerminate();
    return 0;
}
