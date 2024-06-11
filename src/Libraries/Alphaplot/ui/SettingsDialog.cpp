#include <PreCompiled.h>

#include "SettingsDialog.h"

#include <QDebug>
#include <QStandardItem>
#include <QStandardItemModel>

#include "core/IconLoader.h"
#include "widgets/aSettingsListView.h"
#include "FittingSettings.h"
#include "GeneralApplicationSettings.h"
#include "GeneralAppreanceSettings.h"
#include "GeneralConfirmationSettings.h"
#include "GeneralNumericFormatSettings.h"
#include "SettingsPage.h"
#include "TableBasicSettings.h"
#include "TableColorSettings.h"
#include "TableFontSettings.h"
#include "ui_SettingsDialog.h"

# include <QScrollArea>
# include <QScrollBar>
# include <QApplication>
# include <QScreen>


const int SettingsDialog::GroupNameRole = Qt::UserRole;

/* TRANSLATOR Gui::Dialog::SettingsDialog */

std::list<SettingsDialog::TGroupPages> SettingsDialog::_pages;
SettingsDialog* SettingsDialog::_activeDialog = nullptr;

/**
 *  Constructs a SettingsDialog which is a child of 'parent', with
 *  widget flags set to 'fl'
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
SettingsDialog::SettingsDialog(QWidget* parent, Qt::WindowFlags fl)
    : QDialog(parent, fl), ui(new Ui_SettingsDialog),
      invalidParameter(false), canEmbedScrollArea(true)
{
    ui->setupUi(this);
    ui->listBox->setFixedWidth(108);
    ui->listBox->setGridSize(QSize(108, 75));

//    connect(ui->buttonBox,  SIGNAL (helpRequested()),
//            getMainWindow(), SLOT (whatsThis()));
    connect(ui->listBox, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
            this, SLOT(changeGroup(QListWidgetItem *, QListWidgetItem*)));

    setupPages();

    // Maintain a static pointer to the current active dialog (if there is one) so that
    // if the static page manipulation functions are called while the dialog is showing
    // it can update its content.
    SettingsDialog::_activeDialog = this;

  }

/**
 *  Destroys the object and frees any allocated resources.
 */
SettingsDialog::~SettingsDialog()
{
    if (SettingsDialog::_activeDialog == this) {
        SettingsDialog::_activeDialog = nullptr;
    }
}

