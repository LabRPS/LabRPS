#ifndef CHARACTERMAPWIDGET_H
#define CHARACTERMAPWIDGET_H

#include <QDialog>

class QFontComboBox;
class QComboBox;
class QLineEdit;
class QScrollArea;
class CharacterWidget;

class CharacterMapWidget : public QDialog {
  Q_OBJECT

 public:
  CharacterMapWidget(QDialog *parent = nullptr);

 public slots:
  void insertCharacter(const QString &character);
  void updateClipboard();

 protected:
  void resizeEvent(QResizeEvent *event) override;

 private:
  static const int glyphSize_;
  CharacterWidget *characterWidget_;
  QFontComboBox *fontCombo_;
  QComboBox *charlist_;
  QLineEdit *lineEdit_;
  QScrollArea *scrollArea_;
};

#endif  // CHARACTERMAPWIDGET_H
