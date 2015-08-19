#include <stdio.h>
#include <stdlib.h>
#include "cabecalho.h"

void menu();
int NUM_GADOS=92492;
int NUM_FAMILIAS=3959;
cGenetica* criaCGeneticaVazia(){
    cGenetica* carga_genetica;
    carga_genetica= (cGenetica*) malloc (sizeof(cGenetica));
    carga_genetica->cod_familiar=0;
    carga_genetica->carga_genetica=0;
    carga_genetica->prox=NULL;
}
Gado* cria_gado(){
    Gado* li;
    li = (Gado*) malloc (sizeof(Gado));
    li->cod_animal=NULL;
    li->cod_mae=NULL;
    li->cod_pai=NULL;
    li->sexo=NULL;
    li->filhos=NULL;
    li->familia=NULL;
    li->cargas_geneticas=NULL;
    return li;
}
Lista_Gados* Cria_Lista_Gados(){
    struct Lista_Gados* filho;
    filho= (struct Lista_Gados*) malloc (sizeof(struct Lista_Gados));
    filho->id_animal=0;
    filho->prox=NULL;
    return filho;
}
/*Procedimento para realizar a leitura do arquivo*/
void leituraArquivo(Gado* gados[]){
    Gado* gado_aux= cria_gado();//ponteiro para a estrutura que eh salva da leitura do arquivo
    int i;
    for(i=0;i<NUM_GADOS;i++){
        gados[i]=NULL;
    }
    FILE* txt = fopen("ENTRADA1.txt","r");// leitura ; ENTRADA
    if(txt == NULL){// Se arquivo não encontrado retorna NULL
        printf("\nErro a abrir arquivo!");
    }
    else{
//        printf("Ocorreu tudo bem na abertura do arquivo!!!\n\n");
        while((fscanf(txt,"%d,%d,%d,%c,%s\n",&gado_aux->cod_animal,&gado_aux->cod_pai, &gado_aux->cod_mae,&gado_aux->sexo, &gado_aux->dt_nascimento))!= EOF){
                gados[gado_aux->cod_animal]=gado_aux;
                gado_aux=cria_gado();
//                printf("animal %d cadastrado com sucesso!\n", vetor_gados[gado_aux->cod_animal]->cod_animal);
        }
    }
    fclose(txt);
}
/*Procedimento para atribuir uma familia a um animal*/
void Atribuir_familia(Gado* gados[],int i,int familia){
    if(gados[i]!=NULL){
        if(gados[i]->familia==NULL){//nao tem familia entao atribui uma para ele
//            printf("atribuindo familia %d para gado %d\n", familia, i);
            gados[i]->familia=familia;

            if(gados[i]->cod_pai!=0){//o pai tambem tem que ser da mesma familia do filho
                Atribuir_familia(gados,gados[i]->cod_pai,familia);
            }
            if(gados[i]->cod_mae!=0){//a mae tambem tem que ser da familia do filho
                Atribuir_familia(gados,gados[i]->cod_mae,familia);
            }
            if (gados[i]->filhos!=NULL){//todos os filhos devem ser da familia do pai
                struct Lista_Gados* aux= gados[i]->filhos;
                while(aux!=NULL){
                    Atribuir_familia(gados,aux->id_animal,familia);
                    aux=aux->prox;
                }
            }
        }
        ///apenas para testes:
//        else{
//            int d;
//            if(li[i]->familia!=familia){
//                printf(("QUEREM ME TROCAR DE FAMILIA! SOCORRO!!!\n"));
//                scanf("&d");
//            }
//        }
    }
}
/*Procedimento para atribui familias para todos os animais*/
void AtribuiFamiliaToda(Gado* gados[]){
    int i;
    int familia=1;//contador do total de familias separaveis de um vetor de gados (utilizado para atribuir a variavel global NUM_FAMILIAS)
    for(i=1;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->familia==NULL){
                Atribuir_familia(gados,i,familia);
                familia++;
            }
            ///somente para teste:
//        }else{
//            printf("nao existe gado com o codigo %d\n",i);
        }
    }
    printf("O numero de familias eh %d\n", (familia-1));
}
/*Procedimento que imprime cod do animal, pai e mae, sexo, data de nascimento e familia de um animal*/
void imprime_gado(Gado* gado){
    printf("animal\t pai\tmae\tsexo\tdt_nascimento\t\tfamilia\n");
    printf("%d\t%d\t%d\t%c\t%s\t\t%d\n", gado->cod_animal, gado->cod_pai,gado->cod_mae,gado->sexo, gado->dt_nascimento, gado->familia);
}
/*Procedimento para imprimir uma lista inteira de animais*/
void Imprime_Lista_Gado(Gado* gados[]){
    Gado* aux;
    int cont=0;//contador de gados (utilizado para atribuir a variavel global NUM_GADOS)
    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            cont++;
            imprime_gado(gados[i]);
        }
    }
