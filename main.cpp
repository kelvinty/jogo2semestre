#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <locale.h>
#include <time.h>

void* load_image(const char *endereco, int largura, int altura, int x, int y){
	int aux = imagesize(x,y,largura,altura);
	void*image = malloc(aux);
	readimagefile(endereco, x, y, largura, altura);
	getimage(x, y, largura, altura, image);
	return image;
}

void deleteImage(void *image){
	free(image);
}

void DesenhaFundo(int Cor) {
  int i;
  for(i = 0; i < 16; i++) {
    setcolor(i);
    setfillstyle(1, i);
    bar(i*40, 10, (i+1)*40, 490);
  }  
}

struct TMouse{
	int x;
	int y;
	int largura;
	int altura;
};

struct TItem{
	int id;
	char *nome;
	char *imagem;
	char *imagem_mask;
	int x;
	int y;
	int largura;
	int altura;
};

// CRUD ITENS
TItem *criarItem(int id, char *nome,char *imagem, char *image_mask, int x, int y, int largura, int altura) {
	TItem *item = (TItem*)malloc(sizeof(TItem));
	
	item->id = id;
	item->nome = nome;
	item->imagem = imagem;
	item->imagem_mask = image_mask;
	item->x = x;
	item->y = y;
	item->largura = largura;
	item->altura = altura;
	
	return item;
}

//void *mostraItem(const TItem *item) {
//	void *image;
//	image = 
//	return image;
//}

void apagaItem(TItem *item) {
	item = NULL;
}

struct TInventario {
	TItem *itens;
	int x;
	int y;
};

struct TFinal {
	int id;
	TItem *itens;
	char *descricao;
	char *historia; 
};

TFinal *criarFinal(int _id, TItem *_itens, char *_descricao, char *_historia) {
	TFinal *final = (TFinal*)calloc(1,sizeof(TFinal));
	final->id = _id;
	final->itens = _itens;
	final->descricao = _descricao;
	final->historia = _historia;
	return final;
}

struct TSaida {
	int id;
	char* nome;
	int x;
	int y;
	TFinal *finais;
};

TSaida *criarSaida(int _id,char*_nome,int _x, int _y,TFinal *_finais) {
	TSaida *saida = (TSaida*)calloc(1,sizeof(TSaida));
	saida->id = _id;
	saida->nome = _nome;
	saida->x = _x;
	saida->y = _y;
	saida->finais = _finais;
	return saida;
}

struct TCamera {
	int id;
	int qtdItens;
	char *imagem;
	TItem *itens;
	TSaida *saida;
};
//CRUD CAMERA

TCamera *criarCamera(int _id,char*_imagem,TItem* _itens,int _qtdItens, TSaida *_saida) {
	TCamera *camera = (TCamera*) calloc(1,sizeof(TCamera));
	camera->imagem = _imagem;
	camera->id = _id;
	camera->qtdItens = _qtdItens;
	camera->itens = _itens;
	camera->saida = _saida;
}

void *mostrarCamera(const TCamera *camera) {
	void *img = load_image(camera->imagem,1024,768,0,0);
	putimage(0,0,img,COPY_PUT);
}
//
void *mostrarItensCamera(const TCamera *camera) {
	for(int i =0;i<camera->qtdItens;i++) {
		void *image_mask = load_image(camera->itens[i].imagem_mask,camera->itens[i].largura,camera->itens[i].altura,camera->itens[i].x,camera->itens[i].y);
		void *image = load_image(camera->itens[i].imagem,camera->itens[i].largura,camera->itens[i].altura,camera->itens[i].x,camera->itens[i].y);
		
		putimage(camera->itens[i].x, camera->itens[i].y, image_mask, AND_PUT);
    	putimage(camera->itens[i].x, camera->itens[i].y, image, OR_PUT);
	}
}

//void removeItensCamera(TCamera *camera) {
//	for(int i =0;i<camera->qtdItens;i++) {
//		free(camera->itens[i].imagem);
//		free(camera->itens[i].imagem_mask);
//	}
//}

