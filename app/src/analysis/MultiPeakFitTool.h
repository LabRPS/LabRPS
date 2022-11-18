#ifndef MULTI_PEAK_FIT_TOOL
#define MULTI_PEAK_FIT_TOOL

#include <QObject>
#include "MultiPeakFit.h"

class ApplicationWindow;

/*! Plot tool for doing multi-peak fitting.
 *
 * This class can be seen as a user-interface wrapper around MultiPeakFit,
 * providing functionality for visually
 * selecting estimated peak positions and finally executing the fit.
 *
 * Maybe some other parts of the multi-peak fitting process (namely, specifying
 * the number of peaks and optionally
 * the peak profile) could be moved here as well.
 */

class PlotToolInterface {
 public:
  enum RTTI {
    DataPicker,
    ScreenPicker,
    LineProfile,
    MultiPeak,
    RangeSelector,
    TranslateCurve
  };
  virtual RTTI rtti() const = 0;

  PlotToolInterface(AxisRect2D *axisrect);
  virtual ~PlotToolInterface();

 protected:
  AxisRect2D *axisrect_;
};

class MultiPeakFitTool : public QObject, public PlotToolInterface {
  Q_OBJECT
 public:
  MultiPeakFitTool(AxisRect2D *axisrect, ApplicationWindow *app,
                   MultiPeakFit::PeakProfile profile, int num_peaks,
                   const QObject *status_target, const char *status_slot);
  virtual RTTI rtti() const { return MultiPeak; }
  virtual ~MultiPeakFitTool();
 signals:
  /*! Emitted whenever a new message should be presented to the user.
   *
   * You don't have to connect to this signal if you alreay specified a reciever
   * during initialization.
   */
  void statusText(const QString &);
 protected slots:
  void selectPeak(PlotData::AssociatedData *associateddata, int point_index);

 private:
  void finalize();
  MultiPeakFit::PeakProfile d_profile;
  int d_num_peaks, d_selected_peaks;
  //DataPickerTool *d_picker_tool;
  MultiPeakFit *d_fit;
};

#endif  // MULTI_PEAK_FIT_TOOL
