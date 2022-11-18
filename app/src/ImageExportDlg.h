#ifndef IMAGEEXPORTDLG_H
#define IMAGEEXPORTDLG_H

#include <QCheckBox>
#include <QComboBox>
#include <QPrinter>
#include <QSpinBox>

#include "ui/ExtensibleFileDialog.h"

class QStackedWidget;
class QGroupBox;

//! QFileDialog extended with options for image export
class ImageExportDlg : public ExtensibleFileDialog {
  Q_OBJECT

 private:
  //! Create #d_advanced_options and everything it contains.
  void initAdvancedOptions();

  //! Container widget for all advanced options.
  QStackedWidget *d_advanced_options;
  // vector format options
  //! Container widget for all options available for vector formats.
  QGroupBox *d_vector_options;
  QSpinBox *d_resolution;
  QCheckBox *d_color;
  QCheckBox *d_keep_aspect;
  QCheckBox *d_standard_page;
  QComboBox *d_box_page_size;
  QComboBox *d_box_page_orientation;
  // raster format options
  //! Container widget for all options available for raster formats.
  QGroupBox *d_raster_options;
  QSpinBox *d_quality;

 public:
  //! Constructor
  /**
   * \param parent parent widget
   * \param vector_options whether advanced options are to be provided for
   * export to vector formats
   * \param extended flag: show/hide the advanced options on start-up
   * \param flags window flags
   */
  ImageExportDlg(QWidget *parent = nullptr, bool vector_options = true,
                 bool extended = true, Qt::WindowFlags flags = Qt::Widget);
  //! For vector formats: returns the output resolution the user selected,
  //! defaulting to the screen resolution.
  int resolution() const { return d_resolution->value(); }
  //! For vector formats: returns whether colors should be enabled for ouput
  //! (default: true).
  bool color() const { return d_color->isChecked(); }
  //! For vector formats: returns whether the output should preserve aspect
  //! ratio of the plot (default: true).
  bool keepAspect() const { return d_keep_aspect->isChecked(); }
  //! For vector formats: returns a standard output page size (default:
  //! QPrinter::Custom).
  QPrinter::PageSize pageSize() const;
  void setPageSize(QPrinter::PageSize size);
  QPrinter::Orientation pageOrientation() const;
  void setOrientation(QPrinter::Orientation orientation);
  //! Return the quality (in percent) the user selected for export to raster
  //! formats.
  int quality() const { return d_quality->value(); }

  void selectFilter(const QString &filter);

 protected slots:
  void closeEvent(QCloseEvent *);
  //! Update which options are visible and enabled based on the output format.
  void updateAdvancedOptions(const QString &filter);
};

#endif  // IMAGEEXPORTDLG_H
