#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo
{
	int dato;
	int fe;
	struct nodo *izdo, *dcho;
};
typedef struct nodo Nodo;

void InsertarArbol(Nodo** raiz, int clave, int* h);
Nodo* CrearNodo(int clave);
void rotacionII(Nodo** n, Nodo* n1);
void rotacionDD(Nodo** n, Nodo* n1);
void rotacionID(Nodo** n, Nodo* n1);
void rotacionDI(Nodo** n, Nodo* n1);


int main(int argc, char *argv[]){
	Nodo* raiz;
	int altura;

	raiz = NULL;
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
            InsertarArbol(&raiz, var, &altura);
        }
	}
	fclose(archivo);

	return 0;
}

void InsertarArbol(Nodo** raiz, int clave, int *h)
{
	Nodo* n1;
	if (!(*raiz))
	{
		*raiz = CrearNodo(clave);
		printf("%i\n",((*raiz)->dato));
		*h = 1;
	}
	else if (clave < (*raiz) -> dato)
	{
		printf("%s\n","hola izdo");
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
		printf("%i\n", clave);
		(*h) = 0;
	}
}



Nodo* CrearNodo(int clave)
{
	Nodo* t;
	t = (Nodo*) malloc(sizeof(Nodo));
	t -> dato = clave;
	t -> izdo = t -> dcho = NULL;
	t -> fe = 0;
	return t;
}



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





