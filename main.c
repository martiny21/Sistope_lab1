#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
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

    //Creacion de carpeta
    char *carpeta = C;
    if (mkdir(carpeta,0777) == 0) {
        printf("La carpeta se creó correctamente.\n");
    } else {
        printf("Error al crear la carpeta.\n");
    }

    //Creacion archivo CSV
    FILE *fileCSV;
    fileCSV = fopen(R, "w"); // Abre el archivo en modo escritura ("w")

    if (fileCSV == NULL) {
        printf("Error al abrir el archivo.");
        return 0;
    }

    //Archivo CSV con 2 columnas
    fprintf(fileCSV, "Nombre Imagen,Clasificacion\n");
    //fclose(fileCSV);  //--------------El archivo se cierra al terminar el programa

    
    char bmp[20] = ".bmp";
    char *name1;
    name1 = N;
    char signo = '_'; 
    char resultado[100];                    // Se mantiene la declaración de resultado
    char slash = '/';
    char newPath[50];                       // Se crea una arreglo de caracteres para guardar el directorio a llegar
    newPath[0] = '\0';                      // Inicializa como cadena vacia
                                            // actualizar newPath al nombre correspondiente
    /*
    snprintf(newPath, sizeof(newPath), "%s%c", C, slash);
    printf("Después de concatenar: %s\n", newPath);
    */

    // Esto seria mejor separarlo en un codigo aparte para mayor legibilidad
    // Exactamente lo encargado de mover los archivos
    char PathSatured[100];
    char PathGray[100];
    char PathBinary[100];

    PathSatured[0] = '\0';
    PathGray[0] = '\0';
    PathBinary[0] = '\0';
    // Inicializar resultado como una cadena vacía
        resultado[0] = '\0';
    
    while (loop!=0)     //Esto me genera ruido porque de no encontrar mas simplemente termina la ejecucion
    {       

        char saturated[100] = "saturated";
        char grayScale[100] = "grayScale";
        char binarize[100] = "binarize";  

        snprintf(PathSatured, sizeof(PathSatured), "%s%c", C, slash);
        printf("Después de concatenar: %s\n", PathSatured);

        snprintf(PathGray, sizeof(PathGray), "%s%c", C, slash);
        printf("Después de concatenar: %s\n", PathGray);

        snprintf(PathBinary, sizeof(PathBinary), "%s%c", C, slash);
        printf("Después de concatenar: %s\n", PathBinary);


        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar prefijo (N) y símbolo _
        snprintf(resultado, sizeof(resultado), "%s%c", name1, signo);
        printf("Después de concatenar: %s\n", resultado);

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar el número de loop con resultado
        snprintf(resultado + strlen(resultado), sizeof(resultado) - strlen(resultado), "%d", loop); 

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar la extension del archivo
        snprintf(resultado + strlen(resultado), sizeof(resultado) - strlen(resultado), "%s", bmp);
        printf("Después de concatenar: %s\n", resultado);

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar variable saturated con loop y bmp
        snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);

        snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);
        printf("Después de concatenar: %s\n", saturated);

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar variable grayScale con loop y bmp
        snprintf(grayScale + strlen(grayScale), sizeof(grayScale) - strlen(grayScale), "%d", loop);
        
        snprintf(grayScale + strlen(grayScale), sizeof(grayScale)- strlen(saturated), "%s", bmp);
        printf("Después de concatenar: %s\n", grayScale);

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        // Concatenar variable binarize con loop y bmp
        snprintf(binarize + strlen(binarize), sizeof(binarize) - strlen(binarize), "%d", loop);

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        snprintf(binarize + strlen(binarize), sizeof(binarize) - strlen(binarize),"%s", bmp);
        printf("Después de concatenar: %s\n", binarize);
        
        char *name = resultado;
        /*char number[50];
        name= N;                        
        sprintf(number, "%d",loop);
        strcat(name, number);*/
        printf("Nombre = %s\n",name);       //Falta ver como agregar el "_"
        
        BMPImage *image;
        //name = "rb.bmp";              //Cambiar name para probar imagenes
        image = read_bmp(name);
        
        if(image == NULL){
            printf("No se pudo encontrar otra imagen o hubo un error en el proceso\n");   
            //Se podria modificar el read para que devuelva cosas distintas en funcion si no pudo abrir la imagen o
            //hubo un error con el formato de la imagen
            fclose(fileCSV);
            return 0;
        }

        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        BMPImage *new_image = saturate_bmp(image, p);
        write_bmp(saturated, new_image);

        snprintf(PathSatured + strlen(PathSatured), sizeof(PathSatured) - strlen(PathSatured),"%s", saturated);
        printf("Después de concatenar: %s\n", PathSatured);
        
        // Esta parte es para mover la saturacion al directorio creado
        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        if (rename(saturated, PathSatured) == 0) {
        printf("El archivo saturated se movió correctamente a %s.\n", PathSatured);
        } else {
        perror("Error al mover el archivo");
        return 1;
        }


        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        BMPImage *new_image_GS = grayScale_bmp(new_image);
        write_bmp(grayScale, new_image_GS);
        
        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        BMPImage *new_image_B = binarize_bmp(new_image_GS,u);
        write_bmp(binarize, new_image_B);

        //fileCSV = fopen(R, "w");
        if (nearly_black(new_image_B, v) == 1) {
            fprintf(fileCSV, "%s, 1\n", resultado);
        }
        else {
            fprintf(fileCSV, "%s, 0\n", resultado);
        }

        snprintf(PathGray + strlen(PathGray), sizeof(PathGray) - strlen(PathGray),"%s", grayScale);
        printf("Después de concatenar: %s\n", PathGray);

        // Esta parte es para mover la escala de grises al directorio creado
        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        if (rename(grayScale, PathGray) == 0) {
        printf("El archivo saturated se movió correctamente a %s.\n", PathGray);
        } else {
        perror("Error al mover el archivo");
        return 1;
        }
        
        snprintf(PathBinary + strlen(PathBinary), sizeof(PathBinary) - strlen(PathBinary),"%s", binarize);
        printf("Después de concatenar: %s\n", PathBinary);
        // Esta parte es para mover la binarizacion al directorio creado
        // *comentario de desarrollo* esta parte hay que separarla en caso de que se deseen usar menos filtros
        if (rename(binarize, PathBinary) == 0) {
        printf("El archivo saturated se movió correctamente a %s.\n", PathBinary);
        } else {
        perror("Error al mover el archivo");
        return 1;
        }
        
        
        free_bmp(image);
        free_bmp(new_image);
        free_bmp(new_image_GS);
        free_bmp(new_image_B);
        
        loop++;

        /*Despues de clasificacion
        fileCSV = fopen(R, "w");

        if nearly_black == 1
            fprintf(fileCSV, "Nombre Imagen, 1\n");
        else
            fprintf(fileCSV, "Nombre Imagen, 0\n");

        fclose(fileCSV);
        */
    }

    fclose(fileCSV);

    return 0;
}