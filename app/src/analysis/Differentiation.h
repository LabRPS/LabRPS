#ifndef DIFFERENTIATION_H
#define DIFFERENTIATION_H

#include "Filter.h"

class AxisRect2D;

class Differentiation : public Filter {
  Q_OBJECT

 public:
  Differentiation(ApplicationWindow *parent, AxisRect2D *axisrect);
  Differentiation(ApplicationWindow *parent, AxisRect2D *axisrect,
                  PlotData::AssociatedData *associateddata);
  Differentiation(ApplicationWindow *parent, AxisRect2D *axisrect,
                  PlotData::AssociatedData *associateddata, double start,
                  double end);

 private:
  void init();
  void output();
};
#endif  // DIFFERENTIATION_H
