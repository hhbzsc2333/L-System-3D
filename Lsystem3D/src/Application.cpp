//#include <GL/glut.h>

/*void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);//���ɫ�ʻ�����
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//����
	glFlush();

}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//��ʼ��glut  ���ɲ�дĬ�ϣ�
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);//��ʾģʽ��ʼ�� RGB��ʾģʽ��������ģʽ
	glutInitWindowPosition(100, 100);//���ڴ���λ��  ���ɲ�дĬ�ϣ�
	glutInitWindowSize(400, 400);//���ڴ�С  ���ɲ�дĬ�ϣ�
	glutCreateWindow("��һ��OpenGl����");//��������
	glutDisplayFunc(&myDisplay);//�Զ��庯����ͼ
	glutMainLoop();//��Ϣѭ����Ӧ
	return 0;
}*/

//#include <GL/glut.h>

/*void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ���������Ļʱʹ�õ���ɫ
    glMatrixMode(GL_PROJECTION); // ����ͶӰģʽ
    glLoadIdentity(); // ����ͶӰ����
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); // ����͸��ͶӰ
    glMatrixMode(GL_MODELVIEW); // ����ģ����ͼ����
    glLoadIdentity(); // ����ģ����ͼ����
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0); // ���ù۲��ӽ�
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �����ɫ�������Ȼ���
    glColor3f(1.0f, 1.0f, 1.0f); // ���û�����ɫΪ��ɫ

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

    glutSwapBuffers(); // �л���������ʾ
}

int main(int argc, char** argv) {
    glutInit(&argc, argv); // ��ʼ�� GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ������ʾģʽ
    glutInitWindowSize(800, 600); // ���ô��ڴ�С
    glutCreateWindow("OpenGL Shapes"); // �������ڣ���ָ������

    init(); // ��ʼ�� OpenGL

    glutDisplayFunc(display); // ���û�ͼ����

    glEnable(GL_DEPTH_TEST); // ������Ȳ���

    glutMainLoop(); // ���� GLUT ��ѭ��

    return 0;
}*/



