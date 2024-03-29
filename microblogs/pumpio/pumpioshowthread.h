/*
    This file is part of Choqok, the KDE micro-blogging client

    Copyright (C) 2013  Andrea Scarpino <scarpino@kde.org>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.


    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, see http://www.gnu.org/licenses/
*/

#ifndef PUMPIOSHOWTHREAD_H
#define PUMPIOSHOWTHREAD_H

#include <QWidget>

#include "account.h"
#include "choqoktypes.h"

#include "ui_pumpioshowthread.h"

namespace Choqok {
    namespace UI {
        class PostWidget;
    }
}

class PumpIOShowThread : public QWidget, Ui::PumpIOShowThread
{
    Q_OBJECT
public:
    explicit PumpIOShowThread(Choqok::Account *account, Choqok::Post *post,
                              QWidget* parent = 0);
    virtual ~PumpIOShowThread();

protected Q_SLOTS:
    void slotAddPost(Choqok::Account*, Choqok::Post*);

private:
    class Private;
    Private * const d;
};

#endif // PUMPIOSHOWTHREAD_H
