#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <locale.h>

typedef struct mouse_pos {
	int x;
	int y;
	int largura = 2;
	int altura = 2;
} Mouse;

typedef struct item {
	char* nome;
	char* image;
	int x;
	int y;
	int largura;
	int altura;
} Item;

typedef struct Camera{
	char* nome;
	char* image;
	Item* item;
	
	Camera(char* _nome, char* _image, int qtdItem, Item* _item){
		nome = _nome;
		image = _image;
		item = _item;
		
	}
};

typedef  struct {
	char*nome;
	Camera *camera;
	Comodo(char* _nome,Camera* _cam,int qtdCam){
		nome = _nome;
		camera = _cam;
	}
	
} Comodo;


bool clicou = false;

Mouse mousePos(){
	int x,y,button;
	Mouse mouse;
	if(!ismouseclick(WM_LBUTTONDOWN) && clicou == false){
//		getmouseclick(WM_LBUTTONDOWN,x,y);
//		printf("Botão esquerdo (%d,%d)\n",mousex(),mousey());	
		mouse.x = mousex();
		mouse.y = mousey();
		printf("Botão esquerdo (%d,%d,%i)\n",mouse.x,mouse.y,clicou);
		clearmouseclick(WM_LBUTTONDOWN);
	} 
	if(ismouseclick(WM_LBUTTONDOWN)){
		x = mousex();
		y = mousey();
		printf("clicou (%d,%d,%i)\n",x,y,clicou);
		clearmouseclick(WM_LBUTTONDOWN);
	}
	
	
	return mouse;
}

void *load_image(char* image_addres,int x,int y,int largura,int altura) {
	int aux = imagesize(x,y,largura,altura);
	
	void*image;
	image = malloc(aux);
	readimagefile(image_addres,x,y,largura,altura);
	getimage(0,0,largura,altura,image);
	cleardevice();
	return image;
}

//void troca_image(void *image_addres, void proxima_image) {
//	imagem_addres = proxima_image;
//}

int pg = 1;

Item criarItem(char*nome,char*image,int x,int y, int largura, int altura) {
	Item item;
	
	item.nome = nome;
	item.image = image;
	item.x = x;
	item.y = y;
	item.largura = largura;
	item.altura = altura;
	
	return item;
}

bool colisaoMouseItem(Mouse mouse,Item item) {
	if (mouse.x < item.x + item.largura && mouse.x + mouse.largura > item.x && mouse.y < item.y + item.altura && mouse.y + mouse.altura > item.y) 
	{
    	outtextxy(item.x,item.y,item.nome);
	}
}

void mostrarItens(Item *itens, int qtd) {
	for(int i = 0;i< qtd;i++) {
		printf("item: %s,%s,%d,%d,%d,%d \n",itens[i].nome,itens[i].image,itens[i].x,itens[i].y,itens[i].largura,itens[i].altura);
	}
}

//void trocaCamera(Comodo *_comodo){
//	return 0;
//}


int main() {
	int comodo_atual = 0;
	int camera_atual = 0;
	
	
	
	setlocale(LC_ALL,"Portuguese");
	initwindow(1280, 720,"meu jogo");
	
	void*image;
	
	Item *item_camera1 = (Item*) malloc(sizeof(Item)*3);
	Item lanterna = criarItem("lanterna","lanterna.bmp",200,150,50,50);
	Item relogio = criarItem("Relogio","relogio.bmp",50,50,100,100);
	item_camera1[0] = lanterna;
	item_camera1[1] = relogio;
	Camera camera1("camera1","camera1.bmp",3,item_camera1);
	image = load_image("quarto0.bmp",0,0,1280,720);
 	
 	mostrarItens(item_camera1,2);
 	Mouse mouse = mousePos();
 	
 	while(true) {
 		if(pg == 1) pg = 2; else pg = 1;
 		setvisualpage(pg);
		
		printf("Camera: %s,%s",camera1.nome,camera1.image);
		
 		
 		
 		putimage(0,0,image,COPY_PUT);
 		colisaoMouseItem(mousePos(),camera1.item[0]);
//		outtextxy(mousePos().x,mousePos().y,camera1.item[0].nome);
		
 		
 		setactivepage(pg);
 		cleardevice();
	}
 	
 	
	return 0;
}
