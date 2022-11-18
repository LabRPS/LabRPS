#ifndef ASETTINGSLISTVIEW_H
#define ASETTINGSLISTVIEW_H

#include <QListView>

class aSettingsListView : public QListView {
  Q_OBJECT

 public:
  aSettingsListView(QWidget *parent = 0);
  ~aSettingsListView();

  bool autoAdjustHeight();
  static const int listViewWidthPadding_ = 10;
  static const int listViewHeightPadding_ = 5;
};

#endif  // ASETTINGSLISTVIEW_H
