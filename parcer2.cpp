#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct{
	char fila[10000];
}lineas;

int main()
{
	int n,i;
	char c;
	lineas *filas;
	FILE *input, *output;
	input = fopen("generacion_por_tecnologias_21_22_puntos.csv","r");
	output= fopen("generacion_por_tecnologias_21_22_puntos.csv","a");
	if(input==NULL)printf("problema al abrir el fichero input");
	if(output==NULL)printf("Problema al abrir el fichero output");
	while(!feof(input))
	{
		c=fgetc(input);
		if(c=='\n') n++;
	}//contar lineas del archivo
	//printf("Numero de lineas= %i",n);
	rewind(input);
	filas=(lineas*)malloc(n*sizeof(lineas));
	
	for(i=0;i<n;i++)
	{
		fgets(filas[i].fila,sizeof(filas[i].fila),input);
		filas[i].fila[strlen(filas[i].fila)-1]=',';//Se añade un coma justo antes del \0
		filas[i].fila[strlen(filas[i].fila)]='\0';
	}//recoger TODAS las filas
	
	for(i=0;i<n;i++)
	{
		printf("%s\n",filas[i].fila);
	}
	fclose(input);
	
}
