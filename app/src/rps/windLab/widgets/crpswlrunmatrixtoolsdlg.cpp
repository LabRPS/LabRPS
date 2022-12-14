#include "crpswlrunmatrixtoolsdlg.h"
#include "ui_crpswlrunmatrixtoolsdlg.h"
#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"

CRPSWLRunMatrixToolsDlg::CRPSWLRunMatrixToolsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRPSWLRunMatrixToolsDlg)
{
    ui->setupUi(this);

    QString noSelection = "<None>";

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    QString currentMatrixTool = rpsWindLabSimulator->GetWindLabData().matrixTool;

    typedef IrpsWLMatrixTool *(*CreateMatrixToolCallback)();
    std::map<const QString, CreateMatrixToolCallback> ::iterator matrixToolIt;

    // Iterate though the map and show all the registed spatial distribution in the combo box
    for (matrixToolIt = CrpsMatrixToolFactory::GetObjectNamesMap().begin(); matrixToolIt != CrpsMatrixToolFactory::GetObjectNamesMap().end(); ++matrixToolIt)
    {
        // Add it to the combo box
        ui->comboBoxTools->addItem(matrixToolIt->first);

    }

    // Show the current selected randomness
    // Starting index
    int nDex = -1;

    // Search the combo list elements from index 0 until the current selected rp is found, then get its index
    if ((nDex != ui->comboBoxTools->findText(currentMatrixTool)))
    {
        // Select the corresponding randomness in the combox based on the index
        ui->comboBoxTools->setCurrentText(currentMatrixTool);
    }
    else if ((nDex == ui->comboBoxTools->findText(noSelection)))
    {
        // Select the none text then
        ui->comboBoxTools->setCurrentText(noSelection);
    }

    connect( ui->comboBoxTools, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxRunToolsIndexChanged( int ) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

    connect( ui->pushButtonMatrixToolInit, SIGNAL( clicked() ),
              this, SLOT( OnBnClickedMatrixToolInit( ) ) );

}

CRPSWLRunMatrixToolsDlg::~CRPSWLRunMatrixToolsDlg()
{
    delete ui;
}

void CRPSWLRunMatrixToolsDlg::comboBoxRunToolsIndexChanged(int index)
{
    matrixTool = ui->comboBoxTools->currentText();
}

void CRPSWLRunMatrixToolsDlg::acceptInput()
{
    matrixTool = ui->comboBoxTools->currentText();

}

void CRPSWLRunMatrixToolsDlg::OnBnClickedMatrixToolInit()
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    rpsWindLabSimulator->matrixToolInital(ui->comboBoxTools->currentText());
}
