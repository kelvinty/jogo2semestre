#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

void *desenhaImagem(char* endereco, int width, int height,int scale = 1) {
	void *image;
	
	int aux = imagesize(0, 0, width * scale, height * scale);
   	image = malloc(aux);
   	
   	readimagefile(endereco, 0, 0, width * scale, height * scale);
   	getimage(0, 0, width * scale, height * scale, image);
	   //int imagem = loadimage("quarto0.bmp");

   	// desenha a imagem na janela na posição (100, 100) usando o modo padrão
   	putimage(0, 0, image, COPY_PUT);

   	// espera o usuário fechar a janela
   	getch();
   	
   	return image;
}

int main() {
	
 	initwindow(1280, 720,"meu jogo");
 	
 	void *imagem;
 	
 	imagem = desenhaImagem("quarto3.bmp",1280,720,1);
 	
	putimage(0, 0, imagem, COPY_PUT);
   	// fecha a janela e libera a memória usada pela imagem
   	closegraph();
   	free(imagem);
	return 0;
}
