#include "headers.h"

int vue(Graph *G)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *pWindow{nullptr};
    SDL_Renderer *pRenderer{nullptr};

    if (SDL_CreateWindowAndRenderer(1200, 670, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(pWindow, "Projet de Graphes");

    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        return -1;
    }

    Mix_Music *music = Mix_LoadMUS("audio.mp3");

    if (music == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    // les buttons de l'interface

    SDL_Rect rect2 = {1000, 0, 7, 500};
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0);
    SDL_RenderFillRect(pRenderer, &rect2);
    SDL_RenderPresent(pRenderer);

    rect2 = {1030, 100, 155, 60};
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
    SDL_RenderFillRect(pRenderer, &rect2);
    SDL_RenderPresent(pRenderer);
    text(pRenderer, (char *)"Indiquer la source", 16, 1052, 125, 0, 0, 0);

    rect2 = {1030, 200, 155, 60};
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
    SDL_RenderFillRect(pRenderer, &rect2);
    SDL_RenderPresent(pRenderer);
    text(pRenderer, (char *)"Indiquer la destination", 16, 1035, 225, 0, 0, 0);

    rect2 = {1030, 300, 155, 60};
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 0, 255);
    SDL_RenderFillRect(pRenderer, &rect2);
    SDL_RenderPresent(pRenderer);
    text(pRenderer, (char *)"Le plus court chemin", 16, 1038, 325, 0, 0, 0);

    rect2 = {0, 500, 1200, 6};
    SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 0);
    SDL_RenderFillRect(pRenderer, &rect2);
    SDL_RenderPresent(pRenderer);

    //Declaration des variables
    bool isOpen{true};
    SDL_Rect rect1 = {10, 10, 50, 50};
    SDL_Point mouse;
    SDL_Point pointA;
    SDL_Point pointB;
    SDL_Point departLine;
    SDL_Point arriveLine;
    SDL_Point p1, p2;
    Element *searchElem, *searchElem1;
    bool boolPointA = false;
    bool boolPointB = false;
    bool source = false;
    bool destinatin = false;
    char coutArret[10] = "";
    int i = 5;

    while (isOpen)
    {
        SDL_Event events;
        while (SDL_PollEvent(&events))
        {

            switch (events.type)
            {

            case SDL_QUIT:
                isOpen = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
            {
                if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 300 && events.motion.y <= 360)
                {

                    Bellman(G, p1, p2, pRenderer);
                }
                else if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 100 && events.motion.y <= 160)
                {
                    source = true;
                }
                else if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 200 && events.motion.y <= 260)
                {
                    destinatin = true;
                }
                else if (source == true)
                {
                    p1.x = (events.motion.x - (events.motion.x % 100)) / 100;
                    p1.y = (events.motion.y - (events.motion.y % 100)) / 100;

                    source = false;
                }
                else if (destinatin == true)
                {
                    p2.x = (events.motion.x - (events.motion.x % 100)) / 100;
                    p2.y = (events.motion.y - (events.motion.y % 100)) / 100;
                    destinatin = false;
                }
                else
                {

                    strcpy(coutArret, "");
                    mouse.x = events.motion.x - (events.motion.x % 100);
                    mouse.y = events.motion.y - (events.motion.y % 100);
                    searchElem = searchTab(G, mouse.x / 100, mouse.y / 100);
                    if (searchElem != NULL)
                    {
                        if (boolPointA == false)
                        {
                            pointA.x = mouse.x;
                            pointA.y = mouse.y;
                            boolPointA = true;
                        }
                        else if (boolPointA == true && boolPointB == false)
                        {
                            pointB.x = mouse.x;
                            pointB.y = mouse.y;
                            SDL_SetRenderDrawColor(pRenderer, 255, 0, 127, 255);
                            if (pointA.x < pointB.x && pointA.y < pointB.y)
                            {
                                departLine.x = pointA.x + 50;
                                departLine.y = pointA.y + 50;
                                arriveLine.x = pointB.x;
                                arriveLine.y = pointB.y;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.x > pointB.x && pointA.y < pointB.y)
                            {
                                departLine.x = pointA.x;
                                departLine.y = pointA.y + 50;
                                arriveLine.x = pointB.x + 50;
                                arriveLine.y = pointB.y;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.x > pointB.x && pointA.y > pointB.y)
                            {
                                departLine.x = pointA.x;
                                departLine.y = pointA.y;
                                arriveLine.x = pointB.x + 50;
                                arriveLine.y = pointB.y + 50;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.x < pointB.x && pointA.y > pointB.y)
                            {
                                departLine.x = pointA.x + 50;
                                departLine.y = pointA.y;
                                arriveLine.x = pointB.x;
                                arriveLine.y = pointB.y + 50;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.x == pointB.x && pointA.y < pointB.y)
                            {
                                departLine.x = pointA.x + 25;
                                departLine.y = pointA.y + 50;
                                arriveLine.x = pointB.x + 25;
                                arriveLine.y = pointB.y;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.x == pointB.x && pointA.y > pointB.y)
                            {
                                departLine.x = pointA.x + 25;
                                departLine.y = pointA.y;
                                arriveLine.x = pointB.x + 25;
                                arriveLine.y = pointB.y + 50;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.y == pointB.y && pointA.x > pointB.x)
                            {
                                departLine.x = pointA.x;
                                departLine.y = pointA.y + 25;
                                arriveLine.x = pointB.x + 50;
                                arriveLine.y = pointB.y + 25;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }
                            else if (pointA.y == pointB.y && pointA.x < pointB.x)
                            {
                                departLine.x = pointA.x + 50;
                                departLine.y = pointA.y + 25;
                                arriveLine.x = pointB.x;
                                arriveLine.y = pointB.y + 25;
                                SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
                            }

                            SDL_RenderPresent(pRenderer);
                            i += 40;
                            Mix_PlayMusic(music, 1);
                            boolPointA = false;
                            boolPointB = false;
                        }
                    }
                    else
                    {
                        if (mouse.x < 1000 && mouse.y < 500)
                        {

                            rect1.x = mouse.x;
                            rect1.y = mouse.y;
                            SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, 255);
                            SDL_RenderFillRect(pRenderer, &rect1);
                            SDL_RenderPresent(pRenderer);

                            char coordonnes[20] = "";
                            char buffer[20];
                            itoa(rect1.x / 100, buffer, 10);
                            strcat(coordonnes, buffer);
                            strcat(coordonnes, " , ");
                            itoa(rect1.y / 100, buffer, 10);
                            strcat(coordonnes, buffer);
                            text(pRenderer, coordonnes, 17, mouse.x + 12, mouse.y + 21, 0, 0, 102);
                            strcpy(coordonnes, "");

                            addElementNode(G, rect1.x / 100, rect1.y / 100, 0);
                        }
                    }
                }
            }

            case SDL_KEYDOWN:
            {

                if (events.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_Point mileu;

                    mileu.x = (departLine.x + arriveLine.x) / 2;
                    mileu.y = (departLine.y + arriveLine.y) / 2;
                    if (!(pointA.x == pointB.x && pointA.y > pointB.y))
                    {
                        mileu.x = (mileu.x + departLine.x) / 2;
                        mileu.y = (mileu.y + departLine.y) / 2;
                    }

                    searchElem = searchTab(G, pointA.x / 100, pointA.y / 100);
                    searchElem1 = searchTab(G, pointB.x / 100, pointB.y / 100);
                    if (searchElem1 != NULL && searchElem != NULL)
                    {
                        addElementList(&searchElem, searchElem1, atoi(coutArret));
                        addElementList(&searchElem1, searchElem, atoi(coutArret));
                        text(pRenderer, coutArret, 15, mileu.x, mileu.y, 255, 255, 0);
                    }
                }
                if (conditionNumber(events))
                {
                    if (events.key.keysym.sym != SDLK_m)
                        strcat(coutArret, SDL_GetKeyName(events.key.keysym.sym));
                    else
                        strcat(coutArret, "-");
                }
            }

            default:
                continue;
            }
        }
    }

    TTF_Quit();
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void text(SDL_Renderer *pRenderer, char *txt, int fontSize, int x, int y, int R, int G, int B)
{

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font *police = NULL;
    police = TTF_OpenFont("arial.ttf", fontSize);
    SDL_Surface *text = TTF_RenderText_Blended(police, txt, SDL_Color{(Uint8)R, (Uint8)G, (Uint8)B, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, text);
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

bool conditionNumber(SDL_Event events)
{
    if (events.key.keysym.sym == SDLK_0 ||
        events.key.keysym.sym == SDLK_1 ||
        events.key.keysym.sym == SDLK_2 ||
        events.key.keysym.sym == SDLK_3 ||
        events.key.keysym.sym == SDLK_4 ||
        events.key.keysym.sym == SDLK_5 ||
        events.key.keysym.sym == SDLK_6 ||
        events.key.keysym.sym == SDLK_7 ||
        events.key.keysym.sym == SDLK_8 ||
        events.key.keysym.sym == SDLK_9 ||
        events.key.keysym.sym == SDLK_m)
    {
        return true;
    }
    return false;
}

void afficherPlusCourtChemin(SDL_Renderer *pRenderer, BellmanTable chemin[], int nb)
{
    SDL_Rect rect = {300, 570, 50, 50};
    SDL_Point departLine = {}, arriveLine;
    char coordonnes[20] = "";
    char buffer[20];
    for (int i = 0; i < nb; i++)
    {
        printf("\n (%d,%d):%d      ", chemin[i].x, chemin[i].y, chemin[i].valeur);

        SDL_SetRenderDrawColor(pRenderer, 0, 255, 255, 255);
        SDL_RenderFillRect(pRenderer, &rect);
        SDL_RenderPresent(pRenderer);
        itoa(chemin[nb - i - 1].x, buffer, 10);
        strcat(coordonnes, buffer);
        strcat(coordonnes, " , ");
        itoa(chemin[nb - i - 1].y, buffer, 10);
        strcat(coordonnes, buffer);
        text(pRenderer, coordonnes, 17, rect.x + 12, rect.y + 21, 0, 0, 102);
        strcpy(coordonnes, "");

        if (i != nb - 1)
        {
            SDL_SetRenderDrawColor(pRenderer, 255, 0, 127, 255);
            departLine.x = rect.x + 50;
            departLine.y = rect.y + 25;
            arriveLine.x = departLine.x + 100;
            arriveLine.y = departLine.y;
            SDL_RenderDrawLine(pRenderer, departLine.x, departLine.y, arriveLine.x, arriveLine.y);
        }

        rect.x = rect.x + 100;
    }

    text(pRenderer, (char *)"Voilà le plus court chemin", 18, 450, 525, 255, 0, 127);
    strcpy(coordonnes, "Le cout minimal c'est : ");
    itoa(chemin[0].valeur, buffer, 10);
    strcat(coordonnes, buffer);
    text(pRenderer, coordonnes, 18, 10, 590, 255, 255, 0);
}
