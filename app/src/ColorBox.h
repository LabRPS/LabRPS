#ifndef COLORBOX_H
#define COLORBOX_H

#include <QComboBox>

//! A combo box to select a standard color
class ColorBox : public QComboBox {
  Q_OBJECT

 public:
  //! Constructor
  /**
   * \param parent parent widget
   */
  ColorBox(QWidget* parent = nullptr);
  //! Set the current color
  void setColor(const QColor& c);
  //! Return the current color
  QColor color() const;

  //! Return the index for a given color
  static int colorIndex(const QColor& c);
  //! Return the color at index 'colorindex'
  static QColor color(int colorIndex);
  //! Returns TRUE if the color is included in the color box, otherwise returns
  //! FALSE.
  static bool isValidColor(const QColor& color);
  //! Returns the number of predefined colors
  static int numPredefinedColors();

 protected:
  //! Internal initialization function
  void init();
  //! The number of predefined colors
  static const int colors_count = 24;
  //! Array containing the 24 predefined colors
  static const QColor colors[];
};

#endif  // COLORBOX_H
