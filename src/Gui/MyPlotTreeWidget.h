#ifndef MYTREEWIDGET_H
#define MYTREEWIDGET_H
#include <RPSGlobal.h>

#include <QMenu>
#include <QMouseEvent>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "Libraries/Alphaplot/3rdparty/qcustomplot/qcustomplot.h"

class Layout2D;
class AxisRect2D;
class MyWidget;
class QCustomPlot;

//namespace Gui {


    class GuiExport MyPlotTreeWidget : public QTreeWidget {
        Q_OBJECT

    public:
        enum class PropertyItemType : int {
            MyWidgetWindow = 0,
            Plot2DCanvas = 1,
            Plot2DLayout = 2,
            Plot2DGrid = 3,
            Plot2DAxis = 4,
            Plot2DLegend = 5,
            Plot2DTextItem = 6,
            Plot2DLineItem = 7,
            Plot2DImageItem = 8,
            Plot2DLSGraph = 9,
            Plot2DChannelGraph = 10,
            Plot2DCurve = 11,
            Plot2DStatBox = 12,
            Plot2DVector = 13,
            Plot2DBarGraph = 14,
            Plot2DPieGraph = 15,
            Plot2DColorMap = 16,
            Plot2DErrorBar = 17,
            Plot3DCanvas = 18,
            Plot3DTheme = 19,
            Plot3DAxisValue = 20,
            Plot3DAxisCatagory = 21,
            Plot3DSurface = 22,
            Plot3DBar = 23,
            Plot3DScatter = 24,
            Plot3DSurfaceDataBlock = 25,
            Plot3DBarDataBlock = 26,
            Plot3DScatterDataBlock = 27,
            TableWindow = 28,
            MatrixWindow = 29,
        };

        enum class WindLabObjectPropertyItemType : int {
            WindLabPlugin = 0,
            WindLabLocationDistribution = 1,
            WindLabMeanProfile = 2,
            WindLabXSpectrumModel = 3,
            WindLabYSpectrumModel = 4,
            WindLabZSpectrumModel = 5,
            WindLabSpectrumDecompositionMethod = 6,
            WindLabCoherence = 7,
            WindLabSimulationMethod = 8,
            WindLabFrequencyDistribution = 9,
            WindLabRandomness = 10,
            WindLabModulationFunction = 11,
            WindLabCorrelationFunction = 12,
            WindLabTableTool = 13,
            WindLabMatrixTool = 14,
            WindLabUserDefinedRPSObject = 15,
            WindLabCumulativeProbabilityDistribution = 16,
            WindLabGustFactor = 17,
            WindLabKurtosis = 18,
            WindLabPeakFactor = 19,
            WindLabProbabilityDensityFunction = 20,
            WindLabRoughness = 21,
            WindLabShearVelocityOfFlow = 22,
            WindLabSkewness = 23,
            WindLabStandardDeviation = 24,
            WindLabTurbulenceIntensity = 25,
            WindLabTurbulenceScale = 26,
            WindLabVariance = 27,
            WindLabWavePassageEffect = 28,

        };

        enum class SeaLabObjectPropertyItemType : int {
            SeaLabPlugin = 0,

        };

        enum class SeismicLabObjectPropertyItemType : int {
            SeismicLabPlugin = 0,

        };

        enum class UserObjectPropertyItemType : int {
            UserPlugin = 0,
            User = 1,
        };


        enum class DocumentFeaturePropertyItemType : int {
            Simulation = 0,
            WindLabLocationDistribution = 1,
            WindLabMeanProfile = 2,
            WindLabXSpectrumModel = 3,
            WindLabYSpectrumModel = 4,
            WindLabZSpectrumModel = 5,
            WindLabSpectrumDecompositionMethod = 6,
            WindLabCoherence = 7,
            WindLabSimulationMethod = 8,
            WindLabFrequencyDistribution = 9,
            WindLabRandomness = 10,
            WindLabModulationFunction = 11,
            WindLabCorrelationFunction = 12,
            WindLabTableTool = 13,
            WindLabMatrixTool = 14,
            WindLabUserDefinedRPSObject = 15,
            WindLabCumulativeProbabilityDistribution = 16,
            WindLabGustFactor = 17,
            WindLabKurtosis = 18,
            WindLabPeakFactor = 19,
            WindLabProbabilityDensityFunction = 20,
            WindLabRoughness = 21,
            WindLabShearVelocityOfFlow = 22,
            WindLabSkewness = 23,
            WindLabStandardDeviation = 24,
            WindLabTurbulenceIntensity = 25,
            WindLabTurbulenceScale = 26,
            WindLabVariance = 27,
            WindLabWavePassageEffect = 28,
            Document = 29,
            WindLabFeature = 30,


        };



        MyPlotTreeWidget(QWidget* parent = nullptr);
        ~MyPlotTreeWidget();

    Q_SIGNALS:
        void activate(MyWidget* widget);
        void itemRootContextMenuRequested();
        void itemContextMenuRequested(Layout2D* layout, AxisRect2D* axisrect);

    private Q_SLOTS:
        void CurrentItemChanged(QTreeWidgetItem* current);
        void showContextMenu(const QPoint& pos);
        void reorderlegend();
        void cloneAxis2D();
        void removeAxis2D();
        void removeLineSpecial2D();
        void removeLineSpecialChannel2D();
        void removeCurve2D();
        void removeBar2D();
        void removeVector2D();
        void removeStatBox2D();
        void removePie2D();
        void removeErrorBar2D();
        void removeTextItem2D();
        void removeLineItem2D();
        void removeImageItem2D();

    private:
        void showFunction2dDetails();
        void showFunction3dDetails();
        template <class T>
        void moveplottablelayer(QAction* action,
            const QCustomPlot::LayerInsertMode& mode);
        template <class T>
        void moveitemlayer(QAction* action, const QCustomPlot::LayerInsertMode& mode);
        void selectData(QAction* action);


    private:
        QWidget* widget_;
        // Show function
        QAction* showfunctiondetailscurve2d_;
        QAction* showfunctiondetailssurface3d_;
        // slect data
        QAction* selectdatacolumnslsgraph2d_;
        QAction* selectdatacolumnschannelgraph2d_;
        QAction* selectdatacolumnscurvegraph2d_;
        QAction* selectdatacolumnsbargraph2d_;
        QAction* selectdatacolumnsvectorgraph2d_;
        QAction* selectdatacolumnsstatboxgraph2d_;
        QAction* selectdatacolumnserrorgraph2d_;
        QAction* selectdatacolumnspiegraph2d_;
        QAction* selectdatacolumnscolormapgraph2d_;
        // legend order
        QAction* legendreorder_;
        // Remove
        QAction* removeaxis_;
        QAction* removels_;
        QAction* removechannel_;
        QAction* removecurve_;
        QAction* removebar_;
        QAction* removevector_;
        QAction* removestatbox_;
        QAction* removepie_;
        QAction* removeerrorbar_;
        QAction* removetextitem_;
        QAction* removelineitem_;
        QAction* removeimageitem_;
        //  clone axis
        QAction* clonetotopaxis_;
        QAction* clonetobottomaxis_;
        QAction* clonetoleftaxis_;
        QAction* clonetorightaxis_;
        // move layer up
        QAction* moveupls_;
        QAction* moveupchannel_;
        QAction* moveupcurve_;
        QAction* moveupbar_;
        QAction* moveupvector_;
        QAction* moveupstatbox_;
        QAction* moveuppie_;
        QAction* moveupcolormap_;
        QAction* moveuptextitem_;
        QAction* moveuplineitem_;
        QAction* moveupimageitem_;
        // move layer down
        QAction* movedownls_;
        QAction* movedownchannel_;
        QAction* movedowncurve_;
        QAction* movedownbar_;
        QAction* movedownvector_;
        QAction* movedownstatbox_;
        QAction* movedownpie_;
        QAction* movedowncolormap_;
        QAction* movedowntextitem_;
        QAction* movedownlineitem_;
        QAction* movedownimageitem_;
    };


//} //namespace Gui

#endif  // MYTREEWIDGET_H
