#include <getopt.h>
#include <string.h>
#include "functions.h"


int main(int argc, char *argv[]){
    int f = 3, i = 1;
    float u = 0.5, p = 1.3, v = 0.5;
    char *C = NULL , *R = NULL, *N = NULL;
    //Los prametros -C y -R son obligatorios

    int loop = 1;   //Verdadero, es una bandera para continuar un ciclo

    int option;

    /*
    -N: nombre del prefijo de las imágenes.
    -f: cantidad de filtros a aplicar.
    -p: factor de saturación del filtro.
    -u: UMBRAL para binarizar la imagen.
    -v: UMBRAL para clasificación.
    -C: nombre de la carpeta resultante con las imágenes, con los filtros aplicados.
    -R: nombre del archivo CSV con las clasificaciones resultantes.
    */

    //Lectura de argumentos usando getopt()
    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:l")) != -1) { //l simplemente es un parche para que pueda leer R
        switch (option)
        {
        case 'N':
            N = optarg;
            break;
        case 'f':
            f = atoi(optarg);
            break;
        case 'p':
            p = atof(optarg);
            break;
        case 'u':
            u = atoi(optarg);
            break;
        case 'v':
            v = atoi(optarg);
            break;
        case 'C':
            C = optarg;
            break;
        case 'R':
            R = optarg;
            break;
        }
    }

    //printf("R= %s, C = %s, f= %d",R,C,f); BOOOOOOOOOORRAR PAAAAAAAAAAAARA ENTREGA
    //Verificar que se entregan los argumentos olbigatorios
    if (R == NULL && C == NULL){
        printf("Falto el ingreso de parametros obligatorios, nombre de la carpeta resultante o nombre del archivo CSV\n");
        return 0;
    }
    
    
    while (loop!=0)     //Esto me genera ruido porque de no encontrar mas simplemente termina la ejecucion
    {
        
        char *name;
        char number[50];
        name= N;                        
        sprintf(number, "%d",loop);
        strcat(name, number);
        printf("Nombre = %s\n",name);       //Falta ver como agregar el "_"
        
        BMPImage *image;
        image = read_bmp(name);
        
        if(image == NULL){
            printf("No se pudo encontrar otra imagen o hubo un error en el proceso");   
            //Se podria modificar el read para que devuelva cosas distintas en funcion si no pudo abrir la imagen o
            //hubo un error con el formato de la imagen
            return 0;
        }

        BMPImage *new_image = saturation(image, p);

        write_bmp("saturated.bmp", new_image);
        loop++;
    }
    

    return 0;
}