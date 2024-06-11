#include "Precompiled.h"

#include "Surface3D.h"

#include <qmath.h>

#include "DataManager3D.h"
#include "Matrix.h"
#include "Table.h"
#include "future/core/column/Column.h"
#include "future/lib/XmlStreamReader.h"
#include "future/lib/XmlStreamWriter.h"
//#include "MainWindow.h"

//#include "scripting/Script.h"
//#include "scripting/ScriptingEnv.h"

using namespace QtDataVisualization;

Surface3D::Surface3D(Q3DSurface *surface)
    : graph_(surface),
      plotType_(QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe),
      data_(QVector<DataBlockSurface3D *>()),
      counter_(0) {
  graph_->setAxisX(new QValue3DAxis);
  graph_->setAxisY(new QValue3DAxis);
  graph_->setAxisZ(new QValue3DAxis);
}

Surface3D::~Surface3D() {}

void Surface3D::setfunctiondata(
    QList<QPair<QPair<double, double>, double>> *data,
    const Graph3DCommon::Function3DData &funcdata) {
  DataBlockSurface3D *block = new DataBlockSurface3D(data, funcdata);
  graph_->addSeries(block->getdataseries());
  data_ << block;
  block->setgradient(block->getdataseries(), Graph3DCommon::Gradient::BBRY);
  block->getdataseries()->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
  Q_EMIT dataAdded();
}

void Surface3D::setmatrixdatamodel(Matrix *matrix) {
  DataBlockSurface3D *block = new DataBlockSurface3D(matrix);
  graph_->addSeries(block->getdataseries());
  data_ << block;
  block->setgradient(block->getdataseries(), Graph3DCommon::Gradient::BBRY);
  block->getdataseries()->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
  Q_EMIT dataAdded();
}

Q3DSurface *Surface3D::getGraph() const { return graph_; }

QVector<DataBlockSurface3D *> Surface3D::getData() const { return data_; }

