#include "PreCompiled.h"

#include "Layout3D.h"

#include <QMainWindow>
#include <QtCore/qmath.h>
#include <QtDataVisualization/qutils.h>

#include <QtDataVisualization/Q3DInputHandler>
#include <QDateTime>
#include <QPropertyAnimation>
#include <QSurfaceFormat>
#include <QtDataVisualization/Q3DBars>
#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QPrintPreviewDialog>

#include "Bar3D.h"
#include "Custom3DInteractions.h"
#include "DataManager3D.h"
#include "Matrix.h"
#include "MyWidget.h"
#include "Scatter3D.h"
#include "Surface3D.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"
#include "plotcommon/widgets/ImageExportDialog.h"
//#include "MainWindow.h"

const int Layout3D::defaultlayout2dwidth_ = 500;
const int Layout3D::defaultlayout2dheight_ = 400;
const int Layout3D::minimumlayout2dwidth_ = 100;
const int Layout3D::minimumlayout2dheight_ = 100;

Layout3D::Layout3D(const Graph3DCommon::Plot3DType &plottype,
                   const QString &label, QWidget *parent, const QString name,
                   Qt::WindowFlags flag)
    : MyWidget(label, parent, name, flag),
      plottype_(plottype),
      graph3dsurface_(nullptr),
      graph3dbars_(nullptr),
      graph3dscatter_(nullptr),
      surfacemodifier_(nullptr),
      barmodifier_(nullptr),
      scattermodifier_(nullptr),
      custominter_(new Custom3DInteractions) {
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface: {
      graph3dsurface_ = new Q3DSurface();
      main_widget_ = QWidget::createWindowContainer(graph3dsurface_);
      surfacemodifier_ = new Surface3D(graph3dsurface_);
      graph_ = static_cast<QAbstract3DGraph *>(graph3dsurface_);
      connect(surfacemodifier_, &Surface3D::dataAdded, this,
              [&]() { Q_EMIT dataAdded(this); });
    } break;
    case Graph3DCommon::Plot3DType::Bar: {
      graph3dbars_ = new Q3DBars();
      main_widget_ = QWidget::createWindowContainer(graph3dbars_);
      barmodifier_ = new Bar3D(graph3dbars_);
      graph_ = static_cast<QAbstract3DGraph *>(graph3dbars_);
      connect(barmodifier_, &Bar3D::dataAdded, this,
              [&]() { Q_EMIT dataAdded(this); });
    } break;
    case Graph3DCommon::Plot3DType::Scatter: {
      graph3dscatter_ = new Q3DScatter();
      main_widget_ = QWidget::createWindowContainer(graph3dscatter_);
      scattermodifier_ = new Scatter3D(graph3dscatter_);
      graph_ = static_cast<QAbstract3DGraph *>(graph3dscatter_);
      connect(scattermodifier_, &Scatter3D::dataAdded, this,
              [&]() { Q_EMIT dataAdded(this); });
    } break;
  }

  main_widget_->setContentsMargins(0, 0, 0, 0);
  QWidget *widget = new QWidget(this);
  widget->setContentsMargins(0, 0, 0, 0);
  QHBoxLayout *hLayout = new QHBoxLayout(widget);
  hLayout->setMargin(0);
  hLayout->addWidget(main_widget_, 1);
  hLayout->setAlignment(Qt::AlignTop);
  widget->setLayout(hLayout);
  setWidget(widget);
  main_widget_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  main_widget_->setFocusPolicy(Qt::StrongFocus);
  widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  widget->setFocusPolicy(Qt::StrongFocus);

  if (name.isEmpty()) setObjectName(QString::fromLatin1("layout3d"));
  QDateTime birthday = QDateTime::currentDateTime();
  setBirthDate(birthday.toString(Qt::LocalDate));
  setFocusPolicy(Qt::TabFocus);

  setGeometry(QRect(0, 0, defaultlayout2dwidth_, defaultlayout2dheight_));
  setMinimumSize(QSize(minimumlayout2dwidth_, minimumlayout2dheight_));
  setFocusPolicy(Qt::StrongFocus);

  // setting general graph properties;
  graph_->setActiveInputHandler(custominter_);
  graph_->activeTheme()->setType(Q3DTheme::ThemeDigia);
  graph_->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
  graph_->scene()->activeCamera()->setCameraPreset(
      Q3DCamera::CameraPresetFront);
  graph_->setAspectRatio(1.0);
  graph_->setHorizontalAspectRatio(1.0);
  // set animations
  m_animationCameraX_ =
      new QPropertyAnimation(graph_->scene()->activeCamera(), "xRotation");
  m_animationCameraX_->setDuration(20000);
  m_animationCameraX_->setStartValue(QVariant::fromValue(-180.0f));
  m_animationCameraX_->setEndValue(QVariant::fromValue(180.0f));
  m_animationCameraX_->setLoopCount(-1);
  upAnimation_ =
      new QPropertyAnimation(graph_->scene()->activeCamera(), "yRotation");
  upAnimation_->setDuration(10000);
  upAnimation_->setStartValue(QVariant::fromValue(0.0f));
  upAnimation_->setEndValue(QVariant::fromValue(90.0f));
  downAnimation_ =
      new QPropertyAnimation(graph_->scene()->activeCamera(), "yRotation");
  downAnimation_->setDuration(10000);
  downAnimation_->setStartValue(QVariant::fromValue(90.0f));
  downAnimation_->setEndValue(QVariant::fromValue(0.0f));
  m_animationCameraY_ = new QSequentialAnimationGroup();
  m_animationCameraY_->setLoopCount(-1);
  m_animationCameraY_->addAnimation(upAnimation_);
  m_animationCameraY_->addAnimation(downAnimation_);

  graph_->scene()->activeCamera()->setCameraPosition(45, 30, 130);
  connect(custominter_, &Custom3DInteractions::showContextMenu, this,
          &Layout3D::showContextMenu);
  // QWindow doesnt pass mousepressevent to the container widget
  // so do it here manually
  connect(custominter_, &Custom3DInteractions::activateParentWindow, this,
          [=]() {
            Q_EMIT mousepressevent(this);
            unsetCursor();
          });
}

