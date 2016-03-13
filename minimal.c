#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

const int CONST_SEGM = 100;
const float PI = 3.14;



void reshape(unsigned int windowWidth, unsigned int windowHeight) {
  glViewport(0, 0, windowWidth, windowHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-200., 200., -200. * windowHeight/windowWidth, 200.*windowHeight/windowWidth);
}



void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

void dessinCarre(int full){
  if (full == 1)
    glBegin(GL_QUADS);
  else
    glBegin(GL_LINE_LOOP);
  
  glVertex2f(-0.5,0.5); //point de d´epart
  glVertex2f(0.5,0.5); //point d’arriv´e
  glVertex2f(0.5,-0.5); //point de d´epart
  glVertex2f(-0.5,-0.5); //point d’arriv´e
    
  glEnd();

}

void dessinRepere(){
  glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex2f(0,0); //point de d´epart
    glVertex2f(0,1); //point d’arriv´e

    glColor3f(0,1,0);
    glVertex2f(0,0); //point de d´epart
    glVertex2f(1,0); //point d’arriv´e
    
  glEnd();

}

void dessinCercle(int full){
  int i;
  if(full == 1) glBegin(GL_TRIANGLE_FAN);
  else glBegin(GL_LINE_LOOP);
    glVertex2f(0,0); //point de d´epart
    for(i = 0; i <= CONST_SEGM; i++){
      glVertex2f(
        0+ (0.5 * cos(i * 2.0 * PI/CONST_SEGM)),
        0+ (0.5 * sin(i * 2.0 * PI/CONST_SEGM))
      ); 
    } 
  glEnd();
}

void dessinCarreBordRond(int full){
  glPushMatrix();
  glTranslatef(-0.25,0.25,0);
  glScalef(0.5,0.5,1);
  dessinCercle(full);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25,0.25,0);
  glScalef(0.5,0.5,1);
  dessinCercle(full);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.25,-0.25,0);
  glScalef(0.5,0.5,1);
  dessinCercle(full);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.25,-0.25,0);
  glScalef(0.5,0.5,1);
  dessinCercle(full);
  glPopMatrix();

  glPushMatrix();
  glScalef(1,0.5,1);
  dessinCarre(1);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.5,1,1);
  dessinCarre(1);
  glPopMatrix();
}

void dessinHovercraft(){
  int i;

  // les boués

  glPushMatrix();
    glColor3f(0.4,0.4,0.45);
    glBegin(GL_QUADS);
      glVertex2f(-20,12);
      glVertex2f(-7,33);
      glVertex2f(7,33);
      glVertex2f(20,12);
    glEnd();
    glPushMatrix();
      glScalef(38.5,40.,1.);
      dessinCarreBordRond(1);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,-18,0); 
      glScalef(38.5,40.,1.);
      dessinCarreBordRond(1);
    glPopMatrix();
  glPopMatrix();

  for(i =0; i < 6; i++){
    glPushMatrix();
      glColor3f(0.3,0.3,0.3);
      glTranslatef(0,-30+7*i,0); 
      glBegin(GL_POLYGON);
        glVertex2f(-20,i);
        glVertex2f(-20,i+1);
        glVertex2f(0,i-2);
        glVertex2f(20,i+1);
        glVertex2f(20,i);
        glVertex2f(0,i-3);
      glEnd();
    glPopMatrix();
  }

  // la partie bleue claire

  glPushMatrix();
    glColor3f(0.45,0.8,1);
    glBegin(GL_POLYGON);
      glVertex2f(-15,0);
      glVertex2f(-15,10);
      glVertex2f(-3,30);
      glVertex2f(3,30);
      glVertex2f(15,10);
      glVertex2f(15,0);
    glEnd();
    glPushMatrix();
      glTranslatef(0,-5,0);
      glScalef(30.,30.,1.);
      dessinCarreBordRond(1);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,-20,0);
      glScalef(30.,30.,1.);
      dessinCarreBordRond(1);
    glPopMatrix();
  glPopMatrix();

  // l'intérieur

  glPushMatrix();
    glColor3f(0.1,0.3,0.5);
    glBegin(GL_POLYGON);
      glVertex2f(-3,20);
      glVertex2f(-11,10);
      glVertex2f(-11,-30);
      glVertex2f(11,-30);
      glVertex2f(11,10);
      glVertex2f(3,20);
      glVertex2f(3,30);
      glVertex2f(-3,30);
    glEnd();
    glColor3f(0.9,0.9,1);
    glBegin(GL_QUADS);
      glVertex2f(-8,5);
      glVertex2f(-8,-23);
      glVertex2f(8,-23);
      glVertex2f(8,5);
    glEnd();
    glColor3f(0.9,0.9,1);
    glBegin(GL_QUADS);
      glVertex2f(-8,5);
      glVertex2f(8,5);
      glVertex2f(1,15);
      glVertex2f(-1,15);
    glEnd();
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_QUADS);
      glVertex2f(-6,5);
      glVertex2f(-6,-23);
      glVertex2f(6,-23);
      glVertex2f(6,5);
    glEnd();
  glPopMatrix();

  // Les ronds

  glPushMatrix();
    glPushMatrix();
      glColor3f(0.9,0.6,0.4);
      glTranslatef(0,-1.5,0);
      glScalef(8.,8.,1.);
      dessinCercle(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.3,0.3,0.4);
      glTranslatef(0,-35,0);
      glScalef(14.,9.,1.);
      dessinCercle(1);
    glPopMatrix();
    
    glPushMatrix();
     glColor3f(0.95,0.95,1);
      glTranslatef(0,-38,0);
      glScalef(12.,6.,1.);
      dessinCercle(1);
    glPopMatrix();
    
  glPopMatrix();

}

