// -*- mode:C++ ; compile-command: "g++ -I.. -g -c Equation.cc" -*-
#ifndef _KDISPLAY_H
#define _KDISPLAY_H
#ifdef NUMWORKS
#include "config.h"
#include "giacPCH.h"
#include "misc.h"

void numworks_giac_set_pixel(int x,int y,int c);
void numworks_giac_fill_rect(int x,int y,int w,int h,int c);
int numworks_giac_get_pixel(int x,int y);
void numworks_giac_draw_string(int x,int y,int c,int bg,const char * s);
inline void numworks_draw_string(int x,int y,const char * s){ numworks_giac_draw_string(x,y,giac::_BLACK,giac::_WHITE,s);}
void numworks_giac_draw_string_small(int x,int y,int c,int bg,const char * s);
inline void numworks_draw_string_small(int x,int y,const char * s){ numworks_giac_draw_string_small(x,y,giac::_BLACK,giac::_WHITE,s);}
void GetKey(int * key);
void enable_back_interrupt();
inline void set_abort(){  enable_back_interrupt(); }
void disable_back_interrupt();
inline void clear_abort(){  disable_back_interrupt(); }
void numworks_giac_show_graph();
void numworks_giac_hide_graph();
#define COLOR_BLACK _BLACK
#define COLOR_WHITE _WHITE
extern  const int LCD_WIDTH_PX;
extern   const int LCD_HEIGHT_PX;

#define STATUS_AREA_PX 0 // 24
// Character codes
#define KEY_CHAR_0          0x30
#define KEY_CHAR_1          30
#define KEY_CHAR_2          31
#define KEY_CHAR_3          32
#define KEY_CHAR_4          36
#define KEY_CHAR_5          37
#define KEY_CHAR_6          38
#define KEY_CHAR_7          42
#define KEY_CHAR_8          43
#define KEY_CHAR_9          44
#define KEY_CHAR_DP         0x2e
#define KEY_CHAR_EXP        0x0f
#define KEY_CHAR_PMINUS     46
#define KEY_CHAR_PLUS       45
#define KEY_CHAR_MINUS      46
#define KEY_CHAR_MULT       39
#define KEY_CHAR_DIV        40
#define KEY_CHAR_FRAC       0xbb
#define KEY_CHAR_LPAR       0x28
#define KEY_CHAR_RPAR       0x29
#define KEY_CHAR_COMMA      0x2c
#define KEY_CHAR_STORE      0x0e
#define KEY_CHAR_LOG        0x95
#define KEY_CHAR_LN         0x85
#define KEY_CHAR_SIN        0x81
#define KEY_CHAR_COS        0x82
#define KEY_CHAR_TAN        0x83
#define KEY_CHAR_SQUARE     0x8b
#define KEY_CHAR_POW        0xa8
#define KEY_CHAR_IMGNRY     0x7f50
#define KEY_CHAR_LIST       0x7f51
#define KEY_CHAR_MAT        0x7f40
#define KEY_CHAR_EQUAL      0x3d
#define KEY_CHAR_PI         0xd0
#define KEY_CHAR_ANS        0xc0
#define KEY_CHAR_LBRCKT     0x5b
#define KEY_CHAR_RBRCKT     0x5d
#define KEY_CHAR_LBRACE     0x7b
#define KEY_CHAR_RBRACE     0x7d
#define KEY_CHAR_CR         0x0d
#define KEY_CHAR_CUBEROOT   0x96
#define KEY_CHAR_RECIP      0x9b
#define KEY_CHAR_ANGLE      0x7f54
#define KEY_CHAR_EXPN10     0xb5
#define KEY_CHAR_EXPN       0xa5
#define KEY_CHAR_ASIN       0x91
#define KEY_CHAR_ACOS       0x92
#define KEY_CHAR_ATAN       0x93
#define KEY_CHAR_ROOT       0x86
#define KEY_CHAR_POWROOT    0xb8
#define KEY_CHAR_SPACE      0x20
#define KEY_CHAR_DQUATE     0x22
#define KEY_CHAR_VALR       0xcd
#define KEY_CHAR_THETA      0xce
#define KEY_CHAR_A          0x41
#define KEY_CHAR_B          0x42
#define KEY_CHAR_C          0x43
#define KEY_CHAR_D          0x44
#define KEY_CHAR_E          0x45
#define KEY_CHAR_F          0x46
#define KEY_CHAR_G          0x47
#define KEY_CHAR_H          0x48
#define KEY_CHAR_I          0x49
#define KEY_CHAR_J          0x4a
#define KEY_CHAR_K          0x4b
#define KEY_CHAR_L          0x4c
#define KEY_CHAR_M          0x4d
#define KEY_CHAR_N          0x4e
#define KEY_CHAR_O          0x4f
#define KEY_CHAR_P          0x50
#define KEY_CHAR_Q          0x51
#define KEY_CHAR_R          0x52
#define KEY_CHAR_S          0x53
#define KEY_CHAR_T          0x54
#define KEY_CHAR_U          0x55
#define KEY_CHAR_V          0x56
#define KEY_CHAR_W          0x57
#define KEY_CHAR_X          0x58
#define KEY_CHAR_Y          0x59
#define KEY_CHAR_Z          0x5a


