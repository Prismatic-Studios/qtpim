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

#ifndef QVERSITTIMEZONEHANDLER_H
#define QVERSITTIMEZONEHANDLER_H

#include <qversitorganizerglobal.h>
#include <QDateTime>

QTVERSITORGANIZER_BEGIN_NAMESPACE

class Q_VERSIT_ORGANIZER_EXPORT QVersitTimeZoneHandler
{
public:
    virtual ~QVersitTimeZoneHandler() {}

    /*!
      \fn QDateTime QVersitTimeZoneHandler::convertTimeZoneToUtc(const QDateTime& datetime, const QString& timeZoneName);
      Converts \a datetime to the local time for the time zone identified by \a timeZoneName.  The UTC
      offset of the time zone should be calculated taking into account the daylight savings rules that
      might apply at \a datetime.

      \a datetime must be specified with Qt::UTC.  The returned QDateTime will be specified with
      Qt::LocalTime.  Note that unlike the usual semantic of Qt::LocalTime, it does not represent a time
      in the system's local time zone.
      
      An invalid QDateTime is returned on failure (eg. if \a timeZoneName is unknown).
     */
    virtual QDateTime convertTimeZoneToUtc(const QDateTime& datetime, const QString& timeZoneName) = 0;

    /*!
      \fn QDateTime QVersitTimeZoneHandler::convertUtcToTimeZone(const QDateTime& datetime, const QString& timeZoneName);
      Converts \a datetime to UTC, treating \a datetime as if it were a local time for a time zone
      identified by \a timeZoneName.  The UTC offset of the time zone should be calculated taking into
      account the daylight savings rules that might apply at \a datetime.

      \a datetime must be specified with Qt::LocalTime.  Note that unlike the usual semantic of
      Qt::LocalTime, \a datetime does not represent a time in the system's local time zone.
      The returned QDateTime will be specified with Qt::UTC.
      
      An invalid QDateTime is returned on failure (eg. if \a timeZoneName is unknown).
     */
    virtual QDateTime convertUtcToTimeZone(const QDateTime& datetime, const QString& timeZoneName) = 0;
};

QTVERSITORGANIZER_END_NAMESPACE

#define QT_VERSIT_TIMEZONE_HANDLER_INTERFACE "com.nokia.qt.versitorganizer.timezonehandler/1.0"
QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(QtVersitOrganizer::QVersitTimeZoneHandler, QT_VERSIT_TIMEZONE_HANDLER_INTERFACE)
QT_END_NAMESPACE
#endif