Layout3D::~Layout3D() {
  if (!closewithoutcolumnmodelockchange_) switch (plottype_) {
      case Graph3DCommon::Plot3DType::Surface:
        break;
      case Graph3DCommon::Plot3DType::Bar: {
        QVector<DataBlockBar3D *> datalist = barmodifier_->getData();
        Q_FOREACH (DataBlockBar3D *bardata, datalist) {
          if (bardata->getxcolumn())
            bardata->getxcolumn()->setColumnModeLock(false);
          if (bardata->getycolumn())
            bardata->getycolumn()->setColumnModeLock(false);
          if (bardata->getzcolumn())
            bardata->getzcolumn()->setColumnModeLock(false);
        }
      } break;
      case Graph3DCommon::Plot3DType::Scatter: {
        QVector<DataBlockScatter3D *> datalist = scattermodifier_->getData();
        Q_FOREACH (DataBlockScatter3D *scatterdata, datalist) {
          if (scatterdata->getxcolumn())
            scatterdata->getxcolumn()->setColumnModeLock(false);
          if (scatterdata->getycolumn())
            scatterdata->getycolumn()->setColumnModeLock(false);
          if (scatterdata->getzcolumn())
            scatterdata->getzcolumn()->setColumnModeLock(false);
        }
      } break;
    }
}

Surface3D *Layout3D::getSurface3DModifier() const {
  if (plottype_ == Graph3DCommon::Plot3DType::Surface)
    return surfacemodifier_;
  else {
    qDebug() << "getSurface3DModifier() is null: this is not Surface3D";
    return nullptr;
  }
}

Bar3D *Layout3D::getBar3DModifier() const {
  if (plottype_ == Graph3DCommon::Plot3DType::Bar)
    return barmodifier_;
  else {
    qDebug() << "getBar3DModifier() is null: this is not Bar3D";
    return nullptr;
  }
}

Scatter3D *Layout3D::getScatter3DModifier() const {
  if (plottype_ == Graph3DCommon::Plot3DType::Scatter)
    return scattermodifier_;
  else {
    qDebug() << "getScatter3DModifier() is null: this is not Scatter3D";
    return nullptr;
  }
}

QAbstract3DGraph *Layout3D::getAbstractGraph() const { return graph_; }

void Layout3D::setCustomInteractions(QAbstract3DGraph *graph, bool status) {
  std::unique_ptr<Q3DSurface> gg(new Q3DSurface);
  (status) ? graph->setActiveInputHandler(custominter_)
           : graph->setActiveInputHandler(gg->activeInputHandler());
}

void Layout3D::setAnimation(bool status) {
  if (status) {
    m_animationCameraX_->start();
    m_animationCameraY_->start();
  } else {
    m_animationCameraX_->pause();
    m_animationCameraY_->pause();
  }
}

void Layout3D::exportGraph() {
  std::unique_ptr<ImageExportDialog> ied(new ImageExportDialog(this, false));
  ied->enableraster_scale(false);
  ied->setraster_scale(1);
  ied->setraster_antialias(16);
  ied->setraster_height(main_widget_->height());
  ied->setraster_width(main_widget_->width());
  ied->setvector_height(main_widget_->height());
  ied->setraster_width(main_widget_->width());
  if (ied->exec() != QDialog::Accepted) return;
  if (ied->selectedFiles().isEmpty()) return;
  QString selected_filter = ied->selectedNameFilter();

  QString file_name = ied->selectedFiles().at(0);
  QFileInfo file_info(file_name);
  if (!file_info.fileName().contains(QString::fromLatin1(".")))
    file_name.append(selected_filter.remove(QString::fromLatin1("*")));

  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(
        this, tr("Export Error"),
        tr("Could not write to file: <br><h4> %1 </h4><p>Please verify that "
           "you have the right to write to this location!")
            .arg(file_name));
    return;
  }

  int raster_resolution = ied->raster_resolution();
  int raster_width = ied->raster_width();
  int raster_height = ied->raster_height();
  int raster_quality = ied->raster_quality();
  int raster_antialias = ied->raster_antialias();

  // int vector_width = ied->vector_width();
  // int vector_height = ied->vector_height();

  if (selected_filter.contains(QString::fromLatin1(".pdf"))) {
    // plot2dCanvas_->savePdf(file_name, vector_width, vector_height);
  } else if (selected_filter.contains(QString::fromLatin1(".svg"))) {
    // plot2dCanvas_->saveSvg(file_name, vector_width, vector_height);
  } else if (selected_filter.contains(QString::fromLatin1(".ps"))) {
    // plot2dCanvas_->savePs(file_name, vector_width, vector_height);
  } else {
    QByteArray ba = selected_filter.toLatin1();
    ba = ba.trimmed();
    ba.remove(0, 1);
    const char *c_char = ba.data();
    saveRastered(file_name, c_char, raster_quality, raster_antialias,
                 raster_resolution, QSize(raster_width, raster_height));
  }
}

