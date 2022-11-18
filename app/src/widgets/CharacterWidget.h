#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QFont>
#include <QWidget>

class CharacterWidget : public QWidget {
  Q_OBJECT

 public:
  CharacterWidget(QWidget *parent = nullptr);
  QSize sizeHint() const override;
  void resized(int widgetwidth);
  enum class Chars : int {
    All = 0,
    GreekSymbol= 1,
    NumberSymbol = 2,
    SubSuperSymbol = 3,
    MathSymbol = 4,
    ArrowSymbol = 5,
    OtherSymbol = 6
  };

 public slots:
  void updateFont(const QFont &font);
  void updateSize(const int fontSize);
  void updateStyle(const QString &fontStyle);
  void updateFontMerging(bool enable);
  void updateChars(Chars chars);

 signals:
  void characterSelected(const QString &character);

 protected:
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private:
  void calculateSquareSize();
  void loadCharsList();

  QFont displayFont_;
  int columns_ = 16;
  int lastKey_ = -1;
  int squareSize_ = 0;
  QList<int> charsList_;
  bool greeksymbolchar_;
  bool numbersymbolchar_;
  bool subsupersymbolchar_;
  bool mathsymbolchar_;
  bool arrowsymbolchar_;
  bool othersymbolchar_;
};

#endif  // CHARACTERWIDGET_H
