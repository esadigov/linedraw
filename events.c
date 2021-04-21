
/*===============================================================*\
							LINEDRAW
\*===============================================================*/
//for create mode - adding new vertex and deleting last added vertex i defined color black
//for edit mode - select vertex or edge and delete move or insert i defined color blue
//selected vertex will be displayed by red cross and selected edge will be red colored
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>
#include "LineStrip.h"
static void _drawRedLine(int x, int y, int, int);
int window_width, window_height;
//global variable - list of vectors
veclist *myveclist;
//global variabModele MODE which is used to switch between create and edit modes
int MODE = 1;
//target which is send to static function selectVertexOrEdge()
Vector target;
//array of size 2 which values is set to selected edge or vertex pointer
veclist *editableEdge2[2];
//global variable used to define what is selected vertex or edge
int EdgeorVertex = 0;

//-----------------------------------------------------------------
//function draws red cross
//x and y are positions
//size is e length of lines of this cross
static void _drawRedCross(int x, int y, int size)
{
	glColor3ub(255, 0, 0);

	// Horizontal line
	glBegin(GL_LINE_STRIP);
	glVertex2i(x - size, y);
	glVertex2i(x + size, y);
	glEnd();

	// Vertical line
	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y - size);
	glVertex2i(x, y + size);
	glEnd();
}

//----------------------------------------------------------
//function draws a red line
//x , y , x1 and y1 are corrdinates of vertixes of this line
static void _drawRedLine(int x, int y, int x1, int y1)
{
	glColor3ub(255, 0, 0);

	glBegin(GL_LINE_STRIP);
	glVertex2i(x, y);
	glVertex2i(x1, y1);
	glEnd();
}

//------------------------------------------------------------
//this function displays Strip , going through list of vectors
static void displayStrip()
{
	if (VL_isEmpty(myveclist))
		printf("There is no drawing yet!");
	else
	{
		glBegin(GL_LINE_STRIP);
		veclist *temp = myveclist;
		while (temp != NULL)
		{
			glVertex2i(temp->vec.x, temp->vec.y);
			temp = temp->next;
		}
		glEnd();
	}
}

//---------------------------------------------------------------------------------------
//function which colors slected edge in red color , or draws a cross over selected vertex
static void colorSelectedVertexOrEdge()
{
	glColor3ub(0, 0, 255);
	displayStrip();
	if (editableEdge2[0] != NULL && EdgeorVertex == 1)
		_drawRedCross(editableEdge2[0]->vec.x, editableEdge2[0]->vec.y, 5);
	if (editableEdge2[1] != NULL && editableEdge2[0] != NULL && EdgeorVertex == 2)
	{
		_drawRedLine(editableEdge2[0]->vec.x, editableEdge2[0]->vec.y, editableEdge2[1]->vec.x, editableEdge2[1]->vec.y);
	}
}

//--------------------------------------------------------------------------------------
//function which gets target vector from _mouse_CB function and defines user selection
// is it edge or vertex
static void selectVertexOrEdge()
{
	veclist *temp = myveclist;
	for (temp = myveclist; temp != NULL; temp = temp->next)
	{
		if (V_PtPtDistance(temp->vec, target) < 5)
		{
			EdgeorVertex = 1;
			editableEdge2[0] = temp;
		}
		else if (temp->next != NULL && V_PtSegmentDistance(target, temp->vec, temp->next->vec) < 5)
		{
			EdgeorVertex = 2;
			editableEdge2[1] = temp->next;
			editableEdge2[0] = temp;
		}
	}
}

//-------------------------------------------------------------
// The call back function which is called each time that we need
// to draw everything again. All your drawings should be called
// in this function. Initially, we only draw a cross.

static void _display_CB()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, window_width, window_height, 0, -1, 1);

	glClear(GL_COLOR_BUFFER_BIT);
	// Let the current color be black
	glColor3ub(0, 0, 0);
	//if statements defines which mode is used and calls display() in create mode
	//and colorSelectedVertexOrEdge() in edit mode
	//else or default mode is 1 , it is set in case if there is less than 2 vertexes
	if (myveclist == NULL)
	{
		printf("Start Drawing");
	}
	else if (MODE == 1)
	{
		displayStrip();
		_drawRedCross(myveclist->vec.x, myveclist->vec.y, 5);
	}
	else if (MODE == 2 && VL_size(myveclist) > 2)
	{
		colorSelectedVertexOrEdge();
	}
	else
	{
		editableEdge2[1] = NULL;
		editableEdge2[0] = NULL;
		MODE = 1;
		displayStrip();
		_drawRedCross(myveclist->vec.x, myveclist->vec.y, 5);
	}

	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------------
