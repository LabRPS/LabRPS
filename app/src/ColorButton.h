#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>
class QPushButton;
class QHBoxLayout;
class QFrame;

//! A button used for color selection
/**
 * This button contains two widgets:
 * 1) A frame reflecting the current color
 * 2) A button showing a color wheel to select the color
 */
class ColorButton : public QWidget {
  Q_OBJECT

 public:
  //! Constructor
  ColorButton(QWidget *parent = nullptr);
  //! Set the color of the display part
  void setColor(const QColor &c);
  //! Get the color of the display part
  QColor color() const;
  QSize sizeHint() const;

 private:
  QPushButton *selectButton;
  QFrame *display;

 signals:
  //! Signal clicked: This is emitted when the selection button is clicked
  void clicked();

 protected:
  //! Initialize the widget (called from constructor)
  void init();

 private:
  int btn_size;
};

#endif  // COLORBUTTON_H
