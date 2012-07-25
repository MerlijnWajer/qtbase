/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the plugins of the Qt Toolkit.
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qkmsintegration.h"
#include "qkmsdevice.h"
#include "qkmsscreen.h"
#include "qkmswindow.h"
#include "qkmsbackingstore.h"
#include "qkmscontext.h"
#include "qkmsnativeinterface.h"
#include "qkmsudevlistener.h"
#include "qkmsudevdrmhandler.h"

#include <QtPlatformSupport/private/qgenericunixeventdispatcher_p.h>
#include <QtPlatformSupport/private/qgenericunixfontdatabase_p.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtGui/QOpenGLContext>
#include <QtGui/QScreen>

QT_BEGIN_NAMESPACE

QKmsIntegration::QKmsIntegration()
    : QPlatformIntegration(),
      m_fontDatabase(new QGenericUnixFontDatabase()),
      m_eventDispatcher(createUnixEventDispatcher()),
      m_nativeInterface(new QKmsNativeInterface),
      m_udevListener(new QKmsUdevListener)
{
    QGuiApplicationPrivate::instance()->setEventDispatcher(m_eventDispatcher);
    setenv("EGL_PLATFORM", "drm",1);
    m_drmHandler = new QKmsUdevDRMHandler(this);
    m_udevListener->addHandler(m_drmHandler);
}

QKmsIntegration::~QKmsIntegration()
{
    foreach (QKmsDevice *device, m_devices) {
        delete device;
    }
    foreach (QPlatformScreen *screen, m_screens) {
        delete screen;
    }
    delete m_fontDatabase;
    delete m_udevListener;
}

QObject *QKmsIntegration::createDevice(const char *path)
{
    QKmsDevice *device = new QKmsDevice(path, this);
    m_devices.append(device);
    return device;
}

bool QKmsIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case OpenGL: return true;
    case ThreadedOpenGL: return false;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformOpenGLContext *QKmsIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    QKmsScreen *screen = static_cast<QKmsScreen *>(context->screen()->handle());
    return new QKmsContext(context, screen->device());
}

QPlatformWindow *QKmsIntegration::createPlatformWindow(QWindow *window) const
{
    QKmsWindow *w = new QKmsWindow(window);
    w->requestActivateWindow();
    return w;
}

QPlatformBackingStore *QKmsIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new QKmsBackingStore(window);
}

QPlatformFontDatabase *QKmsIntegration::fontDatabase() const
{
    return m_fontDatabase;
}

void QKmsIntegration::addScreen(QKmsScreen *screen)
{
    m_screens.append(screen);
    screenAdded(screen);
}

QAbstractEventDispatcher *QKmsIntegration::guiThreadEventDispatcher() const
{
    return m_eventDispatcher;
}

QPlatformNativeInterface *QKmsIntegration::nativeInterface() const
{
    return m_nativeInterface;
}

QT_END_NAMESPACE
