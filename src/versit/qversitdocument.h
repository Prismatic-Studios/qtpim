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

#ifndef QVERSITDOCUMENT_H
#define QVERSITDOCUMENT_H

#include <qversitglobal.h>

#include <QList>
#include <QSharedDataPointer>
#include <QVariant>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QTextCodec;
QT_END_NAMESPACE

QTPIM_BEGIN_NAMESPACE

class QVersitDocumentPrivate;
class QVersitProperty;

class Q_VERSIT_EXPORT QVersitDocument
{
public:
    enum VersitType {
        InvalidType,
        VCard21Type,    // vCard version 2.1
        VCard30Type,    // vCard version 3.0 (RFC 2426)
        VCard40Type,    // vCard version 4.0
        ICalendar20Type,// iCalendar version 2.0 (RFC 2445/5545)
    };

    QVersitDocument();
    QVersitDocument(const QVersitDocument& other);
    QVersitDocument(VersitType type);
    ~QVersitDocument();

    QVersitDocument& operator=(const QVersitDocument& other);
    bool operator==(const QVersitDocument& other) const;
    bool operator!=(const QVersitDocument& other) const;

    // Metadata about the versit document
    // The type determines the format for serialization
    void setType(VersitType type);
    VersitType type() const;

    // The componentType is the value of the BEGIN property
    void setComponentType(QString componentType);
    QString componentType() const;

    // The content
    void addProperty(const QVersitProperty& property);
    void removeProperty(const QVersitProperty& property);
    void removeProperties(const QString& name);
    void setProperties(const QList<QVersitProperty>& properties);
    QList<QVersitProperty> properties() const;

    void addSubDocument(const QVersitDocument& subdocument);
    void removeSubDocument(const QVersitDocument& subdocument);
    void setSubDocuments(const QList<QVersitDocument>& documents);
    QList<QVersitDocument> subDocuments() const;

    bool isEmpty() const;
    void clear();

private:

    QSharedDataPointer<QVersitDocumentPrivate> d;
};

Q_VERSIT_EXPORT uint qHash(const QVersitDocument& key);
#ifndef QT_NO_DEBUG_STREAM
Q_VERSIT_EXPORT QDebug operator<<(QDebug dbg, const QVersitDocument& property);
#endif

QTPIM_END_NAMESPACE

Q_DECLARE_METATYPE(QTPIM_PREPEND_NAMESPACE(QVersitDocument))

#endif // QVERSITDOCUMENT_H
