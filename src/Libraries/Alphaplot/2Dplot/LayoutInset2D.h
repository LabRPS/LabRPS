#ifndef LAYOUTINSET2D_H
#define LAYOUTINSET2D_H

#include <Libraries/Alphaplot/3rdparty/qcustomplot/qcustomplot.h>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class AxisRect2D;

class AlphaplotExport LayoutInset2D: QCPLayoutInset
{
  Q_OBJECT
public:
  LayoutInset2D(AxisRect2D *axisrect);
  ~LayoutInset2D();

private:
  AxisRect2D *axisrect_;
  QString layername_;
};

#endif // LAYOUTINSET2D_H
