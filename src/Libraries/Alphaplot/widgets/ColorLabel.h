#ifndef COLORLABEL_H
#define COLORLABEL_H

#include <QLabel>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>

class AlphaplotExport ColorLabel: public QLabel
{
  Q_OBJECT
 public:
  ColorLabel(QWidget *parent = nullptr);
  ~ColorLabel();
  void setColor(const QColor &color);
  QColor getColor() const;

 private:
  QColor color_;
  static const int lbl_line_width;
  static const int btn_size;
};

#endif  // COLORLABEL_H
