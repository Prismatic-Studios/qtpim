/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Mobility Components.
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

#ifndef QCONTACTFILTER_P_H
#define QCONTACTFILTER_P_H

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

#include "qcontactfilter.h"
#include <QSharedData>
#include <QDataStream>

#ifndef QT_NO_DEBUG_STREAM
#include <QDebug>
#endif

/* Boiler plate code */
#define Q_IMPLEMENT_CONTACTFILTER_PRIVATE(Class) \
    Class##Private* Class::d_func() { return reinterpret_cast<Class##Private *>(d_ptr.data()); } \
    const Class##Private* Class::d_func() const { return reinterpret_cast<const Class##Private *>(d_ptr.constData()); } \
    Class::Class(const QContactFilter& other) : QContactFilter() { Class##Private::copyIfPossible(d_ptr, other); }

#define Q_IMPLEMENT_CONTACTFILTER_VIRTUALCTORS(Class, Type) \
    QContactFilterPrivate* clone() const { return new Class##Private(*this); } \
    virtual QContactFilter::FilterType type() const {return Type;} \
    static void copyIfPossible(QSharedDataPointer<QContactFilterPrivate>& d_ptr, const QContactFilter& other) \
    { \
        if (other.type() == Type) \
            d_ptr = extract_d(other); \
        else \
            d_ptr = new Class##Private; \
    }

QTCONTACTS_BEGIN_NAMESPACE
class QContactFilterPrivate : public QSharedData
{
public:
    QContactFilterPrivate()
    {
    }

    virtual ~QContactFilterPrivate()
    {
    }

    virtual bool compare(const QContactFilterPrivate* other) const = 0;
    virtual QDataStream& outputToStream(QDataStream& stream, quint8 formatVersion) const = 0;
    virtual QDataStream& inputFromStream(QDataStream& stream, quint8 formatVersion) = 0;
#ifndef QT_NO_DEBUG_STREAM
    // NOTE: on platforms where Qt is built without debug streams enabled, vtable will differ!
    virtual QDebug& debugStreamOut(QDebug& dbg) const = 0;
#endif
    virtual QContactFilterPrivate* clone() const = 0;
    virtual QContactFilter::FilterType type() const = 0;

    /* Helper functions for C++ protection rules */
    static const QSharedDataPointer<QContactFilterPrivate>& extract_d(const QContactFilter& other) {return other.d_ptr;}
};
QTCONTACTS_END_NAMESPACE

QT_BEGIN_NAMESPACE
#if defined(Q_CC_MWERKS)
// This results in multiple symbol definition errors on all other compilers
// but not having a definition here results in an attempt to use the unspecialized
// clone (which fails because of the pure virtuals above)
template<> QTCONTACTS_PREPEND_NAMESPACE(QContactFilterPrivate) *QSharedDataPointer<QTCONTACTS_PREPEND_NAMESPACE(QContactFilterPrivate)>::clone()
{
    return d->clone();
}
#else
template<> QTCONTACTS_PREPEND_NAMESPACE(QContactFilterPrivate) *QSharedDataPointer<QTCONTACTS_PREPEND_NAMESPACE(QContactFilterPrivate)>::clone();
#endif
QT_END_NAMESPACE


#endif
