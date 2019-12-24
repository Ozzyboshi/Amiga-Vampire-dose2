//3703


/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>*/
#include "argb.h"
#include "line.h"
#include "m2d.h"
#include "layer.h"
#include "demo.h"
#include "vorbisfile.h"
//#include "ogdecode.h"
#include "SDL_mixer.h"
#include <unistd.h>

#include <math.h>

#include <SDL/SDL.h>
#include "fix_fread.h"

#define HEAPSIZE 10000000

#define OV_EREAD      -128
#define OV_EFAULT     -129
#define OV_EIMPL      -130
#define OV_EINVAL     -131
#define OV_ENOTVORBIS -132
#define OV_EBADHEADER -133
#define OV_EVERSION   -134
#define OV_ENOTAUDIO  -135
#define OV_EBADPACKET -136
#define OV_EBADLINK   -137
#define OV_ENOSEEK    -138


volatile unsigned frame;
float fsin2(float);
int stopnow=0;
extern float con, bri;
int NOAUDIO=0;

/* Change this to standard fread() and behold: it's x86 byte order! */
#ifndef INTEL
void fix_fread(void *dest,int dummy,int count,FILE *f)
{
    int n;
    unsigned char *d=dest;
    for(n=0;n<count;n++)
        d[3+n/4*4-n%4]=fgetc(f);
}
#else
void fix_fread(void *dest,int dummy,int count,FILE *f)
{
    fread(dest,dummy,count,f);
}
#endif

static unsigned hiippi[HEAPSIZE];
static unsigned *hptrs[4096], hpind=1;
void *getmem(int bytes)
{
    /* Let's keep it aligned */
    int wds=(bytes+4)/4;
    return (hptrs[hpind]+=wds)-wds;
}
void mark() { hptrs[hpind+1]=hptrs[hpind]; hpind++; }
void release() { hpind--; }



M2d *new_m2_roto(float x0, float y0, float r, float i) {
  M2d *m=getmem(sizeof(M2d));
  m->x1=x0; m->y1=y0;
  r=exp(r);
  m->xx=m->yy=cos(i)*r;
  m->xy=-(m->yx=sin(i)*r);
  return m;
}
M2d *new_m2_mul(M2d *a, M2d *b) {
  M2d *m=getmem(sizeof(M2d));
  m->xx=a->xx*b->xx+a->yx*b->xy; m->xy=a->xy*b->xx+a->yy*b->xy; m->x1=a->x1*b->xx+a->y1*b->xy+b->x1;
  m->yx=a->xx*b->yx+a->yx*b->yy; m->yy=a->xy*b->yx+a->yy*b->yy; m->y1=a->x1*b->yx+a->y1*b->yy+b->y1;
  return m;
}


int aikah=0;
void audioback(void *oggi, unsigned char *stream, int len) {
  int i, lkm, foo=0;
  //for (i=0; i<len; i++) stream[i]=rand();

  //if (kcnt[74]) skip=-44100*10, kcnt[74]=0;
  //if (kcnt[78]) skip=44100*10, kcnt[78]=0;
/*      if (skip) {
        if (ov_pcm_seek(&oggi, oggi.pcm_offset+skip)==0) aikah+=skip*4;
        skip=0;
      } */
      //fread(buffer, 100000, 1, vavi);
  if (stopnow) return;
  aikah+=len;
  while (len>0) {
    lkm=ov_read(oggi, stream, len, 0, 2, 1, &foo);
    if (lkm<=0) { stopnow++; return; }
    len-=lkm; stream+=lkm;
  }
  //ttemp=MIDASfeedStreamData(stream, buffer+bufsiz-bytesleft, bytesleft, 0);
  //bytesleft-=ttemp;

}


void fla(int a) {}
int main(int argc, char *argv[]) {
  int i, j, bytesleft;
  int current_section,fullscreen=1;
  int skip=0;
  float t;
//  MIDASstreamHandle stream=0;
  static char buffer[200000];
  OggVorbis_File oggi;
//  Video *v;
  int bufsiz;
  unsigned time0, timex;
  SDL_Surface *screen;
  SDL_Color colors[256];
  static int graffa[160*480];

  fprintf(stdout,"\n\nClassic Amiga port by Ozzyboshi - https://github.com/Ozzyboshi/Amiga-Vampire-dose2\n\n");

//  signal(SIGSEGV, fla);
/*  hiippi=malloc(30000000); if (!hiippi) {
    fprintf(stderr, "cant allok mem");
    return 1;
  }*/
  hptrs[0]=hptrs[1]=hiippi;
  mark();

// This one moved here because of OSX oddities...
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0) {
    fprintf(stderr, "sdlerror %s\n", SDL_GetError());
    return 1;
  }


  atexit(SDL_Quit);
  

  if(argc==2 && !strcmp(argv[1],"-window"))
    fullscreen=0;