//    printf("tem %d gados nesta lista.\n", cont);
}
/*Procedimento para identificar/contar os animais que nao possuem pai(somente), mae(somente) ou pai e mae*/
void Imprime_Orfaos(Gado* gados[]){
    int cont=0;//contador do numero de orfaos de pai e mae (somente para analise da base)
    int cont_pai=0;//contador dos orfaos de pai que tem mae (somente para analise da base)
    int cont_mae=0;//contador dos orfaos de mae que tem pai (somente para analise da base)
    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->cod_pai==0 && gados[i]->cod_mae==0){
//                printf("o gado %d nao possui pai nem mae cadastrado\n", li[i]->cod_animal);
                cont++;
           }else if(gados[i]->cod_pai==0){
//                printf("o gado %d nao possui pai cadastrado\n", li[i]->cod_animal);
                cont_pai++;
            }else if(gados[i]->cod_mae==0){
//                printf("o gado %d nao possui mae cadastrada\n", li[i]->cod_animal);
                cont_mae++;
            }
        }
    }
    printf("tem %d gados sem pai e mae\n", cont);
    printf("tem %d gados sem pai \n", cont_pai);
    printf("tem %d gados sem mae\n", cont_mae);
}
/*Procedimento para identificar/contar os animais machos e as femeas*/
void Imprime_Sexo(Gado* gados[]){
    int cont_macho=0;//contador de machos(somente para analisar a base)
    int cont_femea=0;//contador de femeas (somente para analisar a base)
    int cont=0;//contador de animais com sexo desconhecido (somente para analisar a base)

    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->sexo=='F'){
//                printf("o gado %d eh femea\n", li[i]->cod_animal);
                cont_femea++;
            }else if(gados[i]->sexo=='M'){
//                printf("o gado %d eh macho\n", li[i]->cod_animal);
                cont_macho++;
            }else{
//                printf("não sabe o sexo do gado %d.\n", li[i]->cod_animal);
                cont++;
            }
        }
    }
        printf("tem %d femeas e %d machos\n", cont_macho,cont_femea);
        printf("tem %d animais em que se desconhece o sexo\n", cont);
}
/*Procedimento para identificar/contar os animais que possuem uma data de nascimento conhecida*/
void Imprime_Dt_Nascimento(Gado* gados[]){
    int cont_possui=0;//contador dos gados que possuem data de nascimento conhecida (somente para analisar a base)
    int cont_nao_possui=0;//contador dos gados que não possuem data de nascimento conhecida (somente para analisar a base)

    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->dt_nascimento[0]=='/'){
//                printf("o gado %d nao possui data de nascimento.\n", li[i]->cod_animal);
                cont_nao_possui++;
            }
            else{
//                printf("o gado %d possui data de nascimento igual a %s\n", li[i]->cod_animal, li[i]->dt_nascimento);
                cont_possui++;
            }
        }
    }
    printf("%d gados que nao possuem data de nascimento\n%d gados possuem data de nascimento\n",cont_nao_possui, cont_possui);
}
/*Procedimento para atribuir uma lista de filhos a um animal*/
void Atribui_Lista_Filhos(Gado* gados[]){
    int i;
    Lista_Gados* aux;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->cod_pai!=NULL){//se possui pai, entao vai no animal e o coloca na lista de filhos
                aux= gados[gados[i]->cod_pai]->filhos;
                if(aux==NULL){//este pai ainda nao tem um filho
                    gados[gados[i]->cod_pai]->filhos=Cria_Lista_Gados();
                    gados[gados[i]->cod_pai]->filhos->id_animal=gados[i]->cod_animal;
                }else{
                   while(aux->prox!=NULL){//o filho sera inserido na ultima posição
                        aux=aux->prox;
                    }
                    aux->prox=Cria_Lista_Gados();
                    aux->prox->id_animal=gados[i]->cod_animal;
                }
            }
            if(gados[i]->cod_mae!=NULL){//se possui mae, entao vai na vaca e o coloca na lista de filhos
                aux= gados[gados[i]->cod_mae]->filhos;
                if(aux==NULL){
                    gados[gados[i]->cod_mae]->filhos=Cria_Lista_Gados();
                    gados[gados[i]->cod_mae]->filhos->id_animal=gados[i]->cod_animal;//atribuição
                }else{
                   while(aux->prox!=NULL){
                        aux=aux->prox;
                    }
                    aux->prox=Cria_Lista_Gados();
                    aux->prox->id_animal=gados[i]->cod_animal;//atribuição
                }
            }
        }
    }
