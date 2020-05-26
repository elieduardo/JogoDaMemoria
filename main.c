#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

char palavra[5][20];
char resposta[5][20];
int acertos = 0;

/*https://pt.stackoverflow.com/questions/220055/d%C3%BAvida-sobre-struct-e-ponteiro-para-struct*/

int contagemPalavras(){
	char c;
	FILE *fp;
	int count = 0;
	int flag = 0;

	if ((fp=fopen("teste.txt", "r"))==NULL)
	{
		printf("DEU ERRO AO ABRIR O ARQUIVO");
		exit(1);
	}

	while(!feof(fp))
	{
		c = getc(fp);
		if ( c == ' ' || c == '\n' )
		{
			if (flag == 0)
			{
				count++;
				flag = 1;
			}
		}
		else
		{
			if ( flag == 1 )
				flag = 0;
		}
	}

	fclose(fp);
	return count;
}
void sorteioPalavras(int i){
	sleep(1); 
	FILE* f;

	f = fopen("teste.txt", "r");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

	int qtddepalavras = contagemPalavras();
	
	srand(time(NULL));
	int randomico = rand() % qtddepalavras;

	for(int j = 0; j <= randomico; j++) {
		fscanf(f, "%s", palavra[i]);
	}
	
	fclose(f);	
}

void cronometro ( int segundos)
{
  clock_t fimtempo;
  fimtempo = clock () + segundos * CLK_TCK;
  while (clock() < fimtempo) {}
}

void mostraPalavras(){
	
	int j=5;	
	do{
		system ("cls");
		printf ("Decore as palavras abaixo em %d\n\n\n", j);
		j--;
		for (int i=0;i<5;i++){
			printf ("\t(%d)%s\n", i+1, palavra[i]);
		}
		cronometro(1);	
	}while (j>0);
	
}

void pedePalavras(){
	system ("cls");
	printf ("Informe as palavras que foram exibidos\n\n");
	
	for (int i = 0; i < 5; i++){
		printf ("\t%d° palavra: ", i+1);
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
				
	char ask = 'S';
	
	printf("Você gostaria de cadastrar outra palavra? (S/N)");
	scanf(" %c", &ask);
	
	if(ask == 'S') {			
		cadastrarPalavras();
	}else{
		exit(1);
	}
}

void verificaGanhador(){
	printf("%d \n", acertos);
	system("pause");
	//Fazer a verificação se acertos == 5
	//Pergutar se deseja sair do jogo ou jogar novamente
}

int main(int argc, char *argv[]) {	
	
	int opcao;
	FILE *pont_regras;
	char texto_str[200];
	
	
	do{
		acertos = 0;
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
				printf("----- Sorteando as Palavras -----\n");
				printf("------------ Aguarde -------------\n");
				for(int i = 0; i <=4; i++){
					sorteioPalavras(i);
				}				
				
				mostraPalavras();
				pedePalavras();
				verificaPalavras();
				verificaGanhador();
				break;
				
			case 2:								
				pont_regras = fopen("regras.txt", "r");
				
				while(fgets(texto_str, 200, pont_regras) != NULL)
				printf("%s", texto_str);
				
				fclose(pont_regras);
				system("pause");
				
				break;
			
			case 3:
				cadastrarPalavras();
				break;
			case 0: 
				opcao = 0;
				break;
			default:
				printf("\nOpcao Invalida...\n");
				break;
		}
	}while(opcao != 0);
		
	return 0;
}
