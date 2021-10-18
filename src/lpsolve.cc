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
 * Description
 * ^^^^^^^^^^^
 * Function 'lpsolve' solves a (mixed integer/binary) LP problem in general
 * form. It is used as follows:
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
 * For symbolically given problems, the parameter 'bd' is a sequence of
 * arguments in the form 'name=range', where 'range' is an interval (for
 * example, x=-5..5 or y=0..inf). For problems given in matrix form, 'bd' must
 * be a vector of two vectors bl and bu such that bl<=x<=bu. In that case, all
 * decision variables are bounded at once. For variables that are unbounded
 * from above/below one can use +/-infinity as an upper/lower "bound".
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
 * variables x1, x3 and x7 are integers. The indexes and identifiers may be
 * freely mixed within a list. Variable indexes are 1-based.
 *
 * Objective function can be either maximized or minimized. By default it is
 * minimized, which is equivalent to the (superfluous) option
 *
 *          - lp_maximize = false
 *
 * To solve a maximization problem, one can specify:
 *
 *          - lp_maximize [= true]
 *
 * Integer (mixed) LP problems are solved using the branch and bound method,
 * during which a binary tree of nodes that need to be inspected is formed. The
 * depth of that tree can be limited with option
 *
 *          - lp_depthlimit = <positive integer>
 *
 * and number of inspected nodes can be limited with option
 *
 *          - lp_nodelimit = <positive integer>

 * With 'lp_depthlimit' or 'lp_nodelimit' option set, the integer solution
 * returned by the branch&bound method is feasible, but not necessarily the
 * optimal one. Also, it is possible that no feasible solution is found,
 * although one may exist. By setting 'lp_depthlimit' to zero (which is the
 * default), the feasible solution returned by the branch&bound method is
 * always optimal.
 *
 * By default, 'lpsolve' uses two-phase simplex method for optimization of
 * the objective function.
 *
 * The function 'lpsolve' returns either
 *
 *  - an empty list if no feasible solution exists,
 *  - the list [+infinity,[...]] if the objective function required to be maximized
 *    is unbounded from above, i.e. the list [-infinity,[...]] if the objective
 *    function required to be minimized is unbounded from below, or
 *  - the optimal solution as a list [optimum,[x1=x1*,x2=x2*,...,xn=xn*]] for
 *    symbolically given problems, where x1,x2,...,xn are the decision variables,
 *    or as a list [optimum,[x1*,x2*,...,xn*]] for problems given in matrix form.
 *
 * If one needs only a fesible point with respect to a set of constraints, one
 * should set the parameter 'obj' to 0 for symbolic problems i.e. to [] for
 * matrix problems. The return value is the feasible point as a vector of
 * coordinates or an empty list if the given set of constraints is
 * contradictory.
 *
 * The function returns an error if no constraints were detected (i.e. when
 * none of 'constr', 'bd' and 'assume=(lp_)nonneg(ative/int)' arguments were
 * detected).
 *
 * Examples
 * ^^^^^^^^
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
 *
 * Additional LP problems for testing
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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
 *
 * 5)
 *  [2,10,13,17,7,5,7,3],[[],[],[[22,13,26,33,21,3,14,26],[39,16,22,28,26,30,23,24],[18,14,29,27,30,38,26,26],[41,26,28,36,18,38,16,26]],[7872,10466,11322,12058]],assume=lp_nonnegative
 *
 * 6)
 *  1.06x1+0.56x2+3x3+2703.50x4+4368.23x5,[1.06x1+0.015x3>=729824.87,0.56x2+0.649x3>=1522188.03,x3>=1680.05,x4>=60,x5>=4],assume=lp_nonnegative
 */

using namespace std;
#include "lpsolve.h"
#include "giac.h"

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

/*
 * Maximize obj^t*x subject to A*x<=b using two-phase simplex method. Slack and
 * surplus variables need to be represented with additional columns in matrix
 * m_orig. Equality constraints must come before inequality constraints in that
 * matrix. Function introduces artificial variables automatically when
 * preparing for the first phase. This implementation is intended for exact
 * computation, phase I may fail if calculations are floating-point because of
 * roundoff errors (see example 6 in 'Additional LP problems for testing'
 * section above).
 */
