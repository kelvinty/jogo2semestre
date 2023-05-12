#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <string.h>

//STRUCTS

struct TMouse{
	int x;
	int y;
	int largura;
	int altura;
};

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

struct TInventario {
	int maxItens;
	int qtdItens;
	ItensVetor *itens;
	int x;
	int y;
};

typedef struct saida {
	int id;
	char* nome;
	int x;
	int y;
	int largura;
	int altura;
	FinaisVetor *finais;
}Saida;

struct TCamera {
	int id;
	int qtdItens;
	void *imagem;
	ItensVetor *itens;
	Saida *saida;
};

//FUNCOES E VARIAVEIS GLOBAIS
int pg = 1;
int last_time = clock();

void* load_image(const char *endereco, int largura, int altura, int x, int y){
	int aux = imagesize(x,y,largura,altura);
	void*img = malloc(aux);
	readimagefile(endereco, x, y, largura, altura);
	getimage(x, y, largura, altura, img);
	return img;
}

int strlen(char *str)
{
    int total=0;
    while( str[total] != '\0'){
    	total++;
	}    
    return total;
}

void animacao_texto(char *texto,int quebra_linha,int qtd,int pos_x,int pos_y) {
	
	double larguraString = textwidth(texto);
	int alturaString = textheight(texto);
	int qtdLetrasTexto = strlen(texto);
	
	int larguraLetras = larguraString/qtdLetrasTexto;
	
	int larguraTexto = qtdLetrasTexto*larguraLetras;
	
	int qtdLinhas = ceil(larguraString/quebra_linha);
	int qtdLetras = quebra_linha/larguraLetras;
	
	char **linha = (char**)malloc(sizeof(char*)*qtdLinhas);
	char *str = (char*)malloc(sizeof(char)*qtdLinhas);
  	char *newStr = (char*)malloc(sizeof(char)*qtdLetras);
  	
  	for(int k = 0;k < qtdLinhas;k++) {
  		for(int j = 0; j < qtdLetras;){
  			str[j] = texto[j+ (k*qtdLetras)];
			str[j+1] = '\0';
			j++;
		}
		linha[k] = (char*)malloc(sizeof(char)*(qtdLetras+1));
		strcpy(linha[k], str);
	}

   	for (int i = 0; i < qtdLinhas;i++) {
   		if(pg == 1) pg = 2; else pg = 1;
	 	setvisualpage(pg);

   		for(int l = 0; l < qtdLetras;){
   			if(pg == 1) pg = 2; else pg = 1;
			newStr[l] = linha[i][l];
			newStr[l+1] = '\0';
			outtextxy(pos_x ,pos_y + (i*alturaString),newStr);
			delay(50);
			setactivepage(pg);
			l++;
		}
        outtextxy(pos_x, pos_y + (i*alturaString), linha[i]);
    	setactivepage(pg);
	}
	
	free(str);

	for(int i = 0; i < qtdLinhas; i++) {
		free(linha[i]);	
	}
	free(linha);
	linha = NULL;
	free(newStr);

}

void deleteImage(void *image){
	free(image);
}

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


TMouse *mousePos(){
	TMouse *mouse = (TMouse*)malloc(sizeof(TMouse));
	if(!ismouseclick(WM_LBUTTONDOWN)){
		mouse->x = mousex();
		mouse->y = mousey();
		clearmouseclick(WM_LBUTTONDOWN);
	} 
	if(ismouseclick(WM_LBUTTONDOWN)){
		mouse->x = mousex();
		mouse->y = mousey();
		clearmouseclick(WM_LBUTTONDOWN);
	}
	return mouse;
}


TInventario *criar_inventario(int x, int y) {
	TInventario *inventario = (TInventario*)calloc(1,sizeof(TInventario));
	
//	inventario->maxItens = maxItens;
//	inventario->qtdItens = qtdItens;
	inventario->x = x;
	inventario->y = y;
	inventario->itens = NULL;
	
	return inventario;
}



Saida *criarSaida(int _id,char*_nome,int _x, int _y,int largura, int altura) {
	Saida *saida = (Saida*)calloc(1,sizeof(Saida));
	
	saida->id = _id;
	saida->nome = _nome;
	saida->x = _x;
	saida->y = _y;
	saida->largura = largura;
	saida->altura = altura;
	saida->finais = NULL;
	
	return saida;
}


//CRUD CAMERA

