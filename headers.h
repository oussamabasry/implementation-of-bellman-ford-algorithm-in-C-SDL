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
    int index;
}Data;

typedef struct Elem{
Data *data;
int valuation;
struct Elem *next;
}Element;

typedef struct{
bool isOriented;
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
void displayGraph(Graph *G);
Graph *createGraph(int numberNode,bool orionted);
int vue(Graph *G);
void repere( SDL_Renderer* pRenderer);
Graph *InitializGraphe(bool isOriented);
void addElementNode(Graph *G,int x,int y,int valuation);
int searchTabNode(Graph *G,int x,int y);
Element *searchTab(Graph *G,int x,int y);
void text(SDL_Renderer* pRenderer, char *text,int fontSize, int x,int y);
bool conditionNumber(SDL_Event event);
void audioAlert();
int Bellman(Graph *G, SDL_Point initPoint, SDL_Point finalPoint);
#endif // HEADERS_H_INCLUDED
