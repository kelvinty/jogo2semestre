#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <locale.h>
#include <time.h>
#include <conio.h>

int pg = 1;

void* load_image(const char *endereco, int largura, int altura, int x, int y){
	int aux = imagesize(x,y,largura,altura);
	void*img = malloc(aux);
	readimagefile(endereco, x, y, largura, altura);
	getimage(x, y, largura, altura, img);
	return img;
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



struct TItem{
	int id;
	char *nome;
	void *imagem;
	void *mascara;
	int x;
	int y;
	int largura;
	int altura;
};

// CRUD ITENS
TItem *criarItem(int id, char *nome,void *imagem, void *mascara, int x, int y, int largura, int altura) {
	TItem *item = (TItem*)malloc(sizeof(TItem));
	
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
	void *imagem;
	TItem *itens;
	TSaida *saida;
};
//CRUD CAMERA

TCamera *criarCamera(int _id,void*_imagem,TItem* _itens,int _qtdItens, TSaida *_saida) {
	TCamera *camera = (TCamera*) calloc(1,sizeof(TCamera));
	camera->imagem = _imagem;
	camera->id = _id;
	camera->qtdItens = _qtdItens;
	camera->itens = _itens;
	camera->saida = _saida;
	return camera;
}

void mostrarCamera(const TCamera camera) {
	putimage(0,0,camera.imagem,COPY_PUT);
}


void mostrarItensCamera(const TCamera camera) {
	for(int i =0;i<camera.qtdItens;i++) {
		TItem item = camera.itens[i]; 
		putimage(item.x, item.y, item.mascara, AND_PUT);
		putimage(item.x, item.y, item.imagem, OR_PUT);
	}
}

void removeItensCamera(TCamera *camera) {
	for(int i =0;i<camera->qtdItens;i++) {
		TItem item = camera->itens[i]; 
		free(item.imagem);
		free(item.mascara);
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



void colisaoMouseItens(TMouse *mouse,TCamera camera) {
	for(int i = 0;i<camera.qtdItens;i++) {
		TItem item = camera.itens[i];
		if (mouse->x < item.x + item.largura && 
			mouse->x + mouse->largura > item.x && 
			mouse->y < item.y + item.altura && 
			mouse->y + mouse->altura > item.y) 
		{
			outtextxy(item.x+(item.largura/4), item.y+item.altura, item.nome);
			delay(100);
    		
    		if(verificaMouseClick() == 1){
    			printf("clicou no item: %s\n",item.nome);	
			}	
		}
	}
	
}

void mudarDeCamera(int *camera_atual,int *tecla) {
	
    if (*tecla == 77) { // seta direcional para a direita
    	*tecla = 0;
        *camera_atual = *camera_atual + 1;
        if(*camera_atual > 3) {
        	*camera_atual = 0;
		}
    } else if (*tecla == 75) { // seta direcional para a esquerda
    	*tecla = 0;
        *camera_atual = *camera_atual - 1;
        if(*camera_atual < 0) {
        	*camera_atual = 3;
        	;
		}
    }
    
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
	int tecla = 0;
	int camera_atual = 0;
	int qtdCam = 0;
	
	setlocale(LC_ALL,"Portuguese");
	initwindow(1024, 768,"meu jogo");
	
	TMouse *mouse = mousePos();
	
	void*imagem = load_image("dinamite.bmp",100,100,200,200);
	void*mascara = load_image("dinamite_pb.bmp",100,100,200,200);
	
	TItem *dinamite = criarItem(0,"dinamite",imagem,mascara,200,200,100,100);
    
    //variaveis do jogo
    
    TItem *itens_final0 = (TItem*)malloc(sizeof(TItem));
	itens_final0[0] = *dinamite;
	
	TItem *itens_camera0 = (TItem*)malloc(sizeof(TItem));
//	TItem *itens_camera1 = (TItem*)malloc(sizeof(TItem));
	itens_camera0[0] = *dinamite; 
	
	TFinal *final0 = criarFinal(0,itens_final0,"fuga do carro","kfhjgjodsfhg pokdjsfishdjghfdsjghisj kjshduifghsdijgsdifghoifdus");
	TSaida *saida0 = criarSaida(0,"porta",200,200,final0);
	
	void *img_cam0 = load_image("quarto0.bmp",1024,768,0,0);
	void *img_cam1 = load_image("quarto1.bmp",1024,768,0,0);
	void *img_cam2 = load_image("quarto2.bmp",1024,768,0,0);
	void *img_cam3 = load_image("quarto3.bmp",1024,768,0,0);
	
	TCamera *camera0 = criarCamera(0,img_cam0,itens_camera0,1,saida0);
	TCamera *camera1 = criarCamera(1,img_cam1,itens_camera0,1,saida0);
	TCamera *camera2 = criarCamera(2,img_cam2,itens_camera0,1,saida0);
	TCamera *camera3 = criarCamera(3,img_cam3,itens_camera0,1,saida0);
 	
 	TCamera *cameras = (TCamera*)malloc(sizeof(TCamera)*4);
 	
 	cameras[0] = *camera0;
 	cameras[1] = *camera1;
 	cameras[2] = *camera2;
 	cameras[3] = *camera3;
 	
// 	for(int i = 0;i<4;i++){
// 		qtdCam++;
// 		(TCamera*)realloc(cameras,sizeof(TCamera)*qtdCam);
// 		cameras[i] = cam
//	}
 	
 	
 	while(true) {
 		if(pg == 1) pg = 2; else pg = 1;
 		setvisualpage(pg);
 		cleardevice();
 		mudarDeCamera(&camera_atual,&tecla);
// 		printf("camera {id:%d: nome:%s, atual:%d\n",cameras[camera_atual]->id,cameras[camera_atual].imagem,camera_atual);
 		mostrarCamera(cameras[camera_atual]);
		mostrarItensCamera(cameras[camera_atual]);
			
		colisaoMouseItens(mousePos(),cameras[camera_atual]);
		
 		setactivepage(pg);
 		
		if (kbhit())
		    tecla = getch();
		delay(50);
	}
	
	free(itens_camera0);
 	free(cameras);
 	
 	closegraph();
	return 0;
}
