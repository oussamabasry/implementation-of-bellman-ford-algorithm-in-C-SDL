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


    SDL_Event events;
    SDL_Event ev;
    bool isOpen{ true };
    SDL_Rect rect1={10,10,50,50};
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
        SDL_RenderClear(pRenderer);
        SDL_RenderPresent(pRenderer);


    while (isOpen)
    {
        while (SDL_PollEvent(&events))
        {

            if(events.type==SDL_QUIT){
                isOpen=false;

            }
            else if(events.type==SDL_MOUSEBUTTONDOWN)
            {
                rect1.x=events.motion.x-(events.motion.x%100);
                rect1.y=events.motion.y-(events.motion.y%100);
               SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
               SDL_RenderFillRect(pRenderer, &rect1);
               SDL_RenderPresent(pRenderer);

               addElementNode(G,rect1.x/100,rect1.y/100,0);

            }
            else if(events.key.keysym.sym == SDLK_d && events.type==SDL_KEYDOWN)
            {

                    SDL_Point pointA;
                    SDL_Point pointB;
                    bool test1=false;


                    do{
                            SDL_PollEvent(&events1)
                     printf("\ndebut do");
                    while(test1==false ){
                      printf("\ndebut while1");
                        if(events.button.button == SDL_BUTTON_LEFT){
                            printf("\ndebut if");
                            pointA.x=events.motion.x-(events.motion.x%100);
                            pointA.y=events.motion.y-(events.motion.y%100);
                            printf("\nle premier point");
                            test1=true;
                        }
                    }

                    while(test1==true){
                        printf("\ndebut while2");
                        if(events.button.button == SDL_BUTTON_LEFT){
                            pointB.x=events.motion.x-(events.motion.x%100);
                            pointB.y=events.motion.y-(events.motion.y%100);
                             printf("\nleq deuxieme point");
                            SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
                            SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
                            SDL_RenderPresent(pRenderer);
                            test1=false;

                        }
                    }
                    if(events.key.keysym.sym == SDLK_d && events.type==SDL_KEYDOWN){
                        break;
                    }
                     printf("\hi");
                    }while(1);





            }
            else if (events.key.keysym.sym == SDLK_w)
            {
                isOpen=false;
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
