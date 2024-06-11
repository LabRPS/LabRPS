#ifndef APROJHANDLER_H
#define APROJHANDLER_H

//#include <QAbstractMessageHandler>
#include <QObject>
#include <RPSGlobal.h>


class QFile;
class Folder;
class FolderTreeWidgetItem;
class XmlStreamWriter;
class Table;
class Matrix;
class MyWidget;

namespace Gui {
    class MainAlphaPlot;

    class GuiExport AlphaPlotAprojHandler : public QObject
    {
        Q_OBJECT
    public:
        AlphaPlotAprojHandler(MainAlphaPlot* app);
        ~AlphaPlotAprojHandler();
        MainAlphaPlot* openproject(const QString& filename);
        void appendproject(const QString& filename);
        QStringList checkbeforeappendproject(const QString& filename);
        MyWidget* opentemplate(const QString& filename);
        Folder* readxmlstream(MainAlphaPlot* app, QFile* file,
            const QString& filename,
            FolderTreeWidgetItem* rootitem);

        bool saveproject(const QString& filename, Folder* folder);
        void saveTreeRecursive(Folder* folder, XmlStreamWriter* xmlwriter);
        bool saveTemplate(const QString& filename, MyWidget* mywidget);
        QList<Table*> tables(MainAlphaPlot* app);
        QList<Matrix*> matrixs(MainAlphaPlot* app);

    private:
        QFile* openCompressedFile(const QString& filename);
        bool checkXmlSchema(const QString& filename);

    private:
        MainAlphaPlot* app_;
        int recursivecount_;
        static const QString xmlschemafile_;
    };

    /*class MessageHandler : public QAbstractMessageHandler {
     public:
      MessageHandler(QObject *parent = nullptr);
      QString statusMessage() const;
      int line() const;
      int column() const;

     protected:
      virtual void handleMessage(QtMsgType type, const QString &description,
                                 const QUrl &identifier,
                                 const QSourceLocation &sourceLocation);

     private:
      QString m_description;
      QSourceLocation m_sourceLocation;
    };*/

} //namespace Gui


#endif  // APROJHANDLER_H
