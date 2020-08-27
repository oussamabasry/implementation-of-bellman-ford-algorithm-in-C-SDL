#include "headers.h"
#define INFINI 900


int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint){

    BellmanTable bellmanTable[G->numberNode][G->numberNode];


    for(int i=0;i<G->numberNode;i++){
        bellmanTable[0][i].valeur=INFINI;
        bellmanTable[0][i].x=INFINI;
        bellmanTable[0][i].y=INFINI;
    }

    Element *searchPoint=searchTab(G,initPoint.x,initPoint.y);
    if(searchPoint==NULL)
        return 0;
    bellmanTable[0][searchPoint->data->index].valeur=0;
    Element *balayage;

    for(int i=1;i<G->numberNode;i++){
      bellmanTable[i][searchPoint->data->index].valeur=0;

    for(int j=0;j<G->numberNode;j++){
          balayage=G->tab[j]->next;
        while(balayage!=NULL){

            if(bellmanTable[i-1][balayage->data->index].valeur > bellmanTable[i-1][G->tab[j]->data->index].valeur+ balayage->valuation  ){
              bellmanTable[i][balayage->data->index].valeur=bellmanTable[i-1][G->tab[j]->data->index].valeur+ balayage->valuation;
              bellmanTable[i][balayage->data->index].x=G->tab[j]->data->x;
              bellmanTable[i][balayage->data->index].y=G->tab[j]->data->y;
            }else{
              bellmanTable[i][balayage->data->index].valeur=bellmanTable[i-1][balayage->data->index].valeur;
              bellmanTable[i][balayage->data->index].x=bellmanTable[i-1][balayage->data->index].x;
              bellmanTable[i][balayage->data->index].y=bellmanTable[i-1][balayage->data->index].y;
            }

          if(bellmanTable[i-1][G->tab[j]->data->index].valeur>bellmanTable[i-1][balayage->data->index].valeur+ balayage->valuation ){
              bellmanTable[i][G->tab[j]->data->index].valeur=bellmanTable[i-1][balayage->data->index].valeur+ balayage->valuation;
              bellmanTable[i][G->tab[j]->data->index].x=balayage->data->x;
              bellmanTable[i][G->tab[j]->data->index].y=balayage->data->y;
            }else{
              bellmanTable[i][G->tab[j]->data->index].valeur=bellmanTable[i-1][G->tab[j]->data->index].valeur;
              bellmanTable[i][G->tab[j]->data->index].x=bellmanTable[i-1][G->tab[j]->data->index].x;
              bellmanTable[i][G->tab[j]->data->index].y=bellmanTable[i-1][G->tab[j]->data->index].y;
            }

            balayage=balayage->next;
        }
    }
    bellmanTable[i][searchPoint->data->index].valeur=0;
    }









      for(int i=0;i<G->numberNode;i++){
                for(int j=0;j<G->numberNode;j++){
                    printf("%d       ",bellmanTable[i][j].valeur);
                }
      printf("\n");
      }


    BellmanTable chemin[100];
    int nb=0;
    int index;
    SDL_Point NodeSearch;
    NodeSearch.x=finalPoint.x;
    NodeSearch.y=finalPoint.y;
    chemin[nb].x= NodeSearch.x;
     chemin[nb].y=NodeSearch.y;
     nb++;


    for(int i=G->numberNode-1;i>1;i--){
        printf("\nhi");
        index=searchTab(G,NodeSearch.x,NodeSearch.y)->data->index;
         chemin[nb].x=bellmanTable[i][index].x;
         chemin[nb].y=bellmanTable[i][index].y;
         chemin[nb].valeur=bellmanTable[i][index].valeur;
         NodeSearch.x= chemin[nb].x;
         NodeSearch.y=chemin[nb].y;
         nb++;

            }


    for(int i=0;i<nb-1;i++){
        printf("\n (%d,%d):%d      ",chemin[i].x,chemin[i].y,chemin[i].valeur);
    }
return 1;
}