TCamera *criarCamera(int _id,void*_imagem) {
	TCamera *camera = (TCamera*) calloc(1,sizeof(TCamera));
	
	camera->imagem = _imagem;
	camera->id = _id;
	camera->itens = NULL;
	camera->saida = NULL;
	
	return camera;
}

void mostrarCamera(const TCamera *camera) {
	putimage(0,0,camera->imagem,COPY_PUT);
}

void mostrarItensCamera(const TCamera *camera) {
	for(int i =0;i < camera->itens->tamanho;i++) {
		Item item = camera->itens->itens[i]; 
		putimage(item.x, item.y, item.mascara, AND_PUT);
		putimage(item.x, item.y, item.imagem, OR_PUT);
	}
}

void mostrarSaidasCamera(const TCamera *camera) {
	Saida *saida = camera->saida; 
	if(saida != NULL){
//		bar(saida->x,saida->y,saida->largura,saida->altura);
		rectangle(saida->x,saida->y,saida->largura + saida->x,saida->altura+ saida->y);
	}
//	putimage(item.x, item.y, item.mascara, AND_PUT);
//	putimage(item.x, item.y, item.imagem, OR_PUT);
	
}

void mostrarInventario(const TInventario *inventario) {
	for(int i =0;i <= inventario->itens->capacidade;i++){
		bar(inventario->x,inventario->y+(i*100),inventario->x+100,inventario->y+i+1*100);
	}
//	putimage(0,0,camera->imagem,COPY_PUT);
}

void mostrarItensInventario(const TInventario *inventario) {
	for(int i =0;i < inventario->itens->tamanho;i++) {
		Item item = inventario->itens->itens[i]; 
		putimage(inventario->x, inventario->y + item.altura*i, item.mascara, AND_PUT);
		putimage(inventario->x, inventario->y + item.altura*i, item.imagem, OR_PUT);
	}
}


void removeItensCamera(TCamera *camera) {
	for(int i =0;i<camera->qtdItens;i++) {
		Item *item = camera->itens->itens; 
		free(item->imagem);
		free(item->mascara);
		free(item);
	}
}

bool clicou = false;
//

//
bool verificaMouseClick() {
	int x;
	int y;
	bool clicou = false;
	if(ismouseclick(WM_LBUTTONDOWN)){
		getmouseclick(WM_LBUTTONDOWN,x,y);
		clearmouseclick(WM_LBUTTONDOWN);
		clicou = true;
	}
	return clicou;
}


void pegarItem(Item *_item, TCamera *camera, TInventario *inventario){

	for(int i = 0;i<camera->itens->tamanho;i++){
		Item item = camera->itens->itens[i];
		if(item.id == _item->id){
			Item item = camera->itens->itens[i];
			remove_item_vetor(camera->itens,&item);
			append_vetor_itens(inventario->itens,&item);
		}
	}

}

void colisaoMouseItens(TMouse *mouse,TCamera camera, TInventario *inventario) {
	
	POINT P;
  	HWND janela;
  	janela = GetForegroundWindow();
  	
  	if (GetCursorPos(&P)) // captura a posição do mouse. A variável P é carregada com coordenadas físicas de tela
        if (ScreenToClient(janela, &P)) 
  	
	for(int i = 0;i<camera.itens->tamanho;i++) {
		Item item = camera.itens->itens[i];

		if (P.x < item.x + item.largura && P.x > item.x && P.y < item.y + item.altura && P.y > item.y) {
			int largura_texto = textwidth(item.nome);
			outtextxy(item.x + ((item.largura/2) - (largura_texto/2)), item.y+item.altura,item.nome);
			delay(50);
    		if(GetKeyState(VK_LBUTTON)&0x80){
    			pegarItem(&item,&camera,inventario);
			}

		}
	}
	
}

void colisaoMouseSaidas(TMouse *mouse,TCamera camera, TInventario *inventario) {
	
	POINT P;
  	HWND janela;
  	janela = GetForegroundWindow();
  	
  	if (GetCursorPos(&P))
        if (ScreenToClient(janela, &P)) 
  	
	if(camera.saida != NULL) {
		Saida *saida = camera.saida;

		if (P.x < saida->x + saida->largura && 
			P.x > saida->x && 
			P.y < saida->y + saida->altura && 
			P.y > saida->y) 
		{
			int largura_texto = textwidth(saida->nome);
			int altura_texto = textheight(saida->nome);
			outtextxy(saida->x + ((saida->largura/2) - (largura_texto/2)), saida->y + ((saida->altura/2) - (altura_texto/2)),saida->nome);
			
			delay(50);
    		if(GetKeyState(VK_LBUTTON)&0x80){
    			printf("clicou");
    			printf("clicou na saida:%s\n", saida->nome);	
			}	
		}	
	}	
}

