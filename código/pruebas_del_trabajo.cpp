//La idea es guardar cada una de las lineas en una cadena de caracteres y trabajar con solo las cadenas

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	char lineas[500];
}lin;

struct datos
{
	char tipo[35];
	double dato[24];
}numdatos[17];

struct extra
{
	char cardato[30];//El numero de caracteres que permite la cadena cardato
}extradatos[408];//La dimension es 408 numero que corresponde al numero total de datos que hay, obtenido multiplicando 17*24

void RECOGER(FILE *);
void ESCRIBIR(FILE *);
int MOSTRARTIPOS(int);
int CALCULOESTAD();
int BUSCARDATO(int,int);
float MENU_PRINCIPAL();
int MENU_DATOS();
int MENU_CALCULOS();
float media(int,int);
float varianza(int,int);
float POT(float,int);
float mediana(int,int);
float max(int,int);
float min(int,int);
int MENU_ORDENAR();
void ordenar(int, int,int);
int verificar_char(char c, int *resultado);
int pregunta_calculos(int);

int main()
{
	FILE *fich;
	FILE *fich2;
	if((fich=fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r"))==NULL)printf("Problema al abrir primer fichero"); //Apertura
	RECOGER(fich);//Hacemos la llamada a la funcion que nos almacena todos los datos del archivo en la memoria del ordenador
	fclose(fich);//Se cierra el fichero ya que no necesitamos trabajar mas con el, tenemos ya los datos en nuestra memoria
	if((fich2=fopen("Calculos_estadisticos.csv","w"))==NULL)printf("Problema al abrir segundo fichero"); //Apertura del fichero para escribir
	ESCRIBIR(fich2);
	fclose(fich2);
	//EL menu con sus llamadas a funciones que har?n lo pedido
	MENU_PRINCIPAL();
}

void RECOGER(FILE *fich)//funcion que recoge los datos del archivo y los mete en la memoria del programa
{
	//Primero hay que contar la cantidad de lineas que tenemos.
	//La cantidad de lineas "n" sera la dimension de nuestro vector de estructuras "lin" cada elemento de este vector tendra una linea.
	lin *numlineas; //El puntero de estructuras que cambiaremos a vector con dimension n.
	int n=0,i=0,j=0,k=0,numcomas=0,q=0,d=0,l=0,m=0;
	
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
		//Hay que cerrar la cadena obviamente se a?ade un '\0'
		numlineas[i].lineas[strlen(numlineas[i].lineas)]='\0';
	}
	fclose(fich);//Cerramos fichero ya que ya no vamos a hacer nada con ?l
	
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
																		desde el primer coma hasta el ?ltimo*/
						d++;											//La d sirve para la posicion en la cadena en la que se copia el numero
						q++;											//La posicion de la coma est? indicada por la q esta sigue la cadena copiada
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
	
	/*for(i=0;i<17;i++)
	{
		for(j=0;j<24;j++)
		{
			printf("El dato %i del tipo %i en numeros reales es %f",j+1,i+1,numdatos[i].dato[j]);
    	}
	}*/
}

void ESCRIBIR(FILE *fich)
{
	int i=1,j=0,k=0;
	fprintf(fich,"Generación,Media anio 1,Media anio 2,");
	fprintf(fich,"Mediana anio 1,Mediana anio 2,");
	fprintf(fich,"Varianza anio 1,Varianza anio 2,");
	fprintf(fich,"Maximo Minimo anio 1,Maximo Minimo anio 2,");
	fputc('\n',fich);
	for(j=0,k=0;j<17;j++,k++)
	{
		fprintf(fich,"%s,",numdatos[k].tipo);
		fprintf(fich,"%f,",media(i,j));
		i++;
		fprintf(fich,"%f,",media(i,j));
		i--;
		fprintf(fich,"%f,",mediana(i,j));
		i++;
		fprintf(fich,"%f,",mediana(i,j));
		i--;
		fprintf(fich,"%f,",varianza(i,j));
		i++;
		fprintf(fich,"%f,",varianza(i,j));
		i--;
		fprintf(fich,"%f   %f,",max(i,j),min(i,j));
		i++;
		fprintf(fich,"%f   %f",max(i,j),min(i,j));
		i--;
		fputc('\n',fich);
 	}
}

float RECOGER2(int estad,int anio,int gener)
{
	int n=0,i=0,j=0,k=0,f=0;
	char c, rescarac[50];
	lin *recoger=NULL;
	FILE *fich=NULL;
	if((fich=fopen("Calculos_estadisticos.csv","r"))==NULL)printf("Problema al abrir el fichero 3 para recoger el fichero de calculos\n");
	//Se sabe que tenemos 17 generaciones
	//En nuestro archivo que almacena los calculos hay 18 filas
	recoger=(lin*)malloc(18*sizeof(lin));//El puntero lo hemos cambiado a un vector con dimension "18".
	rewind(fich);
	for(i=0;i<18;i++)
	{
		fgets(recoger[i].lineas,sizeof(recoger[i].lineas),fich);//Esto copia cada fila en cada elemento
		//Se aniade una coma al final para cerrar la columna
		recoger[i].lineas[strlen(recoger[i].lineas)-1]=',';
		//Hay que cerrar la cadena obviamente se a?ade un '\0'
		recoger[i].lineas[strlen(recoger[i].lineas)]='\0';
	}
	printf("%s",recoger[gener].lineas);
	fclose(fich);
	if(estad==1)
	{
		i=1;
		f=2;
		printf("\nLa media deseada es ");	
	}
	else if(estad==2)
	{
		i=3;
		f=4;
		printf("\nLa mediana deseada es ");
	}
	else if(estad==3)
	{
		i=5;
		f=6;
		printf("\nLa varianza deseada es ");
	}
	else if(estad==4)
	{
		i=7;
		f=8;
		printf("\nEl maximo y el minimo deseados son ");
	}
	if(anio==2)
		{
			i++;
			f++;
		}
	while(n!=i)
		{	
			if(recoger[gener].lineas[k]==',')
				{
					n++;
				}
			k++;
		}
	n=0;
	while(n!=f)
		{
			if(recoger[gener].lineas[j]==',')
				{
					n++;
				}
			j++;
		}
	for(i=k,n=0;i<j;i++,n++)
		{
			rescarac[n]=recoger[gener].lineas[i];
		}
	rescarac[n-1]='\0';
	printf("%s",rescarac);
}

float MENU_PRINCIPAL()
{
	int i=0,j=0,x=0,e=0,y=0, z, h, resultado;
	char menu = 4;
	do
	{
		if(menu = 4)
		{
			printf("---------------------------------------------------MENU PRINCIPAL---------------------------------------------------\n");
            printf("1) Buscador de datos.\n");
            printf("2) Calculos estadisticos.\n");
            printf("3) Ordenacion de datos\n");
            printf("4) Salir\n");
            printf("A donde quiere acceder? ");
            fflush(stdin);
            scanf("%c", &menu);
            z = verificar_char(menu, &resultado);
		}
		
		if(z >= 1 && z <= 4)
		{
			switch(z)
        	{
    	    	case 1:
    	    		MENU_DATOS();
					return 0;			
                break;
    	    	case 2:
    	    		MENU_CALCULOS();
    	    		return 0;
    		    break;
    			case 3:
    				MENU_ORDENAR();
    				return 0;
			    break;    
    			case 4:
    				printf("Hasta pronto!");
    				return 0;
			    break; 
			}
		}
		else
		{
			printf("\nOpcion incorrecta, vuelva a intentarlo porfavor\n");
			MENU_PRINCIPAL();
			return 0;
		}
	}
	while(menu != 4);
	
	return 0;
}

int MENU_DATOS()
{
	int i=0,j=0, x, resultado;
	char menu;
	printf("-------------------------------------------MENU PRINCIPAL>>BUSCADOR DATO--------------------------------------------");
	printf("\nTipos de generaciones a elegir\n");
	MOSTRARTIPOS(0);
	printf("\n---> Para volver la menu principal pulsa 0 <---\n");
    printf("\nA que tipo de generacion quiere acceder? ");
    fflush(stdin);
    scanf("%c", &menu);
    x = verificar_char(menu, &resultado);
    if(x > 0 && x < 18)
    {
    	printf("Sabiendo que los datos estan ordenados por meses a lo largo de 2 anios(24 datos en total)\n");
	    printf("Elija la posicion del valor deseado: ");
	    scanf("%i", &j);
	    if(j > 0 && j < 25)
	    {
	    	BUSCARDATO(x,j);
	    	MENU_DATOS();
	    	return 0;
		}
		else
		{
			printf("\nBoton incorrecto\n");
			printf("Vuelva a intentarlo\n");
			MENU_DATOS();
			return 0;
		}
	}
	else if(x == 0)
	{
		MENU_PRINCIPAL();
		return 0;
	}
	else
	{
		printf("\nBoton incorrecto\n");
		printf("Vuelva a intentarlo\n");
		MENU_DATOS();
		return 0;
	}
}

int MENU_CALCULOS()
{
	int i=0,j=0,x=0,e=0,y=0, z, resultado;
	char menu;
	float M,m;
	printf("\n----------------------------------------------MENU PRINCIPAL>>CALCULOS----------------------------------------------\n");
    x=CALCULOESTAD();
    fflush(stdin);
    scanf("%c", &menu);
    z = verificar_char(menu, &resultado);
	if(z==1)
	{
		pregunta_calculos(1);
	}
	else if(z==2)
	{
		pregunta_calculos(2);	
	}
	else if(z==3)
	{
		pregunta_calculos(3);	
	}
	else if(z==4)
	{
		pregunta_calculos(4);
	}
	else if(z == 0)
	{
		MENU_PRINCIPAL();
		return 0;
	}
	else
	{
		printf("Boton incorrecto\n");
		printf("Vuelva a intentarlo\n");
		MENU_CALCULOS();
		return 0;
	}
}

int MENU_ORDENAR()
{
	int i=0,j=0, x, resultado;
	char menu;
	printf("----------------------------------------------MENU PRINCIPAL>>ORDENAR-----------------------------------------------");
	printf("\nTipos de generacion a acceder:\n");
    MOSTRARTIPOS(0);
    printf("\n---> Para volver la menu principal pulsa 0 <---\n");
    printf("\nQue generacion desea? ");
    fflush(stdin);
    scanf("%c", &menu);
    x = verificar_char(menu, &resultado);
    if(x > 0 && x < 18)
    {
    		printf("Que anio le interesa? 2021(1) o 2022(2): ");
    		scanf("%i",&i);
    		if(i == 1 || i == 2)
    		{
    				printf("Como desea ordenar la generacion? Mayor a menor (1) o Menor a mayor(2)?: ");
    	    		scanf("%i",&j);
    	    		if(j == 1 || j == 2)
    	    		{
    		    			ordenar(x,j,i);
    		    			MENU_ORDENAR();
    		    			return 0;
					}
		    		else
		    		{
			   				printf("\nOpcion incorrecta\n");
			    			printf("Vuelva a intentarlo\n");
			    			MENU_ORDENAR();
			    			return 0;
					}   
			}
			else
			{
					printf("\nOpcion incorrecta\n");
					MENU_ORDENAR();
					return 0;
			}
	}
	else if(x == 0)
	{
			MENU_PRINCIPAL();
			return 0;
	}
    else
	{
		printf("\nOpcion incorrecta\n");
		MENU_ORDENAR();
		return 0;
	}	
}

int BUSCARDATO(int tipo, int numdato)//Funcion que busca el dato deseado
{
	int i;
	for(i=0;i<=17;i++)
			{
				if(i == tipo)
				{
					printf("\tEl dato deseado es %.15lf GWh\n",numdatos[i-1].dato[numdato-1]);
				}
			}
		return 1;
}

float media(int r,int y)//Funcion que calcula la media de lo deseado
{
	int i=0;
	float media=0;
	if(r==1)
	{
			for(i=0;i<12;i++)
			{
				media+=numdatos[y].dato[i];
				//printf("%f\t",media);
			}	
	}
	else if(r==2)
	{
		for(i=12;i<24;i++)
			{
				media+=numdatos[y].dato[i];
				//printf("%f\t",media);
			}
	}
	return media/12;
}

float mediana(int r,int x)//Funcion que calcula la mediana
{
	float mediana;
	if(r == 1)
	{
		mediana=numdatos[x].dato[5]+numdatos[x].dato[6];
		return mediana/2;
	}
	else if(r == 2)
	{
		mediana=numdatos[x].dato[17]+numdatos[x].dato[18];
		return mediana/2;
	}

		//printf("De que tipo de generacion quiere calcular la mediana?:\n");
		//MOSTRARTIPOS(0);
		//printf("\n---> Para volver la menu de calculos estadisticos pulsa 0 <---\n");
		//scanf("%i",&x);	
	/*if(x>=1 && x<=17)
	{
			    if(r == 1)
				{
					mediana=numdatos[x-1].dato[5]+numdatos[x-1].dato[6];
					return mediana/2;
				}
				else if(r == 2)
				{
					mediana=numdatos[x-1].dato[17]+numdatos[x-1].dato[18];
					return mediana/2;
				}
	}
	else if(x==0)
	{
		MENU_CALCULOS();
		return 0;
	}
	else
	{
		while(x<1 || x>17)
		{
			printf("Boton incorrecto\n");
			printf("Vuelve a pulsar\n");
			scanf("%i",&x);
		}
		 if(r == 1)
		{
			mediana=numdatos[x-1].dato[5]+numdatos[x-1].dato[6];
			return mediana/2;
		}
		else if(r == 2)
		{
			mediana=numdatos[x-1].dato[17]+numdatos[x-1].dato[18];
			return mediana/2;
		}
	}*/	

}

float varianza(int r,int x)//Funcion que calcula la varianza de lo deseado
{
	int i=0;
	float m;
	float varianza=0;
	if(r==1)
	{
			m=media(1,x);
			for(i=0;i<12;i++)
			{
					varianza+=POT((numdatos[x].dato[i]-m),2);
			}
			return varianza/12;
	}
	else if(r==2)
	{
			m=media(2,x);
			for(i=0;i<12;i++)
			{
					varianza+=POT((numdatos[x].dato[i]-m),2);
			}
			return varianza/12;
	}
	/*printf("De que tipo de generacion quiere calcular la varianza?:\n");
	MOSTRARTIPOS(0);
	printf("\n---> Para volver la menu de calculos estadisticos pulsa 0 <---\n");
	scanf("%i",&x);
	if(x == 0)
	{
		MENU_CALCULOS();
		return 0;
	}
	else if(x>=1 && x<=17)
	{
		if(r==1)
		{
			m=media(1,x);
			for(i=0;i<12;i++)
			{
				varianza+=POT((numdatos[x-1].dato[i]-m),2);
			}
		}
		else if(r==2)
		{
			m=media(1,x);
			for(i=12;i<24;i++)
			{
				varianza+=POT((numdatos[x-1].dato[i]-m),2);
			}
		}
	return varianza/12;	
	}
	else
	{
		printf("Boton incorrecto, vuelve a intentarlo\n");
		MENU_CALCULOS();
		return 0;
	}*/
}

float max(int r,int x)//Funcion que calcula el maximo
{
	int i,j;
	float MAX[24],aux=0;
	//printf("De que tipo de generacion quiere calcular el maximo?:\n");
	//MOSTRARTIPOS(0);
	//scanf("%i",&x);
	
	if(r==1)
	{
		for(i=0;i<12;i++)
		{
			MAX[i]=numdatos[x].dato[i];//Lo copiamos en un vector para facilitar el trabajo y no tener que pensar en estructuras
		}
		for(i=0;i<12;i++)//Vamos a organizar el vector tal que el maximo sea el primer elemento
		{				//El primer for es para hacer la comparacion entre numeros 12 veces
			for(j=0;j<11;j++)//Este for compara cada elemento con su siguiente
			{	
				if(MAX[j]<MAX[j+1])//Si el anterior es menor que su siguiente se cambian de posicion
				{			  	  //Tal que quedaria el minimo ultimo y el maximo primero
					aux=MAX[j];
					MAX[j]=MAX[j+1];
					MAX[j+1]=aux;
				}
			}
		}
		return MAX[0];//Devolvemos simplemente el primer elemento(el maximo)
	}
	else if(r==2)
	{
		for(i=12;i<24;i++)
		{
			MAX[i]=numdatos[x].dato[i];
		}
		for(i=0;i<12;i++)
		{
			for(j=12;j<23;j++)//Para el segundo año hacemos lo mismo pero hay que hacerlo desde el dato 12
			{	
				if(MAX[j]<MAX[j+1])
				{
					aux=MAX[j];
					MAX[j]=MAX[j+1];
					MAX[j+1]=aux;
				}
			}
		}
		return MAX[12];//Pero hay que devolver el elemento 12
	}
}

float min(int r,int x)//Funcion que calcula el minimo
{
	int i,j;
	float MIN[24],aux=0;
	//printf("De que tipo de generacion quiere calcular el minimo?:\n");
	//MOSTRARTIPOS(0);
	//scanf("%i",&x);
	
	if(r==1)
	{
		for(i=0;i<12;i++)
		{
			MIN[i]=numdatos[x].dato[i];
		}
		for(i=0;i<12;i++)
		{
			for(j=0;j<11;j++)
			{	
				if(MIN[j]>MIN[j+1])//En el minimo es hacer lo mismo que en el maximo pero con > en vez de <
				{			  	  
					aux=MIN[j];
					MIN[j]=MIN[j+1];
					MIN[j+1]=aux;
				}
			}
		}
		return MIN[0];
	}
	else if(r==2)
	{
		for(i=12;i<24;i++)
		{
			MIN[i]=numdatos[x].dato[i];
		}
		for(i=0;i<12;i++)
		{
			for(j=12;j<23;j++)//Para el segundo año hacemos lo mismo pero hay que hacerlo desde el dato 12
			{	
				if(MIN[j]>MIN[j+1])
				{
					aux=MIN[j];
					MIN[j]=MIN[j+1];
					MIN[j+1]=aux;
				}
			}
		}
		return MIN[12];//DEVOLVER ELEMENTO 12
	}
}

void ordenar(int tipo, int forma,int r)//Funcion que ordena los datos
{
	int i,j;
	float V1[24],aux;
	
	for(i=0;i<24;i++)
	{
		V1[i]=numdatos[tipo-1].dato[i];
	}
	if(r==1)
	{
		if(forma == 1)
		{
			for(i=0;i<12;i++)
			{
				for(j=0;j<11;j++)
				{
					if(V1[j]<V1[j+1])
					{			  	  
						aux=V1[j];
						V1[j]=V1[j+1];
						V1[j+1]=aux;
					}
				}
			}
		}	
		else if(forma == 2)
		{
			for(i=0;i<12;i++)
			{
				for(j=0;j<11;j++)
				{
					if(V1[j]>V1[j+1])
					{			  	  
						aux=V1[j];
						V1[j]=V1[j+1];
						V1[j+1]=aux;
					}
				}
			}
		}
		
		printf("La generacion ordenada por la forma deseada es:\n");
		for(i=0;i<12;i++)
		{
		 	printf("\t%.3f\n",V1[i]);
		}
	}
	if(r==2)
	{
		if(forma == 1)
		{
			for(i=0;i<12;i++)
			{
				for(j=12;j<23;j++)
				{
					if(V1[j]<V1[j+1])
					{			  	  
						aux=V1[j];
						V1[j]=V1[j+1];
						V1[j+1]=aux;
					}
				}
			}
		}	
		else if(forma == 2)
		{
			for(i=0;i<12;i++)
			{
				for(j=12;j<23;j++)
				{
					if(V1[j]>V1[j+1])
					{			  	  
						aux=V1[j];
						V1[j]=V1[j+1];
						V1[j+1]=aux;
					}
				}
			}
		}
		
		printf("La generacion ordenada por la forma deseada es:\n");
		for(i=12;i<24;i++)
		{
		 	printf("\t%.3f\n",V1[i]);
		}
	}
}

int MOSTRARTIPOS(int t)//Para no repetir el mostrado de los tipos de generacion que hay para escoger uno, he hecho una funcion
{
	int i;
	for(i=0;i<17;i++)
    {
    	printf("\t%i) %s\n", i+1 ,numdatos[i].tipo);
	}
	return 1;
}

float POT(float base,int potencia)//Funcion creada para calcular potencias de numeros enteros con cualquier tipo de base
{
	int i;
	float aux;
	aux=base;
	if(potencia==0)return 1;
	for(i=1;i<potencia;i++)
	{
		base*=aux;
	}
	return base;
}

int CALCULOESTAD()//Esta funcion sirve para elegir que calculo estadistico se quiere acceder
{
	
	int i;
	printf("Distintos calculos a elegir:\n");
		for(i=0;i<4;i++)
    		{
    			printf("%i)",i+1);
    			if(i==0)
				{
    				printf("\tCalculo de media anual.\n");	
				}
				else if(i==1)
				{
					printf("\tCalculo de mediana anual.\n");
				}
				else if(i==2)
				{
					printf("\tCalculo de varianza anual.\n");
				}
				else if(i==3)
				{
					printf("\tCalculo del maximo y minimo anual.\n");
				}
			}
		printf("\n---> Para volver la menu principal pulsa 0 <---\n");	
		printf("\nQue desea? ");
}

int verificar_char(char c, int *resultado)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    {
        *resultado = c;  // Guarda el caracter si es una letra
        return c;
    } 
	else if (c >= '0' && c <= '9') 
	{
        *resultado = c;  // Guarda el numero si es un digito
        return c - 48;
    } 
	else 
	{
        *resultado = c;
        return c;
    }
}

