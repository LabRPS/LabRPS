/***************************************************************************
 *   Copyright (c) 2010 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the LabRPS CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/

#include "PreCompiled.h"
#ifndef _PreComp_
# include <QAbstractItemModel>
# include <QAbstractItemView>
# include <QItemSelection>
# include <QItemSelectionModel>
#endif

#include <App/DocumentObject.h>

#include "Utilities.h"


using namespace Gui;

class ItemViewSelection::MatchName {
public:
    MatchName(const QString& n) : name(n)
    {}
    bool operator() (const App::DocumentObject* obj) {
        return name == QLatin1String(obj->getNameInDocument());
    }
private:
    QString name;
};

ItemViewSelection::ItemViewSelection(QAbstractItemView* view)
  : view(view)
{
}

void ItemViewSelection::applyFrom(const std::vector<App::DocumentObject*> objs)
{
    QAbstractItemModel* model = view->model();
    QItemSelection range;
    for (int i=0; i<model->rowCount(); i++) {
        QModelIndex item = model->index(i,0);
        if (item.isValid()) {
            QVariant name = model->data(item, Qt::UserRole);
            std::vector<App::DocumentObject*>::const_iterator it;
            it = std::find_if(objs.begin(), objs.end(), MatchName(name.toString()));
            if (it != objs.end())
                range.select(item, item);
        }
    }

    view->selectionModel()->select(range, QItemSelectionModel::Select);
}
