//Creacón del parser(rocogida de datos del fichero 2021-2022)
#include<stdio.h>
#include<stdlib.h>


typedef struct
{
	char nombre[20]; //nombre de generacion
	float datos[24];//para acumular los datos de cada mes
}datos2122;

void extraerdatos(FILE *,datos2122 []);

int main()
{
	datos2122 generacion[18];//vector de estructuras de cada generacion electrica
	FILE *fich2122;
	extraerdatos(fich2122,generacion);
}
void extraerdatos(FILE *fich2122,datos2122 generacion[])
{
	int i,j;
	fich2122=fopen("generacion_por_tecnologias_21_22.csv","r");
	if((fich2122)==NULL)
	{
		printf("Problema al abrir fichero de la generacion de 2021-2022");
	}
	else printf("Apertura exitosa\n");//Para probar si el fichero se abre extitosamente
	
	fseek(fich2122,0,SEEK_END);
	int tamano=ftell(fich2122);
	printf("tamano %i",tamano);
	char v1[tamano];
	rewind(fich2122);
	fread(v1,1,tamano,fich2122);
	for(i=0;i<tamano;i++)
	{
		printf("%c",v1[i]);
	}
	/*for(i=0;i<19;i++)
	{
		for(j=0;j<25;j++)
		{
			fflush(stdin);
			while
		}
	}*/
	
}


