#ifdef OSX
  /* On OSX we have two different applets with separate names. The one
     ending with 'w' is widowed */
  if(argv[0][strlen(argv[0])-1]=='w')
    fullscreen=0;
#endif

  if(fullscreen)
    screen=SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_FULLSCREEN);//|SDL_DOUBLEBUF);
  else
  {
    screen=SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);//|SDL_DOUBLEBUF);
    SDL_WM_SetCaption("dose 2 by mfx",NULL);
  }

//  screen=SDL_SetVideoMode(640, 480, 8, 0);
  SDL_ShowCursor(0);

  t=0;
  bytesleft=0;


  Mix_Chunk *wav = NULL;
//Initialize SDL_mixer
  if( Mix_OpenAudio( 8000, AUDIO_S16LSB, 1, 512 ) == -1 )
  {
    fprintf(stderr,"Error mix audio\n");
    return 1;    
  }

  wav = Mix_LoadWAV("data/italo160mono.wav");
  if (wav==NULL)
  {
    fprintf(stderr,"data/italo160mono.wav - %s\n", Mix_GetError());
    return 1;
  }
  
  initdemo();

    
  Mix_PlayChannel(-1,wav,0); 

  time0=SDL_GetTicks();


  SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
  SDL_EventState(SDL_QUIT, SDL_ENABLE);


  while (!stopnow) {

    //char *vm;
    //Lfb *l;
    //static int oldf;
    //int ttemp;
    // ALESSIO non serve float aikaero=.02;
    SDL_Event eve;
    timex=SDL_GetTicks()-time0;

    while (SDL_PollEvent(&eve))
    {
      if (eve.type==SDL_KEYDOWN||eve.type==SDL_QUIT) stopnow++;
      if(eve.type==SDL_MOUSEBUTTONDOWN) stopnow++;
    }
    if (SDL_LockSurface(screen)<0) continue;


    mark();
    con=1, bri=0;

    // ALESSIO NON SERVE aikaero=0.0;//1.43;//oli 1.45

    //if (kcnt[74]) skip=-44100*10, kcnt[74]=0;
    //if (kcnt[78]) skip=44100*10, kcnt[78]=0;
    //ttemp=MIDASfeedStreamData(stream, buffer+bufsiz-bytesleft, bytesleft, 0);
    //bytesleft-=ttemp;
    //aikah+=ttemp;

    //l=vid_openlfb(v);
    init_layers((char*)graffa, new_col(0, 0, 0, 0));
    memset(graffa, 0, 640*480);
    //{ static Positio p; t=pos_get(&p); }

    {
//    float f=(aikah/44100.0/4.0/60.0)*132.3412*4 - aikaero*32;

      /*** ALESSIO ERA COSI
    float f=(timex/1000.0/60.0)*132.3412*4 - aikaero*32;

    ORA COSI*/
    float f=(timex/1000.0/60.0)*132.3412*4;
  
    rundemo(f);//-fsin2(f*.25)*.0);
    }

    {
      int x, y;
      int *p32=screen->pixels, *q32=graffa;
      char *q8=(char*)graffa;
//      p8[rand()&32767]=rand();
      for (x=0; x<screen->w; x++) q8[x]^=q8[x-1];
      for (y=0; y<screen->h-1; y++) {
        for (x=0; x<screen->w>>2; x++) p32[x]=q32[x], q32[x+160]^=q32[x];
        p32+=screen->pitch>>2;
        q32+=160;
      }
    }

    //for (i=1; i<640; i++) l->buf[i]^=l->buf[i-1];


    //for (i=0; i<480; i++) l->buf[i*640]=0, l->buf[i*640+1]=0;
    //for (i=0; i*10<480; i++) l->buf[i*10*640]=l->buf[i*10*640]=i^i+1;
    {
      char *p=teepal1();
      static SDL_Color pp[256];
      for (i=0; i<256; i++) pp[i].r=p[i*3], pp[i].g=p[i*3+1], pp[i].b=p[i*3+2];
      SDL_SetColors(screen, pp, 0, 256);
    }
    //vid_closelfb(v);
//    teepal2();
    SDL_UnlockSurface(screen);
    SDL_Flip(screen);


    release();
  }

  Mix_FreeChunk( wav );
  Mix_CloseAudio();


  SDL_FreeSurface(screen);
  SDL_Quit();
  fprintf(stdout,"Thanks for watching - exiting...\n\n");
  exit(0);
  return 0;
}
