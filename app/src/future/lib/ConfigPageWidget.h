#ifndef CONFIG_PAGE_WIDGET
#define CONFIG_PAGE_WIDGET

#include <QWidget>

//! Widget for configuration pages that has an apply slot
class ConfigPageWidget : public QWidget {
  Q_OBJECT

 public:
  ConfigPageWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::Widget);

 public slots:
  virtual void apply() = 0;
};

#endif  // CONFIG_PAGE_WIDGET
