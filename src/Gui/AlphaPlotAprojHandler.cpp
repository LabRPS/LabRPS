#include "Precompiled.h"
#include "AlphaPlotAprojHandler.h"

#include "PlotPropertyEditor.h"
#include "MainWindow.h"
#include "AlphaPlot.h"

#ifndef _PreComp_
#include <QFile>
#include <QMdiSubWindow>
#include <QMessageBox>>
#endif

#include <Libraries/Alphaplot/2Dplot/Layout2D.h>
#include <Libraries/Alphaplot/3Dplot/Layout3D.h>
#include <Libraries/Alphaplot/Folder.h>
#include <Libraries/Alphaplot/Matrix.h>
#include <Libraries/Alphaplot/Table.h>
#include <Libraries/Alphaplot/future/lib/XmlStreamReader.h>
#include <Libraries/Alphaplot/future/lib/XmlStreamWriter.h>

using namespace Gui;

const QString AlphaPlotAprojHandler::xmlschemafile_ = QString::fromLatin1(":xmlschema/aproj.xsd");

AlphaPlotAprojHandler::AlphaPlotAprojHandler(MainAlphaPlot* app)
    : QObject(app), app_(app), recursivecount_(0) {
  Q_ASSERT(app_);
}

AlphaPlotAprojHandler::~AlphaPlotAprojHandler() {}

MainAlphaPlot* AlphaPlotAprojHandler::openproject(const QString& filename)
{
  QFile *file = nullptr;
  if (filename.endsWith(QString::fromLatin1(".gz"), Qt::CaseInsensitive) ||
      filename.endsWith(QString::fromLatin1(".gz~"), Qt::CaseInsensitive)) {
    file = openCompressedFile(filename);
    if (!file) return nullptr;
  } else {
    file = new QFile(filename);
    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
      qDebug() << "unable to open " << filename;
      delete file;
      return nullptr;
    }
  }

  // check xml schema
  /*if (!checkXmlSchema(filename)) {
    qDebug() << QString("unable to validate %1 using xml schema").arg(filename);
    delete file;

    if (QFile::exists(filename + "~")) {
      int choice = QMessageBox::question(
          app_, tr("File opening error"),
          tr("The file <b>%1</b> is corrupted, but there exists a backup "
             "copy.<br>Do you want to open the backup instead?")
              .arg(filename),
          QMessageBox::Yes | QMessageBox::Default,
          QMessageBox::No | QMessageBox::Escape);
      if (choice == QMessageBox::Yes) {
        QMessageBox::information(app_, tr("Opening backup copy"),
                                 tr("The original (corrupt) file is being left "
                                    "untouched, in case you want to try "
                                    "rescuing data manually. If you want to "
                                    "continue working with the automatically "
                                    "restored backup copy, you have to "
                                    "explicitly overwrite the original file."));
        return openproject(filename + "~");
      }
    }
    QMessageBox::critical(
        app_, tr("File opening error"),
        tr("The file <b>%1</b> is not a valid project file.").arg(filename));
    return nullptr;
  }*/

  if (!file) {
    qDebug() << "unable to open " << filename;
    return nullptr;
  }

  recursivecount_ = 0;
  Gui::MainAlphaPlot* app = getMainWindow()->getAlphaPlot();
  if (!app)
    return nullptr;

  app->applyUserSettings();
  app->projectname = filename;
  app->setWindowTitle(tr("AlphaPlot") + QString::fromLatin1(" - ") + filename);
  app->blockFolderviewsignals(true);
  app->blockSignals(true);
  // rename project folder item
  FolderTreeWidgetItem *item = app->getProjectRootItem();

  Folder *cfolder = readxmlstream(app, file, filename, item);
  file->close();
  delete file;

  app->blockFolderviewsignals(false);
  app->blockSignals(false);
  app->renamedTables.clear();

  app->show();
  //app->executeNotes();
  app->savedProject();

  app->recentProjects.removeAll(filename);
  app->recentProjects.push_front(filename);
  app->updateRecentProjectsList();

  // change folder to user defined current folder
  // force update
  app->changeFolder(app->projectFolder(), true);
  // set current folder
  if (cfolder) {
    app->changeFolder(cfolder, false);
    app->setCurrentFolderViewItem(cfolder->folderTreeWidgetItem());
  }

  return app;
}