void Surface3D::save(XmlStreamWriter *xmlwriter, const bool saveastemplate) {
  xmlwriter->writeStartElement(QString::fromLatin1("surface"));
  xmlwriter->writeAttribute(
      QString::fromLatin1("xrotation"),
      QString::number(graph_->scene()->activeCamera()->xRotation()));
  xmlwriter->writeAttribute(
      QString::fromLatin1("yrotation"),
      QString::number(graph_->scene()->activeCamera()->yRotation()));
  xmlwriter->writeAttribute(
      QString::fromLatin1("zoomlevel"),
      QString::number(graph_->scene()->activeCamera()->zoomLevel()));
  xmlwriter->writeAttribute(QString::fromLatin1("aspectratio"),
                            QString::number(graph_->aspectRatio()));
  xmlwriter->writeAttribute(QString::fromLatin1("horizontalaspectratio"),
                            QString::number(graph_->horizontalAspectRatio()));
  switch (graph_->shadowQuality()) {
    case QAbstract3DGraph::ShadowQuality::ShadowQualityLow:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("low"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualityHigh:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("high"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualityNone:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("none"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualityMedium:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("medium"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualitySoftLow:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("softlow"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualitySoftHigh:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("softhigh"));
      break;
    case QAbstract3DGraph::ShadowQuality::ShadowQualitySoftMedium:
      xmlwriter->writeAttribute(QString::fromLatin1("shadowquality"), QString::fromLatin1("softmedium"));
      break;
  }
  (graph_->flipHorizontalGrid())
      ? xmlwriter->writeAttribute(QString::fromLatin1("fliphorizontalgrid"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("fliphorizontalgrid"), QString::fromLatin1("false"));
  (graph_->isOrthoProjection())
      ? xmlwriter->writeAttribute(QString::fromLatin1("orthoprojection"), QString::fromLatin1("true"))
      : xmlwriter->writeAttribute(QString::fromLatin1("orthoprojection"), QString::fromLatin1("false"));
  (graph_->isPolar()) ? xmlwriter->writeAttribute(QString::fromLatin1("polar"), QString::fromLatin1("true"))
                      : xmlwriter->writeAttribute(QString::fromLatin1("polar"), QString::fromLatin1("false"));
  // graph
  if (!saveastemplate) {
    Q_FOREACH (DataBlockSurface3D *block, data_) {
      xmlwriter->writeStartElement(QString::fromLatin1("plot"));
      // data
      if (block->ismatrix()) {
        xmlwriter->writeAttribute(QString::fromLatin1("data"), QString::fromLatin1("matrix"));
        xmlwriter->writeAttribute(QString::fromLatin1("matrix"), block->getmatrix()->name());
      } else if (block->istable()) {
        xmlwriter->writeAttribute(QString::fromLatin1("data"), QString::fromLatin1("table"));
        xmlwriter->writeAttribute(QString::fromLatin1("table"), block->gettable()->name());
        xmlwriter->writeAttribute(QString::fromLatin1("xcolumn"), block->getxcolumn()->name());
        xmlwriter->writeAttribute(QString::fromLatin1("ycolumn"), block->getycolumn()->name());
        xmlwriter->writeAttribute(QString::fromLatin1("zcolumn"), block->getzcolumn()->name());
      } else {
        xmlwriter->writeAttribute(QString::fromLatin1("data"), QString::fromLatin1("function"));
        xmlwriter->writeAttribute(QString::fromLatin1("function"), block->getfunction());
        xmlwriter->writeAttribute(QString::fromLatin1("xl"), QString::number(block->getxlower()));
        xmlwriter->writeAttribute(QString::fromLatin1("xu"), QString::number(block->getxupper()));
        xmlwriter->writeAttribute(QString::fromLatin1("yl"), QString::number(block->getylower()));
        xmlwriter->writeAttribute(QString::fromLatin1("yu"), QString::number(block->getyupper()));
        xmlwriter->writeAttribute(QString::fromLatin1("zl"), QString::number(block->getzlower()));
        xmlwriter->writeAttribute(QString::fromLatin1("zu"), QString::number(block->getzupper()));
        xmlwriter->writeAttribute(QString::fromLatin1("xpoints"),
                                  QString::number(block->getxpoints()));
        xmlwriter->writeAttribute(QString::fromLatin1("ypoints"),
                                  QString::number(block->getypoints()));
      }
      QSurface3DSeries *series = block->getdataseries();
      (series->isVisible()) ? xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("true"))
                            : xmlwriter->writeAttribute(QString::fromLatin1("visible"), QString::fromLatin1("false"));
      if (series->isFlatShadingEnabled())
        (series->isFlatShadingEnabled())
            ? xmlwriter->writeAttribute(QString::fromLatin1("flatshading"), QString::fromLatin1("true"))
            : xmlwriter->writeAttribute(QString::fromLatin1("flatshading"), QString::fromLatin1("false"));
      switch (series->drawMode()) {
        case QSurface3DSeries::DrawFlag::DrawSurface:
          xmlwriter->writeAttribute(QString::fromLatin1("drawmode"), QString::fromLatin1("surface"));
          break;
        case QSurface3DSeries::DrawFlag::DrawWireframe:
          xmlwriter->writeAttribute(QString::fromLatin1("drawmode"), QString::fromLatin1("wireframe"));
          break;
        case QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe:
          xmlwriter->writeAttribute(QString::fromLatin1("drawmode"), QString::fromLatin1("surfaceandwireframe"));
          break;
      }
      (series->isMeshSmooth())
          ? xmlwriter->writeAttribute(QString::fromLatin1("meshsmooth"), QString::fromLatin1("true"))
          : xmlwriter->writeAttribute(QString::fromLatin1("meshsmooth"), QString::fromLatin1("false"));
      switch (series->colorStyle()) {
        case Q3DTheme::ColorStyle::ColorStyleUniform:
          xmlwriter->writeAttribute(QString::fromLatin1("colorstyle"), QString::fromLatin1("solidcolor"));
          break;
        case Q3DTheme::ColorStyle::ColorStyleRangeGradient:
          xmlwriter->writeAttribute(QString::fromLatin1("colorstyle"), QString::fromLatin1("rangegradient"));
          break;
        case Q3DTheme::ColorStyle::ColorStyleObjectGradient:
          xmlwriter->writeAttribute(QString::fromLatin1("colorstyle"), QString::fromLatin1("objectgradient"));
          break;
      }
      switch (block->getgradient()) {
        case Graph3DCommon::Gradient::Grayscale:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("grayscale"));
          break;
        case Graph3DCommon::Gradient::Hot:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("hot"));
          break;
        case Graph3DCommon::Gradient::Ion:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("ion"));
          break;
        case Graph3DCommon::Gradient::Jet:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("jet"));
          break;
        case Graph3DCommon::Gradient::BBRY:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("bbry"));
          break;
        case Graph3DCommon::Gradient::Cold:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("cold"));
          break;
        case Graph3DCommon::Gradient::GYRD:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("gyrd"));
          break;
        case Graph3DCommon::Gradient::Hues:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("hues"));
          break;
        case Graph3DCommon::Gradient::Candy:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("candy"));
          break;
        case Graph3DCommon::Gradient::Night:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("night"));
          break;
        case Graph3DCommon::Gradient::Polar:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("polar"));
          break;
        case Graph3DCommon::Gradient::Thermal:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("thermal"));
          break;
        case Graph3DCommon::Gradient::Spectrum:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("spectrum"));
          break;
        case Graph3DCommon::Gradient::Geography:
          xmlwriter->writeAttribute(QString::fromLatin1("gradientcolor"), QString::fromLatin1("geography"));
          break;
      }
      xmlwriter->writeAttribute(QString::fromLatin1("solidcolor"),
                                series->baseColor().name(QColor::HexArgb));
      xmlwriter->writeAttribute(
          QString::fromLatin1("highlightcolor"),
          series->singleHighlightColor().name(QColor::HexArgb));
      xmlwriter->writeEndElement();
    }
  }
  xmlwriter->writeEndElement();
}