void SettingsDialog::setupPages()
{
    ApplicationSettingsPage* generalapplicationsettings = new ApplicationSettingsPage(this);
    GeneralConfirmationSettings* generalconfirmationsettings = new GeneralConfirmationSettings(this);
    GeneralAppreanceSettings* generalappearancesettings = new GeneralAppreanceSettings(this);
    GeneralNumericFormatSettings* generalnumericformatsettings = new GeneralNumericFormatSettings(this);
    TableBasicSettings* tablebasicsettings = new TableBasicSettings(this);
    TableColorSettings* tablecolorsettings = new TableColorSettings(this);
    TableFontSettings* tablefontsettings = new TableFontSettings(this);
    FittingSettings* fittingsettings = new FittingSettings(this);


    QTabWidget* generalGroupTab = createTabForGroup("General");
    QTabWidget* tableGroupTab = createTabForGroup("Table");
    QTabWidget* FittingGroupTab = createTabForGroup("Fitting");

    generalapplicationsettings->setProperty("GroupName", generalGroupTab->property("GroupName"));
    generalconfirmationsettings->setProperty("GroupName", generalGroupTab->property("GroupName"));
    generalappearancesettings->setProperty("GroupName", generalGroupTab->property("GroupName"));
    generalnumericformatsettings->setProperty("GroupName", generalGroupTab->property("GroupName"));

    tablebasicsettings->setProperty("GroupName", tableGroupTab->property("GroupName"));
    generalapplicationsettings->setProperty("GroupName", tableGroupTab->property("GroupName"));
    tablefontsettings->setProperty("GroupName", tableGroupTab->property("GroupName"));

    fittingsettings->setProperty("GroupName", FittingGroupTab->property("GroupName"));


    generalGroupTab->addTab(generalapplicationsettings, generalapplicationsettings->windowTitle());
    generalGroupTab->addTab(generalconfirmationsettings, generalconfirmationsettings->windowTitle());
    generalGroupTab->addTab(generalappearancesettings, generalappearancesettings->windowTitle());
    generalGroupTab->addTab(generalnumericformatsettings, generalnumericformatsettings->windowTitle());

    tableGroupTab->addTab(tablebasicsettings, tablebasicsettings->windowTitle());
    tableGroupTab->addTab(tablecolorsettings, tablecolorsettings->windowTitle());
    tableGroupTab->addTab(tablefontsettings, tablefontsettings->windowTitle());

    FittingGroupTab->addTab(fittingsettings, fittingsettings->windowTitle());


    // show the first group
    ui->listBox->setCurrentRow(0);

    connect(generalapplicationsettings,
            &ApplicationSettingsPage::generalapplicationsettingsupdate, this,
            &SettingsDialog::generalapplicationsettingsupdates);
    connect(generalconfirmationsettings,
            &GeneralConfirmationSettings::generalconfirmationsettingsupdate, this,
            &SettingsDialog::generalconfirmationsettingsupdates);
    connect(generalappearancesettings,
            &GeneralAppreanceSettings::generalappreancesettingsupdate, this,
            &SettingsDialog::generalappreancesettingsupdates);

    connect(generalnumericformatsettings,
            &GeneralNumericFormatSettings::generalnumericformatsettingsupdate,
            this, &SettingsDialog::generalnumericformatsettingsupdates);
    connect(tablebasicsettings, &TableBasicSettings::tablebasicsettingsupdate,
            this, &SettingsDialog::tablebasicsettingsupdates);
    connect(tablecolorsettings, &TableColorSettings::tablecolorsettingsupdate,
            this, &SettingsDialog::tablecolorsettingsupdates);
    connect(tablefontsettings, &TableFontSettings::tablefontsettingsupdate, this,
            &SettingsDialog::tablefontsettingsupdates);
    connect(fittingsettings, &FittingSettings::fittingsettingsupdate, this,
            &SettingsDialog::fittingsettingsupdates);

}

/**
 * Create the necessary widgets for a new group named \a groupName. Returns a
 * pointer to the group's QTabWidget: that widget's lifetime is managed by the
 * tabWidgetStack, do not manually deallocate.
 */
QTabWidget* SettingsDialog::createTabForGroup(const std::string &groupName)
{
    QString groupNameQString = QString::fromStdString(groupName);

    QTabWidget* tabWidget = new QTabWidget;
    ui->tabWidgetStack->addWidget(tabWidget);
    tabWidget->setProperty("GroupName", QVariant(groupNameQString));

    QListWidgetItem* item = new QListWidgetItem(ui->listBox);
    item->setData(GroupNameRole, QVariant(groupNameQString));
    item->setText(QObject::tr(groupNameQString.toLatin1()));
    item->setToolTip(QObject::tr(groupNameQString.toLatin1()));
    std::string fileName = groupName;
    for (auto & ch : fileName) {
        if (ch == ' ') ch = '_';
        else ch = tolower(ch);
    }
    fileName = std::string("labrps-preferences-") + fileName;

    item->setIcon(IconLoader::load(QString::fromLatin1(fileName.c_str()), IconLoader::General));
    item->setTextAlignment(Qt::AlignHCenter);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    return tabWidget;
}

/**
 * Create a new preference page called \a pageName on the group tab \a tabWidget.
 */
void SettingsDialog::createPageInGroup(QTabWidget *tabWidget, const std::string &pageName)
{

}

void SettingsDialog::changeGroup(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    ui->tabWidgetStack->setCurrentIndex(ui->listBox->row(current));
}

/**
 * Adds a preference page with its class name \a className and
 * the group \a group it belongs to. To create this page it must
 * be registered in the WidgetFactory.
 * @see WidgetFactory
 * @see PrefPageProducer
 */
void SettingsDialog::addPage(const std::string& className, const std::string& group)
{
    std::list<TGroupPages>::iterator groupToAddTo = _pages.end();
    for (std::list<TGroupPages>::iterator it = _pages.begin(); it != _pages.end(); ++it) {
        if (it->first == group) {
            groupToAddTo = it;
            break;
        }
    }

    if (groupToAddTo != _pages.end()) {
        // The group exists: add this page to the end of the list
        groupToAddTo->second.push_back(className);
    }
    else {
        // This is a new group: create it, with its one page
        std::list<std::string> pages;
        pages.push_back(className);
        _pages.push_back(std::make_pair(group, pages));
    }

    if (SettingsDialog::_activeDialog != nullptr) {
        // If the dialog is currently showing, tell it to insert the new page
        _activeDialog->reloadPages();
    }
}

