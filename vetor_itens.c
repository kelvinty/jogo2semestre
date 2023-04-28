#include "vetor_itens.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct item{
	int id;
	char *nome;
	void *imagem;
	void *mascara;
	int x;
	int y;
	int largura;
	int altura;
} Item;

typedef struct vetor_itens{
	int capacidade;
	int tamanho;
	Item *itens;
} ItensVetor; 

Item *criar_item(int id, char *nome,void *imagem, void *mascara, int x, int y, int largura, int altura) {
	Item *item = (Item*)malloc(sizeof(Item));
	
	item->id = id;
	item->nome = nome;
	item->imagem = imagem;
	item->mascara = mascara;
	item->x = x;
	item->y = y;
	item->largura = largura;
	item->altura = altura;
	
	return item;
}

void apaga_item(Item **item_ref) {
	Item *item = *item_ref;
	free(item);
	*item_ref = NULL;
}

ItensVetor *criar_vetor_itens(int capacidade){
	ItensVetor *vec = (ItensVetor*) calloc(1,sizeof(ItensVetor));
	
	vec->tamanho = 0;
	vec->capacidade = capacidade;
	vec->itens = (Item*) calloc(capacidade,sizeof(Item));
	
	return vec;
}

void print_vetor_itens(ItensVetor *vec){
	for(int i = 0;i < vec->tamanho;i++){
		printf("item:%s, indice:%d\n",vec->itens[i].nome,i);
	}
}

void apaga_vetor_itens(ItensVetor **vec_ref){
	ItensVetor *vec = *vec_ref;
	
	free(vec->itens);
	free(vec);
	
	*vec_ref = NULL;
}

void append_vetor_itens(ItensVetor *vec, Item *item){
	if(vec->tamanho == vec->capacidade){
		fprintf(stderr,"ERROR in 'append'\n");
		fprintf(stderr,"Vetor cheio'\n");
		exit(EXIT_FAILURE);
	}
	
	vec->itens[vec->tamanho] = *item;

	vec->tamanho++;
}

void remove_item_vetor(ItensVetor *vec,Item *item){
	if(vec->tamanho > 0) {
		for(int i = 0;i < vec->tamanho;i++){
			if(vec->itens[i].id == item->id) {
				for(int j = i; j < vec->tamanho -1;j++) {
//					printf("\nachou id:%d | item_id:%d",vec->itens[i].id,item->id);
					vec->itens[j] = vec->itens[j+1];
				}	
				vec->tamanho--;
			}
		}
		print_vetor_itens(vec);
		
	}
	
}



