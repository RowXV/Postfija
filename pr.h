#ifndef PR_H
#define PR_H
#define TAM 20 // definir el tamaño de la expresion tanto infija como posfija 

#include <stdio.h>
#include <string.h>


typedef struct _array array;

struct _array // pila 
{

	int t;

	char a[TAM];
};



static int m[6][7]={ 
//variable estatica para ir comparando cada uno de los elementos de la cadena con la prioridad de los operadores

        {1, 1, 0, 0, 0, 0, 1},

        {1, 1, 0, 0, 0, 0, 1},

        {1, 1, 1, 1, 0, 0, 1},

        {1, 1, 1, 1, 0, 0, 1},

        {1, 1, 1, 1, 1, 0, 1},

        {0, 0, 0, 0, 0, 0, 0}
};

void inpos(char *in, char *pos); // conversion de infija a posfija
int op(char c); // pa separar operadores de operandos
int prioridad(char op1, char op2); // se asigna prioridad a los operadores
char tope(array l); // pa la informacion de la cadena y su posicion
void inicio(array *l); // inicia el array 
int es_vacia(array *l); // verifica si la pila esta vacia
void push(array *l, char s); // insertar en la pila
void pop(array *l, char *s); // sacar de la pila
void imprimir(char *in, char *pos); // imprime la infija y postfija
void guardar(char *pos); // hace archivo de texto 
float evaluar(char *eva); // evaluacion aritmetica

// usando una pila
int pope(); //evaluacion de la funcion pos
int pushe(int n); //evaluacion de la funcion pos 




#endif