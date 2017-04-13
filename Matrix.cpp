#include <iostream>
#include <stdio.h>
#include "Matrix.h"
#include <math.h>
#include <glm/glm.hpp>

using namespace std;

#define PI 3.14159265

Matrix::~Matrix()
{
    
}

glm::mat4 scaleMatrix(float x, float y, float z){
	glm::mat4 m_aux = glm::mat4(1.0f);

	m_aux[0][0] *= x;
	m_aux[1][1] *= y;
	m_aux[2][2] *= z;

	return m_aux;
}

glm::mat4 translateMatrix(float x, float y, float z){
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