#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#include "hovercraft.c"
#include "planUtils.c"

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;



void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-10., 10., -10. * windowHeight/windowWidth, 10.*windowHeight/windowWidth);
}



void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE | SDL_GL_DOUBLEBUFFER)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}


void dessinCarre(int full){
  if (full == 1)
    glBegin(GL_QUADS);
  else
    glBegin(GL_LINE_LOOP);
  
  glVertex2f(-0.5,0.5); 
  glVertex2f(0.5,0.5);
  glVertex2f(0.5,-0.5);
  glVertex2f(-0.5,-0.5);
    
  glEnd();
}

void draw_hovercraft(Hovercraft *hv) {
  glPushMatrix();
    glTranslatef(hv->pos->x, hv->pos->y, 0);
    dessinCarre(0);
  glPopMatrix();
}


int main(int argc, char** argv) {

  Hovercraft *hv = init_hovercraft(init_coordonnees(0,0));

  /* Dimensions de la fenêtre */
  unsigned int windowWidth  = 800;
  unsigned int windowHeight = 600;

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  
  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  setVideoMode(windowWidth, windowHeight);
  reshape(windowWidth, windowHeight);  

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("OpenGL powa :D", NULL);

  
  /* Boucle d'affichage */
  int loop = 1;
  int leftPressed = 0, rightPressed = 0, upPressed = 0, downPressed = 0;

  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    
    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    if (leftPressed)
      hv->pos->x += -1;
    if (rightPressed)
      hv->pos->x += 1;
    if (upPressed)
      hv->pos->y += 1;
    if (downPressed)
      hv->pos->y += -1;
    draw_hovercraft(hv);
    
    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    SDL_GL_SwapBuffers();
    
    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
      /* L'utilisateur ferme la fenêtre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }
      
      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {
        /* Clic souris */
        case SDL_MOUSEBUTTONUP:
          printf("clic en (%d, %d)\n", e.button.x, e.button.y);
          break;

        /* move the mouse */           
        case SDL_MOUSEMOTION:
          
          break;

        /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
          switch (e.key.keysym.sym) {
            case SDLK_a: //TODO Attention, a modifier! Sur windows, le clavier est considéré comme qwerty...
              loop = 0;
              break;
            case SDLK_LEFT:
              leftPressed = 1;
              break;
            case SDLK_RIGHT:
              rightPressed = 1;
              break;
            case SDLK_UP:
              upPressed = 1;
              break;
            case SDLK_DOWN:
              downPressed = 1;
              break;
            default:
              break;
          }
          break;

        case SDL_KEYUP:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
          switch (e.key.keysym.sym) {
            case SDLK_LEFT:
              leftPressed = 0;
              break;
            case SDLK_RIGHT:
              rightPressed = 0;
              break;
            case SDLK_UP:
              upPressed = 0;
              break;
            case SDLK_DOWN:
              downPressed = 0;
              break;
            default:
              break;
          }
          break;
          
        /* resize window */
        case SDL_VIDEORESIZE:
          windowWidth  = e.resize.w;
          windowHeight = e.resize.h;
          setVideoMode(windowWidth, windowHeight);
          reshape(windowWidth, windowHeight);
          break;
 
        default:
          break;
      }
    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }
  
  /* Liberation des ressources associées à la SDL */ 
  SDL_Quit();
  
  return EXIT_SUCCESS;
}
