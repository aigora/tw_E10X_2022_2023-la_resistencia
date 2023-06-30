//La idea es guardar cada una de las lineas en una cadena de caracteres y trabajar con solo las cadenas

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUFFERTAMANOMAX 4

typedef struct//Esta estructura sirve para almacenar cada una de las lineas de nuestro archivo csv
{
	char lineas[500];
}lin;

struct datos//Estructura definitiva que tendrá almacenada el nombre del tipo de generacion y sus correspondientes 24 datos 12 por cada anio(2021 y 2022)
{
	char tipo[35];
	double dato[24];
}numdatos[17];

struct extra//Estructura destinada para guardar cada uno de los datos en caracteres para despues convertirlos en numeros reales(floats)
{
	char cardato[30];//El numero de caracteres que permite la cadena cardato
}extradatos[408];//La dimension es 408 numero que corresponde al numero total de datos que hay, obtenido multiplicando 17*24

void RECOGER(FILE *);//Funcion que recoge los datos del archivo principal y los almacena en la memoria del ordenador con la ayuda de las estructuras
void ESCRIBIR(FILE *);//Funcion destinada a escribir en otro archivo csv que hemos llamado calculos_estadisticos, almacena los calculos que se utilizaran
float RECOGER2(int,int,int);//Funcion que recogera el calculo deseado del archivo calculos
int MOSTRARTIPOS(int);//Funcion que nos muestra los tipos de generacion a elegir
int CALCULOESTAD();//Funcion que nos muestra los calculos estadisticos que el programa puede calcular
int BUSCARDATO(int,int);//Esta funcion busca el calculos deseado por el usuario
float MENU_PRINCIPAL();//El menu principal que contiene las acciones principales que puede realizar el programa
int MENU_DATOS();//Una de las acciones es buscar un dato, esta funcion muestra el menu destinado a buscar con sus preguntas
int MENU_CALCULOS();//Otra de las acciones es calcular unas estadisticas, este es el menu
float media(int,int);//Calcula medias de la generacion deseada
float varianza(int,int);
float POT(float,int);//Una funcion destinada a calcular potencias(elevar numeros), NO perimte raices de ningun tipo pero no es necesario para este programa
float mediana(int,int);
float max(int,int);
float min(int,int);
int MENU_ORDENAR();//La ultima accion es ordenar de mayor a menor o vice versa los datos de una generacion, este es el menu
void ordenar(int, int,int);//Esta funcion ordena los datos
int validarOpcion();//Esta funcion nos sirve para verificar si el usuario ha tecleado un numero o una letra
int pregunta_calculos(int);//Para facilitar el menu de calculos metemos gran parte de sus preguntas en una funcion
float calcularPrimerCuartil(int arr[], int n);
float calcularSegundoCuartil(int arr[], int n);
int MENU_Comparacion_primeranio(int,int);
int MENU_Comparacion_segundoanio(int,int);
int MENU_Comparacion_todo(int,int);
int main()
{
	FILE *fich;//fichero para recoger
	FILE *fich2;//fichero para escribir
	if((fich=fopen("generacion_por_tecnologias_21_22_puntos_simplificado.csv","r"))==NULL)printf("Problema al abrir primer fichero"); //Apertura
	RECOGER(fich);//Llamada a la funcion que nos almacena los datos
	fclose(fich);//Se cierra el fichero ya que no necesitamos trabajar mas con el, tenemos ya los datos en nuestra memoria
	if((fich2=fopen("Calculos_estadisticos.csv","w"))==NULL)printf("Problema al abrir segundo fichero"); //Apertura del fichero para escribir
	ESCRIBIR(fich2);//Se escribe en el nuevo archivo
	fclose(fich2);//Se cierra no lo necesitamos mas
	MENU_PRINCIPAL();
}