void mudarDeCamera(int *camera_atual,int *tecla) {
	if(GetKeyState(VK_LEFT)&0X80) {
		*camera_atual -= 1;
		if(*camera_atual < 0) {
        	*camera_atual = 3;
		}
		delay(200);
	}
	if(GetKeyState(VK_RIGHT)&0X80) {
		*camera_atual += 1;
		if(*camera_atual > 3) {
        	*camera_atual = 0;
		}
		delay(200);
	} 
}

int gt1 = GetTickCount();

//TItem *chave = criarItem(1,"chave","chave.bmp","chave_pb.bmp",200,200,100,100);
//TItem *gasolina = criarItem(2,"gasolina","gasolina.bmp","gasolina_pb.bmp",400,600,50,100);
//TItem *rifle = criarItem(3,"rifle","rifle.bmp","rifle_pb.bmp",400,600,50,100);
//TItem *bala = criarItem(4,"bala","bala.bmp","bala_pb.bmp",400,600,50,100);
//TItem *celular = criarItem(5,"celular","celular.bmp","celular_pb.bmp",400,600,50,100);
//TItem *machado = criarItem(6,"machado","machado.bmp","machado_pg.bmp",400,600,50,100);
//TItem *fosforo = criarItem(7,"fosforo","fosforo.bmp","fosforo_pb.bmp",400,600,50,100);
//TItem *armadilha = criarItem(8,"armadilha","armadilha.bmp","armadilha_pb.bmp",400,600,50,100);

int Conclusao() {
	mciSendString("stop Insetos", NULL, 0, 0);
		
	mciSendString("open .\\assets\\sons\\tecla1.mp3 type MPEGVideo alias tecla1",NULL,0,0);
	mciSendString("open .\\assets\\sons\\tecla2.mp3 type MPEGVideo alias tecla2",NULL,0,0);
	mciSendString("open .\\assets\\sons\\tecla3.mp3 type MPEGVideo alias tecla3",NULL,0,0);
	
	waveOutSetVolume(0,0x88888888);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
	
	int LarTela;
	LarTela = GetSystemMetrics(SM_CXSCREEN) - 500;
	int gt2;
	char *texto = "Você continua a procurar pistas e descobre que a chave do carro que você usou para chegar até a cabana está desaparecida. Sem a chave, você não conseguirá sair dali. De repente, você escuta um som estranho vindo de um dos quartos. Quando entra, vê que a chave do carro está em cima da cama. Ao tentar sair da cabana, você percebe que algo está bloqueando a porta. Então, decide usar o galão de gasolina e o fósforo para criar uma distração e fugir. Depois de algumas tentativas, você finalmente consegue. Quando olha para trás, vê a cabana em chamas e percebe que não estava sozinho ali.";
	
	while(true) {
 		gt2 = GetTickCount();
		if(gt2 - gt1 > 1000/60) {	
			animacao_texto(texto,LarTela,583,50,50);
		}
	}
}