void AlphaPlotAprojHandler::appendproject(const QString &filename) {
  if (filename.isEmpty()) return;

  QFileInfo fi(filename);
  app_->workingDir = fi.absolutePath();

  if (filename.contains(QString::fromLatin1(".aproj"))) {
    QFileInfo fileinfo(filename);
    if (!fileinfo.exists()) {
      QMessageBox::critical(
          app_, tr("File opening error"),
          tr("The file: <b>%1</b> doesn't exist!").arg(filename));
      return;
    }
  } else {
    QMessageBox::critical(
        app_, tr("File opening error"),
        tr("The file: <b>%1</b> is not a AlphaPlot project file!")
            .arg(filename));
    return;
  }

  QStringList conflictlist = checkbeforeappendproject(filename);
  QStringList subfolderlist = app_->current_folder->subfolders();
  QString chopfilename = fi.baseName();
  if (subfolderlist.contains(chopfilename, Qt::CaseSensitive))
    conflictlist.append(chopfilename);
  if (!conflictlist.isEmpty()) {
    QString conflictstring;
    Q_FOREACH (QString string, conflictlist)
      conflictstring += string + QString::fromLatin1("<br>");
    QMessageBox::warning(
        app_, tr("File Appending error"),
        tr("The file: <b>%1</b> contains window names "
           "conflicting with window/folder name(s) from current project. "
           "change the conflicting names and try appending! <br>"
           "Conflicting names:<br>"
           "%2")
            .arg(filename, conflictstring));
    return;
  }

  QFile *file = nullptr;
  if (filename.endsWith(QString::fromLatin1(".gz"), Qt::CaseInsensitive) ||
      filename.endsWith(QString::fromLatin1(".gz~"), Qt::CaseInsensitive)) {
    file = openCompressedFile(filename);
    if (!file) return;
  } else {
    file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
  }

  app_->recentProjects.removeAll(filename);
  app_->recentProjects.push_front(filename);
  app_->updateRecentProjectsList();

  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  Folder *cfolder = app_->addFolder();
  app_->changeFolder(cfolder);
  FolderTreeWidgetItem *item =
      static_cast<FolderTreeWidgetItem *>(cfolder->folderTreeWidgetItem());
  app_->blockFolderviewsignals(true);
  app_->blockSignals(true);
  readxmlstream(app_, file, filename, item);

  file->close();
  delete file;

  app_->blockFolderviewsignals(false);
  app_->blockSignals(false);
  app_->changeFolder(cfolder, true);
  app_->renamedTables = QStringList();
  QApplication::restoreOverrideCursor();
}

QStringList AlphaPlotAprojHandler::checkbeforeappendproject(const QString &filename) {
  QStringList conflictlist, windowlist;
  QFile *file = nullptr;
  if (filename.endsWith(QString::fromLatin1(".gz"), Qt::CaseInsensitive) ||
      filename.endsWith(QString::fromLatin1(".gz~"), Qt::CaseInsensitive)) {
    file = openCompressedFile(filename);
    if (!file) return QStringList();
  } else {
    file = new QFile(filename);
    file->open(QIODevice::ReadOnly);
  }
  std::unique_ptr<XmlStreamReader> xmlreader =
      std::unique_ptr<XmlStreamReader>(new XmlStreamReader(file));
  QXmlStreamReader::TokenType token;
  bool ok;
  while (!xmlreader->atEnd()) {
    token = xmlreader->readNext();
    if (token == QXmlStreamReader::StartElement &&
        xmlreader->name() == QString::fromLatin1("table")) {
      QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
      if (ok) windowlist << name;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("matrix")) {
      QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
      if (ok) windowlist << name;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("note")) {
      QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
      if (ok) windowlist << name;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot2d")) {
      QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
      if (ok) windowlist << name;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot3d")) {
      QString name = xmlreader->readAttributeString(QString::fromLatin1("name"), &ok);
      if (ok) windowlist << name;
    }
  }
  file->close();

  QList<QMdiSubWindow *> slist = app_->subWindowsList();
  Q_FOREACH (QMdiSubWindow *window, slist) {
    MyWidget *widget = qobject_cast<MyWidget *>(window);
    if (widget)
      if (windowlist.contains(widget->name(), Qt::CaseSensitive))
        conflictlist << widget->name();
  }

  return conflictlist;
}

