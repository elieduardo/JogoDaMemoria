#include <stdio.h>
#include <stdlib.h>
#include "Arquivos.h"
#include "Jogo.h"


/*
*Variáveis Globais
*/
char palavra[5][20];
char resposta[5][20];
//Variável que captura a palavra cadastrada
char novapalavra[20];

/*
Objetivo: contar o numero de palavras existente.
Verifica se encontrou o arquivo, caso contrario
ele sai da função.
Executado um loop que vai verificar char por char
e a cada char ' ' ou '\n' adiciona +1 na variável da contagem.
No fim, ele fecha o arquivo e retorna a contagem de palavras.
*/
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

/*
Objetivo:sortear 5 palavras do arquivo txt
Primeiro há a verificação se o arquivo existe.
Criado uma variavel do tipo int que será o retorno da função contagemPalavras,
este função retornará o numero de palavras no arquivo.
Após isso, cria um gerador numérico randomico com limite do numero de palavras.
Este gerador randomico serve para escolher aleatoriamente 5 palavras 
que estejam no arquivo.

*/
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

	//Imprime na tela a palavras escolhidas randomicamente
	for(int j = 0; j <= randomico; j++) {
		fscanf(f, "%s", palavra[i]);
	}
	
	//Fecha o arquivo
	fclose(f);	
}

/*
Objetivo: cadastrar palavra informada pelo jogador no arquivo txt
Input da palavra.
Atribui palavra no arquivo.
Pergunta se usuario deseja adicionar outra palavra.
*/
void cadastrarPalavrasFacil(){
	
	//Verifica se arquivo existe
	FILE* f;
	f = fopen("facil.txt", "r+");
	if(f == 0) {
		printf("Banco de dados de palavras não disponível\n\n");
		exit(1);
	}
	
	printf("Digite a nova palavra, em letras maiúsculas: ");
	scanf("%s", novapalavra);
	
	
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
		cadastrarPalavrasFacil();
	}else{
		exit(1);
	}		
}

/*
Objetivo: cadastrar palavra informada pelo jogador no arquivo txt
Input da palavra.
Atribui palavra no arquivo.
Pergunta se usuario deseja adicionar outra palavra.
*/
void cadastrarPalavrasMedio(){
	
	printf("Digite a nova palavra, em letras maiúsculas: ");
	scanf("%s", novapalavra);
	FILE* f;
	
	//Verifica se arquivo existe
	f = fopen("medio.txt", "r+");
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
		cadastrarPalavrasMedio();
	}else{
		exit(1);
	}
}

/*
Objetivo: cadastrar palavra informada pelo jogador no arquivo txt
Input da palavra.
Atribui palavra no arquivo.
Pergunta se usuario deseja adicionar outra palavra.
*/
void cadastrarPalavrasDificil(){
	
	printf("Digite a nova palavra: ");
	scanf("%s", novapalavra);
	FILE* f;
	
	//Verifica se arquivo existe
	f = fopen("dificil.txt", "r+");
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
		cadastrarPalavrasFacil();
	}else{
		exit(1);
	}
}