matrice simplex_twophase(matrice & m_orig,vecteur & b,vecteur & obj,vecteur & soln,gen & optimum,GIAC_CONTEXT) {
    int nc=m_orig.size(),nv=obj.size();
    int ns=int(m_orig.front()._VECTptr->size())-nv;
    int neq=nc-ns;
    matrice m(m_orig),idn(midn(nc));
    // append columns for artificial variables and b (rhs values)
    vector<int> av;
    m=mtran(m);
    for (int i=-neq;i<ns;++i) {
        if (i<0 || is_one(-m[i+nv][i+neq])) {
            av.push_back(i+neq);
            m.push_back(idn[i+neq]);
        }
    }
    int na=av.size();
    m.push_back(b);
    m=mtran(m);
    vecteur br; // bottom row
    if (na==0) { // no artificial variables, the problem is in canonical form
        br=mergevecteur(-obj,vecteur(ns+na+1,0));
        m.push_back(br);
        m=simplex_reduce(m,soln,optimum,true,false,contextptr);
    }
    else {
        // artificial variables were introduced, proceed with the two phase method
        br=mergevecteur(vecteur(nv+ns,0),vecteur(av.size(),1));
        br.push_back(gen(0));
        for (vector<int>::const_iterator it=av.begin();it!=av.end();++it) {
            br=subvecteur(br,*m[*it]._VECTptr);
        }
        m.push_back(br);
        m=simplex_reduce(m,soln,optimum,true,false,contextptr); // phase I
        if (!is_zero(optimum,contextptr)) { // no feasible solution exists
            soln=vecteur(0);
            return m;
        }
        vector< pair<int,int> > basis;
        vector<bool> found(nc+1,false); // found[i] becomes true when ith column of idn is found
        vector<bool> row_active(nc+1,true); // a constraint is inactive when tautologic (0=0)
        for (int j=0;j<nv+ns+na;++j) {
            int I=-1;
            for (int i=0;i<nc+1;++i) {
                if (!is_zero(m[i][j])) {
                    if (I>=0) {
                        I=-1;
                        break;
                    }
                    I=i;
                }
            }
            if (I==-1 || found[I] || !is_one(m[I][j])) // jth variable not in the basis, skip
                continue;
            // jth variable is in the basis
            found[I]=true; // remember which idn columns have been found so far
            if (j>=nv+ns) { // jth variable is artificial, it must be pushed out of the basis
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
                    basis.push_back(make_pair(I,k));
                }
                else // mark Ith row inactive
                    row_active[I]=false;
            }
            else
                basis.push_back(make_pair(I,j));
        }
        // remove the artificial variables columns and the last row from m
        m=mtran(m);
        m.erase(m.begin()+nv+ns,m.end()-1);
        m=mtran(m);
        m.pop_back();
        br=mergevecteur(-obj,vecteur(ns+1,0)); // bottom row for maximizing the objective function
        for (vector< pair<int,int> >::const_iterator it=basis.begin();it!=basis.end();++it) {
            br=subvecteur(br,multvecteur(br[it->second],*m[it->first]._VECTptr));
        }
        m.push_back(br);
        for (int i=nc;i>=0;--i) {
            if (!row_active[i])
                m.erase(m.begin()+i);
        }
        m=simplex_reduce(m,soln,optimum,true,false,contextptr); // phase II
    }
    return m;
}

/*
 * Assure that b contains no negative elements.
 */
void simplex_prepare(matrice & m,vecteur & b,GIAC_CONTEXT) {
    for (int i=0;i<int(m.size());++i) {
        if (is_strictly_positive(-b[i],contextptr)) {
            m[i]=-m[i];
            b[i]=-b[i];
        }
    }
}

/*
 * Compute vector w=A*v.
 */
vecteur multmatvec(const matrice & m,const vecteur & v) {
    vecteur res(m.size(),gen(0));
    for (int i=0;i<int(m.size());++i) {
        for (int j=0;j<int(v.size());++j) {
            res[i]+=m[i][j]*v[j];
        }
    }
    return res;
}

vecteur multdiagvec(const vecteur & d,const vecteur & v) {
    vecteur res(d.size());
    for (int i=0;i<int(d.size());++i) {
        res[i]=d[i]*v[i];
    }
    return res;
}

bool cholesky_decomposition(const vecteur & A,matrice & L,GIAC_CONTEXT) {
    int n=A.size(),j,k,l;
    for (j=0;j<n;j++) {
        gen s;
        for (l=j;l<n;l++) {
            if (int(L.size())<n)
                L.push_back(vecteur(n,gen(0)));
            s=0;
            for (k=0;k<j;k++) {
                if (is_zero(L[k][k],contextptr))
                    return false;
                s+=L[l][k]*L[j][k]/L[k][k];
            }
            L[l]._VECTptr->at(j)=A[l]._VECTptr->at(j)-s;
//            cout << "(" << l << "," << j << "): " << L[l][j] << endl;
        }
    }
    for (k=0;k<n;k++) {
        gen c(inv(sqrt(L[k][k],contextptr),contextptr));
        for (j=k;j<n;j++) {
            L[j]._VECTptr->at(k)=L[j][k]*c;
        }
    }
    return true;
}

static int step_count;

/*
 * Implementation of primal-dual affine scaling algorithm from:
 * http://www.4er.org/CourseNotes/Book%20B/B-III.pdf
 */
