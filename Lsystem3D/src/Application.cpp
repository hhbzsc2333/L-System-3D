//#include <GL/glut.h>

/*void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);//清空色彩缓存区
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//绘制
	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//初始化glut  （可不写默认）
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//显示模式初始化 RGB显示模式，单缓冲模式
	glutInitWindowPosition(100, 100);//窗口窗口位置  （可不写默认）
	glutInitWindowSize(400, 400);//窗口大小  （可不写默认）
	glutCreateWindow("第一个OpenGl程序");//窗口名称
	glutDisplayFunc(&myDisplay);//自定义函数绘图
	glutMainLoop();//消息循环相应
	return 0;
}*/

//#include <GL/glut.h>

/*void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置清空屏幕时使用的颜色
    glMatrixMode(GL_PROJECTION); // 设置投影模式
    glLoadIdentity(); // 重置投影矩阵
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); // 设置透视投影
    glMatrixMode(GL_MODELVIEW); // 设置模型视图矩阵
    glLoadIdentity(); // 重置模型视图矩阵
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0); // 设置观察视角
}

void drawPlane() {
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();
}*/

/*void drawCube() {
    glutSolidCube(1.0f);
}

void drawCylinder() {
    GLUquadricObj* cylinder = gluNewQuadric();
    gluCylinder(cylinder, 0.5f, 0.5f, 1.0f, 20, 20);
    gluDeleteQuadric(cylinder);
}

void drawSlope() {
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glEnd();
}

void drawPrism() {
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);

    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);

    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, -1.0f);

    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glEnd();
}*/

/*void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 清空颜色缓冲和深度缓冲
    glColor3f(1.0f, 1.0f, 1.0f); // 设置绘制颜色为白色

    glPushMatrix();
    drawPlane();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawCylinder();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2.0f);
    drawSlope();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2.0f);
    drawPrism();
    glPopMatrix();

    glutSwapBuffers(); // 切换缓冲区显示
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // 初始化 GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 设置显示模式
    glutInitWindowSize(800, 600); // 设置窗口大小
    glutCreateWindow("OpenGL Shapes"); // 创建窗口，并指定标题

    init(); // 初始化 OpenGL

    glutDisplayFunc(display); // 设置绘图函数

    glEnable(GL_DEPTH_TEST); // 启用深度测试

    glutMainLoop(); // 进入 GLUT 主循环

    return 0;
}*/



