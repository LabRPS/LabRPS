#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <qglviewer.h>

class SceneView : public QGLViewer {
Q_OBJECT

public:
    SceneView(QWidget *parent = 0);

protected:
  virtual void draw();
  virtual void init();

public:
    void print();

};


#endif  // SCENEVIEW_H
