
#ifndef SEALABGUI_DlgUniformRandomPhases_H
#define SEALABGUI_DlgUniformRandomPhases_H
#define QT_NO_KEYWORDS

#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeaLabGui {

class Ui_DlgUniformRandomPhases;
class DlgUniformRandomPhases : public QWidget
{
    Q_OBJECT

public:
    DlgUniformRandomPhases(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgUniformRandomPhases();
    void accept();
    void reject();

    

private:
    std::unique_ptr<Ui_DlgUniformRandomPhases> ui;
    std::string _featureName;
};

class DlgUniformRandomPhasesEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgUniformRandomPhasesEdit(const App::PropertyFloat& MinimumValue, const App::PropertyFloat& MaximumValue, const App::PropertyString& featureName);
    ~DlgUniformRandomPhasesEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgUniformRandomPhases* widget;
    Gui::TaskView::TaskBox* taskbox;

};

} // namespace SeaLabGui

#endif // SEALABGUI_DlgUniformRandomPhases_H
