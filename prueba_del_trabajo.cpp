/**/


#include <stdio.h>

typedef struct
{
	char fecha[19];
	char tipo[19];
	float datos[24];
}datos_2122;


int main()
{
	datos_2122 generacion[100];  
	FILE *plectura;
	int j = 0, i = 0, k = 0;
	char tamano;
	float numero;
	
	plectura = fopen("generacion_por_tecnologias_21_22_puntos.csv","r");
	
	if (plectura == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1; // Terminar el programa con un código de error
    }
    
	while (fscanf(plectura, "%c", &tamano) != EOF)
	{
		if (i >= 100) 
		{
            printf("Se ha alcanzado el límite máximo de líneas.\n");
            break;
        }
		if(tamano == '\n')
		{
			generacion[i].tipo[j] = '\0';
			i++;
			j = 0;	
		}
		else if(tamano == ',')
		{
			generacion[i].tipo[j] = '\0';
			j++;
		}
		else
		{
			generacion[i].tipo[j] = tamano;
			j++;
		}
		/*if(tamano > '0' && tamano <'9')
		{
			numero = tamano - '0';
		}*/
			    
		//printf("%c", tamano);
    } 
	
	


	fclose(plectura);
	
	for(k=4;k<i;k++)
	{
		printf("Linea %d: %s\n", k+1, generacion[k].tipo);
	}

	
	return 0;
}