void SettingsDialog::removePage(const std::string& className, const std::string& group)
{
    for (std::list<TGroupPages>::iterator it = _pages.begin(); it != _pages.end(); ++it) {
        if (it->first == group) {
            if (className.empty()) {
                _pages.erase(it);
                return;
            }
            else {
                std::list<std::string>& p = it->second;
                for (std::list<std::string>::iterator jt = p.begin(); jt != p.end(); ++jt) {
                    if (*jt == className) {
                        p.erase(jt);
                        if (p.empty())
                            _pages.erase(it);
                        return;
                    }
                }
            }
        }
    }
}

/**
 * Activates the page at position \a index of the group with name \a group.
 */
void SettingsDialog::activateGroupPage(const QString& group, int index)
{
    int ct = ui->listBox->count();
    for (int i=0; i<ct; i++) {
        QListWidgetItem* item = ui->listBox->item(i);
        if (item->data(GroupNameRole).toString() == group) {
            ui->listBox->setCurrentItem(item);
            QTabWidget* tabWidget = (QTabWidget*)ui->tabWidgetStack->widget(i);
            tabWidget->setCurrentIndex(index);
            break;
        }
    }
}

void SettingsDialog::accept()
{
    this->invalidParameter = false;
    applyChanges();
    if (!this->invalidParameter)
        QDialog::accept();
}

void SettingsDialog::on_buttonBox_clicked(QAbstractButton* btn)
{
    if (ui->buttonBox->standardButton(btn) == QDialogButtonBox::Apply)
        applyChanges();
    else if (ui->buttonBox->standardButton(btn) == QDialogButtonBox::Reset)
        restoreDefaults();
    else if (ui->buttonBox->standardButton(btn) == QDialogButtonBox::Close)
        this->close();
}

void SettingsDialog::restoreDefaults()
{

}

/**
 * If the dialog is currently showing and the static variable _pages changed, this function
 * will rescan that list of pages and add any that are new to the current dialog. It will not
 * remove any pages that are no longer in the list, and will not change the user's current
 * active page.
 */
void SettingsDialog::reloadPages()
{
     for (const auto &group : _pages) {
        QString groupName = QString::fromStdString(group.first);

        // First, does this group already exist?
        QTabWidget* tabWidget = nullptr;
        for (int tabNumber = 0; tabNumber < ui->tabWidgetStack->count(); ++tabNumber) {
            auto thisTabWidget = qobject_cast<QTabWidget*>(ui->tabWidgetStack->widget(tabNumber));
            if (thisTabWidget->property("GroupName").toString() == groupName) {
                tabWidget = thisTabWidget;
                break;
            }
        }

        // This is a new tab that wasn't there when we started this instance of the dialog:
        if (!tabWidget) {
            tabWidget = createTabForGroup(group.first);
        }

        // Move on to the pages in the group to see if we need to add any
        for (const auto& page : group.second) {

            // Does this page already exist?
            QString pageName = QString::fromStdString(page);
            bool pageExists = false;
            for (int pageNumber = 0; pageNumber < tabWidget->count(); ++pageNumber) {
                SettingsPage* prefPage = qobject_cast<SettingsPage*>(tabWidget->widget(pageNumber));
                if (prefPage && prefPage->property("PageName").toString() == pageName) {
                    pageExists = true;
                    break;
                }
            }

            // This is a new page that wasn't there when we started this instance of the dialog:
            if (!pageExists) {
                createPageInGroup(tabWidget, page);
            }
        }
    }
}

void SettingsDialog::applyChanges()
{

}

void SettingsDialog::showEvent(QShowEvent* ev)
{
    //canEmbedScrollArea = false;
    this->adjustSize();
    QDialog::showEvent(ev);
}

