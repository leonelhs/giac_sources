// emcc emtest.cc -sSINGLE_FILE -o a.html
// Copyright 2011 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <stdio.h>
#include <SDL/SDL.h>
#include <iostream>
#include <string>

using namespace std;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void alert(const string & s){
  EM_ASM_ARGS({
      var msg = UTF8ToString($0);// Pointer_stringify($0); // Convert message to JS string
      alert(msg);                      // Use JS version of alert          
    }, s.c_str());
}

double get_double(const string & in){
  double d=EM_ASM_DOUBLE({
      var msg=UTF8ToString($0);
      var jsString = prompt(msg);
      // var lengthBytes = lengthBytesUTF8(jsString)+1;
      // return stringToNewUTF8(jsString);
      return eval(jsString);
    },in.c_str());
  return d;  
}

int get_int(const string & in){
  return get_double(in);
  int d=EM_ASM_INT({
      var msg=UTF8ToString($0);
      var jsString = prompt(msg);
      return eval(jsString);
    },in.c_str());
  return d;  
}

string get_string(const string & in){
  char buf[1024];
  EM_ASM({
      var msg=UTF8ToString($0);
      var jsString = prompt(msg);
      var lengthBytes = lengthBytesUTF8(jsString)+1;
      stringToUTF8(jsString,$1,1024);
      },in.c_str(),buf);
  string s(buf);
  //free(buf);
  return s;
}


int main(int argc, char** argv) {
  printf("hello, world!\n");
  // int i=get_int("Tapez un entier?");
  string s=get_string("Quel est votre nom?");
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
  EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif

  if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
  // EM_ASM("prompt('Tapez un nombre');");
  double d=get_double("Tapez un reel");
  cout << s << " " << d <<"\n";
  
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
#ifdef TEST_SDL_LOCK_OPTS
      // Alpha behaves like in the browser, so write proper opaque pixels.
      int alpha = 255;
#else
      // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
      // data (and testing that it does get discarded)
      int alpha = (i+j) % 255;
#endif
      *((Uint32*)screen->pixels + i * 256 + j) = SDL_MapRGBA(screen->format, i, j, 255-i, alpha);
    }
  }
  if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
  SDL_Flip(screen); 

  printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
  printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");

  SDL_Quit();

  return 0;
}

