#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <time.h>

//Variáveis Globais
int dificuldade;
char palavra[5][20];
char resposta[5][20];

//Criação da struct
struct jogador{
	char nome[20];
	int  acertos;
};

/*
Objetivo: cronometro
Inteiro recebido no parametro será o numero de 
segundos que o programa irá "travar"
*/
void cronometro (int segundos)
{
  clock_t fimtempo;
  fimtempo = clock () + segundos * CLK_TCK;
  while (clock() < fimtempo) {}
}


/*
Objetivo: Imprime na tela as 5 palavras randomicamente escolhidas.
Irá imprimir 5 palavras e depois chamará a função cronometro
que dara tempo ao jogador para decorar essas palavras.
*/
void mostraPalavras(int tempo){	
	// j recebe o valor do tempo
	int j= tempo;	
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


/*
Objetivo: pede o input das palavras.
Depois de mostrado as 5 palavras, esta função será 
chamada para obter a resposta do jogador.
*/
void pedePalavras(){
	system ("cls");
	printf ("Informe as palavras que foram exibidos\n\n");
	
	for (int i = 0; i < 5; i++){
		printf ("\t%d° palavra: ", i+1);
		scanf ("%s", resposta[i]);
	}
}

/*
Objetivo: verifica numero de acertos do jogador e imprime 
sentença correspondente ao numero de acertos.
Verifica acertos e imprime resposta com switch case e depois
pede se jogador deseja voltar ao menu ou sair do jogo.
*/
void verificaGanhador(int acertos, char nome[20]){
	int opc;
	
	//Mostra mensagem conforme numero de acertos
	switch(acertos){
			case 0:
				printf("NOSSA %s, você não é MUITO ruim de memória não acertou nenhuma palavra (PROCURE UM MÉDICO URGENTE) \n", nome);
			break;
			case 1:
				printf("Que pena %s, você não é MUITO ruim de memória acertou 1 palavra (PROCURE UM MÉDICO) \n", nome);
			break;
			case 2:
				printf("Que pena %s, você não é MUITO ruim de memória acertou 2 palavra (FIQUE ATENTO)\n", nome);
			break;
			case 3:
				printf("Que pena %s, você não tem uma memória razoável acertou 3 palavra\n", nome);
			break;
			case 4:
				printf("Que pena %s, por pouco você não conseguiu ganhar acertou 4 palavra\n", nome);
			break;
			default:
				printf("PARABÉNS %s! VOCÊ ACERTOU TODAS AS PALAVRAS...\n", nome);
			break;
		}
	
	system("pause");
	
	//Pergunta se jogador que voltar para o menu ou se quer sair do jogo
	system ("cls");
	printf("----- Jogo da memória -----\n");
	printf("(1) Voltar ao Menu\n");
	printf("(0) Sair\n");
	scanf("%d", &opc);
	if(opc == 0){
		exit(1);
	}
}

/*
Objetivo: verificar input do jogador.
Utilizando função que compara duas strings, esta função ira comparar 
a resposta do jogador com a palavra mostrada.
*/
int verificaPalavras(){
	int aux = 0;
	for(int i = 0; i <= 4; i ++){
		//Utiliza função que compara as duas palavras
		int retorno = strcasecmp(resposta[i], palavra[i]);				
		if(retorno == 0){
			aux ++;
		}
	}
	return aux;
}

