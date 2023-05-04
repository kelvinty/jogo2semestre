#include "vetor_itens.h"
#include "vetor_finais.h"
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <string.h>

#include <mfapi.h>
#include <mfidl.h>
#include <Mfreadwrite.h>
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfreadwrite.lib")



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
//   		cleardevice();
   		for(int l = 0; l < qtdLetras;){
   			if(pg == 1) pg = 2; else pg = 1;
//	 		setvisualpage(pg);
			newStr[l] = linha[i][l];
			newStr[l+1] = '\0';
			outtextxy(pos_x ,pos_y + (i*alturaString),newStr);
			delay(50);
			setactivepage(pg);
			l++;
		}
		 // itera pelo array de linhas (substitua "3" pelo número de linhas no seu caso)
        outtextxy(pos_x, pos_y + (i*alturaString), linha[i]); // exibe a linha atual
    	setactivepage(pg);
		printf("\n");
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

struct TInventario {
	int maxItens;
	int qtdItens;
	ItensVetor *itens;
	int x;
	int y;
};

TInventario *criar_inventario(int x, int y) {
	TInventario *inventario = (TInventario*)calloc(1,sizeof(TInventario));
	
//	inventario->maxItens = maxItens;
//	inventario->qtdItens = qtdItens;
	inventario->x = x;
	inventario->y = y;
	inventario->itens = NULL;
	
	return inventario;
}

typedef struct saida {
	int id;
	char* nome;
	int x;
	int y;
	int largura;
	int altura;
	FinaisVetor *finais;
}Saida;

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

struct TCamera {
	int id;
	int qtdItens;
	void *imagem;
	ItensVetor *itens;
	Saida *saida;
};
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

	for(int i = 0;i<camera.itens->tamanho;i++) {
		Item item = camera.itens->itens[i];

		if (mouse->x < item.x + item.largura && 
			mouse->x + mouse->largura > item.x && 
			mouse->y < item.y + item.altura && 
			mouse->y + mouse->altura > item.y) 
		{
			int largura_texto = textwidth(item.nome);
			outtextxy(item.x + ((item.largura/2) - (largura_texto/2)), item.y+item.altura,item.nome);
//			animacao_texto(item.nome,8,item.x + ((item.largura/2) - (largura_texto/2)), item.y+item.altura);
			delay(50);
    		
    		if(verificaMouseClick() == 1){
    			pegarItem(&item,&camera,inventario);	
			}	
		}
	}
	
}

void colisaoMouseSaidas(TMouse *mouse,TCamera camera, TInventario *inventario) {
	if(camera.saida != NULL) {
		Saida *saida = camera.saida;

		if (mouse->x < saida->x + saida->largura && 
			mouse->x + mouse->largura > saida->x && 
			mouse->y < saida->y + saida->altura && 
			mouse->y + mouse->altura > saida->y) 
		{
			int largura_texto = textwidth(saida->nome);
			int altura_texto = textheight(saida->nome);
			outtextxy(saida->x + ((saida->largura/2) - (largura_texto/2)), saida->y + ((saida->altura/2) - (altura_texto/2)),saida->nome);
//			animacao_texto(saida->nome,8,saida->x + ((saida->largura/2) - (largura_texto/2)), saida->y+saida->altura);
    		printf("clicou na saida:%s\n", saida->nome);
    		if(verificaMouseClick() == 1){
    			printf("clicou na saida:%s\n", saida->nome);	
			}	
		}	
	}
//	for(int i = 0;i<camera.itens->tamanho;i++) {
	
//	}
	
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
	int LarTela,LarJogo,AltTela,AltJogo,xIniJogo,yIniJogo;
	
	LarTela = GetSystemMetrics(SM_CXSCREEN) - 100;
	AltTela = GetSystemMetrics(SM_CYSCREEN) - 100;
	
	LarJogo = LarTela;
	AltJogo = AltTela;
	
	xIniJogo = (LarTela - LarJogo) / 2;
	yIniJogo = AltJogo;
	
	setlocale(LC_ALL,"Portuguese");
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
	
	
	TMouse *mouse = mousePos();

//	TInventario *inventario = (TInventario*)malloc(sizeof(TInventario)*1);
//	inventario->itens = (TItem*)malloc(sizeof(TItem)*2); 
	
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
	
	void *img_cam0 = load_image("quarto0.bmp",LarJogo,AltJogo,0,0);
	void *img_cam1 = load_image("quarto1.bmp",LarJogo,AltJogo,0,0);
	void *img_cam2 = load_image("quarto2.bmp",LarJogo,AltJogo,0,0);
	void *img_cam3 = load_image("quarto3.bmp",LarJogo,AltJogo,0,0);
	
	TCamera *camera0 = criarCamera(0,img_cam0);
	camera0->saida = saida0;
	
	TCamera *camera1 = criarCamera(1,img_cam1);
	
	TCamera *camera2 = criarCamera(2,img_cam2);
	camera2->saida = saida1;
	
	TCamera *camera3 = criarCamera(3,img_cam3);
 	
 	TInventario *inventario = criar_inventario(LarJogo-100,0);
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

int Menu(){

	int X,Y;
	
	setbkcolor(BLACK);
	setcolor(WHITE);
	settextstyle(DEFAULT_FONT,HORIZ_DIR,5);
	outtextxy(200, 50, "Blend Scape");
	
	settextstyle(DEFAULT_FONT,HORIZ_DIR,3);
	rectangle(200, 100,400,150);
	outtextxy(220, 115, "Iniciar");
	
	rectangle(200, 200,400,250);
	outtextxy(220, 215, "Sair");
	int gt2;
	
	while(true){
		X = mousex();
		Y = mousey();
		gt2 = GetTickCount();
		if(gt2 - gt1 > 1000/60) {
//			printf("clicou: %d",ismouseclick(WM_LBUTTONDOWN));
			if(ismouseclick(WM_LBUTTONDOWN)){
		
				if(X > 200 && X < 400 && Y > 100 && Y < 150){
					return Comeca_Jogo();
					break;
				}
				clearmouseclick(WM_LBUTTONDOWN);
			}
	
			if(ismouseclick(WM_LBUTTONDOWN)){
				if(X > 200 && X < 400 && Y > 200 && Y < 250){
					return Conclusao();
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
	
	int LarTela,LarJogo,AltTela,AltJogo,xIniJogo,yIniJogo;
	
	LarTela = GetSystemMetrics(SM_CXSCREEN) - 100;
	AltTela = GetSystemMetrics(SM_CYSCREEN) - 100;
	
	LarJogo = LarTela;
	AltJogo = AltTela;
	
	xIniJogo = (LarTela - LarJogo) / 2;
	yIniJogo = AltJogo;
	
	setlocale(LC_ALL,"Portuguese");
	initwindow(LarTela, AltTela,"meu jogo");
	Menu();
	TMouse *mouse = mousePos();
 	closegraph();
	return 0;
}
