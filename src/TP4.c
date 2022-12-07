/*
 ============================================================================
 Name        : TP4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkedList.h"


typedef struct{
int id;
char nombre[50];
char sexo;
float altura;
}ePersona;


int mostrarPersona(ePersona* persona);
int mostrarPersonas(LinkedList* lista);
int compararNombre(void* a, void* b);
ePersona* new_Persona();
ePersona* new_PersonaParam(int id, char* nombre, char sexo, float sueldo);

void destroyPersona(ePersona* pEmpleado);

int personaSetId(ePersona* pEmpleado, int id);
int personaSetNombre(ePersona* pEmpleado, char* nombre);
int personaSetSexo(ePersona* pEmpleado, char sexo);
int personaSetAltura(ePersona* pEmpleado, float altura);

int personaGetId(ePersona* pEmpleado, int* pId);
int personaGetNombre(ePersona* pEmpleado, char* pNombre);
int personaGetSexo(ePersona* pEmpleado, char* pSexo);
int personaGetAltura(ePersona* pEmpleado, float* pAltura);



int main(void) {
	setbuf(stdout,NULL);

	LinkedList* lista = ll_newLinkedList();
	LinkedList* listaClone = ll_newLinkedList();
	int tamLista = -1;
	int indiceTomas = -1;
	ePersona* popPersona;
	ePersona p1 = {100, "Joaquin", 'm', 1.71};
	ePersona p2 = {101, "Raul", 'm', 1.80};
	ePersona p3 = {102, "Fernanda", 'f', 1.66};
	ePersona p4 = {103, "Paloma", 'f', 1.69};
	ePersona p5 = {104, "Gaston", 'm', 1.78};
	ePersona p6 = {105, "Estela", 'f', 1.62};
	ePersona p7 = {106, "Tomas", 'm', 1.80};
	ePersona p8 = {107, "Santino", 'm', 1.70};
	ePersona p9 = {108, "Graciela", 'f', 1.63};

	ll_add(lista, &p1);
	ll_add(lista, &p2);
	ll_add(lista, &p3);
	ll_add(lista, &p4);
	ll_add(lista, &p5);
	ll_add(lista, &p6);

	tamLista = ll_len(lista);
	printf("La lista tiene %d elementos\n", tamLista);

	mostrarPersonas(lista);

	ll_set(lista, 3, &p7);
	printf("Nueva lista ll_set Tomas indice 3\n");
	mostrarPersonas(lista);

	indiceTomas = ll_indexOf(lista, &p7);
	printf("Tomas se encuentra en el indice %d\n", indiceTomas);

	ll_remove(lista, indiceTomas);
	printf("ll_remove de Tomas\n");
	mostrarPersonas(lista);

	ll_push(lista, 5, &p8);
	printf("ll_push Santino en el indice 5\n");
	mostrarPersonas(lista);

	if(ll_isEmpty(lista))
	{
		printf("ll_isEMpty=1 La lista esta vacia\n");
	}
	else
	{
		printf("ll_isEMpty=0 La lista no esta vacia\n");
	}

	popPersona = (ePersona*)ll_pop(lista, 3);
	printf("ll_pop Gaston\n");
	mostrarPersona(popPersona);

	printf("ll_contains de Graciela\n");
	if(!ll_contains(lista, &p9))
	{
		printf("Esa persona no esta en la lista\n");
	}

	listaClone = ll_clone(lista);
	printf("ll_clone de lista\n");
	mostrarPersonas(listaClone);

	printf("ll_containsAll de lista y listaClone\n");
	if(ll_containsAll(lista, listaClone))
	{
		printf("ll_containsAll=1 coinciden\n");
	}
	else
	{
		printf("ll_containsAll=0 no coinciden\n");
	}

	printf("Creo subLista ll_subList from2 t5\n");

	LinkedList* subLista = ll_subList(lista, 2, 5);
	mostrarPersonas(subLista);

	printf("ll_sort de lista por nombre alfabeticamente\n");
	ll_sort(lista, compararNombre, 1);
	mostrarPersonas(lista);

	printf("ll_clear de subLista\n");
	ll_clear(subLista);

	printf("ll_deleteLinkedList de subLista\n");
	ll_deleteLinkedList(subLista);
	return 0;
}


ePersona* new_Persona()
{
    ePersona* nuevaPersona;
    nuevaPersona = (ePersona*) malloc(sizeof(ePersona));

     if(nuevaPersona != NULL)
        {
    	 nuevaPersona->id = 0;
            strcpy(nuevaPersona->nombre, "\n");
            nuevaPersona->sexo = ' ';
            nuevaPersona->altura = 0;
        }
    return nuevaPersona;
}

ePersona* new_PersonaParam(int id, char* nombre, char sexo, float altura)
{
    ePersona* nuevaPersona;

    nuevaPersona = new_Persona();

         if(nuevaPersona != NULL)
        {
            if(!(personaSetId(nuevaPersona, id) &&
                 personaSetNombre(nuevaPersona, nombre) &&
                 personaSetSexo(nuevaPersona, sexo) &&
                 personaSetAltura(nuevaPersona, altura) ))
            {
                free(nuevaPersona);
                nuevaPersona = NULL;
            }
        }
    return nuevaPersona;
}

int compararNombre(void* a, void* b)
{
	int retorno = 0;
	ePersona* persona1 = NULL;
	ePersona* persona2 = NULL;

	if(a != NULL && b != NULL)
	{
		persona1 = (ePersona*) a;
		persona2 = (ePersona*) b;
		retorno = strcmp(persona1->nombre, persona2->nombre);


	}
	return retorno;
}

int mostrarPersonas(LinkedList* lista)
{
	int retorno = 0;
	if(lista != NULL)
	{
		printf("Legajo    Nombre   Sexo   Sueldo\n");
		for(int i = 0; i < ll_len(lista); i++)
		{
			mostrarPersona((ePersona*) ll_get(lista, i));
		}

		printf("\n\n");
		retorno = 1;
	}

	return retorno;
}

int mostrarPersona(ePersona* persona)
{
    int retorno = 0;
    int id;
    char nombre[20];
    char sexo;
    float altura;

    if(persona != NULL)
    {
        if(personaGetId(persona, &id) &&
           personaGetNombre(persona, nombre) &&
           personaGetSexo(persona, &sexo) &&
           personaGetAltura(persona, &altura))
           {
            printf("%d       %-8s   %c    %.2f\n", id, nombre, sexo, altura);
            retorno = 1;
           }

    }
    return retorno;
}



void destroyPersona(ePersona* pPersona)
{
    free(pPersona);
}


int personaSetId(ePersona* pPersona, int id)
{
    int retorno = 0;

    if(pPersona != NULL && id >= 100 && id <= 999)
        {
            pPersona->id = id;
            retorno = 1;
        }else
        {
            printf("ID invalido");
        }

    return retorno;
}

int personaSetNombre(ePersona* pPersona, char* nombre)
{
    int retorno = 0;

    char auxCadena[50];

    if(pPersona != NULL && nombre != NULL && strlen(nombre) > 2 && strlen(nombre) < 50)
        {
            strcpy(auxCadena, nombre);
            auxCadena[0] = toupper(auxCadena[0]);
            strcpy(pPersona->nombre, auxCadena);
            retorno = 1;
        }else
        {
            printf("Nombre invalido");
        }
    return retorno;
}

int personaSetSexo(ePersona* pPersona, char sexo)
{
    int retorno = 0;

    sexo = tolower(sexo);

    if(pPersona != NULL && (sexo == 'm' || sexo == 'f'))
        {
            pPersona->sexo = sexo;
            retorno = 1;
        }else
        {
            printf("Sexo invalido");
        }
    return retorno;
}

int personaSetAltura(ePersona* pPersona, float Altura)
{
    int retorno = 0;

    if(pPersona != NULL && Altura > 0 && Altura < 2)
        {
    	pPersona->altura = Altura;
            retorno = 1;
        }else
        {
            printf("Sueldo invalido");
        }
    return retorno;
}



int personaGetId(ePersona* pPersona, int* pId)
{
    int retorno = 0;

    if(pPersona != NULL && pId != NULL)
        {
            *pId = pPersona->id;
            retorno = 1;
        }
    return retorno;
}

int personaGetNombre(ePersona* pPersona, char* pNombre)
{
    int retorno = 0;

    if(pPersona != NULL && pNombre != NULL)
        {
            strcpy(pNombre, pPersona->nombre);
            retorno = 1;
        }
    return retorno;
}

int personaGetSexo(ePersona* pPersona, char* pSexo)
{
    int retorno = 0;

    if(pPersona != NULL && pSexo != NULL)
        {
            *pSexo = pPersona->sexo;
            retorno = 1;
        }
    return retorno;
}

int personaGetAltura(ePersona* pPersona, float* pAltura)
{
    int retorno = 0;

    if(pPersona != NULL && pAltura != NULL)
        {
            *pAltura = pPersona->altura;
            retorno = 1;
        }
    return retorno;
}
