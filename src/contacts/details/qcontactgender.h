/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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

#ifndef QCONTACTGENDER_H
#define QCONTACTGENDER_H

#include <QString>

#include <qcontactsglobal.h>
#include <qcontactdetail.h>
#include <qcontact.h>

QTPIM_BEGIN_NAMESPACE

/* Leaf class */
class Q_CONTACTS_EXPORT QContactGender : public QContactDetail
{
public:
#ifdef Q_QDOC
    static const QLatin1Constant DefinitionName;
    static const QLatin1Constant FieldGender;
    static const QLatin1Constant GenderMale;
    static const QLatin1Constant GenderFemale;
    static const QLatin1Constant GenderUnspecified;
#else
    Q_DECLARE_CUSTOM_CONTACT_DETAIL(QContactGender, "Gender")
    Q_DECLARE_LATIN1_CONSTANT(FieldGender, "Gender");
    Q_DECLARE_LATIN1_CONSTANT(GenderMale, "Male");
    Q_DECLARE_LATIN1_CONSTANT(GenderFemale, "Female");
    Q_DECLARE_LATIN1_CONSTANT(GenderUnspecified, "Unspecified");
#endif

    void setGender(const QString& gender) {setValue(FieldGender, gender);}
    QString gender() const {return value(FieldGender);}
};

QTPIM_END_NAMESPACE

#endif

