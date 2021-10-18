#ifndef __OPTIMIZATION_H
#define __OPTIMIZATION_H
#include "config.h"
#include "gen.h"
#include "unary.h"

#ifndef NO_NAMESPACE_GIAC
namespace giac {
#endif // ndef NO_NAMESPACE_GIAC

#define GOLDEN_RATIO 1.61803398875

enum {
    _CPCLASS_MIN,
    _CPCLASS_MAX,
    _CPCLASS_POSSIBLE_MIN,
    _CPCLASS_POSSIBLE_MAX,
    _CPCLASS_SADDLE,
    _CPCLASS_UNDECIDED
};

gen _minimize(const gen & g,GIAC_CONTEXT);
gen _maximize(const gen & g,GIAC_CONTEXT);
gen _extrema(const gen & g,GIAC_CONTEXT);
gen _minimax(const gen & g,GIAC_CONTEXT);
gen _tpsolve(const gen & g,GIAC_CONTEXT);

#ifndef NO_NAMESPACE_GIAC
} // namespace giac
#endif // ndef NO_NAMESPACE_GIAC
#endif // __OPTIMIZATION_H
