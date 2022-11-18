#ifndef NOTE_H
#define NOTE_H

#include <qtextedit.h>

#include "MyWidget.h"
#include "core/propertybrowser/ObjectBrowserTreeItem.h"
#include "scripting/ScriptEdit.h"

class ScriptingEnv;
class QXmlStreamWriter;
class XmlStreamReader;
class ObjectBrowserTreeItemModel;
class DummyWindow;

/*!\brief Notes window class.
 *
 * \section future_plans Future Plans
 * - Search and replace
 */
class Note : public MyWidget, public ObjectBrowserTreeItem {
  Q_OBJECT

 public:
  Note(ScriptingEnv *env, const QString &label, QWidget *parent = nullptr,
       const char *name = 0, Qt::WindowFlags f = Qt::SubWindow);
  ~Note();

  virtual QString getItemName();
  virtual QIcon getItemIcon();
  virtual QString getItemTooltip();

  void init(ScriptingEnv *env);
  QString getText();
  ObjectBrowserTreeItemModel *getObjectModel() {return model_;}

 public slots:
  QTextEdit *textWidget() { return qobject_cast<QTextEdit *>(textedit_); }
  bool autoexec() const { return autoExec; }
  void setAutoexec(bool);
  void modifiedNote();

  // ScriptEdit methods
  QString text() { return textedit_->toPlainText(); }
  void setText(const QString &s) { textedit_->setText(s); }
  void save(QXmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);
  void print() { textedit_->print(); }
  void exportPDF(const QString &fileName) { textedit_->exportPDF(fileName); }
  QString exportASCII(const QString &file = QString()) {
    return textedit_->exportASCII(file);
  }
  QString importASCII(const QString &file = QString()) {
    return textedit_->importASCII(file);
  }
  void execute() { textedit_->execute(); }
  void executeAll() { textedit_->executeAll(); }
  void evaluate() { textedit_->evaluate(); }

 private:
  DummyWindow *dummywindow_;
  ObjectBrowserTreeItemModel* model_;
  ScriptEdit *textedit_;
  bool autoExec;
};

Q_DECLARE_METATYPE(Note *);
#endif  // NOTE_H
