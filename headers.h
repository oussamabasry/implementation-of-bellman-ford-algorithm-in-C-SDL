#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>




typedef  struct {
    int x;
    int y;
}Data;

typedef struct Elem{
Data *data;
bool visited;
int valuation;
struct Elem *next;
}Element;

typedef struct{
bool isOriented;
int numberNode;
Element **tab;
}Graph;




/*typedef struct{
Element *head;
}AdjencyList;*/


Data *createData(int x,int y);
Element* createElement(int x,int y,int valuation);
void addElementList(Element **L,int x,int y,int valuation);
void displayList(Element *L);
void displayGraph(Graph *G);
Graph *createGraph(int numberNode,bool orionted);
int vue(Graph *G);
void repere( SDL_Renderer* pRenderer);
Graph *InitializGraphe(bool isOriented);
void addElementNode(Graph *G,int x,int y,int valuation);

#endif // HEADERS_H_INCLUDED
