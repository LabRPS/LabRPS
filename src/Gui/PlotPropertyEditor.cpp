/* This file is part of AlphaPlot.
   Copyright 2016, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   AlphaPlot is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   AlphaPlot is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with AlphaPlot.  If not, see <http://www.gnu.org/licenses/>.

   Description : PlotPropertyEditor */
#include "PreCompiled.h"
#include "PlotPropertyEditor.h"

#include <QDebug>
#include <QSplitter>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QtDataVisualization/QBar3DSeries>
#include <QtDataVisualization/QScatter3DSeries>
#include <QtDataVisualization/QSurface3DSeries>
#include <limits>
#include <Q3DScatter>

#include <Libraries/Alphaplot/2Dplot/Axis2D.h>
#include <Libraries/Alphaplot/2Dplot/TextItem2D.h>
#include <Libraries/QtPropertyBrowser/src/qteditorfactory.h>
#include <Libraries/QtPropertyBrowser/src/qtpropertymanager.h>
#include <Libraries/QtPropertyBrowser/src/qttreepropertybrowser.h>
#include <Libraries/Alphaplot/2Dplot/Bar2D.h>
#include <Libraries/Alphaplot/2Dplot/ColorMap2D.h>
#include <Libraries/Alphaplot/2Dplot/StatBox2D.h>
#include <Libraries/Alphaplot/2Dplot/Curve2D.h>
#include <Libraries/Alphaplot/2Dplot/DataManager2D.h>
#include <Libraries/Alphaplot/2Dplot/ErrorBar2D.h>
#include <Libraries/Alphaplot/2Dplot/Grid2D.h>
#include <Libraries/Alphaplot/2Dplot/ImageItem2D.h>
#include <Libraries/Alphaplot/2Dplot/Layout2D.h>
#include <Libraries/Alphaplot/2Dplot/LayoutGrid2D.h>
#include <Libraries/Alphaplot/2Dplot/Legend2D.h>
#include <Libraries/Alphaplot/2Dplot/LineItem2D.h>
#include <Libraries/Alphaplot/2Dplot/LineSpecial2D.h>
#include <Libraries/Alphaplot/2Dplot/Pie2D.h>
#include <Libraries/Alphaplot/2Dplot/Plot2D.h>
#include <Libraries/Alphaplot/3Dplot/Bar3D.h>
#include <Libraries/Alphaplot/3Dplot/DataManager3D.h>
#include <Libraries/Alphaplot/3Dplot/Layout3D.h>
#include <Libraries/Alphaplot/3Dplot/Scatter3D.h>
#include <Libraries/Alphaplot/3Dplot/Surface3D.h>
#include <Libraries/Alphaplot/MyWidget.h>
//#include <Libraries/Alphaplot/Note.h>
//#include <Gui/Table.h>
//#include <Libraries/Alphaplot/Gui/Matrix.h>
#include  <Libraries/Alphaplot/core/IconLoader.h>
#include <Libraries/Alphaplot/core/Utilities.h>
#include <Libraries/Alphaplot/future/core/column/Column.h>
#include <Libraries/Alphaplot/future/matrix/MatrixView.h>
#include <Libraries/Alphaplot/2Dplot/Graph2DCommon.h>
#include <Libraries/Alphaplot/3Dplot/Graph3DCommon.h>
#include "MainWindow.h"
#include "qcustomplot.h"

using namespace QtDataVisualization;
//using namespace Gui;

PlotPropertyEditor::PlotPropertyEditor(QWidget *parent, Gui::MainAlphaPlot *app)
     : QWidget(parent), app_(app)
    //, splitter_(new QSplitter(Qt::Vertical, this)),
    //  objectbrowser_(new MyPlotTreeWidget(splitter_)),
    //  propertybrowser_(new QtTreePropertyBrowser(splitter_)),
    //  objectitems_(QList<QTreeWidgetItem *>()),
    //  previouswidget_(nullptr),
    //  // property browser Items
    //  groupManager_(new QtGroupPropertyManager(propertybrowser_)),
    //  boolManager_(new QtBoolPropertyManager(propertybrowser_)),
    //  intManager_(new QtIntPropertyManager(propertybrowser_)),
    //  doubleManager_(new QtDoublePropertyManager(propertybrowser_)),
    //  stringManager_(new QtStringPropertyManager(propertybrowser_)),
    //  sizeManager_(new QtSizePropertyManager(propertybrowser_)),
    //  rectManager_(new QtRectPropertyManager(propertybrowser_)),
    //  enumManager_(new QtEnumPropertyManager(propertybrowser_)),
    //  colorManager_(new QtColorPropertyManager(propertybrowser_)),
    //  fontManager_(new QtFontPropertyManager(propertybrowser_)),
    //  datetimeManager_(new QtDateTimePropertyManager(propertybrowser_)),
    //  // Property Widget factory
    //  checkBoxFactory_(new QtCheckBoxFactory(propertybrowser_)),
    //  spinBoxFactory_(new QtSpinBoxFactory(propertybrowser_)),
    //  doubleSpinBoxFactory_(new QtDoubleSpinBoxFactory(propertybrowser_)),
    //  lineEditFactory_(new QtLineEditFactory(propertybrowser_)),
    //  comboBoxFactory_(new QtEnumEditorFactory(propertybrowser_)),
    //  colorFactory_(new QtColorEditorFactory(propertybrowser_)),
    //  fontFactory_(new QtFontEditorFactory(propertybrowser_)),
    //  datetimeFactory_(new QtDateTimeEditFactory(propertybrowser_))
{
    dockWidgetContents = new QWidget(this);
    propEditorGridLayout = new QGridLayout(this);

    splitter_ = (new QSplitter(Qt::Vertical, dockWidgetContents));
    objectbrowser_ = (new MyPlotTreeWidget(splitter_));
    propertybrowser_ = (new QtTreePropertyBrowser(splitter_));
    objectitems_ = (QList<QTreeWidgetItem*>());

    previouswidget_ = (nullptr);
    // property browser Items
    groupManager_ = (new QtGroupPropertyManager(propertybrowser_));
    boolManager_ = (new QtBoolPropertyManager(propertybrowser_));
    intManager_ = (new QtIntPropertyManager(propertybrowser_));
    doubleManager_ = (new QtDoublePropertyManager(propertybrowser_));
    stringManager_ = (new QtStringPropertyManager(propertybrowser_));
    sizeManager_ = (new QtSizePropertyManager(propertybrowser_));
    rectManager_ = (new QtRectPropertyManager(propertybrowser_));
    enumManager_ = (new QtEnumPropertyManager(propertybrowser_));
    colorManager_ = (new QtColorPropertyManager(propertybrowser_));
    fontManager_ = (new QtFontPropertyManager(propertybrowser_));
    datetimeManager_ = (new QtDateTimePropertyManager(propertybrowser_));
    // Property Widget factory
    checkBoxFactory_ = (new QtCheckBoxFactory(propertybrowser_));
    spinBoxFactory_ = (new QtSpinBoxFactory(propertybrowser_));
    doubleSpinBoxFactory_ = (new QtDoubleSpinBoxFactory(propertybrowser_));
    lineEditFactory_ = (new QtLineEditFactory(propertybrowser_));
    comboBoxFactory_ = (new QtEnumEditorFactory(propertybrowser_));
    colorFactory_ = (new QtColorEditorFactory(propertybrowser_));
    fontFactory_ = (new QtFontEditorFactory(propertybrowser_));
    datetimeFactory_ = (new QtDateTimeEditFactory(propertybrowser_));
    propEditorGridLayout->addWidget(splitter_, 0, 0, 1, 1);

  Q_ASSERT(app_);
  setWindowIcon(QIcon());
  objectbrowser_->setColumnCount(1);

  objectbrowser_->setFrameShape(QFrame::NoFrame);
  objectbrowser_->setSelectionMode(QAbstractItemView::SingleSelection);
  splitter_->addWidget(objectbrowser_);
  splitter_->addWidget(propertybrowser_);
  //setWidget(splitter_);
  propertybrowser_->setFocusPolicy(Qt::NoFocus);

  // Pen stle enum
  QStringList axistypelist;
  axistypelist << tr("Linear") << tr("Logarithmic");
  QStringList stroketypelist;
  stroketypelist << tr("Solid Line") << tr("Dash Line") << tr("Dot Line")
                 << tr("Dash Dot Line") << tr("Dash Dot Dot Line");
  QStringList fillstylelist;
  fillstylelist << tr("Solid Color") << tr("Dense Point 1")
                << tr("Dense Point 2") << tr("Dense Point 3")
                << tr("Dense Point 4") << tr("Dense Point 5")
                << tr("Dense Point 6") << tr("Dense Point 7") << tr("Hor Line")
                << tr("Ver Line") << tr("Cross Line") << tr("B Diag Line")
                << tr("F Diag Line") << tr("Diag Cross Line");
  QMap<int, QIcon> fillstyleiconslist;
  fillstyleiconslist[0] = QIcon(QString::fromLatin1(":/icons/common/16/edit-solid-pattern.png"));
  fillstyleiconslist[1] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense1-pattern.png"));
  fillstyleiconslist[2] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense2-pattern.png"));
  fillstyleiconslist[3] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense3-pattern.png"));
  fillstyleiconslist[4] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense4-pattern.png"));
  fillstyleiconslist[5] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense5-pattern.png"));
  fillstyleiconslist[6] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense6-pattern.png"));
  fillstyleiconslist[7] = QIcon(QString::fromLatin1(":/icons/common/16/edit-dense7-pattern.png"));
  fillstyleiconslist[8] = QIcon(QString::fromLatin1(":/icons/common/16/edit-hor-pattern.png"));
  fillstyleiconslist[9] = QIcon(QString::fromLatin1(":/icons/common/16/edit-ver-pattern.png"));
  fillstyleiconslist[10] = QIcon(QString::fromLatin1(":/icons/common/16/edit-cross-pattern.png"));
  fillstyleiconslist[11] = QIcon(QString::fromLatin1(":/icons/common/16/edit-bdiag-pattern.png"));
  fillstyleiconslist[12] = QIcon(QString::fromLatin1(":/icons/common/16/edit-fdiag-pattern.png"));
  fillstyleiconslist[13] =
      QIcon(QString::fromLatin1(":/icons/common/16/edit-diagcross-pattern.png"));
  QStringList axislabelsidelist;
  axislabelsidelist << tr("Down") << tr("Up");
  QMap<int, QIcon> stroketypeiconslist;
  stroketypeiconslist[0] = QIcon(QString::fromLatin1(":/icons/common/16/edit-style-solidline.png"));
  stroketypeiconslist[1] = QIcon(QString::fromLatin1(":/icons/common/16/edit-style-dashline.png"));
  stroketypeiconslist[2] = QIcon(QString::fromLatin1(":/icons/common/16/edit-style-dotline.png"));
  stroketypeiconslist[3] =
      QIcon(QString::fromLatin1(":/icons/common/16/edit-style-dashdotline.png"));
  stroketypeiconslist[4] =
      QIcon(QString::fromLatin1(":/icons/common/16/edit-style-dashdotdotline.png"));
  QStringList formatlist;
  formatlist << QString::fromLatin1("Scientific: 1.250e+01")
             << QString::fromLatin1("Scientific: 1.250.10^-1")
             << QString::fromLatin1("Scientific: 1.250x10^-1")
             << QString::fromLatin1("Scientific: 1.250E+01")
             << QString::fromLatin1("Decimal: 12.500")
             << QString::fromLatin1("Automatic(g)")
             << QString::fromLatin1("Automatic(gb)")
             << QString::fromLatin1("Automatic(gbc)")
             << QString::fromLatin1("Automatic(G)");
  QStringList endingstylelist;
  endingstylelist << tr("None") << tr("Flat Arrow") << tr("Spike Arrow")
                  << tr("Line Arrow") << tr("Disc") << tr("Square")
                  << tr("Diamond") << tr("Bar") << tr("Half Bar")
                  << tr("Skewed Bar");
  QStringList tickstepstrategy;
  tickstepstrategy << tr("Readability") << tr("Meet Tick Count");
  QStringList tickervaluescalestrategy;
  tickervaluescalestrategy << tr("None") << tr("Multiples") << tr("Powers");
  QStringList tickersymbolfractionstyle;
  tickersymbolfractionstyle << tr("Floating Point") << tr("Ascii Fractions")
                            << tr("Unicode Fractions");
  // Property browser set up appropriate widget factory
  propertybrowser_->setFactoryForManager(boolManager_, checkBoxFactory_);
  propertybrowser_->setFactoryForManager(intManager_, spinBoxFactory_);
  propertybrowser_->setFactoryForManager(doubleManager_, doubleSpinBoxFactory_);
  propertybrowser_->setFactoryForManager(stringManager_, lineEditFactory_);
  propertybrowser_->setFactoryForManager(sizeManager_->subIntPropertyManager(),
                                         spinBoxFactory_);
  propertybrowser_->setFactoryForManager(rectManager_->subIntPropertyManager(),
                                         spinBoxFactory_);
  propertybrowser_->setFactoryForManager(enumManager_, comboBoxFactory_);
  propertybrowser_->setFactoryForManager(colorManager_, colorFactory_);
  propertybrowser_->setFactoryForManager(fontManager_, fontFactory_);
  propertybrowser_->setFactoryForManager(datetimeManager_, datetimeFactory_);

  // MyWidget window Properties
  mywidgetwindowrectitem_ = rectManager_->addProperty(tr("Geometry"));
  mywidgetwindownameitem_ = stringManager_->addProperty(tr("Name"));
  mywidgetwindowlabelitem_ = stringManager_->addProperty(tr("Label"));
  stringManager_->setRegExp(mywidgetwindownameitem_,
                            QRegExp(QString::fromLatin1("^[a-zA-Z0-9-]*$")));

  // Plot Canvas properties
  canvaspropertycoloritem_ = colorManager_->addProperty(tr("Background Color"));
  canvaspropertybufferdevicepixelratioitem_ =
      doubleManager_->addProperty(tr("Device Pixel Ratio"));
  canvaspropertyopenglitem_ = boolManager_->addProperty(QString::fromLatin1("OpenGL"));
  canvaspropertysizeitem_ = sizeManager_->addProperty(tr("Plot Dimension"));
  canvaspropertyrowsapcingitem_ = intManager_->addProperty(tr("Row Spacing"));
  canvaspropertycolumnsapcingitem_ =
      intManager_->addProperty(tr("Column Spacing"));
  intManager_->setMinimum(canvaspropertyrowsapcingitem_, 0);
  intManager_->setMinimum(canvaspropertycolumnsapcingitem_, 0);

  // Layout Properties
  layoutpropertymargingroupitem_ = groupManager_->addProperty(tr("Margin"));
  layoutpropertyrectitem_ = rectManager_->addProperty(tr("Outer Rect"));
  layoutpropertycoloritem_ = colorManager_->addProperty(tr("Background Color"));
  layoutpropertyfillstyleitem_ = enumManager_->addProperty(tr("Fill Style"));
  enumManager_->setEnumNames(layoutpropertyfillstyleitem_, fillstylelist);
  enumManager_->setEnumIcons(layoutpropertyfillstyleitem_, fillstyleiconslist);
  layoutpropertyrectitem_->setEnabled(false);
  layoutpropertyautomarginstatusitem_ = boolManager_->addProperty(tr("Auto"));
  layoutpropertyleftmarginitem_ = intManager_->addProperty(tr("Left"));
  layoutpropertyrightmarginitem_ = intManager_->addProperty(tr("Right"));
  layoutpropertytopmarginitem_ = intManager_->addProperty(tr("Top"));
  layoutpropertybottommarginitem_ = intManager_->addProperty(tr("Bottom"));
  layoutpropertymargingroupitem_->addSubProperty(
      layoutpropertyautomarginstatusitem_);
  layoutpropertymargingroupitem_->addSubProperty(layoutpropertyleftmarginitem_);
  layoutpropertymargingroupitem_->addSubProperty(
      layoutpropertyrightmarginitem_);
  layoutpropertymargingroupitem_->addSubProperty(layoutpropertytopmarginitem_);
  layoutpropertymargingroupitem_->addSubProperty(
      layoutpropertybottommarginitem_);
  layoutpropertyrowstreachfactoritem_ =
      doubleManager_->addProperty(tr("Row Stretch Factor"));
  layoutpropertycolumnstreachfactoritem_ =
      doubleManager_->addProperty(tr("Column Stretch Factor"));
  doubleManager_->setMinimum(layoutpropertyrowstreachfactoritem_, 0.0);
  doubleManager_->setMinimum(layoutpropertycolumnstreachfactoritem_, 0.0);
  // Axis Properties
  axispropertyvisibleitem_ = boolManager_->addProperty(tr("Visible"));
  axispropertyoffsetitem_ = intManager_->addProperty(tr("Offset"));
  axispropertyfromitem_ = doubleManager_->addProperty(tr("From"));
  axispropertytoitem_ = doubleManager_->addProperty(tr("To"));
  // setmaximum double limits
  doubleManager_->setMaximum(axispropertyfromitem_,
                             std::numeric_limits<double>::max());
  doubleManager_->setMinimum(axispropertyfromitem_,
                             -std::numeric_limits<double>::max());
  doubleManager_->setMaximum(axispropertytoitem_,
                             std::numeric_limits<double>::max());
  doubleManager_->setMinimum(axispropertytoitem_,
                             -std::numeric_limits<double>::max());
  axispropertyupperendingstyleitem_ =
      enumManager_->addProperty(tr("Upper Ending"));
  enumManager_->setEnumNames(axispropertyupperendingstyleitem_,
                             endingstylelist);
  axispropertylowerendingstyleitem_ =
      enumManager_->addProperty(tr("Lower Ending"));
  enumManager_->setEnumNames(axispropertylowerendingstyleitem_,
                             endingstylelist);
  axispropertylinlogitem_ = enumManager_->addProperty(tr("Type"));
  enumManager_->setEnumNames(axispropertylinlogitem_, axistypelist);
  axispropertyinvertitem_ = boolManager_->addProperty(tr("Inverted"));
  axispropertystrokecoloritem_ = colorManager_->addProperty(tr("Stroke Color"));
  axispropertystrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  axispropertystroketypeitem_ = enumManager_->addProperty(tr("Stroke Type"));
  enumManager_->setEnumNames(axispropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(axispropertystroketypeitem_, stroketypeiconslist);
  axispropertyantialiaseditem_ = boolManager_->addProperty(QString::fromLatin1("Antialiased"));
  axispropertylabeltextitem_ = stringManager_->addProperty(tr("Label Text"));
  axispropertylabelfontitem_ = fontManager_->addProperty(QString::fromLatin1("Label Font"));
  axispropertylabelcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Label Color"));
  axispropertylabelpaddingitem_ = intManager_->addProperty(QString::fromLatin1("Label Padding"));
  // Axis Properties Ticks sub block
  axispropertytickvisibilityitem_ = boolManager_->addProperty(QString::fromLatin1("Axis Ticks"));
  axispropertytickcountitem_ = intManager_->addProperty(QString::fromLatin1("Count"));
  axispropertytickvisibilityitem_->addSubProperty(axispropertytickcountitem_);
  axispropertytickoriginitem_ = doubleManager_->addProperty(QString::fromLatin1("Origin"));
  axispropertytickvisibilityitem_->addSubProperty(axispropertytickoriginitem_);
  axispropertyticklengthinitem_ = intManager_->addProperty(QString::fromLatin1("Length In"));
  axispropertytickvisibilityitem_->addSubProperty(
      axispropertyticklengthinitem_);
  axispropertyticklengthoutitem_ = intManager_->addProperty(QString::fromLatin1("Length Out"));
  axispropertytickvisibilityitem_->addSubProperty(
      axispropertyticklengthoutitem_);
  axispropertytickstrokecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  axispropertytickvisibilityitem_->addSubProperty(
      axispropertytickstrokecoloritem_);
  axispropertytickstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  axispropertytickvisibilityitem_->addSubProperty(
      axispropertytickstrokethicknessitem_);
  axispropertytickstroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  axispropertytickvisibilityitem_->addSubProperty(
      axispropertytickstroketypeitem_);
  enumManager_->setEnumNames(axispropertytickstroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(axispropertytickstroketypeitem_,
                             stroketypeiconslist);
  // Axis Properties Sub-ticks sub block
  axispropertysubtickvisibilityitem_ =
      boolManager_->addProperty(QString::fromLatin1("Axis Sub-Ticks"));
  axispropertysubticklengthinitem_ = intManager_->addProperty(QString::fromLatin1("Length In"));
  axispropertysubtickvisibilityitem_->addSubProperty(
      axispropertysubticklengthinitem_);
  axispropertysubticklengthoutitem_ = intManager_->addProperty(QString::fromLatin1("Length Out"));
  axispropertysubtickvisibilityitem_->addSubProperty(
      axispropertysubticklengthoutitem_);
  axispropertysubtickstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  axispropertysubtickvisibilityitem_->addSubProperty(
      axispropertysubtickstrokecoloritem_);
  axispropertysubtickstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  axispropertysubtickvisibilityitem_->addSubProperty(
      axispropertysubtickstrokethicknessitem_);
  axispropertysubtickstroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  axispropertysubtickvisibilityitem_->addSubProperty(
      axispropertysubtickstroketypeitem_);
  enumManager_->setEnumNames(axispropertysubtickstroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(axispropertysubtickstroketypeitem_,
                             stroketypeiconslist);
  // Axis Properties Ticks Label sub block
  axispropertyticklabelvisibilityitem_ =
      boolManager_->addProperty(QString::fromLatin1("Tick Label"));
  // axispropertytickervaluescalestrategy_ =
  //    enumManager_->addProperty(QString::fromLatin1("Scale Strategy"));
  // enumManager_->setEnumNames(axispropertytickervaluescalestrategy_,
  //                           tickervaluescalestrategy);
  axispropertytickstepstrategy_ = enumManager_->addProperty(QString::fromLatin1("Step Strategy"));
  enumManager_->setEnumNames(axispropertytickstepstrategy_, tickstepstrategy);
  // axispropertytickervaluetickstep_ = doubleManager_->addProperty(QString::fromLatin1("Step"));
  axispropertytickersymbolsymbol_ = stringManager_->addProperty(QString::fromLatin1("Symbol"));
  axispropertytickersymbolvalue_ = doubleManager_->addProperty(QString::fromLatin1("Symbol Value"));
  // axispropertytickersymbolperiodicity_ =
  //    intManager_->addProperty(QString::fromLatin1("Periodicity"));
  axispropertytickersymbolfractionstyle_ =
      enumManager_->addProperty(QString::fromLatin1("Fraction Style"));
  enumManager_->setEnumNames(axispropertytickersymbolfractionstyle_,
                             tickersymbolfractionstyle);
  axispropertytickersubtickcount_ = intManager_->addProperty(QString::fromLatin1("Count"));
  axispropertytickerlogbase_ = doubleManager_->addProperty(QString::fromLatin1("Log Base"));
  axispropertytickertimeformat_ = stringManager_->addProperty(QString::fromLatin1("Time Format"));
  // axispropertytickertimefieldwidth_ = stringManager_;
  axispropertytickerdatetimeformat_ =
      stringManager_->addProperty(QString::fromLatin1("Date Time Format"));
  // axispropertytickerdatetimetickorigin_ =
  //    datetimeManager_->addProperty(QString::fromLatin1("Origin"));
  axispropertytickerdatetimefrom_ = datetimeManager_->addProperty(QString::fromLatin1("from"));
  axispropertytickerdatetimeto_ = datetimeManager_->addProperty(QString::fromLatin1("to"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickstepstrategy_);
  /*axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickervaluetickstep_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickervaluescalestrategy_);*/
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickersymbolvalue_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickersymbolsymbol_);
  // axispropertyticklabelvisibilityitem_->addSubProperty(
  //    axispropertytickersymbolperiodicity_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickersymbolfractionstyle_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickerlogbase_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickertimeformat_);
  // axispropertyticklabelvisibilityitem_->addSubProperty(
  //    axispropertytickertimefieldwidth_);
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertytickerdatetimeformat_);
  // axispropertyticklabelvisibilityitem_->addSubProperty(
  //    axispropertytickerdatetimetickorigin_);
  axispropertyticklabelfontitem_ = fontManager_->addProperty(QString::fromLatin1("Font"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelfontitem_);
  axispropertyticklabelcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Color"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelcoloritem_);
  axispropertyticklabelpaddingitem_ = intManager_->addProperty(QString::fromLatin1("Padding"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelpaddingitem_);
  axispropertyticklabelrotationitem_ = doubleManager_->addProperty(QString::fromLatin1("Rotation"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelrotationitem_);
  axispropertyticklabelsideitem_ = enumManager_->addProperty(QString::fromLatin1("Side"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelsideitem_);
  enumManager_->setEnumNames(axispropertyticklabelsideitem_, axislabelsidelist);
  axispropertyticklabelformatitem_ = enumManager_->addProperty(QString::fromLatin1("Format"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelformatitem_);
  enumManager_->setEnumNames(axispropertyticklabelformatitem_, formatlist);
  axispropertyticklabelprecisionitem_ = intManager_->addProperty(QString::fromLatin1("Precision"));
  axispropertyticklabelvisibilityitem_->addSubProperty(
      axispropertyticklabelprecisionitem_);
  intManager_->setRange(axispropertyticklabelprecisionitem_, 0, 16);
  // Legend Properties
  QStringList directionlist;
  directionlist << tr("Rows") << tr("Columns");
  itempropertylegendoriginxitem_ = doubleManager_->addProperty(QString::fromLatin1("Position X"));
  itempropertylegendoriginyitem_ = doubleManager_->addProperty(QString::fromLatin1("Position Y"));
  itempropertylegendvisibleitem_ = boolManager_->addProperty(QString::fromLatin1("Visible"));
  itempropertylegenddirectionitem_ = enumManager_->addProperty(QString::fromLatin1("Direction"));
  enumManager_->setEnumNames(itempropertylegenddirectionitem_, directionlist);
  itempropertylegendmarginitem_ = rectManager_->addProperty(QString::fromLatin1("Margin"));
  itempropertylegendfontitem_ = fontManager_->addProperty(QString::fromLatin1("Font"));
  itempropertylegendtextcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Text color"));
  itempropertylegendiconwidthitem_ = intManager_->addProperty(QString::fromLatin1("Icon width"));
  itempropertylegendiconheightitem_ = intManager_->addProperty(QString::fromLatin1("Icon Height"));
  itempropertylegendicontextpaddingitem_ =
      intManager_->addProperty(QString::fromLatin1("Icon padding"));
  itempropertylegendborderstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke color"));
  itempropertylegendborderstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke thickness"));
  itempropertylegendborderstroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Stroke style"));
  enumManager_->setEnumNames(itempropertylegendborderstroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(itempropertylegendborderstroketypeitem_,
                             stroketypeiconslist);
  itempropertylegendbackgroundcoloritem_ =
      colorManager_->addProperty(tr("Background color"));
  itempropertylegendbackgroundfillstyleitem_ =
      enumManager_->addProperty(tr("Fill Style"));
  enumManager_->setEnumNames(itempropertylegendbackgroundfillstyleitem_,
                             fillstylelist);
  enumManager_->setEnumIcons(itempropertylegendbackgroundfillstyleitem_,
                             fillstyleiconslist);
  itempropertylegendtitlevisibleitem_ = boolManager_->addProperty(tr("Title"));
  itempropertylegendtitletextitem_ = stringManager_->addProperty(tr("Text"));
  itempropertylegendtitlevisibleitem_->addSubProperty(
      itempropertylegendtitletextitem_);
  itempropertylegendtitlefontitem_ = fontManager_->addProperty(tr("Font"));
  itempropertylegendtitlevisibleitem_->addSubProperty(
      itempropertylegendtitlefontitem_);
  itempropertylegendtitlecoloritem_ = colorManager_->addProperty(tr("Color"));
  itempropertylegendtitlevisibleitem_->addSubProperty(
      itempropertylegendtitlecoloritem_);
  doubleManager_->setRange(itempropertylegendoriginxitem_, 0, 1);
  doubleManager_->setRange(itempropertylegendoriginyitem_, 0, 1);
  doubleManager_->setSingleStep(itempropertylegendoriginxitem_, 0.01);
  doubleManager_->setSingleStep(itempropertylegendoriginyitem_, 0.01);
  // Text Item Properties
  QStringList alignlist;
  alignlist << tr("Top - Left") << tr("Top - Center") << tr("Top - Right")
            << tr("Center - Left") << tr("Center - Center")
            << tr("Center - Right") << tr("Bottom - Left")
            << tr("Bottom - Center") << tr("Bottom - Right");
  itempropertytextpixelpositionxitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position X"));
  itempropertytextpixelpositionyitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position Y"));
  itempropertytextmarginitem_ = rectManager_->addProperty(QString::fromLatin1("Margin"));
  itempropertytexttextitem_ = stringManager_->addProperty(QString::fromLatin1("Text"));
  itempropertytextfontitem_ = fontManager_->addProperty(QString::fromLatin1("Font"));
  itempropertytextcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Text color"));
  itempropertytextantialiaseditem_ = boolManager_->addProperty(QString::fromLatin1("Antialiased"));
  itempropertytextstrokecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  itempropertytextstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  itempropertytextstroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  enumManager_->setEnumNames(itempropertytextstroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(itempropertytextstroketypeitem_,
                             stroketypeiconslist);
  itempropertytextbackgroundcoloritem_ =
      colorManager_->addProperty(tr("Background color"));
  itempropertytextbackgroundfillstyleitem_ =
      enumManager_->addProperty(tr("Fill Style"));
  enumManager_->setEnumNames(itempropertytextbackgroundfillstyleitem_,
                             fillstylelist);
  enumManager_->setEnumIcons(itempropertytextbackgroundfillstyleitem_,
                             fillstyleiconslist);
  itempropertytextrotationitem_ =
      doubleManager_->addProperty(tr("Text Rotation"));
  itempropertytextpositionalignmentitem_ =
      enumManager_->addProperty(tr("Positional alignment"));
  enumManager_->setEnumNames(itempropertytextpositionalignmentitem_, alignlist);
  itempropertytexttextalignmentitem_ =
      enumManager_->addProperty(tr("Text alignment"));
  enumManager_->setEnumNames(itempropertytexttextalignmentitem_, alignlist);

  // Line Item Properties
  itempropertylinepixelpositionx1item_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position X1"));
  itempropertylinepixelpositiony1item_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position Y1"));
  itempropertylinepixelpositionx2item_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position X2"));
  itempropertylinepixelpositiony2item_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position Y2"));
  itempropertylineantialiaseditem_ = boolManager_->addProperty(QString::fromLatin1("Antialiased"));
  itempropertylinestrokecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  itempropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  itempropertylinestroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Style"));
  enumManager_->setEnumNames(itempropertylinestroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(itempropertylinestroketypeitem_,
                             stroketypeiconslist);
  itempropertylineendingstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Ending Style"));
  enumManager_->setEnumNames(itempropertylineendingstyleitem_, endingstylelist);
  itempropertylineendingwidthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Ending Width"));
  itempropertylineendinglengthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Ending Length"));
  itempropertylinestartingstyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Starting Style"));
  enumManager_->setEnumNames(itempropertylinestartingstyleitem_,
                             endingstylelist);
  itempropertylinestartingwidthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Starting Width"));
  itempropertylinestartinglengthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Starting Length"));

  // Image Item Properties
  itempropertyimagepixelpositionxitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position X"));
  itempropertyimagepixelpositionyitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Pixel Position Y"));
  itempropertyimagerotationitem_ = intManager_->addProperty(QString::fromLatin1("Rotation"));
  intManager_->setMinimum(itempropertyimagerotationitem_, 0);
  intManager_->setMaximum(itempropertyimagerotationitem_, 360);
  itempropertyimagesourceitem_ = stringManager_->addProperty(QString::fromLatin1("Source"));
  itempropertyimagesourceitem_->setEnabled(false);
  itempropertyimagestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  itempropertyimagestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  itempropertyimagestroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Style"));
  enumManager_->setEnumNames(itempropertyimagestroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(itempropertyimagestroketypeitem_,
                             stroketypeiconslist);

  // LineSpecial Properties block
  QStringList lstylelist;
  lstylelist << tr("StepLeft") << tr("StepRight") << tr("StepCenter")
             << tr("Impulse") << tr("Line");
  QStringList sstylelist;
  sstylelist << tr("None") << tr("Dot") << tr("Cross") << tr("Plus")
             << tr("Circle") << tr("Disc") << tr("Square") << tr("Diamond")
             << tr("Star") << tr("Triangle") << tr("TriangleInverted")
             << tr("CrossSquare") << tr("PlusSquare") << tr("CrossCircle")
             << tr("PlusCircle") << tr("Peace");
  lsplotpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  lsplotpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  lsplotpropertylinestyleitem_ = enumManager_->addProperty(QString::fromLatin1("Line Style"));
  enumManager_->setEnumNames(lsplotpropertylinestyleitem_, lstylelist);
  lsplotpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Line Stroke Color"));
  lsplotpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Stroke Thickness"));
  lsplotpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Stroke Type"));
  enumManager_->setEnumNames(lsplotpropertylinestroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(lsplotpropertylinestroketypeitem_,
                             stroketypeiconslist);
  lsplotpropertylinefillstatusitem_ =
      boolManager_->addProperty(QString::fromLatin1("Fill Under Area"));
  lsplotpropertylinefillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Area Fill Color"));
  lsplotpropertylinefillstyleitem_ =
      enumManager_->addProperty(tr("Area Fill Style"));
  enumManager_->setEnumNames(lsplotpropertylinefillstyleitem_, fillstylelist);
  enumManager_->setEnumIcons(lsplotpropertylinefillstyleitem_,
                             fillstyleiconslist);
  lsplotpropertylineantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Line Antialiased"));
  lsplotpropertyscatterstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Scatter Style"));
  enumManager_->setEnumNames(lsplotpropertyscatterstyleitem_, sstylelist);
  lsplotpropertyscatterthicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Size"));
  lsplotpropertyscatterfillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Fill Color"));
  lsplotpropertyscatterstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Outline Color"));
  lsplotpropertyscatterstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Outline Thickness"));
  lsplotpropertyscatterstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Outline Type"));
  enumManager_->setEnumNames(lsplotpropertyscatterstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(lsplotpropertyscatterstrokestyleitem_,
                             stroketypeiconslist);
  lsplotpropertyscatterantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Scatter Antialiased"));
  lsplotpropertylegendvisibleitem_ = boolManager_->addProperty(QString::fromLatin1("Legend"));
  lsplotpropertylegendtextitem_ = stringManager_->addProperty(QString::fromLatin1("Plot Legend"));
  lsplotpropertylegendvisibleitem_->addSubProperty(
      lsplotpropertylegendtextitem_);
  // LineSpecialChannel Properties block
  channelplotpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  channelplotpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  channelplotpropertylegendvisibleitem_ = boolManager_->addProperty(QString::fromLatin1("Legend"));
  channelplotpropertylegendtextitem_ =
      stringManager_->addProperty(QString::fromLatin1("Plot Legend"));
  channelplotpropertylegendvisibleitem_->addSubProperty(
      channelplotpropertylegendtextitem_);
  // channel 1st graph
  channel1plotpropertygroupitem_ =
      groupManager_->addProperty(QString::fromLatin1("Channel Border 1"));
  channel1plotpropertylinestyleitem_ = enumManager_->addProperty(QString::fromLatin1("Line Style"));
  enumManager_->setEnumNames(channel1plotpropertylinestyleitem_, lstylelist);
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinestyleitem_);
  channel1plotpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Line Stroke Color"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinestrokecoloritem_);
  channel1plotpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Stroke Thickness"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinestrokethicknessitem_);
  channel1plotpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Stroke Type"));
  enumManager_->setEnumNames(channel1plotpropertylinestroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(channel1plotpropertylinestroketypeitem_,
                             stroketypeiconslist);
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinestroketypeitem_);
  channel1plotpropertylinefillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Area Fill Color"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinefillcoloritem_);
  channel1plotpropertylinefillstylritem_ =
      enumManager_->addProperty(tr("Area Fill Style"));
  enumManager_->setEnumNames(channel1plotpropertylinefillstylritem_,
                             fillstylelist);
  enumManager_->setEnumIcons(channel1plotpropertylinefillstylritem_,
                             fillstyleiconslist);
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylinefillstylritem_);
  channel1plotpropertylineantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Line Antialiased"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertylineantialiaseditem_);
  channel1plotpropertyscatterstyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Style"));
  enumManager_->setEnumNames(channel1plotpropertyscatterstyleitem_, sstylelist);
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterstyleitem_);
  channel1plotpropertyscatterthicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Size"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterthicknessitem_);
  channel1plotpropertyscatterfillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Fill Color"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterfillcoloritem_);
  channel1plotpropertyscatterstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Outline Color"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterstrokecoloritem_);
  channel1plotpropertyscatterstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Outline Thickness"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterstrokethicknessitem_);
  channel1plotpropertyscatterstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Outline Type"));
  enumManager_->setEnumNames(channel1plotpropertyscatterstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(channel1plotpropertyscatterstrokestyleitem_,
                             stroketypeiconslist);
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterstrokestyleitem_);
  channel1plotpropertyscatterantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Scatter Antialiased"));
  channel1plotpropertygroupitem_->addSubProperty(
      channel1plotpropertyscatterantialiaseditem_);
  // channe2 1st graph
  channel2plotpropertygroupitem_ =
      groupManager_->addProperty(QString::fromLatin1("Channel Border 2"));
  channel2plotpropertylinestyleitem_ = enumManager_->addProperty(QString::fromLatin1("Line Style"));
  enumManager_->setEnumNames(channel2plotpropertylinestyleitem_, lstylelist);
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertylinestyleitem_);
  channel2plotpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Line Stroke Color"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertylinestrokecoloritem_);
  channel2plotpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Stroke Thickness"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertylinestrokethicknessitem_);
  channel2plotpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Stroke Type"));
  enumManager_->setEnumNames(channel2plotpropertylinestroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(channel2plotpropertylinestroketypeitem_,
                             stroketypeiconslist);
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertylinestroketypeitem_);
  channel2plotpropertylineantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Line Antialiased"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertylineantialiaseditem_);
  channel2plotpropertyscatterstyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Style"));
  enumManager_->setEnumNames(channel2plotpropertyscatterstyleitem_, sstylelist);
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterstyleitem_);
  channel2plotpropertyscatterthicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Size"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterthicknessitem_);
  channel2plotpropertyscatterfillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Fill Color"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterfillcoloritem_);
  channel2plotpropertyscatterstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Outline Color"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterstrokecoloritem_);
  channel2plotpropertyscatterstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Outline Thickness"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterstrokethicknessitem_);
  channel2plotpropertyscatterstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Outline Type"));
  enumManager_->setEnumNames(channel2plotpropertyscatterstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(channel2plotpropertyscatterstrokestyleitem_,
                             stroketypeiconslist);
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterstrokestyleitem_);
  channel2plotpropertyscatterantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Scatter Antialiased"));
  channel2plotpropertygroupitem_->addSubProperty(
      channel2plotpropertyscatterantialiaseditem_);

  // Curve property block
  QStringList clstylelist;
  clstylelist << tr("None") << tr("Line");
  cplotpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  cplotpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  cplotpropertylinestyleitem_ = enumManager_->addProperty(QString::fromLatin1("Line Style"));
  enumManager_->setEnumNames(cplotpropertylinestyleitem_, clstylelist);
  cplotpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Line Stroke Color"));
  cplotpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Stroke Thickness"));
  cplotpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Stroke Type"));
  enumManager_->setEnumNames(cplotpropertylinestroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(cplotpropertylinestroketypeitem_,
                             stroketypeiconslist);
  cplotpropertylinefillstatusitem_ =
      boolManager_->addProperty(QString::fromLatin1("Fill Under Area"));
  cplotpropertylinefillcoloritem_ =
      colorManager_->addProperty(tr("Area Fill Color"));
  cplotpropertylinefillstyleitem_ =
      enumManager_->addProperty(tr("Area Fill Style"));
  enumManager_->setEnumNames(cplotpropertylinefillstyleitem_, fillstylelist);
  enumManager_->setEnumIcons(cplotpropertylinefillstyleitem_,
                             fillstyleiconslist);
  cplotpropertylineantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Line Antialiased"));
  cplotpropertyscatterstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Scatter Style"));
  enumManager_->setEnumNames(cplotpropertyscatterstyleitem_, sstylelist);
  cplotpropertyscatterthicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Size"));
  cplotpropertyscatterfillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Fill Color"));
  cplotpropertyscatterstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Outline Color"));
  cplotpropertyscatterstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Outline Thickness"));
  cplotpropertyscatterstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Outline Type"));
  enumManager_->setEnumNames(cplotpropertyscatterstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(cplotpropertyscatterstrokestyleitem_,
                             stroketypeiconslist);
  cplotpropertyscatterantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Scatter Antialiased"));
  cplotpropertylegendvisibleitem_ = boolManager_->addProperty(QString::fromLatin1("Legend"));
  cplotpropertylegendtextitem_ = stringManager_->addProperty(QString::fromLatin1("Plot Legend"));
  cplotpropertylegendvisibleitem_->addSubProperty(cplotpropertylegendtextitem_);

  // Box Properties block
  barplotpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  barplotpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  barplotpropertywidthitem_ = doubleManager_->addProperty(QString::fromLatin1("Width"));
  barplotpropertystackgapitem_ = doubleManager_->addProperty(QString::fromLatin1("Stack/Group Gap"));
  barplotpropertyfillantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Fill Antialiased"));
  barplotpropertyfillcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Fill Color"));
  barplotpropertyfillstyleitem_ = enumManager_->addProperty(tr("Fill Style"));
  enumManager_->setEnumNames(barplotpropertyfillstyleitem_, fillstylelist);
  enumManager_->setEnumIcons(barplotpropertyfillcoloritem_, fillstyleiconslist);
  barplotpropertyantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Stroke Antialiased"));
  barplotpropertystrokecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  barplotpropertystrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  barplotpropertystrokestyleitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Style"));
  enumManager_->setEnumNames(barplotpropertystrokestyleitem_, stroketypelist);
  enumManager_->setEnumIcons(barplotpropertystrokestyleitem_,
                             stroketypeiconslist);
  barplotpropertylegendtextitem_ = stringManager_->addProperty(QString::fromLatin1("Legend Text"));
  doubleManager_->setSingleStep(barplotpropertywidthitem_, 0.01);
  barplotpropertyhistautobinstatusitem_ =
      boolManager_->addProperty(tr("Auto Bin"));
  barplotpropertyhistbinitem_ = doubleManager_->addProperty(tr("Bin Size"));
  barplotpropertyhistautobinstatusitem_->addSubProperty(
      barplotpropertyhistbinitem_);
  barplotpropertyhistbeginitem_ = doubleManager_->addProperty(tr("Begin"));
  barplotpropertyhistautobinstatusitem_->addSubProperty(
      barplotpropertyhistbeginitem_);
  barplotpropertyhistenditem_ = doubleManager_->addProperty(tr("End"));
  barplotpropertyhistautobinstatusitem_->addSubProperty(
      barplotpropertyhistenditem_);
  doubleManager_->setDecimals(barplotpropertyhistbinitem_, 10);
  doubleManager_->setMinimum(barplotpropertyhistbinitem_, 0.0000000001);
  doubleManager_->setDecimals(barplotpropertyhistbeginitem_, 10);
  doubleManager_->setDecimals(barplotpropertyhistenditem_, 10);

  // StatBox Properties block
  QStringList whiskerstylelist;
  whiskerstylelist << QString::fromLatin1("SD")
                   << QString::fromLatin1("SE")
                   << QString::fromLatin1("Perc_25_75")
                   << QString::fromLatin1("Perc_10_90")
                   << QString::fromLatin1("Perc_5_95")
                   << QString::fromLatin1("Perc_1_99")
                   << QString::fromLatin1("MinMax")
                   << QString::fromLatin1("Constant")
                   << QString::fromLatin1("IQR_1.5_auto");
  QStringList boxstylelist = whiskerstylelist;
  boxstylelist.removeLast();
  statboxplotpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  statboxplotpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  statboxplotpropertywidthitem_ = doubleManager_->addProperty(QString::fromLatin1("Width"));
  statboxplotpropertywhiskerwidthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Whisker Width"));
  statboxplotpropertyboxstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Box Style"));
  enumManager_->setEnumNames(statboxplotpropertyboxstyleitem_, boxstylelist);
  statboxplotpropertywhiskerstyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Whisker Style"));
  enumManager_->setEnumNames(statboxplotpropertywhiskerstyleitem_,
                             whiskerstylelist);
  statboxplotpropertyantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Antialiased"));
  statboxplotpropertyfillantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Fill Antialiased"));
  statboxplotpropertyboxoutlinecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Box Stroke Color"));
  statboxplotpropertyboxoutlinethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Box Stroke Thickness"));
  statboxplotpropertyboxoutlinestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Box Stroke Style"));
  enumManager_->setEnumNames(statboxplotpropertyboxoutlinestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(statboxplotpropertyboxoutlinestyleitem_,
                             stroketypeiconslist);
  statboxplotpropertyfillstatusitem_ = boolManager_->addProperty(QString::fromLatin1("Fill Status"));
  statboxplotpropertyfillcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Fill Color"));
  statboxplotpropertyfillstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Fill Style"));
  enumManager_->setEnumNames(statboxplotpropertyfillstyleitem_, fillstylelist);
  enumManager_->setEnumIcons(statboxplotpropertyfillstyleitem_,
                             fillstyleiconslist);
  statboxplotpropertywhiskerantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Whisker Antialiased"));
  statboxplotpropertywhiskerstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Whisker Stroke Color"));
  statboxplotpropertywhiskerstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Whisker Stroke Thickness"));
  statboxplotpropertywhiskerstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Whisker Stroke Style"));
  enumManager_->setEnumNames(statboxplotpropertywhiskerstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(statboxplotpropertywhiskerstrokestyleitem_,
                             stroketypeiconslist);
  statboxplotpropertywhiskerbarstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Whiskerbar Stroke Color"));
  statboxplotpropertywhiskerbarstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Whiskerbar Stroke Thickness"));
  statboxplotpropertywhiskerbarstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Whiskerbar Stroke Style"));
  enumManager_->setEnumNames(statboxplotpropertywhiskerbarstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(statboxplotpropertywhiskerbarstrokestyleitem_,
                             stroketypeiconslist);
  statboxplotpropertymedianstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Median Stroke Color"));
  statboxplotpropertymideanstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Median Stroke Thickness"));
  statboxplotpropertymideanstrokestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Median Stroke Style"));
  enumManager_->setEnumNames(statboxplotpropertymideanstrokestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(statboxplotpropertymideanstrokestyleitem_,
                             stroketypeiconslist);
  QStringList sshowlist;
  sshowlist << QString::fromLatin1("Outlier")
            << QString::fromLatin1("All")
            << QString::fromLatin1("Min Max")
            << QString::fromLatin1("None");
  statboxplotpropertyscattershowitem_ = enumManager_->addProperty(QString::fromLatin1("Show"));
  enumManager_->setEnumNames(statboxplotpropertyscattershowitem_, sshowlist);
  statboxplotpropertyscatterantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Scatter Antialiased"));
  statboxplotpropertyscatterstyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Style"));
  enumManager_->setEnumNames(statboxplotpropertyscatterstyleitem_, sstylelist);
  statboxplotpropertyscattersizeitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Size"));
  statboxplotpropertyscatterfillcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Fill Color"));
  statboxplotpropertyscatteroutlinecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Scatter Outline Color"));
  statboxplotpropertyscatteroutlinethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Scatter Outline Thickness"));
  statboxplotpropertyscatteroutlinestyleitem_ =
      enumManager_->addProperty(QString::fromLatin1("Scatter Outline Style"));
  enumManager_->setEnumNames(statboxplotpropertyscatteroutlinestyleitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(statboxplotpropertyscatteroutlinestyleitem_,
                             stroketypeiconslist);
  statboxplotpropertylegendtextitem_ =
      stringManager_->addProperty(QString::fromLatin1("Legend text"));

  // Vector Properties block
  vectorpropertyxaxisitem_ = enumManager_->addProperty(QString::fromLatin1("X Axis"));
  vectorpropertyyaxisitem_ = enumManager_->addProperty(QString::fromLatin1("Y Axis"));
  vectorpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Line Stroke Color"));
  vectorpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Stroke Thickness"));
  vectorpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Stroke Type"));
  enumManager_->setEnumNames(vectorpropertylinestroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(vectorpropertylinestroketypeitem_,
                             stroketypeiconslist);
  vectorpropertylineendingtypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Line Ending Type"));
  enumManager_->setEnumNames(vectorpropertylineendingtypeitem_,
                             endingstylelist);
  vectorpropertylineendingheightitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Ending Height"));
  vectorpropertylineendingwidthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Line Ending Width"));
  vectorpropertylineantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Line Antialiased"));
  vectorpropertylegendvisibleitem_ = boolManager_->addProperty(QString::fromLatin1("Legend"));
  vectorpropertylegendtextitem_ = stringManager_->addProperty(QString::fromLatin1("Plot Legend"));
  vectorpropertylegendvisibleitem_->addSubProperty(
      vectorpropertylegendtextitem_);

  // Pie Properties Block
  QStringList piestyle;
  piestyle << QString::fromLatin1("Pie")
           << QString::fromLatin1("Half Pie");
  pieplotpropertystyleitem_ = enumManager_->addProperty(QString::fromLatin1("Style"));
  enumManager_->setEnumNames(pieplotpropertystyleitem_, piestyle);
  pieplotpropertylinestrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  pieplotpropertylinestrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  pieplotpropertylinestroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Stroke Style"));
  enumManager_->setEnumNames(pieplotpropertylinestroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(pieplotpropertylinestroketypeitem_,
                             stroketypeiconslist);
  pieplotpropertymarginpercentitem_ =
      intManager_->addProperty(QString::fromLatin1("Margin Percent"));
  intManager_->setRange(pieplotpropertymarginpercentitem_, 0, 100);

  // Colormap Properties Block
  QStringList datascaletypelist;
  datascaletypelist << QString::fromLatin1("Linear")
                    << QString::fromLatin1("Logarithmic");
  QStringList gradientlist;
  gradientlist << QString::fromLatin1("Grayscale")
               << QString::fromLatin1("Hot")
               << QString::fromLatin1("Cold")
               << QString::fromLatin1("Night")
               << QString::fromLatin1("candy")
               << QString::fromLatin1("Geography")
               << QString::fromLatin1("Ion")
               << QString::fromLatin1("Thermal")
               << QString::fromLatin1("Polar")
               << QString::fromLatin1("Spectrum")
               << QString::fromLatin1("Jet")
               << QString::fromLatin1("Hues");
  colormappropertyinterpolateitem_ = boolManager_->addProperty(QString::fromLatin1("Interpolate"));
  colormappropertytightboundaryitem_ =
      boolManager_->addProperty(QString::fromLatin1("Tight Boundary"));
  colormappropertylevelcountitem_ = intManager_->addProperty(tr("Level Count"));
  colormappropertygradientinvertitem_ =
      boolManager_->addProperty(tr("Gradient Invert"));
  colormappropertygradientperiodicitem_ =
      boolManager_->addProperty(tr("Gradient Periodic"));
  colormappropertygradientitem_ = enumManager_->addProperty(QString::fromLatin1("Gradient"));
  enumManager_->setEnumNames(colormappropertygradientitem_, gradientlist);
  colormappropertyscalevisibleitem_ =
      boolManager_->addProperty(QString::fromLatin1("Colormap Scale"));
  colormappropertyscalewidthitem_ = intManager_->addProperty(QString::fromLatin1("Scale Width"));
  colormappropertyscalevisibleitem_->addSubProperty(
      colormappropertyscalewidthitem_);
  // Colormap Axis general
  colormappropertyscaleaxisvisibleitem_ =
      boolManager_->addProperty(QString::fromLatin1("Scale Visible"));
  colormappropertyscaleaxisoffsetitem_ = intManager_->addProperty(tr("Offset"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisoffsetitem_);
  colormappropertyscaleaxisfromitem_ = doubleManager_->addProperty(tr("From"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisfromitem_);
  colormappropertyscaleaxistoitem_ = doubleManager_->addProperty(tr("To"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxistoitem_);
  colormappropertyscaleaxislinlogitem_ = enumManager_->addProperty(tr("Type"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxislinlogitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxislinlogitem_,
                             axistypelist);
  colormappropertyscaleaxisinvertitem_ =
      boolManager_->addProperty(tr("Inverted"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisinvertitem_);
  colormappropertyscaleaxisstrokecoloritem_ =
      colorManager_->addProperty(tr("Stroke Color"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisstrokecoloritem_);
  colormappropertyscaleaxisstrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisstrokethicknessitem_);
  colormappropertyscaleaxisstroketypeitem_ =
      enumManager_->addProperty(tr("Stroke Type"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisstroketypeitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxisstroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(colormappropertyscaleaxisstroketypeitem_,
                             stroketypeiconslist);
  colormappropertyscaleaxisantialiaseditem_ =
      boolManager_->addProperty(QString::fromLatin1("Antialiased"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxisantialiaseditem_);
  // Colormap Axis Properties Label sub block
  colormappropertyscaleaxislabeltextitem_ =
      stringManager_->addProperty(tr("Label Text"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxislabeltextitem_);
  colormappropertyscaleaxislabelfontitem_ =
      fontManager_->addProperty(QString::fromLatin1("Label Font"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxislabelfontitem_);
  colormappropertyscaleaxislabelcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Label Color"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxislabelcoloritem_);
  colormappropertyscaleaxislabelpaddingitem_ =
      intManager_->addProperty(QString::fromLatin1("Label Padding"));
  colormappropertyscaleaxisvisibleitem_->addSubProperty(
      colormappropertyscaleaxislabelpaddingitem_);
  // Colormap Axis Properties Ticks sub block
  colormappropertyscaleaxistickvisibilityitem_ =
      boolManager_->addProperty(QString::fromLatin1("Scale Axis Ticks"));
  colormappropertyscaleaxisticklengthinitem_ =
      intManager_->addProperty(QString::fromLatin1("Length In"));
  colormappropertyscaleaxistickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklengthinitem_);
  colormappropertyscaleaxisticklengthoutitem_ =
      intManager_->addProperty(QString::fromLatin1("Length Out"));
  colormappropertyscaleaxistickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklengthoutitem_);
  colormappropertyscaleaxistickstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  colormappropertyscaleaxistickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxistickstrokecoloritem_);
  colormappropertyscaleaxistickstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  colormappropertyscaleaxistickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxistickstrokethicknessitem_);
  colormappropertyscaleaxistickstroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  colormappropertyscaleaxistickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxistickstroketypeitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxistickstroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(colormappropertyscaleaxistickstroketypeitem_,
                             stroketypeiconslist);
  // Colormap Axis Properties Sub-ticks sub block
  colormappropertyscaleaxissubtickvisibilityitem_ =
      boolManager_->addProperty(QString::fromLatin1("Scale Axis Sub-Ticks"));
  colormappropertyscaleaxissubticklengthinitem_ =
      intManager_->addProperty(QString::fromLatin1("Length In"));
  colormappropertyscaleaxissubtickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxissubticklengthinitem_);
  colormappropertyscaleaxissubticklengthoutitem_ =
      intManager_->addProperty(QString::fromLatin1("Length Out"));
  colormappropertyscaleaxissubtickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxissubticklengthoutitem_);
  colormappropertyscaleaxissubtickstrokecoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  colormappropertyscaleaxissubtickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxissubtickstrokecoloritem_);
  colormappropertyscaleaxissubtickstrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  colormappropertyscaleaxissubtickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxissubtickstrokethicknessitem_);
  colormappropertyscaleaxissubtickstroketypeitem_ =
      enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  colormappropertyscaleaxissubtickvisibilityitem_->addSubProperty(
      colormappropertyscaleaxissubtickstroketypeitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxissubtickstroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(colormappropertyscaleaxissubtickstroketypeitem_,
                             stroketypeiconslist);
  // Colormap Axis Properties Ticks Label sub block
  colormappropertyscaleaxisticklabelvisibilityitem_ =
      boolManager_->addProperty(QString::fromLatin1("Scale Tick Label"));
  colormappropertyscaleaxisticklabelfontitem_ =
      fontManager_->addProperty(QString::fromLatin1("Font"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelfontitem_);
  colormappropertyscaleaxisticklabelcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Color"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelcoloritem_);
  colormappropertyscaleaxisticklabelpaddingitem_ =
      intManager_->addProperty(QString::fromLatin1("Padding"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelpaddingitem_);
  colormappropertyscaleaxisticklabelrotationitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Rotation"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelrotationitem_);
  colormappropertyscaleaxisticklabelsideitem_ =
      enumManager_->addProperty(QString::fromLatin1("Side"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelsideitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxisticklabelsideitem_,
                             axislabelsidelist);
  colormappropertyscaleaxisticklabelformatitem_ =
      enumManager_->addProperty(QString::fromLatin1("Format"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelformatitem_);
  enumManager_->setEnumNames(colormappropertyscaleaxisticklabelformatitem_,
                             formatlist);
  colormappropertyscaleaxisticklabelprecisionitem_ =
      intManager_->addProperty(QString::fromLatin1("Precision"));
  colormappropertyscaleaxisticklabelvisibilityitem_->addSubProperty(
      colormappropertyscaleaxisticklabelprecisionitem_);

  errorbarpropertywhiskerwidthitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Whisker Width"));
  errorbarpropertysymbolgaptem_ = doubleManager_->addProperty(QString::fromLatin1("Symbol Gap"));
  errorbarpropertystrokecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Stroke Color"));
  errorbarpropertystrokethicknessitem_ =
      doubleManager_->addProperty(QString::fromLatin1("Stroke Thickness"));
  errorbarpropertystroketypeitem_ = enumManager_->addProperty(QString::fromLatin1("Stroke Type"));
  enumManager_->setEnumNames(errorbarpropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(errorbarpropertystroketypeitem_,
                             stroketypeiconslist);
  errorbarpropertyfillstatusitem_ = boolManager_->addProperty(QString::fromLatin1("Fill"));
  errorbarpropertyfillcoloritem_ = colorManager_->addProperty(QString::fromLatin1("Fill Color"));
  errorbarpropertyantialiaseditem_ = boolManager_->addProperty(QString::fromLatin1("Antialiased"));

  // Axis Properties Major Grid Sub Block
  hgridaxispropertycomboitem_ = enumManager_->addProperty(QString::fromLatin1("Horizontal Axis"));
  hmajgridpropertyvisibleitem_ = boolManager_->addProperty(tr("Major Grid"));
  hgridaxispropertycomboitem_->addSubProperty(hmajgridpropertyvisibleitem_);
  hmajgridpropertystrokecoloritem_ =
      colorManager_->addProperty(tr("Stroke Color"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertystrokecoloritem_);
  hmajgridpropertystrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertystrokethicknessitem_);
  hmajgridpropertystroketypeitem_ =
      enumManager_->addProperty(tr("Stroke Type"));
  hmajgridpropertyvisibleitem_->addSubProperty(hmajgridpropertystroketypeitem_);
  enumManager_->setEnumNames(hmajgridpropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(hmajgridpropertystroketypeitem_,
                             stroketypeiconslist);
  hmajgridpropertyzerolinevisibleitem_ =
      boolManager_->addProperty(tr("Zero Line"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertyzerolinevisibleitem_);
  hmajgridpropertyzerolinestrokecoloritem_ =
      colorManager_->addProperty(tr("Zero Color"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertyzerolinestrokecoloritem_);
  hmajgridpropertyzerolinestrokethicknessitem_ =
      doubleManager_->addProperty(tr("Zero Thickness"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertyzerolinestrokethicknessitem_);
  hmajgridpropertyzerolinestroketypeitem_ =
      enumManager_->addProperty(tr("Zero Type"));
  hmajgridpropertyvisibleitem_->addSubProperty(
      hmajgridpropertyzerolinestroketypeitem_);
  enumManager_->setEnumNames(hmajgridpropertyzerolinestroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(hmajgridpropertyzerolinestroketypeitem_,
                             stroketypeiconslist);

  // Axis Properties Minor Grid Sub Block
  hmingridpropertyvisibleitem_ = boolManager_->addProperty(tr("Minor Grid"));
  hgridaxispropertycomboitem_->addSubProperty(hmingridpropertyvisibleitem_);
  hmingridpropertystrokecoloritem_ =
      colorManager_->addProperty(tr("Stroke Color"));
  hmingridpropertyvisibleitem_->addSubProperty(
      hmingridpropertystrokecoloritem_);
  hmingridpropertystrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  hmingridpropertyvisibleitem_->addSubProperty(
      hmingridpropertystrokethicknessitem_);
  hmingridpropertystroketypeitem_ =
      enumManager_->addProperty(tr("Stroke Type"));
  hmingridpropertyvisibleitem_->addSubProperty(hmingridpropertystroketypeitem_);
  enumManager_->setEnumNames(hmingridpropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(hmingridpropertystroketypeitem_,
                             stroketypeiconslist);

  // Axis Properties Major Grid Sub Block
  vgridaxispropertycomboitem_ = enumManager_->addProperty(QString::fromLatin1("Vertical Axis"));
  vmajgridpropertyvisibleitem_ = boolManager_->addProperty(tr("Major Grid"));
  vgridaxispropertycomboitem_->addSubProperty(vmajgridpropertyvisibleitem_);
  vmajgridpropertystrokecoloritem_ =
      colorManager_->addProperty(tr("Stroke Color"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertystrokecoloritem_);
  vmajgridpropertystrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertystrokethicknessitem_);
  vmajgridpropertystroketypeitem_ =
      enumManager_->addProperty(tr("Stroke Type"));
  vmajgridpropertyvisibleitem_->addSubProperty(vmajgridpropertystroketypeitem_);
  enumManager_->setEnumNames(vmajgridpropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(vmajgridpropertystroketypeitem_,
                             stroketypeiconslist);
  vmajgridpropertyzerolinevisibleitem_ =
      boolManager_->addProperty(tr("Zero Line"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertyzerolinevisibleitem_);
  vmajgridpropertyzerolinestrokecoloritem_ =
      colorManager_->addProperty(tr("Zero Color"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertyzerolinestrokecoloritem_);
  vmajgridpropertyzerolinestrokethicknessitem_ =
      doubleManager_->addProperty(tr("Zero Thickness"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertyzerolinestrokethicknessitem_);
  vmajgridpropertyzerolinestroketypeitem_ =
      enumManager_->addProperty(tr("Zero Type"));
  vmajgridpropertyvisibleitem_->addSubProperty(
      vmajgridpropertyzerolinestroketypeitem_);
  enumManager_->setEnumNames(vmajgridpropertyzerolinestroketypeitem_,
                             stroketypelist);
  enumManager_->setEnumIcons(vmajgridpropertyzerolinestroketypeitem_,
                             stroketypeiconslist);
  // Axis Properties Minor Grid Sub Block
  vmingridpropertyvisibleitem_ = boolManager_->addProperty(tr("Minor Grid"));
  vgridaxispropertycomboitem_->addSubProperty(vmingridpropertyvisibleitem_);
  vmingridpropertystrokecoloritem_ =
      colorManager_->addProperty(tr("Stroke Color"));
  vmingridpropertyvisibleitem_->addSubProperty(
      vmingridpropertystrokecoloritem_);
  vmingridpropertystrokethicknessitem_ =
      doubleManager_->addProperty(tr("Stroke Thickness"));
  vmingridpropertyvisibleitem_->addSubProperty(
      vmingridpropertystrokethicknessitem_);
  vmingridpropertystroketypeitem_ =
      enumManager_->addProperty(tr("Stroke Type"));
  vmingridpropertyvisibleitem_->addSubProperty(vmingridpropertystroketypeitem_);
  enumManager_->setEnumNames(vmingridpropertystroketypeitem_, stroketypelist);
  enumManager_->setEnumIcons(vmingridpropertystroketypeitem_,
                             stroketypeiconslist);

  // Plot3D Canvas properties
  QStringList themelist;
  themelist << QString::fromLatin1("ThemeQt")
            << QString::fromLatin1("ThemePrimaryColors")
            << QString::fromLatin1("ThemeDigia")
            << QString::fromLatin1("ThemeStoneMoss")
            << QString::fromLatin1("ThemeArmyBlue")
            << QString::fromLatin1("ThemeRetro")
            << QString::fromLatin1("ThemeEbony")
            << QString::fromLatin1("ThemeIsabelle")
            << QString::fromLatin1("ThemeUserDefined");
  plot3dcanvasthemeitem_ = enumManager_->addProperty(tr("Theme"));
  enumManager_->setEnumNames(plot3dcanvasthemeitem_, themelist);
  plot3dcanvassizeitem_ = sizeManager_->addProperty(tr("Plot Dimension"));
  plot3dcanvaswindowcoloritem_ =
      colorManager_->addProperty(tr("Background Color"));
  plot3dcanvasbackgroundvisibleitem_ =
      boolManager_->addProperty(tr("Graph Background Visible"));
  plot3dcanvasbackgroundcoloritem_ =
      colorManager_->addProperty(tr("Graph Background Color"));
  plot3dcanvasbackgroundvisibleitem_->addSubProperty(
      plot3dcanvasbackgroundcoloritem_);
  plot3dcanvasambientlightstrengthitem_ =
      doubleManager_->addProperty(tr("Ambient Light Strength"));
  plot3dcanvaslightstrengthitem_ =
      doubleManager_->addProperty(tr("Light Strength"));
  plot3dcanvaslightcoloritem_ = colorManager_->addProperty(tr("Light Color"));
  plot3dcanvasgridvisibleitem_ = boolManager_->addProperty(tr("Grid Visible"));
  plot3dcanvasgridcoloritem_ = colorManager_->addProperty(tr("Grid Color"));
  plot3dcanvasgridvisibleitem_->addSubProperty(plot3dcanvasgridcoloritem_);
  plot3dcanvaslabelbackgroundvisibleitem_ =
      boolManager_->addProperty(tr("Label Background Visible"));
  plot3dcanvaslabelbackgroundcoloritem_ =
      colorManager_->addProperty(tr("Label Background Color"));
  plot3dcanvaslabelbackgroundvisibleitem_->addSubProperty(
      plot3dcanvaslabelbackgroundcoloritem_);
  plot3dcanvaslabelbordervisibleitem_ =
      boolManager_->addProperty(tr("Label Border Visible"));
  plot3dcanvaslabelbackgroundvisibleitem_->addSubProperty(
      plot3dcanvaslabelbordervisibleitem_);
  plot3dcanvaslabeltextcoloritem_ =
      colorManager_->addProperty(tr("Label Text Color"));
  plot3dcanvaslabelbackgroundvisibleitem_->addSubProperty(
      plot3dcanvaslabeltextcoloritem_);
  plot3dcanvasfontitem_ = fontManager_->addProperty(tr("General Font"));
  plot3dcanvaslabelbackgroundvisibleitem_->addSubProperty(
      plot3dcanvasfontitem_);

  // Plot3D Value Axis
  plot3daxisvalueautoadjustrangeitem_ =
      boolManager_->addProperty(tr("Auto Adjust Range"));
  plot3daxisvaluerangeloweritem_ = doubleManager_->addProperty(tr("From"));
  plot3daxisvaluerangeupperitem_ = doubleManager_->addProperty(tr("To"));
  plot3dvalueaxislabelformatitem_ =
      stringManager_->addProperty(QString::fromLatin1("Tick Label Format"));
  plot3dvalueaxisreverseitem_ = boolManager_->addProperty(tr("Inverted"));
  plot3dvalueaxistickcountitem_ = intManager_->addProperty(tr("Tick Count"));
  plot3dvalueaxissubtickcountitem_ =
      intManager_->addProperty(tr("Sub Tick Count"));
  plot3daxisvalueticklabelrotationitem_ =
      doubleManager_->addProperty(tr("Tick Label Rotation"));
  plot3daxisvaluetitlevisibleitem_ =
      boolManager_->addProperty(tr("Label Visible"));
  plot3daxisvaluetitlefixeditem_ = boolManager_->addProperty(tr("Label Fixed"));
  plot3daxisvaluetitletextitem_ = stringManager_->addProperty(QString::fromLatin1("Label Text"));

  // Plot3D Catagory Axis
  plot3daxiscatagoryautoadjustrangeitem_ =
      boolManager_->addProperty(tr("Auto Adjust Range"));
  plot3daxiscatagoryrangeloweritem_ = doubleManager_->addProperty(tr("From"));
  plot3daxiscatagoryrangeupperitem_ = doubleManager_->addProperty(tr("To"));
  plot3daxiscatagoryticklabelrotationitem_ =
      doubleManager_->addProperty(tr("Tick Label Rotation"));
  plot3daxiscatagorytitlevisibleitem_ =
      boolManager_->addProperty(tr("Label Visible"));
  plot3daxiscatagorytitlefixeditem_ =
      boolManager_->addProperty(tr("Label Fixed"));
  plot3daxiscatagorytitletextitem_ = stringManager_->addProperty(QString::fromLatin1("Label Text"));

  // Plot3D Surface
  QStringList shadowquality;
  shadowquality << QString::fromLatin1("ShadowQualityNone")
                << QString::fromLatin1("ShadowQualityLow")
                << QString::fromLatin1("ShadowQualityMedium")
                << QString::fromLatin1("ShadowQualityHigh")
                << QString::fromLatin1("ShadowQualitySoftLow")
                << QString::fromLatin1("ShadowQualitySoftMedium")
                << QString::fromLatin1("ShadowQualitySoftHigh");
  plot3dsurfacefliphorizontalgriditem_ =
      boolManager_->addProperty(tr("Flip Horizontal Grid"));
  plot3dsurfaceaspectratioitem_ =
      doubleManager_->addProperty(tr("Aspectratio"));
  plot3dsurfacehorizontalaspectratioitem_ =
      doubleManager_->addProperty(tr("Horizontal Aspectratio"));
  plot3dsurfaceshadowqualityitem_ =
      enumManager_->addProperty(tr("Shadow Quality"));
  enumManager_->setEnumNames(plot3dsurfaceshadowqualityitem_, shadowquality);
  plot3dsurfaceorthoprojectionstatusitem_ =
      boolManager_->addProperty(tr("Ortho Projection"));
  ;
  plot3dsurfacepolarstatusitem_ =
      boolManager_->addProperty(tr("Polar Coords X"));
  // plot3D Bar
  plot3dbarspacingxitem_ = doubleManager_->addProperty(tr("Spacing X"));
  plot3dbarspacingyitem_ = doubleManager_->addProperty(tr("Spacing Y"));
  plot3dbarspacingrelativeitem_ =
      boolManager_->addProperty(tr("Relative Spacing"));
  plot3dbarthicknessitem_ = doubleManager_->addProperty(tr("Thickness"));
  plot3dbaraspectratioitem_ = doubleManager_->addProperty(tr("Aspectratio"));
  plot3dbarhorizontalaspectratioitem_ =
      doubleManager_->addProperty(tr("Horizontal Aspectratio"));
  plot3dbarshadowqualityitem_ = enumManager_->addProperty(tr("Shadow Quality"));
  enumManager_->setEnumNames(plot3dbarshadowqualityitem_, shadowquality);
  plot3dbarorthoprojectionstatusitem_ =
      boolManager_->addProperty(tr("Ortho Projection"));
  ;
  plot3dbarpolarstatusitem_ = boolManager_->addProperty(tr("Polar Coords X"));
  // Plot3D Scatter
  plot3dscatteraspectratioitem_ =
      doubleManager_->addProperty(tr("Aspectratio"));
  plot3dscatterhorizontalaspectratioitem_ =
      doubleManager_->addProperty(tr("Horizontal Aspectratio"));
  plot3dscattershadowqualityitem_ =
      enumManager_->addProperty(tr("Shadow Quality"));
  enumManager_->setEnumNames(plot3dscattershadowqualityitem_, shadowquality);
  plot3dscatterorthoprojectionstatusitem_ =
      boolManager_->addProperty(tr("Ortho Projection"));
  ;
  plot3dscatterpolarstatusitem_ =
      boolManager_->addProperty(tr("Polar Coords X"));
  // Plot3D Surface Series
  QStringList drawmodelist;
  QStringList meshlist;
  QStringList colorstylelist;
  drawmodelist << QString::fromLatin1("Wireframe")
               << QString::fromLatin1("Surface")
               << QString::fromLatin1("WireframeAndSurface");
  meshlist << QString::fromLatin1("MeshBar")
           << QString::fromLatin1("MeshCube")
           << QString::fromLatin1("MeshPyramid")
           << QString::fromLatin1("MeshCone")
           << QString::fromLatin1("MeshCylinder")
           << QString::fromLatin1("MeshBevelBar")
           << QString::fromLatin1("MeshBevelCube")
           << QString::fromLatin1("MeshSphere")
           << QString::fromLatin1("MeshMinimal")
           << QString::fromLatin1("MeshArrow")
           << QString::fromLatin1("MeshPoint");
  colorstylelist << QString::fromLatin1("Solid Color")
                 << QString::fromLatin1("Gradient Full")
                 << QString::fromLatin1("Gradient Range");
  QStringList gradientlist3d;
  gradientlist3d << QString::fromLatin1("Grayscale")
                 << QString::fromLatin1("Hot")
                 << QString::fromLatin1("Cold")
                 << QString::fromLatin1("Night")
                 << QString::fromLatin1("Candy")
                 << QString::fromLatin1("Geography")
                 << QString::fromLatin1("Ion")
                 << QString::fromLatin1("Thermal")
                 << QString::fromLatin1("Polar")
                 << QString::fromLatin1("Spectrum")
                 << QString::fromLatin1("Jet")
                 << QString::fromLatin1("Hues")
                 << QString::fromLatin1("BBRY")
                 << QString::fromLatin1("GYRD");
  plot3dsurfaceseriesvisibleitem_ = boolManager_->addProperty(tr("Visible"));
  plot3dsurfaceseriesflatshadingstatusitem_ =
      boolManager_->addProperty(tr("Flat Shading"));
  plot3dsurfaceseriesdrawitem_ = enumManager_->addProperty(QString::fromLatin1("Draw"));
  enumManager_->setEnumNames(plot3dsurfaceseriesdrawitem_, drawmodelist);
  plot3dsurfaceseriesmeshsmoothitem_ =
      boolManager_->addProperty(tr("Mesh Smooth"));
  plot3dsurfaceseriescolorstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Color Style"));
  enumManager_->setEnumNames(plot3dsurfaceseriescolorstyleitem_,
                             colorstylelist);
  plot3dsurfaceseriesbasecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Color"));
  plot3dsurfaceseriesbasegradiantitem_ =
      enumManager_->addProperty(QString::fromLatin1("Gradient Color"));
  enumManager_->setEnumNames(plot3dsurfaceseriesbasegradiantitem_,
                             gradientlist3d);
  plot3dsurfaceserieshighlightcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Highlight Color"));
  // Plot3D Bar Series
  plot3dbarseriesvisibleitem_ = boolManager_->addProperty(tr("Visible"));
  plot3dbarseriesmeshitem_ = enumManager_->addProperty(QString::fromLatin1("Mesh"));
  enumManager_->setEnumNames(plot3dbarseriesmeshitem_, meshlist);
  plot3dbarseriesmeshsmoothitem_ = boolManager_->addProperty(tr("Mesh Smooth"));
  plot3dbarseriescolorstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Color Style"));
  enumManager_->setEnumNames(plot3dbarseriescolorstyleitem_, colorstylelist);
  plot3dbarseriesbasecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Color"));
  plot3dbarseriesbasegradiantitem_ =
      enumManager_->addProperty(QString::fromLatin1("Gradient Color"));
  enumManager_->setEnumNames(plot3dbarseriesbasegradiantitem_, gradientlist3d);
  plot3dbarserieshighlightcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Highlight Color"));
  // Plot3D Scatter Series
  plot3dscatterseriesvisibleitem_ = boolManager_->addProperty(tr("Visible"));
  plot3dscatterseriessizeitem_ = doubleManager_->addProperty(tr("Size"));
  plot3dscatterseriesmeshitem_ = enumManager_->addProperty(QString::fromLatin1("Mesh"));
  enumManager_->setEnumNames(plot3dscatterseriesmeshitem_, meshlist);
  plot3dscatterseriesmeshsmoothitem_ =
      boolManager_->addProperty(tr("Mesh Smooth"));
  plot3dscatterseriescolorstyleitem_ = enumManager_->addProperty(QString::fromLatin1("Color Style"));
  enumManager_->setEnumNames(plot3dscatterseriescolorstyleitem_,
                             colorstylelist);
  plot3dscatterseriesbasecoloritem_ = colorManager_->addProperty(QString::fromLatin1("Color"));
  plot3dscatterseriesbasegradiantitem_ =
      enumManager_->addProperty(QString::fromLatin1("Gradient Color"));
  enumManager_->setEnumNames(plot3dscatterseriesbasegradiantitem_,
                             gradientlist3d);
  plot3dscatterserieshighlightcoloritem_ =
      colorManager_->addProperty(QString::fromLatin1("Highlight Color"));

  // Table
  tablewindowrowcountitem_ = intManager_->addProperty(QString::fromLatin1("Row Count"));
  tablewindowcolcountitem_ = intManager_->addProperty(QString::fromLatin1("Column Count"));
  // Matrix
  matrixwindowrowcountitem_ = intManager_->addProperty(QString::fromLatin1("Row Count"));
  matrixwindowcolcountitem_ = intManager_->addProperty(QString::fromLatin1("Column Count"));
  intManager_->setRange(tablewindowrowcountitem_, 0, 100000000);
  intManager_->setRange(tablewindowcolcountitem_, 0, 100000);
  intManager_->setRange(matrixwindowrowcountitem_, 0, 100000);
  intManager_->setRange(matrixwindowcolcountitem_, 0, 100000);

  // initiate property ID required for compare()
  setObjectPropertyId();

  connect(objectbrowser_,
          SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
          SLOT(selectObjectItem(QTreeWidgetItem *)));
  connect(objectbrowser_, &MyPlotTreeWidget::activate,
          [=](MyWidget *widget) { app_->activateWindow(widget); });
  connect(objectbrowser_, &MyPlotTreeWidget::itemRootContextMenuRequested, app_,
          &Gui::MainAlphaPlot::showWindowTitleBarMenu);
  connect(objectbrowser_, &MyPlotTreeWidget::itemContextMenuRequested, app_,
          &Gui::MainAlphaPlot::itemContextMenuRequested);
  connect(boolManager_, SIGNAL(valueChanged(QtProperty *, bool)), this,
          SLOT(valueChange(QtProperty *, const bool &)));
  connect(colorManager_, SIGNAL(valueChanged(QtProperty *, QColor)), this,
          SLOT(valueChange(QtProperty *, const QColor &)));
  connect(rectManager_, SIGNAL(valueChanged(QtProperty *, QRect)), this,
          SLOT(valueChange(QtProperty *, const QRect &)));
  connect(doubleManager_, SIGNAL(valueChanged(QtProperty *, double)), this,
          SLOT(valueChange(QtProperty *, const double &)));
  connect(stringManager_, SIGNAL(valueChanged(QtProperty *, QString)), this,
          SLOT(valueChange(QtProperty *, const QString &)));
  connect(intManager_, SIGNAL(valueChanged(QtProperty *, int)), this,
          SLOT(valueChange(QtProperty *, const int)));
  connect(enumManager_, SIGNAL(valueChanged(QtProperty *, int)), this,
          SLOT(enumValueChange(QtProperty *, const int)));
  connect(fontManager_, SIGNAL(valueChanged(QtProperty *, QFont)), this,
          SLOT(valueChange(QtProperty *, const QFont &)));
  connect(datetimeManager_, &QtDateTimePropertyManager::valueChanged, this,
          &PlotPropertyEditor::datetimeValueChange);
  connect(sizeManager_, SIGNAL(valueChanged(QtProperty *, QSize)), this,
          SLOT(valueChange(QtProperty *, const QSize &)));
  connect(this, &PlotPropertyEditor::refreshCanvasRect, [=]() {
    QTreeWidgetItem *item = objectbrowser_->currentItem();
    if (item && static_cast<MyPlotTreeWidget::PropertyItemType>(
                    item->data(0, Qt::UserRole).value<int>()) ==
                    MyPlotTreeWidget::PropertyItemType::Plot2DCanvas) {
      Plot2D *plotcanvas =
          getgraph2dobject<Plot2D>(objectbrowser_->currentItem());
      sizeManager_->setValue(canvaspropertysizeitem_,
                             QSize(plotcanvas->geometry().width(),
                                   plotcanvas->geometry().height()));
    }
    if (item && static_cast<MyPlotTreeWidget::PropertyItemType>(
                    item->data(0, Qt::UserRole).value<int>()) ==
                    MyPlotTreeWidget::PropertyItemType::Plot2DLayout) {
      AxisRect2D *axisrect =
          getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
      rectManager_->setValue(layoutpropertyrectitem_, axisrect->outerRect());
    }
  });
  connect(this, &PlotPropertyEditor::rescaleAxis2D, [=](Axis2D *axis) {
    QTreeWidgetItem *item = objectbrowser_->currentItem();
    if (item && static_cast<MyPlotTreeWidget::PropertyItemType>(
                    item->data(0, Qt::UserRole).value<int>()) ==
                    MyPlotTreeWidget::PropertyItemType::Plot2DAxis) {
      Axis2D *ax = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
      if (ax == axis && ax) {
        switch (ax->gettickertype_axis()) {
          case Axis2D::TickerType::Text:
          case Axis2D::TickerType::Log:
          case Axis2D::TickerType::Value:
          case Axis2D::TickerType::Pi:
          case Axis2D::TickerType::Time:
            doubleManager_->setValue(axispropertyfromitem_,
                                     axis->getfrom_axis());
            doubleManager_->setValue(axispropertytoitem_, axis->getto_axis());
            break;
          case Axis2D::TickerType::DateTime:
            datetimeManager_->setValue(
                axispropertytickerdatetimefrom_,
                QCPAxisTickerDateTime::keyToDateTime(axis->getfrom_axis()));
            datetimeManager_->setValue(
                axispropertytickerdatetimeto_,
                QCPAxisTickerDateTime::keyToDateTime(axis->getto_axis()));
            break;
        }
      }
    }
  });
}

PlotPropertyEditor::~PlotPropertyEditor() {  }

MyPlotTreeWidget *PlotPropertyEditor::getObjectBrowser() { return objectbrowser_; }

void PlotPropertyEditor::myWidgetConnections(MyWidget *widget) {
  connect(widget, &MyWidget::geometrychange, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::MyWidgetWindow) {
      MyWidget *mw = getgraph2dobject<MyWidget>(objectbrowser_->currentItem());
      if (widget == mw) {
        rectManager_->setValue(mywidgetwindowrectitem_, widget->geometry());
      }
    }
  });
}

void PlotPropertyEditor::tableConnections(Table *table) {
  connect(table, &Table::modifiedWindow, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) == MyPlotTreeWidget::PropertyItemType::TableWindow) {
      Table *tab = getgraph2dobject<Table>(objectbrowser_->currentItem());
      if (table == tab) {
        intManager_->setValue(tablewindowrowcountitem_, table->numRows());
        intManager_->setValue(tablewindowcolcountitem_, table->numCols());
      }
    }
  });
}

void PlotPropertyEditor::matrixConnections(Matrix *matrix) {
  connect(matrix, &Matrix::modifiedWindow, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::MatrixWindow) {
      Matrix *mat = getgraph2dobject<Matrix>(objectbrowser_->currentItem());
      if (matrix == mat) {
        intManager_->setValue(matrixwindowrowcountitem_, matrix->numRows());
        intManager_->setValue(matrixwindowcolcountitem_, matrix->numCols());
      }
    }
  });
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const bool value) {
  if (prop->compare(canvaspropertyopenglitem_)) {
    Plot2D *plot = getgraph2dobject<Plot2D>(objectbrowser_->currentItem());
    plot->setOpenGl(value);
    plot->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(layoutpropertyautomarginstatusitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    (value) ? axisrect->setAutoMargins(QCP::MarginSide::msAll)
            : axisrect->setAutoMargins(QCP::MarginSide::msNone);
    intManager_->setValue(layoutpropertyleftmarginitem_,
                          axisrect->margins().left());
    intManager_->setValue(layoutpropertyrightmarginitem_,
                          axisrect->margins().right());
    intManager_->setValue(layoutpropertytopmarginitem_,
                          axisrect->margins().top());
    intManager_->setValue(layoutpropertybottommarginitem_,
                          axisrect->margins().bottom());
    if (value) {
      layoutpropertytopmarginitem_->setEnabled(false);
      layoutpropertyleftmarginitem_->setEnabled(false);
      layoutpropertybottommarginitem_->setEnabled(false);
      layoutpropertyrightmarginitem_->setEnabled(false);
    } else {
      layoutpropertytopmarginitem_->setEnabled(true);
      layoutpropertyleftmarginitem_->setEnabled(true);
      layoutpropertybottommarginitem_->setEnabled(true);
      layoutpropertyrightmarginitem_->setEnabled(true);
    }
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(axispropertyvisibleitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setshowhide_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(hmajgridpropertyvisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMajorGridVisible(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmingridpropertyvisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMinorGridVisible(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmajgridpropertyzerolinevisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setZerothLineVisible(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertyvisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMajorGridVisible(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmingridpropertyvisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMinorGridVisible(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertyzerolinevisibleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setZerothLineVisible(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(axispropertyinvertitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setinverted_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyantialiaseditem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setantialiased_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickvisibilityitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->settickvisibility_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubtickvisibilityitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubtickvisibility_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklabelvisibilityitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelvisibility_axis(value);
    axis->parentPlot()->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(itempropertylegendvisibleitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->sethidden_legend(value);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendtitlevisibleitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    itempropertylegendtitletextitem_->setEnabled(value);
    itempropertylegendtitlefontitem_->setEnabled(value);
    itempropertylegendtitlecoloritem_->setEnabled(value);
    (value) ? legend->addtitle_legend() : legend->removetitle_legend();
    legend->layer()->replot();
  } else if (prop->compare(itempropertytextantialiaseditem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setAntialiased(value);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylineantialiaseditem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setAntialiased(value);
    lineitem->layer()->replot();
  } else if (prop->compare(lsplotpropertylinefillstatusitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinefillstatus_lsplot(value);
    lsgraph->setlinefillstyle_lsplot(static_cast<Qt::BrushStyle>(
        enumManager_->value(lsplotpropertylinefillstyleitem_) + 1));
    objectbrowser_->currentItem()->setIcon(0, lsgraph->getIcon());
    lsgraph->layer()->replot();
  } else if (prop->compare(lsplotpropertylineantialiaseditem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlineantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterantialiaseditem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscatterantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(lsplotpropertylegendvisibleitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsplotpropertylegendtextitem_->setEnabled(value);
    lsgraph->setlegendvisible_lsplot(value);
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylineantialiaseditem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlineantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterantialiaseditem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(channel2plotpropertylineantialiaseditem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlineantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterantialiaseditem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterantialiased_lsplot(value);
    lsgraph->layer()->replot();
  } else if (prop->compare(channelplotpropertylegendvisibleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    channelplotpropertylegendtextitem_->setEnabled(value);
    lsgraph->setlegendvisible_lsplot(value);
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylinefillstatusitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinefillstatus_cplot(value);
    curve->setlinefillstyle_cplot(static_cast<Qt::BrushStyle>(
        enumManager_->value(cplotpropertylinefillstyleitem_) + 1));
    objectbrowser_->currentItem()->setIcon(0, curve->getIcon());
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylineantialiaseditem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlineantialiased_cplot(value);
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterantialiaseditem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscatterantialiased_cplot(value);
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertylegendvisibleitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    cplotpropertylegendtextitem_->setEnabled(value);
    curve->setlegendvisible_cplot(value);
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertyfillantialiaseditem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setAntialiasedFill(value);
    bar->layer()->replot();
  } else if (prop->compare(barplotpropertyantialiaseditem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setAntialiased(value);
    bar->layer()->replot();
  } else if (prop->compare(barplotpropertyhistautobinstatusitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setHistAutoBin(value);
    if (bar->getdatablock_histplot()->getautobin()) {
      barplotpropertyhistbeginitem_->setEnabled(false);
      barplotpropertyhistenditem_->setEnabled(false);
      barplotpropertyhistbinitem_->setEnabled(false);
    } else {
      barplotpropertyhistbeginitem_->setEnabled(true);
      barplotpropertyhistenditem_->setEnabled(true);
      barplotpropertyhistbinitem_->setEnabled(true);
    }
    bar->layer()->replot();
  } else if (prop->compare(statboxplotpropertyantialiaseditem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setAntialiased(value);
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyfillantialiaseditem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setAntialiasedFill(value);
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyfillstatusitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setfillstatus_statbox(value);
    statbox->setfillstyle_statbox(static_cast<Qt::BrushStyle>(
        enumManager_->value(statboxplotpropertyfillstyleitem_) + 1));
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerantialiaseditem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setWhiskerAntialiased(value);
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatterantialiaseditem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setAntialiasedScatters(value);
    statbox->layer()->replot();
  } else if (prop->compare(vectorpropertylineantialiaseditem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setlineantialiased_vecplot(value);
    vector->parentPlot()->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(vectorpropertylegendvisibleitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vectorpropertylegendtextitem_->setEnabled(value);
    vector->setlegendvisible_vecplot(value);
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(colormappropertyinterpolateitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setInterpolate(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertytightboundaryitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setTightBoundary(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertygradientinvertitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setgradientinverted_colormap(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertygradientperiodicitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setgradientperiodic_colormap(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscalevisibleitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->setVisible(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisvisibleitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setVisible(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisinvertitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setRangeReversed(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisantialiaseditem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setAntialiased(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxistickvisibilityitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTicks(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxissubtickvisibilityitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setSubTicks(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelvisibilityitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabels(value);
    colormap->layer()->replot();
  } else if (prop->compare(errorbarpropertyfillstatusitem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    errorbar->setfillstatus_errorbar(value);
    errorbar->layer()->replot();
  } else if (prop->compare(errorbarpropertyantialiaseditem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    errorbar->setAntialiasedFill(value);
    errorbar->setAntialiasedScatters(value);
    errorbar->setAntialiased(value);
    errorbar->layer()->replot();
  } else if (prop->compare(plot3dcanvasbackgroundvisibleitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setBackgroundEnabled(value);
  } else if (prop->compare(plot3dcanvasgridvisibleitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setGridEnabled(value);
  } else if (prop->compare(plot3dcanvaslabelbackgroundvisibleitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLabelBackgroundEnabled(value);
  } else if (prop->compare(plot3dcanvaslabelbordervisibleitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLabelBorderEnabled(value);
  } else if (prop->compare(plot3daxisvalueautoadjustrangeitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setAutoAdjustRange(value);
  } else if (prop->compare(plot3daxisvaluetitlevisibleitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setTitleVisible(value);
  } else if (prop->compare(plot3daxisvaluetitlefixeditem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setTitleFixed(value);
  } else if (prop->compare(plot3dvalueaxisreverseitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setReversed(value);
  } else if (prop->compare(plot3daxiscatagoryautoadjustrangeitem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setAutoAdjustRange(value);
  } else if (prop->compare(plot3daxiscatagorytitlevisibleitem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setTitleVisible(value);
  } else if (prop->compare(plot3daxiscatagorytitlefixeditem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setTitleFixed(value);
  } else if (prop->compare(plot3dsurfacefliphorizontalgriditem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setFlipHorizontalGrid(value);
  } else if (prop->compare(plot3dbarspacingrelativeitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setBarSpacingRelative(value);
  } else if (prop->compare(plot3dsurfaceorthoprojectionstatusitem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setOrthoProjection(value);
  } else if (prop->compare(plot3dsurfacepolarstatusitem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setPolar(value);
  } else if (prop->compare(plot3dbarorthoprojectionstatusitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setOrthoProjection(value);
  } else if (prop->compare(plot3dbarpolarstatusitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setPolar(value);
  } else if (prop->compare(plot3dscatterorthoprojectionstatusitem_)) {
    Scatter3D *scatter =
        getgraph2dobject<Scatter3D>(objectbrowser_->currentItem());
    scatter->getGraph()->setOrthoProjection(value);
  } else if (prop->compare(plot3dscatterpolarstatusitem_)) {
    Scatter3D *scatter =
        getgraph2dobject<Scatter3D>(objectbrowser_->currentItem());
    scatter->getGraph()->setPolar(value);
  } else if (prop->compare(plot3dsurfaceseriesvisibleitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setVisible(value);
  } else if (prop->compare(plot3dsurfaceseriesflatshadingstatusitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setFlatShadingEnabled(value);
  } else if (prop->compare(plot3dsurfaceseriesmeshsmoothitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setMeshSmooth(value);
  } else if (prop->compare(plot3dbarseriesvisibleitem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setVisible(value);
  } else if (prop->compare(plot3dbarseriesmeshsmoothitem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setMeshSmooth(value);
  } else if (prop->compare(plot3dscatterseriesvisibleitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setVisible(value);
  } else if (prop->compare(plot3dscatterseriesmeshsmoothitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setMeshSmooth(value);
  } else {
    qDebug() << QString::fromLatin1("unknown bool property item");
  }
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const QColor &color) {
  disconnect(colorManager_, SIGNAL(valueChanged(QtProperty *, QColor)), this,
             SLOT(valueChange(QtProperty *, const QColor &)));
  if (prop->compare(canvaspropertycoloritem_)) {
    Plot2D *plotcanvas =
        getgraph2dobject<Plot2D>(objectbrowser_->currentItem());
    plotcanvas->setBackgroundColor(color);
    plotcanvas->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(layoutpropertycoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QBrush brush = axisrect->backgroundBrush();
    brush.setColor(color);
    axisrect->setBackground(brush);
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(hmajgridpropertystrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMajorGridColor(color);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmajgridpropertyzerolinestrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setZerothLineColor(color);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmingridpropertystrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMinorGridColor(color);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertystrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMajorGridColor(color);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertyzerolinestrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setZerothLineColor(color);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmingridpropertystrokecoloritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMinorGridColor(color);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(axispropertystrokecoloritem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setstrokecolor_axis(color);
    axis->layer()->replot();
  } else if (prop->compare(axispropertylabelcoloritem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setlabelcolor_axis(color);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickstrokecoloritem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->settickstrokecolor_axis(color);
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubtickstrokecoloritem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubtickstrokecolor_axis(color);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklabelcoloritem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelcolor_axis(color);
    axis->layer()->replot();
  } else if (prop->compare(itempropertylegendtextcoloritem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setTextColor(color);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendborderstrokecoloritem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setborderstrokecolor_legend(color);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendbackgroundcoloritem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QBrush b = legend->brush();
    b.setColor(color);
    legend->setBrush(b);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendtitlecoloritem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->settitlecolor_legend(color);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendtitlecoloritem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->settitlecolor_legend(color);
    legend->layer()->replot();
  } else if (prop->compare(itempropertytextcoloritem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setColor(color);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextstrokecoloritem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setstrokecolor_textitem(color);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextbackgroundcoloritem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    QBrush b = textitem->brush();
    b.setColor(color);
    textitem->setBrush(b);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylinestrokecoloritem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setstrokecolor_lineitem(color);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertyimagestrokecoloritem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    imageitem->setstrokecolor_imageitem(color);
    imageitem->layer()->replot();
  } else if (prop->compare(lsplotpropertylinestrokecoloritem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinestrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertylinefillcoloritem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinefillcolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterfillcoloritem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscatterfillcolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterstrokecoloritem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscatterstrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinestrokecoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinefillcoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinefillcolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterfillcoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterfillcolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterstrokecoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertylinestrokecoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterfillcoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterfillcolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterstrokecoloritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokecolor_lsplot(color);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylinestrokecoloritem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinestrokecolor_cplot(color);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylinefillcoloritem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinefillcolor_cplot(color);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterfillcoloritem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscatterfillcolor_cplot(color);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterstrokecoloritem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscatterstrokecolor_cplot(color);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertyfillcoloritem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setfillcolor_barplot(color);
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertystrokecoloritem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setstrokecolor_barplot(color);
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyfillcoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setfillcolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyboxoutlinecoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    QPen p = statbox->pen();
    p.setColor(color);
    statbox->setPen(p);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerstrokecoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerstrokecolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerbarstrokecoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerbarstrokecolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertymedianstrokecoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setmedianstrokecolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatterfillcoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscatterfillcolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatteroutlinecoloritem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscatterstrokecolor_statbox(color);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylinestrokecoloritem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setlinestrokecolor_vecplot(color);
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(pieplotpropertylinestrokecoloritem_)) {
    Pie2D *pie = getgraph2dobject<Pie2D>(objectbrowser_->currentItem());
    pie->setstrokecolor_pieplot(color);
    pie->layer()->replot();
    pie->getaxisrect()->getLegend()->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisstrokecoloritem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->basePen();
    p.setColor(color);
    colormap->getcolormapscale_colormap()->axis()->setBasePen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxislabelcoloritem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setLabelColor(color);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxistickstrokecoloritem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->tickPen();
    p.setColor(color);
    colormap->getcolormapscale_colormap()->axis()->setTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxissubtickstrokecoloritem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->subTickPen();
    p.setColor(color);
    colormap->getcolormapscale_colormap()->axis()->setSubTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelcoloritem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabelColor(color);
    colormap->layer()->replot();
  } else if (prop->compare(errorbarpropertystrokecoloritem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    QPen p = errorbar->pen();
    p.setColor(color);
    errorbar->setPen(p);
    errorbar->layer()->replot();
  } else if (prop->compare(errorbarpropertyfillcoloritem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    QBrush b = errorbar->brush();
    b.setColor(color);
    errorbar->setBrush(b);
    errorbar->layer()->replot();
  } else if (prop->compare(plot3dcanvaswindowcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setWindowColor(color);
  } else if (prop->compare(plot3dcanvasbackgroundcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setBackgroundColor(color);
  } else if (prop->compare(plot3dcanvaslightcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLightColor(color);
  } else if (prop->compare(plot3dcanvasgridcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setGridLineColor(color);
  } else if (prop->compare(plot3dcanvaslabelbackgroundcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLabelBackgroundColor(color);
  } else if (prop->compare(plot3dcanvaslabeltextcoloritem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLabelTextColor(color);
  } else if (prop->compare(plot3dsurfaceseriesbasecoloritem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setBaseColor(color);
  } else if (prop->compare(plot3dsurfaceserieshighlightcoloritem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setSingleHighlightColor(color);
  } else if (prop->compare(plot3dbarseriesbasecoloritem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setBaseColor(color);
  } else if (prop->compare(plot3dbarserieshighlightcoloritem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setSingleHighlightColor(color);
  } else if (prop->compare(plot3dscatterseriesbasecoloritem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setBaseColor(color);
  } else if (prop->compare(plot3dscatterserieshighlightcoloritem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setSingleHighlightColor(color);
  } else
    qDebug() << QString::fromLatin1("unknown color item");

  connect(colorManager_, SIGNAL(valueChanged(QtProperty *, QColor)), this,
          SLOT(valueChange(QtProperty *, const QColor &)));
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const QRect &rect) {
  if (prop->compare(mywidgetwindowrectitem_)) {
    MyWidget *widget =
        getgraph2dobject<MyWidget>(objectbrowser_->currentItem());
    if (widget->geometry() == rect) return;
    widget->setGeometry(rect);
  } else if (prop->compare(itempropertylegendmarginitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QMargins margin;
    margin.setLeft(rect.left());
    margin.setTop(rect.top());
    margin.setRight(rect.right());
    margin.setBottom(rect.bottom());
    legend->setMargins(margin);
    legend->layer()->replot();
  } else if (prop->compare(itempropertytextmarginitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    QMargins margin;
    margin.setLeft(rect.left());
    margin.setTop(rect.top());
    margin.setRight(rect.right());
    margin.setBottom(rect.bottom());
    textitem->setPadding(margin);
    textitem->layer()->replot();
  } else
    qDebug() << QString::fromLatin1("unknown QRect Item");
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const double &value) {
  if (prop->compare(canvaspropertybufferdevicepixelratioitem_)) {
    Plot2D *plot = getgraph2dobject<Plot2D>(objectbrowser_->currentItem());
    plot->setBufferDevicePixelRatio(value);
    plot->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(layoutpropertyrowstreachfactoritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 2)
                    .value<void *>();
    Layout2D *layout2d = static_cast<Layout2D *>(ptr);
    QPair<int, int> rowcol = layout2d->getAxisRectRowCol(axisrect);
    layout2d->getLayoutGrid()->setRowStretchFactor(rowcol.first, value);
    layout2d->getPlotCanwas()->replot(
        QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(layoutpropertycolumnstreachfactoritem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 2)
                    .value<void *>();
    Layout2D *layout2d = static_cast<Layout2D *>(ptr);
    QPair<int, int> rowcol = layout2d->getAxisRectRowCol(axisrect);
    layout2d->getLayoutGrid()->setColumnStretchFactor(rowcol.second, value);
    layout2d->getPlotCanwas()->replot(
        QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(hmajgridpropertystrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMajorGridThickness(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmajgridpropertyzerolinestrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setZerothLineThickness(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmingridpropertystrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMinorGridThickness(value);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertystrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMajorGridThickness(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertyzerolinestrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setZerothLineThickness(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmingridpropertystrokethicknessitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMinorGridThickness(value);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(axispropertyfromitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setRangeLower(value);
    axis->parentPlot()->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(axispropertytoitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setRangeUpper(value);
    axis->parentPlot()->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  } else if (prop->compare(axispropertystrokethicknessitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setstrokethickness_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickoriginitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticksorigin(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickstrokethicknessitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->settickstrokethickness_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubtickstrokethicknessitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubtickstrokethickness_axis(value);
    axis->layer()->replot();
  }
  // this seems to crash the application some how
  /*else if (prop->compare(axispropertytickervaluetickstep_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerFixed> valueticker =
        qSharedPointerCast<QCPAxisTickerFixed>(axis->getticker_axis());
    valueticker->setTickStep(value);
    axis->setTicker(valueticker);
    axis->layer()->replot();
  }*/
  else if (prop->compare(axispropertytickerlogbase_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerLog> logticker =
        qSharedPointerCast<QCPAxisTickerLog>(axis->getticker_axis());
    logticker->setLogBase(value);
    axis->setTicker(logticker);
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertytickersymbolvalue_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerPi> piticker =
        qSharedPointerCast<QCPAxisTickerPi>(axis->getticker_axis());
    piticker->setPiValue(value);
    axis->setTicker(piticker);
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertyticklabelrotationitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelrotation_axis(value);
    axis->parentPlot()->replot();
  } else if (prop->compare(itempropertylegendoriginxitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QPointF origin = legend->getposition_legend();
    origin.setX(value);
    if (origin != legend->getposition_legend()) {
      legend->setposition_legend(origin);
      legend->layer()->replot();
    }
  } else if (prop->compare(itempropertylegendoriginyitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QPointF origin = legend->getposition_legend();
    origin.setY(value);
    if (origin != legend->getposition_legend()) {
      legend->setposition_legend(origin);
      legend->layer()->replot();
    }
  } else if (prop->compare(itempropertylegendborderstrokethicknessitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setborderstrokethickness_legend(value);
    legend->layer()->replot();
  } else if (prop->compare(itempropertytextpixelpositionxitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    QPointF point = textitem->position->pixelPosition();
    point.setX(value);
    textitem->setpixelposition_textitem(point);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextpixelpositionyitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    QPointF point = textitem->position->pixelPosition();
    point.setY(value);
    textitem->setpixelposition_textitem(point);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextstrokethicknessitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setstrokethickness_textitem(value);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylinestrokethicknessitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setstrokethickness_lineitem(value);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertytextrotationitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setRotation(value);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylinepixelpositionx1item_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    QPointF point = lineitem->position(QString::fromLatin1("start"))->pixelPosition();
    point.setX(value);
    lineitem->position(QString::fromLatin1("start"))->setPixelPosition(point);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinepixelpositiony1item_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    QPointF point = lineitem->position(QString::fromLatin1("start"))->pixelPosition();
    point.setY(value);
    lineitem->position(QString::fromLatin1("start"))->setPixelPosition(point);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinepixelpositionx2item_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    QPointF point = lineitem->position(QString::fromLatin1("end"))->pixelPosition();
    point.setX(value);
    lineitem->position(QString::fromLatin1("end"))->setPixelPosition(point);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinepixelpositiony2item_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    QPointF point = lineitem->position(QString::fromLatin1("end"))->pixelPosition();
    point.setY(value);
    lineitem->position(QString::fromLatin1("end"))->setPixelPosition(point);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylineendingwidthitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendwidth_lineitem(value, LineItem2D::LineEndLocation::Stop);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylineendinglengthitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendlength_lineitem(value, LineItem2D::LineEndLocation::Stop);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinestartingwidthitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendwidth_lineitem(value, LineItem2D::LineEndLocation::Start);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinestartinglengthitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendlength_lineitem(value, LineItem2D::LineEndLocation::Start);
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertyimagepixelpositionxitem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    QPointF point = imageitem->position(QString::fromLatin1("topLeft"))->pixelPosition();
    point.setX(value);
    imageitem->setposition_imageitem(point);
    imageitem->layer()->replot();
  } else if (prop->compare(itempropertyimagepixelpositionyitem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    QPointF point = imageitem->position(QString::fromLatin1("topLeft"))->pixelPosition();
    point.setY(value);
    imageitem->setposition_imageitem(point);
    imageitem->layer()->replot();
  } else if (prop->compare(itempropertyimagestrokethicknessitem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    imageitem->setstrokethickness_imageitem(value);
    imageitem->layer()->replot();
  } else if (prop->compare(lsplotpropertylinestrokethicknessitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinestrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterthicknessitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscattersize_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterstrokethicknessitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscatterstrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinestrokethicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterthicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscattersize_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterstrokethicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertylinestrokethicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterthicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscattersize_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterstrokethicknessitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokethickness_lsplot(value);
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylinestrokethicknessitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinestrokethickness_cplot(value);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterthicknessitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscattersize_cplot(value);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterstrokethicknessitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscatterstrokethickness_cplot(value);
    curve->layer()->replot();
    curve->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertywidthitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setWidth(value);
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertystackgapitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    (bar->getBarStyle() == Bar2D::BarStyle::Grouped)
        ? bar->getBarGroup()->setSpacing(value)
        : bar->setStackingGap(value);
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertystrokethicknessitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setstrokethickness_barplot(value);
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertyhistbinitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    if (!bar->getdatablock_histplot()->getautobin()) bar->setHistBinSize(value);
    bar->layer()->replot();
  } else if (prop->compare(barplotpropertyhistbeginitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    if (bar->getdatablock_histplot()->getend() > value) {
      if (!bar->getdatablock_histplot()->getautobin()) {
        bar->setHistBegin(value);
        bar->layer()->replot();
      }
    } else {
      doubleManager_->setValue(barplotpropertyhistbeginitem_,
                               bar->getdatablock_histplot()->getbegin());
    }
  } else if (prop->compare(barplotpropertyhistenditem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    if (bar->getdatablock_histplot()->getbegin() < value) {
      if (!bar->getdatablock_histplot()->getautobin()) {
        bar->setHistEnd(value);
        bar->layer()->replot();
      }
    } else {
      doubleManager_->setValue(barplotpropertyhistenditem_,
                               bar->getdatablock_histplot()->getend());
    }
  } else if (prop->compare(statboxplotpropertywidthitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setWidth(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerwidthitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setWhiskerWidth(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyboxoutlinethicknessitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    QPen p = statbox->pen();
    p.setWidthF(value);
    statbox->setPen(p);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerstrokethicknessitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerstrokethickness_statbox(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerbarstrokethicknessitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerbarstrokethickness_statbox(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertymideanstrokethicknessitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setmedianstrokethickness_statbox(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscattersizeitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscattersize_statbox(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatteroutlinethicknessitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscatterstrokethickness_statbox(value);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylinestrokethicknessitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setlinestrokethickness_vecplot(value);
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylineendingheightitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setendheight_vecplot(value, Vector2D::LineEndLocation::Head);
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylineendingwidthitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setendwidth_vecplot(value, Vector2D::LineEndLocation::Head);
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(pieplotpropertylinestrokethicknessitem_)) {
    Pie2D *pie = getgraph2dobject<Pie2D>(objectbrowser_->currentItem());
    pie->setstrokethickness_pieplot(value);
    pie->layer()->replot();
    pie->getaxisrect()->getLegend()->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisfromitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setRangeLower(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxistoitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setRangeUpper(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisstrokethicknessitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->basePen();
    p.setWidthF(value);
    colormap->getcolormapscale_colormap()->axis()->setBasePen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxistickstrokethicknessitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->tickPen();
    p.setWidthF(value);
    colormap->getcolormapscale_colormap()->axis()->setTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(
                 colormappropertyscaleaxissubtickstrokethicknessitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->subTickPen();
    p.setWidthF(value);
    colormap->getcolormapscale_colormap()->axis()->setSubTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelrotationitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabelRotation(value);
    colormap->layer()->replot();
  } else if (prop->compare(errorbarpropertywhiskerwidthitem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    errorbar->setWhiskerWidth(value);
    errorbar->layer()->replot();
  } else if (prop->compare(errorbarpropertysymbolgaptem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    errorbar->setSymbolGap(value);
    errorbar->layer()->replot();
  } else if (prop->compare(errorbarpropertystrokethicknessitem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    QPen p = errorbar->pen();
    p.setWidthF(value);
    errorbar->setPen(p);
    errorbar->layer()->replot();
  } else if (prop->compare(plot3dcanvasambientlightstrengthitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setAmbientLightStrength(value);
  } else if (prop->compare(plot3dcanvaslightstrengthitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setLightStrength(value);
  } else if (prop->compare(plot3daxisvaluerangeloweritem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setMin(value);
  } else if (prop->compare(plot3daxisvaluerangeupperitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setMax(value);
  } else if (prop->compare(plot3daxisvalueticklabelrotationitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setLabelAutoRotation(value);
  } else if (prop->compare(plot3daxiscatagoryrangeloweritem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setMin(value);
  } else if (prop->compare(plot3daxiscatagoryrangeupperitem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setMax(value);
  } else if (prop->compare(plot3daxiscatagoryticklabelrotationitem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setLabelAutoRotation(value);
  } else if (prop->compare(plot3dsurfaceaspectratioitem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setAspectRatio(value);
  } else if (prop->compare(plot3dsurfacehorizontalaspectratioitem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setHorizontalAspectRatio(value);
  } else if (prop->compare(plot3dbarspacingxitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    QSizeF size = bar->getGraph()->barSpacing();
    size.setWidth(value);
    bar->getGraph()->setBarSpacing(size);
  } else if (prop->compare(plot3dbarspacingyitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    QSizeF size = bar->getGraph()->barSpacing();
    size.setHeight(value);
    bar->getGraph()->setBarSpacing(size);
  } else if (prop->compare(plot3dbarthicknessitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setBarThickness(value);
  } else if (prop->compare(plot3dbaraspectratioitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setAspectRatio(value);
  } else if (prop->compare(plot3dbarhorizontalaspectratioitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setHorizontalAspectRatio(value);
  } else if (prop->compare(plot3dscatteraspectratioitem_)) {
    Scatter3D *scatter =
        getgraph2dobject<Scatter3D>(objectbrowser_->currentItem());
    scatter->getGraph()->setAspectRatio(value);
  } else if (prop->compare(plot3dscatterhorizontalaspectratioitem_)) {
    Scatter3D *scatter =
        getgraph2dobject<Scatter3D>(objectbrowser_->currentItem());
    scatter->getGraph()->setHorizontalAspectRatio(value);
  } else if (prop->compare(plot3dscatterseriessizeitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setItemSize(value);
  } else
    qDebug() << QString::fromLatin1("unknown double property item");
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const QString &value) {
  if (prop->compare(mywidgetwindownameitem_)) {
    MyWidget *widget =
        getgraph2dobject<MyWidget>(objectbrowser_->currentItem());
    bool status = app_->renameWindow(widget, value);
    if (!status)
      stringManager_->setValue(mywidgetwindownameitem_, widget->name());
  } else if (prop->compare(mywidgetwindowlabelitem_)) {
    MyWidget *widget =
        getgraph2dobject<MyWidget>(objectbrowser_->currentItem());
    QString label = value;
    label.replace(QString::fromLatin1("\n"), QString::fromLatin1(" ")).replace(QString::fromLatin1("\t"), QString::fromLatin1(" "));
    widget->setWindowLabel(value);
    app_->setListViewLabel(widget->name(), value);
  } else if (prop->compare(axispropertylabeltextitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setLabel(Utilities::splitstring(value));
    objectbrowser_->currentItem()->setText(
        0, axis->getname_axis() + QString::number(axis->getnumber_axis()));
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickersymbolsymbol_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerPi> piticker =
        qSharedPointerCast<QCPAxisTickerPi>(axis->getticker_axis());
    piticker->setPiSymbol(Utilities::splitstring(value));
    axis->setLabel(Utilities::splitstring(value));
    axis->setTicker(piticker);
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertytickertimeformat_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerTime> timeticker =
        qSharedPointerCast<QCPAxisTickerTime>(axis->getticker_axis());
    timeticker->setTimeFormat(Utilities::splitstring(value));
    axis->setTicker(timeticker);
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertytickerdatetimeformat_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerDateTime> datetimeticker =
        qSharedPointerCast<QCPAxisTickerDateTime>(axis->getticker_axis());
    datetimeticker->setDateTimeFormat(Utilities::splitstring(value));
    axis->setTicker(datetimeticker);
    datetimeManager_->setFormat(Utilities::splitstring(value));
    axis->parentPlot()->replot();
  } else if (prop->compare(itempropertylegendtitletextitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->settitletext_legend(value);
    legend->layer()->replot();
  } else if (prop->compare(itempropertytexttextitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setText(Utilities::splitstring(value));
    textitem->layer()->replot();
  } else if (prop->compare(lsplotpropertylegendtextitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlegendtext_lsplot(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(channelplotpropertylegendtextitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlegendtext_lsplot(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertylegendtextitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlegendtext_cplot(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertylegendtextitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setName(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertylegendtextitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setlegendtext_statbox(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylegendtextitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setlegendtext_vecplot(Utilities::splitstring(value));
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    axisrect->getLegend()->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxislabeltextitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->setLabel(value);
    colormap->setname_colormap(Utilities::splitstring(value));
    colormap->layer()->replot();
  } else if (prop->compare(plot3daxisvaluetitletextitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setTitle(value);
  } else if (prop->compare(plot3dvalueaxislabelformatitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setLabelFormat(value);
  } else if (prop->compare(plot3daxiscatagorytitletextitem_)) {
    QCategory3DAxis *axis =
        getgraph2dobject<QCategory3DAxis>(objectbrowser_->currentItem());
    axis->setTitle(value);
  }
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const int value) {
  if (prop->compare(canvaspropertyrowsapcingitem_)) {
    void *ptr1 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 2)
                     .value<void *>();
    Layout2D *layout = static_cast<Layout2D *>(ptr1);
    layout->getLayoutGrid()->setRowSpacing(value);
    layout->getPlotCanwas()->replot();
  } else if (prop->compare(canvaspropertycolumnsapcingitem_)) {
    void *ptr1 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 2)
                     .value<void *>();
    Layout2D *layout = static_cast<Layout2D *>(ptr1);
    layout->getLayoutGrid()->setColumnSpacing(value);
    layout->getPlotCanwas()->replot();
  } else if (prop->compare(layoutpropertyleftmarginitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QMargins mar = axisrect->margins();
    if (mar.left() != value) {
      mar.setLeft(value);
      axisrect->setMargins(mar);
      axisrect->parentPlot()->replot(
          QCustomPlot::RefreshPriority::rpQueuedReplot);
    }
  } else if (prop->compare(layoutpropertytopmarginitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QMargins mar = axisrect->margins();
    if (mar.top() != value) {
      mar.setTop(value);
      axisrect->setMargins(mar);
      axisrect->parentPlot()->replot(
          QCustomPlot::RefreshPriority::rpQueuedReplot);
    }
  } else if (prop->compare(layoutpropertyrightmarginitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QMargins mar = axisrect->margins();
    if (mar.right() != value) {
      mar.setRight(value);
      axisrect->setMargins(mar);
      axisrect->parentPlot()->replot(
          QCustomPlot::RefreshPriority::rpQueuedReplot);
    }
  } else if (prop->compare(layoutpropertybottommarginitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QMargins mar = axisrect->margins();
    if (mar.bottom() != value) {
      mar.setBottom(value);
      axisrect->setMargins(mar);
      axisrect->parentPlot()->replot(
          QCustomPlot::RefreshPriority::rpQueuedReplot);
    }
  } else if (prop->compare(axispropertyoffsetitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setoffset_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertylabelpaddingitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setlabelpadding_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickcountitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->settickscount_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklengthinitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklengthin_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklengthoutitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklengthout_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubticklengthinitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubticklengthin_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubticklengthoutitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubticklengthout_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickersubtickcount_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    switch (axis->gettickertype_axis()) {
      case Axis2D::TickerType::Log: {
        QSharedPointer<QCPAxisTickerLog> logticker =
            qSharedPointerCast<QCPAxisTickerLog>(axis->getticker_axis());
        logticker->setSubTickCount(value);
        axis->setTicker(logticker);
      } break;
      case Axis2D::TickerType::Text: {
        QSharedPointer<QCPAxisTickerText> textticker =
            qSharedPointerCast<QCPAxisTickerText>(axis->getticker_axis());
        textticker->setSubTickCount(value);
        axis->setTicker(textticker);
      } break;
      default:
        qDebug()
            << QString::fromLatin1("axispropertytickersubtickcount_ unsupported for ticker type");
        break;
    }
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertyticklabelpaddingitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelpadding_axis(value);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklabelprecisionitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelprecision_axis(value);
    doubleManager_->setDecimals(axispropertyfromitem_, value);
    doubleManager_->setDecimals(axispropertytoitem_, value);
    axis->layer()->replot();
  } else if (prop->compare(itempropertylegendiconwidthitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QSize size = legend->iconSize();
    size.setWidth(value);
    legend->setIconSize(size);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendiconheightitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QSize size = legend->iconSize();
    size.setHeight(value);
    legend->setIconSize(size);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendicontextpaddingitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setIconTextPadding(value);
    legend->layer()->replot();
  } else if (prop->compare(pieplotpropertymarginpercentitem_)) {
    Pie2D *pie = getgraph2dobject<Pie2D>(objectbrowser_->currentItem());
    pie->setmarginpercent_pieplot(value);
    pie->layer()->replot();
  } else if (prop->compare(colormappropertyscalewidthitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setcolormapscalewidth_colormap(value);
    colormap->parentPlot()->replot();
  } else if (prop->compare(colormappropertyscaleaxisoffsetitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setOffset(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxislabelpaddingitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setLabelPadding(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklengthinitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLengthIn(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklengthoutitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLengthOut(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxissubticklengthinitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setSubTickLengthIn(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxissubticklengthoutitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setSubTickLengthOut(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelpaddingitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabelPadding(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelpaddingitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setNumberPrecision(value);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertylevelcountitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setlevelcount_colormap(value);
    colormap->layer()->replot();
  } else if (prop->compare(itempropertyimagerotationitem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    imageitem->setrotation_imageitem(value);
    imageitem->layer()->replot();
  } else if (prop->compare(plot3dvalueaxistickcountitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setSegmentCount(value);
  } else if (prop->compare(plot3dvalueaxissubtickcountitem_)) {
    QValue3DAxis *axis =
        getgraph2dobject<QValue3DAxis>(objectbrowser_->currentItem());
    axis->setSubSegmentCount(value);
  } else if (prop->compare(tablewindowrowcountitem_)) {
    Table *table = getgraph2dobject<Table>(objectbrowser_->currentItem());
    table->setNumRows(value);
  } else if (prop->compare(tablewindowcolcountitem_)) {
    Table *table = getgraph2dobject<Table>(objectbrowser_->currentItem());
    table->setNumCols(value);
  } else if (prop->compare(matrixwindowrowcountitem_)) {
    Matrix *matrix = getgraph2dobject<Matrix>(objectbrowser_->currentItem());
    matrix->setNumRows(value);
  } else if (prop->compare(matrixwindowcolcountitem_)) {
    Matrix *matrix = getgraph2dobject<Matrix>(objectbrowser_->currentItem());
    matrix->setNumCols(value);
  }
}

void PlotPropertyEditor::enumValueChange(QtProperty *prop, const int value) {
  if (prop->compare(layoutpropertyfillstyleitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    QBrush b = axisrect->backgroundBrush();
    b.setStyle(static_cast<Qt::BrushStyle>(value + 1));
    axisrect->setBackground(b);
    axisrect->layer()->replot();
  } else if (prop->compare(itempropertylegenddirectionitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setdirection_legend(value);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendbackgroundfillstyleitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    QBrush b = legend->brush();
    b.setStyle(static_cast<Qt::BrushStyle>(value + 1));
    legend->setBrush(b);
    legend->layer()->replot();
  } else if (prop->compare(hgridaxispropertycomboitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    Axis2D *axis = axisrect->getXAxes2D().at(value);
    axisrect->bindGridTo(axis);
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmajgridpropertystroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMajorGridStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmajgridpropertyzerolinestroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setZerothLineStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(hmingridpropertystroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().first.first->setMinorGridStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().first.first->layer()->replot();
  } else if (prop->compare(vgridaxispropertycomboitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    Axis2D *axis = axisrect->getYAxes2D().at(value);
    axisrect->bindGridTo(axis);
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertystroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMajorGridStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmajgridpropertyzerolinestroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setZerothLineStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(vmingridpropertystroketypeitem_)) {
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem());
    axisrect->getGridPair().second.first->setMinorGridStyle(
        static_cast<Qt::PenStyle>(value + 1));
    axisrect->getGridPair().second.first->layer()->replot();
  } else if (prop->compare(axispropertyupperendingstyleitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setUpperEnding(static_cast<QCPLineEnding::EndingStyle>(value));
    axis->layer()->replot();
  } else if (prop->compare(axispropertylowerendingstyleitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setLowerEnding(static_cast<QCPLineEnding::EndingStyle>(value));
    axis->layer()->replot();
  } else if (prop->compare(axispropertylinlogitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setscaletype_axis(static_cast<Axis2D::AxisScaleType>(value));
    axis->layer()->replot();
  } else if (prop->compare(axispropertystroketypeitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setstroketype_axis(static_cast<Qt::PenStyle>(value + 1));
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickstroketypeitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->settickstrokestyle_axis(static_cast<Qt::PenStyle>(value + 1));
    axis->layer()->replot();
  } else if (prop->compare(axispropertysubtickstroketypeitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setsubtickstrokestyle_axis(static_cast<Qt::PenStyle>(value + 1));
    axis->layer()->replot();
  } else if (prop->compare(axispropertytickstepstrategy_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTicker> ticker = axis->getticker_axis();
    (value == 0) ? ticker->setTickStepStrategy(
                       QCPAxisTicker::TickStepStrategy::tssReadability)
    : (value == 1) ? ticker->setTickStepStrategy(
                         QCPAxisTicker::TickStepStrategy::tssMeetTickCount)
                   : ticker->setTickStepStrategy(
                         QCPAxisTicker::TickStepStrategy::tssReadability);
    axis->setTicker(ticker);
    axis->layer()->replot();
  } /*else if (prop->compare(axispropertytickervaluescalestrategy_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerFixed> valueticker =
        qSharedPointerCast<QCPAxisTickerFixed>(axis->getticker_axis());
    (value == 0) ? valueticker->setScaleStrategy(
                       QCPAxisTickerFixed::ScaleStrategy::ssNone)
    : (value == 1) ? valueticker->setScaleStrategy(
                         QCPAxisTickerFixed::ScaleStrategy::ssMultiples)
    : (value == 2) ? valueticker->setScaleStrategy(
                         QCPAxisTickerFixed::ScaleStrategy::ssPowers)
                   : valueticker->setScaleStrategy(
                         QCPAxisTickerFixed::ScaleStrategy::ssNone);
    axis->setTicker(valueticker);
    axis->layer()->replot();
  }*/
  else if (prop->compare(axispropertytickersymbolfractionstyle_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerPi> piticker =
        qSharedPointerCast<QCPAxisTickerPi>(axis->getticker_axis());
    (value == 0) ? piticker->setFractionStyle(
                       QCPAxisTickerPi::FractionStyle::fsFloatingPoint)
    : (value == 1) ? piticker->setFractionStyle(
                         QCPAxisTickerPi::FractionStyle::fsAsciiFractions)
    : (value == 2) ? piticker->setFractionStyle(
                         QCPAxisTickerPi::FractionStyle::fsUnicodeFractions)
                   : piticker->setFractionStyle(
                         QCPAxisTickerPi::FractionStyle::fsFloatingPoint);
    axis->setTicker(piticker);
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertyticklabelsideitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelside_axis(static_cast<Axis2D::AxisLabelSide>(value));
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklabelformatitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelformat_axis(static_cast<Axis2D::AxisLabelFormat>(value));
    axis->parentPlot()->replot();
  } else if (prop->compare(itempropertylegendborderstroketypeitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setborderstrokestyle_legend(static_cast<Qt::PenStyle>(value + 1));
    legend->layer()->replot();
  } else if (prop->compare(itempropertytexttextalignmentitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->settextalignment_textitem(
        static_cast<TextItem2D::TextAlignment>(value));
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextstroketypeitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setstrokestyle_textitem(static_cast<Qt::PenStyle>(value + 1));
    textitem->layer()->replot();
  } else if (prop->compare(itempropertytextbackgroundfillstyleitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    QBrush b = textitem->brush();
    b.setStyle(static_cast<Qt::BrushStyle>(value + 1));
    textitem->setBrush(b);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylinestroketypeitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setstrokestyle_lineitem(static_cast<Qt::PenStyle>(value + 1));
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylineendingstyleitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendstyle_lineitem(
        LineItem2D::LineEndLocation::Stop,
        static_cast<QCPLineEnding::EndingStyle>(value));
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylinestartingstyleitem_)) {
    LineItem2D *lineitem =
        getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
    lineitem->setendstyle_lineitem(
        LineItem2D::LineEndLocation::Start,
        static_cast<QCPLineEnding::EndingStyle>(value));
    lineitem->layer()->replot();
  } else if (prop->compare(itempropertylegendborderstroketypeitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setborderstrokestyle_legend(static_cast<Qt::PenStyle>(value + 1));
    legend->layer()->replot();
  } else if (prop->compare(itempropertyimagestroketypeitem_)) {
    ImageItem2D *imageitem =
        getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
    imageitem->setstrokestyle_imageitem(static_cast<Qt::PenStyle>(value + 1));
    imageitem->layer()->replot();
  } else if (prop->compare(lsplotpropertyxaxisitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getXAxis(value);
    if (!axis) return;
    lsgraph->setxaxis_lsplot(axis);
    lsgraph->layer()->replot();
  } else if (prop->compare(lsplotpropertyyaxisitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getYAxis(value);
    if (!axis) return;
    lsgraph->setyaxis_lsplot(axis);
    lsgraph->layer()->replot();
  } else if (prop->compare(lsplotpropertylinestyleitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinetype_lsplot(
        static_cast<Graph2DCommon::LineStyleType>(value));
    objectbrowser_->currentItem()->setIcon(0, lsgraph->getIcon());
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertylinestroketypeitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinestrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertylinefillstyleitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setlinefillstyle_lsplot(static_cast<Qt::BrushStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterstyleitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscattershape_lsplot(
        static_cast<Graph2DCommon::ScatterStyle>(value));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(lsplotpropertyscatterstrokestyleitem_)) {
    LineSpecial2D *lsgraph =
        getgraph2dobject<LineSpecial2D>(objectbrowser_->currentItem());
    lsgraph->setscatterstrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channelplotpropertyxaxisitem_)) {
    void *ptr1 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 1)
                     .value<void *>();
    LineSpecial2D *lsgraph1 = static_cast<LineSpecial2D *>(ptr1);
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getXAxis(value);
    if (!axis) return;
    lsgraph1->setxaxis_lsplot(axis);
    void *ptr2 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 3)
                     .value<void *>();
    LineSpecial2D *lsgraph2 = static_cast<LineSpecial2D *>(ptr2);
    if (!axis) return;
    lsgraph2->setxaxis_lsplot(axis);
    lsgraph1->layer()->replot();
    lsgraph2->layer()->replot();
  } else if (prop->compare(channelplotpropertyyaxisitem_)) {
    void *ptr1 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 1)
                     .value<void *>();
    LineSpecial2D *lsgraph1 = static_cast<LineSpecial2D *>(ptr1);
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getYAxis(value);
    if (!axis) return;
    lsgraph1->setyaxis_lsplot(axis);
    void *ptr2 = objectbrowser_->currentItem()
                     ->data(0, Qt::UserRole + 3)
                     .value<void *>();
    LineSpecial2D *lsgraph2 = static_cast<LineSpecial2D *>(ptr2);
    if (!axis) return;
    lsgraph2->setyaxis_lsplot(axis);
    lsgraph1->layer()->replot();
    lsgraph2->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinestyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinetype_lsplot(
        static_cast<Graph2DCommon::LineStyleType>(value));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinestroketypeitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertylinefillstylritem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinefillstyle_lsplot(static_cast<Qt::BrushStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterstyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscattershape_lsplot(
        static_cast<Graph2DCommon::ScatterStyle>(value));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel1plotpropertyscatterstrokestyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 1)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertylinestyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinetype_lsplot(
        static_cast<Graph2DCommon::LineStyleType>(value));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertylinestroketypeitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setlinestrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterstyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscattershape_lsplot(
        static_cast<Graph2DCommon::ScatterStyle>(value));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(channel2plotpropertyscatterstrokestyleitem_)) {
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 3)
                    .value<void *>();
    LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr);
    lsgraph->setscatterstrokestyle_lsplot(static_cast<Qt::PenStyle>(value + 1));
    lsgraph->layer()->replot();
    lsgraph->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(cplotpropertyxaxisitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getXAxis(value);
    if (!axis) return;
    curve->setxaxis_cplot(axis);
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertyyaxisitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getYAxis(value);
    if (!axis) return;
    curve->setyaxis_cplot(axis);
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertylinestyleitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinetype_cplot(value);
    objectbrowser_->currentItem()->setIcon(0, curve->getIcon());
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertylinestroketypeitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinestrokestyle_cplot(static_cast<Qt::PenStyle>(value + 1));
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertylinefillstyleitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setlinefillstyle_cplot(static_cast<Qt::BrushStyle>(value + 1));
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterstyleitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscattershape_cplot(
        static_cast<Graph2DCommon::ScatterStyle>(value));
    objectbrowser_->currentItem()->setIcon(0, curve->getIcon());
    curve->layer()->replot();
  } else if (prop->compare(cplotpropertyscatterstrokestyleitem_)) {
    Curve2D *curve = getgraph2dobject<Curve2D>(objectbrowser_->currentItem());
    curve->setscatterstrokestyle_cplot(static_cast<Qt::PenStyle>(value + 1));
    curve->layer()->replot();
  } else if (prop->compare(barplotpropertyxaxisitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = nullptr;
    (bar->getxaxis()->getorientation_axis() == Axis2D::AxisOreantation::Top ||
     bar->getxaxis()->getorientation_axis() == Axis2D::AxisOreantation::Bottom)
        ? axis = axisrect->getXAxis(value)
        : axis = axisrect->getYAxis(value);
    if (!axis) return;
    bar->setxaxis_barplot(axis, true);
    bar->layer()->replot();
  } else if (prop->compare(barplotpropertyyaxisitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = nullptr;
    (bar->getxaxis()->getorientation_axis() == Axis2D::AxisOreantation::Top ||
     bar->getxaxis()->getorientation_axis() == Axis2D::AxisOreantation::Bottom)
        ? axis = axisrect->getYAxis(value)
        : axis = axisrect->getXAxis(value);
    if (!axis) return;
    bar->setyaxis_barplot(axis, true);
    bar->layer()->replot();
  } else if (prop->compare(barplotpropertystrokestyleitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setstrokestyle_barplot(static_cast<Qt::PenStyle>(value + 1));
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(barplotpropertyfillstyleitem_)) {
    Bar2D *bar = getgraph2dobject<Bar2D>(objectbrowser_->currentItem());
    bar->setfillstyle_barplot(static_cast<Qt::BrushStyle>(value + 1));
    bar->layer()->replot();
    bar->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyxaxisitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getXAxis(value);
    if (!axis) return;
    statbox->setxaxis_statbox(axis);
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyyaxisitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getYAxis(value);
    if (!axis) return;
    statbox->setyaxis_statbox(axis);
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyboxstyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setboxstyle_statbox(
        static_cast<StatBox2D::BoxWhiskerStyle>(value));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerstyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerstyle_statbox(
        static_cast<StatBox2D::BoxWhiskerStyle>(value));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyboxoutlinestyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    QPen p = statbox->pen();
    p.setStyle(static_cast<Qt::PenStyle>(value + 1));
    statbox->setPen(p);
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyfillstyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setfillstyle_statbox(static_cast<Qt::BrushStyle>(value + 1));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerstrokestyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerstrokestyle_statbox(
        static_cast<Qt::PenStyle>(value + 1));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertywhiskerbarstrokestyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setwhiskerbarstrokestyle_statbox(
        static_cast<Qt::PenStyle>(value + 1));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertymideanstrokestyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setmedianstrokestyle_statbox(static_cast<Qt::PenStyle>(value + 1));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscattershowitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setOutlierScatter(static_cast<StatBox2D::Scatter>(value));
    statbox->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatterstyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscattershape_statbox(
        static_cast<Graph2DCommon::ScatterStyle>(value));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(statboxplotpropertyscatteroutlinestyleitem_)) {
    StatBox2D *statbox =
        getgraph2dobject<StatBox2D>(objectbrowser_->currentItem());
    statbox->setscatterstrokestyle_statbox(
        static_cast<Qt::PenStyle>(value + 1));
    statbox->layer()->replot();
    statbox->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertyxaxisitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getXAxis(value);
    if (!axis) return;
    vector->setxaxis_vecplot(axis);
    vector->layer()->replot();
  } else if (prop->compare(vectorpropertyyaxisitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    AxisRect2D *axisrect =
        getgraph2dobject<AxisRect2D>(objectbrowser_->currentItem()->parent());
    Axis2D *axis = axisrect->getYAxis(value);
    if (!axis) return;
    vector->setyaxis_vecplot(axis);
    vector->layer()->replot();
  } else if (prop->compare(vectorpropertylinestroketypeitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setlinestrokestyle_vecplot(static_cast<Qt::PenStyle>(value + 1));
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(vectorpropertylineendingtypeitem_)) {
    Vector2D *vector =
        getgraph2dobject<Vector2D>(objectbrowser_->currentItem());
    vector->setendstyle_vecplot(static_cast<Vector2D::LineEnd>(value),
                                Vector2D::LineEndLocation::Head);
    vector->layer()->replot();
    vector->getxaxis()->getaxisrect_axis()->getLegend()->layer()->replot();
  } else if (prop->compare(pieplotpropertystyleitem_)) {
    Pie2D *pie = getgraph2dobject<Pie2D>(objectbrowser_->currentItem());
    pie->setstyle_pieplot(static_cast<Graph2DCommon::PieStyle>(value));
    objectbrowser_->currentItem()->setIcon(0, pie->getIcon());
    pie->layer()->replot();
    pie->getaxisrect()->replotBareBones();
    pie->getaxisrect()->getLegend()->layer()->replot();
  } else if (prop->compare(pieplotpropertylinestroketypeitem_)) {
    Pie2D *pie = getgraph2dobject<Pie2D>(objectbrowser_->currentItem());
    pie->setstrokestyle_pieplot(static_cast<Qt::PenStyle>(value + 1));
    pie->layer()->replot();
    pie->getaxisrect()->getLegend()->layer()->replot();
  } else if (prop->compare(colormappropertygradientitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setgradient_colormap(static_cast<ColorMap2D::Gradient>(value));
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxislinlogitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setScaleType(
        static_cast<QCPAxis::ScaleType>(value));
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisstroketypeitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->basePen();
    p.setStyle(static_cast<Qt::PenStyle>(value + 1));
    colormap->getcolormapscale_colormap()->axis()->setBasePen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxistickstroketypeitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->tickPen();
    p.setStyle(static_cast<Qt::PenStyle>(value + 1));
    colormap->getcolormapscale_colormap()->axis()->setTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxissubtickstroketypeitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    QPen p = colormap->getcolormapscale_colormap()->axis()->subTickPen();
    p.setStyle(static_cast<Qt::PenStyle>(value + 1));
    colormap->getcolormapscale_colormap()->axis()->setSubTickPen(p);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelsideitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabelSide(
        static_cast<QCPAxis::LabelSide>(value));
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelformatitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->setcolormapscaleticklabelformat_axis(
        static_cast<Axis2D::AxisLabelFormat>(value));
    colormap->parentPlot()->replot();
  } else if (prop->compare(errorbarpropertystroketypeitem_)) {
    ErrorBar2D *errorbar =
        getgraph2dobject<ErrorBar2D>(objectbrowser_->currentItem());
    QPen p = errorbar->pen();
    p.setStyle(static_cast<Qt::PenStyle>(value + 1));
    errorbar->setPen(p);
    errorbar->layer()->replot();
  } else if (prop->compare(plot3dcanvasthemeitem_)) {
    QAbstract3DGraph *graph =
        getgraph2dobject<QAbstract3DGraph>(objectbrowser_->currentItem());
    graph->activeTheme()->setType(static_cast<Q3DTheme::Theme>(value));
  } else if (prop->compare(plot3dsurfaceshadowqualityitem_)) {
    Surface3D *surface =
        getgraph2dobject<Surface3D>(objectbrowser_->currentItem());
    surface->getGraph()->setShadowQuality(
        static_cast<QAbstract3DGraph::ShadowQuality>(value));
  } else if (prop->compare(plot3dbarshadowqualityitem_)) {
    Bar3D *bar = getgraph2dobject<Bar3D>(objectbrowser_->currentItem());
    bar->getGraph()->setShadowQuality(
        static_cast<QAbstract3DGraph::ShadowQuality>(value));
  } else if (prop->compare(plot3dscattershadowqualityitem_)) {
    Scatter3D *scatter =
        getgraph2dobject<Scatter3D>(objectbrowser_->currentItem());
    scatter->getGraph()->setShadowQuality(
        static_cast<QAbstract3DGraph::ShadowQuality>(value));
  } else if (prop->compare(plot3dsurfaceseriesdrawitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setDrawMode(
        static_cast<QSurface3DSeries::DrawFlag>(value + 1));
  } else if (prop->compare(plot3dsurfaceseriescolorstyleitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->getdataseries()->setColorStyle(
        static_cast<Q3DTheme::ColorStyle>(value));
  } else if (prop->compare(plot3dsurfaceseriesbasegradiantitem_)) {
    DataBlockSurface3D *block =
        getgraph2dobject<DataBlockSurface3D>(objectbrowser_->currentItem());
    block->setgradient(block->getdataseries(),
                       static_cast<Graph3DCommon::Gradient>(value));
  } else if (prop->compare(plot3dbarseriesmeshitem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setMesh(
        static_cast<QAbstract3DSeries::Mesh>(value - 1));
  } else if (prop->compare(plot3dbarseriescolorstyleitem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->getdataseries()->setColorStyle(
        static_cast<Q3DTheme::ColorStyle>(value));
  } else if (prop->compare(plot3dbarseriesbasegradiantitem_)) {
    DataBlockBar3D *block =
        getgraph2dobject<DataBlockBar3D>(objectbrowser_->currentItem());
    block->setgradient(block->getdataseries(),
                       static_cast<Graph3DCommon::Gradient>(value));
  } else if (prop->compare(plot3dscatterseriesmeshitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setMesh(
        static_cast<QAbstract3DSeries::Mesh>(value - 1));
  } else if (prop->compare(plot3dscatterseriescolorstyleitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->getdataseries()->setColorStyle(
        static_cast<Q3DTheme::ColorStyle>(value));
  } else if (prop->compare(plot3dscatterseriesbasegradiantitem_)) {
    DataBlockScatter3D *block =
        getgraph2dobject<DataBlockScatter3D>(objectbrowser_->currentItem());
    block->setgradient(block->getdataseries(),
                       static_cast<Graph3DCommon::Gradient>(value));
  } else
    qDebug() << QString::fromLatin1("unknown enum property");
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const QFont &font) {
  if (prop->compare(axispropertylabelfontitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setlabelfont_axis(font);
    axis->layer()->replot();
  } else if (prop->compare(axispropertyticklabelfontitem_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setticklabelfont_axis(font);
    axis->layer()->replot();
  } else if (prop->compare(itempropertytextfontitem_)) {
    TextItem2D *textitem =
        getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
    textitem->setFont(font);
    textitem->layer()->replot();
  } else if (prop->compare(itempropertylegendfontitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->setFont(font);
    legend->layer()->replot();
  } else if (prop->compare(itempropertylegendtitlefontitem_)) {
    Legend2D *legend =
        getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
    legend->settitlefont_legend(font);
    legend->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxislabelfontitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setLabelFont(font);
    colormap->layer()->replot();
  } else if (prop->compare(colormappropertyscaleaxisticklabelfontitem_)) {
    ColorMap2D *colormap =
        getgraph2dobject<ColorMap2D>(objectbrowser_->currentItem());
    colormap->getcolormapscale_colormap()->axis()->setTickLabelFont(font);
    colormap->layer()->replot();
  } else if (prop->compare(plot3dcanvasfontitem_)) {
    Q3DTheme *theme = getgraph2dobject<Q3DTheme>(objectbrowser_->currentItem());
    theme->setFont(font);
  }
}

void PlotPropertyEditor::datetimeValueChange(QtProperty *prop,
                                         const QDateTime &datetime) {
  /*if (prop->compare(axispropertytickerdatetimetickorigin_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    QSharedPointer<QCPAxisTickerDateTime> datetimeticker =
        qSharedPointerCast<QCPAxisTickerDateTime>(axis->getticker_axis());
    datetimeticker->setTickOrigin(Utilities::dateTimeToDouble(datetime));
    axis->setTicker(datetimeticker);
    axis->parentPlot()->replot();
    Axis2DPropertyBlock(axis);
  } else*/
  if (prop->compare(axispropertytickerdatetimefrom_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setfrom_axis(QCPAxisTickerDateTime::dateTimeToKey(datetime));
    axis->parentPlot()->replot();
  } else if (prop->compare(axispropertytickerdatetimeto_)) {
    Axis2D *axis = getgraph2dobject<Axis2D>(objectbrowser_->currentItem());
    axis->setto_axis(QCPAxisTickerDateTime::dateTimeToKey(datetime));
    axis->parentPlot()->replot();
  }
}

void PlotPropertyEditor::valueChange(QtProperty *prop, const QSize &size) {
  if (prop->compare(canvaspropertysizeitem_)) {
    Plot2D *plot = getgraph2dobject<Plot2D>(objectbrowser_->currentItem());
    QRect oldrect = plot->geometry();
    QRect rect = oldrect;
    rect.setWidth(size.width());
    rect.setHeight(size.height());
    plot->setGeometry(rect);
    MyWidget *widget = qobject_cast<MyWidget *>(plot->parentWidget()->parent());
    if (widget) {
      QRect wrect = widget->geometry();
      widget->resize(wrect.width() + (rect.width() - oldrect.width()),
                     wrect.height() + (rect.height() - oldrect.height()));
    }
    plot->replot(QCustomPlot::RefreshPriority::rpQueuedReplot);
  }
  if (prop->compare(plot3dcanvassizeitem_)) {
    QAbstract3DGraph *graph =
        getgraph2dobject<QAbstract3DGraph>(objectbrowser_->currentItem());
    QSize oldsize = graph->size();
    QSize sizediff = size - oldsize;
    void *ptr = objectbrowser_->currentItem()
                    ->data(0, Qt::UserRole + 2)
                    .value<void *>();
    MyWidget *widget = static_cast<MyWidget *>(ptr);
    widget->resize(widget->size() + sizediff);
  } else
    qDebug() << QString::fromLatin1("unknown size property");
}

void PlotPropertyEditor::selectObjectItem(QTreeWidgetItem *item) {
  if (!item) return;
  switch (static_cast<MyPlotTreeWidget::PropertyItemType>(
      item->data(0, Qt::UserRole).value<int>())) {
    case MyPlotTreeWidget::PropertyItemType::MyWidgetWindow: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      MyWidget *widget = static_cast<MyWidget *>(ptr1);
      WindowPropertyBlock(widget);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DCanvas: {
      void *ptr = item->data(0, Qt::UserRole + 1).value<void *>();
      Plot2D *plotcanvas = static_cast<Plot2D *>(ptr);
      ptr = item->data(0, Qt::UserRole + 2).value<void *>();
      Layout2D *layout2d = static_cast<Layout2D *>(ptr);
      Plot2DPropertyBlock(layout2d, plotcanvas);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DLayout: {
      void *ptr = item->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr);
      ptr = item->data(0, Qt::UserRole + 2).value<void *>();
      Layout2D *layout2d = static_cast<Layout2D *>(ptr);
      Layout2DPropertyBlock(layout2d, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DGrid: {
      void *ptr = item->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr);
      Grid2DPropertyBlock(axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DAxis: {
      void *ptr = item->data(0, Qt::UserRole + 1).value<void *>();
      Axis2D *axis = static_cast<Axis2D *>(ptr);
      Axis2DPropertyBlock(axis);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DLegend: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Legend2D *legend = static_cast<Legend2D *>(ptr1);
      Legend2DPropertyBlock(legend);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DTextItem: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      TextItem2D *textitem = static_cast<TextItem2D *>(ptr1);
      TextItem2DPropertyBlock(textitem);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DLineItem: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      LineItem2D *lineitem = static_cast<LineItem2D *>(ptr1);
      LineItem2DPropertyBlock(lineitem);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DImageItem: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      ImageItem2D *imageitem = static_cast<ImageItem2D *>(ptr1);
      ImageItem2DPropertyBlock(imageitem);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DLSGraph: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      LineSpecial2D *lsgraph = static_cast<LineSpecial2D *>(ptr1);
      void *ptr2 = item->data(0, Qt::UserRole + 2).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      LineSpecial2DPropertyBlock(lsgraph, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DChannelGraph: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      LineSpecial2D *lsgraph1 = static_cast<LineSpecial2D *>(ptr1);
      void *ptr2 = item->data(0, Qt::UserRole + 2).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      void *ptr3 = item->data(0, Qt::UserRole + 3).value<void *>();
      LineSpecial2D *lsgraph2 = static_cast<LineSpecial2D *>(ptr3);
      LineSpecialChannel2DPropertyBlock(lsgraph1, lsgraph2, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DCurve: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Curve2D *curve = static_cast<Curve2D *>(ptr1);
      void *ptr2 = item->data(0, Qt::UserRole + 2).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      Curve2DPropertyBlock(curve, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DBarGraph: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Bar2D *bar = static_cast<Bar2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      Bar2DPropertyBlock(bar, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DStatBox: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      StatBox2D *statbox = static_cast<StatBox2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      StatBox2DPropertyBlock(statbox, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DVector: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Vector2D *vector = static_cast<Vector2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      Vector2DPropertyBlock(vector, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DPieGraph: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Pie2D *pie = static_cast<Pie2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      Pie2DPropertyBlock(pie, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DColorMap: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      ColorMap2D *colormap = static_cast<ColorMap2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      ColorMap2DPropertyBlock(colormap, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      ErrorBar2D *errorbar = static_cast<ErrorBar2D *>(ptr1);
      void *ptr2 = item->parent()->data(0, Qt::UserRole + 1).value<void *>();
      AxisRect2D *axisrect = static_cast<AxisRect2D *>(ptr2);
      ErrorBar2DPropertyBlock(errorbar, axisrect);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DCanvas: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      QAbstract3DGraph *graph = static_cast<QAbstract3DGraph *>(ptr1);
      Canvas3DPropertyBlock(graph);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DTheme: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Q3DTheme *theme = static_cast<Q3DTheme *>(ptr1);
      Theme3DPropertyBlock(theme);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DAxisValue: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      QValue3DAxis *axis = static_cast<QValue3DAxis *>(ptr1);
      Axis3DValuePropertyBlock(axis);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DAxisCatagory: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      QCategory3DAxis *axis = static_cast<QCategory3DAxis *>(ptr1);
      Axis3DCatagoryPropertyBlock(axis);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DSurface: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Surface3D *surface = static_cast<Surface3D *>(ptr1);
      Surface3DPropertyBlock(surface);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DBar: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Bar3D *bar = static_cast<Bar3D *>(ptr1);
      Bar3DPropertyBlock(bar);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DScatter: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Scatter3D *scatter = static_cast<Scatter3D *>(ptr1);
      Scatter3DPropertyBlock(scatter);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DSurfaceDataBlock: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      DataBlockSurface3D *block = static_cast<DataBlockSurface3D *>(ptr1);
      Surface3DSeriesPropertyBlock(block);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DBarDataBlock: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      DataBlockBar3D *block = static_cast<DataBlockBar3D *>(ptr1);
      Bar3DSeriesPropertyBlock(block);
    } break;
    case MyPlotTreeWidget::PropertyItemType::Plot3DScatterDataBlock: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      DataBlockScatter3D *block = static_cast<DataBlockScatter3D *>(ptr1);
      Scatter3DSeriesPropertyBlock(block);
    } break;
    case MyPlotTreeWidget::PropertyItemType::TableWindow: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Table *table = static_cast<Table *>(ptr1);
      TablePropertyBlock(table);
    } break;
    case MyPlotTreeWidget::PropertyItemType::MatrixWindow: {
      void *ptr1 = item->data(0, Qt::UserRole + 1).value<void *>();
      Matrix *matrix = static_cast<Matrix *>(ptr1);
      MatrixPropertyBlock(matrix);
    } break;
  }
}

void PlotPropertyEditor::Layout2DPropertyBlock(Layout2D *layout2d,
                                           AxisRect2D *axisrect) {
  propertybrowser_->clear();

  rectManager_->setValue(layoutpropertyrectitem_, axisrect->outerRect());
  colorManager_->setValue(layoutpropertycoloritem_,
                          axisrect->backgroundBrush().color());
  propertybrowser_->addProperty(layoutpropertycoloritem_);
  propertybrowser_->addProperty(layoutpropertyfillstyleitem_);
  propertybrowser_->addProperty(layoutpropertyrowstreachfactoritem_);
  propertybrowser_->addProperty(layoutpropertycolumnstreachfactoritem_);
  propertybrowser_->addProperty(layoutpropertyrectitem_);
  propertybrowser_->addProperty(layoutpropertymargingroupitem_);
  enumManager_->setValue(layoutpropertyfillstyleitem_,
                         axisrect->backgroundBrush().style() - 1);
  boolManager_->setValue(layoutpropertyautomarginstatusitem_,
                         axisrect->autoMargins());
  intManager_->setValue(layoutpropertyleftmarginitem_,
                        axisrect->margins().left());
  intManager_->setValue(layoutpropertyrightmarginitem_,
                        axisrect->margins().right());
  intManager_->setValue(layoutpropertytopmarginitem_,
                        axisrect->margins().top());
  intManager_->setValue(layoutpropertybottommarginitem_,
                        axisrect->margins().bottom());
  LayoutGrid2D *loutgrid = layout2d->getLayoutGrid();
  QPair<int, int> rowcol = layout2d->getAxisRectRowCol(axisrect);
  doubleManager_->setValue(layoutpropertyrowstreachfactoritem_,
                           loutgrid->rowStretchFactors().at(rowcol.first));
  doubleManager_->setValue(layoutpropertycolumnstreachfactoritem_,
                           loutgrid->columnStretchFactors().at(rowcol.second));
}

void PlotPropertyEditor::Axis2DPropertyBlock(Axis2D *axis) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(axispropertyvisibleitem_);
  propertybrowser_->addProperty(axispropertyoffsetitem_);
  if (axis->gettickertype_axis() != Axis2D::TickerType::DateTime) {
    propertybrowser_->addProperty(axispropertyfromitem_);
    propertybrowser_->addProperty(axispropertytoitem_);
  } else {
    propertybrowser_->addProperty(axispropertytickerdatetimefrom_);
    propertybrowser_->addProperty(axispropertytickerdatetimeto_);
  }
  propertybrowser_->addProperty(axispropertyupperendingstyleitem_);
  propertybrowser_->addProperty(axispropertylowerendingstyleitem_);
  propertybrowser_->addProperty(axispropertylinlogitem_);
  propertybrowser_->addProperty(axispropertyinvertitem_);
  propertybrowser_->addProperty(axispropertystrokecoloritem_);
  propertybrowser_->addProperty(axispropertystrokethicknessitem_);
  propertybrowser_->addProperty(axispropertystroketypeitem_);
  propertybrowser_->addProperty(axispropertyantialiaseditem_);
  propertybrowser_->addProperty(axispropertylabeltextitem_);
  propertybrowser_->addProperty(axispropertylabelfontitem_);
  propertybrowser_->addProperty(axispropertylabelcoloritem_);
  propertybrowser_->addProperty(axispropertylabelpaddingitem_);
  propertybrowser_->addProperty(axispropertytickvisibilityitem_);
  propertybrowser_->addProperty(axispropertysubtickvisibilityitem_);
  propertybrowser_->addProperty(axispropertyticklabelvisibilityitem_);

  boolManager_->setValue(axispropertyvisibleitem_, axis->getshowhide_axis());
  intManager_->setValue(axispropertyoffsetitem_, axis->getoffset_axis());
  if (axis->gettickertype_axis() != Axis2D::TickerType::DateTime) {
    doubleManager_->setValue(axispropertyfromitem_, axis->getfrom_axis());
    doubleManager_->setValue(axispropertytoitem_, axis->getto_axis());
  }
  enumManager_->setValue(axispropertyupperendingstyleitem_,
                         axis->upperEnding().style());
  enumManager_->setValue(axispropertylowerendingstyleitem_,
                         axis->lowerEnding().style());
  enumManager_->setValue(axispropertylinlogitem_,
                         static_cast<int>(axis->getscaletype_axis()));
  boolManager_->setValue(axispropertyinvertitem_, axis->getinverted_axis());
  colorManager_->setValue(axispropertystrokecoloritem_,
                          axis->getstrokecolor_axis());
  doubleManager_->setValue(axispropertystrokethicknessitem_,
                           axis->getstrokethickness_axis());
  enumManager_->setValue(axispropertystroketypeitem_,
                         axis->getstroketype_axis() - 1);
  boolManager_->setValue(axispropertyantialiaseditem_,
                         axis->getantialiased_axis());
  stringManager_->setValue(axispropertylabeltextitem_,
                           Utilities::joinstring(axis->getlabeltext_axis()));
  fontManager_->setValue(axispropertylabelfontitem_, axis->getlabelfont_axis());
  colorManager_->setValue(axispropertylabelcoloritem_,
                          axis->getlabelcolor_axis());
  intManager_->setValue(axispropertylabelpaddingitem_,
                        axis->getlabelpadding_axis());
  boolManager_->setValue(axispropertytickvisibilityitem_,
                         axis->gettickvisibility_axis());
  intManager_->setValue(axispropertytickcountitem_, axis->gettickscount_axis());
  doubleManager_->setValue(axispropertytickoriginitem_, axis->getticksorigin());
  intManager_->setValue(axispropertyticklengthinitem_,
                        axis->getticklengthin_axis());
  intManager_->setValue(axispropertyticklengthoutitem_,
                        axis->getticklengthout_axis());
  colorManager_->setValue(axispropertytickstrokecoloritem_,
                          axis->gettickstrokecolor_axis());
  doubleManager_->setValue(axispropertytickstrokethicknessitem_,
                           axis->gettickstrokethickness_axis());
  enumManager_->setValue(axispropertytickstroketypeitem_,
                         axis->gettickstrokestyle_axis() - 1);
  boolManager_->setValue(axispropertysubtickvisibilityitem_,
                         axis->getsubtickvisibility_axis());
  intManager_->setValue(axispropertysubticklengthinitem_,
                        axis->getsubticklengthin_axis());
  intManager_->setValue(axispropertysubticklengthoutitem_,
                        axis->getsubticklengthout_axis());
  colorManager_->setValue(axispropertysubtickstrokecoloritem_,
                          axis->getsubtickstrokecolor_axis());
  doubleManager_->setValue(axispropertysubtickstrokethicknessitem_,
                           axis->getsubtickstrokethickness_axis());
  enumManager_->setValue(axispropertysubtickstroketypeitem_,
                         axis->getsubtickstrokestyle_axis() - 1);
  boolManager_->setValue(axispropertyticklabelvisibilityitem_,
                         axis->getticklabelvisibility_axis());
  QCPAxisTicker::TickStepStrategy tss =
      axis->getticker_axis()->tickStepStrategy();
  int tssno = 0;
  (tss == QCPAxisTicker::TickStepStrategy::tssReadability)     ? tssno = 0
  : (tss == QCPAxisTicker::TickStepStrategy::tssMeetTickCount) ? tssno = 1
                                                               : tssno = 0;
  enumManager_->setValue(axispropertytickstepstrategy_, tssno);

  // axispropertyticklabelvisibilityitem_->removeSubProperty(
  //    axispropertytickervaluetickstep_);
  // axispropertyticklabelvisibilityitem_->removeSubProperty(
  //    axispropertytickervaluescalestrategy_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickersymbolvalue_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickersymbolsymbol_);
  // axispropertyticklabelvisibilityitem_->addSubProperty(
  //    axispropertytickersymbolperiodicity_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickersymbolfractionstyle_);
  axispropertysubtickvisibilityitem_->removeSubProperty(
      axispropertytickersubtickcount_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickerlogbase_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickertimeformat_);
  // axispropertyticklabelvisibilityitem_->addSubProperty(
  //    axispropertytickertimefieldwidth_);
  axispropertyticklabelvisibilityitem_->removeSubProperty(
      axispropertytickerdatetimeformat_);
  // axispropertyticklabelvisibilityitem_->removeSubProperty(
  //    axispropertytickerdatetimetickorigin_);

  switch (axis->gettickertype_axis()) {
    case Axis2D::TickerType::Value: {
      QSharedPointer<QCPAxisTickerFixed> valueticker =
          qSharedPointerCast<QCPAxisTickerFixed>(axis->getticker_axis());
      // doubleManager_->setValue(axispropertytickervaluetickstep_,
      //                         valueticker->tickStep());
      if (valueticker) {
        /*QCPAxisTickerFixed::ScaleStrategy tfss = valueticker->scaleStrategy();
        int tfssno = 0;
        (tfss == QCPAxisTickerFixed::ScaleStrategy::ssNone)        ? tfssno = 0
        : (tfss == QCPAxisTickerFixed::ScaleStrategy::ssMultiples) ? tfssno = 1
        : (tfss == QCPAxisTickerFixed::ScaleStrategy::ssPowers)    ? tfssno = 2
                                                                   : tfssno =
        0;*/
        // axispropertyticklabelvisibilityitem_->addSubProperty(
        //    axispropertytickervaluetickstep_);
        // axispropertyticklabelvisibilityitem_->addSubProperty(
        //    axispropertytickervaluescalestrategy_);
        // enumManager_->setValue(axispropertytickervaluescalestrategy_,
        // tfssno);
      }
    } break;
    case Axis2D::TickerType::Log: {
      QSharedPointer<QCPAxisTickerLog> logticker =
          qSharedPointerCast<QCPAxisTickerLog>(axis->getticker_axis());
      if (logticker) {
        axispropertysubtickvisibilityitem_->insertSubProperty(
            axispropertytickersubtickcount_,
            axispropertysubtickvisibilityitem_);
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickerlogbase_, axispropertytickstepstrategy_);
        doubleManager_->setValue(axispropertytickerlogbase_,
                                 logticker->logBase());
        intManager_->setValue(axispropertytickersubtickcount_,
                              logticker->subTickCount());
      }
    } break;
    case Axis2D::TickerType::Pi: {
      QSharedPointer<QCPAxisTickerPi> piticker =
          qSharedPointerCast<QCPAxisTickerPi>(axis->getticker_axis());
      if (piticker) {
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickersymbolsymbol_, axispropertytickstepstrategy_);
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickersymbolvalue_, axispropertytickersymbolsymbol_);
        // axispropertyticklabelvisibilityitem_->addSubProperty(
        //    axispropertytickersymbolperiodicity_);
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickersymbolfractionstyle_,
            axispropertytickersymbolvalue_);
        doubleManager_->setValue(axispropertytickersymbolvalue_,
                                 piticker->piValue());
        stringManager_->setValue(axispropertytickersymbolsymbol_,
                                 piticker->piSymbol());
        // boolManager_->setValue(
        //    axispropertytickersymbolperiodicity_, piticker->periodicity());
        QCPAxisTickerPi::FractionStyle fs = piticker->fractionStyle();
        int fsno = 0;
        (fs == QCPAxisTickerPi::FractionStyle::fsFloatingPoint)      ? fsno = 0
        : (fs == QCPAxisTickerPi::FractionStyle::fsAsciiFractions)   ? fsno = 1
        : (fs == QCPAxisTickerPi::FractionStyle::fsUnicodeFractions) ? fsno = 2
                                                                     : fsno = 0;
        enumManager_->setValue(axispropertytickersymbolfractionstyle_, fsno);
      }
    } break;
    case Axis2D::TickerType::Text: {
      QSharedPointer<QCPAxisTickerText> textticker =
          qSharedPointerCast<QCPAxisTickerText>(axis->getticker_axis());
      if (textticker) {
        intManager_->setValue(axispropertytickersubtickcount_,
                              textticker->subTickCount());
        axispropertysubtickvisibilityitem_->insertSubProperty(
            axispropertytickersubtickcount_,
            axispropertysubtickvisibilityitem_);
      }
    } break;
    case Axis2D::TickerType::Time: {
      QSharedPointer<QCPAxisTickerTime> timeticker =
          qSharedPointerCast<QCPAxisTickerTime>(axis->getticker_axis());
      if (timeticker) {
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickertimeformat_, axispropertytickstepstrategy_);
        // axispropertyticklabelvisibilityitem_->addSubProperty(
        //    axispropertytickertimefieldwidth_);
        stringManager_->setValue(axispropertytickertimeformat_,
                                 timeticker->timeFormat());
      }
    } break;
    case Axis2D::TickerType::DateTime: {
      QSharedPointer<QCPAxisTickerDateTime> datetimeticker =
          qSharedPointerCast<QCPAxisTickerDateTime>(axis->getticker_axis());
      if (datetimeticker) {
        axispropertyticklabelvisibilityitem_->insertSubProperty(
            axispropertytickerdatetimeformat_, axispropertytickstepstrategy_);
        // axispropertyticklabelvisibilityitem_->addSubProperty(
        //    axispropertytickerdatetimetickorigin_);
        datetimeManager_->setFormat(datetimeticker->dateTimeFormat());
        stringManager_->setValue(axispropertytickerdatetimeformat_,
                                 datetimeticker->dateTimeFormat());
        // datetimeManager_->setValue(
        //    axispropertytickerdatetimetickorigin_,
        //    Utilities::doubleToDateTime(datetimeticker->tickOrigin()));
        datetimeManager_->setValue(
            axispropertytickerdatetimefrom_,
            QCPAxisTickerDateTime::keyToDateTime(axis->getfrom_axis()));
        datetimeManager_->setValue(
            axispropertytickerdatetimeto_,
            QCPAxisTickerDateTime::keyToDateTime(axis->getto_axis()));
      }
    } break;
  }
  fontManager_->setValue(axispropertyticklabelfontitem_,
                         axis->getticklabelfont_axis());
  colorManager_->setValue(axispropertyticklabelcoloritem_,
                          axis->getticklabelcolor_axis());
  intManager_->setValue(axispropertyticklabelpaddingitem_,
                        axis->getticklabelpadding_axis());
  doubleManager_->setValue(axispropertyticklabelrotationitem_,
                           axis->getticklabelrotation_axis());
  enumManager_->setValue(axispropertyticklabelsideitem_,
                         static_cast<int>(axis->getticklabelside_axis()));
  enumManager_->setValue(axispropertyticklabelformatitem_,
                         static_cast<int>(axis->getticklabelformat_axis()));
  intManager_->setValue(axispropertyticklabelprecisionitem_,
                        axis->getticklabelprecision_axis());
}

void PlotPropertyEditor::Grid2DPropertyBlock(AxisRect2D *axisrect) {
  propertybrowser_->clear();
  QPair<QPair<Grid2D *, Axis2D *>, QPair<Grid2D *, Axis2D *>> gridpair =
      axisrect->getGridPair();
  if (!gridpair.first.first || !gridpair.second.first) {
    qDebug() << QString::fromLatin1("invalid grid pointers");
    return;
  }
  propertybrowser_->addProperty(hgridaxispropertycomboitem_);
  propertybrowser_->addProperty(vgridaxispropertycomboitem_);

  {
    QStringList lsxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      lsxaxislist << xaxes.at(i)->getname_axis() +
                         QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == gridpair.first.second) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(hgridaxispropertycomboitem_, lsxaxislist);
    enumManager_->setValue(hgridaxispropertycomboitem_, currentxaxis);
  }

  Grid2D *hgrid = axisrect->getGridPair().first.first;

  boolManager_->setValue(hmajgridpropertyvisibleitem_,
                         hgrid->getMajorGridVisible());
  colorManager_->setValue(hmajgridpropertystrokecoloritem_,
                          hgrid->getMajorGridColor());
  doubleManager_->setValue(hmajgridpropertystrokethicknessitem_,
                           hgrid->getMajorGridwidth());
  enumManager_->setValue(hmajgridpropertystroketypeitem_,
                         hgrid->getMajorGridStyle() - 1);
  boolManager_->setValue(hmajgridpropertyzerolinevisibleitem_,
                         hgrid->getZerothLineVisible());
  colorManager_->setValue(hmajgridpropertyzerolinestrokecoloritem_,
                          hgrid->getZerothLineColor());
  doubleManager_->setValue(hmajgridpropertyzerolinestrokethicknessitem_,
                           hgrid->getZeroLinewidth());
  enumManager_->setValue(hmajgridpropertyzerolinestroketypeitem_,
                         hgrid->getZeroLineStyle() - 1);
  boolManager_->setValue(hmingridpropertyvisibleitem_,
                         hgrid->getMinorGridVisible());
  colorManager_->setValue(hmingridpropertystrokecoloritem_,
                          hgrid->getMinorGridColor());
  doubleManager_->setValue(hmingridpropertystrokethicknessitem_,
                           hgrid->getMinorGridwidth());
  enumManager_->setValue(hmingridpropertystroketypeitem_,
                         hgrid->getMinorGridStyle() - 1);

  {
    QStringList lsyaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      lsyaxislist << yaxes.at(i)->getname_axis() +
                         QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == gridpair.second.second) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(vgridaxispropertycomboitem_, lsyaxislist);
    enumManager_->setValue(vgridaxispropertycomboitem_, currentyaxis);
  }
  Grid2D *vgrid = axisrect->getGridPair().second.first;

  boolManager_->setValue(vmajgridpropertyvisibleitem_,
                         vgrid->getMajorGridVisible());
  colorManager_->setValue(vmajgridpropertystrokecoloritem_,
                          vgrid->getMajorGridColor());
  doubleManager_->setValue(vmajgridpropertystrokethicknessitem_,
                           vgrid->getMajorGridwidth());
  enumManager_->setValue(vmajgridpropertystroketypeitem_,
                         vgrid->getMajorGridStyle() - 1);
  boolManager_->setValue(vmajgridpropertyzerolinevisibleitem_,
                         vgrid->getZerothLineVisible());
  colorManager_->setValue(vmajgridpropertyzerolinestrokecoloritem_,
                          vgrid->getZerothLineColor());
  doubleManager_->setValue(vmajgridpropertyzerolinestrokethicknessitem_,
                           vgrid->getZeroLinewidth());
  enumManager_->setValue(vmajgridpropertyzerolinestroketypeitem_,
                         vgrid->getZeroLineStyle() - 1);
  boolManager_->setValue(vmingridpropertyvisibleitem_,
                         vgrid->getMinorGridVisible());
  colorManager_->setValue(vmingridpropertystrokecoloritem_,
                          vgrid->getMinorGridColor());
  doubleManager_->setValue(vmingridpropertystrokethicknessitem_,
                           vgrid->getMinorGridwidth());
  enumManager_->setValue(vmingridpropertystroketypeitem_,
                         vgrid->getMinorGridStyle() - 1);
}

void PlotPropertyEditor::Legend2DPropertyBlock(Legend2D *legend) {
  propertybrowser_->clear();

  // Legend Properties
  propertybrowser_->addProperty(itempropertylegendoriginxitem_);
  propertybrowser_->addProperty(itempropertylegendoriginyitem_);
  propertybrowser_->addProperty(itempropertylegendvisibleitem_);
  propertybrowser_->addProperty(itempropertylegenddirectionitem_);
  propertybrowser_->addProperty(itempropertylegendmarginitem_);
  propertybrowser_->addProperty(itempropertylegendfontitem_);
  propertybrowser_->addProperty(itempropertylegendtextcoloritem_);
  propertybrowser_->addProperty(itempropertylegendiconwidthitem_);
  propertybrowser_->addProperty(itempropertylegendiconheightitem_);
  propertybrowser_->addProperty(itempropertylegendicontextpaddingitem_);
  propertybrowser_->addProperty(itempropertylegendborderstrokecoloritem_);
  propertybrowser_->addProperty(itempropertylegendborderstrokethicknessitem_);
  propertybrowser_->addProperty(itempropertylegendborderstroketypeitem_);
  propertybrowser_->addProperty(itempropertylegendbackgroundcoloritem_);
  propertybrowser_->addProperty(itempropertylegendbackgroundfillstyleitem_);
  propertybrowser_->addProperty(itempropertylegendtitlevisibleitem_);

  doubleManager_->setValue(itempropertylegendoriginxitem_,
                           legend->getposition_legend().x());
  doubleManager_->setValue(itempropertylegendoriginyitem_,
                           legend->getposition_legend().y());
  boolManager_->setValue(itempropertylegendvisibleitem_,
                         legend->gethidden_legend());
  enumManager_->setValue(itempropertylegenddirectionitem_,
                         static_cast<int>(legend->getdirection_legend()));
  QRect rect;
  rect.setLeft(legend->margins().left());
  rect.setTop(legend->margins().top());
  rect.setRight(legend->margins().right());
  rect.setBottom(legend->margins().bottom());
  rectManager_->setValue(itempropertylegendmarginitem_, rect);
  fontManager_->setValue(itempropertylegendfontitem_, legend->font());
  colorManager_->setValue(itempropertylegendtextcoloritem_,
                          legend->textColor());
  intManager_->setValue(itempropertylegendiconwidthitem_,
                        legend->iconSize().rwidth());
  intManager_->setValue(itempropertylegendiconheightitem_,
                        legend->iconSize().rheight());
  intManager_->setValue(itempropertylegendicontextpaddingitem_,
                        legend->iconTextPadding());
  colorManager_->setValue(itempropertylegendborderstrokecoloritem_,
                          legend->getborderstrokecolor_legend());
  doubleManager_->setValue(itempropertylegendborderstrokethicknessitem_,
                           legend->getborderstrokethickness_legend());
  enumManager_->setValue(itempropertylegendborderstroketypeitem_,
                         legend->getborderstrokestyle_legend() - 1);
  colorManager_->setValue(itempropertylegendbackgroundcoloritem_,
                          legend->brush().color());
  enumManager_->setValue(itempropertylegendbackgroundfillstyleitem_,
                         legend->brush().style() - 1);
  boolManager_->setValue(itempropertylegendtitlevisibleitem_,
                         legend->istitle_legend());
  if (legend->istitle_legend()) {
    itempropertylegendtitletextitem_->setEnabled(true);
    itempropertylegendtitlefontitem_->setEnabled(true);
    itempropertylegendtitlecoloritem_->setEnabled(true);
  } else {
    itempropertylegendtitletextitem_->setEnabled(false);
    itempropertylegendtitlefontitem_->setEnabled(false);
    itempropertylegendtitlecoloritem_->setEnabled(false);
  }
  stringManager_->setValue(itempropertylegendtitletextitem_,
                           legend->titletext_legend());
  fontManager_->setValue(itempropertylegendtitlefontitem_,
                         legend->titlefont_legend());
  colorManager_->setValue(itempropertylegendtitlecoloritem_,
                          legend->titlecolor_legend());
}

void PlotPropertyEditor::TextItem2DPropertyBlock(TextItem2D* textitem) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(itempropertytextpixelpositionxitem_);
  propertybrowser_->addProperty(itempropertytextpixelpositionyitem_);
  propertybrowser_->addProperty(itempropertytextmarginitem_);
  propertybrowser_->addProperty(itempropertytexttextalignmentitem_);
  propertybrowser_->addProperty(itempropertytexttextitem_);
  propertybrowser_->addProperty(itempropertytextfontitem_);
  propertybrowser_->addProperty(itempropertytextcoloritem_);
  propertybrowser_->addProperty(itempropertytextantialiaseditem_);
  propertybrowser_->addProperty(itempropertytextstrokecoloritem_);
  propertybrowser_->addProperty(itempropertytextstrokethicknessitem_);
  propertybrowser_->addProperty(itempropertytextstroketypeitem_);
  propertybrowser_->addProperty(itempropertytextbackgroundcoloritem_);
  propertybrowser_->addProperty(itempropertytextbackgroundfillstyleitem_);
  propertybrowser_->addProperty(itempropertytextrotationitem_);

  doubleManager_->setValue(itempropertytextpixelpositionxitem_,
                           textitem->position->pixelPosition().x());
  doubleManager_->setValue(itempropertytextpixelpositionyitem_,
                           textitem->position->pixelPosition().y());
  QRect rect;
  rect.setLeft(textitem->padding().left());
  rect.setTop(textitem->padding().top());
  rect.setRight(textitem->padding().right());
  rect.setBottom(textitem->padding().bottom());
  rectManager_->setValue(itempropertytextmarginitem_, rect);
  stringManager_->setValue(itempropertytexttextitem_,
                           Utilities::joinstring(textitem->text()));
  fontManager_->setValue(itempropertytextfontitem_, textitem->font());
  colorManager_->setValue(itempropertytextcoloritem_, textitem->color());
  boolManager_->setValue(itempropertytextantialiaseditem_,
                         textitem->antialiased());
  colorManager_->setValue(itempropertytextstrokecoloritem_,
                          textitem->getstrokecolor_textitem());
  doubleManager_->setValue(itempropertytextstrokethicknessitem_,
                           textitem->getstrokethickness_textitem());
  enumManager_->setValue(itempropertytextstroketypeitem_,
                         textitem->getstrokestyle_textitem() - 1);
  colorManager_->setValue(itempropertytextbackgroundcoloritem_,
                          textitem->brush().color());
  enumManager_->setValue(itempropertytextbackgroundfillstyleitem_,
                         textitem->brush().style() - 1);
  doubleManager_->setValue(itempropertytextrotationitem_, textitem->rotation());
  enumManager_->setValue(
      itempropertytexttextalignmentitem_,
      static_cast<int>(textitem->gettextalignment_textitem()));
}

void PlotPropertyEditor::LineItem2DPropertyBlock(LineItem2D *lineitem) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(itempropertylinepixelpositionx1item_);
  propertybrowser_->addProperty(itempropertylinepixelpositiony1item_);
  propertybrowser_->addProperty(itempropertylinepixelpositionx2item_);
  propertybrowser_->addProperty(itempropertylinepixelpositiony2item_);
  propertybrowser_->addProperty(itempropertylineantialiaseditem_);
  propertybrowser_->addProperty(itempropertylinestrokecoloritem_);
  propertybrowser_->addProperty(itempropertylinestrokethicknessitem_);
  propertybrowser_->addProperty(itempropertylinestroketypeitem_);
  propertybrowser_->addProperty(itempropertylineendingstyleitem_);
  propertybrowser_->addProperty(itempropertylineendingwidthitem_);
  propertybrowser_->addProperty(itempropertylineendinglengthitem_);
  propertybrowser_->addProperty(itempropertylinestartingstyleitem_);
  propertybrowser_->addProperty(itempropertylinestartingwidthitem_);
  propertybrowser_->addProperty(itempropertylinestartinglengthitem_);

  doubleManager_->setValue(itempropertylinepixelpositionx1item_,
                           lineitem->position(QString::fromLatin1("start"))->pixelPosition().x());
  doubleManager_->setValue(itempropertylinepixelpositiony1item_,
                           lineitem->position(QString::fromLatin1("start"))->pixelPosition().y());
  doubleManager_->setValue(itempropertylinepixelpositionx2item_,
                           lineitem->position(QString::fromLatin1("end"))->pixelPosition().x());
  doubleManager_->setValue(itempropertylinepixelpositiony2item_,
                           lineitem->position(QString::fromLatin1("end"))->pixelPosition().y());
  boolManager_->setValue(itempropertylineantialiaseditem_,
                         lineitem->antialiased());
  colorManager_->setValue(itempropertylinestrokecoloritem_,
                          lineitem->getstrokecolor_lineitem());
  doubleManager_->setValue(itempropertylinestrokethicknessitem_,
                           lineitem->getstrokethickness_lineitem());
  enumManager_->setValue(itempropertylinestroketypeitem_,
                         lineitem->getstrokestyle_lineitem() - 1);
  enumManager_->setValue(
      itempropertylineendingstyleitem_,
      lineitem->getendstyle_lineitem(LineItem2D::LineEndLocation::Stop));
  doubleManager_->setValue(
      itempropertylineendingwidthitem_,
      lineitem->getendwidth_lineitem(LineItem2D::LineEndLocation::Stop));
  doubleManager_->setValue(
      itempropertylineendinglengthitem_,
      lineitem->getendlength_lineitem(LineItem2D::LineEndLocation::Stop));
  enumManager_->setValue(
      itempropertylinestartingstyleitem_,
      lineitem->getendstyle_lineitem(LineItem2D::LineEndLocation::Start));
  doubleManager_->setValue(
      itempropertylinestartingwidthitem_,
      lineitem->getendwidth_lineitem(LineItem2D::LineEndLocation::Start));
  doubleManager_->setValue(
      itempropertylinestartinglengthitem_,
      lineitem->getendlength_lineitem(LineItem2D::LineEndLocation::Start));
}

void PlotPropertyEditor::ImageItem2DPropertyBlock(ImageItem2D *imageitem) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(itempropertyimagesourceitem_);
  propertybrowser_->addProperty(itempropertyimagepixelpositionxitem_);
  propertybrowser_->addProperty(itempropertyimagepixelpositionyitem_);
  propertybrowser_->addProperty(itempropertyimagerotationitem_);
  propertybrowser_->addProperty(itempropertyimagestrokecoloritem_);
  propertybrowser_->addProperty(itempropertyimagestrokethicknessitem_);
  propertybrowser_->addProperty(itempropertyimagestroketypeitem_);

  doubleManager_->setValue(itempropertyimagepixelpositionxitem_,
                           imageitem->position(QString::fromLatin1("topLeft"))->pixelPosition().x());
  doubleManager_->setValue(itempropertyimagepixelpositionyitem_,
                           imageitem->position(QString::fromLatin1("topLeft"))->pixelPosition().y());
  intManager_->setValue(itempropertyimagerotationitem_,
                        imageitem->getrotation_imageitem());
  stringManager_->setValue(itempropertyimagesourceitem_,
                           imageitem->getsource_imageitem());
  colorManager_->setValue(itempropertyimagestrokecoloritem_,
                          imageitem->getstrokecolor_imageitem());
  doubleManager_->setValue(itempropertyimagestrokethicknessitem_,
                           imageitem->getstrokethickness_imageitem());
  enumManager_->setValue(itempropertyimagestroketypeitem_,
                         imageitem->getstrokestyle_imageitem() - 1);
}

void PlotPropertyEditor::LineSpecial2DPropertyBlock(LineSpecial2D *lsgraph,
                                                AxisRect2D *axisrect) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(lsplotpropertyxaxisitem_);
  propertybrowser_->addProperty(lsplotpropertyyaxisitem_);
  propertybrowser_->addProperty(lsplotpropertylinestyleitem_);
  propertybrowser_->addProperty(lsplotpropertylinestrokecoloritem_);
  propertybrowser_->addProperty(lsplotpropertylinestrokethicknessitem_);
  propertybrowser_->addProperty(lsplotpropertylinestroketypeitem_);
  propertybrowser_->addProperty(lsplotpropertylinefillstatusitem_);
  propertybrowser_->addProperty(lsplotpropertylinefillcoloritem_);
  propertybrowser_->addProperty(lsplotpropertylinefillstyleitem_);
  propertybrowser_->addProperty(lsplotpropertylineantialiaseditem_);
  propertybrowser_->addProperty(lsplotpropertyscatterstyleitem_);
  propertybrowser_->addProperty(lsplotpropertyscatterthicknessitem_);
  propertybrowser_->addProperty(lsplotpropertyscatterfillcoloritem_);
  propertybrowser_->addProperty(lsplotpropertyscatterstrokecoloritem_);
  propertybrowser_->addProperty(lsplotpropertyscatterstrokestyleitem_);
  propertybrowser_->addProperty(lsplotpropertyscatterstrokethicknessitem_);
  propertybrowser_->addProperty(lsplotpropertyscatterantialiaseditem_);
  propertybrowser_->addProperty(lsplotpropertylegendvisibleitem_);
  {
    QStringList lsyaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      lsyaxislist << yaxes.at(i)->getname_axis() +
                         QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == lsgraph->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(lsplotpropertyyaxisitem_, lsyaxislist);
    enumManager_->setValue(lsplotpropertyyaxisitem_, currentyaxis);
  }

  {
    QStringList lsxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      lsxaxislist << xaxes.at(i)->getname_axis() +
                         QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == lsgraph->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(lsplotpropertyxaxisitem_, lsxaxislist);
    enumManager_->setValue(lsplotpropertyxaxisitem_, currentxaxis);
  }

  enumManager_->setValue(lsplotpropertylinestyleitem_,
                         static_cast<int>(lsgraph->getlinetype_lsplot()));
  colorManager_->setValue(lsplotpropertylinestrokecoloritem_,
                          lsgraph->getlinestrokecolor_lsplot());
  doubleManager_->setValue(lsplotpropertylinestrokethicknessitem_,
                           lsgraph->getlinestrokethickness_lsplot());
  enumManager_->setValue(
      lsplotpropertylinestroketypeitem_,
      static_cast<int>(lsgraph->getlinestrokestyle_lsplot() - 1));
  enumManager_->setValue(lsplotpropertylinefillstyleitem_,
                         lsgraph->getlinefillstyle_lsplot() - 1);
  boolManager_->setValue(lsplotpropertylinefillstatusitem_,
                         lsgraph->getlinefillstatus_lsplot());
  colorManager_->setValue(lsplotpropertylinefillcoloritem_,
                          lsgraph->getlinefillcolor_lsplot());
  boolManager_->setValue(lsplotpropertylineantialiaseditem_,
                         lsgraph->getlineantialiased_lsplot());
  enumManager_->setValue(lsplotpropertyscatterstyleitem_,
                         static_cast<int>(lsgraph->getscattershape_lsplot()));
  doubleManager_->setValue(lsplotpropertyscatterthicknessitem_,
                           lsgraph->getscattersize_lsplot());
  colorManager_->setValue(lsplotpropertyscatterfillcoloritem_,
                          lsgraph->getscatterfillcolor_lsplot());
  colorManager_->setValue(lsplotpropertyscatterstrokecoloritem_,
                          lsgraph->getscatterstrokecolor_lsplot());
  enumManager_->setValue(
      lsplotpropertyscatterstrokestyleitem_,
      static_cast<int>(lsgraph->getscatterstrokestyle_lsplot() - 1));
  doubleManager_->setValue(lsplotpropertyscatterstrokethicknessitem_,
                           lsgraph->getscatterstrokethickness_lsplot());
  boolManager_->setValue(lsplotpropertyscatterantialiaseditem_,
                         lsgraph->getscatterantialiased_lsplot());
  boolManager_->setValue(lsplotpropertylegendvisibleitem_,
                         lsgraph->getlegendvisible_lsplot());
  stringManager_->setValue(
      lsplotpropertylegendtextitem_,
      Utilities::joinstring(lsgraph->getlegendtext_lsplot()));
}

void PlotPropertyEditor::LineSpecialChannel2DPropertyBlock(LineSpecial2D *lsgraph1,
                                                       LineSpecial2D *lsgraph2,
                                                       AxisRect2D *axisrect) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(channelplotpropertyxaxisitem_);
  propertybrowser_->addProperty(channelplotpropertyyaxisitem_);
  propertybrowser_->addProperty(channelplotpropertylegendvisibleitem_);
  propertybrowser_->addProperty(channel1plotpropertygroupitem_);
  propertybrowser_->addProperty(channel2plotpropertygroupitem_);

  {
    QStringList lsyaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      lsyaxislist << yaxes.at(i)->getname_axis() +
                         QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == lsgraph1->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(channelplotpropertyyaxisitem_, lsyaxislist);
    enumManager_->setValue(channelplotpropertyyaxisitem_, currentyaxis);
  }

  {
    QStringList lsxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      lsxaxislist << xaxes.at(i)->getname_axis() +
                         QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == lsgraph1->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(channelplotpropertyxaxisitem_, lsxaxislist);
    enumManager_->setValue(channelplotpropertyxaxisitem_, currentxaxis);
  }

  boolManager_->setValue(channelplotpropertylegendvisibleitem_,
                         lsgraph1->getlegendvisible_lsplot());
  stringManager_->setValue(
      channelplotpropertylegendtextitem_,
      Utilities::joinstring(lsgraph1->getlegendtext_lsplot()));
  enumManager_->setValue(channel1plotpropertylinestyleitem_,
                         static_cast<int>(lsgraph1->getlinetype_lsplot()));
  colorManager_->setValue(channel1plotpropertylinestrokecoloritem_,
                          lsgraph1->getlinestrokecolor_lsplot());
  doubleManager_->setValue(channel1plotpropertylinestrokethicknessitem_,
                           lsgraph1->getlinestrokethickness_lsplot());
  enumManager_->setValue(
      channel1plotpropertylinestroketypeitem_,
      static_cast<int>(lsgraph1->getlinestrokestyle_lsplot() - 1));
  colorManager_->setValue(channel1plotpropertylinefillcoloritem_,
                          lsgraph1->getlinefillcolor_lsplot());
  enumManager_->setValue(channel1plotpropertylinefillstylritem_,
                         lsgraph1->getlinefillstyle_lsplot() - 1);
  boolManager_->setValue(channel1plotpropertylineantialiaseditem_,
                         lsgraph1->getlineantialiased_lsplot());
  enumManager_->setValue(channel1plotpropertyscatterstyleitem_,
                         static_cast<int>(lsgraph1->getscattershape_lsplot()));
  doubleManager_->setValue(channel1plotpropertyscatterthicknessitem_,
                           lsgraph1->getscattersize_lsplot());
  colorManager_->setValue(channel1plotpropertyscatterfillcoloritem_,
                          lsgraph1->getscatterfillcolor_lsplot());
  colorManager_->setValue(channel1plotpropertyscatterstrokecoloritem_,
                          lsgraph1->getscatterstrokecolor_lsplot());
  enumManager_->setValue(
      channel1plotpropertyscatterstrokestyleitem_,
      static_cast<int>(lsgraph1->getscatterstrokestyle_lsplot() - 1));
  doubleManager_->setValue(channel1plotpropertyscatterstrokethicknessitem_,
                           lsgraph1->getscatterstrokethickness_lsplot());
  boolManager_->setValue(channel1plotpropertyscatterantialiaseditem_,
                         lsgraph1->getscatterantialiased_lsplot());
  enumManager_->setValue(channel2plotpropertylinestyleitem_,
                         static_cast<int>(lsgraph2->getlinetype_lsplot()));
  colorManager_->setValue(channel2plotpropertylinestrokecoloritem_,
                          lsgraph2->getlinestrokecolor_lsplot());
  doubleManager_->setValue(channel2plotpropertylinestrokethicknessitem_,
                           lsgraph2->getlinestrokethickness_lsplot());
  enumManager_->setValue(
      channel2plotpropertylinestroketypeitem_,
      static_cast<int>(lsgraph2->getlinestrokestyle_lsplot() - 1));
  boolManager_->setValue(channel2plotpropertylineantialiaseditem_,
                         lsgraph2->getlineantialiased_lsplot());
  enumManager_->setValue(channel2plotpropertyscatterstyleitem_,
                         static_cast<int>(lsgraph2->getscattershape_lsplot()));
  doubleManager_->setValue(channel2plotpropertyscatterthicknessitem_,
                           lsgraph2->getscattersize_lsplot());
  colorManager_->setValue(channel2plotpropertyscatterfillcoloritem_,
                          lsgraph2->getscatterfillcolor_lsplot());
  colorManager_->setValue(channel2plotpropertyscatterstrokecoloritem_,
                          lsgraph2->getscatterstrokecolor_lsplot());
  enumManager_->setValue(
      channel2plotpropertyscatterstrokestyleitem_,
      static_cast<int>(lsgraph2->getscatterstrokestyle_lsplot() - 1));
  doubleManager_->setValue(channel2plotpropertyscatterstrokethicknessitem_,
                           lsgraph2->getscatterstrokethickness_lsplot());
  boolManager_->setValue(channel2plotpropertyscatterantialiaseditem_,
                         lsgraph2->getscatterantialiased_lsplot());
}

void PlotPropertyEditor::Curve2DPropertyBlock(Curve2D *curve,
                                          AxisRect2D *axisrect) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(cplotpropertyxaxisitem_);
  propertybrowser_->addProperty(cplotpropertyyaxisitem_);
  propertybrowser_->addProperty(cplotpropertylinestyleitem_);
  propertybrowser_->addProperty(cplotpropertylinestrokecoloritem_);
  propertybrowser_->addProperty(cplotpropertylinestrokethicknessitem_);
  propertybrowser_->addProperty(cplotpropertylinestroketypeitem_);
  propertybrowser_->addProperty(cplotpropertylinefillstatusitem_);
  propertybrowser_->addProperty(cplotpropertylinefillcoloritem_);
  propertybrowser_->addProperty(cplotpropertylinefillstyleitem_);
  propertybrowser_->addProperty(cplotpropertylineantialiaseditem_);
  propertybrowser_->addProperty(cplotpropertyscatterstyleitem_);
  propertybrowser_->addProperty(cplotpropertyscatterthicknessitem_);
  propertybrowser_->addProperty(cplotpropertyscatterfillcoloritem_);
  propertybrowser_->addProperty(cplotpropertyscatterstrokecoloritem_);
  propertybrowser_->addProperty(cplotpropertyscatterstrokestyleitem_);
  propertybrowser_->addProperty(cplotpropertyscatterstrokethicknessitem_);
  propertybrowser_->addProperty(cplotpropertyscatterantialiaseditem_);
  propertybrowser_->addProperty(cplotpropertylegendvisibleitem_);
  {
    QStringList cyaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      cyaxislist << yaxes.at(i)->getname_axis() +
                        QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == curve->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(cplotpropertyyaxisitem_, cyaxislist);
    enumManager_->setValue(cplotpropertyyaxisitem_, currentyaxis);
  }

  {
    QStringList cxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      cxaxislist << xaxes.at(i)->getname_axis() +
                        QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == curve->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(cplotpropertyxaxisitem_, cxaxislist);
    enumManager_->setValue(cplotpropertyxaxisitem_, currentxaxis);
  }

  enumManager_->setValue(cplotpropertylinestyleitem_,
                         static_cast<int>(curve->getlinetype_cplot()));
  colorManager_->setValue(cplotpropertylinestrokecoloritem_,
                          curve->getlinestrokecolor_cplot());
  doubleManager_->setValue(cplotpropertylinestrokethicknessitem_,
                           curve->getlinestrokethickness_cplot());
  enumManager_->setValue(
      cplotpropertylinestroketypeitem_,
      static_cast<int>(curve->getlinestrokestyle_cplot() - 1));
  enumManager_->setValue(cplotpropertylinefillstyleitem_,
                         curve->getlinefillstyle_cplot() - 1);
  boolManager_->setValue(cplotpropertylinefillstatusitem_,
                         curve->getlinefillstatus_cplot());
  colorManager_->setValue(cplotpropertylinefillcoloritem_,
                          curve->getlinefillcolor_cplot());
  boolManager_->setValue(cplotpropertylineantialiaseditem_,
                         curve->getlineantialiased_cplot());
  enumManager_->setValue(cplotpropertyscatterstyleitem_,
                         static_cast<int>(curve->getscattershape_cplot()));
  doubleManager_->setValue(cplotpropertyscatterthicknessitem_,
                           curve->getscattersize_cplot());
  colorManager_->setValue(cplotpropertyscatterfillcoloritem_,
                          curve->getscatterfillcolor_cplot());
  colorManager_->setValue(cplotpropertyscatterstrokecoloritem_,
                          curve->getscatterstrokecolor_cplot());
  enumManager_->setValue(
      cplotpropertyscatterstrokestyleitem_,
      static_cast<int>(curve->getscatterstrokestyle_cplot() - 1));
  doubleManager_->setValue(cplotpropertyscatterstrokethicknessitem_,
                           curve->getscatterstrokethickness_cplot());
  boolManager_->setValue(cplotpropertyscatterantialiaseditem_,
                         curve->getscatterantialiased_cplot());
  boolManager_->setValue(cplotpropertylegendvisibleitem_,
                         curve->getlegendvisible_cplot());
  stringManager_->setValue(cplotpropertylegendtextitem_,
                           Utilities::joinstring(curve->getlegendtext_cplot()));
}

void PlotPropertyEditor::Bar2DPropertyBlock(Bar2D *bargraph, AxisRect2D *axisrect) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(barplotpropertyxaxisitem_);
  propertybrowser_->addProperty(barplotpropertyyaxisitem_);
  propertybrowser_->addProperty(barplotpropertywidthitem_);
  propertybrowser_->addProperty(barplotpropertystackgapitem_);
  propertybrowser_->addProperty(barplotpropertyfillantialiaseditem_);
  propertybrowser_->addProperty(barplotpropertyfillcoloritem_);
  propertybrowser_->addProperty(barplotpropertyfillstyleitem_);
  propertybrowser_->addProperty(barplotpropertyantialiaseditem_);
  propertybrowser_->addProperty(barplotpropertystrokecoloritem_);
  propertybrowser_->addProperty(barplotpropertystrokethicknessitem_);
  propertybrowser_->addProperty(barplotpropertystrokestyleitem_);
  propertybrowser_->addProperty(barplotpropertylegendtextitem_);
  if (bargraph->ishistogram_barplot())
    propertybrowser_->addProperty(barplotpropertyhistautobinstatusitem_);
  QStringList baryaxislist;
  int currentyaxis = 0;
  int ycount = 0;
  if (bargraph->getxaxis()->getorientation_axis() ==
          Axis2D::AxisOreantation::Top ||
      bargraph->getxaxis()->getorientation_axis() ==
          Axis2D::AxisOreantation::Bottom) {
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();
    for (int i = 0; i < yaxes.size(); i++) {
      baryaxislist << yaxes.at(i)->getname_axis() +
                          QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == bargraph->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
  } else {
    QList<Axis2D *> yaxes = axisrect->getXAxes2D();
    for (int i = 0; i < yaxes.size(); i++) {
      baryaxislist << yaxes.at(i)->getname_axis() +
                          QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == bargraph->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
  }
  enumManager_->setEnumNames(barplotpropertyyaxisitem_, baryaxislist);
  enumManager_->setValue(barplotpropertyyaxisitem_, currentyaxis);

  QStringList barxaxislist;
  int currentxaxis = 0;
  int xcount = 0;
  if (bargraph->getxaxis()->getorientation_axis() ==
          Axis2D::AxisOreantation::Top ||
      bargraph->getxaxis()->getorientation_axis() ==
          Axis2D::AxisOreantation::Bottom) {
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      barxaxislist << xaxes.at(i)->getname_axis() +
                          QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == bargraph->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }
  } else {
    QList<Axis2D *> xaxes = axisrect->getYAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      barxaxislist << xaxes.at(i)->getname_axis() +
                          QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == bargraph->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }
  }
  enumManager_->setEnumNames(barplotpropertyxaxisitem_, barxaxislist);
  enumManager_->setValue(barplotpropertyxaxisitem_, currentxaxis);

  doubleManager_->setValue(barplotpropertywidthitem_, bargraph->width());
  double spacing;
  (bargraph->getBarStyle() == Bar2D::BarStyle::Grouped)
      ? spacing = bargraph->getBarGroup()->spacing()
      : spacing = bargraph->stackingGap();
  doubleManager_->setValue(barplotpropertystackgapitem_, spacing);
  boolManager_->setValue(barplotpropertyfillantialiaseditem_,
                         bargraph->antialiasedFill());
  colorManager_->setValue(barplotpropertyfillcoloritem_,
                          bargraph->getfillcolor_barplot());
  enumManager_->setValue(barplotpropertyfillstyleitem_,
                         bargraph->getfillstyle_barplot() - 1);
  boolManager_->setValue(barplotpropertyantialiaseditem_,
                         bargraph->antialiased());
  colorManager_->setValue(barplotpropertystrokecoloritem_,
                          bargraph->getstrokecolor_barplot());
  doubleManager_->setValue(barplotpropertystrokethicknessitem_,
                           bargraph->getstrokethickness_barplot());
  enumManager_->setValue(barplotpropertystrokestyleitem_,
                         bargraph->getstrokestyle_barplot() - 1);
  stringManager_->setValue(barplotpropertylegendtextitem_,
                           Utilities::joinstring(bargraph->name()));
  if (bargraph->ishistogram_barplot()) {
    boolManager_->setValue(barplotpropertyhistautobinstatusitem_,
                           bargraph->getdatablock_histplot()->getautobin());
    doubleManager_->setValue(barplotpropertyhistbeginitem_,
                             bargraph->getdatablock_histplot()->getbegin());
    doubleManager_->setValue(barplotpropertyhistenditem_,
                             bargraph->getdatablock_histplot()->getend());
    doubleManager_->setValue(barplotpropertyhistbinitem_,
                             bargraph->getdatablock_histplot()->getbinsize());
  }
}

void PlotPropertyEditor::StatBox2DPropertyBlock(StatBox2D *statbox,
                                            AxisRect2D *axisrect) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(statboxplotpropertyxaxisitem_);
  propertybrowser_->addProperty(statboxplotpropertyyaxisitem_);
  propertybrowser_->addProperty(statboxplotpropertywidthitem_);
  propertybrowser_->addProperty(statboxplotpropertyboxstyleitem_);
  propertybrowser_->addProperty(statboxplotpropertyantialiaseditem_);
  propertybrowser_->addProperty(statboxplotpropertyboxoutlinecoloritem_);
  propertybrowser_->addProperty(statboxplotpropertyboxoutlinethicknessitem_);
  propertybrowser_->addProperty(statboxplotpropertyboxoutlinestyleitem_);
  propertybrowser_->addProperty(statboxplotpropertyfillantialiaseditem_);
  propertybrowser_->addProperty(statboxplotpropertyfillstatusitem_);
  propertybrowser_->addProperty(statboxplotpropertyfillcoloritem_);
  propertybrowser_->addProperty(statboxplotpropertyfillstyleitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerwidthitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerstyleitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerantialiaseditem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerstrokecoloritem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerstrokethicknessitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerstrokestyleitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerbarstrokecoloritem_);
  propertybrowser_->addProperty(
      statboxplotpropertywhiskerbarstrokethicknessitem_);
  propertybrowser_->addProperty(statboxplotpropertywhiskerbarstrokestyleitem_);
  propertybrowser_->addProperty(statboxplotpropertymedianstrokecoloritem_);
  propertybrowser_->addProperty(statboxplotpropertymideanstrokethicknessitem_);
  propertybrowser_->addProperty(statboxplotpropertymideanstrokestyleitem_);
  propertybrowser_->addProperty(statboxplotpropertyscatterantialiaseditem_);
  propertybrowser_->addProperty(statboxplotpropertyscattershowitem_);
  propertybrowser_->addProperty(statboxplotpropertyscatterstyleitem_);
  propertybrowser_->addProperty(statboxplotpropertyscattersizeitem_);
  propertybrowser_->addProperty(statboxplotpropertyscatterfillcoloritem_);
  propertybrowser_->addProperty(statboxplotpropertyscatteroutlinecoloritem_);
  propertybrowser_->addProperty(
      statboxplotpropertyscatteroutlinethicknessitem_);
  propertybrowser_->addProperty(statboxplotpropertyscatteroutlinestyleitem_);
  propertybrowser_->addProperty(statboxplotpropertylegendtextitem_);

  {
    QStringList statboxyaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      statboxyaxislist << yaxes.at(i)->getname_axis() +
                              QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == statbox->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(statboxplotpropertyyaxisitem_, statboxyaxislist);
    enumManager_->setValue(statboxplotpropertyyaxisitem_, currentyaxis);
  }

  {
    QStringList statboxxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      statboxxaxislist << xaxes.at(i)->getname_axis() +
                              QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == statbox->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(statboxplotpropertyxaxisitem_, statboxxaxislist);
    enumManager_->setValue(statboxplotpropertyxaxisitem_, currentxaxis);
  }

  doubleManager_->setValue(statboxplotpropertywidthitem_, statbox->width());
  doubleManager_->setValue(statboxplotpropertywhiskerwidthitem_,
                           statbox->whiskerWidth());
  enumManager_->setValue(statboxplotpropertyboxstyleitem_,
                         static_cast<int>(statbox->getboxstyle_statbox()));
  enumManager_->setValue(statboxplotpropertywhiskerstyleitem_,
                         static_cast<int>(statbox->getwhiskerstyle_statbox()));
  boolManager_->setValue(statboxplotpropertyantialiaseditem_,
                         statbox->antialiased());
  boolManager_->setValue(statboxplotpropertyfillantialiaseditem_,
                         statbox->antialiasedFill());

  colorManager_->setValue(statboxplotpropertyboxoutlinecoloritem_,
                          statbox->pen().color());
  doubleManager_->setValue(statboxplotpropertyboxoutlinethicknessitem_,
                           statbox->pen().widthF());
  enumManager_->setValue(statboxplotpropertyboxoutlinestyleitem_,
                         statbox->pen().style() - 1);
  enumManager_->setValue(statboxplotpropertyfillstyleitem_,
                         statbox->getfillstyle_statbox() - 1);
  boolManager_->setValue(statboxplotpropertyfillstatusitem_,
                         statbox->getfillstatus_statbox());
  colorManager_->setValue(statboxplotpropertyfillcoloritem_,
                          statbox->getfillcolor_statbox());
  boolManager_->setValue(statboxplotpropertywhiskerantialiaseditem_,
                         statbox->whiskerAntialiased());
  colorManager_->setValue(statboxplotpropertywhiskerstrokecoloritem_,
                          statbox->getwhiskerstrokecolor_statbox());
  doubleManager_->setValue(statboxplotpropertywhiskerstrokethicknessitem_,
                           statbox->getwhiskerstrokethickness_statbox());
  enumManager_->setValue(statboxplotpropertywhiskerstrokestyleitem_,
                         statbox->getwhiskerstrokestyle_statbox() - 1);
  colorManager_->setValue(statboxplotpropertywhiskerbarstrokecoloritem_,
                          statbox->getwhiskerbarstrokecolor_statbox());
  doubleManager_->setValue(statboxplotpropertywhiskerbarstrokethicknessitem_,
                           statbox->getwhiskerbarstrokethickness_statbox());
  enumManager_->setValue(statboxplotpropertywhiskerbarstrokestyleitem_,
                         statbox->getwhiskerbarstrokestyle_statbox() - 1);
  colorManager_->setValue(statboxplotpropertymedianstrokecoloritem_,
                          statbox->getmedianstrokecolor_statbox());
  doubleManager_->setValue(statboxplotpropertymideanstrokethicknessitem_,
                           statbox->getmedianstrokethickness_statbox());
  enumManager_->setValue(statboxplotpropertymideanstrokestyleitem_,
                         statbox->getmedianstrokestyle_statbox() - 1);
  boolManager_->setValue(statboxplotpropertyscatterantialiaseditem_,
                         statbox->antialiasedScatters());
  enumManager_->setValue(
      statboxplotpropertyscattershowitem_,
      static_cast<int>(statbox->getOutlierScatter_statbox()));
  enumManager_->setValue(statboxplotpropertyscatterstyleitem_,
                         static_cast<int>(statbox->getscattershape_statbox()));
  doubleManager_->setValue(statboxplotpropertyscattersizeitem_,
                           statbox->getscattersize_statbox());
  colorManager_->setValue(statboxplotpropertyscatterfillcoloritem_,
                          statbox->getscatterfillcolor_statbox());
  colorManager_->setValue(statboxplotpropertyscatteroutlinecoloritem_,
                          statbox->getscatterstrokecolor_statbox());
  doubleManager_->setValue(statboxplotpropertyscatteroutlinethicknessitem_,
                           statbox->getscatterstrokethickness_statbox());
  enumManager_->setValue(statboxplotpropertyscatteroutlinestyleitem_,
                         statbox->getscatterstrokestyle_statbox() - 1);
  stringManager_->setValue(statboxplotpropertylegendtextitem_,
                           Utilities::joinstring(statbox->name()));
}

void PlotPropertyEditor::Vector2DPropertyBlock(Vector2D *vectorgraph,
                                           AxisRect2D *axisrect) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(vectorpropertyxaxisitem_);
  propertybrowser_->addProperty(vectorpropertyyaxisitem_);
  propertybrowser_->addProperty(vectorpropertylinestrokecoloritem_);
  propertybrowser_->addProperty(vectorpropertylinestrokethicknessitem_);
  propertybrowser_->addProperty(vectorpropertylinestroketypeitem_);
  propertybrowser_->addProperty(vectorpropertylineendingtypeitem_);
  propertybrowser_->addProperty(vectorpropertylineendingheightitem_);
  propertybrowser_->addProperty(vectorpropertylineendingwidthitem_);
  propertybrowser_->addProperty(vectorpropertylineantialiaseditem_);
  propertybrowser_->addProperty(vectorpropertylegendvisibleitem_);
  {
    QStringList vectoryaxislist;
    int currentyaxis = 0;
    int ycount = 0;
    QList<Axis2D *> yaxes = axisrect->getYAxes2D();

    for (int i = 0; i < yaxes.size(); i++) {
      vectoryaxislist << yaxes.at(i)->getname_axis() +
                             QString::number(yaxes.at(i)->getnumber_axis());
      if (yaxes.at(i) == vectorgraph->getyaxis()) {
        currentyaxis = ycount;
      }
      ycount++;
    }
    enumManager_->setEnumNames(vectorpropertyyaxisitem_, vectoryaxislist);
    enumManager_->setValue(vectorpropertyyaxisitem_, currentyaxis);
  }

  {
    QStringList vectorxaxislist;
    int currentxaxis = 0;
    int xcount = 0;
    QList<Axis2D *> xaxes = axisrect->getXAxes2D();
    for (int i = 0; i < xaxes.size(); i++) {
      vectorxaxislist << xaxes.at(i)->getname_axis() +
                             QString::number(xaxes.at(i)->getnumber_axis());
      if (xaxes.at(i) == vectorgraph->getxaxis()) {
        currentxaxis = xcount;
      }
      xcount++;
    }

    enumManager_->setEnumNames(vectorpropertyxaxisitem_, vectorxaxislist);
    enumManager_->setValue(vectorpropertyxaxisitem_, currentxaxis);
  }
  colorManager_->setValue(vectorpropertylinestrokecoloritem_,
                          vectorgraph->getlinestrokecolor_vecplot());
  doubleManager_->setValue(vectorpropertylinestrokethicknessitem_,
                           vectorgraph->getlinestrokethickness_vecplot());
  enumManager_->setValue(
      vectorpropertylinestroketypeitem_,
      static_cast<int>(vectorgraph->getlinestrokestyle_vecplot() - 1));
  enumManager_->setValue(vectorpropertylineendingtypeitem_,
                         static_cast<int>(vectorgraph->getendstyle_vecplot(
                             Vector2D::LineEndLocation::Head)));
  doubleManager_->setValue(
      vectorpropertylineendingheightitem_,
      vectorgraph->getendheight_vecplot(Vector2D::LineEndLocation::Head));
  doubleManager_->setValue(
      vectorpropertylineendingwidthitem_,
      vectorgraph->getendwidth_vecplot(Vector2D::LineEndLocation::Head));
  boolManager_->setValue(vectorpropertylineantialiaseditem_,
                         vectorgraph->getlineantialiased_vecplot());
  boolManager_->setValue(vectorpropertylegendvisibleitem_,
                         vectorgraph->getlegendvisible_vecplot());
  stringManager_->setValue(
      vectorpropertylegendtextitem_,
      Utilities::joinstring(vectorgraph->getlegendtext_vecplot()));
}

void PlotPropertyEditor::Pie2DPropertyBlock(Pie2D *piegraph, AxisRect2D *axisrect) {
  Q_UNUSED(axisrect)
  propertybrowser_->clear();

  // Pie Properties Block
  propertybrowser_->addProperty(pieplotpropertystyleitem_);
  propertybrowser_->addProperty(pieplotpropertylinestrokecoloritem_);
  propertybrowser_->addProperty(pieplotpropertylinestrokethicknessitem_);
  propertybrowser_->addProperty(pieplotpropertylinestroketypeitem_);
  propertybrowser_->addProperty(pieplotpropertymarginpercentitem_);

  enumManager_->setValue(pieplotpropertystyleitem_,
                         static_cast<int>(piegraph->getStyle_pieplot()));
  colorManager_->setValue(pieplotpropertylinestrokecoloritem_,
                          piegraph->getstrokecolor_pieplot());
  doubleManager_->setValue(pieplotpropertylinestrokethicknessitem_,
                           piegraph->getstrokethickness_pieplot());
  enumManager_->setValue(pieplotpropertylinestroketypeitem_,
                         piegraph->getstrokestyle_pieplot() - 1);
  intManager_->setValue(pieplotpropertymarginpercentitem_,
                        piegraph->getmarginpercent_pieplot());
}

void PlotPropertyEditor::ColorMap2DPropertyBlock(ColorMap2D *colormap,
                                             AxisRect2D *axisrect) {
  Q_UNUSED(axisrect)
  propertybrowser_->clear();

  // Colormap Properties Block
  propertybrowser_->addProperty(colormappropertyinterpolateitem_);
  propertybrowser_->addProperty(colormappropertytightboundaryitem_);
  propertybrowser_->addProperty(colormappropertylevelcountitem_);
  propertybrowser_->addProperty(colormappropertygradientitem_);
  propertybrowser_->addProperty(colormappropertygradientinvertitem_);
  propertybrowser_->addProperty(colormappropertygradientperiodicitem_);

  propertybrowser_->addProperty(colormappropertyscalevisibleitem_);
  propertybrowser_->addProperty(colormappropertyscaleaxisvisibleitem_);
  propertybrowser_->addProperty(colormappropertyscaleaxistickvisibilityitem_);
  propertybrowser_->addProperty(
      colormappropertyscaleaxissubtickvisibilityitem_);
  propertybrowser_->addProperty(
      colormappropertyscaleaxisticklabelvisibilityitem_);

  boolManager_->setValue(colormappropertyinterpolateitem_,
                         colormap->interpolate());
  boolManager_->setValue(colormappropertytightboundaryitem_,
                         colormap->tightBoundary());
  intManager_->setValue(colormappropertylevelcountitem_,
                        colormap->getlevelcount_colormap());
  enumManager_->setValue(colormappropertygradientitem_,
                         static_cast<int>(colormap->getgradient_colormap()));
  boolManager_->setValue(colormappropertygradientinvertitem_,
                         colormap->getgradientinverted_colormap());
  boolManager_->setValue(colormappropertygradientperiodicitem_,
                         colormap->getgradientperiodic_colormap());
  boolManager_->setValue(colormappropertyscalevisibleitem_,
                         colormap->getcolormapscale_colormap()->visible());
  intManager_->setValue(colormappropertyscalewidthitem_,
                        colormap->getcolormapscalewidth_colormap());
  boolManager_->setValue(
      colormappropertyscaleaxisvisibleitem_,
      colormap->getcolormapscale_colormap()->axis()->visible());
  intManager_->setValue(
      colormappropertyscaleaxisoffsetitem_,
      colormap->getcolormapscale_colormap()->axis()->offset());
  doubleManager_->setValue(
      colormappropertyscaleaxisfromitem_,
      colormap->getcolormapscale_colormap()->axis()->range().lower);
  doubleManager_->setValue(
      colormappropertyscaleaxistoitem_,
      colormap->getcolormapscale_colormap()->axis()->range().upper);
  enumManager_->setValue(colormappropertyscaleaxislinlogitem_,
                         static_cast<int>(colormap->dataScaleType()));
  boolManager_->setValue(
      colormappropertyscaleaxisinvertitem_,
      colormap->getcolormapscale_colormap()->axis()->rangeReversed());
  colorManager_->setValue(
      colormappropertyscaleaxisstrokecoloritem_,
      colormap->getcolormapscale_colormap()->axis()->basePen().color());
  doubleManager_->setValue(
      colormappropertyscaleaxisstrokethicknessitem_,
      colormap->getcolormapscale_colormap()->axis()->basePen().widthF());
  enumManager_->setValue(
      colormappropertyscaleaxisstroketypeitem_,
      colormap->getcolormapscale_colormap()->axis()->basePen().style() - 1);
  boolManager_->setValue(
      colormappropertyscaleaxisantialiaseditem_,
      colormap->getcolormapscale_colormap()->axis()->antialiased());
  stringManager_->setValue(colormappropertyscaleaxislabeltextitem_,
                           colormap->getname_colormap());
  fontManager_->setValue(
      colormappropertyscaleaxislabelfontitem_,
      colormap->getcolormapscale_colormap()->axis()->labelFont());
  colorManager_->setValue(
      colormappropertyscaleaxislabelcoloritem_,
      colormap->getcolormapscale_colormap()->axis()->labelColor());
  intManager_->setValue(
      colormappropertyscaleaxislabelpaddingitem_,
      colormap->getcolormapscale_colormap()->axis()->labelPadding());
  boolManager_->setValue(
      colormappropertyscaleaxistickvisibilityitem_,
      colormap->getcolormapscale_colormap()->axis()->ticks());
  intManager_->setValue(
      colormappropertyscaleaxisticklengthinitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLengthIn());
  intManager_->setValue(
      colormappropertyscaleaxisticklengthoutitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLengthOut());
  colorManager_->setValue(
      colormappropertyscaleaxistickstrokecoloritem_,
      colormap->getcolormapscale_colormap()->axis()->tickPen().color());
  doubleManager_->setValue(
      colormappropertyscaleaxistickstrokethicknessitem_,
      colormap->getcolormapscale_colormap()->axis()->tickPen().widthF());
  enumManager_->setValue(
      colormappropertyscaleaxistickstroketypeitem_,
      colormap->getcolormapscale_colormap()->axis()->tickPen().style() - 1);
  boolManager_->setValue(
      colormappropertyscaleaxissubtickvisibilityitem_,
      colormap->getcolormapscale_colormap()->axis()->subTicks());
  intManager_->setValue(
      colormappropertyscaleaxissubticklengthinitem_,
      colormap->getcolormapscale_colormap()->axis()->subTickLengthIn());
  intManager_->setValue(
      colormappropertyscaleaxissubticklengthoutitem_,
      colormap->getcolormapscale_colormap()->axis()->subTickLengthOut());
  colorManager_->setValue(
      colormappropertyscaleaxissubtickstrokecoloritem_,
      colormap->getcolormapscale_colormap()->axis()->subTickPen().color());
  doubleManager_->setValue(
      colormappropertyscaleaxissubtickstrokethicknessitem_,
      colormap->getcolormapscale_colormap()->axis()->subTickPen().widthF());
  enumManager_->setValue(
      colormappropertyscaleaxissubtickstroketypeitem_,
      colormap->getcolormapscale_colormap()->axis()->subTickPen().style() - 1);
  boolManager_->setValue(
      colormappropertyscaleaxisticklabelvisibilityitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabels());
  fontManager_->setValue(
      colormappropertyscaleaxisticklabelfontitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabelFont());
  colorManager_->setValue(
      colormappropertyscaleaxisticklabelcoloritem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabelColor());
  intManager_->setValue(
      colormappropertyscaleaxisticklabelpaddingitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabelPadding());
  doubleManager_->setValue(
      colormappropertyscaleaxisticklabelrotationitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabelRotation());
  enumManager_->setValue(
      colormappropertyscaleaxisticklabelsideitem_,
      colormap->getcolormapscale_colormap()->axis()->tickLabelSide());
  enumManager_->setValue(
      colormappropertyscaleaxisticklabelformatitem_,
      static_cast<int>(colormap->getcolormapscaleticklabelformat_axis()));
  intManager_->setValue(
      colormappropertyscaleaxisticklabelprecisionitem_,
      colormap->getcolormapscale_colormap()->axis()->numberPrecision());
}

void PlotPropertyEditor::ErrorBar2DPropertyBlock(ErrorBar2D *errorbar,
                                             AxisRect2D *axisrect) {
  Q_UNUSED(axisrect)
  propertybrowser_->clear();
  propertybrowser_->addProperty(errorbarpropertywhiskerwidthitem_);
  propertybrowser_->addProperty(errorbarpropertysymbolgaptem_);
  propertybrowser_->addProperty(errorbarpropertyantialiaseditem_);
  propertybrowser_->addProperty(errorbarpropertystrokecoloritem_);
  propertybrowser_->addProperty(errorbarpropertystrokethicknessitem_);
  propertybrowser_->addProperty(errorbarpropertystroketypeitem_);
  propertybrowser_->addProperty(errorbarpropertyfillstatusitem_);
  propertybrowser_->addProperty(errorbarpropertyfillcoloritem_);
  doubleManager_->setValue(errorbarpropertywhiskerwidthitem_,
                           errorbar->whiskerWidth());
  doubleManager_->setValue(errorbarpropertysymbolgaptem_,
                           errorbar->symbolGap());
  colorManager_->setValue(errorbarpropertystrokecoloritem_,
                          errorbar->pen().color());
  doubleManager_->setValue(errorbarpropertystrokethicknessitem_,
                           errorbar->pen().widthF());
  enumManager_->setValue(errorbarpropertystroketypeitem_,
                         errorbar->pen().style() - 1);
  boolManager_->setValue(errorbarpropertyfillstatusitem_,
                         errorbar->getfillstatus_errorbar());
  colorManager_->setValue(errorbarpropertyfillcoloritem_,
                          errorbar->brush().color());
  boolManager_->setValue(errorbarpropertyantialiaseditem_,
                         errorbar->antialiased());
}

void PlotPropertyEditor::Canvas3DPropertyBlock(QAbstract3DGraph *graph) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dcanvasthemeitem_);
  propertybrowser_->addProperty(plot3dcanvassizeitem_);

  enumManager_->setValue(plot3dcanvasthemeitem_, graph->activeTheme()->type());
  sizeManager_->setValue(plot3dcanvassizeitem_, graph->size());
}

void PlotPropertyEditor::Theme3DPropertyBlock(Q3DTheme *theme) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dcanvaswindowcoloritem_);
  propertybrowser_->addProperty(plot3dcanvasbackgroundvisibleitem_);
  propertybrowser_->addProperty(plot3dcanvaslightcoloritem_);
  propertybrowser_->addProperty(plot3dcanvasgridvisibleitem_);
  propertybrowser_->addProperty(plot3dcanvaslabelbackgroundvisibleitem_);
  propertybrowser_->addProperty(plot3dcanvasambientlightstrengthitem_);
  propertybrowser_->addProperty(plot3dcanvaslightstrengthitem_);

  colorManager_->setValue(plot3dcanvaswindowcoloritem_, theme->windowColor());
  boolManager_->setValue(plot3dcanvasbackgroundvisibleitem_,
                         theme->isBackgroundEnabled());
  colorManager_->setValue(plot3dcanvasbackgroundcoloritem_,
                          theme->backgroundColor());
  doubleManager_->setValue(plot3dcanvasambientlightstrengthitem_,
                           theme->ambientLightStrength());
  doubleManager_->setValue(plot3dcanvaslightstrengthitem_,
                           theme->lightStrength());
  colorManager_->setValue(plot3dcanvaslightcoloritem_, theme->lightColor());
  boolManager_->setValue(plot3dcanvasgridvisibleitem_, theme->isGridEnabled());
  colorManager_->setValue(plot3dcanvasgridcoloritem_, theme->gridLineColor());
  fontManager_->setValue(plot3dcanvasfontitem_, theme->font());
  boolManager_->setValue(plot3dcanvaslabelbackgroundvisibleitem_,
                         theme->isLabelBackgroundEnabled());
  colorManager_->setValue(plot3dcanvaslabelbackgroundcoloritem_,
                          theme->labelBackgroundColor());
  boolManager_->setValue(plot3dcanvaslabelbordervisibleitem_,
                         theme->isLabelBorderEnabled());
  colorManager_->setValue(plot3dcanvaslabeltextcoloritem_,
                          theme->labelTextColor());
}

void PlotPropertyEditor::Axis3DValuePropertyBlock(QValue3DAxis *axis) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3daxisvalueautoadjustrangeitem_);
  propertybrowser_->addProperty(plot3daxisvaluerangeloweritem_);
  propertybrowser_->addProperty(plot3daxisvaluerangeupperitem_);
  propertybrowser_->addProperty(plot3dvalueaxisreverseitem_);
  propertybrowser_->addProperty(plot3dvalueaxistickcountitem_);
  propertybrowser_->addProperty(plot3dvalueaxissubtickcountitem_);
  propertybrowser_->addProperty(plot3dvalueaxislabelformatitem_);
  propertybrowser_->addProperty(plot3daxisvalueticklabelrotationitem_);
  propertybrowser_->addProperty(plot3daxisvaluetitlevisibleitem_);
  propertybrowser_->addProperty(plot3daxisvaluetitlefixeditem_);
  propertybrowser_->addProperty(plot3daxisvaluetitletextitem_);

  boolManager_->setValue(plot3daxisvalueautoadjustrangeitem_,
                         axis->isAutoAdjustRange());
  doubleManager_->setValue(plot3daxisvaluerangeloweritem_, axis->min());
  doubleManager_->setValue(plot3daxisvaluerangeupperitem_, axis->max());
  stringManager_->setValue(plot3dvalueaxislabelformatitem_,
                           axis->labelFormat());
  boolManager_->setValue(plot3dvalueaxisreverseitem_, axis->reversed());
  intManager_->setValue(plot3dvalueaxistickcountitem_, axis->segmentCount());
  intManager_->setValue(plot3dvalueaxissubtickcountitem_,
                        axis->subSegmentCount());
  doubleManager_->setValue(plot3daxisvalueticklabelrotationitem_,
                           axis->labelAutoRotation());
  boolManager_->setValue(plot3daxisvaluetitlevisibleitem_,
                         axis->isTitleVisible());
  boolManager_->setValue(plot3daxisvaluetitlefixeditem_, axis->isTitleFixed());
  stringManager_->setValue(plot3daxisvaluetitletextitem_, axis->title());
}

void PlotPropertyEditor::Axis3DCatagoryPropertyBlock(QCategory3DAxis *axis) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3daxiscatagoryautoadjustrangeitem_);
  propertybrowser_->addProperty(plot3daxiscatagoryrangeloweritem_);
  propertybrowser_->addProperty(plot3daxiscatagoryrangeupperitem_);
  propertybrowser_->addProperty(plot3daxiscatagoryticklabelrotationitem_);
  propertybrowser_->addProperty(plot3daxiscatagorytitlevisibleitem_);
  propertybrowser_->addProperty(plot3daxiscatagorytitlefixeditem_);
  propertybrowser_->addProperty(plot3daxiscatagorytitletextitem_);

  boolManager_->setValue(plot3daxiscatagoryautoadjustrangeitem_,
                         axis->isAutoAdjustRange());
  doubleManager_->setValue(plot3daxiscatagoryrangeloweritem_, axis->min());
  doubleManager_->setValue(plot3daxiscatagoryrangeupperitem_, axis->max());
  doubleManager_->setValue(plot3daxiscatagoryticklabelrotationitem_,
                           axis->labelAutoRotation());
  boolManager_->setValue(plot3daxiscatagorytitlevisibleitem_,
                         axis->isTitleVisible());
  boolManager_->setValue(plot3daxiscatagorytitlefixeditem_,
                         axis->isTitleFixed());
  stringManager_->setValue(plot3daxiscatagorytitletextitem_, axis->title());
}

void PlotPropertyEditor::Surface3DPropertyBlock(Surface3D *surface) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dsurfaceaspectratioitem_);
  propertybrowser_->addProperty(plot3dsurfacehorizontalaspectratioitem_);
  propertybrowser_->addProperty(plot3dsurfaceshadowqualityitem_);
  propertybrowser_->addProperty(plot3dsurfacefliphorizontalgriditem_);
  propertybrowser_->addProperty(plot3dsurfaceorthoprojectionstatusitem_);
  propertybrowser_->addProperty(plot3dsurfacepolarstatusitem_);

  doubleManager_->setValue(plot3dsurfaceaspectratioitem_,
                           surface->getGraph()->aspectRatio());
  doubleManager_->setValue(plot3dsurfacehorizontalaspectratioitem_,
                           surface->getGraph()->horizontalAspectRatio());
  enumManager_->setValue(
      plot3dsurfaceshadowqualityitem_,
      static_cast<int>(surface->getGraph()->shadowQuality()));
  boolManager_->setValue(plot3dsurfacefliphorizontalgriditem_,
                         surface->getGraph()->flipHorizontalGrid());
  boolManager_->setValue(plot3dsurfaceorthoprojectionstatusitem_,
                         surface->getGraph()->isOrthoProjection());
  boolManager_->setValue(plot3dsurfacepolarstatusitem_,
                         surface->getGraph()->isPolar());
}

void PlotPropertyEditor::Bar3DPropertyBlock(Bar3D *bar) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dbaraspectratioitem_);
  propertybrowser_->addProperty(plot3dbarhorizontalaspectratioitem_);
  propertybrowser_->addProperty(plot3dbarshadowqualityitem_);
  propertybrowser_->addProperty(plot3dbarspacingxitem_);
  propertybrowser_->addProperty(plot3dbarspacingyitem_);
  propertybrowser_->addProperty(plot3dbarspacingrelativeitem_);
  propertybrowser_->addProperty(plot3dbarthicknessitem_);
  propertybrowser_->addProperty(plot3dbarorthoprojectionstatusitem_);
  propertybrowser_->addProperty(plot3dbarpolarstatusitem_);

  doubleManager_->setValue(plot3dbaraspectratioitem_,
                           bar->getGraph()->aspectRatio());
  doubleManager_->setValue(plot3dbarhorizontalaspectratioitem_,
                           bar->getGraph()->horizontalAspectRatio());
  enumManager_->setValue(plot3dbarshadowqualityitem_,
                         static_cast<int>(bar->getGraph()->shadowQuality()));
  doubleManager_->setValue(plot3dbarspacingxitem_,
                           bar->getGraph()->barSpacing().width());
  doubleManager_->setValue(plot3dbarspacingyitem_,
                           bar->getGraph()->barSpacing().height());
  boolManager_->setValue(plot3dbarspacingrelativeitem_,
                         bar->getGraph()->isBarSpacingRelative());
  doubleManager_->setValue(plot3dbarthicknessitem_,
                           bar->getGraph()->barThickness());
  boolManager_->setValue(plot3dbarorthoprojectionstatusitem_,
                         bar->getGraph()->isOrthoProjection());
  boolManager_->setValue(plot3dbarpolarstatusitem_, bar->getGraph()->isPolar());
}

void PlotPropertyEditor::Scatter3DPropertyBlock(Scatter3D *scatter) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dscatteraspectratioitem_);
  propertybrowser_->addProperty(plot3dscatterhorizontalaspectratioitem_);
  propertybrowser_->addProperty(plot3dscattershadowqualityitem_);
  propertybrowser_->addProperty(plot3dscatterorthoprojectionstatusitem_);
  propertybrowser_->addProperty(plot3dscatterpolarstatusitem_);

  doubleManager_->setValue(plot3dscatteraspectratioitem_,
                           scatter->getGraph()->aspectRatio());
  doubleManager_->setValue(plot3dscatterhorizontalaspectratioitem_,
                           scatter->getGraph()->horizontalAspectRatio());
  enumManager_->setValue(
      plot3dscattershadowqualityitem_,
      static_cast<int>(scatter->getGraph()->shadowQuality()));
  boolManager_->setValue(plot3dscatterorthoprojectionstatusitem_,
                         scatter->getGraph()->isOrthoProjection());
  boolManager_->setValue(plot3dscatterpolarstatusitem_,
                         scatter->getGraph()->isPolar());
}

void PlotPropertyEditor::Surface3DSeriesPropertyBlock(DataBlockSurface3D *block) {
  propertybrowser_->clear();

  propertybrowser_->addProperty(plot3dsurfaceseriesvisibleitem_);
  if (block->getdataseries()->isFlatShadingSupported())
    propertybrowser_->addProperty(plot3dsurfaceseriesflatshadingstatusitem_);
  propertybrowser_->addProperty(plot3dsurfaceseriesdrawitem_);
  propertybrowser_->addProperty(plot3dsurfaceseriesmeshsmoothitem_);
  propertybrowser_->addProperty(plot3dsurfaceseriescolorstyleitem_);
  propertybrowser_->addProperty(plot3dsurfaceseriesbasecoloritem_);
  propertybrowser_->addProperty(plot3dsurfaceseriesbasegradiantitem_);
  propertybrowser_->addProperty(plot3dsurfaceserieshighlightcoloritem_);

  boolManager_->setValue(plot3dsurfaceseriesvisibleitem_,
                         block->getdataseries()->isVisible());
  if (block->getdataseries()->isFlatShadingSupported())
    boolManager_->setValue(plot3dsurfaceseriesflatshadingstatusitem_,
                           block->getdataseries()->isFlatShadingEnabled());
  enumManager_->setValue(plot3dsurfaceseriesdrawitem_,
                         block->getdataseries()->drawMode() - 1);
  boolManager_->setValue(plot3dsurfaceseriesmeshsmoothitem_,
                         block->getdataseries()->isMeshSmooth());
  enumManager_->setValue(plot3dsurfaceseriescolorstyleitem_,
                         block->getdataseries()->colorStyle());
  colorManager_->setValue(plot3dsurfaceseriesbasecoloritem_,
                          block->getdataseries()->baseColor());
  enumManager_->setValue(plot3dsurfaceseriesbasegradiantitem_,
                         static_cast<int>(block->getgradient()));
  colorManager_->setValue(plot3dsurfaceserieshighlightcoloritem_,
                          block->getdataseries()->singleHighlightColor());
}

void PlotPropertyEditor::Bar3DSeriesPropertyBlock(DataBlockBar3D *block) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(plot3dbarseriesvisibleitem_);
  // propertybrowser_->addProperty(plot3dbarseriesmeshitem_);
  propertybrowser_->addProperty(plot3dbarseriesmeshsmoothitem_);
  propertybrowser_->addProperty(plot3dbarseriescolorstyleitem_);
  propertybrowser_->addProperty(plot3dbarseriesbasecoloritem_);
  propertybrowser_->addProperty(plot3dbarseriesbasegradiantitem_);
  propertybrowser_->addProperty(plot3dbarserieshighlightcoloritem_);

  boolManager_->setValue(plot3dbarseriesvisibleitem_,
                         block->getdataseries()->isVisible());
  // enumManager_->setValue(plot3dbarseriesmeshitem_,
  //                       block->getdataseries()->mesh());
  boolManager_->setValue(plot3dbarseriesmeshsmoothitem_,
                         block->getdataseries()->isMeshSmooth());
  enumManager_->setValue(plot3dbarseriescolorstyleitem_,
                         block->getdataseries()->colorStyle());
  colorManager_->setValue(plot3dbarseriesbasecoloritem_,
                          block->getdataseries()->baseColor());
  enumManager_->setValue(plot3dbarseriesbasegradiantitem_,
                         static_cast<int>(block->getgradient()));
  colorManager_->setValue(plot3dbarserieshighlightcoloritem_,
                          block->getdataseries()->singleHighlightColor());
}

void PlotPropertyEditor::Scatter3DSeriesPropertyBlock(DataBlockScatter3D *block) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(plot3dscatterseriesvisibleitem_);
  propertybrowser_->addProperty(plot3dscatterseriessizeitem_);
  // propertybrowser_->addProperty(plot3dscatterseriesmeshitem_);
  propertybrowser_->addProperty(plot3dscatterseriesmeshsmoothitem_);
  propertybrowser_->addProperty(plot3dscatterseriescolorstyleitem_);
  propertybrowser_->addProperty(plot3dscatterseriesbasecoloritem_);
  propertybrowser_->addProperty(plot3dscatterseriesbasegradiantitem_);
  propertybrowser_->addProperty(plot3dscatterserieshighlightcoloritem_);

  boolManager_->setValue(plot3dscatterseriesvisibleitem_,
                         block->getdataseries()->isVisible());
  doubleManager_->setValue(plot3dscatterseriessizeitem_,
                           block->getdataseries()->itemSize());
  // enumManager_->setValue(plot3dscatterseriesmeshitem_,
  //                       block->getdataseries()->mesh() + 1);
  boolManager_->setValue(plot3dscatterseriesmeshsmoothitem_,
                         block->getdataseries()->isMeshSmooth());
  enumManager_->setValue(plot3dscatterseriescolorstyleitem_,
                         block->getdataseries()->colorStyle());
  colorManager_->setValue(plot3dscatterseriesbasecoloritem_,
                          block->getdataseries()->baseColor());
  enumManager_->setValue(plot3dscatterseriesbasegradiantitem_,
                         static_cast<int>(block->getgradient()));
  colorManager_->setValue(plot3dscatterserieshighlightcoloritem_,
                          block->getdataseries()->singleHighlightColor());
}

void PlotPropertyEditor::TablePropertyBlock(Table *table) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(tablewindowrowcountitem_);
  propertybrowser_->addProperty(tablewindowcolcountitem_);

  intManager_->setValue(tablewindowrowcountitem_, table->numRows());
  intManager_->setValue(tablewindowcolcountitem_, table->numCols());
}

void PlotPropertyEditor::MatrixPropertyBlock(Matrix *matrix) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(matrixwindowrowcountitem_);
  propertybrowser_->addProperty(matrixwindowcolcountitem_);

  intManager_->setValue(matrixwindowrowcountitem_, matrix->numRows());
  intManager_->setValue(matrixwindowcolcountitem_, matrix->numCols());
}

void PlotPropertyEditor::axisRectCreated(AxisRect2D *axisrect, MyWidget *widget) {
  populateObjectBrowser(widget);
  axisrectConnections(axisrect);
}

void PlotPropertyEditor::objectschanged() {
  MyWidget *mywidget = app_->getactiveMyWidget();
  populateObjectBrowser(mywidget);
}

void PlotPropertyEditor::WindowPropertyBlock(MyWidget *widget) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(mywidgetwindownameitem_);
  propertybrowser_->addProperty(mywidgetwindowlabelitem_);
  propertybrowser_->addProperty(mywidgetwindowrectitem_);

  stringManager_->setValue(mywidgetwindownameitem_, widget->name());
  stringManager_->setValue(mywidgetwindowlabelitem_, widget->windowLabel());
  rectManager_->setValue(mywidgetwindowrectitem_, widget->geometry());
}

void PlotPropertyEditor::Plot2DPropertyBlock(Layout2D *layout2d,
                                         Plot2D *plotcanvas) {
  propertybrowser_->clear();
  propertybrowser_->addProperty(canvaspropertysizeitem_);
  propertybrowser_->addProperty(canvaspropertycoloritem_);
  propertybrowser_->addProperty(canvaspropertybufferdevicepixelratioitem_);
  propertybrowser_->addProperty(canvaspropertyopenglitem_);
  propertybrowser_->addProperty(canvaspropertyrowsapcingitem_);
  propertybrowser_->addProperty(canvaspropertycolumnsapcingitem_);
  colorManager_->setValue(canvaspropertycoloritem_,
                          plotcanvas->getBackgroundColor());
  doubleManager_->setValue(canvaspropertybufferdevicepixelratioitem_,
                           plotcanvas->bufferDevicePixelRatio());
  boolManager_->setValue(canvaspropertyopenglitem_, plotcanvas->openGl());
  sizeManager_->setValue(canvaspropertysizeitem_,
                         QSize(plotcanvas->width(), plotcanvas->height()));
  intManager_->setValue(canvaspropertyrowsapcingitem_,
                        layout2d->getLayoutGrid()->rowSpacing());
  intManager_->setValue(canvaspropertycolumnsapcingitem_,
                        layout2d->getLayoutGrid()->columnSpacing());
}

void PlotPropertyEditor::populateObjectBrowser(MyWidget *widget) {
  // delete all TreeWidgetItems
  objectbrowser_->blockSignals(true);
  while (objectbrowser_->topLevelItemCount()) {
    QTreeWidgetItemIterator itr(objectbrowser_,
                                QTreeWidgetItemIterator::NoChildren);
    while (*itr) {
      delete (*itr);
      ++itr;
    }
  }
  objectbrowser_->clear();
  objectitems_.clear();
  propertybrowser_->clear();
  objectbrowser_->blockSignals(false);

  if (!widget) {
    objectbrowser_->setHeaderLabel(QString::fromLatin1("(none)"));
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("clear-loginfo"), IconLoader::General));
    return;
  }

  QString tooltiptextx = QString::fromLatin1(
      "<tr> <td align=\"right\">Table :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Column :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%5</td></tr>");
  QString tooltiptextxy = QString::fromLatin1(
      "<tr> <td align=\"right\">Table :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Column X :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Column Y :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%5</td></tr>");
  QString tooltiptextfuncxy = QString::fromLatin1(
      "<tr> <td align=\"right\">Type :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Function :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">Points :</td><td>%5</td></tr>");
  QString tooltiptextfuncparam = QString::fromLatin1(
      "<tr> <td align=\"right\">Type :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Function X :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Function Y :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">Parameter :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%5</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%6</td></tr>"
      "<tr> <td align=\"right\">Points :</td><td>%7</td></tr>");
  QString tooltiptextfuncpolar = QString::fromLatin1(
      "<tr> <td align=\"right\">Type :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Function R :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Function Theta :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">Parameter :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%5</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%6</td></tr>"
      "<tr> <td align=\"right\">Points :</td><td>%7</td></tr>");
  QString tooltiptextxyyy = QString::fromLatin1(
      "<tr> <td align=\"right\">Table :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Column :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Column :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">Column :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">Column :</td><td>%5</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%6</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%7</td></tr>");
  QString tooltiptextxyy = QString::fromLatin1(
      "<tr> <td align=\"right\">Table :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Column X :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Column Y1 :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">Column Y2 :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">From :</td><td>%6</td></tr>"
      "<tr> <td align=\"right\">To :</td><td>%7</td></tr>");
  QString tooltiptextmatrix = QString::fromLatin1(
      "<tr> <td align=\"right\">Matrix :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">Rows :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">Columns :</td><td>%4</td></tr>");
  QString tooltiptextfuncsurface = QString::fromLatin1(
      "<tr> <td align=\"right\">Function :</td><td>%1</td></tr>"
      "<tr> <td align=\"right\">xl :</td><td>%2</td></tr>"
      "<tr> <td align=\"right\">xu :</td><td>%3</td></tr>"
      "<tr> <td align=\"right\">yl :</td><td>%4</td></tr>"
      "<tr> <td align=\"right\">yu :</td><td>%5</td></tr>"
      "<tr> <td align=\"right\">zl :</td><td>%6</td></tr>"
      "<tr> <td align=\"right\">zu :</td><td>%7</td></tr>"
      "<tr> <td align=\"right\">Points :</td><td>%8</td></tr>");

  // window
  {
    QString windowitemtext = QString::fromLatin1("Window");
    QTreeWidgetItem *windowitem = new QTreeWidgetItem(
        static_cast<QTreeWidget *>(nullptr), QStringList(windowitemtext));
    windowitem->setToolTip(0, windowitemtext);
    windowitem->setIcon(
        0, IconLoader::load(QString::fromLatin1("edit-table-dimension"), IconLoader::LightDark));
    windowitem->setData(
        0, Qt::UserRole,
        static_cast<int>(MyPlotTreeWidget::PropertyItemType::MyWidgetWindow));
    windowitem->setData(0, Qt::UserRole + 1,
                        QVariant::fromValue<void *>(widget));
    objectitems_.append(windowitem);
  }

  if (qobject_cast<Layout2D *>(widget)) {
    Layout2D *gd = qobject_cast<Layout2D *>(widget);
    objectbrowser_->setHeaderLabel(qobject_cast<Layout2D *>(widget)->name());
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("edit-graph"), IconLoader::LightDark));
    QList<AxisRect2D *> elementslist = gd->getAxisRectList();

    // canvas
    QString canvasitemtext = QString::fromLatin1("Canvas");
    QTreeWidgetItem *canvasitem = new QTreeWidgetItem(
        static_cast<QTreeWidget *>(nullptr), QStringList(canvasitemtext));
    canvasitem->setToolTip(0, canvasitemtext);
    canvasitem->setIcon(0,
                        IconLoader::load(QString::fromLatin1("view-image"), IconLoader::LightDark));
    canvasitem->setData(
        0, Qt::UserRole,
        static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DCanvas));
    canvasitem->setData(0, Qt::UserRole + 1,
                        QVariant::fromValue<void *>(gd->getPlotCanwas()));
    canvasitem->setData(0, Qt::UserRole + 2, QVariant::fromValue<void *>(gd));
    objectitems_.append(canvasitem);

    // Layout items
    for (int i = 0; i < elementslist.size(); ++i) {
      AxisRect2D *element = elementslist.at(i);
      QPair<int, int> rowcol = gd->getAxisRectRowCol(element);
      QString itemtext = QString::fromLatin1("Layout: %1 (%2x%3)")
                             .arg(i + 1)
                             .arg(rowcol.first + 1)
                             .arg(rowcol.second + 1);
      QTreeWidgetItem *item = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(itemtext));
      item->setToolTip(0, itemtext);
      item->setIcon(0,
                    IconLoader::load(QString::fromLatin1("graph2d-layout"), IconLoader::LightDark));
      item->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DLayout));
      item->setData(0, Qt::UserRole + 1, QVariant::fromValue<void *>(element));
      item->setData(0, Qt::UserRole + 2, QVariant::fromValue<void *>(gd));

      // Legend
      QString legendtext = tr("Legend");
      QTreeWidgetItem *legenditem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(legendtext));
      legenditem->setToolTip(0, legendtext);
      legenditem->setIcon(
          0, IconLoader::load(QString::fromLatin1("edit-legend"), IconLoader::LightDark));
      legenditem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DLegend));
      Legend2D *legend = element->getLegend();
      legenditem->setData(0, Qt::UserRole + 1,
                          QVariant::fromValue<void *>(legend));
      item->addChild(legenditem);

      // Axis items
      QList<Axis2D *> xaxes = element->getXAxes2D();
      QList<Axis2D *> yaxes = element->getYAxes2D();

      for (int j = 0; j < xaxes.size(); j++) {
        Axis2D *axis = xaxes.at(j);
        QString axistext;
        QTreeWidgetItem *axisitem =
            new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));

        switch (axis->getorientation_axis()) {
          case Axis2D::AxisOreantation::Bottom:
            axistext = QString(axis->getname_axis() +
                               QString::number(axis->getnumber_axis()));
            break;
          case Axis2D::AxisOreantation::Top:
            axistext = QString(axis->getname_axis() +
                               QString::number(axis->getnumber_axis()));
            break;
          case Axis2D::AxisOreantation::Left:
          case Axis2D::AxisOreantation::Right:
            qDebug() << QString::fromLatin1("no left & right oriented X axis");
            break;
        }
        axisitem->setIcon(0, axis->geticon_axis());
        axisitem->setText(0, axistext);
        axisitem->setToolTip(0, axistext);
        axisitem->setData(
            0, Qt::UserRole,
            static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DAxis));
        axisitem->setData(0, Qt::UserRole + 1,
                          QVariant::fromValue<void *>(axis));
        item->addChild(axisitem);
      }

      for (int j = 0; j < yaxes.size(); j++) {
        Axis2D *axis = yaxes.at(j);
        QString axistext;
        QTreeWidgetItem *axisitem =
            new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));

        switch (axis->getorientation_axis()) {
          case Axis2D::AxisOreantation::Left:
            axistext = QString(axis->getname_axis() +
                               QString::number(axis->getnumber_axis()));
            break;
          case Axis2D::AxisOreantation::Right:
            axistext = QString(axis->getname_axis() +
                               QString::number(axis->getnumber_axis()));
            break;
          case Axis2D::AxisOreantation::Top:
          case Axis2D::AxisOreantation::Bottom:
            qDebug() << QString::fromLatin1("no top & bottom oriented Y axis");
            break;
        }
        axisitem->setIcon(0, axis->geticon_axis());
        axisitem->setText(0, axistext);
        axisitem->setToolTip(0, axistext);
        axisitem->setData(
            0, Qt::UserRole,
            static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DAxis));
        axisitem->setData(0, Qt::UserRole + 1,
                          QVariant::fromValue<void *>(axis));
        item->addChild(axisitem);
      }

      // plottables & items vector of element
      auto textitems = element->getTextItemVec();
      auto lineitems = element->getLineItemVec();
      auto imageitems = element->getImageItemVec();
      auto graphvec = element->getLsVec();
      auto curvevec = element->getCurveVec();
      auto statboxvec = element->getStatBoxVec();
      auto vectorvec = element->getVectorVec();
      auto channelvec = element->getChannelVec();
      auto barvec = element->getBarVec();
      auto pievec = element->getPieVec();
      auto colormapvec = element->getColorMapVec();
      auto layervec = element->getLayerVec();
      // reverse layer list order
      for (int k = 0, s = layervec.size(), max = (s / 2); k < max; k++)
#if (QT_VERSION >= QT_VERSION_CHECK(5, 13, 0))
        layervec.swapItemsAt(k, s - (1 + k));
#else
        layervec.swap(k, s - (1 + k));
#endif

      Q_FOREACH(QCPLayer *layer, layervec) {
        bool layerfound = false;
        // Text items
        for (int j = 0; j < textitems.size(); j++) {
          if (layer == textitems.at(j)->layer()) {
            QTreeWidgetItem *textitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            QString text = QString(QString::fromLatin1("Text Item: ") + QString::number(j + 1));
            textitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("draw-text"), IconLoader::LightDark));
            textitem->setText(0, text);
            textitem->setToolTip(0, text);
            textitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DTextItem));
            textitem->setData(0, Qt::UserRole + 1,
                              QVariant::fromValue<void *>(textitems.at(j)));
            item->addChild(textitem);
            textitems.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Line items
        for (int j = 0; j < lineitems.size(); j++) {
          if (layer == lineitems.at(j)->layer()) {
            QTreeWidgetItem *lineitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            QString text = QString(QString::fromLatin1("Line Item: ") + QString::number(j + 1));
            lineitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("draw-line"), IconLoader::LightDark));
            lineitem->setText(0, text);
            lineitem->setToolTip(0, text);
            lineitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DLineItem));
            lineitem->setData(0, Qt::UserRole + 1,
                              QVariant::fromValue<void *>(lineitems.at(j)));
            item->addChild(lineitem);
            lineitems.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Image items
        for (int j = 0; j < imageitems.size(); j++) {
          if (layer == imageitems.at(j)->layer()) {
            QTreeWidgetItem *imageitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            QString text = QString(QString::fromLatin1("Image Item: ") + QString::number(j + 1));
            imageitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("view-image"), IconLoader::LightDark));
            imageitem->setText(0, text);
            imageitem->setToolTip(0, text);
            imageitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DImageItem));
            imageitem->setData(0, Qt::UserRole + 1,
                               QVariant::fromValue<void *>(imageitems.at(j)));
            item->addChild(imageitem);
            imageitems.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // LineSpecial plot Items
        for (int j = 0; j < graphvec.size(); j++) {
          if (layer == graphvec.at(j)->layer()) {
            LineSpecial2D *lsgraph = graphvec.at(j);
            DataBlockGraph *data = lsgraph->getdatablock_lsplot();
            QString lsgraphtext = data->gettable()->name() + QString::fromLatin1("_") +
                                  data->getxcolumn()->name() + QString::fromLatin1("_") +
                                  data->getycolumn()->name() + QString::fromLatin1("[") +
                                  QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                  QString::number(data->getto() + 1) + QString::fromLatin1("]");
            QTreeWidgetItem *lsgraphitem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(lsgraphtext));
            QString tooltiptext = tooltiptextxy.arg(data->gettable()->name())
                                      .arg(data->getxcolumn()->name())
                                      .arg(data->getycolumn()->name())
                                      .arg(QString::number(data->getfrom() + 1))
                                      .arg(QString::number(data->getto() + 1));
            lsgraphitem->setToolTip(0, tooltiptext);
            lsgraphitem->setIcon(0, lsgraph->getIcon());
            lsgraphitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DLSGraph));
            lsgraphitem->setData(0, Qt::UserRole + 1,
                                 QVariant::fromValue<void *>(lsgraph));
            lsgraphitem->setData(0, Qt::UserRole + 2,
                                 QVariant::fromValue<void *>(element));
            item->addChild(lsgraphitem);
            // x error
            ErrorBar2D *xerror = lsgraph->getxerrorbar_lsplot();
            if (xerror) {
              DataBlockError *data = xerror->getdatablock_error();
              QString xerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *xerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(xerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              xerroritem->setToolTip(0, tooltiperror);
              xerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-x-error"), IconLoader::LightDark));
              xerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              xerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(xerror));
              lsgraphitem->addChild(xerroritem);
            }
            // y error
            ErrorBar2D *yerror = lsgraph->getyerrorbar_lsplot();
            if (yerror) {
              DataBlockError *data = yerror->getdatablock_error();
              QString yerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *yerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(yerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              yerroritem->setToolTip(0, tooltiperror);
              yerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-y-error"), IconLoader::LightDark));
              yerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              yerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(yerror));
              lsgraphitem->addChild(yerroritem);
            }
            graphvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Curve plot Items
        int function = 1;
        for (int j = 0; j < curvevec.size(); j++) {
          if (layer == curvevec.at(j)->layer()) {
            Curve2D *curvegraph = curvevec.at(j);
            QString curvegraphtext = QString::fromLatin1("curve");
            QTreeWidgetItem *curvegraphitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr),
                                    QStringList(curvegraphtext));
            curvegraphitem->setIcon(0, curvegraph->getIcon());
            switch (curvegraph->getplottype_cplot()) {
              case Graph2DCommon::PlotType::Associated: {
                DataBlockCurve *data = curvegraph->getdatablock_cplot();
                curvegraphtext = data->gettable()->name() + QString::fromLatin1("_") +
                                 data->getxcolumn()->name() + QString::fromLatin1("_") +
                                 data->getycolumn()->name() + QString::fromLatin1("[") +
                                 QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                 QString::number(data->getto() + 1) + QString::fromLatin1("]");
                curvegraphitem->setText(0, curvegraphtext);
                QString tooltiptext =
                    tooltiptextxy.arg(data->gettable()->name())
                        .arg(data->getxcolumn()->name())
                        .arg(data->getycolumn()->name())
                        .arg(QString::number(data->getfrom() + 1))
                        .arg(QString::number(data->getto() + 1));
                curvegraphitem->setToolTip(0, tooltiptext);
              } break;
              case Graph2DCommon::PlotType::Function: {
                curvegraphtext = QString(QString::fromLatin1("Function %1").arg(function++));
                curvegraphitem->setText(0, curvegraphtext);
                PlotData::FunctionData funcdata =
                    curvegraph->getfuncdata_cplot();
                switch (funcdata.type) {
                  case 0: {
                    QString functype, func;
                    if (funcdata.functions.size() == 1) {
                      functype = QString(tr("Normal XY"));
                      func = funcdata.functions.at(0);
                    } else {
                      functype = QString(tr("Unknown"));
                      func = QString(tr("unknown"));
                    }
                    curvegraphitem->setToolTip(0, QString(tooltiptextfuncxy)
                                                      .arg(functype)
                                                      .arg(func)
                                                      .arg(funcdata.from)
                                                      .arg(funcdata.to)
                                                      .arg(funcdata.points));
                  } break;
                  case 1: {
                    QString functype, func1, func2;
                    if (funcdata.functions.size() == 2) {
                      functype = QString(tr("Parametric"));
                      func1 = funcdata.functions.at(0);
                      func2 = funcdata.functions.at(1);
                    } else {
                      functype = QString(tr("Unknown"));
                      func1 = QString(tr("unknown"));
                      func2 = QString(tr("unknown"));
                    }
                    curvegraphitem->setToolTip(0, QString(tooltiptextfuncparam)
                                                      .arg(functype)
                                                      .arg(func1)
                                                      .arg(func2)
                                                      .arg(funcdata.parameter)
                                                      .arg(funcdata.from)
                                                      .arg(funcdata.to)
                                                      .arg(funcdata.points));
                  } break;
                  case 2: {
                    QString functype, func1, func2;
                    if (funcdata.functions.size() == 2) {
                      functype = QString(tr("Polar"));
                      func1 = funcdata.functions.at(0);
                      func2 = funcdata.functions.at(1);
                    } else {
                      functype = QString(tr("Unknown"));
                      func1 = QString(tr("unknown"));
                      func2 = QString(tr("unknown"));
                    }
                    curvegraphitem->setToolTip(0, QString(tooltiptextfuncpolar)
                                                      .arg(functype)
                                                      .arg(func1)
                                                      .arg(func2)
                                                      .arg(funcdata.parameter)
                                                      .arg(funcdata.from)
                                                      .arg(funcdata.to)
                                                      .arg(funcdata.points));
                  } break;
                }
              } break;
            }
            curvegraphitem->setData(
                0, Qt::UserRole,
                static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DCurve));
            curvegraphitem->setData(0, Qt::UserRole + 1,
                                    QVariant::fromValue<void *>(curvegraph));
            curvegraphitem->setData(0, Qt::UserRole + 2,
                                    QVariant::fromValue<void *>(element));
            item->addChild(curvegraphitem);
            // x error
            ErrorBar2D *xerror = curvegraph->getxerrorbar_curveplot();
            if (xerror) {
              DataBlockError *data = xerror->getdatablock_error();
              QString xerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *xerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(xerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              xerroritem->setToolTip(0, tooltiperror);
              xerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-x-error"), IconLoader::LightDark));
              xerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              xerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(xerror));
              curvegraphitem->addChild(xerroritem);
            }
            // y error
            ErrorBar2D *yerror = curvegraph->getyerrorbar_curveplot();
            if (yerror) {
              DataBlockError *data = yerror->getdatablock_error();
              QString yerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *yerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(yerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              yerroritem->setToolTip(0, tooltiperror);
              yerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-y-error"), IconLoader::LightDark));
              yerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              yerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(yerror));
              curvegraphitem->addChild(yerroritem);
            }
            curvevec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Statbox plot Items
        for (int j = 0; j < statboxvec.size(); j++) {
          if (layer == statboxvec.at(j)->layer()) {
            StatBox2D *statbox = statboxvec.at(j);
            QString statboxtext =
                statbox->gettable_statbox()->name() + QString::fromLatin1("_") +
                statbox->getcolumn_statbox()->name() + QString::fromLatin1("[") +
                QString::number(statbox->getfrom_statbox() + 1) + QString::fromLatin1(":") +
                QString::number(statbox->getto_statbox() + 1) + QString::fromLatin1("]");
            QTreeWidgetItem *statboxitem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(statboxtext));
            QString tooltip =
                tooltiptextx.arg(statbox->gettable_statbox()->name())
                    .arg(statbox->getcolumn_statbox()->name())
                    .arg(QString::number(statbox->getfrom_statbox() + 1))
                    .arg(QString::number(statbox->getto_statbox() + 1));
            statboxitem->setToolTip(0, tooltip);
            statboxitem->setIcon(0, statbox->getIcon());
            statboxitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DStatBox));
            statboxitem->setData(0, Qt::UserRole + 1,
                                 QVariant::fromValue<void *>(statbox));
            statboxitem->setData(0, Qt::UserRole + 2,
                                 QVariant::fromValue<void *>(element));
            item->addChild(statboxitem);
            statboxvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Vector plot Items
        for (int j = 0; j < vectorvec.size(); j++) {
          if (layer == vectorvec.at(j)->layer()) {
            Vector2D *vector = vectorvec.at(j);
            QString vectortext =
                vector->gettable_vecplot()->name() + QString::fromLatin1("_") +
                vector->getfirstcol_vecplot()->name() + QString::fromLatin1("_") +
                vector->getsecondcol_vecplot()->name() + QString::fromLatin1("_") +
                vector->getthirdcol_vecplot()->name() + QString::fromLatin1("_") +
                vector->getfourthcol_vecplot()->name() + QString::fromLatin1("[") +
                QString::number(vector->getfrom_vecplot() + 1) + QString::fromLatin1(":") +
                QString::number(vector->getto_vecplot() + 1) + QString::fromLatin1("]");
            QTreeWidgetItem *vectoritem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(vectortext));
            QString tooltiptext =
                tooltiptextxyyy.arg(vector->gettable_vecplot()->name())
                    .arg(vector->getfirstcol_vecplot()->name())
                    .arg(vector->getsecondcol_vecplot()->name())
                    .arg(vector->getthirdcol_vecplot()->name())
                    .arg(vector->getfourthcol_vecplot()->name())
                    .arg(QString::number(vector->getfrom_vecplot() + 1))
                    .arg(QString::number(vector->getto_vecplot() + 1));
            vectoritem->setToolTip(0, tooltiptext);
            vectoritem->setIcon(0, vector->getIcon());
            vectoritem->setData(
                0, Qt::UserRole,
                static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DVector));
            vectoritem->setData(0, Qt::UserRole + 1,
                                QVariant::fromValue<void *>(vector));
            vectoritem->setData(0, Qt::UserRole + 2,
                                QVariant::fromValue<void *>(element));
            item->addChild(vectoritem);
            vectorvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // LineSpecialchannel plot Items
        for (int j = 0; j < channelvec.size(); j++) {
          if (layer == channelvec.at(j).first->layer()) {
            LineSpecial2D *lsgraph1 = channelvec.at(j).first;
            LineSpecial2D *lsgraph2 = channelvec.at(j).second;
            DataBlockGraph *data1 = lsgraph1->getdatablock_lsplot();
            DataBlockGraph *data2 = lsgraph2->getdatablock_lsplot();
            QString lsgraph1text = data1->gettable()->name() + QString::fromLatin1("_") +
                                   data1->getxcolumn()->name() + QString::fromLatin1("_") +
                                   data1->getycolumn()->name() + QString::fromLatin1("_") +
                                   data2->getycolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data1->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data1->getto() + 1) + QString::fromLatin1("]");
            QTreeWidgetItem *channelitem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(lsgraph1text));
            QString tooltiptext =
                tooltiptextxyy.arg(data1->gettable()->name())
                    .arg(data1->getxcolumn()->name())
                    .arg(data1->getycolumn()->name())
                    .arg(data2->getycolumn()->name())
                    .arg(QString::number(data1->getfrom() + 1))
                    .arg(QString::number(data1->getto() + 1));
            channelitem->setToolTip(0, tooltiptext);
            channelitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("graph2d-channel"), IconLoader::LightDark));
            channelitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DChannelGraph));
            channelitem->setData(0, Qt::UserRole + 1,
                                 QVariant::fromValue<void *>(lsgraph1));
            channelitem->setData(0, Qt::UserRole + 2,
                                 QVariant::fromValue<void *>(element));
            channelitem->setData(0, Qt::UserRole + 3,
                                 QVariant::fromValue<void *>(lsgraph2));
            item->addChild(channelitem);
            channelvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Bar Plot items
        for (int j = 0; j < barvec.size(); j++) {
          if (layer == barvec.at(j)->layer()) {
            Bar2D *bar = barvec.at(j);
            QString bartext = QString::fromLatin1("Histogram");
            QTreeWidgetItem *baritem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(bartext));
            baritem->setIcon(0, bar->getIcon());
            if (bar->ishistogram_barplot()) {
              bartext =
                  bar->getdatablock_histplot()->gettable()->name() + QString::fromLatin1("_") +
                  bar->getdatablock_histplot()->getcolumn()->name() + QString::fromLatin1("[") +
                  QString::number(bar->getdatablock_histplot()->getfrom() + 1) +
                  QString::fromLatin1(":") +
                  QString::number(bar->getdatablock_histplot()->getto() + 1) +
                  QString::fromLatin1("]");
              QString tooltiptext =
                  tooltiptextx
                      .arg(bar->getdatablock_histplot()->gettable()->name())
                      .arg(bar->getdatablock_histplot()->getcolumn()->name())
                      .arg(QString::number(
                          bar->getdatablock_histplot()->getfrom() + 1))
                      .arg(QString::number(
                          bar->getdatablock_histplot()->getto() + 1));
              baritem->setToolTip(0, tooltiptext);
              baritem->setText(0, bartext);
            } else {
              DataBlockBar *data = bar->getdatablock_barplot();
              bartext = data->gettable()->name() + QString::fromLatin1("_") +
                        data->getxcolumn()->name() + QString::fromLatin1("_") +
                        data->getycolumn()->name() + QString::fromLatin1("[") +
                        QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                        QString::number(data->getto() + 1) + QString::fromLatin1("]");
              baritem->setText(0, bartext);

              QString tooltiptext =
                  tooltiptextxy.arg(data->gettable()->name())
                      .arg(data->getxcolumn()->name())
                      .arg(data->getycolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              baritem->setToolTip(0, tooltiptext);
            }
            baritem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DBarGraph));
            baritem->setData(0, Qt::UserRole + 1,
                             QVariant::fromValue<void *>(bar));
            baritem->setData(0, Qt::UserRole + 2,
                             QVariant::fromValue<void *>(element));
            item->addChild(baritem);
            // x error
            ErrorBar2D *xerror = bar->getxerrorbar_barplot();
            if (xerror) {
              DataBlockError *data = xerror->getdatablock_error();
              QString xerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *xerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(xerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              xerroritem->setToolTip(0, tooltiperror);
              xerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-x-error"), IconLoader::LightDark));
              xerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              xerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(xerror));
              baritem->addChild(xerroritem);
            }
            // y error
            ErrorBar2D *yerror = bar->getyerrorbar_barplot();
            if (yerror) {
              DataBlockError *data = yerror->getdatablock_error();
              QString yerrortext = data->gettable()->name() + QString::fromLatin1("_") +
                                   data->geterrorcolumn()->name() + QString::fromLatin1("[") +
                                   QString::number(data->getfrom() + 1) + QString::fromLatin1(":") +
                                   QString::number(data->getto() + 1) + QString::fromLatin1("]");
              QTreeWidgetItem *yerroritem = new QTreeWidgetItem(
                  static_cast<QTreeWidget *>(nullptr), QStringList(yerrortext));
              QString tooltiperror =
                  tooltiptextx.arg(data->gettable()->name())
                      .arg(data->geterrorcolumn()->name())
                      .arg(QString::number(data->getfrom() + 1))
                      .arg(QString::number(data->getto() + 1));
              yerroritem->setToolTip(0, tooltiperror);
              yerroritem->setIcon(
                  0, IconLoader::load(QString::fromLatin1("graph-y-error"), IconLoader::LightDark));
              yerroritem->setData(
                  0, Qt::UserRole,
                  static_cast<int>(
                      MyPlotTreeWidget::PropertyItemType::Plot2DErrorBar));
              yerroritem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(yerror));
              baritem->addChild(yerroritem);
            }
            barvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // Pie Plot Items
        for (int j = 0; j < pievec.size(); j++) {
          if (layer == pievec.at(j)->layer()) {
            Pie2D *pie = pievec.at(j);
            QString pietext = pie->gettable_pieplot()->name() + QString::fromLatin1("_") +
                              pie->getxcolumn_pieplot()->name() + QString::fromLatin1("[") +
                              QString::number(pie->getfrom_pieplot() + 1) +
                              QString::fromLatin1(":") + QString::number(pie->getto_pieplot() + 1) +
                              QString::fromLatin1("]");
            QTreeWidgetItem *pieitem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(pietext));
            QString tooltip =
                tooltiptextx.arg(pie->gettable_pieplot()->name())
                    .arg(pie->getxcolumn_pieplot()->name())
                    .arg(QString::number(pie->getfrom_pieplot() + 1))
                    .arg(QString::number(pie->getto_pieplot() + 1));
            pieitem->setToolTip(0, tooltip);
            pieitem->setIcon(0, pie->getIcon());
            pieitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DPieGraph));
            pieitem->setData(0, Qt::UserRole + 1,
                             QVariant::fromValue<void *>(pie));
            pieitem->setData(0, Qt::UserRole + 2,
                             QVariant::fromValue<void *>(element));
            item->addChild(pieitem);
            pievec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;

        // ColorMap Plot Items
        for (int j = 0; j < colormapvec.size(); j++) {
          if (layer == colormapvec.at(j)->layer()) {
            ColorMap2D *colormap = colormapvec.at(j);

            QString colormaptext =
                colormap->getmatrix_colormap()->name() + QString::fromLatin1("[") +
                QString::number(colormap->getrows_colormap()) + QString::fromLatin1("x") +
                QString::number(colormap->getcolumns_colormap()) + QString::fromLatin1("]");
            QTreeWidgetItem *colormapitem = new QTreeWidgetItem(
                static_cast<QTreeWidget *>(nullptr), QStringList(colormaptext));
            QString tooltip =
                tooltiptextmatrix.arg(colormap->getmatrix_colormap()->name())
                    .arg(QString::number(colormap->getrows_colormap()))
                    .arg(QString::number(colormap->getcolumns_colormap()));
            colormapitem->setToolTip(0, tooltip);
            colormapitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("edit-colormap3d"), IconLoader::General));
            colormapitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot2DColorMap));
            colormapitem->setData(0, Qt::UserRole + 1,
                                  QVariant::fromValue<void *>(colormap));
            colormapitem->setData(0, Qt::UserRole + 2,
                                  QVariant::fromValue<void *>(element));
            item->addChild(colormapitem);
            colormapvec.removeAt(j);
            layerfound = true;
            break;
          }
        }
        if (layerfound) continue;
      }

      // Grids
      QString gridtext = QString::fromLatin1("Axis Grids");
      QTreeWidgetItem *griditem =
          new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr),
                              QStringList(QString::fromLatin1("Axis Grids")));
      griditem->setToolTip(0, gridtext);
      griditem->setIcon(
          0, IconLoader::load(QString::fromLatin1("graph3d-cross"), IconLoader::LightDark));
      griditem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot2DGrid));
      griditem->setData(0, Qt::UserRole + 1,
                        QVariant::fromValue<void *>(element));
      item->addChild(griditem);

      objectitems_.append(item);
    }
    if (previouswidget_ != gd)
      connect(gd, SIGNAL(AxisRectCreated(AxisRect2D *, MyWidget *)), this,
              SLOT(axisRectCreated(AxisRect2D *, MyWidget *)));
    previouswidget_ = gd;
  } else if (qobject_cast<Layout3D *>(widget)) {
    objectbrowser_->setHeaderLabel(qobject_cast<Layout3D *>(widget)->name());
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("edit-graph3d"), IconLoader::LightDark));

    Layout3D *lout = qobject_cast<Layout3D *>(widget);
    const Graph3DCommon::Plot3DType plottype = lout->getPlotType();
    QVariant plot3dptvar;
    // plot axis type
    QString axisxitemtext;
    QString axisyitemtext;
    QVariant axis3dxptvar;
    QVariant axis3dyptvar;
    QVariant axis3dzptvar;
    MyPlotTreeWidget::PropertyItemType propertyitemtype;
    switch (plottype) {
      case Graph3DCommon::Plot3DType::Surface: {
        plot3dptvar = QVariant::fromValue<void *>(lout->getSurface3DModifier());
        axisxitemtext = QString::fromLatin1("X Axis(val)");
        axisyitemtext = QString::fromLatin1("Y Axis(val)");
        propertyitemtype = MyPlotTreeWidget::PropertyItemType::Plot3DAxisValue;
        axis3dxptvar = QVariant::fromValue<void *>(
            lout->getSurface3DModifier()->getGraph()->axisX());
        axis3dyptvar = QVariant::fromValue<void *>(
            lout->getSurface3DModifier()->getGraph()->axisY());
        axis3dzptvar = QVariant::fromValue<void *>(
            lout->getSurface3DModifier()->getGraph()->axisZ());
      } break;
      case Graph3DCommon::Plot3DType::Scatter: {
        plot3dptvar = QVariant::fromValue<void *>(lout->getScatter3DModifier());
        axisxitemtext = QString::fromLatin1("X Axis(val)");
        axisyitemtext = QString::fromLatin1("Y Axis(val)");
        propertyitemtype = MyPlotTreeWidget::PropertyItemType::Plot3DAxisValue;
        axis3dxptvar = QVariant::fromValue<void *>(
            lout->getScatter3DModifier()->getGraph()->axisX());
        axis3dyptvar = QVariant::fromValue<void *>(
            lout->getScatter3DModifier()->getGraph()->axisY());
        axis3dzptvar = QVariant::fromValue<void *>(
            lout->getScatter3DModifier()->getGraph()->axisZ());
      } break;
      case Graph3DCommon::Plot3DType::Bar: {
        plot3dptvar = QVariant::fromValue<void *>(lout->getBar3DModifier());
        axisxitemtext = QString::fromLatin1("X Axis(cat)");
        axisyitemtext = QString::fromLatin1("Y Axis(cat)");
        propertyitemtype = MyPlotTreeWidget::PropertyItemType::Plot3DAxisCatagory;
        axis3dxptvar = QVariant::fromValue<void *>(
            lout->getBar3DModifier()->getGraph()->rowAxis());
        axis3dyptvar = QVariant::fromValue<void *>(
            lout->getBar3DModifier()->getGraph()->columnAxis());
        axis3dzptvar = QVariant::fromValue<void *>(
            lout->getBar3DModifier()->getGraph()->valueAxis());
      } break;
    }

    // canvas
    {
      QVariant plot3dptcanvas;
      QString canvasitemtext = QString::fromLatin1("Canvas");
      QTreeWidgetItem *canvasitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(canvasitemtext));
      canvasitem->setToolTip(0, canvasitemtext);
      canvasitem->setIcon(
          0, IconLoader::load(QString::fromLatin1("view-image"), IconLoader::LightDark));
      canvasitem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DCanvas));
      switch (plottype) {
        case Graph3DCommon::Plot3DType::Surface:
          plot3dptcanvas =
              QVariant::fromValue<void *>(static_cast<QAbstract3DGraph *>(
                  lout->getSurface3DModifier()->getGraph()));
          break;
        case Graph3DCommon::Plot3DType::Bar:
          plot3dptcanvas =
              QVariant::fromValue<void *>(static_cast<QAbstract3DGraph *>(
                  lout->getBar3DModifier()->getGraph()));
          break;
        case Graph3DCommon::Plot3DType::Scatter:
          plot3dptcanvas =
              QVariant::fromValue<void *>(static_cast<QAbstract3DGraph *>(
                  lout->getScatter3DModifier()->getGraph()));
          break;
      }
      canvasitem->setData(0, Qt::UserRole + 1, plot3dptcanvas);
      canvasitem->setData(
          0, Qt::UserRole + 2,
          QVariant::fromValue<void *>(static_cast<MyWidget *>(lout)));
      objectitems_.append(canvasitem);
    }

    // theme
    {
      QString themeitemtext = QString::fromLatin1("Theme");
      QTreeWidgetItem *themeitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(themeitemtext));
      themeitem->setToolTip(0, themeitemtext);
      themeitem->setIcon(0, IconLoader::load(QString::fromLatin1("theme"), IconLoader::General));
      themeitem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DTheme));
      QVariant plot3dpttheme;
      switch (plottype) {
        case Graph3DCommon::Plot3DType::Surface:
          plot3dpttheme = QVariant::fromValue<void *>(
              lout->getSurface3DModifier()->getGraph()->activeTheme());
          break;
        case Graph3DCommon::Plot3DType::Bar:
          plot3dpttheme = QVariant::fromValue<void *>(
              lout->getBar3DModifier()->getGraph()->activeTheme());
          break;
        case Graph3DCommon::Plot3DType::Scatter:
          plot3dpttheme = QVariant::fromValue<void *>(
              lout->getScatter3DModifier()->getGraph()->activeTheme());
          break;
      }
      themeitem->setData(0, Qt::UserRole + 1, plot3dpttheme);
      objectitems_.append(themeitem);
    }

    // Axis X
    {
      QTreeWidgetItem *axisxitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(axisxitemtext));
      axisxitem->setToolTip(0, axisxitemtext);
      axisxitem->setIcon(
          0, IconLoader::load(QString::fromLatin1("graph2d-axis-bottom"), IconLoader::LightDark));
      axisxitem->setData(0, Qt::UserRole, static_cast<int>(propertyitemtype));
      axisxitem->setData(0, Qt::UserRole + 1, axis3dxptvar);
      objectitems_.append(axisxitem);
    }

    // Axis Y
    {
      QTreeWidgetItem *axisyitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(axisyitemtext));
      axisyitem->setToolTip(0, axisyitemtext);
      axisyitem->setIcon(
          0, IconLoader::load(QString::fromLatin1("graph2d-axis-left"), IconLoader::LightDark));
      axisyitem->setData(0, Qt::UserRole, static_cast<int>(propertyitemtype));
      axisyitem->setData(0, Qt::UserRole + 1, axis3dyptvar);
      objectitems_.append(axisyitem);
    }

    // Axis Z
    {
      QString axiszitemtext = QString::fromLatin1("Z Axis(val)");
      QTreeWidgetItem *axiszitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(axiszitemtext));
      axiszitem->setToolTip(0, axiszitemtext);
      axiszitem->setIcon(
          0, IconLoader::load(QString::fromLatin1("graph2d-axis-right"), IconLoader::LightDark));
      axiszitem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DAxisValue));
      axiszitem->setData(0, Qt::UserRole + 1, axis3dzptvar);
      objectitems_.append(axiszitem);
    }

    // 3D plot
    QString plot3ditemtext = QString::fromLatin1("");
    QTreeWidgetItem *plot3ditem =
        new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
    switch (plottype) {
      case Graph3DCommon::Plot3DType::Surface: {
        plot3ditemtext = tr("Surface");
        plot3ditem->setIcon(
            0, IconLoader::load(QString::fromLatin1("graph3d-ribbon"), IconLoader::LightDark));
        plot3ditem->setData(
            0, Qt::UserRole,
            static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DSurface));
      } break;
      case Graph3DCommon::Plot3DType::Bar: {
        plot3ditemtext = tr("Bar");
        plot3ditem->setIcon(
            0, IconLoader::load(QString::fromLatin1("graph3d-bar"), IconLoader::LightDark));
        plot3ditem->setData(
            0, Qt::UserRole,
            static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DBar));
      } break;
      case Graph3DCommon::Plot3DType::Scatter: {
        plot3ditemtext = tr("Scatter");
        plot3ditem->setIcon(
            0, IconLoader::load(QString::fromLatin1("graph3d-scatter"), IconLoader::LightDark));
        plot3ditem->setData(
            0, Qt::UserRole,
            static_cast<int>(MyPlotTreeWidget::PropertyItemType::Plot3DScatter));
      } break;
    }
    plot3ditem->setText(0, plot3ditemtext);
    plot3ditem->setToolTip(0, plot3ditemtext);
    plot3ditem->setData(0, Qt::UserRole + 1, plot3dptvar);
    objectitems_.append(plot3ditem);

    // 3D series
    {
      switch (plottype) {
        case Graph3DCommon::Plot3DType::Surface: {
          int count = 1;
          Q_FOREACH (DataBlockSurface3D *block,
                   lout->getSurface3DModifier()->getData()) {
            QString surfaceseriesitemtext;
            if (block->ismatrix()) {
              surfaceseriesitemtext = tr("%1").arg(block->getmatrix()->name());
              tooltiptextfuncsurface = surfaceseriesitemtext;
            } else {
              surfaceseriesitemtext = tr("function %1").arg(count++);
              tooltiptextfuncsurface =
                  tooltiptextfuncsurface.arg(block->getfunction())
                      .arg(QString::number(block->getxlower()))
                      .arg(QString::number(block->getxupper()))
                      .arg(QString::number(block->getylower()))
                      .arg(QString::number(block->getyupper()))
                      .arg(QString::number(block->getzlower()))
                      .arg(QString::number(block->getzupper()))
                      .arg(QString::number(block->getxpoints()));
            }
            QTreeWidgetItem *surfaceseriesitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            surfaceseriesitem->setIcon(0,
                                       IconLoader::load(QString::fromLatin1("graph3d-polygon-mesh"),
                                                        IconLoader::LightDark));
            surfaceseriesitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot3DSurfaceDataBlock));
            surfaceseriesitem->setText(0, surfaceseriesitemtext);
            surfaceseriesitem->setToolTip(0, tooltiptextfuncsurface);
            surfaceseriesitem->setData(0, Qt::UserRole + 1,
                                       QVariant::fromValue<void *>(block));
            plot3ditem->addChild(surfaceseriesitem);
          }
        } break;
        case Graph3DCommon::Plot3DType::Bar: {
          Q_FOREACH (DataBlockBar3D *block, lout->getBar3DModifier()->getData()) {
            QString barseriesitemtext;
            (block->ismatrix())
                ? barseriesitemtext = tr("%1").arg(block->getmatrix()->name())
                : barseriesitemtext = tr("%1_%2")
                                          .arg(block->gettable()->name())
                                          .arg(block->getzcolumn()->name());
            QTreeWidgetItem *barseriesitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            barseriesitem->setIcon(
                0, IconLoader::load(QString::fromLatin1("graph3d-bar"), IconLoader::LightDark));
            barseriesitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot3DBarDataBlock));
            barseriesitem->setText(0, barseriesitemtext);
            barseriesitem->setToolTip(0, barseriesitemtext);
            barseriesitem->setData(0, Qt::UserRole + 1,
                                   QVariant::fromValue<void *>(block));
            plot3ditem->addChild(barseriesitem);
          }
        } break;
        case Graph3DCommon::Plot3DType::Scatter: {
            Q_FOREACH (DataBlockScatter3D *block,
                   lout->getScatter3DModifier()->getData()) {
            QString scatterseriesitemtext;
            (block->ismatrix())
                ? scatterseriesitemtext =
                      tr("%1").arg(block->getmatrix()->name())
                : scatterseriesitemtext = tr("%1_%2")
                                              .arg(block->gettable()->name())
                                              .arg(block->getzcolumn()->name());
            QTreeWidgetItem *scatterseriesitem =
                new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr));
            scatterseriesitem->setIcon(
                0,
                IconLoader::load(QString::fromLatin1("graph3d-point-mesh"), IconLoader::LightDark));
            scatterseriesitem->setData(
                0, Qt::UserRole,
                static_cast<int>(
                    MyPlotTreeWidget::PropertyItemType::Plot3DScatterDataBlock));
            scatterseriesitem->setText(0, scatterseriesitemtext);
            scatterseriesitem->setToolTip(0, scatterseriesitemtext);
            scatterseriesitem->setData(0, Qt::UserRole + 1,
                                       QVariant::fromValue<void *>(block));
            plot3ditem->addChild(scatterseriesitem);
          }
        } break;
      }
    }
  } else if (qobject_cast<Table *>(widget)) {
    Table *table = qobject_cast<Table *>(widget);
    objectbrowser_->setHeaderLabel(table->name());
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("table"), IconLoader::LightDark));
    // table window
    {
      QString tableitemtext = QString::fromLatin1("Rows x Cols");
      QTreeWidgetItem *tableitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(tableitemtext));
      tableitem->setToolTip(0, tableitemtext);
      tableitem->setIcon(0,
                         IconLoader::load(QString::fromLatin1("goto-cell"), IconLoader::LightDark));
      tableitem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::TableWindow));
      tableitem->setData(0, Qt::UserRole + 1,
                         QVariant::fromValue<void *>(table));
      objectitems_.append(tableitem);
    }
    tableConnections(table);
  } /*else if (qobject_cast<Note *>(widget)) {
    objectbrowser_->setHeaderLabel(qobject_cast<Note *>(widget)->name());
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("edit-note"), IconLoader::LightDark));
  } */else if (qobject_cast<Matrix *>(widget)) {
    Matrix *matrix = qobject_cast<Matrix *>(widget);
    objectbrowser_->setHeaderLabel(matrix->name());
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("matrix"), IconLoader::LightDark));
    // matrix window
    {
      QString matrixitemtext = QString(tr("Rows x Cols"));
      QTreeWidgetItem *matrixitem = new QTreeWidgetItem(
          static_cast<QTreeWidget *>(nullptr), QStringList(matrixitemtext));
      matrixitem->setToolTip(0, matrixitemtext);
      matrixitem->setIcon(0,
                          IconLoader::load(QString::fromLatin1("goto-cell"), IconLoader::LightDark));
      matrixitem->setData(
          0, Qt::UserRole,
          static_cast<int>(MyPlotTreeWidget::PropertyItemType::MatrixWindow));
      matrixitem->setData(0, Qt::UserRole + 1,
                          QVariant::fromValue<void *>(matrix));
      objectitems_.append(matrixitem);
    }
    matrixConnections(matrix);
  } else {
    objectbrowser_->setHeaderLabel(QString::fromLatin1("(Unknown)"));
    objectbrowser_->headerItem()->setIcon(
        0, IconLoader::load(QString::fromLatin1("clear-loginfo"), IconLoader::General));
    qDebug() << QString::fromLatin1("unknown Mywidget");
  }
  // add to Tree
  objectbrowser_->addTopLevelItems(objectitems_);
  objectbrowser_->insertTopLevelItems(0, objectitems_);
  objectbrowser_->expandAll();
  myWidgetConnections(widget);
  // always select toplevel item 0
  /*if (objectbrowser_->selectedItems().size() == 0 &&
      objectbrowser_->topLevelItemCount() > 0) {
    objectbrowser_->topLevelItem(0)->setSelected(true);
    selectObjectItem(objectbrowser_->topLevelItem(0));
  }*/
}

void PlotPropertyEditor::axisrectConnections(AxisRect2D *axisrect) {
  // created
  connect(axisrect, &AxisRect2D::Axis2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Axis2DCloned, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect->getLegend(), &Legend2D::legendMoved, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::Plot2DLegend) {
      Legend2D *lgnd =
          getgraph2dobject<Legend2D>(objectbrowser_->currentItem());
      if (axisrect == lgnd->getaxisrect_legend()) {
        QPointF origin = axisrect->getLegend()->getposition_legend();
        doubleManager_->setValue(itempropertylegendoriginxitem_, origin.x());
        doubleManager_->setValue(itempropertylegendoriginyitem_, origin.y());
        axisrect->parentPlot()->replot(
            QCustomPlot::RefreshPriority::rpQueuedRefresh);
      }
    }
  });
  connect(axisrect, &AxisRect2D::TextItem2DMoved, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::Plot2DTextItem) {
      TextItem2D *textitem =
          getgraph2dobject<TextItem2D>(objectbrowser_->currentItem());
      if (axisrect == textitem->getaxisrect()) {
        QPointF origin = textitem->position->pixelPosition();
        doubleManager_->setValue(itempropertytextpixelpositionxitem_,
                                 origin.x());
        doubleManager_->setValue(itempropertytextpixelpositionyitem_,
                                 origin.y());
      }
    }
  });
  connect(axisrect, &AxisRect2D::LineItem2DMoved, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::Plot2DLineItem) {
      LineItem2D *lineitem =
          getgraph2dobject<LineItem2D>(objectbrowser_->currentItem());
      if (axisrect == lineitem->getaxisrect()) {
        QPointF origin1 = lineitem->position(QString::fromLatin1("start"))->pixelPosition();
        QPointF origin2 = lineitem->position(QString::fromLatin1("end"))->pixelPosition();
        doubleManager_->setValue(itempropertylinepixelpositionx1item_,
                                 origin1.x());
        doubleManager_->setValue(itempropertylinepixelpositiony1item_,
                                 origin1.y());
        doubleManager_->setValue(itempropertylinepixelpositionx2item_,
                                 origin2.x());
        doubleManager_->setValue(itempropertylinepixelpositiony2item_,
                                 origin2.y());
      }
    }
  });
  connect(axisrect, &AxisRect2D::ImageItem2DMoved, this, [=]() {
    if (objectbrowser_->currentItem() &&
        static_cast<MyPlotTreeWidget::PropertyItemType>(
            objectbrowser_->currentItem()
                ->data(0, Qt::UserRole)
                .value<int>()) ==
            MyPlotTreeWidget::PropertyItemType::Plot2DImageItem) {
      ImageItem2D *imageitem =
          getgraph2dobject<ImageItem2D>(objectbrowser_->currentItem());
      if (axisrect == imageitem->getaxisrect()) {
        QPointF origin = imageitem->position(QString::fromLatin1("topLeft"))->pixelPosition();
        doubleManager_->setValue(itempropertyimagepixelpositionxitem_,
                                 origin.x());
        doubleManager_->setValue(itempropertyimagepixelpositionyitem_,
                                 origin.y());
      }
    }
  });

  connect(axisrect, &AxisRect2D::TextItem2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineItem2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ImageItem2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineSpecial2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineSpecialChannel2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });

  connect(axisrect, &AxisRect2D::Curve2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::StatBox2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Vector2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Bar2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Pie2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ColorMap2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ErrorBar2DCreated, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });

  // Removed
  connect(axisrect, &AxisRect2D::Axis2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::TextItem2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineItem2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ImageItem2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineSpecial2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::LineSpecialChannel2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Curve2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::StatBox2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Vector2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Bar2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::Pie2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ColorMap2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
  connect(axisrect, &AxisRect2D::ErrorBar2DRemoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });

  // Layer moved
  connect(axisrect, &AxisRect2D::LayerMoved, this, [=]() {
    axisrect->parentPlot()->replot(
        QCustomPlot::RefreshPriority::rpQueuedRefresh);
    objectschanged();
  });
}

void PlotPropertyEditor::setObjectPropertyId() {
  // MyWidget Properties
  mywidgetwindowrectitem_->setPropertyId(QString::fromLatin1("mywidgetwindowrectitem_"));
  mywidgetwindownameitem_->setPropertyId(QString::fromLatin1("mywidgetwindownameitem_"));
  mywidgetwindowlabelitem_->setPropertyId(QString::fromLatin1("mywidgetwindowlabelitem_"));
  // Plot Canvas properties
  canvaspropertycoloritem_->setPropertyId(QString::fromLatin1("canvaspropertycoloritem_"));
  canvaspropertybufferdevicepixelratioitem_->setPropertyId(
      QString::fromLatin1("canvaspropertybufferdevicepixelratioitem_"));
  canvaspropertyopenglitem_->setPropertyId(QString::fromLatin1("canvaspropertyopenglitem_"));
  canvaspropertysizeitem_->setPropertyId(QString::fromLatin1("canvaspropertysizeitem_"));
  canvaspropertyrowsapcingitem_->setPropertyId(QString::fromLatin1("canvaspropertyrowsapcingitem_"));
  canvaspropertycolumnsapcingitem_->setPropertyId(
      QString::fromLatin1("canvaspropertycolumnsapcingitem_"));
  // Layout properties
  layoutpropertymargingroupitem_->setPropertyId(
      QString::fromLatin1("layoutpropertymargingroupitem_"));
  layoutpropertyrectitem_->setPropertyId(QString::fromLatin1("layoutpropertyrectitem_"));
  layoutpropertycoloritem_->setPropertyId(QString::fromLatin1("layoutpropertycoloritem_"));
  layoutpropertyfillstyleitem_->setPropertyId(QString::fromLatin1("layoutpropertyfillstyleitem_"));
  layoutpropertyautomarginstatusitem_->setPropertyId(
      QString::fromLatin1("layoutpropertyautomarginstatusitem_"));
  layoutpropertyleftmarginitem_->setPropertyId(QString::fromLatin1("layoutpropertyleftmarginitem_"));
  layoutpropertyrightmarginitem_->setPropertyId(
      QString::fromLatin1("layoutpropertyrightmarginitem_"));
  layoutpropertytopmarginitem_->setPropertyId(QString::fromLatin1("layoutpropertytopmarginitem_"));
  layoutpropertybottommarginitem_->setPropertyId(
      QString::fromLatin1("layoutpropertybottommarginitem_"));
  layoutpropertyrowstreachfactoritem_->setPropertyId(
      QString::fromLatin1("layoutpropertyrowstreachfactoritem_"));
  layoutpropertycolumnstreachfactoritem_->setPropertyId(
      QString::fromLatin1("layoutpropertycolumnstreachfactoritem_"));
  // Axis Properties General Block
  axispropertyvisibleitem_->setPropertyId(QString::fromLatin1("axispropertyvisibleitem_"));
  axispropertyoffsetitem_->setPropertyId(QString::fromLatin1("axispropertyoffsetitem_"));
  axispropertyfromitem_->setPropertyId(QString::fromLatin1("axispropertyfromitem_"));
  axispropertytoitem_->setPropertyId(QString::fromLatin1("axispropertytoitem_"));
  axispropertyupperendingstyleitem_->setPropertyId(
      QString::fromLatin1("axispropertyupperendingstyleitem_"));
  axispropertylowerendingstyleitem_->setPropertyId(
      QString::fromLatin1("axispropertylowerendingstyleitem_"));
  axispropertylinlogitem_->setPropertyId(QString::fromLatin1("axispropertylinlogitem_"));
  axispropertyinvertitem_->setPropertyId(QString::fromLatin1("axispropertyinvertitem_"));
  axispropertystrokecoloritem_->setPropertyId(QString::fromLatin1("axispropertystrokecoloritem_"));
  axispropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("axispropertystrokethicknessitem_"));
  axispropertystroketypeitem_->setPropertyId(QString::fromLatin1("axispropertystroketypeitem_"));
  axispropertyantialiaseditem_->setPropertyId(QString::fromLatin1("axispropertyantialiaseditem_"));
  // Axis Properties Label sub block
  axispropertylabeltextitem_->setPropertyId(QString::fromLatin1("axispropertylabeltextitem_"));
  axispropertylabelfontitem_->setPropertyId(QString::fromLatin1("axispropertylabelfontitem_"));
  axispropertylabelcoloritem_->setPropertyId(QString::fromLatin1("axispropertylabelcoloritem_"));
  axispropertylabelpaddingitem_->setPropertyId(QString::fromLatin1("axispropertylabelpaddingitem_"));
  // Axis Properties Ticks sub block
  axispropertytickvisibilityitem_->setPropertyId(
      QString::fromLatin1("axispropertytickvisibilityitem_"));
  axispropertytickstepstrategy_->setPropertyId(QString::fromLatin1("axispropertytickstepstrategy_"));
  // axispropertytickervaluetickstep_->setPropertyId(
  //    "axispropertytickervaluetickstep_"));
  // axispropertytickervaluescalestrategy_->setPropertyId(
  //    "axispropertytickervaluescalestrategy_"));
  axispropertytickersymbolsymbol_->setPropertyId(
      QString::fromLatin1("axispropertytickersymbolsymbol_"));
  axispropertytickersymbolvalue_->setPropertyId(
      QString::fromLatin1("axispropertytickersymbolvalue_"));
  // axispropertytickersymbolperiodicity_->setPropertyId(
  //    "axispropertytickersymbolperiodicity_"));
  axispropertytickersymbolfractionstyle_->setPropertyId(
      QString::fromLatin1("axispropertytickersymbolfractionstyle_"));
  axispropertytickersubtickcount_->setPropertyId(
      QString::fromLatin1("axispropertytickersubtickcount_"));
  axispropertytickerlogbase_->setPropertyId(QString::fromLatin1("axispropertytickerlogbase_"));
  axispropertytickertimeformat_->setPropertyId(QString::fromLatin1("axispropertytickertimeformat_"));
  // axispropertytickertimefieldwidth_->setPropertyId(
  //    "axispropertytickertimefieldwidth_"));
  axispropertytickerdatetimeformat_->setPropertyId(
      QString::fromLatin1("axispropertytickerdatetimeformat_"));
  // axispropertytickerdatetimetickorigin_->setPropertyId(
  //    "axispropertytickerdatetimetickorigin_"));
  axispropertytickerdatetimefrom_->setPropertyId(
      QString::fromLatin1("axispropertytickerdatetimefrom_"));
  axispropertytickerdatetimeto_->setPropertyId(QString::fromLatin1("axispropertytickerdatetimeto_"));
  axispropertytickcountitem_->setPropertyId(QString::fromLatin1("axispropertytickcountitem_"));
  axispropertytickoriginitem_->setPropertyId(QString::fromLatin1("axispropertytickoriginitem_"));
  axispropertyticklengthinitem_->setPropertyId(QString::fromLatin1("axispropertyticklengthinitem_"));
  axispropertyticklengthoutitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklengthoutitem_"));
  axispropertytickstrokecoloritem_->setPropertyId(
      QString::fromLatin1("axispropertytickstrokecoloritem_"));
  axispropertytickstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("axispropertytickstrokethicknessitem_"));
  axispropertytickstroketypeitem_->setPropertyId(
      QString::fromLatin1("axispropertytickstroketypeitem_"));
  // Axis Properties Sub-ticks sub block
  axispropertysubtickvisibilityitem_->setPropertyId(
      QString::fromLatin1("axispropertysubtickvisibilityitem_"));
  axispropertysubticklengthinitem_->setPropertyId(
      QString::fromLatin1("axispropertysubticklengthinitem_"));
  axispropertysubticklengthoutitem_->setPropertyId(
      QString::fromLatin1("axispropertysubticklengthoutitem_"));
  axispropertysubtickstrokecoloritem_->setPropertyId(
      QString::fromLatin1("axispropertysubtickstrokecoloritem_"));
  axispropertysubtickstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("axispropertysubtickstrokethicknessitem_"));
  axispropertysubtickstroketypeitem_->setPropertyId(
      QString::fromLatin1("axispropertysubtickstroketypeitem_"));
  // Axis Properties Ticks Label sub block
  axispropertyticklabelvisibilityitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelvisibilityitem_"));
  axispropertyticklabelfontitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelfontitem_"));
  axispropertyticklabelcoloritem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelcoloritem_"));
  axispropertyticklabelpaddingitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelpaddingitem_"));
  axispropertyticklabelrotationitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelrotationitem_"));
  axispropertyticklabelsideitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelsideitem_"));
  axispropertyticklabelformatitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelformatitem_"));
  axispropertyticklabelprecisionitem_->setPropertyId(
      QString::fromLatin1("axispropertyticklabelprecisionitem_"));
  // Legend Properties
  itempropertylegendoriginxitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendoriginxitem_"));
  itempropertylegendoriginyitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendoriginyitem_"));
  itempropertylegendvisibleitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendvisibleitem_"));
  itempropertylegenddirectionitem_->setPropertyId(
      QString::fromLatin1("itempropertylegenddirectionitem_"));
  itempropertylegendmarginitem_->setPropertyId(QString::fromLatin1("itempropertylegendmarginitem_"));
  itempropertylegendfontitem_->setPropertyId(QString::fromLatin1("itempropertylegendfontitem_"));
  itempropertylegendtextcoloritem_->setPropertyId(
      QString::fromLatin1("itempropertylegendtextcoloritem_"));
  itempropertylegendiconwidthitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendiconwidthitem_"));
  itempropertylegendiconheightitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendiconheightitem_"));
  itempropertylegendicontextpaddingitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendicontextpaddingitem_"));
  itempropertylegendborderstrokecoloritem_->setPropertyId(
      QString::fromLatin1("itempropertylegendborderstrokecoloritem_"));
  itempropertylegendborderstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendborderstrokethicknessitem_"));
  itempropertylegendborderstroketypeitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendborderstroketypeitem_"));
  itempropertylegendbackgroundcoloritem_->setPropertyId(
      QString::fromLatin1("itempropertylegendbackgroundcoloritem_"));
  itempropertylegendbackgroundfillstyleitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendbackgroundfillstyleitem_"));
  itempropertylegendtitlevisibleitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendtitlevisibleitem_"));
  itempropertylegendtitletextitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendtitletextitem_"));
  itempropertylegendtitlefontitem_->setPropertyId(
      QString::fromLatin1("itempropertylegendtitlefontitem_"));
  itempropertylegendtitlecoloritem_->setPropertyId(
      QString::fromLatin1("itempropertylegendtitlecoloritem_"));
  // Text Item Properties block
  itempropertytextpixelpositionxitem_->setPropertyId(
      QString::fromLatin1("itempropertytextpixelpositionxitem_"));
  itempropertytextpixelpositionyitem_->setPropertyId(
      QString::fromLatin1("itempropertytextpixelpositionyitem_"));
  itempropertytextmarginitem_->setPropertyId(QString::fromLatin1("itempropertytextmarginitem_"));
  itempropertytexttextitem_->setPropertyId(QString::fromLatin1("itempropertytexttextitem_"));
  itempropertytextfontitem_->setPropertyId(QString::fromLatin1("itempropertytextfontitem_"));
  itempropertytextcoloritem_->setPropertyId(QString::fromLatin1("itempropertytextcoloritem_"));
  itempropertytextantialiaseditem_->setPropertyId(
      QString::fromLatin1("itempropertytextantialiaseditem_"));
  itempropertytextstrokecoloritem_->setPropertyId(
      QString::fromLatin1("itempropertytextstrokecoloritem_"));
  itempropertytextstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("itempropertytextstrokethicknessitem_"));
  itempropertytextstroketypeitem_->setPropertyId(
      QString::fromLatin1("itempropertytextstroketypeitem_"));
  itempropertytextbackgroundcoloritem_->setPropertyId(
      QString::fromLatin1("itempropertytextbackgroundcoloritem_"));
  itempropertytextbackgroundfillstyleitem_->setPropertyId(
      QString::fromLatin1("itempropertytextbackgroundfillstyleitem_"));
  itempropertytextrotationitem_->setPropertyId(QString::fromLatin1("itempropertytextrotationitem_"));
  itempropertytextpositionalignmentitem_->setPropertyId(
      QString::fromLatin1("itempropertytextpositionalignmentitem_"));
  itempropertytexttextalignmentitem_->setPropertyId(
      QString::fromLatin1("itempropertytexttextalignmentitem_"));
  // Line Item Properties
  itempropertylinepixelpositionx1item_->setPropertyId(
      QString::fromLatin1("itempropertylinepixelpositionx1item_"));
  itempropertylinepixelpositiony1item_->setPropertyId(
      QString::fromLatin1("itempropertylinepixelpositiony1item_"));
  itempropertylinepixelpositionx2item_->setPropertyId(
      QString::fromLatin1("itempropertylinepixelpositionx2item_"));
  itempropertylinepixelpositiony2item_->setPropertyId(
      QString::fromLatin1("itempropertylinepixelpositiony2item_"));
  itempropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("itempropertylineantialiaseditem_"));
  itempropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("itempropertylinestrokecoloritem_"));
  itempropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("itempropertylinestrokethicknessitem_"));
  itempropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("itempropertylinestroketypeitem_"));
  itempropertylineendingstyleitem_->setPropertyId(
      QString::fromLatin1("itempropertylineendingstyleitem_"));
  itempropertylineendingwidthitem_->setPropertyId(
      QString::fromLatin1("itempropertylineendingwidthitem_"));
  itempropertylineendinglengthitem_->setPropertyId(
      QString::fromLatin1("itempropertylineendinglengthitem_"));
  itempropertylinestartingstyleitem_->setPropertyId(
      QString::fromLatin1("itempropertylinestartingstyleitem_"));
  itempropertylinestartingwidthitem_->setPropertyId(
      QString::fromLatin1("itempropertylinestartingwidthitem_"));
  itempropertylinestartinglengthitem_->setPropertyId(
      QString::fromLatin1("itempropertylinestartinglengthitem_"));
  // Image Item Properties
  itempropertyimagepixelpositionxitem_->setPropertyId(
      QString::fromLatin1("itempropertyimagepixelpositionxitem_"));
  itempropertyimagepixelpositionyitem_->setPropertyId(
      QString::fromLatin1("itempropertyimagepixelpositionyitem_"));
  itempropertyimagerotationitem_->setPropertyId(
      QString::fromLatin1("itempropertyimagerotationitem_"));
  itempropertyimagesourceitem_->setPropertyId(QString::fromLatin1("itempropertyimagesourceitem_"));
  itempropertyimagestrokecoloritem_->setPropertyId(
      QString::fromLatin1("itempropertyimagestrokecoloritem_"));
  itempropertyimagestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("itempropertyimagestrokethicknessitem_"));
  itempropertyimagestroketypeitem_->setPropertyId(
      QString::fromLatin1("itempropertyimagestroketypeitem_"));
  // Line Scatter Property Block
  lsplotpropertyxaxisitem_->setPropertyId(QString::fromLatin1("lsplotpropertyxaxisitem_"));
  lsplotpropertyyaxisitem_->setPropertyId(QString::fromLatin1("lsplotpropertyyaxisitem_"));
  lsplotpropertylinestyleitem_->setPropertyId(QString::fromLatin1("lsplotpropertylinestyleitem_"));
  lsplotpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinestrokecoloritem_"));
  lsplotpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinestrokethicknesitem_"));
  lsplotpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinestroketypeitem_"));
  lsplotpropertylinefillstatusitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinefillstatusitem_"));
  lsplotpropertylinefillcoloritem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinefillcoloritem_"));
  lsplotpropertylinefillstyleitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylinefillstyleitem_"));
  lsplotpropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylineantialiaseditem_"));
  lsplotpropertyscatterstyleitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterstyleitem_"));
  lsplotpropertyscatterthicknessitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterthicknessitem_"));
  lsplotpropertyscatterfillcoloritem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterfillcoloritem_"));
  lsplotpropertyscatterstrokecoloritem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterstrokecoloritem_"));
  lsplotpropertyscatterstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterstrokethicknessitem_"));
  lsplotpropertyscatterstrokestyleitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterstrokestyleitem_"));
  lsplotpropertyscatterantialiaseditem_->setPropertyId(
      QString::fromLatin1("lsplotpropertyscatterantialiaseditem_"));
  lsplotpropertylegendvisibleitem_->setPropertyId(
      QString::fromLatin1("lsplotpropertylegendvisibleitem_"));
  lsplotpropertylegendtextitem_->setPropertyId(QString::fromLatin1("lsplotpropertylegendtextitem_"));
  // LineSpecialChannel Properties block
  channelplotpropertyxaxisitem_->setPropertyId(QString::fromLatin1("channelplotpropertyxaxisitem_"));
  channelplotpropertyyaxisitem_->setPropertyId(QString::fromLatin1("channelplotpropertyyaxisitem_"));
  channelplotpropertylegendvisibleitem_->setPropertyId(
      QString::fromLatin1("channelplotpropertylegendvisibleitem_"));
  channelplotpropertylegendtextitem_->setPropertyId(
      QString::fromLatin1("channelplotpropertylegendtextitem_"));
  channel1plotpropertygroupitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertygroupitem_"));
  channel1plotpropertylinestyleitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinestyleitem_"));
  channel1plotpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinestrokecoloritem_"));
  channel1plotpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinestrokethicknessitem_"));
  channel1plotpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinestroketypeitem_"));
  channel1plotpropertylinefillcoloritem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinefillcoloritem_"));
  channel1plotpropertylinefillstylritem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylinefillstylritem_"));
  channel1plotpropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertylineantialiaseditem_"));
  channel1plotpropertyscatterstyleitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterstyleitem_"));
  channel1plotpropertyscatterthicknessitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterthicknessitem_"));
  channel1plotpropertyscatterfillcoloritem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterfillcoloritem_"));
  channel1plotpropertyscatterstrokecoloritem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterstrokecoloritem_"));
  channel1plotpropertyscatterstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterstrokethicknessitem_"));
  channel1plotpropertyscatterstrokestyleitem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterstrokestyleitem_"));
  channel1plotpropertyscatterantialiaseditem_->setPropertyId(
      QString::fromLatin1("channel1plotpropertyscatterantialiaseditem_"));
  channel2plotpropertygroupitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertygroupitem_"));
  channel2plotpropertylinestyleitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertylinestyleitem_"));
  channel2plotpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertylinestrokecoloritem_"));
  channel2plotpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertylinestrokethicknessitem_"));
  channel2plotpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertylinestroketypeitem_"));
  channel2plotpropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertylineantialiaseditem_"));
  channel2plotpropertyscatterstyleitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterstyleitem_"));
  channel2plotpropertyscatterthicknessitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterthicknessitem_"));
  channel2plotpropertyscatterfillcoloritem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterfillcoloritem_"));
  channel2plotpropertyscatterstrokecoloritem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterstrokecoloritem_"));
  channel2plotpropertyscatterstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterstrokethicknessitem_"));
  channel2plotpropertyscatterstrokestyleitem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterstrokestyleitem_"));
  channel2plotpropertyscatterantialiaseditem_->setPropertyId(
      QString::fromLatin1("channel2plotpropertyscatterantialiaseditem_"));
  // Curve Property Block
  cplotpropertyxaxisitem_->setPropertyId(QString::fromLatin1("cplotpropertyxaxisitem_"));
  cplotpropertyyaxisitem_->setPropertyId(QString::fromLatin1("cplotpropertyyaxisitem_"));
  cplotpropertylinestyleitem_->setPropertyId(QString::fromLatin1("cplotpropertylinestyleitem_"));
  cplotpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinestrokecoloritem_"));
  cplotpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinestrokethicknesitem_"));
  cplotpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinestroketypeitem_"));
  cplotpropertylinefillstatusitem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinefillstatusitem_"));
  cplotpropertylinefillcoloritem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinefillcoloritem_"));
  cplotpropertylinefillstyleitem_->setPropertyId(
      QString::fromLatin1("cplotpropertylinefillstyleitem_"));
  cplotpropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("cplotpropertylineantialiaseditem_"));
  cplotpropertyscatterstyleitem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterstyleitem_"));
  cplotpropertyscatterthicknessitem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterthicknessitem_"));
  cplotpropertyscatterfillcoloritem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterfillcoloritem_"));
  cplotpropertyscatterstrokecoloritem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterstrokecoloritem_"));
  cplotpropertyscatterstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterstrokethicknessitem_"));
  cplotpropertyscatterstrokestyleitem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterstrokestyleitem_"));
  cplotpropertyscatterantialiaseditem_->setPropertyId(
      QString::fromLatin1("cplotpropertyscatterantialiaseditem_"));
  cplotpropertylegendvisibleitem_->setPropertyId(
      QString::fromLatin1("cplotpropertylegendvisibleitem_"));
  cplotpropertylegendtextitem_->setPropertyId(QString::fromLatin1("cplotpropertylegendtextitem_"));

  // Box Properties block
  barplotpropertyxaxisitem_->setPropertyId(QString::fromLatin1("barplotpropertyxaxisitem_"));
  barplotpropertyyaxisitem_->setPropertyId(QString::fromLatin1("barplotpropertyyaxisitem_"));
  barplotpropertywidthitem_->setPropertyId(QString::fromLatin1("barplotpropertywidthitem_"));
  barplotpropertystackgapitem_->setPropertyId(QString::fromLatin1("barplotpropertystackgapitem_"));
  barplotpropertyfillantialiaseditem_->setPropertyId(
      QString::fromLatin1("barplotpropertyfillantialiaseditem_"));
  barplotpropertyfillcoloritem_->setPropertyId(QString::fromLatin1("barplotpropertyfillcoloritem_"));
  barplotpropertyfillstyleitem_->setPropertyId(QString::fromLatin1("barplotpropertyfillstyleitem_"));
  barplotpropertyantialiaseditem_->setPropertyId(
      QString::fromLatin1("barplotpropertyantialiaseditem_"));
  barplotpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("barplotpropertystrokecoloritem_"));
  barplotpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("barplotpropertystrokethicknessitem_"));
  barplotpropertystrokestyleitem_->setPropertyId(
      QString::fromLatin1("barplotpropertystrokestyleitem_"));
  barplotpropertylegendtextitem_->setPropertyId(
      QString::fromLatin1("barplotpropertylegendtextitem_"));
  barplotpropertyhistautobinstatusitem_->setPropertyId(
      QString::fromLatin1("barplotpropertyhistautobinstatusitem_"));
  barplotpropertyhistbinitem_->setPropertyId(QString::fromLatin1("barplotpropertyhistbinitem_"));
  barplotpropertyhistbeginitem_->setPropertyId(QString::fromLatin1("barplotpropertyhistbeginitem_"));
  barplotpropertyhistenditem_->setPropertyId(QString::fromLatin1("barplotpropertyhistenditem_"));

  // StatBox Properties block
  statboxplotpropertyxaxisitem_->setPropertyId(QString::fromLatin1("statboxplotpropertyxaxisitem_"));
  statboxplotpropertyyaxisitem_->setPropertyId(QString::fromLatin1("statboxplotpropertyyaxisitem_"));
  statboxplotpropertywidthitem_->setPropertyId(QString::fromLatin1("statboxplotpropertywidthitem_"));
  statboxplotpropertywhiskerwidthitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerwidthitem_"));
  statboxplotpropertyboxstyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyboxstyleitem_"));
  statboxplotpropertywhiskerstyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerstyleitem_"));
  statboxplotpropertyantialiaseditem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyantialiaseditem_"));
  statboxplotpropertyfillantialiaseditem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyfillantialiaseditem_"));
  statboxplotpropertyboxoutlinecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyboxoutlinecoloritem_"));
  statboxplotpropertyboxoutlinethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyboxoutlinethicknessitem_"));
  statboxplotpropertyboxoutlinestyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyboxoutlinestyleitem_"));
  statboxplotpropertyfillstatusitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyfillstatusitem_"));
  statboxplotpropertyfillcoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyfillcoloritem_"));
  statboxplotpropertyfillstyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyfillstyleitem_"));
  statboxplotpropertywhiskerantialiaseditem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerantialiaseditem_"));
  statboxplotpropertywhiskerstrokecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerstrokecoloritem_"));
  statboxplotpropertywhiskerstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerstrokethicknessitem_"));
  statboxplotpropertywhiskerstrokestyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerstrokestyleitem_"));
  statboxplotpropertywhiskerbarstrokecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerbarstrokecoloritem_"));
  statboxplotpropertywhiskerbarstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerbarstrokethicknessitem_"));
  statboxplotpropertywhiskerbarstrokestyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertywhiskerbarstrokestyleitem_"));
  statboxplotpropertymedianstrokecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertymedianstrokecoloritem_"));
  statboxplotpropertymideanstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertymideanstrokethicknessitem_"));
  statboxplotpropertymideanstrokestyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertymideanstrokestyleitem_"));
  statboxplotpropertyscattershowitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscattershowitem_"));
  statboxplotpropertyscatterantialiaseditem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatterantialiaseditem_"));
  statboxplotpropertyscatterstyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatterstyleitem_"));
  statboxplotpropertyscattersizeitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscattersizeitem_"));
  statboxplotpropertyscatterfillcoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatterfillcoloritem_"));
  statboxplotpropertyscatteroutlinecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatteroutlinecoloritem_"));
  statboxplotpropertyscatteroutlinethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatteroutlinethicknessitem_"));
  statboxplotpropertyscatteroutlinestyleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertyscatteroutlinestyleitem_"));
  statboxplotpropertylegendtextitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylegendtextitem_"));

  // Vector property block
  vectorpropertyxaxisitem_->setPropertyId(QString::fromLatin1("vectorpropertyxaxisitem_"));
  vectorpropertyyaxisitem_->setPropertyId(QString::fromLatin1("vectorpropertyyaxisitem_"));
  vectorpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylinestrokecoloritem_"));
  vectorpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylinestrokethicknessitem_"));
  vectorpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylinestroketypeitem_"));
  vectorpropertylineendingtypeitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylineendingtypeitem_"));
  vectorpropertylineendingheightitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylineendingheightitem_"));
  vectorpropertylineendingwidthitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylineendingwidthitem_"));
  vectorpropertylineantialiaseditem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylineantialiaseditem_"));
  vectorpropertylegendvisibleitem_->setPropertyId(
      QString::fromLatin1("statboxplotpropertylegendvisibleitem_"));
  vectorpropertylegendtextitem_->setPropertyId(QString::fromLatin1("vectorpropertylegendtextitem_"));

  // Pie Properties Block
  pieplotpropertystyleitem_->setPropertyId(QString::fromLatin1("pieplotpropertystyleitem_"));
  pieplotpropertylinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("pieplotpropertylinestrokecoloritem_"));
  pieplotpropertylinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("pieplotpropertylinestrokethicknessitem_"));
  pieplotpropertylinestroketypeitem_->setPropertyId(
      QString::fromLatin1("pieplotpropertylinestroketypeitem_"));
  pieplotpropertymarginpercentitem_->setPropertyId(
      QString::fromLatin1("pieplotpropertymarginpercentitem_"));

  // Colormap Properties Block
  colormappropertyinterpolateitem_->setPropertyId(
      QString::fromLatin1("colormappropertyinterpolateitem_"));
  colormappropertytightboundaryitem_->setPropertyId(
      QString::fromLatin1("colormappropertytightboundaryitem_"));
  colormappropertylevelcountitem_->setPropertyId(
      QString::fromLatin1("colormappropertylevelcountitem_"));
  colormappropertygradientitem_->setPropertyId(QString::fromLatin1("colormappropertygradientitem_"));
  colormappropertygradientinvertitem_->setPropertyId(
      QString::fromLatin1("colormappropertygradientinvertitem_"));
  colormappropertygradientperiodicitem_->setPropertyId(
      QString::fromLatin1("colormappropertygradientperiodicitem_"));
  colormappropertyscalevisibleitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscalevisibleitem_"));
  colormappropertyscalewidthitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscalewidthitem_"));
  // Colormap Axis general
  colormappropertyscaleaxisvisibleitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisvisibleitem_"));
  colormappropertyscaleaxisoffsetitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisoffsetitem_"));
  colormappropertyscaleaxisfromitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisfromitem_"));
  colormappropertyscaleaxistoitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxistoitem_"));
  colormappropertyscaleaxislinlogitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxislinlogitem_"));
  colormappropertyscaleaxisinvertitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisinvertitem_"));
  colormappropertyscaleaxisstrokecoloritem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisstrokecoloritem_"));
  colormappropertyscaleaxisstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisstrokethicknessitem_"));
  colormappropertyscaleaxisstroketypeitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisstroketypeitem_"));
  colormappropertyscaleaxisantialiaseditem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisantialiaseditem_"));
  // Colormap Axis Properties Label sub block
  colormappropertyscaleaxislabeltextitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxislabeltextitem_"));
  colormappropertyscaleaxislabelfontitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxislabelfontitem_"));
  colormappropertyscaleaxislabelcoloritem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxislabelcoloritem_"));
  colormappropertyscaleaxislabelpaddingitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxislabelpaddingitem_"));
  // Colormap Axis Properties Ticks sub block
  colormappropertyscaleaxistickvisibilityitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxistickvisibilityitem_"));
  colormappropertyscaleaxisticklengthinitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklengthinitem_"));
  colormappropertyscaleaxisticklengthoutitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklengthoutitem_"));
  colormappropertyscaleaxistickstrokecoloritem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxistickstrokecoloritem_"));
  colormappropertyscaleaxistickstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxistickstrokethicknessitem_"));
  colormappropertyscaleaxistickstroketypeitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxistickstroketypeitem_"));
  // Colormap Axis Properties Sub-ticks sub block
  colormappropertyscaleaxissubtickvisibilityitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubtickvisibilityitem_"));
  colormappropertyscaleaxissubticklengthinitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubticklengthinitem_"));
  colormappropertyscaleaxissubticklengthoutitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubticklengthoutitem_"));
  colormappropertyscaleaxissubtickstrokecoloritem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubtickstrokecoloritem_"));
  colormappropertyscaleaxissubtickstrokethicknessitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubtickstrokethicknessitem_"));
  colormappropertyscaleaxissubtickstroketypeitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxissubtickstroketypeitem_"));
  // Colormap Axis Properties Ticks Label sub block
  colormappropertyscaleaxisticklabelvisibilityitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelvisibilityitem_"));
  colormappropertyscaleaxisticklabelfontitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelfontitem_"));
  colormappropertyscaleaxisticklabelcoloritem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelcoloritem_"));
  colormappropertyscaleaxisticklabelpaddingitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelpaddingitem_"));
  colormappropertyscaleaxisticklabelrotationitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelrotationitem_"));
  colormappropertyscaleaxisticklabelsideitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelsideitem_"));
  colormappropertyscaleaxisticklabelformatitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelformatitem_"));
  colormappropertyscaleaxisticklabelprecisionitem_->setPropertyId(
      QString::fromLatin1("colormappropertyscaleaxisticklabelprecisionitem_"));

  // ErrorBar2D
  errorbarpropertywhiskerwidthitem_->setPropertyId(
      QString::fromLatin1("errorbarpropertywhiskerwidthitem_"));
  errorbarpropertysymbolgaptem_->setPropertyId(QString::fromLatin1("errorbarpropertysymbolgaptem_"));
  errorbarpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("errorbarpropertystrokecoloritem_"));
  errorbarpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("errorbarpropertystrokethicknessitem_"));
  errorbarpropertystroketypeitem_->setPropertyId(
      QString::fromLatin1("errorbarpropertystroketypeitem_"));
  errorbarpropertyantialiaseditem_->setPropertyId(
      QString::fromLatin1("errorbarpropertyantialiaseditem_"));
  errorbarpropertyfillstatusitem_->setPropertyId(
      QString::fromLatin1("errorbarpropertyfillstatusitem_"));
  errorbarpropertyfillcoloritem_->setPropertyId(
      QString::fromLatin1("errorbarpropertyfillcoloritem_"));

  // Grid Block
  hgridaxispropertycomboitem_->setPropertyId(QString::fromLatin1("hgridaxispropertycomboitem_"));
  hmajgridpropertyvisibleitem_->setPropertyId(QString::fromLatin1("hmajgridpropertyvisibleitem_"));
  hmajgridpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertystrokecoloritem_"));
  hmajgridpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertystrokethicknessitem_"));
  hmajgridpropertystroketypeitem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertystroketypeitem_"));
  hmajgridpropertyzerolinevisibleitem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertyzerolinevisibleitem_"));
  hmajgridpropertyzerolinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertyzerolinestrokecoloritem_"));
  hmajgridpropertyzerolinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertyzerolinestrokethicknessitem_"));
  hmajgridpropertyzerolinestroketypeitem_->setPropertyId(
      QString::fromLatin1("hmajgridpropertyzerolinestroketypeitem_"));
  hmingridpropertyvisibleitem_->setPropertyId(QString::fromLatin1("hmingridpropertyvisibleitem_"));
  hmingridpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("hmingridpropertystrokecoloritem_"));
  hmingridpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("hmingridpropertystrokethicknessitem_"));
  hmingridpropertystroketypeitem_->setPropertyId(
      QString::fromLatin1("hmingridpropertystroketypeitem_"));
  vgridaxispropertycomboitem_->setPropertyId(QString::fromLatin1("vgridaxispropertycomboitem_"));
  vmajgridpropertyvisibleitem_->setPropertyId(QString::fromLatin1("vmajgridpropertyvisibleitem_"));
  vmajgridpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertystrokecoloritem_"));
  vmajgridpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertystrokethicknessitem_"));
  vmajgridpropertystroketypeitem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertystroketypeitem_"));
  vmajgridpropertyzerolinevisibleitem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertyzerolinevisibleitem_"));
  vmajgridpropertyzerolinestrokecoloritem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertyzerolinestrokecoloritem_"));
  vmajgridpropertyzerolinestrokethicknessitem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertyzerolinestrokethicknessitem_"));
  vmajgridpropertyzerolinestroketypeitem_->setPropertyId(
      QString::fromLatin1("vmajgridpropertyzerolinestroketypeitem_"));
  vmingridpropertyvisibleitem_->setPropertyId(QString::fromLatin1("vmingridpropertyvisibleitem_"));
  vmingridpropertystrokecoloritem_->setPropertyId(
      QString::fromLatin1("vmingridpropertystrokecoloritem_"));
  vmingridpropertystrokethicknessitem_->setPropertyId(
      QString::fromLatin1("vmingridpropertystrokethicknessitem_"));
  vmingridpropertystroketypeitem_->setPropertyId(
      QString::fromLatin1("vmingridpropertystroketypeitem_"));

  // Plot3D Canvas properties
  plot3dcanvasthemeitem_->setPropertyId(QString::fromLatin1("plot3dcanvasthemeitem_"));
  plot3dcanvassizeitem_->setPropertyId(QString::fromLatin1("plot3dcanvassizeitem_"));
  plot3dcanvaswindowcoloritem_->setPropertyId(QString::fromLatin1("plot3dcanvaswindowcoloritem_"));
  plot3dcanvasbackgroundvisibleitem_->setPropertyId(
      QString::fromLatin1("plot3dcanvasbackgroundvisibleitem_"));
  plot3dcanvasbackgroundcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dcanvasbackgroundcoloritem_"));
  plot3dcanvasambientlightstrengthitem_->setPropertyId(
      QString::fromLatin1("plot3dcanvasambientlightstrengthitem_"));
  plot3dcanvaslightstrengthitem_->setPropertyId(
      QString::fromLatin1("plot3dcanvaslightstrengthitem_"));
  plot3dcanvaslightcoloritem_->setPropertyId(QString::fromLatin1("plot3dcanvaslightcoloritem_"));
  plot3dcanvasgridvisibleitem_->setPropertyId(QString::fromLatin1("plot3dcanvasgridvisibleitem_"));
  plot3dcanvasgridcoloritem_->setPropertyId(QString::fromLatin1("plot3dcanvasgridcoloritem_"));
  plot3dcanvasfontitem_->setPropertyId(QString::fromLatin1("plot3dcanvasfontitem_"));
  plot3dcanvaslabelbackgroundvisibleitem_->setPropertyId(
      QString::fromLatin1("plot3dcanvaslabelbackgroundvisibleitem_"));
  plot3dcanvaslabelbackgroundcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dcanvaslabelbackgroundcoloritem_"));
  plot3dcanvaslabelbordervisibleitem_->setPropertyId(
      QString::fromLatin1("plot3dcanvaslabelbordervisibleitem_"));
  plot3dcanvaslabeltextcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dcanvaslabeltextcoloritem_"));

  // Plot3d value axis
  plot3daxisvalueautoadjustrangeitem_->setPropertyId(
      QString::fromLatin1("plot3daxisvalueautoadjustrangeitem_"));
  plot3daxisvaluerangeloweritem_->setPropertyId(
      QString::fromLatin1("plot3daxisvaluerangeloweritem_"));
  plot3daxisvaluerangeupperitem_->setPropertyId(
      QString::fromLatin1("plot3daxisvaluerangeupperitem_"));
  plot3dvalueaxislabelformatitem_->setPropertyId(
      QString::fromLatin1("plot3dvalueaxislabelformatitem_"));
  plot3dvalueaxisreverseitem_->setPropertyId(QString::fromLatin1("plot3dvalueaxisreverseitem_"));
  plot3dvalueaxistickcountitem_->setPropertyId(QString::fromLatin1("plot3dvalueaxistickcountitem_"));
  plot3dvalueaxissubtickcountitem_->setPropertyId(
      QString::fromLatin1("plot3dvalueaxissubtickcountitem_"));
  plot3daxisvalueticklabelrotationitem_->setPropertyId(
      QString::fromLatin1("plot3daxisvalueticklabelrotationitem_"));
  plot3daxisvaluetitlevisibleitem_->setPropertyId(
      QString::fromLatin1("plot3daxisvaluetitlevisibleitem_"));
  plot3daxisvaluetitlefixeditem_->setPropertyId(
      QString::fromLatin1("plot3daxisvaluetitlefixeditem_"));
  plot3daxisvaluetitletextitem_->setPropertyId(QString::fromLatin1("plot3daxisvaluetitletextitem_"));

  // Plot3d catagory axis
  plot3daxiscatagoryautoadjustrangeitem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagoryautoadjustrangeitem_"));
  plot3daxiscatagoryrangeloweritem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagoryrangeloweritem_"));
  plot3daxiscatagoryrangeupperitem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagoryrangeupperitem_"));
  plot3daxiscatagoryticklabelrotationitem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagoryticklabelrotationitem_"));
  plot3daxiscatagorytitlevisibleitem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagorytitlevisibleitem_"));
  plot3daxiscatagorytitlefixeditem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagorytitlefixeditem_"));
  plot3daxiscatagorytitletextitem_->setPropertyId(
      QString::fromLatin1("plot3daxiscatagorytitletextitem_"));

  // Plot3D Surface
  plot3dsurfacefliphorizontalgriditem_->setPropertyId(
      QString::fromLatin1("plot3dsurfacefliphorizontalgriditem_"));
  plot3dsurfaceaspectratioitem_->setPropertyId(QString::fromLatin1("plot3dsurfaceaspectratioitem_"));
  plot3dsurfacehorizontalaspectratioitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfacehorizontalaspectratioitem_"));
  plot3dsurfaceshadowqualityitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceshadowqualityitem_"));
  plot3dsurfaceorthoprojectionstatusitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceorthoprojectionstatusitem_"));
  plot3dsurfacepolarstatusitem_->setPropertyId(QString::fromLatin1("plot3dsurfacepolarstatusitem_"));
  // plot3D Bar
  plot3dbarspacingxitem_->setPropertyId(QString::fromLatin1("plot3dbarspacingxitem_"));
  plot3dbarspacingyitem_->setPropertyId(QString::fromLatin1("plot3dbarspacingyitem_"));
  plot3dbarspacingrelativeitem_->setPropertyId(QString::fromLatin1("plot3dbarspacingrelativeitem_"));
  plot3dbarthicknessitem_->setPropertyId(QString::fromLatin1("plot3dbarthicknessitem_"));
  plot3dbaraspectratioitem_->setPropertyId(QString::fromLatin1("plot3dbaraspectratioitem_"));
  plot3dbarhorizontalaspectratioitem_->setPropertyId(
      QString::fromLatin1("plot3dbarhorizontalaspectratioitem_"));
  plot3dbarshadowqualityitem_->setPropertyId(QString::fromLatin1("plot3dbarshadowqualityitem_"));
  plot3dbarorthoprojectionstatusitem_->setPropertyId(
      QString::fromLatin1("plot3dbarorthoprojectionstatusitem_"));
  plot3dbarpolarstatusitem_->setPropertyId(QString::fromLatin1("plot3dbarpolarstatusitem_"));
  // Plot3D Scatter
  plot3dscatteraspectratioitem_->setPropertyId(
      QString::fromLatin1("plot3dscatteraspectratioitem_"));
  plot3dscatterhorizontalaspectratioitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterhorizontalaspectratioitem_"));
  plot3dscattershadowqualityitem_->setPropertyId(
      QString::fromLatin1("plot3dscattershadowqualityitem_"));
  plot3dscatterorthoprojectionstatusitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterorthoprojectionstatusitem_"));
  plot3dscatterpolarstatusitem_->setPropertyId(QString::fromLatin1("plot3dscatterpolarstatusitem_"));
  // Plot3D Surface Series
  plot3dsurfaceseriesvisibleitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriesvisibleitem_"));
  plot3dsurfaceseriesflatshadingstatusitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriesflatshadingstatusitem_"));
  plot3dsurfaceseriesdrawitem_->setPropertyId(QString::fromLatin1("plot3dsurfaceseriesdrawitem_"));
  plot3dsurfaceseriesmeshsmoothitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriesmeshsmoothitem_"));
  plot3dsurfaceseriescolorstyleitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriescolorstyleitem_"));
  plot3dsurfaceseriesbasecoloritem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriesbasecoloritem_"));
  plot3dsurfaceseriesbasegradiantitem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceseriesbasegradiantitem_"));
  plot3dsurfaceserieshighlightcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dsurfaceserieshighlightcoloritem_"));
  // Plot3D Bar Series
  plot3dbarseriesvisibleitem_->setPropertyId(QString::fromLatin1("plot3dbarseriesvisibleitem_"));
  plot3dbarseriesmeshitem_->setPropertyId(QString::fromLatin1("plot3dbarseriesmeshitem_"));
  plot3dbarseriesmeshsmoothitem_->setPropertyId(
      QString::fromLatin1("plot3dbarseriesmeshsmoothitem_"));
  plot3dbarseriescolorstyleitem_->setPropertyId(
      QString::fromLatin1("plot3dbarseriescolorstyleitem_"));
  plot3dbarseriesbasecoloritem_->setPropertyId(QString::fromLatin1("plot3dbarseriesbasecoloritem_"));
  plot3dbarseriesbasegradiantitem_->setPropertyId(
      QString::fromLatin1("plot3dbarseriesbasegradiantitem_"));
  plot3dbarserieshighlightcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dbarserieshighlightcoloritem_"));
  // Plot3D Scatter Series
  plot3dscatterseriesvisibleitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterseriesvisibleitem_"));
  plot3dscatterseriessizeitem_->setPropertyId(QString::fromLatin1("plot3dscatterseriessizeitem_"));
  plot3dscatterseriesmeshitem_->setPropertyId(QString::fromLatin1("plot3dscatterseriesmeshitem_"));
  plot3dscatterseriesmeshsmoothitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterseriesmeshsmoothitem_"));
  plot3dscatterseriescolorstyleitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterseriescolorstyleitem_"));
  plot3dscatterseriesbasecoloritem_->setPropertyId(
      QString::fromLatin1("plot3dscatterseriesbasecoloritem_"));
  plot3dscatterseriesbasegradiantitem_->setPropertyId(
      QString::fromLatin1("plot3dscatterseriesbasegradiantitem_"));
  plot3dscatterserieshighlightcoloritem_->setPropertyId(
      QString::fromLatin1("plot3dscatterserieshighlightcoloritem_"));

  // Table
  tablewindowrowcountitem_->setPropertyId(QString::fromLatin1("tablewindowrowcountitem_"));
  tablewindowcolcountitem_->setPropertyId(QString::fromLatin1("tablewindowcolcountitem_"));
  // Matrix
  matrixwindowrowcountitem_->setPropertyId(QString::fromLatin1("matrixwindowrowcountitem_"));
  matrixwindowcolcountitem_->setPropertyId(QString::fromLatin1("matrixwindowcolcountitem_"));
}

void PlotPropertyEditor::blockManagers(bool value) {
  groupManager_->blockSignals(value);
  boolManager_->blockSignals(value);
  intManager_->blockSignals(value);
  doubleManager_->blockSignals(value);
  stringManager_->blockSignals(value);
  sizeManager_->blockSignals(value);
  rectManager_->blockSignals(value);
  enumManager_->blockSignals(value);
  colorManager_->blockSignals(value);
  fontManager_->blockSignals(value);
}

// /**
//  * Sets the strings of the subwidgets using the current language.
//  */
// void PlotPropertyEditor::changeEvent(QEvent* e)
// {
//     if (e->type() == QEvent::LanguageChange) {
//         ui_->retranslateUi(this);
//     }
//     else {
//         QWidget::changeEvent(e);
//     }
// }