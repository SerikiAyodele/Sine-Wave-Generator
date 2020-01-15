/*	Seriki, Ayodele H.
	170408501
	B.Sc. (Hons.) Computer Engineering
	Department of Electrical and Electronics Engineering, University of Lagos


	EEG324: Transmission lines and Filters
	Sine wave generator program written in C++
	API: Open Graphics Library (openGL)
*/

#include <Windows.h>
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <gl/GL.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

const double xScale = 20;// Meaning 20 pixel points rep 1 unit on the x-axis
const double yScale = 20; // Meaning 20 pixel points rep 1 unit on the y-axis

double A; //Amplitude
double w; //Angular frequency
double p; //Phase difference

//Rounding function (This function converts a decimal number to its nearest whole number)
int toWholeNumber(double decimalNumber)
{
	int wholeNumber;

	if(decimalNumber >= 0)
	{
		wholeNumber = (int)(decimalNumber + 0.5);
	}
	else
	{
		decimalNumber *= -1;
		wholeNumber = (int)(decimalNumber + 0.5);
		wholeNumber *= -1;
	}

	return wholeNumber;
}

void display(void)
{

	glBegin(GL_LINES);
	{
		//Grey (Darker)
		glColor3f(0.07, 0.07, 0.07);

		//0.5 unit lines (vertical)
		for (int k = 0; k < 20; k++)
		{
			glVertex2s(100, (-100 + k*10));
			glVertex2s(-100, (-100 + k*10));
		}

		//0.5 unit lines (horizontal)
		for (int k = 0; k < 20; k++)
		{
			glVertex2s((-100 + k*10), 100);
			glVertex2s((-100 + k*10), -100);
		}

		//Grey (Lighter)
		glColor3f(0.3, 0.3, 0.3);

		//1 unit lines (vertical)
		for (int k = 0; k < 10; k++)
		{
			glVertex2s(100, (-100 + k*20));
			glVertex2s(-100, (-100 + k*20));
		}

		//1 unit lines (horizontal)
		for (int k = 0; k < 10; k++)
		{
			glVertex2s((-100 + k*20), 100);
			glVertex2s((-100 + k*20), -100);
		}

		//White
		glColor3f(1.0, 1.0, 1.0);

		//X-axis line
		glVertex2s(100, 0);
		glVertex2s(-100, 0);

		//Y-axis line
		glVertex2s(0, 100);
		glVertex2s(0, -100);

	}
	glEnd();
	
	glBegin(GL_LINES);
	{
		//White
		glColor3f(1.0, 1.0, 1.0);
		
		//X label
		glVertex2s(93, 2);
		glVertex2s(97, 6);
		glVertex2s(97, 2);
		glVertex2s(93, 6);
		
		//Y label
		glVertex2s(4, 95);
		glVertex2s(6, 97);
		glVertex2s(4, 95);
		glVertex2s(2, 97);
		glVertex2s(4, 95);
		glVertex2s(4, 93);
		
	}
	glEnd();


	glBegin(GL_LINE_STRIP);
	{
		glColor3f(0.2, 0.2, 1.0);

		int x_plot, y_plot;

		//Sine wave plotter
		for (int l = -100; l <= 100; l++)
		{
			x_plot = l;
			y_plot = toWholeNumber(A*yScale*(sin(((double)(l*w)/xScale) + p)));
			glVertex2s(x_plot, y_plot);
		}
	}
	glEnd();

	glBegin(GL_POINTS);
	{
		glColor3f(1.0, 0.0, 0.0);

		int x_plot, y_plot;

		//Sine wave plotter
		for (int l = -100; l <= 100; l+=10)
		{
			x_plot = l;
			y_plot = toWholeNumber(A*yScale*(sin(((double)(l*w)/xScale) + p)));
			glVertex2s(x_plot, y_plot);
		}
	}
	glEnd();

	glFlush();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
	cout << "SINE WAVE GENERATOR" << endl;
	cout << "This program generates the plot of y = Asin(wx + p)" << endl;
	cout << "Where A = Amplitude" << endl;
	cout << "      w = Angular frequency (w = 2.pi.f = 2.pi/T)" << endl;
	cout << "      p = Phase difference" << endl << endl;

	cout << "Enter the amplitude: ";
	cin >> A;
	cout << "Enter the angular frequency: ";
	cin >> w;
	cout << "Enter the phase difference: ";
	cin >> p;

	//Description of the final equation to be plotted
	cout << "The wave y = " << A <<"sin(" << w << "x + " << p << ") is being generated" << endl;


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Wave Generator (Seriki Ayodele - 170408501)");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}