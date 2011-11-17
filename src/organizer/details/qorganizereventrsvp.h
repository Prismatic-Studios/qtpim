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

#ifndef QORGANIZEREVENTRSVP_H
#define QORGANIZEREVENTRSVP_H

#include <qorganizereventattendee.h>
#include <qorganizeritemdetail.h>

QTORGANIZER_BEGIN_NAMESPACE

class Q_ORGANIZER_EXPORT QOrganizerEventRsvp : public QOrganizerItemDetail
{
public:
    Q_DECLARE_CUSTOM_ORGANIZER_DETAIL(QOrganizerEventRsvp, "Rsvp")
    const static QString FieldParticipationStatus;
    const static QString FieldParticipationRole;
    const static QString FieldResponseRequirement;
    const static QString FieldResponseDeadline;
    const static QString FieldResponseDate;
    const static QString FieldOrganizerName;
    const static QString FieldOrganizerEmail;

    enum ResponseRequirement {
        ResponseNotRequired = 0,
        ResponseRequired = 1
    };

    void setParticipationStatus(QOrganizerEventAttendee::ParticipationStatus status);
    QOrganizerEventAttendee::ParticipationStatus participationStatus() const;

    void setParticipationRole(QOrganizerEventAttendee::ParticipationRole role);
    QOrganizerEventAttendee::ParticipationRole participationRole() const;

    void setResponseRequirement(ResponseRequirement responseRequirement);
    ResponseRequirement responseRequirement() const;

    void setResponseDeadline(const QDate &date);
    QDate responseDeadline() const;

    void setResponseDate(const QDate &date);
    QDate responseDate() const;

    void setOrganizerName(const QString &name);
    QString organizerName() const;

    void setOrganizerEmail(const QString &email);
    QString organizerEmail() const;
};

QTORGANIZER_END_NAMESPACE

#endif// QORGANIZEREVENTRSVP_H