int Comeca_Jogo(){
	
	int gt2;
	
    int tecla = 0;
	int camera_atual = 0;
	int qtdCam = 0;
	int LarTela,AltTela;
	
	LarTela = 1280;
	AltTela = 720;
	
	setlocale(LC_ALL,"Portuguese");
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
	
	
	TMouse *mouse = mousePos();

//	TInventario *inventario = (TInventario*)malloc(sizeof(TInventario)*1);
//	inventario->itens = (TItem*)malloc(sizeof(TItem)*2); 

	//sons
	
	mciSendString("open .\\Audios\\BugsSound.mp3 type MPEGVideo alias Insetos", NULL, 0, 0);
	waveOutSetVolume(0,0x88888888);
	mciSendString("play Insetos repeat", NULL, 0, 0);
/*	mciSendString("seek Tema to start", NULL, 0, 0);
	waveOutSetVolume(0,0x44444444);
	mciSendString("play Tema repeat", NULL, 0, 0);*/
	
	
	void*imagem = load_image("dinamite.bmp",100,100,200,200);
	void*mascara = load_image("dinamite_pb.bmp",100,100,200,200);
	
	Item *dinamite1 = criar_item(0,"dinamite1",imagem,mascara,200,200,100,100);
    Item *dinamite2 = criar_item(1,"dinamite2",imagem,mascara,300,200,100,100);
    Item *dinamite3 = criar_item(2,"dinamite3",imagem,mascara,400,200,100,100);
    Item *dinamite4 = criar_item(3,"dinamite4",imagem,mascara,500,200,100,100);
    Item *dinamite5 = criar_item(4,"dinamite5",imagem,mascara,600,200,100,100);
    Item *dinamite6 = criar_item(5,"dinamite6",imagem,mascara,700,200,100,100);
    //variaveis do jogo
    
	Final *final0 = criar_final(0,"fuga de carro","Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque id dignissim quam. Proin sit amet pulvinar nulla, et sagittis magna. Curabitur congue consectetur sollicitudin. Suspendisse aliquam lorem a est tincidunt semper. Vestibulum sed hendrerit elit. Praesent lorem ex, lacinia vel");
	Final *final1 = criar_final(1,"matar monstro","Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque id dignissim quam. Proin sit amet pulvinar nulla, et sagittis magna. Curabitur congue consectetur sollicitudin. Suspendisse aliquam lorem a est tincidunt semper. Vestibulum sed hendrerit elit. Praesent lorem ex, lacinia vel");
	Final *final2 = criar_final(2,"quebrar a janela","Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque id dignissim quam. Proin sit amet pulvinar nulla, et sagittis magna. Curabitur congue consectetur sollicitudin. Suspendisse aliquam lorem a est tincidunt semper. Vestibulum sed hendrerit elit. Praesent lorem ex, lacinia vel");
	Final *final3 = criar_final(3,"botar fogo na casa","Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque id dignissim quam. Proin sit amet pulvinar nulla, et sagittis magna. Curabitur congue consectetur sollicitudin. Suspendisse aliquam lorem a est tincidunt semper. Vestibulum sed hendrerit elit. Praesent lorem ex, lacinia vel");
	
	final0->itens = criar_vetor_itens(2);
	
	append_vetor_itens(final0->itens,dinamite2);
	append_vetor_itens(final0->itens,dinamite5);
	
	FinaisVetor *finais0 = criar_vetor_finais(4);
	
	append_vetor_finais(finais0,final0);
	append_vetor_finais(finais0,final1);
	append_vetor_finais(finais0,final2);
	append_vetor_finais(finais0,final3);
	
	print_vetor_finais(finais0);
	print_vetor_itens(final0->itens);
	
	Saida *saida0 = criarSaida(0,"porta",1300,300,200,500);
	Saida *saida1 = criarSaida(0,"janela",50,300,750,300);
	
	saida0->finais = criar_vetor_finais(6);
	saida1->finais = criar_vetor_finais(6);
	
	append_vetor_finais(saida0->finais,final0);
	append_vetor_finais(saida0->finais,final1);
	append_vetor_finais(saida0->finais,final2);
	append_vetor_finais(saida0->finais,final3);
	
	print_vetor_finais(saida0->finais);
	
	void *img_cam0 = load_image("quarto0.bmp",LarTela,AltTela,0,0);
	void *img_cam1 = load_image("quarto1.bmp",LarTela,AltTela,0,0);
	void *img_cam2 = load_image("quarto2.bmp",LarTela,AltTela,0,0);
	void *img_cam3 = load_image("quarto3.bmp",LarTela,AltTela,0,0);
	
	TCamera *camera0 = criarCamera(0,img_cam0);
	camera0->saida = saida0;
	
	TCamera *camera1 = criarCamera(1,img_cam1);
	
	TCamera *camera2 = criarCamera(2,img_cam2);
	camera2->saida = saida1;
	
	TCamera *camera3 = criarCamera(3,img_cam3);
 	
 	TInventario *inventario = criar_inventario(LarTela-100,0);
 	inventario->itens = criar_vetor_itens(2);
 	
 	TCamera *cameras = (TCamera*)malloc(sizeof(TCamera)*4);
 	
 	cameras[0] = *camera0;
 	cameras[1] = *camera1;
 	cameras[2] = *camera2;
 	cameras[3] = *camera3;
 	
 	cameras[0].itens = criar_vetor_itens(20);
 	cameras[1].itens = criar_vetor_itens(20);
 	cameras[2].itens = criar_vetor_itens(20);
 	cameras[3].itens = criar_vetor_itens(20);
 	
 	append_vetor_itens(cameras[0].itens,dinamite1);
 	append_vetor_itens(cameras[0].itens,dinamite2);
 	append_vetor_itens(cameras[1].itens,dinamite3);
 	append_vetor_itens(cameras[3].itens,dinamite4);
	append_vetor_itens(cameras[1].itens,dinamite5);
	append_vetor_itens(cameras[3].itens,dinamite6);
	
 	while(true) {
 		gt2 = GetTickCount();
 		
 		if(gt2 - gt1 > 1000/60) {
 			if(pg == 1) pg = 2; else pg = 1;
 			setvisualpage(pg);
 			cleardevice();
 			
 			mudarDeCamera(&camera_atual,&tecla);

 			mostrarCamera(&cameras[camera_atual]);
			mostrarItensCamera(&cameras[camera_atual]);
			
			mostrarInventario(inventario);
			mostrarItensInventario(inventario);
			mostrarSaidasCamera(&cameras[camera_atual]);
			colisaoMouseItens(mousePos(),cameras[camera_atual],inventario);
			colisaoMouseSaidas(mousePos(),cameras[camera_atual],inventario);
			
 			setactivepage(pg);
		}
		
	}
	
	apaga_vetor_finais(&saida0->finais);
	apaga_vetor_finais(&saida1->finais);
	free(saida0);
	free(saida1);
	apaga_vetor_itens(&cameras[0].itens);
 	free(cameras);
	return 0;
}

