#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <SDL2/SDL.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
// structure qui contient les coordonnes et la valiation
typedef struct
{
    int x;
    int y;
    int valuation;
    int index;
} Data;

// structure element c'est liste simplement chainèe
typedef struct Elem
{
    Data *data;
    struct Elem *next;
} Element;

// structure graphe c'est un tableau d'adresse des élements
typedef struct
{
    int numberNode;
    Element **tab;
} Graph;

// structure BellmanTable qui represente le tableau de calcul
// de l'algo de bellman ford
typedef struct
{
    int valeur;
    int x;
    int y;
} BellmanTable;

Data *createData(int x, int y);
Element *createElement(int x, int y, int valuation, int index);
void addElementList(Element **L, Element *suiv, int valuation);
void displayList(Element *L);
int vue(Graph *G);
Graph *createGraph();
void addElementNode(Graph *G, int x, int y, int valuation);
Element *searchTab(Graph *G, int x, int y);
void text(SDL_Renderer *pRenderer, char *text, int fontSize, int x, int y, int R, int G, int B);
bool conditionNumber(SDL_Event event);
void audioAlert();
int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint, SDL_Renderer *pRenderer);
void afficherPlusCourtChemin(SDL_Renderer *pRenderer, BellmanTable chemin[], int nb);
void Draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height, int red, int green, int blue);
void Draw_arc(SDL_Renderer *renderer, SDL_Point pointA, SDL_Point pointB, SDL_Point *departLine, SDL_Point *arriveLine);

#endif // HEADERS_H_INCLUDED
