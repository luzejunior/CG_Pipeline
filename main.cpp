#include <stdio.h>
#include "main.h"
#include "objLoader.h"
#include "Matrix.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include "glm/gtc/matrix_transform.hpp"

#define PI 3.14159265

// Ponteiro para o objeto que carregará o modelo 3D (formato OBJ).
objLoader *objData;

unsigned int ViewPortWidth  = 512;
unsigned int ViewPortHeight = 512;

//Matrix M_Model;
//Matrix R1;
//Matrix R2;

glm::mat4 M_Model = glm::mat4(1.0f);;
glm::mat4 R1 = matrixRotationX(0.0f);
glm::mat4 R2 = matrixRotationY(0.5f);
glm::vec3 camera_pos;
glm::vec3 camera_look_at;
glm::vec3 camera_look_up;

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	cleanScreen();
	R1 = matrixRotationX(0.0f);
	R2 = glm::rotate(R2, 0.005f, glm::vec3(0.0f, 1.0f, 0.0f));

	M_Model = R1 * R2;

	printf("\nRotação: %f", M_Model[2][0]);

	camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
	camera_look_at = glm::vec3(0.0f, 0.0f, 0.0f);
	camera_look_up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 z_camera = -(camera_look_at - camera_pos) / glm::l1Norm(camera_look_at - camera_pos);
	glm::vec3 x_camera = glm::cross(camera_look_up, z_camera) / glm::l1Norm(glm::cross(camera_look_up, z_camera));
	glm::vec3 y_camera = glm::cross(z_camera, x_camera);

	glm::mat4 Bt = createMatrixWithVec3(x_camera, y_camera, z_camera);
	glm::mat4 T = translateMatrix(-camera_pos[0], -camera_pos[1], -camera_pos[2]);
	glm::mat4 M_View = T * Bt;

	glm::mat4 M_Model_View = M_Model * M_View;

	int d = 1;
	glm::mat4 M_Projection = createM_Projection(d);

	glm::mat4 M_Model_View_Projection = M_Model_View * M_Projection;

	//Create Screen Space:
	glm::mat4 M_Invert = glm::mat4(1.0f);
	M_Invert[1][1] = -1;

	glm::mat4 M_Translate = translateMatrix(0.9f, 0.8f, 0.0f);

	glm::mat4 M_Scale = glm::mat4(1.0f);
	M_Scale[0][0] = (ViewPortWidth-1) * 0.6f;
	M_Scale[1][1] = (ViewPortHeight-1) * 0.6f;

	glm::mat4 M_Screen = M_Invert * M_Translate * M_Scale;

	//printf("%d\n", objData->faceCount);
	for(int i=0; i<objData->faceCount; i++)
	{
	 	obj_face *o = objData->faceList[i];
  		glm::vec4 v1 = glm::vec4(objData->vertexList[o->vertex_index[0]]->e[0], // primeira linha
  					objData->vertexList[o->vertex_index[0]]->e[1],
  					objData->vertexList[o->vertex_index[0]]->e[2], 
	 				1.0f);
  		glm::vec4 v2 = glm::vec4(objData->vertexList[o->vertex_index[1]]->e[0], // primeira linha
  					objData->vertexList[o->vertex_index[1]]->e[1],
  					objData->vertexList[o->vertex_index[1]]->e[2], 
 				1.0f);
 		glm::vec4 v3 = glm::vec4(objData->vertexList[o->vertex_index[2]]->e[0], // primeira linha
 					objData->vertexList[o->vertex_index[2]]->e[1],
 					objData->vertexList[o->vertex_index[2]]->e[2], 
 				1.0f);

  		//M_V_Projection to vertices
  		v1 = v1 * M_Model_View_Projection;
  		v2 = v2 * M_Model_View_Projection;
  		v3 = v3 * M_Model_View_Projection;

  		//Canonic Space Homog.
  		v1 = v1 / v1[3];
  		v2 = v2 / v2[3];
  		v3 = v3 / v3[3];

  		//Espaço de tela:
  		v1 = v1 * M_Screen;
  		v2 = v2 * M_Screen;
  		v3 = v3 * M_Screen;

  		if(i == 346)
  			printf("\n V1: %d V1: %d, V2: %d V2: %d, V3: %d V3: %d e i = %d", (int) v1[0], (int)v1[1], (int)v2[0], (int)v2[1], (int)v3[0], (int)v3[1], i);

 	 	drawTriangle((int)v1[0], (int)v1[1], colorWhite, (int)v2[0], (int)v2[1], colorWhite, (int)v3[0], (int)v3[1], colorWhite);
 	}

	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	//putPixel(0, 1, colorGreen);
	//putPixel(0, 0, colorGreen);	
	//putPixel(1, 0, colorGreen);
	//putPixel(1, 1, colorGreen);
	//drawLine(0,0, colorRed, 511, 511, colorGreen); //1 octante
	// drawLine(0,0, colorRed, 100, 200, colorGreen); //2 octante
	// drawLine(0,0, colorRed, -100, 200, colorGreen); //3 octante
	//drawLine(0,0, colorRed, -200, 100, colorGreen); //4 octante
	//drawLine(0,0, colorRed, -200, -100, colorGreen); //5 octante
	// drawLine(0,0, colorRed, -100, -200, colorGreen); //6 octante
	//drawLine(0,0, colorRed, 100, -200, colorGreen); //7 octante
	//drawLine(0,0, colorRed, 200, -100, colorGreen); //8 octante
	//drawLine(-100, 0, colorRed, -100, 90, colorGreen);
	//drawLine(-100, 0, colorRed, 100, 0, colorBlue);
	//drawLine(-100, 90, colorGreen, 100, 0, colorBlue);
	//drawTriangle(292, 366, colorBlue, 275, 379, colorBlue, 275, 379, colorBlue);
	//drawTriangle(309, 290, colorBlue, 311, 296, colorBlue, 309, 290, colorBlue);
}

void cleanScreen(){
	for(int i=0; i<IMAGE_WIDTH; i++){
		for(int j=0; j<IMAGE_HEIGHT; j++){
			putPixel(i, j, colorBlack);
		}
	}
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	objData = new objLoader();			// cria o objeto que carrega o modelo
	objData->load("monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
										// Neste caso, deve ser sempre do tipo OBJ.

	// Habilite esta função se você deseja imprimir na tela dados do modelo
	// gerados durante a sua carga.
	//PrintModelInfo(objData);

	//glutInit(&argc,argv);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	//glutInitWindowSize(512, 512);
	//glutInitWindowPosition(100,100);
	//glutCreateWindow("OBJ Loader");

	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