//    printf("lista de filhos atribuida com sucesso!!\n \n");
}
/*Procedimento para identificar os animais com mais de "500" filhos*/
void Contador_de_Filhos(Gado* gados[]){
    int vet[92492]={0};//cada posição do vetor representa um gado (posicao=cod_animal)
    int i;
    int cont=0;//contar o numero de filhos
    int maior=0;//verificar o gado que possui maior numero de filhos
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->cod_pai!=0){
                vet[gados[i]->cod_pai]=vet[gados[i]->cod_pai]+1;
            }
            if(gados[i]->cod_mae!=0){
                vet[gados[i]->cod_mae]=vet[gados[i]->cod_mae]+1;
            }
        }
    }
    ///somente para testes:
    for (i=0;i<NUM_GADOS;i++){
        if(vet[i]>maior){
            maior=vet[i];
        }
        if(vet[i]>0){
//            printf("o animal %d tem %d filhos\n",i, vet[i]);
            cont++;
            if(vet[i]>500){//apenas os animais que possuem mais de 500 filhos
                printf("o gado %d possui %d filhos\n", i, vet[i]);
            }
        }

   }
    printf("%d gados possuem filhos, o maximo de filhos eh %d\n", cont, maior);
}
/*Procedimento para imprimir a lista de filhos de um animal*/
void Imprime_Lista_Filhos(Gado* gados[], int i){
    if(gados[i]!=NULL){//existe filhos
        if(gados[i]->filhos!=NULL){//percorrer a lista de filhos
            Lista_Gados* aux=gados[i]->filhos;
            printf("\nO animal %d eh pai de:",gados[i]->cod_animal);
            while(aux!=NULL){
                printf(" %d, ",aux->id_animal);
                aux=aux->prox;
            }
            printf("\n");
        }
    }else{
        printf("O gado %d não possui filhos.\n", gados[i]->cod_animal);
    }
}
/*Procedimento para imprimir a lista de gados pertecentes a uma familia passada por parametro*/
void Imprime_familia(Gado* gados[], int id_familia){
    int i;
    int cont=0; //conta numero de bois da familia (somente para teste)
    for(i=1;i<NUM_GADOS;i++){
        if(gados[i]!=NULL && gados[i]->familia==id_familia){
            printf("o gado %d pertence a familia %d\n", gados[i]->cod_animal,gados[i]->familia);
            cont++;
        }
    }
    printf("Esta familia possui %d gados\n", cont);
}
/*Procedimento para dizer a qual familia um gado(parametro) pertence*/
void imprimeIDFamiliaGado (Gado* gado){
    if(gado!=NULL){
        if(gado->familia!=NULL)
            printf("\nO gado %d esta na familia: %d\n", gado->cod_animal, gado->familia);
    }
}
/*Funcao que retorna o numero de filhos de um animal*/
int numFilhos (Gado* gados[], int cod_animal){
    int cont = 0;//contador de filhos
    Lista_Gados* aux = gados[cod_animal]->filhos;
    while(aux != NULL){
        cont++;
        aux = aux->prox;
    }
    return cont;
}
/*Procedimento que atribui uma relacao de parentesco (c_genetica) em um animal*/
void atribuiFatorGenetico(Gado* gados[], int cod_animal, int cod_pai, double fator){
    if(gados[cod_animal]->cargas_geneticas==NULL){
       //inserir primeiro grau de parentesco
        cGenetica* aux2= criaCGeneticaVazia();
        aux2->carga_genetica=fator;
        aux2->cod_familiar=cod_pai;
        aux2->prox=NULL;
        gados[cod_animal]->cargas_geneticas=aux2;
    }else{
        int flag = 0;
        cGenetica* aux = gados[cod_animal]->cargas_geneticas; //ponteiro para varrer as cargas geneticas
        cGenetica* ultimo = gados[cod_animal]->cargas_geneticas;

        while(aux!=NULL){
            if (aux->cod_familiar == cod_pai){
                if(aux->carga_genetica<fator){
                    aux->carga_genetica=fator;
            /*quando um gado possui duas cargas geneticas provindas*/
            /* de um mesmo gado ascendente:Prevalece a maior!*/
                }
                flag = 1;
                break;
            }
            ultimo=aux;
            aux=aux->prox;
        }
        if (!flag){
            cGenetica* aux2= criaCGeneticaVazia(); //inserir esse no em todos os filhos
            aux2->carga_genetica=fator;
            aux2->cod_familiar=cod_pai;
            aux2->prox=NULL;
            ultimo->prox=aux2;
        }
    }

    Lista_Gados* filho=gados[cod_animal]->filhos;
    while(filho!=NULL){
        atribuiFatorGenetico(gados, filho->id_animal, cod_pai, (fator/2));
        filho=filho->prox;
    }
}
/*Procedimento que atribui carga genetica para todos os gados*/
void calculaCargasGenticas(Gado* gados[]){
    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            Lista_Gados* filho=gados[i]->filhos;
            while(filho!=NULL){
                atribuiFatorGenetico(gados, filho->id_animal, i, 0.5);
                filho=filho->prox;
            }
        }
    }
}
/*Procedimento para imprimir as cargas geneticas que compoem um animal*/
void imprimeCargaGeneticaBoi(Gado* gado){
    if(gado!=NULL){
        cGenetica* aux=gado->cargas_geneticas;
        while(aux!=NULL){
            printf("A carga genetica do animal %d para o animal %d eh: %.4f\n", gado->cod_animal, aux->cod_familiar, aux->carga_genetica);
///somente para teste:
//            if(exiteGargaGenetica(li[cod_animal],aux->cod_familiar)){
//                printf("Erro!! Carga repetida!!");
//            }
            aux=aux->prox;
        }
    }
    else{
        printf("não existe animal com o codigo %d", gado->cod_animal);
    }
}
/*Procedimento para imprimir a carga genetica de todos os animais*/
void imprimeTodasCargasGeneticas(Gado* gados[]){
    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->cargas_geneticas!=NULL){
                imprimeCargaGeneticaBoi(gados[i]);
            }
        }
    }
}
/*Funcao retorna verdadeiro se o animal possui carga genetica de um familiar(parametro) senão retorna falso*/
int exiteGargaGenetica (Gado* gado, int cod_familiar){

    cGenetica* carga = gado->cargas_geneticas;
    while(carga != NULL){
        if(carga->carga_genetica == cod_familiar){
            return 1;
        }
        carga = carga->prox;
    }
    return 0;
}
/*Procedimento que imprime o cod_animal de gados que nao possuem filhos*/
void imprimeGadosSemFilhos(Gado* gados[]){
    int i;
    int cont=0;//conta numero de gados sem filhos
     printf("o gado %d não possui filhos1111\n", i);
    for(i=0;i<NUM_GADOS;i++){
        if(gados[i]!=NULL){
            if(gados[i]->filhos==NULL){
                printf("o gado %d nao possui filhos;\n", i);
                cont++;
            }
        }
    }
    printf("tem %d gados sem filhos nesta base.\n", cont);
}
/*Procedimento apenas para conhecer a base de dados. (Somente para testes)*/
void imprimeNumeroMembrosFamilia (Gado* gado[]){
    int tam_familias[3960]={0};
    int i;
    for(i=0;i<NUM_GADOS;i++){
        if(gado[i]!=NULL){
            if(gado[i]->familia!=NULL){
                tam_familias[gado[i]->familia]=(tam_familias[gado[i]->familia])+1;
                if(tam_familias[gado[i]->familia]==24){
                    printf("A familia %d tem 24 gados\n",gado[i]->familia);
                }
            }else{
                printf("Uai! Tem gente sem familia ai...\n");
            }
        }
    }


    printf("Ja coloquei todos os gados em suas familias\n\n");
    printf("a familia 162 possui %d membros\n", tam_familias[162]);
    int num_familias[30]={0};
    for(i=0;i<3960;i++){
        if(tam_familias[i]<30){
            num_familias[tam_familias[i]]++;
        }else{
            num_familias[29]++;
        }
    }

    for(i=20;i<30;i++){
        printf("tem %d familias com %d gados\n", num_familias[i], i);
    }
}
