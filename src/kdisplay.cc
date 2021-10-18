// -*- mode:C++ ; compile-command: "g++-3.4 -I. -I.. -g -c Equation.cc -DHAVE_CONFIG_H -DIN_GIAC -Wall" -*-
/*
 *  Copyright (C) 2005,2014 B. Parisse, Institut Fourier, 38402 St Martin d'Heres
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifdef NUMWORKS

#include "kdisplay.h"
#include "input_parser.h"
//giac::context * contextptr=0;
int clip_ymin=0;
int lang=0;
bool xthetat=true;
int esc_flag=0;
using namespace std;
using namespace giac;
const int LCD_WIDTH_PX=320;
const int LCD_HEIGHT_PX=222;

// Numworks Logo commands
#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC
  void DefineStatusMessage(const char * s,int a,int b,int c){
  }

  void DisplayStatusArea(){
  }

  void set_xcas_status(){
  }
  int GetSetupSetting(int mode){
    return 0;
  }

  void handle_f5(){
  }

  void copy_clipboard(const string & s,bool b){
  }
  string paste_clipboard(){
    return "";
  }
  bool inputline(const char * prompt,std::string & res,bool b){
    return false;
  }
  bool inputline(const char * prompt,int pos,std::string & res,bool b){
    return false;
  }
  void invalid_varname(){
  }
  bool confirm_overwrite(){
    return true;
  }
  int confirm(const char * prompt1,const char * prompt2){
    return KEY_CTRL_F6;
  }
  bool isalphanum(char c){
    return (c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9');
  }
  const char * keytostring(int key,int keyflag){
    return 0;
  }
  void translate_fkey(int & key){
  }
  const char * console_menu(int key,int keyflag){
    return "factor";
  }

  logo_turtle * turtleptr=0;
  
  logo_turtle & turtle(){
    if (!turtleptr)
      turtleptr=new logo_turtle;
    return * turtleptr;
  }
  
  const int MAX_LOGO=368; // 512;

  std::vector<logo_turtle> & turtle_stack(){
    static std::vector<logo_turtle> * ans = 0;
    if (!ans){
      // initialize from python app storage
      ans=new std::vector<logo_turtle>(1,(*turtleptr));
     
    }
    return *ans;
  }

  logo_turtle vecteur2turtle(const vecteur & v){
    int s=int(v.size());
    if (s>=5 && v[0].type==_DOUBLE_ && v[1].type==_DOUBLE_ && v[2].type==_DOUBLE_ && v[3].type==_INT_ && v[4].type==_INT_ ){
      logo_turtle t;
      t.x=v[0]._DOUBLE_val;
      t.y=v[1]._DOUBLE_val;
      t.theta=v[2]._DOUBLE_val;
      int i=v[3].val;
      t.mark=(i%2)!=0;
      i=i >> 1;
      t.visible=(i%2)!=0;
      i=i >> 1;
      t.direct = (i%2)!=0;
      i=i >> 1;
      t.turtle_length = i & 0xff;
      i=i >> 8;
      t.color = i;
      t.radius = v[4].val;
      if (s>5 && v[5].type==_INT_)
	t.s=v[5].val;
      else
	t.s=-1;
      return t;
    }
#ifndef NO_STDEXCEPT
    setsizeerr(gettext("vecteur2turtle")); // FIXME
#endif
    return logo_turtle();
  }

  static int turtle_status(const logo_turtle & turtle){
    int status= (turtle.color << 11) | ( (turtle.turtle_length & 0xff) << 3) ;
    if (turtle.direct)
      status += 4;
    if (turtle.visible)
      status += 2;
    if (turtle.mark)
      status += 1;
    return status;
  }

  bool set_turtle_state(const vecteur & v,GIAC_CONTEXT){
    if (v.size()>=2 && v[0].type==_DOUBLE_ && v[1].type==_DOUBLE_){
      vecteur w(v);
      int s=int(w.size());
      if (s==2)
	w.push_back(double((*turtleptr).theta));
      if (s<4)
	w.push_back(turtle_status((*turtleptr)));
      if (s<5)
	w.push_back(0);
      if (w[2].type==_DOUBLE_ && w[3].type==_INT_ && w[4].type==_INT_){
	(*turtleptr)=vecteur2turtle(w);
#ifdef TURTLETAB
	turtle_stack_push_back(*turtleptr);
#else
	turtle_stack().push_back((*turtleptr));
#endif
	return true;
      }
    }
    return false;
  }

  gen turtle2gen(const logo_turtle & turtle){
    return gen(makevecteur(turtle.x,turtle.y,double(turtle.theta),turtle_status(turtle),turtle.radius,turtle.s),_LOGO__VECT);
  }

  gen turtle_state(GIAC_CONTEXT){
    return turtle2gen((*turtleptr));
  }

  static gen update_turtle_state(bool clrstring,GIAC_CONTEXT){
#ifdef TURTLETAB
    if (turtle_stack_size>=MAX_LOGO)
      return gensizeerr("Not enough memory");
#else
    if (turtle_stack().size()>=MAX_LOGO){
      ctrl_c=true; interrupted=true;
      return gensizeerr("Not enough memory");
    }
#endif
    if (clrstring)
      (*turtleptr).s=-1;
    (*turtleptr).theta = (*turtleptr).theta - floor((*turtleptr).theta/360)*360;
#ifdef TURTLETAB
    turtle_stack_push_back((*turtleptr));
#else
    turtle_stack().push_back((*turtleptr));
#endif
    gen res=turtle_state(contextptr);
#ifdef EMCC // should directly interact with canvas
    return gen(turtlevect2vecteur(turtle_stack()),_LOGO__VECT);
#endif
    return res;
  }

  gen _avance(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    double i;
    if (g.type!=_INT_){
      if (g.type==_VECT)
	i=(*turtleptr).turtle_length;
      else {
	gen g1=evalf_double(g,1,contextptr);
	if (g1.type==_DOUBLE_)
	  i=g1._DOUBLE_val;
	else
	  return gensizeerr(contextptr);
      }
    }
    else
      i=g.val;
    (*turtleptr).x += i * std::cos((*turtleptr).theta*deg2rad_d);
    (*turtleptr).y += i * std::sin((*turtleptr).theta*deg2rad_d) ;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _avance_s []="avance";
  static define_unary_function_eval2 (__avance,&_avance,_avance_s,&printastifunction);
  define_unary_function_ptr5( at_avance ,alias_at_avance,&__avance,0,T_LOGO);

  static const char _forward_s []="forward";
  static define_unary_function_eval (__forward,&_avance,_forward_s);
  define_unary_function_ptr5( at_forward ,alias_at_forward,&__forward,0,true);

  gen _recule(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    if (g.type==_VECT)
      return _avance(-(*turtleptr).turtle_length,contextptr);
    return _avance(-g,contextptr);
  }
  static const char _recule_s []="recule";
  static define_unary_function_eval2 (__recule,&_recule,_recule_s,&printastifunction);
  define_unary_function_ptr5( at_recule ,alias_at_recule,&__recule,0,T_LOGO);

  static const char _backward_s []="backward";
  static define_unary_function_eval (__backward,&_recule,_backward_s);
  define_unary_function_ptr5( at_backward ,alias_at_backward,&__backward,0,true);

  gen _position(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    if (g.type!=_VECT)
      return makevecteur((*turtleptr).x,(*turtleptr).y);
    // return turtle_state();
    vecteur v = *g._VECTptr;
    int s=int(v.size());
    if (!s)
      return makevecteur((*turtleptr).x,(*turtleptr).y);
    v[0]=evalf_double(v[0],1,contextptr);
    if (s>1)
      v[1]=evalf_double(v[1],1,contextptr);
    if (s>2)
      v[2]=evalf_double(v[2],1,contextptr); 
    if (set_turtle_state(v,contextptr))
      return update_turtle_state(true,contextptr);
    return zero;
  }
  static const char _position_s []="position";
  static define_unary_function_eval2 (__position,&_position,_position_s,&printastifunction);
  define_unary_function_ptr5( at_position ,alias_at_position,&__position,0,T_LOGO);

  gen _cap(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    gen gg=evalf_double(g,1,contextptr);
    if (gg.type!=_DOUBLE_)
      return double((*turtleptr).theta);
    (*turtleptr).theta=gg._DOUBLE_val;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _cap_s []="cap";
  static define_unary_function_eval2 (__cap,&_cap,_cap_s,&printastifunction);
  define_unary_function_ptr5( at_cap ,alias_at_cap,&__cap,0,T_LOGO);

  static const char _heading_s []="heading";
  static define_unary_function_eval (__heading,&_cap,_heading_s);
  define_unary_function_ptr5( at_heading ,alias_at_heading,&__heading,0,true);


  gen _tourne_droite(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    if (g.type!=_INT_){
      if (g.type==_VECT)
	(*turtleptr).theta -= 90;
      else {
	gen g1=evalf_double(g,1,contextptr);
	if (g1.type==_DOUBLE_)
	  (*turtleptr).theta -= g1._DOUBLE_val;
	else
	  return gensizeerr(contextptr);
      }
    }
    else
      (*turtleptr).theta -= g.val;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _tourne_droite_s []="tourne_droite";
  static define_unary_function_eval2 (__tourne_droite,&_tourne_droite,_tourne_droite_s,&printastifunction);
  define_unary_function_ptr5( at_tourne_droite ,alias_at_tourne_droite,&__tourne_droite,0,T_LOGO);

  gen _tourne_gauche(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    if (g.type==_VECT){
      (*turtleptr).theta += 90;
      (*turtleptr).radius = 0;
      return update_turtle_state(true,contextptr);
    }
    return _tourne_droite(-g,contextptr);
  }
  static const char _tourne_gauche_s []="tourne_gauche";
  static define_unary_function_eval2 (__tourne_gauche,&_tourne_gauche,_tourne_gauche_s,&printastifunction);
  define_unary_function_ptr5( at_tourne_gauche ,alias_at_tourne_gauche,&__tourne_gauche,0,T_LOGO);

  gen _leve_crayon(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    (*turtleptr).mark = false;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _leve_crayon_s []="leve_crayon";
  static define_unary_function_eval2 (__leve_crayon,&_leve_crayon,_leve_crayon_s,&printastifunction);
  define_unary_function_ptr5( at_leve_crayon ,alias_at_leve_crayon,&__leve_crayon,0,T_LOGO);

  static const char _penup_s []="penup";
  static define_unary_function_eval (__penup,&_leve_crayon,_penup_s);
  define_unary_function_ptr5( at_penup ,alias_at_penup,&__penup,0,T_LOGO);

  gen _baisse_crayon(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    (*turtleptr).mark = true;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _baisse_crayon_s []="baisse_crayon";
  static define_unary_function_eval2 (__baisse_crayon,&_baisse_crayon,_baisse_crayon_s,&printastifunction);
  define_unary_function_ptr5( at_baisse_crayon ,alias_at_baisse_crayon,&__baisse_crayon,0,T_LOGO);

  static const char _pendown_s []="pendown";
  static define_unary_function_eval (__pendown,&_baisse_crayon,_pendown_s);
  define_unary_function_ptr5( at_pendown ,alias_at_pendown,&__pendown,0,T_LOGO);

  vector<string> * ecrisptr=0;
  vector<string> & ecristab(){
    if (!ecrisptr)
      ecrisptr=new vector<string>;
    return * ecrisptr;
  }
  gen _ecris(const gen & g,GIAC_CONTEXT){    
    if ( g.type==_STRNG && g.subtype==-1) return  g;
#if 0 //def TURTLETAB
    return gensizeerr("String support does not work with static turtle table");
#endif
    // logo instruction
    (*turtleptr).radius=14;
    if (g.type==_VECT){ 
      vecteur & v =*g._VECTptr;
      int s=int(v.size());
      if (s==2 && v[1].type==_INT_){
	(*turtleptr).radius=absint(v[1].val);
	(*turtleptr).s=ecristab().size();
	ecristab().push_back(gen2string(v.front()));
	return update_turtle_state(false,contextptr);
      }
      if (s==4 && v[1].type==_INT_ && v[2].type==_INT_ && v[3].type==_INT_){
	logo_turtle t=(*turtleptr);
	_leve_crayon(0,contextptr);
	_position(makevecteur(v[2],v[3]),contextptr);
	(*turtleptr).radius=absint(v[1].val);
	(*turtleptr).s=ecristab().size();
	ecristab().push_back(gen2string(v.front()));
	update_turtle_state(false,contextptr);
	(*turtleptr)=t;
	return update_turtle_state(true,contextptr);
      }
    }
    (*turtleptr).s=ecristab().size();
    ecristab().push_back(gen2string(g));
    return update_turtle_state(false,contextptr);
  }
  static const char _ecris_s []="ecris";
  static define_unary_function_eval2 (__ecris,&_ecris,_ecris_s,&printastifunction);
  define_unary_function_ptr5( at_ecris ,alias_at_ecris,&__ecris,0,T_LOGO);

  gen _signe(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    return _ecris(makevecteur(g,20,10,10),contextptr);
  }
  static const char _signe_s []="signe";
  static define_unary_function_eval2 (__signe,&_signe,_signe_s,&printastifunction);
  define_unary_function_ptr5( at_signe ,alias_at_signe,&__signe,0,T_LOGO);

  gen _saute(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    _leve_crayon(0,contextptr);
    _avance(g,contextptr);
    return _baisse_crayon(0,contextptr);
  }
  static const char _saute_s []="saute";
  static define_unary_function_eval2 (__saute,&_saute,_saute_s,&printastifunction);
  define_unary_function_ptr5( at_saute ,alias_at_saute,&__saute,0,T_LOGO);

  static const char _jump_s []="jump";
  static define_unary_function_eval2 (__jump,&_saute,_jump_s,&printastifunction);
  define_unary_function_ptr5( at_jump ,alias_at_jump,&__jump,0,T_LOGO);

  gen _pas_de_cote(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    _leve_crayon(0,contextptr);
    _tourne_droite(-90,contextptr);
    _avance(g,contextptr);
    _tourne_droite(90,contextptr);
    return _baisse_crayon(0,contextptr);
  }
  static const char _pas_de_cote_s []="pas_de_cote";
  static define_unary_function_eval2 (__pas_de_cote,&_pas_de_cote,_pas_de_cote_s,&printastifunction);
  define_unary_function_ptr5( at_pas_de_cote ,alias_at_pas_de_cote,&__pas_de_cote,0,T_LOGO);

  static const char _skip_s []="skip";
  static define_unary_function_eval2 (__skip,&_pas_de_cote,_skip_s,&printastifunction);
  define_unary_function_ptr5( at_skip ,alias_at_skip,&__skip,0,T_LOGO);

  gen _cache_tortue(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    (*turtleptr).visible=false;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _cache_tortue_s []="cache_tortue";
  static define_unary_function_eval2 (__cache_tortue,&_cache_tortue,_cache_tortue_s,&printastifunction);
  define_unary_function_ptr5( at_cache_tortue ,alias_at_cache_tortue,&__cache_tortue,0,T_LOGO);

  static const char _hideturtle_s []="hideturtle";
  static define_unary_function_eval (__hideturtle,&_cache_tortue,_hideturtle_s);
  define_unary_function_ptr5( at_hideturtle ,alias_at_hideturtle,&__hideturtle,0,true);

  gen _montre_tortue(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    (*turtleptr).visible=true;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _montre_tortue_s []="montre_tortue";
  static define_unary_function_eval2 (__montre_tortue,&_montre_tortue,_montre_tortue_s,&printastifunction);
  define_unary_function_ptr5( at_montre_tortue ,alias_at_montre_tortue,&__montre_tortue,0,T_LOGO);

  static const char _showturtle_s []="showturtle";
  static define_unary_function_eval (__showturtle,&_montre_tortue,_showturtle_s);
  define_unary_function_ptr5( at_showturtle ,alias_at_showturtle,&__showturtle,0,true);


  gen _repete(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    if (g.type!=_VECT || g._VECTptr->size()<2)
      return gensizeerr(contextptr);
    // logo instruction
    vecteur v = *g._VECTptr;
    v[0]=eval(v[0],contextptr);
    if (v.front().type!=_INT_)
      return gentypeerr(contextptr);
    gen prog=vecteur(v.begin()+1,v.end());
    int i=absint(v.front().val);
    gen res;
    for (int j=0;j<i;++j){
      res=eval(prog,contextptr);
    }
    return res;
  }
  static const char _repete_s []="repete";
  static define_unary_function_eval_quoted (__repete,&_repete,_repete_s);
  define_unary_function_ptr5( at_repete ,alias_at_repete,&__repete,_QUOTE_ARGUMENTS,T_RETURN);

  gen _crayon(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    if (g.type==_STRNG) return _crayon(gen(*g._STRNGptr,contextptr),contextptr);
    // logo instruction
    if (g.type==_VECT && g._VECTptr->size()==3)
      return _crayon(_rgb(g,contextptr),contextptr);
    if (g.type!=_INT_){
      gen res=(*turtleptr).color;
      res.subtype=_INT_COLOR;
      return res;
    }
    (*turtleptr).color=g.val;
    (*turtleptr).radius = 0;
    return update_turtle_state(true,contextptr);
  }
  static const char _crayon_s []="crayon";
  static define_unary_function_eval2 (__crayon,&_crayon,_crayon_s,&printastifunction);
  define_unary_function_ptr5( at_crayon ,alias_at_crayon,&__crayon,0,T_LOGO);

  static const char _pencolor_s []="pencolor";
  static define_unary_function_eval (__pencolor,&_crayon,_pencolor_s);
  define_unary_function_ptr5( at_pencolor ,alias_at_pencolor,&__pencolor,0,T_LOGO);

  gen _efface_logo(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    if (g.type==_INT_){
      _crayon(int(FL_WHITE),contextptr);
      _recule(g,contextptr);
      return _crayon(0,contextptr);
    }
    // logo instruction
    (*turtleptr) = logo_turtle();
#ifdef TURTLETAB
    turtle_stack_size=0;
#else
    turtle_stack().clear();
#endif
    ecristab().clear();
    return update_turtle_state(true,contextptr);
  }
  static const char _efface_logo_s []="efface";
  static define_unary_function_eval2 (__efface_logo,&_efface_logo,_efface_logo_s,&printastifunction);
  define_unary_function_ptr5( at_efface_logo ,alias_at_efface_logo,&__efface_logo,0,T_LOGO);

  static const char _efface_s []="efface";
  static define_unary_function_eval2 (__efface,&_efface_logo,_efface_s,&printastifunction);
  define_unary_function_ptr5( at_efface ,alias_at_efface,&__efface,0,T_LOGO);

  static const char _reset_s []="reset";
  static define_unary_function_eval2 (__reset,&_efface_logo,_reset_s,&printastifunction);
  define_unary_function_ptr5( at_reset ,alias_at_reset,&__reset,0,T_LOGO);

  static const char _clearscreen_s []="clearscreen";
  static define_unary_function_eval2 (__clearscreen,&_efface_logo,_clearscreen_s,&printastifunction);
  define_unary_function_ptr5( at_clearscreen ,alias_at_clearscreen,&__clearscreen,0,T_LOGO);

  gen _debut_enregistrement(const gen &g,GIAC_CONTEXT){
    return undef;
  }
  static const char _debut_enregistrement_s []="debut_enregistrement";
  static define_unary_function_eval2 (__debut_enregistrement,&_debut_enregistrement,_debut_enregistrement_s,&printastifunction);
  define_unary_function_ptr5( at_debut_enregistrement ,alias_at_debut_enregistrement,&__debut_enregistrement,0,T_LOGO);

  static const char _fin_enregistrement_s []="fin_enregistrement";
  static define_unary_function_eval2 (__fin_enregistrement,&_debut_enregistrement,_fin_enregistrement_s,&printastifunction);
  define_unary_function_ptr5( at_fin_enregistrement ,alias_at_fin_enregistrement,&__fin_enregistrement,0,T_LOGO);

  static const char _turtle_stack_s []="turtle_stack";
  static define_unary_function_eval2 (__turtle_stack,&_debut_enregistrement,_turtle_stack_s,&printastifunction);
  define_unary_function_ptr5( at_turtle_stack ,alias_at_turtle_stack,&__turtle_stack,0,T_LOGO);

  gen _vers(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    if (g.type!=_VECT || g._VECTptr->size()!=2)
      return gensizeerr(contextptr);
    gen x=evalf_double(g._VECTptr->front(),1,contextptr),
      y=evalf_double(g._VECTptr->back(),1,contextptr);
    if (x.type!=_DOUBLE_ || y.type!=_DOUBLE_)
      return gensizeerr(contextptr);
    double xv=x._DOUBLE_val,yv=y._DOUBLE_val,xt=(*turtleptr).x,yt=(*turtleptr).y;
    double theta=atan2(yv-yt,xv-xt);
    return _cap(theta*180/M_PI,contextptr);
  }
  static const char _vers_s []="vers";
  static define_unary_function_eval2 (__vers,&_vers,_vers_s,&printastifunction);
  define_unary_function_ptr5( at_vers ,alias_at_vers,&__vers,0,T_LOGO);

  static int find_radius(const gen & g,int & r,int & theta2,bool & direct){
    int radius;
    direct=true;
    theta2 = 360 ;
    // logo instruction
    if (g.type==_VECT && !g._VECTptr->empty()){
      vecteur v = *g._VECTptr;
      bool seg=false;
      if (v.back()==at_segment){
	v.pop_back();
	seg=true;
      }
      if (v.size()<2)
	return RAND_MAX; // setdimerr(contextptr);
      if (v[0].type==_INT_)
	r=v[0].val;
      else {
	gen v0=evalf_double(v[0],1,context0);
	if (v0.type==_DOUBLE_)
	  r=int(v0._DOUBLE_val+0.5);
	else 
	  return RAND_MAX; // setsizeerr(contextptr);
      }
      if (r<0){
	r=-r;
	direct=false;
      }
      int theta1;
      if (v[1].type==_DOUBLE_)
	theta1=int(v[1]._DOUBLE_val+0.5);
      else { 
	if (v[1].type==_INT_)
	  theta1=v[1].val;
	else return RAND_MAX; // setsizeerr(contextptr);
      }
      while (theta1<0)
	theta1 += 360;
      if (v.size()>=3){
	if (v[2].type==_DOUBLE_)
	  theta2 = int(v[2]._DOUBLE_val+0.5);
	else {
	  if (v[2].type==_INT_)
	    theta2 = v[2].val;
	  else return RAND_MAX; // setsizeerr(contextptr);
	}
	while (theta2<0)
	  theta2 += 360;
	radius = giacmin(r,512) | (giacmin(theta1,360) << 9) | (giacmin(theta2,360) << 18 ) | (seg?(1<<28):0);
      }
      else {// angle 1=0
	theta2 = theta1;
	if (theta2<0)
	  theta2 += 360;
	radius = giacmin(r,512) | (giacmin(theta2,360) << 18 ) | (seg?(1<<28):0);
      }
      return radius;
    }
    radius = 10;
    if (g.type==_INT_)
      radius= (r=g.val);
    if (g.type==_DOUBLE_)
      radius= (r=int(g._DOUBLE_val));
    if (radius<=0){
      radius = -radius;
      direct=false;
    }
    radius = giacmin(radius,512 )+(360 << 18) ; // 2nd angle = 360 degrees
    return radius;
  }

  static void turtle_move(int r,int theta2,GIAC_CONTEXT){
    double theta0;
    if ((*turtleptr).direct)
      theta0=(*turtleptr).theta-90;
    else {
      theta0=(*turtleptr).theta+90;
      theta2=-theta2;
    }
    (*turtleptr).x += r*(std::cos(M_PI/180*(theta2+theta0))-std::cos(M_PI/180*theta0));
    (*turtleptr).y += r*(std::sin(M_PI/180*(theta2+theta0))-std::sin(M_PI/180*theta0));
    (*turtleptr).theta = (*turtleptr).theta+theta2 ;
    if ((*turtleptr).theta<0)
      (*turtleptr).theta += 360;
    if ((*turtleptr).theta>360)
      (*turtleptr).theta -= 360;
  }

  gen _rond(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    int r,theta2,tmpr;
    tmpr=find_radius(g,r,theta2,(*turtleptr).direct);
    if (tmpr==RAND_MAX)
      return gensizeerr(contextptr);
    (*turtleptr).radius=tmpr;
    turtle_move(r,theta2,contextptr);
    return update_turtle_state(true,contextptr);
  }
  static const char _rond_s []="rond";
  static define_unary_function_eval2 (__rond,&_rond,_rond_s,&printastifunction);
  define_unary_function_ptr5( at_rond ,alias_at_rond,&__rond,0,T_LOGO);

  gen _disque(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    int r,theta2,tmpr=find_radius(g,r,theta2,(*turtleptr).direct);
    if (tmpr==RAND_MAX)
      return gensizeerr(contextptr);
    (*turtleptr).radius=tmpr;
    turtle_move(r,theta2,contextptr);
    (*turtleptr).radius += 1 << 27;
    return update_turtle_state(true,contextptr);
  }
  static const char _disque_s []="disque";
  static define_unary_function_eval2 (__disque,&_disque,_disque_s,&printastifunction);
  define_unary_function_ptr5( at_disque ,alias_at_disque,&__disque,0,T_LOGO);

  gen _disque_centre(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    int r,theta2;
    bool direct;
    int radius=find_radius(g,r,theta2,direct);
    if (radius==RAND_MAX)
      return gensizeerr(contextptr);
    r=absint(r);
    _saute(r,contextptr);
    _tourne_gauche(direct?90:-90,contextptr);
    (*turtleptr).radius = radius;
    (*turtleptr).direct=direct;
    turtle_move(r,theta2,contextptr);
    (*turtleptr).radius += 1 << 27;
    update_turtle_state(true,contextptr);
    _tourne_droite(direct?90:-90,contextptr);
    return _saute(-r,contextptr);
  }
  static const char _disque_centre_s []="disque_centre";
  static define_unary_function_eval2 (__disque_centre,&_disque_centre,_disque_centre_s,&printastifunction);
  define_unary_function_ptr5( at_disque_centre ,alias_at_disque_centre,&__disque_centre,0,T_LOGO);

  gen _polygone_rempli(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    if (g.type==_INT_){
      (*turtleptr).radius=-absint(g.val);
      if ((*turtleptr).radius<-1)
	return update_turtle_state(true,contextptr);
    }
    return gensizeerr(gettext("Integer argument >= 2"));
  }
  static const char _polygone_rempli_s []="polygone_rempli";
  static define_unary_function_eval2 (__polygone_rempli,&_polygone_rempli,_polygone_rempli_s,&printastifunction);
  define_unary_function_ptr5( at_polygone_rempli ,alias_at_polygone_rempli,&__polygone_rempli,0,T_LOGO);

  gen _rectangle_plein(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    gen gx=g,gy=g;
    if (g.type==_VECT && g._VECTptr->size()==2){
      gx=g._VECTptr->front();
      gy=g._VECTptr->back();
    }
    for (int i=0;i<2;++i){
      _avance(gx,contextptr);
      _tourne_droite(-90,contextptr);
      _avance(gy,contextptr);
      _tourne_droite(-90,contextptr);
    }
    //for (int i=0;i<turtle_stack().size();++i){ *logptr(contextptr) << turtle2gen(turtle_stack()[i]) <<endl;}
    return _polygone_rempli(-8,contextptr);
  }
  static const char _rectangle_plein_s []="rectangle_plein";
  static define_unary_function_eval2 (__rectangle_plein,&_rectangle_plein,_rectangle_plein_s,&printastifunction);
  define_unary_function_ptr5( at_rectangle_plein ,alias_at_rectangle_plein,&__rectangle_plein,0,T_LOGO);

  gen _triangle_plein(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    gen gx=g,gy=g,gtheta=60;
    if (g.type==_VECT && g._VECTptr->size()>=2){
      vecteur & v=*g._VECTptr;
      gx=v.front();
      gy=v[1];
      gtheta=90;
      if (v.size()>2)
	gtheta=v[2];
    }
    logo_turtle t=(*turtleptr);
    _avance(gx,contextptr);
    double save_x=(*turtleptr).x,save_y=(*turtleptr).y;
    _recule(gx,contextptr);
    _tourne_gauche(gtheta,contextptr);
    _avance(gy,contextptr);
    (*turtleptr).x=save_x;
    (*turtleptr).y=save_y;
    update_turtle_state(true,contextptr);
    (*turtleptr)=t;
    (*turtleptr).radius=0;
    update_turtle_state(true,contextptr);
    return _polygone_rempli(-3,contextptr);
  }
  static const char _triangle_plein_s []="triangle_plein";
  static define_unary_function_eval2 (__triangle_plein,&_triangle_plein,_triangle_plein_s,&printastifunction);
  define_unary_function_ptr5( at_triangle_plein ,alias_at_triangle_plein,&__triangle_plein,0,T_LOGO);

  gen _dessine_tortue(const gen & g,GIAC_CONTEXT){
    if ( g.type==_STRNG && g.subtype==-1) return  g;
    // logo instruction
    /*
      _triangle_plein(makevecteur(17,5));
      _tourne_droite(90);
      _triangle_plein(makevecteur(5,17));
      return _tourne_droite(-90);
    */
    double save_x=(*turtleptr).x,save_y=(*turtleptr).y;
    _tourne_droite(90,contextptr);
    _avance(5,contextptr);
    _tourne_gauche(106,contextptr);
    _avance(18,contextptr);
    _tourne_gauche(148,contextptr);
    _avance(18,contextptr);
    _tourne_gauche(106,contextptr);
    _avance(5,contextptr);
    (*turtleptr).x=save_x; (*turtleptr).y=save_y;
    gen res(_tourne_gauche(90,contextptr));
    if (is_one(g))
      return res;
    return _polygone_rempli(-9,contextptr);
  }
  static const char _dessine_tortue_s []="dessine_tortue";
  static define_unary_function_eval2 (__dessine_tortue,&_dessine_tortue,_dessine_tortue_s,&printastifunction);
  define_unary_function_ptr5( at_dessine_tortue ,alias_at_dessine_tortue,&__dessine_tortue,0,T_LOGO);
  