void Surface3D::load(XmlStreamReader *xmlreader, QList<Table *> tabs,
                     QList<Matrix *> mats, Gui::MainWindow* app) {
  while (!xmlreader->atEnd()) {
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("surface")) break;
    xmlreader->readNext();
    if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("surface")) break;
    if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("surface")) {
      bool ok = false;
      bool xrstatus = false;
      bool yrstatus = false;
      bool zlstatus = false;

      // x rotation
      double xrotation = xmlreader->readAttributeDouble(QString::fromLatin1("xrotation"), &ok);
      if (ok) xrstatus = true;

      // y rotation
      double yrotation = xmlreader->readAttributeDouble(QString::fromLatin1("yrotation"), &ok);
      if (ok) yrstatus = true;

      // zoomlevel
      double zoomlevel = xmlreader->readAttributeDouble(QString::fromLatin1("zoomlevel"), &ok);
      if (ok) zlstatus = true;

      if (xrstatus && yrstatus && zlstatus)
        graph_->scene()->activeCamera()->setCameraPosition(xrotation, yrotation,
                                                           zoomlevel);
      else
        xmlreader->raiseWarning(
            QString::fromLatin1("Surface3D cameraposition property setting error"));

      // aspect ratio
      double aspectratio = xmlreader->readAttributeDouble(QString::fromLatin1("aspectratio"), &ok);
      if (ok)
        graph_->setAspectRatio(aspectratio);
      else
          xmlreader->raiseWarning(
              QString::fromLatin1("Surface3D aspectratio property setting error"));

      // horizontal aspect ratio
      double haspectratio =
          xmlreader->readAttributeDouble(QString::fromLatin1("horizontalaspectratio"), &ok);
      if (ok)
        graph_->setHorizontalAspectRatio(haspectratio);
      else
        xmlreader->raiseWarning(
            QString::fromLatin1("Surface3D horizontal aspectratio property setting error"));

      // shadow quality
      QString shadowquality =
          xmlreader->readAttributeString(QString::fromLatin1("shadowquality"), &ok);
      if (ok) {
        if (shadowquality == QString::fromLatin1("low")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualityLow);
        } else if (shadowquality == QString::fromLatin1("high")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualityHigh);
        } else if (shadowquality == QString::fromLatin1("none")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualityNone);
        } else if (shadowquality == QString::fromLatin1("medium")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualityMedium);
        } else if (shadowquality == QString::fromLatin1("softlow")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualitySoftLow);
        } else if (shadowquality == QString::fromLatin1("softhigh")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualitySoftHigh);
        } else if (shadowquality == QString::fromLatin1("softmedium")) {
          graph_->setShadowQuality(
              QAbstract3DGraph::ShadowQuality::ShadowQualitySoftMedium);
        }
      } else
        xmlreader->raiseWarning(
            QString::fromLatin1("Surface3D shadow quality property setting error"));

      // flip horizontal grid
      bool fliphgrid = xmlreader->readAttributeBool(QString::fromLatin1("fliphorizontalgrid"), &ok);
      if (ok)
        graph_->setFlipHorizontalGrid(fliphgrid);
      else
        xmlreader->raiseWarning(
            QString::fromLatin1("Surface3D flip horizontal grid property setting error"));

      // ortho projection
      bool orthoproj = xmlreader->readAttributeBool(QString::fromLatin1("orthoprojection"), &ok);
      if (ok)
        graph_->setOrthoProjection(orthoproj);
      else
        xmlreader->raiseWarning(
            QString::fromLatin1("Surface3D ortho projection property setting error"));

      // flip horizontal grid
      bool polar = xmlreader->readAttributeBool(QString::fromLatin1("polar"), &ok);
      if (ok)
        graph_->setPolar(polar);
      else
          xmlreader->raiseWarning(QString::fromLatin1("Surface3D polar property setting error"));

      counter_ = 0;
      loadplot(xmlreader, tabs, mats, app);
    }
  }
}

