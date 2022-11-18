/****************************************************************************

	GLWidget Class
	Copyright (C) 2009-2012 Andre Deperrois adeperrois@xflr5.com

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#include "GLWidget.h"

#include <QtOpenGL>
#include <math.h>


GLWidget::GLWidget(QWidget *parent)
    : QGLViewer(parent)
{
    setAttribute(Qt::WA_AcceptTouchEvents, true);
	setAutoFillBackground(false);  // prevent QPainter from filling the background
	setCursor(Qt::CrossCursor);
}

void GLWidget::draw() {
	// Save current OpenGL state
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	
	// Restore OpenGL state
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}

void GLWidget::paintEvent(QPaintEvent */*event*/) {

}

void GLWidget::overpaint(QPainter &painter) {
//	/* draw the text collected with overpaintText */
//	painter.setPen(g_mainFrame->m_TextColor);
//    for (int i = 0; i < m_overpaintText.size(); ++i) {
//        if (m_overpaintFont.contains(i)) {
//            painter.setFont(m_overpaintFont[i]);
//        }
//        painter.drawText(m_overpaintText[i].first, m_overpaintText[i].second);
//    }
//	m_overpaintFont.clear();
//	m_overpaintText.clear();
	

}

void GLWidget::overpaintText(double x, double y, double z, QString text) {
	qglviewer::Vec position = camera()->projectedCoordinatesOf(qglviewer::Vec(x, y, z));
	m_overpaintText.append(QPair<QPoint, QString> (QPoint(position.x, position.y), text));
}

void GLWidget::setOverpaintFont(QFont font) {
	m_overpaintFont[m_overpaintText.size()] = font;
}