void RECOGER(FILE *fich)
{
	//Primero hay que contar la cantidad de lineas que tenemos.
	//La cantidad de lineas "n" sera la dimension de nuestro vector de estructuras "lin" cada elemento de este vector tendra una linea
	lin *numlineas; //El puntero de estructuras que cambiaremos a vector con dimension n.
	int n=0,i=0,j=0,k=0,numcomas=0,q=0,d=0,l=0,m=0;
	while(!feof(fich))
	{
		if(fgetc(fich)=='\n') n++;
	}
	//printf("El numero total de lineas en el archivo es %i",n);
	//Nos da el valor n igual a 22
	numlineas=(lin*)malloc(n*sizeof(lin));//El puntero lo hemos cambiado a un vector con dimension "n" de tipo lin para que sea de estructuras
	rewind(fich);//es importante mover el vector hacia el principio otra vez ya que hemos leido y lo hemos dejado alfinal al hacerlo
	//Ahora copiamos en cada elemento de numlineas una cadena(linea).
	for(i=0;i<n;i++)
	{
		fgets(numlineas[i].lineas,sizeof(numlineas[i].lineas),fich);//Esto copia cada fila en cada elemento
		//Lo que pasa es que el fgets tambien copia el '\n' asi que hay que cambiarlo por un ',' para cerrar la linea en el archivo ya que es csv
		numlineas[i].lineas[strlen(numlineas[i].lineas)-1]=',';
		//Hay que cerrar la cadena, se aniade un '\0' al final
		numlineas[i].lineas[strlen(numlineas[i].lineas)]='\0';
	}
	fclose(fich);//Cerramos fichero ya que ya no vamos a hacer nada con el

	//Se ve si hemos copiado bien el archivo entero
	/*for(i=0;i<n;i++)
	{
		printf("%s",numlineas[i].lineas);
	}*/

	/*Lo siguente que tenemos que hacer es ordenar los nombres de los tipos en la segunda estructura
	y cambiar los numeros de caracteres a floats(numeros reales)*/

	//Para ello encontramos la coma en cada cadena
	//Al mismo tiempo lo copiamos
	for(i=5,k=0;i<n;i++,k++)//i se inicia en 5 ya que determina en que linea estamos y solo nos interesa copiar los datos
							//(empiezan en la linea 6 que para el ordenador es el 5 ya que cada vector o array empieza en el elemento 0)
	{
		for(j=0,numcomas=0;numcomas<1;j++)//Esto nos encontrara la posicion de la coma definida por j
		{
			if(numlineas[i].lineas[j]==',')
			{
				numcomas++;
				//printf("\nEn la linea %i la primera coma se encuentra en la posicion %i",i,j);
				//Ahora copiamos en la segunda estructura el nombre del tipo correspondiente
				memcpy(numdatos[k].tipo,numlineas[i].lineas,j*sizeof(char));
				q=j;//Para los datos empezamos desde la primera coma entcontrada en la linea
				for(m=0;m<24;m++)
				{
					q++;//Debe de empezar en la proxima posicion despues de cada coma le sumamos a q uno
					//printf("Valor de q= %i",q);
					d=0;
					while(numlineas[i].lineas[q]!=',')//***Aqui es donde lo copiamos***//
					{
						extradatos[l].cardato[d]=numlineas[i].lineas[q];/*Se copia cada numero que esta entre comas
																		desde la primera coma hasta la ultima*/
						d++;											//La d sirve para la posicion en la cadena en la que se copia el numero
						q++;											//La posicion de la coma esta indicada por la q esta sigue la cadena copiada
						//printf("\t%s\t",extradatos[l].cardato);
					}
					l++;//Para el siguiente dato
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
			numdatos[i].dato[j]=atof(extradatos[k].cardato);//atof funcion que cambia de ascii a float
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
	//Se empieza a escibir en el nuevo archivo poniendo los titulos
	//En la primera columna ponemos los tipos de generaciones
	//En las siguientes columnas ponemos los calculos de los dos anios separados primero va la media, despues la mediana y etc.
	int i=1,j=0,k=0;//el valor de i NO se puede cambiar es importante que entre en el for como un uno
	fprintf(fich,"Generación,Media anio 1,Media anio 2,");//Estos printfs no son tan eficientes ya que solo sirven para un caso particular,												  //se tendrian que cambiar si se utiliza otra mentalidad con el archivo
	fprintf(fich,"Mediana anio 1,Mediana anio 2,");
	fprintf(fich,"Varianza anio 1,Varianza anio 2,");
	fprintf(fich,"Maximo Minimo anio 1,Maximo Minimo anio 2,");
    fprintf(fich,"Cuartil_primero anio 1,Cuartil_primero anio 2,");
	fprintf(fich,"Cuartil_tercero anio 1,Cuartil_tercero anio 2,");

	fputc('\n',fich);
	for(j=0,k=0;j<17;j++,k++) //Ahora se escribe en el fichero cada columna
	{
		fprintf(fich,"%s,",numdatos[k].tipo); //Primero va el nombre del tipo, tiene una k y esta se va sumando cada vez que acaba con una linea
		fprintf(fich,"%f,",media(i,j));//Seguido por la media del primer anio
		i++;//Las funciones se explicaran despues pero la i sirve para indicar en que anio estamos por eso se suma uno, su valor sera 2(segundo anio)
		fprintf(fich,"%f,",media(i,j));//y se sigue con la media del segundo anio
		i--;//Pero el siguiente dato corresponde al primer anio asique se le resta un uno para que quede 1(primer anio)
		fprintf(fich,"%f,",mediana(i,j));//la cadena sigue con sus correspondientes funciones
		i++;
		fprintf(fich,"%f,",mediana(i,j));//Las comas son MUY importantes ya que queremos que sea un csv separan cada dato con un coma
		i--;
		fprintf(fich,"%f,",varianza(i,j));
		i++;
		fprintf(fich,"%f,",varianza(i,j));
		i--;
		fprintf(fich,"%f   %f,",max(i,j),min(i,j));
		i++;
		fprintf(fich,"%f   %f",max(i,j),min(i,j));
		i--;
		fprintf(fich,"%f"  calcularPrimerCuartil(i,j));
		i++
		fprintf(fich,"%f"  calcularPrimerCuartil(i,j));
		i--
		fprintf(fich,"%f"  calcularTercerCuartil(i,j));
		i++
        fprintf(fich,"%f"  calcularTercerCuartil(i,j));
        i--
		fputc('\n',fich);//Para seguir en la siguiente linea se le aniade un retorno de carro al final
 	}
}

float RECOGER2(int estad,int anio,int gener)
{
	//Ya que tenemos los calculos almacenados dentro del nuevo archivo los vamos a sacar de ahi cuando nos lo pida el usuario
	//Esta funcion lo hace, los parametros de entrada son la estadistica(que estadistica le interesa la media,mediana,...),el anio y el tipo de generacion
	//La mentalidad es la misma que con el archivo anterior vamos a almacenar cada linea en una cadena de caracteres
	int n=0,i=0,j=0,k=0,f=0;
	char c,rescarac[50];//En esta cadena vamos a meter nuetro resultado que vamos a mostrar al usuario esta en caracteres
	//No nos interesa calcular nada mas con estos calculos por lo que solo mostramos caracteres
	lin *recoger;//Vamos a reutilizar la estructura que hemos utilizado para almacenar cada linea del archivo anterior
	FILE *fich;
	if((fich=fopen("Calculos_estadisticos.csv","r"))==NULL)printf("Problema al abrir el fichero 3 para recoger el archivo de calculos\n");
	//Se sabe que tenemos 17 generaciones
	//En nuestro archivo que almacena los calculos hay 18 filas
	recoger=(lin*)malloc(18*sizeof(lin));//El puntero lo hemos cambiado a un vector con dimension "18".
	rewind(fich);
	for(i=0;i<18;i++)
	{
		fgets(recoger[i].lineas,sizeof(recoger[i].lineas),fich);//Esto copia cada fila en cada elemento
		//Se aniade una coma al final para cerrar la columna
		recoger[i].lineas[strlen(recoger[i].lineas)-1]=',';
		//Hay que cerrar la cadena, se aniade un '\0'
		recoger[i].lineas[strlen(recoger[i].lineas)]='\0';
	}
	//printf("%s",recoger[gener].lineas); /Esto nos sirve para comprobar si hemos recogido bien la linea
	fclose(fich);
	//Ahora es similar a lo que ya hemos hecho tenemos que encontrar las comas pero esta vez al mismo tiempo de saber su posicion, hay que contarlas
	if(estad==1)//En el archivo que hemos creado la cantidad de comas que tenemos que encontrar es distinta para cada estadistica
	{
		i=1;//La i indica cuantas comas hay que contar antes del dato que buscamos
		f=2;//La f indica cuantas comas hay que contar en total para encontrar el dato
		/*Por ejemplo, en la media del primer anio el dato esta entre la primera y segunda coma
		para la mediana del primer anio el dato esta entre la tercera y la cuarta*/
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
	if(anio==2)//Si nos interesa el segundo anio le sumamos simplemente uno a los dos parametros
		{
			i++;
			f++;
		}
	while(n!=i)//Los whiles sirven para saber en que posicion tenemos las comas deseadas por los parametros
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
	for(i=k,n=0;i<j;i++,n++)//Entonces simplemente copiamos cada caracter en rescarac para despues imprimer la cadena
		{
			rescarac[n]=recoger[gener].lineas[i];
		}
	rescarac[n-1]='\0';
	printf("%s",rescarac);
}

float MENU_PRINCIPAL()
{
	int z;
	printf("---------------------------------------------------MENU PRINCIPAL---------------------------------------------------\n");
	printf("1) Buscador de datos.\n");
    printf("2) Calculos estadisticos.\n");
    printf("3) Ordenacion de datos.\n");
    printf("4) Comparacion de datos\n");
	printf("5) Salir\n");
    printf("A donde quiere acceder? ");
    z=validarOpcion();
	if(z>0 && z<5)
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

int MENU_DATOS()
{
	int z=0,j=0;
	printf("-------------------------------------------MENU PRINCIPAL>>BUSCADOR DATO--------------------------------------------");
	printf("\nTipos de generaciones a elegir\n");
	MOSTRARTIPOS(0);
	printf("\n---> Para volver la menu principal pulsa 0 <---\n");
    printf("\nA que tipo de generacion quiere acceder? ");
    z=validarOpcion();
    if(z>0 && z<18)
    {
    	printf("Sabiendo que los datos estan ordenados por meses a lo largo de 2 anios(24 datos en total)\n");
	    printf("Elija la posicion del valor deseada: ");
    	j=validarOpcion();
	    if(j > 0 && j < 25)
	    {
	    	BUSCARDATO(z,j);
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
	else if(z == 0)
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
	int z;
	printf("\n----------------------------------------------MENU PRINCIPAL>>CALCULOS----------------------------------------------\n");
    CALCULOESTAD();
    z=validarOpcion();
	if(z>0 && z<5)
	{
		pregunta_calculos(z);
		return 0;
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
	int j=0,z=0,x=0;
	printf("----------------------------------------------MENU PRINCIPAL>>ORDENAR-----------------------------------------------");
	printf("\nTipos de generacion a acceder:\n");
    MOSTRARTIPOS(0);
    printf("\n---> Para volver la menu principal pulsa 0 <---\n");
    printf("\nQue generacion desea? ");
    z=validarOpcion();
    if(z>0 && z<18)
    {
    		printf("Que anio le interesa? 2021(1) o 2022(2): ");
    		x=validarOpcion();
    		if(x == 1 || x == 2)
    		{
    				printf("Como desea ordenar la generacion? Mayor a menor (1) o Menor a mayor(2)?: ");
    	    		j=validarOpcion();
    	    		if(j == 1 || j == 2)
    	    		{
    		    			ordenar(z,j,x);
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
	else if(z==0)
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


int Menu_Comparacion()
int x;
if(x>0 && (x<2)
   {


switch(z)
        {
    	    case 1:
    	   		MENU_Comparacion_primeraño();
				return 0;
            break;
    	    case 2:
    	    	MENU_Comparacion_segundoaño();
    	    	return 0;
    		break;
    		case 3:
    			MENU_Comparacion_todo();
    			return 0;
			break;

		}

   }




int BUSCARDATO(int tipo, int numdato)
{
	//Trabajamos con el tipo y el numero del dato recogido anteriormente
	printf("\tEl dato deseado es %.15lf GWh\n",numdatos[tipo-1].dato[numdato-1]);//Mostramos simplemente el dato que queremos de ese tipo
	return 0;
}

float media(int r,int x)//La r es el anio y la x es la generacion que se escoge
{
	int i=0;
	float media=0;
	if(r==1)//Si hemos pedido la media del primer anio hacemos el calculo con los 12 primeros datos
	{
			for(i=0;i<12;i++)
			{
				media+=numdatos[x].dato[i];//Hacemos el sumatorio de los datos de la generacion "y"
				//printf("%f\t",media);
			}
	}
	else if(r==2)//si es el segundo anio el calculo es desde el dato 13 que seria enero de 2022(segundo anio) para el ordenador es el 12
	{
		for(i=12;i<24;i++)
			{
				media+=numdatos[x].dato[i];
				//printf("%f\t",media);
			}
	}
	return media/12;//Se devuelve simplemente el sumatorio dividido por el numero de datos sumados
}

float mediana(int r,int x)//Funcion que calcula la mediana
{
	float mediana;
	if(r == 1)
	{
		mediana=numdatos[x].dato[5]+numdatos[x].dato[6];//Como el numero de datos que tenemos es par la mediana es el promedio de los dos datos centrales
						    						   //Para el anio 1 los dos datos centrales son el 6 y el 7 para el ordenador el 5 y el 6
	}
	else if(r == 2)
	{
		mediana=numdatos[x].dato[17]+numdatos[x].dato[18];
													  //Para el anio 2 los dos datos centrales son el 18 y el 19 para el ordenador el 17 y el 18
	}
	return mediana/2;
}

float varianza(int r,int x)//Funcion que calcula la varianza de lo deseado
{
	//Para la varianza utilizamos una formula que hemos estudiado en estadistica:
	//La varianza es el sumatorio del cuadrado de la resta de cada dato y la media dividido por el numero de datos totales
	int i=0;
	float m;
	float varianza=0;
	if(r==1)
	{
			m=media(1,x);//Calculamos rapidamente la media de la generacion de la que queremos calcular la varianza
			for(i=0;i<12;i++)
			{
					varianza+=POT((numdatos[x].dato[i]-m),2);
			}
	}
	else if(r==2)
	{
			m=media(2,x);
			for(i=12;i<24;i++)
			{
					varianza+=POT((numdatos[x].dato[i]-m),2);
			}
	}
	return varianza/12;
}

float max(int r,int x)//Funcion que calcula el maximo
{
	//La mentalidad es ordenar los datos de mayor a menor y simplemente devolver el primer dato
	int i,j;
	float MAX[24],aux=0;
	if(r==1)
	{
		for(i=0;i<12;i++)
		{
			MAX[i]=numdatos[x].dato[i];//Lo copiamos en un vector para facilitar el trabajo y no tener que pensar en estructuras
		}
		for(i=0;i<12;i++)//El primer for es para hacer la comparacion entre numeros 12 veces
		{
			for(j=0;j<11;j++)//Este for compara cada elemento con su siguiente pero lo hace 11 veces ya que un elemento no se compara con si mismo
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
	//Esta funcion hace lo mismo que el maximo y minimo pero el resultado en este caso es todos los datos ordenados
	int i,j;
	float V1[24],aux;

	for(i=0;i<24;i++)
	{
		V1[i]=numdatos[tipo-1].dato[i];
	}
	if(r==1)//Se devide la funcion es dos partes una para un anio y otra para el otro con sus dos sub-partes que sirven para las dos formas distintas
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
	//Recibimos como parametros de entrada la base y la potencia
	int i;
	float aux;
	aux=base;
	if(potencia==0)return 1;//si la potencia es 0 el resultado es 1 por lo que devoldemos ese numero
	for(i=1;i<potencia;i++)//Se multiplica el numero menos uno de la potencia veces la base por el numero original que era la base
	{
		base*=aux;
	}
	return base;
}

int CALCULOESTAD()//Esta funcion sirve para elegir que calculo estadistico se quiere acceder
{

	int i;
	printf("Distintos calculos a elegir:\n");
		for(i=0;i<4;i++)//Este for no es imprescindible ya que se puede hacer manualmente con printfs pero es mas rapido asi
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

int validarOpcion()//La funcion que nos permite averiguar si lo introducido es valido o no
{
	char c,resp[BUFFERTAMANOMAX];//Ponemos como dimension la constante que hemos definido esto es el numero-1 de caracteres maximo permitido al introducir algo
	int i=0;		      		//En nuestro programa es igual a 2 ya que no hay ninguna opcion que pida un numero con mas digitos
	fflush(stdin); 				//Pero el fgets nos recoge tambien el retorno de carro por lo que vamos a poner dimension 4 para incluirlo e incluir '\0'
    fgets(resp,4,stdin);//Recogemos la cadena

	while(resp[i]!='\0')//Lo primero que vamos a hacer es encotrar un caracter en nuestro string si lo hay
	{					//Si hemos puesto como maximo dos numeros por ejemoplo, puede haber solo un caracter en nuestro string y es el retorno de carro
						//estaria en la tercera posicion
		c=resp[i];
		if(!(c>47 && c<58))//Este if se activa cuando encuentra un caracter que no sea un numero, incluye cualquier digito en la tabla ascii
		{
			if(c=='\n')
			{
				resp[i]='\0';/*Aqui encontramos el retorno de carro y lo cambiamos a '\0'
							 ya que si hemos entrado en este if es porque no ha encotrado ningun otro caracter y lo anterior es todo numero aceptable*/
				return atoi(resp);
			}
			else return -1;//Si encuentra otro caracter sabemos inmediatamente que la opcion es incorrecta y retornamos un -1 NO un 0 ya que es valido tambien
		}
		i++;
	}
	i=0;
	while(resp[i]!='\0')//Si el primer while no ha encontrado ningun caracter podria ser que nuestro numero introducido sea de mas de dos digitos
	{
		i++;//Un simple contador de digitos y si es mayor que dos retornamos opcion incorrecta
	}
	if(i>2)
	{
		return -1;
	}
	return atoi(resp);//Si todo ha ido bien retorna el numero convertido en int aun asi podria ser un numero de dos digitos y ser mayor que nuestras opciones
}					  //En ese caso la opcion incorrecta la detecta la otra funcion

int pregunta_calculos(int s)
{
	//Esta es nuestra funcion mas larga esta dividida en 4 partes para las distintas estadisticas que hay
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
// En este caso diseñamos unas funciones para calcular los cuartiles:

  //Prototipos

/*
 int main(){

  int n, i;

   printf("Ingrese el numero de datos: ");
   scanf("%d", &n);
   int *arr = (int *)malloc(n * sizeof(int)); // Lo usamos para reservar la memoria para después el arreglo dinámico

   printf("Ingrese los datos:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }


 ordenar2(arr, n); // Ordena el arreglo en orden ascendente

    float primerCuartil = calcularPrimerCuartil(arr, n);
    float segundoCuartil = calcularSegundoCuartil(arr, n);

    printf("Primer Cuartil: %.2f\n", primerCuartil);
    printf("Segundo Cuartil: %.2f\n", segundoCuartil);

    free(arr); // Libera la memoria del arreglo dinámico

    return 0;
}



// Función para calcular el primer cuartil
float calcularPrimerCuartil(int anio, int gener) {
    int i,j;
    float cuartil;
    *ptr=v1
    int anio,gener;
    posicion = 12 / 4; // Ver la posición del primer cuartil

    return cuartil;
}

// Funcion para calcular el segundo cuartil

float calcularTercerCuartil(int arr[], int n) {
    float cuartil;
    if (n % 2 == 0) { // Si el número de elementos es par
        cuartil = (arr[n / 2 - 1] + arr[n / 2]) / 2.0; // Calcula el promedio de los dos valores del centro
    } else { // Si el número de elementos es impar
        cuartil = arr[n / 2]; // Obtiene directamente el valor del centro
    }
    return cuartil;
}
*/
int Menu_Comparacion()
if(r==1)//Si hemos pedido la media del primer anio hacemos el calculo con los 12 primeros datos
	{
			for(i=0;i<12;i++)
			{
				   printf("Cogemos datos del primer año")	//Hacemos el sumatorio de los datos de la generacion "y"
				//printf("%f\t",media);
			}
	   printf(Cogemos datos del primer a)
	}
	else if(r==2)//si es el segundo anio el calculo es desde el dato 13 que seria enero de 2022(segundo anio) para el ordenador es el 12
	{
		for(i=12;i<24;i++)
			{
				media+=numdatos[x].dato[i];
				//printf("%f\t",media);
			}
	}
	return 0;
}

switch(z)
        {
    	    case 1:
    	   		MENU_Comparacion_primeraño();
				return 0;
            break;
    	    case 2:
    	    	MENU_Comparacion_segundoaño();
    	    	return 0;
    		break;
    		case 3:
    			MENU_Comparacion_todo();
    			return 0;
			break;

		}

int Menu_Comparacion_segundoaño();

    printf("----------------------------------------------MENU PRINCIPAL>>ORDENAR-----------------------------------------------");
	printf("\nTipos de generacion a acceder:\n");
    MOSTRARTIPOS(0);
    printf("\n---> Para volver la menu principal pulsa 0 <---\n");


int i;
char e=validarOpcion;

int validarOpcion()//La funcion que nos permite averiguar si lo introducido es valido o no
{
	char c,resp[BUFFERTAMANOMAX];//Ponemos como dimension la constante que hemos definido esto es el numero-1 de caracteres maximo permitido al introducir algo
	int i=0;		      		//En nuestro programa es igual a 2 ya que no hay ninguna opcion que pida un numero con mas digitos
	fflush(stdin); 				//Pero el fgets nos recoge tambien el retorno de carro por lo que vamos a poner dimension 4 para incluirlo e incluir '\0'
    fgets(resp,4,stdin);//Recogemos la cadena

	while(resp[i]!='\0')//Lo primero que vamos a hacer es encotrar un caracter en nuestro string si lo hay
	{					//Si hemos puesto como maximo dos numeros por ejemoplo, puede haber solo un caracter en nuestro string y es el retorno de carro
						//estaria en la tercera posicion
		c=resp[i];
		if(!(c>47 && c<58))//Este if se activa cuando encuentra un caracter que no sea un numero, incluye cualquier digito en la tabla ascii
		{
			if(c=='\n')
			{
				resp[i]='\0';/*Aqui encontramos el retorno de carro y lo cambiamos a '\0'
							 ya que si hemos entrado en este if es porque no ha encotrado ningun otro caracter y lo anterior es todo numero aceptable*/
				return atoi(resp);
			}
			else return -1;//Si encuentra otro caracter sabemos inmediatamente que la opcion es incorrecta y retornamos un -1 NO un 0 ya que es valido tambien
		}
		i++;
	}
	i=0;
	while(resp[i]!='\0')//Si el primer while no ha encontrado ningun caracter podria ser que nuestro numero introducido sea de mas de dos digitos
	{
		i++;//Un simple contador de digitos y si es mayor que dos retornamos opcion incorrecta
	}
	if(i>2)
	{
		return -1;
	}
	return atoi(resp);//Si todo ha ido bien retorna el numero convertido en int aun asi podria ser un numero de dos digitos y ser mayor que nuestras opciones
}					  //En ese caso la opcion incorrecta la detecta la otra funcion