void Surface3D::loadplot(XmlStreamReader *xmlreader, QList<Table *> tabs,
                         QList<Matrix *> mats, Gui::MainWindow* app) {
  //while (!xmlreader->atEnd()) {
  //  if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("plot")) break;
  //  xmlreader->readNext();
  //  if (xmlreader->isEndElement() && xmlreader->name() == QString::fromLatin1("plot")) break;
  //  bool ok = false;
  //  // data
  //  QString data = xmlreader->readAttributeString(QString::fromLatin1("data"), &ok);
  //  if (!ok)
  //      xmlreader->raiseError(QString::fromLatin1("Surface3D data property setting error"));

  //  bool loadseries = false;
  //  // matrix data
  //  if (data == QString::fromLatin1("matrix")) {
  //    Matrix *matrix = nullptr;
  //    QString matname = xmlreader->readAttributeString(QString::fromLatin1("matrix"), &ok);
  //    if (ok) {
  //      matrix = getMatrixByName(mats, matname);
  //    } else
  //      xmlreader->raiseError(tr("Surface3D Matrix not found error"));
  //    if (matrix) {
  //      setmatrixdatamodel(matrix);
  //      loadseries = true;
  //    }
  //    // Table data
  //  } else if (data == QString::fromLatin1("table")) {
  //    Table *table = nullptr;
  //    Column *xcolumn = nullptr;
  //    Column *ycolumn = nullptr;
  //    Column *zcolumn = nullptr;
  //    QString tablename = xmlreader->readAttributeString(QString::fromLatin1("table"), &ok);
  //    if (ok) {
  //      table = getTableByName(tabs, tablename);
  //    } else
  //      xmlreader->raiseError(tr("Surface3D Table not found error"));
  //    QString xcolname = xmlreader->readAttributeString(QString::fromLatin1("xcolumn"), &ok);
  //    if (ok) {
  //      (table) ? xcolumn = table->column(xcolname) : xcolumn = nullptr;
  //    } else
  //      xmlreader->raiseWarning(tr("Surface3D Table X column not found error"));
  //    QString ycolname = xmlreader->readAttributeString(QString::fromLatin1("ycolumn"), &ok);
  //    if (ok) {
  //      (table) ? ycolumn = table->column(ycolname) : ycolumn = nullptr;
  //    } else
  //      xmlreader->raiseWarning(tr("Surface3D Table Y column not found error"));
  //    QString zcolname = xmlreader->readAttributeString(QString::fromLatin1("zcolumn"), &ok);
  //    if (ok) {
  //      (table) ? zcolumn = table->column(zcolname) : zcolumn = nullptr;
  //    } else
  //      xmlreader->raiseWarning(tr("Surface3D Table Z column not found error"));
  //    if (table && xcolumn && ycolumn && zcolumn) {
  //      qDebug() << "table is not a valid data structure for Surface3D";
  //      loadseries = false;
  //    }
  //  } else if (data == QString::fromLatin1("function")) {
  //    bool funcstatus = false;
  //    bool xlstatus = false;
  //    bool xustatus = false;
  //    bool ylstatus = false;
  //    bool yustatus = false;
  //    bool zlstatus = false;
  //    bool zustatus = false;
  //    bool xpointstatus = false;
  //    bool ypointstatus = false;

  //    // function
  //    QString func = xmlreader->readAttributeString(QString::fromLatin1("function"), &ok);
  //    if (ok)
  //      funcstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D function not found error"));

  //    // xl
  //    double xl = xmlreader->readAttributeDouble(QString::fromLatin1("xl"), &ok);
  //    if (ok)
  //      xlstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D xl not found error"));

  //    // xu
  //    double xu = xmlreader->readAttributeDouble(QString::fromLatin1("xu"), &ok);
  //    if (ok)
  //      xustatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D xu not found error"));

  //    // yl
  //    double yl = xmlreader->readAttributeDouble(QString::fromLatin1("yl"), &ok);
  //    if (ok)
  //      ylstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D yl not found error"));

  //    // yu
  //    double yu = xmlreader->readAttributeDouble(QString::fromLatin1("yu"), &ok);
  //    if (ok)
  //      yustatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D yu not found error"));

  //    // zl
  //    double zl = xmlreader->readAttributeDouble(QString::fromLatin1("zl"), &ok);
  //    if (ok)
  //      zlstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D zl not found error"));

  //    // zu
  //    double zu = xmlreader->readAttributeDouble(QString::fromLatin1("zu"), &ok);
  //    if (ok)
  //      zustatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D zu not found error"));

  //    // xpoints
  //    int xpoints = xmlreader->readAttributeInt(QString::fromLatin1("xpoints"), &ok);
  //    if (ok)
  //      xpointstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D xpoints not found error"));

  //    // ypoints
  //    int ypoints = xmlreader->readAttributeInt(QString::fromLatin1("ypoints"), &ok);
  //    if (ok)
  //      ypointstatus = true;
  //    else
  //      xmlreader->raiseWarning(tr("Surface3D ypoints not found error"));
  //    if (funcstatus && xlstatus && xustatus && ylstatus && yustatus &&
  //        zlstatus && zustatus && xpointstatus && ypointstatus) {
  //      Graph3DCommon::Function3DData funcdata;
  //      funcdata.function = func;
  //      funcdata.xl = xl;
  //      funcdata.xu = xu;
  //      funcdata.yl = yl;
  //      funcdata.yu = yu;
  //      funcdata.zl = zl;
  //      funcdata.zu = zu;
  //      funcdata.xpoints = xpoints;
  //      funcdata.ypoints = ypoints;
  //      setfunctiondata(app->generateFunction3ddata(funcdata), funcdata);

  //      loadseries = true;
  //    }
  //  }

  //  if (loadseries) {
  //    // visible
  //    QSurface3DSeries *series = data_.at(counter_)->getdataseries();
  //    bool vis = xmlreader->readAttributeBool(QString::fromLatin1("visible"), &ok);
  //    (ok) ? series->setVisible(vis)
  //         : xmlreader->raiseWarning(
  //               QString::fromLatin1("Surface3D visible series property setting error"));

  //    // flatshade
  //    bool flatshade = xmlreader->readAttributeDouble(QString::fromLatin1("flatshading"), &ok);
  //    (ok) ? series->setFlatShadingEnabled(flatshade)
  //         : xmlreader->raiseWarning(
  //               QString::fromLatin1("Surface3D series flatshading property setting error"));

  //    // draw mode
  //    QString dmode = xmlreader->readAttributeString(QString::fromLatin1("drawmode"), &ok);
  //    if (ok) {
  //      if (dmode == QString::fromLatin1("surface"))
  //        series->setDrawMode(QSurface3DSeries::DrawFlag::DrawSurface);
  //      else if (dmode == QString::fromLatin1("wireframe"))
  //        series->setDrawMode(QSurface3DSeries::DrawFlag::DrawWireframe);
  //      else if (dmode == QString::fromLatin1("surfaceandwireframe"))
  //        series->setDrawMode(
  //            QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe);
  //    } else
  //      xmlreader->raiseWarning(
  //          QString::fromLatin1("Surface3D drawmode series property setting error"));

  //    // smooth
  //    bool smooth = xmlreader->readAttributeBool(QString::fromLatin1("meshsmooth"), &ok);
  //    (ok) ? series->setMeshSmooth(smooth)
  //         : xmlreader->raiseWarning(
  //               QString::fromLatin1("Surface3D meshsmooth series property setting error"));

  //    // color style
  //    QString colorstyle = xmlreader->readAttributeString(QString::fromLatin1("colorstyle"), &ok);
  //    if (ok) {
  //      if (colorstyle == QString::fromLatin1("solidcolor"))
  //        series->setColorStyle(Q3DTheme::ColorStyle::ColorStyleUniform);
  //      else if (colorstyle == QString::fromLatin1("rangegradient"))
  //        series->setColorStyle(Q3DTheme::ColorStyle::ColorStyleRangeGradient);
  //      else if (colorstyle == QString::fromLatin1("objectgradient"))
  //        series->setColorStyle(Q3DTheme::ColorStyle::ColorStyleObjectGradient);
  //    } else
  //      xmlreader->raiseWarning(
  //          QString::fromLatin1("Surface3D colorstyle series property setting error"));

  //    // gradient
  //    QString gradient = xmlreader->readAttributeString(QString::fromLatin1("gradientcolor"), &ok);
  //    if (ok) {
  //      if (gradient == QString::fromLatin1("grayscale"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Grayscale);
  //      else if (gradient == QString::fromLatin1("hot"))
  //        data_.at(counter_)->setgradient(series, Graph3DCommon::Gradient::Hot);
  //      else if (gradient == QString::fromLatin1("ion"))
  //        data_.at(counter_)->setgradient(series, Graph3DCommon::Gradient::Ion);
  //      else if (gradient == QString::fromLatin1("jet"))
  //        data_.at(counter_)->setgradient(series, Graph3DCommon::Gradient::Jet);
  //      else if (gradient == QString::fromLatin1("bbry"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::BBRY);
  //      else if (gradient == QString::fromLatin1("cold"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Cold);
  //      else if (gradient == QString::fromLatin1("gyrd"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::GYRD);
  //      else if (gradient == QString::fromLatin1("hues"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Hues);
  //      else if (gradient == QString::fromLatin1("candy"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Candy);
  //      else if (gradient == QString::fromLatin1("night"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Night);
  //      else if (gradient == QString::fromLatin1("polar"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Polar);
  //      else if (gradient == QString::fromLatin1("thermal"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Thermal);
  //      else if (gradient == QString::fromLatin1("spectrum"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Spectrum);
  //      else if (gradient == QString::fromLatin1("geography"))
  //        data_.at(counter_)->setgradient(series,
  //                                        Graph3DCommon::Gradient::Geography);
  //    } else
  //      xmlreader->raiseWarning(
  //          QString::fromLatin1("Surface3D gradient color series property setting error"));

  //    // Solid Color
  //    QString solidcolor = xmlreader->readAttributeString(QString::fromLatin1("solidcolor"), &ok);
  //    (ok) ? series->setBaseColor(QColor(solidcolor))
  //         : xmlreader->raiseWarning(
  //               QString::fromLatin1("Surface3D series solid color property setting error"));

  //    // Highlight Color
  //    QString hcolor = xmlreader->readAttributeString(QString::fromLatin1("highlightcolor"), &ok);
  //    (ok) ? series->setSingleHighlightColor(QColor(hcolor))
  //         : xmlreader->raiseWarning(
  //               QString::fromLatin1("Surface3D series highlight color property setting error"));
  //  }
  //}
  //xmlreader->readNext();
  //if (xmlreader->isStartElement() && xmlreader->name() == QString::fromLatin1("plot")) {
  //  loadplot(xmlreader, tabs, mats, app);
  //  counter_++;
  //}//koffa the way
}

