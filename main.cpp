#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <locale.h>
#include <time.h>

struct TMouse{
	int x;
	int y;
	int largura;
	int altura;
};

struct TItem{
	char* nome;
	char* image;
	int x;
	int y;
	int largura;
	int altura;
};

struct TPorta {
	int pos_x;
	int pos_y;
	int largura;
	int altura;
	int indice_comodo;
	bool aberta;	
};

struct TCorredor {
	char* image;
	TPorta *portas;
};

struct TComodo{
	char* nome;
	char* image;
	int qtdItens;
	TItem* item;
};

bool clicou = false;

TMouse *mousePos(){
	int x,y,button;
	TMouse *mouse;
	if(!ismouseclick(WM_LBUTTONDOWN) && clicou == false){
//		getmouseclick(WM_LBUTTONDOWN,x,y);
//		printf("Botão esquerdo (%d,%d)\n",mousex(),mousey());	
		mouse->x = mousex();
		mouse->y = mousey();
//		printf("Botão esquerdo (%d,%d,%i)\n",mouse.x,mouse.y,clicou);
		clearmouseclick(WM_LBUTTONDOWN);
	} 
	if(ismouseclick(WM_LBUTTONDOWN)){
		mouse->x = mousex();
		mouse->y = mousey();
//		printf("clicou (%d,%d,%i)\n",mouse.x,mouse.y,clicou);
		clearmouseclick(WM_LBUTTONDOWN);
	}
	
	return mouse;
}

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

TItem criarItem(char*nome,char*image,int x,int y, int largura, int altura) {
	TItem item;
	
	item.nome = nome;
	item.image = image;
	item.x = x;
	item.y = y;
	item.largura = largura;
	item.altura = altura;
	
	return item;
}

int colisaoMouseItens(TMouse *mouse,TComodo *comodo) {
//	printf("mouse(%d,%d)\n",mouse->x,mouse->y);
//	printf("qtd(%d)\n",comodo->qtdItens,comodo->qtdItens);
	for(int i = 0;i<comodo->qtdItens;i++) {
		TItem *item = comodo->item;
		if (mouse->x < item[i].x + item[i].largura && 
			mouse->x + mouse->largura > item[i].x && 
			mouse->y < item[i].y + item[i].altura && 
			mouse->y + mouse->altura > item[i].y) 
		{
			outtextxy(item[i].x,item[i].y,item[i].nome);
			delay(100);
    		
    		if(verificaMouseClick() == 1){
    			printf("clicou no item: %s\n",item[i].nome);
    			
			}
			
		}
	}
	return 0;
}



void mostrarItens(TItem *itens, int qtd) {
	for(int i = 0;i< qtd;i++) {
		printf("item: %s,%s,%d,%d,%d,%d \n",itens[i].nome,itens[i].image,itens[i].x,itens[i].y,itens[i].largura,itens[i].altura);
	}
}

//void trocaCamera(Comodo *_comodo){
//	return 0;
//}

// testandoooooooooo
int main() {
	setlocale(LC_ALL,"Portuguese");
	initwindow(1280, 720,"meu jogo");
	
	int fps = 60;
    int frame_interval = 1000 / fps;
    clock_t start_time, current_time;
	

	int comodo_atual = 0;
	void*image;
	
	TItem *item_camera1 = (TItem*) malloc(sizeof(TItem)*3);
	
	TItem lanterna = criarItem("lanterna","lanterna.bmp",200,150,50,50);
	TItem relogio = criarItem("Relogio","relogio.bmp",50,50,100,100);
	TItem caderno = criarItem("Caderno","caderno.bmp",80,300,100,100);
	
	item_camera1[0] = lanterna;
	item_camera1[1] = relogio;
	item_camera1[2] = caderno;
	
//	TPorta porta_quarto = (100,400,100,400,1,true);
//	
//	TCorredor corredor("corredor.bmp",&porta_quarto);
//	
//	TComodo quarto("quarto principal","quarto_principal.bmp",3,item_camera1);
	
	image = load_image("quarto0.bmp",0,0,1280,720);
 	
 	mostrarItens(item_camera1,2);
 	TMouse *mouse = mousePos();
 	
 	while(true) {
 		if(pg == 1) pg = 2; else pg = 1;
 		setvisualpage(pg);
		mousePos();
//		printf("Camera: %s,%s",camera1.nome,camera1.image);
 		
 		putimage(0,0,image,COPY_PUT);
// 		colisaoMouseItens(mouse,&quarto);
// 		printf("mouse pos (%d,%d)\n",mouse->x,mouse->y);
//		outtextxy(mousePos().x,mousePos().y,camera1.item[0].nome);
		
 		
 		setactivepage(pg);
 		
 		
 		start_time = clock();
        while ((current_time = clock()) - start_time < frame_interval)
        	
            delay(1);
        cleardevice();
	}
 	
 	
	return 0;
}
