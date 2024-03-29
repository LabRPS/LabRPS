#include "ColorBox.h"

#include <QPainter>
#include <QPixmap>
#include <algorithm>

const QColor ColorBox::colors[] = {
    QColor(Qt::black),       QColor(Qt::red),        QColor(Qt::green),
    QColor(Qt::blue),        QColor(Qt::cyan),       QColor(Qt::magenta),
    QColor(Qt::yellow),      QColor(Qt::darkYellow), QColor(Qt::darkBlue),
    QColor(Qt::darkMagenta), QColor(Qt::darkRed),    QColor(Qt::darkGreen),
    QColor(Qt::darkCyan),    QColor(0, 0, 160),      QColor(255, 128, 0),
    QColor(128, 0, 255),     QColor(255, 0, 128),    QColor(Qt::white),
    QColor(Qt::lightGray),   QColor(Qt::gray),       QColor(255, 255, 128),
    QColor(128, 255, 255),   QColor(255, 128, 255),  QColor(Qt::darkGray),
};

ColorBox::ColorBox(QWidget* parent) : QComboBox(parent) {
  setEditable(false);
  init();
}

void ColorBox::init() {
  QPixmap icon = QPixmap(28, 16);
  QRect r = QRect(0, 0, 27, 15);

  icon.fill(colors[0]);
  this->addItem(icon, tr("black"));

  QPainter p;
  p.begin(&icon);
  p.setBrush(QBrush(colors[1]));
  p.drawRect(r);
  this->addItem(icon, tr("red"));

  p.setBrush(QBrush(colors[2]));
  p.drawRect(r);
  this->addItem(icon, tr("green"));

  p.setBrush(QBrush(colors[3]));
  p.drawRect(r);
  this->addItem(icon, tr("blue"));

  p.setBrush(QBrush(colors[4]));
  p.drawRect(r);
  this->addItem(icon, tr("cyan"));

  p.setBrush(QBrush(colors[5]));
  p.drawRect(r);
  this->addItem(icon, tr("magenta"));

  p.setBrush(QBrush(colors[6]));
  p.drawRect(r);
  this->addItem(icon, tr("yellow"));

  p.setBrush(QBrush(colors[7]));
  p.drawRect(r);
  this->addItem(icon, tr("dark yellow"));

  p.setBrush(QBrush(colors[8]));
  p.drawRect(r);
  this->addItem(icon, tr("navy"));

  p.setBrush(QBrush(colors[9]));
  p.drawRect(r);
  this->addItem(icon, tr("purple"));

  p.setBrush(QBrush(colors[10]));
  p.drawRect(r);
  this->addItem(icon, tr("wine"));

  p.setBrush(QBrush(colors[11]));
  p.drawRect(r);
  this->addItem(icon, tr("olive"));

  p.setBrush(QBrush(colors[12]));
  p.drawRect(r);
  this->addItem(icon, tr("dark cyan"));

  p.setBrush(QBrush(colors[13]));
  p.drawRect(r);
  this->addItem(icon, tr("royal"));

  p.setBrush(QBrush(colors[14]));
  p.drawRect(r);
  this->addItem(icon, tr("orange"));

  p.setBrush(QBrush(colors[15]));
  p.drawRect(r);
  this->addItem(icon, tr("violet"));

  p.setBrush(QBrush(colors[16]));
  p.drawRect(r);
  this->addItem(icon, tr("pink"));

  p.setBrush(QBrush(colors[17]));
  p.drawRect(r);
  this->addItem(icon, tr("white"));

  p.setBrush(QBrush(colors[18]));
  p.drawRect(r);
  this->addItem(icon, tr("light gray"));

  p.setBrush(QBrush(colors[19]));
  p.drawRect(r);
  this->addItem(icon, tr("gray"));

  p.setBrush(QBrush(colors[20]));
  p.drawRect(r);
  this->addItem(icon, tr("light yellow"));

  p.setBrush(QBrush(colors[21]));
  p.drawRect(r);
  this->addItem(icon, tr("light cyan"));

  p.setBrush(QBrush(colors[22]));
  p.drawRect(r);
  this->addItem(icon, tr("light magenta"));

  p.setBrush(QBrush(colors[23]));
  p.drawRect(r);
  this->addItem(icon, tr("dark gray"));
  p.end();
}

void ColorBox::setColor(const QColor& c) {
  const QColor* ite = std::find(colors, colors + sizeof(colors), c);
  if (ite == colors + sizeof(colors))
    this->setCurrentIndex(0);  // default color is black.
  else
    this->setCurrentIndex(ite - colors);
}

QColor ColorBox::color() const {
  size_t i = this->currentIndex();
  if (i < sizeof(colors))
    return colors[this->currentIndex()];
  else
    return QColor(Qt::black);  // default color is black.
}

int ColorBox::colorIndex(const QColor& c) {
  const QColor* ite = std::find(colors, colors + sizeof(colors), c);
  return (ite - colors);
}

QColor ColorBox::color(int colorIndex) {
  if (colorIndex < (int)sizeof(colors))
    return colors[colorIndex];
  else
    return QColor(Qt::black);  // default color is black.
}

bool ColorBox::isValidColor(const QColor& color) {
  for (int i = 0; i < colors_count; i++) {
    if (color == colors[i]) return true;
  }
  return false;
}

int ColorBox::numPredefinedColors() { return colors_count; }
