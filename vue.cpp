#include <SDL2/SDL.h>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "headers.h"
#include<string.h>





int vue(Graph *G)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }



    SDL_Window* pWindow{ nullptr };
    SDL_Renderer* pRenderer{ nullptr };

    if (SDL_CreateWindowAndRenderer(1300,600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
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
    SDL_Point pointA;
    SDL_Point pointB;
    int le_cout;

    bool boolPointA=false;
    bool boolPointB=false;
    bool testSaisieCout=false;
    char coutArret[10]="";
    int i=5;

    Element *searchElem;
   /* TTF_Font *police = NULL;
    police = TTF_OpenFont("arial.ttf", 20);
    SDL_Surface* text = TTF_RenderText_Blended(police, "Algorithme de bellman ford", SDL_Color{ 0, 255, 0, 255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, text);
    SDL_Rect position;
    SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
    position.x = 830;
    position.y = 40;
    SDL_FreeSurface(text);
    TTF_CloseFont(police);
*/

if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        return -1;
    }

    Mix_Music* music = Mix_LoadMUS("audio.mp3");

if (music == nullptr)
{
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
    Mix_CloseAudio();
    SDL_Quit();
    return -1;
}



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
                  {
                    strcpy(coutArret,"");
                    mouse.x=events.motion.x-(events.motion.x%100);
                    mouse.y=events.motion.y-(events.motion.y%100);
                    searchElem=searchTab(G,mouse.x/100,mouse.y/100);
                    if(searchElem!=NULL){
                            if(boolPointA==false){
                                  pointA.x=mouse.x;
                                  pointA.y=mouse.y;
                                  boolPointA=true;
                            }else if(boolPointA==true&& boolPointB==false){
                                 pointB.x=mouse.x;
                                 pointB.y=mouse.y;
                                 SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
                                 if(pointA.x<pointB.x && pointA.y<pointB.y){
                                    SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y+50, pointB.x, pointB.y);
                                 }else if(pointA.x>pointB.x && pointA.y<pointB.y){
                                   SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y+50, pointB.x+50, pointB.y);
                                 }else if(pointA.x>pointB.x && pointA.y>pointB.y){
                                    SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x+50, pointB.y+50);
                                 }else if(pointA.x<pointB.x && pointA.y>pointB.y){
                                    SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y, pointB.x, pointB.y+50);
                                 }else if(pointA.x==pointB.x && pointA.y<pointB.y){
                                   SDL_RenderDrawLine(pRenderer, pointA.x+25, pointA.y+50, pointB.x+25, pointB.y);
                                 }else if(pointA.x==pointB.x && pointA.y>pointB.y){
                                 SDL_RenderDrawLine(pRenderer, pointA.x+25, pointA.y, pointB.x+25, pointB.y+50);
                                 }else if(pointA.y==pointB.y && pointA.x>pointB.x){
                                   SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y+25, pointB.x+50, pointB.y+25);
                                 }else if(pointA.y==pointB.y && pointA.x<pointB.x){
                                     SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y+25, pointB.x, pointB.y+25);
                                 }

                                 SDL_RenderPresent(pRenderer);
                                 //printf("\ndonner le cout:");
                                // scanf("%d",&le_cout);
                                 i+=40;
                                 text(pRenderer,(char *)"Saisir le cout de l'arret",17,1000,i);
                                // audioAlert();
                                Mix_PlayMusic(music, 1);
                                 boolPointA=false;
                                 boolPointB=false;


                            }
                    }else {
                        if(mouse.x<1000){

                            rect1.x=mouse.x;
                            rect1.y=mouse.y;
                            SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 255);
                            SDL_RenderFillRect(pRenderer, &rect1);
                            SDL_RenderPresent(pRenderer);

                            char coordonnes[20]="";
                            char buffer[20];
                            itoa(rect1.x/100,buffer,10);
                            strcat(coordonnes,buffer);
                            strcat(coordonnes," , ");
                            itoa(rect1.y/100,buffer,10);
                            strcat(coordonnes,buffer);
                            text(pRenderer,coordonnes,17,mouse.x+12,mouse.y+21);
                            strcpy(coordonnes,"");


                            addElementNode(G,rect1.x/100,rect1.y/100,0);


                        }

                    }
                  }

            case SDL_KEYDOWN:
                {

                  if(events.key.keysym.sym == SDLK_ESCAPE){
                        SDL_Point mileu;

                        if(pointA.x<pointB.x && pointA.y<pointB.y){
                                   // SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y+50, pointB.x, pointB.y);
                                    mileu.x=((pointA.x+50+pointB.x)/2);
                                    mileu.y=((pointA.y+50+pointB.y)/2);
                                 }else if(pointA.x>pointB.x && pointA.y<pointB.y){
                                   //SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y+50, pointB.x+50, pointB.y);
                                   mileu.x=((pointA.x+pointB.x+50)/2);
                                   mileu.y=((pointA.y+50+pointB.y)/2);
                                 }else if(pointA.x>pointB.x && pointA.y>pointB.y){
                                   // SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x+50, pointB.y+50);
                                    mileu.x=((pointA.x+pointB.x+50)/2);
                                    mileu.y=((pointA.y+pointB.y+50)/2);
                                 }else if(pointA.x<pointB.x && pointA.y>pointB.y){
                                    //SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y, pointB.x, pointB.y+50);
                                    mileu.x=((pointA.x+50+pointB.x)/2);
                                    mileu.y=((pointA.y+pointB.y+50)/2);
                                 }else if(pointA.x==pointB.x && pointA.y<pointB.y){
                                   //SDL_RenderDrawLine(pRenderer, pointA.x+25, pointA.y+50, pointB.x+25, pointB.y);
                                   mileu.x=((pointA.x+25+pointB.x+25)/2);
                                   mileu.y=((pointA.y+50+pointB.y)/2);
                                 }else if(pointA.x==pointB.x && pointA.y>pointB.y){
                                 //SDL_RenderDrawLine(pRenderer, pointA.x+25, pointA.y, pointB.x+25, pointB.y+50);
                                 mileu.x=((pointA.x+25+pointB.x+25)/2)-(((pointA.x+25+pointB.x+25)/2)/10);
                                 mileu.y=((pointA.y+pointB.y+50)/2);
                                 }else if(pointA.y==pointB.y && pointA.x>pointB.x){
                                   //SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y+25, pointB.x+50, pointB.y+25);
                                   mileu.x=((pointA.x+pointB.x+50)/2);
                                   mileu.y=((pointA.y+25+pointB.y+25)/2);
                                 }else if(pointA.y==pointB.y && pointA.x<pointB.x){
                                     //SDL_RenderDrawLine(pRenderer, pointA.x+50, pointA.y+25, pointB.x, pointB.y+25);
                                     mileu.x=((pointA.x+50+pointB.x)/2);
                                     mileu.y=((pointA.y+25+pointB.y+25)/2);
                                 }


                        searchElem=searchTab(G,pointA.x/100,pointA.y/100);
                        addElementList(&searchElem,pointB.x/100,pointB.y/100,atoi(coutArret));
                        text(pRenderer,coutArret,15,mileu.x,mileu.y);

                  }
                  if(conditionNumber(events)){
                    strcat(coutArret,SDL_GetKeyName(events.key.keysym.sym));
                  }
                }
           default: continue;



            }
        }

    repere(pRenderer);


 /*
        SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
        SDL_RenderCopy(pRenderer, texture, nullptr, &position);
        SDL_RenderPresent(pRenderer);
 */
    }


    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;

}

