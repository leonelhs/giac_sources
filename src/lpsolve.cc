/*
 * lpsolve.cc
 * 
 * Copyright 2017 Luka Marohnić
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 * Sample LP problems for testing
 * ==============================
 * 
 * 1) Maximize
 * 
 *  z = -3x1 + 2x2 - x3 + 4x4
 * 
 *  subject to:
 * 
 *       x1 + x2 - 4x3 + 2x4 ≥  4,
 *     -3x1 + x2 - 2x3       ≤  6,
 *            x2       -  x4 = -1,
 *       x1 + x2 -  x3       =  0,
 *                  x3,   x4 ≥  0.
 * 
 * 
 * 2) Minimize or maximize
 * 
 *  z =   28x11 + 84x12 + 112x13 + 112x14 + 60x21 + 20x22
 *      + 50x23 + 50x24 +  96x31 +  60x32 + 24x33 + 60x34
 *      + 64x41 + 40x42 +  40x43 +  16x44 + 50y1  + 50y2
 *      + 50y3  + 50y4
 *
 *  subject to:
 *
 *       x11 + x12 + x13 + x14       = 1,
 *       x21 + x22 + x23 + x24       = 1,
 *       x31 + x32 + x33 + x34       = 1,
 *       x41 + x42 + x43 + x44       = 1,
 *      -x11 - x21 - x31 - x41 + 4y1 ≥ 0,
 *      -x12 - x22 - x32 - x42 + 4y2 ≥ 0,
 *      -x13 - x23 - x33 - x43 + 4y3 ≥ 0,
 *      -x14 - x24 - x34 - x44 + 4y4 ≥ 0,
 *                           xij, zi ∈ {0,1} for all i,j=1,2,3,4.
 * 
 * 
 * 3) (from cascmd_fr) Minimize
 * 
 *  z = 2x + y - z + 4
 * 
 *  subject to:
 * 
 *       x          ≤ 1,
 *            y     ≥ 2,
 *       x + 3y - z = 2,
 *      2x -  y + z ≤ 8,
 *      -x +  y     ≤ 5.
 * 
 * 
 * 4) The problem of putting as much queens as possible on an 8x8 chessboard so that they don't threat each other.
 * 
 * Maximize
 *   c.x,
 *   where c = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
 * subject to:
 *   A.x<=b
 *   where A = [[1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1],[1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0],[0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0],[0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0],[0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0],[0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0],[0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0],[0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1],[1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1],[0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0],[0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0]]
 *   and   b = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
 *      (42 constraints in total)
 *   64 decision variables x=(x11,x12,...,x18,x21,x22,...,x28,...,x81,x82,...,x88), all binary
 *      xij=1 if there is a queen on field in ith row and jth column of a chessboard, xij=0 if the field is empty
 */
