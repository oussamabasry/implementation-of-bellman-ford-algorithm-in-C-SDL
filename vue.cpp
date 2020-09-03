#include "headers.h"

int vue(Graph *G)
{
    // L'initialisation de la SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("\nErreur lors de l'initialisation de la SDL");
        //libérer en mémoire les ressources utilisées par la SDL
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // la création de la fenetre et du rendu
    if (SDL_CreateWindowAndRenderer(1200, 670, SDL_WINDOW_SHOWN, &window, &renderer) != 0)
    {
        printf("\nErreur lors de la création de la fenetre");
        //libérer en mémoire les ressources utilisées par la SDL
        SDL_Quit();
        return 1;
    }

    // Le titre de la fenetre
    SDL_SetWindowTitle(window, "Algorithme de Bellman ford");

    // Initialiser SDL_Mixer
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
    {
        printf("\nErreur initialisation SDL_mixer");
        return -1;
    }
    // Le chargement de l'audio
    Mix_Music *music = Mix_LoadMUS("audio.mp3");

    if (music == NULL)
    {
        printf("\Erreur chargement de la musique");
        //libérer en mémoire les ressources utilisées par la SDL_Mixer
        Mix_CloseAudio();
        //libérer en mémoire les ressources utilisées par la SDL
        SDL_Quit();
        return -1;
    }

    /* les buttons et les lignes de l'interface*/

    // La droit rouge vertical
    Draw_rect(renderer, 1000, 0, 7, 500, 255, 0, 0);

    // Button Indiquer la source
    Draw_rect(renderer, 1030, 100, 155, 60, 255, 255, 0);
    text(renderer, (char *)"Indiquer la source", 16, 1052, 125, 0, 0, 0);

    //Button Indiquer la destination
    Draw_rect(renderer, 1030, 200, 155, 60, 255, 255, 0);
    text(renderer, (char *)"Indiquer la destination", 16, 1035, 225, 0, 0, 0);

    //Button Indiquer Le plus court chemin
    Draw_rect(renderer, 1030, 300, 155, 60, 255, 255, 0);
    text(renderer, (char *)"Le plus court chemin", 16, 1038, 325, 0, 0, 0);

    // Le droit rouge horizontal
    Draw_rect(renderer, 0, 500, 1200, 6, 255, 0, 0);

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

    // la boucle du jeu
    while (isOpen)
    {
        SDL_Event events;
        while (SDL_PollEvent(&events)) // capter et lire d'éventuels événements
        {

            switch (events.type)
            {

            case SDL_QUIT: //clique sur la croix rouge
                isOpen = false;
                break;
            // les evenements de la souris
            case SDL_MOUSEBUTTONDOWN:
            {
                // si j'ai cliquee sur ces coordoonnes alors lancer algo de bellman
                if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 300 && events.motion.y <= 360)
                {

                    Bellman(G, p1, p2, renderer);
                }
                // si j'ai cliquee sur ces coordoonnes alors source reçoit true
                else if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 100 && events.motion.y <= 160)
                {
                    source = true;
                }
                // si j'ai cliquee sur ces coordoonnes alors destination reçoit true
                else if (events.motion.x >= 1030 && events.motion.x <= 1185 && events.motion.y >= 200 && events.motion.y <= 260)
                {
                    destinatin = true;
                }
                else if (source == true) // si le button cliquee est source
                {
                    p1.x = (events.motion.x - (events.motion.x % 100)) / 100;
                    p1.y = (events.motion.y - (events.motion.y % 100)) / 100;
                    source = false;
                }
                else if (destinatin == true) // si le button cliquee est destination
                {
                    p2.x = (events.motion.x - (events.motion.x % 100)) / 100;
                    p2.y = (events.motion.y - (events.motion.y % 100)) / 100;
                    destinatin = false;
                }
                else
                {

                    strcpy(coutArret, "");
                    // stocker les coordonnees di clique et chercher si le noeud deja existe
                    mouse.x = events.motion.x - (events.motion.x % 100);
                    mouse.y = events.motion.y - (events.motion.y % 100);
                    searchElem = searchTab(G, mouse.x / 100, mouse.y / 100);
                    // si le noeud cliquee existe deja
                    if (searchElem != NULL)
                    {
                        // si on n'a pas encore cliquer sur un noeud
                        // remplir la pointA par les coordonnes du clique et boolPointA recoit true
                        if (boolPointA == false)
                        {
                            pointA.x = mouse.x;
                            pointA.y = mouse.y;
                            boolPointA = true;
                        }
                        // si on a deja clicker sur un noeud c-a-d boolPointA est true
                        // remplir la pointB par les coordonnes du clique

                        else if (boolPointA == true && boolPointB == false)
                        {
                            pointB.x = mouse.x;
                            pointB.y = mouse.y;
                            // tracer l'arc et ça depent du position du pointA et PointB
                            Draw_arc(renderer, pointA, pointB, &departLine, &arriveLine);
                            i += 40;
                            Mix_PlayMusic(music, 1);
                            // boolPointA et boolPointB deviennent false (L'eata initial aucun noeud selectioner
                            boolPointA = false;
                            boolPointB = false;
                        }
                    }
                    // si le noeud n'existe pas avec on doit l'ajouter
                    else
                    {
                        if (mouse.x < 1000 && mouse.y < 500)
                        {

                            rect1.x = mouse.x;
                            rect1.y = mouse.y;
                            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                            SDL_RenderFillRect(renderer, &rect1);
                            SDL_RenderPresent(renderer);
                            // construction des coordonnees
                            char coordonnes[20] = "";
                            char buffer[20];
                            itoa(rect1.x / 100, buffer, 10);
                            strcat(coordonnes, buffer);
                            strcat(coordonnes, " , ");
                            itoa(rect1.y / 100, buffer, 10);
                            strcat(coordonnes, buffer);
                            text(renderer, coordonnes, 17, mouse.x + 12, mouse.y + 21, 0, 0, 102);
                            strcpy(coordonnes, "");
                            // ajouter le noeud au graphe avec une valuation de 0
                            addElementNode(G, rect1.x / 100, rect1.y / 100, 0);
                        }
                    }
                }
            }
                // les evenements du clavier
            case SDL_KEYDOWN:
            {
                // le button echap pour valider la saisie du cout de l'arc
                if (events.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_Point mileu;
                    // positionner le cout au mileu de l'arc
                    mileu.x = (departLine.x + arriveLine.x) / 2;
                    mileu.y = (departLine.y + arriveLine.y) / 2;
                    if (!(pointA.x == pointB.x && pointA.y > pointB.y))
                    {
                        mileu.x = (mileu.x + departLine.x) / 2;
                        mileu.y = (mileu.y + departLine.y) / 2;
                    }
                    // chercher les adresses des extrimites de l'arc dans le graphe
                    searchElem = searchTab(G, pointA.x / 100, pointA.y / 100);
                    searchElem1 = searchTab(G, pointB.x / 100, pointB.y / 100);
                    // si les deus noeud existent
                    if (searchElem1 != NULL && searchElem != NULL)
                    {
                        //ajouter l'un comme seccesseur de l'autre
                        addElementList(&searchElem, searchElem1, atoi(coutArret));
                        // dessiner l'arc
                        text(renderer, coutArret, 15, mileu.x, mileu.y, 255, 255, 0);
                    }
                }
                // si la touche est un nombre ou bien la touche M qui represente le signe moins
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
    //libérer en mémoire les ressources utilisées par TTF
    TTF_Quit();
    //libérer en mémoire les ressources utilisées par Mixer
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    //libérer en mémoire les ressources utilisées par window et renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //libérer en mémoire les ressources utilisées par la SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}

// Les fonctions

void Draw_arc(SDL_Renderer *renderer, SDL_Point pointA, SDL_Point pointB, SDL_Point *departLine, SDL_Point *arriveLine)
{
    // Cà depent la position de A et B trouver les bons coordonnes
    // de debut de l'arct et la fin de l'arc
    if (pointA.x < pointB.x && pointA.y < pointB.y)
    {
        departLine->x = pointA.x + 50;
        departLine->y = pointA.y + 50;
        arriveLine->x = pointB.x;
        arriveLine->y = pointB.y;
    }
    else if (pointA.x > pointB.x && pointA.y < pointB.y)
    {
        departLine->x = pointA.x;
        departLine->y = pointA.y + 50;
        arriveLine->x = pointB.x + 50;
        arriveLine->y = pointB.y;
    }
    else if (pointA.x > pointB.x && pointA.y > pointB.y)
    {
        departLine->x = pointA.x;
        departLine->y = pointA.y;
        arriveLine->x = pointB.x + 50;
        arriveLine->y = pointB.y + 50;
    }
    else if (pointA.x < pointB.x && pointA.y > pointB.y)
    {
        departLine->x = pointA.x + 50;
        departLine->y = pointA.y;
        arriveLine->x = pointB.x;
        arriveLine->y = pointB.y + 50;
    }
    else if (pointA.x == pointB.x && pointA.y < pointB.y)
    {
        departLine->x = pointA.x + 25;
        departLine->y = pointA.y + 50;
        arriveLine->x = pointB.x + 25;
        arriveLine->y = pointB.y;
    }
    else if (pointA.x == pointB.x && pointA.y > pointB.y)
    {
        departLine->x = pointA.x + 25;
        departLine->y = pointA.y;
        arriveLine->x = pointB.x + 25;
        arriveLine->y = pointB.y + 50;
    }
    else if (pointA.y == pointB.y && pointA.x > pointB.x)
    {
        departLine->x = pointA.x;
        departLine->y = pointA.y + 25;
        arriveLine->x = pointB.x + 50;
        arriveLine->y = pointB.y + 25;
    }
    else if (pointA.y == pointB.y && pointA.x < pointB.x)
    {
        departLine->x = pointA.x + 50;
        departLine->y = pointA.y + 25;
        arriveLine->x = pointB.x;
        arriveLine->y = pointB.y + 25;
    }
    // Dessiner l'arct
    SDL_SetRenderDrawColor(renderer, 255, 0, 127, 255);
    SDL_RenderDrawLine(renderer, departLine->x, departLine->y, arriveLine->x, arriveLine->y);
    SDL_RenderPresent(renderer);
    return;
}

// afficher un text dans le window dans une position et  une couleur specifiques
void text(SDL_Renderer *pRenderer, char *txt, int fontSize, int x, int y, int R, int G, int B)
{

    if (TTF_Init() < 0)
    {
        printf("\nErreur d'initialisation de TTF_Init");
        exit(1);
    }
    TTF_Font *police = NULL;
    police = TTF_OpenFont("arial.ttf", fontSize);
    SDL_Surface *text = TTF_RenderText_Blended(police, txt, SDL_Color{(Uint8)R, (Uint8)G, (Uint8)B, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, text);
    SDL_Rect position;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    position.x = x;
    position.y = y;
    SDL_FreeSurface(text);
    TTF_CloseFont(police);

    SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255);
    SDL_RenderCopy(pRenderer, texture, NULL, &position);
    SDL_RenderPresent(pRenderer);
    TTF_Quit();
}

// fonction test si un event est un click sur un chiffre ou la touche M
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

// afficher le plus court chemin à la fin du programme
void afficherPlusCourtChemin(SDL_Renderer *pRenderer, BellmanTable chemin[], int nb)
{
    SDL_Rect rect = {300, 570, 50, 50};
    SDL_Point departLine = {}, arriveLine;
    char coordonnes[20] = "";
    char buffer[20];
    for (int i = 0; i < nb; i++)
    {
        // Cette printf pour afficher les valeurs dans la console
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

//Dessiner un rect avec une couleur,largeur,longeur et couleur specifiques
void Draw_rect(SDL_Renderer *renderer, int x, int y, int width, int height, int red, int green, int blue)
{
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}
