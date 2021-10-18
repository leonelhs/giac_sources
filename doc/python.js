// CodeMirror, copyright (c) by Marijn Haverbeke and others
// Distributed under an MIT license: http://codemirror.net/LICENSE

(function(mod) {
  if (typeof exports == "object" && typeof module == "object") // CommonJS
    mod(require("../../lib/codemirror"));
  else if (typeof define == "function" && define.amd) // AMD
    define(["../../lib/codemirror"], mod);
  else // Plain browser env
    mod(CodeMirror);
})(function(CodeMirror) {
  "use strict";

  function wordRegexp(words) {
    return new RegExp("^((" + words.join(")|(") + "))\\b");
  }

  var wordOperators = wordRegexp(["and", "or", "not", "is"]);
  var commonKeywords = ["as", "assert", "break", "class", "continue",
                        "def", "del", "elif", "else", "except", "finally",
                        "for", "from", "global", "if", "import",
                        "lambda", "pass", "raise", "return",
                        "try", "while", "with", "yield", "in"];
  var commonBuiltins = ["abs", "all", "any", "bin", "bool", "bytearray", "callable", "chr",
                        "classmethod", "compile", "complex", "delattr", "dict", "dir", "divmod",
                        "enumerate", "eval", "filter", "float", "format", "frozenset",
                        "getattr", "globals", "hasattr", "hash", "help", "hex", "id",
                        "input", "int", "isinstance", "issubclass", "iter", "len",
                        "list", "locals", "map", "max", "memoryview", "min", "next",
                        "object", "oct", "open", "ord", "pow", "property", "range",
                        "repr", "reversed", "round", "set", "setattr", "slice",
                        "sorted", "staticmethod", "str", "sum", "super", "tuple",
                        "type", "vars", "zip", "__import__", "NotImplemented",
                        "Ellipsis", "__debug__"];
  CodeMirror.registerHelper("hintWords", "python", commonKeywords.concat(commonBuiltins));

  function top(state) {
    return state.scopes[state.scopes.length - 1];
  }

  CodeMirror.defineMode("python", function(conf, parserConf) {
    var ERRORCLASS = "error";

    var delimiters = parserConf.delimiters || parserConf.singleDelimiters || /^[\(\)\[\]\{\}@,:`=;\.]/;
    //               (Backwards-compatiblity with old, cumbersome config system)
    var operators = [parserConf.singleOperators, parserConf.doubleOperators, parserConf.doubleDelimiters, parserConf.tripleDelimiters,
                     parserConf.operators || /^([-+*/%\/&|^]=?|[<>=]+|\/\/=?|\*\*=?|!=|[~!@])/]
    for (var i = 0; i < operators.length; i++) if (!operators[i]) operators.splice(i--, 1)

    var hangingIndent = parserConf.hangingIndent || conf.indentUnit;

    var myKeywords = commonKeywords, myBuiltins = commonBuiltins;
    if (parserConf.extra_keywords != undefined)
      myKeywords = myKeywords.concat(parserConf.extra_keywords);

    if (parserConf.extra_builtins != undefined)
      myBuiltins = myBuiltins.concat(parserConf.extra_builtins);

    var py3 = !(parserConf.version && Number(parserConf.version) < 3)
    if (py3) {
      // since http://legacy.python.org/dev/peps/pep-0465/ @ is also an operator
      var identifiers = parserConf.identifiers|| /^[_A-Za-z\u00A1-\uFFFF][_A-Za-z0-9\u00A1-\uFFFF]*/;
      myKeywords = myKeywords.concat(["nonlocal", "False", "True", "None", "async", "await"]);
      myBuiltins = myBuiltins.concat(["ascii", "bytes", "exec", "print"]);
      var stringPrefixes = new RegExp("^(([rbuf]|(br))?('{3}|\"{3}|['\"]))", "i");
    } else {
      var identifiers = parserConf.identifiers|| /^[_A-Za-z][_A-Za-z0-9]*/;
      myKeywords = myKeywords.concat(["exec", "print"]);
      myBuiltins = myBuiltins.concat(["apply", "basestring", "buffer", "cmp", "coerce", "execfile",
                                      "file", "intern", "long", "raw_input", "reduce", "reload",
                                      "unichr", "unicode", "xrange", "False", "True", "None"]);
      var stringPrefixes = new RegExp("^(([rubf]|(ur)|(br))?('{3}|\"{3}|['\"]))", "i");
    }
    myKeywords = myKeywords.concat(["ABS","ACOS","ACOSH","ACOT","ACSC","ADDCOL","ADDROW","ALOG","ARC","ARG","ASEC","ASIN","ASINH","ATAN","ATANH","Airy_Ai","Airy_Bi","Ans","Archive","BINOMIAL","BesselI","BesselJ","BesselK","BesselY","Beta","Bezier","BlockDiagonal","CEILING","CHOOSE","COLNORM","COMB","CONCAT","COND","CONJ","COS","COSH","COT","CROSS","CSC","Celsius2Fahrenheit","Ci","Ci0","Circle","ClrDraw","ClrGraph","ClrIO","CopyVar","CyclePic","DEGXRAD","DELCOL","DELROW","DET","DISP","DOT","DROP","DUP","DelFold","DelVar","Det","Dirac","DispG","DispHome","DrawFunc","DrawInv","DrawParm","DrawPol","DrawSlp","DrwCtour","EDITMAT","EIGENVAL","EIGENVV","EXP","EXPM1","EXPORT","Ei","Ei0","Ei_f","Eta","Exec","FLOOR","FNROOT","Factor","Fahrenheit2Celsius","Fill","GETKEY","ifndef NO_RTTI{GF","endif{Gamma","Gcd","Gcdex","Get","GetCalc","GetFold","Graph","HMSX","Heaviside","IDENMAT","IFTE","IM","INPUT","INVERSE","ISOLATE","ITERATE","Input","InputStr","Int","Inverse","JordanBlock","LINE","LN","LNP1","LOG","LQ","LSQ","LU","Line","LineHorz","LineTan","LineVert","MAKELIST","MAKEMAT","MANT","MAX","MAXREAL","MIN","MINREAL","MOD","MSGBOX","NOP","NORMALD","NTHROOT","NewFold","NewPic","Nullspace","OVER","Output","Ox_2d_unit_vector","Ox_3d_unit_vector","Oy_2d_unit_vector","Oy_3d_unit_vector","Oz_3d_unit_vector","PERM","PICK","PIECEWISE","PIXOFF","PIXON","POISSON","POLYCOEF","POLYEVAL","POLYFORM","POLYROOT","POS","PRINT","Pause","Phi","Pictsize","PopUp","Prompt","Psi","Psi_minus_ln","PtOff","PtOn","PtText","PxlOff","PxlOn","QR","QUAD","QUOTE","Quo","RADXDEG","RANDMAT","RANDOM","RANDSEED","RANK","RCL","RE","RECT","RECURSE","REDIM","REPLACE","REVERSE","ROUND","ROWNORM","RREF","RandSeed","Rank","RclPic","Rem","Resultant","RplcPic","Rref","SCALE","SCALEADD","SCHUR","SEC","SIGN","SIN","SINH","SIZE","SORT","SPECNORM","SPECRAD","SUB","SVD","SVL","SWAP","SWAPCOL","SWAPROW","SetFold","Si","SiCi_f","SiCi_g","SortA","SortD","StoPic","Store","Sum","TAN","TANH","TAYLOR","TRACE","TRN","TRUNCATE","TeX","UTPC","UTPF","UTPN","UTPT","Unarchiv","VIEWS","WAIT","XHMS","XPON","Zeta","ZoomRcl","ZoomSto","a2q","abcuv","about","abs","abscissa","accumulate_head_tail","acos","acos2asin","acos2atan","acosh","acot","acsc","add","add_language","additionally","adjoint_matrix","affix","algvar","alog10","alors","altitude","and","angle","angleat","angleatraw","animate","animate3d","animation","ans","append","apply","approx","arc","arcLen","area","areaat","areaatraw","areaplot","arg","array","array_sto","as_function_of","asc","asec","asin","asin2acos","asin2atan","asinh","assert","assign","assume","atan","atan2acos","atan2asin","atanh","atrig2ln","augment","avance","avgRC","background","backward","baisse_crayon","bar_plot","barycenter","basis","bernoulli","bezout_entiers","binomial","binomial_cdf","binomial_icdf","binprint","bisector","bitand","bitmap","bitor","bitxor","black","blockmatrix","blue","border","bounded_function","boxwhisker","break","breakpoint","by","c1oc2","c1op2","cFactor","cSolve","cZeros","cache_tortue","calc_mode","camembert","canonical_form","cap","cas_setup","cat","cd","ceil","ceiling","cell","center","center2interval","centered_cube","centered_tetrahedron","cfactor","changebase","char","charpoly","chinrem","chisquare","chisquare_cdf","chisquare_icdf","cholesky","choosebox","chrem","circle","circumcircle","classes","clearscreen","click","close","coeff","coeffs","col","colDim","colNorm","coldim","collect","colnorm","color","colspace","comDenom","comb","combine","comment","common_perpendicular","companion","compare","complexroot","concat","cone","conic","conj","cont","contains","content","contourplot","convert","convertir","convexhull","coordinates","copy","correlation","cos","cos2sintan","cosh","cot","cote","count","count_eq","count_inf","count_sup","courbe_parametrique","courbe_polaire","covariance","covariance_correlation","cpartfrac","crationalroot","crayon","critical","cross","crossP","cross_ratio","crossproduct","csc","csolve","csv2gen","cube","curvature","cumSum","cumulated_frequencies","curl","current_sheet","curve","cyan","cycle2perm","cycleinv","cycles2permu","cyclotomic","cylinder","de","deSolve","debug","debug_infolevel","debut_enregistrement","decrement","degree","delcols","delrows","deltalist","denom","densityplot","deriver","desolve","dessine_tortue","det","det_minor","developper","developper_transcendant","dfc","dfc2f","diag","diff","dim","display","disque","disque_centre","distance","distance2","distanceat","distanceatraw","div","divcrement","divergence","divide","divis","division_point","divisors","divpc","dodecahedron","dot","dotP","dotprod","droit","droite","droite_tangente","dsolve","e2r","ecart_type","ecart_type_population","ecris","efface","egcd","egv","egvl","eigVc","eigVl","eigenvals","eigenvalues","eigenvectors","eigenvects","element","ellipse","entry","envelope","epsilon2zero","equal2diff","equal2list","equation","equilateral_triangle","erase3d","erf","erfc","erfs","et","euler","euler_mac_laurin","eval","eval_level","evala","evalb","evalc","evalf","evalm","even","evolute","exact","exbisector","excircle","execute","exp","exp2list","exp2pow","exp2trig","expexpand","exponential_regression","exponential_regression_plot","expr","extract_measure","extrema","ezgcd","f2nd","fMax","fMin","fPart","faces","facteurs_premiers","factor","factor_xn","factorial","factoriser","factoriser_entier","factoriser_sur_C","factoriser_xn","factors","faire","fclose","fcoeff","ffonction","fft","fieldplot","filled","fin_enregistrement","findhelp","fisher","fisher_cdf","fisher_icdf","flatten","float","float2rational","floor","fonction","fonction_derivee","fopen","format","forward","fourier_an","fourier_bn","fourier_cn","fprint","frac","fracmod","frame_2d","frame_3d","froot","fsolve","funcplot","function_diff","fxnd","gauche","gauss","gaussjord","gbasis","gcd","gcdex","genpoly","geo2d","geo3d","getDenom","getKey","getNum","getType","giac","goto","grad","gramschmidt","graph2tex","graph3d2tex","graphe","graphe3d","graphe_suite","greduce","green","groupermu","hadamard","half_cone","half_line","halftan","halftan_hyp2exp","halt","hamdist","harmonic_conjugate","harmonic_division","has","hasard","head","heap_mult","hermite","hessenberg","hessian","heugcd","hexagon","hexprint","hidden_name","hilbert","histogram","hold","homothety","horner","hp38","hyp2exp","hyperbola","hyperplan","hypersphere","hypersurface","iPart","iabcuv","ibasis","ibpdv","ibpu","ichinrem","ichrem","icontent","icosahedron","id","identity","idivis","idn","iegcd","ifactor","ifactors","ifft","igcd","igcdex","ihermite","ilaplace","im","imag","image","implicitplot","implicitplot3d","inString","in_ideal","incircle","increment","indets","inequationplot","input","inputform","insmod","int","intDiv","integer_format","integrate","integrer","inter","interactive","interactive_odeplot","interactive_plotode","interp","interval2center","inv","inverse","inversion","invlaplace","invztrans","iquo","iquorem","iratrecon","irem","isPrime","is_collinear","is_concyclic","is_conjugate","is_coplanar","is_cycle","is_element","is_equilateral","is_harmonic","is_harmonic_circle_bundle","is_harmonic_line_bundle","is_orthogonal","is_parallel","is_parallelogram","is_permu","is_perpendicular","is_prime","is_pseudoprime","is_rectangle","is_rhombus","is_square","ismith","isobarycenter","isom","isopolygon","isprime","ithprime","jacobi_symbol","jordan","jusque","ker","kernel","keyboard","kill","l1norm","l2norm","label","lagrange","laguerre","laplace","laplacian","latex","lcm","lcoeff","ldegree","left","legend","legendre","legendre_symbol","length","leve_crayon","lgcd","lhs","ligne_polygonale","ligne_polygonale_pointee","limit","limite","lin","line","line_inter","line_segments","linear_interpolate","linear_regression","linear_regression_plot","lineariser","lineariser_trigo","linfnorm","linsolve","lis","lis_phrase","list2mat","listplot","lll","ln","lnGamma_minus","lname","lncollect","lnexpand","locus","log10","logarithmic_regression","logarithmic_regression_plot","logb","logistic_regression","logistic_regression_plot","lpsolve","lsmod","lu","lvar","mRow","mRowAdd","magenta","makelist","makemat","makemod","makesuite","makevector","map","maple2mupad","maple2xcas","maple_ifactors","maple_mode","mat2list","mathml","matpow","matrix","matrix_norm","max","maxnorm","mean","median","median_line","member","mid","midpoint","min","mkisom","mksa","modgcd","modgcd_cachesize","modp","mods","montre_tortue","moustache","moyal","moyenne","mpzclass_allowed","mul","mult_c_conjugate","mult_conjugate","multcrement","multiplier_conjugue","multiplier_conjugue_complexe","multiply","mupad2maple","mupad2xcas","nCr","nDeriv","nInt","nPr","nSolve","ncols","newList","newMat","newton","nextperm","nextprime","nodisp","non","non_recursive_normal","nop","nops","norm","normal","normal_cdf","normal_icdf","normald","normald_cdf","normald_icdf","normalize","normalt","nrows","nuage_points","nullspace","numer","octahedron","octprint","odd","odeplot","odesolve","op","open","open_polygon","or","ord","order_size","ordinate","orthocenter","orthogonal","os_version","ou","output","p1oc2","p1op2","pa2b2","pade","padic_linsolve","parabola","parabolic_interpolate","parallel","parallelepiped","parallelogram","parameq","parameter","paramplot","pari","pari_unlock","part","partfrac","pas","pas_de_cote","pcar","pcar_hessenberg","pcoeff","perimeter","perimeterat","perimeteratraw","perm","perminv","permu2cycles","permu2mat","permuorder","perpen_bisector","perpendicular","peval","piecewise","pivot","pixoff","pixon","plane","plot","plot3d","plot_style","plotarea","plotcontour","plotdensity","plotfield","plotfunc","plotimplicit","plotinequation","plotlist","plotode","plotparam","plotpolar","plotseq","pmin","pnt","point","point2d","point3d","pointer","poisson","poisson_cdf","poisson_icdf","polar","polar2rectangular","polar_coordinates","polar_point","polarplot","pole","poly2symb","polyEval","polygone_rempli","polygonplot","polygonscatterplot","polyhedron","polynomial_regression","polynomial_regression_plot","position","potential","pour","pow2exp","power_regression","power_regression_plot","powermod","powerpc","powexpand","powmod","prepend","preval","prevperm","prevprime","primpart","print","printpow","prism","product","prog_eval_level","projection","proot","propFrac","propfrac","psrgcd","ptayl","purge","pwd","pyramid","q2a","qr","quadric","quadrilateral","quantile","quartile1","quartile3","quartiles","quaternion","quest","quo","quorem","quote","r2e","radical_axis","radius","ramene","rand","randMat","randNorm","randPoly","randexp","randint","randmatrix","randperm","randpoly","randvector","range","rank","ranm","ranv","rassembler_trigo","rat_jordan","rat_jordan_block","rationalroot","ratnormal","rdiv","re","read","readrgb","readwav","real","realroot","reciprocation","rectangle","rectangle_plein","rectangular2polar","rectangular_coordinates","recule","red","reduced_conic","reduced_quadric","ref","reflection","rem","remain","remove","remove_language","reorder","repete","reset_solve_counter","residue","resoudre","resoudre_dans_C","resoudre_systeme_lineaire","restart","restart_modes","restart_vars","resultant","reverse_rsolve","revert","revlist","rhombus","rhs","right","right_triangle","rm_a_z","rm_all_vars","rmbreakpoint","rmmod","rmwatch","romberg","rond","rootof","roots","rotate","rotation","round","row","rowAdd","rowDim","rowNorm","rowSwap","rowdim","rownorm","rowspace","rref","rsolve","saute","sauve","save_history","scalarProduct","scalar_product","scatterplot","sec","segment","select","semi_augment","seq","seqplot","seqsolve","series","shift","shift_phase","show_language","si","sialorssinon","sign","signature","signe","similarity","simp2","simplex_reduce","simplifier","simplify","simult","sin","sin2costan","sincos","single_inter","singular","sinh","sinon","size","sizes","slope","slopeat","slopeatraw","smod","snedecor","snedecor_cdf","snedecor_icdf","solve","solve_zero_extremum","somme","sommet","sort","sphere","spline","split","spread2mathml","spreadsheet","sq","sqrfree","sqrt","square","srand","sst","sst_in","stdDev","stddev","stddevp","sto","string","student","student_cdf","student_icdf","studentt","sturm","sturmab","sturmseq","subMat","submatrix","subst","substituer","sum","sum_riemann","suppress","surd","svd","switch_axes","sylvester","symb2poly","syst2mat","tCollect","tExpand","table","tablefunc","tableseq","tabvar","tail","tan","tan2cossin2","tan2sincos","tan2sincos2","tangent","tangente","tanh","tantque","taylor","tchebyshev1","tchebyshev2","tcoeff","tcollect","testfunc","tests","tetrahedron","texpand","textinput","threads_allowed","throw","time","tlin","to","tourne_droite","tourne_gauche","trace","tran","translation","transpose","triangle","triangle_plein","trig2exp","trigcos","trigexpand","trigsin","trigtan","trn","trunc","truncate","tsimplify","type","ufactor","unapply","unarchive","unarchive_ti","uniformd","unitV","unquote","usimplify","valuation","vandermonde","variance","vector","vers","version","vertices","vertices_abc","vertices_abca","vpotential","watch","whattype","when","white","widget_size","with_sqrt","write","writergb","writewav","xcas_mode","xyztrange","yellow","zeros","zip","ztrans","ΔLIST","ΠLIST","Σ","ΣLIST","∂","∫"]);
    var keywords = wordRegexp(myKeywords);
    var builtins = wordRegexp(myBuiltins);

    // tokenizers
    function tokenBase(stream, state) {
      if (stream.sol()) state.indent = stream.indentation()
      // Handle scope changes
      if (stream.sol() && top(state).type == "py") {
        var scopeOffset = top(state).offset;
        if (stream.eatSpace()) {
          var lineOffset = stream.indentation();
          if (lineOffset > scopeOffset)
            pushPyScope(state);
          else if (lineOffset < scopeOffset && dedent(stream, state) && stream.peek() != "#")
            state.errorToken = true;
          return null;
        } else {
          var style = tokenBaseInner(stream, state);
          if (scopeOffset > 0 && dedent(stream, state))
            style += " " + ERRORCLASS;
          return style;
        }
      }
      return tokenBaseInner(stream, state);
    }

    function tokenBaseInner(stream, state) {
      if (stream.eatSpace()) return null;

      var ch = stream.peek();

      // Handle Comments
      if (ch == "#") {
        stream.skipToEnd();
        return "comment";
      }

      // Handle Number Literals
      if (stream.match(/^[0-9\.]/, false)) {
        var floatLiteral = false;
        // Floats
        if (stream.match(/^[\d_]*\.\d+(e[\+\-]?\d+)?/i)) { floatLiteral = true; }
        if (stream.match(/^[\d_]+\.\d*/)) { floatLiteral = true; }
        if (stream.match(/^\.\d+/)) { floatLiteral = true; }
        if (floatLiteral) {
          // Float literals may be "imaginary"
          stream.eat(/J/i);
          return "number";
        }
        // Integers
        var intLiteral = false;
        // Hex
        if (stream.match(/^0x[0-9a-f_]+/i)) intLiteral = true;
        // Binary
        if (stream.match(/^0b[01_]+/i)) intLiteral = true;
        // Octal
        if (stream.match(/^0o[0-7_]+/i)) intLiteral = true;
        // Decimal
        if (stream.match(/^[1-9][\d_]*(e[\+\-]?[\d_]+)?/)) {
          // Decimal literals may be "imaginary"
          stream.eat(/J/i);
          // TODO - Can you have imaginary longs?
          intLiteral = true;
        }
        // Zero by itself with no other piece of number.
        if (stream.match(/^0(?![\dx])/i)) intLiteral = true;
        if (intLiteral) {
          // Integer literals may be "long"
          stream.eat(/L/i);
          return "number";
        }
      }

      // Handle Strings
      if (stream.match(stringPrefixes)) {
        state.tokenize = tokenStringFactory(stream.current());
        return state.tokenize(stream, state);
      }

      for (var i = 0; i < operators.length; i++)
        if (stream.match(operators[i])) return "operator"

      if (stream.match(delimiters)) return "punctuation";

      if (state.lastToken == "." && stream.match(identifiers))
        return "property";

      if (stream.match(keywords) || stream.match(wordOperators))
        return "keyword";

      if (stream.match(builtins))
        return "builtin";

      if (stream.match(/^(self|cls)\b/))
        return "variable-2";

      if (stream.match(identifiers)) {
        if (state.lastToken == "def" || state.lastToken == "class")
          return "def";
        return "variable";
      }

      // Handle non-detected items
      stream.next();
      return ERRORCLASS;
    }

    function tokenStringFactory(delimiter) {
      while ("rubf".indexOf(delimiter.charAt(0).toLowerCase()) >= 0)
        delimiter = delimiter.substr(1);

      var singleline = delimiter.length == 1;
      var OUTCLASS = "string";

      function tokenString(stream, state) {
        while (!stream.eol()) {
          stream.eatWhile(/[^'"\\]/);
          if (stream.eat("\\")) {
            stream.next();
            if (singleline && stream.eol())
              return OUTCLASS;
          } else if (stream.match(delimiter)) {
            state.tokenize = tokenBase;
            return OUTCLASS;
          } else {
            stream.eat(/['"]/);
          }
        }
        if (singleline) {
          if (parserConf.singleLineStringErrors)
            return ERRORCLASS;
          else
            state.tokenize = tokenBase;
        }
        return OUTCLASS;
      }
      tokenString.isString = true;
      return tokenString;
    }

    function pushPyScope(state) {
      while (top(state).type != "py") state.scopes.pop()
      state.scopes.push({offset: top(state).offset + conf.indentUnit,
                         type: "py",
                         align: null})
    }

    function pushBracketScope(stream, state, type) {
      var align = stream.match(/^([\s\[\{\(]|#.*)*$/, false) ? null : stream.column() + 1
      state.scopes.push({offset: state.indent + hangingIndent,
                         type: type,
                         align: align})
    }

    function dedent(stream, state) {
      var indented = stream.indentation();
      while (state.scopes.length > 1 && top(state).offset > indented) {
        if (top(state).type != "py") return true;
        state.scopes.pop();
      }
      return top(state).offset != indented;
    }

    function tokenLexer(stream, state) {
      if (stream.sol()) state.beginningOfLine = true;

      var style = state.tokenize(stream, state);
      var current = stream.current();

      // Handle decorators
      if (state.beginningOfLine && current == "@")
        return stream.match(identifiers, false) ? "meta" : py3 ? "operator" : ERRORCLASS;

      if (/\S/.test(current)) state.beginningOfLine = false;

      if ((style == "variable" || style == "builtin")
          && state.lastToken == "meta")
        style = "meta";

      // Handle scope changes.
      if (current == "pass" || current == "return")
        state.dedent += 1;

      if (current == "lambda") state.lambda = true;
      if (current == ":" && !state.lambda && top(state).type == "py")
        pushPyScope(state);

      var delimiter_index = current.length == 1 ? "[({".indexOf(current) : -1;
      if (delimiter_index != -1)
        pushBracketScope(stream, state, "])}".slice(delimiter_index, delimiter_index+1));

      delimiter_index = "])}".indexOf(current);
      if (delimiter_index != -1) {
        if (top(state).type == current) state.indent = state.scopes.pop().offset - hangingIndent
        else return ERRORCLASS;
      }
      if (state.dedent > 0 && stream.eol() && top(state).type == "py") {
        if (state.scopes.length > 1) state.scopes.pop();
        state.dedent -= 1;
      }

      return style;
    }

    var external = {
      startState: function(basecolumn) {
        return {
          tokenize: tokenBase,
          scopes: [{offset: basecolumn || 0, type: "py", align: null}],
          indent: basecolumn || 0,
          lastToken: null,
          lambda: false,
          dedent: 0
        };
      },

      token: function(stream, state) {
        var addErr = state.errorToken;
        if (addErr) state.errorToken = false;
        var style = tokenLexer(stream, state);

        if (style && style != "comment")
          state.lastToken = (style == "keyword" || style == "punctuation") ? stream.current() : style;
        if (style == "punctuation") style = null;

        if (stream.eol() && state.lambda)
          state.lambda = false;
        return addErr ? style + " " + ERRORCLASS : style;
      },

      indent: function(state, textAfter) {
        if (state.tokenize != tokenBase)
          return state.tokenize.isString ? CodeMirror.Pass : 0;

        var scope = top(state), closing = scope.type == textAfter.charAt(0)
        if (scope.align != null)
          return scope.align - (closing ? 1 : 0)
        else
          return scope.offset - (closing ? hangingIndent : 0)
      },

      electricInput: /^\s*[\}\]\)]$/,
      closeBrackets: {triples: "'\""},
      lineComment: "#",
      fold: "indent"
    };
    return external;
  });

  CodeMirror.defineMIME("text/x-python", "python");

  var words = function(str) { return str.split(" "); };

  CodeMirror.defineMIME("text/x-cython", {
    name: "python",
    extra_keywords: words("by cdef cimport cpdef ctypedef enum except "+
                          "extern gil include nogil property public "+
                          "readonly struct union DEF IF ELIF ELSE")
  });

});
