#include "render.h"

GLuint VAO = 0;

//	Z == -1 is the background Z
GLfloat backgroundVertices[] =
{
	//	Pos,   TexCoord
	-1,  1, -1,  0, 1,	//	Top left
	 1,  1, -1,  1, 1,	//	Top right
	-1, -1, -1,  0, 0,	//	Bottom left
	 1, -1, -1,  1, 0	//	Bottom right
};
GLuint backgroundVertexIndices[] =
{
	2, 1, 0, /**/ 1, 2, 3
};

GLuint backgroundVertexBuffer = 0;
GLuint backgroundElementBuffer = 0;

void initRenderer(void)
{
	//	General OpenGL Info
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	//	Global VAO
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

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

	//	Background Indices
	glGenBuffers(1,&backgroundElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,backgroundElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(backgroundVertexIndices),backgroundVertexIndices,GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void renderBackground(GLuint texture)
{
	if(!texture) return;
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D,texture);
	//fprintf(stderr,"Texture bound!\n");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,backgroundElementBuffer);
	//fprintf(stderr,"Buffer bound!\n");
	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
	//fprintf(stderr,"Elements drawn!\n");
	glBindVertexArray(0);
}