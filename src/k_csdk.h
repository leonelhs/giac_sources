/* C header for Khicas interface with calculator OS */
#ifndef K_CSDK_H
#define K_CSDK_H
#ifdef __cplusplus
extern "C" {
#endif
  int ext_main();
  bool waitforvblank();
  bool back_key_pressed() ;
  // next 3 functions may be void if not inside a window class hierarchy
  void os_show_graph(); // show graph inside Python shell (Numworks), not used
  void os_hide_graph(); // hide graph, not used anymore
  void os_redraw(); // force redraw of window class hierarchy
#ifdef NUMWORKS
  void numworks_set_pixel(int x,int y,int c);
  int numworks_get_pixel(int x,int y);
  void numworks_fill_rect(int x,int y,int w,int h,int c);
  int numworks_draw_string(int x,int y,int c,int bg,const char * s,bool fake=false);
  int numworks_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake=false);
  void numworks_show_graph();
  void numworks_hide_graph();
  void numworks_redraw();
  void numworks_wait_1ms(int ms);
  // access to Numworks OS, defined in port.cpp (or modkandinsky.cpp)
  inline void os_set_pixel(int x,int y,int c){
    numworks_set_pixel(x,y,c);
  }
  inline int os_get_pixel(int x,int y){
    return numworks_get_pixel(x,y);
  }
  inline void os_fill_rect(int x,int y,int w,int h,int c){
    numworks_fill_rect(x,y,w,h,c);
  }
  inline int os_draw_string(int x,int y,int c,int bg,const char * s,bool fake){
    return numworks_draw_string(x,y,c,bg,s,fake);
  }
  inline int os_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake){
    return numworks_draw_string_small(x,y,c,bg,s,fake);
  }
  inline void os_shaw_graph(){ return numworks_show_graph(); }
  inline void os_hide_graph(){ return numworks_hide_graph(); }
  inline void os_redraw(){ return numworks_redraw(); }
  inline void os_wait_1ms(int ms) { numworks_wait_1ms(ms); }
#endif // NUMWORKS

  bool os_set_angle_unit(int mode);
  int os_get_angle_unit();
  double millis(); //extern int time_shift;
  // void os_wait_1ms();
  bool file_exists(const char * filename);
  bool erase_file(const char * filename);
  const char * read_file(const char * filename);
  bool write_file(const char * filename,const char * s,size_t len=0);
#define MAX_NUMBER_OF_FILENAMES 255
  int os_file_browser(const char ** filenames,int maxrecords,const char * extension);
  void os_set_pixel(int x,int y,int c);
  void os_fill_rect(int x,int y,int w,int h,int c);
  inline void drawRectangle(int x,int y,int w,int h,int c){
    os_fill_rect(x,y,w,h,c);
  }
  int os_get_pixel(int x,int y);
  /* returns new x position */
  int os_draw_string(int x,int y,int c,int bg,const char * s,bool fake=false);
  inline int os_draw_string_(int x,int y,const char * s){ return os_draw_string(x,y,giac::_BLACK,giac::_WHITE,s);}
  int os_draw_string_small(int x,int y,int c,int bg,const char * s,bool fake=false);
  inline int os_draw_string_small_(int x,int y,const char * s){ return os_draw_string_small(x,y,giac::_BLACK,giac::_WHITE,s);}
  void GetKey(int * key);
  int getkey_raw(bool allow_suspend); // Numworks scan code
  int getkey(bool allow_suspend); // transformed
  void enable_back_interrupt();
  inline void set_abort(){  enable_back_interrupt(); }
  void disable_back_interrupt();
  inline void clear_abort(){  disable_back_interrupt(); }
  bool isalphaactive();
  bool alphawasactive();
  void lock_alpha();
  void reset_kbd();
  void statuslinemsg(const char * msg);
  void statusline(int mode=0);

#define COLOR_BLACK giac::_BLACK
#define COLOR_RED giac::_RED
#define COLOR_GREEN giac::_GREEN
#define COLOR_CYAN giac::_CYAN
#define COLOR_BLUE giac::_BLUE
#define COLOR_YELLOW giac::_YELLOW
#define COLOR_MAGENTA giac::_MAGENTA
#define COLOR_WHITE giac::_WHITE
#define COLOR_YELLOWDARK 64934
#define COLOR_BROWN 65000
#define TEXT_COLOR_BLACK giac::_BLACK
#define TEXT_COLOR_RED giac::_RED
#define TEXT_COLOR_GREEN giac::_GREEN
#define TEXT_COLOR_CYAN giac::_CYAN
#define TEXT_COLOR_BLUE giac::_BLUE
#define TEXT_COLOR_YELLOW giac::_YELLOW
#define TEXT_COLOR_WHITE giac::_WHITE
#define TEXT_COLOR_MAGENTA giac::_MAGENTA

  // Character codes
#define KEY_CHAR_0          0x30
#define KEY_CHAR_1          0x31
#define KEY_CHAR_2          0x32
#define KEY_CHAR_3          0x33
#define KEY_CHAR_4          0x34
#define KEY_CHAR_5          0x35
#define KEY_CHAR_6          0x36
#define KEY_CHAR_7          0x37
#define KEY_CHAR_8          0x38
#define KEY_CHAR_9          0x39
#define KEY_CHAR_DP         0x2e
#define KEY_CHAR_EXP        0x0f
#define KEY_CHAR_PMINUS     30200
#define KEY_CHAR_PLUS       43
#define KEY_CHAR_MINUS      45
#define KEY_CHAR_MULT       42
#define KEY_CHAR_DIV        47
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
#define KEY_SHIFT_ANS        0xc1
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
#define KEY_CHAR_FACTOR     0xda
#define KEY_CHAR_NORMAL     0xdb
#define KEY_CHAR_SHIFTMINUS     0xdc
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
#define KEY_CTRL_FORMAT     30203
#define KEY_CTRL_NOP        30202
#define KEY_CTRL_EXE        30201
#define KEY_CTRL_DEL        30025
#define KEY_CTRL_AC         30070
#define KEY_CTRL_FD         30046
#define KEY_CTRL_UNDO	    30045	
#define KEY_CTRL_XTT        30001
#define KEY_CTRL_EXIT       5
#define KEY_CTRL_OK       4
#define KEY_CTRL_SHIFT      30006
#define KEY_CTRL_ALPHA      30007
#define KEY_CTRL_OPTN       30008
#define KEY_CTRL_VARS       30030
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
#define KEY_CTRL_F7         30015
#define KEY_CTRL_F8         30016
#define KEY_CTRL_F9         30017
#define KEY_CTRL_F10         30018
#define KEY_CTRL_F11         30019
#define KEY_CTRL_F12         30020
#define KEY_CTRL_F13         30021
#define KEY_CTRL_F14         30022
#define KEY_CTRL_CATALOG    30100
#define KEY_CTRL_CAPTURE    30055
#define KEY_CTRL_CLIP       30050
#define KEY_CTRL_CUT       30250
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

#ifdef __cplusplus
}
#endif
#endif // K_CSDK_H
