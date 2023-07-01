#include <stdio.h>
#include <string.h>

//Calcular la cifra de datos por Cada Tecnologia  y compararlos con los mismos de la fila, y cada uno con el otro del siguiente año
int main ()
{

    FILE *pf;
    char c;
  // Abre ficheros:
  // El origen en modo lectura:

  // Contadores:

pf= fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv", "r");
  if (pf == NULL) {
    printf("Error al abrir el archivo origen.\n");
    return -1;
  }
  else

  {

// Leemos carácter a carácter hasta encontrar EOF
  while (fscanf(pf, "%c", &c) != EOF)
{

  int contador=0;

  if(c == '\n')
  {
    contador ++;
  }
  if(contador == 5)
  {
    break;
  }

  scanf("%i",&contador);
  printf("Estas en la linea:%c",c);

    // Comenzamos en la linea 6
 /*  iContador=0;
  char texto[10.000];
  int i;
  printf("Los caracteres son:\n");
  for(i = 6; texto[i] != '\0'; i++)
  {
    printf("%c \t", texto[i]);

    if(texto[i]== ',')
    {
        printf("%s",texto[i+1]);
    }
      int icontador=0
  }*/
}



