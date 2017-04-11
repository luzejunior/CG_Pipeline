#include <iostream>
#include <stdio.h>
#include "Matrix.h"
#include <math.h>
#include <glm/glm.hpp>

using namespace std;

#define PI 3.14159265

void Matrix::loadIdentity(){
	//Linha 1:
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	//Linha 2:
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	//Linha 3:
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;
	
	//Linha 4:
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix::matrixScale(float x, float y, float z){
	m[0][0] *= x;
	m[1][1] *= y;
	m[2][2] *= z;
}

Matrix::~Matrix()
{
    
}

glm::mat4 transposeMatrix(float x, float y, float z){
	glm::mat4 m_aux = glm::mat4(1.0f);
	//m_aux.loadIdentity();

	m_aux[0][3] = x;
	m_aux[1][3] = y;
	m_aux[2][3] = z;

	return m_aux;
}

glm::mat4 matrixRotationX(float angle){
	glm::mat4 m_aux = glm::mat4(1.0f);
	
	m_aux[1][1] = cos(angle*PI/180.0);
	m_aux[2][1] = sin(angle*PI/180.0);
	m_aux[1][2] = -sin(angle*PI/180.0);
	m_aux[2][2] = cos(angle*PI/180.0);

	return m_aux;
}

glm::mat4 matrixRotationY(float angle){
	glm::mat4 m_aux = glm::mat4(1.0f);

	m_aux[0][0] = cos(angle*PI/180.0);
	m_aux[0][2] = sin(angle*PI/180.0);
	m_aux[2][0] = -sin(angle*PI/180.0);
	m_aux[2][2] = cos(angle*PI/180.0);

	return m_aux;
}

glm::mat4 createMatrixWithVec3(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3){
	glm::mat4 m_aux = glm::mat4(1.0f);

	for(int i=0; i<3; i++){
		m_aux[0][i] = v1[i];
	}

	for(int i=0; i<3; i++){
		m_aux[1][i] = v2[i];
	}

	for(int i=0; i<3; i++){
		m_aux[2][i] = v3[i];
	}
	return m_aux;
}

glm::mat4 createM_Projection(float d){
	glm::mat4 m_aux = glm::mat4(1.0f);

	m_aux[2][3] = d;
	m_aux[3][2] = -1/d;
	m_aux[3][3] = 0;

	return m_aux;
}

Matrix matrixMultiply(Matrix m1, Matrix m2){
	Matrix m_aux;
	m_aux.loadIdentity();

	for(int i=0; i<4; i++){
		printf("[ ");
		for(int j=0; j<4; j++){
			printf("| %f |", m1.m[i][j]);
		}
		printf("]\n");
	}

	printf("\n");

	for(int i=0; i<4; i++){
		printf("[ ");
		for(int j=0; j<4; j++){
			printf("| %f |", m2.m[i][j]);
		}
		printf("]\n");
	}

	printf("\n");

	m_aux.m[0][0] = m1.m[0][0]*m2.m[0][0] + m1.m[0][1]*m2.m[1][0] + m1.m[0][2]*m2.m[2][0] + m1.m[0][3]*m2.m[3][0];
	m_aux.m[0][1] = m1.m[0][0]*m2.m[0][1] + m1.m[0][1]*m2.m[1][1] + m1.m[0][2]*m2.m[2][1] + m1.m[0][3]*m2.m[3][1];
	m_aux.m[0][2] = m1.m[0][0]*m2.m[0][2] + m1.m[0][1]*m2.m[1][2] + m1.m[0][2]*m2.m[2][2] + m1.m[0][3]*m2.m[3][2];
	m_aux.m[0][3] = m1.m[0][0]*m2.m[0][3] + m1.m[0][1]*m2.m[1][3] + m1.m[0][2]*m2.m[2][3] + m1.m[0][3]*m2.m[3][3];

	m_aux.m[1][0] = m1.m[1][0]*m2.m[0][0] + m1.m[1][1]*m2.m[1][0] + m1.m[1][2]*m2.m[2][0] + m1.m[1][3]*m2.m[3][0];
	m_aux.m[1][1] = m1.m[1][0]*m2.m[0][1] + m1.m[1][1]*m2.m[1][1] + m1.m[1][2]*m2.m[2][1] + m1.m[1][3]*m2.m[3][1];
	m_aux.m[1][2] = m1.m[1][0]*m2.m[0][2] + m1.m[1][1]*m2.m[1][2] + m1.m[1][2]*m2.m[2][2] + m1.m[1][3]*m2.m[3][2];
	m_aux.m[1][3] = m1.m[1][0]*m2.m[0][3] + m1.m[1][1]*m2.m[1][3] + m1.m[1][2]*m2.m[2][3] + m1.m[1][3]*m2.m[3][3];

	m_aux.m[2][0] = m1.m[2][0]*m2.m[0][0] + m1.m[2][1]*m2.m[1][0] + m1.m[2][2]*m2.m[2][0] + m1.m[2][3]*m2.m[3][0];
	m_aux.m[2][1] = m1.m[2][0]*m2.m[0][1] + m1.m[2][1]*m2.m[1][1] + m1.m[2][2]*m2.m[2][1] + m1.m[2][3]*m2.m[3][1];
	m_aux.m[2][2] = m1.m[2][0]*m2.m[0][2] + m1.m[2][1]*m2.m[1][2] + m1.m[2][2]*m2.m[2][2] + m1.m[2][3]*m2.m[3][2];
	m_aux.m[2][3] = m1.m[2][0]*m2.m[0][3] + m1.m[2][1]*m2.m[1][3] + m1.m[2][2]*m2.m[2][3] + m1.m[2][3]*m2.m[3][3];

	m_aux.m[3][0] = m1.m[3][0]*m2.m[0][0] + m1.m[3][1]*m2.m[1][0] + m1.m[3][2]*m2.m[2][0] + m1.m[3][3]*m2.m[3][0];
	m_aux.m[3][1] = m1.m[3][0]*m2.m[0][1] + m1.m[3][1]*m2.m[1][1] + m1.m[3][2]*m2.m[2][1] + m1.m[3][3]*m2.m[3][1];
	m_aux.m[3][2] = m1.m[3][0]*m2.m[0][2] + m1.m[3][1]*m2.m[1][2] + m1.m[3][2]*m2.m[2][2] + m1.m[3][3]*m2.m[3][2];
	m_aux.m[3][3] = m1.m[3][0]*m2.m[0][3] + m1.m[3][1]*m2.m[1][3] + m1.m[3][2]*m2.m[2][3] + m1.m[3][3]*m2.m[3][3];

	return m_aux;
}