void SettingsDialog::resizeEvent(QResizeEvent* ev)
{
    if (canEmbedScrollArea) {
        // embed the widget stack into a scroll area if the size is
        // bigger than the available desktop
        QRect rect = QApplication::primaryScreen()->availableGeometry();
        int maxHeight = rect.height() - 60;
        int maxWidth = rect.width();
        if (height() > maxHeight || width() > maxWidth) {
            canEmbedScrollArea = false;
            ui->hboxLayout->removeWidget(ui->tabWidgetStack);
            QScrollArea* scrollArea = new QScrollArea(this);
            scrollArea->setFrameShape(QFrame::NoFrame);
            scrollArea->setWidgetResizable(true);
            scrollArea->setWidget(ui->tabWidgetStack);
            ui->hboxLayout->addWidget(scrollArea);

            // if possible the minimum width should so that it doesn't show
            // a horizontal scroll bar.
            QScrollBar* bar = scrollArea->verticalScrollBar();
            if (bar) {
                int newWidth = width() + bar->width();
                newWidth = std::min<int>(newWidth, maxWidth);
                int newHeight = std::min<int>(height(), maxHeight);
                QMetaObject::invokeMethod(this, "resizeWindow",
                    Qt::QueuedConnection,
                    QGenericReturnArgument(),
                    Q_ARG(int, newWidth),
                    Q_ARG(int, newHeight));
            }
            QPoint center = rect.center();
            move(center.x() - width() * 0.5, 10);
        }
    }
    QDialog::resizeEvent(ev);
}

void SettingsDialog::resizeWindow(int w, int h)
{
    resize(w, h);
}

void SettingsDialog::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
        // update the widgets' tabs
        for (int i=0; i<ui->tabWidgetStack->count(); i++) {
            QTabWidget* tabWidget = (QTabWidget*)ui->tabWidgetStack->widget(i);
            for (int j=0; j<tabWidget->count(); j++) {
                QWidget* page = tabWidget->widget(j);
                tabWidget->setTabText(j, page->windowTitle());
            }
        }
        // update the items' text
        for (int i=0; i<ui->listBox->count(); i++) {
            QListWidgetItem *item = ui->listBox->item(i);
            QByteArray group = item->data(GroupNameRole).toByteArray();
            item->setText(QObject::tr(group.constData()));
        }
    } else {
        QWidget::changeEvent(e);
    }
}

void SettingsDialog::reload()
{
    for (int i = 0; i < ui->tabWidgetStack->count(); i++) {
        QTabWidget* tabWidget = (QTabWidget*)ui->tabWidgetStack->widget(i);
        for (int j = 0; j < tabWidget->count(); j++) {
//            PreferencePage* page = qobject_cast<PreferencePage*>(tabWidget->widget(j));
//            if (page)
//                page->loadSettings();
        }
    }
    applyChanges();
}
/////////////////////////////////////////////////////////////////////////////

//SettingsDialog::SettingsDialog(QWidget* parent)
//    : QDialog(parent),
//      ui_(new Ui_SettingsDialog),
//      settingsViewMenu_(new QMenu(this)),
//      settingsViewGroup_(new QActionGroup(this)),
//      treeView_(new QAction(this)),
//      iconView_(new QAction(this)),
//      generalSettingsModel_(new QStandardItemModel(this)),
//      tableSettingsModel_(new QStandardItemModel(this)),
//      plot2dSettingsModel_(new QStandardItemModel(this)),
//      plot3dSettingsModel_(new QStandardItemModel(this)),
//      fittingSettingsModel_(new QStandardItemModel(this)),
//      scriptingSettingsModel_(new QStandardItemModel(this)) {
//  ui_->setupUi(this);
//  setWindowTitle(tr("Settings"));
//  setWindowIcon(IconLoader::load("edit-preference", IconLoader::LightDark));
//  setModal(true);
//  setMinimumSize(sizeHint());

//  // Colors (TODO: use some central qpalette handling)
//  baseColor_ = qApp->palette().color(QPalette::Base);
//  fontColor_ = qApp->palette().color(QPalette::Text);