// Control codes
#define KEY_CTRL_NOP        0
#define KEY_CTRL_EXE        52
#define KEY_CTRL_DEL        30025
#define KEY_CTRL_AC         30015
#define KEY_CTRL_FD         30046
#define KEY_CTRL_UNDO	    30045	
#define KEY_CTRL_XTT        30001
#define KEY_CTRL_EXIT       5
#define KEY_CTRL_OK       4
#define KEY_CTRL_SHIFT      30006
#define KEY_CTRL_ALPHA      30007
#define KEY_CTRL_OPTN       30008
#define KEY_CTRL_VARS       30016
#define KEY_CTRL_UP         1
#define KEY_CTRL_DOWN       2
#define KEY_CTRL_LEFT       0
#define KEY_CTRL_RIGHT      3
#define KEY_CTRL_F1         30009
#define KEY_CTRL_F2         30010
#define KEY_CTRL_F3         30011
#define KEY_CTRL_F4         30012
#define KEY_CTRL_F5         30013
#define KEY_CTRL_F6         30014
#define KEY_CTRL_F7         30014
#define KEY_CTRL_F14         30014
#define KEY_CTRL_CATALOG    30100
#define KEY_CTRL_CAPTURE    30055
#define KEY_CTRL_CLIP       30050
#define KEY_CTRL_PASTE      30036
#define KEY_CTRL_INS        30033
#define KEY_CTRL_MIXEDFRAC  30054
#define KEY_CTRL_FRACCNVRT  30026
#define KEY_CTRL_QUIT       30029
#define KEY_CTRL_PRGM       30028
#define KEY_CTRL_SETUP      30037
#define KEY_CTRL_PAGEUP     30052
#define KEY_CTRL_PAGEDOWN   30053
#define KEY_CTRL_MENU       30003
#define KEY_SHIFT_OPTN	    30059
#define KEY_CTRL_RESERVE1	30060
#define KEY_CTRL_RESERVE2	30061
#define KEY_SHIFT_LEFT		30062
#define KEY_SHIFT_RIGHT		30063

#define KEY_PRGM_ACON 10
#define KEY_PRGM_DOWN 37
#define KEY_PRGM_EXIT 47
#define KEY_PRGM_F1 79
#define KEY_PRGM_F2 69
#define KEY_PRGM_F3 59
#define KEY_PRGM_F4 49
#define KEY_PRGM_F5 39
#define KEY_PRGM_F6 29
#define KEY_PRGM_LEFT 38
#define KEY_PRGM_NONE 0
#define KEY_PRGM_RETURN 31
#define KEY_PRGM_RIGHT 27
#define KEY_PRGM_UP 28
#define KEY_PRGM_1 72
#define KEY_PRGM_2 62
#define KEY_PRGM_3 52
#define KEY_PRGM_4 73
#define KEY_PRGM_5 63
#define KEY_PRGM_6 53
#define KEY_PRGM_7 74
#define KEY_PRGM_8 64
#define KEY_PRGM_9 54
#define KEY_PRGM_A 76
#define KEY_PRGM_F 26
#define KEY_PRGM_ALPHA 77 
#define KEY_PRGM_SHIFT 78
#define KEY_PRGM_MENU 48


