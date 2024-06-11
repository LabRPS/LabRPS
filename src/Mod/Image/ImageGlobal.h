/***************************************************************************
 *   Copyright (c) Imetric 4D Imaging Sarl                                 *
 *                                                                         *
 *   Author: Werner Mayer                                                  *
 *                                                                         *
 ***************************************************************************/

#include <RPSGlobal.h>

#ifndef IMAGE_GLOBAL_H
#define IMAGE_GLOBAL_H


// Image
#ifndef ImageExport
#ifdef Image_EXPORTS
#  define ImageExport   LABRPS_DECL_EXPORT
#else
#  define ImageExport   LABRPS_DECL_IMPORT
#endif
#endif

// ImageGui
#ifndef ImageGuiExport
#ifdef ImageGui_EXPORTS
#  define ImageGuiExport   LABRPS_DECL_EXPORT
#else
#  define ImageGuiExport   LABRPS_DECL_IMPORT
#endif
#endif

#endif //IMAGE_GLOBAL_H
