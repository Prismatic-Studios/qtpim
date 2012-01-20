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

#include "qcontactobserver.h"
#include "qcontactid.h"
#include "qcontactmanager_p.h"

QTCONTACTS_BEGIN_NAMESPACE

class QContactObserverPrivate
{
    public:
        QContactLocalId m_localId;
        QWeakPointer<QContactManager> m_manager;
};

/*!
  \class QContactObserver
  \brief The QContactObserver class is a simple class that emits a signal when a single particular
  contact is updated or deleted.
  \inmodule QtContacts

  \ingroup contacts-main
 */

/*!
  Constructs a QContactObserver to observe the contact in \a manager with the
  given \a localId and \a parent object.
 */
QContactObserver::QContactObserver(QContactManager* manager,
                                   QContactLocalId localId,
                                   QObject* parent)
    : QObject(parent),
      d(new QContactObserverPrivate)
{
    d->m_localId = localId;
    d->m_manager = manager;
    QContactManagerData::registerObserver(manager, this);
}

/*!
  Destroys this observer.
 */
QContactObserver::~QContactObserver()
{
    if (!d->m_manager.isNull()) {
        QContactManagerData::unregisterObserver(d->m_manager.data(), this);
    }
    delete d;
}

/*!
  Returns the local id of the contact that this object observes.
 */
QContactLocalId QContactObserver::contactLocalId() const {
    return d->m_localId;
}

/*!
  \fn QContactObserver::contactChanged()

  This signal is emitted when the observed contact is changed in the manager.
 */

/*!
  \fn QContactObserver::contactRemoved()

  This signal is emitted when the observed contact is removed from the manager.
 */

#include "moc_qcontactobserver.cpp"

QTCONTACTS_END_NAMESPACE
