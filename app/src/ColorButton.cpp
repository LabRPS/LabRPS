#include "ColorButton.h"

#include <QPalette>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFrame>

ColorButton::ColorButton(QWidget *parent) : QWidget(parent) { init(); }

void ColorButton::init() {
  const int btn_size = 28;
  selectButton = new QPushButton(QPixmap(":/palette.xpm"), QString(), this);
  selectButton->setMinimumWidth(btn_size);
  selectButton->setMinimumHeight(btn_size);

  display = new QFrame(this);
  display->setLineWidth(2);
  display->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  display->setMinimumHeight(btn_size);
  display->setMinimumWidth(2 * btn_size);
  display->setAutoFillBackground(true);
  setColor(QColor(Qt::white));

  QHBoxLayout *l = new QHBoxLayout(this);
  l->setMargin(0);
  l->addWidget(display);
  l->addWidget(selectButton);

  setMaximumWidth(3 * btn_size);
  setMaximumHeight(btn_size);

  connect(selectButton, SIGNAL(clicked()), this, SIGNAL(clicked()));
}

void ColorButton::setColor(const QColor &c) {
  QPalette pal;
  pal.setColor(QPalette::Window, c);
  display->setPalette(pal);
}

QColor ColorButton::color() const {
  return display->palette().color(QPalette::Window);
}

QSize ColorButton::sizeHint() const { return QSize(4 * btn_size, btn_size); }
