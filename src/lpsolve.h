#ifndef __LPSOLVE_H
#define __LPSOLVE_H
#include "first.h"
#include "global.h"
#include "gen.h"
#include "unary.h"
#include "symbolic.h"

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

  gen simplex_twophase(const matrice & lh,vecteur & rel,vecteur & rh,vecteur & obj_orig,std::vector<int> & varsign,GIAC_CONTEXT);
  gen simplex_dual(const matrice & lh,vecteur & rel,vecteur & rh,vecteur & obj,GIAC_CONTEXT);
  int branch_and_bound(matrice & lh_orig,vecteur & rel_orig,vecteur & rh_orig,vecteur & obj_orig,
            std::vector<int> & vartype,vecteur & soln,std::vector<int> & varsign_orig,vecteur & incumbent,
            bool maximize,int depth,int depthlimit,GIAC_CONTEXT);
  bool is_realcons(const gen & g,GIAC_CONTEXT);
  bool lincomb_coeff(const gen & e_orig,const vecteur & v,vecteur & c,gen & r,GIAC_CONTEXT);
  bool interval2vecteur(const gen & g,vecteur & v,GIAC_CONTEXT);
  gen _lpsolve(const gen & args,GIAC_CONTEXT);

  extern const unary_function_ptr * const  at_lpsolve;

#ifndef NO_NAMESPACE_GIAC
} // namespace giac
#endif // ndef NO_NAMESPACE_GIAC
#endif // __LPSOLVE_H
