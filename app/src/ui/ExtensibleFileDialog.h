#ifndef EXTENSIBLE_FILE_DIALOG_H
#define EXTENSIBLE_FILE_DIALOG_H

#include <QFileDialog>
#include <QPushButton>

//! QFileDialog plus generic extension support.
/**
 * This is a simple hack on top of QFileDialog that allows a custom extension
 * widget to be added to
 * the bottom of the dialog. A button is provided for toggling display of this
 * widget on/off.
 *
 * For the placement of button and extension widget, it is assumed that
 * QFileDialog uses a
 * QGridLayout as its top-level layout. Other layouts will probably lead to a
 * strange outlook,
 * although the functionality should stay intact.
 */
class ExtensibleFileDialog : public QFileDialog {
  Q_OBJECT

 public:
  //! Constructor.
  /**
   * \param parent parent widget (only affects placement of the dialog)
   * \param extended flag: show/hide the advanced options on start-up
   * \param flags window flags
   */
  ExtensibleFileDialog(QWidget *parent = nullptr, bool extended = true,
                       Qt::WindowFlags flags = Qt::Widget);
  //! Set the extension widget to be displayed when the user presses the toggle
  //! button.
  void setExtensionWidget(QWidget *extension);

  //! Tells weather the dialog has a valid extension widget
  bool isExtendable() { return d_extension != nullptr; }
  bool isExtended() { return d_extension_toggle->isChecked(); }
  void setExtended(bool extended) { d_extension_toggle->setChecked(extended); }

 protected:
  //! Button for toggling display of extension on/off.
  QPushButton *d_extension_toggle;

 private slots:
  //! Resize to make/take space for the extension widget.
  void resize(bool extension_on);

 private:
  //! The extension widget
  QWidget *d_extension;
  //! The layout row (of the assumed QGridLayout) used for extensions
  int d_extension_row;
};

#endif  // EXTENSIBLE_FILE_DIALOG_H
