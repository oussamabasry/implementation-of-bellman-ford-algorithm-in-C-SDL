#include"headers.h"


Data *createData(int x,int y){
Data *data;
data=(Data*)malloc(sizeof(Data));
data->x=x;
data->y=y;
return data;
}

Element* createElement(int x,int y,int valuation){
Element *elem;
elem=(Element*)malloc(sizeof(Element));
elem->data=createData(x,y);
elem->valuation=valuation;
elem->visited=false;
elem->next=NULL;
return elem;
}


void addElementList(Element **L,int x,int y,int valuation){
Element *elem;
 elem=createElement(x,y,valuation);
if(*L==NULL){
    *L=elem;
    return;
}
Element *p; p=*L;
while(p->next!=NULL)
    p=p->next;
p->next=elem;
}

void addElementNode(Graph *G,int x,int y,int valuation){
Element *elem;
  elem=createElement(x,y,valuation);
  //G->tab=(Element**)realloc(G->tab,sizeof(Element*)*(G->numberNode+1));
  //printf("\nhiiii");
  G->tab[G->numberNode]=elem;
  G->numberNode++;
}

void displayList(Element *L){
while(L!=NULL){
    printf("(%d,%d,%d) - ",L->data->x,L->data->y,L->valuation);
    L=L->next;
}
}



Graph *createGraph(int numberNode,bool isOriented){
Graph *gr;
int i;

gr=(Graph*)malloc(sizeof(Graph));
gr->isOriented=isOriented;
gr->numberNode=numberNode;
gr->tab=(Element**)malloc(sizeof(Element**)*gr->numberNode);
for(i=0;i<gr->numberNode;i++)
{
    gr->tab[i]=NULL;
}

return gr;
}

Graph *InitializGraphe(bool isOriented){
Graph *gr;


gr=(Graph*)malloc(sizeof(Graph));
gr->isOriented=isOriented;
gr->numberNode=0;
gr->tab=(Element**)malloc(sizeof(Element**)*1000);
/*gr->tab=(Element**)malloc(sizeof(Element**)*gr->numberNode);
for(i=0;i<gr->numberNode;i++)
{
    gr->tab[i]=NULL;
}*/

return gr;
}



void displayGraph(Graph *G){
int i;
Element *elem;
printf("\n ******************* Display ************************\n\n");
printf("(element): -->xy:edge -->y:edge -->.....\n\n");
for(i=0;i<G->numberNode;i++)
{    elem=G->tab[i];
    while(elem!=NULL){
    printf("%d%d -> ",elem->data->x,elem->data->y);
    elem=elem->next;
   }
   printf("null\n");
}

}


int searchTabNode(Graph *G,int x,int y){
  for(int i=0;i<G->numberNode;i++)
   {
      if(G->tab[i]->data->x==x&&G->tab[i]->data->y==y)
        return 1;
   }
 return 0;
}

Element* searchTab(Graph *G,int x,int y){
  for(int i=0;i<G->numberNode;i++)
   {
      if(G->tab[i]->data->x==x&&G->tab[i]->data->y==y)
        return G->tab[i];
   }
 return NULL;
}

