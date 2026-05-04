### UNIHELPER - SISTEMA DE GERENCIAMENTO ACADÊMICO

#### Instalação
``` bash
git clone https://github.com/felipequintiere/uerj-unihelper.git
cd uerj-unihelper
make all && make clean
```

#### Uso do programa
```bash
$ ./unihelper --help
Usage: ./a.out [OPTION]... [FILE]...

  -f, --file <FILE>        path to data file
  -v, --version     output version information and exit
  -h, --help        display this help and exit
```
nota: caso não seja especificado um arquivo por meio da flag `-f`, o arquivo de destino padrão `dados.bin` será usado

---
&nbsp;


#### **Domínio da Aplicação**

Consiste em um sistema de gerenciamento acadêmico para a administração de informações de alunos e docentes. O `unihelper` permite o cadastro, edição, consulta e remoção de registros acadêmicos e gestão de grades horárias.

#### **Informações Gerenciadas**

1. **Registro Principal**
    ```c
    typedef struct {  // ESTRUTRURA COMUM ENTRE OS TIPOS
        //bool status_de_validacao;
        short int status_de_validacao;  // indicador de remoção
        unsigned int id_unico;  // gerado automaticamente

        //signed char nome[NOME_LEN+1];
        char nome[NOME_LEN+1]; // fgets espera 'char *' e não 'unsigned char*'
        int numero_de_disciplinas;
        int grade[DIAS][TURNOS];
        // grade de horários [i][j]
        //     i: dias da semana (seg <-> sex)
        //     j: horários (m1 <-> t3 <-> n6)
        // nota: os elementos são os códigos de disciplinas

        // nota: tamanho variável do tipo enum
        enum {ALUNO = 0, PROFESSOR} tipo;
        union {
            Dados_aluno aluno;
            Dados_professor professor;
        } dados;
        // nota: structs/unions anônimos são padrão apenas a partir
        // do C11
    } Membro;
    ```

1. **Registro do aluno**
    ```c
    typedef struct {  // ESTRUTURA ALUNO
        unsigned long long matricula;
        unsigned short int periodo;
    } Dados_aluno;
    ```

1. **Registro do professor**
    ```c
    typedef struct {  // ESTRUTURA PROFESSOR
        unsigned long long registro;
        float salario;
    } Dados_professor;
    ```

---

&nbsp;
#### **Operações desenvolvidas**

0. Escolha do arquivo de leitura/escrita dos dados\
    `$ ./unihelper -f "nome_do_arquivo"`

1. Criação de Registros\
    cadastro de novos alunos e professores\
    preenchimento de dados pessoais e acadêmicos\
    definição de grades horárias

1. Edição de Registros\
    modificação de informações pessoais\
    atualização de grades horárias\
    adição/remoção de disciplinas (alunos) ou turmas (professores)\
    restauração de registros previamente removidos

1. Remoção de Registros\
    exclusão lógica de registros (marcado como inválido)

1. Busca e Consulta\
    Busca por ID único\
    Busca por nome (por parte do nome)

1. Visualização\
    exibição detalhada de registros individuais\
    listagem completa: exibição de todos os registros ativos

1. Persistência de Dados\
    armazenamento em arquivo binário\
    estrutura de registro fixa (451 bytes por entrada)
