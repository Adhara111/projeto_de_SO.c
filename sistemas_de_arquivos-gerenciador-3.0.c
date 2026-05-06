#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> //para listar arquivos
#include <unistd.h> // navegar em diretorios
#include <sys/stat.h>//criar diretorios

//declaração de funções ?

void listarArquivos();
void mudarDiretorio(char *caminho);
void criarPasta(char *nome);
void removerArquivo(char *nome);
void mostrarArquivo(char *nome);
void mostrarTutorial();
int criarArquivo();
void escreverArquivo(char *nome);
void adicionarArquivo(char *nome);

int main() {
    char comando[100];
    char cwd[1024];
    char opcao;

    // Menu inicial
    printf("Deseja ver o tutorial? (s/n): ");
    scanf(" %c", &opcao);
    getchar(); //limpa alguma coisa

    if (opcao == 's' || opcao == 'S') {
        mostrarTutorial();//autoexplicativo
    }

    while (1) {
        // pegar diretório atual

        getcwd(cwd, sizeof(cwd));
        printf("\n[%s] >> ", cwd);

        fgets(comando, sizeof(comando), stdin);
        comando[strcspn(comando, "\n")] = 0;

        if (strcmp(comando, "exit") == 0) {
            break;
        }
        else if (strcmp(comando, "ls") == 0) {
            listarArquivos();
        }
        else if (strncmp(comando, "cd ", 3) == 0) {
            mudarDiretorio(comando + 3);//(comando + 3)=operadores para identificar pocisção no vetor
        }
        else if (strncmp(comando, "mkdir ", 6) == 0) {
            criarPasta(comando + 6);
        }
        else if (strncmp(comando, "rm ", 3) == 0) {
            removerArquivo(comando + 3);
        }
        else if (strncmp(comando, "cat ", 4) == 0) {
            mostrarArquivo(comando + 4);
        }
        else if (strcmp(comando, "touch") == 0) {
        criarArquivo();
        }
        else if (strncmp(comando, "write ", 6) == 0) {
            escreverArquivo(comando + 6);
        }
        else if (strncmp(comando, "append ", 7) == 0) {
            adicionarArquivo(comando + 7);
        }
        else if (strcmp(comando, "help") == 0) {
            mostrarTutorial();
        }
        else {
            printf("Comando inválido! Digite 'help' para ver os comandos.\n");//genial
        }
    }

    return 0;
}
//autoexplicativo 2.0

void mostrarTutorial() {
    printf("\n=== COMANDOS DISPONÍVEIS ===\n");
    printf("ls              -> listar arquivos\n");
    printf("cd <dir>        -> mudar diretório\n");
    printf("mkdir <nome>    -> criar pasta\n");
    printf("rm <arquivo>    -> remover arquivo\n");
    printf("cat <arquivo>   -> mostrar conteúdo\n");
    printf("touch           -> cria arquivo\n");
    printf("write           -> escreve no arquivo(sobrescreve)\n");
    printf("append          -> adicionar conteudo\n");
    printf("help            -> mostrar comandos\n");
    printf("exit            -> sair\n");
    printf("===========================\n");
}

void listarArquivos() {
    struct dirent *d;
    DIR *dir = opendir(".");

    if (dir == NULL) {
        printf("Erro ao abrir diretório\n");
        return;
    }

    while ((d = readdir(dir)) != NULL) {
        printf("%s\n", d->d_name);
    }

    closedir(dir);
}

void mudarDiretorio(char *caminho) {
    if (chdir(caminho) != 0) {
        printf("Erro ao mudar diretório\n");
    }
}

void criarPasta(char *nome) {
    if (mkdir(nome, 0777) == 0)/*(0777) permisão do diretorio no linux em base octal
                                0777 = rwx (dono) rwx (grupo) rwx (outros) todos podem ler, escrever e acessar :o
                                [não recomendado em sistemas reais]*/
    {
        printf("Pasta criada\n");
    } else {
        printf("Erro ao criar pasta\n");
    }
}

void removerArquivo(char *nome) {
    if (remove(nome) == 0) {
        printf("Arquivo removido\n");
    } else {
        printf("Erro ao remover\n");
    }
}

void mostrarArquivo(char *nome) {
    FILE *f = fopen(nome, "r");
    char c;

    if (f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }

    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }

    fclose(f);
}
int criarArquivo()
{
    FILE *f = fopen("novo_arquivo.txt", "w");

    if (f == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 0;
    }

    fclose(f);
    printf("Arquivo 'novo_arquivo.txt' criado com sucesso!\n");

    return 1;
}


   void escreverArquivo(char *nome)
{
    FILE *f = fopen(nome, "w");
    char texto[500];

    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o conteudo ('.' para encerrar): \n");

    while(1){
        fgets(texto, sizeof(texto), stdin);
        texto[strcspn(texto, "\n")] = 0;

        if(strcmp(texto, ".") == 0){
            break;
        }

        fprintf(f, "%s\n", texto); // FALTAVA ISSO
    }

    fclose(f);
    printf("Conteudo escrito com sucesso!\n");
}

/*void adicionarArquivo(char *nome)
{
   void adicionarArquivo(char *nome)
{
    FILE *f = fopen(nome, "a");
    char texto[500];

    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o conteudo para adicionar ('.' para encerrar): \n");

    while(1){
        fgets(texto, sizeof(texto), stdin);
        texto[strcspn(texto, "\n")] = 0;

        if(strcmp(texto, ".") == 0){
            break;
        }

        fprintf(f, "%s\n", texto);
    }

    fclose(f);
    printf("Conteudo adicionado com sucesso!\n");
}
}*/
void adicionarArquivo(char *nome)
{
    FILE *f = fopen(nome, "a");
    char texto[500];

    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("Digite o conteudo para adicionar ('.' para encerrar): \n");

    while(1){
        fgets(texto, sizeof(texto), stdin);
        texto[strcspn(texto, "\n")] = 0;

        if(strcmp(texto, ".") == 0){
            break;
        }

        fprintf(f, "%s\n", texto);
    }

    fclose(f);
    printf("Conteudo adicionado com sucesso!\n");
}
