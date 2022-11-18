#ifndef TEXTFORMATBUTTONS_H
#define TEXTFORMATBUTTONS_H

#include <QWidget>
class QTextEdit;
class QPushButton;

//! Widget with text format buttons (connected to a QTextEdit)
class TextFormatButtons : public QWidget {
  Q_OBJECT

 public:
  //! Constructor
  /**
   * \param textEdit the QTextEdit that the buttons shall affect
   * \param parent parent widget
   */
  TextFormatButtons(QTextEdit *textEdit, QWidget *parent = nullptr);
  //! Show/Hide the "add curve" button
  void toggleCurveButton(bool enable);

 private:
  QTextEdit *connectedTextEdit;
  QPushButton *buttonCurve;
  QPushButton *buttonSubscript;
  QPushButton *buttonSuperscript;
  QPushButton *buttonLowerGreek;
  QPushButton *buttonUpperGreek;
  QPushButton *buttonMathSymbols;
  QPushButton *buttonArrowSymbols;
  QPushButton *buttonBold;
  QPushButton *buttonItalics;
  QPushButton *buttonUnderline;

  //! Internal function: format selected text with prefix and postfix
  void formatText(const QString &prefix, const QString &postfix);

 private slots:
  //! Format seleted text to subscript
  void addSubscript();
  //! Format seleted text to superscript
  void addSuperscript();
  //! Format seleted text to underlined
  void addUnderline();
  //! Format seleted text to italics
  void addItalics();
  //! Format seleted text to bold
  void addBold();
  //! Insert curve marker into the text
  void addCurve();

  //! Let the user insert lower case greek letters
  void showLowerGreek();
  //! Let the user insert capital greek letters
  void showUpperGreek();
  //! Let the user insert mathematical symbols
  void showMathSymbols();
  //! Let the user insert arrow symbols
  void showArrowSymbols();
  //! Insert 'letter' into the text
  void addSymbol(const QString &letter);
};

#endif  // TEXTFORMATBUTTONS_H
