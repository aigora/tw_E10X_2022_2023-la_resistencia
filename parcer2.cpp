#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

typedef struct{

	char fila[1000];

}lineas;

float obtener_datos(char *filas);

int main()
{
	int n = 0,i = 0;
	char c;
	lineas *filas;
	FILE *input, *output;
	input = fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r");
	output= fopen("salida.csv","w");
	if(input==NULL)printf("problema al abrir el fichero input");
    if(output==NULL)printf("Problema al abrir el fichero output");
	while(!feof(input))
	{
		c=fgetc(input);
		if(c=='\n') n++;
	}//contar lineas del archivo
	printf("Numero de lineas= %i",n);
	rewind(input);
	filas=(lineas*)malloc(n*sizeof(lineas));
	
	for(i=0;i<n+1;i++)
	{
		fgets(filas[i].fila,sizeof(filas[i].fila),input);
		filas[i].fila[strlen(filas[i].fila)-1]=',';//Se añade un coma justo antes del \0
		filas[i].fila[strlen(filas[i].fila)]='\0';
	}//recoger TODAS las filas
	
	
	for(i=3;i<(n+1);i++)
	{
		printf("\n%.2f", obtener_datos(filas[i].fila));
	} 

	
	fclose(input);
	
	return 0;
}

float obtener_datos(char *filas)
{
	char numdato[25];
	float dato[25];
	int k = 0, i = 0, j = 0;
	
	while(k<25)
	{
		for(j=0; filas[i] != ',';j++,i++)
		{
			numdato[j]=filas[i];
		}
		numdato[j] = '\0';
		dato[k]=atof(numdato);
		printf ("\ndato %i %f\t", k, dato[k]);
		i++;
		k++;
	}
	
	
	return dato[k - 1];
}
