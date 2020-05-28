#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <locale.h>

//Vari�veis Globais
char palavra[5][20];
char resposta[5][20];

//Cria��o da struct
struct jogador{
		char nome[20];
		int  acertos;
};

//Fun��o conta quantas palavras existem no arquivo txt
int contagemPalavras(){
	char c;
	FILE *fp;
	int count = 0;
	int flag = 0;

	//Verifica se arquivo existe
	if ((fp=fopen("teste.txt", "r"))==NULL)
	{
		printf("DEU ERRO AO ABRIR O ARQUIVO");
		exit(1);
	}

	//Faz a contagem
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
	
	//Fecha o arquivo	
	fclose(fp);
	//Retorna o numero de palavras no arquivo
	return count;
}

//Fun��o que sorteia 5 palavras do arquivo txt
void sorteioPalavras(int i){
	sleep(1); 
	FILE* f;

	//Verifica se arquivo existe
	f = fopen("teste.txt", "r");
	if(f == 0) {
		printf("Banco de dados de palavras n�o dispon�vel\n\n");
		exit(1);
	}

	//Atribui quantidade de palavras que existem no arquivo
	int qtddepalavras = contagemPalavras();
	
	//Gerador rand�mico de numero com limite do numero de palavras no txt
	srand(time(NULL));
	int randomico = rand() % qtddepalavras;

	//Escreve na tela as 5 palavras
	for(int j = 0; j <= randomico; j++) {
		fscanf(f, "%s", palavra[i]);
	}
	
	//Fecha o arquivo
	fclose(f);	
}

//Fun��o utilizada como um cronometro de 5 segundos
void cronometro ( int segundos)
{
  clock_t fimtempo;
  fimtempo = clock () + segundos * CLK_TCK;
  while (clock() < fimtempo) {}
}

//Imprime as palavras na tela e roda o cronometro de 5 segundos
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

//Pede input do jogador
void pedePalavras(){
	system ("cls");
	printf ("Informe as palavras que foram exibidos\n\n");
	
	for (int i = 0; i < 5; i++){
		printf ("\t%d� palavra: ", i+1);
		scanf ("%s", resposta[i]);
	}
}

int verificaPalavras(){
	int aux = 0;
	for(int i = 0; i <= 4; i ++){
		//Utiliza fun��o que compara as duas palavras
		int retorno = strcmp(resposta[i], palavra[i]);				
		if(retorno == 0){
			aux ++;
		}
	}
	return aux;
}


void cadastrarPalavras(){
	
	//Vari�vel que captura a palavra cadastrada
	char novapalavra[20];

	printf("Digite a nova palavra, em letras mai�sculas: ");
	scanf("%s", novapalavra);

	FILE* f;

	//Verifica se arquivo existe
	f = fopen("teste.txt", "r+");
	if(f == 0) {
		printf("Banco de dados de palavras n�o dispon�vel\n\n");
		exit(1);
	}

	//Atribui a palavra no arquivo 
	int qtd;
	fscanf(f, "%d", &qtd);
	qtd++;
	fseek(f, 0, SEEK_SET);
	fprintf(f, "%d", qtd);

	fseek(f, 0, SEEK_END);
	fprintf(f, "\n%s", novapalavra);

	//Fecha arquivo
	fclose(f);
						
	char ask = 'S';
	
	//Pergunta se jogador deseja cadastrar outra palavra
	printf("Voc� gostaria de cadastrar outra palavra? (S/N)");
	scanf(" %c", &ask);
	
	//Verifica resposta
	if(ask == 'S') {			
		cadastrarPalavras();
	}else{
		exit(1);
	}
}

void verificaGanhador(int acertos, char nome[20]){
	int opc;
	
	//Mostra mensagem conforme numero de acertos
	switch(acertos){
			case 0:
				printf("NOSSA %s, voc� n�o � MUITO ruim de mem�ria n�o acertou nenhuma palavra (PROCURE UM M�DICO URGENTE) \n", nome);
			break;
			case 1:
				printf("Que pena %s, voc� n�o � MUITO ruim de mem�ria acertou 1 palavra (PROCURE UM M�DICO) \n", nome);
			break;
			case 2:
				printf("Que pena %s, voc� n�o � MUITO ruim de mem�ria acertou 2 palavra (FIQUE ATENTO)\n", nome);
			break;
			case 3:
				printf("Que pena %s, voc� n�o tem uma mem�ria razo�vel acertou 3 palavra\n", nome);
			break;
			case 4:
				printf("Que pena %s, por pouco voc� n�o conseguiu ganhar acertou 4 palavra\n", nome);
			break;
			default:
				printf("PARAB�NS %s! VOC� ACERTOU TODAS AS PALAVRAS...\n", nome);
			break;
		}
	
	system("pause");
	
	//Pergunta se jogador que voltar para o menu ou se quer sair do jogo
	system ("cls");
	printf("----- Jogo da mem�ria -----\n");
	printf("(1) Voltar ao Menu\n");
	printf("(0) Sair\n");
	scanf("%d", &opc);
	if(opc == 0){
		exit(1);
	}
}

int main(int argc, char *argv[]) {		
	
	struct jogador Jogador, *jgdor;
	jgdor = &Jogador;
	
	int opcao;
	FILE *pont_regras;
	char texto_str[200];
	
	
	do{		
		setlocale(LC_ALL, "Portuguese");		
		system ("cls");
		printf("----- Jogo da mem�ria -----\n");
		printf("(1) Jogar \n");
		printf("(2) Como Jogar?\n");
		printf("(3) Cadastrar Palavras\n");
		printf("(0) Sair\n");
		scanf("%d", &opcao);
		
		switch(opcao){
			case 1:
				system ("cls");
				//Atribui��o do nome do jogador
				printf("Digite o nome do Jogador:");
            	scanf("%s",(*jgdor).nome);
				system ("cls");
				printf("----- Sorteando as Palavras -----\n");
				printf("------------ Aguarde -------------\n");
				//Sorteio de 5 palavras
				for(int i = 0; i <=4; i++){
					sorteioPalavras(i);
				}
				//Fun��o mostra as 5 palavras e d� tempo para jogar decorar		
				mostraPalavras();
				//Recebe a resposta do jogador
				pedePalavras();
				//Variavel de acertos do jogador recebe retorno da fun��o verificaPalavras, retorna quantidade de acertos
				(*jgdor).acertos = verificaPalavras();
				//Verifica quantidade de acertos e imprime uma mensagem correspondente ao numero de acertos
				verificaGanhador(Jogador.acertos, Jogador.nome);
				break;
				
			case 2:
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
				//Chamada da fun��o para jogador cadastrar as palavras
				cadastrarPalavras();
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