//bool clicou = false;
//TMouse *mousePos(){
//	
//	int x,y,button;
//	TMouse *mouse;
//	
//	if(!ismouseclick(WM_LBUTTONDOWN) && clicou == false){
////		getmouseclick(WM_LBUTTONDOWN,x,y);
////		printf("Botão esquerdo (%d,%d)\n",mousex(),mousey());	
//		mouse->x = mousex();
//		mouse->y = mousey();
////		printf("Botão esquerdo (%d,%d,%i)\n",mouse.x,mouse.y,clicou);
//		clearmouseclick(WM_LBUTTONDOWN);
//	} 
//	if(ismouseclick(WM_LBUTTONDOWN)){
//		mouse->x = mousex();
//		mouse->y = mousey();
////		printf("clicou (%d,%d,%i)\n",mouse.x,mouse.y,clicou);
//		clearmouseclick(WM_LBUTTONDOWN);
//	}
//	
//	return mouse;
//}

//bool verificaMouseClick() {
//	int x;
//	int y;
//	bool clicou = false;
//	if(ismouseclick(WM_LBUTTONDOWN)){
//		getmouseclick(WM_LBUTTONDOWN,x,y);
//		clearmouseclick(WM_LBUTTONDOWN);
//		clicou = true;
//	}
//	return clicou;
//}



//int colisaoMouseItens(TMouse *mouse,TCamera *camera) {
//	for(int i = 0;i<camera->qtdItens;i++) {
//		TItem item = camera->itens[i];
//		if (mouse->x < item.x + item.largura && 
//			mouse->x + mouse->largura > item.x && 
//			mouse->y < item.y + item.altura && 
//			mouse->y + mouse->altura > item.y) 
//		{
//			outtextxy(item.x,item.y,item.nome);
//			delay(100);
//    		
//    		if(verificaMouseClick() == 1){
//    			printf("clicou no item: %s\n",item.nome);	
//			}	
//		}
//	}
//	return 0;
//}


//
//void mostrarItens(TItem *itens, int qtd) {
//	for(int i = 0;i< qtd;i++) {
//		putimage(0,0,mostraItem(itens[i]),COPY_PUT);
//	}
//}

TItem *dinamite = criarItem(0,"dinamite","dinamite.bmp","dinamite_pb.bmp",200,200,100,100);
TItem *chave = criarItem(1,"chave","chave.bmp","chave_pb.bmp",200,200,100,100);
TItem *gasolina = criarItem(2,"gasolina","gasolina.bmp","gasolina_pb.bmp",400,600,50,100);
TItem *rifle = criarItem(3,"rifle","rifle.bmp","rifle_pb.bmp",400,600,50,100);
TItem *bala = criarItem(4,"bala","bala.bmp","bala_pb.bmp",400,600,50,100);
TItem *celular = criarItem(5,"celular","celular.bmp","celular_pb.bmp",400,600,50,100);
TItem *machado = criarItem(6,"machado","machado.bmp","machado_pg.bmp",400,600,50,100);
TItem *fosforo = criarItem(7,"fosforo","fosforo.bmp","fosforo_pb.bmp",400,600,50,100);
TItem *armadilha = criarItem(8,"armadilha","armadilha.bmp","armadilha_pb.bmp",400,600,50,100);

int main() {
	
	setlocale(LC_ALL,"Portuguese");
	initwindow(1024, 768,"meu jogo");
	int aux;
	int pg = 1;
	int fps = 60;
    int frame_interval = 1000 / fps;
    
    clock_t start_time, current_time;
    
    //variaveis do jogo
    
    TItem *itens_final0 = (TItem*)malloc(sizeof(TItem));
	
	itens_final0[0] = *dinamite;
	
	TItem *itens_camera0 = (TItem*)malloc(sizeof(TItem));
	
	itens_camera0[0] = *dinamite; 
	
	TFinal *final0 = criarFinal(0,itens_final0,"fuga do carro","kfhjgjodsfhg pokdjsfishdjghfdsjghisj kjshduifghsdijgsdifghoifdus");

	TSaida *saida0 = criarSaida(0,"porta",200,200,final0);
	
	TCamera *camera0 = criarCamera(0,"quarto0.bmp",itens_camera0,1,saida0);
 	
 	while(true) {
 		setvisualpage(pg);
 		if(pg == 1) pg = 2; else pg = 1;
 		
 		
 		//mostra elementos
 		cleardevice();
 		
 		mostrarCamera(camera0);
 		mostrarItensCamera(camera0);

 		setactivepage(pg);
 		
 		start_time = clock();
        while ((current_time = clock()) - start_time < frame_interval){
        	delay(1);
		}
         
	}
 	
 	closegraph();
	return 0;
}