// The call back function which is called each time that the
// graphical window is resized.

static void _reshape_CB(int largeur, int hauteur)
{
	printf("Window resized.\n"); // You can comment this line
	window_width = largeur;
	window_height = hauteur;
	glViewport(0, 0, window_width, window_height);
}

//-------------------------------------------------------------
// The call back function which is called each time at mouse click
//it is used to add new vertex and send target vector to function which defines
//is it selected vertex , edge or non of them
static void _mouse_CB(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (MODE == 1)
		{
			myveclist = VL_push(myveclist, V_new(x, y));
		}
		else if (MODE == 2)
		{
			target = V_new(x, y);
			selectVertexOrEdge();
		}

		glutPostRedisplay();
	}
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a key (corresponding to an ascii code) on the keyboard is pressed.
static void _keyboard_CB(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // escape key
		exit(0);
		break;
	case 8:			   // backspace
		if (MODE == 1) //in create mode it simply pops (delete last created vertex)
		{
			myveclist = VL_pop(myveclist);
			glutPostRedisplay();
		}
		//in create mode it is a little bit different if it is last element
		//then it will set selected vertex to new last vertex in other cases selected vertex is previos one
		//selected vertex will be displayed by red cross
		else if (MODE == 2)
		{
			if (myveclist == editableEdge2[0])
			{
				myveclist = VL_pop(myveclist);
				editableEdge2[0] = myveclist;
			}
			else if (EdgeorVertex == 1)
			{
				veclist *temp = VL_previous(myveclist, editableEdge2[0]);
				VL_removeByAddress(&myveclist, editableEdge2[0]);
				editableEdge2[0] = temp;
			}
			glutPostRedisplay();
		}
		break;
	case 's':
		VL_show(myveclist, "Our Strip");
		break;
	// i key is pressed in order to insert vertex in middle of edge - adding new element after first vertex of selected edge
	case 'i':
		if (MODE == 2 && editableEdge2[1] != NULL && editableEdge2[0] != NULL)
		{
			Vector vec = V_new((editableEdge2[1]->vec.x + editableEdge2[0]->vec.x) / 2, (editableEdge2[1]->vec.y + editableEdge2[0]->vec.y) / 2);
			VL_insertAfter(myveclist, editableEdge2[0], vec);
			EdgeorVertex = 1;
			target = vec;
			selectVertexOrEdge(); //to display red cross at this point , starting function with this target
		}
		glutPostRedisplay();
		break;
	case 13:
		MODE = 2;
		glutPostRedisplay();
		break;
	case 'n':
		MODE = 1;
		editableEdge2[0] = NULL;
		editableEdge2[0] = NULL;
		glutPostRedisplay();
		break;
	default:
		printf("Button with no action----Unknown key : %d %c\n", key, key);
	}
}

//-------------------------------------------------------------
// The call back function which is called each time that
// a special key (arrows, function keys) is pressed.
//-------------------------------------------------------------
//this function is used to move sleceted vertex by increasing or decreasing values of x and y
//of vector which is sent as pointer of strip
static void _special_CB(int key, int x, int y)
{
	EdgeorVertex = 1;
	switch (key)
	{
	case GLUT_KEY_LEFT:
		editableEdge2[0]->vec.x--;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		editableEdge2[0]->vec.x++;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		editableEdge2[0]->vec.y--;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		editableEdge2[0]->vec.y++;
		glutPostRedisplay();
		break;
	default:
		fprintf(stderr, "Button with no action----Unknown special key.\n");
	}
	glutPostRedisplay();
}

//-------------------------------------------------------------
//main function calls functions and defines size of drawing window
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("\nUsage : %s <width> <height>\n\n", argv[0]);
		return 1;
	}
	else
	{
		// Reading the command line arguments
		window_width = atoi(argv[1]);
		window_height = atoi(argv[2]);

		int windowPosX = 100, windowPosY = 100;
		// Initializing GLUT (graphic window and events manager)
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(window_width, window_height);
		glutInitWindowPosition(windowPosX, windowPosY);
		glutCreateWindow(argv[0]);

		// Initializing OpenGL (drawing tool)
		glViewport(0, 0, window_width, window_height);
		glClearColor(255, 255, 255, 0);

		// Associating callback functions to each type of event
		glutDisplayFunc(_display_CB);
		glutReshapeFunc(_reshape_CB);
		glutKeyboardFunc(_keyboard_CB);
		glutSpecialFunc(_special_CB);
		glutMouseFunc(_mouse_CB);

		// Starting the loop which waits for events.
		glutMainLoop();
	}
}