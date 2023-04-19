// # JOGNA2 – Entrega N1.D – Grupo Formado por João Victor, Renan, Igor e Kelvin

// OBS: Não achei em nenhum arquivo no siga ou no teams a informação do número do grupo

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
#include <time.h>

struct TStars {
	int starX, starY; 
	int r;
	int g;
	int b;
	int starC;
	int grandeza;
	bool apagou;
};

void mostraEstrelas(TStars *stars,int qtd) {
	for(int i = 0;i < qtd;i++){
		TStars star = stars[i];
		if(star.grandeza == 1) {
			putpixel(star.starX, star.starY, star.starC);
		} else {
			for(int k=0; k<2; k++) {
				for (int j=0; j<2; j++){
					putpixel(stars[i].starX+k,stars[i].starY+j, stars[i].starC);
				}
			}
			
		}
		
	}
}

void piscaEstrela(TStars *stars, int qtd) {
	for(int i = 0;i < qtd;i++){
		if(stars[i].grandeza == 1) {
			if(stars[i].apagou == false) {
				if(stars[i].r <= 0 || stars[i].g <= 0 || stars[i].b <= 0) {
					stars[i].apagou = true;
					stars[i].starC = RGB(0, 0, 0);
				} else {
					
					stars[i].r = stars[i].r - 1;
					stars[i].g = stars[i].g - 1;
					stars[i].b = stars[i].b - 1;

					stars[i].starC = RGB(stars[i].r, stars[i].g, stars[i].b);
				}
//				putpixel(star.starX, star.starY, star.starC);
			} else {
				if(stars[i].r >= 254 || stars[i].g >= 254 || stars[i].b >= 254) {
					stars[i].apagou = false;
//					stars[i].starC = RGB(255, 255, 255);
				} else {
					stars[i].r = stars[i].r + 1;
					stars[i].g = stars[i].g + 1;
					stars[i].b = stars[i].b + 1;
				
					stars[i].starC = RGB(stars[i].r, stars[i].g, stars[i].b);
				}
				
			}
		} 
	}
}

void moveTriangulo(int tecla,int *points,int telax,int telay) {
	int randomico_x = rand()%telax;
    int randomico_y = rand()%telay;
    
	switch (tecla) { // verifica qual seta foi pressionada
        case 72: // seta para cima
            printf("Seta para cima pressionada\n");
            points[1] = points[1] - 5;
            points[3] = points[3] - 5;
            points[5] = points[5] - 5;
            break;
        case 80: // seta para baixo
            printf("Seta para baixo pressionada\n");
            points[1] = points[1] + 5;
            points[3] = points[3] + 5;
            points[5] = points[5] + 5;
            break;
        case 75: // seta para esquerda
            printf("Seta para esquerda pressionada\n");
            points[0] = points[0] - 5;
            points[2] = points[2] - 5;
            points[4] = points[4] - 5;
            break;
        case 77: // seta para direita
            printf("Seta para direita pressionada\n");
            points[0] = points[0] + 5;
            points[2] = points[2] + 5;
            points[4] = points[4] + 5;
            break;
        case 32:
        	points[0] = randomico_x;
        	points[1] = randomico_y;
            points[2] = randomico_x - 30;
            points[3] = randomico_y + 30;
            points[4] = randomico_x + 30;
            points[5] = randomico_y + 30;
            printf("Espaço: x:%d, y:%d",randomico_x,randomico_y);
            break;
        default: // outro código de tecla especial
            break;
    }
}

void saltoTemporal(TStars *stars,int qtd, int centro_x, int centro_y) {
	for(int i = 0;i < qtd;i++){
		float distancia = sqrt(pow(centro_x - stars[i].starX, 2) + pow(centro_y - stars[i].starY, 2));
		float passo_x = (centro_x - stars[i].starX) / distancia;
   		float passo_y = (centro_y - stars[i].starY) / distancia;
   		printf("x:%lf,y:%lf\n",passo_x,passo_y);
		
		for(int K = 0;K < 10;K++) {
			putpixel(stars[i].starX - passo_x * 10,stars[i].starY - passo_y * 10,stars[i].starC);
		}
		
			
	}
}

void viagemEstelar(TStars *stars, int qtd, int tela_h, int tela_v) {
	
	for(int i = 0;i < qtd;i++) {
		stars[i].starX = rand()%tela_h;
		stars[i].starY = rand()%tela_v;
		stars[i].r = rand()%255;
		stars[i].g = rand()%255;
		stars[i].b = rand()%255;
		stars[i].starC = RGB(stars[i].r, stars[i].g, stars[i].b);
		stars[i].grandeza = (rand()%2) + 1;
	}
}

