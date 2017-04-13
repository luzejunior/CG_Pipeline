#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************

//Função para desenhar pixels na tela.
//Recebe como parametro os pontos X e Y a serem colocados num plano cartesiano na tela.
void putPixel(int x, int y, int RGBA[4]){

	int print_position = (x + (y * IMAGE_WIDTH)) * 4; //Posição do Array da memória onde o Pixel vai ser pintado.

	//Definição do array dos pixels na tela.
	for(int i = 0; i<4; i++){
		FBptr[print_position+i] = RGBA[i];
	}
}

//Função para desenhar linhas na tela.
void drawLine(int x0, int y0, int RGBA0[4], int x1, int y1, int RGBA1[4]){

	//Variables.
	int deltaX = x1 - x0; //Valor de DeltaX
	int deltaY = y1 - y0; //Valor de DeltaY
	int j = y0; //Inicializando variável J, que corresponde ao Y do plano cartesiano.
	int incrementX = 0; //Variável que controla o incremento do X no plano cartesiano.
	int incrementX1 = 0;
	int incrementY = 0; //Variável que controla o incremento do Y no plano cartesiano.
	int incrementY1 = 0; //Variável auxiliar que controla o incremento do Y no plano cartesiano.
	int RGBA2[4]; //Variavel para cor Auxiliar

	//Definição da variável de cor auxiliar.
	RGBA2[0] = RGBA0[0];
	RGBA2[1] = RGBA0[1];
	RGBA2[2] = RGBA0[2];
	RGBA2[3] = RGBA0[3];

	if(deltaX == 0 && deltaY == 0){
		putPixel(x0, y0, RGBA2);
		return;
	}

	if (deltaX < 0){
		deltaX = -deltaX;
		incrementX = -1;
		incrementX1 = -1;
	}
	else if(deltaX > 0){
		incrementX = 1;
		incrementX1 = 1;
	}
	if(deltaY < 0){
		deltaY = -deltaY;
		incrementY = -1;
	}
	else if(deltaY > 0){
		incrementY = 1;
	}

	if(deltaY > deltaX){
		int tmp1 = deltaX;
		deltaX = deltaY;
		deltaY = tmp1;
		if (incrementY<0){
			deltaX = -deltaX;
			//std::clog << deltaX << "\n";
		}
		if(deltaX<0){
			incrementY1 = -1;
			deltaX = -deltaX;
		}
		else if(deltaX>0){
			incrementY1 = 1;
		}
		incrementX1 = 0;
	}

	int maior_Distancia = deltaX; //Numero máximo de pixels que vai ser pintado.
	if(deltaX == 0){
		maior_Distancia = deltaY;
	}

	int colorGradientRatio = 256/maior_Distancia;
	int error = (maior_Distancia)/2;
	int i = x0;

	for(int k=0; k<=maior_Distancia; k++){
		// std::clog << "Pixel X: " << i << " Y: " << j << "\n";
		// std::clog << "DeltaX: " << deltaX << "\n";
		// std::clog << "DeltaY: " << deltaY << "\n";
		// std::clog << "Error: " << error << "\n";
		// std::clog << "incrementX: " << incrementX << " e " << incrementX1 << "\n";
		// std::clog << "incrementY: " << incrementY << " e " << incrementY1 << "\n\n";	
		
		putPixel(i, j, RGBA2);
		error += deltaY;

		// if(RGBA0[0] > 0 && RGBA2[0] <= 255){
		// 	RGBA2[0] -= colorGradientRatio;
		// }
		// else if(RGBA0[1] > 0 && RGBA2[1] <= 255){
		// 	RGBA2[1] -= colorGradientRatio;
		// }
		// else if(RGBA0[2] > 0 && RGBA2[2] <= 255){
		// 	RGBA2[2] -= colorGradientRatio;
		// }
		// if(RGBA1[0] > 0 && RGBA2[0] <= 255){
		// 	RGBA2[0] += colorGradientRatio;
		// }
		// if(RGBA1[1] > 0 && RGBA2[1] <= 255){
		// 	RGBA2[1] += colorGradientRatio;
		// }
		// if(RGBA1[2] > 0 && RGBA2[2] <= 255){
		// 	RGBA2[2] += colorGradientRatio;
		// }

		//std::clog << "RGBA2 : " << RGBA2[0] << " " << RGBA2[1] << " " << RGBA2[2] << "\n";
	
		if(error >= deltaX){
			// std::clog << "ENTREI AQUI!";
			j += incrementY;
			i += incrementX;
			error -= deltaX;
		}else{
			// std::clog << "ENTREI AQUI2!";
			j += incrementY1;
			i += incrementX1;
		}	
	}
}

void drawTriangle(int x0, int y0, int RGBA0[4], int x1, int y1, int RGBA1[4], int x2, int y2, int RGBA2[4]){
	drawLine(x0, y0, RGBA0, x1, y1, RGBA1);
	drawLine(x0, y0, RGBA0, x2, y2, RGBA2);
	drawLine(x1, y1, RGBA1, x2, y2, RGBA2);
}

#endif // _MYGL_H_

