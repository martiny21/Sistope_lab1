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
    char *C = NULL , *R = NULL, *N = NULL; //Los prametros -C y -R son obligatorios
    
    int loop = 1;   //Verdadero, es una bandera para continuar un ciclo
    int option;

    //Lectura de argumentos usando getopt()
    while((option = getopt(argc, argv, "N:f:p:u:v:C:R:l")) != -1) { //l simplemente es un parche para que pueda leer R
        switch (option)
        {
        case 'N':
            N = optarg; //-N: nombre del prefijo de las imágenes.
            break;
        case 'f':
            f = atoi(optarg); //-f: cantidad de filtros a aplicar.
            break;
        case 'p':
            p = atof(optarg); //-p: factor de saturación del filtro.
            break;
        case 'u':
            u = atof(optarg); //-u: UMBRAL para binarizar la imagen.
            break;
        case 'v':
            v = atof(optarg); //-v: UMBRAL para clasificación.
            break;
        case 'C':
            C = optarg; //-C: nombre de la carpeta resultante con las imágenes, con los filtros aplicados.
            break;
        case 'R':
            R = optarg; //-R: nombre del archivo CSV con las clasificaciones resultantes.
            break;
        }
    }
    //Verificar que f sea un valor valido
    if((f > 3) || f < 0){
        printf("Por favor ingrese un valor entero para f entre 1 y 3\n");
        return 0;
    }

    //Verificar que se entregan los argumentos olbigatorios
    if (R == NULL && C == NULL){
        printf("Falto el ingreso de parametros obligatorios, nombre de la carpeta resultante o nombre del archivo CSV\n");
        return 0;
    }

    //Verificar que se ingrese una factor de saturación valido
    if(p <= 0) {
        printf("Por favor ingrese un valor entero mayor que 0 para el factor de saturación (p)\n");
        return 0;
    }

    //Verificar que el umbral de binarización esté dentro de un rango valido
    if(u > 1 || u < 0) {
        printf("Por favor ingrese un valor entre 0 y 1 para el umbral de binarización (u)\n");
        return 0;
    }

    //Verificar que el umbral de clasificación esté dentro de un rango valido
    if(v >= 1 || v < 0) {
        printf("Por favor ingrese un valor entre 0 y 1 para el umbral de clasificación (v)\n");
        return 0;
    }

    if(N == NULL){
        printf("Por favor ingrese el prefijo de las imagenes a trabajar (N)\n");
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
    fileCSV = fopen(R, "w"); // Abre el archivo en modo escritura ("w"), se cierra al finalizar el programa

    if (fileCSV == NULL) {
        printf("Error al abrir el archivo.");
        return 0;
    }

    //Archivo CSV con 2 columnas
    fprintf(fileCSV, "Nombre Imagen,Clasificacion\n");

    //Variables para concatenacion de cadenas de caracteres
    char bmp[20] = ".bmp";
    char *name1;
    name1 = N;
    char signo = '_'; 
    char resultado[100];                    // Se mantiene la declaración de resultado
    char slash = '/';
    char newPath[50];                       // Se crea una arreglo de caracteres para guardar el directorio a llegar

    char PathSatured[100];
    char PathGray[100];
    char PathBinary[100];

    // Inicializar variables como una cadena vacía
    PathSatured[0] = '\0';
    PathGray[0] = '\0';
    PathBinary[0] = '\0';
    resultado[0] = '\0';
    newPath[0] = '\0';  

    while (loop!=0) 
    {   
        //Variables para concatenacion de cadenas de caracteres
        char saturated[100] = "saturated";
        char grayScale[100] = "grayScale";
        char binarize[100] = "binarize";
        
        // Concatenar prefijo (N) y símbolo _
        snprintf(resultado, sizeof(resultado), "%s%c", name1, signo);

        // Concatenar el número de loop con resultado
        snprintf(resultado + strlen(resultado), sizeof(resultado) - strlen(resultado), "%d", loop);

        // Concatenar la extension del archivo
        snprintf(resultado + strlen(resultado), sizeof(resultado) - strlen(resultado), "%s", bmp);

        // Lectura de archivo
        BMPImage *image;
        image = read_bmp(resultado);

        if(image == NULL){
            printf("No se pudo encontrar otra imagen o hubo un error en el proceso\n");   
            fclose(fileCSV);
            return 0;
        }

        switch (f)
        {
        case 1:

            snprintf(PathSatured, sizeof(PathSatured), "%s%c", C, slash);

            // Concatenar variable saturated con loop y bmp
            snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);
            snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);

            // Saturacion de la imagen
            BMPImage *new_image = saturate_bmp(image, p);
            write_bmp(saturated, new_image);

            snprintf(PathSatured + strlen(PathSatured), sizeof(PathSatured) - strlen(PathSatured),"%s", saturated);
            
            // Se mueve el archivo al directorio creado
            if (rename(saturated, PathSatured) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            //Clasificacion de imagen
            if (nearly_black(new_image, v) == 1) {
                fprintf(fileCSV, "%s,1\n", resultado);
            }
            else {
                fprintf(fileCSV, "%s,0\n", resultado);
            }

            free_bmp(new_image);

            break;

        case 2:

            // Concatenar variable saturated con loop y bmp
            snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);
            snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);

            // Concatenar "/" a los Path 
            snprintf(PathSatured, sizeof(PathSatured), "%s%c", C, slash);
            snprintf(PathGray, sizeof(PathGray), "%s%c", C, slash);

            // Concatenar variable grayScale con loop y bmp
            snprintf(grayScale + strlen(grayScale), sizeof(grayScale) - strlen(grayScale), "%d", loop);
            snprintf(grayScale + strlen(grayScale), sizeof(grayScale)- strlen(saturated), "%s", bmp);

            snprintf(PathSatured + strlen(PathSatured), sizeof(PathSatured) - strlen(PathSatured),"%s", saturated);

            // Saturacion de la imagen
            BMPImage *new_image2 = saturate_bmp(image, p);
            write_bmp(saturated, new_image2);

            // Se mueve el archivo al directorio creado
            if (rename(saturated, PathSatured) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            BMPImage *new_image_GS = grayScale_bmp(new_image2);
            write_bmp(grayScale, new_image_GS);

            snprintf(PathGray + strlen(PathGray), sizeof(PathGray) - strlen(PathGray),"%s", grayScale);

            // Esta parte es para mover la escala de grises al directorio creado
            if (rename(grayScale, PathGray) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            // Clasificacion de imagen
            if (nearly_black(new_image_GS, v) == 1) {
                fprintf(fileCSV, "%s,1\n", resultado);
            }
            else {
                fprintf(fileCSV, "%s,0\n", resultado);
            }

            free_bmp(new_image2);
            free_bmp(new_image_GS);

            break;

        case 3:

            snprintf(PathSatured, sizeof(PathSatured), "%s%c", C, slash);
            snprintf(PathGray, sizeof(PathGray), "%s%c", C, slash);
            snprintf(PathBinary, sizeof(PathBinary), "%s%c", C, slash);

            // Concatenar variable saturated con loop y bmp
            snprintf(saturated + strlen(saturated), sizeof(saturated) - strlen(saturated), "%d", loop);
            snprintf(saturated + strlen(saturated), sizeof(saturated)- strlen(saturated), "%s", bmp);

            snprintf(PathSatured + strlen(PathSatured), sizeof(PathSatured) - strlen(PathSatured),"%s", saturated);

            // Concatenar variable grayScale con loop y bmp
            snprintf(grayScale + strlen(grayScale), sizeof(grayScale) - strlen(grayScale), "%d", loop);
            snprintf(grayScale + strlen(grayScale), sizeof(grayScale)- strlen(saturated), "%s", bmp);

            // Concatenar variable binarize con loop y bmp
            snprintf(binarize + strlen(binarize), sizeof(binarize) - strlen(binarize), "%d", loop);
            snprintf(binarize + strlen(binarize), sizeof(binarize) - strlen(binarize),"%s", bmp);

            // Saturacion de la imagen
            BMPImage *new_image3 = saturate_bmp(image, p);
            write_bmp(saturated, new_image3);

            // Se mueve el archivo al directorio creado
            if (rename(saturated, PathSatured) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            BMPImage *new_image_GS3 = grayScale_bmp(new_image3);
            write_bmp(grayScale, new_image_GS3);
            
            snprintf(PathGray + strlen(PathGray), sizeof(PathGray) - strlen(PathGray),"%s", grayScale);

            // Esta parte es para mover la escala de grises al directorio creado
            if (rename(grayScale, PathGray) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            BMPImage *new_image_B = binarize_bmp(new_image_GS3,u);
            write_bmp(binarize, new_image_B);

            snprintf(PathBinary + strlen(PathBinary), sizeof(PathBinary) - strlen(PathBinary),"%s", binarize);

            // Esta parte es para mover la binarizacion al directorio creado
            if (rename(binarize, PathBinary) != 0) {
                perror("Error al mover el archivo");
                return 1;
            }

            // Clasificacion de imagen
            if (nearly_black(new_image_B, v) == 1) {
                fprintf(fileCSV, "%s,1\n", resultado);
            }
            else {
                fprintf(fileCSV, "%s,0\n", resultado);
            }
        
            free_bmp(new_image3);
            free_bmp(new_image_GS3);
            free_bmp(new_image_B);
            break;
        
        default:
            break;
        }
        
        free_bmp(image);
        loop++;
    }

    // Cerrar archivo CSV
    fclose(fileCSV);
    return 0;
}