void hiperEspaco(TStars *stars, int qtd, int centro_x, int centro_y) {
	for(int i = 0;i < qtd;i++){
		float distancia = sqrt(pow(centro_x - stars[i].starX, 2) + pow(centro_y - stars[i].starY, 2));
		float passo_x = (centro_x - stars[i].starX) / distancia;
   		float passo_y = (centro_y - stars[i].starY) / distancia;
   		printf("x:%lf, y:%lf, distancia:%lf\n",passo_x,passo_y,distancia);
		
//		for(int k = 0;k < 100;k++) {
//			printf("x:%lf,y:%lf\n",passo_x,passo_y);
//			line(stars[i].starX, stars[i].starY, stars[i].starX + passo_x * 10, stars[i].starY + passo_y * 10);
////			putpixel(stars[i].starX + passo_x * 5,stars[i].starY + passo_y * 5,stars[i].starC);
//		}
		if(distancia > 0) {
			line(stars[i].starX, stars[i].starY, centro_x, centro_y);
			delay(2);
//			float ini_distancia = distancia;
//			int ini_x = stars[i].starX;
//			int ini_y = stars[i].starY;
//			float ini_passo_x = (centro_x - stars[i].starX) / ini_distancia;
//			float ini_passo_y = (centro_y - stars[i].starY) / ini_distancia;
			
//			while(ini_distancia > 0){
			
//				line(ini_x, ini_y, stars[i].starX, stars[i].starY);
//				stars[i].starX += passo_x * 5; 
//				stars[i].starY += passo_y * 5;
//				ini_distancia = sqrt(pow(centro_x - stars[i].starX, 2) + pow(centro_y - stars[i].starY, 2)); 
//				ini_passo_x = (centro_x - stars[i].starX) / ini_distancia;
//				ini_passo_y = (centro_y - stars[i].starY) / ini_distancia;
//			} 
		}
		
		
			
	}
}

int main() {
	int tecla = 0;
	int pg = 1;
	int tela_h,tela_v;
	int tela_tot, qtdStars;
	int pos_x,pos_y;
	int vel;
	
	float tempo;
	float last_time = clock();
	
	srand(time(NULL));
	
	printf("Digite a largura da tela:");
	scanf("%d",&tela_h);
	
	tela_v = round(tela_h * 0.66);
	
	tela_tot = tela_h * tela_v;
	qtdStars = round(tela_tot*0.008);
	
	TStars *stars = (TStars*) malloc(sizeof(TStars)* qtdStars);
	
	pos_x = tela_h/2;
	pos_y = tela_v/2;
	
	initwindow(tela_h,tela_v,"Desafio Viagem estelar");
	
	for(int i = 0;i < qtdStars;i++) {
		stars[i].starX = rand()%tela_h;
		stars[i].starY = rand()%tela_v;
		stars[i].r = rand()%255;
		stars[i].g = rand()%255;
		stars[i].b = rand()%255;
		stars[i].starC = RGB(stars[i].r, stars[i].g, stars[i].b);
		stars[i].grandeza = (rand()%2) + 1;
		stars[i].apagou = false;
	}
	
	int points[] = { pos_x, pos_y, pos_x-30, pos_y+30, pos_x + 30, pos_y + 30 };
    int num_points = 3;
	
	while(true){
		
		if(pg == 1) pg = 2; else pg = 1;
		
 		setvisualpage(pg);
 		cleardevice();
		
		mostraEstrelas(stars,qtdStars);
		piscaEstrela(stars,qtdStars);
		setfillstyle(1, RGB(255,255,255));
    	fillpoly(num_points, points);
		
		setactivepage(pg);
//		piscaEstrela(stars,qtdStars);
//		if (clock() - last_update_time > CLOCKS_PER_SEC / 30) {
//			
//			last_update_time = clock();
//		}
		if (kbhit()){
            tecla = getch(); // captura o código de tecla especial
          	printf("%d",tecla);
            moveTriangulo(tecla,points,tela_h,tela_v);
            
            if(tecla == 83 || tecla == 115) {
            	tempo = clock();
            	float ini_time = (tempo - last_time)/1000;
            	float current_time = (tempo - last_time)/1000;
            	printf("%.2lf\n",current_time/1000);
            	//tecla "S"
            	
            	while(current_time - ini_time < 5) {
            		tempo = clock();
            		current_time = (tempo - last_time)/1000;
            		saltoTemporal(stars,qtdStars,tela_h/2,tela_v/2);
				}
            
			}
			if (tecla == 86 || tecla == 118) {
				viagemEstelar(stars,qtdStars,tela_h,tela_v);
			}
			if (tecla == 104) {
				tempo = clock();
            	float ini_time = (tempo - last_time)/1000;
            	float current_time = (tempo - last_time)/1000;
            	printf("%.2lf\n",current_time/1000);
            	//tecla "S"
            	
            	while(current_time - ini_time < 5) {
            		tempo = clock();
            		current_time = (tempo - last_time)/1000;
            		hiperEspaco(stars,qtdStars,tela_h/2,tela_v/2);
				}
			}
        }
//		delay(50);
	}
	free(stars);
	system("pause");
	
	return 0;
}
