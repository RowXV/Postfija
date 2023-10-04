#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "PR.h"


int main(int argc, char *argv[])
{

    char pos[TAM], *in; // para entrada y salida de las cadenas
    int i;             // para aplicar la funcion strlen
    char *valor;

    in = *++argv; // para pasar infomracion de argv a in ,

    i = strlen(in); // le da el valor a i del total de caracteres de la cadena
    in[i] = '\0';   // para diferenciar operadores de operandos

    inpos(in, pos);    // realiza la comparacion de caracteres y la conversion de infija a posfija
    imprimir(in, pos); // imprime los resultados
    guardar(pos);
    printf("\n");

    for (int j = 0; j < i; j++) // asigna valores a las variables de la expresion posfija
    {
        if (op(pos[j])) // excluye a los operadores
        {
            fflush(stdin);
            printf("El valor para %c es:\n", (pos[j]));
            scanf("%s", &valor[j]); //guarda valores en las variables de la expresion posfija
        }
        else
        {
            valor[j] = pos[j]; //guarda los operadores en el mismo orden
        }
    }

    evaluar(valor); // evalua la expresion posfija ya con valores y devuelve el resultado 
    return 0;
}

int pila[TAM]; // pila para formar
int top = -1;  // y poder evaluar la notacion posfija 

float evaluar(char *eva)  
{
    int i, a, b, resultado, ev;
    char ch;
    for (i = 0; eva[i] != '\0'; i++)
    {
        ch = eva[i]; // iguala caracter por caracter para determinar si es operador u operando 

        if (isdigit(ch))
        {
            pushe(ch - '0'); // inserta en la pila de evaluacion si es un operando
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^')
        {
            b = pope(); // saca de la pila  si es un operador 
            a = pope();

            switch (ch) // se utiliza para realizar las operaciones aritmeticas necesarias
            {
            case '+':
                resultado = a + b;
                break;
            case '-':
                resultado = a - b;
                break;
            case '*':
                resultado = a * b;
                break;
            case '/':
                resultado = a / b;
                break;
            case '%':
                resultado = a % b;
                break;
            case '^':
                resultado = pow(a, b);
                break;
            }
            pushe(resultado); // mete el resultado de las operaciones a la pila 
        }
    }

    ev = pope(); // saca lo que haya en la pila y lo iguala a ev 

    printf("\nLa operacion aritmetica de la notacion posfija es: %d\n", ev); // imprime a ev que es el resultado de las operaciones aritmeticas 

    return 0;
}

void inpos(char *in, char *pos)
{

    array l;
    int i, j;
    char aux;
    i = 0;
    j = -1;

    inicio(&l);

    while (in[i] != '\0')
    {

        if (op(in[i])) // si es operando y no operador
        {
            pos[++j] = in[i++]; // preincremento en posfija e incremento en infija
        }
        else
        {
            while (!es_vacia(&l) && prioridad(tope(l), in[i])) // mientas no sea vacia se meten y sacan elementos a la pila
            {
                pop(&l, &aux);
                pos[++j] = aux;
            }
            if (in[i] == ')')
            {
                pop(&l, &aux);
            }
            else
            {
                push(&l, in[i]);
            }
            i++;
        }
    }

    while (!es_vacia(&l)) // si no esta vacia, sacamos lo que haya de la pila
    {
        pop(&l, &aux);
        pos[++j] = aux;
    }
    pos[++j] = 0;
}

int op(char c) // para filtrar operandos de operadores
{
    return (c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != ')' && c != '(' && c != '%' && c != '\0');
}

int prioridad(char op1, char op2) // aqui se ordena dandole valores de 0 a 5 dependiendo la prioridad de cada operando
{

    int i, j;

    switch (op1)
    {
    case '+':
        i = 0;
        break;
    case '-':
        i = 1;
        break;
    case '*':
        i = 2;
        break;
    case '%':
        i = 2;
        break;
    case '/':
        i = 3;
        break;
    case '^':
        i = 4;
        break;
    case '(':
        i = 5;
        break;
    }

    switch (op2)
    {

    case '+':
        j = 0;
        break;
    case '-':
        j = 1;
        break;
    case '*':
        j = 2;
        break;
    case '%':
        j = 2;
        break;
    case '/':
        j = 3;
        break;
    case '^':
        j = 4;
        break;
    case '(':
        j = 5;
        break;
    case ')':
        j = 6;
        break;
    }
    return (m[i][j]); // se va a la variable estatica
}

char tope(array l)
{
    return (l.a[l.t - 1]); // la informacion del entero y char de array
}

void inicio(array *l) // inicio la pila
{
    l->t = 0;
}

int es_vacia(array *l) // comprobar si esta vacia
{
    return (!l->t);
}

void imprimir(char *in, char *pos) // imprime los resultados
{
    printf("La cadena infija es: %s\nLa cadena postfija es: %s  ", in, pos);
}

void guardar(char *pos) // guarda los resultados de posfija en un archivo de texto 
{
    int x;
    printf("\nDesea guardar la notacion postfija?\n1)Si\n2)No\n");
    scanf("%d", &x);

    if (x == 1)
    {
        FILE *arch;
        arch = fopen("Postfija.txt", "wt");
        fputs(pos, arch);
        fclose(arch);
    }
    else if (x == 2)
    {
        printf("Terminando");
    }
    else
    {
        printf("Opcion incorrecta");
    }
}

void push(array *l, char s) // insertar push para in a pos
{

    if (l->t == TAM)
    {
        printf("La pila esta llena\n"); // llego al tope de la pila
    }
    else
    {
        l->t++;
        l->a[l->t - 1] = s; // se va reduciendo el espacio en la pila
    }
}

void pop(array *l, char *s) // remover pop de in a pos 
{

    if (es_vacia(l))
    {
        printf("la pila esta vacia\n");

        *s = '\0';
    }

    else
    {

        *s = l->a[l->t - 1];

        l->t--;
    }
}

int pushe(int n)// mete a la pila, es para la evaluacion de la posfija
{
    if (top < TAM - 1)
    {
        pila[++top] = n;
    }
    else
    {
        printf("Pila llena\n");
        exit(-1);
    }
}

int pope() // sacar de la pila, es para la evaluacion de la posfija
{
    int n;
    if (top > -1)
    {
        n = pila[top];
        pila[top--] = -1;
        return n;
    }
    else
    {
        printf("Pila llena\n");
        exit(-1);
    }
}