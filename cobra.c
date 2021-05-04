#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // funcao SetConsole
#include <conio.h>  // funcao getch() e kbhit()
#include <time.h>  // funcao rand()

// variavel global

	int c[300][2], pontos=1, cx=2, cy=2,  comida[2], velo=150;
	
//FUNCOES
	void gotoxy(int x, int y){

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

	void desenha(){
		int i;
		for(i=0; i<pontos; i++){
			gotoxy(c[i][0], c[i][1]);
			printf("%c",219);
			
		}
			
	}
	
	void atualiza(){  //para atualizar a posicao cobra
		
		int i;
		gotoxy(c[pontos][0], c[pontos][1]);
		printf(" ");
		for(i=pontos; i>=0; i--){
			c[i+1][0] = c[i][0];
			c[i+1][1] = c[i][1];
			
			
		}
								
	}
	
	
	int analiza(){   //ve se a bateu no proprio corpo
		
		int i, retorno=0;
		for(i=1; i<pontos; i++){
			if(cx==c[i][0] && cy==c[i][1])
				retorno=1;
			
		}
			return retorno;
		
	}
	
	void geraComida(){
		
		gotoxy(comida[0],comida[1]);  //Gera comida em posicao
		printf(" ");   // Apaga a comida
		srand(time(NULL));  //Gerador de comida aleatorio
		comida[0] = (rand() % 48) +1;
		comida[1] = (rand() % 18) +1;
		gotoxy(comida[0],comida[1]);
		printf("%c", 4);  //Imprimi a comida gerada	
		
	}
	
	int main(){
		int i, gameover=0;
		char tecla;
		
		for(i=0; i<50; i++){  //Linha superior
			gotoxy(i,0);
			printf("%c",219);  //caractere todo preenchido
			Sleep(5);	  //para ficar como uma animacao (pausa 5 milisegundos)			
		}
		for(i=0; i<20; i++){  //Coluna da Direita
			gotoxy(50,i);
			printf("%c", 219);
			Sleep(5);
			
		}
		for(i=50; i>=0; i--){  //linha inferior
			gotoxy(i,20);
			printf("%c", 219);
			Sleep(5);			
			
		}
		for(i=20; i>=0; i--){ //Coluna Esquerda
			gotoxy(0,i);
			printf("%c", 219);
			Sleep(5);
					
		}
		
		geraComida(); // Gera primeira comida
		desenha();    // Desenha cobra
		tecla='d';    // Direcao comeca pela direita
		
		
		while(gameover==0){
			gotoxy(52,2);
			printf("Pontos: %d\t", pontos);
			gotoxy(52,4);
			printf("Desenvolvido por Herbert Sprengel");
			c[0][0]=cx;
			c[0][1]=cy;
			if(kbhit())
				tecla=getch();
				
			if(tecla=='w' || tecla=='W' || tecla==72){
				cy--;
				if(cy==0) break;
				// se bater na parede superior o jogo termina
						
			}
			if(tecla=='a' || tecla=='A' || tecla==75){
				cx--;
				if(cx==0) break;
				// Se bater na parede da esquerda, acaba;					
			}
			if(tecla=='s' || tecla=='S' || tecla==80){
				cy++;
				if(cy==20) break;
				// Se bater na parte de baixo, acaba;	
			}
			if(tecla=='d' || tecla=='D' || tecla==77){
				cx++;
				if(cx==50) break;
				// se bater na parede da direita, acaba
						
			}
			
			if(cx==comida[0] && cy==comida[1]){
				pontos++;
				if(velo>50) velo-=10;
				// velo é a velociadade media em milisegundos				
				geraComida();		
			}
			gameover=analiza();
			atualiza();  // Atualiza posicao da cobra
			desenha();  // Desenha Cobra
			gotoxy(50, 20);  //Para o cursor nao atrapalhar
			Sleep(velo);  // Pausa o jogo por "velo"				
		}
		system("cls");
		printf("Voce perdeu! Fez %d pontos.\n",pontos);
		system("pause");
		
		
	}
	
	
	
