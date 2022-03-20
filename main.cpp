#include <windows.h>
#include<string.h>
#include<stdarg.h>
#include<stdio.h>
#include <gl/glut.h>
static double carx=-1.2,cary=-4 ;
static double cx[5]={6,15,22,30,40},cy[5]={-1,-10,-24,-30,-40},x[10]={0};
static double s1=0;
static bool stop=false, red=true,green=false,crash=false;

void *font;
void *currentfont;

void setFont(void *font)
{
	currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);

	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,1.0,1.0);
		glutBitmapCharacter(currentfont,*c);
	}
}






void road(){
	//Background
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	glVertex2f(-6,6);
	glVertex2f(6,6);
	glVertex2f(6,-6);
	glVertex2f(-6,-6);
	glEnd();

	// Horizontal Road
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_POLYGON);
	glVertex2f(-500,2.5);
	glVertex2f(6,2.5);
	glVertex2f(6,1.5);
	glVertex2f(-6,1.5);
	glEnd();

	// Vertical road
	glColor3f(0.4,0.4,0.4);
	glBegin(GL_POLYGON);
	glVertex2f(0.4,6);
	glVertex2f(-0.4,6);
	glVertex2f(-0.4,-6);
	glVertex2f(0.4,-6);
	glEnd();




}

void bdg(float x1, float y1)
{
	glPushMatrix();
	glTranslatef(x1,y1,0);
	glScaled(0.5,0.4,2.2);
	glutSolidCube(1);
	glPopMatrix();
}

