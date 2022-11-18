#include "aSettingsListView.h"

#include <QPainter>

aSettingsListView::aSettingsListView(QWidget *parent) : QListView(parent) {
  // Set listview color to window base color & set alpha to 0
  QString listview_color =
      "QListView{background-color : rgba(0,0,0,0); border: 0 rgba(0,0,0,0);}";
  setStyleSheet(listview_color);

  // General settings for grid icon view
  setViewMode(QListView::IconMode);
  setIconSize(QSize(32, 32));
  setWordWrap(true);
  setGridSize(QSize(100, 100));
  setResizeMode(QListView::Adjust);
  setDragEnabled(false);
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setMouseTracking(true);
  setFrameShape(QFrame::NoFrame);
  viewport()->setAttribute(Qt::WA_Hover);
  setMovement(QListView::Static);
  setFocusPolicy(Qt::NoFocus);

  // Set listview hight appropriately
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

aSettingsListView::~aSettingsListView() {}

bool aSettingsListView::autoAdjustHeight() {
  if (!isVisible()) {
    return false;
  }

  if (model()->rowCount() > 0) {
    const int firstItemRectBottom = visualRect(model()->index(0, 0)).bottom();
    const int lastItemRectBottom =
        visualRect(model()->index(model()->rowCount() - 1, 0)).bottom();
    const int gridHeight = gridSize().height();
    const int final =
        (((lastItemRectBottom - firstItemRectBottom) / gridHeight) + 1) *
        gridHeight;
    setFixedHeight(final + listViewHeightPadding_);
  } else {
    setFixedHeight(0);
  }
  return true;
}
