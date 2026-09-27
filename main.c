#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// test format specifiers
//#include <stdint.h>
//#include <inttypes.h>

#include "./include/macros.h"
#include "./include/types.h"

#include "./include/flags.h"
#include "./include/util.h"
#include "./include/ler_entrada.h"
#include "./include/criar_registro.h"
#include "./include/editar_registro.h"
#include "./include/remover_registro.h"
#include "./include/buscar_registro_nome.h"

int main(int argc, char *argv[])
{
	/* modificar uma string literal resulta em UB */
	const char *arquivo = "./dados.bin";

	int flag_option;
	while ((flag_option = getopt(argc, argv, "hvf:")) != -1) {
		switch (flag_option) {
		case 'h':
			flag_help(argv[0]);
			exit(EXIT_SUCCESS);
			break;
		case 'v':
			flag_version(argv[0]);
			exit(EXIT_SUCCESS);
			break;
		case 'f':
			arquivo = optarg;
			break;
		case '?':
			exit(EXIT_FAILURE);
			break;
		default:
			break;
		}
	}

	char entrada[ENTRADA_LEN+1] = {0};
	for (;;) {
		PRINT_STR(CYAN,"\n"
			  "[1] criar registro\n"
			  "[2] editar registro\n"
			  "[3] remover registro\n"
			  "[4] buscar registro por id\n"
			  "[5] buscar registro por nome\n"
			  "[6] listar registros\n"
			  "[7-9] sair\n\n");
		PRINT_STR(PURPLE, "Escolha uma opção: ");
		ler_entrada(ENTRADA_LEN + 1, entrada);

		switch (entrada[0]) {
		case '1':
			criar_registro(id_unico_prox(arquivo), arquivo);
			break;
		case '2':
			editar_registro(arquivo);
			break;
		case '3':
			remover_registro(arquivo);
			break;
		case '4':
			system("clear||cls");
			buscar_registro_id(arquivo);
			break;
		case '5':
			buscar_registro_nome(arquivo);
			break;
		case '6': listar_registros(arquivo); // ./src/util.c
			break;
		case '7':
			/* fall through */
		case '8':
		case '9':
			exit(EXIT_SUCCESS);
			break;
		default:
			fprintf(stderr, "opção '%c' inválida!\n", entrada[0]);
			break;
		}
	}
	return EXIT_SUCCESS;
}
