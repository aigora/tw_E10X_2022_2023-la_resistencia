#include <stdio.h>

int main() {
    FILE *archivo;
    char caracter;
    int contador = 0;
    int linea_inicio= 6;

    archivo = fopen("generacion_por_tecnologias_21_22_puntos_simplificado (1).csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Leemos las lineas caracter a caracter
     while ((caracter = getc(archivo)) != EOF) {
        if (caracter == '\n') {
            contador++;
        }
        if (contador >= linea_inicio) {
            printf("%c", caracter);
        }
    }

    fclose(archivo);

    return 0;
}
