/**/


#include <stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct
{
	char linea[400];
}lineas;

typedef struct
{
	char tipo[30];
}tipos;

typedef struct
{
	char num1[30],num2[30],num3[30],num4[30]
	    ,num5[30],num6[30],num7[30],num8[30]
		,num9[30],num10[30],num11[30],num12[30]
		,num13[30],num14[30],num15[30],num16[30]
		,num17[30],num18[30],num19[30],num20[30]
		,num21[30],num22[30],num23[30],num24[30];
    double numero[24];
}datos;

void lectura_datos();
float media();
float moda();
float mediana();
float maximo();
float minimo();
float varianza();
float desviacion_tipica();
float buscar_dato(int x, int j);

int main()
{
	lineas c[22];
	tipos t[22];
	datos n[22];
	int i = 0, j = 0, k = 0;
	FILE *pf, *pl;
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
            fscanf(pf,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
			          ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
					  ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",t[i].tipo,
			          n[i].num1,n[i].num2,n[i].num3,n[i].num4,n[i].num5,n[i].num6
					 ,n[i].num7,n[i].num8,n[i].num9,n[i].num10,n[i].num11,n[i].num12
					 ,n[i].num13,n[i].num14,n[i].num15,n[i].num16,n[i].num17,n[i].num18
					 ,n[i].num19,n[i].num20,n[i].num21,n[i].num22,n[i].num23,n[i].num24);
            
            i++;
        }
    }
    /*for(i=0;i<5;i++)
    {
    	printf("%s:%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"
		       ",%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"
			   ",%s,%s,%s\n", t[i].tipo,n[i].num1
			   ,n[i].num2,n[i].num3,n[i].num4,n[i].num5
			   ,n[i].num6,n[i].num7,n[i].num8,n[i].num9
			   ,n[i].num10,n[i].num11,n[i].num12,n[i].num13
			   ,n[i].num14,n[i].num15,n[i].num16,n[i].num17
			   ,n[i].num18,n[i].num19,n[i].num20,n[i].num21
			   ,n[i].num22,n[i].num23,n[i].num24);
	}*/
	for(i=0;i<=17;i++)
	{
		for(j=0;j<24;j++)
		{
			if(j == 0)
			{
				n[i].numero[j] = atof(n[i].num1);
			}
			else if(j == 1)
			{
				n[i].numero[j] = atof(n[i].num2);
			}
			else if(j == 2)
			{
				n[i].numero[j] = atof(n[i].num3);
			}
			else if(j == 3)
			{
				n[i].numero[j] = atof(n[i].num4);
			}
			else if(j == 4)
			{
				n[i].numero[j] = atof(n[i].num5);
			}
			else if(j == 5)
			{
				n[i].numero[j] = atof(n[i].num6);
			}
			else if(j == 6)
			{
				n[i].numero[j] = atof(n[i].num7);
			}
			else if(j == 7)
			{
				n[i].numero[j] = atof(n[i].num8);
			}
			else if(j == 8)
			{
				n[i].numero[j] = atof(n[i].num9);
			}
			else if(j == 9)
			{
				n[i].numero[j] = atof(n[i].num10);
			}
			else if(j == 10)
			{
				n[i].numero[j] = atof(n[i].num11);
			}
			else if(j == 11)
			{
				n[i].numero[j] = atof(n[i].num12);
			}
			else if(j == 12)
			{
				n[i].numero[j] = atof(n[i].num13);
			}
			else if(j == 13)
			{
				n[i].numero[j] = atof(n[i].num14);
			}
			else if(j == 14)
			{
				n[i].numero[j] = atof(n[i].num15);
			}
			else if(j == 15)
			{
				n[i].numero[j] = atof(n[i].num16);
			}
			else if(j == 16)
			{
				n[i].numero[j] = atof(n[i].num17);
			}
			else if(j == 17)
			{
				n[i].numero[j] = atof(n[i].num18);
			}
			else if(j == 18)
			{
				n[i].numero[j] = atof(n[i].num19);
			}
			else if(j == 19)
			{
				n[i].numero[j] = atof(n[i].num20);
			}
			else if(j == 20)
			{
				n[i].numero[j] = atof(n[i].num21);
			}
			else if(j == 21)
			{
				n[i].numero[j] = atof(n[i].num22);
			}
			else if(j == 22)
			{
				n[i].numero[j] = atof(n[i].num23);
			}
			else if(j == 23)
			{
				n[i].numero[j] = atof(n[i].num24);
			}
			
		}
		
	}

    fclose(pf);
	
	
	int tecla;
	int x;
	
    printf("--------------------------------------------------------MENU--------------------------------------------------------\n");
    printf("1) Buscador de datos.\n");
    printf("2) Calculos estadisticos.\n");
    printf("3) Salir\n");
    printf("A donde quiere acceder?\n");
    scanf("%i", &tecla);
    
    switch(tecla)
    {
    	case 1:
    		printf("A que tipo de generacion quiere acceder?\n");
            for(i=0;i<17;i++)
            {
    	        printf("%i) %s\n", i+1 ,t[i].tipo);
	        }
	        scanf("%i", &x);
	        printf("Sabiendo que los datos estan ordenados por meses a lo largo de 2 años(24 datos en total)\n");
			printf("Elija la posicion del valor deseado:\t");
			scanf("%i", &j);
    		buscar_dato(x,j);
			
    		break;
    	case 2:
    		printf("");
    		break;
    	case 3:
    		char respuesta[5];
		    printf("Estas seguro de que quieres salir del programa?(si/no)");
			scanf("%s", &respuesta);
			break;
	}
    
    
    
    
    

	
	return 0;
}

