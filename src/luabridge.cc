#include <os.h>
#include <lauxlib.h>
#include "giac.h"
#include "luabridge.h"
#include "kdisplay.h"

using namespace giac;
//const char std::endl='\n';
//nio::console * std::console_cin_ptr=0;
using namespace std;

void luagiac_init(){
  nspirelua=true;
  giac::context * contextptr=(giac::context *)giac::caseval("caseval contextptr");
  giac::micropy_ptr=micropy_ck_eval;
  freeze=true;
  python_heap=0;
  xcas::sheetptr=0;
  shutdown=do_shutdown;
  // SetQuitHandler(save_session); // automatically save session when exiting
  if (!turtleptr){
    turtle();
    giac::_efface_logo(giac::vecteur(0),contextptr);
  }
  giac::caseval("floor"); // init xcas parser for Python syntax coloration (!)
  int key;
  xcas::Console_Init(contextptr);
  rand_seed(millis(),contextptr);
  giac::angle_radian(os_get_angle_unit()==0,contextptr);
  // GetKey(&key);
  // Console_Disp(1,contextptr);
}

const char * giac_caseval(const char * s){
  static int initialized=0;
  if (!initialized){
    luagiac_init();
    initialized=1;
  }
  vx_var=identificateur("x");
  //static nio::console console_cin;
  //console_cin_ptr=&console_cin;
  giac::debug_infolevel=2;
  const char * res=giac::caseval(s);
  return res;
}

