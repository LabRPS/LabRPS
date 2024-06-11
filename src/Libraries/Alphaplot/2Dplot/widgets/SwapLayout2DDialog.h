#ifndef SWAPLAYOUT2DDIALOG_H
#define SWAPLAYOUT2DDIALOG_H

#include <QDialog>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class Layout2D;
class Ui_SwapLayout2DDialog;

class AlphaplotExport SwapLayout2DDialog : public QDialog {
  Q_OBJECT

 public:
  typedef QPair<int,int> Pair;
  explicit SwapLayout2DDialog(Layout2D *parent = nullptr);
  ~SwapLayout2DDialog();

 private Q_SLOTS:
  void swap();

 private:
  Ui_SwapLayout2DDialog *ui_;
  Layout2D *layout_;
};

#endif  // SWAPLAYOUT2DDIALOG_H