int Menu();

int Tutorial(){
	int X,Y;
	int LarTela,LarJogo,AltTela,AltJogo,xIniJogo,yIniJogo;
	
	LarTela = 1280;
	AltTela = 720;
	
	void *img_Menu = load_image("Tutorial.bmp",LarTela,AltTela,0,0);
	
	setcolor(WHITE);
	rectangle(50, 800, 150, 850);

	int gt2;
	
	while(true){
		X = mousex();
		Y = mousey();
		
		gt2 = GetTickCount();
		if(gt2 - gt1 > 1000/60) {
//			printf("clicou: %d",ismouseclick(WM_LBUTTONDOWN));		
			if(ismouseclick(WM_LBUTTONDOWN)){
		
				if(X > 30 && X < 200 && Y > 650 && Y < 700){
					return Menu();
					break;
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}
		}
	}
	return 0;
}

int Menu(){

	int X,Y,tam1,tam2,tam3;
	int LarTela,LarJogo,AltTela,AltJogo,xIniJogo,yIniJogo;
	void *Iniciar, *Iniciar2; 
    void *MascIniciar, *MascIniciar2;
    void *Instrucoes;
    void *MascInstrucoes;
    void *Sair;
    void *MascSair;
    
    bool BTNInicio = false;
    
    int Larg[3] = {206,330,142};
    int Alt[3] = {74, 80, 74};
	
	int posX[3] = {540, 490, 575};
	int posY[3] = {430, 525, 630};
	
	LarTela = 1280;
	AltTela = 720;
	
	
	mciSendString("open .\\Audios\\MusicaTema.mp3 type MPEGVideo alias Tema", NULL, 0, 0);
	waveOutSetVolume(0,0xFFFFFFFF);
	mciSendString("play Tema repeat", NULL, 0, 0);
	
	tam1 = imagesize(0, 0, Larg[0], Alt[0]);
    Iniciar = malloc(tam1);
    MascIniciar = malloc(tam1);
    readimagefile(".\\Hud\\Iniciar1.bmp", 0, 0, Larg[0], Alt[0]);
    getimage(0, 0, Larg[0], Alt[0], Iniciar);
    readimagefile(".\\Hud\\Iniciar1WB.bmp", 0, 0, Larg[0], Alt[0]);
    getimage(0, 0, Larg[0], Alt[0], MascIniciar);
    
    tam1 = imagesize(0, 0, Larg[0], Alt[0]);
    Iniciar2 = malloc(tam1);
    MascIniciar2 = malloc(tam1);
    readimagefile(".\\Hud\\Iniciar2.bmp", 0, 0, Larg[0], Alt[0]);
    getimage(0, 0, Larg[0], Alt[0], Iniciar2);
    readimagefile(".\\Hud\\Iniciar2WB.bmp", 0, 0, Larg[0], Alt[0]);
    getimage(0, 0, Larg[0], Alt[0], MascIniciar2);
    
    
    tam2 = imagesize(0, 0, Larg[1], Alt[1]);
    Instrucoes = malloc(tam2);
    MascInstrucoes = malloc(tam2);
    readimagefile(".\\Hud\\Instrução1.bmp", 0, 0, Larg[1], Alt[1]);
    getimage(0, 0, Larg[1], Alt[1], Instrucoes);
    readimagefile(".\\Hud\\Instrução1WB.bmp", 0, 0, Larg[1], Alt[1]);
    getimage(0, 0, Larg[1], Alt[1], MascInstrucoes);
    
    tam3 = imagesize(0, 0, Larg[2], Alt[2]);
    Sair = malloc(tam3);
    MascSair = malloc(tam3);
    readimagefile(".\\Hud\\Sair1.bmp", 0, 0, Larg[2], Alt[2]);
    getimage(0, 0, Larg[2], Alt[2], Sair);
    readimagefile(".\\Hud\\Sair1WB.bmp", 0, 0, Larg[2], Alt[2]);
    getimage(0, 0, Larg[2], Alt[2], MascSair);
    
    void *img_Menu = load_image("HorrorHut2.bmp",LarTela,AltTela,0,0);
    
	if(BTNInicio){
		putimage(posX[0],posY[0],MascIniciar2,AND_PUT);
		putimage(posX[0],posY[0],Iniciar2,OR_PUT);
	}
	else{
		putimage(posX[0],posY[0],MascIniciar,AND_PUT);
		putimage(posX[0],posY[0],Iniciar,OR_PUT);
	}
	
	putimage(posX[1],posY[1],MascInstrucoes,AND_PUT);
	putimage(posX[1],posY[1],Instrucoes,OR_PUT);
	
	putimage(posX[2],posY[2],MascSair,AND_PUT);
	putimage(posX[2],posY[2],Sair,OR_PUT);

	int gt2;
	
	while(true){
		X = mousex();
		Y = mousey();
		
		gt2 = GetTickCount();
		if(gt2 - gt1 > 1000/60) {
//			printf("clicou: %d",ismouseclick(WM_LBUTTONDOWN));
			BTNInicio = false;
			if(!(X > 540 && X < 750 && Y > 450 && Y < 510))
				BTNInicio = true;
			
			if(ismouseclick(WM_LBUTTONDOWN)){
		
				if(X > 540 && X < 750 && Y > 450 && Y < 510){
					mciSendString("stop Tema", NULL, 0, 0);
					return Comeca_Jogo();
					break;
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}
			
			if(ismouseclick(WM_LBUTTONDOWN)){
		
				if(X > 490 && X < 820 && Y > 525 && Y < 600){
					return Tutorial();
					break;
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}
	
			if(ismouseclick(WM_LBUTTONDOWN)){
				if(X > 575 && X < 720 && Y > 610 && Y < 680){
//					return Conclusao();
					break;
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}
		}
	}
	return 0;
}

//TItem *chave = criarItem(1,"chave","chave.bmp","chave_pb.bmp",200,200,100,100);
//TItem *gasolina = criarItem(2,"gasolina","gasolina.bmp","gasolina_pb.bmp",400,600,50,100);
//TItem *rifle = criarItem(3,"rifle","rifle.bmp","rifle_pb.bmp",400,600,50,100);
//TItem *bala = criarItem(4,"bala","bala.bmp","bala_pb.bmp",400,600,50,100);
//TItem *celular = criarItem(5,"celular","celular.bmp","celular_pb.bmp",400,600,50,100);
//TItem *machado = criarItem(6,"machado","machado.bmp","machado_pg.bmp",400,600,50,100);
//TItem *fosforo = criarItem(7,"fosforo","fosforo.bmp","fosforo_pb.bmp",400,600,50,100);
//TItem *armadilha = criarItem(8,"armadilha","armadilha.bmp","armadilha_pb.bmp",400,600,50,100);

int main() {
	
	int LarTela = 1280;
	int AltTela = 720;
	
	setlocale(LC_ALL,"Portuguese");
	initwindow(LarTela, AltTela,"meu jogo");
	Menu();
	TMouse *mouse = mousePos();
 	closegraph();
	return 0;
}