bool primal_dual_affine_scaling(matrice & A,vecteur & b,vecteur & c,
                                vecteur & x,vecteur & p,vecteur & s,GIAC_CONTEXT) {
    gen alpha(0.99995),beta(0.1),mu;
    int nv=A.front()._VECTptr->size(),nc=A.size();
    matrice At(mtran(A)),L;
    vecteur xinv(nv),dx(nv),ds;
    do {
        ++step_count;
        mu=beta*scalarproduct(s,x,contextptr)/gen(nv);
        for (int k=0;k<nv;++k) {
            xinv[k]=pow(x[k],-1);
        }
        // solve the system:
        // [-X^-1*S At] [dx] _ [c-At*p-mu*X^-1*e]
        // [  A     0 ] [ds] ‾ [      b-A*x     ]
        // where X^-1=diag(xinv) and S=diag(s)
        vecteur B,rh1(subvecteur(c,addvecteur(multmatvec(At,p),multvecteur(mu,xinv))));
        vecteur rh2(subvecteur(b,multmatvec(A,x)));
        for (int j=0;j<nv;++j) {
            for (int i=0;i<nc;++i) {
                if (int(B.size())<nc)
                    B.push_back(vecteur(i+1,0));
                gen cf(A[i][j]*x[j]/s[j]);
                vecteur r(At[j]._VECTptr->begin(),At[j]._VECTptr->begin()+i+1);
                B[i]=addvecteur(*B[i]._VECTptr,multvecteur(cf,r));
                rh2[i]+=cf*rh1[j];
            }
        }
        if (!cholesky_decomposition(B,L,contextptr)) // can't iterate further
            break;
        vecteur dp(rh2);
        for (int i=0;i<nc;++i) {
            for (int j=0;j<i;++j) {
                dp[i]-=L[i][j]*dp[j];
            }
            dp[i]=dp[i]/L[i][i];
        }
        for (int j=nc-1;j>=0;--j) {
            for (int i=j+1;i<nc;++i) {
                dp[j]-=L[i][j]*dp[i];
            }
            dp[j]=dp[j]/L[j][j];
        }
        for (int k=0;k<nv;++k) {
            rh1[k]-=scalarproduct(*At[k]._VECTptr,dp,contextptr);
            dx[k]=-x[k]*rh1[k]/s[k];
        }
        ds=-addvecteur(s,multdiagvec(xinv,subvecteur(multdiagvec(s,dx),vecteur(nv,mu))));
        if (_count_inf(makesequence(gen(0),dx),contextptr).val==0 ||
                _count_inf(makesequence(gen(0),ds),contextptr).val==0)
            // no optimal solution can be found
            return false;
        vecteur theta_xv,theta_sv;
        for (int k=0;k<nv;++k) {
            if (is_positive(-dx[k],contextptr) && !is_exactly_zero(dx[k]))
                theta_xv.push_back(-x[k]/dx[k]);
            if (is_positive(-ds[k],contextptr) && !is_exactly_zero(ds[k]))
                theta_sv.push_back(-s[k]/ds[k]);
        }
        gen theta_x(_min(theta_xv,contextptr)),theta_s(_min(theta_sv,contextptr));
        gen theta(_min(makesequence(gen(1),alpha*theta_x),contextptr));
        gen phi(_min(makesequence(gen(1),alpha*theta_s),contextptr));
        x=addvecteur(x,multvecteur(theta,dx));
        p=addvecteur(p,multvecteur(phi,dp));
        s=addvecteur(s,multvecteur(phi,ds));
    } while (!is_zero(_max(_abs(multdiagvec(dx,ds),contextptr),contextptr),contextptr));
    // x is optimal
    return true;
}

/*
 * Return true iff m has full row rank.
 */
bool is_fullrank(const matrice & m,int & r,GIAC_CONTEXT) {
    r=_rank(m,contextptr).val;
    return r==int(m.size());
}

/*
 * Maximize z=c^T*x subject to A*x=b using primal-dual affine scaling method.
 * Optimal value z* is returned.
 */
gen affscale(matrice & A,vecteur & b,vecteur & c_orig,vecteur & x,bool report,GIAC_CONTEXT) {
    int rnk;
    if (!is_fullrank(A,rnk,contextptr)) {
        x=vecteur(0);
        if (report)
            cout << "Error: constraint matrix is not full rank" << endl;
        return undef;
    }
    step_count=0;
    int nv=int(c_orig.size()),ns=A.front()._VECTptr->size()-nv,nc=A.size();
    vecteur c(mergevecteur(-c_orig,vecteur(ns,gen(0))));
    if (x.empty())
        x=vecteur(nv,gen(1));
    vecteur y(ns);
    for (int k=0;k<ns;++k) {
        int i=k+nc-ns,j=nv+k;
        vecteur & r = *A[i]._VECTptr;
        y[k]=(b[i]-scalarproduct(vecteur(r.begin(),r.begin()+nv),x,contextptr))/A[i][j];
        if (!is_strictly_positive(y[k],contextptr))
            y[k]=gen(1);
    }
    x=mergevecteur(x,y);
    vecteur s(nv+ns,gen(1)),p(nc,gen(0));
    if (!primal_dual_affine_scaling(A,b,c,x,p,s,contextptr)) {
        x=vecteur(0);
        if (report)
            cout << "No optimal solution found" << endl;
        return undef;
    }
    return scalarproduct(-c,x,contextptr);
}

/*
 * Test if g is integer w.r.t. tolerance itol. g is considered integer if
 * |g-round(g)|<=itol.
 */