int pregunta_calculos(int s)
{
	int i=0,j=0,x=0,e=0,y=0;
	float M,m;
	if(s == 1)
	{
		printf("\nDe que anio desea calcular medias? 1 para el primero(2021) o 2 para el segundo(2022): ");
	    scanf("%i",&e);
	    if(e==1)
	    {
	        printf("Tipos de generacion a elegir:\n");
	        MOSTRARTIPOS(0);
	        printf("Que generacion desea? ");
	        scanf("%i",&y);
	        if(y>0 && y<18)
	        {
	            RECOGER2(s,e,y);
	            MENU_CALCULOS();
	            return 0;
		    }
		    else
		    {
			    printf("Boton incorrecto\n");
			    printf("Vuelva a intentarlo\n");
			    MENU_CALCULOS();
			    return 0;
	        }
        }
        else if(e==2)
        {
		    printf("Tipos de generacion a elegir:\n");
	        MOSTRARTIPOS(0);
	        printf("Que generacion desea? ");
	        scanf("%i",&y);
	        if(y >0 && y <18)
	        {
	            RECOGER2(s,e,y);
	            MENU_CALCULOS();
	            return 0;
		    }
		    else
		    {
		        printf("Boton incorrecto\n");
			    printf("Vuelva a intentarlo\n");
			    MENU_CALCULOS();
		        return 0;
	        }		
	    }
	    else
	    {
	        printf("Boton incorrecto\n");
		    printf("Vuelva a intentarlo\n");
		    MENU_CALCULOS();
	 	    return 0;
	    }
	}
	else if(s == 2)
	{
		printf("\nDe que anio desea calcular medianas? 1 para el primero(2021) o 2 para el segundo(2022): ");
		scanf("%i",&e);
		if(e==1)
	    {
	       	printf("Tipos de generacion a elegir:\n");
	       	MOSTRARTIPOS(0);
	       	printf("Que generacion desea? ");
	       	scanf("%i",&y);
	        if(y>0 && y<18)
	        	{
	        		RECOGER2(s,e,y);
	            	MENU_CALCULOS();
	            	return 0;
				}
			else
				{
					printf("Boton incorrecto\n");
					printf("Vuelva a intentarlo\n");
					MENU_CALCULOS();
					return 0;
	    		}
	    }
	    else if(e==2)
	    {
			printf("Tipos de generacion a elegir:\n");
	        MOSTRARTIPOS(0);
	        printf("Que generacion desea? ");
	        scanf("%i",&y);
	        if(y >0 && y <18)
	        {
	        	RECOGER2(s,e,y);
	            MENU_CALCULOS();
	            return 0;
			}
			else
			{
				printf("Boton incorrecto\n");
				printf("Vuelva a intentarlo\n");
				MENU_CALCULOS();
				return 0;
	    	}		
	    }
		else
	    {
	    	printf("Boton incorrecto\n");
			printf("Vuelva a intentarlo\n");
			MENU_CALCULOS();
			return 0;
		}
	}
	else if(s == 3)
	{
		printf("\nDe que anio desea calcular la varianza? 1 para el primero(2021) o 2 para el segundo(2022): ");
		scanf("%i",&e);
		if(e==1)
	    {
	       	printf("Tipos de generacion a elegir:\n");
	       	MOSTRARTIPOS(0);
	       	printf("Que generacion desea? ");
	       	scanf("%i",&y);
	        if(y>0 && y<18)
	        	{
	        		RECOGER2(s,e,y);
	            	MENU_CALCULOS();
	            	return 0;
				}
			else
				{
					printf("Boton incorrecto\n");
					printf("Vuelva a intentarlo\n");
					MENU_CALCULOS();
					return 0;
	    		}
	    }
	    else if(e==2)
	    {
			printf("Tipos de generacion a elegir:\n");
	        MOSTRARTIPOS(0);
	        printf("Que generacion desea? ");
	        scanf("%i",&y);
	        if(y >0 && y <18)
	        {
	        	RECOGER2(s,e,y);
	            MENU_CALCULOS();
	            return 0;
			}
			else
			{
				printf("Boton incorrecto\n");
				printf("Vuelva a intentarlo\n");
				MENU_CALCULOS();
				return 0;
	    	}		
	    }
		else
	    {
	    	printf("Boton incorrecto\n");
			printf("Vuelva a intentarlo\n");
			MENU_CALCULOS();
			return 0;
		}
	}
	else if(s == 4)
	{
		printf("\nDe que anio desea calcular el maximo y el minimo? 1 para el primero(2021) o 2 para el segundo(2022): ");
		scanf("%i",&e);
		if(e == 1)
	    {
	       	printf("Tipos de generacion a elegir:\n");
	       	MOSTRARTIPOS(0);
	       	printf("Que generacion desea? ");
	       	scanf("%i",&y);
	        if(y > 0 && y < 18)
	        	{
	        		RECOGER2(s,e,y);
	        		MENU_CALCULOS();
	            	return 0;
				}
			else
				{
					printf("Boton incorrecto\n");
					printf("Vuelva a intentarlo\n");
					MENU_CALCULOS();
					return 0;
	    		}
	    }
	    else if(e==2)
	    {
			printf("Tipos de generacion a elegir:\n");
	        MOSTRARTIPOS(0);
	        printf("Que generacion desea? ");
	        scanf("%i",&y);
	        if(y >0 && y <18)
	        {
	        	RECOGER2(s,e,y);
	        	MENU_CALCULOS();
	           	return 0;
			}
			else
			{
				printf("Boton incorrecto\n");
				printf("Vuelva a intentarlo\n");
				MENU_CALCULOS();
				return 0;
	    	}		
	    }
	    else
	    {
	    	printf("Boton incorrecto\n");
			printf("Vuelva a intentarlo\n");
			MENU_CALCULOS();
			return 0;
		}
	}
	
}

