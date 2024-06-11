
#include "DlgRandomPhasesFromFile.h"
#include <Mod/WindLabPlugins/WindLabPlugin/ui_DlgRandomPhasesFromFile.h>
#include <Mod/WindLabPlugins/WindLabPlugin/RPSRandomPhasesFromFile.h>
#include <App/Application.h>
#include <App/Document.h>

#include <QSignalMapper>
#include <QPushButton>
#include <QFileDialog>
#include <QFileInfo>



using namespace WindLabGui;

/* TRANSLATOR WindLabGui::DlgRandomPhasesFromFile */

DlgRandomPhasesFromFile::DlgRandomPhasesFromFile(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName, QWidget* parent)
	: QWidget(parent), ui(new Ui_DlgRandomPhasesFromFile), _featureName(featureName.getStrValue())
{
	ui->setupUi(this);

    ui->le_working_dir->setText(WorkingDirectory.getValue());
    workingDirectory = "";

    connect(ui->tb_choose_working_dir, &QPushButton::clicked, this, &DlgRandomPhasesFromFile::slotSetWorkingDirectory);
}

/*
 *  Destroys the object and frees any allocated resources
 */
DlgRandomPhasesFromFile::~DlgRandomPhasesFromFile()
{
}

void DlgRandomPhasesFromFile::accept()
{
    auto doc = App::GetApplication().getActiveDocument();
    if(!doc)
	    return;
    WindLab::CRPSRandomPhasesFromFile* activefeature = static_cast<WindLab::CRPSRandomPhasesFromFile*>(doc->getObject(_featureName.c_str()));
    if (!activefeature)
        return;
    activefeature->WorkingDirectory.setValue(ui->le_working_dir->text().toStdString());

  }

void DlgRandomPhasesFromFile::reject()
{

}

void DlgRandomPhasesFromFile::slotSetWorkingDirectory() 
{
  QString filter = "Text files (*.txt)";

  QString fn = QFileDialog::getOpenFileName(0,"Import random phases from file", workingDirectory, filter);
  if (!fn.isEmpty()) {
    QFileInfo fi(fn);
      workingDirectory = fi.absoluteFilePath().toUtf8().constData();
    ui->le_working_dir->setText(workingDirectory);
  }
}
// ----------------------------------------------

/* TRANSLATOR PartGui::DlgRandomPhasesFromFileEdit */

DlgRandomPhasesFromFileEdit::DlgRandomPhasesFromFileEdit(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName)
{
	// create and show dialog for the WindLabFeatures
    widget = new DlgRandomPhasesFromFile(WorkingDirectory, featureName, nullptr);
	taskbox = new Gui::TaskView::TaskBox(QPixmap(), widget->windowTitle(), true, nullptr);
	taskbox->groupLayout()->addWidget(widget);
	Content.push_back(taskbox);

}

DlgRandomPhasesFromFileEdit::~DlgRandomPhasesFromFileEdit()
{
	// automatically deleted in the sub-class
}


QDialogButtonBox::StandardButtons DlgRandomPhasesFromFileEdit::getStandardButtons() const
{
	return QDialogButtonBox::Cancel | QDialogButtonBox::Ok;
}

bool DlgRandomPhasesFromFileEdit::accept()
{ 
	widget->accept();
	return true;
}

bool DlgRandomPhasesFromFileEdit::reject()
{
	widget->reject();
	return true;
}

//#include "moc_DlgRandomPhasesFromFile.cpp"
