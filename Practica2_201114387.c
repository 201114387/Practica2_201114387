#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

#define GNUPLOT_PATH "/usr/bin/gnuplot"

struct nodo
{
	int dato;
	int fe;
	struct nodo *izdo, *dcho;
};
typedef struct nodo Nodo;
typedef struct nodo Aux;



void InsertarArbol(Nodo** raiz, int clave, int* h);
Nodo* CrearNodo(int clave);
void rotacionII(Nodo** n, Nodo* n1);
void rotacionDD(Nodo** n, Nodo* n1);
void rotacionID(Nodo** n, Nodo* n1);
void rotacionDI(Nodo** n, Nodo* n1);
void InOrden(Nodo** raiz);
void Recorrer_Arbol(Nodo** raiz);

void ordBurbuja(int a[], int n);
void quicksort(int a[], int primero, int ultimo);

void imprimirarray(int b[], int number);

void graficar(char* graf,char* titulo);


int main(int argc, char *argv[]){
	Nodo* raiz;

	Aux* auxiliar;
	int altura;
	raiz = NULL;
	int contador = 0;
	clock_t start = clock();
	clock_t start1 = clock();
	clock_t start2 = clock();
	clock_t start3 = clock();

	int var;
	FILE *archivo;
	char carateres[100];
    archivo = fopen(argv[1],"r"); 

	if(archivo == NULL)
		exit(1);

	while(feof(archivo) == 0)
	{
		fgets(carateres,100,archivo);
		var = atoi(carateres);
		if (var != 0){
            //Insertar(A,val); 
			contador++;
            InsertarArbol(&raiz, var, &altura);
            auxiliar = raiz;
        }
	}
	fclose(archivo);
	printf("Ingresar arbol -  %f %s",((double)clock() - start) / CLOCKS_PER_SEC, "segundos");


	int array[contador];
	int array2[contador];


	int numeros;
	int bandera = 0;
	FILE *archivo1;
	char carateres1[100];
    archivo1 = fopen(argv[1],"r"); 

	if(archivo1 == NULL)
		exit(1);

	while(feof(archivo1) == 0)
	{
		fgets(carateres1,100,archivo1);
		numeros = atoi(carateres1);
		if (numeros != 0){
            //Insertar(A,val); 
            if (bandera < contador)
            {
            	array[bandera] = numeros;
            	array2[bandera] = numeros;
            	bandera++;
            }
        }
	}
	fclose(archivo1);

	printf("\n");
	printf("%s\n", "Datos ingresador");
	imprimirarray(array, contador);
 	printf("\n\n");
 	Recorrer_Arbol(&auxiliar);
 	printf("Recorrido del arbol -  %f %s",((double)clock() - start1) / CLOCKS_PER_SEC, "segundos");
 	printf("\n");
	ordBurbuja(array, contador);
	printf("Ordenado Burbuja -  %f %s", ((double)clock() - start2) / CLOCKS_PER_SEC, "segundos");
	printf("\n");
	quicksort(array2, 0, contador-1);
	printf("Ordenado Quicksort -  %f %s",((double)clock() - start3) / CLOCKS_PER_SEC, "segundos");

	printf("\n\n");

	printf("%s\n", "Salida ordenada Burbuja");
	imprimirarray(array, contador);
	printf("\n");
	printf("%s\n", "Salida ordenada Quicksort");
	imprimirarray(array2, contador);
	printf("\n");
	printf("%s\n", "in orden" );
	InOrden(&auxiliar);

	printf("\n");

	char* g = "plot (x)";
	char* z = "grafica";
	graficar(g, z);

	return 0;
}


/*--------------------------------------------------------------------------------*/
/*---------------------------------Insertar Arbol---------------------------------*/
/*--------------------------------------------------------------------------------*/

void InsertarArbol(Nodo** raiz, int clave, int *h)
{
	Nodo* n1;
	if (!(*raiz))
	{
		*raiz = CrearNodo(clave);
		//printf("%i\n",((*raiz)->dato));
		*h = 1;
	}
	else if (clave < (*raiz) -> dato)
	{
		//printf("%s\n","hola izdo");
		InsertarArbol(&((*raiz) -> izdo), clave, h);

		if (*h)
		{
			switch((*raiz) -> fe)
			{
				case 1: (*raiz) -> fe = 0;
				    (*h) = 0;
				    break;

				case 0: (*raiz) -> fe = -1;
				    break;

				case -1: 
					n1 = (*raiz) -> izdo;
					if (n1 -> fe == -1)
					{
						rotacionII(raiz, n1);
					}
					else
					{
						rotacionID(raiz, n1);
					}

					(*h) = 0;
			}
		}
	}
	else if (clave > (*raiz) -> dato)
	{
		InsertarArbol(&((*raiz) -> dcho), clave, h);

		if (*h)
		{
			switch((*raiz)-> fe)
			{
				case 1: 
					n1 = (*raiz) -> dcho;
					if (n1 -> fe == +1)
					{
						rotacionDD(raiz, n1);
					}
					else
					{
						rotacionDI(raiz, n1);
					}

					(*h) = 0;
					break;

				case 0: (*raiz) -> fe = +1;
					break;

				case -1: (*raiz) -> fe = 0;
					(*h) = 0;
					break;
			}
		}
	}
	else
	{
		puts("claves repetidas");
		(*h) = 0;
	}
}


