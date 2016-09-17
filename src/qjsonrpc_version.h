
#pragma once

#include <rc_description.h>

#define QJSONRPC_VERSION_MAJOR  2
#define QJSONRPC_VERSION_MINOR  0
#define QJSONRPC_VERSION_POINT  0
#define QJSONRPC_VERSION_POINT2 0


#ifdef __cplusplus
#  define EXTERN_C  extern "C"
#else
#  define EXTERN_C
#endif

#ifndef _CRT_STRINGIZE
#define __CRT_STRINGIZE(_Value) #_Value
#define _CRT_STRINGIZE(_Value) __CRT_STRINGIZE(_Value)
#endif  /* _CRT_STRINGIZE */

#ifndef _CRT_WIDE
#define __CRT_WIDE(_String) L ## _String
#define _CRT_WIDE(_String) __CRT_WIDE(_String)
#endif  /* _CRT_WIDE */

#ifndef _CRT_APPEND
#define __CRT_APPEND(_Value1, _Value2) _Value1 ## _Value2
#define _CRT_APPEND(_Value1, _Value2) __CRT_APPEND(_Value1, _Value2)
#endif  /* _CRT_APPEND */

#ifndef _T
#ifdef _UNICODE
#define __TXT(x)    L ## x
#else  /* _UNICODE */
#define __TXT(x)    x
#endif  /* _UNICODE */
#define _T(x)       __TXT(x)
#endif  /* _T */

#define QJSONRPC_VERSION                    \
    _CRT_APPEND(QJSONRPC_VERSION_MAJOR,     \
    _CRT_APPEND(QJSONRPC_VERSION_MINOR,     \
                QJSONRPC_VERSION_POINT))

#ifdef _WIN32
#  ifdef qjsonrpc_EXPORT
#    define QJSONRPCAPI_EXTERN  extern __declspec(dllexport)
#    define QJSONRPCAPI         __declspec(dllexport)
#  else
#    define QJSONRPCAPI_EXTERN  extern __declspec(dllimport)
#    define QJSONRPCAPI         __declspec(dllimport)
#  endif
#endif
#ifndef QJSONRPCAPI
#  define QJSONRPCAPI_EXTERN    extern
#  define QJSONRPCAPI
#endif


#define FILE_VERSION_MAJOR  QJSONRPC_VERSION_MAJOR
#define FILE_VERSION_MINOR  QJSONRPC_VERSION_MINOR
#define FILE_VERSION_POINT  QJSONRPC_VERSION_POINT
#define FILE_VERSION_POINT2 QJSONRPC_VERSION_POINT2


#define INTERAL_NAME        _T(_CRT_STRINGIZE(PROJECT_NAME))
#define FILE_DESCRIPTION    _T("QJsonRpc is a Qt implementation of the JSON-RPC protocol.")
#define PRODUCT_NAME        FILE_DESCRIPTION
#define LEGAL_COPYRIGHT     _T("Copyright (C) 2016-2016 ") COMPANY_NAME

#define FILE_VERSION        _T(_CRT_STRINGIZE(FILE_VERSION_MAJOR)) _T(".")    \
                            _T(_CRT_STRINGIZE(FILE_VERSION_MINOR)) _T(".")    \
                            _T(_CRT_STRINGIZE(FILE_VERSION_POINT)) _T(".")    \
                            _T(_CRT_STRINGIZE(FILE_VERSION_POINT2))
