
#include "DlgUniformRandomPhases.h"
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/ui_DlgUniformRandomPhases.h>
#include <Mod/SeismicLabPlugins/SeismicLabPlugin/RPSUniformRandomPhases.h>
#include <QSignalMapper>
#include <App/Application.h>
#include <App/Document.h>


using namespace SeismicLabGui;

/* TRANSLATOR SeismicLabGui::DlgUniformRandomPhases */

DlgUniformRandomPhases::DlgUniformRandomPhases(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgUniformRandomPhases), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->doubleSpinBox_MinValue->setRange(0.00, DBL_MAX);
    ui->doubleSpinBox_MaxValue->setRange(0.00, DBL_MAX);

    ui->doubleSpinBox_MinValue->setValue(MinimumValue.getValue());
    ui->doubleSpinBox_MaxValue->setValue(MaximumValue.getValue());

    ui->label_Image->setPixmap(QPixmap(":icons/RPSUniformRandomPhases.png"));
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgUniformRandomPhases::~DlgUniformRandomPhases()
{
}

void DlgUniformRandomPhases::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    SeismicLab::CRPSUniformRandomPhases* activefeature = static_cast<SeismicLab::CRPSUniformRandomPhases*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->MinimumValue.setValue(ui->doubleSpinBox_MinValue->value().getValue());
    activefeature->MaximumValue.setValue(ui->doubleSpinBox_MaxValue->value().getValue());

  }

void DlgUniformRandomPhases::reject()
{

}


// ----------------------------------------------

/* TRANSLATOR PartGui::DlgUniformRandomPhasesEdit */

DlgUniformRandomPhasesEdit::DlgUniformRandomPhasesEdit(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName)
{
	// create and show dialog for the SeismicLabFeatures
    widget = new DlgUniformRandomPhases(MinimumValue, MaximumValue, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgUniformRandomPhasesEdit::~DlgUniformRandomPhasesEdit()
{
	// automatically deleted in the sub-class
}

QDialogButtonBox::StandardButtons DlgUniformRandomPhasesEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgUniformRandomPhasesEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgUniformRandomPhasesEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgUniformRandomPhases.cpp"
