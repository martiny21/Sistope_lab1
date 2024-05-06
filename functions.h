#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "BMPImage.h"
#include "BMPHeader.h"
#include "BMPInfoHeader.h"

//Leer archivo
BMPImage* read_bmp(const char* filename);

void free_bmp(BMPImage* image);

void write_bmp(const char* filename, BMPImage* image);

BMPImage* grayScale_bmp(BMPImage* image);