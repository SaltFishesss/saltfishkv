
#ifndef SALTFISH_EXPORT_H
#define SALTFISH_EXPORT_H

#ifdef SALTFISH_STATIC_DEFINE
#  define SALTFISH_EXPORT
#  define SALTFISH_NO_EXPORT
#else
#  ifndef SALTFISH_EXPORT
#    ifdef saltfish_util_EXPORTS
        /* We are building this library */
#      define SALTFISH_EXPORT 
#    else
        /* We are using this library */
#      define SALTFISH_EXPORT 
#    endif
#  endif

#  ifndef SALTFISH_NO_EXPORT
#    define SALTFISH_NO_EXPORT 
#  endif
#endif

#ifndef SALTFISH_DEPRECATED
#  define SALTFISH_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SALTFISH_DEPRECATED_EXPORT
#  define SALTFISH_DEPRECATED_EXPORT SALTFISH_EXPORT SALTFISH_DEPRECATED
#endif

#ifndef SALTFISH_DEPRECATED_NO_EXPORT
#  define SALTFISH_DEPRECATED_NO_EXPORT SALTFISH_NO_EXPORT SALTFISH_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SALTFISH_NO_DEPRECATED
#    define SALTFISH_NO_DEPRECATED
#  endif
#endif

#endif /* SALTFISH_EXPORT_H */