bool is_whole(const gen & g,gen & itol,GIAC_CONTEXT) {
    gen d(_abs(g-_round(g,contextptr),contextptr));
    return is_greater(itol,d,contextptr);
}

bool exactify_solution(vecteur & soln,vector<int> vartype,gen & itol,GIAC_CONTEXT) {
    for (int i=0;i<int(vartype.size());++i) {
        if (vartype[i]==1) {
            if (is_whole(soln[i],itol,contextptr)) {
                if (is_exactly_zero(itol))
                    soln[i]=exact(soln[i],contextptr);
            }
            else
                return false;
        }
    }
    return true;
}

bool is_slack_integer(matrice & m,vecteur & b,int J,vector<int> & vartype,vecteur & eq,GIAC_CONTEXT) {
    int i=0,nv=vartype.size();
    for (;is_zero(m[i][J]);++i);
    eq=*m[i]._VECTptr;
    eq[J]=gen(0);
    eq.push_back(b[i]);
    eq=multvecteur(-m[i][J],eq);
    gen itol(0);
    if (!is_whole(eq.back(),itol,contextptr))
        return false;
    for (int j=0;j<nv;++j) {
        if (is_zero(eq[j]))
            continue;
        if (vartype[j]==0 || !is_whole(eq[j],itol,contextptr))
            return false;
    }
    return true;
}

/*
 * Some heuristics mentioned in:
 *
 *      http://eventos.cmm.uchile.cl/discretas2016/wp-content/uploads/sites/26/2015/12/ChileSummerSchool.pdf
 *
 * (see page 25) are implemented in this function to discard bad cuts.
 * A bad cut is represented by an empty vector.
 */
vecteur gomory_cut(matrice & M,matrice & m,vecteur & b,int I,int J,vector<int> & vartype,GIAC_CONTEXT) {
    int n=m.front()._VECTptr->size(),nv=vartype.size();
    vecteur eq(*M[I]._VECTptr),cut(n,gen(0));
    gen f0(eq.back()-_floor(eq.back(),contextptr));
    if (is_greater(f0,gen(0.99),contextptr) || is_strictly_greater(gen(0.01),f0,contextptr))
        // f0 or 1-f0 is too small
        return vecteur(0);
    eq.pop_back();
    cut.push_back(gen(1));
    gen cfmin(0),cfmax(0);
    for (int j=0;j<n;++j) {
        if (j==J || is_zero(eq[j]))
            continue;
        vecteur eqj;
        gen &aij=eq[j];
        if (j<nv?(vartype[j]==1):is_slack_integer(m,b,j,vartype,eqj,contextptr)) {
            gen fj(aij-_floor(aij,contextptr));
            cut[j]=is_greater(f0,fj,contextptr)?fj/f0:(1-fj)/(1-f0);
        }
        else
            cut[j]=aij/(is_positive(aij,contextptr)?f0:f0-1);
        if (is_exactly_zero(cfmin) || is_strictly_greater(cfmin,cut[j],contextptr))
            cfmin=cut[j];
        if (is_strictly_greater(cut[j],cfmax,contextptr))
            cfmax=cut[j];
        if (j>=nv) {
            cut=addvecteur(cut,multvecteur(cut[j],eqj));
            cut[j]=gen(0);
        }
    }
    if (is_greater(_abs(_evalf(cfmax/cfmin,contextptr),contextptr),pow(gen(10),6),contextptr))
        // dynamism of the cut is too large
        return vecteur(0);
    int nz=nv;
    for (int i=0;i<nv;++i) {
        if (is_exactly_zero(cut[i]))
            --nz;
    }
    if (nz>1+nv/2) // the cut is too dense
        return vecteur(0);
    cut=*exact(cut,contextptr)._VECTptr;
    gen nzv(_abs(_denom(cut.back(),contextptr),contextptr));
    for (int i=0;i<nv;++i) {
        if (is_zero(cut[i]))
            continue;
        nzv=_lcm(makesequence(nzv,_abs(_denom(cut[i],contextptr),contextptr)),contextptr);
    }
    return multvecteur(nzv,cut);
}

static int cut_count;

bool simplex_gomory(matrice & M,matrice & m,vecteur & b,vecteur & obj,vector<int> & vartype,
                    vecteur & soln,gen & optimum,GIAC_CONTEXT) {
    int nv=obj.size(),discarded_cuts=0;
    if (soln.empty())
        return false;
    matrice cuts;
    gen itol(0);
    for (int j=0;j<nv;++j) {
        if (vartype[j]==1 && !is_whole(soln[j],itol,contextptr)) {
            int i=0;
            for (;!is_one(M[i][j]);++i);
            vecteur cut(gomory_cut(M,m,b,i,j,vartype,contextptr));
            if (cut.empty())
                ++discarded_cuts;
            if (!cut.empty() && find(cuts.begin(),cuts.end(),cut)==cuts.end())
                cuts.push_back(cut);
        }
    }
    if (cuts.empty())
        return false;
    cut_count+=int(cuts.size());
    cuts=mtran(cuts);
    vecteur rv(*cuts.back()._VECTptr);
    cuts.pop_back();
    cuts=mtran(cuts);
    int nc=m.size(),ncuts=cuts.size();
    m=mtran(mergevecteur(mtran(m),*_matrix(makesequence(ncuts,nc,0),contextptr)._VECTptr));
    cuts=mtran(mergevecteur(mtran(cuts),multvecteur(gen(-1),midn(ncuts))));
    m=mergevecteur(m,cuts);
    b=mergevecteur(b,rv);
    simplex_prepare(m,b,contextptr);
    simplex_twophase(m,b,obj,soln,optimum,contextptr);
    return true;
}

