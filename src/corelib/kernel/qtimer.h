/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTIMER_H
#define QTIMER_H

#ifndef QT_NO_QOBJECT

#include <QtCore/qbasictimer.h> // conceptual inheritance
#include <QtCore/qobject.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class Q_CORE_EXPORT QTimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool singleShot READ isSingleShot WRITE setSingleShot)
    Q_PROPERTY(int interval READ interval WRITE setInterval)
    Q_PROPERTY(Qt::TimerType timerType READ timerType WRITE setTimerType)
    Q_PROPERTY(bool active READ isActive)
public:
    explicit QTimer(QObject *parent = 0);
    ~QTimer();

    inline bool isActive() const { return id >= 0; }
    int timerId() const { return id; }

    void setInterval(int msec);
    int interval() const { return inter; }

    void setTimerType(Qt::TimerType atype) { this->type = atype; }
    Qt::TimerType timerType() const { return Qt::TimerType(type); }

    inline void setSingleShot(bool singleShot);
    inline bool isSingleShot() const { return single; }

    static void singleShot(int msec, QObject *receiver, const char *member);
    static void singleShot(int msec, Qt::TimerType timerType, QObject *receiver, const char *member);

public Q_SLOTS:
    void start(int msec);

    void start();
    void stop();

Q_SIGNALS:
    void timeout();

protected:
    void timerEvent(QTimerEvent *);

private:
    Q_DISABLE_COPY(QTimer)

    inline int startTimer(int){ return -1;}
    inline void killTimer(int){}

    int id, inter, del;
    uint single : 1;
    uint nulltimer : 1;
    uint type : 2;
    // reserved : 28
};

inline void QTimer::setSingleShot(bool asingleShot) { single = asingleShot; }

QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_QOBJECT

#endif // QTIMER_H
