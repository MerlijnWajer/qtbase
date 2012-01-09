/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the QtTest module of the Qt Toolkit.
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

#ifndef QTESTXUNITSTREAMER_P_H
#define QTESTXUNITSTREAMER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE


class QTestElement;
class QTestElementAttribute;
class QXunitTestLogger;
struct QTestCharBuffer;

class QTestXunitStreamer
{
    public:
        QTestXunitStreamer(QXunitTestLogger *logger);
        ~QTestXunitStreamer();

        void formatStart(const QTestElement *element, QTestCharBuffer *formatted) const;
        void formatEnd(const QTestElement *element, QTestCharBuffer *formatted) const;
        void formatAfterAttributes(const QTestElement *element, QTestCharBuffer *formatted) const;
        void formatAttributes(const QTestElement *element, const QTestElementAttribute *attribute, QTestCharBuffer *formatted) const;
        void output(QTestElement *element) const;
        void outputElements(QTestElement *element, bool isChildElement = false) const;
        void outputElementAttributes(const QTestElement *element, QTestElementAttribute *attribute) const;

        void outputString(const char *msg) const;

    private:
        void displayXunitXmlHeader() const;
        static void indentForElement(const QTestElement* element, char* buf, int size);

        QXunitTestLogger *testLogger;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif
