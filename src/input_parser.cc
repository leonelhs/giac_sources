/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         giac_yyparse
#define yylex           giac_yylex
#define yyerror         giac_yyerror
#define yylval          giac_yylval
#define yychar          giac_yychar
#define yydebug         giac_yydebug
#define yynerrs         giac_yynerrs


/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 24 "input_parser.yy"

         #define YYPARSE_PARAM scanner
         #define YYLEX_PARAM   scanner
	 
/* Line 268 of yacc.c  */
#line 33 "input_parser.yy"

#include "giacPCH.h"
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "first.h"
#include <stdexcept>
#include <cstdlib>
#include "giacPCH.h"
#include "index.h"
#include "gen.h"
#define YYSTYPE giac::gen
#define YY_EXTRA_TYPE  const giac::context *
#include "lexer.h"
#include "input_lexer.h"
#include "usual.h"
#include "derive.h"
#include "sym2poly.h"
#include "vecteur.h"
#include "modpoly.h"
#include "alg_ext.h"
#include "prog.h"
#include "rpn.h"
#include "intg.h"
#include "plot.h"
#include "maple.h"
using namespace std;

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

// It seems there is a bison bug when it reallocates space for the stack
// therefore I redefine YYINITDEPTH to 4000 (max size is YYMAXDEPTH)
// instead of 200
// Feel free to change if you need but then readjust YYMAXDEPTH
#if defined RTOS_THREADX || defined NSPIRE
#define YYINITDEPTH 100
#define YYMAXDEPTH 101
#else // RTOS_THREADX
// Note that the compilation by bison with -v option generates a file y.output
// to debug the grammar, compile input_parser.yy with bison
// then add yydebug=1 in input_parser.cc at the beginning of yyparse (
#define YYDEBUG 1
#ifdef GNUWINCE
#define YYINITDEPTH 1000
#else 
#define YYINITDEPTH 4000
#define YYMAXDEPTH 20000
#define YYERROR_VERBOSE 1
#endif // GNUWINCE
#endif // RTOS_THREADX


gen polynome_or_sparse_poly1(const gen & coeff, const gen & index){
  if (index.type==_VECT){
    index_t i;
    const_iterateur it=index._VECTptr->begin(),itend=index._VECTptr->end();
    i.reserve(itend-it);
    for (;it!=itend;++it){
      if (it->type!=_INT_)
         return gentypeerr();
      i.push_back(it->val);
    }
    monomial<gen> m(coeff,i);
    return polynome(m);
  }
  else {
    sparse_poly1 res;
    res.push_back(monome(coeff,index));
    return res;
  }
}


/* Line 268 of yacc.c  */
#line 161 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_NUMBER = 258,
     T_SYMBOL = 259,
     T_LITERAL = 260,
     T_DIGITS = 261,
     T_STRING = 262,
     T_END_INPUT = 263,
     T_EXPRESSION = 264,
     T_UNARY_OP = 265,
     T_OF = 266,
     T_NOT = 267,
     T_TYPE_ID = 268,
     T_VIRGULE = 269,
     T_AFFECT = 270,
     T_MAPSTO = 271,
     T_BEGIN_PAR = 272,
     T_END_PAR = 273,
     T_PLUS = 274,
     T_MOINS = 275,
     T_FOIS = 276,
     T_DIV = 277,
     T_MOD = 278,
     T_POW = 279,
     T_QUOTED_BINARY = 280,
     T_QUOTE = 281,
     T_PRIME = 282,
     T_TEST_EQUAL = 283,
     T_EQUAL = 284,
     T_INTERVAL = 285,
     T_UNION = 286,
     T_INTERSECT = 287,
     T_MINUS = 288,
     T_AND_OP = 289,
     T_COMPOSE = 290,
     T_DOLLAR = 291,
     T_DOLLAR_MAPLE = 292,
     T_INDEX_BEGIN = 293,
     T_VECT_BEGIN = 294,
     T_VECT_DISPATCH = 295,
     T_VECT_END = 296,
     T_SET_BEGIN = 297,
     T_SET_END = 298,
     T_SEMI = 299,
     T_DEUXPOINTS = 300,
     T_DOUBLE_DEUX_POINTS = 301,
     T_IF = 302,
     T_RPN_IF = 303,
     T_ELIF = 304,
     T_THEN = 305,
     T_ELSE = 306,
     T_IFTE = 307,
     T_SWITCH = 308,
     T_CASE = 309,
     T_DEFAULT = 310,
     T_ENDCASE = 311,
     T_FOR = 312,
     T_FROM = 313,
     T_TO = 314,
     T_DO = 315,
     T_BY = 316,
     T_WHILE = 317,
     T_MUPMAP_WHILE = 318,
     T_RPN_WHILE = 319,
     T_REPEAT = 320,
     T_UNTIL = 321,
     T_IN = 322,
     T_START = 323,
     T_BREAK = 324,
     T_CONTINUE = 325,
     T_TRY = 326,
     T_CATCH = 327,
     T_TRY_CATCH = 328,
     T_PROC = 329,
     T_BLOC = 330,
     T_BLOC_BEGIN = 331,
     T_BLOC_END = 332,
     T_RETURN = 333,
     T_LOCAL = 334,
     T_LOCALBLOC = 335,
     T_NAME = 336,
     T_PROGRAM = 337,
     T_NULL = 338,
     T_ARGS = 339,
     T_FACTORIAL = 340,
     T_RPN_OP = 341,
     T_RPN_BEGIN = 342,
     T_RPN_END = 343,
     T_STACK = 344,
     T_GROUPE_BEGIN = 345,
     T_GROUPE_END = 346,
     T_LINE_BEGIN = 347,
     T_LINE_END = 348,
     T_VECTOR_BEGIN = 349,
     T_VECTOR_END = 350,
     T_CURVE_BEGIN = 351,
     T_CURVE_END = 352,
     T_ROOTOF_BEGIN = 353,
     T_ROOTOF_END = 354,
     T_SPOLY1_BEGIN = 355,
     T_SPOLY1_END = 356,
     T_POLY1_BEGIN = 357,
     T_POLY1_END = 358,
     T_MATRICE_BEGIN = 359,
     T_MATRICE_END = 360,
     T_ASSUME_BEGIN = 361,
     T_ASSUME_END = 362,
     T_HELP = 363,
     TI_DEUXPOINTS = 364,
     TI_LOCAL = 365,
     TI_LOOP = 366,
     TI_FOR = 367,
     TI_WHILE = 368,
     TI_STO = 369,
     TI_TRY = 370,
     TI_DIALOG = 371,
     T_PIPE = 372,
     TI_DEFINE = 373,
     TI_PRGM = 374,
     TI_SEMI = 375,
     TI_HASH = 376,
     T_ACCENTGRAVE = 377,
     T_MAPLELIB = 378,
     T_INTERROGATION = 379,
     T_UNIT = 380,
     T_BIDON = 381,
     T_LOGO = 382,
     T_SQ = 383,
     T_CASE38 = 384,
     T_IFERR = 385,
     T_MOINS38 = 386,
     T_NEG38 = 387,
     T_UNARY_OP_38 = 388,
     T_FUNCTION = 389,
     T_IMPMULT = 390
   };
#endif
/* Tokens.  */
#define T_NUMBER 258
#define T_SYMBOL 259
#define T_LITERAL 260
#define T_DIGITS 261
#define T_STRING 262
#define T_END_INPUT 263
#define T_EXPRESSION 264
#define T_UNARY_OP 265
#define T_OF 266
#define T_NOT 267
#define T_TYPE_ID 268
#define T_VIRGULE 269
#define T_AFFECT 270
#define T_MAPSTO 271
#define T_BEGIN_PAR 272
#define T_END_PAR 273
#define T_PLUS 274
#define T_MOINS 275
#define T_FOIS 276
#define T_DIV 277
#define T_MOD 278
#define T_POW 279
#define T_QUOTED_BINARY 280
#define T_QUOTE 281
#define T_PRIME 282
#define T_TEST_EQUAL 283
#define T_EQUAL 284
#define T_INTERVAL 285
#define T_UNION 286
#define T_INTERSECT 287
#define T_MINUS 288
#define T_AND_OP 289
#define T_COMPOSE 290
#define T_DOLLAR 291
#define T_DOLLAR_MAPLE 292
#define T_INDEX_BEGIN 293
#define T_VECT_BEGIN 294
#define T_VECT_DISPATCH 295
#define T_VECT_END 296
#define T_SET_BEGIN 297
#define T_SET_END 298
#define T_SEMI 299
#define T_DEUXPOINTS 300
#define T_DOUBLE_DEUX_POINTS 301
#define T_IF 302
#define T_RPN_IF 303
#define T_ELIF 304
#define T_THEN 305
#define T_ELSE 306
#define T_IFTE 307
#define T_SWITCH 308
#define T_CASE 309
#define T_DEFAULT 310
#define T_ENDCASE 311
#define T_FOR 312
#define T_FROM 313
#define T_TO 314
#define T_DO 315
#define T_BY 316
#define T_WHILE 317
#define T_MUPMAP_WHILE 318
#define T_RPN_WHILE 319
#define T_REPEAT 320
#define T_UNTIL 321
#define T_IN 322
#define T_START 323
#define T_BREAK 324
#define T_CONTINUE 325
#define T_TRY 326
#define T_CATCH 327
#define T_TRY_CATCH 328
#define T_PROC 329
#define T_BLOC 330
#define T_BLOC_BEGIN 331
#define T_BLOC_END 332
#define T_RETURN 333
#define T_LOCAL 334
#define T_LOCALBLOC 335
#define T_NAME 336
#define T_PROGRAM 337
#define T_NULL 338
#define T_ARGS 339
#define T_FACTORIAL 340
#define T_RPN_OP 341
#define T_RPN_BEGIN 342
#define T_RPN_END 343
#define T_STACK 344
#define T_GROUPE_BEGIN 345
#define T_GROUPE_END 346
#define T_LINE_BEGIN 347
#define T_LINE_END 348
#define T_VECTOR_BEGIN 349
#define T_VECTOR_END 350
#define T_CURVE_BEGIN 351
#define T_CURVE_END 352
#define T_ROOTOF_BEGIN 353
#define T_ROOTOF_END 354
#define T_SPOLY1_BEGIN 355
#define T_SPOLY1_END 356
#define T_POLY1_BEGIN 357
#define T_POLY1_END 358
#define T_MATRICE_BEGIN 359
#define T_MATRICE_END 360
#define T_ASSUME_BEGIN 361
#define T_ASSUME_END 362
#define T_HELP 363
#define TI_DEUXPOINTS 364
#define TI_LOCAL 365
#define TI_LOOP 366
#define TI_FOR 367
#define TI_WHILE 368
#define TI_STO 369
#define TI_TRY 370
#define TI_DIALOG 371
#define T_PIPE 372
#define TI_DEFINE 373
#define TI_PRGM 374
#define TI_SEMI 375
#define TI_HASH 376
#define T_ACCENTGRAVE 377
#define T_MAPLELIB 378
#define T_INTERROGATION 379
#define T_UNIT 380
#define T_BIDON 381
#define T_LOGO 382
#define T_SQ 383
#define T_CASE38 384
#define T_IFERR 385
#define T_MOINS38 386
#define T_NEG38 387
#define T_UNARY_OP_38 388
#define T_FUNCTION 389
#define T_IMPMULT 390




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 473 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  151
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   13784

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  136
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  251
/* YYNRULES -- Number of states.  */
#define YYNSTATES  593

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   390

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    16,    18,    21,    26,
      30,    33,    39,    47,    49,    51,    58,    65,    72,    79,
      88,    92,    96,   100,   104,   108,   112,   116,   121,   126,
     131,   133,   135,   137,   141,   146,   150,   154,   158,   164,
     168,   171,   175,   179,   183,   187,   191,   195,   199,   203,
     206,   209,   213,   217,   221,   224,   227,   230,   236,   240,
     242,   246,   249,   254,   259,   261,   266,   271,   276,   280,
     282,   285,   288,   295,   300,   306,   311,   313,   318,   320,
     324,   328,   333,   335,   338,   340,   344,   346,   348,   356,
     366,   376,   384,   394,   396,   401,   407,   415,   419,   421,
     425,   428,   434,   438,   442,   445,   449,   453,   457,   461,
     465,   467,   471,   476,   483,   490,   494,   498,   502,   504,
     507,   511,   514,   518,   521,   523,   525,   528,   530,   534,
     539,   541,   548,   556,   560,   562,   567,   575,   584,   592,
     602,   611,   620,   630,   640,   651,   656,   660,   668,   678,
     684,   691,   697,   703,   711,   716,   718,   726,   731,   736,
     740,   742,   745,   749,   754,   760,   765,   772,   778,   782,
     796,   809,   822,   831,   835,   838,   841,   849,   863,   873,
     879,   885,   887,   891,   895,   899,   903,   909,   912,   916,
     919,   922,   923,   926,   929,   934,   937,   941,   945,   947,
     951,   953,   957,   961,   965,   969,   971,   975,   977,   979,
     980,   982,   983,   985,   987,   990,   993,   994,   997,  1001,
    1003,  1004,  1007,  1008,  1011,  1014,  1017,  1019,  1021,  1022,
    1026,  1029,  1033,  1038,  1040,  1044,  1050,  1057,  1059,  1062,
    1064,  1067,  1068,  1072,  1078,  1079,  1082,  1088,  1089,  1092,
    1099,  1107
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     137,     0,    -1,   138,    -1,   139,     8,    -1,   139,    44,
       8,    -1,   139,    44,   138,    -1,     3,    -1,     3,     4,
      -1,     3,     4,    24,     3,    -1,     3,     4,   128,    -1,
       3,     5,    -1,     3,    10,    17,   139,    18,    -1,     3,
      10,    17,   139,    18,    24,     3,    -1,     7,    -1,     9,
      -1,   140,    17,   148,    18,    15,   156,    -1,   140,    17,
     148,    18,    15,   139,    -1,   139,   114,   140,    17,   148,
      18,    -1,   139,   114,   140,    38,   139,    41,    -1,   139,
     114,   140,    38,    40,   139,    41,    41,    -1,   139,   114,
     140,    -1,   139,   114,    10,    -1,   139,   114,    19,    -1,
     139,   114,    21,    -1,   139,   114,    22,    -1,   139,   114,
      14,    -1,   139,   114,   114,    -1,   139,   114,   125,   139,
      -1,   140,    17,   148,    18,    -1,   139,    17,   148,    18,
      -1,   140,    -1,     5,    -1,     6,    -1,     6,    15,   139,
      -1,     6,    17,   139,    18,    -1,     6,    17,    18,    -1,
     139,   114,     6,    -1,   139,    28,   139,    -1,   139,    28,
     140,    28,   139,    -1,   139,    29,   139,    -1,    29,   139,
      -1,   139,    19,   139,    -1,   139,    20,   139,    -1,   139,
     131,   139,    -1,   139,    21,   139,    -1,   139,    22,   139,
      -1,   139,    24,   139,    -1,   139,    23,   139,    -1,   139,
      30,   139,    -1,   139,    30,    -1,    30,   139,    -1,    30,
      14,   139,    -1,   139,    34,   139,    -1,   139,    45,   139,
      -1,    20,   139,    -1,   132,   139,    -1,    19,   139,    -1,
     100,   139,    14,   139,   101,    -1,    98,   139,    99,    -1,
      11,    -1,   139,    15,   139,    -1,    12,   139,    -1,    84,
      17,   139,    18,    -1,    84,    38,   139,    41,    -1,    84,
      -1,    10,    17,   139,    18,    -1,   133,    17,   139,    18,
      -1,    10,    38,   139,    41,    -1,    10,    17,    18,    -1,
      10,    -1,   139,    27,    -1,   139,    85,    -1,    47,   139,
      50,   156,    51,   156,    -1,    47,   139,    50,   156,    -1,
      47,   139,    50,   149,   157,    -1,    52,    17,   139,    18,
      -1,    52,    -1,    82,    17,   139,    18,    -1,    82,    -1,
     139,    16,   156,    -1,   139,    16,   139,    -1,    75,    17,
     139,    18,    -1,    75,    -1,    78,   139,    -1,    78,    -1,
      26,    78,    26,    -1,    69,    -1,    70,    -1,    57,   140,
      67,   139,    60,   149,    77,    -1,    57,   140,   153,    59,
     139,   152,   154,   149,    77,    -1,    57,   140,   153,   152,
      59,   139,    60,   149,    77,    -1,    57,   140,   153,   152,
      60,   149,    77,    -1,    57,   140,   153,   152,    63,   139,
      60,   149,    77,    -1,    57,    -1,    65,   149,    66,   139,
      -1,    65,   149,    66,   139,    77,    -1,   130,   149,    50,
     149,    51,   149,    77,    -1,   129,   162,    77,    -1,    13,
      -1,    26,    13,    26,    -1,    37,   139,    -1,   139,    37,
     140,    67,   139,    -1,   139,    37,   139,    -1,   139,    36,
     139,    -1,    36,     4,    -1,   139,    35,   139,    -1,   139,
      31,   139,    -1,   139,    32,   139,    -1,   139,    33,   139,
      -1,   139,   117,   139,    -1,    25,    -1,    26,   139,    26,
      -1,   139,    38,   139,    41,    -1,   139,    38,    40,   139,
      41,    41,    -1,    17,   139,    18,    17,   148,    18,    -1,
      17,   139,    18,    -1,    40,   148,    41,    -1,   139,    14,
     139,    -1,    83,    -1,   108,   139,    -1,   139,   124,   139,
      -1,   125,   139,    -1,   139,   125,   139,    -1,   139,   128,
      -1,     1,    -1,   142,    -1,   127,   139,    -1,   127,    -1,
     127,    17,    18,    -1,    80,    17,   139,    18,    -1,    80,
      -1,    47,    17,   139,    18,   156,   155,    -1,    47,    17,
     139,    18,   139,    44,   155,    -1,    87,   150,    88,    -1,
     123,    -1,   123,    38,   139,    41,    -1,    74,    17,   148,
      18,   141,   149,    77,    -1,    74,   140,    17,   148,    18,
     141,   149,    77,    -1,    74,   140,    17,   148,    18,   149,
      77,    -1,    74,   140,    17,   148,    18,    76,   141,   149,
      77,    -1,    74,    17,   148,    18,   141,    76,   149,    77,
      -1,   140,    17,   148,    18,    74,   141,   149,    77,    -1,
     140,    17,   148,    18,    15,    74,   141,   149,    77,    -1,
      57,    17,   147,    44,   147,    44,   147,    18,   156,    -1,
      57,    17,   147,    44,   147,    44,   147,    18,   139,    44,
      -1,    57,    17,   139,    18,    -1,   139,    67,   139,    -1,
      40,   139,    57,   145,    67,   139,    41,    -1,    40,   139,
      57,   145,    67,   139,    47,   139,    41,    -1,    62,    17,
     139,    18,   156,    -1,    62,    17,   139,    18,   139,    44,
      -1,    62,   139,    60,   149,    77,    -1,    63,   139,    60,
     149,    77,    -1,    71,   156,    72,    17,   139,    18,   156,
      -1,    73,    17,   139,    18,    -1,    73,    -1,    53,    17,
     139,    18,    76,   160,    77,    -1,    54,    17,     4,    18,
      -1,    54,   139,   161,    56,    -1,   122,   151,   122,    -1,
      86,    -1,    78,   109,    -1,   111,   149,   158,    -1,    47,
     139,   109,   139,    -1,   115,   149,    51,   149,   158,    -1,
     115,   149,    51,   158,    -1,   115,   149,   109,    51,   149,
     158,    -1,   115,   149,   109,    51,   158,    -1,   139,   120,
     139,    -1,   109,   140,    17,   148,    18,   119,   149,   109,
     110,   148,   109,   149,   158,    -1,   109,   140,    17,   148,
      18,   119,   149,   110,   148,   109,   149,   158,    -1,   109,
     140,    17,   148,    18,   119,   109,   110,   148,   109,   149,
     158,    -1,   109,   140,    17,   148,    18,   119,   149,   158,
      -1,   116,   149,   158,    -1,   116,   156,    -1,   109,   139,
      -1,   118,   140,    17,   148,    18,    29,   139,    -1,   118,
     140,    17,   148,    18,    29,   119,   109,   110,   148,   109,
     149,   158,    -1,   118,   140,    17,   148,    18,    29,   119,
     149,   158,    -1,   112,   148,   109,   149,   158,    -1,   113,
     139,   109,   149,   158,    -1,     4,    -1,     4,    46,    13,
      -1,     4,    46,    10,    -1,     4,    46,     4,    -1,     4,
      46,   133,    -1,     4,    46,    26,   139,    26,    -1,    46,
       4,    -1,     3,    46,     4,    -1,    13,     4,    -1,   121,
     139,    -1,    -1,   141,   143,    -1,   144,   141,    -1,    89,
      17,   139,    18,    -1,    89,    83,    -1,    79,   145,    44,
      -1,    81,   139,    44,    -1,   146,    -1,   145,    14,   146,
      -1,   140,    -1,     4,    15,   139,    -1,     4,    29,   139,
      -1,     4,    45,   139,    -1,    17,   146,    18,    -1,    10,
      -1,    10,    46,   139,    -1,    13,    -1,     3,    -1,    -1,
     139,    -1,    -1,   139,    -1,   139,    -1,   149,   139,    -1,
     149,   163,    -1,    -1,   151,   150,    -1,   151,    14,   150,
      -1,    10,    -1,    -1,    61,   139,    -1,    -1,    15,   139,
      -1,    29,   139,    -1,    58,   139,    -1,    44,    -1,    60,
      -1,    -1,   159,   139,    44,    -1,   159,   156,    -1,    76,
     149,    77,    -1,    76,   141,   149,    77,    -1,   158,    -1,
     159,   149,   158,    -1,    49,   139,    50,   149,   157,    -1,
     109,    49,   139,    50,   149,   157,    -1,    77,    -1,   109,
      77,    -1,    51,    -1,   109,    51,    -1,    -1,    55,    45,
     156,    -1,    54,     3,    45,   156,   160,    -1,    -1,    55,
     149,    -1,    11,     3,    60,   149,   161,    -1,    -1,    55,
     149,    -1,    47,   139,    50,   149,    77,   162,    -1,    47,
     139,    50,   149,    77,    44,   162,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   190,   190,   198,   199,   200,   203,   204,   205,   206,
     207,   208,   209,   211,   212,   215,   216,   217,   218,   222,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   252,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   266,   267,   268,   273,   278,   284,   285,   291,
     292,   293,   294,   295,   296,   297,   307,   312,   316,   323,
     326,   327,   328,   329,   330,   333,   334,   335,   336,   337,
     341,   348,   349,   351,   352,   353,   355,   356,   357,   382,
     395,   408,   412,   416,   421,   426,   432,   436,   437,   441,
     442,   443,   444,   445,   446,   447,   448,   449,   450,   451,
     454,   455,   460,   464,   468,   469,   486,   495,   501,   502,
     503,   504,   509,   513,   514,   523,   524,   525,   526,   527,
     531,   532,   535,   540,   541,   542,   543,   548,   553,   558,
     563,   568,   573,   578,   579,   580,   581,   582,   583,   584,
     588,   591,   595,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     619,   623,   627,   630,   631,   632,   633,   634,   638,   639,
     658,   670,   671,   676,   677,   678,   679,   680,   681,   689,
     694,   698,   699,   700,   704,   705,   708,   711,   714,   715,
     722,   723,   724,   725,   726,   727,   728,   729,   737,   747,
     748,   751,   752,   755,   757,   762,   765,   766,   767,   770,
     840,   841,   844,   845,   846,   847,   850,   851,   854,   855,
     856,   860,   863,   870,   871,   875,   878,   883,   884,   887,
     888,   891,   892,   893,   896,   897,   898,   901,   902,   903,
     904,   907
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_NUMBER", "T_SYMBOL", "T_LITERAL",
  "T_DIGITS", "T_STRING", "T_END_INPUT", "T_EXPRESSION", "T_UNARY_OP",
  "T_OF", "T_NOT", "T_TYPE_ID", "T_VIRGULE", "T_AFFECT", "T_MAPSTO",
  "T_BEGIN_PAR", "T_END_PAR", "T_PLUS", "T_MOINS", "T_FOIS", "T_DIV",
  "T_MOD", "T_POW", "T_QUOTED_BINARY", "T_QUOTE", "T_PRIME",
  "T_TEST_EQUAL", "T_EQUAL", "T_INTERVAL", "T_UNION", "T_INTERSECT",
  "T_MINUS", "T_AND_OP", "T_COMPOSE", "T_DOLLAR", "T_DOLLAR_MAPLE",
  "T_INDEX_BEGIN", "T_VECT_BEGIN", "T_VECT_DISPATCH", "T_VECT_END",
  "T_SET_BEGIN", "T_SET_END", "T_SEMI", "T_DEUXPOINTS",
  "T_DOUBLE_DEUX_POINTS", "T_IF", "T_RPN_IF", "T_ELIF", "T_THEN", "T_ELSE",
  "T_IFTE", "T_SWITCH", "T_CASE", "T_DEFAULT", "T_ENDCASE", "T_FOR",
  "T_FROM", "T_TO", "T_DO", "T_BY", "T_WHILE", "T_MUPMAP_WHILE",
  "T_RPN_WHILE", "T_REPEAT", "T_UNTIL", "T_IN", "T_START", "T_BREAK",
  "T_CONTINUE", "T_TRY", "T_CATCH", "T_TRY_CATCH", "T_PROC", "T_BLOC",
  "T_BLOC_BEGIN", "T_BLOC_END", "T_RETURN", "T_LOCAL", "T_LOCALBLOC",
  "T_NAME", "T_PROGRAM", "T_NULL", "T_ARGS", "T_FACTORIAL", "T_RPN_OP",
  "T_RPN_BEGIN", "T_RPN_END", "T_STACK", "T_GROUPE_BEGIN", "T_GROUPE_END",
  "T_LINE_BEGIN", "T_LINE_END", "T_VECTOR_BEGIN", "T_VECTOR_END",
  "T_CURVE_BEGIN", "T_CURVE_END", "T_ROOTOF_BEGIN", "T_ROOTOF_END",
  "T_SPOLY1_BEGIN", "T_SPOLY1_END", "T_POLY1_BEGIN", "T_POLY1_END",
  "T_MATRICE_BEGIN", "T_MATRICE_END", "T_ASSUME_BEGIN", "T_ASSUME_END",
  "T_HELP", "TI_DEUXPOINTS", "TI_LOCAL", "TI_LOOP", "TI_FOR", "TI_WHILE",
  "TI_STO", "TI_TRY", "TI_DIALOG", "T_PIPE", "TI_DEFINE", "TI_PRGM",
  "TI_SEMI", "TI_HASH", "T_ACCENTGRAVE", "T_MAPLELIB", "T_INTERROGATION",
  "T_UNIT", "T_BIDON", "T_LOGO", "T_SQ", "T_CASE38", "T_IFERR",
  "T_MOINS38", "T_NEG38", "T_UNARY_OP_38", "T_FUNCTION", "T_IMPMULT",
  "$accept", "input", "correct_input", "exp", "symbol", "entete", "stack",
  "local", "nom", "suite_symbol", "affectable_symbol", "exp_or_empty",
  "suite", "prg_suite", "rpn_suite", "rpn_token", "step", "from",
  "loop38_do", "else", "bloc", "elif", "ti_bloc_end", "ti_else", "switch",
  "case", "case38", "semi", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   136,   137,   138,   138,   138,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   141,   141,   141,   142,   142,   143,   144,   145,   145,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   147,
     147,   148,   148,   149,   149,   149,   150,   150,   150,   151,
     152,   152,   153,   153,   153,   153,   154,   154,   155,   155,
     155,   156,   156,   157,   157,   157,   157,   158,   158,   159,
     159,   160,   160,   160,   161,   161,   161,   162,   162,   162,
     162,   163
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     3,     1,     2,     4,     3,
       2,     5,     7,     1,     1,     6,     6,     6,     6,     8,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     4,
       1,     1,     1,     3,     4,     3,     3,     3,     5,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     3,     3,     3,     2,     2,     2,     5,     3,     1,
       3,     2,     4,     4,     1,     4,     4,     4,     3,     1,
       2,     2,     6,     4,     5,     4,     1,     4,     1,     3,
       3,     4,     1,     2,     1,     3,     1,     1,     7,     9,
       9,     7,     9,     1,     4,     5,     7,     3,     1,     3,
       2,     5,     3,     3,     2,     3,     3,     3,     3,     3,
       1,     3,     4,     6,     6,     3,     3,     3,     1,     2,
       3,     2,     3,     2,     1,     1,     2,     1,     3,     4,
       1,     6,     7,     3,     1,     4,     7,     8,     7,     9,
       8,     8,     9,     9,    10,     4,     3,     7,     9,     5,
       6,     5,     5,     7,     4,     1,     7,     4,     4,     3,
       1,     2,     3,     4,     5,     4,     6,     5,     3,    13,
      12,    12,     8,     3,     2,     2,     7,    13,     9,     5,
       5,     1,     3,     3,     3,     3,     5,     2,     3,     2,
       2,     0,     2,     2,     4,     2,     3,     3,     1,     3,
       1,     3,     3,     3,     3,     1,     3,     1,     1,     0,
       1,     0,     1,     1,     2,     2,     0,     2,     3,     1,
       0,     2,     0,     2,     2,     2,     1,     1,     0,     3,
       2,     3,     4,     1,     3,     5,     6,     1,     2,     1,
       2,     0,     3,     5,     0,     2,     5,     0,     2,     6,
       7,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   124,     6,   181,    31,    32,    13,    14,    69,    59,
       0,    98,     0,     0,     0,   110,     0,     0,     0,     0,
       0,     0,     0,     0,    76,     0,     0,    93,     0,     0,
       0,    86,    87,     0,   155,     0,    82,     0,   130,    78,
     118,    64,   160,   216,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,     0,     0,
     247,     0,     0,     0,     0,     2,     0,    30,   125,     7,
      10,     0,     0,     0,     0,     0,     0,     0,    61,   189,
       0,    56,    54,    98,     0,     0,    40,     0,    50,   104,
     100,   212,     0,   187,     0,     0,     0,     0,     0,   244,
       0,     0,     0,   222,     0,     0,     0,   213,     0,     0,
       0,     0,     0,     0,     0,     0,    83,     0,     0,     0,
       0,   219,     0,   216,     0,   195,     0,     0,   119,   175,
      30,     0,   212,     0,     0,     0,     0,   174,     0,   190,
       0,     0,   121,     0,   126,     0,     0,     0,     0,    55,
       0,     1,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,   123,     0,     0,     0,     9,     0,
     188,   184,   183,   182,     0,   185,    33,    35,     0,    68,
       0,     0,   115,    99,     0,   111,    51,     0,   116,     0,
       0,     0,     0,     0,   181,     0,     0,     0,   210,     0,
       0,     0,     0,     0,   220,     0,     0,     0,   251,     0,
     214,   215,     0,     0,   191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   216,   217,     0,    58,
       0,     0,   237,     0,   162,     0,     0,     0,     0,   173,
       0,   159,     0,   128,     0,     0,    97,     0,     0,   117,
      60,    80,    79,     0,    41,    42,    44,    45,    47,    46,
      37,    30,    39,    48,   106,   107,   108,    52,   105,   103,
     102,    30,     0,     0,     4,     5,    53,   146,    36,    21,
      25,    22,    23,    24,    26,     0,    20,   109,   168,   120,
     122,    43,     0,     8,     0,     0,    34,    65,    67,     0,
     208,   181,   205,   207,     0,   200,     0,   198,     0,     0,
      73,   163,    75,     0,   157,     0,     0,   158,   145,     0,
     223,   224,   225,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,   192,     0,   193,   231,     0,   154,   191,
       0,    81,   129,    77,    62,    63,   218,   194,   117,     0,
     238,     0,     0,     0,   165,     0,     0,   135,     0,     0,
      66,    29,     0,     0,     0,   112,    27,     0,     0,    28,
      11,   186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   228,     0,   239,     0,    74,   233,     0,     0,
     241,     0,   210,     0,     0,   220,   221,     0,     0,     0,
       0,   149,   151,   152,    95,   197,     0,   232,     0,     0,
       0,    57,    28,   179,   180,   164,     0,   167,     0,     0,
       0,    38,   101,     0,     0,     0,     0,     0,   191,     0,
     114,   201,   202,   203,   206,   204,   199,     0,     0,   228,
       0,   131,     0,     0,     0,   240,     0,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   196,
       0,     0,     0,   191,     0,     0,     0,   166,     0,   247,
       0,   113,    17,     0,    18,   191,    16,    15,     0,    12,
     147,     0,   132,     0,   230,     0,     0,   234,     0,     0,
     156,    59,   246,     0,    88,   226,   227,     0,     0,    91,
       0,   153,     0,   136,     0,     0,   138,     0,     0,     0,
     176,   247,   249,    96,     0,     0,     0,     0,   229,     0,
       0,     0,   242,     0,     0,     0,     0,   140,     0,   137,
       0,     0,     0,   172,     0,     0,   250,    19,     0,   141,
     148,   235,     0,   241,     0,   143,    89,    90,    92,   139,
       0,     0,     0,     0,   178,   142,   236,   243,   144,     0,
       0,     0,     0,     0,     0,     0,     0,   171,     0,   170,
       0,   169,   177
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    64,    65,   107,    67,   233,    68,   353,   234,   326,
     327,   219,    92,   108,   122,   123,   346,   224,   517,   461,
     110,   406,   407,   408,   470,   217,   147,   231
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -509
static const yytype_int16 yypact[] =
{
    8625,  -509,   198,   -14,  -509,   175,  -509,  -509,    78,  -509,
    8625,    63,  8625,  8625,  8625,  -509,  8758,  8625,  6231,    96,
    8625,  6364,   101,  8891,    69,   105,  9024,    86,  9157,  8625,
    8625,  -509,  -509,    57,   122,   260,   135,  1044,   161,   167,
    -509,    89,  -509,   177,     8,  8625,  8625,  8625,  8625,  8625,
    8625,  8625,  8625,  6497,    67,  8625,   177,   157,  8625,  1177,
      82,  8625,  8625,   180,   199,  -509,   623,   181,  -509,   -21,
    -509,   183,   201,    30,  8625,  6630,  6763,  8625,   329,  -509,
   10279,   329,   329,    31,  1709, 10339, 13409,  8625, 13603,  -509,
   13527, 10398,   168,  -509,  8625,  9984,  8625,  8625,  9290,  9942,
     164,    63,  6896,    15,  8625, 10457, 10516, 12819,  2507,  2640,
     141,  8625,  7029,   213,  8625,  1310, 12819,  8625,  8625,  8625,
    8625,  -509,   127,   128,  8625,  -509, 10575, 12878, 12819, 12819,
     214,  2773, 12819,   107, 10634,  2906,  2773,  -509,   219,   106,
     115,  8625, 10373,  7162, 13409,  8625,  8625,   151,  3039,   329,
    8625,  -509,  -509,  8625,  8625,  6497,  7029,  8625,  8625,  8625,
    8625,  8625,  8625,  -509,  8625,  8625,   778,  8625,  8625,  8625,
    8625,  8625,  8625,  8625,  9423,  7295,  8625,  8625,  -509,   277,
    8625,  8625,  8625,  8625,  -509,  8625,  7029,   215,  -509,  8625,
    -509,  -509,  -509,  -509,  8625,  -509, 12996,  -509, 10693,  -509,
   10752, 10811,   228,  -509,   911,  -509, 13291,    75,  -509, 10870,
    6497,  8625, 10929, 10988,     6,   245,  8625,   193, 11047,   208,
    8625,  8625,  8625,  8625,   132, 11106,  8625,  8625,  -509,  8625,
   12819,  -509,  8625,  7428,   178,  3172,   244, 11165,   250,  7029,
   11224, 11283, 11342, 11401, 11460,  -509,   177,  -509, 11519,  -509,
    8625,  7029,  -509,  7561,  -509,  8625,  8625,  7694,  7827,  -509,
    7029,  -509, 11578,  -509, 11637,  3305,  -509,  8625, 11696, 13291,
   12996, 13468,  -509,   251, 13146, 13146, 13323, 13626, 13656,    -2,
   13547,    25, 13527, 13603, 10025,   485, 13581, 13490,   106,  1849,
   13527,    84,  6364, 11755,  -509,  -509, 13409, 13055,  -509,  -509,
    -509,  -509,  -509,  -509,  -509,  8625,   111, 12937, 13114, 13350,
   10373, 13146,   252,  -509, 11814, 11874,  -509,  -509,  -509,  7029,
     164,   211,   216,    63,    75,  -509,     5,  -509,  1443,  1842,
     220, 12819,  -509,   196,  -509,   218,  3438,  -509,  -509,  6896,
   12819, 12819, 12819, 11933,  8625,  8625,     1,  1576,  3571,  3704,
   11992, 12051,    75,  -509,  3837,   195,  -509,  8625,  -509,   178,
     257,  -509,  -509,  -509,  -509,  -509,  -509,  -509, 13232,   258,
    -509,  2773,  2773,  2773,  -509,  7694,   261,  -509,  8625,  3970,
    -509,  -509,  8625,  8625, 10102,  -509, 10373,  7029,  9556,   -11,
     262,  -509,   264,  8625,  8625,  8625,  8625,   266,    75,  8625,
    7029, 12110,   -43,  8625,  -509,  1975,  -509,  -509,  8625,    57,
      92,  8625, 12819,   249,  8625, 12170, 12819,  8625,  8625,  8625,
   12229,  -509,  -509,  -509,  -509,  -509,    -5,  -509, 12288,  4103,
    2108,  -509,    -9,  -509,  -509,  -509,  2773,  -509,   259,  4236,
    8625, 13547, 13055,   248,   282,  6364, 12347,  7960,   178,   292,
    -509, 12819, 13173, 13173, 13173,  -509,  -509, 10161, 10279,   -43,
     253,  -509,  6497, 12406,  8625,  -509,  2773,  -509,   298,   263,
     230,  2241,  8093,  4369,    49, 12465,  4502, 12524,  -509,  -509,
      57,  8625,  4635,   178,  7428,  4768,  9689,  -509,  8226,    -6,
    4901,  -509,  -509, 10220,  -509,   221, 12996,  -509,  7428,  -509,
    -509,  8625,  -509, 12583,  -509,  8625, 12642,  -509,   265,    57,
    -509,   245,  -509,   291,  -509,  -509,  -509,  8625,  8625,  -509,
    8625,  -509,  5034,  -509,  7428,  5167,  -509,  8359,  2374,  9822,
   13527,    82,  -509,  -509,   270,  7428,  5300, 12701,  -509,  1842,
    8625,    57,  -509,  6497,  5433,  5566,  5699,  -509,  5832,  -509,
    8625,  5965,  8625,  -509,  8492,  2773,  -509,  -509,  6098,  -509,
    -509,  -509,  1842,    92, 12760,  -509,  -509,  -509,  -509,  -509,
     203,  8625,   204,  8625,  -509,  -509,  -509,  -509,  -509,  8625,
     205,  8625,   207,  2773,  8625,  2773,  8625,  -509,  2773,  -509,
    2773,  -509,  -509
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -509,  -509,   142,     0,   179,  -229,  -509,  -509,  -509,   -34,
    -317,  -338,   129,   194,  -121,   268,   -95,  -509,  -509,  -138,
      87,  -508,    81,  -391,  -241,  -146,  -462,  -509
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -249
static const yytype_int16 yytable[] =
{
      66,   413,   247,   187,   447,   355,   447,   397,   404,   398,
      78,   462,    80,    81,    82,   156,    85,    86,    88,   398,
      90,    91,   162,    95,   334,   124,    99,   532,   105,   106,
     220,   561,    73,   171,   191,    79,   174,   116,   531,   479,
     192,   145,   186,   193,   221,   126,   127,   128,   129,   146,
     132,   134,    73,   382,   576,   139,   194,   203,   142,   144,
     417,   418,   149,   448,   419,   448,   460,    79,   462,   556,
     100,     3,   399,   222,   196,   198,   200,   201,   320,   321,
     101,   456,   223,   178,   116,   322,    96,   206,   323,   100,
       3,   125,   324,   515,   209,    76,   212,   213,    80,   101,
      89,   186,   218,   102,   225,    93,   119,   188,   230,   516,
     486,   237,   132,    22,   240,   129,    77,   241,   242,   243,
     244,    22,    97,   156,   248,   366,   184,   120,   387,   145,
     429,   230,    22,   109,   513,   230,   230,   146,   121,   111,
     137,   262,   246,    80,   174,   264,   468,   469,   230,   388,
     268,   383,   114,   269,   270,   271,   132,   274,   275,   276,
     277,   278,   279,   195,   280,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   293,    66,   296,   297,   117,   133,
     307,   308,   309,   310,   118,   311,   132,   121,    55,   314,
      74,   344,    75,   345,   315,   141,    55,   150,   186,   151,
     189,   484,    69,    70,    85,   190,   103,    55,    71,   208,
      72,   331,   254,   236,   113,   245,   255,   259,   313,   498,
     340,   341,   342,   343,   100,     3,   393,   130,   266,   350,
     239,   251,   351,   138,   101,   230,   260,   261,   112,   132,
     394,   238,   272,   131,    72,   319,   135,   136,   335,   337,
     368,   132,   339,   129,   524,   148,   395,    73,   129,   232,
     132,   357,   396,   100,     3,   230,   535,    22,   359,   381,
     389,   409,   410,   101,   352,   430,   432,   112,   411,   438,
     100,     3,   450,   298,   455,   273,   449,   299,   488,   491,
     101,   300,   384,   472,   130,   499,   301,   330,   302,   303,
     492,   508,   232,   235,   465,   386,    22,   510,   509,   543,
     541,   557,   579,   581,   584,   312,   586,   295,   426,   132,
     474,   502,   577,    22,   140,   512,     0,     0,   401,   230,
       0,     0,     0,     0,     0,     0,   230,     0,   374,   412,
     265,     0,    55,   281,   415,   416,   156,   420,   230,   230,
       0,     0,   291,   162,   230,     0,   163,   428,   306,     0,
       0,     0,     0,     0,   171,   172,     0,   174,   360,     0,
       0,   230,   230,   230,     0,     0,     0,     0,     0,   230,
     369,    55,   441,   442,     0,     0,   325,   132,   446,   376,
       0,   304,     0,   451,   452,   453,   454,     0,    55,   457,
     458,     0,   305,   463,   329,   129,     0,     0,     0,     0,
     336,     0,     0,     0,   178,   402,     0,   475,     0,   477,
     348,   349,     0,     0,     0,     0,     0,   354,     0,     0,
       0,     0,   130,     0,   421,     0,   230,   130,     0,   230,
       0,     0,     0,     0,     0,   493,     0,   496,   392,   371,
     372,   373,   433,   434,   435,     0,   437,   184,     0,     0,
       0,   379,   503,     0,   506,     0,   230,     0,     0,     0,
       0,   230,   412,   230,     0,     0,   230,     0,     0,     0,
       0,     0,   230,     0,     0,   230,     0,     0,   530,     0,
     230,     0,     0,     0,     0,     0,   467,     0,     0,     0,
       0,   537,   156,   325,   157,   158,   159,   160,   161,   162,
       0,     0,   163,     0,     0,   166,   444,   487,     0,     0,
     171,   172,   230,   174,     0,   230,     0,   129,   230,   392,
       0,   325,     0,     0,   497,     0,   230,     0,     0,   230,
       0,     0,     0,   564,   230,   230,   230,   507,   230,   504,
     132,   129,   132,     0,   129,   230,     0,     0,   230,     0,
       0,     0,   230,     0,     0,     0,     0,   521,     0,   436,
     178,   132,   439,   132,     0,     0,     0,   325,     0,     0,
       0,     0,     0,   230,   130,   230,     0,     0,   230,     0,
     230,     0,     0,     0,     0,     0,   542,     0,     0,     0,
       0,     0,   466,     0,     0,   471,     0,     0,   473,   553,
     183,     0,   476,   184,     0,     0,   185,     0,     0,     0,
       0,     0,     0,   482,   485,     0,     0,     0,   563,     0,
     565,   152,     0,     0,   490,     0,   574,   153,   154,   155,
     156,     0,   157,   158,   159,   160,   161,   162,     0,     0,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,   587,     0,   589,   175,   176,   591,
       0,   592,     0,     0,   113,   522,     0,     0,   525,   570,
     528,   572,     0,     0,     0,     0,     0,     0,     0,     0,
     177,     0,   536,     0,     0,     0,     0,     0,     0,   539,
     580,     0,   582,     0,     0,     0,   130,     0,   178,     0,
       0,   544,   545,     0,   546,     0,     0,     0,   548,     0,
       0,     0,     0,   555,     0,     0,     0,     0,     0,   558,
     130,     0,     0,   130,   562,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,     0,
       0,   184,     0,     0,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   583,     0,   585,     0,     0,   588,     1,
     590,     2,     3,     4,     5,     6,   -49,     7,     8,     9,
      10,    11,   -49,   -49,   -49,    12,   -49,    13,    14,   -49,
     -49,   -49,   -49,    15,    16,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -49,   -49,    19,   -49,   -49,     0,    21,   -49,
       0,     0,   -49,   -49,    22,    23,     0,   -49,   -49,   -49,
      24,    25,    26,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
      28,    29,     0,    30,   -49,   -49,     0,    31,    32,    33,
       0,    34,    35,    36,     0,   -49,   -49,     0,    38,     0,
      39,    40,    41,   -49,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,   -49,    46,   -49,
       0,     0,     0,     0,     0,     0,    47,   -49,   -49,    49,
      50,    51,   -49,    52,    53,   -49,    54,     0,   -49,    55,
      56,    57,   -49,    58,     0,   -49,   -49,    60,    61,   -49,
      62,    63,     1,     0,     2,     3,     4,     5,     6,   -85,
       7,     8,     9,    10,    83,   -85,   -85,   -85,    12,   -85,
      13,    14,   -85,   -85,   -85,   -85,    15,    16,   -85,   -85,
      17,    18,   -85,   -85,   -85,   -85,   -85,    19,    20,   -85,
       0,    21,   -85,     0,     0,   -85,   -85,    22,    23,     0,
     -85,   -85,   -85,    24,    25,    26,   -85,   -85,    27,   -85,
     -85,   -85,   -85,    28,    29,     0,    30,   -85,   -85,     0,
      31,    32,    33,     0,    34,    35,    36,     0,   -85,    84,
       0,    38,     0,    39,    40,    41,   -85,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
     -85,    46,   -85,     0,     0,     0,     0,     0,     0,    47,
      48,   -85,    49,    50,    51,   -85,    52,    53,   -85,    54,
       0,   -85,    55,    56,    57,   -85,    58,     0,    59,   -85,
      60,    61,   -85,    62,    63,     1,     0,     2,     3,     4,
       5,     6,   -84,     7,     8,     9,    10,    11,   -84,   -84,
     -84,    12,   -84,    13,    14,   -84,   -84,   -84,   -84,    15,
      16,   -84,   -84,    17,    18,   -84,   -84,   -84,   -84,   -84,
      19,    20,   -84,     0,    21,   -84,     0,     0,   -84,   -84,
      22,    23,     0,   -84,   -84,   -84,    24,    25,    26,   -84,
     -84,    27,   -84,   -84,   -84,   -84,    28,    29,     0,    30,
     -84,   -84,     0,    31,    32,    33,     0,    34,    35,    36,
       0,   -84,     0,     0,    38,     0,    39,    40,    41,   -84,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,   -84,    46,   -84,     0,     0,     0,     0,
       0,     0,    47,   -84,   -84,    49,    50,    51,   -84,    52,
      53,   -84,    54,     0,   -84,    55,    56,    57,   -84,    58,
       0,    59,   -84,    60,    61,   -84,    62,    63,     1,     0,
       2,     3,     4,     5,     6,  -127,     7,     8,     9,    10,
      11,  -127,  -127,  -127,   143,  -127,    13,    14,  -127,  -127,
    -127,  -127,    15,    16,  -127,  -127,    17,    18,  -127,  -127,
    -127,  -127,  -127,    19,    20,  -127,     0,    21,  -127,     0,
       0,  -127,  -127,    22,    23,     0,  -127,  -127,  -127,    24,
      25,    26,  -127,  -127,  -127,  -127,  -127,  -127,  -127,    28,
      29,     0,    30,  -127,  -127,     0,    31,    32,    33,     0,
      34,    35,    36,     0,  -127,  -127,     0,    38,     0,    39,
      40,    41,  -127,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,  -127,    46,  -127,     0,
       0,     0,     0,     0,     0,    47,  -127,  -127,    49,    50,
      51,  -127,    52,    53,  -127,    54,     0,  -127,    55,    56,
      57,  -127,    58,     0,     0,  -127,    60,    61,  -127,    62,
      63,     1,     0,     2,     3,     4,     5,     6,  -161,     7,
       8,     9,    10,    11,  -161,  -161,  -161,    12,  -161,    13,
      14,  -161,  -161,  -161,  -161,    15,    16,  -161,  -161,    17,
      18,  -161,  -161,  -161,  -161,  -161,    19,    20,  -161,     0,
      21,  -161,     0,     0,  -161,  -161,    22,    23,     0,  -161,
    -161,  -161,    24,    25,    26,  -161,  -161,    27,  -161,  -161,
    -161,  -161,    28,    29,     0,    30,  -161,  -161,     0,    31,
      32,    33,     0,    34,    35,    36,     0,  -161,    37,     0,
      38,     0,    39,    40,    41,  -161,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,  -161,
      46,  -161,     0,     0,     0,     0,     0,     0,    47,     0,
    -161,    49,    50,    51,  -161,    52,    53,  -161,    54,     0,
    -161,    55,    56,    57,  -161,    58,     0,    59,  -161,    60,
      61,  -161,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,  -115,  -115,  -115,
     400,     0,    13,    14,  -115,  -115,  -115,  -115,    15,    16,
    -115,  -115,    17,    18,  -115,  -115,  -115,  -115,  -115,    19,
      20,  -115,     0,    21,     0,     0,     0,     0,  -115,    22,
      23,     0,     0,  -115,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
    -115,     0,    31,    32,    33,     0,    34,    35,    36,   109,
       0,    37,     0,    38,     0,    39,    40,    41,  -115,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,  -115,    52,    53,
    -115,    54,     0,  -115,    55,    56,    57,  -115,    58,     0,
      59,  -115,    60,    61,  -115,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
    -115,  -115,  -115,   400,     0,    13,    14,  -115,  -115,  -115,
    -115,    15,    16,  -115,  -115,    17,    18,  -115,  -115,  -115,
    -115,  -115,    19,    20,  -115,     0,    21,     0,     0,     0,
       0,  -115,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,  -115,     0,    28,    29,
       0,    30,     0,  -115,     0,    31,    32,    33,     0,    34,
      35,    36,   109,     0,    37,     0,    38,     0,    39,    40,
      41,  -115,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
    -115,    52,    53,  -115,    54,     0,  -115,    55,    56,    57,
    -115,    58,     0,    59,  -115,    60,    61,  -115,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,   -84,   -84,   -84,    12,     0,    13,    14,
     -84,   -84,   -84,   -84,    15,   204,   -84,   -84,    17,    18,
     -84,   -84,   -84,   -84,   -84,    19,    20,   -84,     0,    21,
       0,     0,     0,     0,   -84,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,   -84,     0,    31,    32,
      33,     0,    34,    35,    36,     0,     0,    37,     0,    38,
       0,    39,    40,    41,   -84,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,   115,     0,
      49,    50,    51,   -84,    52,    53,   -84,    54,     0,   -84,
      55,    56,    57,   -84,    58,     0,    59,   -84,    60,    61,
     -84,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,   156,    15,    16,     0,
       0,    17,    18,   162,     0,     0,   163,     0,    19,    20,
       0,     0,    21,     0,   171,  -249,   228,   174,    22,    23,
       0,   403,     0,   404,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,   252,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,   178,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,   405,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,   184,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,     0,
       0,    22,    23,     0,   464,     0,   465,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,   370,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,     0,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,     0,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,   483,     0,    37,  -191,    38,   232,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,   511,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,   228,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,   216,  -244,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,     0,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,     0,     0,     0,   228,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,   252,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,   551,   552,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,   228,     0,    22,    23,     0,     0,     0,     0,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,   229,     0,     0,    31,    32,    33,     0,
      34,    35,    36,     0,     0,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,    35,    36,     0,     0,    37,  -191,
      38,   232,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,    21,     0,     0,     0,   228,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,     0,
     252,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,   253,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,    21,     0,     0,     0,
     228,     0,    22,    23,     0,     0,     0,   257,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,     0,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,   258,     0,    49,    50,    51,
       0,    52,    53,     0,    54,     0,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,   228,     0,    22,    23,     0,     0,   267,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,     0,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,    48,     0,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,   228,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,   356,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,    48,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,     0,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,   228,
       0,    22,    23,     0,     0,     0,     0,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,  -248,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,     0,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,   228,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,  -245,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,     0,     0,    37,     0,    38,     0,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,   228,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,   422,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,     0,     0,     0,   228,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,   423,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,    48,     0,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,   228,     0,    22,    23,     0,     0,     0,     0,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,     0,     0,     0,    31,    32,    33,     0,
      34,    35,    36,     0,   427,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,   228,     0,    22,    23,     0,     0,
       0,   440,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,    35,    36,     0,     0,    37,     0,
      38,     0,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,    21,     0,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,   481,
       0,    37,   352,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,    21,     0,     0,     0,
     228,     0,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,   489,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
       0,    52,    53,     0,    54,     0,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,   228,     0,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,   514,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,    48,     0,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,   228,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,   519,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,    48,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,     0,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,   228,
       0,    22,    23,     0,     0,     0,     0,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,   523,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,     0,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,   228,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,     0,   526,    37,     0,    38,     0,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,   228,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,   533,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,     0,     0,     0,   228,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,   547,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,    48,     0,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,   228,     0,    22,    23,     0,     0,     0,     0,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,     0,     0,     0,    31,    32,    33,     0,
      34,    35,    36,     0,   549,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,   228,     0,    22,    23,     0,     0,
       0,     0,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,    35,    36,     0,   559,    37,     0,
      38,     0,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,    21,     0,     0,     0,   228,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,     0,
     566,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,    21,     0,     0,     0,
     228,     0,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,   567,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
       0,    52,    53,     0,    54,     0,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,   228,     0,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,   568,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,    48,     0,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,   228,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,   569,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,    48,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,     0,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,     0,
       0,    22,    23,     0,     0,     0,     0,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,   370,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,   571,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,   228,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,     0,   575,    37,     0,    38,     0,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,    11,    87,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,     0,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,     0,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,  -211,     0,     0,     0,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,     0,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,    48,     0,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,     0,     0,    22,    23,     0,     0,     0,     0,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,     0,     0,     0,    31,    32,    33,     0,
      34,    35,    36,   109,     0,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,   197,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,    35,    36,     0,     0,    37,     0,
      38,     0,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,   199,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,    21,     0,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,     0,
       0,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,    21,     0,     0,     0,
    -209,     0,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,     0,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
       0,    52,    53,     0,    54,     0,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,  -211,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,     0,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,    48,     0,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
     263,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,     0,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,     0,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,    48,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,     0,     2,     3,
       4,     5,     6,   294,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,     0,
       0,    22,    23,     0,     0,     0,     0,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,     0,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,     0,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    11,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,     0,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,     0,     0,    37,   352,    38,     0,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,    11,     0,     0,     0,    12,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,     0,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,   370,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    12,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,     0,     0,     0,     0,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,   252,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,   253,     0,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,    12,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,     0,     0,    22,    23,     0,     0,     0,   375,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,     0,     0,     0,    31,    32,    33,     0,
      34,    35,    36,     0,     0,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,     3,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,   495,    36,   109,     0,    37,     0,
      38,     0,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,  -209,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,    21,     0,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,     0,
       0,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,    21,     0,     0,     0,
       0,     0,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,     0,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
       0,    52,    53,     0,    54,   529,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,     0,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,    48,   550,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,     0,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,     0,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,    48,   573,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,     0,    62,    63,     1,     0,     2,     3,
       4,     5,     6,     0,     7,     8,     9,    10,    11,     0,
       0,     0,    12,     0,    13,    14,     0,     0,     0,     0,
      15,    16,     0,     0,    17,    18,     0,     0,     0,     0,
       0,    19,    20,     0,     0,    21,     0,     0,     0,     0,
       0,    22,    23,     0,     0,     0,     0,    24,    25,    26,
       0,     0,    27,     0,     0,     0,     0,    28,    29,     0,
      30,     0,     0,     0,    31,    32,    33,     0,    34,    35,
      36,     0,     0,    37,     0,    38,     0,    39,    40,    41,
       0,    42,    43,     0,    44,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    46,     0,     0,     0,     0,
       0,     0,     0,    47,    48,     0,    49,    50,    51,     0,
      52,    53,     0,    54,     0,     0,    55,    56,    57,     0,
      58,     0,    59,     0,    60,    61,     0,    62,    63,     1,
       0,     2,     3,     4,     5,     6,     0,     7,     8,     9,
      10,    83,     0,     0,     0,    12,     0,    13,    14,     0,
       0,     0,     0,    15,    16,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,    21,     0,
       0,     0,     0,     0,    22,    23,     0,     0,     0,     0,
      24,    25,    26,     0,     0,    27,     0,     0,     0,     0,
      28,    29,     0,    30,     0,     0,     0,    31,    32,    33,
       0,    34,    35,    36,     0,     0,    84,     0,    38,     0,
      39,    40,    41,     0,    42,    43,     0,    44,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    46,     0,
       0,     0,     0,     0,     0,     0,    47,    48,     0,    49,
      50,    51,     0,    52,    53,     0,    54,     0,     0,    55,
      56,    57,     0,    58,     0,    59,     0,    60,    61,     0,
      62,    63,     1,     0,     2,     3,     4,     5,     6,     0,
       7,     8,     9,    10,    11,     0,     0,     0,    94,     0,
      13,    14,     0,     0,     0,     0,    15,    16,     0,     0,
      17,    18,     0,     0,     0,     0,     0,    19,    20,     0,
       0,    21,     0,     0,     0,     0,     0,    22,    23,     0,
       0,     0,     0,    24,    25,    26,     0,     0,    27,     0,
       0,     0,     0,    28,    29,     0,    30,     0,     0,     0,
      31,    32,    33,     0,    34,    35,    36,     0,     0,    37,
       0,    38,     0,    39,    40,    41,     0,    42,    43,     0,
      44,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,    46,     0,     0,     0,     0,     0,     0,     0,    47,
      48,     0,    49,    50,    51,     0,    52,    53,     0,    54,
       0,     0,    55,    56,    57,     0,    58,     0,    59,     0,
      60,    61,     0,    62,    63,     1,     0,     2,     3,     4,
       5,     6,     0,     7,     8,     9,    10,    11,     0,     0,
       0,    98,     0,    13,    14,     0,     0,     0,     0,    15,
      16,     0,     0,    17,    18,     0,     0,     0,     0,     0,
      19,    20,     0,     0,    21,     0,     0,     0,     0,     0,
      22,    23,     0,     0,     0,     0,    24,    25,    26,     0,
       0,    27,     0,     0,     0,     0,    28,    29,     0,    30,
       0,     0,     0,    31,    32,    33,     0,    34,    35,    36,
       0,     0,    37,     0,    38,     0,    39,    40,    41,     0,
      42,    43,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,     0,    46,     0,     0,     0,     0,     0,
       0,     0,    47,    48,     0,    49,    50,    51,     0,    52,
      53,     0,    54,     0,     0,    55,    56,    57,     0,    58,
       0,    59,     0,    60,    61,     0,    62,    63,     1,     0,
       2,     3,     4,     5,     6,     0,     7,     8,     9,    10,
      11,     0,     0,     0,   104,     0,    13,    14,     0,     0,
       0,     0,    15,    16,     0,     0,    17,    18,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    21,     0,     0,
       0,     0,     0,    22,    23,     0,     0,     0,     0,    24,
      25,    26,     0,     0,    27,     0,     0,     0,     0,    28,
      29,     0,    30,     0,     0,     0,    31,    32,    33,     0,
      34,    35,    36,     0,     0,    37,     0,    38,     0,    39,
      40,    41,     0,    42,    43,     0,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    45,     0,    46,     0,     0,
       0,     0,     0,     0,     0,    47,    48,     0,    49,    50,
      51,     0,    52,    53,     0,    54,     0,     0,    55,    56,
      57,     0,    58,     0,    59,     0,    60,    61,     0,    62,
      63,     1,     0,     2,   214,     4,     5,     6,     0,     7,
       8,     9,    10,    11,     0,     0,     0,    12,     0,    13,
      14,     0,     0,     0,     0,    15,    16,     0,     0,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
      21,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,    24,    25,    26,     0,     0,    27,     0,     0,
       0,     0,    28,    29,     0,    30,     0,     0,     0,    31,
      32,    33,     0,    34,    35,    36,     0,     0,    37,     0,
      38,     0,    39,    40,    41,     0,    42,    43,     0,    44,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
      46,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    49,    50,    51,     0,    52,    53,     0,    54,     0,
       0,    55,    56,    57,     0,    58,     0,    59,     0,    60,
      61,     0,    62,    63,     1,     0,     2,     3,     4,     5,
       6,     0,     7,     8,     9,    10,    11,     0,     0,     0,
      12,     0,    13,    14,     0,     0,     0,     0,    15,    16,
       0,     0,    17,    18,     0,     0,     0,     0,     0,    19,
      20,     0,     0,   292,     0,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,    24,    25,    26,     0,     0,
      27,     0,     0,     0,     0,    28,    29,     0,    30,     0,
       0,     0,    31,    32,    33,     0,    34,    35,    36,     0,
       0,    37,     0,    38,     0,    39,    40,    41,     0,    42,
      43,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,    45,     0,    46,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,    49,    50,    51,     0,    52,    53,
       0,    54,     0,     0,    55,    56,    57,     0,    58,     0,
      59,     0,    60,    61,     0,    62,    63,     1,     0,     2,
       3,     4,     5,     6,     0,     7,     8,     9,    10,    11,
       0,     0,     0,    12,     0,    13,    14,     0,     0,     0,
       0,    15,    16,     0,     0,    17,    18,     0,     0,     0,
       0,     0,    19,    20,     0,     0,   445,     0,     0,     0,
       0,     0,    22,    23,     0,     0,     0,     0,    24,    25,
      26,     0,     0,    27,     0,     0,     0,     0,    28,    29,
       0,    30,     0,     0,     0,    31,    32,    33,     0,    34,
      35,    36,     0,     0,    37,     0,    38,     0,    39,    40,
      41,     0,    42,    43,     0,    44,     0,     0,     0,     0,
       0,     0,     0,     0,    45,     0,    46,     0,     0,     0,
       0,     0,     0,     0,    47,    48,     0,    49,    50,    51,
       0,    52,    53,     0,    54,     0,     0,    55,    56,    57,
       0,    58,     0,    59,     0,    60,    61,     0,    62,    63,
       1,     0,     2,     3,     4,     5,     6,     0,     7,     8,
       9,    10,    11,     0,     0,     0,    12,     0,    13,    14,
       0,     0,     0,     0,    15,    16,     0,     0,    17,    18,
       0,     0,     0,     0,     0,    19,    20,     0,     0,    21,
       0,     0,     0,     0,     0,    22,    23,     0,     0,     0,
       0,    24,    25,    26,     0,     0,    27,     0,     0,     0,
       0,    28,    29,     0,    30,     0,     0,     0,    31,    32,
      33,     0,    34,    35,    36,     0,     0,    37,     0,    38,
       0,    39,    40,    41,     0,    42,    43,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,    46,
       0,     0,     0,     0,     0,     0,     0,    47,   527,     0,
      49,    50,    51,     0,    52,    53,     0,    54,     0,     0,
      55,    56,    57,     0,    58,     0,    59,     0,    60,    61,
       0,    62,    63,     1,     0,     2,     3,     4,     5,     6,
       0,     7,     8,     9,    10,    11,     0,     0,     0,    12,
       0,    13,    14,     0,     0,     0,     0,    15,    16,     0,
       0,    17,    18,     0,     0,     0,     0,     0,    19,    20,
       0,     0,    21,     0,     0,     0,     0,     0,    22,    23,
       0,     0,     0,     0,    24,    25,    26,     0,     0,    27,
       0,     0,     0,     0,    28,    29,     0,    30,     0,     0,
       0,    31,    32,    33,     0,    34,    35,    36,     0,     0,
      37,     0,    38,     0,    39,    40,    41,     0,    42,    43,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,     0,    46,     0,     0,     0,     0,     0,     0,     0,
      47,   554,     0,    49,    50,    51,     0,    52,    53,     0,
      54,     0,     0,    55,    56,    57,     0,    58,     0,    59,
       0,    60,    61,   215,    62,    63,   153,   154,   155,   156,
       0,   157,   158,   159,   160,   161,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   216,   153,   154,
     155,   156,     0,   157,   158,   159,   160,   161,   162,   177,
       0,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,   178,     0,   176,
       0,     0,     0,     0,   210,     0,     0,     0,     0,     0,
       0,     0,   156,     0,   157,   158,   159,   160,   161,   162,
       0,   177,   163,     0,     0,   166,   179,   168,   169,   180,
     171,   172,   181,   174,     0,     0,   182,   183,     0,   178,
     184,     0,     0,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   211,     0,     0,     0,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,   182,   183,
     178,     0,   184,     0,     0,   185,   153,   154,   155,   156,
       0,   157,   158,   159,   160,   161,   162,     0,     0,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,   443,     0,     0,     0,   176,     0,     0,
     183,     0,     0,   184,     0,     0,   185,     0,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   177,
       0,     0,     0,     0,     0,   153,   154,   155,   156,     0,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,   500,     0,     0,     0,   176,     0,   501,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,   182,   183,   177,     0,
     184,     0,     0,   185,   153,   154,   155,   156,     0,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,   534,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,   207,   180,     0,
       0,   181,     0,     0,     0,   182,   183,   177,     0,   184,
       0,     0,   185,   153,   154,   155,   156,   202,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,   182,   183,   177,     0,   184,     0,
       0,   185,     0,   153,   154,   155,   156,     0,   157,   158,
     159,   160,   161,   162,   178,   205,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
     156,     0,     0,   179,     0,     0,   180,   162,     0,   181,
     163,     0,     0,   182,   183,     0,   177,   184,   171,   172,
     185,   174,   153,   154,   155,   156,     0,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,   207,   180,     0,   178,   181,
       0,     0,     0,   182,   183,   177,     0,   184,     0,     0,
     185,   153,   154,   155,   156,     0,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,  -249,     0,
       0,   184,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,   180,     0,   226,   181,     0,
       0,     0,   182,   183,   177,     0,   184,     0,     0,   185,
     153,   154,   155,   156,     0,   157,   158,   159,   160,   161,
     162,     0,   178,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,   180,     0,   227,   181,     0,     0,
       0,   182,   183,   177,     0,   184,     0,     0,   185,   153,
     154,   155,   156,     0,   157,   158,   159,   160,   161,   162,
       0,   178,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
     182,   183,   177,     0,   184,     0,     0,   185,   153,   154,
     155,   156,     0,   157,   158,   159,   160,   161,   162,     0,
     178,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,   249,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,   182,
     183,   177,     0,   184,     0,     0,   185,   153,   154,   155,
     156,   316,   157,   158,   159,   160,   161,   162,     0,   178,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,   256,     0,     0,     0,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,   182,   183,
     177,     0,   184,     0,     0,   185,   153,   154,   155,   156,
     317,   157,   158,   159,   160,   161,   162,     0,   178,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,   177,
       0,   184,     0,     0,   185,   153,   154,   155,   156,     0,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,   318,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,   182,   183,   177,     0,
     184,     0,     0,   185,   153,   154,   155,   156,   328,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,   182,   183,   177,     0,   184,
       0,     0,   185,   153,   154,   155,   156,   332,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,   182,   183,   177,     0,   184,     0,
       0,   185,   153,   154,   155,   156,   333,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,   182,   183,   177,     0,   184,     0,     0,
     185,   153,   154,   155,   156,   338,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,   182,   183,   177,     0,   184,     0,     0,   185,
     153,   154,   155,   156,   347,   157,   158,   159,   160,   161,
     162,     0,   178,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,   182,   183,   177,     0,   184,     0,     0,   185,   153,
     154,   155,   156,   358,   157,   158,   159,   160,   161,   162,
       0,   178,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
     182,   183,   177,     0,   184,     0,     0,   185,   153,   154,
     155,   156,   361,   157,   158,   159,   160,   161,   162,     0,
     178,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,   182,
     183,   177,     0,   184,     0,     0,   185,   153,   154,   155,
     156,   362,   157,   158,   159,   160,   161,   162,     0,   178,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,   182,   183,
     177,     0,   184,     0,     0,   185,   153,   154,   155,   156,
     363,   157,   158,   159,   160,   161,   162,     0,   178,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,   177,
       0,   184,     0,     0,   185,   153,   154,   155,   156,   364,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,     0,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,   182,   183,   177,     0,
     184,     0,     0,   185,   153,   154,   155,   156,     0,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,   365,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,   182,   183,   177,     0,   184,
       0,     0,   185,   153,   154,   155,   156,   367,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,   182,   183,   177,     0,   184,     0,
       0,   185,   153,   154,   155,   156,     0,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,   377,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,   182,   183,   177,     0,   184,     0,     0,
     185,   153,   154,   155,   156,     0,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,   378,     0,     0,
       0,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,   182,   183,   177,     0,   184,     0,     0,   185,
     153,   154,   155,   156,   380,   157,   158,   159,   160,   161,
     162,     0,   178,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,   182,   183,   177,     0,   184,     0,     0,   185,   153,
     154,   155,   156,     0,   157,   158,   159,   160,   161,   162,
       0,   178,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,   385,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,   180,     0,     0,   181,     0,     0,     0,
     182,   183,   177,     0,   184,     0,     0,   185,   153,   154,
     155,   156,   390,   157,   158,   159,   160,   161,   162,     0,
     178,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,   180,     0,     0,   181,     0,     0,     0,   182,
     183,   177,     0,   184,     0,     0,   185,     0,   153,   154,
     155,   156,     0,   157,   158,   159,   160,   161,   162,   178,
     391,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,   182,   183,
       0,   177,   184,     0,     0,   185,     0,   153,   154,   155,
     156,     0,   157,   158,   159,   160,   161,   162,     0,   178,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,   180,     0,   414,   181,     0,     0,     0,   182,   183,
     177,     0,   184,     0,     0,   185,   153,   154,   155,   156,
       0,   157,   158,   159,   160,   161,   162,     0,   178,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,   177,
       0,   184,     0,     0,   185,   153,   154,   155,   156,   424,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,     0,     0,     0,   425,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,   182,   183,   177,     0,
     184,     0,     0,   185,   153,   154,   155,   156,     0,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   459,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,   182,   183,   177,     0,   184,
       0,     0,   185,     0,   153,   154,   155,   156,     0,   157,
     158,   159,   160,   161,   162,   178,     0,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,   345,     0,     0,   182,   183,     0,   177,   184,     0,
       0,   185,     0,   153,   154,   155,   156,     0,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,   478,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,   182,   183,   177,     0,   184,     0,
       0,   185,   153,   154,   155,   156,   480,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,   182,   183,   177,     0,   184,     0,     0,
     185,   153,   154,   155,   156,     0,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,   494,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,   182,   183,   177,     0,   184,     0,     0,   185,
     153,   154,   155,   156,     0,   157,   158,   159,   160,   161,
     162,     0,   178,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,   505,     0,     0,     0,
       0,   179,     0,     0,   180,     0,     0,   181,     0,     0,
       0,   182,   183,   177,     0,   184,     0,     0,   185,   153,
     154,   155,   156,     0,   157,   158,   159,   160,   161,   162,
       0,   178,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     179,     0,     0,   180,     0,   518,   181,     0,     0,     0,
     182,   183,   177,     0,   184,     0,     0,   185,   153,   154,
     155,   156,     0,   157,   158,   159,   160,   161,   162,     0,
     178,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   179,
       0,     0,   180,     0,   520,   181,     0,     0,     0,   182,
     183,   177,     0,   184,     0,     0,   185,   153,   154,   155,
     156,     0,   157,   158,   159,   160,   161,   162,     0,   178,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,     0,     0,   538,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   179,     0,
       0,   180,     0,     0,   181,     0,     0,     0,   182,   183,
     177,     0,   184,     0,     0,   185,   153,   154,   155,   156,
       0,   157,   158,   159,   160,   161,   162,     0,   178,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,   540,     0,     0,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,   177,
       0,   184,     0,     0,   185,   153,   154,   155,   156,     0,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,   560,     0,     0,     0,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   179,     0,     0,   180,
       0,     0,   181,     0,     0,     0,   182,   183,   177,     0,
     184,     0,     0,   185,   153,   154,   155,   156,     0,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   578,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   179,     0,     0,   180,     0,
       0,   181,     0,     0,     0,   182,   183,   177,     0,   184,
       0,     0,   185,   153,   154,   155,   156,     0,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,     0,     0,
       0,     0,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,     0,     0,   180,     0,     0,
     181,     0,     0,     0,   182,   183,   177,     0,   184,     0,
       0,   185,   250,   154,   155,   156,     0,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,     0,     0,     0,
       0,     0,     0,   176,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,     0,     0,   180,     0,     0,   181,
       0,     0,     0,   182,   183,   177,     0,   184,     0,     0,
     185,   153,   154,   155,   156,     0,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,     0,     0,     0,     0,
       0,     0,   176,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,   180,     0,     0,   181,     0,
       0,     0,   182,   183,   177,     0,   184,     0,     0,   185,
     153,  -249,   155,   156,     0,   157,   158,   159,   160,   161,
     162,     0,   178,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,     0,     0,     0,     0,     0,
       0,   176,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -249,     0,     0,   181,     0,     0,
       0,   182,   183,   177,     0,   184,     0,     0,   185,   153,
       0,   155,   156,     0,   157,   158,   159,   160,   161,   162,
       0,   178,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   181,     0,     0,     0,
     182,   183,  -249,     0,   184,     0,     0,   185,   153,     0,
     155,   156,     0,   157,   158,   159,   160,   161,   162,     0,
     178,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,     0,     0,     0,     0,     0,     0,   176,
       0,     0,     0,   156,     0,     0,     0,   159,   160,   161,
     162,     0,     0,   163,     0,   181,     0,     0,     0,   182,
     183,   171,   172,   184,   174,     0,   185,     0,   154,   155,
     156,     0,   157,   158,   159,   160,   161,   162,     0,   178,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,     0,     0,     0,     0,     0,     0,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,     0,     0,     0,     0,     0,     0,   182,   183,
       0,     0,   184,     0,     0,   185,     0,     0,   155,   156,
       0,   157,   158,   159,   160,   161,   162,     0,   178,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   183,     0,     0,   184,     0,     0,   176,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   179,     0,     0,
     180,     0,     0,   181,     0,     0,     0,   182,   183,     0,
       0,   184,     0,     0,   185,     0,     0,   155,   156,     0,
     157,   158,   159,   160,   161,   162,     0,   178,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
       0,     0,     0,   431,     0,     0,   176,     0,     0,     0,
     156,     0,     0,     0,     0,   160,   161,   162,     0,     0,
     163,     0,     0,     0,     0,     0,   182,   183,   171,   172,
     184,   174,     0,   185,     0,     0,   155,   156,     0,   157,
     158,   159,   160,   161,   162,     0,   178,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   178,     0,
       0,     0,     0,     0,     0,   182,   183,     0,     0,   184,
       0,     0,   185,     0,     0,   155,   156,     0,   157,   158,
     159,   160,   161,   162,     0,   178,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   183,     0,
       0,   184,     0,     0,   176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -249,   183,     0,     0,   184,     0,
       0,   185,     0,     0,  -249,   156,     0,   157,   158,   159,
     160,   161,   162,     0,   178,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   156,     0,   157,
     158,   159,   160,   161,   162,     0,     0,   163,   164,   165,
     166,   167,   168,   169,     0,   171,   172,   173,   174,     0,
       0,     0,     0,     0,   183,     0,     0,   184,     0,     0,
     185,     0,     0,     0,   156,     0,   157,   158,   159,   160,
     161,   162,     0,   178,   163,   164,   165,   166,   167,   168,
     169,     0,   171,   172,   156,   174,   157,   158,   159,   160,
     161,   162,     0,     0,   163,   178,     0,   166,   167,   168,
     169,     0,   171,   172,     0,   174,     0,     0,     0,     0,
       0,     0,     0,   183,     0,     0,   184,     0,   156,   185,
     157,   158,   159,   160,   161,   162,     0,     0,   163,     0,
       0,   166,   178,   168,  -249,   183,   171,   172,   184,   174,
     156,   185,   157,   158,   159,   160,   161,   162,     0,     0,
     163,     0,   178,     0,     0,     0,     0,     0,   171,   172,
       0,   174,     0,   156,     0,     0,     0,     0,     0,   161,
     162,     0,   183,   163,     0,   184,     0,     0,   185,     0,
       0,   171,   172,     0,   174,     0,   178,     0,     0,     0,
       0,     0,   183,   156,     0,   184,     0,     0,   185,  -249,
     162,     0,     0,   163,     0,     0,     0,     0,   178,     0,
       0,   171,   172,     0,   174,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,     0,     0,   184,
       0,   178,   185,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   183,     0,
       0,   184,     0,     0,   185,     0,     0,     0,     0,     0,
       0,   178,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,   184,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,   184
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-509))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-249))