matrice copy_matrix(matrice & m) {
    matrice m_copy;
    for (const_iterateur it=m.begin();it!=m.end();++it) {
        vecteur v(*it->_VECTptr);
        m_copy.push_back(v);
    }
    return m_copy;
}

static int node_count;

void branch_and_bound(matrice & m_orig,vecteur & b_orig,vecteur & obj,vector<int> & varsign,
                      vector<int> & vartype,vecteur & soln_relaxed,vecteur & incumbent,gen & optimum,
                      gen & itol,bool use_affscale,int depth,int depthlimit,int nodelimit,GIAC_CONTEXT) {
    if ((depthlimit>0 && depth>depthlimit) || (nodelimit>0 && node_count>=nodelimit))
        return;
    int nv=int(obj.size()),nc=m_orig.size(); // number of variables
    int ns=int(m_orig.front()._VECTptr->size())-nv;
    int k=-1;
    gen fr,min_fr(0);
    for (int i=0;i<nv;++i) {
        if (vartype[i]==0) // ith variable is continuous, skip
            continue;
        fr=_abs(soln_relaxed[i]-_round(soln_relaxed[i],contextptr),contextptr);
        if (is_strictly_greater(fr,min_fr,contextptr)) {
            k=i;
            min_fr=fr;
        }
    }
    if (k<0) // no variable to branch on
        return;
    vector<int> nxt;
    gen xk=soln_relaxed[k];
    vecteur bounds=makevecteur(_ceil(xk,contextptr),_floor(xk,contextptr));
    vecteur solnv(2),optv(2),mv(2),bv(2);
    // solve two subproblems
    matrice idn(midn(nv+ns));
    for (int i=0;i<2;++i) {
        matrice m(copy_matrix(m_orig));
        vecteur b(b_orig),soln;
        for (int j=0;j<nc;++j) {
            m[j]._VECTptr->push_back(gen(0));
        }
        vecteur c(*idn[k]._VECTptr);
        c.push_back(gen(2*i-1));
        m.push_back(c);
        b.push_back(bounds[i]);
        if (i==0 && is_strictly_positive(bounds[i],contextptr)) {
            int l=0;
            for (vector<int>::const_iterator it=varsign.begin();it!=varsign.end();++it) {
                if (*it==0 && (k==l || k==l+1)) {
                    c=*idn[k+(k==l?1:-1)]._VECTptr;
                    c.push_back(gen(0));
                    m=mergevecteur(vecteur(1,c),m);
                    b=mergevecteur(vecteur(1,gen(0)),b);
                }
                l+=*it==0?2:1;
            }
        }
        if (use_affscale) {
            optv[i]=affscale(m,b,obj,soln,false,contextptr);
            soln=*_epsilon2zero(soln,contextptr)._VECTptr;
        }
        else {
            matrice M(simplex_twophase(m,b,obj,soln,optv[i],contextptr));
            simplex_gomory(M,m,b,obj,vartype,soln,optv[i],contextptr);
        }
        if (!soln.empty() && !is_inf(_abs(optv[i],contextptr)) &&
                (incumbent.empty() || is_strictly_greater(optv[i],optimum,contextptr))) {
            if (exactify_solution(soln,vartype,itol,contextptr)) { // update incumbent solution
                incumbent=soln;
                optimum=optv[i];
            }
            else { // mark this branch for further searching
                nxt.push_back(i);
                mv[i]=m;
                bv[i]=b;
                solnv[i]=soln;
            }
        }
        ++node_count;
        if (nodelimit>0 && node_count>=nodelimit)
            return;
    }
    // start with the branch that has higher upper bound
    if (nxt.size()==2 && is_strictly_greater(optv[1],optv[2],contextptr))
        reverse(nxt.begin(),nxt.end());
    // test marked branches recursively
    for (vector<int>::const_iterator it=nxt.begin();it!=nxt.end();++it) {
        branch_and_bound(*mv[*it]._VECTptr,*bv[*it]._VECTptr,obj,varsign,vartype,*solnv[*it]._VECTptr,
                incumbent,optimum,itol,use_affscale,depth+1,depthlimit,nodelimit,contextptr);
    }
}

