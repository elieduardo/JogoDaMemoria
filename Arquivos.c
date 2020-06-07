#include <stdio.h>
#include <stdlib.h>
#include "Arquivos.h"
#include "Jogo.h"


//Variáveis Globais
char palavra[5][20];
char resposta[5][20];

//Função conta quantas palavras existem no arquivo txt
int contagemPalavras(char arquivo[15]){
	char c;
	FILE *fp;
	int count = 0;
	int flag = 0;

	//Verifica se arquivo existe
	if ((fp=fopen(arquivo, "r"))==NULL)
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

//Função que sorteia 5 palavras do arquivo txt
void sorteioPalavras(int i, char arquivo[15]){
	FILE* f;		
	
	//Verifica se arquivo existe
	f = fopen(arquivo, "r");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}

	//Atribui quantidade de palavras que existem no arquivo
	int qtddepalavras = contagemPalavras(arquivo);
	
	//Gerador randômico de numero com limite do numero de palavras no txt
	//srand(time(NULL));
	int randomico = rand() % qtddepalavras;


	for(int j = 0; j <= randomico; j++) {
		fscanf(f, "%s", palavra[i]);
	}
	
	//Fecha o arquivo
	fclose(f);	
}

void cadastrarPalavras(){
	
	//Variável que captura a palavra cadastrada
	char novapalavra[20];

	printf("Digite a nova palavra, em letras maiúsculas: ");
	scanf("%s", novapalavra);

	FILE* f;

	//Verifica se arquivo existe
	f = fopen("teste.txt", "r+");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
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
	printf("Você gostaria de cadastrar outra palavra? (S/N)");
	scanf(" %c", &ask);
	
	//Verifica resposta
	if(ask == 'S') {			
		cadastrarPalavras();
	}else{
		exit(1);
	}
}



