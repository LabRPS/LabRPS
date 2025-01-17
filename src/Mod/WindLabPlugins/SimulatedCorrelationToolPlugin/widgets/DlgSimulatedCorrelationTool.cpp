
#include "DlgSimulatedCorrelationTool.h"
#include <Mod/WindLabPlugins/SimulatedCorrelationToolPlugin/ui_DlgSimulatedCorrelationTool.h>
#include <Mod/WindLabPlugins/SimulatedCorrelationToolPlugin/SimulatedCorrelationTool.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgSimulatedCorrelationTool */

DlgSimulatedCorrelationTool::DlgSimulatedCorrelationTool(const App::PropertyInteger& fftPointsNumber, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgSimulatedCorrelationTool), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_NumberOfFFTPoints->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_NumberOfFFTPoints->setValue(fftPointsNumber.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSSimulatedCorrelationTool.png"));

}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgSimulatedCorrelationTool::~DlgSimulatedCorrelationTool()
{
}

void DlgSimulatedCorrelationTool::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::SimulatedCorrelationTool* activefeature = static_cast<WindLab::SimulatedCorrelationTool*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->fftPointsNumber.setValue(ui->doubleSpinBox_NumberOfFFTPoints->value().getValue());

  }

void DlgSimulatedCorrelationTool::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgSimulatedCorrelationToolEdit */

DlgSimulatedCorrelationToolEdit::DlgSimulatedCorrelationToolEdit(const App::PropertyInteger& fftPointsNumber, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgSimulatedCorrelationTool(fftPointsNumber,featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgSimulatedCorrelationToolEdit::~DlgSimulatedCorrelationToolEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgSimulatedCorrelationToolEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgSimulatedCorrelationToolEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgSimulatedCorrelationToolEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgSimulatedCorrelationTool.cpp"
