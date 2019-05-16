/*******************************
Name: Bryan Cagle
Class: CSCE 4230.001
Due Date: 03-03-2016
Description: The purpose of this program
is to individually animate five created shape-objects using
translations and rotations in loop.

Created from source code/initial settings of planet.c as base
*******************************/

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>

static double speed=0.5, move=0.0, move2=0.0, spin=0.0;
int dir1=1, dir2=1;
GLUquadric *quad;

void init(void) 
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_FLAT);
	quad = gluNewQuadric ();
}
void Animations(void)
{
	spin=spin+speed;
	if(spin>360.0)
	spin-=360.0;

	//changes direction of movement for the first object once a point is reached
	if(dir1==1)
	move=move+speed/4;
	else
	move=move-speed/4;
	if(move>2&&dir1==1)
	dir1=-1;
	if(move<-2&&dir1==-1)
	dir1=1;

	//changes direction of movement for the second object once a point is reached
	if(dir2==1)
	move2=move2+speed/4;
	else
	move2=move2-speed/4;
	if(move2>4.5&&dir2==1)
	dir2=-1;
	if(move2<.5&&dir2==-1)
	dir2=1;

	glutPostRedisplay();
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

	//First object is rotated on t he Y and Z axis simultaniously,and moved up and down
   	glPushMatrix();
	glColor3f (0, 0, 1);
	glTranslatef(0, -move, 0);
	glTranslatef(2.5, 0, 0);
	glRotatef(spin*4,0,1,1);
	glTranslatef(-2.5, 0, 0);
	//Hexagon created from verticies
	glPointSize(1.0);
	glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * M_PI; i += M_PI / 3)
 		glVertex3f(cos(i) * 0.25+2.5, sin(i) * 0.25, 0.0);
	glEnd();
	glFlush();
   	glPopMatrix();
   
	//second object moves left and right and rotates on the Z axis
   	glPushMatrix();
	glColor3f (0, 1, 0);
	glTranslatef(move2, 2, 0);
	glTranslatef(-2, 0, 0);
	glRotatef(-spin*8,0,0,1);
	glTranslatef(2, 0, 0);
	//Triangle created from verticies
	glPointSize(1.0);
		glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * M_PI; i += M_PI / 1.5)
 		glVertex3f(cos(i) * 0.4-2.5, sin(i) * 0.4, 0.0);
	glEnd();
	glFlush();
   	glPopMatrix();

	//Draws initial disk shape that other shapes revolve around to act as a "sun"
	glPushMatrix();
	glColor3f (1, 0, 0);	
	glTranslatef(-.75,-.75,0);
	glTranslatef(.75,.75,0);
	glRotatef(spin*8,0,1,0);
	glTranslatef(-.75,-.75,0);
	gluDisk(quad,0.25,0.5,18,2);
		
		//Draws another shape within the matrix of the disk function to act as an "earth"
		glPushMatrix();
		glColor3f (0.1, 1, 0.5);
		glRotatef(spin*8, 0, 0, 1);
		glTranslatef(1.2, 0, 0);
		glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * M_PI; i += M_PI / 2)
 		glVertex3f(cos(i) * 0.2, sin(i) * 0.2, 0.0);
		glEnd();
			
			//Draws a final shape relative to the "earth" to as a "moon"
			glPushMatrix();
			glColor3f (.5, .25, .8);
			glRotatef(-spin*16, 1, 0, 1);
			glTranslatef(.4, 0, 0);
			glBegin(GL_POLYGON);
			for(double i = 0; i < 2 * M_PI; i += M_PI / 5)
 			glVertex3f(cos(i) * 0.1, sin(i) * 0.1, 0.0);
			glEnd();

			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glMatrixMode (GL_PROJECTION);
   glViewport(0,0,w,h);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0); //keeps aspect-ratio when window is resized, does not center objects however
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void MenuSelect(int idCommand)
{
	//Each menu selection has a seperate purpose for each action on the animation
        switch(idCommand)
        {
                case 'p':
                        glutIdleFunc(Animations); //sets the idle function to the animations
                        break;
                case 's':
                        speed=0.15; //slow speed
                        break;
                case 'm':
                        speed=0.5; //medium, default speed
                        break;
                case 'f':
                        speed=2.0; //fast
                        break;
                case 32:
                        glutIdleFunc(NULL); //stops all animations
                        break;
                case 27: exit(0); break; //ends program
                default: break;
        }
}
void keyboard (unsigned char key, int x, int y)
{
	//keyboard functions that reroute to menu functions
	switch (key) {
      	case 'p':
         	MenuSelect('p');
         	break;
	case 's':
		MenuSelect('s');
		break;
	case 'm':
		MenuSelect('m');
		break;
	case 'f':
		MenuSelect('f');
		break;
      	case 32:
       	 	MenuSelect(32);
        	break;
      	case 27:
        	MenuSelect(27);
       		break;
		default:
       	 	break;
   }
}

int BuildMenu(void)
{
	int menu;
	menu=glutCreateMenu(MenuSelect);
	glutAddMenuEntry("Play/Continue Animation (p)",'p');
	glutAddMenuEntry("Slow Speed Animation (s)", 's');
	glutAddMenuEntry("Medium Speed Animation (m)", 'm');
	glutAddMenuEntry("Fast Speed Animation (f)", 'f');
	glutAddMenuEntry("Stop Animations (space)", 32);
	glutAddMenuEntry("Exit Program (ESC)", 27);
}
int main(int argc, char** argv)
{
   	glutInit(&argc, argv);
   	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   	glutInitWindowSize (550, 309); //16:9 window dimensions 
   	glutInitWindowPosition (100, 100);
   	glutCreateWindow ("Program 3: Animation");
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	BuildMenu();
	glutAttachMenu(GLUT_RIGHT_BUTTON); 
	glutMainLoop();
	return 0;
}
