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
	char entrada[NOME_LEN+1];
	int ultimo_id;
	Membro *membro = (Membro*) malloc(sizeof(Membro));

	if ( (ultimo_id = id_unico_prox(arquivo)) == 0)
	{
		PRINT_STR(RED,"\nnão há dados armazenados em '%s'!\n",arquivo);
		return;
	}

	system("clear||cls");
	PRINT_STR(PURPLE,"BUSCAR REGISTRO POR NOME:\n");

	PRINT_STR(GREEN,"insira o texto: ");
	ler_entrada(NOME_LEN+1,entrada);
	int count = 0;
	for (int id=0; id<ultimo_id; id++)
	{
		arquivo_para_registro(membro,id,arquivo);
		if (strstr(membro->nome,entrada) != NULL && 
			membro->status_de_validacao != 0)
		{
			printf("\n----------------------------------------\n");
			mostrar_registro(membro);	
			count++;
		}
	}
	if (count)
	{
		printf("\n----------------------------------------\n");
	}
	else
	{
		PRINT_STR(RED,"\nnenhum resultado encontrado!\n");
	}
}
/*
// man 3 string
char *strstr(const char *haystack, const char *needle);
		Find the first occurrence of the  substring  needle  in
		the  string  haystack, returning a pointer to the found
		substring.

// man 3 strstr
RETURN VALUE
		These functions return a pointer to the beginning of  the  lo‐
		cated substring, or NULL if the substring is not found.

		If  needle  is  the  empty  string, the return value is always
		haystack itself.
*/