void Layout3D::saveRastered(const QString &filename, const char *format,
                            const int quality, const int maa, int dpi,
                            const QSize &size) {
  QImage image = QImage();
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      image = graph3dsurface_->renderToImage(maa, size);
      break;
    case Graph3DCommon::Plot3DType::Bar:
      image = graph3dbars_->renderToImage(maa, size);
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      image = graph3dscatter_->renderToImage(maa, size);
      break;
  }
  int dpm = dpi / 0.0254;
  image.setDotsPerMeterX(dpm);
  image.setDotsPerMeterY(dpm);
  image.save(filename, format, quality);
}

void Layout3D::exportGraphwithoutdialog(const QString &name,
                                        const QString &selected_filter,
                                        const QSize &size) {
  // set default values
  int raster_quality = 100;
  int raster_dpi = 300;
  int raster_antialias = 8;

  if (selected_filter.contains(QString::fromLatin1(".pdf"))) {
    // plot2dCanvas_->savePdf(name, vector_width, vector_height);
  } else if (selected_filter.contains(QString::fromLatin1(".svg"))) {
    // plot2dCanvas_->saveSvg(name, vector_width, vector_height);
  } else if (selected_filter.contains(QString::fromLatin1(".ps"))) {
    // plot2dCanvas_->savePs(name, vector_width, vector_height);
  } else {
    QByteArray ba = selected_filter.toLatin1();
    ba = ba.trimmed();
    ba.remove(0, 1);
    const char *c_char = ba.data();
    saveRastered(name, c_char, raster_quality, raster_antialias, raster_dpi,
                 size);
  }
}

QSize Layout3D::getContainerSize() const { return main_widget_->size(); }

Graph3DCommon::Plot3DType Layout3D::getPlotType() const { return plottype_; }

void Layout3D::load(XmlStreamReader *xmlreader, QList<Table *> tabs,
                    QList<Matrix *> mats, Gui::MainWindow* app,
                    bool setname) {
  if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("plot3d")) {
    bool ok = false;

    // read caption spec
    int x = xmlreader->readAttributeInt(QString::fromLatin1("x"), &ok);
    if (ok) {
      int y = xmlreader->readAttributeInt(QString::fromLatin1("y"), &ok);
      if (ok) {
        int width = xmlreader->readAttributeInt(QString::fromLatin1("width"), &ok);
        if (ok) {
          int height = xmlreader->readAttributeInt(QString::fromLatin1("height"), &ok);
          if (ok) {
            setGeometry(x, y, width, height);
          }
        }
      }
    } else
      xmlreader->raiseWarning(tr("Plot3D geometry setting error."));

    // read creation time
    QString time = xmlreader->readAttributeString(QString::fromLatin1("creation_time"), &ok);
    QDateTime creation_time =
        QDateTime::fromString(time, QString::fromLatin1("yyyy-dd-MM hh:mm:ss:zzz"));
    if (!time.isEmpty() && creation_time.isValid() && ok) {
      setBirthDate(creation_time.toString(Qt::LocalDate));
    } else {
      xmlreader->raiseWarning(
          tr("Invalid creation time. Using current time insted."));
      setBirthDate(QDateTime::currentDateTime().toString(Qt::LocalDate));
    }

    // read caption spec
    int captionspec = xmlreader->readAttributeInt(QString::fromLatin1("caption_spec"), &ok);
    if (ok)
      setCaptionPolicy(static_cast<MyWidget::CaptionPolicy>(captionspec));
    else
      xmlreader->raiseWarning(tr("Invalid caption policy or read error."));

    // read name
    QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
    if (setname) {
      if (ok) {
        setName(name);
      } else
        xmlreader->raiseWarning(tr("Layout3D name missing or empty"));
    }

    // read label
    QString label = xmlreader->readAttributeString(QString::fromLatin1("label"), &ok);
    if (ok) {
      setWindowLabel(label);
    } else
      xmlreader->raiseWarning(tr("Layout3D label missing or empty"));

    loadCanvas(xmlreader);
    loadTheme(xmlreader);
    switch (plottype_) {
      case Graph3DCommon::Plot3DType::Surface:
        loadValueAxis(xmlreader);
        loadValueAxis(xmlreader);
        loadValueAxis(xmlreader);
        surfacemodifier_->load(xmlreader, tabs, mats, app);
        break;
      case Graph3DCommon::Plot3DType::Bar:
        loadCategoryAxis(xmlreader);
        loadCategoryAxis(xmlreader);
        loadValueAxis(xmlreader);
        barmodifier_->load(xmlreader, tabs, mats);
        break;
      case Graph3DCommon::Plot3DType::Scatter:
        loadValueAxis(xmlreader);
        loadValueAxis(xmlreader);
        loadValueAxis(xmlreader);
        scattermodifier_->load(xmlreader, tabs, mats);
        break;
    }
  }
}

void Layout3D::loadCanvas(XmlStreamReader *xmlreader) {
  while (!xmlreader->atEnd()) {
    xmlreader->readNext();
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("canvas")) break;
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("canvas")) {
      bool ok = false;
      Q3DTheme::Theme theme = Q3DTheme::Theme::ThemeQt;
      QString themename = xmlreader->readAttributeString(QString::fromLatin1("themename"), &ok);
      if (!ok) xmlreader->raiseWarning(QString::fromLatin1("Plot3D theme unknown!"));

      // theme
      if (themename == QString::fromLatin1("themeqt"))
        theme = Q3DTheme::Theme::ThemeQt;
      else if (themename == QString::fromLatin1("themedigia"))
        theme = Q3DTheme::Theme::ThemeDigia;
      else if (themename == QString::fromLatin1("themeebony"))
        theme = Q3DTheme::Theme::ThemeEbony;
      else if (themename == QString::fromLatin1("themeretro"))
        theme = Q3DTheme::Theme::ThemeRetro;
      else if (themename == QString::fromLatin1("themearmyblue"))
        theme = Q3DTheme::Theme::ThemeArmyBlue;
      else if (themename == QString::fromLatin1("themeisabelle"))
        theme = Q3DTheme::Theme::ThemeIsabelle;
      else if (themename == QString::fromLatin1("themestonemoss"))
        theme = Q3DTheme::Theme::ThemeStoneMoss;
      else if (themename == QString::fromLatin1("themeuserdefined"))
        theme = Q3DTheme::Theme::ThemeUserDefined;
      else if (themename == QString::fromLatin1("themeprimarycolors"))
        theme = Q3DTheme::Theme::ThemePrimaryColors;
      else
        xmlreader->raiseWarning(QString::fromLatin1("Plot3D theme setting unknown!"));
      graph_->activeTheme()->setType(theme);
    }
  }
}

