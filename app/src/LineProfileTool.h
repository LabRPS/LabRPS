#ifndef LINE_PROFILE_TOOL_H
#define LINE_PROFILE_TOOL_H

#include "PlotToolInterface.h"
#include "core/column/Column.h"

#include <QWidget>

class QPoint;
class QImage;
class ImageMarker;

/*!\brief Plot tool for calculating intensity profiles of image markers along a
 * line.
 *
 * It is assumed that on the parent Graph an ImageMarker is selected. During
 * initialization,
 * a pointer to this marker is stored and the selection is removed. The
 * LineProfileTool
 * adds itself as a full-sized child widget to the Graph's canvas, allowing for
 * fast redraws
 * while selection of the line is in progress. Once the line is selected (mouse
 * button is
 * released), the profile is calculate and displayed, a new LineMarker denoting
 * the selected
 * profile line is added to the Graph and the LineProfileTool deletes itself by
 * setting the
 * Graph's active tool to NULL.
 *
 * \section future_plans Future Plans
 * Actually, image analysis doesn't fit terribly well into the Graph framework.
 * A cleaner approach would be to add a new MyWidget subclass (Image?) that
 * operates on a single
 * image, providing things like line profiles, intensity tables and measuring
 * points on scanned graphs
 * (simple <a href="http://www.frantz.fi/software/g3data.php">g3data</a>-like
 * functionality).
 * There could be facilities for making an Image from an ImageMarker and vice
 * versa
 * (if that's really needed).
 * [ postponed until after the redesign of project handling ]
 */
class LineProfileTool : public QWidget, public PlotToolInterface {
  Q_OBJECT

 public:
  //! Standard constructor.
  LineProfileTool(Graph *graph, int average_pixels);
  virtual RTTI rtti() const { return LineProfile; }
  void calculateLineProfile(const QPoint &start, const QPoint &end);

 signals:
  /*! Emitted whenever a new message should be presented to the user.
   *
   * You don't have to connect to this signal if you alreay specified a reciever
   * during initialization.
   */
  void statusText(const QString &);
  void createTablePlot(const QString &, const QString &, QList<Column *>);

 protected:
  int averageImagePixel(const QImage &image, int px, int py,
                        bool moreHorizontal);
  void addLineMarker(const QPoint &start, const QPoint &end);
  /*!\brief Draw line during operation (replaced by a LineMarker at the end).
   */
  virtual void paintEvent(QPaintEvent *e);
  /*!\brief Pressing the left mouse button starts line selection.
   *
   * Clicks with anything else than the left button are propagated to the parent
   * as usual.
   */
  virtual void mousePressEvent(QMouseEvent *e);
  /*!\brief Mouse movements need to be monitored for updating the line during
   * operation.
   */
  virtual void mouseMoveEvent(QMouseEvent *e);
  /*!\brief Mouse releases end line selection and cause the profile to be
   * displayed.
   */
  virtual void mouseReleaseEvent(QMouseEvent *e);

 private:
  //! Number of image pixels over which to average.
  int d_average_pixels;
  //! The image marker to operate on.
  ImageMarker *d_target;
  /*!\brief Mouse position where an operation started.
   */
  QPoint d_op_start;
  //! Difference between current and start position during operation.
  QPoint d_op_dp;
};

#endif  // LINE_PROFILE_TOOL_H
