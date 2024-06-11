/***************************************************************************
    File                 : MyWidget.h
    Project              : AlphaPlot
    Description          : MDI window widget
    --------------------------------------------------------------------
    Copyright            : (C) 2006-2009 Knut Franke (knut.franke*gmx.de)
    Copyright            : (C) 2006-2009 Tilman Benkert (thzs*gmx.net)
    Copyright            : (C) 2006-2007 by Ion Vasilief (ion_vasilief*yahoo.fr)
                           (replace * with @ in the email address)

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *  This program is free software; you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation; either version 2 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the Free Software           *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor,                    *
 *   Boston, MA  02110-1301  USA                                           *
 *                                                                         *
 ***************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QMdiSubWindow>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>


class QEvent;
class QCloseEvent;
class QString;
class Folder;

/* brief Base class of all MDI client windows.
 *
 * These are the main objects of every AlphaPlot project.
 * All content (apart from the directory structure) is managed by subclasses of
 * MyWidget.
 *
 * section future_plans Future Plans
 * Rename to Aspect.
 *
 * sa Folder, ApplicationWindow */
class AlphaplotExport MyWidget: public QMdiSubWindow
{
  Q_OBJECT

 public:
  //! Constructor
  /**
   * \param label window label
   * \param parent parent widget
   * \param name window name
   * \param f window flags
   * \sa setCaptionPolicy(), captionPolicy()
   */
  MyWidget(const QString &label = QString(), QWidget *parent = nullptr,
           const QString name = QString(), Qt::WindowFlags f = Qt::SubWindow);

  //! Possible window captions.
  enum CaptionPolicy {
    Name = 0,   //!< caption determined by the window name
    Label = 1,  //!< caption detemined by the window label
    Both = 2    //!< caption = "name - label"
  };
  enum Status { Hidden = -1, Normal = 0, Minimized = 1, Maximized = 2 };

  //! Return the window label
  virtual QString windowLabel() { return QString(w_label); }
  //! Set the window label
  virtual void setWindowLabel(const QString &s) {
    w_label = s;
    updateCaption();
  }

  //! Return the window name
  virtual QString name() { return objectName(); }
  //! Set the window name
  virtual void setName(const QString &s) {
    setObjectName(s);
    updateCaption();
  }

  //! Return the caption policy
  virtual CaptionPolicy captionPolicy() { return caption_policy; }
  //! Set the caption policy
  virtual void setCaptionPolicy(CaptionPolicy policy) {
    caption_policy = policy;
    updateCaption();
  }

  //! Return the creation date
  virtual QString birthDate() { return birthdate; }
  //! Set the creation date
  virtual void setBirthDate(const QString &s) { birthdate = s; }

  //! Return the window status as a string
  QString aspect();
  //! Return the window status flag (hidden, normal, minimized or maximized)
  Status status() { return w_status; }
  //! Set the window status flag (hidden, normal, minimized or maximized)
  void setStatus(Status status);

  virtual void print() {}
  virtual void exportPDF(const QString &) {}

  //! Notifies that a window was hidden by a direct user action
  virtual void setHidden();

  // event handlers
  //! Close event handler
  /**
   * Ask the user "delete, hide, or cancel?" if the
   * "ask on close" flag is set.
   */
  void closeEvent(QCloseEvent *);
  //! Toggle the "ask on close" flag
  void askOnCloseEvent(bool ask) { askOnClose = ask; }

  //! Returns the pointer to the parent folder of the window
  Folder *folder() { return parentFolder; }

  //! Initializes the pointer to the parent folder of the window
  void setFolder(Folder *f) { parentFolder = f; }

  //! Notifies the main application that the window has been modified
  void notifyChanges() { Q_EMIT modifiedWindow(this); }

  void setNormal();
  void setMinimized();
  void setMaximized();

 Q_SIGNALS:
  //! Emitted when the window was closed
  void closedWindow(MyWidget *);
  //! Emitted when the window was hidden
  void hiddenWindow(MyWidget *);
  void modifiedWindow(MyWidget *);
  void geometrychange(MyWidget *);
  //! Emitted when the window status changed
  void statusChanged(MyWidget *);
  //! Emitted when the title bar recieves a QContextMenuEvent
  void showTitleBarMenu();
  void mousepressevent(MyWidget *);

 protected Q_SLOTS:
  //! Set caption according to current CaptionPolicy, name and label
  void updateCaption();

 protected:
  virtual void changeEvent(QEvent *event);
  //! Catches parent changes (in order to gain access to the title bar)
  virtual void contextMenuEvent(QContextMenuEvent *event);
  virtual void resizeEvent(QResizeEvent *resizeEvent);
  virtual void moveEvent(QMoveEvent *moveEvent);
  virtual void mousePressEvent(QMouseEvent *event);

  //! Pointer to the parent folder of the window
  Folder *parentFolder;
  //! The window label
  /**
   * \sa setWindowLabel(), windowLabel(), setCaptionPolicy()
   */
  QString w_label;
  //! The creation date
  QString birthdate;
  //! The window status
  Status w_status;
  //! The caption policy
  /**
   * \sa setCaptionPolicy(), captionPolicy()
   */
  CaptionPolicy caption_policy;
  //! Toggle on/off: Ask the user "delete, hide, or cancel?" on a close event
  bool askOnClose;
};

#endif  // WIDGET_H