#ifndef NO_NAMESPACE_GIAC
} // namespace giac
#endif // ndef NO_NAMESPACE_GIAC


#ifndef NO_NAMESPACE_XCAS
namespace xcas {
#endif // ndef NO_NAMESPACE_XCAS
  void drawRectangle(int x,int y,int w,int h,int c){
    draw_rectangle(x,y,w,h,c,context0);
  }
  void draw_rectangle(int x,int y,int w,int h,int c){
    draw_rectangle(x,y,w,h,c,context0);
  }
  void draw_line(int x0,int y0,int x1,int y1,int c){
    draw_line(x0,y0,x1,y1,c,context0);
  }
  void draw_circle(int xc,int yc,int r,int color,bool q1=true,bool q2=true,bool q3=true,bool q4=true){
    draw_circle(xc,yc,r,color,q1,q2,q3,q4,context0);
  }
  void draw_filled_circle(int xc,int yc,int r,int color,bool left=true,bool right=true){
    draw_filled_circle(xc,yc,r,color,left,right,context0);
  }
  void draw_filled_polygon(std::vector< vector<int> > &L,int xmin,int xmax,int ymin,int ymax,int color){
    draw_filled_polygon(L,xmin,xmax,ymin,ymax,color,context0);
  }
  unsigned max_prettyprint_equation=256;

  // make a free copy of g
  gen Equation_copy(const gen & g){
    if (g.type==_EQW)
      return *g._EQWptr;
    if (g.type!=_VECT)
      return g;
    vecteur & v = *g._VECTptr;
    const_iterateur it=v.begin(),itend=v.end();
    vecteur res;
    res.reserve(itend-it);
    for (;it!=itend;++it)
      res.push_back(Equation_copy(*it));
    return gen(res,g.subtype);
  }

  // matrix/list select
  bool do_select(gen & eql,bool select,gen & value){
    if (eql.type==_VECT && !eql._VECTptr->empty()){
      vecteur & v=*eql._VECTptr;
      size_t s=v.size();
      if (v[s-1].type!=_EQW)
	return false;
      v[s-1]._EQWptr->selected=select;
      gen sommet=v[s-1]._EQWptr->g;
      --s;
      vecteur args(s);
      for (size_t i=0;i<s;++i){
	if (!do_select(v[i],select,args[i]))
	  return false;
	if (args[i].type==_EQW)
	  args[i]=args[i]._EQWptr->g;
      }
      gen va=s==1?args[0]:gen(args,_SEQ__VECT);
      if (sommet.type==_FUNC)
	va=symbolic(*sommet._FUNCptr,va);
      else
	va=sommet(va,context0);
      //cout << "va " << va << endl;
      value=*v[s]._EQWptr;
      value._EQWptr->g=va;
      //cout << "value " << value << endl;
      return true;
    }
    if (eql.type!=_EQW)
      return false;
    eql._EQWptr->selected=select;
    value=eql;
    return true;
  }
  
  bool Equation_box_sizes(const gen & g,int & l,int & h,int & x,int & y,attributs & attr,bool & selected){
    if (g.type==_EQW){
      eqwdata & w=*g._EQWptr;
      x=w.x;
      y=w.y;
      l=w.dx;
      h=w.dy;
      selected=w.selected;
      attr=w.eqw_attributs;
      //cout << g << endl;
      return true;
    }
    else {
      if (g.type!=_VECT || g._VECTptr->empty() ){
	l=0;
	h=0;
	x=0;
	y=0;
	attr=attributs(0,0,0);
	selected=false;
	return true;
      }
      gen & g1=g._VECTptr->back();
      Equation_box_sizes(g1,l,h,x,y,attr,selected);
      return false;
    }
  }

  // return true if g has some selection inside, gsel points to the selection
  bool Equation_adjust_xy(gen & g,int & xleft,int & ytop,int & xright,int & ybottom,gen * & gsel,gen * & gselparent,int &gselpos,std::vector<int> * goto_ptr){
    gsel=0;
    gselparent=0;
    gselpos=0;
    int x,y,w,h;
    attributs f(0,0,0);
    bool selected;
    Equation_box_sizes(g,w,h,x,y,f,selected);
    if ( (g.type==_EQW__VECT) || selected ){ // terminal or selected
      xleft=x;
      ybottom=y;
      if (selected){ // g is selected
	ytop=y+h;
	xright=x+w;
	gsel =  &g;
	//cout << "adjust " << *gsel << endl;
	return true;
      }
      else { // no selection
	xright=x;
	ytop=y;
	return false;
      }
    }
    if (g.type!=_VECT)
      return false;
    // last not selected, recurse
    iterateur it=g._VECTptr->begin(),itend=g._VECTptr->end()-1;
    for (;it!=itend;++it){
      if (Equation_adjust_xy(*it,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,goto_ptr)){
	if (goto_ptr){
	  goto_ptr->push_back(it-g._VECTptr->begin());
	  //cout << g << ":" << *goto_ptr << endl;
	}
	if (gsel==&*it){
	  // check next siblings
	  
	  gselparent= &g;
	  gselpos=it-g._VECTptr->begin();
	  //cout << "gselparent " << g << endl;
	}
	return true;
      }
    }
    return false;
  }
 
  // select or deselect part of the current eqution
  // This is done *in place*
  void Equation_select(gen & g,bool select){
    if (g.type==_EQW){
      eqwdata & e=*g._EQWptr;
      e.selected=select;
    }
    if (g.type!=_VECT)
      return;
    vecteur & v=*g._VECTptr;
    iterateur it=v.begin(),itend=v.end();
    for (;it!=itend;++it)
      Equation_select(*it,select);
  }

  // decrease selection (like HP49 eqw Down key)
  int eqw_select_down(gen & g){
    int xleft,ytop,xright,ybottom,gselpos;
    int newxleft,newytop,newxright,newybottom;
    gen * gsel,*gselparent;
    if (Equation_adjust_xy(g,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos)){
      //cout << "select down before " << *gsel << endl;
      if (gsel->type==_VECT && !gsel->_VECTptr->empty()){
	Equation_select(*gsel,false);
	Equation_select(gsel->_VECTptr->front(),true);
	//cout << "select down after " << *gsel << endl;
	Equation_adjust_xy(g,newxleft,newytop,newxright,newybottom,gsel,gselparent,gselpos);
	return newytop-ytop;
      }
    }
    return 0;
  }

  int eqw_select_up(gen & g){
    int xleft,ytop,xright,ybottom,gselpos;
    int newxleft,newytop,newxright,newybottom;
    gen * gsel,*gselparent;
    if (Equation_adjust_xy(g,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos) && gselparent){
      Equation_select(*gselparent,true);
      //cout << "gselparent " << *gselparent << endl;
      Equation_adjust_xy(g,newxleft,newytop,newxright,newybottom,gsel,gselparent,gselpos);
      return newytop-ytop;
    }
    return false;
  }

  // exchange==0 move selection to left or right sibling, ==2 add left or right
  // sibling, ==1 exchange selection with left or right sibling
  int eqw_select_leftright(Equation & eq,bool left,int exchange,GIAC_CONTEXT){
    gen & g=eq.data;
    int xleft,ytop,xright,ybottom,gselpos;
    int newxleft,newytop,newxright,newybottom;
    gen * gsel,*gselparent;
    vector<int> goto_sel;
    if (Equation_adjust_xy(g,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel) && gselparent && gselparent->type==_VECT){
      vecteur & gselv=*gselparent->_VECTptr;
      int n=gselv.size()-1,gselpos_orig=gselpos;
      if (n<1) return 0;
      if (left) {
	if (gselpos==0)
	  gselpos=n-1;
	else
	  gselpos--;
      }
      else {
	if (gselpos==n-1)
	  gselpos=0;
	else
	  gselpos++;
      }
      if (exchange==1){ // exchange gselpos_orig and gselpos
	swapgen(gselv[gselpos],gselv[gselpos_orig]);
	gsel=&gselv[gselpos_orig];
	gen value;
	if (xcas::do_select(*gsel,true,value) && value.type==_EQW)
	  replace_selection(eq,value._EQWptr->g,gsel,&goto_sel,contextptr);
      }
      else {
	// increase selection to next sibling possible for + and * only
	if (n>2 && exchange==2 && gselv[n].type==_EQW && (gselv[n]._EQWptr->g==at_plus || gselv[n]._EQWptr->g==at_prod)){
	  gen value1, value2,tmp;
	  if (gselpos_orig<gselpos)
	    swapint(gselpos_orig,gselpos);
	  // now gselpos<gselpos_orig
	  xcas::do_select(gselv[gselpos_orig],true,value1);
	  xcas::do_select(gselv[gselpos],true,value2);
	  if (value1.type==_EQW && value2.type==_EQW){
	    tmp=gselv[n]._EQWptr->g==at_plus?value1._EQWptr->g+value2._EQWptr->g:value1._EQWptr->g*value2._EQWptr->g;
	    gselv.erase(gselv.begin()+gselpos_orig);
	    replace_selection(eq,tmp,&gselv[gselpos],&goto_sel,contextptr);
	  }
	}
	else {
	  Equation_select(*gselparent,false);
	  gen & tmp=(*gselparent->_VECTptr)[gselpos];
	  Equation_select(tmp,true);
	}
      }
      Equation_adjust_xy(g,newxleft,newytop,newxright,newybottom,gsel,gselparent,gselpos);
      return newxleft-xleft;
    }
    return 0;
  }

  bool eqw_select(const gen & eq,int l,int c,bool select,gen & value){
    value=undef;
    if (l<0 || eq.type!=_VECT || eq._VECTptr->size()<=l)
      return false;
    gen & eql=(*eq._VECTptr)[l];
    if (c<0)
      return do_select(eql,select,value);
    if (eql.type!=_VECT || eql._VECTptr->size()<=c)
      return false;
    gen & eqlc=(*eql._VECTptr)[c];
    return do_select(eqlc,select,value);
  }

  gen Equation_compute_size(const gen & g,const attributs & a,int windowhsize,GIAC_CONTEXT);
  
  // void Bdisp_MMPrint(int x, int y, const char* string, int mode_flags, int xlimit, int P6, int P7, int color, int back_color, int writeflag, int P11); 
  // void PrintCXY(int x, int y, const char *cptr, int mode_flags, int P5, int color, int back_color, int P8, int P9)
  // void PrintMini( int* x, int* y, const char* string, int mode_flags, unsigned int xlimit, int P6, int P7, int color, int back_color, int writeflag, int P11) 
  void text_print(int fontsize,const char * s,int x,int y,int c=COLOR_BLACK,int bg=COLOR_WHITE,int mode=0){
    // *logptr(contextptr) << x << " " << y << " " << fontsize << " " << s << endl; return;
    c=(unsigned short) c;
    if (x>LCD_WIDTH_PX) return;
    int ss=strlen(s);
    if (ss==1 && s[0]==0x1e){ // arrow for limit
      if (mode==4)
	c=bg;
      draw_line(x,y-4,x+fontsize/2,y-4,c);
      draw_line(x,y-3,x+fontsize/2,y-3,c);
      draw_line(x+fontsize/2-4,y,x+fontsize/2,y-4,c);
      draw_line(x+fontsize/2-3,y,x+fontsize/2+1,y-4,c);
      draw_line(x+fontsize/2-4,y-7,x+fontsize/2,y-3,c);   
      draw_line(x+fontsize/2-3,y-7,x+fontsize/2+1,y-3,c);   
      return;
    }
    if (ss==2 && strcmp(s,"pi")==0){
      if (mode==4){
	drawRectangle(x,y+2-fontsize,fontsize,fontsize,c);
	c=bg;
      }
      draw_line(x+fontsize/3-1,y+1,x+fontsize/3,y+6-fontsize,c);
      draw_line(x+fontsize/3-2,y+1,x+fontsize/3-1,y+6-fontsize,c);
      draw_line(x+2*fontsize/3,y+1,x+2*fontsize/3,y+6-fontsize,c);
      draw_line(x+2*fontsize/3+1,y+1,x+2*fontsize/3+1,y+6-fontsize,c);
      draw_line(x+2,y+6-fontsize,x+fontsize,y+6-fontsize,c);
      draw_line(x+2,y+5-fontsize,x+fontsize,y+5-fontsize,c);
      return;
    }
    if (fontsize>=16 && ss==2 && s[0]==char(0xe5) && (s[1]==char(0xea) || s[1]==char(0xeb))) // special handling for increasing and decreasing in tabvar output
      fontsize=18;
    if (fontsize>=18){
      y -= 16;// status area shift
      numworks_giac_draw_string(x,y,mode==4?bg:c,mode==4?c:bg,s);
      // PrintMini(&x,&y,(unsigned char *)s,mode,0xffffffff,0,0,c,bg,1,0);
      return;
    }
    y -= 12;
    numworks_giac_draw_string_small(x,y,mode==4?bg:c,mode==4?c:bg,s);// PrintMiniMini( &x, &y, (unsigned char *)s, mode,c, 0 );
    return;
  }
  
  int text_width(int fontsize,const char * s){
    if (fontsize>=18)
      return strlen(s)*11;
    return strlen(s)*7;
  }

  void fl_arc(int x,int y,int rx,int ry,int theta1_deg,int theta2_deg,int c=COLOR_BLACK){
    rx/=2;
    ry/=2;
    // *logptr(contextptr) << "theta " << theta1_deg << " " << theta2_deg << endl;
    if (ry==rx){
      if (theta2_deg-theta1_deg==360){
	draw_circle(x+rx,y+rx,rx,c);
	return;
      }
      if (theta1_deg==0 && theta2_deg==180){
	draw_circle(x+rx,y+rx,rx,c,true,true,false,false);
	return;
      }
      if (theta1_deg==180 && theta2_deg==360){
	draw_circle(x+rx,y+rx,rx,c,false,false,true,true);
	return;
      }
    }
    // *logptr(contextptr) << "draw_arc" << theta1_deg*M_PI/180. << " " << theta2_deg*M_PI/180. << endl;
    draw_arc(x+rx,y+ry,rx,ry,c,theta1_deg*M_PI/180.,theta2_deg*M_PI/180.,context0);
  }

