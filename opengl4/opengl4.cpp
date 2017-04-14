#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <iostream>

using namespace std;

int speed = 1;

GLfloat angle = 0;
GLfloat length = 0.1f;
bool trans = 1;
GLfloat movelen = 0;
GLfloat scale_size = 0;
bool endis = 1;

int task = 5;

void cube()
{
	if(endis)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0, 0);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(length, length, length);
	glVertex3f(-length, length, length);
	glVertex3f(-length, -length, length);
	glVertex3f(length, -length, length);

	glColor3f(1.0f, 1.0f, 0);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(-length, length, -length);
	glVertex3f(length, length, -length);
	glVertex3f(length, -length, -length);

	glColor3f(0, 1.0f, 0);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(length, length, length);
	glVertex3f(length, length, -length);
	glVertex3f(-length, length, -length);
	glVertex3f(-length, length, length);

	glColor3f(0, 1.0f, 1.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(length, -length, -length);
	glVertex3f(length, -length, length);
	glVertex3f(-length, -length, length);

	glColor3f(0, 0, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(length, length, length);
	glVertex3f(length, -length, length);
	glVertex3f(length, -length, -length);
	glVertex3f(length, length, -length);

	glColor3f(1.0f, 0, 1.0f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-length, -length, -length);
	glVertex3f(-length, -length, length);
	glVertex3f(-length, length, length);
	glVertex3f(-length, length, -length);

	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	if (task == 1)
	{
		glRotatef(angle, 1.0f, 0, 0);
		glRotatef(angle, 0, 1.0f, 0);
		glRotatef(angle, 0, 0, 1.0f);
	}
	if (task == 4 || task == 5)
	{
		//scale
		double t = clock();
		glScalef(GLfloat(sin(t / 1000.0)), GLfloat(sin(t / 1000.0)), GLfloat(sin(t / 1000.0)));
	}
	if (task == 3 || task == 5)
	{
		//rotate
		glRotatef(angle, 1.0f, 1.0f, 0);
	}
	angle += speed*0.01f;
	if (task == 2 || task == 5)
	{
		//translate
		if (trans)
		{
			glTranslatef(movelen, 0, 0);
			movelen += speed*0.0003f;
			if (movelen > 1.0f)
				trans = 0;
		}
		else
		{
			glTranslatef(movelen, 0, 0);
			movelen -= speed*0.0003f;
			if (movelen < -1.0f)
				trans = 1;
		}
	}

	cube();
	glutSwapBuffers();
}

void bonus() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 1.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(angle, 0, 1.0f, 0);
	glScalef(scale_size, scale_size, scale_size);
	scale_size += speed*0.00005f;
	cube();
	glPopMatrix();

	glRotatef(angle, 0, 0, -1.0f);	
	glTranslatef(0.8f, 0, 0);
	glRotatef(angle, 1.0f, 1.0f, 0);
	cube();
	angle += speed*0.01f;
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	cout << "Disable(GL_DEPTH_TEST)?(int)(y0/n1)" << endl;
	cin >> endis;
	cout << "speed(int)" << endl;
	cin >> speed;
	cout << "1.Draw a cube" << endl << "2.Translations" << endl << "3.Rotations" << endl << "4.Scaling" << endl << "5.all" << endl << "6.bonus" << endl;
	int c;
	cin >> c;
	switch (c)
	{
	case 1:
	{
		task = 1;
		break;
	}
	case 2:
	{
		task = 2;
		break;
	}
	case 3:
	{
		task = 3;
		break;
	}
	case 4:
	{
		task = 4;
		break;
	}
	case 5:
	{
		task = 5;
		break;
	}
	default:
		break;
	}

	glutCreateWindow("cube");
	glutPostRedisplay();
	if (c == 6)
	{
		glutDisplayFunc(bonus);
		glutIdleFunc(bonus);
	}
	else
	{
		glutDisplayFunc(display);
		glutIdleFunc(display);
	}
	glutMainLoop();
	return 0;
}