static const yytype_int16 yycheck[] =
{
       0,   339,   123,    24,    15,   234,    15,   324,    51,    14,
      10,   402,    12,    13,    14,    17,    16,    17,    18,    14,
      20,    21,    24,    23,    18,    17,    26,   489,    28,    29,
      15,   539,    46,    35,     4,     4,    38,    37,    44,    44,
      10,    47,    17,    13,    29,    45,    46,    47,    48,    55,
      50,    51,    46,    28,   562,    55,    26,    26,    58,    59,
      59,    60,    62,    74,    63,    74,   109,     4,   459,   531,
       3,     4,    67,    58,    74,    75,    76,    77,     3,     4,
      13,   398,    67,    85,    84,    10,    17,    87,    13,     3,
       4,    83,    17,    44,    94,    17,    96,    97,    98,    13,
       4,    17,   102,    17,   104,     4,    17,   128,   108,    60,
     119,   111,   112,    46,   114,   115,    38,   117,   118,   119,
     120,    46,    17,    17,   124,   246,   128,    38,    17,    47,
     359,   131,    46,    76,   472,   135,   136,    55,    10,    17,
      53,   141,    14,   143,    38,   145,    54,    55,   148,    38,
     150,    67,    17,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   133,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,    17,    50,
     180,   181,   182,   183,    17,   185,   186,    10,   121,   189,
      15,    59,    17,    61,   194,    38,   121,    17,    17,     0,
      17,   430,     4,     5,   204,     4,    27,   121,    10,    41,
      46,   211,   131,    72,    35,    88,   109,   136,     3,   448,
     220,   221,   222,   223,     3,     4,    15,    48,    77,   229,
      17,    17,   232,    54,    13,   235,    17,   122,    17,   239,
      29,   112,   155,    49,    46,    17,    52,    53,     3,    56,
     250,   251,    44,   253,   483,    61,    45,    46,   258,    81,
     260,    17,    46,     3,     4,   265,   495,    46,    18,    18,
      18,    51,    76,    13,    79,    18,    18,    17,    60,    18,
       3,     4,    18,     6,    18,   156,    24,    10,    29,    41,
      13,    14,   292,    44,   115,     3,    19,   210,    21,    22,
      18,     3,    81,   109,    51,   305,    46,    77,    45,    18,
      45,    41,   109,   109,   109,   186,   109,   175,   352,   319,
     415,   459,   563,    46,    56,   471,    -1,    -1,   328,   329,
      -1,    -1,    -1,    -1,    -1,    -1,   336,    -1,   257,   339,
     146,    -1,   121,   164,   344,   345,    17,   347,   348,   349,
      -1,    -1,   173,    24,   354,    -1,    27,   357,   179,    -1,
      -1,    -1,    -1,    -1,    35,    36,    -1,    38,   239,    -1,
      -1,   371,   372,   373,    -1,    -1,    -1,    -1,    -1,   379,
     251,   121,   382,   383,    -1,    -1,   207,   387,   388,   260,
      -1,   114,    -1,   393,   394,   395,   396,    -1,   121,   399,
     400,    -1,   125,   403,   210,   405,    -1,    -1,    -1,    -1,
     216,    -1,    -1,    -1,    85,   328,    -1,   417,    -1,   419,
     226,   227,    -1,    -1,    -1,    -1,    -1,   233,    -1,    -1,
      -1,    -1,   253,    -1,   347,    -1,   436,   258,    -1,   439,
      -1,    -1,    -1,    -1,    -1,   445,    -1,   447,   319,   255,
     256,   257,   371,   372,   373,    -1,   375,   128,    -1,    -1,
      -1,   267,   462,    -1,   464,    -1,   466,    -1,    -1,    -1,
      -1,   471,   472,   473,    -1,    -1,   476,    -1,    -1,    -1,
      -1,    -1,   482,    -1,    -1,   485,    -1,    -1,   488,    -1,
     490,    -1,    -1,    -1,    -1,    -1,   409,    -1,    -1,    -1,
      -1,   501,    17,   324,    19,    20,    21,    22,    23,    24,
      -1,    -1,    27,    -1,    -1,    30,   387,   436,    -1,    -1,
      35,    36,   522,    38,    -1,   525,    -1,   527,   528,   400,
      -1,   352,    -1,    -1,   447,    -1,   536,    -1,    -1,   539,
      -1,    -1,    -1,   543,   544,   545,   546,   466,   548,   462,
     550,   551,   552,    -1,   554,   555,    -1,    -1,   558,    -1,
      -1,    -1,   562,    -1,    -1,    -1,    -1,   480,    -1,   375,
      85,   571,   378,   573,    -1,    -1,    -1,   398,    -1,    -1,
      -1,    -1,    -1,   583,   405,   585,    -1,    -1,   588,    -1,
     590,    -1,    -1,    -1,    -1,    -1,   509,    -1,    -1,    -1,
      -1,    -1,   408,    -1,    -1,   411,    -1,    -1,   414,   528,
     125,    -1,   418,   128,    -1,    -1,   131,    -1,    -1,    -1,
      -1,    -1,    -1,   429,   430,    -1,    -1,    -1,   541,    -1,
     543,     8,    -1,    -1,   440,    -1,   555,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,   583,    -1,   585,    44,    45,   588,
      -1,   590,    -1,    -1,   495,   481,    -1,    -1,   484,   550,
     486,   552,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    -1,   498,    -1,    -1,    -1,    -1,    -1,    -1,   505,
     571,    -1,   573,    -1,    -1,    -1,   527,    -1,    85,    -1,
      -1,   517,   518,    -1,   520,    -1,    -1,    -1,   524,    -1,
      -1,    -1,    -1,   529,    -1,    -1,    -1,    -1,    -1,   535,
     551,    -1,    -1,   554,   540,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    -1,
      -1,   128,    -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   579,    -1,   581,    -1,    -1,   584,     1,
     586,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    40,    41,
      -1,    -1,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    -1,    65,    66,    67,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      82,    83,    84,    85,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,    -1,   120,   121,
     122,   123,   124,   125,    -1,   127,   128,   129,   130,   131,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    40,    41,    -1,    -1,    44,    45,    46,    47,    -1,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    -1,    65,    66,    67,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    77,    78,
      -1,    80,    -1,    82,    83,    84,    85,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      99,   100,   101,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
      -1,   120,   121,   122,   123,   124,   125,    -1,   127,   128,
     129,   130,   131,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    40,    41,    -1,    -1,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    -1,    65,
      66,    67,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    -1,    -1,    80,    -1,    82,    83,    84,    85,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    99,   100,   101,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,    -1,   120,   121,   122,   123,   124,   125,
      -1,   127,   128,   129,   130,   131,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    41,    -1,
      -1,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    -1,    65,    66,    67,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    77,    78,    -1,    80,    -1,    82,
      83,    84,    85,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    99,   100,   101,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,    -1,   120,   121,   122,
     123,   124,   125,    -1,    -1,   128,   129,   130,   131,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      40,    41,    -1,    -1,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    77,    78,    -1,
      80,    -1,    82,    83,    84,    85,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    99,
     100,   101,    -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,
     110,   111,   112,   113,   114,   115,   116,   117,   118,    -1,
     120,   121,   122,   123,   124,   125,    -1,   127,   128,   129,
     130,   131,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    40,    -1,    -1,    -1,    -1,    45,    46,
      47,    -1,    -1,    50,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      67,    -1,    69,    70,    71,    -1,    73,    74,    75,    76,
      -1,    78,    -1,    80,    -1,    82,    83,    84,    85,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,   114,   115,   116,
     117,   118,    -1,   120,   121,   122,   123,   124,   125,    -1,
     127,   128,   129,   130,   131,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    40,    -1,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    60,    -1,    62,    63,
      -1,    65,    -1,    67,    -1,    69,    70,    71,    -1,    73,
      74,    75,    76,    -1,    78,    -1,    80,    -1,    82,    83,
      84,    85,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
     114,   115,   116,   117,   118,    -1,   120,   121,   122,   123,
     124,   125,    -1,   127,   128,   129,   130,   131,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    40,
      -1,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    67,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      -1,    82,    83,    84,    85,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,   114,   115,   116,   117,   118,    -1,   120,
     121,   122,   123,   124,   125,    -1,   127,   128,   129,   130,
     131,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    17,    25,    26,    -1,
      -1,    29,    30,    24,    -1,    -1,    27,    -1,    36,    37,
      -1,    -1,    40,    -1,    35,    36,    44,    38,    46,    47,
      -1,    49,    -1,    51,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,   128,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    -1,    49,    -1,    51,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    77,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    -1,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,   110,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    66,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    78,    79,
      80,    81,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    -1,
      77,    78,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    51,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,    50,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    44,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    77,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    77,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    77,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    51,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    76,
      -1,    78,    79,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    77,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    77,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    44,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    77,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    77,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    77,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    77,    78,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    -1,
      77,    78,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    77,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    77,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    77,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    77,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,   110,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    77,    78,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    14,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    -1,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    41,    -1,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    -1,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    76,    -1,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    -1,
      -1,    78,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      44,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      18,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    -1,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    -1,    78,    79,    80,    -1,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    77,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    77,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    51,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    76,    -1,    78,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    -1,
      -1,    78,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,   119,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,   110,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    -1,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,   110,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    -1,   132,   133,     1,    -1,     3,     4,
       5,     6,     7,    -1,     9,    10,    11,    12,    13,    -1,
      -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,
      25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,
      -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,
      65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,
      75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,    84,
      -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,
     115,   116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,
     125,    -1,   127,    -1,   129,   130,    -1,   132,   133,     1,
      -1,     3,     4,     5,     6,     7,    -1,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,
      -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,
      -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,
      -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,    -1,
      82,    83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,
     112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,
     122,   123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,
     132,   133,     1,    -1,     3,     4,     5,     6,     7,    -1,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,
      29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,
      69,    70,    71,    -1,    73,    74,    75,    -1,    -1,    78,
      -1,    80,    -1,    82,    83,    84,    -1,    86,    87,    -1,
      89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,
      -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,
     109,    -1,   111,   112,   113,    -1,   115,   116,    -1,   118,
      -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,
     129,   130,    -1,   132,   133,     1,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,
      -1,    -1,    -1,    69,    70,    71,    -1,    73,    74,    75,
      -1,    -1,    78,    -1,    80,    -1,    82,    83,    84,    -1,
      86,    87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,   111,   112,   113,    -1,   115,
     116,    -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,
      -1,   127,    -1,   129,   130,    -1,   132,   133,     1,    -1,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,
      -1,    -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,
      63,    -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,
      73,    74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,
      83,    84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,
     113,    -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,
     123,    -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,
     133,     1,    -1,     3,     4,     5,     6,     7,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,
      70,    71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,
      80,    -1,    82,    83,    84,    -1,    86,    87,    -1,    89,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
      -1,   111,   112,   113,    -1,   115,   116,    -1,   118,    -1,
      -1,   121,   122,   123,    -1,   125,    -1,   127,    -1,   129,
     130,    -1,   132,   133,     1,    -1,     3,     4,     5,     6,
       7,    -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,
      -1,    -1,    69,    70,    71,    -1,    73,    74,    75,    -1,
      -1,    78,    -1,    80,    -1,    82,    83,    84,    -1,    86,
      87,    -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   108,   109,    -1,   111,   112,   113,    -1,   115,   116,
      -1,   118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,
     127,    -1,   129,   130,    -1,   132,   133,     1,    -1,     3,
       4,     5,     6,     7,    -1,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    25,    26,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    37,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    -1,    57,    -1,    -1,    -1,    -1,    62,    63,
      -1,    65,    -1,    -1,    -1,    69,    70,    71,    -1,    73,
      74,    75,    -1,    -1,    78,    -1,    80,    -1,    82,    83,
      84,    -1,    86,    87,    -1,    89,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    98,    -1,   100,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,   111,   112,   113,
      -1,   115,   116,    -1,   118,    -1,    -1,   121,   122,   123,
      -1,   125,    -1,   127,    -1,   129,   130,    -1,   132,   133,
       1,    -1,     3,     4,     5,     6,     7,    -1,     9,    10,
      11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    62,    63,    -1,    65,    -1,    -1,    -1,    69,    70,
      71,    -1,    73,    74,    75,    -1,    -1,    78,    -1,    80,
      -1,    82,    83,    84,    -1,    86,    87,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    98,    -1,   100,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,    -1,
     111,   112,   113,    -1,   115,   116,    -1,   118,    -1,    -1,
     121,   122,   123,    -1,   125,    -1,   127,    -1,   129,   130,
      -1,   132,   133,     1,    -1,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      -1,    19,    20,    -1,    -1,    -1,    -1,    25,    26,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    62,    63,    -1,    65,    -1,    -1,
      -1,    69,    70,    71,    -1,    73,    74,    75,    -1,    -1,
      78,    -1,    80,    -1,    82,    83,    84,    -1,    86,    87,
      -1,    89,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      98,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,   111,   112,   113,    -1,   115,   116,    -1,
     118,    -1,    -1,   121,   122,   123,    -1,   125,    -1,   127,
      -1,   129,   130,    11,   132,   133,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    67,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    85,    -1,    45,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    -1,    19,    20,    21,    22,    23,    24,
      -1,    67,    27,    -1,    -1,    30,   114,    32,    33,   117,
      35,    36,   120,    38,    -1,    -1,   124,   125,    -1,    85,
     128,    -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,
      85,    -1,   128,    -1,    -1,   131,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
     125,    -1,    -1,   128,    -1,    -1,   131,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      -1,    -1,    -1,    -1,    -1,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,
     128,    -1,    -1,   131,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    57,   117,    -1,
      -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,
      -1,    -1,   131,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,
      -1,   131,    -1,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    85,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    -1,   114,    -1,    -1,   117,    24,    -1,   120,
      27,    -1,    -1,   124,   125,    -1,    67,   128,    35,    36,
     131,    38,    14,    15,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    57,   117,    -1,    85,   120,
      -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,
     131,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,   125,    -1,
      -1,   128,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,    -1,    60,   120,    -1,
      -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,
      14,    15,    16,    17,    -1,    19,    20,    21,    22,    23,
      24,    -1,    85,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    -1,   117,    -1,    60,   120,    -1,    -1,
      -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      -1,    85,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,
     124,   125,    67,    -1,   128,    -1,    -1,   131,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    -1,
      85,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    99,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,
     125,    67,    -1,   128,    -1,    -1,   131,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    85,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,   109,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,
      67,    -1,   128,    -1,    -1,   131,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    85,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,
      -1,   128,    -1,    -1,   131,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,
     128,    -1,    -1,   131,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,
      -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,
      -1,    -1,   131,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,
      -1,   131,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,
      -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,
     131,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,
      -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    85,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,
      -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      -1,    85,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,
     124,   125,    67,    -1,   128,    -1,    -1,   131,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      85,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,
     125,    67,    -1,   128,    -1,    -1,   131,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    -1,    85,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,
      67,    -1,   128,    -1,    -1,   131,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    -1,    85,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,
      -1,   128,    -1,    -1,   131,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,
     128,    -1,    -1,   131,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,
      -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,
      -1,    -1,   131,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,
      -1,   131,    14,    15,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,
      -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,
     131,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,
      -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    -1,    85,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,
      -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      -1,    85,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    41,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,
     124,   125,    67,    -1,   128,    -1,    -1,   131,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    -1,
      85,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,
     125,    67,    -1,   128,    -1,    -1,   131,    -1,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    85,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,
      -1,    67,   128,    -1,    -1,   131,    -1,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    -1,    85,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    60,   120,    -1,    -1,    -1,   124,   125,
      67,    -1,   128,    -1,    -1,   131,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    -1,    85,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,
      -1,   128,    -1,    -1,   131,    14,    15,    16,    17,    77,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,
     128,    -1,    -1,   131,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,
      -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,
      -1,    -1,   131,    -1,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    85,    -1,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    61,    -1,    -1,   124,   125,    -1,    67,   128,    -1,
      -1,   131,    -1,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,
      -1,   131,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,
      -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,
     131,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    41,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,
      -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,
      14,    15,    16,    17,    -1,    19,    20,    21,    22,    23,
      24,    -1,    85,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,
      -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,    14,
      15,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      -1,    85,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     114,    -1,    -1,   117,    -1,    60,   120,    -1,    -1,    -1,
     124,   125,    67,    -1,   128,    -1,    -1,   131,    14,    15,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    -1,
      85,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,
      -1,    -1,   117,    -1,    60,   120,    -1,    -1,    -1,   124,
     125,    67,    -1,   128,    -1,    -1,   131,    14,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    -1,    85,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,
      -1,   117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,
      67,    -1,   128,    -1,    -1,   131,    14,    15,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    -1,    85,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,
      -1,   128,    -1,    -1,   131,    14,    15,    16,    17,    -1,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,
      -1,    -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,
     128,    -1,    -1,   131,    14,    15,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,
      -1,   120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,
      -1,    -1,   131,    14,    15,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,
     120,    -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,
      -1,   131,    14,    15,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,
      -1,    -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,
     131,    14,    15,    16,    17,    -1,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   114,    -1,    -1,   117,    -1,    -1,   120,    -1,
      -1,    -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,
      14,    15,    16,    17,    -1,    19,    20,    21,    22,    23,
      24,    -1,    85,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,
      -1,   124,   125,    67,    -1,   128,    -1,    -1,   131,    14,
      -1,    16,    17,    -1,    19,    20,    21,    22,    23,    24,
      -1,    85,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   120,    -1,    -1,    -1,
     124,   125,    67,    -1,   128,    -1,    -1,   131,    14,    -1,
      16,    17,    -1,    19,    20,    21,    22,    23,    24,    -1,
      85,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    -1,    27,    -1,   120,    -1,    -1,    -1,   124,
     125,    35,    36,   128,    38,    -1,   131,    -1,    15,    16,
      17,    -1,    19,    20,    21,    22,    23,    24,    -1,    85,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,
      -1,    -1,   128,    -1,    -1,   131,    -1,    -1,    16,    17,
      -1,    19,    20,    21,    22,    23,    24,    -1,    85,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   125,    -1,    -1,   128,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,    -1,    -1,
     117,    -1,    -1,   120,    -1,    -1,    -1,   124,   125,    -1,
      -1,   128,    -1,    -1,   131,    -1,    -1,    16,    17,    -1,
      19,    20,    21,    22,    23,    24,    -1,    85,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,   101,    -1,    -1,    45,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    22,    23,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,   124,   125,    35,    36,
     128,    38,    -1,   131,    -1,    -1,    16,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    85,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    -1,    -1,    -1,    -1,   124,   125,    -1,    -1,   128,
      -1,    -1,   131,    -1,    -1,    16,    17,    -1,    19,    20,
      21,    22,    23,    24,    -1,    85,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   125,    -1,
      -1,   128,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   124,   125,    -1,    -1,   128,    -1,
      -1,   131,    -1,    -1,    16,    17,    -1,    19,    20,    21,
      22,    23,    24,    -1,    85,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    17,    -1,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    29,
      30,    31,    32,    33,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,   125,    -1,    -1,   128,    -1,    -1,
     131,    -1,    -1,    -1,    17,    -1,    19,    20,    21,    22,
      23,    24,    -1,    85,    27,    28,    29,    30,    31,    32,
      33,    -1,    35,    36,    17,    38,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    85,    -1,    30,    31,    32,
      33,    -1,    35,    36,    -1,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   125,    -1,    -1,   128,    -1,    17,   131,
      19,    20,    21,    22,    23,    24,    -1,    -1,    27,    -1,
      -1,    30,    85,    32,    33,   125,    35,    36,   128,    38,
      17,   131,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    -1,    85,    -1,    -1,    -1,    -1,    -1,    35,    36,
      -1,    38,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,
      24,    -1,   125,    27,    -1,   128,    -1,    -1,   131,    -1,
      -1,    35,    36,    -1,    38,    -1,    85,    -1,    -1,    -1,
      -1,    -1,   125,    17,    -1,   128,    -1,    -1,   131,    23,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    85,    -1,
      -1,    35,    36,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,   128,
      -1,    85,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,
      -1,   128,    -1,    -1,   131,    -1,    -1,    -1,    -1,    -1,
      -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   125,    -1,    -1,   128
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,     5,     6,     7,     9,    10,    11,
      12,    13,    17,    19,    20,    25,    26,    29,    30,    36,
      37,    40,    46,    47,    52,    53,    54,    57,    62,    63,
      65,    69,    70,    71,    73,    74,    75,    78,    80,    82,
      83,    84,    86,    87,    89,    98,   100,   108,   109,   111,
     112,   113,   115,   116,   118,   121,   122,   123,   125,   127,
     129,   130,   132,   133,   137,   138,   139,   140,   142,     4,
       5,    10,    46,    46,    15,    17,    17,    38,   139,     4,
     139,   139,   139,    13,    78,   139,   139,    14,   139,     4,
     139,   139,   148,     4,    17,   139,    17,    17,    17,   139,
       3,    13,    17,   140,    17,   139,   139,   139,   149,    76,
     156,    17,    17,   140,    17,   109,   139,    17,    17,    17,
      38,    10,   150,   151,    17,    83,   139,   139,   139,   139,
     140,   149,   139,   148,   139,   149,   149,   156,   140,   139,
     151,    38,   139,    17,   139,    47,    55,   162,   149,   139,
      17,     0,     8,    14,    15,    16,    17,    19,    20,    21,
      22,    23,    24,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    44,    45,    67,    85,   114,
     117,   120,   124,   125,   128,   131,    17,    24,   128,    17,
       4,     4,    10,    13,    26,   133,   139,    18,   139,    18,
     139,   139,    18,    26,    26,    26,   139,    57,    41,   139,
      50,   109,   139,   139,     4,    11,    55,   161,   139,   147,
      15,    29,    58,    67,   153,   139,    60,    60,    44,    66,
     139,   163,    81,   141,   144,   149,    72,   139,   148,    17,
     139,   139,   139,   139,   139,    88,    14,   150,   139,    99,
      14,    17,    77,   109,   158,   109,   109,    51,   109,   158,
      17,   122,   139,    18,   139,   149,    77,    50,   139,   139,
     139,   139,   156,   148,   139,   139,   139,   139,   139,   139,
     139,   140,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,    40,   139,     8,   138,   139,   139,     6,    10,
      14,    19,    21,    22,   114,   125,   140,   139,   139,   139,
     139,   139,   148,     3,   139,   139,    18,    18,    41,    17,
       3,     4,    10,    13,    17,   140,   145,   146,    18,   149,
     156,   139,    18,    18,    18,     3,   149,    56,    18,    44,
     139,   139,   139,   139,    59,    61,   152,    18,   149,   149,
     139,   139,    79,   143,   149,   141,    77,    17,    18,    18,
     148,    18,    18,    18,    18,    41,   150,    18,   139,   148,
      77,   149,   149,   149,   158,    51,   148,    41,    50,   149,
      18,    18,    28,    67,   139,    41,   139,    17,    38,    18,
      18,    26,   148,    15,    29,    45,    46,   146,    14,    67,
      17,   139,   156,    49,    51,   109,   157,   158,   159,    51,
      76,    60,   139,   147,    60,   139,   139,    59,    60,    63,
     139,   156,    77,    77,    77,    44,   145,    77,   139,   141,
      18,   101,    18,   158,   158,   158,   149,   158,    18,   149,
      51,   139,   139,    41,   148,    40,   139,    15,    74,    24,
      18,   139,   139,   139,   139,    18,   146,   139,   139,    44,
     109,   155,   159,   139,    49,    51,   149,   156,    54,    55,
     160,   149,    44,   149,   152,   139,   149,   139,    44,    44,
      18,    76,   149,    76,   141,   149,   119,   158,    29,    77,
     149,    41,    18,   139,    41,    74,   139,   156,   141,     3,
      41,    47,   155,   139,   156,    50,   139,   158,     3,    45,
      77,    11,   161,   147,    77,    44,    60,   154,    60,    77,
      60,   156,   149,    77,   141,   149,    77,   109,   149,   119,
     139,    44,   162,    77,    41,   141,   149,   139,    44,   149,
      50,    45,   156,    18,   149,   149,   149,    77,   149,    77,
     110,   109,   110,   158,   109,   149,   162,    41,   149,    77,
      41,   157,   149,   156,   139,   156,    77,    77,    77,    77,
     148,   110,   148,   110,   158,    77,   157,   160,    44,   109,
     148,   109,   148,   149,   109,   149,   109,   158,   149,   158,
     149,   158,   158
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (scanner, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void * scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void * scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (scanner);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void * scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void * scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void * scanner)
#else
static void
yy_reduce_print (yyvsp, yyrule, scanner)
    YYSTYPE *yyvsp;
    int yyrule;
    void * scanner;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, scanner); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void * scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void * scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (scanner);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void * scanner);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void * scanner)
