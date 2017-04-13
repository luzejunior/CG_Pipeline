#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

unsigned char * FBptr;

int colorRed[4] = {255, 0, 0, 255}; //Array de 4 elementos que compõem a cor Vermelha.
int colorGreen[4] = {0, 255, 0, 255}; //Array de 4 elementos que compõem a cor Verde.
int colorBlue[4] = {0, 0, 255, 255}; //Array de 4 elementos que compõem a cor Azul.
int colorWhite[4] = {255, 255, 255, 255};
int colorBlack[4] = {0,0,0,255};

#endif // _DEFINITIONS_H_

