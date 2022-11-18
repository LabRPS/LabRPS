#ifndef RPSSCENE_H
#define RPSSCENE_H

#include <qtextedit.h>
#include "SceneView.h"

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
class RPSScene : public MyWidget, public ObjectBrowserTreeItem {
  Q_OBJECT

 public:
  RPSScene(ScriptingEnv *env, const QString &label, QWidget *parent = nullptr,
       const char *name = 0, Qt::WindowFlags f = Qt::SubWindow);
  ~RPSScene();

  virtual QString getItemName();
  virtual QIcon getItemIcon();
  virtual QString getItemTooltip();

  void init(ScriptingEnv *env);
  //QString getText();
  ObjectBrowserTreeItemModel *getObjectModel() {return model_;}

 public slots:
  SceneView *getViewWidget() { return qobject_cast<SceneView *>(sceneView_); }
  bool autoexec() const { return autoExec; }
  void setAutoexec(bool);
  void modifiedView();

   //ScriptEdit methods
  void save(QXmlStreamWriter *xmlwriter);
  bool load(XmlStreamReader *xmlreader);
  void print() { sceneView_->print(); }

 private:
  DummyWindow *dummywindow_;
  ObjectBrowserTreeItemModel* model_;
  SceneView *sceneView_;
  bool autoExec;
};

Q_DECLARE_METATYPE(RPSScene *);
#endif  // RPSSCENE_H
