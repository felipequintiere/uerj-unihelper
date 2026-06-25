#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/macros.h"
#include "../include/types.h"
#include "../include/util.h"
#include "../include/ler_entrada.h"
#include "../include/buscar_registro_nome.h"

void buscar_registro_nome(const char * const arquivo)
{
	char     entrada[NOME_LEN+1];
	Membro  *membro = (Membro*) malloc(sizeof(Membro));

	int ultimo_id;
	if ((ultimo_id = id_unico_prox(arquivo)) == 0) {
		PRINT_STR(RED,
			  "\nnão há dados armazenados em '%s'!\n",
			  arquivo);
		return;
	}

	system("clear||cls");
	PRINT_STR(PURPLE,"BUSCAR REGISTRO POR NOME:\n");

	PRINT_STR(GREEN,"insira o texto: ");
	ler_entrada(NOME_LEN+1,entrada);
	int count = 0;
	for (int id = 0; id < ultimo_id; id++) {
		arquivo_para_registro(membro,id,arquivo);

		if (strstr(membro->nome,entrada) != NULL &&
			membro->status_de_validacao != 0) {
			printf("\n----------------------------------------\n");
			mostrar_registro(membro);
			count++;
		}
	}

	if (count)
		printf("\n----------------------------------------\n");
	else
		PRINT_STR(RED,"\nnenhum resultado encontrado!\n");
}
