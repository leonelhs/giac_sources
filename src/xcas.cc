#include "config.h"
#include "giacPCH.h"
#ifdef HAVE_LIBFLTK
#include "hist.cxx"
#else
#include <stdio.h>
using namespace std;
int main(){
  printf("No GUI support, try icas instead or recompile Giac with\n");
  printf("./configure --enable-fltk-support\n");
  printf("make clean ; make\n");
}
#endif
