/**/


#include <stdio.h>


typedef struct
{
	char linea[400];
}lineas;

typedef struct
{
	char tipo[300];
}tipos;

typedef struct
{
	float num[];
}datos;

int main()
{
	lineas c[22];
	tipos t[22];
	datos n[24];
	int i = 0, j = 0;
	FILE *pf;
	pf = fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r");
	if (pf == NULL)
    {
        printf("Error al abrir el fichero.\n");
        return -1;
    }
	
	int contador = 0;

    while (fgets(c[i].linea, sizeof(c[i].linea), pf) != NULL) 
	{
        contador++;

        if (contador >= 5) 
		{
            //printf("%s\n", c[i].linea);
            fscanf(pf,"%[^,]",t[i].tipo);
            i++;
        }
    }
    
    for(i=0;i<17;i++)
    {
    	printf("%s\n", t[i].tipo);
	}

	printf("%s",c[6].linea);

    fclose(pf);
	
    
    
    

	
	return 0;
}


