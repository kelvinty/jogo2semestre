#include "vetor_finais.h"
#include "vetor_itens.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct final {
	int id;
	ItensVetor *itens;
	char *descricao;
	char *historia; 
} Final;

typedef struct vetor_finais {
	int capacidade;
	int tamanho;
	Final *finais;
} FinaisVetor;

Final *criar_final(int _id, char *_descricao, char *_historia) {
	Final *final = (Final*)calloc(1,sizeof(Final));
	
	final->id = _id;
	final->itens = NULL;
	final->descricao = _descricao;
	final->historia = _historia;
	
	return final;
}

void apaga_final(Final **final_ref) {
	Final *final = *final_ref;
	free(final);
	*final_ref = NULL;
}

FinaisVetor *criar_vetor_finais(int capacidade){
	FinaisVetor *vec = (FinaisVetor*) calloc(1,sizeof(FinaisVetor));
	
	vec->tamanho = 0;
	vec->capacidade = capacidade;
	vec->finais = (Final*) calloc(capacidade,sizeof(Final));
	
	return vec;
}

void print_vetor_finais(FinaisVetor *vec){
	for(int i = 0;i < vec->tamanho;i++){
		printf("final:%s, indice:%d\n",vec->finais[i].descricao,i);
	}
}

void apaga_vetor_finais(FinaisVetor **vec_ref){
	FinaisVetor *vec = *vec_ref;
	
	free(vec->finais);
	free(vec);
	
	*vec_ref = NULL;
}

void append_vetor_finais(FinaisVetor *vec, Final *final){
	if(vec->tamanho == vec->capacidade){
		fprintf(stderr,"ERROR in 'append'\n");
		fprintf(stderr,"Vetor cheio'\n");
		exit(EXIT_FAILURE);
	}
	
	vec->finais[vec->tamanho] = *final;

	vec->tamanho++;
}

void remove_final_vetor(FinaisVetor *vec,Final *final){
	if(vec->tamanho > 0) {
		for(int i = 0;i < vec->tamanho;i++){
			if(vec->finais[i].id == final->id) {
				for(int j = i; j < vec->tamanho -1;j++) {
//					printf("\nachou id:%d | item_id:%d",vec->itens[i].id,item->id);
					vec->finais[j] = vec->finais[j+1];
				}	
				vec->tamanho--;
			}
		}
		print_vetor_finais(vec);
	}
}



