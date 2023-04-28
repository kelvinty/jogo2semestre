typedef struct vetor_itens ItensVetor;
typedef struct item Item;

Item *criar_item(int id, char *nome,void *imagem, void *mascara, int x, int y, int largura, int altura);
void apaga_item(Item **item);
void print_item(Item *item);

ItensVetor *criar_vetor_itens(int capacidade);
void apaga_vetor_itens(ItensVetor **vec);
void remove_item_vetor(ItensVetor *vec, Item *item);
int tamanho_vetor_item(const ItensVetor *vec);
int capacidade_vetor_itens(const ItensVetor *vec);
float at_vetor_itens(const ItensVetor *vec, int index);
float get_vetor_itens(const ItensVetor *vec, int index);
void append_vetor_itens(ItensVetor *vec, Item *item);
void set_vetor_itens(ItensVetor *vec, int index,Item *item);
void print_vetor_itens(ItensVetor *vec);
