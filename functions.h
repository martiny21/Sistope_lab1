#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "BMPImage.h"
#include "BMPHeader.h"
#include "BMPInfoHeader.h"

//Leer archivo
BMPImage* read_bmp(const char* filename);

void free_bmp(BMPImage* image);                         //liberar espacion de imagen

void write_bmp(const char* filename, BMPImage* image);

BMPImage* grayScale_bmp(BMPImage* image);               //Escala de grises

BMPImage* saturate_bmp(BMPImage* image, float factor);  //Saturacion

BMPImage* binarize_bmp(BMPImage* image,float factor);    //Binarizacion