//  // adjust layout spacing & margins.
//  ui_->settingGridLayout->setSpacing(3);
//  ui_->settingGridLayout->setContentsMargins(0, 0, 0, 0);
//  ui_->headerHorizontalLayout->setSpacing(0);
//  ui_->scrollVerticalLayout->setSpacing(0);
//  ui_->scrollVerticalLayout->setContentsMargins(3, 3, 3, 3);
//  ui_->scrollVerticalLayout->setContentsMargins(0, 0, 0, 0);
//  ui_->stackGridLayout->setSpacing(0);
//  ui_->stackGridLayout->setContentsMargins(0, 0, 0, 0);
//  ui_->scrollAreaWidgetContents->setContentsMargins(0, 0, 0, 0);
//  // ui_->scrollAreaWidgetContents->setSpacing(0);

//  // Setup search box.
//  // ui_->searchBox->setMaximumWidth(300);
//  // ui_->searchBox->setToolTip(tr("search"));

//  // Prepare buttons
//  ui_->settingsButton->setIcon(
//      IconLoader::load("go-previous", IconLoader::LightDark));
//  ui_->settingsButton->setEnabled(false);

//  // Add settings configure menu items(tree/icon view)
//  settingsViewGroup_->addAction(treeView_);
//  settingsViewGroup_->addAction(iconView_);
//  treeView_->setText(tr("Tree view"));
//  iconView_->setText(tr("Icon view"));
//  treeView_->setCheckable(true);
//  iconView_->setCheckable(true);
//  settingsViewMenu_->addAction(treeView_);
//  settingsViewMenu_->addAction(iconView_);

//  // Prepare scrollarea.
//  QString scrollbackcol =
//      ".QScrollArea {border: 0; background-color: rgba(%1,%2,%3,%4);}";
//  ui_->scrollArea->setStyleSheet(scrollbackcol.arg(baseColor_.red())
//                                     .arg(baseColor_.green())
//                                     .arg(baseColor_.blue())
//                                     .arg(baseColor_.alpha()));
//  ui_->settingsButton->setStyleSheet(
//      "QPushButton {background-color : rgba(0,0,0,0);border: 0 "
//      "rgba(0,0,0,0);}");

//  // Prepare label.
//  QString label_font_color =
//      "QLabel {background-color : rgba(0,0,0,0);"
//      " padding-left: 10px;"
//      " padding-right: 10px;"
//      " padding-top: 10px;"
//      " padding-bottom: 10px; border: 0 rgba(0,0,0,0);}";
//  ui_->generalLabel->setStyleSheet(label_font_color);
//  ui_->tableLabel->setStyleSheet(label_font_color);
//  ui_->plot2dLabel->setStyleSheet(label_font_color);
//  ui_->plot3dLabel->setStyleSheet(label_font_color);
//  ui_->fittingLabel->setStyleSheet(label_font_color);
//  ui_->scriptingLabel->setStyleSheet(label_font_color);
//  ui_->generalLabel->hide();
//  ui_->tableLabel->hide();
//  ui_->plot2dLabel->hide();
//  ui_->plot3dLabel->hide();
//  ui_->fittingLabel->hide();
//  ui_->scriptingLabel->hide();

//  // Add pages to stack widget
//  // addPage(General, Page_RootSettings, new ApplicationSettingsPage(this));
//  ApplicationSettingsPage* generalapplicationsettings =
//      new ApplicationSettingsPage(this);
//  GeneralConfirmationSettings* generalconfirmationsettings =
//      new GeneralConfirmationSettings(this);
//  GeneralAppreanceSettings* generalappearancesettings =
//      new GeneralAppreanceSettings(this);
//  GeneralNumericFormatSettings* generalnumericformatsettings =
//      new GeneralNumericFormatSettings(this);
//  TableBasicSettings* tablebasicsettings = new TableBasicSettings(this);
//  TableColorSettings* tablecolorsettings = new TableColorSettings(this);
//  TableFontSettings* tablefontsettings = new TableFontSettings(this);
//  FittingSettings* fittingsettings = new FittingSettings(this);
//  addPage(General, Page_GeneralApplication, generalapplicationsettings);
//  addPage(General, Page_GeneralConfirmation, generalconfirmationsettings);
//  addPage(General, Page_GeneralAppearance, generalappearancesettings);
//  addPage(General, Page_GeneralNumericFormat, generalnumericformatsettings);
//  addPage(Table, Page_TableBasic, tablebasicsettings);
//  addPage(Table, Page_TableColor, tablecolorsettings);
//  addPage(Table, Page_TableFont, tablefontsettings);
//  addPage(Fitting, Page_Fitting, fittingsettings);

