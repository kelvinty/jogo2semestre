typedef struct vetor_finais FinaisVetor;
typedef struct final Final;

Final *criar_final(int _id, char *_descricao, char *_historia);
void apaga_final(Final **final);
void print_final(Final *final);

FinaisVetor *criar_vetor_finais(int capacidade);

void apaga_vetor_finais(FinaisVetor **vec_ref);
void remove_final_vetor(FinaisVetor *vec,Final *final);
void append_vetor_finais(FinaisVetor *vec, Final *final);
void print_vetor_finais(FinaisVetor *vec);
