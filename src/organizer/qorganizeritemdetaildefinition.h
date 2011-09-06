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


#ifndef QORGANIZERITEMDETAILDEFINITION_H
#define QORGANIZERITEMDETAILDEFINITION_H

#include <QStringList>
#include <QString>
#include <QSharedDataPointer>
#include <QVariant>

#include "qorganizerglobal.h"
#include "qorganizeritemdetailfielddefinition.h"

class QDataStream;

QTPIM_BEGIN_NAMESPACE

class QOrganizerItemDetailDefinitionData;
class Q_ORGANIZER_EXPORT QOrganizerItemDetailDefinition
{
    friend class QOrganizerManager;

public:
    // default constructor: produces an invalid QOrganizerItemFieldDefinition.
    QOrganizerItemDetailDefinition();
    ~QOrganizerItemDetailDefinition();

    /* copy ctor & assignment */
    QOrganizerItemDetailDefinition(const QOrganizerItemDetailDefinition& other);
    QOrganizerItemDetailDefinition& operator=(const QOrganizerItemDetailDefinition& other);

    /* Comparator (for use in lists) */
    bool operator==(const QOrganizerItemDetailDefinition& other) const;
    bool operator!=(const QOrganizerItemDetailDefinition& other) const {return !operator==(other);}

    /* Check emptiness */
    bool isEmpty() const;

    /* name (identifier) of the definition */
    void setName(const QString& definitionName);
    QString name() const;

    /* can you have more than one detail of this definition? */
    void setUnique(bool unique);
    bool isUnique() const;

    /* Mapping of field key to fields allowed in details of this definition */
    void setFields(const QMap<QString, QOrganizerItemDetailFieldDefinition>& fields);
    QMap<QString, QOrganizerItemDetailFieldDefinition> fields() const;
    void insertField(const QString& key, const QOrganizerItemDetailFieldDefinition& field);
    void removeField(const QString& key);

private:
    QSharedDataPointer<QOrganizerItemDetailDefinitionData> d;
};

#ifndef QT_NO_DATASTREAM
Q_ORGANIZER_EXPORT QDataStream& operator<<(QDataStream& out, const QOrganizerItemDetailDefinition& definition);
Q_ORGANIZER_EXPORT QDataStream& operator>>(QDataStream& in, QOrganizerItemDetailDefinition& definition);
#endif

#ifndef QT_NO_DEBUG_STREAM
Q_ORGANIZER_EXPORT QDebug operator<<(QDebug dbg, const QOrganizerItemDetailDefinition& definition);
#endif

QTPIM_END_NAMESPACE

Q_DECLARE_TYPEINFO(QTPIM_PREPEND_NAMESPACE(QOrganizerItemDetailDefinition), Q_MOVABLE_TYPE);

#endif
