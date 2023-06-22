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
int MOSTRARTIPOS(int );
int CALCULOESTAD(int);
int BUSCARDATO(int,int);
float MENU_PRINCIPAL();
int MENU_DATOS();
int MENU_CALCULOS();
float media(int,int);
float varianza(int);
float POT(float,int);
float mediana(int);
float max(int);
float min(int);
int MENU_ORDENAR();
void ordenar(int, int,int);

int main()
{
	int tecla,i=0,j=0,x=0,e=0,y=0;
	FILE *fich;
	if((fich=fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r"))==NULL)printf("Problema al abrir fichero"); //Apertura
	
	RECOGER(fich);//Hacemos la llamada a la funcion que nos almacena todos los datos del archivo en la memoria del ordenador
	
	fclose(fich);//Se cierra el fichero ya que no necesitamos trabajar mas con el, tenemos ya los datos en nuestra memoria
	
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

float MENU_PRINCIPAL()
{
	int menu1=4,i=0,j=0,x=0,e=0,y=0;
	do
	{
		if(menu1==4)
		{
			printf("--------------------------------------------------------MENU--------------------------------------------------------\n");
        	printf("1) Buscador de datos.\n");
        	printf("2) Calculos estadisticos.\n");
        	printf("3) Ordenacion de datos\n");
        	printf("4) Salir\n");
        	printf("A donde quiere acceder?\n");
        	scanf("%i", &menu1);
		}
        switch(menu1)
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
			    break;   
		}
	}while(menu1!=4);
	
	return 0;
}

int MENU_DATOS()
{
	int menu1,menu2,i=0,j=0,x=0,e=0,y=0;
	int regresar = 0, volver = 0;
	printf("------------------------------------------------------BUSCADOR------------------------------------------------------");
	printf("\nA que tipo de generacion quiere acceder?\n");
    MOSTRARTIPOS(0);
    printf("----> Volver(18)\n");
    scanf("%i", &menu2);
    if(menu2 >=1 && menu2<=17)
    {
    	printf("Sabiendo que los datos estan ordenados por meses a lo largo de 2 a?os(24 datos en total)\n");
	    printf("Elija la posicion del valor deseado:\n");
	    scanf("%i", &j);
	    if(j >= 1 && j <= 24)
	    {
	    	BUSCARDATO(menu2,j);
	        printf("\nDesea buscar otro numero(1) o quiere volver al menu principal(2)?");
	        scanf("%i",&i);
	        if(i == 1)
	        {
	    	    MENU_DATOS();
	    	    return 0;
		    }
		    else if(i == 2)
		    {
			    MENU_PRINCIPAL();
			    return 0;
		    }
		}
		else
		{
			while(i != 1 && i != 2)
			{
				printf("Boton incorrecto\n");
			    printf("Vuelva a pulsar\n");
			    scanf("%i", &i);
			    if(i == 1)
	            {
	    	        MENU_DATOS();
	    	        return 0;
		        }
		        else if(i == 2)
		        {
			        MENU_PRINCIPAL();
			        return 0;
		        }
			}
			
		}
	    
	}
	else if(menu2 == 18)
	{
		MENU_PRINCIPAL();
		return 0;
	}
	else
	{
		printf("Boton incorrecto\n");
		MENU_DATOS();
		return 0;
	}
}

int MENU_CALCULOS()
 {
	int menu1,i=0,j=0,x=0,e=0,y=0;
	float M,m;
	printf("------------------------------------------------------CALCULOS------------------------------------------------------");
	printf("\nQue calculo desea?\n");
    x=CALCULOESTAD(x);
	if(x==1)
	{
		printf("De que a?o desea calcular medias? 1 para el primero(2021) 2 para el segundo(2022):\n");
		scanf("%i",&e);
		while(e==1)
	    {
	        printf("De que tipo de generacion quiere calcular la media?:\n");
	        MOSTRARTIPOS(0);
	        scanf("%i",&y);
	        if(y >= 1 && y <= 17)
	        {
	        	printf("La media en 2021 es %f GWh",media(1,y));
	            printf("\nDesea calcular otra media de 2021? 1 para si, 2 para calcular medias del 2022 y cualquier otro numero para otros calculos:\n");
	            scanf("%i",&e);
	            if(e != 1 && e != 2)
			    {
				    MENU_CALCULOS();
				    return 0;
			    }
			}
			else if(y == 18)
			{
				MENU_CALCULOS();
				return 0;
			}
			else
			{
				while(y > 17)
				{
					printf("Boton incorrecto\n");
					printf("Vuelva a intentarlo\n");
					scanf("%i", &y);
					if(y >= 1 && y <= 17)
					{
						printf("La media en 2021 es %f GWh",media(1,y));
	                    printf("\nDesea calcular otra media de 2021? 1 para si, 2 para calcular medias del 2022 y cualquier otro numero para otros calculos:\n");
	                    scanf("%i",&e);
	                    if(e != 1 && e != 2)
			            {
				            MENU_CALCULOS();
				            return 0;
			            }
					}
				}
			} 
	    }
	    while(e==2)
	    {
			printf("De que tipo de generacion quiere calcular la media?:\n");
	        MOSTRARTIPOS(0);
	        printf("----> Volver(18)\n");
	        scanf("%i",&y);
	        if(y >= 1 && y <= 17)
	        {
	        	printf("La media en 2022 es %f GWh",media(2,y));
	            printf("\nDesea calcular otra media de 2022? 2 para si, cualquier otro numero para no y calcular otros calculos:\n");
	            scanf("%i",&e);
	            if(e != 1 && e != 2)
			    {
				    MENU_CALCULOS();
				    return 0;
			    }
			}
			else if(y == 18)
			{
				MENU_CALCULOS();
				return 0;
			}
			else
			{
				while(y > 17)
				{
					printf("Boton incorrecto\n");
					printf("Vuelva a intentarlo\n");
					scanf("%i", &y);
					if(y >= 1 && y <= 17)
					{
						printf("La media en 2022 es %f GWh",media(2,y));
	                    printf("\nDesea calcular otra media de 2022? 2 para si, cualquier otro numero para no y calcular otros calculos:\n");
	                    scanf("%i",&e);
	                    if(e != 1 && e != 2)
			            {
				            MENU_CALCULOS();
				            return 0;
			            }
					}
				}
			}
	    }
		while(e != 1 && e != 2)
		{
		    printf("\nBoton incorrecto\n");
		    MENU_CALCULOS();
		    return 0;
	    }
	}  
	else if(x==2)
	{
		printf("De que a?o desea calcular la mediana? 1 para el primero(2021) 2 para el segundo(2022):\n");
		scanf("%i",&e);
	    while(e==1)
	    {
		    printf("La mediana en 2021 es %f GWh\n",mediana(1));
	        printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		    scanf("%i",&e);
		    if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
 	    }
		while(e==2)
		{
			printf("La mediana en 2022 es %f GWh\n",mediana(2));
		    printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			scanf("%i",&e);
			if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
		}
		while(e != 1 && e != 2)
		{
		    printf("\nBoton incorrecto\n");
		    printf("Vuelve a pulsar\n");
		    scanf("%i", &e);
		    if(e == 1)
		    {
		    	while(e==1)
	            {
		            printf("La mediana en 2021 es %f GWh\n",mediana(1));
	                printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		            scanf("%i",&e);
		            if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
 	            }
			}
			else if(e == 2)
			{
				while(e==2)
		        {
			        printf("La mediana en 2022 es %f GWh\n",mediana(2));
		            printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			        scanf("%i",&e);
			        if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
		        }
			}
	    }
	}
	else if(x==3)
	{
	printf("De que a?o desea calcularla? 1 para el primero(2021) 2 para el segundo(2022):\n");
	scanf("%i",&e);
	    while(e==1)
	    {
		    printf("La varianza en 2021 es %f GWh\n",varianza(1));
	        printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		    scanf("%i",&e);
		    if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
 	    }
		while(e==2)
		{
			printf("La varianza en 2022 es %f GWh\n",varianza(2));
		    printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			scanf("%i",&e);
			if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
		}
		while(e != 1 && e != 2)
		{
		    printf("\nBoton incorrecto\n");
		    printf("Vuelva a pulsar\n");
		    scanf("%i", &e);
		    if(e == 1)
		    {
		    	while(e==1)
	            {
		            printf("La varianza en 2021 es %f GWh\n",varianza(1));
	                printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		            scanf("%i",&e);
		            if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
 	            }
			}
			else if(e == 2)
			{
				while(e==2)
		        {
			        printf("La varianza en 2022 es %f GWh\n",varianza(2));
		            printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			        scanf("%i",&e);
			        if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
		        }
			}
	    }
	}
	else if(x==4)
	{
		printf("De que a?o desea calcular el maximo y el minimo? 1 para el primero(2021) 2 para el segundo(2022):\n");
		scanf("%i",&e);
	    while(e==1)
	    {
	    	M=max(1);
	    	m=min(1);
		    printf("El maximo en 2021 es %f GWh y el minimo es %f GWh\n",M,m);
	        printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		    scanf("%i",&e);
		    if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
 	    }
		while(e==2)
		{
			M=max(2);
	    	m=min(2);
			printf("El maximo en 2022 es %f GWh y el minimo es %f GWh\n",M,m);
		    printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			scanf("%i",&e);
			if(e != 1 && e != 2)
			{
				MENU_CALCULOS();
				return 0;
			}
		}
		while(e != 1 && e != 2)
		{
			printf("\nBoton incorrecto\n");
		    printf("Vuelva a pulsar\n");
		    scanf("%i", &e);
		    if(e == 1)
		    {
		    	while(e==1)
	            {
	    	        M=max(1);
	    	        m=min(1);
		            printf("El maximo en 2021 es %f GWh y el minimo es %f GWh\n",M,m);
	                printf("\nDesea calcular otra vez de 2021? 1 para si, 2 para calcular del 2022 y cualquier otro numero para otros calculos:\n");
		            scanf("%i",&e);
		            if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
 	            }
			}
			else if(e == 2)
			{
				while(e==2)
		        {
			        M=max(2);
	    	        m=min(2);
			        printf("El maximo en 2022 es %f GWh y el minimo es %f GWh\n",M,m);
		            printf("\nDesea calcular otra vez de 2022? 2 para si y cualquier otro numero para otros calculos:\n");
			        scanf("%i",&e);
			        if(e != 1 && e != 2)
			        {
				        MENU_CALCULOS();
				        return 0;
			        }
		        }
			}
		}
	}
	else if(x == 5)
	{
		MENU_PRINCIPAL();
		return 0;
	}
	else
	{
		printf("Boton incorrecto\n");
		MENU_CALCULOS();
		return 0;
	}
}

int MENU_ORDENAR()
{
	int menu1,menu2,i=0,j=0,x=0,e=0,y=0;
	int regresar = 0, volver = 0;
	printf("------------------------------------------------------ORDENAR------------------------------------------------------");
	printf("\nA que tipo de generacion quiere acceder?\n");
    MOSTRARTIPOS(0);
    printf("----> Volver(18)\n");
    scanf("%i", &menu2);
    if(menu2 >=1 && menu2<=17)
    {
    	printf("Que a�o le interesa? 2021(1) o 2022(2):\n");
    	scanf("%i",&e);
    	if(e == 1 || e == 2)
    	{
    		printf("Como desea ordenar la generacion? Mayor a menor (1) o Menor a mayor(2)?:\n");
    	    scanf("%i",&j);
    	    if(j == 1 || j == 2)
    	    {
    		    ordenar(menu2,j,e);
	            printf("\nDesea ordenar otravez?(1) o desea volver al menu principal(2)?");
	            scanf("%i",&i);
	            if(i == 1)
	            {
	    	        MENU_ORDENAR();
	    	        return 0;
		        }
		        else if(i == 2)
		        {
			        MENU_PRINCIPAL();
			        return 0;
		        }
		        else
		        {
			        while(i != 1 && i!=2)
			        {
				        printf("\nBoton incorrecto\n");
				        printf("Vuelva a pulsar\n");
				        scanf("%i", &i);
				        if(i == 1)
				        {
					        MENU_ORDENAR();
					        return 0;
				        }
				        else if(i == 2)
				        {
				    	    MENU_PRINCIPAL();
					        return 0;
					    }
			        }
		        }
		    }
		    else
		    {
			    printf("\nBoton incorrecto\n");
			    printf("Vuelva a pulsar\n");
			    scanf("%i", &j);
			    if(j == 1)
				{
					ordenar(menu2,j,e);
					printf("\nDesea ordenar otravez?(1) o desea volver al menu principal(2)?");
	                scanf("%i",&i);
	                if(i == 1)
	                {
	    	            MENU_ORDENAR();
	    	            return 0;
		            }
		            else if(i == 2)
		            {
			            MENU_PRINCIPAL();
			            return 0;
		            }
		            else
		            {
			            while(i != 1 && i!=2)
			            {
				            printf("\nBoton incorrecto\n");
				            printf("Vuelva a pulsar\n");
				            scanf("%i", &i);
				            if(i == 1)
				            {
					            MENU_ORDENAR();
					            return 0;
				            }
				            else if(i == 2)
				            {
				    	        MENU_PRINCIPAL();
					            return 0;
					        }
			            }
		            }
				}
				else if(j == 2)
				{
				    ordenar(menu2,j,e);
				    ordenar(menu2,j,e);
					printf("\nDesea ordenar otravez?(1) o desea volver al menu principal(2)?");
	                scanf("%i",&i);
	                if(i == 1)
	                {
	    	            MENU_ORDENAR();
	    	            return 0;
		            }
		            else if(i == 2)
		            {
			            MENU_PRINCIPAL();
			            return 0;
		            }
		            else
		            {
			            while(i != 1 && i!=2)
			            {
				            printf("\nBoton incorrecto\n");
				            printf("Vuelva a pulsar\n");
				            scanf("%i", &i);
				            if(i == 1)
				            {
					            MENU_ORDENAR();
					            return 0;
				            }
				            else if(i == 2)
				            {
				    	        MENU_PRINCIPAL();
					            return 0;
					        }
			            }
		            }
				}
		    }
		}
		else
		{
			printf("\nBoton incorrecto\n");
			MENU_ORDENAR();
		}    
	}
	else
	{
		printf("\nBoton incorrecto\n");
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
					printf("%.15lf GWh",numdatos[i-1].dato[numdato-1]);
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
				media+=numdatos[y-1].dato[i];
				//printf("%f\t",media);
			}	
	}
	else if(r==2)
	{
		for(i=12;i<24;i++)
			{
				media+=numdatos[y-1].dato[i];
				//printf("%f\t",media);
			}
	}
	return media/12;
}

float mediana(int r)//Funcion que calcula la mediana
{
	int x;
	float mediana;
	printf("De que tipo de generacion quiere calcular la mediana?:\n");
	MOSTRARTIPOS(0);
	printf("----> Volver(18)");
	scanf("%i",&x);
	if(r==1)
	{
		mediana=numdatos[x-1].dato[5]+numdatos[x-1].dato[6];
	}
	else if(r==2)
	{
		mediana=numdatos[x-1].dato[17]+numdatos[x-1].dato[18];
	}
	else
	{
		while(r != 1 && r != 2)
		{
			printf("Boton incorrecto\n");
			printf("Vuelve a pulsar\n");
			scanf("%i", &r);
			if(r == 1)
			{
				mediana=numdatos[x-1].dato[5]+numdatos[x-1].dato[6];
			}
			else if(r == 2)
			{
				mediana=numdatos[x-1].dato[17]+numdatos[x-1].dato[18];
			}
		}
	}
	return mediana/2;
}

float varianza(int r)//Funcion que calcula la varianza de lo deseado
{
	int i=0,x=0;
	float m;
	float varianza=0;
	printf("De que tipo de generacion quiere calcular la varianza?:\n");
	MOSTRARTIPOS(0);
	scanf("%i",&x);
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

float max(int r)//Funcion que calcula el maximo
{
	int x,i,j;
	float MAX[24],aux=0;
	printf("De que tipo de generacion quiere calcular el maximo?:\n");
	MOSTRARTIPOS(0);
	scanf("%i",&x);
	
	if(r==1)
	{
		for(i=0;i<12;i++)
		{
			MAX[i]=numdatos[x-1].dato[i];//Lo copiamos en un vector para facilitar el trabajo y no tener que pensar en estructuras
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
			MAX[i]=numdatos[x-1].dato[i];
		}
		printf("El dato 12 =%f",numdatos[x-1].dato[12]);
		for(i=0;i<12;i++)
		{
			for(j=12;j<23;j++)//Para el segundo a�o hacemos lo mismo pero hay que hacerlo desde el dato 12
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

float min(int r)//Funcion que calcula el minimo
{
	int x,i,j;
	float MIN[24],aux=0;
	printf("De que tipo de generacion quiere calcular el minimo?:\n");
	MOSTRARTIPOS(0);
	scanf("%i",&x);
	
	if(r==1)
	{
		for(i=0;i<12;i++)
		{
			MIN[i]=numdatos[x-1].dato[i];
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
			MIN[i]=numdatos[x-1].dato[i];
		}
		for(i=0;i<12;i++)
		{
			for(j=12;j<23;j++)//Para el segundo a�o hacemos lo mismo pero hay que hacerlo desde el dato 12
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
		 	printf("%.3f\n",V1[i]);
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
		 	printf("%.3f\n",V1[i]);
		}
	}
}

int MOSTRARTIPOS(int t)//Para no repetir el mostrado de los tipos de generacion que hay para escoger uno, he hecho una funcion
{
	int i;
	for(i=0;i<17;i++)
    {
    	printf("%i) %s\n", i+1 ,numdatos[i].tipo);
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

int CALCULOESTAD(int x)//Esta funcion sirve para elegir que calculo estadistico se quiere acceder
{
	int i;
		for(i=0;i<5;i++)
    		{
    			printf("%i)",i+1);
    			if(i==0)
				{
    				printf("Calculo de media anual.\n");	
				}
				else if(i==1)
				{
					printf("Calculo de mediana anual.\n");
				}
				else if(i==2)
				{
					printf("Calculo de varianza anual.\n");
				}
				else if(i==3)
				{
					printf("Calculo del maximo y minimo anual.\n");
				}
				else if(i==4)
				{
					printf("Volver al menu principal.\n");
				}
			}
		scanf("%i",&x);
		return x;
}
