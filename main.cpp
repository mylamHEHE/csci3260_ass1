///////////////////////////////////////////
////Type your name and student ID here/////
////Name:Lam Ming Yuen
////Student ID:1155083016
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
//using glm::vec3; for namespace reason
//using glm::mat4;
GLint programID;

GLfloat head[];
GLuint vao_head;

GLfloat line[];
GLuint vao_line;

//GLfloat floor[];
GLuint vao_floor;

GLfloat button[];
GLuint vao_button;

bool rotating = false;
bool scaling = false;

float x = 1.0f;
float y = 1.0f;
float z = 1.0f;

float x_delta = 0.1f;
int x_press_num = 0;
float y_delta = 0.1f;
int y_press_num = 0;
float z_delta = 0.1f;
int z_press_num = 0;
float theta = 0.0f;
float theta_delta = 0.0008f;

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

void keyboard(unsigned char key, int x, int y)
{
	if (x_press_num == 3 && y_press_num == 2 && z_press_num == -1)
	{
		Beep (330,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (392,100);Sleep(700);
        Beep (196,100);Sleep(700);
        Beep (262,300);Sleep(300);
        Beep (196,300);Sleep(300);
        Beep (164,300);Sleep(300);
        Beep (220,300);Sleep(100);
        Beep (246,100);Sleep(300);
        Beep (233,200);
        Beep (220,100);Sleep(300);
        Beep (196,100);Sleep(150);
        Beep (330,100);Sleep(150);
        Beep (392,100);Sleep(150);
        Beep (440,100);Sleep(300);
        Beep (349,100);Sleep(100);
        Beep (392,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(100);
        Beep (247,100);Sleep(500);
        Beep (262,300);Sleep(300);
        Beep (196,300);Sleep(300);
        Beep (164,300);Sleep(300);
        Beep (220,300);Sleep(100);
        Beep (246,100);Sleep(300);
        Beep (233,200);
        Beep (220,100);Sleep(300);
        Beep (196,100);Sleep(150);
        Beep (330,100);Sleep(150);
        Beep (392,100);Sleep(150);
        Beep (440,100);Sleep(300);
        Beep (349,100);Sleep(100);
        Beep (392,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(100);
        Beep (247,100);Sleep(900);
        Beep (392,100);Sleep(100);
        Beep (370,100);Sleep(100);
        Beep (349,100);Sleep(100);
        Beep (311,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (207,100);Sleep(100);
        Beep (220,100);Sleep(100);
        Beep (262,100);Sleep(300);
        Beep (220,100);Sleep(100);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(500);
        Beep (392,100);Sleep(100);
        Beep (370,100);Sleep(100);
        Beep (349,100);Sleep(100);
        Beep (311,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (523,100);Sleep(300);
        Beep (523,100);Sleep(100);
        Beep (523,100);Sleep(1100);
        Beep (392,100);Sleep(100);
        Beep (370,100);Sleep(100);
        Beep (349,100);Sleep(100);
        Beep (311,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (207,100);Sleep(100);
        Beep (220,100);Sleep(100);
        Beep (262,100);Sleep(300);
        Beep (220,100);Sleep(100);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(500);
        Beep (311,300);Sleep(300);
        Beep (296,300);Sleep(300);
        Beep (262,300);Sleep(1300);
        Beep (262,100);Sleep(100);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(300);
        Beep (330,200);Sleep(50);
        Beep (262,200);Sleep(50);
        Beep (220,200);Sleep(50);
        Beep (196,100);Sleep(700);
        Beep (262,100);Sleep(100);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(100);
        Beep (330,100);Sleep(700);
        Beep (440,100);Sleep(300);
        Beep (392,100);Sleep(500);
        Beep (262,100);Sleep(100);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (294,100);Sleep(300);
        Beep (330,200);Sleep(50);
        Beep (262,200);Sleep(50);
        Beep (220,200);Sleep(50);
        Beep (196,100);Sleep(700);
        /*Intro*/
        Beep (330,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (330,100);Sleep(300);
        Beep (262,100);Sleep(100);
        Beep (330,100);Sleep(300);
        Beep (392,100);Sleep(700);
        Beep (196,100);Sleep(700);
        Beep (196,100);Sleep(125);
        Beep (262,100);Sleep(125);
        Beep (330,100);Sleep(125);
        Beep (392,100);Sleep(125);
        Beep (523,100);Sleep(125);
        Beep (660,100);Sleep(125);
        Beep (784,100);Sleep(575);
        Beep (660,100);Sleep(575);
        Beep (207,100);Sleep(125);
        Beep (262,100);Sleep(125);
        Beep (311,100);Sleep(125);
        Beep (415,100);Sleep(125);
        Beep (523,100);Sleep(125);
        Beep (622,100);Sleep(125);
        Beep (830,100);Sleep(575);
        Beep (622,100);Sleep(575);
        Beep (233,100);Sleep(125);
        Beep (294,100);Sleep(125);
        Beep (349,100);Sleep(125);
        Beep (466,100);Sleep(125);
        Beep (587,100);Sleep(125);
        Beep (698,100);Sleep(125);
        Beep (932,100);Sleep(575);
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (932,100);Sleep(125);
        Beep (1046,675);
	}
	//TODO:
	if (key == 'a')
	{
		x_press_num -= 1;
	}
	if (key == 'd')
	{
		x_press_num += 1;
	}
	if (key == 'x')
	{
		y_press_num -= 1;
	}
	if (key == 'w')
	{
		y_press_num += 1;
	}
	if (key == 'f')
	{
		z_press_num -= 1;
	}
	if (key == 'c')
	{
		z_press_num += 1;
	}
	if (key == 'z')
	{
		x_press_num = 0;
		y_press_num = 0;
		z_press_num = 0;
	}
}

void mouse(int button, int state, int _x, int _y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		rotating = !rotating;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		scaling = !scaling;
		if (scaling)
		{
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;
		}
		else
		{
			x = 0.5f;
			y = 0.5f;
			z = 0.5f;
		}
	}
}

void sendDataToOpenGL()
{
	//TODO:
	//create point, line, 2D object and 3D object here and bind to VAOs & VBOs
	const GLfloat head[] =
	{
		//top
		+2.0f, +2.0f, -2.0f,//leftup
		+1.0f, +1.0f, +1.0f,//colour

		+4.0f, +2.0f, -2.0f,//rightup
		+1.0f, +1.0f, +1.0f,//colour

		+2.0f, +2.0f, +0.0f,//leftdown
		+1.0f, +1.0f, +1.0f,//colour

		+4.0f, +2.0f, +0.0f,//rightdown
		+1.0f, +1.0f, +1.0f,//colour

		//bottom
		+2.0f, +0.0f, -2.0f,//leftup
		+1.0f, +1.0f, +1.0f,//colour

		+4.0f, +0.0f, -2.0f,//rightup
		+1.0f, +1.0f, +1.0f,//colour

		+2.0f, +0.0f, +0.0f,//leftdown
		+1.0f, +1.0f, +1.0f,//colour

		+4.0f, +0.0f, +0.0f,//rightdown
		+1.0f, +1.0f, +1.0f,//colour
	};
	GLushort head_index[] =
	{
		0,1,2, 1,2,3,
		4,5,6, 5,6,7,
		0,2,6, 0,4,6,
		1,3,5, 3,5,7,
		2,3,6, 3,6,7,
		0,1,4, 1,4,5,

	};
	const GLfloat line[] =
	{
		//top
		+2.0f, +2.0f, -2.0f,//leftup
		+0.0f, +0.0f, +0.0f,//colour

		+4.0f, +2.0f, -2.0f,//rightup
		+0.0f, +0.0f, +0.0f,//colour

		+2.0f, +2.0f, +0.0f,//leftdown
		+0.0f, +0.0f, +0.0f,//colour

		+4.0f, +2.0f, +0.0f,//rightdown
		+0.0f, +0.0f, +0.0f,//colour

		//bottom
		+2.0f, +0.0f, -2.0f,//leftup
		+0.0f, +0.0f, +0.0f,//colour

		+4.0f, +0.0f, -2.0f,//rightup
		+0.0f, +0.0f, +0.0f,//colour

		+2.0f, +0.0f, +0.0f,//leftdown
		+0.0f, +0.0f, +0.0f,//colour

		+4.0f, +0.0f, +0.0f,//rightdown
		+0.0f, +0.0f, +0.0f,//colour


		+2.5f, +0.5f, +0.0f,//mouth
		+1.0f, +0.0f, +0.0f,//colour

		+3.5f, +0.5f, +0.0f,//mouth
		+1.0f, +0.0f, +0.0f,//colour

		+2.5f, +1.5f, +0.0f,//left eye
		+0.0f, +1.0f, +0.0f,//colour

		+3.5f, +1.5f, +0.0f,//right eye
		+0.0f, +1.0f, +0.0f,//colour

		+3.0f, +1.0f, +0.0f,//nose
		+0.0f, +0.0f, +0.0f,//colour
	};
	GLushort line_index[] =
	{
		0,1, 1,3, 3,2, 0,2,
		4,6, 4,5, 5,7, 6,7,
		0,4, 2,6, 3,7, 1,5,
		8,9
	};
	const GLfloat button[] =
	{
		+0.5f, +0.0f, +0.0f,//mouth
		+2.0f, +2.0f, +0.0f,//colour

		+1.5f, +0.0f, +0.0f,//mouth
		+2.0f, +2.0f, +0.0f,//colour

		+1.5f, +1.5f, +0.0f,//mouth
		+2.0f, +2.0f, +0.0f,//colour

		+0.5f, +1.5f, +0.0f,//mouth
		+2.0f, +2.0f, +0.0f,//colour
	};
	GLushort button_index[] =
	{
		0,2,3, 0,1,2,
	};
	const GLfloat floor[] =
	{
		+0.0f, +0.0f, +0.0f,
		+0.0f, +0.0f, +1.0f,

		+10.0f, +0.0f, +0.0f,
		+0.0f, +0.0f, +1.0f,

		+10.0f, +0.0f, +10.0f,
		+0.0f, +0.0f, +1.0f,

		+0.0f, +0.0f, +10.0f,
		+0.0f, +0.0f, +1.0f,
};
	GLushort floor_index[] =
	{
		0,2,3, 0,1,2,
	};

	vao_head;
	glGenVertexArrays(1, &vao_head);
	glBindVertexArray(vao_head);  
	GLuint vbo_head;
	glGenBuffers(1, &vbo_head);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_head);
	glBufferData(GL_ARRAY_BUFFER, sizeof(head), head, GL_STATIC_DRAW);
	//index buffer
	GLuint vbo_head_buffer;
	glGenBuffers(1, &vbo_head_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_head_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(head_index), head_index, GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	
	//LINE
	vao_line;
	glGenVertexArrays(1, &vao_line);
	glBindVertexArray(vao_line); 
	GLuint vbo_line;
	glGenBuffers(1, &vbo_line);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
	//index buffer
	GLuint vbo_line_buffer;
	glGenBuffers(1, &vbo_line_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_line_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_index), line_index, GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));

	//floor
	vao_floor;
	glGenVertexArrays(1, &vao_floor);
	glBindVertexArray(vao_floor);
	GLuint vbo_floor;
	glGenBuffers(1, &vbo_floor);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(floor), floor, GL_STATIC_DRAW);
	//index buffer
	GLuint vbo_floor_buffer;
	glGenBuffers(1, &vbo_floor_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_floor_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floor_index), floor_index, GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));

	//button
	vao_button;
	glGenVertexArrays(1, &vao_button);
	glBindVertexArray(vao_button);
	GLuint vbo_button;
	glGenBuffers(1, &vbo_button);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_button);
	glBufferData(GL_ARRAY_BUFFER, sizeof(button), button, GL_STATIC_DRAW);
	//index buffer
	GLuint vbo_button_buffer;
	glGenBuffers(1, &vbo_button_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_button_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(button_index), button_index, GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	//vertex color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
}

void paintGL(void)
{
	//TODO:
	//render your objects and control the transformation here
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f); //specify the background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	if(rotating) theta += theta_delta;

	glm::mat4 modelTransformMatrix;
	GLint modelTransformMatrixUniformLocation; 
	glm::mat4 projectionMatrix;
	GLuint projectionMatrixUniformLocation;

	//floor
	glBindVertexArray(vao_floor);
	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, -7.0f)) *
		glm::translate(glm::mat4(), glm::vec3(5.0f, 0.0f, 5.0f)) *
		glm::rotate(glm::mat4(), theta, glm::vec3(0.0f, 1.0f, 0.0f))*
		glm::translate(glm::mat4(), glm::vec3(-5.0f, 0.0f, -5.0f));
	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

	//button
	glBindVertexArray(vao_button);

	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::translate(glm::mat4(), glm::vec3(3.0f, 1.0f, 0.0f))*
			//glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f))*
			glm::scale(glm::mat4(), glm::vec3(x, y, z))*
			//glm::translate(glm::mat4(), glm::vec3(2.0f, 0.25f, 0.0f));
			glm::translate(glm::mat4(), glm::vec3(-1.0f, -0.75f, 0.0f));
	

	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

	//body
	glBindVertexArray(vao_head);
	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);
	
	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
	
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0); //render primitives from array data

	//head
	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(), glm::vec3(x_press_num, y_press_num, z_press_num))*
		glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5f, 0.5f))*
		glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, 1.0f));
	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0); //render primitives from array data

	//line
	glBindVertexArray(vao_line);
	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glLineWidth(1.5f);
	glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, 0);

	//line
	modelTransformMatrix = glm::lookAt(glm::vec3(8.0f, 8.0f, 6.0f),
		glm::vec3(3.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::translate(glm::mat4(), glm::vec3(x_press_num, y_press_num, z_press_num))*
		glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5f, 0.5f))*
		glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, 1.0f));
	modelTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelTransformMatrix");
	glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1,
		GL_FALSE, &modelTransformMatrix[0][0]);

	projectionMatrix = glm::perspective(20.0f, 1.0f, 0.5f, 20.f);
	projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 10, 3);
	glDrawElements(GL_LINES, 36, GL_UNSIGNED_SHORT, 0); 
	
	glFlush();
	glutPostRedisplay();
}

void initializedGL(void) //run only once
{
	sendDataToOpenGL();
	installShaders();
}

int main(int argc, char *argv[])
{
	/*Initialization*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Assignment 1");
	glewInit();

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	initializedGL();
	glutDisplayFunc(paintGL);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

	return 0;
}