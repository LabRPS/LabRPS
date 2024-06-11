#ifndef PLOTCOLUMNS_H
#define PLOTCOLUMNS_H
#include <QList>

#include "Libraries/Alphaplot/2Dplot/AxisRect2D.h"
#include "Libraries/Alphaplot/2Dplot/Bar2D.h"
#include "Libraries/Alphaplot/2Dplot/Curve2D.h"
#include "Libraries/Alphaplot/2Dplot/LineSpecial2D.h"
#include "Libraries/Alphaplot/2Dplot/DataManager2D.h"
#include "Libraries/Alphaplot/Table.h"
#include "Libraries/Alphaplot/future/core/column/Column.h"
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


namespace PlotColumns {
static QList<PlotData::AssociatedData *> plottedcolumns(AxisRect2D *axisrect) {
  QList<PlotData::AssociatedData *> associateddata;

  QVector<LineSpecial2D *> lslist = axisrect->getLsVec();
  QVector<Curve2D *> curvelist = axisrect->getCurveVec();
  QVector<Bar2D *> barlist = axisrect->getBarVec();
  Q_FOREACH (LineSpecial2D *ls, lslist) {
    PlotData::AssociatedData *data =
        ls->getdatablock_lsplot()->getassociateddata();
    associateddata << data;
  }
  Q_FOREACH (Curve2D *curve, curvelist) {
    if (curve->getplottype_cplot() == Graph2DCommon::PlotType::Associated) {
      PlotData::AssociatedData *data =
          curve->getdatablock_cplot()->getassociateddata();
      associateddata << data;
    }
  }

  Q_FOREACH (Bar2D *bar, barlist) {
    if (!bar->ishistogram_barplot()) {
      PlotData::AssociatedData *data =
          bar->getdatablock_barplot()->getassociateddata();
      associateddata << data;
    }
  }
  return associateddata;
}

static PlotData::AssociatedData *getassociateddatafromstring(
    AxisRect2D *axisrect, const QString string) {
  PlotData::AssociatedData *data = nullptr;
  if (!axisrect) return data;

  QList<PlotData::AssociatedData *> list =
      PlotColumns::plottedcolumns(axisrect);

  Q_FOREACH (PlotData::AssociatedData *associateddata, list) {
    if (associateddata->table->name() + QString::fromLatin1("_") + associateddata->xcol->name() +
            QString::fromLatin1("_") + associateddata->ycol->name() ==
        string)
      data = associateddata;
  }
  return data;
}

static QStringList getstringlistfromassociateddata(AxisRect2D *axisrect) {
  QStringList namelist;
  if (!axisrect) return namelist;
  QList<PlotData::AssociatedData *> list =
      PlotColumns::plottedcolumns(axisrect);

  Q_FOREACH (PlotData::AssociatedData *associateddata, list) {
    namelist << associateddata->table->name() + QString::fromLatin1("_") +
                    associateddata->xcol->name() + QString::fromLatin1("_") +
                    associateddata->ycol->name();
  }
  return namelist;
}

static QString getstringfromassociateddata(
    PlotData::AssociatedData *associateddata) {
  return associateddata->table->name() + QString::fromLatin1("_") + associateddata->xcol->name() +
         QString::fromLatin1("_") + associateddata->ycol->name();
  ;
}

}  // namespace PlotColumns

#endif  // PLOTCOLUMNS_H