void cars(float x1,float y1)
{
	glPushMatrix();
	glScaled(0.3,0.5,0.5);
	glTranslatef(x1,y1,0);
	glPushMatrix();
	glColor3f(1,0,1);
	glutSolidCube(1);
	glPopMatrix();

	//wheel 1
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(-0.45,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
	glColor3f(.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//wheel 2
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(0.35,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
    glColor3f(.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//footer cube
	glPushMatrix();
	glTranslatef(-0.2,0,0);
	glScaled(1.5,1,.7);
	glColor3f(0,0,1);
    glutSolidCube(1);
	glPopMatrix();
glPopMatrix();
}

void carsv(float x1,float y1)
{
	glPushMatrix();
	glScaled(0.3,0.5,0.5);
	glTranslatef(x1,y1,0);
	glRotatef(-90,0,0,1);
	glPushMatrix();
	glColor3f(1,0,1);
	glutSolidCube(1);
	glPopMatrix();

	//wheel 1
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(-0.45,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
	glColor3f(.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//wheel 2
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(0.35,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
    glColor3f(.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//footer cube
	glPushMatrix();
	glTranslatef(-0.2,0,0);
	glScaled(1.5,1,.7);
	glColor3f(0,0,1);
    glutSolidCube(1);
	glPopMatrix();
glPopMatrix();
}

void myCar(float x1,float y1)
{
	glPushMatrix();
	glScaled(0.2,0.6,0.1);
	glTranslatef(x1,y1,0);
	glPushMatrix();
	glColor3f(0,0,1);
	glutSolidCube(1);
	glPopMatrix();

	//wheel 1
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(-0.4,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
	glColor3f(1.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//wheel 2
	glPushMatrix();
	glRotatef(90,1.0f,0.0f,0.0f);
	glTranslatef(0.4,0.15,-0.02);
	glScaled(0.15,0.15,0.6);
    glColor3f(1.5,.5,.5);
	glutSolidTorus(1,0.8,20,20);
	glPopMatrix();

	//footer cube
	glPushMatrix();
	glTranslatef(0,-.25,0);
	glScaled(1,0.6,2.7);
	glColor3f(1,1,0);
    glutSolidCube(1);
	glPopMatrix();
glPopMatrix();
}

// Draw Traffic Control
void trafic(double ang)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-13.0f);
    //glRotatef(ang,0.0f,1.0f,0.0f);

	// To change the view
	glRotatef(-70,1,0,0);

	//Draw road
	glPushMatrix();
	road();
	glPopMatrix();

	// Vertical Driving cars
	float tempy[5]={cy[0]+x[5]/15,cy[1]+x[6]/15,cy[2]+x[7]/15,cy[3]+x[8]/15,cy[4]+x[9]/15};

	for(int ty=0;ty<=4;ty++){
		//Reset the cars to their original positions if last car exceeds y-axis by +12.
		if(tempy[4]>=8){
		for(int i=0;i<=9;i++)
			x[i]=0;
		}

		if(tempy[ty]>=1.5 && tempy[ty]<=2 && red ){

		}else if(ty==0)
		{
		x[ty+5]+=0.07;
		}
		else if(tempy[ty]>=tempy[ty-1]-2)
		{
		}
		else
		x[ty+5]+=0.07;

		carsv(0.7,tempy[ty]);
	}

	// Horizontally Driving cars

	float tempx[5]={cx[0]-x[0]/15,cx[1]-x[1]/15,cx[2]-x[2]/15,cx[3]-x[3]/15,cx[4]-x[4]/15};

	for(int tx=0;tx<=4;tx++)
	{
		if(tempx[tx]>=1.8 && tempx[tx]<=3 && green){

		}else if(tx==0)
		{
		x[tx]+=0.07;
		}
		else if(tempx[tx]<=tempx[tx-1]+2)
		{
		}
		else
		x[tx]+=0.07;

		cars(tempx[tx],3.5);
	}
	// Condition for vertical car crash
	for(int ty1=0;ty1<=4;ty1++)
	{
	if(carx>=0 && carx<=1 && cary>=tempy[ty1]-0.4 && cary<=tempy[ty1]+0.4 )
	{
	crash=true;
	}
	}

	// Condition for Horizontal car crash
	for(int ty2=0;ty2<=4;ty2++)
	{
	if(cary>=3.0 && cary<=3.8 && carx>=tempx[ty2]-0.4 && carx<=tempx[ty2]+0.4 )
	{
	crash=true;
	}
	}

	// Draw our car
	myCar(carx,cary);



	//End Wall
	glPushMatrix();
	glTranslatef(0,8,0);
	glColor3f(0.1,0.1,0.1);
	glScaled(30,0.5,13);
	glutSolidCube(1);
	glPopMatrix();


	//Welcome arc
	glPushMatrix();
	glTranslatef(0,6,0);
	glRotatef(90,1,0,0);
	glScaled(0.5,1.5,13);
	glColor3f(0,0,0.1);
	glutSolidTorus(0.1,1,30,30);
	glPopMatrix();

	//Signal for vertical cars
	//Pole
	glPushMatrix();
	glTranslatef(0.65,2.8,0);
	glScaled(0.3,0.2,4.5);
	glColor3f(0,0,0);
	glutSolidCube(0.5);
	glPopMatrix();

	//red signal
	glPushMatrix();
	if(red)
	glColor3f(1,0,0);
	else
	glColor3f(0,0,0);
	glTranslatef(0.65,2.6,1.05);
	glScaled(0.2,0.2,0.2);
	glutSolidSphere(0.35,30,30);
	glPopMatrix();

	//green signal
	glPushMatrix();
	if(green)
	glColor3f(0,1,0);
	else
	glColor3f(0,0,0);
	glTranslatef(0.65,2.5,0.9);
	glScaled(0.2,0.2,0.2);
	glutSolidSphere(0.35,30,30);
	glPopMatrix();

	//Signal for horizontal cars
	//Pole
	glPushMatrix();
	glTranslatef(-0.65,0.8,0);
	glScaled(0.2,0.4,4.5);
	glutSolidCube(0.5);
	glPopMatrix();

	//red signal
	glPushMatrix();
	if(red)
	glColor3f(0,1,0);
	else
	glColor3f(0,0,0);
	glTranslatef(-0.6,0.8,0.7);
	glScaled(0.2,0.5,0.5);
	glutSolidSphere(0.25,30,30);
	glPopMatrix();

	//green signal
	glPushMatrix();
	if(green)
	glColor3f(1,0,0);
	else
	glColor3f(0,0,0);
	glTranslatef(-0.6,0.8,1);
	glScaled(0.2,0.5,0.5);
	glutSolidSphere(0.25,30,30);
	glPopMatrix();

	//Garden trees
	glPushMatrix();
	glTranslatef(2.5,-2.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5,-2.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5,-2.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5,-4.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5,-4.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.5,-4.8,1);
	glRotatef(70,1,0,0);
	glScaled(0.4,0.4,0.4);

	glPopMatrix();

	glFlush();
    glutSwapBuffers();
}

void i()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.5,0.5,0);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-13.0f);

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,1,-1.0,"Submitted By");
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-2,0,-1.0,"Kieran Champion");
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-2,-1,-1.0,"Tinashe Mugwanda");



	glEnable(GL_COLOR_MATERIAL);
	glFlush();
	glutSwapBuffers();
 }

void c()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5,0.0,0.5,0);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-13.0f);

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,2,-1.0,"Press p/P -> Start");
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,1,-1.0,"USER Car Control keys");
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,0,-1.0,"Press w/W -> UP");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,-1,-1.0,"Press a/A -> LEFT");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,-2,-1.0,"Press d/D -> RIGHT");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1,1,1);
	drawstring(-1,-3,-1.0,"Press s/S -> DOWN");

	glEnable(GL_COLOR_MATERIAL);
	glFlush();
	glutSwapBuffers();
 }

