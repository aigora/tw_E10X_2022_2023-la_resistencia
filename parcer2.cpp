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
	int n,i,k,j = 0;
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
		filas[i].fila[strlen(filas[i].fila)-1]=',';
		filas[i].fila[strlen(filas[i].fila)]='\0';
	}//recoger TODAS las filas
	
	/*for(i=4;i<n;i++)
	{
		printf("%s\n",filas[i].fila);
	}*/
	for(i=8;i<n;i++)
	{
		printf("%s %.2f\n",filas[i].fila,obtener_datos(filas[i].fila));
	} 

	
	fclose(input);
	
	
	return 0;
}

float obtener_datos(char *filas)
{
	char numdato[25];
	float dato[25];
	float datofinal, suma;
	int k = 0, i, j;
	
	while(k<24)
	{
		for(j=0; filas[i] != ',';j++,i++)
		{
			numdato[j]=filas[i];
		}
		numdato[j]='\0';
		printf("esta es la nota como cadena: %s\n",numdato);
		dato[k]=atof(numdato);
		printf ("esta es la nota como real: %f\n",dato[k]);
		i++;
		k++;
	}
	for(k=0,suma=0;k<24;k++)
	{
		suma += dato[k];
	}
	
	datofinal = suma/3.;
	
	return datofinal;
}
