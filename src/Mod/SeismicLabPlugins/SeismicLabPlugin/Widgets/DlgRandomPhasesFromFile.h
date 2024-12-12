
#ifndef SEISMICLABGUI_DlgRandomPhasesFromFile_H
#define SEISMICLABGUI_DlgRandomPhasesFromFile_H


#include <Gui/TaskView/TaskDialog.h>
#include <Gui/TaskView/TaskView.h>
#include <App/PropertyUnits.h>
#include <QString>

class QSignalMapper;

namespace SeismicLabGui {

class Ui_DlgRandomPhasesFromFile;
class DlgRandomPhasesFromFile : public QWidget
{
    Q_OBJECT

public:
    DlgRandomPhasesFromFile(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName, QWidget* parent = nullptr);
    ~DlgRandomPhasesFromFile();
    void accept();
    void reject();

 public Q_SLOTS:
    void slotSetWorkingDirectory();   

private:
    std::unique_ptr<Ui_DlgRandomPhasesFromFile> ui;
    std::string _featureName;
    QString workingDirectory;
};

class DlgRandomPhasesFromFileEdit : public Gui::TaskView::TaskDialog
{
    Q_OBJECT

public:
    DlgRandomPhasesFromFileEdit(const App::PropertyString& WorkingDirectory, const App::PropertyString& featureName);
    ~DlgRandomPhasesFromFileEdit();
    
public:
    bool accept();
    bool reject();
    QDialogButtonBox::StandardButtons getStandardButtons() const;

public:
    DlgRandomPhasesFromFile* widget;
    Gui::TaskView::TaskBox* taskbox;
};

} // namespace SeismicLabGui

#endif // SEISMICLABGUI_DlgRandomPhasesFromFile_H
