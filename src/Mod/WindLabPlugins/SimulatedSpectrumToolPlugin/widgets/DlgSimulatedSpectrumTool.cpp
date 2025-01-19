
#include "DlgSimulatedSpectrumTool.h"
#include <Mod/WindLabPlugins/SimulatedSpectrumToolPlugin/ui_DlgSimulatedSpectrumTool.h>
#include <Mod/WindLabPlugins/SimulatedSpectrumToolPlugin/SimulatedSpectrumTool.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgSimulatedSpectrumTool */

DlgSimulatedSpectrumTool::DlgSimulatedSpectrumTool(const App::PropertyInteger& fftPointsNumber, const App::PropertyInteger& WindowLength, const App::PropertyInteger& OverLap, const App::PropertyEnumeration& WindowType, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgSimulatedSpectrumTool), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_NumberOfFFTPoints->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_OverlapLength->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_WindowLength->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_NumberOfFFTPoints->setValue(fftPointsNumber.getValue());
    ui->doubleSpinBox_OverlapLength->setValue(OverLap.getValue());
    ui->doubleSpinBox_WindowLength->setValue(WindowLength.getValue());


    int currentIndex = 0;
    const char** enums = WindowType.getEnums();
    for (int i = 0; i <= WindowType.getEnum().maxValue(); ++i) {
        ui->comboBox->addItem(QString::fromUtf8(enums[i]));

        if (QString::fromUtf8(enums[i]) == WindowType.getValueAsString())
            currentIndex = i;
    }
    ui->comboBox->setCurrentIndex(currentIndex);


    ui->label_Image->setPixmap(QPixmap(":icons/RPSSimulatedSpectrumTool.png"));

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSimulatedSpectrumTool::~DlgSimulatedSpectrumTool()
{
}

void DlgSimulatedSpectrumTool::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::SimulatedSpectrumTool* activefeature = static_cast<WindLab::SimulatedSpectrumTool*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->fftPointsNumber.setValue(ui->doubleSpinBox_NumberOfFFTPoints->value().getValue());
    activefeature->OverLap.setValue(ui->doubleSpinBox_OverlapLength->value().getValue());
    activefeature->WindowLength.setValue(ui->doubleSpinBox_WindowLength->value().getValue());
    activefeature->WindowType.setValue(ui->comboBox->currentText().toUtf8().constData());

  }

void DlgSimulatedSpectrumTool::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSimulatedSpectrumToolEdit */

DlgSimulatedSpectrumToolEdit::DlgSimulatedSpectrumToolEdit(const App::PropertyInteger& fftPointsNumber,  const App::PropertyInteger& WindowLength, const App::PropertyInteger& OverLap, const App::PropertyEnumeration& WindowType, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgSimulatedSpectrumTool(fftPointsNumber, WindowLength,OverLap, WindowType,featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSimulatedSpectrumToolEdit::~DlgSimulatedSpectrumToolEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSimulatedSpectrumToolEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgSimulatedSpectrumToolEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSimulatedSpectrumToolEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSimulatedSpectrumTool.cpp"
