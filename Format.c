#include "Format.h"

/*
Entrada: Entero a concatenar
Salida: Cadena de caracteres formateado
Descripcion:
*/
char * SaturatedChars(int loop){

    char saturated[100] = "saturated";
    char bmp[20] = ".bmp";
    char *retorno = (char*)malloc(strlen(saturated));
    
    // Concatenar variable saturated con loop y bmp
    snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);
    snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);
    
    strcpy(retorno,saturated);
    return retorno;
}

/*
Entrada: Entero a concatenar
Salida: Cadena de caracteres formateado
Descripcion:
*/
char* GrayChars(int loop){
    
    char grayScale[100] = "grayScale";
    char bmp[20] = ".bmp";
    char *retorno = (char*)malloc(strlen(grayScale));

    snprintf(grayScale + strlen(grayScale), sizeof(grayScale) - strlen(grayScale), "%d", loop);
    snprintf(grayScale + strlen(grayScale), sizeof(grayScale)- strlen(grayScale), "%s", bmp);

    strcpy(retorno,grayScale);
    return retorno;

}