  void fl_pie(int x,int y,int rx,int ry,int theta1_deg,int theta2_deg,int c=COLOR_BLACK,bool segment=false){
    //cout << "fl_pie " << theta1_deg << " " << theta2_deg << " " << c << endl;
    if (!segment && ry==rx){
      if (theta2_deg-theta1_deg>=360){
	rx/=2;
	draw_filled_circle(x+rx,y+rx,rx,c);
	return;
      }
      if (theta1_deg==-90 && theta2_deg==90){
	rx/=2;
	draw_filled_circle(x+rx,y+rx,rx,c,false,true);
	return;
      }
      if (theta1_deg==90 && theta2_deg==270){
	rx/=2;
	draw_filled_circle(x+rx,y+rx,rx,c,true,false);
	return;
      }
    }
    // approximation by a filled polygon
    // points: (x,y), (x+rx*cos(theta)/2,y+ry*sin(theta)/2) theta=theta1..theta2
    while (theta2_deg<theta1_deg)
      theta2_deg+=360;
    if (theta2_deg-theta1_deg>=360){
      theta1_deg=0;
      theta2_deg=360;
    }
    int N0=theta2_deg-theta1_deg+1;
    // reduce N if rx or ry is small
    double red=double(rx)/LCD_WIDTH_PX*double(ry)/LCD_HEIGHT_PX;
    if (red>1) red=1;
    if (red<0.1) red=0.1;
    int N=red*N0;
    if (N<5)
      N=N0>5?5:N0;
    if (N<2)
      N=2;
    vector< vector<int> > v(segment?N+1:N+2,vector<int>(2));
    x += rx/2;
    y += ry/2;
    int i=0;
    if (!segment){
      v[0][0]=x;
      v[0][1]=y;
      ++i;
    }
    double theta=theta1_deg*M_PI/180;
    double thetastep=(theta2_deg-theta1_deg)*M_PI/(180*(N-1));
    for (;i<v.size()-1;++i){
      v[i][0]=int(x+rx*std::cos(theta)/2+.5);
      v[i][1]=int(y-ry*std::sin(theta)/2+.5); // y is inverted
      theta += thetastep;
    }
    v.back()=v.front();
    draw_filled_polygon(v,0,LCD_WIDTH_PX,24,LCD_HEIGHT_PX,c);
  }

  bool binary_op(const unary_function_ptr & u){
    const unary_function_ptr binary_op_tab_ptr []={*at_plus,*at_prod,*at_pow,*at_and,*at_ou,*at_xor,*at_different,*at_same,*at_equal,*at_unit,*at_compose,*at_composepow,*at_deuxpoints,*at_tilocal,*at_pointprod,*at_pointdivision,*at_pointpow,*at_division,*at_normalmod,*at_minus,*at_intersect,*at_union,*at_interval,*at_inferieur_egal,*at_inferieur_strict,*at_superieur_egal,*at_superieur_strict,*at_equal2,0};
    return equalposcomp(binary_op_tab_ptr,u);
  }
  
  eqwdata Equation_total_size(const gen & g){
    if (g.type==_EQW)
      return *g._EQWptr;
    if (g.type!=_VECT || g._VECTptr->empty())
      return eqwdata(0,0,0,0,attributs(0,0,0),undef);
    return Equation_total_size(g._VECTptr->back());
  }

  // find smallest value of y and height
  void Equation_y_dy(const gen & g,int & y,int & dy){
    y=0; dy=0;
    if (g.type==_EQW){
      y=g._EQWptr->y;
      dy=g._EQWptr->dy;
    }
    if (g.type==_VECT){
      iterateur it=g._VECTptr->begin(),itend=g._VECTptr->end();
      for (;it!=itend;++it){
	int Y,dY;
	Equation_y_dy(*it,Y,dY);
	// Y, Y+dY and y,y+dy
	int ymax=giacmax(y+dy,Y+dY);
	if (Y<y)
	  y=Y;
	dy=ymax-y;
      }
    }
  }

  void Equation_translate(gen & g,int deltax,int deltay){
    if (g.type==_EQW){
      g._EQWptr->x += deltax;
      g._EQWptr->y += deltay;
      g._EQWptr->baseline += deltay;
      return ;
    }
    if (g.type!=_VECT)
      setsizeerr();
    vecteur & v=*g._VECTptr;
    iterateur it=v.begin(),itend=v.end();
    for (;it!=itend;++it)
      Equation_translate(*it,deltax,deltay);
  }

  gen Equation_change_attributs(const gen & g,const attributs & newa){
    if (g.type==_EQW){
      gen res(*g._EQWptr);
      res._EQWptr->eqw_attributs = newa;
      return res;
    }
    if (g.type!=_VECT)
      return gensizeerr();
    vecteur v=*g._VECTptr;
    iterateur it=v.begin(),itend=v.end();
    for (;it!=itend;++it)
      *it=Equation_change_attributs(*it,newa);
    return gen(v,g.subtype);
  }

  vecteur Equation_subsizes(const gen & arg,const attributs & a,int windowhsize,GIAC_CONTEXT){
    vecteur v;
    if ( (arg.type==_VECT) && ( (arg.subtype==_SEQ__VECT) 
				// || (!ckmatrix(arg)) 
				) ){
      const_iterateur it=arg._VECTptr->begin(),itend=arg._VECTptr->end();
      for (;it!=itend;++it)
	v.push_back(Equation_compute_size(*it,a,windowhsize,contextptr));
    }
    else {
      v.push_back(Equation_compute_size(arg,a,windowhsize,contextptr));
    }
    return v;
  }

  // vertical merge with same baseline
  // for vertical merge of hp,yp at top (like ^) add fontsize to yp
  // at bottom (like lower bound of int) substract fontsize from yp
  void Equation_vertical_adjust(int hp,int yp,int & h,int & y){
    int yf=min(y,yp);
    h=max(y+h,yp+hp)-yf;
    y=yf;
  }

