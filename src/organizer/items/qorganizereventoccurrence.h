/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef QORGANIZEREVENTOCCURRENCE_H
#define QORGANIZEREVENTOCCURRENCE_H

#include "qorganizer.h"
#include "qorganizeritempriority.h"

QTPIM_BEGIN_NAMESPACE

class Q_ORGANIZER_EXPORT QOrganizerEventOccurrence : public QOrganizerItem
{
public:

#ifdef Q_QDOC
    static const QLatin1Constant QOrganizerEventOccurrence;
#else
    Q_DECLARE_CUSTOM_ORGANIZER_ITEM(QOrganizerEventOccurrence, QOrganizerItemType::TypeEventOccurrence)
#endif

    void setStartDateTime(const QDateTime& startDateTime);
    QDateTime startDateTime() const;
    void setEndDateTime(const QDateTime& endDateTime);
    QDateTime endDateTime() const;

    void setParentId(const QOrganizerItemId& parentId);
    QOrganizerItemId parentId() const;
    void setOriginalDate(const QDate& date);
    QDate originalDate() const;

    void setPriority(QOrganizerItemPriority::Priority);
    QOrganizerItemPriority::Priority priority() const;

    QString location() const;
    void setLocation(const QString& location);
};

QTPIM_END_NAMESPACE

#endif