MyWidget *AlphaPlotAprojHandler::opentemplate(const QString &filename) {
  QFile *file = new QFile(filename);
  if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
    qDebug() << "unable to open " << filename;
    delete file;
    return nullptr;
  }

  MyWidget *mywidget = nullptr;
  std::unique_ptr<XmlStreamReader> xmlreader =
      std::unique_ptr<XmlStreamReader>(new XmlStreamReader(file));
  QXmlStreamReader::TokenType token;
  bool istemplate = false;
  while (!xmlreader->atEnd()) {
    token = xmlreader->readNext();
    if (token == QXmlStreamReader::StartElement &&
        (xmlreader->name() == QString::fromLatin1("amt") || xmlreader->name() == QString::fromLatin1("apt") ||
         xmlreader->name() == QString::fromLatin1("att") || xmlreader->name() == QString::fromLatin1("ast"))) {
      QXmlStreamAttributes attributes = xmlreader->attributes();
      istemplate = true;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("table") && istemplate) {
      Table *table = app_->newTable(QString::fromLatin1("table"), 1, 1);
      table->d_future_table->load(xmlreader.get());
      mywidget = table;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("matrix") && istemplate) {
      Matrix *matrix = app_->newMatrix(QString::fromLatin1("matrix"), 1, 1);
      matrix->d_future_matrix->load(xmlreader.get());
      mywidget = matrix;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot2d") && istemplate) {
      Layout2D *plot2d = app_->newGraph2D();
      plot2d->load(xmlreader.get(), tables(app_), matrixs(app_));
      // (hack) for some unknown reason this connection need to be manually set
      // here
      Q_FOREACH (AxisRect2D *axisrect, plot2d->getAxisRectList()) {
        app_->plotPropertyeditor->axisrectConnections(axisrect);
      }
      mywidget = plot2d;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot3d") && istemplate) {
      bool ok = false;
      Layout3D *plot = nullptr;
      QString ptype = xmlreader->readAttributeString(QString::fromLatin1("type"), &ok);
      if (ok) {
        if (ptype == QString::fromLatin1("surface"))
          plot = app_->newGraph3D(Graph3DCommon::Plot3DType::Surface);
        else if (ptype == QString::fromLatin1("bar"))
          plot = app_->newGraph3D(Graph3DCommon::Plot3DType::Bar);
        else if (ptype == QString::fromLatin1("scatter"))
          plot = app_->newGraph3D(Graph3DCommon::Plot3DType::Scatter);
        else
          xmlreader->raiseError(tr("Layout3D PlotType unknown %1").arg(ptype));
      } else
        xmlreader->raiseError(tr("Layout3D PlotType missing or empty"));
      if (plot) {
        plot->load(xmlreader.get(), tables(app_), matrixs(app_), 0);//koffa
        mywidget = plot;
      } else
        return nullptr;
    } else if (token == QXmlStreamReader::StartElement && !istemplate) {
      QMessageBox::critical(
          app_, tr("File opening error"),
          tr("The file: <b>%1</b> is not a AlphaPlot template file!")
              .arg(filename));
      return nullptr;
    }
  }

  if (xmlreader->hasWarnings()) {
    Q_FOREACH (QString warning, xmlreader->warningStrings()) {
      qDebug() << warning;
    }
  }

  return mywidget;
}

