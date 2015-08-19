

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cabecalho.h"

int main()
{
    void menu();
    Gado* vetor_gados[NUM_GADOS];
    leituraArquivo(vetor_gados);//lê arquivo e atribui gados ao vetor_gados.
    Atribui_Lista_Filhos(vetor_gados);
    AtribuiFamiliaToda(vetor_gados);
    Imprime_Orfaos(vetor_gados);
    Imprime_Sexo(vetor_gados);
    Imprime_Dt_Nascimento(vetor_gados);
    Imprime_familia(vetor_gados,1);
    imprime_gado(vetor_gados[4004]);
//    Imprime_Lista_Gado(vetor_gados);
    Imprime_Lista_Filhos(vetor_gados, 4004);
    Contador_de_Filhos(vetor_gados);
    imprimeIDFamiliaGado(vetor_gados[5956]);
    int filhos4004=numFilhos(vetor_gados, 4004);
    printf("o gado 4004 tem %d filhos\n", filhos4004);
    calculaCargasGenticas(vetor_gados);
    imprimeCargaGeneticaBoi(vetor_gados[5956]);
    imprime_gado(vetor_gados[5956]);
    imprime_gado(vetor_gados[2838]);
    imprime_gado(vetor_gados[1609]);
    imprime_gado(vetor_gados[1794]);
    imprime_gado(vetor_gados[373]);
    imprime_gado(vetor_gados[1092]);
    imprime_gado(vetor_gados[1116]);
    imprime_gado(vetor_gados[197]);
    imprimeTodasCargasGeneticas(vetor_gados);
    imprimeGadosSemFilhos(vetor_gados);
//    imprimeNumeroMembrosFamilia(vetor_gados);


    return 0;

    }
