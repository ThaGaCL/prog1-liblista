#ifndef _LIBlista_t_H
#define _LIBlista_t_H
#include <stdlib.h>
#include <stdio.h>
#include "liblista.h"

struct nodo_l {
    int elemento;       /* lista de numeros inteiros */
    struct nodo_l* prox;  /* ponteiro para o proximo   */
};
typedef struct nodo_l nodo_l_t;

struct lista {
    nodo_l_t* ini;      /* ponteiro para o inicio da lista */
    int tamanho;        /* numero de elementos na lista    */
};
typedef struct lista lista_t;

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t* lista_cria ()
{
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista==NULL)
        return NULL;
    lista->ini=NULL;
    lista->tamanho=0;
    return lista;    
};

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t* l)
{
    if((l->tamanho==0)||(l->ini==NULL))
        return 1;
    return 0;
};

/*
 * Remove todos os elementos da lista, libera espaco e retorna NULL.
*/
lista_t* lista_destroi (lista_t* l)
{
    /*existe algum erro que eu não consegui identificar aqui*/
    /*o malloc de alguns elementos não são libereados*/
    if(lista_vazia(l)!=0)
    {
        nodo_l_t* aux;
        /*aux2 vai segurar a proxima posição*/
        nodo_l_t* aux2;
        for(aux=l->ini; aux!=NULL; aux=aux2)
        {
            aux2=aux->prox;
            aux->prox=NULL;
            aux->elemento=0;
            free(aux);
            /*coloca o elemento como 0 e seta o ponteiro para o proximo elemento como nulo*/
        }

        l->tamanho=0;
    }
    /*libera a memoria alocada pela lista*/
    free(l);
    return NULL;
};


/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int lista_tamanho (lista_t* l)
{
    return l->tamanho;
};

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_inicio (lista_t* l, int elemento)
{
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    if(nodo == NULL)
        return 0;
    /*se a lista esta vazia inicio recebe o novo nodo*/
    if(lista_vazia(l)==1)
        l->ini=nodo;
    else
    {
    /*se não o proximo nodo recebe o atual inicio e o inicio se torna o novo nodo*/
        nodo->prox=l->ini;
        l->ini=nodo;
    }
    l->tamanho++;
    nodo->prox=l->ini->prox;
    nodo->elemento=elemento;
    return 1;
};

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_fim (lista_t* l, int elemento)
{
    nodo_l_t* nodo = malloc(sizeof(nodo_l_t));
    nodo_l_t* aux;
    if(nodo == NULL)
        return 0;
    /*se a lista esta vazia inicio = fim, logo inicio recebe o novo nodo*/
    if(lista_vazia(l)==1)
        l->ini=nodo;
    else
    {
        /*percorre a lista até o penultimo elemento*/
        /*aux->prox aponta pro ultimo e o ultimo recebe o nodo*/
        for(aux=l->ini;aux->prox!=NULL; aux=aux->prox);
        aux->prox=nodo;
    }
    l->tamanho++;    
    nodo->prox=NULL;
    nodo->elemento=elemento;
    return 1;
};

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t* l, int elemento)
{
    /*função não implementada*/
    return 1;
};

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_inicio (lista_t* l, int* elemento)
{
    if(lista_vazia(l)==1)
        return 0;
    else
    {
        /*salva um ponteiro pro primeiro elemento para liberar a memoria após a remoção*/
        nodo_l_t* aux = l->ini;
        *elemento=l->ini->elemento;
        l->ini->elemento=0;
        l->ini=l->ini->prox;
        free(aux);
    }
    return 1;
};

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int lista_retira_fim (lista_t* l, int* elemento)
{
    nodo_l_t* aux;
    if(lista_vazia(l)==1)
        return 0;

    /*se a lista esta vazia inicio=fim, remove o primeiro elemento*/
    if(lista_tamanho(l)==1)
    {
        l->ini->elemento=0;
        l->ini=NULL;
        l->tamanho--;
        free(l->ini);    
        return 1;
    }
    /*percorre o vetor até o antepenultimo elemento*/
    /*outra maneira de salvar o ponteiro pro elemento*/
    for(aux=l->ini;aux->prox->prox!=NULL; aux=aux->prox);
    *elemento=aux->prox->elemento;     
    aux->prox->elemento=0;   
    aux->prox=NULL;
    free(aux->prox);   
    l->tamanho--;    
    
    return 1; 
};


/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int lista_pertence (lista_t* l, int elemento){
    if((lista_vazia(l)!=1))
    {
        nodo_l_t* aux;
        for(aux=l->ini;aux!=NULL; aux=aux->prox)
        {
            if(aux->elemento==elemento)
                return 1;
        }
    }
    return 0;
};
/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int lista_retira_elemento (lista_t *l, int *elemento)
{
    nodo_l_t* aux;
    /*se a lista não tem o elemento retorna 0*/
    if(lista_pertence(l,*elemento)==0)
        return 0;
    /*se a lista tem 1 elemento e ele é o elemento procurado remove ele e libera o inicio*/
    if((lista_tamanho(l)==1)&&(l->ini->elemento==*elemento)){
        l->ini=0;
        l->ini=NULL;
        free(l->ini);
        l->tamanho--;
        return 1;
    }
    /*checa se o inicio é o elemento procurado e se sim o remove*/
    if(l->ini->elemento==*elemento){
        l->ini->elemento=0;
        aux=l->ini;
        l->ini=l->ini->prox;
        free(aux);
        l->tamanho--;
        return 1;
    }
    /*percorre a lista completa e procura em qual posição esta o elemento*/
    for(aux=l->ini;aux!=NULL; aux=aux->prox){
        if(aux->prox->elemento==*elemento)
        {
            aux->prox->elemento=0;
            /*checa se é necessario mover o proximo elemento para a posição do removido*/
            if(aux->prox->prox!=NULL)
            {
                aux->prox=aux->prox->prox;
            }
            else
            {
                aux->prox=NULL;
                free(aux->prox);
            }
            break;
        }
    }
    l->tamanho--;
    return 1;
};


/*
 * Imprime a lista, do inicio ate o fim, este por ultimo, sem espaco no final.
 * Quando a lista estiver vazia, nao imprime nada, nem um \n.s
*/
void lista_imprime (lista_t* l)
{
    if((lista_vazia(l)!=1))
    {
        nodo_l_t* aux;
        /*percorre a lista até o penultimo vetor para imprimir o ultimo sem espaço vazio*/
        for(aux=l->ini;aux->prox!=NULL; aux=aux->prox)
        {
            printf("%d ",aux->elemento);
        }

        printf("%d\n",aux->elemento);
    }
};



#endif