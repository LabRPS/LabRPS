#include "crpswlruntabletoolsdlg.h"
#include "ui_crpswlruntabletoolsdlg.h"
#include "RPSWindLabAPI.h"
#include "rps/windLab/rpsWindLabSimulation.h"

CRPSWLRunTableToolsDlg::CRPSWLRunTableToolsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRPSWLRunTableToolsDlg)
{
    ui->setupUi(this);
    QString noSelection = "<None>";

    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();

    QString currentTableTool = rpsWindLabSimulator->GetWindLabData().tableTool;


    typedef IrpsWLTableTool *(*CreateTableToolCallback)();
    std::map<const QString, CreateTableToolCallback> ::iterator tableToolIt;

    // Iterate though the map and show all the registed spatial distribution in the combo box
    for (tableToolIt = CrpsTableToolFactory::GetObjectNamesMap().begin(); tableToolIt != CrpsTableToolFactory::GetObjectNamesMap().end(); ++tableToolIt)
    {
        // Add it to the combo box
        ui->comboBoxTools->addItem(tableToolIt->first);

    }

    // Show the current selected randomness
    // Starting index
    int nDex = -1;

    // Search the combo list elements from index 0 until the current selected rp is found, then get its index
    if ((nDex != ui->comboBoxTools->findText(currentTableTool)))
    {
        // Select the corresponding randomness in the combox based on the index
        ui->comboBoxTools->setCurrentText(currentTableTool);
    }
    else if ((nDex == ui->comboBoxTools->findText(noSelection)))
    {
        // Select the none text then
        ui->comboBoxTools->setCurrentText(noSelection);
    }

    connect( ui->comboBoxTools, SIGNAL( currentIndexChanged( int ) ),
             this, SLOT( comboBoxRunToolsIndexChanged( int ) ) );

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptInput()));

    connect( ui->pushButtonTableToolInit, SIGNAL( clicked() ),
              this, SLOT( OnBnClickedTableToolInit( ) ) );


}

CRPSWLRunTableToolsDlg::~CRPSWLRunTableToolsDlg()
{
    delete ui;
}

void CRPSWLRunTableToolsDlg::comboBoxRunToolsIndexChanged(int index)
{
    tableTool = ui->comboBoxTools->currentText();
}

void CRPSWLRunTableToolsDlg::acceptInput()
{
    tableTool = ui->comboBoxTools->currentText();
}

void CRPSWLRunTableToolsDlg::OnBnClickedTableToolInit()
{
    RPSWindLabSimulation *rpsWindLabSimulator = (RPSWindLabSimulation *)this->parent();
    rpsWindLabSimulator->tableToolInital(ui->comboBoxTools->currentText());
}

