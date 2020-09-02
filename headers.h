#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED


#include <SDL2/SDL.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>



typedef  struct {
    int x;
    int y;
    int valuation;
    int index;
}Data;

typedef struct Elem{
Data *data;
struct Elem *next;
}Element;

typedef struct{
int numberNode;
Element **tab;
}Graph;


typedef struct{
    int valeur;
    int x;
    int y;
}BellmanTable;




Data *createData(int x,int y);
Element* createElement(int x,int y,int valuation, int index);
void addElementList(Element **L,Element *suiv,int valuation);
void displayList(Element *L);
Graph *createGraph(int numberNode);
int vue(Graph *G);
Graph *InitializGraphe();
void addElementNode(Graph *G,int x,int y,int valuation);
Element *searchTab(Graph *G,int x,int y);
void text(SDL_Renderer* pRenderer, char *text,int fontSize, int x,int y, int R, int G, int B);
bool conditionNumber(SDL_Event event);
void audioAlert();
int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint, SDL_Renderer* pRenderer);
void afficherPlusCourtChemin(SDL_Renderer* pRenderer, BellmanTable chemin[],int nb);

#endif // HEADERS_H_INCLUDED
