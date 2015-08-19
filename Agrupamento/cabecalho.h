#ifndef CABECALHO_H_INCLUDED
#define CABECALHO_H_INCLUDED
extern int NUM_GADOS;
extern int NUM_FAMILIAS;

typedef struct Lista_Gados{
    int id_animal;
    struct Lista_Gados* prox;
}Lista_Gados;

typedef struct Carga_Genetica {
    int cod_familiar;
    double carga_genetica;
    struct cGenetica* prox;
}cGenetica;

typedef struct Gados{
    int cod_animal;
    int cod_pai;
    int cod_mae;
    char sexo;
    char dt_nascimento[10];
    int familia;
    //para nao aloca muita memoria desnecessaria as estruturas de dados escolhidas sao listas oara estes casos:
    struct cGenetica* cargas_geneticas;//matriz[600][600] já nao roda. entao precisei usar lista
    struct Lista_Gados* filhos;
}Gado;

///*Procedimento para realizar a leitura do arquivo*/
void leituraArquivo(Gado* gados[]);

///*Procedimento para atribuir uma familia a um animal*/
void Atribuir_familia(Gado* gados[],int i,int familia);

///*Procedimento para atribui familias para todos os animais*/
void AtribuiFamiliaToda(Gado* gados[]);

///*Procedimento que imprime cod do animal, pai e mae, sexo, data de nascimento e familia de um animal*/
void imprime_gado(Gado* gado);

///*Procedimento para imprimir uma lista inteira de animais*/
void Imprime_Lista_Gado(Gado* gados[]);

///*Procedimento para identificar/contar os animais que nao possuem pai(somente), mae(somente) ou pai e mae*/
void Imprime_Orfaos(Gado* gados[]);

///*Procedimento para identificar/contar os animais machos e as femeas*/
void Imprime_Sexo(Gado* gados[]);

///*Procedimento para identificar/contar os animais que possuem uma data de nascimento conhecida*/
void Imprime_Dt_Nascimento(Gado* gados[]);

///*Procedimento para atribuir uma lista de filhos a um animal*/
void Atribui_Lista_Filhos(Gado* gados[]);

///*Procedimento para identificar os animais com mais de "500" filhos*/
void Contador_de_Filhos(Gado* gados[]);

///*Procedimento para imprimir a lista de filhos de um animal*/
void Imprime_Lista_Filhos(Gado* gados[], int i);

///*Procedimento para imprimir a lista de gados pertecentes a uma familia passada por parametro*/
void Imprime_familia(Gado* gados[], int id_familia);

///*Procedimento para dizer a qual familia um gado(parametro) pertence*/
void imprimeIDFamiliaGado (Gado* gado);

///*Funcao que retorna o numero de filhos de um animal*/
int numFilhos (Gado* gados[], int cod_animal);

///*Procedimento que atribui uma relacao de parentesco (c_genetica) em um animal*/
void atribuiFatorGenetico(Gado* gados[], int cod_animal, int cod_pai, double fator);

///*Procedimento que atribui carga genetica para todos os gados*/
void calculaCargasGenticas(Gado* gados[]);

///*Procedimento para imprimir as cargas geneticas que compoem um animal*/
void imprimeCargaGeneticaBoi(Gado* gado);

///*Procedimento para imprimir a carga genetica de todos os animais*/
void imprimeTodasCargasGeneticas(Gado* gados[]);

///*Funcao retorna verdadeiro se o animal possui carga genetica de um familiar(parametro) senão retorna falso*/
int exiteGargaGenetica (Gado* gado, int cod_familiar);

///*Procedimento que imprime o cod_animal de gados que nao possuem filhos*/
void imprimeGadosSemFilhos(Gado* gados[]);

///*Procedimento apenas para conhecer a base de dados. (Somente para testes)*/
void imprimeNumeroMembrosFamilia (Gado* gado[]);


#endif // CABECALHO_H_INCLUDED