void lectura_datos()
{
	lineas c[22];
	tipos t[22];
	datos n[22];
	int i = 0, j = 0, k = 0;
	FILE *pf;
	pf = fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r");
	if (pf == NULL)
    {
        printf("Error al abrir el fichero.\n");
        return;
    }
	
	int contador = 0;

    while (fgets(c[i].linea, sizeof(c[i].linea), pf) != NULL) 
	{
        contador++;

        if (contador >= 5) 
		{
            //printf("%s\n", c[i].linea);
            fscanf(pf,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
			          ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
					  ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",t[i].tipo,
			          n[i].num1,n[i].num2,n[i].num3,n[i].num4,n[i].num5,n[i].num6
					 ,n[i].num7,n[i].num8,n[i].num9,n[i].num10,n[i].num11,n[i].num12
					 ,n[i].num13,n[i].num14,n[i].num15,n[i].num16,n[i].num17,n[i].num18
					 ,n[i].num19,n[i].num20,n[i].num21,n[i].num22,n[i].num23,n[i].num24);
            
            i++;
        }
    }
    /*for(i=0;i<5;i++)
    {
    	printf("%s:%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"
		       ",%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s"
			   ",%s,%s,%s\n", t[i].tipo,n[i].num1
			   ,n[i].num2,n[i].num3,n[i].num4,n[i].num5
			   ,n[i].num6,n[i].num7,n[i].num8,n[i].num9
			   ,n[i].num10,n[i].num11,n[i].num12,n[i].num13
			   ,n[i].num14,n[i].num15,n[i].num16,n[i].num17
			   ,n[i].num18,n[i].num19,n[i].num20,n[i].num21
			   ,n[i].num22,n[i].num23,n[i].num24);
	}*/
	for(i=0;i<=17;i++)
	{
		for(j=0;j<24;j++)
		{
			if(j == 0)
			{
				n[i].numero[j] = atof(n[i].num1);
			}
			else if(j == 1)
			{
				n[i].numero[j] = atof(n[i].num2);
			}
			else if(j == 2)
			{
				n[i].numero[j] = atof(n[i].num3);
			}
			else if(j == 3)
			{
				n[i].numero[j] = atof(n[i].num4);
			}
			else if(j == 4)
			{
				n[i].numero[j] = atof(n[i].num5);
			}
			else if(j == 5)
			{
				n[i].numero[j] = atof(n[i].num6);
			}
			else if(j == 6)
			{
				n[i].numero[j] = atof(n[i].num7);
			}
			else if(j == 7)
			{
				n[i].numero[j] = atof(n[i].num8);
			}
			else if(j == 8)
			{
				n[i].numero[j] = atof(n[i].num9);
			}
			else if(j == 9)
			{
				n[i].numero[j] = atof(n[i].num10);
			}
			else if(j == 10)
			{
				n[i].numero[j] = atof(n[i].num11);
			}
			else if(j == 11)
			{
				n[i].numero[j] = atof(n[i].num12);
			}
			else if(j == 12)
			{
				n[i].numero[j] = atof(n[i].num13);
			}
			else if(j == 13)
			{
				n[i].numero[j] = atof(n[i].num14);
			}
			else if(j == 14)
			{
				n[i].numero[j] = atof(n[i].num15);
			}
			else if(j == 15)
			{
				n[i].numero[j] = atof(n[i].num16);
			}
			else if(j == 16)
			{
				n[i].numero[j] = atof(n[i].num17);
			}
			else if(j == 17)
			{
				n[i].numero[j] = atof(n[i].num18);
			}
			else if(j == 18)
			{
				n[i].numero[j] = atof(n[i].num19);
			}
			else if(j == 19)
			{
				n[i].numero[j] = atof(n[i].num20);
			}
			else if(j == 20)
			{
				n[i].numero[j] = atof(n[i].num21);
			}
			else if(j == 21)
			{
				n[i].numero[j] = atof(n[i].num22);
			}
			else if(j == 22)
			{
				n[i].numero[j] = atof(n[i].num23);
			}
			else if(j == 23)
			{
				n[i].numero[j] = atof(n[i].num24);
			}
			
		}
		
	}
}

float buscar_dato(int x, int j)
{
	datos n[22];
	int i;
	for(i=0;i<=17;i++)
		{
			if(x == i)
			{
				printf("%.15lf GWh",n[i-1].numero[j-1]);
			}
		}
}
