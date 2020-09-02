#include "headers.h"
#define INFINI 900

int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint, SDL_Renderer *pRenderer)
{

    BellmanTable bellmanTable[G->numberNode][G->numberNode];

    for (int i = 0; i < G->numberNode; i++)
    {
        for (int j = 0; j < G->numberNode; j++)
        {
            bellmanTable[i][j].valeur = INFINI;
            bellmanTable[i][j].x = INFINI;
            bellmanTable[i][j].y = INFINI;
        }
    }

    Element *searchPoint = searchTab(G, initPoint.x, initPoint.y);
    if (searchPoint == NULL)
    {
        return 0;
    }


    bellmanTable[0][searchPoint->data->index].valeur = 0;
    Element *balayage;

    for (int i = 1; i < G->numberNode; i++)
    {

        bellmanTable[i][searchPoint->data->index].valeur = 0;

        for (int j = 0; j < G->numberNode; j++)
        {

            balayage = G->tab[j]->next;
            while (balayage != NULL)
            {

                if (balayage->data->x != searchPoint->data->x && balayage->data->y != searchPoint->data->y)
                {

                    BellmanTable depart = bellmanTable[i - 1][G->tab[j]->data->index];
                    BellmanTable arrive = bellmanTable[i - 1][balayage->data->index];
                    int val = balayage->data->valuation;

                    if (arrive.valeur > depart.valeur + val && depart.valeur + val < bellmanTable[i][balayage->data->index].valeur)
                    {

                        bellmanTable[i][balayage->data->index].valeur = depart.valeur + val;
                        bellmanTable[i][balayage->data->index].x = G->tab[j]->data->x;
                        bellmanTable[i][balayage->data->index].y = G->tab[j]->data->y;
                    }
                    else if (arrive.valeur <= depart.valeur + val && depart.valeur + val < bellmanTable[i][balayage->data->index].valeur)
                    {

                        bellmanTable[i][balayage->data->index].valeur = arrive.valeur;
                        bellmanTable[i][balayage->data->index].x = arrive.x;
                        bellmanTable[i][balayage->data->index].y = arrive.y;
                    }
                }

                balayage = balayage->next;
            }
        }
    }

    for (int i = 0; i < G->numberNode; i++)
    {
        for (int j = 0; j < G->numberNode; j++)
        {
            printf("%d       ", bellmanTable[i][j].valeur);
        }
        printf("\n");
    }

    bool cycleAbsorb = false;
    for (int i = 0; i < G->numberNode; i++)
    {
        if (bellmanTable[G->numberNode - 2][i].valeur != bellmanTable[G->numberNode - 1][i].valeur)
        {
            cycleAbsorb = true;
            break;
        }
    }

    if (cycleAbsorb == false)
    {
        BellmanTable chemin[100];
        int nb = 0;
        int index;
        SDL_Point NodeSearch;
        NodeSearch.x = finalPoint.x;
        NodeSearch.y = finalPoint.y;
        chemin[nb].x = NodeSearch.x;
        chemin[nb].y = NodeSearch.y;
        index = searchTab(G, NodeSearch.x, NodeSearch.y)->data->index;
        chemin[nb].valeur = bellmanTable[G->numberNode - 1][index].valeur;
        nb++;

        for (int i = G->numberNode - 1; i > 0; i--)
        {

            index = searchTab(G, NodeSearch.x, NodeSearch.y)->data->index;
            chemin[nb].x = bellmanTable[i][index].x;
            chemin[nb].y = bellmanTable[i][index].y;
            chemin[nb].valeur = bellmanTable[i][index].valeur;
            NodeSearch.x = chemin[nb].x;
            NodeSearch.y = chemin[nb].y;
            nb++;
            if (NodeSearch.x == initPoint.x && NodeSearch.y == initPoint.y)
            {
                chemin[nb].x = initPoint.x;
                chemin[nb].y = initPoint.y;
                break;
            }
        }

        afficherPlusCourtChemin(pRenderer, chemin, nb);
    }
    else
    {
        text(pRenderer, (char *)"Le graphe contient un circuit absorbant !!", 18, 450, 525, 255, 0, 127);
    }

    return 1;
}
