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
	printf("Numero de lineas= %i",n);
	rewind(input);
	filas=(lineas*)malloc(n*sizeof(lineas));
	
	for(i=0;i<n;i++)
	{
		fgets(filas[i].fila,sizeof(filas[i].fila),input);
		filas[i].fila[strlen(filas[i].fila)-1]=',';//Se añade un coma justo antes del \0
		filas[i].fila[strlen(filas[i].fila)]='\0';
	}//recoger TODAS las filas
	

	/*for(i=4;i<n;i++)
	{
		printf("%s\n",filas[i].fila);
	}*/
	
	//printf("\n%s", filas[6].fila);
	
	for(i=4;i<n;i++)
	{
		printf("%s %.2f\n",filas[i].fila,obtener_datos(filas[i].fila));
	} 

	
	
	fclose(input);
	

	
	return 0;
}

float obtener_datos(char *filas)
{
	char numdato[24];
	float dato[24];
	int k = 0, i = 0, j;
	
	while(k<23)
	{
		for(j=0; filas[i] != ',';j++,i++)
		{
			numdato[j]=filas[i];
		}
		numdato[j]='\0';
		printf("esta es el dato como cadena: %s\n",numdato);
		dato[k]=atof(numdato);
		printf ("esta es el dato como real: %f\n",dato[k]);
		i++;
		k++;
	}
	
	
	return dato[k];
}