//  connect(generalapplicationsettings,
//          &ApplicationSettingsPage::generalapplicationsettingsupdate, this,
//          &SettingsDialog::generalapplicationsettingsupdates);
//  connect(generalconfirmationsettings,
//          &GeneralConfirmationSettings::generalconfirmationsettingsupdate, this,
//          &SettingsDialog::generalconfirmationsettingsupdates);
//  connect(generalappearancesettings,
//          &GeneralAppreanceSettings::generalappreancesettingsupdate, this,
//          &SettingsDialog::generalappreancesettingsupdates);
//  connect(
//      generalappearancesettings,
//      &GeneralAppreanceSettings::generalappreancesettingsupdate, this, [=]() {
//        // baseColor_ = ui_->searchBox->palette().color(QPalette::Base);
//        fontColor_ = palette().color(QPalette::Text);
//        QString scrollbackcol =
//            ".QScrollArea {border: 0; background-color: rgba(%1,%2,%3,%4);}";
//        ui_->scrollArea->setStyleSheet(scrollbackcol.arg(baseColor_.red())
//                                           .arg(baseColor_.green())
//                                           .arg(baseColor_.blue())
//                                           .arg(baseColor_.alpha()));
//      });
//  connect(generalnumericformatsettings,
//          &GeneralNumericFormatSettings::generalnumericformatsettingsupdate,
//          this, &SettingsDialog::generalnumericformatsettingsupdates);
//  connect(tablebasicsettings, &TableBasicSettings::tablebasicsettingsupdate,
//          this, &SettingsDialog::tablebasicsettingsupdates);
//  connect(tablecolorsettings, &TableColorSettings::tablecolorsettingsupdate,
//          this, &SettingsDialog::tablecolorsettingsupdates);
//  connect(tablefontsettings, &TableFontSettings::tablefontsettingsupdate, this,
//          &SettingsDialog::tablefontsettingsupdates);
//  connect(fittingsettings, &FittingSettings::fittingsettingsupdate, this,
//          &SettingsDialog::fittingsettingsupdates);

//  // Set model to the view
//  ui_->generalListView->setModel(generalSettingsModel_);
//  ui_->tableListView->setModel(tableSettingsModel_);
//  ui_->plot2dListView->setModel(plot2dSettingsModel_);
//  ui_->plot3dListView->setModel(plot3dSettingsModel_);
//  ui_->fittingListView->setModel(fittingSettingsModel_);
//  ui_->scriptingListView->setModel(scriptingSettingsModel_);

//  // Signals & slot connections
//  connect(ui_->settingsButton, &QPushButton::clicked, this,
//          &SettingsDialog::getBackToRootSettingsPage);
//  connect(ui_->generalListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::generalEnsureSelection);
//  connect(ui_->tableListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::tableEnsureSelection);
//  connect(ui_->plot2dListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::plot2dEnsureSelection);
//  connect(ui_->plot3dListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::plot3dEnsureSelection);
//  connect(ui_->fittingListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::fittingEnsureSelection);
//  connect(ui_->scriptingListView, &aSettingsListView::clicked, this,
//          &SettingsDialog::scriptingEnsureSelection);
//}

//SettingsDialog::~SettingsDialog() { delete ui_; }

//QSize SettingsDialog::sizeHint() const { return QSize(610, 420); }

//void SettingsDialog::resizeEvent(QResizeEvent*) {
//  // Adjust listviews height according to icon & grid size.
//  // Before listview becomes visible, we need to handle
//  // resize here.
//  // Pretty nasty hacks but seems to work..
//  if (!ui_->generalListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->generalListView);
//  }
//  if (!ui_->tableListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->tableListView);
//  }
//  if (!ui_->plot2dListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->plot2dListView);
//  }
//  if (!ui_->plot3dListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->plot3dListView);
//  }
//  if (!ui_->fittingListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->fittingListView);
//  }
//  if (!ui_->scriptingListView->autoAdjustHeight()) {
//    handleResizeBeforeListviewVisible(ui_->scriptingListView);
//  }
//}

//void SettingsDialog::addPage(Catagory catogory, Page id, SettingsPage* page) {
//  QStandardItem* item = new QStandardItem;
//  item->setText(page->windowTitle());
//  item->setIcon(page->windowIcon());

