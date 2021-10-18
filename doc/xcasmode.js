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

  CodeMirror.defineSimpleMode = function(name, states) {
    CodeMirror.defineMode(name, function(config) {
      return CodeMirror.simpleMode(config, states);
    });
  };

/* Example definition of a simple mode that understands a subset of
 * JavaScript:
 */

CodeMirror.defineSimpleMode("simplemode", {
  // The start state contains the rules that are intially used
  start: [
    // The regex matches the token, the token property contains the type
    {regex: /"(?:[^\\]|\\.)*?"/, token: "string"},
    // You can match multiple tokens at once. Note that the captured
    // groups must span the whole string in this case
    {regex: /(function)(\s+)([a-z$][\w$]*)/,
     token: ["keyword", null, "variable-2"]},
    // Rules are matched in the order in which they appear, so there is
    // no ambiguity between this one and the one above
    {regex: /(?:function|var|local|return|if|for|while|else|do|in|from|si|alors|sinon|fsi|tantque|ftantque|pour|fpour)\b/,
     token: "keyword"},
    {regex: /(?:ABS|ACOS|ACOSH|ACOT|ACSC|ADDCOL|ADDROW|ALOG|ARC|ARG|ASEC|ASIN|ASINH|ATAN|ATANH|Airy_Ai|Airy_Bi|Ans|Archive|BINOMIAL|BesselI|BesselJ|BesselK|BesselY|Beta|Bezier|BlockDiagonal|CEILING|CHOOSE|COLNORM|COMB|CONCAT|COND|CONJ|COS|COSH|COT|CROSS|CSC|Celsius2Fahrenheit|Ci|Ci0|Circle|ClrDraw|ClrGraph|ClrIO|CopyVar|CyclePic|DEGXRAD|DELCOL|DELROW|DET|DISP|DOT|DROP|DUP|DelFold|DelVar|Det|Dirac|DispG|DispHome|DrawFunc|DrawInv|DrawParm|DrawPol|DrawSlp|DrwCtour|EDITMAT|EIGENVAL|EIGENVV|EXP|EXPM1|EXPORT|Ei|Ei0|Ei_f|Eta|Exec|FLOOR|FNROOT|Factor|Fahrenheit2Celsius|Fill|GETKEY|ifndef NO_RTTI{GF|endif{Gamma|Gcd|Gcdex|Get|GetCalc|GetFold|Graph|HMSX|Heaviside|IDENMAT|IFTE|IM|INPUT|INVERSE|ISOLATE|ITERATE|Input|InputStr|Int|Inverse|JordanBlock|LINE|LN|LNP1|LOG|LQ|LSQ|LU|Line|LineHorz|LineTan|LineVert|MAKELIST|MAKEMAT|MANT|MAX|MAXREAL|MIN|MINREAL|MOD|MSGBOX|NOP|NORMALD|NTHROOT|NewFold|NewPic|Nullspace|OVER|Output|Ox_2d_unit_vector|Ox_3d_unit_vector|Oy_2d_unit_vector|Oy_3d_unit_vector|Oz_3d_unit_vector|PERM|PICK|PIECEWISE|PIXOFF|PIXON|POISSON|POLYCOEF|POLYEVAL|POLYFORM|POLYROOT|POS|PRINT|Pause|Phi|Pictsize|PopUp|Prompt|Psi|Psi_minus_ln|PtOff|PtOn|PtText|PxlOff|PxlOn|QR|QUAD|QUOTE|Quo|RADXDEG|RANDMAT|RANDOM|RANDSEED|RANK|RCL|RE|RECT|RECURSE|REDIM|REPLACE|REVERSE|ROUND|ROWNORM|RREF|RandSeed|Rank|RclPic|Rem|Resultant|RplcPic|Rref|SCALE|SCALEADD|SCHUR|SEC|SIGN|SIN|SINH|SIZE|SORT|SPECNORM|SPECRAD|SUB|SVD|SVL|SWAP|SWAPCOL|SWAPROW|SetFold|Si|SiCi_f|SiCi_g|SortA|SortD|StoPic|Store|Sum|TAN|TANH|TAYLOR|TRACE|TRN|TRUNCATE|TeX|UTPC|UTPF|UTPN|UTPT|Unarchiv|VIEWS|WAIT|XHMS|XPON|Zeta|ZoomRcl|ZoomSto|a2q|abcuv|about|abs|abscissa|accumulate_head_tail|acos|acos2asin|acos2atan|acosh|acot|acsc|add|add_language|additionally|adjoint_matrix|affix|algvar|alog10|alors|altitude|and|angle|angleat|angleatraw|animate|animate3d|animation|ans|append|apply|approx|arc|arcLen|area|areaat|areaatraw|areaplot|arg|array|array_sto|as_function_of|asc|asec|asin|asin2acos|asin2atan|asinh|assign|assume|atan|atan2acos|atan2asin|atanh|atrig2ln|augment|avance|avgRC|background|baisse_crayon|bar_plot|barycenter|basis|bernoulli|bezout_entiers|binomial|binomial_cdf|binomial_icdf|binprint|bisector|bitand|bitmap|bitor|bitxor|black|blockmatrix|blue|border|bounded_function|boxwhisker|break|breakpoint|c1oc2|c1op2|cFactor|cSolve|cZeros|cache_tortue|calc_mode|camembert|canonical_form|cap|cas_setup|cat|cd|ceil|ceiling|cell|center|center2interval|centered_cube|centered_tetrahedron|cfactor|changebase|char|charpoly|chinrem|chisquare|chisquare_cdf|chisquare_icdf|cholesky|choosebox|chrem|circle|circumcircle|classes|click|close|coeff|coeffs|col|colDim|colNorm|coldim|collect|colnorm|color|colspace|comDenom|comb|combine|comment|common_perpendicular|companion|compare|complexroot|concat|cone|conic|conj|cont|contains|content|contourplot|convert|convertir|convexhull|coordinates|copy|correlation|cos|cos2sintan|cosh|cot|cote|count|count_eq|count_inf|count_sup|courbe_parametrique|courbe_polaire|covariance|covariance_correlation|cpartfrac|crationalroot|crayon|cross|crossP|cross_ratio|crossproduct|csc|csolve|csv2gen|cube|cumSum|cumulated_frequencies|curl|current_sheet|curve|cyan|cycle2perm|cycleinv|cycles2permu|cyclotomic|cylinder|de|deSolve|debug|debug_infolevel|debut_enregistrement|decrement|degree|delcols|delrows|deltalist|denom|densityplot|deriver|desolve|dessine_tortue|det|det_minor|developper|developper_transcendant|dfc|dfc2f|diag|diff|dim|display|disque|disque_centre|distance|distance2|distanceat|distanceatraw|div|divcrement|divergence|divide|divis|division_point|divisors|divpc|dodecahedron|dot|dotP|dotprod|droit|droite_tangente|dsolve|e2r|ecart_type|ecart_type_population|ecris|efface|egcd|egv|egvl|eigVc|eigVl|eigenvals|eigenvalues|eigenvectors|eigenvects|element|ellipse|entry|envelope|epsilon2zero|equal2diff|equal2list|equation|equilateral_triangle|erase3d|erf|erfc|erfs|et|euler|euler_mac_laurin|eval|eval_level|evala|evalb|evalc|evalf|evalm|even|exact|exbisector|excircle|execute|exp|exp2list|exp2pow|exp2trig|expexpand|exponential_regression|exponential_regression_plot|expr|extract_measure|ezgcd|f2nd|fMax|fMin|fPart|faces|facteurs_premiers|factor|factor_xn|factorial|factoriser|factoriser_entier|factoriser_sur_C|factoriser_xn|factors|faire|fclose|fcoeff|fft|fieldplot|filled|fin_enregistrement|findhelp|fisher|fisher_cdf|fisher_icdf|float|float2rational|floor|fonction|fonction_derivee|fopen|format|fourier_an|fourier_bn|fourier_cn|fprint|frac|fracmod|frame_2d|frame_3d|froot|fsolve|funcplot|function_diff|fxnd|gauche|gauss|gaussjord|gbasis|gcd|gcdex|genpoly|geo2d|geo3d|getDenom|getKey|getNum|getType|giac|goto|grad|gramschmidt|graph2tex|graph3d2tex|graphe|graphe3d|graphe_suite|greduce|green|groupermu|hadamard|half_cone|half_line|halftan|halftan_hyp2exp|halt|hamdist|harmonic_conjugate|harmonic_division|has|hasard|head|heap_mult|hermite|hessenberg|hessian|heugcd|hexagon|hexprint|hidden_name|hilbert|histogram|hold|homothety|horner|hp38|hyp2exp|hyperbola|hyperplan|hypersphere|hypersurface|iPart|iabcuv|ibasis|ibpdv|ibpu|ichinrem|ichrem|icontent|icosahedron|id|identity|idivis|idn|iegcd|ifactor|ifactors|ifft|igcd|igcdex|ihermite|ilaplace|im|imag|image|implicitplot|implicitplot3d|inString|in_ideal|incircle|increment|indets|inequationplot|input|inputform|insmod|int|intDiv|integer_format|integrate|integrer|inter|interactive|interactive_odeplot|interactive_plotode|interp|interval2center|inv|inverse|inversion|invlaplace|invztrans|iquo|iquorem|iratrecon|irem|isPrime|is_collinear|is_concyclic|is_conjugate|is_coplanar|is_cycle|is_element|is_equilateral|is_harmonic|is_harmonic_circle_bundle|is_harmonic_line_bundle|is_orthogonal|is_parallel|is_parallelogram|is_permu|is_perpendicular|is_prime|is_pseudoprime|is_rectangle|is_rhombus|is_square|ismith|isobarycenter|isom|isopolygon|isprime|ithprime|jacobi_symbol|jordan|jusque|ker|kernel|keyboard|kill|l1norm|l2norm|label|lagrange|laguerre|laplace|laplacian|latex|lcm|lcoeff|ldegree|left|legend|legendre|legendre_symbol|length|leve_crayon|lgcd|lhs|ligne_polygonale|ligne_polygonale_pointee|limit|limite|lin|line|line_inter|line_segments|linear_interpolate|linear_regression|linear_regression_plot|lineariser|lineariser_trigo|linsolve|lis|lis_phrase|list2mat|listplot|lll|ln|lnGamma_minus|lname|lncollect|lnexpand|locus|log10|logarithmic_regression|logarithmic_regression_plot|logb|logistic_regression|logistic_regression_plot|lsmod|lu|lvar|mRow|mRowAdd|magenta|makelist|makemat|makemod|makesuite|makevector|map|maple2mupad|maple2xcas|maple_ifactors|maple_mode|mat2list|mathml|matpow|matrix|max|maxnorm|mean|median|median_line|member|mid|midpoint|min|mkisom|mksa|modgcd|modgcd_cachesize|modp|mods|montre_tortue|moustache|moyal|moyenne|mpzclass_allowed|mul|mult_c_conjugate|mult_conjugate|multcrement|multiplier_conjugue|multiplier_conjugue_complexe|multiply|mupad2maple|mupad2xcas|nCr|nDeriv|nInt|nPr|nSolve|ncols|newList|newMat|newton|nextperm|nextprime|nodisp|non|non_recursive_normal|nop|nops|norm|normal|normal_cdf|normal_icdf|normald|normald_cdf|normald_icdf|normalize|nrows|nuage_points|nullspace|numer|octahedron|octprint|odd|odeplot|odesolve|op|open|open_polygon|or|ord|order_size|ordinate|orthocenter|orthogonal|os_version|ou|output|p1oc2|p1op2|pa2b2|pade|padic_linsolve|parabola|parabolic_interpolate|parallel|parallelepiped|parallelogram|parameq|parameter|paramplot|pari|pari_unlock|part|partfrac|pas|pas_de_cote|pcar|pcar_hessenberg|pcoeff|perimeter|perimeterat|perimeteratraw|perm|perminv|permu2cycles|permu2mat|permuorder|perpen_bisector|perpendicular|peval|piecewise|pivot|pixoff|pixon|plane|plot|plot3d|plot_style|plotarea|plotcontour|plotdensity|plotfield|plotfunc|plotimplicit|plotinequation|plotlist|plotode|plotparam|plotpolar|plotseq|pmin|pnt|point|point2d|point3d|pointer|poisson|poisson_cdf|poisson_icdf|polar|polar2rectangular|polar_coordinates|polar_point|polarplot|pole|poly2symb|polyEval|polygone_rempli|polygonplot|polygonscatterplot|polyhedron|polynomial_regression|polynomial_regression_plot|position|potential|pour|pow2exp|power_regression|power_regression_plot|powermod|powerpc|powexpand|powmod|prepend|preval|prevperm|prevprime|primpart|print|printpow|prism|product|prog_eval_level|projection|proot|propFrac|propfrac|psrgcd|ptayl|purge|pwd|pyramid|q2a|qr|quadric|quadrilateral|quantile|quartile1|quartile3|quartiles|quaternion|quest|quo|quorem|quote|r2e|radical_axis|radius|ramene|rand|randMat|randNorm|randPoly|randexp|randmatrix|randperm|randpoly|randvector|rank|ranm|rassembler_trigo|rat_jordan|rat_jordan_block|rationalroot|ratnormal|rdiv|re|read|readrgb|readwav|real|realroot|reciprocation|rectangle|rectangle_plein|rectangular2polar|rectangular_coordinates|recule|red|reduced_conic|reduced_quadric|ref|reflection|rem|remain|remove|remove_language|reorder|repete|reset_solve_counter|residue|resoudre|resoudre_dans_C|resoudre_systeme_lineaire|restart|restart_modes|restart_vars|resultant|reverse_rsolve|revert|revlist|rhombus|rhs|right|right_triangle|rm_a_z|rm_all_vars|rmbreakpoint|rmmod|rmwatch|romberg|rond|rootof|roots|rotate|rotation|round|row|rowAdd|rowDim|rowNorm|rowSwap|rowdim|rownorm|rowspace|rref|rsolve|saute|sauve|save_history|scalarProduct|scalar_product|scatterplot|sec|segment|select|semi_augment|seq|seqplot|seqsolve|series|shift|shift_phase|show_language|si|sialorssinon|sign|signature|signe|similarity|simp2|simplex_reduce|simplifier|simplify|simult|sin|sin2costan|sincos|single_inter|singular|sinh|sinon|size|sizes|slope|slopeat|slopeatraw|smod|snedecor|snedecor_cdf|snedecor_icdf|solve|solve_zero_extremum|somme|sommet|sort|sphere|spline|split|spread2mathml|spreadsheet|sq|sqrfree|sqrt|square|srand|sst|sst_in|stdDev|stddev|stddevp|sto|string|student|student_cdf|student_icdf|sturm|sturmab|sturmseq|subMat|submatrix|subst|substituer|sum|sum_riemann|suppress|surd|svd|switch_axes|sylvester|symb2poly|syst2mat|tCollect|tExpand|table|tablefunc|tableseq|tail|tan|tan2cossin2|tan2sincos|tan2sincos2|tangent|tangente|tanh|tantque|taylor|tchebyshev1|tchebyshev2|tcoeff|tcollect|testfunc|tests|tetrahedron|texpand|textinput|threads_allowed|throw|time|tlin|tourne_droite|tourne_gauche|trace|tran|translation|transpose|triangle|triangle_plein|trig2exp|trigcos|trigexpand|trigsin|trigtan|trn|trunc|truncate|tsimplify|type|ufactor|unapply|unarchive|unarchive_ti|unitV|unquote|usimplify|valuation|vandermonde|variance|vector|vers|version|vertices|vertices_abc|vertices_abca|vpotential|watch|whattype|when|white|widget_size|with_sqrt|write|writergb|writewav|xcas_mode|xyztrange|yellow|zeros|zip|ztrans|ΔLIST|ΠLIST|Σ|ΣLIST|∂|∫)\b/,
     token: "comment"},
    {regex: /integration|est_pair|est_impair|barycentre|isobarycentre|milieu|aretes|mediane|demi_droite|parallele|perpendiculaire|perpendiculaire_commune|enveloppe|triangle_equilateral|triangle_isocele|triangle_rectangle|lieu|cercle|conique|conique_reduite|quadrique|quadrique_reduite|hyperbole|cylindre|demi_cone|droite|plan|parabole|losange|carre|hexagone|pyramide|quadrilatere|parallelogramme|orthocentre|exbissectrice|parallelepipede|polyedre|tetraedre|tetraedre_centre|cube_centre|octaedre|dodecaedre|icosaedre|bissectrice|mediatrice|affixe|hauteur|circonscrit|exinscrit|inscrit|est_premier|est_equilateral|est_rectangle|est_parallele|est_perpendiculaire|est_orthogonal|est_aligne|est_cocyclique|est_element|est_inclus|est_coplanaire|est_isocele|est_carre|est_losange|est_parallelogramme|est_conjugue|est_faisceau_droite|est_faisceau_cercle|est_dans|aire|perimetre|longueur|longueur2|aireen|penteen|angleen|perimetreen|distanceen|aireenbrut|penteenbrut|angleenbrut|perimetreenbrut|distanceenbrut|extraire_mesure|coordonnees|abscisse|ordonnee|centre|rayon|puissance|sommets|polygone|isopolygone|polygone_ouvert|homothetie|similitude|symetrie|polaire_reciproque|produit_scalaire|birapport|axe_radical|polaire|point_polaire|coordonnees_polaires|coordonnees_rectangulaires|conj_harmonique|div_harmonique|point_div|affichage|sommets_abc|sommets_abca|inter_droite|inter_unique|couleur|legende|est_harmonique|diagramme_batons|diagrammebatons|histogramme|prisme|est_cospherique|papier_pointe|papier_quadrille|papier_ligne|papier_triangule|vecteur|tracer_aire|graphe_probabiliste|mult_conjugue_C|mult_conjugue|forme_canonique|vrai|faux|ou|et|non|integrer_par_parties_u|integrer_par_parties_dv|quand|pente|table_fonction|table_suite|resoudre_numerique|saisir|afficher|supposons|domaine|point_arret|montrer|ne_plus_montrer|suppr_point_arret|alea|saisir_chaine|rempli|nom_cache|noir|blanc|rouge|bleu|jaune|vert|vecteur_unitaire_Ox_2d|vecteur_unitaire_Oy_2d|vecteur_unitaire_Ox_3d|vecteur_unitaire_Oy_3d|vecteur_unitaire_Oz_3d|repere_2d|repere_3d|areaplot tracer_aire|resoudre_recurrence|supposons|racines|fonction_bornee|trier|frequences_cumulees|frequences|loi_normale|regrouper|cercle_osculateur|courbure|developpee/, token: "atom"},
    {regex: /true|false|pi|i|undef/, token: "atom"},
    {regex: /0x[a-f\d]+|[-+]?(?:\.\d+|\d+\.?\d*)(?:e[-+]?\d+)?/i,
     token: "number"},
    {regex: /\/\/.*/, token: "comment"},
    {regex: /\/(?:[^\\]|\\.)*?\//, token: "variable-3"},
    // A next property will cause the mode to move to a different state
    {regex: /\/\*/, token: "comment", next: "comment"},
    {regex: /[-+\/*=<>!]+/, token: "operator"},
    // indent and dedent properties guide autoindentation
    {regex: /[\{\[\(]/, indent: true},
    {regex: /[\}\]\)]/, dedent: true},
    {regex: /[a-z$][\w$]*/, token: "variable"},
    // You can embed other modes with the mode property. This rule
    // causes all code between << and >> to be highlighted with the XML
    // mode.
    {regex: /<</, token: "meta", mode: {spec: "xml", end: />>/}}
  ],
  // The multi-line comment state.
  comment: [
    {regex: /.*?\*\//, token: "comment", next: "start"},
    {regex: /.*/, token: "comment"}
  ],
  // The meta property contains global information about the mode. It
  // can contain properties like lineComment, which are supported by
  // all modes, and also directives like dontIndentStates, which are
  // specific to simple modes.
  meta: {
    dontIndentStates: ["comment"],
    lineComment: "//"
  }
});

  CodeMirror.simpleMode = function(config, states) {
    ensureState(states, "start");
    var states_ = {}, meta = states.meta || {}, hasIndentation = false;
    for (var state in states) if (state != meta && states.hasOwnProperty(state)) {
      var list = states_[state] = [], orig = states[state];
      for (var i = 0; i < orig.length; i++) {
        var data = orig[i];
        list.push(new Rule(data, states));
        if (data.indent || data.dedent) hasIndentation = true;
      }
    }
    var mode = {
      startState: function() {
        return {state: "start", pending: null,
                local: null, localState: null,
                indent: hasIndentation ? [] : null};
      },
      copyState: function(state) {
        var s = {state: state.state, pending: state.pending,
                 local: state.local, localState: null,
                 indent: state.indent && state.indent.slice(0)};
        if (state.localState)
          s.localState = CodeMirror.copyState(state.local.mode, state.localState);
        if (state.stack)
          s.stack = state.stack.slice(0);
        for (var pers = state.persistentStates; pers; pers = pers.next)
          s.persistentStates = {mode: pers.mode,
                                spec: pers.spec,
                                state: pers.state == state.localState ? s.localState : CodeMirror.copyState(pers.mode, pers.state),
                                next: s.persistentStates};
        return s;
      },
      token: tokenFunction(states_, config),
      innerMode: function(state) { return state.local && {mode: state.local.mode, state: state.localState}; },
      indent: indentFunction(states_, meta)
    };
    if (meta) for (var prop in meta) if (meta.hasOwnProperty(prop))
      mode[prop] = meta[prop];
    return mode;
  };

  function ensureState(states, name) {
    if (!states.hasOwnProperty(name))
      throw new Error("Undefined state " + name + "in simple mode");
  }

  function toRegex(val, caret) {
    if (!val) return /(?:)/;
    var flags = "";
    if (val instanceof RegExp) {
      if (val.ignoreCase) flags = "i";
      val = val.source;
    } else {
      val = String(val);
    }
    return new RegExp((caret === false ? "" : "^") + "(?:" + val + ")", flags);
  }

  function asToken(val) {
    if (!val) return null;
    if (typeof val == "string") return val.replace(/\./g, " ");
    var result = [];
    for (var i = 0; i < val.length; i++)
      result.push(val[i] && val[i].replace(/\./g, " "));
    return result;
  }

  function Rule(data, states) {
    if (data.next || data.push) ensureState(states, data.next || data.push);
    this.regex = toRegex(data.regex);
    this.token = asToken(data.token);
    this.data = data;
  }

  function tokenFunction(states, config) {
    return function(stream, state) {
      if (state.pending) {
        var pend = state.pending.shift();
        if (state.pending.length == 0) state.pending = null;
        stream.pos += pend.text.length;
        return pend.token;
      }

      if (state.local) {
        if (state.local.end && stream.match(state.local.end)) {
          var tok = state.local.endToken || null;
          state.local = state.localState = null;
          return tok;
        } else {
          var tok = state.local.mode.token(stream, state.localState), m;
          if (state.local.endScan && (m = state.local.endScan.exec(stream.current())))
            stream.pos = stream.start + m.index;
          return tok;
        }
      }

      var curState = states[state.state];
      for (var i = 0; i < curState.length; i++) {
        var rule = curState[i];
        var matches = (!rule.data.sol || stream.sol()) && stream.match(rule.regex);
        if (matches) {
          if (rule.data.next) {
            state.state = rule.data.next;
          } else if (rule.data.push) {
            (state.stack || (state.stack = [])).push(state.state);
            state.state = rule.data.push;
          } else if (rule.data.pop && state.stack && state.stack.length) {
            state.state = state.stack.pop();
          }

          if (rule.data.mode)
            enterLocalMode(config, state, rule.data.mode, rule.token);
          if (rule.data.indent)
            state.indent.push(stream.indentation() + config.indentUnit);
          if (rule.data.dedent)
            state.indent.pop();
          if (matches.length > 2) {
            state.pending = [];
            for (var j = 2; j < matches.length; j++)
              if (matches[j])
                state.pending.push({text: matches[j], token: rule.token[j - 1]});
            stream.backUp(matches[0].length - (matches[1] ? matches[1].length : 0));
            return rule.token[0];
          } else if (rule.token && rule.token.join) {
            return rule.token[0];
          } else {
            return rule.token;
          }
        }
      }
      stream.next();
      return null;
    };
  }

  function cmp(a, b) {
    if (a === b) return true;
    if (!a || typeof a != "object" || !b || typeof b != "object") return false;
    var props = 0;
    for (var prop in a) if (a.hasOwnProperty(prop)) {
      if (!b.hasOwnProperty(prop) || !cmp(a[prop], b[prop])) return false;
      props++;
    }
    for (var prop in b) if (b.hasOwnProperty(prop)) props--;
    return props == 0;
  }

  function enterLocalMode(config, state, spec, token) {
    var pers;
    if (spec.persistent) for (var p = state.persistentStates; p && !pers; p = p.next)
      if (spec.spec ? cmp(spec.spec, p.spec) : spec.mode == p.mode) pers = p;
    var mode = pers ? pers.mode : spec.mode || CodeMirror.getMode(config, spec.spec);
    var lState = pers ? pers.state : CodeMirror.startState(mode);
    if (spec.persistent && !pers)
      state.persistentStates = {mode: mode, spec: spec.spec, state: lState, next: state.persistentStates};

    state.localState = lState;
    state.local = {mode: mode,
                   end: spec.end && toRegex(spec.end),
                   endScan: spec.end && spec.forceEnd !== false && toRegex(spec.end, false),
                   endToken: token && token.join ? token[token.length - 1] : token};
  }

  function indexOf(val, arr) {
    for (var i = 0; i < arr.length; i++) if (arr[i] === val) return true;
  }

  function indentFunction(states, meta) {
    return function(state, textAfter, line) {
      if (state.local && state.local.mode.indent)
        return state.local.mode.indent(state.localState, textAfter, line);
      if (state.indent == null || state.local || meta.dontIndentStates && indexOf(state.state, meta.dontIndentStates) > -1)
        return CodeMirror.Pass;

      var pos = state.indent.length - 1, rules = states[state.state];
      scan: for (;;) {
        for (var i = 0; i < rules.length; i++) {
          var rule = rules[i];
          if (rule.data.dedent && rule.data.dedentIfLineStart !== false) {
            var m = rule.regex.exec(textAfter);
            if (m && m[0]) {
              pos--;
              if (rule.next || rule.push) rules = states[rule.next || rule.push];
              textAfter = textAfter.slice(m[0].length);
              continue scan;
            }
          }
        }
        break;
      }
      return pos < 0 ? 0 : state.indent[pos];
    };
  }
});