void dessinCheckpoint(){
  glPushMatrix();
    glPushMatrix();
      glColor3f(0.56,0.33,0);
      glScalef(45.,10.,1.);
      dessinCarreBordRond(1);
    glPopMatrix();
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      glVertex2f(-20,-3);
      glVertex2f(-20,3);
      glVertex2f(-10,3);
      glVertex2f(-10,-3);
    glEnd();
    glColor3f(0.98,0.78,0.17);
    glBegin(GL_QUADS);
      glVertex2f(-10,-3);
      glVertex2f(-10,3);
      glVertex2f(10,3);
      glVertex2f(10,-3);
    glEnd();
    glColor3f(0.91,0.66,0);
    glBegin(GL_QUADS);
      glVertex2f(10,-3);
      glVertex2f(10,3);
      glVertex2f(20,3);
      glVertex2f(20,-3);
    glEnd();
  glPopMatrix();
}

void dessinPiece(){
  glPushMatrix();
    glPushMatrix();
      glColor3f(0.56,0.33,0);
      glScalef(42.,45.,1.);
      dessinCercle(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(1,0.83,0.17);
      glScalef(37.,40.,1.);
      dessinCercle(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.91,0.66,0);
      glScalef(26.,29.,1.);
      dessinCercle(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.98,0.78,0.17);
      glScalef(22.,25.,1.);
      dessinCercle(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.91,0.66,0);
      glTranslatef(-1,0,0);
      glScalef(5.,17.,1.);
      dessinCarre(1);
    glPopMatrix();
    glPushMatrix();
      glColor3f(1,1,1);
      glScalef(3.5,15.,1.);
      dessinCarre(1);
    glPopMatrix();
  glPopMatrix();
}







int main(int argc, char** argv) {

  /* Dimensions de la fenêtre */
  unsigned int windowWidth  = 800;
  unsigned int windowHeight = 600;
  // float debutY = 0.;
  // float deplacementY = 0.15;
  float alpha = 0, rotation = 1;



  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }
  
  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  setVideoMode(windowWidth, windowHeight);
  reshape(windowWidth, windowHeight);  

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("Hovercraft", NULL);

  GLuint idHovercraft;
  idHovercraft = glGenLists(1);
  glNewList(idHovercraft,GL_COMPILE);
  dessinHovercraft();   
  glEndList();

  GLuint idCheckpoint;
  idCheckpoint = glGenLists(1);
  glNewList(idCheckpoint,GL_COMPILE);
  dessinCheckpoint();   
  glEndList();

  GLuint idPiece;
  idPiece = glGenLists(1);
  glNewList(idPiece,GL_COMPILE);
  dessinPiece();   
  glEndList();

  
  
  /* Boucle d'affichage */
  int loop = 1;
  

  while(loop) {
    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    
    
    /* Placer ici le code de dessin */
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    
    glPushMatrix();
    // deplacementHovercraft(&debutY,&deplacementY);
      glScalef(0.8,0.8,1.);
      
      glCallList(idHovercraft);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-100,0,0);
      glRotatef(alpha,0.0,0.0,1.0);
      glCallList(idCheckpoint);
    glPopMatrix();

    //if(alpha > 3 || alpha < -3) rotation = -rotation;
    alpha = alpha + rotation;

    glPushMatrix();
      glTranslatef(-100,100,0);
      glCallList(idPiece);
    glPopMatrix();
   
    

 
    
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

        case SDL_MOUSEBUTTONDOWN:
          break;


        /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d)\n", e.key.keysym.sym);
          if(e.key.keysym.sym == SDLK_q)
            loop = 0;
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
