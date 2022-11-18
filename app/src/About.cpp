#include "About.h"

#include "core/IconLoader.h"
#include "core/Utilities.h"
#include "globals.h"

About::About(QWidget* parent) : QDialog(parent) {
  ui_.setupUi(this);
  setWindowIcon(IconLoader::load("help-about", IconLoader::LightDark));

  ui_.gridLayout->setContentsMargins(0, 0, 0, 0);
  ui_.verticalLayout_2->setSpacing(0);
  ui_.verticalLayout_2->setContentsMargins(0, 0, 0, 0);
  ui_.horizontalLayout->setContentsMargins(0, 10, 0, 10);
  ui_.horizontalLayout->setSpacing(10);
  ui_.verticalLayout->setContentsMargins(0, 0, 0, 0);
  ui_.verticalLayout->setSpacing(0);

  ui_.versionLabel->setText(LabRPS::versionString() + "-" +
                            LabRPS::extraVersion());
  ui_.releaseDateLabel->setText(LabRPS::releaseDateString());
  ui_.buildLabel->setText(QSysInfo::buildCpuArchitecture());

  ui_.buildLabel->setVisible(false);
  ui_.buildLabelCaption->setVisible(false);
  ui_.originalAuthorLabel->setText(LabRPS::originalAuthor());
  ui_.osLabel->setText(QString("%1 %2-bit")
                           .arg(QSysInfo::prettyProductName(),
                                QSysInfo::currentCpuArchitecture()));
}