void Layout3D::loadTheme(XmlStreamReader *xmlreader) {
  while (!xmlreader->atEnd()) {
    xmlreader->readNext();
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("theme")) break;
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("theme")) {
      bool ok = false;
      Q3DTheme *theme = graph_->activeTheme();

      // canvas color
      QString canvascolor = xmlreader->readAttributeString(QString::fromLatin1("canvascolor"), &ok);
      if (ok)
        theme->setWindowColor(canvascolor);
      else
        xmlreader->raiseWarning(QString::fromLatin1("Plot3D canvas color property setting error"));

      // background
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("background"))
          break;
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("background")) {
          bool ok = false;

          // background visible
          bool visible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
          if (ok)
            theme->setBackgroundEnabled(visible);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D background visible property setting error"));

          // background color
          QString bkcolor = xmlreader->readAttributeString(QString::fromLatin1("color"), &ok);
          if (ok)
            theme->setBackgroundColor(bkcolor);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D background color property setting error"));
        }
      }

      // light
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("light")) break;
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("light")) {
          bool ok = false;

          // light color
          QString lightcolor = xmlreader->readAttributeString(QString::fromLatin1("color"), &ok);
          if (ok)
            theme->setLightColor(lightcolor);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D light color property setting error"));

          // light strength
          int strength = xmlreader->readAttributeInt(QString::fromLatin1("strength"), &ok);
          if (ok)
            theme->setLightStrength(strength);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D light strength property setting error"));

          // ambient light strength
          int ambstrength = xmlreader->readAttributeInt(QString::fromLatin1("ambientstrength"), &ok);
          if (ok)
            theme->setAmbientLightStrength(ambstrength);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D ambient light strength property setting error"));
        }
      }

      // grid
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("grid")) break;
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("grid")) {
          bool ok = false;

          // grid visible
          bool visible = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
          if (ok)
            theme->setGridEnabled(visible);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D grid visible property setting error"));

          // grid line color
          QString gdcolor = xmlreader->readAttributeString(QString::fromLatin1("color"), &ok);
          if (ok)
            theme->setGridLineColor(gdcolor);
          else
            xmlreader->raiseWarning(
                QString::fromLatin1("Plot3D grid line color property setting error"));
        }
      }

      // label
      while (!xmlreader->atEnd()) {
        xmlreader->readNext();
        if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("label")) break;
        if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("label")) {
          bool ok = false;

          // label background visible
          bool visible = xmlreader->readAttributeBool(QString::fromLatin1("backgroundvisible"), &ok);
          if (ok)
            theme->setLabelBackgroundEnabled(visible);
          else
            xmlreader->raiseWarning(
               QString::fromLatin1( "Plot3D label background visible property setting error"));

          // label background color
          QString bkcolor =
              xmlreader->readAttributeString(QString::fromLatin1("backgroundcolor"), &ok);
          if (ok)
            theme->setLabelBackgroundColor(bkcolor);
          else
            xmlreader->raiseWarning(
               QString::fromLatin1( "Plot3D label background color property setting error"));

          // label border visible
          bool lbbovisible = xmlreader->readAttributeBool(QString::fromLatin1("bordervisible"), &ok);
          if (ok)
            theme->setLabelBorderEnabled(lbbovisible);
          else
            xmlreader->raiseWarning(
               QString::fromLatin1( "Plot3D label border visible property setting error"));

          // label font
          while (!xmlreader->atEnd()) {
            xmlreader->readNext();
            if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("font")) break;
            if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("font")) {
              QPair<QFont, QColor> fontpair = xmlreader->readFont(&ok);
              if (ok) {
                theme->setFont(fontpair.first);
                theme->setLabelTextColor(fontpair.second);
              } else
                xmlreader->raiseWarning(
                    tr("Plot3D label font & color property setting error"));
            }
          }
        }
      }
    }
  }
}