//  switch (catogory) {
//    case General:
//      generalSettingsModel_->appendRow(item);
//      if (ui_->generalLabel->isHidden()) ui_->generalLabel->show();
//      break;
//    case Table:
//      tableSettingsModel_->appendRow(item);
//      if (ui_->tableLabel->isHidden()) ui_->tableLabel->show();
//      break;
//    case Plot2d:
//      plot2dSettingsModel_->appendRow(item);
//      if (ui_->plot2dLabel->isHidden()) ui_->plot2dLabel->show();
//      break;
//    case Plot3d:
//      plot3dSettingsModel_->appendRow(item);
//      if (ui_->plot3dLabel->isHidden()) ui_->plot3dLabel->show();
//      break;
//    case Fitting:
//      fittingSettingsModel_->appendRow(item);
//      if (ui_->fittingLabel->isHidden()) ui_->fittingLabel->show();
//      break;
//    case Scripting:
//      scriptingSettingsModel_->appendRow(item);
//      if (ui_->scriptingLabel->isHidden()) ui_->scriptingLabel->show();
//      break;
//    default:
//      // Will never reach
//      qDebug() << "Settings page item not added";
//      delete item;
//      item = 0;
//      break;
//  }

//  // Add page to stackwidget at position id
//  ui_->stackedWidget->insertWidget(id, page);
//  // ui_->stackedWidget->addWidget(page);
//}

//void SettingsDialog::handleResizeBeforeListviewVisible(
//    aSettingsListView*& listView) {
//  if (listView->model()->rowCount() > 0) {
//    listView->setFixedHeight(
//        ((((listView->model()->rowCount() * listView->gridSize().width()) /
//           (width() - 50)) +
//          1) *
//         listView->gridSize().width()) +
//        aSettingsListView::listViewHeightPadding_);
//  } else {
//    listView->setFixedHeight(0);
//  }
//}

//void SettingsDialog::clearAllSelection() {
//  ui_->generalListView->clearSelection();
//  ui_->tableListView->clearSelection();
//  ui_->plot2dListView->clearSelection();
//  ui_->plot3dListView->clearSelection();
//  ui_->fittingListView->clearSelection();
//  ui_->scriptingListView->clearSelection();
//}

//void SettingsDialog::getBackToRootSettingsPage() {
//  QWidget* w = ui_->stackedWidget->currentWidget();
//  SettingsPage* sp = dynamic_cast<SettingsPage*>(w);
//  bool result = true;
//  if (sp) {
//    result = sp->settingsChangeCheck();
//  }
//  if (result) {
//    ui_->stackedWidget->setCurrentIndex(Page_RootSettings);
//    // ui_->searchBox->show();
//    ui_->settingsButton->setEnabled(false);
//  }
//}

//// when ported to QT5, use lambda functions insted of slots.
//// Clear Multiple selection & ensure single item selection
//void SettingsDialog::generalEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->generalListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(index.row() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}

//void SettingsDialog::tableEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->tableListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(index.row() +
//                                      generalSettingsModel_->rowCount() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}

//void SettingsDialog::plot2dEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->plot2dListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(index.row() +
//                                      generalSettingsModel_->rowCount() +
//                                      tableSettingsModel_->rowCount() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}

//void SettingsDialog::plot3dEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->plot3dListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(
//      index.row() + generalSettingsModel_->rowCount() +
//      tableSettingsModel_->rowCount() + plot2dSettingsModel_->rowCount() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}

//void SettingsDialog::fittingEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->fittingListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(
//      index.row() + generalSettingsModel_->rowCount() +
//      tableSettingsModel_->rowCount() + plot2dSettingsModel_->rowCount() +
//      plot3dSettingsModel_->rowCount() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}

//void SettingsDialog::scriptingEnsureSelection(const QModelIndex& index) {
//  clearAllSelection();
//  ui_->scriptingListView->setCurrentIndex(index);
//  ui_->stackedWidget->setCurrentIndex(
//      index.row() + generalSettingsModel_->rowCount() +
//      tableSettingsModel_->rowCount() + plot2dSettingsModel_->rowCount() +
//      plot3dSettingsModel_->rowCount() + fittingSettingsModel_->rowCount() + 1);
//  // ui_->searchBox->hide();
//  ui_->settingsButton->setEnabled(true);
//}
