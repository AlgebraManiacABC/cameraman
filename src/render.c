#include "render.h"
#include "shaders.h"
#include <cglm/cglm.h>

GLuint backgroundVAO = 0;
GLuint actorVAO = 0;
GLuint squareVAO = 0;

//	Z == -1 is the background Z
GLuint backgroundVertexBuffer = 0;
GLfloat backgroundVertices[] =
{
	//	Pos,   TexCoord
	-1,  1, 0.75,  0, 1,	//	Top left
	 1,  1, 0.75,  1, 1,	//	Top right
	-1, -1, 0.75,  0, 0,	//	Bottom left
	 1, -1, 0.75,  1, 0	//	Bottom right
};

GLuint bodyVertexBuffer = 0;
GLfloat bodyVertices[] =
{
	-0.5,  0.5, 0.25,  0, 1,	//	Top left
	 0.5,  0.5, 0.25,  1, 1,	//	Top right
	-0.5, -0.5, 0.25,  0, 0,	//	Bottom left
	 0.5, -0.5, 0.25,  1, 0	//	Bottom right
};

GLuint squareVertexBuffer = 0;
GLfloat squareVertices[] =
{
	-0.5,  0.5, 0.25,  0, 1,
	 0.5,  0.5, 0.25,  1, 1,
	-0.5, -0.5, 0.25,  0, 0,
	 0.5, -0.5, 0.25,  1, 0
};

GLuint rectVertexIndices[] =
{
	2, 1, 0, /**/ 1, 2, 3
};
GLuint rectElementBuffer = 0;

void initRenderer(void)
{
	//	General OpenGL Info
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0f,1.0f,0.0f,1.0f);

	//	Global VAO
	glGenVertexArrays(1,&backgroundVAO);
	glBindVertexArray(backgroundVAO);

	//	Background Vertex Data
	glGenBuffers(1,&backgroundVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,backgroundVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(backgroundVertices),backgroundVertices,GL_STATIC_DRAW);
	//	Specify Pos:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,NULL);
	//	Specify TexCoord:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,(void*)(sizeof(GLfloat)*3));
	//	Done!
	glBindBuffer(GL_ARRAY_BUFFER,0);

	//	Rectangle Indices
	glGenBuffers(1,&rectElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rectElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(rectVertexIndices),rectVertexIndices,GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	//	Actor VAO (Cameraman)
	glGenVertexArrays(1,&actorVAO);
	glBindVertexArray(actorVAO);

	//	Cameraman Vertex Data
	glGenBuffers(1,&bodyVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,bodyVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(bodyVertices),bodyVertices,GL_STATIC_DRAW);
	//	Specify Pos:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,NULL);
	//	Specify TexCoord:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,(void*)(sizeof(GLfloat)*3));
	//	Done!
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rectElementBuffer);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

	glGenVertexArrays(1,&squareVAO);
	glBindVertexArray(squareVAO);

	//	Square Vertex Data
	glGenBuffers(1,&squareVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,squareVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER,sizeof(squareVertices),squareVertices,GL_STATIC_DRAW);
	//	Specify Pos:
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,NULL);
	//	Specify TexCoord:
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(GLfloat)*5,(void*)(sizeof(GLfloat)*3));
	//	Done!
	glBindBuffer(GL_ARRAY_BUFFER,0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rectElementBuffer);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void renderBackground(GLuint texture)
{
	if(!texture) return;
	mat4 mvMatrix = GLM_MAT4_IDENTITY_INIT;
	glUniformMatrix4fv(transformLoc,1,GL_FALSE,(float*)mvMatrix);
	glBindVertexArray(backgroundVAO);
	glBindTexture(GL_TEXTURE_2D,texture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rectElementBuffer);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
	glBindVertexArray(0);
}

void renderButton(button *b)
{
	mat4 modelMatrix;
	getButtonMatrix(b,modelMatrix);
	glUniformMatrix4fv(transformLoc,1,GL_FALSE,(float*)modelMatrix);
	glBindVertexArray(squareVAO);
	glBindTexture(GL_TEXTURE_2D,getButtonTexture(b));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,rectElementBuffer);
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
	glBindVertexArray(0);
}