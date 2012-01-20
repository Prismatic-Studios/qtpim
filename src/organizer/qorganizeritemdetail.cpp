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

#include <qorganizeritemdetail.h>
#include <private/qorganizeritemdetail_p.h>
#include <qorganizeritemrecurrence.h>

#include <qdebug.h>
#include <qdatastream.h>

QTORGANIZER_BEGIN_NAMESPACE

/*!
    \class QOrganizerItemDetail

    \brief The QOrganizerItemDetail class represents a single, complete detail about an organizer item.
    \inmodule QtOrganizer
    \ingroup organizer-main

    All of the information for an organizer item is stored in one or more QOrganizerItemDetail objects.

    A detail is a group of logically related bits of data - for example, a QOrganizerItemTimestamp is a single
    detail that has multiple fields (timestamp of creation, timestamp of last update, etc). Different organizer
    managers may support different details for different item types, e.g. certain manager may not support the
    timestamp, while others do.

    In general, QOrganizerItemDetail and the built in subclasses (like \l QOrganizerEventTime) provide
    convenience and standardized access to values. For example, \l QOrganizerEventTime provides a
    convenient API for manipulating a QOrganizerItemDetail to describe the start and end time of an
    event. Subclasses also provide constants for the names of fields (like \l QOrganizerEventTime::FieldStartDateTime).
    Typically the constants for field names start with \c Field, and the constants for predefined values
    of a field start with the name of that field (e.g. \c TypeEvent is a predefined constant for \c FieldType).

    QOrganizerItemDetail objects act like type checked values.  In general, you can assign them
    to and fro and have reasonable behaviour, like the following example.

    \code
    QOrganizerItemDescription description;
    description.setDescription("Some descriptive text");
    // description.value(QOrganizerItemDescription::FieldDescription) == "Some descriptive text";
    // description.type() == QOrganizerItemDetail::TypeDescription

    QOrganizerItemDetail detail = description;
    // detail.value(QOrganizerItemDescription::FieldDescription) == "Some descriptive text";
    // detail.type() == QOrganizerItemDetail::TypeDescription

    QOrganizerItemDescription otherDescription = detail;
    // otherDescription.description() == "Some descriptive text";
    // otherDescription.type() == QOrganizerItemDetail::TypeDescription

    QOrganizerItemDisplayLabel label = detail;
    // label is now a default constructed QOrganizerItemDisplayLabel
    // label.value(QOrganizerItemDescription::FieldDescription) is empty
    // label.type() == QOrganizerItemDetail::TypeDisplayLabel

    QOrganizerItemDisplayLabel otherLabel = description;
    // otherLabel is now a default constructed QOrganizerItemDisplayLabel
    // otherLabel.value(QOrganizerItemDescription::FieldDescription) is empty
    // otherLabel.type() == QOrganizerItemDetail::TypeDisplayLabel
    \endcode

    \sa QOrganizerItem, QOrganizerItemDetailFilter, QOrganizerItemDetailRangeFilter
 */

/*!
    \enum QOrganizerItemDetail::DetailType

    This enumeration describes the type of the organizer item detail.

    \value TypeUndefined        This detail is of type undefined.
    \value TypeClassification   This detail is a classification.
    \value TypeComment          This detail is a comment
    \value TypeDescription      This detail is a description.
    \value TypeDisplayLabel     This detail is a display label.
    \value TypeItemType         This detail is an item type.
    \value TypeGuid             This detail is a GUID.
    \value TypeLocation         This detail is a location.
    \value TypeParent           This detail is a parent. Should not be used in parent items.
    \value TypePriority         This detail is a priority.
    \value TypeRecurrence       This detail is a recurrence. Should not be used in occurrences.
    \value TypeTag              This detail is a tag.
    \value TypeTimestamp        This detail is a timestamp.
    \value TypeReminder         This detail is a reminder. Should not be directly used.
    \value TypeAudibleReminder  This detail is an audible reminder.
    \value TypeEmailReminder    This detail is an email reminder.
    \value TypeVisualReminder   This detail is a visual reminder.
    \value TypeExtendedDetail   This detail is an extended detail.
    \value TypeEventAttendee    This detail is an event attendee.
    \value TypeEventRsvp        This detail is an event RSVP.
    \value TypeEventTime        This detail is an event time.
    \value TypeJournalTime      This detail is a journal time.
    \value TypeTodoTime         This detail is a TODO time.
    \value TypeTodoProgress     This detail is a TODO progress.
 */

