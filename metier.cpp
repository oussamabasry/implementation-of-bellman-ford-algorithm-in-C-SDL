#include "headers.h"


// Permet de creer un element  Data c'est les donnees d'un nœud
Data *createData(int x, int y, int index)
{
    Data *data;
    data = (Data *)malloc(sizeof(Data));
    data->x = x;
    data->y = y;
    data->index = index;
    return data;
}

// Permet de creer un nœud
Element *createElement(int x, int y, int valuation, int index)
{
    Element *elem;
    elem = (Element *)malloc(sizeof(Element));
    elem->data = createData(x, y, index);
    elem->data->valuation = valuation;
    elem->next = NULL;
    return elem;
}

// Permet d'ajouter un seccesseur à un nœud
void addElementList(Element **L, Element *suiv, int valuation)
{
    Element *elem;
    elem = createElement(suiv->data->x, suiv->data->y, valuation, suiv->data->index);
    if (*L == NULL)
    {
        *L = elem;
        return;
    }

    Element *p;
    p = *L;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = elem;
}

// Permet d'ajouter un nœud à notre tableau
void addElementNode(Graph *G, int x, int y, int valuation)
{
    Element *elem;
    elem = createElement(x, y, valuation, G->numberNode);
    //G->tab=(Element**)realloc(G->tab,sizeof(Element*)*(G->numberNode+1));
    //printf("\nhiiii");
    G->tab[G->numberNode] = elem;
    G->numberNode++;
}

// Permet d'afficher les successeurs d'un nœud
void displayList(Element *L)
{
    while (L != NULL)
    {
        printf("(%d,%d,%d) - ", L->data->x, L->data->y, L->data->valuation);
        L = L->next;
    }
}


// Cette fonction permet de creer et initialiser un graphe
Graph *createGraph()
{

    Graph *gr;
    gr = (Graph *)malloc(sizeof(Graph));
    gr->numberNode = 0;
    gr->tab = (Element **)malloc(sizeof(Element **) * 1000);
    return gr;
}

// Permet de chercher un nœud de notre graphe
// et qui retourne son adresse
Element *searchTab(Graph *G, int x, int y)
{
    for (int i = 0; i < G->numberNode; i++)
    {
        if (G->tab[i]->data->x == x && G->tab[i]->data->y == y)
            return G->tab[i];
    }
    return NULL;
}
