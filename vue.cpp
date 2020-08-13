#include <SDL2/SDL.h>
#include <cstdlib>
#include "headers.h"



int vue(Graph *G)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* pWindow{ nullptr };
    SDL_Renderer* pRenderer{ nullptr };

    if (SDL_CreateWindowAndRenderer(800,600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(pWindow,"Projet de Graphes");




    bool isOpen{ true };
    SDL_Rect rect1={10,10,50,50};
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pRenderer);
    SDL_RenderPresent(pRenderer);

    SDL_Point mouse;



    while (isOpen)
    {
        SDL_Event events;
        while (SDL_PollEvent(&events))
        {

            switch(events.type){

                case SDL_QUIT:
                    isOpen=false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouse.x=events.motion.x-(events.motion.x%100);
                    mouse.y=events.motion.y-(events.motion.y%100);
                    if(searchTabNode(G,mouse.x/100,mouse.y/100)==1){

                    }else {
                        rect1.x=mouse.x;
                        rect1.y=mouse.y;
                        SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
                        SDL_RenderFillRect(pRenderer, &rect1);
                        SDL_RenderPresent(pRenderer);
                        addElementNode(G,rect1.x/100,rect1.y/100,0);
                    }


                default:continue;

            }


        }

    repere(pRenderer);

    }

    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;

}

void repere( SDL_Renderer* pRenderer){

   SDL_Point pointA;
   SDL_Point pointB;
   int i;

   for(i=0;i<800;i+=100){
    pointA.y=0;
    pointB.y=600;
    pointA.x=i;
    pointB.x=i;
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
    SDL_RenderPresent(pRenderer);
   }
    for(i=0;i<800;i+=100){
    pointA.y=i;
    pointB.y=i;
    pointA.x=0;
    pointB.x=800;
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
    SDL_RenderPresent(pRenderer);
   }

}



/*
else if(events.key.keysym.sym == SDLK_d && events.type==SDL_KEYDOWN)
            {
                   SDL_Point pointA;
                   SDL_Point pointB;
                   printf("\ndebut");
                   SDL_Event ev;
                   SDL_WaitEvent(&ev);
                   pointA.x=events.motion.x-(events.motion.x%100);
                   pointA.y=events.motion.y-(events.motion.y%100);
                   printf("\nmilieu");
                   SDL_WaitEvent(&ev);
                   pointB.x=events.motion.x-(events.motion.x%100);
                   pointB.y=events.motion.y-(events.motion.y%100);
                    printf("\nfin");

                  SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
                  SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
                  SDL_RenderPresent(pRenderer);
*/
