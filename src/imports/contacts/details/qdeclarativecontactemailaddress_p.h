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

#ifndef QDECLARATIVECONTACTEMAILADDRESS_H
#define QDECLARATIVECONTACTEMAILADDRESS_H

#include <QtContacts/qcontactemailaddress.h>

#include "qdeclarativecontactdetail_p.h"

QTCONTACTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE

class QDeclarativeContactEmailAddress : public QDeclarativeContactDetail
{
    Q_OBJECT
    Q_PROPERTY(QString emailAddress READ emailAddress WRITE setEmailAddress NOTIFY valueChanged)
    Q_ENUMS(FieldType)
public:
    enum FieldType {
        EmailAddress = QContactEmailAddress::FieldEmailAddress
    };
    QDeclarativeContactEmailAddress(QObject* parent = 0)
        :QDeclarativeContactDetail(parent)
    {
        setDetail(QContactEmailAddress());
        connect(this, SIGNAL(valueChanged()), SIGNAL(detailChanged()));
    }

    DetailType detailType() const
    {
        return QDeclarativeContactDetail::Email;
    }

    void setEmailAddress(const QString& v)
    {
        if (!readOnly() && v != emailAddress()) {
            detail().setValue(QContactEmailAddress::FieldEmailAddress, v);
            emit valueChanged();
        }
    }
    QString emailAddress() const {return detail().value(QContactEmailAddress::FieldEmailAddress).toString();}

signals:
    void valueChanged();
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeContactEmailAddress)

#endif // QDECLARATIVECONTACTEMAILADDRESS_H
