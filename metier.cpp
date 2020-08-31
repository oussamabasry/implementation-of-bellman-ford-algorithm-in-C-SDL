#include"headers.h"


Data *createData(int x,int y, int index){
Data *data;
data=(Data*)malloc(sizeof(Data));
data->x=x;
data->y=y;
data->index=index;
return data;
}

Element* createElement(int x,int y,int valuation, int index){
Element *elem;
elem=(Element*)malloc(sizeof(Element));
elem->data=createData(x,y,index);
elem->data->valuation=valuation;
elem->next=NULL;
return elem;
}


void addElementList(Element **L,Element *suiv,int valuation){
Element *elem;
 elem=createElement(suiv->data->x,suiv->data->y,valuation,suiv->data->index);
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
  elem=createElement(x,y,valuation,G->numberNode);
  //G->tab=(Element**)realloc(G->tab,sizeof(Element*)*(G->numberNode+1));
  //printf("\nhiiii");
  G->tab[G->numberNode]=elem;
  G->numberNode++;
}

void displayList(Element *L){
while(L!=NULL){
    printf("(%d,%d,%d) - ",L->data->x,L->data->y,L->data->valuation);
    L=L->next;
}
}



Graph *createGraph(int numberNode,bool isOriented){
Graph *gr;
int i;

gr=(Graph*)malloc(sizeof(Graph));
gr->numberNode=numberNode;
gr->tab=(Element**)malloc(sizeof(Element**)*gr->numberNode);
for(i=0;i<gr->numberNode;i++)
{
    gr->tab[i]=NULL;
}

return gr;
}

Graph *InitializGraphe(){
Graph *gr;


gr=(Graph*)malloc(sizeof(Graph));
gr->numberNode=0;
gr->tab=(Element**)malloc(sizeof(Element**)*1000);
/*gr->tab=(Element**)malloc(sizeof(Element**)*gr->numberNode);
for(i=0;i<gr->numberNode;i++)
{
    gr->tab[i]=NULL;
}*/

return gr;
}


Element* searchTab(Graph *G,int x,int y){
  for(int i=0;i<G->numberNode;i++)
   {
      if(G->tab[i]->data->x==x&&G->tab[i]->data->y==y)
        return G->tab[i];
   }
 return NULL;
}