Folder *AlphaPlotAprojHandler::readxmlstream(MainAlphaPlot *app, QFile *file,
                                    const QString &filename,
                                    FolderTreeWidgetItem *rootitem) {
  Folder *cfolder = nullptr;
  QFileInfo fileinfo(filename);
  std::unique_ptr<XmlStreamReader> xmlreader =
      std::unique_ptr<XmlStreamReader>(new XmlStreamReader(file));
  QXmlStreamReader::TokenType token;
  while (!xmlreader->atEnd()) {
    token = xmlreader->readNext();
    if (token == QXmlStreamReader::StartElement &&
        xmlreader->name() == QString::fromLatin1("aproj")) {
      QXmlStreamAttributes attributes = xmlreader->attributes();
      if (attributes.hasAttribute(QString::fromLatin1("scripting"))) {
       /* if (!app->setScriptingLang(attributes.value(QString::fromLatin1("scripting")).toString(),
                                   true))
          QMessageBox::warning(
              app, tr("File opening error"),
              tr("The file \"%1\" was created using \"%2\" as scripting "
                 "language.\n\n Initializing support for this language FAILED; "
                 "I'm using default instead.\nVarious parts of this file may "
                 "not be displayed as expected.")
                  .arg(filename, attributes.value(QString::fromLatin1("scripting")).toString()));*/
      }
      rootitem->setText(0, fileinfo.baseName());
      rootitem->folder()->setName(fileinfo.baseName());
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("folder")) {
      recursivecount_++;
      QXmlStreamAttributes attr = xmlreader->attributes();
      QString name = xmlreader->attributes().value(QString::fromLatin1("name")).toString();
      QString creation_time =
          xmlreader->attributes().value(QString::fromLatin1("creation_time")).toString();
      QString lastmodified_time =
          xmlreader->attributes().value(QString::fromLatin1("lastmodified_time")).toString();
      QString current = xmlreader->attributes().value(QString::fromLatin1("current")).toString();
      Folder *folder = new Folder(app->current_folder, name);
      folder->setBirthDate(creation_time);
      folder->setModificationDate(lastmodified_time);
      FolderTreeWidgetItem *fli = new FolderTreeWidgetItem(
          app->current_folder->folderTreeWidgetItem(), folder);
      fli->setText(0, name);
      folder->setFolderTreeWidgetItem(fli);
      app->current_folder = folder;
      if (current.trimmed() == QString::fromLatin1("true")) cfolder = folder;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("table")) {
      bool ok;
      QString time = xmlreader->readAttributeString(QString::fromLatin1("creation_time"), &ok);
      Table *table = app->newTable(QString::fromLatin1("table"), 1, 1);
      table->d_future_table->load(xmlreader.get());
      // unable to set datetime via above method for some unknown reason. Thus
      // had to do it here (find the cause of this issue and remove this later)
      if (ok) {
        table->setBirthDate(
            QDateTime::fromString(time, QString::fromLatin1("yyyy-dd-MM hh:mm:ss:zzz"))
                .toString(Qt::LocalDate));
      } else {
        table->setBirthDate(
            QDateTime::currentDateTime().toString(Qt::LocalDate));
        xmlreader->raiseWarning(
            tr("Invalid creation time. Using current time insted."));
      }
      table->showNormal();

    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("matrix")) {
      Matrix *matrix = app->newMatrix(QString::fromLatin1("matrix"), 1, 1);
      matrix->d_future_matrix->load(xmlreader.get());
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot2d")) {
      Layout2D *plot2d = app->newGraph2D();
      plot2d->load(xmlreader.get(), tables(app), matrixs(app));
      // (hack) for some unknown reason this connection need to be manually set
      // here
      Q_FOREACH (AxisRect2D *axisrect, plot2d->getAxisRectList()) {
        app->plotPropertyeditor->axisrectConnections(axisrect);
      }
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("plot3d")) {
      bool ok = false;
      Layout3D *plot = nullptr;
      QString ptype = xmlreader->readAttributeString(QString::fromLatin1("type"), &ok);
      if (ok) {
        if (ptype == QString::fromLatin1("surface"))
          plot = app->newGraph3D(Graph3DCommon::Plot3DType::Surface);
        else if (ptype == QString::fromLatin1("bar"))
          plot = app->newGraph3D(Graph3DCommon::Plot3DType::Bar);
        else if (ptype == QString::fromLatin1("scatter"))
          plot = app->newGraph3D(Graph3DCommon::Plot3DType::Scatter);
        else
          xmlreader->raiseError(tr("Layout3D PlotType unknown %1").arg(ptype));
      } else
        xmlreader->raiseError(tr("Layout3D PlotType missing or empty"));
      if (plot)
        plot->load(xmlreader.get(), tables(app), matrixs(app), 0);//koffa
      else
        return nullptr;
    } else if (token == QXmlStreamReader::StartElement &&
               xmlreader->name() == QString::fromLatin1("log")) {
      QXmlStreamAttributes attributes = xmlreader->attributes();
      if (attributes.hasAttribute(QString::fromLatin1("value"))) {
        QString loginfo = attributes.value(QString::fromLatin1("value")).toString();
        app->showResults(loginfo);
      } else
        xmlreader->raiseWarning(tr("Invalid attribute '%1' log element. "
                                   "skipping the attribute now.")
                                    .arg(QString::fromLatin1("value")));
    } else if (token == QXmlStreamReader::EndElement &&
               xmlreader->name() == QString::fromLatin1("folder")) {
      while (recursivecount_ > 0) {
        Folder *fl = static_cast<Folder *>(app->current_folder->parent());
        if (fl) {
          app->current_folder = fl;
        }
        recursivecount_--;
      }
    }
  }

  if (xmlreader->hasWarnings()) {
    Q_FOREACH (QString warning, xmlreader->warningStrings()) {
      qDebug() << warning;
    }
  }

  return cfolder;
}

