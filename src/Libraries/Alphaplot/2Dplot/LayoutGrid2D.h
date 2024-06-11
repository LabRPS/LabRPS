#ifndef LAYOUTGRID2D_H
#define LAYOUTGRID2D_H

#include "../3rdparty/qcustomplot/qcustomplot.h"
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class AlphaplotExport LayoutGrid2D : public QCPLayoutGrid {
  Q_OBJECT
 public:
  LayoutGrid2D();
  ~LayoutGrid2D();
};

#endif  // LAYOUTGRID2D_H
