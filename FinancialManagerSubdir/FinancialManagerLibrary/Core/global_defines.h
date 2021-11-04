#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#if defined MAKE_LIB_EXPORT
    #define LIB_EXPORT Q_DECL_EXPORT
#else
    #define LIB_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_DEFINES_H