QFile *AlphaPlotAprojHandler::openCompressedFile(const QString &filename) {
  QTemporaryFile *tempfile = new QTemporaryFile;
  std::unique_ptr<QFile> file = std::unique_ptr<QFile>(new QFile(filename));
  if (!file->open(QIODevice::ReadOnly) || !tempfile->open()) {
    qDebug() << "unable to open " << filename;
    delete tempfile;
    return nullptr;
  }
  std::unique_ptr<QByteArray> bytearray =
      std::unique_ptr<QByteArray>(new QByteArray);

  *bytearray.get() = file->readAll();
  tempfile->write(qUncompress(*bytearray.get()));
  bytearray->clear();
  tempfile->reset();
  return tempfile;
}

bool AlphaPlotAprojHandler::saveproject(const QString &filename, Folder *folder) {
  bool compress = false;
  if (filename.endsWith(QString::fromLatin1(".gz"))) compress = true;

  std::unique_ptr<XmlStreamWriter> xmlwriter;
  std::unique_ptr<QFile> file = std::unique_ptr<QFile>(new QFile(filename));
  if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "failed to open xml file for writing";
    return false;
  }
  std::unique_ptr<QByteArray> bytearray =
      std::unique_ptr<QByteArray>(new QByteArray);

  if (!compress) {
    // Uncompressed file save
    xmlwriter =
        std::unique_ptr<XmlStreamWriter>(new XmlStreamWriter(file.get()));
  } else {
    // Compressed file save
    bytearray = std::unique_ptr<QByteArray>(new QByteArray);
    xmlwriter =
        std::unique_ptr<XmlStreamWriter>(new XmlStreamWriter(bytearray.get()));
  }

  xmlwriter->setCodec("UTF-8");

  xmlwriter->setAutoFormatting(false);
  Folder *root = folder;
  xmlwriter->writeStartDocument();
  xmlwriter->writeComment(QString::fromLatin1("AlphaPlot project file"));
  xmlwriter->writeStartElement(QString::fromLatin1("aproj"));
  xmlwriter->writeAttribute(QString::fromLatin1("version"), QString::number(AlphaPlot::version()));
  xmlwriter->writeAttribute(QString::fromLatin1("scripting"), QString::fromLatin1("muParser"));
  xmlwriter->writeAttribute(QString::fromLatin1("windows"),
                            QString::number(root->windowCount(true)));

  recursivecount_ = 0;
  saveTreeRecursive(root, xmlwriter.get());
  xmlwriter->writeStartElement(QString::fromLatin1("log"));
  xmlwriter->writeAttribute(QString::fromLatin1("value"), app_->getLogInfoText());
  xmlwriter->writeEndElement();
  xmlwriter->writeEndElement();
  xmlwriter->writeEndDocument();
  // Compressed file
  if (compress) {
    file->write(qCompress(*bytearray.get()));
  }
  file->commitTransaction();
  return true;
}