/*!
    \internal
    \macro Q_DECLARE_CUSTOM_ORGANIZER_DETAIL
    \relates QOrganizerItemDetail

    Macro for simplifying declaring leaf detail classes.

    The first argument is the name of the class, and the second argument is the
    detail definition name.

    If you are creating a leaf detail class for a type of QOrganizerItemDetail,
    you should use this macro when declaring your class to ensure that
    it interoperates with other organizer item functionality.
 */


/*!
    \fn bool QOrganizerItemDetail::operator!=(const QOrganizerItemDetail &other) const

    Returns true if the values or id of this detail is different to those of the \a other detail
 */

/*!
    Constructs a new, empty detail.
 */
QOrganizerItemDetail::QOrganizerItemDetail()
    : d(new QOrganizerItemDetailPrivate)
{
}

/*!
    Constructs a new, empty detail of the \a detailType.
 */
QOrganizerItemDetail::QOrganizerItemDetail(DetailType detailType)
    : d(new QOrganizerItemDetailPrivate)
{
    d->m_detailType = detailType;
}

/*!
    Constructs a detail that is a copy of \a other.
 */
QOrganizerItemDetail::QOrganizerItemDetail(const QOrganizerItemDetail &other)
    : d(other.d)
{
}

/*!
    \internal

    Constructs a detail that is a copy of \a other if \a other is of the type
    identified by \a expectedDetailType, else constructs a new, empty detail of the
    type identified by the \a expectedDetailType.
*/
QOrganizerItemDetail::QOrganizerItemDetail(const QOrganizerItemDetail &other, DetailType expectedDetailType)
{
    if (other.d->m_detailType == expectedDetailType) {
        d = other.d;
    } else {
        d = new QOrganizerItemDetailPrivate;
        d->m_detailType = expectedDetailType;
    }
}

/*!
    Assigns this detail to \a other.
 */
QOrganizerItemDetail &QOrganizerItemDetail::operator=(const QOrganizerItemDetail &other)
{
    if (this != &other)
        d = other.d;
    return *this;
}

/*!
    \internal

    Assigns this detail to \a other if the type of \a other is that identified
    by the given \a expectedDetailType, else assigns this detail to be a new, empty
    detail of the type identified by the given \a expectedDetailType.
 */
QOrganizerItemDetail &QOrganizerItemDetail::assign(const QOrganizerItemDetail &other, DetailType expectedDetailType)
{
    if (this != &other) {
        if (other.d->m_detailType == expectedDetailType) {
            d = other.d;
        } else {
            d = new QOrganizerItemDetailPrivate;
            d->m_detailType = expectedDetailType;
        }
    }
    return *this;
}

/*!
    Frees the memory used by this detail.
 */
QOrganizerItemDetail::~QOrganizerItemDetail()
{
}

/*!
    Returns the detail type.
 */
QOrganizerItemDetail::DetailType QOrganizerItemDetail::type() const
{
    return d->m_detailType;
}

/*!
    To be removed soon, please use type() instead.
 */
QOrganizerItemDetail::DetailType QOrganizerItemDetail::definitionName() const
{
    return type();
}

/*!
    Compares this detail to \a other.  Returns true if the type and values of \a other are equal to those of this detail.
    The keys of each detail are not considered during the comparison, in order to allow details from different organizer items to
    be compared according to their values.
 */
bool QOrganizerItemDetail::operator==(const QOrganizerItemDetail &other) const
{
    if (!(d->m_detailType == other.d->m_detailType))
        return false;

    // QVariant doesn't support == on QOrganizerItemRecurrence - do it manually
    if (d->m_detailType == QOrganizerItemDetail::TypeRecurrence)
        return static_cast<QOrganizerItemRecurrence>(*this) == static_cast<QOrganizerItemRecurrence>(other);

    if (d->m_values != other.d->m_values)
        return false;

    return true;
}

bool compareOrganizerItemDetail(const QOrganizerItemDetail &one, const QOrganizerItemDetail &other)
{
    return (one.type() < other.type());
}

