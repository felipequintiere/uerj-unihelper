#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #include <stdint.h>
// #include <inttypes.h>  // format specifiers

#include "./include/macros.h"
#include "./include/types.h"

#include "./include/flags.h"
#include "./include/util.h"
#include "./include/ler_entrada.h"
#include "./include/criar_registro.h"
#include "./include/editar_registro.h"
#include "./include/remover_registro.h"
#include "./include/buscar_registro_nome.h"

#define ARQUIVO_DADOS "./dados.bin"

int main(int argc, char *argv[])
{
	char *arquivo = ARQUIVO_DADOS;

	if (argc >= 2)
	{
		// mesmo que os if's dentro desse compound statement sejam
		// mutuamente exclusivos, o uso do `else if` foi apenas
		// empregado para maior clareza
		if (!strcmp("-h",argv[1]) || !strcmp("--help",argv[1]))
		{
			flag_help(argv[0]); // argv[0]: nome do programa
			exit(EXIT_SUCCESS);
		}

		else if (!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version"))
		{
			flag_version(argv[0]);
			exit(EXIT_SUCCESS);
		}

		else if (!strcmp(argv[1],"-f") || !strcmp(argv[1],"--file"))
		{
			if (argc == 2)
			{
				fprintf(stderr,
					"error: a value is required for '--file <FILE>' but none "
					"was supplied\n\nFor more information, try '--help'.\n"
				);
				exit(EXIT_FAILURE);
			}

			else if (argc > 3)
			{
				fprintf(stderr,
					"error: unrecognized subcommand '%s'"
					"\n\nFor more information, try '--help'.\n", argv[3]
				);
				exit(EXIT_FAILURE);
				// argv[3]: quarto argumento passado para o programa
			}

			else
			{
				// nesse caso, são passados exatamente três argumentos
				// (incluindo o nome do programa)
				//     ./nome_do_programa -f nome_do_arquivo

				// se o arquivo não existir, o programa pode exigir que o
				// usuário o crie manualmente; basta descomentar o bloco
				// abaixo
				/*
				FILE *fp;
				if ((fp = fopen(argv[2],"rb")) == NULL)
				{
					fprintf(stderr,
						"error: file '%s' does not exist\n",argv[2]
					);
					exit(EXIT_FAILURE);
				}
				fclose(fp);
				*/

				arquivo = argv[2]; // armazena o nome do arquivo escolhido
				PRINT_DEBUG("\nnome do arquivo escolhido: %s\n",arquivo);
			}
		}

		else
		{
			flag_invalid(argv);	// passa todos os argumentos
			exit(EXIT_FAILURE);
		}
	}

#if !defined(DEBUG)
	system("clear||cls");
#elif defined(DEBUG) && DEBUG==0
	system("clear||cls");
#endif

	char entrada[ENTRADA_LEN+1] = {0};

	for (;;)
	{
		PRINT_STR(CYAN,"\n"
		"[1] criar registro\n"
		"[2] editar registro\n"
		"[3] remover registro\n"
		"[4] buscar registro por id\n"
		"[5] buscar registro por nome\n"
		"[6] listar registros\n"
		"[7-9] sair\n\n");
		PRINT_STR(PURPLE,"Escolha uma opção: ");

		ler_entrada(ENTRADA_LEN+1,entrada);	
		//		   scanf(" %c", &option); 
		// nota:
		// Em uma entrada como "abcde...", esse scanf leria o
		// primeiro caractere, porém, os demais ficariam dentro
		// do input buffer. Consequentemente, as próximas
		// chamadas do scanf leriam esses valores armazenados no
		// buffer 

		switch (entrada[0])
		{
			// ./src/criar_registro.c
			case '1': criar_registro(id_unico_prox(arquivo),arquivo);
				break;
			case '2': editar_registro(arquivo); // ./src/editar_registro.c
				break;
			case '3': remover_registro(arquivo); // ./src/remover_registro.c
				break;
			case '4': 
				system("clear||cls");
				buscar_registro_id(arquivo); // ./src/util.c
				break;
			case '5': buscar_registro_nome(arquivo); // ./src/buscar_registro_nome.c
				break;
			case '6': listar_registros(arquivo); // ./src/util.c
				break;
			case '7':
			case '8':
			case '9': exit(EXIT_SUCCESS);

			default:
				fprintf(stderr,"opção '%c' inválida!\n",entrada[0]);
		}
	}
	return EXIT_SUCCESS;
}