void AlphaPlotAprojHandler::saveTreeRecursive(Folder *folder,
                                     XmlStreamWriter *xmlwriter) {
  // make sure that plots are saved after tables & metrices
  QList<MyWidget *> others;
  QList<MyWidget *> plots;
  Q_FOREACH (MyWidget *subwindow, folder->windowsList()) {
    (qobject_cast<Layout2D *>(subwindow) || qobject_cast<Layout3D *>(subwindow))
        ? plots << subwindow
        : others << subwindow;
  }
  others.append(plots);
  Q_FOREACH (MyWidget *subwindow, others) {
    if (qobject_cast<Table *>(subwindow)) {
      Table *table = qobject_cast<Table *>(subwindow);
      table->d_future_table->save(xmlwriter);
    } else if (qobject_cast<Matrix *>(subwindow)) {
      Matrix *matrix = qobject_cast<Matrix *>(subwindow);
      matrix->d_future_matrix->save(xmlwriter);
    } else if (qobject_cast<Layout2D *>(subwindow)) {
      Layout2D *graph = qobject_cast<Layout2D *>(subwindow);
      graph->save(xmlwriter);
    } else if (qobject_cast<Layout3D *>(subwindow)) {
      Layout3D *graph = qobject_cast<Layout3D *>(subwindow);
      graph->save(xmlwriter);
    }
  }
  Q_FOREACH (Folder *subfolder, folder->folders()) {
    recursivecount_++;
    xmlwriter->writeStartElement(QString::fromLatin1("folder"));
    xmlwriter->writeAttribute(QString::fromLatin1("name"), subfolder->name());
    xmlwriter->writeAttribute(QString::fromLatin1("creation_time"), subfolder->birthDate());
    xmlwriter->writeAttribute(QString::fromLatin1("lastmodified_time"),
                              subfolder->modificationDate());

    (subfolder == app_->currentFolder())
        ? xmlwriter->writeAttribute(QString::fromLatin1("current"), QString::fromLatin1("true"))
        : xmlwriter->writeAttribute(QString::fromLatin1("current"), QString::fromLatin1("false"));

    saveTreeRecursive(subfolder, xmlwriter);
    while (recursivecount_ > 0) {
      xmlwriter->writeEndElement();
      recursivecount_--;
    }
  }
}

bool AlphaPlotAprojHandler::saveTemplate(const QString &filename, MyWidget *mywidget) {
  QString fname = filename;
  std::unique_ptr<QFile> file = std::unique_ptr<QFile>(new QFile(fname));
  if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "failed to open xml file for writing";
    return false;
  }
  QString selectedfilter = QString();
  (fname.endsWith(QString::fromLatin1(".amt")))   ? selectedfilter = QString::fromLatin1("amt")
  : (fname.endsWith(QString::fromLatin1(".apt"))) ? selectedfilter = QString::fromLatin1("apt")
  : (fname.endsWith(QString::fromLatin1(".att"))) ? selectedfilter = QString::fromLatin1("att")
  : (fname.endsWith(QString::fromLatin1(".ast"))) ? selectedfilter = QString::fromLatin1("att")
                             : selectedfilter = QString();
  if (selectedfilter.isEmpty()) {
    qDebug() << "unknown selected filter: ." << selectedfilter;
    return false;
  }
  std::unique_ptr<XmlStreamWriter> xmlwriter =
      std::unique_ptr<XmlStreamWriter>(new XmlStreamWriter(file.get()));
  xmlwriter->setCodec("UTF-8");
  xmlwriter->setAutoFormatting(false);

  xmlwriter->writeStartDocument();
  xmlwriter->writeComment(QString::fromLatin1("AlphaPlot Template file"));
  xmlwriter->writeStartElement(selectedfilter);
  xmlwriter->writeAttribute(QString::fromLatin1("version"), QString::number(AlphaPlot::version()));
  if (qobject_cast<Table *>(mywidget)) {
    Table *table = qobject_cast<Table *>(mywidget);
    table->d_future_table->save(xmlwriter.get(), true);
  } else if (qobject_cast<Matrix *>(mywidget)) {
    Matrix *matrix = qobject_cast<Matrix *>(mywidget);
    matrix->d_future_matrix->save(xmlwriter.get(), true);
  } else if (qobject_cast<Layout2D *>(mywidget)) {
    Layout2D *graph = qobject_cast<Layout2D *>(mywidget);
    graph->save(xmlwriter.get(), true);
  } else if (qobject_cast<Layout3D *>(mywidget)) {
    Layout3D *graph = qobject_cast<Layout3D *>(mywidget);
    graph->save(xmlwriter.get(), true);
  }
  xmlwriter->writeEndElement();
  xmlwriter->writeEndDocument();
  file->close();
  return true;
}

