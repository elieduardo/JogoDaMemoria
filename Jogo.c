#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <time.h>

//Vari�veis Globais
int dificuldade;
char palavra[5][20];
char resposta[5][20];

//Cria��o da struct
struct jogador{
	char nome[20];
	int  acertos;
};

/*
Objetivo: cronometro
Inteiro recebido no parametro ser� o numero de 
segundos que o programa ir� "travar"
*/
void cronometro (int segundos)
{
  clock_t fimtempo;
  fimtempo = clock () + segundos * CLK_TCK;
  while (clock() < fimtempo) {}
}


/*
Objetivo: Imprime na tela as 5 palavras randomicamente escolhidas.
Ir� imprimir 5 palavras e depois chamar� a fun��o cronometro
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
Depois de mostrado as 5 palavras, esta fun��o ser� 
chamada para obter a resposta do jogador.
*/
void pedePalavras(){
	system ("cls");
	printf ("Informe as palavras que foram exibidos\n\n");
	
	for (int i = 0; i < 5; i++){
		printf ("\t%d� palavra: ", i+1);
		scanf ("%s", resposta[i]);
	}
}

/*
Objetivo: verifica numero de acertos do jogador e imprime 
senten�a correspondente ao numero de acertos.
Verifica acertos e imprime resposta com switch case e depois
pede se jogador deseja voltar ao menu ou sair do jogo.
*/
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

/*
Objetivo: verificar input do jogador.
Utilizando fun��o que compara duas strings, esta fun��o ira comparar 
a resposta do jogador com a palavra mostrada.
*/
int verificaPalavras(){
	int aux = 0;
	for(int i = 0; i <= 4; i ++){
		//Utiliza fun��o que compara as duas palavras
		int retorno = strcasecmp(resposta[i], palavra[i]);				
		if(retorno == 0){
			aux ++;
		}
	}
	return aux;
}

