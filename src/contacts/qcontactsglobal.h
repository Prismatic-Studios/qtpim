/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd and/or its subsidiary(-ies).
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtContacts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QTCONTACTSGLOBAL_H
#define QTCONTACTSGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QT_NAMESPACE)
#  define QTCONTACTS_PREPEND_NAMESPACE(name) ::QT_NAMESPACE::QtContacts::name
#  define QT_BEGIN_NAMESPACE_CONTACTS namespace QT_NAMESPACE { namespace QtContacts {
#  define QT_END_NAMESPACE_CONTACTS } }
#  define QTCONTACTS_USE_NAMESPACE using namespace QT_NAMESPACE; using namespace QtContacts;
#else
#  define QTCONTACTS_PREPEND_NAMESPACE(name) ::QtContacts::name
#  define QT_BEGIN_NAMESPACE_CONTACTS namespace QtContacts {
#  define QT_END_NAMESPACE_CONTACTS }
#  define QTCONTACTS_USE_NAMESPACE using namespace QtContacts;
#endif

#ifndef QT_STATIC
#  if defined(QT_BUILD_CONTACTS_LIB)
#    define Q_CONTACTS_EXPORT Q_DECL_EXPORT
#  else
#    define Q_CONTACTS_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_CONTACTS_EXPORT
#endif

#define QTCONTACTS_VERSION_NAME "org.qt-project.Qt.contacts.api.version"
#define QTCONTACTS_IMPLEMENTATION_VERSION_NAME "org.qt-project.Qt.contacts.implementation.version"

QT_BEGIN_NAMESPACE_CONTACTS
QT_END_NAMESPACE_CONTACTS

#endif // QTCONTACTSGLOBAL_H
