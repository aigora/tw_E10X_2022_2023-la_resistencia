/**/


#include <stdio.h>
#define N 10000

typedef struct
{
	int fecha[19];
	char tipo[19];
	float datos[24];
}datos_2122;


int main()
{
	datos_2122 generacion;  
	FILE *plectura, *pescritura;
	int j = 0;
	char tamano;
	float numero;
	
	plectura = fopen("C:/Users/Adrian/Downloads/generacion_por_tecnologias_21_22.csv","r");
	
	while (fscanf(plectura, "%c", &tamano) != EOF)
	{
		if(tamano =='\n')
		{
			++j;	
		}	    
		//printf("%c", tamano);
    }  
	
	while (fscanf(plectura, "%[^,]", &numero) != EOF)
	{
		printf("%f\n", numero);	    
    }
    
    if(j=4)
    {
    	fscanf(plectura,"%[^,]", &generacion.fecha);
    	printf("%i\t", generacion.fecha);
	}
	


	//printf("Hay %i caracteres\n", i);
	printf("Hay %i lineas\n", j);

	fclose(plectura);
	
	return 0;
}




