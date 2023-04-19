#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<time.h>

#define ESC 27

int main() {
	
	int pg = 1;
	int i;
	int poly[10];
  	int x, y, raio;
  	int passox, passoy;
  	char tecla;
  	
  	tecla = 0;
  	x = 200;
  	y = 100;
  	raio = 18; 
  	passox = 2;
  	passoy = 1;
  	
  	srand(time(NULL));
  	initwindow(500, 500, "CENÁRIO", 620, 50);//cria a tela preta de 500x500 pixels
  	setbkcolor(RGB(134, 255, 153));
	
	while(tecla != ESC) {
		if (pg == 1) pg = 2; else pg=1;
    	setactivepage(pg);
    	cleardevice();
    	
    	setfillstyle(1, RGB(0, 0, 0));
    	setcolor(RGB(0, 0, 0));
    	fillellipse(x, y, raio, raio);
	
		x = x + passox; 
    	if (x <= 10+raio || x >= 400-raio)  // || -> or   && -> and
      		passox = -passox;
      
    	y = y + passoy;
    	if (y <= 10+raio || y >= 400-raio)
      		passoy = -passoy;

		for (i = 0; i < 1000; i++)
    		putpixel(rand()%500+0, rand()%300+350, RGB(rand()%10, rand()%256, rand()%256));
    		
    	setfillstyle(1, RGB(100, 200, 200));//cria a cor de preenchimento do objeto
		bar(500, 500, 0, 350);//cria um retângulo opaco. int left, int top, int right, int bottom
		
		setfillstyle(1, RGB(206, 93, 0));//plataforma
		bar(100, 200, 0, 350);
		
		setfillstyle(1, RGB(100, 100, 100));//peixe
		setcolor(RGB(100, 100, 100));
	
		poly[0] = 400; //primeiro vértice 
 		poly[1] = 350; 
 		poly[2] = 450; //segundo vértice
 		poly[3] = 400; 
 		poly[4] = 400; //terceiro vértice
 		poly[5] = 450; 
 		poly[6] = 440; //quarto vértice 
 		poly[7] = 450;
		poly[8] = 400; //quinto vértice
		poly[9] = 400;
		poly[10] = 400;
		poly[11] = 350;
 		poly[12] = poly[0]; /* drawpoly doesn't automatically close */ 
 		poly[13] = poly[1]; /* the polygon, so we close it */ 
 		fillpoly(6, poly); /* draw the polygon */
 	
 		setcolor(RGB(0, 0, 0));
 		poly[0] = 410; //primeiro vértice 
 		poly[1] = 390; 
 		poly[2] = 420; //segundo vértice
 		poly[3] = 400; 
 		poly[4] = 415; //terceiro vértice
 		poly[5] = 410; 
		poly[6] = poly[0]; //quinto vértice
		poly[7] = poly[1];
		drawpoly(4, poly); /* draw the polygon */

  		setcolor(RGB(255, 0, 255));
		setfillstyle(1, RGB(255, 0, 255));
		fillellipse(410, 370, 3, 3);
	
		setfillstyle(1, RGB(226, 122, 150));//cabelo
		bar(80, 100, 60, 200);
	
		setfillstyle(1, RGB(220, 187, 190));//corpo
		bar(80, 110, 60, 200);
	
		setfillstyle(1, RGB(0, 0, 0));//calça
		bar(80, 160, 60, 200);
	
		setfillstyle(1, RGB(60, 136, 56));//camisa
		bar(80, 150, 60, 125);
	
		setfillstyle(1, RGB(160, 170, 50));//olho
		bar(79, 114, 75, 111);
	
		setfillstyle(1, RGB(220, 187, 190));//braço
		bar(108, 135, 60, 125);
	
		setfillstyle(1, RGB(60, 136, 56));//camisa braço
		bar(90, 135, 60, 125);
	
		setfillstyle(1, RGB(0, 0, 0));//vara
		bar(200, 130, 107, 127);
	
		setcolor(RGB(255, 255, 255));
		setfillstyle(1, RGB(255, 255, 255));
		fillellipse(130, 50, 80, 30);//nuvens
	
		setfillstyle(1, RGB(255, 255, 255));
		fillellipse(200, 50, 80, 30);//nuvens
	
		setfillstyle(1, RGB(255, 255, 255));
		fillellipse(280, 50, 80, 30);//nuvens
	
		//setcolor(RGB(165, 220, 115));//peixe 1
		//rectangle(100, 400, 10, 450);
	
		//setcolor(RGB(165, 0, 115));//peixe 2
		//rectangle(150, 390, 50, 430);
	
		setcolor(RGB(255, 255, 255));//linha da vara
		moveto(200, 130);
		lineto(400, 350);
	
		setcolor(RGB(0, 255, 255));//linhas da água
		moveto(500, 350);
		lineto(0, 350);
	
		setcolor(RGB(0, 255, 255));
		moveto(500, 351);
		lineto(0, 351);
	
		setcolor(RGB(0, 255, 255));
		moveto(500, 353);
		lineto(0, 353);
	
		setcolor(RGB(0, 255, 255));
		moveto(500, 355);
		lineto(0, 355);
	
		setcolor(RGB(0, 255, 255));
		moveto(500, 358);
		lineto(0, 358);
	
		setcolor(RGB(0, 255, 255));
		moveto(500, 362);
		lineto(0, 362);
	
		setcolor(RGB(0, 255, 255));
  		circle(420, 300, 10);//bolhas na água
  	
  		setcolor(RGB(0, 255, 255));
  		circle(400, 330, 5);
  	
  		setcolor(RGB(0, 255, 255));
  		circle(430, 330, 20);
  	
  		setcolor(RGB(0, 255, 255));
  		circle(410, 340, 3);
	
	
		
		delay(10);
		
    	fflush(stdin);
    	if (kbhit()){
      	tecla = getch();
    	} 
    	
    	setvisualpage(pg);
	}
	
	closegraph();//fecha o programa ao apertar qualquer tecla
	return 0;//termina o programa
}
