#ifndef PICKERTOOL2D_H
#define PICKERTOOL2D_H

#include "Layout2D.h"

class PickerTool2D : public QObject {
  Q_OBJECT
 public:
  explicit PickerTool2D(Layout2D *parent);
  ~PickerTool2D();

  // setters
  void setPicker(const Graph2DCommon::Picker &picker);
  void setRangePickerCurve(Curve2D *curve);

  // getters
  Graph2DCommon::Picker getPicker() const;
  Curve2D *getRangePickerCurve();
  QPair<double, double> getRangePickerLower() const;
  QPair<double, double> getRangePickerUpper() const;

  void showtooltip(const QPointF position, const double xval, const double yval,
                   Axis2D *xaxis, Axis2D *yaxis);
  // move picker
  void movepickermouspresscurve(Curve2D *curve, const double xval,
                                const double yval, Axis2D *xaxis,
                                Axis2D *yaxis);
  void movepickermouspressls(LineSpecial2D *ls, const double xval,
                                const double yval, Axis2D *xaxis,
                                Axis2D *yaxis);
  void movepickermouspressbar(Bar2D *bar, const double xval,
                                const double yval, Axis2D *xaxis,
                                Axis2D *yaxis);
  void movepickermousedrag(const QPointF &position, const double xval,
                           const double yval);
  void movepickermouserelease(const QPointF position);
  // drag range
  void rangepickermousepress(Curve2D *curve, const double xval,
                           const double yval);
  void rangepickermousedrag(const QPointF &position, const double xval,
                         const double yval);
  void rangepickermouserelease(const QPointF position);
  void datapoint(Curve2D *curve, const double xval, const double yval);

 private:
  struct DatarangePicker {
    Curve2D *curve;
    QCPItemStraightLine *line;
    double lowerx;
    double lowery;
    double upperx;
    double uppery;
    bool active;
    DatarangePicker()
        : curve(nullptr),
          line(nullptr),
          lowerx(0.0),
          lowery(0.0),
          upperx(0.0),
          uppery(0.0),
          active(false) {}
  };
  struct DataMovePicker {
    double xval;
    double yval;
    DataMovePicker() : xval(0.0), yval(0.0) {}
  };
  // move picker
  void movepickermouspress(const double xval, const double yval, Axis2D *xaxis,
                           Axis2D *yaxis);
  // rangepicker
  void setupRangepicker();
  void setupMovePicker();
  void removePickerLinesAndEllipses();
  void resetDataRangePicker();
  void moveLineEllipseItenTo(double xval, double yval, bool active);

  Layout2D *layout_;
  Curve2D *curve_;
  LineSpecial2D *ls_;
  Bar2D *bar_;
  Graph2DCommon::Picker picker_;
  QCPItemStraightLine *xpickerline_;
  QCPItemStraightLine *ypickerline_;
  QCPItemEllipse *xpickerellipse_;
  QCPItemEllipse *ypickerellipse_;
  DatarangePicker rangepicker_;
  DataMovePicker movepicker_;
  static const int ellipseradius_;
};

#endif  // PICKERTOOL2D_H
