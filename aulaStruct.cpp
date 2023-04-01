#include <stdio.h>
#include <stdlib.h>

struct TDados {
	int a;
	int b;
	int c;
	double x;
	double y;
};

void mostraVetor(TDados *vec,int tamanhoV) {
	for(int i = 0;i < tamanhoV;i++){
		printf("Vetor[%d]: [%d, %d, %d, %.2lf, %.2lf]\n",i,vec[i].a, vec[i].b, vec[i].c, vec[i].x, vec[i].y);
	}
}

int main () {
	int TamV;
	TDados aux;
	TDados *V;
	FILE *Arquivo;
	
	Arquivo = fopen("dados.txt","r");
	TamV = 0;
	V = NULL;
	while (fscanf(Arquivo, "%d;%d;%d;%lf;%lf",&aux.a,&aux.b,&aux.c,&aux.x,&aux.y) != EOF) {
		TamV++;
		V = (TDados *) realloc(V,sizeof(TDados)*TamV);
		V[TamV - 1] = aux; 
	}
	
	mostraVetor(V,TamV);
	
	free(V);
}
