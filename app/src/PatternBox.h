#ifndef PATTERNBOX_H
#define PATTERNBOX_H

#include <QComboBox>

//! Pattern combo box
class PatternBox : public QComboBox {
  Q_OBJECT
 public:
  PatternBox(bool rw, QWidget* parent = nullptr);
  PatternBox(QWidget* parent = nullptr);
  void setPattern(const Qt::BrushStyle& c);
  Qt::BrushStyle getSelectedPattern() const;

  static const Qt::BrushStyle patterns[];
  static int patternIndex(const Qt::BrushStyle& style);

 protected:
  void init();
};

#endif  // PATTERNBOX_H