void Layout3D::loadValueAxis(XmlStreamReader *xmlreader) {
  while (!xmlreader->atEnd()) {
    xmlreader->readNext();
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("axis")) break;
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("axis")) {
      bool ok = false;

      // axis type
      QString axistype = xmlreader->readAttributeString(QString::fromLatin1("type"), &ok);
      if (!ok) xmlreader->raiseError(QString::fromLatin1("Plot3D axis type unknown error!"));
      if (axistype != QString::fromLatin1("value"))
        xmlreader->raiseError(QString::fromLatin1("Plot3D axis type unexpected error!"));

      // axis orientation
      QString axisori = xmlreader->readAttributeString(QString::fromLatin1("orientation"), &ok);
      if (!ok) xmlreader->raiseError(QString::fromLatin1("Plot3D axis orientation unknown error!"));
      QValue3DAxis *axis = nullptr;
      switch (plottype_) {
        case Graph3DCommon::Plot3DType::Surface:
          if (axisori == QString::fromLatin1("x"))
            axis = surfacemodifier_->getGraph()->axisX();
          else if (axisori == QString::fromLatin1("y"))
            axis = surfacemodifier_->getGraph()->axisY();
          else if (axisori == QString::fromLatin1("z"))
            axis = surfacemodifier_->getGraph()->axisZ();
          break;
        case Graph3DCommon::Plot3DType::Bar:
          if (axisori == QString::fromLatin1("z")) axis = barmodifier_->getGraph()->valueAxis();
          break;
        case Graph3DCommon::Plot3DType::Scatter:
          if (axisori == QString::fromLatin1("x"))
            axis = scattermodifier_->getGraph()->axisX();
          else if (axisori == QString::fromLatin1("y"))
            axis = scattermodifier_->getGraph()->axisY();
          else if (axisori == QString::fromLatin1("z"))
            axis = scattermodifier_->getGraph()->axisZ();
          break;
      }
      if (!axis)
        xmlreader->raiseError(QString::fromLatin1("Plot3D value axis unable to initialize error!"));

      // Axis autorange
      bool autorange = xmlreader->readAttributeBool(QString::fromLatin1("autorange"), &ok);
      (ok) ? axis->setAutoAdjustRange(autorange)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis autorange setting error!"));

      // Axis from
      double from = xmlreader->readAttributeDouble(QString::fromLatin1("from"), &ok);
      (ok) ? axis->setMin(from)
           : xmlreader->raiseWarning(QString::fromLatin1("Plot3D value axis from setting error!"));

      // Axis to
      double to = xmlreader->readAttributeDouble(QString::fromLatin1("to"), &ok);
      (ok) ? axis->setMax(to)
           : xmlreader->raiseWarning(QString::fromLatin1("Plot3D value axis to setting error!"));

      // Axis range reverse
      bool reverse = xmlreader->readAttributeBool(QString::fromLatin1("reverse"), &ok);
      (ok)
          ? axis->setReversed(reverse)
          : xmlreader->raiseWarning(QString::fromLatin1("Plot3D value axis reverse setting error!"));

      // Axis tick count
      int tickcount = xmlreader->readAttributeInt(QString::fromLatin1("tickcount"), &ok);
      (ok) ? axis->setSegmentCount(tickcount)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis tick count setting error!"));

      // Axis subtick count
      int subtickcount = xmlreader->readAttributeInt(QString::fromLatin1("subtickcount"), &ok);
      (ok) ? axis->setSubSegmentCount(subtickcount)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis subtick count setting error!"));

      // Axis ticklabel format
      QString lblformat =
          xmlreader->readAttributeString(QString::fromLatin1("ticklabelformat"), &ok);
      (ok) ? axis->setLabelFormat(lblformat)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis tick label format setting error!"));

      // Axis tick label rotation
      double tklblrotation =
          xmlreader->readAttributeDouble(QString::fromLatin1("ticklabelrotation"), &ok);
      (ok) ? axis->setLabelAutoRotation(tklblrotation)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis tick label rotation setting error!"));

      // Axis label visible
      bool lblvisible = xmlreader->readAttributeBool(QString::fromLatin1("labelvisible"), &ok);
      (ok) ? axis->setTitleVisible(lblvisible)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis title visible setting error!"));

      // Axis label fixed
      bool lblfixed = xmlreader->readAttributeBool(QString::fromLatin1("labelfixed"), &ok);
      (ok) ? axis->setTitleFixed(lblfixed)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D value axis title fixed setting error!"));

      // Axis label text
      QString label = xmlreader->readAttributeString(QString::fromLatin1("label"), &ok);
      (ok) ? axis->setTitle(label)
           : xmlreader->raiseWarning(QString::fromLatin1("Plot3D value axis label setting error!"));
    }
  }
}

void Layout3D::loadCategoryAxis(XmlStreamReader *xmlreader) {
  while (!xmlreader->atEnd()) {
    xmlreader->readNext();
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("axis")) break;
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("axis")) {
      bool ok = false;

      // axis type
      QString axistype = xmlreader->readAttributeString(QString::fromLatin1("type"), &ok);
      if (!ok) xmlreader->raiseError(QString::fromLatin1("Plot3D axis type unknown error!"));
      if (axistype != QString::fromLatin1("category"))
        xmlreader->raiseError(QString::fromLatin1("Plot3D axis type unexpected error!"));

      // axis orientation
      QString axisori = xmlreader->readAttributeString(QString::fromLatin1("orientation"), &ok);
      if (!ok) xmlreader->raiseError(QString::fromLatin1("Plot3D axis orientation unknown error!"));
      QCategory3DAxis *axis = nullptr;
      switch (plottype_) {
        case Graph3DCommon::Plot3DType::Surface:
          break;
        case Graph3DCommon::Plot3DType::Bar:
          if (axisori == QString::fromLatin1("x"))
            axis = barmodifier_->getGraph()->rowAxis();
          else if (axisori == QString::fromLatin1("y"))
            axis = barmodifier_->getGraph()->columnAxis();
          break;
        case Graph3DCommon::Plot3DType::Scatter:
          break;
      }
      if (!axis)
        xmlreader->raiseError(
           QString::fromLatin1( "Plot3D category axis unable to initialize error!"));

      // Axis autorange
      bool autorange = xmlreader->readAttributeBool(QString::fromLatin1("autorange"), &ok);
      (ok) ? axis->setAutoAdjustRange(autorange)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D category axis autorange setting error!"));

      // Axis from
      double from = xmlreader->readAttributeDouble(QString::fromLatin1("from"), &ok);
      (ok)
          ? axis->setMin(from)
          : xmlreader->raiseWarning(QString::fromLatin1("Plot3D category axis from setting error!"));

      // Axis to
      double to = xmlreader->readAttributeDouble(QString::fromLatin1("to"), &ok);
      (ok) ? axis->setMax(to)
           : xmlreader->raiseWarning(QString::fromLatin1("Plot3D category axis to setting error!"));

      // Axis tick label rotation
      double tklblrotation =
          xmlreader->readAttributeDouble(QString::fromLatin1("ticklabelrotation"), &ok);
      (ok) ? axis->setLabelAutoRotation(tklblrotation)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D category axis tick label rotation setting error!"));

      // Axis label visible
      bool lblvisible = xmlreader->readAttributeBool(QString::fromLatin1("labelvisible"), &ok);
      (ok) ? axis->setTitleVisible(lblvisible)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D category axis title visible setting error!"));

      // Axis label fixed
      bool lblfixed = xmlreader->readAttributeBool(QString::fromLatin1("labelfixed"), &ok);
      (ok) ? axis->setTitleFixed(lblfixed)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D category axis title fixed setting error!"));

      // Axis label text
      QString label = xmlreader->readAttributeString(QString::fromLatin1("label"), &ok);
      (ok) ? axis->setTitle(label)
           : xmlreader->raiseWarning(
                QString::fromLatin1( "Plot3D category axis label setting error!"));
    }
  }
}

