#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

char palavra[5][20];
char resposta[5][20];
int acertos = 0;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void sorteioPalavras(int i){
		sleep(1); 
		FILE* f;
	
		f = fopen("teste.txt", "r");
		if(f == 0) {
			printf("Banco de dados de palavras não disponível\n\n");
			exit(1);
		}
	
		int qtddepalavras;
		fscanf(f, "%d", &qtddepalavras);
	
		srand(time(NULL));
		int randomico = rand() % qtddepalavras;
	
		for(int j = 0; j <= randomico; j++) {
			fscanf(f, "%s", palavra[i]);
		}
		
		fclose(f);		
		i++;
}

void mostraPalavras(){
	int j=5;	
	do{
		system ("cls");
		printf ("Decore as palavras abaixo em %d\n\n\n", j);
		j--;
		for (int i=0;i<5;i++){
			printf ("%s\t", palavra[i]);
		}
		Sleep (1000);
	}while (j>0);
}

void pedePalavras(){
	system ("cls");
	printf ("Informe as palavras que foram exibidos\n\n");
	
	for (int i = 0; i < 5; i++){
		printf ("\t%° palavra: ", i+1);
		scanf ("%s", resposta[i]);
	}
}

void verificaPalavras(){
	for(int i = 0; i <= 4; i ++){
		int retorno = strcmp(resposta[i], palavra[i]);				
		if(retorno == 0){
			acertos++;
		}
	}
}



void cadastrarPalavras(){
	char ask;

	printf("Você gostaria de cadastrar uma nova palavra? (S/N)?");
	scanf(" %c", &ask);

	if(ask == 'S') {
		char novapalavra[20];

		printf("Digite a nova palavra, em letras maiúsculas: ");
		scanf("%s", novapalavra);

		FILE* f;

		f = fopen("teste.txt", "r+");
		if(f == 0) {
			printf("Banco de dados de palavras não disponível\n\n");
			exit(1);
		}

		int qtd;
		fscanf(f, "%d", &qtd);
		qtd++;
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtd);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);

	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "Portuguese");
	int opcao;
	system ("cls");
	printf("----- Jogo da memória -----\n");
	printf("(1) Jogar \n");
	printf("(2) Como Jogar?\n");
	printf("(3) Cadastrar Palavras\n");
	printf("(0) Sair\n");
	scanf("%d", &opcao);
	
	for(int i = 0; i <=4; i++){
		sorteioPalavras(i);
	}
	mostraPalavras();
	pedePalavras();
	verificaPalavras();
	
	printf("%d \n", acertos);
	
	cadastrarPalavras();
	return 0;
}