#ifndef NO_NAMESPACE_XCAS
namespace xcas {
#endif // ndef NO_NAMESPACE_XCAS

  // maximum "size" of symbolics displayed in an Equation (pretty print)
  extern unsigned max_prettyprint_equation;
  // matrix select
  bool eqw_select(const giac::gen & eq,int l,int c,bool select,giac::gen & value);
  void Equation_select(giac::gen & eql,bool select);
  int eqw_select_down(giac::gen & g);
  int eqw_select_up(giac::gen & g);

  giac::gen Equation_compute_size(const giac::gen & g,const giac::attributs & a,int windowhsize,const giac::context * contextptr);
  giac::eqwdata Equation_total_size(const giac::gen & g);  
  // Equation_translate(giac::gen & g,int deltax,int deltay);
  void Equation_vertical_adjust(int hp,int yp,int & h,int & y);
  bool Equation_find_vector_pos(giac::const_iterateur it,giac::const_iterateur itend,int & i,int &nrows);
  bool Equation_adjust_xy(giac::gen & g,int & xleft,int & ytop,int & xright,int & ybottom,giac::gen * & gsel,giac::gen * & gselparent,int &gselpos,std::vector<int> * gotosel=0);
  // select and set value from eqwdata in eql
  bool do_select(giac::gen & eql,bool select,giac::gen & value);

  class Equation {
    int _x,_y;
  public:
    giac::gen data,undodata; // of type eqwdata or undef if empty
    giac::attributs attr;
    const giac::context * contextptr;
    int x() const { return _x;}
    int y() const { return _y;}
    Equation(int x_, int y_, const giac::gen & g,const giac::context *);
  };

  void display(Equation &eq ,int x,int y,const giac::context *);
  // replace selection in eq by tmp
  void replace_selection(Equation & eq,const giac::gen & tmp,giac::gen * gsel,const std::vector<int> * gotoptr,const giac::context *);
  int eqw_select_leftright(xcas::Equation & g,bool left,int exchange,const giac::context *);

  class Graph2d{
  public:
    double window_xmin,window_xmax,window_ymin,window_ymax,
      x_scale,y_scale,x_tick,y_tick;
    int display_mode,show_axes,show_names,labelsize;
    giac::gen g;
    const giac::context * contextptr;
    bool findij(const giac::gen & e0,double x_scale,double y_scale,double & i0,double & j0,const giac::context * ) const;
    void update();
    void zoomx(double d,bool round=false);
    void zoomy(double d,bool round=false);
    void zoom(double);
    void left(double d);
    void right(double d);
    void up(double d);
    void down(double d);
    void autoscale(bool fullview=false);
    void orthonormalize();
    void draw();
    Graph2d(const giac::gen & g_,const giac::context * );
  };

  struct Turtle {
    void draw();
#ifdef TURTLETAB
    giac::logo_turtle * turtleptr;
#else
    std::vector<giac::logo_turtle> * turtleptr;
#endif
    int turtlex,turtley; // Turtle translate
    double turtlezoom; // Zoom factor for turtle screen
    int maillage; // 0 (none), 1 (square), 2 (triangle), bit3 used for printing
  };
  
  void displaygraph(const giac::gen & ge, const giac::context * contextptr);
  void displaylogo();
  giac::gen eqw(const giac::gen & ge,bool editable,const giac::context * contextptr);
#ifndef NO_NAMESPACE_XCAS
} // namespace xcas
#endif // ndef NO_NAMESPACE_XCAS

#ifndef NO_NAMESPACE_XCAS
namespace giac {
#endif // ndef NO_NAMESPACE_XCAS
  gen turtle_state(const giac::context * contextptr);
#ifndef NO_NAMESPACE_XCAS
} // namespace giac
#endif // ndef NO_NAMESPACE_XCAS

#endif // _KDISPLAY_H
#endif
