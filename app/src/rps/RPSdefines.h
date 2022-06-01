#pragma once
#ifndef RPS_G_DEFINES_H
#define RPS_G_DEFINES_H

#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(__CYGWIN__)
#ifdef RPS_BUILDING_CORE
#define RPS_CORE_API   __declspec(dllexport)
#define RPS_PLUGIN_API __declspec(dllimport)
#else
#define RPS_CORE_API   __declspec(dllimport)
#define RPS_PLUGIN_API __declspec(dllexport)
#endif
#else
#define RPS_CORE_API
#define RPS_PLUGIN_API
#endif

#endif