#else
int
yyparse (scanner)
    void * scanner;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 190 "input_parser.yy"
    {   const giac::context * contextptr = giac_yyget_extra(scanner);
			    if ((yyvsp[(1) - (1)])._VECTptr->size()==1)
			     parsed_gen((yyvsp[(1) - (1)])._VECTptr->front(),contextptr);
                          else
			     parsed_gen(gen(*(yyvsp[(1) - (1)])._VECTptr,_SEQ__VECT),contextptr);
			 }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 198 "input_parser.yy"
    { (yyval)=vecteur(1,(yyvsp[(1) - (2)])); }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 199 "input_parser.yy"
    { if ((yyvsp[(2) - (3)]).val==1) (yyval)=vecteur(1,symbolic(at_nodisp,(yyvsp[(1) - (3)]))); else (yyval)=vecteur(1,(yyvsp[(1) - (3)])); }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 200 "input_parser.yy"
    { if ((yyvsp[(2) - (3)]).val==1) (yyval)=mergevecteur(makevecteur(symbolic(at_nodisp,(yyvsp[(1) - (3)]))),*(yyvsp[(3) - (3)])._VECTptr); else (yyval)=mergevecteur(makevecteur((yyvsp[(1) - (3)])),*(yyvsp[(3) - (3)])._VECTptr); }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 203 "input_parser.yy"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 204 "input_parser.yy"
    {if (is_one((yyvsp[(1) - (2)]))) (yyval)=(yyvsp[(2) - (2)]); else (yyval)=symbolic(at_prod,gen(makevecteur((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])),_SEQ__VECT));}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 205 "input_parser.yy"
    {if (is_one((yyvsp[(1) - (4)]))) (yyval)=symb_pow((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)])); else (yyval)=symbolic(at_prod,gen(makevecteur((yyvsp[(1) - (4)]),symb_pow((yyvsp[(2) - (4)]),(yyvsp[(4) - (4)]))),_SEQ__VECT));}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 206 "input_parser.yy"
    {(yyval)=symbolic(at_prod,gen(makevecteur((yyvsp[(1) - (3)]),symb_pow((yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]))) ,_SEQ__VECT));}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 207 "input_parser.yy"
    {if (is_one((yyvsp[(1) - (2)]))) (yyval)=(yyvsp[(2) - (2)]); else	(yyval)=symbolic(at_prod,gen(makevecteur((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])) ,_SEQ__VECT));}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 208 "input_parser.yy"
    { (yyval) =(yyvsp[(1) - (5)])*symbolic(*(yyvsp[(2) - (5)])._FUNCptr,(yyvsp[(4) - (5)])); }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 209 "input_parser.yy"
    { (yyval) =(yyvsp[(1) - (7)])*symb_pow(symbolic(*(yyvsp[(2) - (7)])._FUNCptr,(yyvsp[(4) - (7)])),(yyvsp[(7) - (7)])); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 211 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 212 "input_parser.yy"
    { if ((yyvsp[(1) - (1)]).type==_FUNC) (yyval)=symbolic(*(yyvsp[(1) - (1)])._FUNCptr,gen(vecteur(0),_SEQ__VECT)); else (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 215 "input_parser.yy"
    {(yyval) = symb_program_sto((yyvsp[(3) - (6)]),(yyvsp[(3) - (6)])*zero,(yyvsp[(6) - (6)]),(yyvsp[(1) - (6)]),false,giac_yyget_extra(scanner));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 216 "input_parser.yy"
    {if (is_array_index((yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),giac_yyget_extra(scanner)) || (abs_calc_mode(giac_yyget_extra(scanner))==38 && (yyvsp[(1) - (6)]).type==_IDNT && strlen((yyvsp[(1) - (6)])._IDNTptr->id_name)==2 && check_vect_38((yyvsp[(1) - (6)])._IDNTptr->id_name))) (yyval)=symbolic(at_sto,gen(makevecteur((yyvsp[(6) - (6)]),symbolic(at_of,gen(makevecteur((yyvsp[(1) - (6)]),(yyvsp[(3) - (6)])) ,_SEQ__VECT))) ,_SEQ__VECT)); else { (yyval) = symb_program_sto((yyvsp[(3) - (6)]),(yyvsp[(3) - (6)])*zero,(yyvsp[(6) - (6)]),(yyvsp[(1) - (6)]),true,giac_yyget_extra(scanner)); (yyval)._SYMBptr->feuille.subtype=_SORTED__VECT;  } }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 217 "input_parser.yy"
    {if (is_array_index((yyvsp[(3) - (6)]),(yyvsp[(5) - (6)]),giac_yyget_extra(scanner)) || (abs_calc_mode(giac_yyget_extra(scanner))==38 && (yyvsp[(3) - (6)]).type==_IDNT && check_vect_38((yyvsp[(3) - (6)])._IDNTptr->id_name))) (yyval)=symbolic(at_sto,gen(makevecteur((yyvsp[(1) - (6)]),symbolic(at_of,gen(makevecteur((yyvsp[(3) - (6)]),(yyvsp[(5) - (6)])) ,_SEQ__VECT))) ,_SEQ__VECT)); else (yyval) = symb_program_sto((yyvsp[(5) - (6)]),(yyvsp[(5) - (6)])*zero,(yyvsp[(1) - (6)]),(yyvsp[(3) - (6)]),false,giac_yyget_extra(scanner));}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 218 "input_parser.yy"
    { 
         const giac::context * contextptr = giac_yyget_extra(scanner);
         gen g=symb_at((yyvsp[(3) - (6)]),(yyvsp[(5) - (6)]),contextptr); (yyval)=symb_sto((yyvsp[(1) - (6)]),g); 
        }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 222 "input_parser.yy"
    { 
         const giac::context * contextptr = giac_yyget_extra(scanner);
         gen g=symbolic(at_of,gen(makevecteur((yyvsp[(3) - (8)]),(yyvsp[(6) - (8)])) ,_SEQ__VECT)); (yyval)=symb_sto((yyvsp[(1) - (8)]),g); 
        }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 226 "input_parser.yy"
    { if ((yyvsp[(3) - (3)]).type==_IDNT) { const char * ch=(yyvsp[(3) - (3)]).print(context0).c_str(); if (ch[0]=='_' && unit_conversion_map().find(ch+1) != unit_conversion_map().end()) (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (3)]),symbolic(at_unit,makevecteur(1,(yyvsp[(3) - (3)])))) ,_SEQ__VECT)); else (yyval)=symb_sto((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); } else (yyval)=symb_sto((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 227 "input_parser.yy"
    { (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 228 "input_parser.yy"
    { (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 229 "input_parser.yy"
    { (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 230 "input_parser.yy"
    { (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 231 "input_parser.yy"
    { (yyval)=symbolic(at_time,(yyvsp[(1) - (3)]));}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 232 "input_parser.yy"
    { (yyval)=symbolic(at_POLYFORM,gen(makevecteur((yyvsp[(1) - (3)]),at_eval),_SEQ__VECT));}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 233 "input_parser.yy"
    { (yyval)=symbolic(at_convert,gen(makevecteur((yyvsp[(1) - (4)]),symb_unit(plus_one,(yyvsp[(4) - (4)]),giac_yyget_extra(scanner))),_SEQ__VECT)); opened_quote(giac_yyget_extra(scanner)) &= 0x7ffffffd;}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 234 "input_parser.yy"
    {(yyval) = check_symb_of((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),giac_yyget_extra(scanner));}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 235 "input_parser.yy"
    {(yyval) = check_symb_of((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),giac_yyget_extra(scanner));}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 236 "input_parser.yy"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 237 "input_parser.yy"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 238 "input_parser.yy"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 239 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (3)])._FUNCptr,(yyvsp[(3) - (3)]));}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 240 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,(yyvsp[(3) - (4)]));}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 241 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (3)])._FUNCptr,gen(vecteur(0),_SEQ__VECT));}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 242 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(3) - (3)])._FUNCptr,(yyvsp[(1) - (3)]));}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 243 "input_parser.yy"
    {if (is_inequation((yyvsp[(1) - (3)]))){ (yyval) = symb_and((yyvsp[(1) - (3)]),symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)])._SYMBptr->feuille[1],(yyvsp[(3) - (3)])),_SEQ__VECT)));} else (yyval) = symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 244 "input_parser.yy"
    {(yyval) = symb_and(symbolic(*(yyvsp[(2) - (5)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (5)]),(yyvsp[(3) - (5)])),_SEQ__VECT)),symbolic(*(yyvsp[(4) - (5)])._FUNCptr,gen(makevecteur((yyvsp[(3) - (5)]),(yyvsp[(5) - (5)])),_SEQ__VECT)));}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 245 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(2) - (3)])._FUNCptr,makesequence((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 246 "input_parser.yy"
    { 
	if ((yyvsp[(2) - (2)]).type==_SYMB) (yyval)=(yyvsp[(2) - (2)]); else (yyval)=symbolic(at_nop,(yyvsp[(2) - (2)])); 
	(yyval).change_subtype(_SPREAD__SYMB); 
        const giac::context * contextptr = giac_yyget_extra(scanner);
       spread_formula(false,contextptr); 
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 252 "input_parser.yy"
    { if ((yyvsp[(1) - (3)]).is_symb_of_sommet(at_plus) && (yyvsp[(1) - (3)])._SYMBptr->feuille.type==_VECT){ (yyvsp[(1) - (3)])._SYMBptr->feuille._VECTptr->push_back((yyvsp[(3) - (3)])); (yyval)=(yyvsp[(1) - (3)]); } else
  (yyval) =symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 254 "input_parser.yy"
    {(yyval) = symb_plus((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]).type<_IDNT?-(yyvsp[(3) - (3)]):symbolic(at_neg,(yyvsp[(3) - (3)])));}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 255 "input_parser.yy"
    {(yyval) = symb_plus((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]).type<_IDNT?-(yyvsp[(3) - (3)]):symbolic(at_neg,(yyvsp[(3) - (3)])));}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 256 "input_parser.yy"
    {(yyval) =symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 257 "input_parser.yy"
    {(yyval) =symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 258 "input_parser.yy"
    {if ((yyvsp[(1) - (3)])==symbolic(at_exp,1) && (yyvsp[(2) - (3)])==at_pow) (yyval)=symbolic(at_exp,(yyvsp[(3) - (3)])); else (yyval) =symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 259 "input_parser.yy"
    {if ((yyvsp[(2) - (3)]).type==_FUNC) (yyval)=symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT)); else (yyval) = symbolic(at_normalmod,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 260 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 261 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(2) - (2)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (2)]),RAND_MAX) ,_SEQ__VECT)); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 262 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (2)])._FUNCptr,gen(makevecteur(0,(yyvsp[(2) - (2)])) ,_SEQ__VECT)); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 263 "input_parser.yy"
    {(yyval) = makesequence(symbolic(*(yyvsp[(1) - (3)])._FUNCptr,gen(makevecteur(0,RAND_MAX) ,_SEQ__VECT)),(yyvsp[(3) - (3)])); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 266 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])),_SEQ__VECT));}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 267 "input_parser.yy"
    {(yyval)= symbolic(at_deuxpoints,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT));}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 268 "input_parser.yy"
    { 
					if ((yyvsp[(2) - (2)])==unsigned_inf)
						(yyval) = minus_inf;
					else { if ((yyvsp[(2) - (2)]).type==_INT_) (yyval)=(-(yyvsp[(2) - (2)]).val); else { if ((yyvsp[(2) - (2)]).type==_DOUBLE_) (yyval)=(-(yyvsp[(2) - (2)])._DOUBLE_val); else (yyval)=symbolic(at_neg,(yyvsp[(2) - (2)])); } }
				}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 273 "input_parser.yy"
    { 
					if ((yyvsp[(2) - (2)])==unsigned_inf)
						(yyval) = minus_inf;
					else { if ((yyvsp[(2) - (2)]).type==_INT_ || (yyvsp[(2) - (2)]).type==_DOUBLE_ || (yyvsp[(2) - (2)]).type==_FLOAT_) (yyval)=-(yyvsp[(2) - (2)]); else (yyval)=symbolic(at_neg,(yyvsp[(2) - (2)])); }
				}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 278 "input_parser.yy"
    {
					if ((yyvsp[(2) - (2)])==unsigned_inf)
						(yyval) = plus_inf;
					else
						(yyval) = (yyvsp[(2) - (2)]);
				}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 284 "input_parser.yy"
    {(yyval) = polynome_or_sparse_poly1(eval((yyvsp[(2) - (5)]),1, giac_yyget_extra(scanner)),(yyvsp[(4) - (5)]));}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 285 "input_parser.yy"
    { 
           if ( ((yyvsp[(2) - (3)]).type==_SYMB) && ((yyvsp[(2) - (3)])._SYMBptr->sommet==at_deuxpoints) )
             (yyval) = algebraic_EXTension((yyvsp[(2) - (3)])._SYMBptr->feuille._VECTptr->front(),(yyvsp[(2) - (3)])._SYMBptr->feuille._VECTptr->back());
           else (yyval)=(yyvsp[(2) - (3)]);
        }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 291 "input_parser.yy"
    { (yyval)=gen(at_of,2); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 292 "input_parser.yy"
    {(yyval) = symb_sto((yyvsp[(3) - (3)]),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)])==at_array_sto); if ((yyvsp[(3) - (3)]).is_symb_of_sommet(at_program)) *logptr(giac_yyget_extra(scanner))<<"// End defining "<<(yyvsp[(1) - (3)])<<endl;}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 293 "input_parser.yy"
    { (yyval) = symbolic(*(yyvsp[(1) - (2)])._FUNCptr,(yyvsp[(2) - (2)]));}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 294 "input_parser.yy"
    {(yyval) = symb_args((yyvsp[(3) - (4)]));}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 295 "input_parser.yy"
    {(yyval) = symb_args((yyvsp[(3) - (4)]));}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 296 "input_parser.yy"
    { (yyval)=symb_args(vecteur(0)); }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 297 "input_parser.yy"
    {
	(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,(yyvsp[(3) - (4)]));
        const giac::context * contextptr = giac_yyget_extra(scanner);
	if (*(yyvsp[(1) - (4)])._FUNCptr==at_maple_mode ||*(yyvsp[(1) - (4)])._FUNCptr==at_xcas_mode ){
          xcas_mode(contextptr)=(yyvsp[(3) - (4)]).val;
        }
	if (*(yyvsp[(1) - (4)])._FUNCptr==at_user_operator){
          user_operator((yyvsp[(3) - (4)]),contextptr);
        }
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 307 "input_parser.yy"
    {
	if ((yyvsp[(3) - (4)]).type==_VECT && (yyvsp[(3) - (4)])._VECTptr->empty())
          giac_yyerror(scanner,"void argument");
	(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,(yyvsp[(3) - (4)]));	
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 312 "input_parser.yy"
    { 
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_at((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),contextptr);
        }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 316 "input_parser.yy"
    {
	(yyval) = symbolic(*(yyvsp[(1) - (3)])._FUNCptr,gen(vecteur(0),_SEQ__VECT));
	if (*(yyvsp[(1) - (3)])._FUNCptr==at_rpn)
          rpn_mode(giac_yyget_extra(scanner))=1;
	if (*(yyvsp[(1) - (3)])._FUNCptr==at_alg)
          rpn_mode(giac_yyget_extra(scanner))=0;
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 323 "input_parser.yy"
    {
	(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 326 "input_parser.yy"
    {(yyval) = symbolic(at_derive,(yyvsp[(1) - (2)]));}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 327 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(2) - (2)])._FUNCptr,(yyvsp[(1) - (2)])); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 328 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (6)])._FUNCptr,makevecteur(equaltosame((yyvsp[(2) - (6)])),symb_bloc((yyvsp[(4) - (6)])),symb_bloc((yyvsp[(6) - (6)]))));}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 329 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,makevecteur(equaltosame((yyvsp[(2) - (4)])),(yyvsp[(4) - (4)]),0));}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 330 "input_parser.yy"
    {
	(yyval) = symbolic(*(yyvsp[(1) - (5)])._FUNCptr,makevecteur(equaltosame((yyvsp[(2) - (5)])),symb_bloc((yyvsp[(4) - (5)])),(yyvsp[(5) - (5)])));
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 333 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,(yyvsp[(3) - (4)]));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 334 "input_parser.yy"
    {(yyval) = (yyvsp[(1) - (1)]);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 335 "input_parser.yy"
    {(yyval) = symb_program((yyvsp[(3) - (4)]));}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 336 "input_parser.yy"
    {(yyval) = gen(at_program,3);}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 337 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
         (yyval) = symb_program((yyvsp[(1) - (3)]),zero*(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),contextptr);
        }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 341 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
             if ((yyvsp[(3) - (3)]).type==_VECT) 
                (yyval) = symb_program((yyvsp[(1) - (3)]),zero*(yyvsp[(1) - (3)]),symb_bloc(makevecteur(at_nop,(yyvsp[(3) - (3)]))),contextptr); 
             else 
                (yyval) = symb_program((yyvsp[(1) - (3)]),zero*(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),contextptr);
		}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 348 "input_parser.yy"
    {(yyval) = symb_bloc((yyvsp[(3) - (4)]));}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 349 "input_parser.yy"
    {(yyval) = at_bloc;}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 351 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(1) - (2)])._FUNCptr,(yyvsp[(2) - (2)])); }
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 352 "input_parser.yy"
    {(yyval) = gen(*(yyvsp[(1) - (1)])._FUNCptr,0);}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 353 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]);}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 355 "input_parser.yy"
    {(yyval) = symbolic(at_break,zero);}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 356 "input_parser.yy"
    {(yyval) = symbolic(at_continue,zero);}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 357 "input_parser.yy"
    { 
	/*
	  gen kk(identificateur("index"));
	  vecteur v(*$6._VECTptr);
          const giac::context * contextptr = giac_yyget_extra(scanner);
	  v.insert(v.begin(),symb_sto(symb_at($4,kk,contextptr),$2));
	  $$=symbolic(*$1._FUNCptr,makevecteur(symb_sto(xcas_mode(contextptr)!=0,kk),symb_inferieur_strict(kk,symb_size($4)+(xcas_mode(contextptr)!=0)),symb_sto(symb_plus(kk,plus_one),kk),symb_bloc(v))); 
          */
          if ((yyvsp[(7) - (7)]).type==_INT_ && (yyvsp[(7) - (7)]).val && (yyvsp[(7) - (7)]).val!=2 && (yyvsp[(7) - (7)]).val!=9)
	    giac_yyerror(scanner,"missing loop end delimiter");
 	  bool rg=(yyvsp[(4) - (7)]).is_symb_of_sommet(at_range);
          gen f=(yyvsp[(4) - (7)]).type==_SYMB?(yyvsp[(4) - (7)])._SYMBptr->feuille:0,inc=1;
          if (rg){
            if (f.type!=_VECT) f=makesequence(0,f);
            vecteur v=*f._VECTptr;
            if (v.size()>=2) f=makesequence(v.front(),v[1]-1);
            if (v.size()==3) inc=v[2];
          }
          if (inc.type==_INT_  && f.type==_VECT && f._VECTptr->size()==2 && (rg || ((yyvsp[(4) - (7)]).is_symb_of_sommet(at_interval) 
	  // && f._VECTptr->front().type==_INT_ && f._VECTptr->back().type==_INT_ 
	  )))
            (yyval)=symbolic(*(yyvsp[(1) - (7)])._FUNCptr,makevecteur(symb_sto(f._VECTptr->front(),(yyvsp[(2) - (7)])),inc.val>0?symb_inferieur_egal((yyvsp[(2) - (7)]),f._VECTptr->back()):symb_superieur_egal((yyvsp[(2) - (7)]),f._VECTptr->back()),symb_sto(symb_plus((yyvsp[(2) - (7)]),inc),(yyvsp[(2) - (7)])),symb_bloc((yyvsp[(6) - (7)]))));
          else 
            (yyval)=symbolic(*(yyvsp[(1) - (7)])._FUNCptr,makevecteur(1,symbolic(*(yyvsp[(1) - (7)])._FUNCptr,makevecteur((yyvsp[(2) - (7)]),(yyvsp[(4) - (7)]))),1,symb_bloc((yyvsp[(6) - (7)]))));
	  }
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 382 "input_parser.yy"
    { 
          if ((yyvsp[(9) - (9)]).type==_INT_ && (yyvsp[(9) - (9)]).val && (yyvsp[(9) - (9)]).val!=2 && (yyvsp[(9) - (9)]).val!=9) giac_yyerror(scanner,"missing loop end delimiter");
          gen tmp,st=(yyvsp[(6) - (9)]);  
       if (st==1 && (yyvsp[(4) - (9)])!=1) st=(yyvsp[(4) - (9)]);
          const giac::context * contextptr = giac_yyget_extra(scanner);
	  if (!lidnt(st).empty())
            *logptr(contextptr) << "Warning, step is not numeric " << st << std::endl;
          bool b=has_evalf(st,tmp,1,context0);
          if (!b || is_positive(tmp,context0)) 
             (yyval)=symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (9)]),(yyvsp[(2) - (9)])),symb_inferieur_egal((yyvsp[(2) - (9)]),(yyvsp[(5) - (9)])),symb_sto(symb_plus((yyvsp[(2) - (9)]),b?abs(st,context0):symb_abs(st)),(yyvsp[(2) - (9)])),symb_bloc((yyvsp[(8) - (9)])))); 
          else 
            (yyval)=symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (9)]),(yyvsp[(2) - (9)])),symb_superieur_egal((yyvsp[(2) - (9)]),(yyvsp[(5) - (9)])),symb_sto(symb_plus((yyvsp[(2) - (9)]),st),(yyvsp[(2) - (9)])),symb_bloc((yyvsp[(8) - (9)])))); 
        }
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 395 "input_parser.yy"
    { 
          if ((yyvsp[(9) - (9)]).type==_INT_ && (yyvsp[(9) - (9)]).val && (yyvsp[(9) - (9)]).val!=2 && (yyvsp[(9) - (9)]).val!=9) giac_yyerror(scanner,"missing loop end delimiter");
         gen tmp,st=(yyvsp[(4) - (9)]); 
        if (st==1 && (yyvsp[(5) - (9)])!=1) st=(yyvsp[(5) - (9)]);
         const giac::context * contextptr = giac_yyget_extra(scanner);
	 if (!lidnt(st).empty())
            *logptr(contextptr) << "Warning, step is not numeric " << st << std::endl;
         bool b=has_evalf(st,tmp,1,context0);
         if (!b || is_positive(tmp,context0)) 
           (yyval)=symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (9)]),(yyvsp[(2) - (9)])),symb_inferieur_egal((yyvsp[(2) - (9)]),(yyvsp[(6) - (9)])),symb_sto(symb_plus((yyvsp[(2) - (9)]),b?abs(st,context0):symb_abs(st)),(yyvsp[(2) - (9)])),symb_bloc((yyvsp[(8) - (9)])))); 
         else 
           (yyval)=symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (9)]),(yyvsp[(2) - (9)])),symb_superieur_egal((yyvsp[(2) - (9)]),(yyvsp[(6) - (9)])),symb_sto(symb_plus((yyvsp[(2) - (9)]),st),(yyvsp[(2) - (9)])),symb_bloc((yyvsp[(8) - (9)])))); 
        }
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 408 "input_parser.yy"
    { 
          if ((yyvsp[(7) - (7)]).type==_INT_ && (yyvsp[(7) - (7)]).val && (yyvsp[(7) - (7)]).val!=2 && (yyvsp[(7) - (7)]).val!=9) giac_yyerror(scanner,"missing loop end delimiter");
          (yyval)=symbolic(*(yyvsp[(1) - (7)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (7)]),(yyvsp[(2) - (7)])),plus_one,symb_sto(symb_plus((yyvsp[(2) - (7)]),(yyvsp[(4) - (7)])),(yyvsp[(2) - (7)])),symb_bloc((yyvsp[(6) - (7)])))); 
        }
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 412 "input_parser.yy"
    { 
          if ((yyvsp[(9) - (9)]).type==_INT_ && (yyvsp[(9) - (9)]).val && (yyvsp[(9) - (9)]).val!=2 && (yyvsp[(9) - (9)]).val!=9 && (yyvsp[(9) - (9)]).val!=8) giac_yyerror(scanner,"missing loop end delimiter");
          (yyval)=symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur(symb_sto((yyvsp[(3) - (9)]),(yyvsp[(2) - (9)])),(yyvsp[(6) - (9)]),symb_sto(symb_plus((yyvsp[(2) - (9)]),(yyvsp[(4) - (9)])),(yyvsp[(2) - (9)])),symb_bloc((yyvsp[(8) - (9)])))); 
        }
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 416 "input_parser.yy"
    {(yyval) = gen(*(yyvsp[(1) - (1)])._FUNCptr,4);}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 421 "input_parser.yy"
    { 
        vecteur v=gen2vecteur((yyvsp[(2) - (4)]));
        v.push_back(symb_ifte(equaltosame((yyvsp[(4) - (4)])),symbolic(at_break,zero),0));
	(yyval)=symbolic(*(yyvsp[(1) - (4)])._FUNCptr,makevecteur(zero,1,zero,symb_bloc(v))); 
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 426 "input_parser.yy"
    { 
        if ((yyvsp[(5) - (5)]).type==_INT_ && (yyvsp[(5) - (5)]).val && (yyvsp[(5) - (5)]).val!=2 && (yyvsp[(5) - (5)]).val!=9) giac_yyerror(scanner,"missing loop end delimiter");
        vecteur v=gen2vecteur((yyvsp[(2) - (5)]));
        v.push_back(symb_ifte(equaltosame((yyvsp[(4) - (5)])),symbolic(at_break,zero),0));
	(yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,makevecteur(zero,1,zero,symb_bloc(v))); 
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 432 "input_parser.yy"
    {
          if ((yyvsp[(7) - (7)]).type==_INT_ && (yyvsp[(7) - (7)]).val && (yyvsp[(7) - (7)]).val!=4) giac_yyerror(scanner,"missing iferr end delimiter");
           (yyval)=symbolic(at_try_catch,makevecteur(symb_bloc((yyvsp[(2) - (7)])),0,symb_bloc((yyvsp[(4) - (7)])),symb_bloc((yyvsp[(6) - (7)]))));
        }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 436 "input_parser.yy"
    {(yyval)=symbolic(at_piecewise,(yyvsp[(2) - (3)])); }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 437 "input_parser.yy"
    { 
	(yyval)=(yyvsp[(1) - (1)]); 
	// $$.subtype=1; 
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 441 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]); /* $$.subtype=1; */ }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 442 "input_parser.yy"
    { (yyval) = symb_dollar((yyvsp[(2) - (2)])); }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 443 "input_parser.yy"
    {(yyval)=symb_dollar(gen(makevecteur((yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),(yyvsp[(5) - (5)])) ,_SEQ__VECT));}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 444 "input_parser.yy"
    { (yyval) = symb_dollar(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 445 "input_parser.yy"
    { (yyval) = symb_dollar(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 446 "input_parser.yy"
    { (yyval)=symb_dollar((yyvsp[(2) - (2)])); }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 447 "input_parser.yy"
    { (yyval) = symb_compose(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 448 "input_parser.yy"
    { (yyval) = symb_union(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 449 "input_parser.yy"
    { (yyval) = symb_intersect(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 450 "input_parser.yy"
    { (yyval) = symb_minus(gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); }
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 451 "input_parser.yy"
    { 
	(yyval)=symbolic(*(yyvsp[(2) - (3)])._FUNCptr,gen(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])) ,_SEQ__VECT)); 
	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 454 "input_parser.yy"
    { (yyval) = (yyvsp[(1) - (1)]); }
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 455 "input_parser.yy"
    {if ((yyvsp[(2) - (3)]).type==_FUNC) (yyval)=(yyvsp[(2) - (3)]); else { 
          // const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_quote((yyvsp[(2) - (3)]));
          } 
        }
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 460 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
	  (yyval) = symb_at((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]),contextptr);
        }
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 464 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
	  (yyval) = symbolic(at_of,gen(makevecteur((yyvsp[(1) - (6)]),(yyvsp[(4) - (6)])) ,_SEQ__VECT));
        }
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 468 "input_parser.yy"
    {(yyval) = check_symb_of((yyvsp[(2) - (6)]),(yyvsp[(5) - (6)]),giac_yyget_extra(scanner));}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 469 "input_parser.yy"
    {
	if (abs_calc_mode(giac_yyget_extra(scanner))==38 && (yyvsp[(2) - (3)]).type==_VECT && (yyvsp[(2) - (3)]).subtype==_SEQ__VECT && (yyvsp[(2) - (3)])._VECTptr->size()==2 && ((yyvsp[(2) - (3)])._VECTptr->front().type<=_DOUBLE_ || (yyvsp[(2) - (3)])._VECTptr->front().type==_FLOAT_) && ((yyvsp[(2) - (3)])._VECTptr->back().type<=_DOUBLE_ || (yyvsp[(2) - (3)])._VECTptr->back().type==_FLOAT_)){ 
          const giac::context * contextptr = giac_yyget_extra(scanner);
	  gen a=evalf((yyvsp[(2) - (3)])._VECTptr->front(),1,contextptr),
	      b=evalf((yyvsp[(2) - (3)])._VECTptr->back(),1,contextptr);
	  if ( (a.type==_DOUBLE_ || a.type==_FLOAT_) &&
               (b.type==_DOUBLE_ || b.type==_FLOAT_))
            (yyval)= a+b*cst_i; 
          else (yyval)=(yyvsp[(2) - (3)]);
  	} else {
             if (calc_mode(giac_yyget_extra(scanner))==1 && (yyvsp[(2) - (3)]).type==_VECT && (yyvsp[(1) - (3)])!=_LIST__VECT &&
	     (yyvsp[(2) - (3)]).subtype==_SEQ__VECT && ((yyvsp[(2) - (3)])._VECTptr->size()==2 || (yyvsp[(2) - (3)])._VECTptr->size()==3) )
               (yyval) = gen(*(yyvsp[(2) - (3)])._VECTptr,_GGB__VECT);
             else
               (yyval)=(yyvsp[(2) - (3)]);
           }
	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 486 "input_parser.yy"
    { 
        // cerr << $2 << endl;
        (yyval) = gen(*((yyvsp[(2) - (3)])._VECTptr),(yyvsp[(1) - (3)]).val);
	if ((yyvsp[(2) - (3)])._VECTptr->size()==1 && (yyvsp[(2) - (3)])._VECTptr->front().is_symb_of_sommet(at_ti_semi) ) {
	  (yyval)=(yyvsp[(2) - (3)])._VECTptr->front();
        }
        // cerr << $$ << endl;

        }
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 495 "input_parser.yy"
    { 
         if ((yyvsp[(1) - (3)]).type==_VECT && (yyvsp[(1) - (3)]).subtype==_SEQ__VECT && !((yyvsp[(3) - (3)]).type==_VECT && (yyvsp[(2) - (3)]).subtype==_SEQ__VECT)){ (yyval)=(yyvsp[(1) - (3)]); (yyval)._VECTptr->push_back((yyvsp[(3) - (3)])); }
	 else
           (yyval) = makesuite((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); 

        }
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 501 "input_parser.yy"
    { (yyval)=gen(vecteur(0),_SEQ__VECT); }
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 502 "input_parser.yy"
    {(yyval)=symb_findhelp((yyvsp[(2) - (2)]));}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 503 "input_parser.yy"
    { (yyval)=symb_interrogation((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 504 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_unit(plus_one,(yyvsp[(2) - (2)]),contextptr); 
          opened_quote(giac_yyget_extra(scanner)) &= 0x7ffffffd;	
        }
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 509 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_unit((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),contextptr); 
          opened_quote(giac_yyget_extra(scanner)) &= 0x7ffffffd;        }
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 513 "input_parser.yy"
    { (yyval)=symb_pow((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)])); }
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 514 "input_parser.yy"
    { 
        const giac::context * contextptr = giac_yyget_extra(scanner);
#ifdef HAVE_SIGNAL_H_OLD
	messages_to_print += parser_filename(contextptr) + parser_error(contextptr); 
	/* *logptr(giac_yyget_extra(scanner)) << messages_to_print; */
#endif
	(yyval)=undef;
        spread_formula(false,contextptr); 
	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 523 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 524 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(1) - (2)])._FUNCptr,(yyvsp[(2) - (2)])); }
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 525 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (1)])._FUNCptr,gen(vecteur(0),_SEQ__VECT));}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 526 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (3)])._FUNCptr,gen(vecteur(0),_SEQ__VECT));}
    break;

  case 129:

/* Line 1806 of yacc.c  */
#line 527 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval) = symb_local((yyvsp[(3) - (4)]),contextptr);
        }
    break;

  case 130:

/* Line 1806 of yacc.c  */
#line 531 "input_parser.yy"
    {(yyval) = gen(at_local,2);}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 532 "input_parser.yy"
    {
	(yyval) = symbolic(*(yyvsp[(1) - (6)])._FUNCptr,makevecteur(equaltosame((yyvsp[(3) - (6)])),symb_bloc((yyvsp[(5) - (6)])),(yyvsp[(6) - (6)])));
	}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 535 "input_parser.yy"
    {
        vecteur v=makevecteur(equaltosame((yyvsp[(3) - (7)])),(yyvsp[(5) - (7)]),(yyvsp[(7) - (7)]));
	// *logptr(giac_yyget_extra(scanner)) << v << endl;
	(yyval) = symbolic(*(yyvsp[(1) - (7)])._FUNCptr,v);
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 540 "input_parser.yy"
    { (yyval)=symb_rpn_prog((yyvsp[(2) - (3)])); }
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 541 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 542 "input_parser.yy"
    { (yyval)=symbolic(at_maple_lib,makevecteur((yyvsp[(1) - (4)]),(yyvsp[(3) - (4)]))); }
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 543 "input_parser.yy"
    { 
          if ((yyvsp[(7) - (7)]).type==_INT_ && (yyvsp[(7) - (7)]).val && (yyvsp[(7) - (7)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program((yyvsp[(3) - (7)]),zero*(yyvsp[(3) - (7)]),symb_local((yyvsp[(5) - (7)]),(yyvsp[(6) - (7)]),contextptr),contextptr); 
        }
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 548 "input_parser.yy"
    { 
          if ((yyvsp[(8) - (8)]).type==_INT_ && (yyvsp[(8) - (8)]).val && (yyvsp[(8) - (8)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program_sto((yyvsp[(4) - (8)]),zero*(yyvsp[(4) - (8)]),symb_local((yyvsp[(6) - (8)]),(yyvsp[(7) - (8)]),contextptr),(yyvsp[(2) - (8)]),false,contextptr); 
        }
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 553 "input_parser.yy"
    { 
          if ((yyvsp[(7) - (7)]).type==_INT_ && (yyvsp[(7) - (7)]).val && (yyvsp[(7) - (7)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program_sto((yyvsp[(4) - (7)]),zero*(yyvsp[(4) - (7)]),symb_bloc((yyvsp[(6) - (7)])),(yyvsp[(2) - (7)]),false,contextptr); 
        }
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 558 "input_parser.yy"
    { 
          if ((yyvsp[(9) - (9)]).type==_INT_ && (yyvsp[(9) - (9)]).val && (yyvsp[(9) - (9)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program_sto((yyvsp[(4) - (9)]),zero*(yyvsp[(4) - (9)]),symb_local((yyvsp[(7) - (9)]),(yyvsp[(8) - (9)]),contextptr),(yyvsp[(2) - (9)]),false,contextptr); 
        }
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 563 "input_parser.yy"
    { 
          if ((yyvsp[(8) - (8)]).type==_INT_ && (yyvsp[(8) - (8)]).val && (yyvsp[(8) - (8)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
         (yyval)=symb_program((yyvsp[(3) - (8)]),zero*(yyvsp[(3) - (8)]),symb_local((yyvsp[(5) - (8)]),(yyvsp[(7) - (8)]),contextptr),contextptr); 
        }
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 568 "input_parser.yy"
    { 
          if ((yyvsp[(8) - (8)]).type==_INT_ && (yyvsp[(8) - (8)]).val && (yyvsp[(8) - (8)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program_sto((yyvsp[(3) - (8)]),zero*(yyvsp[(3) - (8)]),symb_local((yyvsp[(6) - (8)]),(yyvsp[(7) - (8)]),contextptr),(yyvsp[(1) - (8)]),false,contextptr); 
        }
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 573 "input_parser.yy"
    { 
          if ((yyvsp[(9) - (9)]).type==_INT_ && (yyvsp[(9) - (9)]).val && (yyvsp[(9) - (9)]).val!=3) giac_yyerror(scanner,"missing func/prog/proc end delimiter");
          const giac::context * contextptr = giac_yyget_extra(scanner);
           (yyval)=symb_program_sto((yyvsp[(3) - (9)]),zero*(yyvsp[(3) - (9)]),symb_local((yyvsp[(7) - (9)]),(yyvsp[(8) - (9)]),contextptr),(yyvsp[(1) - (9)]),false,contextptr); 
        }
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 578 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (9)])._FUNCptr,makevecteur((yyvsp[(3) - (9)]),equaltosame((yyvsp[(5) - (9)])),(yyvsp[(7) - (9)]),symb_bloc((yyvsp[(9) - (9)]))));}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 579 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (10)])._FUNCptr,makevecteur((yyvsp[(3) - (10)]),equaltosame((yyvsp[(5) - (10)])),(yyvsp[(7) - (10)]),(yyvsp[(9) - (10)])));}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 580 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,gen2vecteur((yyvsp[(3) - (4)])));}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 581 "input_parser.yy"
    {(yyval)=symbolic(at_member,makesequence((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])));}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 582 "input_parser.yy"
    { (yyval)=symbolic(at_apply,makesequence(symbolic(at_program,makesequence((yyvsp[(4) - (7)]),0*(yyvsp[(4) - (7)]),vecteur(1,(yyvsp[(2) - (7)])))),(yyvsp[(6) - (7)]))); }
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 583 "input_parser.yy"
    { (yyval)=symbolic(at_apply,symbolic(at_program,makesequence((yyvsp[(4) - (9)]),0*(yyvsp[(4) - (9)]),vecteur(1,(yyvsp[(2) - (9)])))),symbolic(at_select,makesequence(symbolic(at_program,makesequence((yyvsp[(4) - (9)]),0*(yyvsp[(4) - (9)]),(yyvsp[(8) - (9)]))),(yyvsp[(6) - (9)])))); }
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 584 "input_parser.yy"
    { 
	vecteur v=makevecteur(zero,equaltosame((yyvsp[(3) - (5)])),zero,symb_bloc((yyvsp[(5) - (5)])));
	(yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,v); 
	}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 588 "input_parser.yy"
    { 
	(yyval)=symbolic(*(yyvsp[(1) - (6)])._FUNCptr,makevecteur(zero,equaltosame((yyvsp[(3) - (6)])),zero,(yyvsp[(5) - (6)]))); 
	}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 591 "input_parser.yy"
    { 
          if ((yyvsp[(5) - (5)]).type==_INT_ && (yyvsp[(5) - (5)]).val && (yyvsp[(5) - (5)]).val!=9 && (yyvsp[(5) - (5)]).val!=8) giac_yyerror(scanner,"missing loop end delimiter");
	  (yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,makevecteur(zero,equaltosame((yyvsp[(2) - (5)])),zero,symb_bloc((yyvsp[(4) - (5)])))); 
        }
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 595 "input_parser.yy"
    { 
          if ((yyvsp[(5) - (5)]).type==_INT_ && (yyvsp[(5) - (5)]).val && (yyvsp[(5) - (5)]).val!=9 && (yyvsp[(5) - (5)]).val!=8) giac_yyerror(scanner,"missing loop end delimiter");
          (yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,makevecteur(zero,equaltosame((yyvsp[(2) - (5)])),zero,symb_bloc((yyvsp[(4) - (5)])))); 
        }
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 599 "input_parser.yy"
    { (yyval)=symb_try_catch(makevecteur(symb_bloc((yyvsp[(2) - (7)])),(yyvsp[(5) - (7)]),symb_bloc((yyvsp[(7) - (7)]))));}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 600 "input_parser.yy"
    {(yyval)=symb_try_catch(gen2vecteur((yyvsp[(3) - (4)])));}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 601 "input_parser.yy"
    {(yyval)=gen(at_try_catch,3);}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 602 "input_parser.yy"
    { (yyval)=symb_case((yyvsp[(3) - (7)]),(yyvsp[(6) - (7)])); }
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 603 "input_parser.yy"
    { (yyval) = symb_case((yyvsp[(3) - (4)])); }
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 604 "input_parser.yy"
    { (yyval)=symb_case((yyvsp[(2) - (4)]),(yyvsp[(3) - (4)])); }
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 605 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 606 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 607 "input_parser.yy"
    {(yyval) = gen(*(yyvsp[(1) - (2)])._FUNCptr,0);}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 608 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(1) - (3)])._FUNCptr,makevecteur(zero,plus_one,zero,symb_bloc((yyvsp[(2) - (3)])))); }
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 609 "input_parser.yy"
    {(yyval) = symbolic(*(yyvsp[(1) - (4)])._FUNCptr,makevecteur(equaltosame((yyvsp[(2) - (4)])),(yyvsp[(4) - (4)]),0));}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 610 "input_parser.yy"
    { (yyval)=symb_try_catch(makevecteur(symb_bloc((yyvsp[(2) - (5)])),at_break,symb_bloc((yyvsp[(4) - (5)])))); }
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 611 "input_parser.yy"
    { (yyval)=symb_try_catch(makevecteur(symb_bloc((yyvsp[(2) - (4)])),at_break,0)); }
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 612 "input_parser.yy"
    { (yyval)=symb_try_catch(makevecteur(symb_bloc((yyvsp[(2) - (6)])),at_break,symb_bloc((yyvsp[(5) - (6)])))); }
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 613 "input_parser.yy"
    { (yyval)=symb_try_catch(makevecteur(symb_bloc((yyvsp[(2) - (5)])),at_break,0)); }
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 614 "input_parser.yy"
    { vecteur v1(gen2vecteur((yyvsp[(1) - (3)]))),v3(gen2vecteur((yyvsp[(3) - (3)]))); (yyval)=symbolic(at_ti_semi,makevecteur(v1,v3)); }
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 615 "input_parser.yy"
    { 
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_program_sto((yyvsp[(4) - (13)]),(yyvsp[(4) - (13)])*zero,symb_local((yyvsp[(10) - (13)]),mergevecteur(*(yyvsp[(7) - (13)])._VECTptr,*(yyvsp[(12) - (13)])._VECTptr),contextptr),(yyvsp[(2) - (13)]),false,contextptr); 
	}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 619 "input_parser.yy"
    { 
          const giac::context * contextptr = giac_yyget_extra(scanner);
	(yyval)=symb_program_sto((yyvsp[(4) - (12)]),(yyvsp[(4) - (12)])*zero,symb_local((yyvsp[(9) - (12)]),mergevecteur(*(yyvsp[(7) - (12)])._VECTptr,*(yyvsp[(11) - (12)])._VECTptr),contextptr),(yyvsp[(2) - (12)]),false,contextptr); 
	}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 623 "input_parser.yy"
    { 
          const giac::context * contextptr = giac_yyget_extra(scanner);
	(yyval)=symb_program_sto((yyvsp[(4) - (12)]),(yyvsp[(4) - (12)])*zero,symb_local((yyvsp[(9) - (12)]),(yyvsp[(11) - (12)]),contextptr),(yyvsp[(2) - (12)]),false,contextptr); 
	}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 627 "input_parser.yy"
    { 
	(yyval)=symb_program_sto((yyvsp[(4) - (8)]),(yyvsp[(4) - (8)])*zero,symb_bloc((yyvsp[(7) - (8)])),(yyvsp[(2) - (8)]),false,giac_yyget_extra(scanner)); 
	}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 630 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(1) - (3)])._FUNCptr,(yyvsp[(2) - (3)])); }
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 631 "input_parser.yy"
    { (yyval)=symbolic(*(yyvsp[(1) - (2)])._FUNCptr,(yyvsp[(2) - (2)])); }
    break;

  case 175:

/* Line 1806 of yacc.c  */
#line 632 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 633 "input_parser.yy"
    { (yyval)=symb_program_sto((yyvsp[(4) - (7)]),(yyvsp[(4) - (7)])*zero,(yyvsp[(7) - (7)]),(yyvsp[(2) - (7)]),false,giac_yyget_extra(scanner));}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 634 "input_parser.yy"
    { 
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval)=symb_program_sto((yyvsp[(4) - (13)]),(yyvsp[(4) - (13)])*zero,symb_local((yyvsp[(10) - (13)]),(yyvsp[(12) - (13)]),contextptr),(yyvsp[(2) - (13)]),false,contextptr);
        }
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 638 "input_parser.yy"
    { (yyval)=symb_program_sto((yyvsp[(4) - (9)]),(yyvsp[(4) - (9)])*zero,symb_bloc((yyvsp[(8) - (9)])),(yyvsp[(2) - (9)]),false,giac_yyget_extra(scanner)); }
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 639 "input_parser.yy"
    {
           vecteur & v=*(yyvsp[(2) - (5)])._VECTptr;
           if ( (v.size()<3) || v[0].type!=_IDNT){
             *logptr(giac_yyget_extra(scanner)) << "Syntax For name,begin,end[,step]" << endl;
             (yyval)=undef;
           }
           else {
             gen pas(plus_one);
             if (v.size()==4)
               pas=v[3];
             gen condition;
             if (is_positive(-pas,0))
               condition=symb_superieur_egal(v[0],v[2]);
            else
               condition=symb_inferieur_egal(v[0],v[2]);
            vecteur w=makevecteur(symb_sto(v[1],v[0]),condition,symb_sto(symb_plus(v[0],pas),v[0]),symb_bloc((yyvsp[(4) - (5)])));
             (yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,w);
           }
	}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 658 "input_parser.yy"
    { 
	vecteur v=makevecteur(zero,equaltosame((yyvsp[(2) - (5)])),zero,symb_bloc((yyvsp[(4) - (5)])));
	(yyval)=symbolic(*(yyvsp[(1) - (5)])._FUNCptr,v); 
	}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 670 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 671 "input_parser.yy"
    { 
	       gen tmp((yyvsp[(3) - (3)])); 
	       // tmp.subtype=1; 
	       (yyval)=symb_check_type(makevecteur(tmp,(yyvsp[(1) - (3)])),context0); 
          }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 676 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 677 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 678 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 679 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (5)]),(yyvsp[(4) - (5)]))); }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 680 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur(0,(yyvsp[(2) - (2)]))); }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 681 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 689 "input_parser.yy"
    { 
	  gen tmp((yyvsp[(1) - (2)])); 
	  // tmp.subtype=1; 
	  (yyval)=symb_check_type(makevecteur(tmp,(yyvsp[(2) - (2)])),context0); 
	  }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 694 "input_parser.yy"
    {(yyval)=symbolic(*(yyvsp[(1) - (2)])._FUNCptr,(yyvsp[(2) - (2)])); }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 698 "input_parser.yy"
    { (yyval)=makevecteur(vecteur(0),vecteur(0)); }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 699 "input_parser.yy"
    { vecteur v1 =gen2vecteur((yyvsp[(1) - (2)])); vecteur v2=gen2vecteur((yyvsp[(2) - (2)])); (yyval)=makevecteur(mergevecteur(gen2vecteur(v1[0]),gen2vecteur(v2[0])),mergevecteur(gen2vecteur(v1[1]),gen2vecteur(v2[1]))); }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 700 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 704 "input_parser.yy"
    { if ((yyvsp[(3) - (4)]).type==_VECT) (yyval)=gen(*(yyvsp[(3) - (4)])._VECTptr,_RPN_STACK__VECT); else (yyval)=gen(vecteur(1,(yyvsp[(3) - (4)])),_RPN_STACK__VECT); }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 705 "input_parser.yy"
    { (yyval)=gen(vecteur(0),_RPN_STACK__VECT); }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 708 "input_parser.yy"
    { if (!(yyvsp[(1) - (3)]).val) (yyval)=makevecteur((yyvsp[(2) - (3)]),vecteur(0)); else (yyval)=makevecteur(vecteur(0),(yyvsp[(2) - (3)]));}
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 711 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 714 "input_parser.yy"
    { (yyval)=gen(vecteur(1,(yyvsp[(1) - (1)])),_SEQ__VECT); }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 715 "input_parser.yy"
    { 
	       vecteur v=*(yyvsp[(1) - (3)])._VECTptr;
	       v.push_back((yyvsp[(3) - (3)]));
	       (yyval)=gen(v,_SEQ__VECT);
	     }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 722 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 723 "input_parser.yy"
    { (yyval)=symb_sto((yyvsp[(3) - (3)]),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)])==at_array_sto); }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 724 "input_parser.yy"
    { (yyval)=symb_equal((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])); }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 725 "input_parser.yy"
    { (yyval)=symbolic(at_deuxpoints,makesequence((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)])));  }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 726 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 727 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); *logptr(giac_yyget_extra(scanner)) << "Error: reserved word "<< (yyvsp[(1) - (1)]) <<endl;}
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 728 "input_parser.yy"
    { (yyval)=symb_double_deux_points(makevecteur((yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]))); *logptr(giac_yyget_extra(scanner)) << "Error: reserved word "<< (yyvsp[(1) - (3)]) <<endl; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 729 "input_parser.yy"
    { 
  const giac::context * contextptr = giac_yyget_extra(scanner);
  (yyval)=string2gen("_"+(yyvsp[(1) - (1)]).print(contextptr),false); 
  if (!giac::first_error_line(contextptr)){
    giac::first_error_line(giac::lexer_line_number(contextptr),contextptr);
    giac:: error_token_name((yyvsp[(1) - (1)]).print(contextptr)+ " (reserved word)",contextptr);
  }
}
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 737 "input_parser.yy"
    { 
  const giac::context * contextptr = giac_yyget_extra(scanner);
  (yyval)=string2gen("_"+(yyvsp[(1) - (1)]).print(contextptr),false);
  if (!giac::first_error_line(contextptr)){
    giac::first_error_line(giac::lexer_line_number(contextptr),contextptr);
    giac:: error_token_name((yyvsp[(1) - (1)]).print(contextptr)+ " reserved word",contextptr);
  }
}
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 747 "input_parser.yy"
    { (yyval)=plus_one;}
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 748 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 751 "input_parser.yy"
    { (yyval)=gen(vecteur(0),_SEQ__VECT); }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 752 "input_parser.yy"
    { (yyval)=makesuite((yyvsp[(1) - (1)])); }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 755 "input_parser.yy"
    { (yyval) = makevecteur((yyvsp[(1) - (1)])); }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 757 "input_parser.yy"
    { vecteur v(1,(yyvsp[(1) - (2)])); 
			  if ((yyvsp[(1) - (2)]).type==_VECT) v=*((yyvsp[(1) - (2)])._VECTptr); 
			  v.push_back((yyvsp[(2) - (2)])); 
			  (yyval) = v;
			}
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 762 "input_parser.yy"
    { (yyval) = (yyvsp[(1) - (2)]);}
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 765 "input_parser.yy"
    { (yyval)=vecteur(0); }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 766 "input_parser.yy"
    { (yyval)=mergevecteur(vecteur(1,(yyvsp[(1) - (2)])),*((yyvsp[(2) - (2)])._VECTptr));}
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 767 "input_parser.yy"
    { (yyval)=mergevecteur(vecteur(1,(yyvsp[(1) - (3)])),*((yyvsp[(3) - (3)])._VECTptr));}
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 770 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 840 "input_parser.yy"
    { (yyval)=plus_one; }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 841 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 844 "input_parser.yy"
    { (yyval)=plus_one; }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 845 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 846 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 847 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 850 "input_parser.yy"
    { (yyval)=plus_one; }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 851 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 854 "input_parser.yy"
    { (yyval)=0; }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 855 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 856 "input_parser.yy"
    { (yyval)=symb_bloc((yyvsp[(2) - (2)])); }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 860 "input_parser.yy"
    { 
	(yyval) = (yyvsp[(2) - (3)]);
	}
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 863 "input_parser.yy"
    {
          const giac::context * contextptr = giac_yyget_extra(scanner);
          (yyval) = symb_local((yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),contextptr);
         }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 870 "input_parser.yy"
    { if ((yyvsp[(1) - (1)]).type==_INT_ && (yyvsp[(1) - (1)]).val && (yyvsp[(1) - (1)]).val!=4) giac_yyerror(scanner,"missing test end delimiter"); (yyval)=0; }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 871 "input_parser.yy"
    {
          if ((yyvsp[(3) - (3)]).type==_INT_ && (yyvsp[(3) - (3)]).val && (yyvsp[(3) - (3)]).val!=4) giac_yyerror(scanner,"missing test end delimiter");
	(yyval)=symb_bloc((yyvsp[(2) - (3)])); 
	}
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 875 "input_parser.yy"
    { 
	  (yyval)=symb_ifte(equaltosame((yyvsp[(2) - (5)])),symb_bloc((yyvsp[(4) - (5)])),(yyvsp[(5) - (5)]));
	  }
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 878 "input_parser.yy"
    { 
	  (yyval)=symb_ifte(equaltosame((yyvsp[(3) - (6)])),symb_bloc((yyvsp[(5) - (6)])),(yyvsp[(6) - (6)]));
	  }
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 883 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 884 "input_parser.yy"
    { (yyval)=(yyvsp[(2) - (2)]); }
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 887 "input_parser.yy"
    { (yyval)=0; }
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 888 "input_parser.yy"
    { (yyval)=0; }
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 891 "input_parser.yy"
    { (yyval)=vecteur(0); }
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 892 "input_parser.yy"
    { (yyval)=makevecteur(symb_bloc((yyvsp[(3) - (3)])));}
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 893 "input_parser.yy"
    { (yyval)=mergevecteur(makevecteur((yyvsp[(2) - (5)]),symb_bloc((yyvsp[(4) - (5)]))),*((yyvsp[(5) - (5)])._VECTptr));}
    break;

  case 244:

