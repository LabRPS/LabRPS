#ifndef RPSTOOLS_DEFINES_H
#define RPSTOOLS_DEFINES_H

#ifdef _WIN32
#  define RPS_TOOLS_EXPORT __declspec(dllexport)
#  define RPS_TOOLS_IMPORT __declspec(dllimport)
#else
#  define RPS_TOOLS_EXPORT
#  define RPS_TOOLS_IMPORT
#endif
#endif //RPSTOOLS_DEFINES_H