/*!
    Returns the hash value for \a key.
 */
uint qHash(const QOrganizerItemDetail &key)
{
    uint hash = QT_PREPEND_NAMESPACE(qHash)(key.d->m_detailType);
    QMap<int, QVariant>::const_iterator it = key.d->m_values.constBegin();
    while (it != key.d->m_values.constEnd()) {
        hash += QT_PREPEND_NAMESPACE(qHash)(it.key()) + QT_PREPEND_NAMESPACE(qHash)(it.value().toString());
        ++it;
    }
    return hash;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QOrganizerItemDetail &detail)
{
    dbg.nospace() << "QOrganizerItemDetail(name=" << detail.type() << ", key=" << detail.key();
    QMap<int, QVariant> fields = detail.values();
    QMap<int, QVariant>::const_iterator it;
    for (it = fields.constBegin(); it != fields.constEnd(); ++it)
        dbg.nospace() << ", " << it.key() << '=' << it.value();
    dbg.nospace() << ')';
    return dbg.maybeSpace();
}
#endif // QT_NO_DEBUG_STREAM

#ifndef QT_NO_DATASTREAM
/*!
    Writes \a detail to the stream \a out.
 */
QDataStream &operator<<(QDataStream &out, const QOrganizerItemDetail &detail)
{
    quint8 formatVersion = 1; // Version of QDataStream format for QOrganizerItemDetail
    return out << formatVersion
               << detail.type()
               << detail.values();
}

/*!
    Reads aan organizer item detail from stream \a in into \a detail.
 */
QDataStream &operator>>(QDataStream &in, QOrganizerItemDetail &detail)
{
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        quint32 detailType;
        QMap<int, QVariant> values;
        in >> detailType >> values;

        detail = QOrganizerItemDetail(static_cast<QOrganizerItemDetail::DetailType>(detailType));

        QMapIterator<int, QVariant> it(values);
        while (it.hasNext()) {
            it.next();
            detail.setValue(it.key(), it.value());
        }
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
#endif // QT_NO_DATASTREAM

/*!
    Returns true if no values are contained in this detail.  Note that context is stored as a value; hence, if a context is set, this function will return false.
 */
bool QOrganizerItemDetail::isEmpty() const
{
    return (d->m_values.isEmpty());
}

/*!
    Returns the key of this detail.
 */
int QOrganizerItemDetail::key() const
{
    return d->m_id;
}

/*!
    Causes the implicitly-shared detail to be detached from any other copies, and generates a new key for it.
    This ensures that calling QOrganizerItem::saveDetail() will result in a new detail being saved, rather than
    another detail being updated.
 */
void QOrganizerItemDetail::resetKey()
{
    d->m_id = QOrganizerItemDetailPrivate::lastDetailKey().fetchAndAddOrdered(1);
}

/*!
    Returns the value stored in this detail for the given \a field. An invalid QVariant is returned if the
    value of \a field is not set.
 */
QVariant QOrganizerItemDetail::value(int field) const
{
    return d->m_values.value(field);
}

/*!
    Returns true if the value of the given \a field has been set, or false otherwise.
 */
bool QOrganizerItemDetail::hasValue(int field) const
{
    return d->m_values.contains(field);
}

/*!
    Sets the value of the given \a field to be \a value. If the given \a value is invalid, removes
    the given \a field from the detail. Returns true on success, or false otherwise.
 */
bool QOrganizerItemDetail::setValue(int field, const QVariant &value)
{
    if (!value.isValid())
        return removeValue(field);

    d->m_values.insert(field, value);
    return true;
}

/*!
    Removes the value stored in this detail for the given \a field.  Returns true if a value was stored
    for the given \a field and the removing succeeds, or false otherwise.
 */
bool QOrganizerItemDetail::removeValue(int field)
{
    return d->m_values.remove(field);
}

/*!
    Returns the values stored in this detail as a field-to-value map.
 */
QMap<int, QVariant> QOrganizerItemDetail::values() const
{
    return d->m_values;
}

/*!
    \fn T QOrganizerItemDetail::value(const QString &field) const
    Returns the value of the template type associated with the given \a field.
 */

QTORGANIZER_END_NAMESPACE