/* Line 1806 of yacc.c  */
#line 896 "input_parser.yy"
    { (yyval)=vecteur(0); }
    break;

  case 245:

/* Line 1806 of yacc.c  */
#line 897 "input_parser.yy"
    { (yyval)=vecteur(1,symb_bloc((yyvsp[(2) - (2)]))); }
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 898 "input_parser.yy"
    { (yyval)=mergevecteur(makevecteur((yyvsp[(2) - (5)]),symb_bloc((yyvsp[(4) - (5)]))),*((yyvsp[(5) - (5)])._VECTptr));}
    break;

  case 247:

/* Line 1806 of yacc.c  */
#line 901 "input_parser.yy"
    { (yyval)=vecteur(0); }
    break;

  case 248:

/* Line 1806 of yacc.c  */
#line 902 "input_parser.yy"
    { (yyval)=vecteur(1,symb_bloc((yyvsp[(2) - (2)]))); }
    break;

  case 249:

/* Line 1806 of yacc.c  */
#line 903 "input_parser.yy"
    { (yyval)=mergevecteur(makevecteur((yyvsp[(2) - (6)]),symb_bloc((yyvsp[(4) - (6)]))),gen2vecteur((yyvsp[(6) - (6)])));}
    break;

  case 250:

/* Line 1806 of yacc.c  */
#line 904 "input_parser.yy"
    { (yyval)=mergevecteur(makevecteur((yyvsp[(2) - (7)]),symb_bloc((yyvsp[(4) - (7)]))),gen2vecteur((yyvsp[(7) - (7)])));}
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 907 "input_parser.yy"
    { (yyval)=(yyvsp[(1) - (1)]); }
    break;



