#include "Saturated.h"

/*
Entrada: Entero a concatenar
Salida: Cadena de caracteres formateado
Descripcion:
*/
char * SaturatedChars(int loop){

    char saturated[100] = "saturated";
    char bmp[20] = ".bmp";

    // Concatenar variable saturated con loop y bmp
    snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);
    snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);

    return *saturated;
}