void Layout3D::save(XmlStreamWriter *xmlwriter, const bool saveastemplate) {
  xmlwriter->writeStartElement(QString::fromLatin1("plot3d"));
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("surface"));
      break;
    case Graph3DCommon::Plot3DType::Bar:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("bar"));
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("scatter"));
      break;
  }
  xmlwriter->writeAttribute(QString::fromLatin1("x"), QString::number(pos().x()));
  xmlwriter->writeAttribute(QString::fromLatin1("y"), QString::number(pos().y()));
  xmlwriter->writeAttribute(QString::fromLatin1("width"), QString::number(width()));
  xmlwriter->writeAttribute(QString::fromLatin1("height"), QString::number(height()));
  QDateTime datetime = QDateTime::fromString(birthDate(), Qt::LocalDate);
  xmlwriter->writeAttribute(QString::fromLatin1("creation_time"),
                            datetime.toString(QString::fromLatin1("yyyy-dd-MM hh:mm:ss:zzz")));
  xmlwriter->writeAttribute(QString::fromLatin1("caption_spec"), QString::number(captionPolicy()));
  xmlwriter->writeAttribute(QString::fromLatin1("name"), name());
  xmlwriter->writeAttribute(QString::fromLatin1("label"), windowLabel());
  saveCanvas(xmlwriter);
  saveTheme(xmlwriter);
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      saveValueAxis(xmlwriter, surfacemodifier_->getGraph()->axisX());
      saveValueAxis(xmlwriter, surfacemodifier_->getGraph()->axisY());
      saveValueAxis(xmlwriter, surfacemodifier_->getGraph()->axisZ());
      surfacemodifier_->save(xmlwriter, saveastemplate);
      break;
    case Graph3DCommon::Plot3DType::Bar:
      saveCategoryAxis(xmlwriter, barmodifier_->getGraph()->columnAxis());
      saveCategoryAxis(xmlwriter, barmodifier_->getGraph()->rowAxis());
      saveValueAxis(xmlwriter, barmodifier_->getGraph()->valueAxis());
      barmodifier_->save(xmlwriter, saveastemplate);
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      saveValueAxis(xmlwriter, scattermodifier_->getGraph()->axisX());
      saveValueAxis(xmlwriter, scattermodifier_->getGraph()->axisY());
      saveValueAxis(xmlwriter, scattermodifier_->getGraph()->axisZ());
      scattermodifier_->save(xmlwriter, saveastemplate);
      break;
  }
  xmlwriter->writeEndElement();
}

void Layout3D::saveCanvas(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("canvas"));
  Q3DTheme *theme = graph_->activeTheme();
  switch (theme->type()) {
    case Q3DTheme::Theme::ThemeQt:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeqt"));
      break;
    case Q3DTheme::Theme::ThemeDigia:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themedigia"));
      break;
    case Q3DTheme::Theme::ThemeEbony:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeebony"));
      break;
    case Q3DTheme::Theme::ThemeRetro:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeretro"));
      break;
    case Q3DTheme::Theme::ThemeArmyBlue:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themearmyblue"));
      break;
    case Q3DTheme::Theme::ThemeIsabelle:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeisabelle"));
      break;
    case Q3DTheme::Theme::ThemeStoneMoss:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themestonemoss"));
      break;
    case Q3DTheme::Theme::ThemeUserDefined:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeuserdefined"));
      break;
    case Q3DTheme::Theme::ThemePrimaryColors:
      xmlwriter->writeAttribute(QString::fromLatin1("themename"), QString::fromLatin1("themeprimarycolors"));
      break;
  }
  xmlwriter->writeEndElement();
}