/* Line 1806 of yacc.c  */
#line 6959 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, scanner);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 914 "input_parser.yy"


#ifndef NO_NAMESPACE_GIAC
} // namespace giac


#endif // ndef NO_NAMESPACE_GIAC
int giac_yyget_column  (yyscan_t yyscanner);

// Error print routine (store error string in parser_error)
#if 1
int giac_yyerror(yyscan_t scanner,const char *s) {
 const giac::context * contextptr = giac_yyget_extra(scanner);
 int col = giac_yyget_column(scanner);
 int line = giac::lexer_line_number(contextptr);
 std::string token_name=string(giac_yyget_text(scanner));
 bool is_at_end = (token_name.size()==2 && (token_name[0]==char(0xC3)) && (token_name[1]==char(0xBF)));
 std::string suffix = " (reserved word)";
 if (token_name.size()>suffix.size() && token_name.compare(token_name.size()-suffix.size(),suffix.size(),suffix)) {
  if (col>=token_name.size()-suffix.size()) {
   col -= token_name.size()-suffix.size();
  }
 } else if (col>=token_name.size()) {
   col -= token_name.size();
 }
 giac::lexer_column_number(contextptr)=col;
 if (is_at_end) {
  parser_error(":" + giac::print_INT_(line) + ": " +string(s) + " at end of input\n",contextptr);
  giac::parsed_gen(giac::undef,contextptr);
 } else {
 parser_error( ":" + giac::print_INT_(line) + ": " + string(s) + " line " + giac::print_INT_(line) + " col " + giac::print_INT_(col) + " at " + token_name +"\n",contextptr);
 giac::parsed_gen(giac::string2gen(token_name,false),contextptr);
 }
 if (!giac::first_error_line(contextptr)) {
  giac::first_error_line(line,contextptr);
  if (is_at_end) {
   token_name="end of input";
  }
  giac:: error_token_name(token_name,contextptr);
 }
 return line;
}

#else

int giac_yyerror(yyscan_t scanner,const char *s)
{
  const giac::context * contextptr = giac_yyget_extra(scanner);
  int col= giac_yyget_column(scanner);
  giac::lexer_column_number(contextptr)=col;
  if ( (*giac_yyget_text( scanner )) && (giac_yyget_text( scanner )[0]!=-61) && (giac_yyget_text( scanner )[1]!=-65)){
    std::string txt=giac_yyget_text( scanner );
    parser_error( ":" + giac::print_INT_(giac::lexer_line_number(contextptr)) + ": " + string(s) + " line " + giac::print_INT_(giac::lexer_line_number(contextptr)) + " col " + giac::print_INT_(col) + " at " + txt +"\n",contextptr);
     giac::parsed_gen(giac::string2gen(txt,false),contextptr);
  }
  else {
    parser_error(":" + giac::print_INT_(giac::lexer_line_number(contextptr)) + ": " +string(s) + " at end of input\n",contextptr);
    giac::parsed_gen(giac::undef,contextptr);
  }
  if (!giac::first_error_line(contextptr)){
    giac::first_error_line(giac::lexer_line_number(contextptr),contextptr);
    std::string s=string(giac_yyget_text( scanner ));
    if (s.size()==2 && s[0]==-61 && s[1]==-65)
      s="end of input";
    giac:: error_token_name(s,contextptr);
  }
  return giac::lexer_line_number(contextptr);
}
#endif

