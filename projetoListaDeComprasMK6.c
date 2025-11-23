#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

float soma = 0;

void menu() {
    printf("--------------Menu--------------\n");
    printf("1 - Inserir novos produtos\n");
    printf("2 - Ver o valor Total da Compra\n");
    printf("3 - Sair\n");
    printf(" \n ");
}
//Altera o nome do arquivo conforme o input do usuario
void obterNomeArquivo(char *mes, char *nomeArquivo) {
    snprintf(nomeArquivo, 50, "%s.csv", mes);
    system("cls");
}
//Verifica se o arquivo existe
int arquivoExiste(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file) {
        fclose(file);
        return 1;//Retorna 1 se o arquivo existe
    }
    return 0;
}
//Struct para armazena as informações dos produtos
struct produtos {
    char nome[50];
    int quantidade;
    float valor;
};

struct produtos produtos[50];
//Ler o valor antigo do arquivo
float lerTotalAntigo(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");//Abre o arquivo para leitura
    if (!file) return 0; //Se não conseguir abrir, retorna 0

    char linha[200];
    float ultimoTotal = 0;
	//Loop que passa pelo arquivo todo
    while (fgets(linha, sizeof(linha), file)) {
    	//Procura pela linha que contém o total
        if (sscanf(linha, ";;;;TOTAL: R$ %f", &ultimoTotal) == 1) {
            //Se encontrar, pega o valor
        }
    }

    fclose(file);
    return ultimoTotal; //Retorna o valor encontrado
}

void reescreverArquivoSemTotal(char *nomeArquivo, char *tempArquivo) {
    FILE *original = fopen(nomeArquivo, "r");
    if (!original) return; //Se não existir, não faz nada

    FILE *temporario = fopen(tempArquivo, "w");
    if (!temporario) {
        fclose(original);
        return;
    }

    char linha[200];
    int primeiraLinha = 1;

    //Copia o cabeçalho e os produtos, ignorando o total
    while (fgets(linha, sizeof(linha), original)) {
        float valor;
        //Verifica se é a linha do total
        if (sscanf(linha, ";;;;TOTAL: R$ %f", &valor) == 1) {
            continue; //pula essa linha
        }
        
        //Mantém o cabeçalho original
        fputs(linha, temporario);
    }
    fclose(original);
    fclose(temporario);
	//Altera o nome do arquivo para que não crie uma planilha temp, que salva os dados anteriores, apagando o original e renomenando o novo
    remove(nomeArquivo);//Original
    rename(tempArquivo, nomeArquivo);//Novo
}

void adicionarItem(char *nomeArquivo) {
	//Verifica se o arquivo existe
    int arquivoJaExistia = arquivoExiste(nomeArquivo);
    
    if (arquivoJaExistia) {
        soma = lerTotalAntigo(nomeArquivo);
        reescreverArquivoSemTotal(nomeArquivo, "temp.csv");
    } else {
        soma = 0;
    }

    FILE *file;
    int alt, inseriu = 0;
    int i = 0; //Índice corrigido para começar em 0

    //Abre o arquivo no modo apropriado
    if (arquivoJaExistia) {
        file = fopen(nomeArquivo, "a"); //Adiciona ao final se já existe
    } else {
        file = fopen(nomeArquivo, "w"); //Cria o cabeçalho mas apenas se não existir, em arquivos novos
        fprintf(file, "Produto;Quantidade;Valor\n");
    }

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
	//Entrada de novos produtos
    do {
        system("cls");
        printf("Nome do produto: ");
        scanf(" %[^\n]", produtos[i].nome);

        printf("Quantidade: ");
        scanf("%d", &produtos[i].quantidade);

        printf("Preço: ");
        scanf("%f", &produtos[i].valor);

        float subtotal = produtos[i].quantidade * produtos[i].valor;
        soma += subtotal;

        //Adiciona o produto na próxima linha do arquivo
        fprintf(file, "%s;%d;%.2f\n", produtos[i].nome, produtos[i].quantidade, produtos[i].valor);
        inseriu = 1;

        printf("Item adicionado com sucesso!\n");
        printf(" \n ");
        //Loop para não ter limite de entrada de dados, caso o usuario não saiba de cabeça quantos produtos deseja registrar
        printf("Deseja continuar? (1 - Sim | 2 - Não)\n");
        printf(" = ");
        scanf("%d", &alt);
        //Se não for continuar ele limpa a tela com essa condicional
        if (alt == 2){
        	system("cls");
		}
        i++;
    } while (alt == 1);

    //Adiciona o total no final
    fprintf(file, ";;;;TOTAL: R$ %.2f\n", soma);
    fclose(file);

    if (!inseriu) {
        printf("Nenhum item foi inserido, mas o total foi atualizado.\n");
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    char nomePlanilha[40], nomeArquivo[50];
    int op;
	//Entrada do nome do arquivo
    printf("Digite o nome para a lista de compras: ");
    scanf(" %[^\n]", nomePlanilha);
    obterNomeArquivo(nomePlanilha, nomeArquivo);
	//Verifica e altera o resultado final da soma, para que ela não fique não mesma linha do arquivo CSV anterior(Foi a forma de resolver o bug do total ficar no meio da planilha)
    if (arquivoExiste(nomeArquivo)) {
        soma = lerTotalAntigo(nomeArquivo);
    } else {
        soma = 0;
    }

    do {
        menu();
        printf(" = ");
        scanf("%d", &op);
        system("cls");

        switch (op) {
            case 1:
            	//Criar item
                adicionarItem(nomeArquivo);
                break;
            case 2:
            	//Apresenta o total da compra
                printf("Total da Compra: R$ %.2f\n\n", soma);
                break;
            case 3:
            	//Fecha o codigo
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (op != 3);

    return 0;
}
