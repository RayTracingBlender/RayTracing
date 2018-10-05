// Auch wenn man Debugt wird die Release lib von Python importiert
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED 1
#undef _DEBUG
#endif

#include <Python.h>
#include <arrayobject.h>

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG 1
#endif
