//La idea es guardar cada una de las lineas en una cadena de caracteres y trabajar con solo las cadenas

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char lineas[500];
}lin;

typedef struct
{
	char tipo[35];
	double dato[24];
}datos;

struct extra
{
	char cardato[30];//El numero de caracteres que permite la cadena cardato
}extradatos[408];//La dimension es 408 numero que corresponde al numero total de datos que hay, obtenido multiplicando 17*24

//void DATOS(char *,float *);


int main()
{
	//Primero hay que contar la cantidad de lineas que tenemos.
	//La cantidad de lineas "n" sera la dimension de nuestro vector de estructuras "lin" cada elemento de este vector tendra una linea.
	lin *numlineas; //El puntero de estructuras que cambiaremos a vector con dimension n.
	FILE *fich;
	int n=0,i=0,j=0,k=0,numcomas=0,q=0,d=0,l=0,m=0;
	char c;
	datos numdatos[17];
	if((fich=fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r"))==NULL)printf("Problema al abrir fichero"); //Apertura



	while(!feof(fich))
	{
		if(fgetc(fich)=='\n') n++;
	}
	//printf("El numero total de lineas en el archivo es %i",n);
	//Nos da el valor n igual a 22.
	numlineas=(lin*)malloc(n*sizeof(lin));//El puntero lo hemos cambiado a un vector con dimension "n".
	rewind(fich);
	//Ahora copiamos en cada elemento de numlineas una cadena(linea).
	for(i=0;i<n;i++)
	{
		fgets(numlineas[i].lineas,sizeof(numlineas[i].lineas),fich);//Esto copia cada fila en cada elemento
		//Lo que pasa es que el fgets tambien copia el '\n' asi que hay que cambiarlo por un , para cerrar la linea
		numlineas[i].lineas[strlen(numlineas[i].lineas)-1]=',';
		//Hay que cerrar la cadena obviamente se añade un '\0'
		numlineas[i].lineas[strlen(numlineas[i].lineas)]='\0';
	}
	fclose(fich);//Cerramos fichero ya que ya no vamos a hacer nada con él
	
	//Se ve si hemos copiado bien el archivo entero
	/*for(i=0;i<n;i++)
	{
		printf("%s",numlineas[i].lineas);
	}*/
	
	//Pero solo nos interesa desde la linea que empiezan los tipos de datos(linea 6)
	/*for(i=6;i<n;i++)
	{
		printf("\n%s",numlineas[i].lineas);
	}*/	


	/*Lo siguente que tenemos que hacer es ordenar los nombres de los tipos en la segunda estructura 
	y cambiar los numeros de caracteres a floats(numeros reales)*/
	
	
	//Para ello encontramos la coma en cada cadena
	//Al mismo tiempo lo copiamos
	for(i=5,k=0;i<n;i++,k++)
	{
		for(j=0,numcomas=0;numcomas<1;j++)
		{
			if(numlineas[i].lineas[j]==',')
			{
				numcomas++;
				//printf("\nEn la linea %i la primera coma se encuentra en la posicion %i",i,j);
				//Ahora copiamos en la segunda estructura el nombre del tipo correspondiente
				memcpy(numdatos[k].tipo,numlineas[i].lineas,j*sizeof(char));
				q=j;
				for(m=0;m<24;m++)
				{
					q++;
					//printf("Valor de q= %i",q);
					//printf("\t%c\t",numlineas[5].lineas[11]);
					d=0;
					while(numlineas[i].lineas[q]!=',')//***Aqui es donde lo copiamos***//
					{
						extradatos[l].cardato[d]=numlineas[i].lineas[q];/*Se copia cada numero que esta entre comas
																		desde el primer coma hasta el último*/
						d++;											//La d sirve para la posicion en la cadena en la que se copia el numero
						q++;											//La posicion de la coma está indicada por la q esta sigue la cadena copiada
						//printf("\t%s\t",extradatos[l].cardato);
					}
					l++;			
				}
			}
		}
	}

	//Tranformamos los datos de caracteres a floats(numeros reales aptos para hacer calculos)
	k=0;
	for(i=0;i<17;i++)
	{
		for(j=0;j<24;j++)
		{
			numdatos[i].dato[j]=atof(extradatos[k].cardato);
			k++;
		}
	}

	//Comprobacion
	for(i=0;i<17;i++)
	{
		for(j=0;j<24;j++)
		{
			printf("El dato %i del tipo %i en numeros reales es %f",j+1,i+1,numdatos[i].dato[j]);
    	}
	}



}