/*--------------------------------------------------------------------------------*/
/*-----------------------------------Crear Nodo-----------------------------------*/
/*--------------------------------------------------------------------------------*/

Nodo* CrearNodo(int clave)
{
	Nodo* t;
	t = (Nodo*) malloc(sizeof(Nodo));
	t -> dato = clave;
	t -> izdo = t -> dcho = NULL;
	t -> fe = 0;
	return t;
}


/*--------------------------------------------------------------------------------*/
/*----------------------------------Rotacion II-----------------------------------*/
/*--------------------------------------------------------------------------------*/

void rotacionII(Nodo** n, Nodo* n1)
{
	(*n) -> izdo = n1 -> dcho;
	n1 -> dcho = (*n);

	if (n1 -> fe == -1)
	{
		(*n) -> fe = 0;
		n1 -> fe = 0;
	}
	else
	{
		(*n)-> fe = -1;
		n1 -> fe = 1;
	}

	(*n) = n1;
}


/*--------------------------------------------------------------------------------*/
/*----------------------------------Rotacion DD-----------------------------------*/
/*--------------------------------------------------------------------------------*/

void rotacionDD(Nodo** n, Nodo* n1)
{
	(*n) -> dcho = n1 -> izdo;
	n1 -> izdo = (*n);

	if (n1 -> fe == +1)
	{
		(*n) -> fe = 0;
		n1 -> fe = 0;
	}
	else
	{
		(*n) -> fe = +1;
		n1 -> fe = -1;
	}

	(*n) = n1;
}


/*--------------------------------------------------------------------------------*/
/*----------------------------------Rotacion ID-----------------------------------*/
/*--------------------------------------------------------------------------------*/

void rotacionID(Nodo** n, Nodo* n1)
{
	Nodo* n2;

	n2 = n1 -> dcho;
	(*n) -> izdo = n2 -> dcho;
	n2 -> dcho = *n;
	n1 -> dcho = n2 -> izdo;
	n2 -> izdo = n1;

	if (n2 -> fe == +1)
	{
		n1 -> fe = -1;
	}
	else
		n1 -> fe = 0;

	if(n2 -> fe == -1)
		(*n) -> fe = 1;
	else
		(*n) -> fe = 0;

	n2 -> fe = 0;
	(*n) = n2;
}


/*--------------------------------------------------------------------------------*/
/*----------------------------------Rotacion DI-----------------------------------*/
/*--------------------------------------------------------------------------------*/

void rotacionDI(Nodo** n, Nodo* n1)
{
	Nodo* n2;

	n2 = n1 -> izdo;
	(*n) -> dcho = n2 -> izdo;
	n2 -> izdo = *n;
	n1 -> izdo = n2 -> dcho;
	n2 -> dcho = n1;

	if(n2 -> fe == +1)
		(*n) -> fe = -1;
	else
		(*n) -> fe = 0;

	if(n2 -> fe == -1)
		n1 -> fe = 1;
	else
		n1 -> fe = 0;

	n2 -> fe = 0;
	(*n) = n2;
}


/*--------------------------------------------------------------------------------*/
/*-------------------------------Recorrido InOrden--------------------------------*/
/*--------------------------------------------------------------------------------*/
void InOrden(Nodo** raiz)
{
	if ((*raiz) != NULL)
	{
		InOrden(&((*raiz) -> izdo));
		printf("%i ", ((*raiz) -> dato));
		InOrden(&((*raiz) -> dcho));
	}
}


void ordBurbuja(int a[], int n)
{
	int interruptor = 1;
	int pasada, j;

	for(pasada = 0; pasada < n-1 && interruptor; pasada++)
	{
		interruptor = 0;
		for(j = 0; j< n-pasada-1; j++)
		{
			if (a[j] > a[j+1])
			{
				int auxbur;
				interruptor = 1;
				auxbur = a[j];
				a[j] = a[j+1];
				a[j+1] = auxbur;
			}
		}
	}
}

void quicksort(int a[], int primero, int ultimo)
{
	int i, j, central;
	int pivote;

	central = (primero + ultimo)/2;
	pivote = a[central];
	i = primero;
	j = ultimo;

	do
	{
		while(a[i] < pivote) i++;
		while(a[j] > pivote) j--;

		if (i <= j)
		{
			int tmp;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
	}while(i <= j);

	if (primero < j)
	{
		quicksort(a, primero, j);
	}

	if (i < ultimo)
	{
		quicksort(a, i, ultimo);
	}
}

void imprimirarray(int b[], int number)
{
	int k;
	for(k = 0; k < number; k++)
	{
		printf("%i ", b[k]);
	}
}


void graficar(char* graf,char* titulo)
{
   FILE *gp;
   gp = popen(GNUPLOT_PATH,"w");
   if (gp == NULL)
   {
        fprintf(stderr,"Archivo No Encontrado %s",GNUPLOT_PATH);
   }
   else
   {
        fprintf(gp,"set title '%s' \n",titulo);
        fprintf(gp,"%s \n",graf);
        fflush(gp);
        getchar();
        pclose(gp);
   }
}


void Recorrer_Arbol(Nodo** raiz)
{
	if ((*raiz) != NULL)
	{
		Recorrer_Arbol(&((*raiz) -> izdo));
		Recorrer_Arbol(&((*raiz) -> dcho));
	}
}



