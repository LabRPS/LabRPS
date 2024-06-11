#ifndef FUNCTION2DDIALOG_H
#define FUNCTION2DDIALOG_H

#include <QDialog>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class Ui_Function2DDialog;
class AxisRect2D;

class AlphaplotExport Function2DDialog : public QDialog {
  Q_OBJECT

 public:
  explicit Function2DDialog(QWidget* parent = nullptr);
  ~Function2DDialog();

  void setLayout2DToModify(AxisRect2D* axisrect, int plottomidify);

  void insertParamFunctionsList(const QStringList& xList,
                                const QStringList& yList);
  void insertPolarFunctionsList(const QStringList& rList,
                                const QStringList& thetaList);
  int getType() { return this->type; }
  QStringList getFormulas() { return formulas; }
  QList<double> getRange() { return ranges; }
  int getPoints() { return points; }
  AxisRect2D* getAxisrect() { return axisrect_; }
  int getPlottomodify() { return plottomodify_; }
  QString getTheText() { return theText; }

 private Q_SLOTS:
  void raiseWidget(const int index) const;
  // void setFunctionPlotToModify(LineScatter2D *ls);
  // void setParametricFunctionPlotToModify();
  bool apply();
  void accept();
  bool acceptFunction();
  bool acceptParametric();
  // bool acceptPolar();
  void clearList();

 Q_SIGNALS:
  void updateFunctionLists(int, QStringList);
  void clearParamFunctionsList();
  void clearPolarFunctionsList();

 private:
  Ui_Function2DDialog* ui_;
  AxisRect2D* axisrect_;
  int plottomodify_;
  
  int type;
  QStringList formulas;
  QList<double> ranges;
  int points;
  QString theText;
};

#endif  // FUNCTION2DDIALOG_H