  gen Equation_compute_symb_size(const gen & g,const attributs & a,int windowhsize,GIAC_CONTEXT){
    if (g.type!=_SYMB)
      return Equation_compute_size(g,a,windowhsize,contextptr);
    unary_function_ptr & u=g._SYMBptr->sommet;
    gen arg=g._SYMBptr->feuille,rootof_value;
    if (u==at_makevector){
      vecteur v(1,arg);
      if (arg.type==_VECT)
	v=*arg._VECTptr;
      iterateur it=v.begin(),itend=v.end();
      for (;it!=itend;++it){
	if ( (it->type==_SYMB) && (it->_SYMBptr->sommet==at_makevector) )
	  *it=_makevector(it->_SYMBptr->feuille,contextptr);
      }
      return Equation_compute_size(v,a,windowhsize,contextptr);
    }
    if (u==at_makesuite){
      if (arg.type==_VECT)
	return Equation_compute_size(gen(*arg._VECTptr,_SEQ__VECT),a,windowhsize,contextptr);
      else
	return Equation_compute_size(arg,a,windowhsize,contextptr);
    }
    if (u==at_sqrt)
      return Equation_compute_size(symb_pow(arg,plus_one_half),a,windowhsize,contextptr);
    if (u==at_division){
      if (arg.type!=_VECT || arg._VECTptr->size()!=2)
	return Equation_compute_size(arg,a,windowhsize,contextptr);
      gen tmp=Tfraction<gen>(arg._VECTptr->front(),arg._VECTptr->back());
      return Equation_compute_size(tmp,a,windowhsize,contextptr);
    }
    if (u==at_prod){
      gen n,d;
      if (rewrite_prod_inv(arg,n,d)){
	if (n.is_symb_of_sommet(at_neg))
	  return Equation_compute_size(symbolic(at_neg,Tfraction<gen>(-n,d)),a,windowhsize,contextptr);
	return Equation_compute_size(Tfraction<gen>(n,d),a,windowhsize,contextptr);
      }
    }
    if (u==at_inv){
      if ( (is_integer(arg) && is_positive(-arg,contextptr))
	   || (arg.is_symb_of_sommet(at_neg)))
	return Equation_compute_size(symbolic(at_neg,Tfraction<gen>(plus_one,-arg)),a,windowhsize,contextptr);
      return Equation_compute_size(Tfraction<gen>(plus_one,arg),a,windowhsize,contextptr);
    }
    if (u==at_expr && arg.type==_VECT && arg.subtype==_SEQ__VECT && arg._VECTptr->size()==2 && arg._VECTptr->back().type==_INT_){
      gen varg1=Equation_compute_size(arg._VECTptr->front(),a,windowhsize,contextptr);
      eqwdata vv(Equation_total_size(varg1));
      gen varg2=eqwdata(0,0,0,0,a,arg._VECTptr->back());
      vecteur v12(makevecteur(varg1,varg2));
      v12.push_back(eqwdata(vv.dx,vv.dy,0,vv.y,a,at_expr,0));
      return gen(v12,_SEQ__VECT);
    }
    int llp=int(text_width(a.fontsize,("(")))-1;
    int lrp=llp;
    int lc=int(text_width(a.fontsize,(",")));
    string us=u.ptr()->s;
    int ls=int(text_width(a.fontsize,(us.c_str())));
    // if (isalpha(u.ptr()->s[0])) ls += 1;
    if (u==at_abs)
      ls = 2;
    // special cases first int, sigma, /, ^
    // and if printed as printsommetasoperator
    // otherwise print with usual functional notation
    int x=0;
    int h=a.fontsize;
    int y=0;
#if 1
    if ((u==at_integrate) || (u==at_sum) ){ // Int
      int s=1;
      if (arg.type==_VECT)
	s=arg._VECTptr->size();
      else
	arg=vecteur(1,arg);
      // s==1 -> general case
      if ( (s==1) || (s==2) ){ // int f(x) dx and sum f(n) n
	vecteur v(Equation_subsizes(gen(*arg._VECTptr,_SEQ__VECT),a,windowhsize,contextptr));
	eqwdata vv(Equation_total_size(v[0]));
	if (s==1){
	  x=a.fontsize;
	  Equation_translate(v[0],x,0);
	  x += int(text_width(a.fontsize,(" dx")));
	}
	if (s==2){
	  if (u==at_integrate){
	    x=a.fontsize;
	    Equation_translate(v[0],x,0);
	    x += vv.dx+int(text_width(a.fontsize,(" d")));
	    Equation_vertical_adjust(vv.dy,vv.y,h,y);
	    vv=Equation_total_size(v[1]);
	    Equation_translate(v[1],x,0);
	    Equation_vertical_adjust(vv.dy,vv.y,h,y);
	  }
	  else {
	    Equation_vertical_adjust(vv.dy,vv.y,h,y);
	    eqwdata v1=Equation_total_size(v[1]);
	    x=max(a.fontsize,v1.dx)+2*a.fontsize/3; // var name size
	    Equation_translate(v[1],0,-v1.dy-v1.y);
	    Equation_vertical_adjust(v1.dy,-v1.dy,h,y);
	    Equation_translate(v[0],x,0);
	    x += vv.dx; // add function size
	  }
	}
	if (u==at_integrate){
	  x += vv.dx;
	  if (h==a.fontsize)
	    h+=2*a.fontsize/3;
	  if (y==0){
	    y=-2*a.fontsize/3;
	    h+=2*a.fontsize/3;
	  }
	}
	v.push_back(eqwdata(x,h,0,y,a,u,0));
	return gen(v,_SEQ__VECT);
      }
      if (s>=3){ // int _a^b f(x) dx
	vecteur & intarg=*arg._VECTptr;
	gen tmp_l,tmp_u,tmp_f,tmp_x;
	attributs aa(a);
	if (a.fontsize>=10)
	  aa.fontsize -= 2;
	tmp_f=Equation_compute_size(intarg[0],a,windowhsize,contextptr);
	tmp_x=Equation_compute_size(intarg[1],a,windowhsize,contextptr);
	tmp_l=Equation_compute_size(intarg[2],aa,windowhsize,contextptr);
	if (s==4)
	  tmp_u=Equation_compute_size(intarg[3],aa,windowhsize,contextptr);
	x=a.fontsize+(u==at_integrate?-2:+4);
	eqwdata vv(Equation_total_size(tmp_l));
	Equation_translate(tmp_l,x,-vv.y-vv.dy);
	vv=Equation_total_size(tmp_l);
	Equation_vertical_adjust(vv.dy,vv.y,h,y);
	int lx = vv.dx;
	if (s==4){
	  vv=Equation_total_size(tmp_u);
	  Equation_translate(tmp_u,x,a.fontsize-3-vv.y);
	  vv=Equation_total_size(tmp_u);
	  Equation_vertical_adjust(vv.dy,vv.y,h,y);
	}
	x += max(lx,vv.dx);
	Equation_translate(tmp_f,x,0);
	vv=Equation_total_size(tmp_f);
	Equation_vertical_adjust(vv.dy,vv.y,h,y);
	if (u==at_integrate){
	  x += vv.dx+int(text_width(a.fontsize,(" d")));
	  Equation_translate(tmp_x,x,0);
	  vv=Equation_total_size(tmp_x);
	  Equation_vertical_adjust(vv.dy,vv.y,h,y);
	  x += vv.dx;
	}
	else {
	  x += vv.dx;
	  Equation_vertical_adjust(vv.dy,vv.y,h,y);
	  vv=Equation_total_size(tmp_x);
	  x=max(x,vv.dx)+a.fontsize/3;
	  Equation_translate(tmp_x,0,-vv.dy-vv.y);
	  //Equation_translate(tmp_l,0,-1);	  
	  if (s==4) Equation_translate(tmp_u,-2,0);	  
	  Equation_vertical_adjust(vv.dy,-vv.dy,h,y);
	}
	vecteur res(makevecteur(tmp_f,tmp_x,tmp_l));
	if (s==4)
	  res.push_back(tmp_u);
	res.push_back(eqwdata(x,h,0,y,a,u,0));
	return gen(res,_SEQ__VECT);
      }
    }
    if (u==at_limit && arg.type==_VECT){ // limit
      vecteur limarg=*arg._VECTptr;
      int s=limarg.size();
      if (s==2 && limarg[1].is_symb_of_sommet(at_equal)){
	limarg.push_back(limarg[1]._SYMBptr->feuille[1]);
	limarg[1]=limarg[1]._SYMBptr->feuille[0];
	++s;
      }
      if (s>=3){
	gen tmp_l,tmp_f,tmp_x,tmp_dir;
	attributs aa(a);
	if (a.fontsize>=10)
	  aa.fontsize -= 2;
	tmp_f=Equation_compute_size(limarg[0],a,windowhsize,contextptr);
	tmp_x=Equation_compute_size(limarg[1],aa,windowhsize,contextptr);
	tmp_l=Equation_compute_size(limarg[2],aa,windowhsize,contextptr);
	if (s==4)
	  tmp_dir=Equation_compute_size(limarg[3],aa,windowhsize,contextptr);
	eqwdata vf(Equation_total_size(tmp_f));
	eqwdata vx(Equation_total_size(tmp_x));
	eqwdata vl(Equation_total_size(tmp_l));
	eqwdata vdir(Equation_total_size(tmp_dir));
	int sous=max(vx.dy,vl.dy);
	if (s==4)
	  Equation_translate(tmp_f,vx.dx+vl.dx+vdir.dx+a.fontsize+4,0);
	else
	  Equation_translate(tmp_f,vx.dx+vl.dx+a.fontsize+2,0);
	Equation_translate(tmp_x,0,-sous-vl.y);
	Equation_translate(tmp_l,vx.dx+a.fontsize+2,-sous-vl.y);
	if (s==4)
	  Equation_translate(tmp_dir,vx.dx+vl.dx+a.fontsize+4,-sous-vl.y);
	h=vf.dy;
	y=vf.y;
	vl=Equation_total_size(tmp_l);
	Equation_vertical_adjust(vl.dy,vl.y,h,y);
	vecteur res(makevecteur(tmp_f,tmp_x,tmp_l));
	if (s==4){
	  res.push_back(tmp_dir);
	  res.push_back(eqwdata(vf.dx+vx.dx+a.fontsize+4+vl.dx+vdir.dx,h,0,y,a,u,0));
	}
	else
	  res.push_back(eqwdata(vf.dx+vx.dx+a.fontsize+2+vl.dx,h,0,y,a,u,0));
	return gen(res,_SEQ__VECT);
      }
    }
#endif
    if ( (u==at_of || u==at_at) && arg.type==_VECT && arg._VECTptr->size()==2 ){
      // user function, function in 1st arg, arguments in 2nd arg
      gen varg1=Equation_compute_size(arg._VECTptr->front(),a,windowhsize,contextptr);
      eqwdata vv=Equation_total_size(varg1);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      gen arg2=arg._VECTptr->back();
      if (u==at_at && xcas_mode(contextptr)!=0){
	if (arg2.type==_VECT)
	  arg2=gen(addvecteur(*arg2._VECTptr,vecteur(arg2._VECTptr->size(),plus_one)),_SEQ__VECT);
	else
	  arg2=arg2+plus_one; 
      }
      gen varg2=Equation_compute_size(arg2,a,windowhsize,contextptr);
      Equation_translate(varg2,vv.dx+llp,0);
      vv=Equation_total_size(varg2);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      vecteur res(makevecteur(varg1,varg2));
      res.push_back(eqwdata(vv.dx+vv.x+lrp,h,0,y,a,u,0));
      return gen(res,_SEQ__VECT);
    }
    if (u==at_pow){ 
      // first arg not translated
      gen varg=Equation_compute_size(arg._VECTptr->front(),a,windowhsize,contextptr);
      eqwdata vv=Equation_total_size(varg);
      // 1/2 ->sqrt, otherwise as exponent
      if (arg._VECTptr->back()==plus_one_half){
	Equation_translate(varg,a.fontsize,0);
	vecteur res(1,varg);
	res.push_back(eqwdata(vv.dx+a.fontsize,vv.dy+4,vv.x,vv.y,a,at_sqrt,0));
	return gen(res,_SEQ__VECT);
      }
      bool needpar=vv.g.type==_FUNC || vv.g.is_symb_of_sommet(at_pow) || need_parenthesis(vv.g);
      if (needpar)
	x=llp;
      Equation_translate(varg,x,0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      vecteur res(1,varg);
      // 2nd arg translated 
      if (needpar)
	x+=vv.dx+lrp;
      else
	x+=vv.dx+1;
      int arg1dy=vv.dy,arg1y=vv.y;
      if (a.fontsize>=16){
	attributs aa(a);
	aa.fontsize -= 2;
	varg=Equation_compute_size(arg._VECTptr->back(),aa,windowhsize,contextptr);
      }
      else
	varg=Equation_compute_size(arg._VECTptr->back(),a,windowhsize,contextptr);
      vv=Equation_total_size(varg);
      Equation_translate(varg,x,arg1y+(3*arg1dy)/4-vv.y);
      res.push_back(varg);
      vv=Equation_total_size(varg);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      x += vv.dx;
      res.push_back(eqwdata(x,h,0,y,a,u,0));
      return gen(res,_SEQ__VECT);
    }
    if (u==at_factorial){
      vecteur v;
      gen varg=Equation_compute_size(arg,a,windowhsize,contextptr);
      eqwdata vv=Equation_total_size(varg);
      bool paren=need_parenthesis(vv.g) || vv.g==at_prod || vv.g==at_division || vv.g==at_pow;
      if (paren)
	x+=llp;
      Equation_translate(varg,x,0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      v.push_back(varg);
      x += vv.dx;
      if (paren)
	x+=lrp;
      varg=eqwdata(x+4,h,0,y,a,u,0);
      v.push_back(varg);
      return gen(v,_SEQ__VECT);
    }
    if (u==at_sto){ // A:=B, *it -> B
      gen varg=Equation_compute_size(arg._VECTptr->back(),a,windowhsize,contextptr);
      eqwdata vv=Equation_total_size(varg);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      Equation_translate(varg,x,0);
      vecteur v(2);
      v[1]=varg;
      x+=vv.dx;
      x+=ls+3;
      // first arg not translated
      varg=Equation_compute_size(arg._VECTptr->front(),a,windowhsize,contextptr);
      vv=Equation_total_size(varg);
      if (need_parenthesis(vv.g))
	x+=llp;
      Equation_translate(varg,x,0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      v[0]=varg;
      x += vv.dx;
      if (need_parenthesis(vv.g))
	x+=lrp;
      v.push_back(eqwdata(x,h,0,y,a,u,0));
      return gen(v,_SEQ__VECT);
    }
    if (u==at_program && arg._VECTptr->back().type!=_VECT && !arg._VECTptr->back().is_symb_of_sommet(at_local) ){
      gen varg=Equation_compute_size(arg._VECTptr->front(),a,windowhsize,contextptr);
      eqwdata vv=Equation_total_size(varg);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      Equation_translate(varg,x,0);
      vecteur v(2);
      v[0]=varg;
      x+=vv.dx;
      x+=int(text_width(a.fontsize,("->")))+3;
      varg=Equation_compute_size(arg._VECTptr->back(),a,windowhsize,contextptr);
      vv=Equation_total_size(varg);
      Equation_translate(varg,x,0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      v[1]=varg;
      x += vv.dx;
      v.push_back(eqwdata(x,h,0,y,a,u,0));
      return gen(v,_SEQ__VECT);      
    }
    bool binaryop= (u.ptr()->printsommet==&printsommetasoperator) || binary_op(u);
    if ( u!=at_sto && u.ptr()->printsommet!=NULL && !binaryop ){
      gen tmp=string2gen(g.print(contextptr),false);
      return Equation_compute_size(symbolic(at_expr,makesequence(tmp,xcas_mode(contextptr))),a,windowhsize,contextptr);
    }
    vecteur v;
    if (!binaryop || arg.type!=_VECT)
      v=Equation_subsizes(arg,a,windowhsize,contextptr);
    else
      v=Equation_subsizes(gen(*arg._VECTptr,_SEQ__VECT),a,windowhsize,contextptr);
    iterateur it=v.begin(),itend=v.end();
    if ( it==itend || (itend-it==1) ){ 
      gen gtmp;
      if (it==itend)
	gtmp=Equation_compute_size(gen(vecteur(0),_SEQ__VECT),a,windowhsize,contextptr);
      else
	gtmp=*it;
      // unary op, shift arg position horizontally
      eqwdata vv=Equation_total_size(gtmp);
      bool paren = u!=at_neg || (vv.g!=at_prod && need_parenthesis(vv.g)) ;
      x=ls+(paren?llp:0);
      gen tmp=gtmp; Equation_translate(tmp,x,0);
      x=x+vv.dx+(paren?lrp:0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      return gen(makevecteur(tmp,eqwdata(x,h,0,y,a,u,0)),_EQW__VECT);
    }
    if (binaryop){ // op (default with par)
      int currenth=h,largeur=0;
      iterateur itprec=v.begin();
      h=0;
      if (u==at_plus){ // op without parenthesis
	if (it->type==_VECT && !it->_VECTptr->empty() && it->_VECTptr->back().type==_EQW && it->_VECTptr->back()._EQWptr->g==at_equal)
	  ;
	else {
	  llp=0;
	  lrp=0;
	}
      }
      for (;;){
	eqwdata vv=Equation_total_size(*it);
	if (need_parenthesis(vv.g))
	  x+=llp;
	if (u==at_plus && it!=v.begin() &&
	    ( 
	     (it->type==_VECT && it->_VECTptr->back().type==_EQW && it->_VECTptr->back()._EQWptr->g==at_neg) 
	     || 
	     ( it->type==_EQW && (is_integer(it->_EQWptr->g) || it->_EQWptr->g.type==_DOUBLE_) && is_strictly_positive(-it->_EQWptr->g,contextptr) ) 
	      ) 
	    )
	  x -= ls;
#if 0 //
	if (x>windowhsize-vv.dx && x>windowhsize/2 && (itend-it)*vv.dx>windowhsize/2){
	  largeur=max(x,largeur);
	  x=0;
	  if (need_parenthesis(vv.g))
	    x+=llp;
	  h+=currenth;
	  Equation_translate(*it,x,0);
	  for (iterateur kt=v.begin();kt!=itprec;++kt)
	    Equation_translate(*kt,0,currenth);
	  if (y){
	    for (iterateur kt=itprec;kt!=it;++kt)
	      Equation_translate(*kt,0,-y);
	  }
	  itprec=it;
	  currenth=vv.dy;
	  y=vv.y;
	}
	else
#endif
	  {
	    Equation_translate(*it,x,0);
	    vv=Equation_total_size(*it);
	    Equation_vertical_adjust(vv.dy,vv.y,currenth,y);
	  }
	x+=vv.dx;
	if (need_parenthesis(vv.g))
	  x+=lrp;
	++it;
	if (it==itend){
	  for (iterateur kt=v.begin();kt!=itprec;++kt)
	    Equation_translate(*kt,0,currenth+y);
	  h+=currenth;
	  v.push_back(eqwdata(max(x,largeur),h,0,y,a,u,0));
	  //cout << v << endl;
	  return gen(v,_SEQ__VECT);
	}
	x += ls+3;
      } 
    }
    // normal printing
    x=ls+llp;
    for (;;){
      eqwdata vv=Equation_total_size(*it);
      Equation_translate(*it,x,0);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      x+=vv.dx;
      ++it;
      if (it==itend){
	x+=lrp;
	v.push_back(eqwdata(x,h,0,y,a,u,0));
	return gen(v,_SEQ__VECT);
      }
      x+=lc;
    }
  }

  // windowhsize is used for g of type HIST__VECT (history) right justify answers
  // Returns either a eqwdata type object (terminal) or a vector 
  // (of subtype _EQW__VECT or _HIST__VECT)
  gen Equation_compute_size(const gen & g,const attributs & a,int windowhsize,GIAC_CONTEXT){
    /*****************
     *   FRACTIONS   *
     *****************/
    if (g.type==_FRAC){
      if (is_integer(g._FRACptr->num) && is_positive(-g._FRACptr->num,contextptr))
	return Equation_compute_size(symbolic(at_neg,fraction(-g._FRACptr->num,g._FRACptr->den)),a,windowhsize,contextptr);
      gen v1=Equation_compute_size(g._FRACptr->num,a,windowhsize,contextptr);
      eqwdata vv1=Equation_total_size(v1);
      gen v2=Equation_compute_size(g._FRACptr->den,a,windowhsize,contextptr);
      eqwdata vv2=Equation_total_size(v2);
      // Center the fraction
      int w1=vv1.dx,w2=vv2.dx;
      int w=max(w1,w2)+6;
      vecteur v(3);
      v[0]=v1; Equation_translate(v[0],(w-w1)/2,11-vv1.y);
      v[1]=v2; Equation_translate(v[1],(w-w2)/2,5-vv2.dy-vv2.y);
      v[2]=eqwdata(w,a.fontsize/2+vv1.dy+vv2.dy+1,0,(a.fontsize<=14?4:3)-vv2.dy,a,at_division,0);
      return gen(v,_SEQ__VECT);
    }
    /***************
     *   VECTORS   *
     ***************/
    if ( (g.type==_VECT) && !g._VECTptr->empty() ){
      vecteur v;
      const_iterateur it=g._VECTptr->begin(),itend=g._VECTptr->end();
      int x=0,y=0,h=a.fontsize; 
      /***************
       *   MATRICE   *
       ***************/
      bool gmat=ckmatrix(g);
      vector<int> V; int p=0;
      if (!gmat && is_mod_vecteur(*g._VECTptr,V,p) && p!=0){
	gen gm=makemodquoted(unmod(g),p);
	return Equation_compute_size(gm,a,windowhsize,contextptr);
      }
      vector< vector<int> > M; 
      if (gmat && is_mod_matrice(*g._VECTptr,M,p) && p!=0){
	gen gm=makemodquoted(unmod(g),p);
	return Equation_compute_size(gm,a,windowhsize,contextptr);
      }
      if (gmat && g.subtype!=_SEQ__VECT && g.subtype!=_SET__VECT && g.subtype!=_POLY1__VECT && g._VECTptr->front().subtype!=_SEQ__VECT){
	gen mkvect(at_makevector);
	mkvect.subtype=_SEQ__VECT;
	gen mkmat(at_makevector);
	mkmat.subtype=_MATRIX__VECT;
	int nrows,ncols;
	mdims(*g._VECTptr,nrows,ncols);
	if (ncols){
	  vecteur all_sizes;
	  all_sizes.reserve(nrows);
	  vector<int> row_heights(nrows),row_bases(nrows),col_widths(ncols);
	  // vertical gluing
	  for (int i=0;it!=itend;++it,++i){
	    gen tmpg=*it;
	    tmpg.subtype=_SEQ__VECT;
	    vecteur tmp(Equation_subsizes(tmpg,a,max(windowhsize/ncols-a.fontsize,230),contextptr));
	    int h=a.fontsize,y=0;
	    const_iterateur jt=tmp.begin(),jtend=tmp.end();
	    for (int j=0;jt!=jtend;++jt,++j){
	      eqwdata w(Equation_total_size(*jt));
	      Equation_vertical_adjust(w.dy,w.y,h,y);
	      col_widths[j]=max(col_widths[j],w.dx);
	    }
	    if (i)
	      row_heights[i]=row_heights[i-1]+h+a.fontsize/2;
	    else
	      row_heights[i]=h;
	    row_bases[i]=y;
	    all_sizes.push_back(tmp);
	  }
	  // accumulate col widths
	  col_widths.front() +=(3*a.fontsize)/2;
	  vector<int>::iterator iit=col_widths.begin()+1,iitend=col_widths.end();
	  for (;iit!=iitend;++iit)
	    *iit += *(iit-1)+a.fontsize;
	  // translate each cell
	  it=all_sizes.begin();
	  itend=all_sizes.end();
	  int h,y,prev_h=0;
	  for (int i=0;it!=itend;++it,++i){
	    h=row_heights[i];
	    y=row_bases[i];
	    iterateur jt=it->_VECTptr->begin(),jtend=it->_VECTptr->end();
	    for (int j=0;jt!=jtend;++jt,++j){
	      eqwdata w(Equation_total_size(*jt));
	      if (j)
		Equation_translate(*jt,col_widths[j-1]-w.x,-h-y);
	      else
		Equation_translate(*jt,-w.x+a.fontsize/2,-h-y);
	    }
	    it->_VECTptr->push_back(eqwdata(col_widths.back(),h-prev_h,0,-h,a,mkvect,0));
	    prev_h=h;
	  }
	  all_sizes.push_back(eqwdata(col_widths.back(),row_heights.back(),0,-row_heights.back(),a,mkmat,-row_heights.back()/2));
	  gen all_sizesg=all_sizes; Equation_translate(all_sizesg,0,row_heights.back()/2); return all_sizesg;
	}
      } // end matrices
      /*************************
       *   SEQUENCES/VECTORS   *
       *************************/
      // horizontal gluing
      if (g.subtype!=_PRINT__VECT) x += a.fontsize/2;
      int ncols=itend-it;
      //ncols=min(ncols,5);
      for (;it!=itend;++it){
	gen cur_size=Equation_compute_size(*it,a,
					   max(windowhsize/ncols-a.fontsize,
#ifdef IPAQ
					       200
#else
					       480
#endif
					       ),contextptr);
	eqwdata tmp=Equation_total_size(cur_size);
	Equation_translate(cur_size,x-tmp.x,0); v.push_back(cur_size);
	x=x+tmp.dx+((g.subtype==_PRINT__VECT)?2:a.fontsize);
	Equation_vertical_adjust(tmp.dy,tmp.y,h,y);
      }
      gen mkvect(at_makevector);
      if (g.subtype==_SEQ__VECT)
	mkvect=at_makesuite;
      else
	mkvect.subtype=g.subtype;
      v.push_back(eqwdata(x,h,0,y,a,mkvect,0));
      return gen(v,_EQW__VECT);
    } // end sequences
    if (g.type==_MOD){ 
      int x=0;
      int h=a.fontsize;
      int y=0;
      bool py=python_compat(contextptr);
      int modsize=int(text_width(a.fontsize,(py?" mod":"%")))+4;
      bool paren=is_positive(-*g._MODptr,contextptr);
      int llp=int(text_width(a.fontsize,("(")));
      int lrp=int(text_width(a.fontsize,(")")));
      gen varg1=Equation_compute_size(*g._MODptr,a,windowhsize,contextptr);
      if (paren) Equation_translate(varg1,llp,0);
      eqwdata vv=Equation_total_size(varg1);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      gen arg2=*(g._MODptr+1);
      gen varg2=Equation_compute_size(arg2,a,windowhsize,contextptr);
      if (paren)
	Equation_translate(varg2,vv.dx+modsize+lrp,0);
      else
	Equation_translate(varg2,vv.dx+modsize,0);
      vv=Equation_total_size(varg2);
      Equation_vertical_adjust(vv.dy,vv.y,h,y);
      vecteur res(makevecteur(varg1,varg2));
      res.push_back(eqwdata(vv.dx+vv.x,h,0,y,a,at_normalmod,0));
      return gen(res,_SEQ__VECT);
    }
    if (g.type!=_SYMB){
      string s=g.type==_STRNG?*g._STRNGptr:g.print(contextptr);
      //if (g==cst_pi) s=char(129);
      if (s.size()>2000)
	s=s.substr(0,2000)+"...";
      int i=int(text_width(a.fontsize,(s.c_str())));
      gen tmp=eqwdata(i,a.fontsize,0,0,a,g);
      return tmp;
    }
    /**********************
     *  SYMBOLIC HANDLING *
     **********************/
    return Equation_compute_symb_size(g,a,windowhsize,contextptr);
    // return Equation_compute_symb_size(aplatir_fois_plus(g),a,windowhsize,contextptr);
    // aplatir_fois_plus is a problem for Equation_replace_selection
    // because it will modify the structure of the data
  }

  void Equation_draw(const eqwdata & e,int x,int y,int rightx,int lowery,Equation * eq,GIAC_CONTEXT){
    if ( (e.dx+e.x<x) || (e.x>rightx) || (e.y>y) || e.y+e.dy<lowery)
      ; // return; // nothing to draw, out of window
    gen gg=e.g;
    int fontsize=e.eqw_attributs.fontsize;
    int text_color=COLOR_BLACK;
    int background=COLOR_WHITE;
    string s=gg.type==_STRNG?*gg._STRNGptr:gg.print(contextptr);
    if (gg.type==_IDNT && !s.empty() && s[0]=='_')
      s=s.substr(1,s.size()-1);
    // if (gg==cst_pi){      s="p";      s[0]=(unsigned char)129;    }
    if (s.size()>2000)
      s=s.substr(0,2000)+"...";
    // cerr << s.size() << endl;
    text_print(fontsize,s.c_str(),eq->x()+e.x-x,eq->y()+y-e.y,text_color,background,e.selected?4:0);
    return;
  }

  inline void check_fl_rectf(int x,int y,int w,int h,int imin,int jmin,int di,int dj,int delta_i,int delta_j,int c){
    drawRectangle(x+delta_i,y+delta_j,w,h,c);
    //fl_rectf(x+delta_i,y+delta_j,w,h,c);
  }

  void Equation_draw(const gen & g,int x,int y,int rightx,int lowery,Equation * equat,GIAC_CONTEXT){
    int eqx=equat->x(),eqy=equat->y();
    if (g.type==_EQW){ // terminal
      eqwdata & e=*g._EQWptr;
      Equation_draw(e,x,y,rightx,lowery,equat,contextptr);
    }
    if (g.type!=_VECT)
      return;
    vecteur & v=*g._VECTptr;
    if (v.empty())
      return;
    gen tmp=v.back();
    if (tmp.type!=_EQW){
      cout << "EQW error:" << v << endl;
      return;
    }
    eqwdata & w=*tmp._EQWptr;
    if ( (w.dx+w.x-x<0) || (w.x>rightx) || (w.y>y) || (w.y+w.dy<lowery) )
      ; // return; // nothing to draw, out of window
    /*******************
     * draw the vector *
     *******************/
    // v is the vector, w the master operator eqwdata
    gen oper=w.g; 
    bool selected=w.selected ;
    int fontsize=w.eqw_attributs.fontsize;
    int background=w.eqw_attributs.background;
    int text_color=w.eqw_attributs.text_color;
    int mode=selected?4:0;
    int draw_line_color=selected?background:text_color;
    int x0=w.x;
    int y0=w.y; // lower coordinate of the master vector
    int y1=y0+w.dy; // upper coordinate of the master vector
    if (selected)
      drawRectangle(eqx+w.x-x,eqy+y-w.y-w.dy+1,w.dx,w.dy+1,text_color);
    // draw arguments of v
    const_iterateur it=v.begin(),itend=v.end()-1;
    if (oper==at_expr && v.size()==3){
      Equation_draw(*it,x,y,rightx,lowery,equat,contextptr);
      return;
    }
    for (;it!=itend;++it)
      Equation_draw(*it,x,y,rightx,lowery,equat,contextptr);
    if (oper==at_multistring)
      return;
    string s;
    if (oper.type==_FUNC){
      // catch here special cases user function, vect/matr, ^, int, sqrt, etc.
      unary_function_ptr & u=*oper._FUNCptr;
      if (u==at_at){ // draw brackets around 2nd arg
	gen arg2=v[1]; // 2nd arg of at_of, i.e. what's inside the parenth.
	eqwdata varg2=Equation_total_size(arg2);
	x0=varg2.x;
	y0=varg2.y;
	y1=y0+varg2.dy;
	fontsize=varg2.eqw_attributs.fontsize;
	if (x0<rightx)
	  text_print(fontsize,"[",eqx+x0-x-int(text_width(fontsize,("["))),eqy+y-varg2.baseline,text_color,background,mode);
	x0 += varg2.dx ;
	if (x0<rightx)
	  text_print(fontsize,"]",eqx+x0-x,eqy+y-varg2.baseline,text_color,background,mode);
	return;
      }
      if (u==at_of){ // do we need to draw some parenthesis?
	gen arg2=v[1]; // 2nd arg of at_of, i.e. what's inside the parenth.
	if (arg2.type!=_VECT || arg2._VECTptr->back().type !=_EQW || arg2._VECTptr->back()._EQWptr->g!=at_makesuite){ // Yes (if not _EQW it's a sequence with parent)
	  eqwdata varg2=Equation_total_size(arg2);
	  x0=varg2.x;
	  y0=varg2.y;
	  y1=y0+varg2.dy;
	  fontsize=varg2.eqw_attributs.fontsize;
	  int pfontsize=max(fontsize,(fontsize+(varg2.baseline-varg2.y))/2);
	  if (x0<rightx)
	    text_print(pfontsize,"(",eqx+x0-x-int(text_width(fontsize,("("))),eqy+y-varg2.baseline,text_color,background,mode);
	  x0 += varg2.dx ;
	  if (x0<rightx)
	    text_print(pfontsize,")",eqx+x0-x,eqy+y-varg2.baseline,text_color,background,mode);
	}
	return;
      }
      if (u==at_makesuite){
	bool paren=v.size()!=2; // Sequences with 1 arg don't show parenthesis
	int pfontsize=max(fontsize,(fontsize+(w.baseline-w.y))/2);
	if (paren && x0<rightx)
	  text_print(pfontsize,"(",eqx+x0-x-int(text_width(fontsize,("(")))/2,eqy+y-w.baseline,text_color,background,mode);
	x0 += w.dx;
	if (paren && x0<rightx)
	  text_print(pfontsize,")",eqx+x0-x-int(text_width(fontsize,("(")))/2,eqy+y-w.baseline,text_color,background,mode);
	// print commas between args
	it=v.begin(),itend=v.end()-2;
	for (;it!=itend;++it){
	  eqwdata varg2=Equation_total_size(*it);
	  fontsize=varg2.eqw_attributs.fontsize;
	  if (varg2.x+varg2.dx<rightx)
	    text_print(fontsize,",",eqx+varg2.x+varg2.dx-x+1,eqy+y-varg2.baseline,text_color,background,mode);
	}
	return;
      }
      if (u==at_makevector){ // draw [] delimiters for vector/matrices
	if (oper.subtype!=_SEQ__VECT && oper.subtype!=_PRINT__VECT){
	  int decal=1;
	  switch (oper.subtype){
	  case _MATRIX__VECT: decal=2; break;
	  case _SET__VECT: decal=4; break;
	  case _POLY1__VECT: decal=6; break;
	  }
	  if (eqx+x0-x+1>=0){
	    draw_line(eqx+x0-x+1,eqy+y-y0+1,eqx+x0-x+1,eqy+y-y1+1,draw_line_color);
	    draw_line(eqx+x0-x+decal,eqy+y-y0+1,eqx+x0-x+decal,eqy+y-y1+1,draw_line_color);
	    draw_line(eqx+x0-x+1,eqy+y-y0+1,eqx+x0-x+fontsize/4,eqy+y-y0+1,draw_line_color);
	    draw_line(eqx+x0-x+1,eqy+y-y1+1,eqx+x0-x+fontsize/4,eqy+y-y1+1,draw_line_color);
	  }
	  x0 += w.dx ;
	  if (eqx+x0-x-1<LCD_WIDTH_PX){
	    draw_line(eqx+x0-x-1,eqy+y-y0+1,eqx+x0-x-1,eqy+y-y1+1,draw_line_color);
	    draw_line(eqx+x0-x-decal,eqy+y-y0+1,eqx+x0-x-decal,eqy+y-y1+1,draw_line_color);
	    draw_line(eqx+x0-x-1,eqy+y-y0+1,eqx+x0-x-fontsize/4,eqy+y-y0+1,draw_line_color);
	    draw_line(eqx+x0-x-1,eqy+y-y1+1,eqx+x0-x-fontsize/4,eqy+y-y1+1,draw_line_color);
	  }
	} // end if oper.subtype!=SEQ__VECT
	if (oper.subtype!=_MATRIX__VECT && oper.subtype!=_PRINT__VECT){
	  // print commas between args
	  it=v.begin(),itend=v.end()-2;
	  for (;it!=itend;++it){
	    eqwdata varg2=Equation_total_size(*it);
	    fontsize=varg2.eqw_attributs.fontsize;
	    if (varg2.x+varg2.dx<rightx)
	      text_print(fontsize,",",eqx+varg2.x+varg2.dx-x+1,eqy+y-varg2.baseline,text_color,background,mode);
	  }
	}
	return;
      }
      int lpsize=int(text_width(fontsize,("(")));
      int rpsize=int(text_width(fontsize,(")")));
      eqwdata tmp=Equation_total_size(v.front()); // tmp= 1st arg eqwdata
      if (u==at_sto)
	tmp=Equation_total_size(v[1]);
      x0=w.x-x;
      y0=y-w.baseline;
      if (u==at_pow){
	if (!need_parenthesis(tmp.g)&& tmp.g!=at_pow && tmp.g!=at_prod && tmp.g!=at_division)
	  return;
	if (tmp.g==at_pow){
	  fontsize=tmp.eqw_attributs.fontsize+2;
	}
	if (tmp.x-lpsize<rightx)
	  text_print(fontsize,"(",eqx+tmp.x-x-lpsize,eqy+y-tmp.baseline,text_color,background,mode);
	if (tmp.x+tmp.dx<rightx)
	  text_print(fontsize,")",eqx+tmp.x+tmp.dx-x,eqy+y-tmp.baseline,text_color,background,mode);
	return;
      }
      if (u==at_program){
	if (tmp.x+tmp.dx<rightx)
	  text_print(fontsize,"->",eqx+tmp.x+tmp.dx-x,eqy+y-tmp.baseline,text_color,background,mode);
	return;
      }
#if 1
      if (u==at_sum){
	if (x0<rightx){
	  draw_line(eqx+x0,eqy+y0,eqx+x0+(2*fontsize)/3,eqy+y0,draw_line_color);
	  draw_line(eqx+x0,eqy+y0-fontsize,eqx+x0+(2*fontsize)/3,eqy+y0-fontsize,draw_line_color);
	  draw_line(eqx+x0,eqy+y0,eqx+x0+fontsize/2,eqy+y0-fontsize/2,draw_line_color);
	  draw_line(eqx+x0+fontsize/2,eqy+y0-fontsize/2,eqx+x0,eqy+y0-fontsize,draw_line_color);
	  if (v.size()>2){ // draw the =
	    eqwdata ptmp=Equation_total_size(v[1]);
	    if (ptmp.x+ptmp.dx<rightx)
	      text_print(fontsize,"=",eqx+ptmp.x+ptmp.dx-x-2,eqy+y-ptmp.baseline,text_color,background,mode);
	  }
	}
	return;
      }
#endif
      if (u==at_abs){
	y0 =1+y-w.y;
	int h=w.dy;
	if (x0<rightx){
	  draw_line(eqx+x0+2,eqy+y0-1,eqx+x0+2,eqy+y0-h+3,draw_line_color);
	  draw_line(eqx+x0+1,eqy+y0-1,eqx+x0+1,eqy+y0-h+3,draw_line_color);
	  draw_line(eqx+x0+w.dx-1,eqy+y0-1,eqx+x0+w.dx-1,eqy+y0-h+3,draw_line_color);
	  draw_line(eqx+x0+w.dx,eqy+y0-1,eqx+x0+w.dx,eqy+y0-h+3,draw_line_color);
	}
	return;
      }
      if (u==at_sqrt){
	y0 =1+y-w.y;
	int h=w.dy;
	if (x0<rightx){
	  draw_line(eqx+x0+2,eqy+y0-h/2,eqx+x0+fontsize/2,eqy+y0-1,draw_line_color);
	  draw_line(eqx+x0+fontsize/2,eqy+y0-1,eqx+x0+fontsize,eqy+y0-h+3,draw_line_color);
	  draw_line(eqx+x0+fontsize,eqy+y0-h+3,eqx+x0+w.dx-1,eqy+y0-h+3,draw_line_color);
	  ++y0;
	  draw_line(eqx+x0+2,eqy+y0-h/2,eqx+x0+fontsize/2,eqy+y0-1,draw_line_color);
	  draw_line(eqx+x0+fontsize/2,eqy+y0-1,eqx+x0+fontsize,eqy+y0-h+3,draw_line_color);
	  draw_line(eqx+x0+fontsize,eqy+y0-h+3,eqx+x0+w.dx-1,eqy+y0-h+3,draw_line_color);
	}
	return;
      }
      if (u==at_factorial){
	text_print(fontsize,"!",eqx+w.x+w.dx-4-x,eqy+y-w.baseline,text_color,background,mode);
	if (!need_parenthesis(tmp.g)
	    && tmp.g!=at_pow && tmp.g!=at_prod && tmp.g!=at_division
	    )
	  return;
	if (tmp.x-lpsize<rightx)
	  text_print(fontsize,"(",eqx+tmp.x-x-lpsize,eqy+y-tmp.baseline,text_color,background,mode);
	if (tmp.x+tmp.dx<rightx)
	  text_print(fontsize,")",eqx+tmp.x+tmp.dx-x,eqy+y-tmp.baseline,text_color,background,mode);
	return;
      }
#if 1
      if (u==at_integrate){
	x0+=2;
	y0+=fontsize/2;
	if (x0<rightx){
	  fl_arc(eqx+x0,eqy+y0,fontsize/3,fontsize/3,180,360,draw_line_color);
	  draw_line(eqx+x0+fontsize/3,eqy+y0,eqx+x0+fontsize/3,eqy+y0-2*fontsize+4,draw_line_color);
	  fl_arc(eqx+x0+fontsize/3,eqy+y0-2*fontsize+3,fontsize/3,fontsize/3,0,180,draw_line_color);
	}
	if (v.size()!=2){ // if arg has size > 1 draw the d
	  eqwdata ptmp=Equation_total_size(v[1]);
	  if (ptmp.x<rightx)
	    text_print(fontsize," d",eqx+ptmp.x-x-int(text_width(fontsize,(" d"))),eqy+y-ptmp.baseline,text_color,background,mode);
	}
	else {
	  eqwdata ptmp=Equation_total_size(v[0]);
	  if (ptmp.x+ptmp.dx<rightx)
	    text_print(fontsize," dx",eqx+ptmp.x+ptmp.dx-x,eqy+y-ptmp.baseline,text_color,background,mode);
	}
	return;
      }
#endif
      if (u==at_division){
	if (x0<rightx){
	  int yy=eqy+y0-8;
	  draw_line(eqx+x0+2,yy,eqx+x0+w.dx-2,yy,draw_line_color);
	  ++yy;
	  draw_line(eqx+x0+2,yy,eqx+x0+w.dx-2,yy,draw_line_color);
	}
	return;
      }
#if 1
      if (u==at_limit && v.size()>=4){
	if (x0<rightx)
	  text_print(fontsize,"lim",eqx+w.x-x,eqy+y-w.baseline,text_color,background,mode);
	gen arg2=v[1]; // 2nd arg of limit, i.e. the variable
	if (arg2.type==_EQW){ 
	  eqwdata & varg2=*arg2._EQWptr;
	  if (varg2.x+varg2.dx+2<rightx)
	    text_print(fontsize,"\x1e",eqx+varg2.x+varg2.dx+2-x,eqy+y-varg2.y,text_color,background,mode);
	}
	if (v.size()>=5){
	  arg2=v[2]; // 3rd arg of lim, the point, draw a comma after if dir.
	  if (arg2.type==_EQW){ 
	    eqwdata & varg2=*arg2._EQWptr;
	    if (varg2.x+varg2.dx<rightx)
	      text_print(fontsize,",",eqx+varg2.x+varg2.dx-x,eqy+y-varg2.baseline,text_color,background,mode);
	  }
	}
	return;
      } // limit
#endif
      bool parenthesis=true;
      string opstring(",");
      if (u.ptr()->printsommet==&printsommetasoperator || binary_op(u) ){
	if (u==at_normalmod && python_compat(contextptr))
	  opstring=" mod";
	else
	  opstring=u.ptr()->s;
      }
      else {
	if (u==at_sto)
	  opstring=":=";
	parenthesis=false;
      }
      // int yy=y0; // y0 is the lower coordinate of the whole eqwdata
      // int opsize=int(text_width(fontsize,(opstring.c_str())))+3;
      it=v.begin();
      itend=v.end()-1;
      // Reminder: here tmp is the 1st arg eqwdata, w the whole eqwdata
      if ( (itend-it==1) && ( (u==at_neg) 
			      || (u==at_plus) // uncommented for +infinity
			      ) ){ 
	if ( (u==at_neg &&need_parenthesis(tmp.g) && tmp.g!=at_prod)){
	  if (tmp.x-lpsize<rightx)
	    text_print(fontsize,"(",eqx+tmp.x-x-lpsize,eqy+y-tmp.baseline,text_color,background,mode);
	  if (tmp.x+tmp.dx<rightx)
	    text_print(fontsize,")",eqx+tmp.x-x+tmp.dx,eqy+y-tmp.baseline,text_color,background,mode);
	}
	if (w.x<rightx){
	  text_print(fontsize,u.ptr()->s,eqx+w.x-x,eqy+y-w.baseline,text_color,background,mode);
	}
	return;
      }
      // write first open parenthesis
      if (u==at_plus && tmp.g!=at_equal)
	parenthesis=false;
      else {
	if (parenthesis && need_parenthesis(tmp.g)){
	  if (w.x<rightx){
	    int pfontsize=max(fontsize,(fontsize+(tmp.baseline-tmp.y))/2);
	    text_print(pfontsize,"(",eqx+w.x-x,eqy+y-tmp.baseline,text_color,background,mode);
	  }
	}
      }
      for (;;){
	// write close parenthesis at end
	int xx=tmp.dx+tmp.x-x;
	if (parenthesis && need_parenthesis(tmp.g)){
	  if (xx<rightx){
	    int pfontsize=min(max(fontsize,(fontsize+(tmp.baseline-tmp.y))/2),fontsize*2);
	    int deltapary=(2*(pfontsize-fontsize))/3;
	    text_print(pfontsize,")",eqx+xx,eqy+y-tmp.baseline+deltapary,text_color,background,mode);
	  }
	  xx +=rpsize;
	}
	++it;
	if (it==itend){
	  if (u.ptr()->printsommet==&printsommetasoperator || u==at_sto || binary_op(u))
	    return;
	  else
	    break;
	}
	// write operator
	if (u==at_prod){
	  // text_print(fontsize,".",eqx+xx+3,eqy+y-tmp.baseline-fontsize/3);
	  text_print(fontsize,opstring.c_str(),eqx+xx+1,eqy+y-tmp.baseline,text_color,background,mode);
	}
	else {
	  gen tmpgen;
	  if (u==at_plus && ( 
			     (it->type==_VECT && it->_VECTptr->back().type==_EQW && it->_VECTptr->back()._EQWptr->g==at_neg) 
			     || 
			     ( it->type==_EQW && (is_integer(it->_EQWptr->g) || it->_EQWptr->g.type==_DOUBLE_) && is_strictly_positive(-it->_EQWptr->g,contextptr) ) 
			      )
	      )
	    ;
	  else {
	    if (xx+1<rightx)
	      // fl_draw(opstring.c_str(),xx+1,y-tmp.y-tmp.dy/2+fontsize/2);
	      text_print(fontsize,opstring.c_str(),eqx+xx+1,eqy+y-tmp.baseline,text_color,background,mode);
	  }
	}
	// write right parent, update tmp
	tmp=Equation_total_size(*it);
	if (parenthesis && (need_parenthesis(tmp.g)) ){
	  if (tmp.x-lpsize<rightx){
	    int pfontsize=min(max(fontsize,(fontsize+(tmp.baseline-tmp.y))/2),fontsize*2);
	    int deltapary=(2*(pfontsize-fontsize))/3;
	    text_print(pfontsize,"(",eqx+tmp.x-pfontsize*lpsize/fontsize-x,eqy+y-tmp.baseline+deltapary,text_color,background,mode);
	  }
	}
      } // end for (;;)
      if (w.x<rightx){
	s = u.ptr()->s;
	s += '(';
	text_print(fontsize,s.c_str(),eqx+w.x-x,eqy+y-w.baseline,text_color,background,mode);
      }
      if (w.x+w.dx-rpsize<rightx)
	text_print(fontsize,")",eqx+w.x+w.dx-x-rpsize+2,eqy+y-w.baseline,text_color,background,mode);
      return;
    }
    s=oper.print(contextptr);
    if (w.x<rightx){
      text_print(fontsize,s.c_str(),eqx+w.x-x,eqy+y-w.baseline,text_color,background,mode);
    }
  }

  Equation::Equation(int x_, int y_, const gen & g,const giac::context * cptr){
    _x=x_;
    _y=y_;
    attr=attributs(18,COLOR_WHITE,COLOR_BLACK);
    contextptr=cptr;
    if (taille(g,max_prettyprint_equation)<max_prettyprint_equation)
      data=Equation_compute_size(g,attr,LCD_WIDTH_PX,contextptr);
    else
      data=Equation_compute_size(string2gen("Object_too_large",false),attr,LCD_WIDTH_PX,contextptr);
    undodata=Equation_copy(data);
  }

  void replace_selection(Equation & eq,const gen & tmp,gen * gsel,const vector<int> * gotoptr,GIAC_CONTEXT){
    int xleft,ytop,xright,ybottom,gselpos; gen *gselparent;
    vector<int> goto_sel;
    eq.undodata=Equation_copy(eq.data);
    if (gotoptr==0){
      if (xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel) && gsel)
	gotoptr=&goto_sel;
      else
	return;
    }
    *gsel=xcas::Equation_compute_size(tmp,eq.attr,LCD_WIDTH_PX,contextptr);
    gen value;
    xcas::do_select(eq.data,true,value);
    if (value.type==_EQW)
      eq.data=xcas::Equation_compute_size(value._EQWptr->g,eq.attr,LCD_WIDTH_PX,contextptr);
    //cout << "new value " << value << " " << eq.data << " " << *gotoptr << endl;
    xcas::Equation_select(eq.data,false);
    gen * gptr=&eq.data;
    for (int i=gotoptr->size()-1;i>=0;--i){
      int pos=(*gotoptr)[i];
      if (gptr->type==_VECT &&gptr->_VECTptr->size()>pos)
	gptr=&(*gptr->_VECTptr)[pos];
    }
    xcas::Equation_select(*gptr,true);
    //cout << "new sel " << *gptr << endl;
  }

  void display(Equation & eq,int x,int y,GIAC_CONTEXT){
    // Equation_draw(eq.data,x,y,LCD_WIDTH_PX,0,&eq,contextptr);
    int xleft,ytop,xright,ybottom,gselpos; gen * gsel,*gselparent;
    eqwdata eqdata=Equation_total_size(eq.data);
    if ( (eqdata.dx>LCD_WIDTH_PX || eqdata.dy>LCD_HEIGHT_PX-STATUS_AREA_PX) && Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos)){
      if (x<xleft){
	if (x+LCD_WIDTH_PX<xright)
	  x=giacmin(xleft,xright-LCD_WIDTH_PX);
      }
      if (x>=xleft && x+LCD_WIDTH_PX>=xright){
	if (xright-x<LCD_WIDTH_PX)
	  x=giacmax(xright-LCD_WIDTH_PX,0);
      }
#if 0
      cout << "avant " << y << " " << ytop << " " << ybottom << endl;
      if (y<ytop){
	if (y+LCD_HEIGHT_PX<ybottom)
	  y=giacmin(ytop,ybottom-LCD_HEIGHT_PX);
      }
      if (y>=ytop && y+LCD_HEIGHT_PX>=ybottom){
	if (ybottom-y<LCD_HEIGHT_PX)
	  y=giacmax(ybottom-LCD_HEIGHT_PX,0);
      }
      cout << "apres " << y << " " << ytop << " " << ybottom << endl;
#endif
    }
    int save_ymin_clip=clip_ymin;
    clip_ymin=STATUS_AREA_PX;
    Equation_draw(eq.data,x,y,RAND_MAX,0,&eq,contextptr);
    clip_ymin=save_ymin_clip;
  }
  
  /* ******************* *
   *      GRAPH          *
   * ******************* *
   */
#if 1

  double find_tick(double dx){
    double d=std::pow(10.0,std::floor(std::log10(absdouble(dx))));
    if (dx<2*d)
      d=d/5;
    else {
      if (dx<5*d)
	d=d/2;
    }
    return d;
  }

  Graph2d::Graph2d(const giac::gen & g_,const giac::context * cptr):window_xmin(gnuplot_xmin),window_xmax(gnuplot_xmax),window_ymin(gnuplot_ymin),window_ymax(gnuplot_ymax),g(g_),display_mode(0x45),show_axes(1),show_names(1),labelsize(16),contextptr(cptr) {
    update();
    autoscale();
  }
  
  void Graph2d::zoomx(double d,bool round){
    double x_center=(window_xmin+window_xmax)/2;
    double dx=(window_xmax-window_xmin);
    if (dx==0)
      dx=gnuplot_xmax-gnuplot_xmin;
    dx *= d/2;
    x_tick = find_tick(dx);
    window_xmin = x_center - dx;
    if (round) 
      window_xmin=int( window_xmin/x_tick -1)*x_tick;
    window_xmax = x_center + dx;
    if (round)
      window_xmax=int( window_xmax/x_tick +1)*x_tick;
    update();
  }

  void Graph2d::zoomy(double d,bool round){
    double y_center=(window_ymin+window_ymax)/2;
    double dy=(window_ymax-window_ymin);
    if (dy==0)
      dy=gnuplot_ymax-gnuplot_ymin;
    dy *= d/2;
    y_tick = find_tick(dy);
    window_ymin = y_center - dy;
    if (round)
      window_ymin=int( window_ymin/y_tick -1)*y_tick;
    window_ymax = y_center + dy;
    if (round)
      window_ymax=int( window_ymax/y_tick +1)*y_tick;
    update();
  }

  void Graph2d::zoom(double d){ 
    zoomx(d);
    zoomy(d);
  }

  void Graph2d::autoscale(bool fullview){
    // Find the largest and lowest x/y/z in objects (except lines/plans)
    vector<double> vx,vy,vz;
    int s;
    bool ortho=autoscaleg(g,vx,vy,vz,contextptr);
    autoscaleminmax(vx,window_xmin,window_xmax,fullview);
    zoomx(1.0);
    autoscaleminmax(vy,window_ymin,window_ymax,fullview);
    zoomy(1.0);
    bool do_ortho=ortho;
    if (!do_ortho){
      double w=LCD_WIDTH_PX;
      double h=LCD_HEIGHT_PX-STATUS_AREA_PX;
      double window_w=window_xmax-window_xmin,window_h=window_ymax-window_ymin;
      double tst=h/w*window_w/window_h;
      if (tst>0.7 && tst<1.4)
	do_ortho=true;
    }
    if (do_ortho )
      orthonormalize();
    y_tick=find_tick(window_ymax-window_ymin);
    update();
  }

  void Graph2d::orthonormalize(){ 
    // Center of the directions, orthonormalize
    double w=LCD_WIDTH_PX;
    double h=LCD_HEIGHT_PX-STATUS_AREA_PX;
    double window_w=window_xmax-window_xmin,window_h=window_ymax-window_ymin;
    double window_hsize=h/w*window_w;
    if (window_h > window_hsize*1.01){ // enlarge horizontally
      double window_xcenter=(window_xmin+window_xmax)/2;
      double window_wsize=w/h*window_h;
      window_xmin=window_xcenter-window_wsize/2;
      window_xmax=window_xcenter+window_wsize/2;
    }
    if (window_h < window_hsize*0.99) { // enlarge vertically
      double window_ycenter=(window_ymin+window_ymax)/2;
      window_ymin=window_ycenter-window_hsize/2;
      window_ymax=window_ycenter+window_hsize/2;
    }
    x_tick=find_tick(window_xmax-window_xmin);
    y_tick=find_tick(window_ymax-window_ymin);
    update();
  }

  void Graph2d::update(){
    x_scale=LCD_WIDTH_PX/(window_xmax-window_xmin);    
    y_scale=(LCD_HEIGHT_PX-STATUS_AREA_PX)/(window_ymax-window_ymin);    
  }

  bool Graph2d::findij(const gen & e0,double x_scale,double y_scale,double & i0,double & j0,GIAC_CONTEXT) const {
    gen e,f0,f1;
    evalfdouble2reim(e0,e,f0,f1,contextptr);
    if ((f0.type==_DOUBLE_) && (f1.type==_DOUBLE_)){
      if (display_mode & 0x400){
	if (f0._DOUBLE_val<=0)
	  return false;
	f0=std::log10(f0._DOUBLE_val);
      }
      i0=(f0._DOUBLE_val-window_xmin)*x_scale;
      if (display_mode & 0x800){
	if (f1._DOUBLE_val<=0)
	  return false;
	f1=std::log10(f1._DOUBLE_val);
      }
      j0=(window_ymax-f1._DOUBLE_val)*y_scale;
      return true;
    }
    // cerr << "Invalid drawing data" << endl;
    return false;
  }

  inline void swapint(int & i0,int & i1){
    int tmp=i0;
    i0=i1;
    i1=tmp;
  }

  void check_fl_draw(int fontsize,const char * ch,int i0,int j0,int imin,int jmin,int di,int dj,int delta_i,int delta_j,int c){
    /* int n=fl_size();
       if (j0>=jmin-n && j0<=jmin+dj+n) */
    // cerr << i0 << " " << j0 << endl;
    if (strlen(ch)>200)
      text_print(fontsize,"String too long",i0+delta_i,j0+delta_j,c);
    else
      text_print(fontsize,ch,i0+delta_i,j0+delta_j,c);
  }

  inline void check_fl_point(int i0,int j0,int imin,int jmin,int di,int dj,int delta_i,int delta_j,int c){
    /* if (i0>=imin && i0<=imin+di && j0>=jmin && j0<=jmin+dj) */
    numworks_giac_set_pixel(i0+delta_i,j0+delta_j,c);
  }

  inline void fl_line(int x0,int y0,int x1,int y1,int c){
    draw_line(x0,y0,x1,y1,c);
  }

  inline void fl_polygon(int x0,int y0,int x1,int y1,int x2,int y2,int c){
    draw_line(x0,y0,x1,y1,c);
    draw_line(x1,y1,x2,y2,c);
  }

  inline void check_fl_line(int i0,int j0,int i1,int j1,int imin,int jmin,int di,int dj,int delta_i,int delta_j,int c){
    fl_line(i0+delta_i,j0+delta_j,i1+delta_i,j1+delta_j,c);
  }

  int logplot_points=20;

  void checklog_fl_line(double i0,double j0,double i1,double j1,double deltax,double deltay,bool logx,bool logy,double window_xmin,double x_scale,double window_ymax,double y_scale,int c){
    if (!logx && !logy){
      fl_line(round(i0+deltax),round(j0+deltay),round(i1+deltax),round(j1+deltay),c);
      return;
    }
  }

  void find_dxdy(const string & legendes,int labelpos,int labelsize,int & dx,int & dy){
    int l=text_width(labelsize,legendes.c_str());
    dx=3;
    dy=1;
    switch (labelpos){
    case 1:
      dx=-l-3;
      break;
    case 2:
      dx=-l-3;
      dy=labelsize-2;
      break;
    case 3:
      dy=labelsize-2;
      break;
    }
    dy += labelsize;
  }

  void draw_legende(const vecteur & f,int i0,int j0,int labelpos,const Graph2d * iptr,int clip_x,int clip_y,int clip_w,int clip_h,int deltax,int deltay,int c,GIAC_CONTEXT){
    if (f.empty() ||!iptr->show_names )
      return;
    string legendes;
    if (f[0].is_symb_of_sommet(at_curve)){
      gen & f0=f[0]._SYMBptr->feuille;
      if (f0.type==_VECT && !f0._VECTptr->empty()){
	gen & f1 = f0._VECTptr->front();
	if (f1.type==_VECT && f1._VECTptr->size()>4 && (!is_zero((*f1._VECTptr)[4]) || (iptr->show_names & 2)) ){
	  gen legende=f1._VECTptr->front();
	  gen var=(*f1._VECTptr)[1];
	  gen r=re(legende,contextptr),i=im(legende,contextptr),a,b;
	  if (var.type==_IDNT && is_linear_wrt(r,*var._IDNTptr,a,b,contextptr)){
	    i=subst(i,var,(var-b)/a,false,contextptr);
	    legendes=i.print(contextptr);
	  }
	  else
	    legendes=r.print(contextptr)+","+i.print(contextptr);
	  if (legendes.size()>18){
	    if (legendes.size()>30)
	      legendes="";
	    else
	      legendes=legendes.substr(0,16)+"...";
	  }
	}
      }
    }
    if (f.size()>2)
      legendes=gen2string(f[2])+(legendes.empty()?"":":")+legendes;
    if (legendes.empty())
      return;
    int fontsize=iptr->labelsize;
    int dx=3,dy=1;
    find_dxdy(legendes,labelpos,fontsize,dx,dy);
    check_fl_draw(fontsize,legendes.c_str(),i0+dx,j0+dy,clip_x,clip_y,clip_w,clip_h,deltax,deltay,c);
  }

  void petite_fleche(double i1,double j1,double dx,double dy,int deltax,int deltay,int width,int c){
    double dxy=std::sqrt(dx*dx+dy*dy);
    if (dxy){
      dxy/=max(2,min(5,int(dxy/10)))+width;
      dx/=dxy;
      dy/=dxy;
      double dxp=-dy,dyp=dx; // perpendicular
      dx*=std::sqrt(3.0);
      dy*=sqrt(3.0);
      fl_polygon(round(i1)+deltax,round(j1)+deltay,round(i1+dx+dxp)+deltax,round(j1+dy+dyp)+deltay,round(i1+dx-dxp)+deltax,round(j1+dy-dyp)+deltay,c);
    }
  }

  void fltk_point(int deltax,int deltay,int i0,int j0,int epaisseur_point,int type_point,int c){
    switch (type_point){
    case 1: // losange
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0,deltay+j0-epaisseur_point,c);
      fl_line(deltax+i0,deltay+j0-epaisseur_point,deltax+i0+epaisseur_point,deltay+j0,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0,deltay+j0+epaisseur_point,c);
      fl_line(deltax+i0,deltay+j0+epaisseur_point,deltax+i0+epaisseur_point,deltay+j0,c);
      break;
    case 2: // croix verticale
      fl_line(deltax+i0,deltay+j0-epaisseur_point,deltax+i0,deltay+j0+epaisseur_point,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0+epaisseur_point,deltay+j0,c);
      break;
    case 3: // carre
      fl_line(deltax+i0-epaisseur_point,deltay+j0-epaisseur_point,deltax+i0-epaisseur_point,deltay+j0+epaisseur_point,c);
      fl_line(deltax+i0+epaisseur_point,deltay+j0-epaisseur_point,deltax+i0+epaisseur_point,deltay+j0+epaisseur_point,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0-epaisseur_point,deltax+i0+epaisseur_point,deltay+j0-epaisseur_point,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0+epaisseur_point,deltax+i0+epaisseur_point,deltay+j0+epaisseur_point,c);
      break;
    case 5: // triangle
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0,deltay+j0-epaisseur_point,c);
      fl_line(deltax+i0,deltay+j0-epaisseur_point,deltax+i0+epaisseur_point,deltay+j0,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0+epaisseur_point,deltay+j0,c);
      break;
    case 7: // point
      if (epaisseur_point>2)
	fl_arc(deltax+i0-(epaisseur_point-1),deltay+j0-(epaisseur_point-1),2*(epaisseur_point-1),2*(epaisseur_point-1),0,360,c);
      else
	fl_line(deltax+i0,deltay+j0,deltax+i0+1,deltay+j0,c);
      break;
    case 6: // etoile
      fl_line(deltax+i0-epaisseur_point,deltay+j0,deltax+i0+epaisseur_point,deltay+j0,c);
      // no break to add the following lines
    case 0: // 0 croix diagonale
      fl_line(deltax+i0-epaisseur_point,deltay+j0-epaisseur_point,deltax+i0+epaisseur_point,deltay+j0+epaisseur_point,c);
      fl_line(deltax+i0-epaisseur_point,deltay+j0+epaisseur_point,deltax+i0+epaisseur_point,deltay+j0-epaisseur_point,c);
      break;
    default: // 4 nothing drawn
      break;
    }
  }

  int horiz_or_vert(const_iterateur jt,GIAC_CONTEXT){
    gen tmp(*(jt+1)-*jt),r,i;
    reim(tmp,r,i,contextptr);
    if (is_zero(r,contextptr)) return 1;
    if (is_zero(i,contextptr)) return 2;
    return 0;
  }

  void fltk_draw(Graph2d & Mon_image,const gen & g,double x_scale,double y_scale,int clip_x,int clip_y,int clip_w,int clip_h,GIAC_CONTEXT){
    int deltax=0,deltay=STATUS_AREA_PX,fontsize=Mon_image.labelsize;
    if (g.type==_VECT){
      const vecteur & v=*g._VECTptr;
      const_iterateur it=v.begin(),itend=v.end();
      for (;it!=itend;++it)
	fltk_draw(Mon_image,*it,x_scale,y_scale,clip_x,clip_y,clip_w,clip_h,contextptr);
    }
    if (g.type!=_SYMB)
      return;
    unary_function_ptr s=g._SYMBptr->sommet;
    if (g._SYMBptr->feuille.type!=_VECT)
      return;
    vecteur f=*g._SYMBptr->feuille._VECTptr;
    int mxw=LCD_WIDTH_PX,myw=LCD_HEIGHT_PX-STATUS_AREA_PX;
    double i0,j0,i0save,j0save,i1,j1;
    int fs=f.size();
    if ((fs==4) && (s==at_parameter)){
      return ;
    }
    string the_legend;
    vecteur style(get_style(f,the_legend));
    int styles=style.size();
    // color
    int ensemble_attributs = style.front().val;
    bool hidden_name = false;
    if (style.front().type==_ZINT){
      ensemble_attributs = mpz_get_si(*style.front()._ZINTptr);
      hidden_name=true;
    }
    else
      hidden_name=ensemble_attributs<0;
    int width           =(ensemble_attributs & 0x00070000) >> 16; // 3 bits
    int epaisseur_point =(ensemble_attributs & 0x00380000) >> 19; // 3 bits
    int type_line       =(ensemble_attributs & 0x01c00000) >> 22; // 3 bits
    if (type_line>4)
      type_line=(type_line-4)<<8;
    int type_point      =(ensemble_attributs & 0x0e000000) >> 25; // 3 bits
    int labelpos        =(ensemble_attributs & 0x30000000) >> 28; // 2 bits
    bool fill_polygon   =(ensemble_attributs & 0x40000000) >> 30;
    int couleur         =(ensemble_attributs & 0x0007ffff);
    epaisseur_point += 2;
    if (s==at_pnt){ 
      // f[0]=complex pnt or vector of complex pnts or symbolic
      // f[1] -> style 
      // f[2] optional=label
      gen point=f[0];
      if (point.type==_VECT && point.subtype==_POINT__VECT)
	return;
      if ( (f[0].type==_SYMB) && (f[0]._SYMBptr->sommet==at_curve) && (f[0]._SYMBptr->feuille.type==_VECT) && (f[0]._SYMBptr->feuille._VECTptr->size()) ){
	// Mon_image.show_mouse_on_object=false;
	point=f[0]._SYMBptr->feuille._VECTptr->back();
	if (type_line>=4 && point.type==_VECT && point._VECTptr->size()>2){
	  vecteur v=*point._VECTptr;
	  int vs=v.size()/2; // 3 -> 1
	  if (Mon_image.findij(v[vs],x_scale,y_scale,i0,j0,contextptr) && Mon_image.findij(v[vs+1],x_scale,y_scale,i1,j1,contextptr)){
	    bool logx=Mon_image.display_mode & 0x400,logy=Mon_image.display_mode & 0x800;
	    checklog_fl_line(i0,j0,i1,j1,deltax,deltay,logx,logy,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	    double dx=i0-i1,dy=j0-j1;
	    petite_fleche(i1,j1,dx,dy,deltax,deltay,width+3,couleur);
	  }
	}
      }
      if (is_undef(point))
	return;
      // fl_line_style(type_line,width+1,0); 
      if (point.type==_SYMB) {
	if (point._SYMBptr->sommet==at_cercle){
	  vecteur v=*point._SYMBptr->feuille._VECTptr;
	  gen diametre=remove_at_pnt(v[0]);
	  gen e1=diametre._VECTptr->front().evalf_double(1,contextptr),e2=diametre._VECTptr->back().evalf_double(1,contextptr);
	  gen centre=rdiv(e1+e2,2.0,contextptr);
	  gen e12=e2-e1;
	  double ex=evalf_double(re(e12,contextptr),1,contextptr)._DOUBLE_val,ey=evalf_double(im(e12,contextptr),1,contextptr)._DOUBLE_val;
	  if (!Mon_image.findij(centre,x_scale,y_scale,i0,j0,contextptr))
	    return;
	  gen diam=std::sqrt(ex*ex+ey*ey);
	  gen angle=std::atan2(ey,ex);
	  gen a1=v[1].evalf_double(1,contextptr),a2=v[2].evalf_double(1,contextptr);
	  bool full=v[1]==0 && v[2]==cst_two_pi;
	  if ( (diam.type==_DOUBLE_) && (a1.type==_DOUBLE_) && (a2.type==_DOUBLE_) ){
	    i1=diam._DOUBLE_val*x_scale/2.0;
	    j1=diam._DOUBLE_val*y_scale/2.0;
	    double a1d=a1._DOUBLE_val,a2d=a2._DOUBLE_val,angled=angle._DOUBLE_val;
	    bool changer_sens=a1d>a2d;
	    if (changer_sens){
	      double tmp=a1d;
	      a1d=a2d;
	      a2d=tmp;
	    }
	    double anglei=(angled+a1d),anglef=(angled+a2d),anglem=(anglei+anglef)/2;
	    if (fill_polygon)
	      fl_pie(deltax+round(i0-i1),deltay+round(j0-j1),round(2*i1),round(2*j1),full?0:anglei*180/M_PI+.5,full?360:anglef*180/M_PI+.5,couleur,false);
	    else {
	      fl_arc(deltax+round(i0-i1),deltay+round(j0-j1),round(2*i1),round(2*j1),full?0:anglei*180/M_PI+.5,full?360:anglef*180/M_PI+.5,couleur);
	      if (v.size()>=4){ // if cercle has the optionnal 5th arg
		if (v[3]==2)
		  petite_fleche(i0+i1*std::cos(anglem),j0-j1*std::sin(anglem),-i1*std::sin(anglem),-j1*std::cos(anglem),deltax,deltay,width,couleur);
		else {
		  if (changer_sens)
		    petite_fleche(i0+i1*std::cos(anglei),j0-j1*std::sin(anglei),-i1*std::sin(anglei),-j1*std::cos(anglei),deltax,deltay,width,couleur);
		  else
		    petite_fleche(i0+i1*std::cos(anglef),j0-j1*std::sin(anglef),i1*std::sin(anglef),j1*std::cos(anglef),deltax,deltay,width,couleur);
		}
	      }
	    }
	    // Label a few degrees from the start angle, 
	    // FIXME should use labelpos
	    double anglel=angled+a1d+0.3;
	    if (v.size()>=4 && v[3]==2)
	      anglel=angled+(0.45*a1d+0.55*a2d);
	    i0=i0+i1*std::cos(anglel); 
	    j0=j0-j1*std::sin(anglel);
	    if (!hidden_name)
	      draw_legende(f,round(i0),round(j0),labelpos,&Mon_image,clip_x,clip_y,clip_w,clip_h,0,0,couleur,contextptr);
	    return;
	  }
	} // end circle
#if 0
	if (point._SYMBptr->sommet==at_legende){
	  gen & f=point._SYMBptr->feuille;
	  if (f.type==_VECT && f._VECTptr->size()==3){
	    vecteur & fv=*f._VECTptr;
	    if (fv[0].type==_VECT && fv[0]._VECTptr->size()>=2 && fv[1].type==_STRNG && fv[2].type==_INT_){
	      vecteur & fvv=*fv[0]._VECTptr;
	      if (fvv[0].type==_INT_ && fvv[1].type==_INT_){
		int dx=0,dy=0;
		string legendes(*fv[1]._STRNGptr);
		find_dxdy(legendes,labelpos,fontsize,dx,dy);
		text_print(fontsize,legendes.c_str(),deltax+fvv[0].val+dx,deltay+fvv[1].val+dy,fv[2].val);
	      }
	    }
	  }
	}
#endif
      } // end point.type==_SYMB
      if (point.type!=_VECT || (point.type==_VECT && (point.subtype==_GROUP__VECT || point.subtype==_VECTOR__VECT) && point._VECTptr->size()==2 && is_zero(point._VECTptr->back()-point._VECTptr->front())) ){ // single point
	if (!Mon_image.findij((point.type==_VECT?point._VECTptr->front():point),x_scale,y_scale,i0,j0,contextptr))
	  return;
	if (i0>0 && i0<mxw && j0>0 && j0<myw)
	  fltk_point(deltax,deltay,round(i0),round(j0),epaisseur_point,type_point,couleur);
	if (!hidden_name)
	  draw_legende(f,round(i0),round(j0),labelpos,&Mon_image,clip_x,clip_y,clip_w,clip_h,0,0,couleur,contextptr);
	return;
      }
      // path
      const_iterateur jt=point._VECTptr->begin(),jtend=point._VECTptr->end();
      if (jt==jtend)
	return;
      bool logx=Mon_image.display_mode & 0x400,logy=Mon_image.display_mode & 0x800;
      if (jt->type==_VECT)
	return;
      if ( (type_point || epaisseur_point>2) && type_line==0 && width==0){
	for (;jt!=jtend;++jt){
	  if (!Mon_image.findij(*jt,x_scale,y_scale,i0,j0,contextptr))
	    return;
	  if (i0>0 && i0<mxw && j0>0 && j0<myw)
	    fltk_point(deltax,deltay,round(i0),round(j0),epaisseur_point,type_point,couleur);
	}
	if (!hidden_name)
	  draw_legende(f,round(i0),round(j0),labelpos,&Mon_image,clip_x,clip_y,clip_w,clip_h,0,0,couleur,contextptr);
	return;
      }
      // initial point
      if (!Mon_image.findij(*jt,x_scale,y_scale,i0,j0,contextptr))
	return;
      i0save=i0;
      j0save=j0;
      if (fill_polygon){
	if (jtend-jt==5 && *(jt+4)==*jt){
	  // check rectangle parallel to axes -> draw_rectangle (filled)
	  int cote1=horiz_or_vert(jt,contextptr);
	  if (cote1 && horiz_or_vert(jt+1,contextptr)==3-cote1 && horiz_or_vert(jt+2,contextptr)==cote1 && horiz_or_vert(jt+3,contextptr)==3-cote1){
	    if (!Mon_image.findij(*(jt+2),x_scale,y_scale,i0,j0,contextptr))
	      return;
	    int x,y,w,h;
	    if (i0<i0save){
	      x=i0;
	      w=i0save-i0;
	    }
	    else {
	      x=i0save;
	      w=i0-i0save;
	    }
	    if (j0<j0save){
	      y=j0;
	      h=j0save-j0;
	    }
	    else {
	      y=j0save;
	      h=j0-j0save;
	    }
	    draw_rectangle(deltax+x,deltay+y,w,h,couleur);
	    return;
	  }
	} // end rectangle check
	bool closed=*jt==*(jtend-1);
	vector< vector<int> > vi(jtend-jt+(closed?0:1),vector<int>(2));
	for (int pos=0;jt!=jtend;++pos,++jt){
	  if (!Mon_image.findij(*jt,x_scale,y_scale,i0,j0,contextptr))
	    return;
	  vi[pos][0]=i0+deltax;
	  vi[pos][1]=j0+deltay;
	}
	if (!closed)
	  vi.back()=vi.front();
	draw_filled_polygon(vi,0,LCD_WIDTH_PX,24,LCD_HEIGHT_PX,couleur);
	return;
      }
      ++jt;
      if (jt==jtend){
	if (i0>0 && i0<mxw && j0>0 && j0<myw)
	  check_fl_point(deltax+round(i0),deltay+round(j0),clip_x,clip_y,clip_w,clip_h,0,0,couleur);
	if (!hidden_name)
	  draw_legende(f,round(i0),round(j0),labelpos,&Mon_image,clip_x,clip_y,clip_w,clip_h,0,0,couleur,contextptr);
	return;
      }
      bool seghalfline=( point.subtype==_LINE__VECT || point.subtype==_HALFLINE__VECT ) && (point._VECTptr->size()==2);
      // rest of the path
      for (;;){
	if (!Mon_image.findij(*jt,x_scale,y_scale,i1,j1,contextptr))
	  return;
	if (!seghalfline){
	  checklog_fl_line(i0,j0,i1,j1,deltax,deltay,logx,logy,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	  if (point.subtype==_VECTOR__VECT){
	    double dx=i0-i1,dy=j0-j1;
	    petite_fleche(i1,j1,dx,dy,deltax,deltay,width,couleur);
	  }
	}
	++jt;
	if (jt==jtend){ // label of line at midpoint
	  if (point.subtype==_LINE__VECT){
	    i0=(6*i1-i0)/5-8;
	    j0=(6*j1-j0)/5-8;
	  }
	  else {
	    i0=(i0+i1)/2-8;
	    j0=(j0+j1)/2;
	  }
	  break;
	}
	i0=i1;
	j0=j1;
      }
      // check for a segment/halfline/line
      if ( seghalfline){
	double deltai=i1-i0save,adeltai=absdouble(deltai);
	double deltaj=j1-j0save,adeltaj=absdouble(deltaj);
	if (point.subtype==_LINE__VECT){
	  if (deltai==0)
	    checklog_fl_line(i1,0,i1,clip_h,deltax,deltay,logx,logy,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	  else {
	    if (deltaj==0)
	      checklog_fl_line(0,j1,clip_w,j1,deltax,deltay,Mon_image.display_mode & 0x400,Mon_image.display_mode & 0x800,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	    else {
	      // Find the intersections with the 4 rectangle segments
	      // Horizontal x=0 or w =i1+t*deltai: y=j1+t*deltaj
	      vector< complex<double> > pts;
	      double y0=j1-i1/deltai*deltaj,tol=clip_h*1e-6;
	      if (y0>=-tol && y0<=clip_h+tol)
		pts.push_back(complex<double>(0.0,y0));
	      double yw=j1+(clip_w-i1)/deltai*deltaj;
	      if (yw>=-tol && yw<=clip_h+tol)
		pts.push_back(complex<double>(clip_w,yw));
	      // Vertical y=0 or h=j1+t*deltaj, x=i1+t*deltai
	      double x0=i1-j1/deltaj*deltai;
	      tol=clip_w*1e-6;
	      if (x0>=-tol && x0<=clip_w+tol)
		pts.push_back(complex<double>(x0,0.0));
	      double xh=i1+(clip_h-j1)/deltaj*deltai;
	      if (xh>=-tol && xh<=clip_w+tol)
		pts.push_back(complex<double>(xh,clip_h));
	      if (pts.size()>=2)
		checklog_fl_line(pts[0].real(),pts[0].imag(),pts[1].real(),pts[1].imag(),deltax,deltay,Mon_image.display_mode & 0x400,Mon_image.display_mode & 0x800,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	    } // end else adeltai==0 , adeltaj==0
	  } // end else adeltai==0
	} // end LINE_VECT
	else {
	  double N=1;
	  if (adeltai){
	    N=clip_w/adeltai+1;
	    if (adeltaj)
	      N=max(N,clip_h/adeltaj+1);
	  }
	  else {
	    if (adeltaj)
	      N=clip_h/adeltaj+1;
	  }
	  N *= 2; // increase N since rounding might introduce too small clipping
	  while (fabs(N*deltai)>10000)
	    N /= 2;
	  while (fabs(N*deltaj)>10000)
	    N /= 2;
	  checklog_fl_line(i0save,j0save,i1+N*deltai,j1+N*deltaj,deltax,deltay,Mon_image.display_mode & 0x400,Mon_image.display_mode & 0x800,Mon_image.window_xmin,x_scale,Mon_image.window_ymax,y_scale,couleur);
	}
      } // end seghalfline
      if ( (point.subtype==_GROUP__VECT) && (point._VECTptr->size()==2))
	; // no legend for segment
      else {
	if (!hidden_name)
	  draw_legende(f,round(i0),round(j0),labelpos,&Mon_image,clip_x,clip_y,clip_w,clip_h,0,0,couleur,contextptr);
      }
    } // end pnt subcase
  }
#endif

  // return a vector of values with simple decimal representation
  // between xmin/xmax or including xmin/xmax (if bounds is true)
  vecteur ticks(double xmin,double xmax,bool bounds){
    if (xmax<xmin)
      swapdouble(xmin,xmax);
    double dx=xmax-xmin;
    vecteur res;
    if (dx==0)
      return res;
    double d=std::pow(10.0,std::floor(std::log10(dx)));
    if (dx<2*d)
      d=d/5;
    else {
      if (dx<5*d)
	d=d/2;
    }
    double x1=std::floor(xmin/d)*d;
    double x2=(bounds?std::ceil(xmax/d):std::floor(xmax/d))*d;
    for (double x=x1+(bounds?0:d);x<=x2;x+=d){
      if (absdouble(x-int(x+.5))<1e-6*d)
	res.push_back(int(x+.5));
      else
	res.push_back(x);
    }
    return res;
  }

  void Graph2d::draw(){
    int save_clip_ymin=clip_ymin;
    clip_ymin=STATUS_AREA_PX;
    int horizontal_pixels=LCD_WIDTH_PX,vertical_pixels=LCD_HEIGHT_PX-STATUS_AREA_PX,deltax=0,deltay=STATUS_AREA_PX,clip_x=0,clip_y=0,clip_w=horizontal_pixels,clip_h=vertical_pixels;
    drawRectangle(0, STATUS_AREA_PX, horizontal_pixels, vertical_pixels,COLOR_WHITE);
    // Draw axis
    double I0,J0;
    findij(zero,x_scale,y_scale,I0,J0,contextptr); // origin
    int i_0=round(I0),j_0=round(J0);
    if (show_axes &&  (window_ymax>=0) && (window_ymin<=0)){ // X-axis
      vecteur aff; int affs;
      char ch[256];
      check_fl_line(deltax,deltay+j_0,deltax+horizontal_pixels,deltay+j_0,clip_x,clip_y,clip_w,clip_h,0,0,_GREEN); 
      check_fl_line(deltax+i_0,deltay+j_0,deltax+i_0+int(x_scale),deltay+j_0,clip_x,clip_y,clip_w,clip_h,0,0,_CYAN);
      aff=ticks(window_xmin,window_xmax,true);
      affs=aff.size();
      for (int i=0;i<affs;++i){
	double d=evalf_double(aff[i],1,contextptr)._DOUBLE_val;
	if (fabs(d)<1e-6) strcpy(ch,"0"); else sprint_double(ch,d);
	int delta=int(horizontal_pixels*(d-window_xmin)/(window_xmax-window_xmin));
	int taille=strlen(ch)*9;
	fl_line(delta,deltay+j_0,delta,deltay+j_0-4,_GREEN);
      }
      check_fl_draw(labelsize,"x",deltax+horizontal_pixels-40,deltay+j_0-4,clip_x,clip_y,clip_w,clip_h,0,0,_GREEN);
    }
    if ( show_axes && (window_xmax>=0) && (window_xmin<=0) ) {// Y-axis
      vecteur aff; int affs;
      char ch[256];
      check_fl_line(deltax+i_0,deltay,deltax+i_0,deltay+vertical_pixels,clip_x,clip_y,clip_w,clip_h,0,0,_RED);
      check_fl_line(deltax+i_0,deltay+j_0,deltax+i_0,deltay+j_0-int(y_scale),clip_x,clip_y,clip_w,clip_h,0,0,_CYAN);
      aff=ticks(window_ymin,window_ymax,true);
      affs=aff.size();
      int taille=5;
      for (int j=0;j<affs;++j){
	double d=evalf_double(aff[j],1,contextptr)._DOUBLE_val;
	if (fabs(d)<1e-6) strcpy(ch,"0"); else sprint_double(ch,d);
	int delta=int(vertical_pixels*(window_ymax-d)/(window_ymax-window_ymin));
	if (delta>=taille && delta<=vertical_pixels-taille){
	  fl_line(deltax+i_0,STATUS_AREA_PX+delta,deltax+i_0+4,STATUS_AREA_PX+delta,_RED);
	}
      }
      check_fl_draw(labelsize,"y",deltax+i_0+2,deltay+labelsize,clip_x,clip_y,clip_w,clip_h,0,0,_RED);
    }
#if 0 // if ticks are enabled, don't forget to set freeze to false
    // Ticks
    if (show_axes && (horizontal_pixels)/(x_scale*x_tick) < 40 && vertical_pixels/(y_tick*y_scale) <40  ){
      if (x_tick>0 && y_tick>0 ){
	double nticks=(horizontal_pixels-I0)/(x_scale*x_tick);
	double mticks=(vertical_pixels-J0)/(y_tick*y_scale);
	int count=0;
	for (int ii=int(-I0/(x_tick*x_scale));ii<=nticks;++ii){
	  int iii=int(I0+ii*x_scale*x_tick+.5);
	  for (int jj=int(-J0/(y_tick*y_scale));jj<=mticks && count<1600;++jj,++count){
	    int jjj=int(J0+jj*y_scale*y_tick+.5);
	    check_fl_point(deltax+iii,deltay+jjj,clip_x,clip_y,clip_w,clip_h,0,0,COLOR_BLACK);
	  }
	}
      }
    }
#endif
    if (show_axes){ 
      int taille,affs,delta;
      vecteur aff;
      char ch[256];
      // X
      aff=ticks(window_xmin,window_xmax,true);
      affs=aff.size();
      for (int i=0;i<affs;++i){
	double d=evalf_double(aff[i],1,contextptr)._DOUBLE_val;
	sprint_double(ch,d);
	delta=int(horizontal_pixels*(d-window_xmin)/(window_xmax-window_xmin));
	taille=strlen(ch)*9;
	fl_line(delta,vertical_pixels+STATUS_AREA_PX-6,delta,vertical_pixels+STATUS_AREA_PX-1,_GREEN);
	if (delta>=taille/2 && delta<=horizontal_pixels){
	  text_print(10,ch,delta-taille/2,vertical_pixels+STATUS_AREA_PX-7,_GREEN);
	}
      }
      // Y
      aff=ticks(window_ymin,window_ymax,true);
      affs=aff.size();
      taille=5;
      for (int j=0;j<affs;++j){
	double d=evalf_double(aff[j],1,contextptr)._DOUBLE_val;
	sprint_double(ch,d);
	delta=int(vertical_pixels*(window_ymax-d)/(window_ymax-window_ymin));
	if (delta>=taille && delta<=vertical_pixels-taille){
	  fl_line(horizontal_pixels-5,STATUS_AREA_PX+delta,horizontal_pixels-1,STATUS_AREA_PX+delta,_RED);
	  text_print(10,ch,horizontal_pixels-strlen(ch)*9,STATUS_AREA_PX+delta+taille,_RED);
	}
      }
    }
    
    // draw
    fltk_draw(*this,g,x_scale,y_scale,clip_x,clip_y,clip_w,clip_h,contextptr);
    clip_ymin=save_clip_ymin;
  }
  
  void Graph2d::left(double d){ 
    window_xmin -= d;
    window_xmax -= d;
  }

  void Graph2d::right(double d){ 
    window_xmin += d;
    window_xmax += d;
  }

  void Graph2d::up(double d){ 
    window_ymin += d;
    window_ymax += d;
  }

  void Graph2d::down(double d){ 
    window_ymin -= d;
    window_ymax -= d;
  }

  void Turtle::draw(){
    const int deltax=0,deltay=0;
    int horizontal_pixels=LCD_WIDTH_PX-2*giac::COORD_SIZE;
    // Check for fast redraw
    // Then redraw the background
    drawRectangle(deltax, deltay, LCD_WIDTH_PX, LCD_HEIGHT_PX-24,COLOR_WHITE);
    if (turtleptr &&
#ifdef TURTLETAB
	turtle_stack_size
#else
	!turtleptr->empty()
#endif
	){
      if (turtlezoom>8)
	turtlezoom=8;
      if (turtlezoom<0.125)
	turtlezoom=0.125;
      // check that position is not out of screen
#ifdef TURTLETAB
      logo_turtle t=turtleptr[turtle_stack_size-1];
#else
      logo_turtle t=turtleptr->back();
#endif
      double x=turtlezoom*(t.x-turtlex);
      if (x<0)
	turtlex += int(x/turtlezoom);
      if (x>=LCD_WIDTH_PX-10)
	turtlex += int((x-LCD_WIDTH_PX+10)/turtlezoom);
      double y=turtlezoom*(t.y-turtley);
      if (y<0)
	turtley += int(y/turtlezoom);
      if (y>LCD_HEIGHT_PX-10)
	turtley += int((y-LCD_HEIGHT_PX+10)/turtlezoom);
    }
#if 0
    if (maillage & 0x3){
      fl_color(FL_BLACK);
      double xdecal=std::floor(turtlex/10.0)*10;
      double ydecal=std::floor(turtley/10.0)*10;
      if ( (maillage & 0x3)==1){
	for (double i=xdecal;i<LCD_WIDTH_PX+xdecal;i+=10){
	  for (double j=ydecal;j<LCD_HEIGHT_PX+ydecal;j+=10){
	    fl_point(deltax+int((i-turtlex)*turtlezoom+.5),deltay+LCD_HEIGHT_PX-int((j-turtley)*turtlezoom+.5));
	  }
	}
      }
      else {
	double dj=std::sqrt(3.0)*10,i0=xdecal;
	for (double j=ydecal;j<LCD_HEIGHT_PX+ydecal;j+=dj){
	  int J=deltay+int(LCD_HEIGHT_PX-(j-turtley)*turtlezoom);
	  for (double i=i0;i<LCD_WIDTH_PX+xdecal;i+=10){
	    fl_point(deltax+int((i-turtlex)*turtlezoom+.5),J);
	  }
	  i0 += dj;
	  while (i0>=10)
	    i0 -= 10;
	}
      }
    }
#endif
    // Show turtle position/cap
    if (turtleptr &&
#ifdef TURTLETAB
	turtle_stack_size &&
#else
	!turtleptr->empty() &&
#endif
	!(maillage & 0x4)){
#ifdef TURTLETAB
      logo_turtle turtle=turtleptr[turtle_stack_size-1];
#else
      logo_turtle turtle=turtleptr->back();
#endif
      drawRectangle(deltax+horizontal_pixels,deltay,LCD_WIDTH_PX-horizontal_pixels,2*COORD_SIZE,_YELLOW);
      // drawRectangle(deltax, deltay, LCD_WIDTH_PX, LCD_HEIGHT_PX,COLOR_BLACK);
      char buf[32];
      sprintf(buf,"x %i   ",int(turtle.x+.5));
      text_print(18,buf,deltax+horizontal_pixels,deltay+(2*COORD_SIZE)/3-2,COLOR_BLACK,_YELLOW);
      sprintf(buf,"y %i   ",int(turtle.y+.5));
      text_print(18,buf,deltax+horizontal_pixels,deltay+(4*COORD_SIZE)/3-3,COLOR_BLACK,_YELLOW);
      sprintf(buf,"t %i   ",int(turtle.theta+.5));
      text_print(18,buf,deltax+horizontal_pixels,deltay+2*COORD_SIZE-4,COLOR_BLACK,_YELLOW);
    }
    // draw turtle Logo
    if (turtleptr){
#ifdef TURTLETAB
      int l=turtle_stack_size;
#else
      int l=turtleptr->size();
#endif
      if (l>0){
#ifdef TURTLETAB
	logo_turtle prec =turtleptr[0];
#else
	logo_turtle prec =(*turtleptr)[0];
#endif
	for (int k=1;k<l;++k){
#ifdef TURTLETAB
	  logo_turtle current =(turtleptr)[k];
#else
	  logo_turtle current =(*turtleptr)[k];
#endif
#if 1
	  if (current.s>=0){ // Write a string
	    //cout << current.radius << " " << current.s << endl;
	    if (current.s<ecristab().size())
	      text_print(current.radius,ecristab()[current.s].c_str(),int(deltax+turtlezoom*(current.x-turtlex)),int(deltay+LCD_HEIGHT_PX-turtlezoom*(current.y-turtley)),current.color);
	  }
	  else
#endif
	    {
	    if (current.radius>0){
	      int r=current.radius & 0x1ff; // bit 0-8
	      double theta1,theta2;
	      if (current.direct){
		theta1=prec.theta+double((current.radius >> 9) & 0x1ff); // bit 9-17
		theta2=prec.theta+double((current.radius >> 18) & 0x1ff); // bit 18-26
	      }
	      else {
		theta1=prec.theta-double((current.radius >> 9) & 0x1ff); // bit 9-17
		theta2=prec.theta-double((current.radius >> 18) & 0x1ff); // bit 18-26
	      }
	      bool rempli=(current.radius >> 27) & 0x1;
	      bool seg=(current.radius >> 28) & 0x1;
	      double angle;
	      int x,y,R;
	      R=int(2*turtlezoom*r+.5);
	      angle = M_PI/180*(theta2-90);
	      if (current.direct){
		x=int(turtlezoom*(current.x-turtlex-r*std::cos(angle) - r)+.5);
		y=int(turtlezoom*(current.y-turtley-r*std::sin(angle) + r)+.5);
	      }
	      else {
		x=int(turtlezoom*(current.x-turtlex+r*std::cos(angle) -r)+.5);
		y=int(turtlezoom*(current.y-turtley+r*std::sin(angle) +r)+.5);
	      }
	      if (current.direct){
		if (rempli)
		  fl_pie(deltax+x,deltay+LCD_HEIGHT_PX-y,R,R,theta1-90,theta2-90,current.color,seg);
		else
		  fl_arc(deltax+x,deltay+LCD_HEIGHT_PX-y,R,R,theta1-90,theta2-90,current.color);
	      }
	      else {
		if (rempli)
		  fl_pie(deltax+x,deltay+LCD_HEIGHT_PX-y,R,R,90+theta2,90+theta1,current.color,seg);
		else
		  fl_arc(deltax+x,deltay+LCD_HEIGHT_PX-y,R,R,90+theta2,90+theta1,current.color);
	      }
	    } // end radius>0
	    else {
	      if (prec.mark){
		fl_line(deltax+int(turtlezoom*(prec.x-turtlex)+.5),deltay+int(LCD_HEIGHT_PX+turtlezoom*(turtley-prec.y)+.5),deltax+int(turtlezoom*(current.x-turtlex)+.5),deltay+int(LCD_HEIGHT_PX+turtlezoom*(turtley-current.y)+.5),prec.color);
	      }
	    }
	    if (current.radius<-1 && k+current.radius>=0){
	      // poly-line from (*turtleptr)[k+current.radius] to (*turtleptr)[k]
	      vector< vector<int> > vi(1-current.radius,vector<int>(2));
	      for (int i=0;i>=current.radius;--i){
#ifdef TURTLETAB
		logo_turtle & t=(turtleptr)[k+i];
#else
		logo_turtle & t=(*turtleptr)[k+i];
#endif
		vi[-i][0]=deltax+turtlezoom*(t.x-turtlex);
		vi[-i][1]=deltay+LCD_HEIGHT_PX+turtlezoom*(turtley-t.y);
		//*logptr(contextptr) << i << " " << vi[-i][0] << " " << vi[-i][1] << endl;
	      }
	      //vi.back()=vi.front();
	      draw_filled_polygon(vi,0,LCD_WIDTH_PX,24,LCD_HEIGHT_PX,current.color);
	    }
	  } // end else (non-string turtle record)
	  prec=current;
	} // end for (all turtle records)
#ifdef TURTLETAB
	logo_turtle & t = (turtleptr)[l-1];
#else
	logo_turtle & t = (*turtleptr)[l-1];
#endif
	int x=int(turtlezoom*(t.x-turtlex)+.5);
	int y=int(turtlezoom*(t.y-turtley)+.5);
	double cost=std::cos(t.theta*deg2rad_d);
	double sint=std::sin(t.theta*deg2rad_d);
	int Dx=int(turtlezoom*t.turtle_length*cost/2+.5);
	int Dy=int(turtlezoom*t.turtle_length*sint/2+.5);
	if (t.visible){
	  fl_line(deltax+x+Dy,deltay+LCD_HEIGHT_PX-(y-Dx),deltax+x-Dy,deltay+LCD_HEIGHT_PX-(y+Dx),t.color);
	  int c=t.color;
	  if (!t.mark)
	    c=t.color ^ 0x7777;
	  fl_line(deltax+x+Dy,deltay+LCD_HEIGHT_PX-(y-Dx),deltax+x+3*Dx,deltay+LCD_HEIGHT_PX-(y+3*Dy),c);
	  fl_line(deltax+x-Dy,deltay+LCD_HEIGHT_PX-(y+Dx),deltax+x+3*Dx,deltay+LCD_HEIGHT_PX-(y+3*Dy),c);
	}
      }
      return;
    } // End logo mode
  }  
  

  void displaygraph(const giac::gen & ge,GIAC_CONTEXT){
    // graph display
    //if (aborttimer > 0) { Timer_Stop(aborttimer); Timer_Deinstall(aborttimer);}
    xcas::Graph2d gr(ge,contextptr);
    gr.show_axes=true;
    // initial setting for x and y
    if (ge.type==_VECT){
      const_iterateur it=ge._VECTptr->begin(),itend=ge._VECTptr->end();
      for (;it!=itend;++it){
	if (it->is_symb_of_sommet(at_equal)){
	  const gen & f=it->_SYMBptr->feuille;
	  gen & optname = f._VECTptr->front();
	  gen & optvalue= f._VECTptr->back();
	  if (optname.val==_AXES && optvalue.type==_INT_)
	    gr.show_axes=optvalue.val;
	  if (optname.type==_INT_ && optname.subtype == _INT_PLOT && optname.val>=_GL_X && optname.val<=_GL_Z && optvalue.is_symb_of_sommet(at_interval)){
	    //*logptr(contextptr) << optname << " " << optvalue << endl;
	    gen optvf=evalf_double(optvalue._SYMBptr->feuille,1,contextptr);
	    if (optvf.type==_VECT && optvf._VECTptr->size()==2){
	      gen a=optvf._VECTptr->front();
	      gen b=optvf._VECTptr->back();
	      if (a.type==_DOUBLE_ && b.type==_DOUBLE_){
		switch (optname.val){
		case _GL_X:
		  gr.window_xmin=a._DOUBLE_val;
		  gr.window_xmax=b._DOUBLE_val;
		  gr.update();
		  break;
		case _GL_Y:
		  gr.window_ymin=a._DOUBLE_val;
		  gr.window_ymax=b._DOUBLE_val;
		  gr.update();
		  break;
		}
	      }
	    }
	  }
	}
      }
    }
    // UI
    DefineStatusMessage((char*)"+-: zoom, pad: move, EXIT: quit", 1, 0, 0);
    // EnableStatusArea(2);
    for (;;){
      gr.draw();
      DisplayStatusArea();
      // int x=0,y=LCD_HEIGHT_PX-STATUS_AREA_PX-17;
      // PrintMini(&x,&y,(unsigned char *)"menu",0x04,0xffffffff,0,0,COLOR_BLACK,COLOR_WHITE,1,0);
      int key=-1;
      GetKey(&key);
#if 0
      if (key==KEY_CTRL_F1){
	char menu_xmin[32],menu_xmax[32],menu_ymin[32],menu_ymax[32];
	string s;
	s="xmin "+print_DOUBLE_(gr.window_xmin,6);
	strcpy(menu_xmin,s);
	s="xmax "+print_DOUBLE_(gr.window_xmax,6);
	strcpy(menu_xmax,s);
	s="ymin "+print_DOUBLE_(gr.window_ymin,6);
	strcpy(menu_ymin,s);
	s="ymax "+print_DOUBLE_(gr.window_ymax,6);
	strcpy(menu_ymax,s);
	Menu smallmenu;
	smallmenu.numitems=12;
	MenuItem smallmenuitems[smallmenu.numitems];
	smallmenu.items=smallmenuitems;
	smallmenu.height=8;
	//smallmenu.title = "KhiCAS";
	smallmenuitems[0].text = (char *) menu_xmin;
	smallmenuitems[1].text = (char *) menu_xmax;
	smallmenuitems[2].text = (char *) menu_ymin;
	smallmenuitems[3].text = (char *) menu_ymax;
	smallmenuitems[4].text = (char*) "Orthonormalize /";
	smallmenuitems[5].text = (char*) "Autoscale *";
	smallmenuitems[6].text = (char *) ("Zoom in +");
	smallmenuitems[7].text = (char *) ("Zoom out -");
	smallmenuitems[8].text = (char *) ("Y-Zoom out (-)");
	smallmenuitems[9].text = (char*) (lang?"Voir axes":"Show axes");
	smallmenuitems[10].text = (char*) (lang?"Cacher axes":"Hide axes");
	smallmenuitems[11].text = (char*)(lang?"Quitter":"Quit");
	int sres = doMenu(&smallmenu);
	if(sres == MENU_RETURN_SELECTION) {
	  const char * ptr=0;
	  string s1; double d;
	  if (smallmenu.selection==1){
	    if (inputdouble(menu_xmin,d)){
	      gr.window_xmin=d;
	      gr.update();
	    }
	  }
	  if (smallmenu.selection==2){
	    if (inputdouble(menu_xmax,d)){
	      gr.window_xmax=d;
	      gr.update();
	    }
	  }
	  if (smallmenu.selection==3){
	    if (inputdouble(menu_ymin,d)){
	      gr.window_ymin=d;
	      gr.update();
	    }
	  }
	  if (smallmenu.selection==4){
	    if (inputdouble(menu_ymax,d)){
	      gr.window_ymax=d;
	      gr.update();
	    }
	  }
	  if (smallmenu.selection==5)
	    gr.orthonormalize();
	  if (smallmenu.selection==6)
	    gr.autoscale();	
	  if (smallmenu.selection==7)
	    gr.zoom(0.7);	
	  if (smallmenu.selection==8)
	    gr.zoom(1/0.7);	
	  if (smallmenu.selection==9)
	    gr.zoomy(1/0.7);
	  if (smallmenu.selection==10)
	    gr.show_axes=true;	
	  if (smallmenu.selection==11)
	    gr.show_axes=false;	
	  if (smallmenu.selection==12)
	    break;
	}
      }
#endif
      if (key==KEY_CTRL_EXIT || key==KEY_CTRL_OK){
	numworks_giac_hide_graph();
	break;
      }
      if (key==KEY_CTRL_UP){ gr.up((gr.window_ymax-gr.window_ymin)/5); }
      if (key==KEY_CTRL_PAGEUP) { gr.up((gr.window_ymax-gr.window_ymin)/2); }
      if (key==KEY_CTRL_DOWN) { gr.down((gr.window_ymax-gr.window_ymin)/5); }
      if (key==KEY_CTRL_PAGEDOWN) { gr.down((gr.window_ymax-gr.window_ymin)/2);}
      if (key==KEY_CTRL_LEFT) { gr.left((gr.window_xmax-gr.window_xmin)/5); }
      if (key==KEY_SHIFT_LEFT) { gr.left((gr.window_xmax-gr.window_xmin)/2); }
      if (key==KEY_CTRL_RIGHT) { gr.right((gr.window_xmax-gr.window_xmin)/5); }
      if (key==KEY_SHIFT_RIGHT) { gr.right((gr.window_xmax-gr.window_xmin)/5); }
      if (key==KEY_CHAR_PLUS) { gr.zoom(0.7);}
      if (key==KEY_CHAR_MINUS){ gr.zoom(1/0.7); }
      if (key==KEY_CHAR_PMINUS){ gr.zoomy(1/0.7); }
      if (key==KEY_CHAR_MULT){ gr.autoscale(); }
      if (key==KEY_CHAR_DIV) { gr.orthonormalize(); }
      if (key==KEY_CTRL_VARS) {gr.show_axes=!gr.show_axes;}
    }
    // aborttimer = Timer_Install(0, check_execution_abort, 100); if (aborttimer > 0) { Timer_Start(aborttimer); }
    return ;
  }

  void displaylogo(){
#ifdef TURTLETAB
    xcas::Turtle t={tablogo,0,0,1,1};
#else
    xcas::Turtle t={&turtle_stack(),0,0,1,1};
#endif
    DefineStatusMessage((char*)"+-: zoom, pad: move, EXIT: quit", 1, 0, 0);
    DisplayStatusArea();
    while (1){
      int save_ymin=clip_ymin;
      clip_ymin=24;
      t.draw();
      clip_ymin=save_ymin;
      int key;
      GetKey(&key);
      if (key==KEY_CTRL_EXIT || key==KEY_CTRL_OK || key==KEY_PRGM_ACON || key==KEY_CTRL_MENU || key==KEY_CTRL_EXE || key==KEY_CTRL_VARS)
	break;
      if (key==KEY_CTRL_UP){ t.turtley += 10; }
      if (key==KEY_CTRL_PAGEUP) { t.turtley += 100; }
      if (key==KEY_CTRL_DOWN) { t.turtley -= 10; }
      if (key==KEY_CTRL_PAGEDOWN) { t.turtley -= 100;}
      if (key==KEY_CTRL_LEFT) { t.turtlex -= 10; }
      if (key==KEY_SHIFT_LEFT) { t.turtlex -= 100; }
      if (key==KEY_CTRL_RIGHT) { t.turtlex += 10; }
      if (key==KEY_SHIFT_RIGHT) { t.turtlex += 100;}
      if (key==KEY_CHAR_PLUS) { t.turtlezoom *= 2;}
      if (key==KEY_CHAR_MINUS){ t.turtlezoom /= 2;  }
    }
    numworks_giac_hide_graph();
  }

  bool ispnt(const gen & g){
    if (g.is_symb_of_sommet(giac::at_pnt))
      return true;
    if (g.type!=_VECT || g._VECTptr->empty())
      return false;
    return ispnt(g._VECTptr->back());
  }

  giac::gen eqw(const giac::gen & ge,bool editable,GIAC_CONTEXT){
    bool edited=false;
    const int margin=24;
#ifdef CURSOR
    Cursor_SetFlashOff();
#endif
    giac::gen geq(_copy(ge,contextptr));
    // if (ge.type!=giac::_DOUBLE_ && giac::has_evalf(ge,geq,1,contextptr)) geq=giac::symb_equal(ge,geq);
    int line=-1,col=-1,nlines=0,ncols=0,listormat=0;
    xcas::Equation eq(0,0,geq,contextptr);
    giac::eqwdata eqdata=xcas::Equation_total_size(eq.data);
    if (eqdata.dx>1.5*LCD_WIDTH_PX || eqdata.dy>1.5*LCD_HEIGHT_PX){
      if (eqdata.dx>2.25*LCD_WIDTH_PX || eqdata.dy>2.25*LCD_HEIGHT_PX)
	eq.attr=giac::attributs(14,COLOR_WHITE,COLOR_BLACK);
      else
	eq.attr=giac::attributs(16,COLOR_WHITE,COLOR_BLACK);
      eq.data=0; // clear memory
      eq.data=xcas::Equation_compute_size(geq,eq.attr,LCD_WIDTH_PX,contextptr);
      eqdata=xcas::Equation_total_size(eq.data);
    }
    int dx=(eqdata.dx-LCD_WIDTH_PX)/2,dy=LCD_HEIGHT_PX-2*margin+eqdata.y;
    if (geq.type==_VECT){
      nlines=geq._VECTptr->size();
      if (eqdata.dx>=LCD_WIDTH_PX)
	dx=-20; // line=nlines/2;
      //else
      if (geq.subtype!=_SEQ__VECT){
	line=0;
	listormat=1;
	if (ckmatrix(geq)){
	  ncols=geq._VECTptr->front()._VECTptr->size();
	  if (eqdata.dy>=LCD_HEIGHT_PX-margin)
	    dy=eqdata.y+eqdata.dy+32;// col=ncols/2;
	  // else
	  col=0;
	  listormat=2;
	}
      }
    }
    if (!listormat){
      xcas::Equation_select(eq.data,true);
      xcas::eqw_select_down(eq.data);
    }
    //cout << eq.data << endl;
    int firstrun=2;
    for (;;){
#if 1
      if (firstrun==2){
	DefineStatusMessage((char*)(lang?"EXE: quitte, resultat dans last":"EXE: quit, result stored in last"), 1, 0, 0);
	DisplayStatusArea();
	firstrun=1;
      }
      else
	set_xcas_status();
#else
      DefineStatusMessage((char*)"+-: zoom, pad: move, EXIT: quit", 1, 0, 0);
      EnableStatusArea(2);
      DisplayStatusArea();
#endif
      gen value;
      if (listormat) // select line l, col c
	xcas::eqw_select(eq.data,line,col,true,value);
      if (eqdata.dx>LCD_WIDTH_PX){
	if (dx<-20)
	  dx=-20;
	if (dx>eqdata.dx-LCD_WIDTH_PX+20)
	  dx=eqdata.dx-LCD_WIDTH_PX+20;
      }
#define EQW_TAILLE 18
      if (eqdata.dy>LCD_HEIGHT_PX-2*EQW_TAILLE){
	if (dy-eqdata.y<LCD_HEIGHT_PX-2*EQW_TAILLE)
	  dy=eqdata.y+LCD_HEIGHT_PX-2*EQW_TAILLE;
	if (dy-eqdata.y>eqdata.dy+32)
	  dy=eqdata.y+eqdata.dy+32;
      }
      drawRectangle(0, STATUS_AREA_PX, LCD_WIDTH_PX, LCD_HEIGHT_PX-STATUS_AREA_PX,COLOR_WHITE);
      // Bdisp_AllClr_VRAM();
      int save_clip_ymin=clip_ymin;
      clip_ymin=STATUS_AREA_PX;
      xcas::display(eq,dx,dy,contextptr);
#if 0
      string menu(" ");
      menu += menu_f1;
      while (menu.size()<6)
	menu += " ";
      menu += " | ";
      menu += string(menu_f2);
      while (menu.size()<13)
	menu += " ";
      menu += " | edit+-| cmds | A<>a | eval";
      PrintMini(0,58,menu.c_str(),4);
#endif
      //draw_menu(2);
      clip_ymin=save_clip_ymin;
      int keyflag = GetSetupSetting( (unsigned int)0x14);
      bool alph=keyflag==4||keyflag==0x84||keyflag==8||keyflag==0x88;
      if (firstrun){ // workaround for e.g. 1+x/2 partly not displayed
	firstrun=0;
	continue;
      }
      int key;
      //cout << eq.data << endl;
      GetKey(&key);
      if (key==KEY_CTRL_OK){
	numworks_giac_hide_graph();
	return geq;
      }
      if (key==KEY_CTRL_EXIT || key==KEY_CTRL_AC || key==KEY_CTRL_EXE){
	if (!edited){
	  numworks_giac_hide_graph();
	  return geq;
	}
	if (confirm(lang?"Vraiment abandonner?":"Really leave",lang?"F1: retour editeur,  F6: confirmer":"F1: back to editor,  F6: confirm")==KEY_CTRL_F6){
	  numworks_giac_hide_graph();
	  return undef;
	}
      }
      if (key==KEY_CTRL_UNDO){
	giac::swapgen(eq.undodata,eq.data);
	continue;
      }
      if (key==KEY_CTRL_F5){
	handle_f5();
	continue;
      }
      int redo=0;
      bool ins=key==KEY_CHAR_STORE  || key==KEY_CHAR_RPAR || key==KEY_CHAR_LPAR || key==KEY_CHAR_COMMA || key==KEY_CTRL_PASTE;
      int xleft,ytop,xright,ybottom,gselpos; gen * gsel=0,*gselparent=0;
      if (key==KEY_CTRL_CLIP){
	xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,0);
	if (gsel==0)
	  gsel==&eq.data;
	// cout << "var " << g << " " << eq.data << endl;
	if (xcas::do_select(*gsel,true,value) && value.type==_EQW){
	  //cout << g << ":=" << value._EQWptr->g << endl;
	  copy_clipboard(value._EQWptr->g.print(contextptr),true);
	  continue;
	}
      }
      if (key==KEY_CHAR_STORE){
	int keyflag = GetSetupSetting( (unsigned int)0x14);
	if (keyflag==0)
	  handle_f5();
	std::string varname;
	if (inputline((lang?"Stocker la selection dans":"Save selection in",lang?"Nom de variable: ":"Variable name: "),varname,false) && !varname.empty() && isalpha(varname[0])){
	  giac::gen g(varname,contextptr);
	  giac::gen ge(eval(g,1,contextptr));
	  if (g.type!=_IDNT){
	    invalid_varname();
	    continue;
	  }
	  if (ge==g || confirm_overwrite()){
	    vector<int> goto_sel;
	    xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel);
	    if (gsel==0)
	      gsel==&eq.data;
	    // cout << "var " << g << " " << eq.data << endl;
	    if (xcas::do_select(*gsel,true,value) && value.type==_EQW){
	      //cout << g << ":=" << value._EQWptr->g << endl;
	      giac::sto(value._EQWptr->g,g,contextptr);
	    }
	  }
	}
	continue;
      }
      if (key==KEY_CTRL_DEL){
	vector<int> goto_sel;
	if (xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel) && gsel && xcas::do_select(*gsel,true,value) && value.type==_EQW){
	  value=value._EQWptr->g;
	  if (value.type==_SYMB){
	    gen tmp=value._SYMBptr->feuille;
	    if (tmp.type!=_VECT || tmp.subtype!=_SEQ__VECT){
	      xcas::replace_selection(eq,tmp,gsel,&goto_sel,contextptr);
	      continue;
	    }
	  }
	  if (!goto_sel.empty() && gselparent && gselparent->type==_VECT && !gselparent->_VECTptr->empty()){
	    vecteur & v=*gselparent->_VECTptr;
	    if (v.back().type==_EQW){
	      gen opg=v.back()._EQWptr->g;
	      if (opg.type==_FUNC){
		int i=0;
		for (;i<v.size()-1;++i){
		  if (&v[i]==gsel)
		    break;
		}
		if (i<v.size()-1){
		  if (v.size()==5 && (opg==at_integrate || opg==at_sum) && i>=2)
		    v.erase(v.begin()+2,v.begin()+4);
		  else
		    v.erase(v.begin()+i);
		  xcas::do_select(*gselparent,true,value);
		  if (value.type==_EQW){
		    value=value._EQWptr->g;
		    // cout << goto_sel << " " << value << endl; continue;
		    if (v.size()==2 && (opg==at_plus || opg==at_prod))
		      value=eval(value,1,contextptr);
		    goto_sel.erase(goto_sel.begin());
		    xcas::replace_selection(eq,value,gselparent,&goto_sel,contextptr);
		    continue;
		  }
		}
	      }
	    }
	  }
	}
      }
      if (key==KEY_CTRL_F3){
	if (keyflag==1){
	  if (eq.attr.fontsize>=18) continue;
	  xcas::do_select(eq.data,true,value);
	  if (value.type==_EQW)
	    geq=value._EQWptr->g;
	  if (eq.attr.fontsize==14)
	    eq.attr.fontsize=16;
	  else
	    eq.attr.fontsize=18;
	  redo=1;
	}
	else {
	  if (alph){
	    if (eq.attr.fontsize<=14) continue;
	    xcas::do_select(eq.data,true,value);
	    if (value.type==_EQW)
	      geq=value._EQWptr->g;
	    if (eq.attr.fontsize==16)
	      eq.attr.fontsize=14;
	    else
	      eq.attr.fontsize=16;
	    redo=1;
	  }
	  else {
	    // Edit
	    edited=true;
	    ins=true;
	  }
	}
      }
      if (key==KEY_CHAR_IMGNRY)
	key='i';
      const char keybuf[2]={(key==KEY_CHAR_PMINUS?'-':char(key)),0};
      const char * adds=(key==KEY_CHAR_PMINUS ||
			 (key==char(key) && (isalphanum(key)|| key=='.' ))
			 )?keybuf:keytostring(key,keyflag);
      translate_fkey(key);
      if ( key==KEY_CTRL_F1 || key==KEY_CTRL_F2 ||
	   (key>=KEY_CTRL_F7 && key<=KEY_CTRL_F14)){
	adds=console_menu(key,1);//alph?"simplify":(keyflag==1?"factor":"partfrac");
	// workaround for infinitiy
	if (strlen(adds)>=2 && adds[0]=='o' && adds[1]=='o')
	  key=KEY_CTRL_F5;      
      }
      if (key==KEY_CTRL_F5)
	adds="oo";
      if (key==KEY_CTRL_F6){
	adds=alph?"regroup":(keyflag==1?"evalf":"eval");
      }
      if (key==KEY_CHAR_MINUS)
	adds="-";
      if (key==KEY_CHAR_EQUAL)
	adds="=";
      if (key==KEY_CHAR_RECIP)
	adds="inv";
      if (key==KEY_CHAR_SQUARE)
	adds="sq";
      if (key==KEY_CHAR_POWROOT)
	adds="surd";
      if (key==KEY_CHAR_CUBEROOT)
	adds="surd";
      int addssize=adds?strlen(adds):0;
      // cout << addssize << " " << adds << endl;
      if (key==KEY_CTRL_EXE){
	if (xcas::do_select(eq.data,true,value) && value.type==_EQW){
	  //cout << "ok " << value._EQWptr->g << endl;
	  //DefineStatusMessage((char*)lang?"resultat stocke dans last":"result stored in last", 1, 0, 0);
	  //DisplayStatusArea();
	  giac::sto(value._EQWptr->g,giac::gen("last",contextptr),contextptr);
	  return value._EQWptr->g;
	}
	//cout << "no " << eq.data << endl; if (value.type==_EQW) cout << value._EQWptr->g << endl ;
	return geq;
      }
      if ( key!=KEY_CHAR_MINUS && key!=KEY_CHAR_EQUAL &&
	   (ins || key==KEY_CHAR_PI || key==KEY_CTRL_F5 || (addssize==1 && (isalphanum(adds[0])|| adds[0]=='.' || adds[0]=='-') ) )
	   ){
	edited=true;
	if (line>=0 && xcas::eqw_select(eq.data,line,col,true,value)){
	  string s;
	  if (ins){
	    if (key==KEY_CTRL_PASTE)
	      s=paste_clipboard();
	    else {
	      if (value.type==_EQW){
		s=value._EQWptr->g.print(contextptr);
	      }
	      else
		s=value.print(contextptr);
	    }
	  }
	  else
	    s = adds;
	  string msg("Line ");
	  msg += print_INT_(line+1);
	  msg += " Col ";
	  msg += print_INT_(col+1);
	  if (inputline(msg.c_str(),0,s,false)==KEY_CTRL_EXE){
	    value=gen(s,contextptr);
	    if (col<0)
	      (*geq._VECTptr)[line]=value;
	    else
	      (*((*geq._VECTptr)[line]._VECTptr))[col]=value;
	    redo=2;
	    key=KEY_SHIFT_RIGHT;
	  }
	  else
	    continue;
	}
	else {
	  vector<int> goto_sel;
	  if (xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel) && gsel && xcas::do_select(*gsel,true,value) && value.type==_EQW){
	    string s;
	    if (ins){
	      if (key==KEY_CTRL_PASTE)
		s=paste_clipboard();
	      else {
		s = value._EQWptr->g.print(contextptr);
		if (key==KEY_CHAR_COMMA)
		  s += ',';
	      }
	    }
	    else
	      s = adds;
	    if (inputline(value._EQWptr->g.print(contextptr).c_str(),0,s,false)==KEY_CTRL_EXE){
	      value=gen(s,contextptr);
	      //cout << value << " goto " << goto_sel << endl;
	      xcas::replace_selection(eq,value,gsel,&goto_sel,contextptr);
	      firstrun=-1; // workaround, force 2 times display
	    }
	    continue;
	  }
	}
      }
      if (redo){
	eq.data=0; // clear memory
	eq.data=xcas::Equation_compute_size(geq,eq.attr,LCD_WIDTH_PX,contextptr);
	eqdata=xcas::Equation_total_size(eq.data);
	if (redo==1){
	  dx=(eqdata.dx-LCD_WIDTH_PX)/2;
	  dy=LCD_HEIGHT_PX-2*margin+eqdata.y;
	  if (listormat) // select line l, col c
	    xcas::eqw_select(eq.data,line,col,true,value);
	  else {
	    xcas::Equation_select(eq.data,true);
	    xcas::eqw_select_down(eq.data);
	  }
	  continue;
	}
      }
      bool doit=eqdata.dx>=LCD_WIDTH_PX;
      int delta=0;
      if (listormat){
	if (key==KEY_CTRL_LEFT  || (!doit && key==KEY_SHIFT_LEFT)){
	  if (line>=0 && xcas::eqw_select(eq.data,line,col,false,value)){
	    if (col>=0){
	      --col;
	      if (col<0){
		col=ncols-1;
		if (line>0)
		  --line;
	      }
	    }
	    else {
	      if (line>0)
		--line;
	    }
	    xcas::eqw_select(eq.data,line,col,true,value);
	    if (doit) dx -= value._EQWptr->dx;
	  }
	  continue;
	}
	if (doit && key==KEY_SHIFT_LEFT){
	  dx -= 20;
	  continue;
	}
	if (key==KEY_CTRL_RIGHT  || (!doit && key==KEY_SHIFT_RIGHT)) {
	  if (line>=0 && xcas::eqw_select(eq.data,line,col,false,value)){
	    if (doit)
	      dx += value._EQWptr->dx;
	    if (col>=0){
	      ++col;
	      if (col==ncols){
		col=0;
		if (line<nlines-1)
		  ++line;
	      }
	    } else {
	      if (line<nlines-1)
		++line;
	    }
	    xcas::eqw_select(eq.data,line,col,true,value);
	  }
	  continue;
	}
	if (key==KEY_SHIFT_RIGHT && doit){
	  dx += 20;
	  continue;
	}
	doit=eqdata.dy>=LCD_HEIGHT_PX-2*margin;
	if (key==KEY_CTRL_UP || (!doit && key==KEY_CTRL_PAGEUP)){
	  if (line>0 && col>=0 && xcas::eqw_select(eq.data,line,col,false,value)){
	    --line;
	    xcas::eqw_select(eq.data,line,col,true,value);
	    if (doit)
	      dy += value._EQWptr->dy+eq.attr.fontsize/2;
	  }
	  continue;
	}
	if (key==KEY_CTRL_PAGEUP && doit){
	  dy += 10;
	  continue;
	}
	if (key==KEY_CTRL_DOWN  || (!doit && key==KEY_CTRL_PAGEDOWN)){
	  if (line<nlines-1 && col>=0 && xcas::eqw_select(eq.data,line,col,false,value)){
	    if (doit)
	      dy -= value._EQWptr->dy+eq.attr.fontsize/2;
	    ++line;
	    xcas::eqw_select(eq.data,line,col,true,value);
	  }
	  continue;
	}
	if ( key==KEY_CTRL_PAGEDOWN && doit){
	  dy -= 10;
	  continue;
	}
      }
      else { // else listormat
	if (key==KEY_CTRL_LEFT){
	  delta=xcas::eqw_select_leftright(eq,true,alph?2:0,contextptr);
	  // cout << "left " << delta << endl;
	  if (doit) dx += (delta?delta:-20);
	  continue;
	}
	if (key==KEY_SHIFT_LEFT){
	  delta=xcas::eqw_select_leftright(eq,true,1,contextptr);
	  vector<int> goto_sel;
	  if (doit) dx += (delta?delta:-20);
	  continue;
	}
	if (key==KEY_CTRL_RIGHT){
	  delta=xcas::eqw_select_leftright(eq,false,alph?2:0,contextptr);
	  // cout << "right " << delta << endl;
	  if (doit)
	    dx += (delta?delta:20);
	  continue;
	}
	if (key==KEY_SHIFT_RIGHT){
	  delta=xcas::eqw_select_leftright(eq,false,1,contextptr);
	  // cout << "right " << delta << endl;
	  if (doit)
	    dx += (delta?delta:20);
	  // dx=eqdata.dx-LCD_WIDTH_PX+20;
	  continue;
	}
	doit=eqdata.dy>=LCD_HEIGHT_PX-2*margin;
	if (key==KEY_CTRL_UP){
	  delta=xcas::eqw_select_up(eq.data);
	  // cout << "up " << delta << endl;
	  continue;
	}
	//cout << "up " << eq.data << endl;
	if (key==KEY_CTRL_PAGEUP && doit){
	  dy=eqdata.y+eqdata.dy+20;
	  continue;
	}
	if (key==KEY_CTRL_DOWN){
	  delta=xcas::eqw_select_down(eq.data);
	  // cout << "down " << delta << endl;
	  continue;
	}
	//cout << "down " << eq.data << endl;
	if ( key==KEY_CTRL_PAGEDOWN && doit){
	  dy=eqdata.y+LCD_HEIGHT_PX-margin;
	  continue;
	}
      }
      if (adds){
	edited=true;
	if (strcmp(adds,"'")==0)
	  adds="diff";
	if (strcmp(adds,"^2")==0)
	  adds="sq";
	if (strcmp(adds,">")==0)
	  adds="simplify";
	if (strcmp(adds,"<")==0)
	  adds="factor";
	if (strcmp(adds,"#")==0)
	  adds="partfrac";
	string cmd(adds);
	if (cmd.size() && cmd[cmd.size()-1]=='(')
	  cmd ='\''+cmd.substr(0,cmd.size()-1)+'\'';
	vector<int> goto_sel;
	if (xcas::Equation_adjust_xy(eq.data,xleft,ytop,xright,ybottom,gsel,gselparent,gselpos,&goto_sel) && gsel){
	  gen op;
	  int addarg=0;
	  if (addssize==1){
	    switch (adds[0]){
	    case '+':
	      addarg=1;
	      op=at_plus;
	      break;
	    case '^':
	      addarg=1;
	      op=at_pow;
	      break;
	    case '=':
	      addarg=1;
	      op=at_equal;
	      break;
	    case '-':
	      addarg=1;
	      op=at_binary_minus;
	      break;
	    case '*':
	      addarg=1;
	      op=at_prod;
	      break;
	    case '/':
	      addarg=1;
	      op=at_division;
	      break;
	    case '\'':
	      addarg=1;
	      op=at_derive;
	      break;
	    }
	  }
	  if (op==0)
	    op=gen(cmd,contextptr);
	  if (op.type==_SYMB)
	    op=op._SYMBptr->sommet;
	  // cout << "keyed " << adds << " " << op << " " << op.type << endl;
	  if (op.type==_FUNC){
	    edited=true;
	    // execute command on selection
	    gen tmp,value;
	    if (xcas::do_select(*gsel,true,value) && value.type==_EQW){
	      if (op==at_integrate || op==at_sum)
		addarg=3;
	      if (op==at_limit)
		addarg=2;
	      gen args=eval(value._EQWptr->g,1,contextptr);
	      gen vx=xthetat?t__IDNT_e:x__IDNT_e;
	      if (addarg==1)
		args=makesequence(args,0);
	      if (addarg==2)
		args=makesequence(args,vx_var,0);
	      if (addarg==3)
		args=makesequence(args,vx_var,0,1);
	      if (op==at_surd)
		args=makesequence(args,key==KEY_CHAR_CUBEROOT?3:4);
	      if (op==at_subst)
		args=makesequence(args,giac::symb_equal(vx_var,0));
	      unary_function_ptr immediate_op[]={*at_eval,*at_evalf,*at_evalc,*at_regrouper,*at_simplify,*at_normal,*at_ratnormal,*at_factor,*at_cfactor,*at_partfrac,*at_cpartfrac,*at_expand,*at_canonical_form,*at_exp2trig,*at_trig2exp,*at_sincos,*at_lin,*at_tlin,*at_tcollect,*at_texpand,*at_trigexpand,*at_trigcos,*at_trigsin,*at_trigtan,*at_halftan};
	      if (equalposcomp(immediate_op,*op._FUNCptr)){
		set_abort();
		tmp=(*op._FUNCptr)(args,contextptr);
		clear_abort();
		esc_flag=0;
		giac::ctrl_c=false;
		giac::interrupted=false;
	      }
	      else
		tmp=symbolic(*op._FUNCptr,args);
	      //cout << "sel " << value._EQWptr->g << " " << tmp << " " << goto_sel << endl;
	      esc_flag=0;
	      giac::ctrl_c=false;
	      giac::interrupted=false;
	      if (!is_undef(tmp)){
		xcas::replace_selection(eq,tmp,gsel,&goto_sel,contextptr);
		if (addarg){
		  xcas::eqw_select_down(eq.data);
		  xcas::eqw_select_leftright(eq,false,0,contextptr);
		}
		eqdata=xcas::Equation_total_size(eq.data);
		dx=(eqdata.dx-LCD_WIDTH_PX)/2;
		dy=LCD_HEIGHT_PX-2*margin+eqdata.y;
		firstrun=-1; // workaround, force 2 times display
	      }
	    }
	  }
	}
      }
    }
    //*logptr(contextptr) << eq.data << endl;
  }

#ifndef NO_NAMESPACE_XCAS
} // namespace xcas
#endif // ndef NO_NAMESPACE_XCAS


#endif // NUMWORKS
