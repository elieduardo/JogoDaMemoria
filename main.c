#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Arquivos.h"
#include "Jogo.h"

/*
Criação da struct que guardará 
os dados do jogador
*/
struct jogador{
	char nome[20];
	int  acertos;
};

int main(int argc, char *argv[]) {
	struct jogador Jogador, *jgdor;
	jgdor = &Jogador;
	
	int opcao;
	char arquivoDificuldade;
	FILE *pont_regras;
	char texto_str[200];	
	
	do{			
		int dificuldade = 0;
		setlocale(LC_ALL, "Portuguese");		
		system ("cls");
		printf("----- Jogo da memória -----\n");
		printf("(1) Jogar \n");
		printf("(2) Como Jogar?\n");
		printf("(3) Cadastrar Palavras\n");
		printf("(0) Sair\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				system ("cls");	
				printf("Escolha o modo do jogo\n");
				printf("(1) Fácil \n");
				printf("(2) Médio\n");
				printf("(3) Difícil\n");
				scanf("%d", &dificuldade);	
				
				//Verfica se foi digitado um valor válido
				while(dificuldade != 1 && dificuldade != 2 && dificuldade != 3){					
					system ("cls");
					printf("Escolha o modo do jogo\n");
					printf("(1) Fácil \n");
					printf("(2) Médio\n");
					printf("(3) Difícil\n");
					scanf("%d", &dificuldade);
				}
				
				char arquivo[15];
				int tempo = 0;
				
				//Atribui o nome do arquivo para uso nas funcoes
				switch(dificuldade){
					case 1:
						strcpy( arquivo, "facil.txt");
						tempo = 10;
						break;
					case 2:
						strcpy( arquivo, "medio.txt");
						tempo = 7;
						break;
					default:
						strcpy( arquivo, "dificil.txt");
						tempo = 5;
						break;
				}				
								
				system ("cls");
				//Atribuição do nome do jogador
				printf("Digite o nome do Jogador:");
            	scanf("%s",(*jgdor).nome);
            	
				system ("cls");
				printf("----- Sorteando as Palavras -----\n");
				printf("------------ Aguarde -------------\n");
				//Sorteio de 5 palavras
				for(int i = 0; i <=4; i++){
					sorteioPalavras(i, arquivo);
				}
				//Função mostra as 5 palavras e dá tempo para jogar decorar (DEPENDENDO da dificuldade escolhida)		
				mostraPalavras(tempo);
				//Recebe a resposta do jogador
				pedePalavras();
				//Variavel de acertos do jogador recebe retorno da função verificaPalavras, retorna quantidade de acertos
				(*jgdor).acertos = verificaPalavras();
				//Verifica quantidade de acertos e imprime uma mensagem correspondente ao numero de acertos
				verificaGanhador(Jogador.acertos, Jogador.nome);
				break;
				
			case 2:
				system ("cls");
				//Abre arquivo das regras
				pont_regras = fopen("regras.txt", "r");
				
				//Imprime todo o arquivo na tela
				while(fgets(texto_str, 200, pont_regras) != NULL)
				printf("%s", texto_str);
				
				//Fecha arquivo
				fclose(pont_regras);
				system("pause");
				
				break;
			
			case 3:
				system ("cls");
				//Chamada da função para jogador cadastrar as palavras
				printf("Voce deseja adicionar palavras para qual dificuldade: \n");
				printf("(1) Facil\n(2) Medio\n(3) Dificil\n");
				scanf("%d", &arquivoDificuldade);
				if(arquivoDificuldade == 1){
					cadastrarPalavrasFacil();
				}else if(arquivoDificuldade == 2){
					cadastrarPalavrasMedio();
				}else if(arquivoDificuldade == 3){
					cadastrarPalavrasDificil();
				}
				break;
			case 0: 
				//Fecha o jogo
				opcao = 0;
				break;
			default:
				printf("\nOpcao Invalida...\n");
				break;
		}
	}while(opcao != 0);
	return 0;
}
