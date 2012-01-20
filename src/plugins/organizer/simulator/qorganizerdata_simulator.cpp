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

#include "qorganizerdata_simulator_p.h"
#include "qorganizeritemengineid.h"
#include "engines/qorganizeritemmemorybackend_p.h"

#include <QtCore/QDataStream>

QDataStream &operator<<(QDataStream &out, const QtMobility::Simulator::SaveOrganizerItemReply &s)
{
    out << s.savedItem << static_cast<int>(s.error);
    return out;
}

QDataStream &operator>>(QDataStream &in, QtMobility::Simulator::SaveOrganizerItemReply &s)
{
    int errorInt;
    in >> s.savedItem >> errorInt;
    s.error = static_cast<QtMobility::QOrganizerManager::Error>(errorInt);
    return in;
}

QDataStream &operator<<(QDataStream &out, const QtMobility::Simulator::SaveOrganizerCollectionReply &s)
{
    out << s.savedCollection << static_cast<int>(s.error);
    return out;
}

QDataStream &operator>>(QDataStream &in, QtMobility::Simulator::SaveOrganizerCollectionReply &s)
{
    int errorInt;
    in >> s.savedCollection >> errorInt;
    s.error = static_cast<QtMobility::QOrganizerManager::Error>(errorInt);
    return in;
}

QDataStream &operator<<(QDataStream &out, const QtMobility::Simulator::OrganizerItemId &s)
{
    out << s.id;
    return out;
}

QDataStream &operator>>(QDataStream &in, QtMobility::Simulator::OrganizerItemId &s)
{
    in >> s.id;
    return in;
}

QDataStream &operator<<(QDataStream &out, const QtMobility::Simulator::OrganizerCollectionId &s)
{
    out << s.id;
    return out;
}

QDataStream &operator>>(QDataStream &in, QtMobility::Simulator::OrganizerCollectionId &s)
{
    in >> s.id;
    return in;
}

QTM_BEGIN_NAMESPACE

void qt_registerOrganizerTypes()
{
    qRegisterMetaTypeStreamOperators<QOrganizerItem>("QtMobility::QOrganizerItem");
    qRegisterMetaTypeStreamOperators<QOrganizerCollection>("QtMobility::QOrganizerCollection");
    qRegisterMetaTypeStreamOperators<QOrganizerItemId>("QtMobility::QOrganizerItemId");
    qRegisterMetaTypeStreamOperators<QOrganizerCollectionId>("QtMobility::QOrganizerCollectionId");
    qRegisterMetaTypeStreamOperators<QOrganizerItemDetailDefinition>("QtMobility::QOrganizerItemDetailDefinition");
    qRegisterMetaTypeStreamOperators<Simulator::OrganizerItemId>("QtMobility::Simulator::OrganizerItemId");
    qRegisterMetaTypeStreamOperators<Simulator::OrganizerCollectionId>("QtMobility::Simulator::OrganizerCollectionId");
    qRegisterMetaTypeStreamOperators<Simulator::SaveOrganizerItemReply>("QtMobility::Simulator::SaveOrganizerItemReply");
    qRegisterMetaTypeStreamOperators<Simulator::SaveOrganizerCollectionReply>("QtMobility::Simulator::SaveOrganizerCollectionReply");
}

QTM_END_NAMESPACE