void Layout3D::saveTheme(XmlStreamWriter *xmlwriter) {
  xmlwriter->writeStartElement(QString::fromLatin1("theme"));
  Q3DTheme *theme = graph_->activeTheme();
  xmlwriter->writeAttribute(QString::fromLatin1("canvascolor"),
                            theme->windowColor().name(QColor::HexArgb));
  xmlwriter->writeStartElement(QString::fromLatin1("background"));
  (theme->isBackgroundEnabled())
      ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("color"),
                            theme->backgroundColor().name(QColor::HexArgb));
  xmlwriter->writeEndElement();
  xmlwriter->writeStartElement(QString::fromLatin1("light"));
  xmlwriter->writeAttribute(QString::fromLatin1("color"), theme->lightColor().name(QColor::HexArgb));
  xmlwriter->writeAttribute(QString::fromLatin1("strength"),
                            QString::number(theme->lightStrength()));
  xmlwriter->writeAttribute(QString::fromLatin1("ambientstrength"),
                            QString::number(theme->ambientLightStrength()));
  xmlwriter->writeEndElement();
  xmlwriter->writeStartElement(QString::fromLatin1("grid"));
  (theme->isGridEnabled()) ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
                           : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("color"),
                            theme->gridLineColor().name(QColor::HexArgb));
  xmlwriter->writeEndElement();
  xmlwriter->writeStartElement(QString::fromLatin1("label"));
  (theme->isLabelBackgroundEnabled())
      ? xmlwriter->writeAttribute(QString::fromLatin1("backgroundvisible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("backgroundvisible"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(
      QString::fromLatin1("backgroundcolor"), theme->labelBackgroundColor().name(QColor::HexArgb));
  (theme->isLabelBorderEnabled())
      ? xmlwriter->writeAttribute(QString::fromLatin1("bordervisible"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("bordervisible"), QString::fromLatin1("false"));
  xmlwriter->writeFont(theme->font(), theme->labelTextColor());
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
}

void Layout3D::saveValueAxis(XmlStreamWriter *xmlwriter, QValue3DAxis *axis) {
  xmlwriter->writeStartElement(QString::fromLatin1("axis"));
  xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("value"));
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      if (surfacemodifier_->getGraph()->axisX() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("x"));
      else if (surfacemodifier_->getGraph()->axisY() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("y"));
      else if (surfacemodifier_->getGraph()->axisZ() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("z"));
      break;
    case Graph3DCommon::Plot3DType::Bar:
      if (barmodifier_->getGraph()->valueAxis() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("z"));
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      if (scattermodifier_->getGraph()->axisX() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("x"));
      else if (scattermodifier_->getGraph()->axisY() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("y"));
      else if (scattermodifier_->getGraph()->axisZ() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("z"));
      break;
  }
  (axis->isAutoAdjustRange()) ? xmlwriter->writeAttribute(QString::fromLatin1("autorange"), QString::fromLatin1("true"))
                              : xmlwriter->writeAttribute(QString::fromLatin1("autorange"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("from"), QString::number(axis->min()));
  xmlwriter->writeAttribute(QString::fromLatin1("to"), QString::number(axis->max()));
  (axis->reversed()) ? xmlwriter->writeAttribute(QString::fromLatin1("reverse"), QString::fromLatin1("true"))
                     : xmlwriter->writeAttribute(QString::fromLatin1("reverse"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("tickcount"), QString::number(axis->segmentCount()));
  xmlwriter->writeAttribute(QString::fromLatin1("subtickcount"),
                            QString::number(axis->subSegmentCount()));
  xmlwriter->writeAttribute(QString::fromLatin1("ticklabelformat"), axis->labelFormat());
  xmlwriter->writeAttribute(QString::fromLatin1("ticklabelrotation"),
                            QString::number(axis->labelAutoRotation()));
  (axis->isTitleVisible()) ? xmlwriter->writeAttribute(QString::fromLatin1("labelvisible"), QString::fromLatin1("true"))
                           : xmlwriter->writeAttribute(QString::fromLatin1("labelvisible"), QString::fromLatin1("false"));
  (axis->isTitleFixed()) ? xmlwriter->writeAttribute(QString::fromLatin1("labelfixed"), QString::fromLatin1("true"))
                         : xmlwriter->writeAttribute(QString::fromLatin1("labelfixed"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("label"), axis->title());
  xmlwriter->writeEndElement();
}

void Layout3D::saveCategoryAxis(XmlStreamWriter *xmlwriter,
                                QCategory3DAxis *axis) {
  xmlwriter->writeStartElement(QString::fromLatin1("axis"));
  xmlwriter->writeAttribute(QString::fromLatin1("type"), QString::fromLatin1("category"));
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      break;
    case Graph3DCommon::Plot3DType::Bar:
      if (barmodifier_->getGraph()->rowAxis() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("x"));
      else if (barmodifier_->getGraph()->columnAxis() == axis)
        xmlwriter->writeAttribute(QString::fromLatin1("orientation"), QString::fromLatin1("y"));
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      break;
  }
  (axis->isAutoAdjustRange()) ? xmlwriter->writeAttribute(QString::fromLatin1("autorange"), QString::fromLatin1("true"))
                              : xmlwriter->writeAttribute(QString::fromLatin1("autorange"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("from"), QString::number(axis->min()));
  xmlwriter->writeAttribute(QString::fromLatin1("to"), QString::number(axis->max()));
  xmlwriter->writeAttribute(QString::fromLatin1("ticklabelrotation"),
                            QString::number(axis->labelAutoRotation()));
  (axis->isTitleVisible()) ? xmlwriter->writeAttribute(QString::fromLatin1("labelvisible"), QString::fromLatin1("true"))
                           : xmlwriter->writeAttribute(QString::fromLatin1("labelvisible"), QString::fromLatin1("false"));
  (axis->isTitleFixed()) ? xmlwriter->writeAttribute(QString::fromLatin1("labelfixed"), QString::fromLatin1("true"))
                         : xmlwriter->writeAttribute(QString::fromLatin1("labelfixed"), QString::fromLatin1("false"));
  xmlwriter->writeAttribute(QString::fromLatin1("label"), axis->title());
  xmlwriter->writeEndElement();
}

void Layout3D::setCloseWithoutColumnModeLockChange(const bool value) {
  closewithoutcolumnmodelockchange_ = value;
}

QList<MyWidget *> Layout3D::dependentTableMatrix() {
  QList<MyWidget *> dependeon;
  /*switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface: {
      QVector<DataBlockSurface3D *> sdata = surfacemodifier_->getData();
      Q_FOREACH (DataBlockSurface3D *block, sdata) {
        if (block->ismatrix() && block->getmatrix())
          dependeon << block->getmatrix();
        else if (block->istable() && block->gettable())
          dependeon << block->gettable();
      }
    } break;
    case Graph3DCommon::Plot3DType::Bar: {
      QVector<DataBlockBar3D *> sdata = barmodifier_->getData();
      Q_FOREACH (DataBlockBar3D *block, sdata) {
        if (block->ismatrix() && block->getmatrix())
          dependeon << block->getmatrix();
        else if (block->gettable())
          dependeon << block->gettable();
      }
    } break;
    case Graph3DCommon::Plot3DType::Scatter: {
      QVector<DataBlockScatter3D *> sdata = scattermodifier_->getData();
      Q_FOREACH (DataBlockScatter3D *block, sdata) {
        if (block->ismatrix() && block->getmatrix())
          dependeon << block->getmatrix();
        else if (block->gettable())
          dependeon << block->gettable();
      }
    } break;
  }*/
  return dependeon;
}

void Layout3D::copy(Layout3D *layout, QList<Table *> tables,
                    QList<Matrix *> matrixs, Gui::MainWindow* app) {
  std::unique_ptr<QTemporaryFile> file =
      std::unique_ptr<QTemporaryFile>(new QTemporaryFile(QString::fromLatin1("temp")));
  if (!file->open()) {
    qDebug() << "failed to open xml file for writing";
    return;
  }
  std::unique_ptr<XmlStreamWriter> xmlwriter =
      std::unique_ptr<XmlStreamWriter>(new XmlStreamWriter(file.get()));
  xmlwriter->setCodec("UTF-8");
  xmlwriter->setAutoFormatting(false);
  layout->save(xmlwriter.get());
  file->close();
  if (!file->open()) {
    qDebug() << "failed to read xml file for writing";
    return;
  }
  std::unique_ptr<XmlStreamReader> xmlreader =
      std::unique_ptr<XmlStreamReader>(new XmlStreamReader(file.get()));

  QXmlStreamReader::TokenType token;
  while (!xmlreader->atEnd()) {
    token = xmlreader->readNext();
    if (token == QXmlStreamReader::StartElement &&
        xmlreader->name() == QString::fromLatin1("plot3d")) {
      load(xmlreader.get(), tables, matrixs, app, false);
    }
  }
  file->close();
}

QList<Column *> Layout3D::getPlotColumns() {
  QList<Column *> collist;
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      break;
    case Graph3DCommon::Plot3DType::Bar: {
      QVector<DataBlockBar3D *> bvec = barmodifier_->getData();
      Q_FOREACH (DataBlockBar3D *b, bvec) {
        if (b->getxcolumn()) collist << b->getxcolumn();
        if (b->getycolumn()) collist << b->getycolumn();
        if (b->getzcolumn()) collist << b->getzcolumn();
      }
    } break;
    case Graph3DCommon::Plot3DType::Scatter: {
      QVector<DataBlockScatter3D *> svec = scattermodifier_->getData();
      Q_FOREACH (DataBlockScatter3D *s, svec) {
        if (s->getxcolumn()) collist << s->getxcolumn();
        if (s->getycolumn()) collist << s->getycolumn();
        if (s->getzcolumn()) collist << s->getzcolumn();
      }
    } break;
  }
  return collist;
}

void Layout3D::print() {
  std::unique_ptr<QPrinter> printer = std::unique_ptr<QPrinter>(new QPrinter);
  std::unique_ptr<QPrintPreviewDialog> previewDialog =
      std::unique_ptr<QPrintPreviewDialog>(
          new QPrintPreviewDialog(printer.get(), this));
  connect(previewDialog.get(), &QPrintPreviewDialog::paintRequested,
          [=](QPrinter *printer) {
            printer->setColorMode(QPrinter::Color);
            std::unique_ptr<QPainter> painter =
                std::unique_ptr<QPainter>(new QPainter(printer));

            QImage image = QImage();
            QSize size = QSize(main_widget_->width(), main_widget_->height());
            switch (plottype_) {
              case Graph3DCommon::Plot3DType::Surface:
                image = graph3dsurface_->renderToImage(64, size);
                break;
              case Graph3DCommon::Plot3DType::Bar:
                image = graph3dbars_->renderToImage(64, size);
                break;
              case Graph3DCommon::Plot3DType::Scatter:
                image = graph3dscatter_->renderToImage(64, size);
                break;
            }
            // int dpm = 72 / 0.0254;
            // image.setDotsPerMeterX(dpm);
            // image.setDotsPerMeterY(dpm);

            QPointF point = QPointF((printer->pageLayout()
                                         .paintRectPixels(printer->resolution())
                                         .width() /
                                     2) -
                                        (size.width() / 2),
                                    (printer->pageLayout()
                                         .paintRectPixels(printer->resolution())
                                         .height() /
                                     2) -
                                        (size.height() / 2));
            painter->drawImage(point.x(), point.y(), image);
          });
  previewDialog->exec();
}

void Layout3D::copyToClipbord() {
  QImage image = QImage();
  QSize size = QSize(main_widget_->width(), main_widget_->height());
  switch (plottype_) {
    case Graph3DCommon::Plot3DType::Surface:
      image = graph3dsurface_->renderToImage(64, size);
      break;
    case Graph3DCommon::Plot3DType::Bar:
      image = graph3dbars_->renderToImage(64, size);
      break;
    case Graph3DCommon::Plot3DType::Scatter:
      image = graph3dscatter_->renderToImage(64, size);
      break;
  }
  QGuiApplication::clipboard()->setImage(image, QClipboard::Clipboard);
}