#include "giacPCH.h"
using namespace std;
#include "lpsolve.h"
#include "giac.h"

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

  /*
   * Function 'simplex_twophase' determines the optimal solution (if one
   * exists) to the general type of maximization LP-problem in matrix form,
   * with continuous variables. It has five arguments. First three arguments
   * specify constraints, the fourth specifies the objective function and
   * the fifth specifies which variables are nonnegative and which are
   * unrestricted in sign.
   * 
   *   1) lh: matrix in which the ith row defines coefficients of
   *       the lhs of the ith constraint
   *   2) rel: vector whose ith component specifies the relation between
   *       lhs and rhs of the ith constraint. It is equal to -1 for
   *      the less-or-equal relation, 0 for equality and 1 for the
   *      greater-or-equal relation
   *   3) rh: vector whose ith component is equal to the rhs of
   *      the ith constraint (a numerical constant)
   *   4) obj_orig: vector of coefficients of the objective function)
   *   5) varsign: vector of integers, ith component is 1 iff ith
   *      decision variable is nonnegative, -1 if not positive and 0 if unrestricted
   * 
   * The optimal solution, if one exists, is found by applying the two-phase
   * simplex method. For each <= constraint a slack variable is added and
   * for each >= constraint a surplus variable is added. Then the artificial
   * variables are introduced for >= and = constraints.
   * The first run of the simplex method (phase I) is used to minimize sum of
   * the artificial variables to zero (hence making them all equal to zero).
   * Then, artificial variables are removed and the simplex method is run
   * again on the initial feasible solution to the original problem, which
   * is obtained from the reduced matrix provided by phase I.
   * 
   * This function can also be used to solve minimization LP-problem: a
   * solution is obtained by changing the sign of the objective function
   * and maximizing the latter.
   * 
   * Function returns a list with two elements: the maximum value of the objective
   * function and the optimal solution as a list containing optimal values
   * of the decision variables. If no feasible solution exists return an empty
   * list. If the objective function is unbounded, the return value is [+infinity,[...]]
   * (solution point may be given, but generally it is meaningless).
   */
  gen simplex_twophase(const matrice & lh,vecteur & rel,vecteur & rh,vecteur & obj_orig,vector<int> & varsign,GIAC_CONTEXT) {
    matrice m(lh);
    vecteur b(rh),r(rel),obj(obj_orig),br,soln;
    gen optimum;
    int nc=int(lh.size());  // total number of given constraints
    int nv=int(obj.size());  // total number of decision variables
    // Create matrix m with the constraints such that every one with negative
    // rhs is first multiplied by -1, which also affects vectors b and r.
    // Thus we get nonnegative vector b, required by simplex_reduce.
    for (int i=0;i<nc;++i) {
      if (!is_positive(rh[i],contextptr)) {
        m[i]=-m[i];
        r[i]=-r[i];
        b[i]=-b[i];
      }
    }
    m=mtran(m);
    // turn not-positive variables to nonnegative
    for (int i=0;i<nv;++i) {
      if (varsign[i]<0) {
        obj[i]=-obj[i];
        m[i]=-m[i];
      }
    }
    // replace unrestricted variables with the difference of two nonnegative variables
    for (int i=nv-1;i>=0;--i) {
      if (varsign[i]==0) {
        m.insert(m.begin()+i,-*m[i]._VECTptr);
        obj.insert(obj.begin()+i,-obj[i]);
      }
    }
    nv=int(obj.size());  // update number of variables
    // Create columns for slack, surplus and artifical variables.
    // Also, append column b (vector of rhs) at the end.
    matrice mi(midn(nc));
    vector<int> art;
    int ns=0,na=0;  // total number of slack/surplus resp. artificial variables
    for (int i=0;i<nc;++i) {
      bool needs_art=is_positive(r[i],contextptr);  // an artificial variable needs to be added
      if (!is_zero(r[i])) {
        // append slack/surplus variable column
        m.push_back(needs_art ? -mi[i] : mi[i]);
        ns++;
      }
      if (needs_art) {
        art.push_back(i);
        na++;
      }
    }
    // append columns for artificial variables
    for (vector<int>::const_iterator it=art.begin();it!=art.end();++it) {
      m.push_back(mi[*it]);
    }
    m.push_back(b);  // column of rhs (the last one)
    m=mtran(m);
    if (na==0) {
      // there are no artificial variables, i.e. the problem is in canonical form
      m.push_back(mergevecteur(-obj,vecteur(ns+na+1,0)));  // add bottom row
      m=simplex_reduce(m,soln,optimum,true,false,contextptr);  // optimize
    }
    else {
      // There is at least one artificial variable introduced, so we proceed
      // with the two phase method.
      // create bottom row for maximization of -sum(art), which needs to be zero
      br=mergevecteur(vecteur(nv+ns,0),vecteur(na,1));
      br.push_back(gen(0));
      // make zeros in columns of artificial variables (pivot, actually)
      for (vector<int>::const_iterator it=art.begin();it!=art.end();++it) {
        br=subvecteur(br,*m[*it]._VECTptr);
      }
      m.push_back(br);
      // run phase I
      m=simplex_reduce(m,soln,optimum,true,false,contextptr);
      if (!is_zero(optimum))
        // no feasible solution exists
        return vecteur (0);
      // ----------
      // * PHASE II
      // ----------
      vector<int> basis_cols;
      vector<int> basis_rows;
      vector<bool> found(nc+1,false);  // found[i] becomes true when ith column of idn is found
      vector<bool> row_active(nc+1,true);  // a row is inactive when the corresponding constraint is tautologic (0=0)
      for (int j=0;j<nv+ns+na;++j) {
        int I=-1;
        // check if jth column is an idn column, i.e. that jth variable is in the basis
        for (int i=0;i<nc+1;++i) {
          if (!is_zero(m[i][j])) {
            if (I>=0) {
              I=-1;
              break;
            }
            I=i;
          }
        }
        if (I==-1 || found[I] || !is_one(m[I][j]))  // jth variable not in basis, skip
          continue;
        // jth variable is in the basis
        found[I]=true;  // remember which idn columns have been found so far
        if (j>=nv+ns) {  // jth variable is artificial, it must be pushed out of the basis
          int k=0;
          for (;k<nv+ns && is_zero(m[I][k]);++k);
          if (k<nv+ns) {  // kth variable entering the basis, jth leaving
            m[I]=divvecteur(*m[I]._VECTptr,m[I][k]);
            vecteur & pivot_v = *m[I]._VECTptr;
            gen a;
            for (int i=0;i<nc+1;++i) {
              if (i==I)
                continue;
              vecteur & v=*m[i]._VECTptr;
              a=v[k];
              for (int J=0;J<nv+ns+na+1;++J) {
                v[J]=v[J]-a*pivot_v[J];
              }
            }
            basis_cols.push_back(k);
            basis_rows.push_back(I);
          }
          else  // mark Ith row inactive
            row_active[I]=false;
        }
        else {
          basis_cols.push_back(j);
          basis_rows.push_back(I);
        }
      }
      // remove the artificial variables columns
      m=mtran(m);
      m.erase(m.begin()+nv+ns,m.end()-1);
      m=mtran(m);
      // remove the last row
      m.pop_back();
      // append bottom row for maximizing the objective function
      br=mergevecteur(-obj,vecteur(ns+1,0));
      for (int k=0;k<int(basis_cols.size());++k) {
        int i=basis_rows[k],j=basis_cols[k];
        br=subvecteur(br,multvecteur(br[j],*m[i]._VECTptr));
      }
      m.push_back(br);
      // remove inactive rows
      for (int i=nc;i>=0;--i) {  // from bottom to top
        if (!row_active[i])
          m.erase(m.begin()+i);
      }
      // run phase II
      m=simplex_reduce(m,soln,optimum,true,false,contextptr);
    }
    if (int(soln.size())>0) {
      // calculate optimal values for given decision variables
      soln.resize(nv);  // drop slack/surplus variables from solution
      int i=0;
      for (vector<int>::const_iterator it=varsign.begin();it!=varsign.end();++it) {
        switch (*it) {
        case 0:
          soln[i+1]-=soln[i];
          soln.erase(soln.begin()+i);
          break;
        case -1:
          soln[i]=-soln[i];
          break;
        }
        ++i;
      }      
    }
    return makevecteur(optimum,soln);
  }

  /* 
   * Function 'simplex_dual' is used to solve a LP-problem in which a nonnegative
   * objective function needs to be minimized. The input arguments are the same
   * as in function 'simplex_twophase' above, with requirement that the coefficients
   * of the objective function (i.e. the components of fourth input argument), as
   * well as the decision variables, are all nonnegative. Thus, the dual problem
   * is a LP maximization problem which is in canonical form, so it can be
   * optimized by a single call of 'simplex_reduce'.
   * 
   * This function is intended to be a faster variant for solving minimization
   * problem with a nonnegative objective function. Namely, it requires only
   * one run of the simplex algorithm, while the function 'simplex_twophase', which can also
   * solve the problem, will run the algorithm twice, as it implements the two-
   * phase method.
   * 
   * Function returns the optimal solution of the given LP minimization problem as a
   * list with two elements: the minimum value of the objective function and
   * list of the optimal values of decision variables. If no feasible solution
   * exists, an empty list is returned.
   */
  gen simplex_dual(const matrice & lh,vecteur & rel,vecteur & rh,vecteur & obj,GIAC_CONTEXT) {
    matrice m(lh);
    vecteur r(rel),b(rh);
    int nc=int(lh.size());  // number of constraints
    int nv=int(obj.size());  // number of variables
    // turn every constraint into the equivalent form using relation >=
    for (int i=0;i<nc;++i) {
      if (is_minus_one(r[i])) {
        m[i]=-m[i];
        b[i]=-b[i];
      }
      else if (is_zero(r[i])) {
        // equation constraints are replaced with two inequalities,
        // append the second one
        m.push_back(-m[i]);
        b.push_back(-b[i]);
      }
    }
    nc=int(m.size());  // refresh total number of constraints
    // create the initial tableau for the dual maximization problem
    m=mergevecteur(m,midn(nv));
    m.push_back(obj);
    m=mtran(m);
    m.push_back(mergevecteur(-b,vecteur(nv+1,0)));
    // apply the simplex method
    vecteur soln;
    gen optimum;
    m=simplex_reduce(m,soln,optimum,true,false,contextptr);
    if (soln.size()==0)  // no feasible solution exists, return an empty list
      return vecteur(0);
    // get optimal values of the decision variables and objective function
    // of the primal problem from the last row of the reduced matrix m
    soln=*m[nv]._VECTptr;
    soln.erase(soln.begin(),soln.begin()+nc);
    optimum=soln.back();
    soln.pop_back();
    return makevecteur(optimum,soln);
  }


  /* 
   * Function 'branch_and_bound' applies branch & bound method to solve an (mixed) integer
   * linear programming problem (MIP). The problem is specified by the first
   * four arguments, which are the same as in functions 'simplex_twophase' and 'simplex_dual'.
   * Other arguments are:
   * 
   *   5) vartype (vector of integers): ith component determines the type of the ith
   *      decision variable: 0 - continuous, 1 - integer
   *   6) soln (vector): solution to the relaxed LP-problem which is
   *      not integer-valued
   *   7) varsign_orig (vector of integers): ith component is 1 if the ith
   *      decision variable is nonnegative, -1 if not positive and 0 if unrestricted
   *   8) incumbent (vector): the most optimal integer solution to the given
   *      problem found so far. This vector is modified in place during the
   *      iterations of the branch & bound method and holds the optimal solution to
   *      the given ILP after the function returns.
   *      If no feasible integer solution exists, this vector will be empty.
   *   9) maximize (boolean): this should be set to true for maximization problems
   *      and to false for problems in which the nonnegative objective function is
   *      minimized, i.e. those which can be solved by the function 'simplex_dual'.
   *      It makes solving faster in the latter case.
   *  10) depth (nonnegative integer): current depth of the binary tree created
   *      recursively by the branch & bound method.
   *  11) depthlimit (nonnegative integer): when optimizing (mixed) integer linear
   *      programs, the branch & bound tree will not be deeper than 'depthlimit'.
   *      As a consequence, the number of recursive calls to 'branch_and_bound' will be limited.
   *      If this parameter is set, the final solution may not be the optimal one.
   * 
   * At every node, index k of the component x*_k of the noninteger solution 'soln'
   * which has fractional part closest to 1/2 is determined. Then branching is done
   * with respect to the decision variable x_k: first branch gets additional constraint
   * x_k>=ceil(x*_k) and the second branch gets additional constraint x_k<=floor(x*_k).
   * Thus the branches represent LP-subproblems, which are solved by using either 'lmpax' if
   * argument 'maximize' is true or 'simplex_dual' if 'maximize' is false. A branch is pruned when
   * 
   *   - the solution of corresponding subproblem is integer-valued where required,
   *     in which case the incumbent solution is possibly improved, or
   *   - the maximum/minimum value of the objective function with respect to the
   *     corresponding subproblems' constraints is smaller/greater or equal to the
   *     maximum/minimum objective value with respect to the current incumbent solution.
   *     Therefore, no further optimization is possible within this branch.
   * 
   * The function 'branch_and_bound' is then called recursively on the branches that were
   * not pruned, possibly improving the incumbent solution.
   * 
   * Function returns number of examined nodes in the tree produced by recursion. Nodes
   * which are in pruned branches are not counted.
   */
  int branch_and_bound(matrice & lh_orig,vecteur & rel_orig,vecteur & rh_orig,vecteur & obj_orig,
                       vector<int> & vartype,vecteur & soln,vector<int> & varsign_orig,vecteur & incumbent,
                       bool maximize,int depth,int depthlimit,GIAC_CONTEXT) {
    if (depthlimit>0 && depth>depthlimit)
      // maximum tree depth reached, stop
      return 0;
    int nv=int(obj_orig.size());  // number of variables
    // find k such that kth component of the solution is farthest from the
    // nearest whole number, search only components which are required to be integer
    int k=-1;
    gen xi,f,min_f(0);
    for (int i=0;i<nv;++i) {
      if (vartype[i]==0)
        // ith variable is continuous, skip
        continue;
      xi=soln[1][i];
      f=_abs(xi-_round(xi,contextptr),contextptr);  // distance from the nearest whole number
      if (is_strictly_greater(f,min_f,contextptr)) {
        k=i;
        min_f=f;
      }
    }
    if (k<0)  // there is no variable to branch on
      return 0;
    vector<int> nxt;
    vecteur solnv(2);
    gen xk=soln[1][k];
    vecteur bounds=makevecteur(_ceil(xk,contextptr),_floor(xk,contextptr));
    vector< vector<int> > varsign(2,varsign_orig);
    vecteur obj=makevecteur(obj_orig,obj_orig),
            lh=makevecteur(lh_orig,lh_orig),
            rel=makevecteur(rel_orig,rel_orig),
            rh=makevecteur(rh_orig,rh_orig);
    // formulate and solve two subproblems
    matrice mi(midn(nv));
    for (int i=0;i<2;++i) {
      vecteur &lhi=*lh[i]._VECTptr,&obji=*obj[i]._VECTptr,&reli=*rel[i]._VECTptr,&rhi=*rh[i]._VECTptr;
      vector<int> & varsigni = varsign[i];
      if (maximize) {
        if (i==0 && is_positive(bounds[0],contextptr))
          // kth variable is nonnegative
          varsigni[k]=1;
        if (i==1 && !is_strictly_positive(bounds[1],contextptr))
          // kth variable is not positive
          varsigni[k]=-1;
      }
      lhi.push_back(mi[k]);
      reli.push_back(gen(1-2*i));
      rhi.push_back(bounds[i]);
      solnv[i]=maximize ? simplex_twophase(lhi,reli,rhi,obji,varsigni,contextptr) : simplex_dual(lhi,reli,rhi,obji,contextptr);
      if (int(solnv[i]._VECTptr->size())==0 || _abs(solnv[i][0],contextptr)==plus_inf)
        // no feasible solution, pruning branch
        continue;
      if (int(incumbent.size())>0) {
        gen z=incumbent[0],zi=solnv[i][0];
        if ((!maximize && is_greater(zi,z,contextptr)) || (maximize && is_greater(z,zi,contextptr)))
          // no improvement of the incumbent solution is possible within this branch, pruning it
          continue;
      }
      // check if required variables have integer values: the sum of
      // their fractional parts should be equal to zero
      gen f(0),xj;
      for (int j=0;j<nv;++j) {
        xj=solnv[i][1][j];
        if (vartype[j]==1)
          f+=_abs(xj-_round(xj,contextptr),contextptr);
      }
      if (is_zero(_recursive_normal(f,contextptr)))  // update incumbent solution
        incumbent=vecteur(*exact(*solnv[i]._VECTptr,contextptr)._VECTptr);
      else  // mark this branch for further searching
        nxt.push_back(i);
    }
    // start with the branch that has higher maximum (when maximize=true) i.e. lower
    // minimum (when maximize=false) for the objective function, speeding up the algorithm
    if (nxt.size()==2) {
      // upper(maximize=true) i.e. lower(maximize=false) bounds of the objective functions in branches
      gen z1=solnv[0][0],z2=solnv[1][0];
      // compare z1,z2 and reverse nxt if necessary (branch in the front will be examined first)
      if ((maximize && is_strictly_greater(z2,z1,contextptr)) || (!maximize && is_strictly_greater(z1,z2,contextptr)))
        reverse(nxt.begin(),nxt.end());
    }
    // test marked branches recursively and count the examined nodes of the branch&bound tree
    int node_count=1;
    for (vector<int>::const_iterator it=nxt.begin();it!=nxt.end();++it) {
      node_count+=branch_and_bound(
        *lh[*it]._VECTptr,*rel[*it]._VECTptr,*rh[*it]._VECTptr,*obj[*it]._VECTptr,vartype,
        *solnv[*it]._VECTptr,varsign[*it],incumbent,maximize,depth+1,depthlimit,contextptr);
    }
    // return the total number of nodes in the b&b tree (not counting ones from pruned branches)
    return node_count;
  }
  
  /*
   * Return true iff g is a real constant or +/-infinity or a vector of those.
   */
  bool is_realcons(const gen & g,GIAC_CONTEXT) {
    if (g.type==_VECT) {
      vecteur & v = *g._VECTptr;
      for (vecteur::const_iterator it=v.begin();it!=v.end();++it) {
        if (!is_realcons(*it,contextptr))
          return false;
      }
      return true;
    }
    return (_abs(g,contextptr)==plus_inf || _evalf(g,contextptr).type==_DOUBLE_);
  }
  
  /*
   * Function 'lincomb_coeff' accepts exactly four arguments:
   * 
   *   1) e_orig: a symbolic expression that is supposed to be a linear
   *      combination of variables in the second argument
   *   2) v: vector of variables
   *   3) c: vector of coefficients
   *   4) r: the constant term
   * 
   * If the given symbolic expression is linear, vector c is filled with 
   * coefficients of the linear combination. For example, if
   * e_orig = 5x + 2y - 3z, and v=[x,y,z], then c would be equal to [5,2,-3].
   * The order of coefficients is the same as the order of matching variables
   * in vector v. The argument r represents the constant term. If the given
   * expression is not a linear combination with numerical coefficients,
   * function returns false.
   */
  bool lincomb_coeff(const gen & e_orig,const vecteur & v,vecteur & c,gen & r,GIAC_CONTEXT) {
    gen e(e_orig),a;
    c=vecteur(0);
    for (vecteur::const_iterator it=v.begin();it!=v.end();++it) {
      a=gen(0);
      if (is_constant_wrt(e,*it,contextptr) || (is_linear_wrt(e,*it,a,e,contextptr) && is_realcons(a,contextptr)))
        c.push_back(a);
      else return false;
    }
    return is_realcons(r=e,contextptr);
  }
  
  /*
   * If g is an interval, fill vector v with corresponding bounds.
   * Else return false and leave v untouched. Return true iff the bounds
   * are real constants.
   */
  bool interval2vecteur(const gen & g,vecteur & v,GIAC_CONTEXT) {
    if (g.type!=_SYMB || !g.is_symb_of_sommet(at_interval))
      return false;  // g is not an interval
    v=*g._SYMBptr->feuille._VECTptr;
    return is_realcons(v,contextptr);
  }
  
  /*
   * For vectors v and vars of identifiers, return vector w of integers such
   * that w[i] is the index of v[i] in the vector vars. If v is a vector of
   * integers, return vector of that values converted to ints.
   */
  vector<int> findvars(const vecteur & v, const vecteur & vars) {
    vector<int> indexes;
    for (vecteur::const_iterator it=v.begin();it!=v.end();++it) {
      if ((*it).type==_IDNT) {
        // the variable is specified as an identifier
        // find its index in 'vars'
        int i=0;
        for (;i<vars.size();++i) {
          if (vars[i]==*it) {
            indexes.push_back(i);
            break;
          }
        }
      }
      else if (is_integer(*it))
        // the variable is already specified as an index
        indexes.push_back(int((*it).val)-1);
    }
    return indexes;
  }
  
  /*
   * Function 'lpsolve' solves a (mixed integer/binary) LP problem in
   * general form. It is used as follows:
   * 
   *   lpsolve (obj, constr, bd, opts)
   * 
   * Parameters:
   * 
   *   obj    - (mandatory) linear objective function (it is allowed to have a constant term)
   *   constr - (optional) list of linear constraints
   *   bd     - (optional) bounds for one or more variables
   *   opts   - (optional) equation(s) of the form 'option=value', where
   *            'option' is one of: 'assume', 'lp_variables', 'lp_integervariables,
   *            'lp_binaryvariables', 'lp_maximize' or 'lp_depthlimit'
   * 
   * The problem may be given in symbolic form or in matrix form. The objective
   * function may be given as symbolic expression (including an optional constant
   * term) and the constraints as equations and inequalities. Also, a constraint
   * may be given in form 'Expr=a..b', where Expr is a linear expression and a,b
   * are real constants (possibly +/-infinity).
   * 
   * It is also possible to enter constraints of type 'Expr ∈ [a,b]' as 'Expr=a..b',
   * where Expr is a linear expression and a, b are real numbers.
   * 
   * For problems given in matrix form, the parameter 'obj' is a vector c and 'constr' is
   * a list [A, b, Aeq, beq] where A,Aeq are matrices and b,beq are vectors such that
   * c.x is maximized/minimized subject to A.x<=b and Aeq.x=beq. Parameters Aeq and beq
   * may be omitted if the problem does not have equality constraints.
   * 
   * For symbolically given problems, the parameter 'bd' is a sequence of arguments
   * in the form 'name=range', where 'range' is an interval (for example, x=-5..5
   * or y=0..inf). For problems given in matrix form, 'bd' must be a vector of two
   * vectors bl and bu such that bl<=x<=bu. In that case, all decision variables are
   * bounded at once. For variables that are unbounded from above/below one can use
   * +/-infinity as an upper/lower "bound".
   * 
   * All decision variables are unbounded and continuous by default.
   * 
   * With the 'assume' option one can specify:
   * 
   *          - assume = integer or lp_integer     (all variables are integers)
   *          - assume = lp_binary                 (all variables are binary)
   *          - assume = lp_nonnegative            (all variables are nonnegative)
   *          - assume = nonnegint or lp_nonnegint (all variables are nonnegative integers)
   * 
   * The following options are used to specify continuous, integer and binary
   * variables in mixed LP problems:
   * 
   *          - lp_variables = <list of continuous variables>
   *          - lp_integervariables = <list of integer variables>
   *          - lp_binaryvariables = <list of binary variables>
   * 
   * Instead of a list of identifiers, a list or an interval of their indexes may
   * be given as the value for 'lp_(integer/binary)variables'. For example,
   * option 'lp_binaryvariables=m..n' specifies xm,x(m+1),...,xn as binary
   * variables, and option 'lp_integervariables=[1,3,7]' specifies that the
   * variables x1, x3 and x7 are integers. The indexes and identifiers may
   * be freely mixed within a list. Variable indexes are 1-based.
   * 
   * Objective function can be either maximized or minimized. By default it
   * is minimized, which is equivalent to the (superfluous) option
   * 
   *          - lp_maximize = false
   * 
   * To solve a maximization problem, one can specify:
   * 
   *          - lp_maximize [= true]
   * 
   * Integer (mixed) LP problems are solved using the branch and bound method,
   * during which a binary tree of nodes that need to be inspected is formed.
   * The depth of that tree can be limited with option
   * 
   *          - lp_depthlimit = <positive integer>
   * 
   * With 'lp_depthlimit' option set, the integer solution returned by the branch&bound
   * method is feasible, but not necessarily the optimal one. Also, it is possible
   * that no feasible solution is found, although one may exist. By setting 'lp_depthlimit'
   * to zero (which is the default), the feasible solution returned by the
   * branch&bound method is always optimal.
   * 
   * The function 'lpsolve' uses the two-phase simplex method for maximization of
   * the objective function. For minimization of the nonnegative objective function the
   * dual (maximization) problem is solved because it only requires a single run of
   * the simplex method.
   * 
   * The function 'lpsolve' returns either
   * 
   *          - an empty list if no feasible solution exists,
   *          - the list [+infinity,[...]] if the objective function required to be maximized
   *            is unbounded from above, i.e. the list [-infinity,[...]] if the objective
   *            function required to be minimized is unbounded from below, or
   *          - the optimal solution as a list [optimum,[x1=x1*,x2=x2*,...,xn=xn*]] for
   *            symbolically given problems, where x1,x2,...,xn are the decision variables,
   *            or as a list [optimum,[x1*,x2*,...,xn*]] for problems given in matrix form.
   * 
   * If one needs only a fesible point with respect to a set of constraints, one should set
   * the parameter 'obj' to 0 for symbolic problems i.e. to [] for matrix problems. The
   * return value is the feasible point as a vector of coordinates or an empty list if
   * the given set of constraints is contradictory.
   * 
   * The function returns an error if no constraints were detected (i.e. when none
   * of 'constr', 'bd' and 'assume=(lp_)nonneg(ative/int)' arguments were detected).
   * 
   * 
   * Examples
   * ========
   * 
   *  1) Use LPSolve to minimize a linear function subject to linear constraints.
   *     Remember that all decision variables are unrestricted in sign by default.
   * 
   *   lpsolve(2x+y-z+4,[x<=1,y>=2,x+3y-z=2,2x-y+z<=8,-x+y<=5])
   *   lpsolve(-4x-5y,[x+2y<=6,5x+4y<=20,0<=x,0<=y])
   * 
   *  2) Use the 'lp_maximize [= true]' option to maximize the objective function.
   * 
   *   lpsolve(-7x+2y,[4x-12y<=20,-x+3y<=3],x=-5..5,y=0..inf,lp_maximize=true)
   *   lpsolve(x-y-2z+3,[-3x-y+z<=3,2x-3y>=4z,x-z=y,x>=0,y<=0],lp_maximize)
   * 
   *  3) Use the 'assume = lp_nonnegative' option instead of including
   *     non-negative constraints explicitly.
   * 
   *   lpsolve(-x-y,[y<=3x+1/2,y<=-5x+2],assume=lp_nonnegative)
   *   lpsolve(x+y,[x<=8,-x+y<=4,-x+2y>=6,2x+y<=25,3x+y>=18,-x+2y>=6],assume=lp_nonnegative)
   *   lpsolve(45.55x1+21.87x2,[1.64x1+2.67x2<=31.2,2.11x1+2.3x2>=13.9],assume=lp_nonnegative)
   *   lpsolve(3x+4y,[x<=4,x+3y<=15,-x+2y>=5,x-y>=9,x+y=6],assume=lp_nonnegative,lp_maximize=true)
   * 
   *  4) Simple bounds can be added separately.
   * 
   *   lpsolve(-6x+4y+z,[5x-10y<=20,2z-3y=6,-x+3y<=3],x=1..20,y=0..inf)
   * 
   *  5) Use the 'integer' or 'lp_integervariables' option to solve integer
   *     programming problems.
   * 
   *   lpsolve(-5x-7y,[7x+y<=35,-x+3y<=6],assume=integer)
   *   lpsolve(x+3y+3z,[x+3y+2z<=7,2x+2y+z<=11],assume=lp_nonnegative,lp_integervariables=[x,z],lp_maximize)
   * 
   *  6) The 'nonnegint' option can be used to get non-negative integer values.
   * 
   *   lpsolve(2x+5y,[3x-y=1,x-y<=5],assume=nonnegint)
   *   lpsolve(x1+x2,[2x1+5x2<=16,6x1+5x2<=30],assume=nonnegint,lp_maximize)
   * 
   *  7) Use the 'lp_binary' option to solve binary integer programming problems,
   *    where the decision variables can only have values from the set {0,1}.
   * 
   *   lpsolve(8x1+11x2+6x3+4x4,[5x1+7x2+4x3+3x4<=14],assume=lp_binary,lp_maximize)
   * 
   *  8) LP problems can also be given in matrix form.
   * 
   *   c:=[-2,1];A:=[[-1,1],[1,1],[-1,0],[0,-1]];b:=[3,5,0,0];lpsolve(c,[A,b])
   *   c:=[-1,1];A:=[[-3,1],[5,1]];b:=[1/2,2];lpsolve(c,[A,b],assume=lp_nonnegative)
   * 
   *  9) Bounds for problem in matrix form can be added separately. In
   *     the following example, there are no other constraints.
   * 
   *   c:=[-2,5,-3];bl:=[2,3,1];bu:=[6,10,3.5];lpsolve(c,[],[bl,bu])
   * 
   * 10) For problems in matrix form with no inequality constraints, an empty list
   *     is passed for parameters A and b.
   * 
   *   c:=[4,5];Aeq:=[[-1,1.5],[-3,2]];beq:=[2,3];lpsolve(c,[[],[],Aeq,beq])
   * 
   * 11) The 'lp_integervariables' or 'lp_binaryvariables' option can be used to
   *     specify mixed-integer problems.
   * 
   *   c:=[2,-3,-5];A:=[[-5,4,-5],[2,5,7],[2,-3,4]];b:=[3,1,-2];lpsolve(c,[A,b],lp_integervariables=[1,3])
   */
  gen _lpsolve(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT || g._VECTptr->size()<2)
      // too few arguments, stop
      return gensizeerr(contextptr);
    vecteur & gv = *g._VECTptr,constr,vars;
    vars=*_lname(gv[0],contextptr)._VECTptr;  // detect variable names from objective function
    int ibd;  // position of the parameter 'bd' (or 'opts', if 'bd' is not given)
    if (gv[1].type==_VECT) {
      // the parameter 'constr' is given
      constr=*gv[1]._VECTptr;
      vecteur constr_vars=*_lname(gv[1],contextptr)._VECTptr;  // scan variables in constraints
      // detect variables not appearing in the objective function
      for (vecteur::const_iterator it=constr_vars.begin();it!=constr_vars.end();++it) {
        if (!contains(vars,*it))
          vars.push_back(*it);
      }
      ibd=2;
    } else
      // the parameter 'constr' is not given
      ibd=1;
    vecteur lr,bconstr,cvars,ivars,bvars,pvars,nvars;
    int dl=0;  // branch&bound tree depth limit
    bool maximize=false;
    bool all_nonneg=false;
    bool all_integer=false;
    bool all_binary=false;
    // check if any boundaries or options are set
    for (vecteur::const_iterator it=gv.begin()+ibd;it!=gv.end();++it) {
      if (is_integer(*it) && int((*it).val)==_LP_MAXIMIZE)
        // this is a maximization problem
        maximize=true;
      if ((*it).type!=_SYMB)
        continue;
      gen R=(*it)._SYMBptr->sommet;
      if (R==at_equal) {
        // parse the argument in form "option=value"
        vecteur ops(*((*it)._SYMBptr->feuille._VECTptr));
        if (ops[0].type==_IDNT && interval2vecteur(ops[1],lr,contextptr)) {
          // the boundaries for variable ops[0] are set
          if (!is_zero(lr[0]) && is_strictly_greater(lr[0],minus_inf,contextptr))
            bconstr.push_back(symbolic(at_superieur_egal,makevecteur(ops[0],lr[0])));
          if (is_strictly_greater(plus_inf,lr[1],contextptr))
            bconstr.push_back(symbolic(at_inferieur_egal,makevecteur(ops[0],lr[1])));
          if (is_positive(lr[0],contextptr))
            // variable is nonnegative
            pvars.push_back(ops[0]);
          else if (!is_strictly_positive(lr[1],contextptr))
            // variable is not positive
            nvars.push_back(ops[0]);
        }
        if (ops[0]==at_assume) {
          // parse assumptions
          if (is_integer(ops[1])) {
            switch(ops[1].val) {
            case _ZINT:
            case _LP_INTEGER:
              // all variables are integer
              all_integer=true;
              ivars=vars;
              break;
            case _LP_BINARY:
              // all variables are binary
              all_nonneg=true;
              all_binary=true;
              bvars=vars;
              break;
            case _NONNEGINT:
            case _LP_NONNEGINT:
              // all variables are nonnegative integers
              all_nonneg=true;
              all_integer=true;
              ivars=vars;
              break;
            case _LP_NONNEGATIVE:
              // all variables are nonnegative
              all_nonneg=true;
              break;
            }
          }
        }
        if (is_integer(ops[0])) {
          switch(ops[0].val) {
          case _LP_VARIABLES:
            // specify continuous variables
            if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
              for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                cvars.push_back(gen(i));
              }
            }
            else if (ops[1].type==_VECT)
              cvars=*ops[1]._VECTptr;
            break;
          case _LP_INTEGERVARIABLES:
            // specify integer variables
            if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
              for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                ivars.push_back(gen(i));
              }
            }
            else if (ops[1].type==_VECT)
              ivars=*ops[1]._VECTptr;
            break;
          case _LP_BINARYVARIABLES:
            // specify binary variables
            if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
              for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                bvars.push_back(gen(i));
              }
            }
            else if (ops[1].type==_VECT)
              bvars=*ops[1]._VECTptr;
            break;
          case _LP_DEPTHLIMIT:
            // specify branch&bound tree depth limit
            if (is_integer(ops[1]))
              int dl=int(ops[1].val);
            break;
          case _LP_MAXIMIZE:
            // maximize=true for maximization, maximize=false for minimization
            maximize=!is_zero(ops[1]);
            break;
          }
        }
      }
    }
    gen obj_ct; // the constant term of the objective function
    vecteur lh,rel,rh,obj_orig;
    int nv; // number of variables
    vector<int> varsign;  // ith is 1 for variable xi nonnegative, -1 for negative and 0 for unconstrained
    if (gv[0].type==_VECT && vars.size()==0) {
      // the problem is given in matrix form
      // objective: c=[c1,c2,...,cn], maximize/minimize c.x
      obj_orig=*gv[0]._VECTptr;
      nv=int(obj_orig.size());  // number of variables
      int nconstr=int(constr.size());
      if ((nv==0 && nconstr==0) || (nconstr!=0 && nconstr!=4 && nconstr!=2))
        // improper specification of constraints, stop
        return gensizeerr(contextptr);
      if (nconstr>0) {
        // constraints: [A,b,Aeq,beq] such that A.x<=b and/or Aeq.x=beq
        lh=*constr[0]._VECTptr;  // matrice A
        rh=*constr[1]._VECTptr;  // vecteur b
        rel=vecteur(lh.size(),-1);
        if (nconstr==4) {
          // there are equation constraints
          vecteur &Aeq=*constr[2]._VECTptr,&beq=*constr[3]._VECTptr;
          int neq=int(Aeq.size());
          if (neq>0) {
            lh=mergevecteur(lh,Aeq);
            rh=mergevecteur(rh,beq);
            rel=mergevecteur(rel,vecteur(neq,0));
          }
        }
        if (!ckmatrix(lh) || rh.size()!=lh.size() || rel.size()!=lh.size())
          // invalid dimensions, stop
          return gendimerr(contextptr);
        if (nv==0) {
          // an empty list was given for the objective vector, set all its coefficients to 0
          nv=int(lh.front()._VECTptr->size());
          obj_orig=vecteur(nv,0);
        }
      }
      varsign=vector<int>(nv,all_nonneg ? 1 : 0); 
      // check if the third argument is a vector of bounds for variables
      // [bl,bu] such that bl<=x<=bu
      if (int(gv.size())>ibd &&
          gv[ibd].type==_VECT &&
          ckmatrix(*gv[ibd]._VECTptr) &&
          int(gv[ibd]._VECTptr->front()._VECTptr->size())==nv &&
          int(gv[ibd]._VECTptr->size())==2) {
        // set boundaries to the variables
        vecteur & bl = *(*gv[ibd]._VECTptr)[0]._VECTptr;
        vecteur & bu = *(*gv[ibd]._VECTptr)[1]._VECTptr;
        matrice mi(midn(nv));
        for (int i=0;i<nv;++i) {
          if (!is_zero(bl[i]) && is_strictly_greater(bl[i],minus_inf,contextptr)) {
            lh.push_back(*mi[i]._VECTptr);
            rel.push_back(gen(1));
            rh.push_back(bl[i]);
          }
          if (!is_greater(bu[i],plus_inf,contextptr)) {
            lh.push_back(*mi[i]._VECTptr);
            rel.push_back(gen(-1));
            rh.push_back(bu[i]);
          }
          if (!all_nonneg) {
            if (is_positive(bl[i],contextptr))
              // ith variable is nonnegative
              varsign[i]=1;
            else if (!is_strictly_positive(bu[i],contextptr))
              // ith variable is not positive
              varsign[i]=-1;
          }
        }
      }
    }
    else if ((gv[0].type==_SYMB || is_zero(gv[0])) && vars.size()>0) {
      // the problem is given in symbolic form
      // objective: c1*x1+c2*x2+...+cn*xn
      // constraints: a list of linear equations and inequalities
      gen r;
      if (!lincomb_coeff(gv[0],vars,obj_orig,obj_ct,contextptr)) {
        // objective function is not linear, stop
        cout << "Error: the objective function must be linear" << endl;
        return gentypeerr(contextptr);
      }
      nv=int(vars.size());
      varsign=vector<int>(nv,all_nonneg ? 1 : 0);
      constr=mergevecteur(constr,bconstr);
      // write the constraints in matrix form
      for (vecteur::const_iterator it=constr.begin();it!=constr.end();++it) {
        gen s=(*it)._SYMBptr->sommet;
        vecteur sides(*((*it)._SYMBptr->feuille._VECTptr)),c,bnd;
        if (s==at_equal && interval2vecteur(sides[1],bnd,contextptr)) {
          // a bounded expression was given as constraint
          if (!lincomb_coeff(sides[0],vars,c,r,contextptr)) {
            // constraint is not linear, stop
            cout << "Error: all bounded expressions must be linear" << endl;
            return gentypeerr(contextptr);
          }
          lh=mergevecteur(lh,vecteur(2,c));
          rel=mergevecteur(rel,makevecteur(gen(1),gen(-1)));
          rh=mergevecteur(rh,subvecteur(bnd,vecteur(2,r)));
          continue;
        }
        // turn constraint to vector form
        gen d=sides[0]-sides[1];
        if (!lincomb_coeff(d,vars,c,r,contextptr)) {
          // constraint is not linear, stop
          cout << "Error: all constraints must be linear" << endl;
          return gentypeerr(contextptr);
        }
        lh.push_back(c);
        rh.push_back(-r);
        if (s==at_equal)
          rel.push_back(gen(0));
        else if (s==at_inferieur_egal)
          rel.push_back(gen(-1));
        else if (s==at_superieur_egal)
          rel.push_back(gen(1));
        else {
          // constraint type is not recognized, stop
          cout << "Error: unrecognized relation type, it should be either >=, <= or =" << endl;
          return gentypeerr(contextptr);
        }
      }
      // update varsign
      vector<int> vp=findvars(pvars,vars),vn=findvars(nvars,vars);
      for (vector<int>::const_iterator vit=vp.begin();vit!=vp.end();++vit) {
        varsign[*vit]=1;
      }
      for (vector<int>::const_iterator vit=vn.begin();vit!=vn.end();++vit) {
        varsign[*vit]=-1;
      }
    } else
      // the problem is given improperly, stop
      return gentypeerr(contextptr);
    if (int(lh.size())==0 && !all_nonneg) {
      // no constraints were specified, stop
      cout << "Error: no constraints found" << endl;
      return gensizeerr(contextptr);
    }
    vecteur obj(obj_orig);
    vector<int> vartype(nv,(all_integer || all_binary) ? 1 : 0);
    vector<int> vi=findvars(ivars,vars),vb=findvars(bvars,vars);
    for (vector<int>::const_iterator it=vi.begin();it!=vi.end();++it) {
      vartype[*it]=1;
    }
    for (vector<int>::const_iterator it=vb.begin();it!=vb.end();++it) {
      vartype[*it]=1;
      varsign[*it]=1;  // binary variables are always nonnegative
      // append constraint of type xb<=1
      lh.push_back(midn(nv)[*it]);
      rel.push_back(gen(-1));
      rh.push_back(gen(1));
    }
    vector<int> vc=findvars(cvars,vars);
    for (vector<int>::const_iterator it=vc.begin();it!=vc.end();++it) {
      vartype[*it]=0;
    }
    gen soln;
    bool use_twophase=true; // does the solver use 'simplex_twophase' or 'simplex_dual' function
    if (maximize)
      // maximization problem
      soln=simplex_twophase(lh,rel,rh,obj,varsign,contextptr);
    else {
      // minimization problem
      // first check if the objective function has nonnegative coefficients
      // if it does, use 'simplex_dual', else maximize the negative objective function
      int i=0;
      for (;i<nv && is_positive(obj[i],contextptr) && varsign[i]>0;++i);
      if (i==nv) {
        // using simplex_dual
        use_twophase=false;
        soln=simplex_dual(lh,rel,rh,obj,contextptr);
      } else {
        // using simplex_twophase
        obj=-obj;
        soln=simplex_twophase(lh,rel,rh,obj,varsign,contextptr);
      }
    }
    if (int(soln._VECTptr->size())==0 || _abs(soln[0],contextptr)==plus_inf) {
      // there is no optimal solution
      if (int(soln._VECTptr->size())>0 && !maximize && use_twophase) {
        // objective function is actually unbounded from below
        soln._VECTptr->front()=minus_inf;
      }
      return soln;
    }
    // check if the required variables have integer values
    gen f(0);
    for (int i=0;i<nv;++i) {
      gen xi=soln[1][i];
      if (vartype[i]==1)
        f+=_abs(xi-_round(xi,contextptr),contextptr);
    }
    if (!is_zero(_recursive_normal(f,contextptr))) {
      // branch & bound
      vecteur isoln;
      int node_count=branch_and_bound(lh,rel,rh,obj,vartype,*soln._VECTptr,varsign,isoln,use_twophase,0,dl,contextptr);
      cout << "branch and bound: " << node_count << " node(s) examined" << endl;
      if (int((soln=isoln)._VECTptr->size())==0)
        // there is no feasible integer solution
        return soln;
    }
    // calculate the value of the objective function with respect to the optimal solution 'soln'
    gen optimum=scalarproduct(*soln[1]._VECTptr,obj_orig,contextptr);
    vecteur & v = *soln[1]._VECTptr;
    // for symbolically entered problems (i.e. when 'vars' is not empty),
    // return optimal solution in the form [x1=x1*,x2=x2*,...,xn=xn*]
    if (int(vars.size())>0) {
      for (int i=0;i<nv;++i) {
        v[i]=symbolic(at_equal,makevecteur(vars[i],v[i]));
      }
    }
    // return simplified optimal solution paired with the maximum/minimum value
    // of the objective function
    v=*_simplify(v,contextptr)._VECTptr;
    if ((gv[0].type==_VECT && int(gv[0]._VECTptr->size())==0) || is_zero(gv[0]))
      // the user needed a feasible point only
      return v;
    return makevecteur(_simplify(optimum+obj_ct,contextptr),v);
  }
  static const char _lpsolve_s []="lpsolve";
  static define_unary_function_eval (__lpsolve,&_lpsolve,_lpsolve_s);
  define_unary_function_ptr5(at_lpsolve,alias_at_lpsolve,&__lpsolve,0,true);

#ifndef NO_NAMESPACE_GIAC
}
#endif // ndef NO_NAMESPACE_GIAC
