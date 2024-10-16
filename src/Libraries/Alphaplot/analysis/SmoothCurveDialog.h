/***************************************************************************
    File                 : SmoothCurveDialog.h
    Project              : AlphaPlot
    --------------------------------------------------------------------
    Copyright            : (C) 2006 by Ion Vasilief, Tilman Benkert
    Email (use @ for *)  : ion_vasilief*yahoo.fr, thzs*gmx.net
    Description          : Smoothing options dialog

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
#ifndef SMOOTHDIALOG_H
#define SMOOTHDIALOG_H

#include <QDialog>
#include <Libraries/Alphaplot/AlphaplotGlobal.h>

class QPushButton;
class QComboBox;
class QSpinBox;
class AxisRect2D;
class ColorBox;

namespace Gui {
    class MainWindow;
}

//! Smoothing options dialog
class AlphaplotExport SmoothCurveDialog : public QDialog {
  Q_OBJECT

 public:
  SmoothCurveDialog(int method, QWidget* parent = nullptr,
                    Qt::WindowFlags fl = Qt::Widget);
  ~SmoothCurveDialog() {}

  QPushButton* btnSmooth;
  QPushButton* buttonCancel;
  QComboBox* boxName;
  QSpinBox *boxPointsLeft, *boxPointsRight, *boxOrder;
  ColorBox* boxColor;

 public Q_SLOTS:
  void setAxisRect(AxisRect2D* axisrect);
  void smooth();
  void activateCurve(const QString& curveName);

 private:
  AxisRect2D* axisrect_;
  Gui::MainWindow* app_;
  int smooth_method;
};

#endif  // SMOOTHDIALOG_H