void gameOver(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-13.0f);

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0,0,0);
	drawstring(-1,0,-1.0,"Accident");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0,0,0);
	drawstring(-1,-1,-1.0,"Press r -> Reset");

	glFlush();
    glutSwapBuffers();
}


void p()
{
	//automate signals
	if(s1<=10){
		if(s1<5){
red=true;
green=false;
s1+=0.006;
		}
		if(s1>5){
red=false;
green=true;
s1+=0.006;
		}
		if(s1>=9.5){
			s1=0;
	}
	}

	if(crash)
	{
	gameOver();
	}
	else{

	//if(!stop)
	//x+=0.07;
	trafic(x[0]);

	}

  }


void P()
{
	//x += .07;
	trafic(x[0]);
}


void doInit()
{

	/* Background and foreground color */
    glClearColor(1.0,1.0,1.0,0);
       glViewport(0,0,640,480);

	/* Select the projection matrix and reset it then
     setup our view perspective */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f,(GLfloat)640/(GLfloat)480,0.1f,200.0f);

    /* Select the modelview matrix, which we alter with rotatef() */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
		glEnable( GL_COLOR_MATERIAL );
    glDepthFunc(GL_LEQUAL);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,0);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-13.0f);

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0,0,0);
	drawstring(-2,0,-1.0,"A Mini Project on 'TRAFFIC SIGNALS'");


	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(0,0,0);
	drawstring(-2,-1,-1.0," Press 'I/i' For Students Information");

	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
		glColor3f(0,0,0);

	drawstring(-2,-2,-1.0,"Press 'C/c' For KeyBoard Interaction");

	GLfloat mat_ambient[]={0.0f,1.0f,2.0f,1.0f};
	GLfloat mat_diffuse[]={0.0f,1.5f,.5f,1.0f};
	GLfloat mat_specular[]={5.0f,1.0f,1.0f,1.0f};
	GLfloat mat_shininess[]={50.0f};
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	GLfloat lightIntensity[]={1.7f,1.7f,1.7f,1.0f};
	GLfloat light_position3[]={2.0f,10.0f,3.0f,1.0f};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position3);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	GLfloat lightIntensity1[]={1.7f,1.7f,1.7f,1.0f};
	GLfloat light_position1[]={-2.0f,1.0f,-5.0f,1.0f};
	glLightfv(GL_LIGHT1,GL_POSITION,light_position1);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,lightIntensity1);
	glEnable(GL_COLOR_MATERIAL);
	glFlush();
	glutSwapBuffers();
}

void menu(int id)
{
	switch(id)
	{
	case 1:glutIdleFunc(P);
		break;
	case 2:glutIdleFunc(p);
		break;

	case 5:exit(0);
		break;

	}
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mykey(unsigned char key,int x,int y)
{
	if(key=='p')
	{
		glutIdleFunc(p);
	}



	if(key=='P')
	{
		glutIdleFunc(P);
	}


	if(key=='w' || key=='W')
	{
		cary+=0.08;
		glutIdleFunc(p);
	}

	if(key=='a' || key=='A')
	{
		if(carx>=-1.5)
		carx-=0.1;

		glutIdleFunc(p);
	}


	if(key=='d' || key=='D')
	{	if(carx<=1.5)
		carx+=0.1;
		glutIdleFunc(p);
	}


	if(key=='s' || key=='S')
	{	cary-=0.08;
		glutIdleFunc(P);
	}


	if(key=='1')
	{	red=true;
		green=false;
		glutIdleFunc(p);
	}


	if(key=='2')
	{	red=false;
		green=true;

		glutIdleFunc(p);
	}

		if(key=='r')
	{	red=false;
		green=true;
		crash=false;
		glClearColor(1,1,1,1);
		glutIdleFunc(p);
	}

	if(key=='i')
	{
		glutIdleFunc(i);
	}
if(key=='c')
	{
		glutIdleFunc(c);
	}

	if(key=='q'||key=='Q')
	{
		exit(0);
	}


}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(1000,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Traffic Control");
    glutDisplayFunc(display);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glutKeyboardFunc(mykey);
	glutCreateMenu(menu);
    glutAddMenuEntry("Start       'p'",1);
	glutAddMenuEntry("Quit            'q'",5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	doInit();
    glutMainLoop();
	return 0;
}
