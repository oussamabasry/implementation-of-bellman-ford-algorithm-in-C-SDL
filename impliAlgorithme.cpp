#include "headers.h"
#define INFINI 9000

int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint, SDL_Renderer *pRenderer)
{
    // Declaration de la table de calcul
    BellmanTable bellmanTable[G->numberNode][G->numberNode];

    // Initialiser la table tout la table avec la valeur infini
    for (int i = 0; i < G->numberNode; i++)
    {
        for (int j = 0; j < G->numberNode; j++)
        {
            bellmanTable[i][j].valeur = INFINI;
            bellmanTable[i][j].x = INFINI;
            bellmanTable[i][j].y = INFINI;
        }
    }

    // chercher l'adresse du nœud source
    Element *searchPoint = searchTab(G, initPoint.x, initPoint.y);
    if (searchPoint == NULL)
    {
        return 0;
    }

    // Initialiser la valeur du nœud source avec la valeur 0 à la premiere iteration
    bellmanTable[0][searchPoint->data->index].valeur = 0;

    Element *balayage;

    for (int i = 1; i < G->numberNode; i++)
    {
        // Initialiser la valeur du nœud source avec la valeur 0 à chaque itération
        bellmanTable[i][searchPoint->data->index].valeur = 0;
        // Pour chaque nœud du tableau
        for (int j = 0; j < G->numberNode; j++)
        {
            // Visiter tous les seccesseurs de cet nœud
            balayage = G->tab[j]->next;
            while (balayage != NULL)
            {

                // des affectation juste pour simplifier les expressions
                BellmanTable depart = bellmanTable[i - 1][G->tab[j]->data->index];
                BellmanTable arrive = bellmanTable[i - 1][balayage->data->index];
                int val = balayage->data->valuation;

                if (arrive.valeur > depart.valeur + val &&
                    depart.valeur + val < bellmanTable[i][balayage->data->index].valeur)
                {

                    bellmanTable[i][balayage->data->index].valeur = depart.valeur + val;
                    bellmanTable[i][balayage->data->index].x = G->tab[j]->data->x;
                    bellmanTable[i][balayage->data->index].y = G->tab[j]->data->y;
                }
                else if (arrive.valeur <= depart.valeur + val &&
                         depart.valeur + val < bellmanTable[i][balayage->data->index].valeur)
                {

                    bellmanTable[i][balayage->data->index].valeur = arrive.valeur;
                    bellmanTable[i][balayage->data->index].x = arrive.x;
                    bellmanTable[i][balayage->data->index].y = arrive.y;
                }

                // Passage au seccesseur suivant
                balayage = balayage->next;
            }
        }
    }

    // Imprimer les valeurs à la console juste pour vérifer le résultat
    for (int i = 0; i < G->numberNode; i++)
    {
        for (int j = 0; j < G->numberNode; j++)
        {
            printf("%d       ", bellmanTable[i][j].valeur);
        }
        printf("\n");
    }

    // Tester l'existence du circuit absorbant
    bool cycleAbsorb = false;
    for (int i = 0; i < G->numberNode; i++)
    {
        if (bellmanTable[G->numberNode - 2][i].valeur != bellmanTable[G->numberNode - 1][i].valeur)
        {
            cycleAbsorb = true;
            break;
        }
    }

    // Si il n'ya pas de circuit absorbant afficher le plus court chemin
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
    // Si il y a un circuit absorbant afficher un message
    else
    {
        text(pRenderer, (char *)"Le graphe contient un circuit absorbant !!", 18, 450, 525, 255, 0, 127);
    }

    return 1;
}
