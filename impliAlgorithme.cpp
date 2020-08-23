#include "headers.h"
#define INFINI 90000000


int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint){

    BellmanTable bellmanTable[G->numberNode][G->numberNode];

    bellmanTable[0][0]=0;
    for(int i=1;i<G->numberNode;i++){
        bellmanTable[0][i]=INFINI;
    }
    Element *balayage;

    for(int i=0;i<G->numberNode-1;i++){
    for(int j=0;j<G->numberNode;j++){
          balayage=G->tab[i];
        while(balayage->next!=NULL){
            if(bellmanTable[i][])

            balayage=balayage->next;
        }
    }
    }
}
