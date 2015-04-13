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

#ifndef QCONTACTORGANIZATION_H
#define QCONTACTORGANIZATION_H

#include <QtCore/qurl.h>

#include <QtContacts/qcontactdetail.h>

QT_BEGIN_NAMESPACE_CONTACTS

/* Leaf class */
class Q_CONTACTS_EXPORT QContactOrganization : public QContactDetail
{
public:
#ifndef Q_QDOC
    Q_DECLARE_CUSTOM_CONTACT_DETAIL(QContactOrganization)
#else
    static const DetailType Type;
#endif

    enum OrganizationField {
        FieldName = 0,
        FieldLogoUrl,
        FieldDepartment,
        FieldLocation,
        FieldRole,
        FieldTitle,
        FieldAssistantName,
    };

    void setName(const QString& name) {setValue(FieldName, name);}
    QString name() const {return value(FieldName).toString();}
    void setLogoUrl(const QUrl& logo) {setValue(FieldLogoUrl, logo);}
    QUrl logoUrl() const {return value<QUrl>(FieldLogoUrl);}
    void setDepartment(const QStringList& department) {setValue(FieldDepartment, department);}
    QStringList department() const {return value<QStringList>(FieldDepartment);}
    void setLocation(const QString& location) {setValue(FieldLocation, location);}
    QString location() const {return value(FieldLocation).toString();}
    void setRole(const QString& role) {setValue(FieldRole, role);}
    QString role() const {return value(FieldRole).toString();}
    void setTitle(const QString& title) {setValue(FieldTitle, title);}
    QString title() const {return value(FieldTitle).toString();}
    void setAssistantName(const QString& assistantName) {setValue(FieldAssistantName, assistantName);}
    QString assistantName() const {return value(FieldAssistantName).toString();}
};

QT_END_NAMESPACE_CONTACTS

#endif // QCONTACTORGANIZATION_H