void repere( SDL_Renderer* pRenderer){

   SDL_Point pointA;
   SDL_Point pointB;
   int i;

   for(i=0;i<=900;i+=100){
    pointA.y=0;
    pointB.y=600;
    pointA.x=i;
    pointB.x=i;
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, 255);
    SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
    SDL_RenderPresent(pRenderer);
   }
    for(i=0;i<800;i+=100){
    pointA.y=i;
    pointB.y=i;
    pointA.x=0;
    pointB.x=900;
    SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, 255);
    SDL_RenderDrawLine(pRenderer, pointA.x, pointA.y, pointB.x, pointB.y);
    SDL_RenderPresent(pRenderer);
   }

}


void text(SDL_Renderer* pRenderer, char *txt,int fontSize, int x, int y){

     if(TTF_Init() <0)
      {
         fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
         exit(EXIT_FAILURE);
     }
    TTF_Font *police = NULL;
    police = TTF_OpenFont("arial.ttf", fontSize);
    SDL_Surface* text = TTF_RenderText_Blended(police,txt , SDL_Color{ 0, 255, 0, 255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, text);
    SDL_Rect position;
    SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
    position.x = x;
    position.y = y;
    SDL_FreeSurface(text);
    TTF_CloseFont(police);

    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderCopy(pRenderer, texture, nullptr, &position);
    SDL_RenderPresent(pRenderer);
    TTF_Quit();
}

bool conditionNumber(SDL_Event events){
if(events.key.keysym.sym == SDLK_0 ||
   events.key.keysym.sym == SDLK_1 ||
   events.key.keysym.sym == SDLK_2 ||
   events.key.keysym.sym == SDLK_3 ||
   events.key.keysym.sym == SDLK_4 ||
   events.key.keysym.sym == SDLK_5 ||
   events.key.keysym.sym == SDLK_6 ||
   events.key.keysym.sym == SDLK_7 ||
   events.key.keysym.sym == SDLK_8 ||
   events.key.keysym.sym == SDLK_9 ){
    return true;
   }
 return false;
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