bool is_realcons(const gen & g,GIAC_CONTEXT) {
    if (g.type==_VECT) {
        vecteur & v = *g._VECTptr;
        for (vecteur::const_iterator it=v.begin();it!=v.end();++it) {
            if (!is_realcons(*it,contextptr))
                return false;
        }
        return true;
    }
    return (is_inf(_abs(g,contextptr)) || _evalf(g,contextptr).type==_DOUBLE_);
}

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

bool interval2vecteur(const gen & g,vecteur & v,GIAC_CONTEXT) {
    if (g.type!=_SYMB || !g.is_symb_of_sommet(at_interval))
        return false;  // g is not an interval
    v=*g._SYMBptr->feuille._VECTptr;
    return is_realcons(v,contextptr);
}

vector<int> findvars(const vecteur & v, const vecteur & vars) {
    vector<int> indexes;
    for (vecteur::const_iterator it=v.begin();it!=v.end();++it) {
        if ((*it).type==_IDNT) {
            // the variable is specified as an identifier
            // find its index in 'vars'
            int i=0;
            for (;i<int(vars.size());++i) {
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

gen _lpsolve(const gen & g,GIAC_CONTEXT) {
    if (g.type==_STRNG && g.subtype==-1) return g;
    if (g.type!=_VECT || g.subtype!=_SEQ__VECT || g._VECTptr->size()<2)
        return gensizeerr(contextptr);
    vecteur & gv = *g._VECTptr,constr,vars;
    vars=*_lname(gv[0],contextptr)._VECTptr;  // detect variable names from the objective function
    int ibd;  // position of the parameter 'bd' (or 'opts', if 'bd' is not given)
    if (gv[1].type==_VECT) { // the parameter 'constr' is given
        constr=*gv[1]._VECTptr;
        vecteur constr_vars=*_lname(gv[1],contextptr)._VECTptr;  // scan variables in constraints
        // detect variables not appearing in the objective function
        for (vecteur::const_iterator it=constr_vars.begin();it!=constr_vars.end();++it) {
            if (!contains(vars,*it))
                vars.push_back(*it);
        }
        ibd=2;
    } else // the parameter 'constr' is not given
        ibd=1;
    vecteur lr,bconstr,cvars,ivars,bvars,pvars,nvars,initp;
    int dl=0,nl=0;  // branch&bound tree depth/node limit
    gen itol(0);
    bool maximize=false;
    bool all_nonneg=false;
    bool all_integer=false;
    bool all_binary=false;
    bool use_affscale=false;
    // check if any boundaries or options are set
    for (vecteur::const_iterator it=gv.begin()+ibd;it!=gv.end();++it) {
        if (is_integer(*it)) {
            switch(it->val) {
            case _LP_MAXIMIZE:
                maximize=true;
                break;
            }
        }
        else if (it->is_symb_of_sommet(at_equal)) {
            // parse the argument in form "option=value"
            vecteur ops(*it->_SYMBptr->feuille._VECTptr);
            if (ops[0].type==_IDNT && interval2vecteur(ops[1],lr,contextptr)) {
                // the boundaries for variable ops[0] are set
                if (!is_zero(lr[0]) && !is_inf(-lr[0]))
                    bconstr.push_back(symbolic(at_superieur_egal,makevecteur(ops[0],lr[0])));
                if (!is_zero(lr[1]) && !is_inf(lr[1]))
                    bconstr.push_back(symbolic(at_inferieur_egal,makevecteur(ops[0],lr[1])));
                if (is_positive(lr[0],contextptr))
                    // variable is nonnegative
                    pvars.push_back(ops[0]);
                else if (!is_strictly_positive(lr[1],contextptr))
                    nvars.push_back(ops[0]);
            }
            if (ops[0]==at_assume) { // parse assumptions
                if (is_integer(ops[1])) {
                    switch(ops[1].val) {
                    case _ZINT:
                    case _LP_INTEGER: // all variables are integer
                        all_integer=true;
                        ivars=vars;
                        break;
                    case _LP_BINARY: // all variables are binary
                        all_nonneg=true;
                        all_binary=true;
                        bvars=vars;
                        break;
                    case _NONNEGINT:
                    case _LP_NONNEGINT: // all variables are nonnegative integers
                        all_nonneg=true;
                        all_integer=true;
                        ivars=vars;
                        break;
                    case _LP_NONNEGATIVE: // all variables are nonnegative
                        all_nonneg=true;
                        break;
                    }
                }
            }
            if (is_integer(ops[0])) {
                switch(ops[0].val) {
                case _LP_VARIABLES: // specify continuous variables
                    if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
                        for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                            cvars.push_back(gen(i));
                        }
                    }
                    else if (ops[1].type==_VECT)
                        cvars=*ops[1]._VECTptr;
                    break;
                case _LP_INTEGERVARIABLES: // specify integer variables
                    if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
                        for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                            ivars.push_back(gen(i));
                        }
                    }
                    else if (ops[1].type==_VECT)
                        ivars=*ops[1]._VECTptr;
                    break;
                case _LP_BINARYVARIABLES: // specify binary variables
                    if (interval2vecteur(ops[1],lr,contextptr) && is_integer_vecteur(lr)) {
                        for (int i=int(lr[0].val);i<=int(lr[1].val);++i) {
                            bvars.push_back(gen(i));
                        }
                    }
                    else if (ops[1].type==_VECT)
                        bvars=*ops[1]._VECTptr;
                    break;
                case _LP_DEPTHLIMIT: // specify branch&bound tree depth limit
                    if (is_integer(ops[1]))
                        dl=ops[1].val;
                    break;
                case _LP_NODE_LIMIT: // specify branch&bound tree node limit
                    if (is_integer(ops[1]))
                        nl=ops[1].val;
                    break;
                case _LP_INTEGER_TOLERANCE: // specify integer tolerance for MIP
                    if (_evalf(ops[1],contextptr).type==_DOUBLE_ && is_positive(ops[1],contextptr))
                        itol=ops[1];
                    break;
                case _LP_INITIAL_POINT: // specify initial point for affine scaling algorithm
                    if (ops[1].type==_VECT)
                        initp=*ops[1]._VECTptr;
                    use_affscale=true;
                    break;
                case _LP_MAXIMIZE: // maximize=true/false for maximization/minimization
                    maximize=is_one(ops[1]);
                    break;
                case _LP_METHOD:
                    if (is_integer(ops[1])) {
                        switch (ops[1].val) {
                        case _LP_SIMPLEX:
                            use_affscale=false;
                            break;
                        case _LP_INTERIOR_POINT:
                            use_affscale=true;
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
    gen obj_ct(0); // the constant term of the objective function
    int nv=0; // number of variables
    vector<int> sv,varsign; // ith is 1 for variable xi nonnegative, -1 for negative and 0 for unconstrained
    matrice m;
    vecteur b,obj_orig;
    if (gv[0].type==_VECT && vars.size()==0) {
        // the problem is given in matrix form
        // objective: c=[c1,c2,...,cn], maximize/minimize c.x
        obj_orig=*gv[0]._VECTptr;
        nv=obj_orig.size(); // number of variables
        int n=constr.size();
        if ((nv==0 && n==0) || (n!=0 && n!=4 && n!=2))
            // improper specification of constraints, stop
            return gensizeerr(contextptr);
        if (n>0) {
            // constraints: [A,b,Aeq,beq] such that A.x<=b and/or Aeq.x=beq
            m=*constr[0]._VECTptr;  // matrice A
            sv=vector<int>(m.size(),-1);
            b=*constr[1]._VECTptr;  // vecteur b
            if (m.size()!=b.size())
                return gendimerr(contextptr);
            if (n==4) { // there are equation constraints
                vecteur &Aeq=*constr[2]._VECTptr,&beq=*constr[3]._VECTptr;
                if (!ckmatrix(Aeq) || Aeq.size()!=beq.size())
                    return gendimerr(contextptr);
                if (!Aeq.empty()) {
                    m=mergevecteur(Aeq,m);
                    b=mergevecteur(beq,b);
                }
            }
            if (!ckmatrix(m))
                return gendimerr(contextptr);
            if (nv==0) {
                nv=m.front()._VECTptr->size();
                obj_orig=vecteur(nv,gen(0));
            }
            if (nv!=int(m.front()._VECTptr->size()))
                return gendimerr(contextptr);
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
            matrice idn(midn(nv));
            for (int i=0;i<nv;++i) {
                if (!is_zero(bl[i]) && !is_inf(-bl[i])) {
                    m.push_back(*idn[i]._VECTptr);
                    sv.push_back(1);
                    b.push_back(bl[i]);
                }
                if (!is_inf(bu[i])) {
                    m.push_back(*idn[i]._VECTptr);
                    sv.push_back(-1);
                    b.push_back(bu[i]);
                }
                if (!all_nonneg) {
                    if (is_positive(bl[i],contextptr))
                        varsign[i]=1;
                    else if (!is_strictly_positive(bu[i],contextptr))
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
            cout << "Error: the objective function must be linear" << endl;
            return gentypeerr(contextptr);
        }
        nv=vars.size();
        varsign=vector<int>(nv,all_nonneg?1:0);
        constr=mergevecteur(constr,bconstr);
        // write the constraints in matrix form
        for (vecteur::const_iterator it=constr.begin();it!=constr.end();++it) {
            vecteur sides(*((*it)._SYMBptr->feuille._VECTptr)),c,bnd;
            if (it->is_symb_of_sommet(at_equal) && interval2vecteur(sides[1],bnd,contextptr)) {
                // a bounded expression was given as constraint
                if (!lincomb_coeff(sides[0],vars,c,r,contextptr)) {
                    cout << "Error: all constraints must be linear" << endl;
                    return gentypeerr(contextptr);
                }
                m=mergevecteur(m,vecteur(2,c));
                sv.push_back(1);
                sv.push_back(-1);
                b=mergevecteur(b,subvecteur(bnd,vecteur(2,r)));
                continue;
            }
            // turn constraint to vector form
            gen d=sides[0]-sides[1];
            if (!lincomb_coeff(d,vars,c,r,contextptr)) {
                cout << "Error: all constraints must be linear" << endl;
                return gentypeerr(contextptr);
            }
            if (it->is_symb_of_sommet(at_equal)) {
                m=mergevecteur(vecteur(1,c),m);
                b=mergevecteur(vecteur(1,-r),b);
                continue;
            }
            else if (it->is_symb_of_sommet(at_inferieur_egal)) {
                if (d.type==_IDNT && find(vars.begin(),vars.end(),d)!=vars.end())
                    nvars.push_back(d);
                else {
                    sv.push_back(-1);
                    m.push_back(c);
                    b.push_back(-r);
                }
            }
            else if (it->is_symb_of_sommet(at_superieur_egal)) {
                if (d.type==_IDNT && find(vars.begin(),vars.end(),d)!=vars.end())
                    pvars.push_back(d);
                else {
                    sv.push_back(1);
                    m.push_back(c);
                    b.push_back(-r);
                }
            }
            else {
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
    } else // the problem is given improperly, stop
        return gentypeerr(contextptr);
    if (m.empty()) {
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
        varsign[*it]=1; // binary variables are always nonnegative
        // append constraint of type xb<=1
        m.push_back(midn(nv)[*it]);
        sv.push_back(-1);
        b.push_back(gen(1));
    }
    vector<int> vc=findvars(cvars,vars);
    for (vector<int>::const_iterator it=vc.begin();it!=vc.end();++it) {
        vartype[*it]=0;
    }
    int nc=m.size(),ns=sv.size();
    bool has_initp=use_affscale && !initp.empty();
    if (has_initp) {
        if (int(initp.size())!=nv)
            return gendimerr(contextptr);
        initp=mergevecteur(initp,vecteur(ns,gen(1)));
    }
    m=mtran(m);
    // add slack/surplus variables
    matrice idn(midn(nc));
    for (int i=nc-ns;i<nc;++i) {
        m.push_back(multvecteur(gen(-sv[i-nc+ns]),*idn[i]._VECTptr));
    }
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
            vartype.insert(vartype.begin()+i,vartype[i]);
            if (has_initp) {
                if (is_positive(initp[i],contextptr)) {
                    initp[i]+=gen(1);
                    initp.insert(initp.begin()+i,gen(1));
                }
                else {
                    initp[i]=-initp[i]+gen(1);
                    initp.insert(initp.begin()+i+1,gen(1));
                }
            }
        }
    }
    m=mtran(m);
    nv=obj.size();
    // solve the problem
    vecteur soln;
    gen optimum;
    if (!maximize)
        obj=-obj;
    if (use_affscale) {
        soln=initp;
        m=*_evalf(m,contextptr)._VECTptr;
        b=*_evalf(b,contextptr)._VECTptr;
        obj=*_evalf(obj,contextptr)._VECTptr;
        optimum=affscale(m,b,obj,soln,true,contextptr);
    }
    else {
        simplex_prepare(m,b,contextptr);
        simplex_twophase(m,b,obj,soln,optimum,contextptr);
    }
    if (soln.empty())
        return soln;
    if (is_inf(_abs(optimum,contextptr)))
        return makevecteur(maximize?optimum:-optimum,vecteur(0));
    if (!exactify_solution(soln,vartype,itol,contextptr)) { // apply branch & bound method
        vecteur isoln;
        gen ioptimum;
        node_count=0;
        cut_count=0;
        if (use_affscale)
            itol=_max(makesequence(gen(epsilon(contextptr)*100),itol),contextptr);
        branch_and_bound(m,b,obj,varsign,vartype,soln,isoln,ioptimum,itol,use_affscale,0,dl,nl,contextptr);
        cout << "branch and bound summary: " << node_count << " subproblems examined";
        if (use_affscale)
            cout << endl;
        else
            cout << ", " << cut_count << " GMI cut" << (cut_count==1?"":"s") << " added" << endl;
        soln=isoln;
        optimum=ioptimum;
        if (soln.empty()) // no feasible integer solution
            return soln;
    }
    if (!is_exactly_zero(itol)) {
        soln=*_evalf(soln,contextptr)._VECTptr;
        optimum=_evalf(optimum,contextptr);
    }
    if (!maximize)
        optimum=-optimum;
    // recreate variables
    int i=0;
    soln.resize(nv);
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
    vecteur v=vars.empty()?soln:*_zip(makesequence(at_equal,vars,soln),contextptr)._VECTptr;
    if ((gv[0].type==_VECT && int(gv[0]._VECTptr->size())==0) || is_zero(gv[0]))
        return _simplify(v,contextptr);
    return makevecteur(_simplify(optimum+obj_ct,contextptr),_simplify(v,contextptr));
}
static const char _lpsolve_s []="lpsolve";
static define_unary_function_eval (__lpsolve,&_lpsolve,_lpsolve_s);
define_unary_function_ptr5(at_lpsolve,alias_at_lpsolve,&__lpsolve,0,true)

#ifndef NO_NAMESPACE_GIAC
}
#endif // ndef NO_NAMESPACE_GIAC
