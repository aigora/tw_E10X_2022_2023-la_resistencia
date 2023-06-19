/**/


#include <stdio.h>


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
	char num1[30],num2[30],num3[30],num4[30],num5[30],num6[30],num7[30],num8[30],num9[30],num10[30],num11[30],num12[30],num13[30],num14[30],num15[30],num16[30],num17[30],num18[30],num19[30],num20[30],num21[30],num22[30],num23[30],num24[30];
}datos;

int main()
{
	lineas c[22];
	tipos t[22];
	datos n[22];
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
            fscanf(pf,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",t[i].tipo,
			       n[i].num1,n[i].num2,n[i].num3,n[i].num4,n[i].num5,n[i].num6,n[i].num7,n[i].num8,n[i].num9,n[i].num10,n[i].num11,n[i].num12,n[i].num13,n[i].num14,n[i].num15,n[i].num16,n[i].num17,n[i].num18,n[i].num19,n[i].num20,n[i].num21,n[i].num22,n[i].num23,n[i].num24);
            
            i++;
        }
    }
    /*for(i=0;i<5;i++)
    {
    	printf("%s:%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", t[i].tipo,n[i].num1,n[i].num2,n[i].num3,n[i].num4,n[i].num5,n[i].num6,n[i].num7,n[i].num8,n[i].num9,n[i].num10,n[i].num11,n[i].num12,n[i].num13,n[i].num14,n[i].num15,n[i].num16,n[i].num17,n[i].num18,n[i].num19,n[i].num20,n[i].num21,n[i].num22,n[i].num23,n[i].num24);
	}*/
	printf("%s",n[1].num7);

	//printf("%s",c[6].linea);

    fclose(pf);
	
    
    
    

	
	return 0;
}


