#include "table/future_SortDialog.h"

#include <QApplication>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

namespace future {

SortDialog::SortDialog(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl) {
  setWindowIcon(qApp->windowIcon());
  setWindowTitle(tr("Sorting Options"));
  setSizeGripEnabled(true);

  QGroupBox* group_box1 = new QGroupBox();
  QGridLayout* top_layout = new QGridLayout(group_box1);
  QHBoxLayout* hl = new QHBoxLayout();
  hl->addStretch();

  top_layout->addWidget(new QLabel(tr("Sort columns")), 0, 0);
  ui.box_type = new QComboBox();
  ui.box_type->addItem(tr("Separately"));
  ui.box_type->addItem(tr("Together"));
  top_layout->addWidget(ui.box_type, 0, 1);
  ui.box_type->setCurrentIndex(Together);

  top_layout->addWidget(new QLabel(tr("Order")), 1, 0);
  ui.box_order = new QComboBox();
  ui.box_order->addItem(tr("Ascending"));
  ui.box_order->addItem(tr("Descending"));
  top_layout->addWidget(ui.box_order, 1, 1);

  top_layout->addWidget(new QLabel(tr("Leading column")), 2, 0);
  ui.columns_list = new QComboBox();
  top_layout->addWidget(ui.columns_list, 2, 1);
  top_layout->setRowStretch(3, 1);

  ui.button_ok = new QPushButton(tr("&Sort"));
  ui.button_ok->setDefault(true);
  hl->addWidget(ui.button_ok);

  ui.button_close = new QPushButton(tr("&Close"));
  hl->addWidget(ui.button_close);

  QVBoxLayout* mainlayout = new QVBoxLayout(this);
  mainlayout->addWidget(group_box1);
  mainlayout->addLayout(hl);

  connect(ui.button_ok, &QPushButton::clicked, this, &SortDialog::accept);
  connect(ui.button_close, &QPushButton::clicked, this, &SortDialog::close);
  connect(ui.box_type, qOverload<int>(&QComboBox::currentIndexChanged), this,
          &SortDialog::changeType);
}

void SortDialog::accept() {
  Column* leading;
  if (ui.box_type->currentIndex() == Together)
    leading = d_columns_list.at(ui.columns_list->currentIndex());
  else
    leading = 0;
  emit sort(leading, d_columns_list, ui.box_order->currentIndex() == Ascending);
}

void SortDialog::setColumnsList(QList<Column*> list) {
  d_columns_list = list;

  for (int i = 0; i < list.size(); i++)
    ui.columns_list->addItem(list.at(i)->name());
  ui.columns_list->setCurrentIndex(0);
}

void SortDialog::changeType(int Type) {
  if (Type == Together)
    ui.columns_list->setEnabled(true);
  else
    ui.columns_list->setEnabled(false);
}

}  // namespace future