QList<Table *> AlphaPlotAprojHandler::tables(MainAlphaPlot *app) {
  QList<QMdiSubWindow *> subwindowlist = app->subWindowsList();
  QList<Table *> tables;
  Q_FOREACH (QMdiSubWindow *subwindow, subwindowlist) {
    Table *tab = qobject_cast<Table *>(subwindow);
    if (tab) {
      tables << tab;
    }
  }
  return tables;
}

QList<Matrix *> AlphaPlotAprojHandler::matrixs(MainAlphaPlot *app) {
  QList<QMdiSubWindow *> subwindowlist = app->subWindowsList();
  QList<Matrix *> matrixs;
  Q_FOREACH (QMdiSubWindow *subwindow, subwindowlist) {
    Matrix *mat = qobject_cast<Matrix *>(subwindow);
    if (mat) {
      matrixs << mat;
    }
  }
  return matrixs;
}

bool AlphaPlotAprojHandler::checkXmlSchema(const QString &filename) {
  Q_UNUSED(filename);
  /*std::unique_ptr<MessageHandler> messageHandler =
      std::unique_ptr<MessageHandler>(new MessageHandler);
  std::unique_ptr<QFile> xsdfile =
      std::unique_ptr<QFile>(new QFile(xmlschemafile_));
  if (!xsdfile->open(QIODevice::ReadOnly)) {
    qDebug()
        << QString("unable to open xml schema file %1").arg(xmlschemafile_);
    return false;
  }
  std::unique_ptr<QXmlSchema> schema =
      std::unique_ptr<QXmlSchema>(new QXmlSchema);
  schema->setMessageHandler(messageHandler.get());
  bool errorOccurred = false;
  if (schema->load(xsdfile.get(), QUrl::fromLocalFile(xsdfile->fileName())) ==
      false)
    errorOccurred = true;
  else {
    std::unique_ptr<QXmlSchemaValidator> xmlvalidator =
        std::unique_ptr<QXmlSchemaValidator>(
            new QXmlSchemaValidator(*schema.get()));
    std::unique_ptr<QFile> xmlfile =
        std::unique_ptr<QFile>(new QFile(filename));
    xmlfile->open(QIODevice::ReadOnly);
    if (!xmlvalidator->validate(xmlfile.get(),
                                QUrl::fromLocalFile(xmlfile->fileName())))
      errorOccurred = true;
    xmlfile->close();
  }
  xsdfile->close();
  if (errorOccurred) {
    QString msgstring = messageHandler->statusMessage();
    QMessageBox::critical(app_, tr("File opening error"),
                          tr("Unable to validate xml schema; error at Line %1, "
                             "Row %2, Error Msg %3")
                              .arg(messageHandler->line())
                              .arg(messageHandler->column())
                              .arg(msgstring.toUtf8().constData()));
    return false;
  } else {
    return true;
  }*/
  return false;
}

// xml schema message handling class
/*MessageHandler::MessageHandler(QObject *parent)
    : QAbstractMessageHandler(parent) {}

QString MessageHandler::statusMessage() const { return m_description; }

int MessageHandler::line() const {
  return static_cast<int>(m_sourceLocation.line());
}

int MessageHandler::column() const {
  return static_cast<int>(m_sourceLocation.column());
}

void MessageHandler::handleMessage(QtMsgType type, const QString &description,
                                   const QUrl &identifier,
                                   const QSourceLocation &sourceLocation) {
  Q_UNUSED(type);
  Q_UNUSED(identifier);
  m_description = description;
  m_sourceLocation = sourceLocation;
}*/
