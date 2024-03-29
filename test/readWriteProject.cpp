#include "readWriteProject.h"
#include "ApplicationWindow.h"

#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

extern "C" {
void file_compress(const char *file, const char *mode);
}

void ReadWriteProjectTest::readWriteProject() {
  unique_ptr<ApplicationWindow> app(open("testProject.rps"));
  QVERIFY(app.get());
  app->saveFolder(app->projectFolder(), "testProject1.rps");
  unique_ptr<ApplicationWindow> app1(open("testProject1.rps"));
  // TODO check that app1 is the same as app?
  QVERIFY(app1.get());
  file_compress("testProject1.rps", "wb9");
  app1.reset(open("testProject1.rps.gz"));
  QVERIFY(app1.get());
}

// Override showHelp() & chooseHelpFolder() to suppress documentation file
// path not found error. Need to fix this later (importance : high)
void ReadWriteProjectTest::showHelp() {}
void ReadWriteProjectTest::chooseHelpFolder() {}

QTEST_MAIN(ReadWriteProjectTest)

typedef QMessageBox::StandardButton StandardButton;

// override the QmessageBox static methods to turn a failure messages into
// throws, and ignore warnings
StandardButton QMessageBox::information(QWidget *, const QString &,
                                        const QString &text, StandardButtons,
                                        StandardButton) {
  cerr << text.toStdString() << endl;
  return QMessageBox::Ok;
}

StandardButton QMessageBox::question(QWidget *, const QString &,
                                     const QString &text, StandardButtons,
                                     StandardButton) {
  cerr << text.toStdString() << endl;
  return QMessageBox::Yes;
}

int QMessageBox::question(QWidget *, const QString &, const QString &text, int,
                          int, int) {
  cerr << text.toStdString() << endl;
  return QMessageBox::Yes;
}

StandardButton QMessageBox::warning(QWidget *, const QString &,
                                    const QString &text, StandardButtons,
                                    StandardButton) {
  cerr << text.toStdString() << endl;
  return QMessageBox::Ok;
}

StandardButton QMessageBox::critical(QWidget *, const QString &,
                                     const QString &text, StandardButtons,
                                     StandardButton) {
  throw runtime_error(text.toStdString());
}