Table *Surface3D::getTableByName(QList<Table *> tabs, const QString name) {
  Table *table = nullptr;
  Q_FOREACH (Table *tab, tabs) {
    if (tab->name() == name) table = tab;
  }
  return table;
}

Matrix *Surface3D::getMatrixByName(QList<Matrix *> mats, const QString name) {
  Matrix *matrix = nullptr;
  Q_FOREACH (Matrix *mat, mats) {
    if (mat->name() == name) matrix = mat;
  }
  return matrix;
}

void Surface3D::setSurfaceMeshType(const QSurface3DSeries::DrawFlag &type) {
  if (graph_->seriesList().isEmpty()) return;
  plotType_ = type;
  Q_FOREACH (QSurface3DSeries *series, graph_->seriesList()) {
    series->setDrawMode(type);
  }
}

void Surface3D::setSurfaceMeshType(const QSurface3DSeries::DrawFlag &type,
                                   QSurface3DSeries *series) {
  series->setDrawMode(type);
}

QtDataVisualization::QSurface3DSeries::DrawFlag Surface3D::getSurfaceMeshType(
    QSurface3DSeries *series) const {
  if (series->drawMode().testFlag(QSurface3DSeries::DrawFlag::DrawSurface))
    return QSurface3DSeries::DrawFlag::DrawSurface;
  else if (series->drawMode().testFlag(
               QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe))
    return QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe;
  else if (series->drawMode().testFlag(
               QSurface3DSeries::DrawFlag::DrawWireframe))
    return QSurface3DSeries::DrawFlag::DrawWireframe;
  else
    return QSurface3DSeries::DrawFlag::DrawSurfaceAndWireframe;
}
