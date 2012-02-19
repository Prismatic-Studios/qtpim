/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtContacts module of the Qt Toolkit.
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qcontactdetail.h"
#include "qcontactdetail_p.h"
#include "qcontactmanager.h"
#include <QDebug>
#include <QDataStream>

/*
    When these conditions are satisfied, QStringLiteral is implemented by
    gcc's statement-expression extension.  However, in this file it will
    not work, because "statement-expressions are not allowed outside functions
    nor in template-argument lists".

    Fall back to the less-performant QLatin1String in this case.
*/
#if defined(QStringLiteral) && defined(QT_UNICODE_LITERAL_II) && defined(Q_CC_GNU) && !defined(Q_COMPILER_LAMBDA)
# undef QStringLiteral
# define QStringLiteral QLatin1String
#endif

QTCONTACTS_BEGIN_NAMESPACE

/* Initialise our static private data member */
QAtomicInt QContactDetailPrivate::lastDetailKey(1);

/* Definitions of predefined string constants */
const QString QContactDetail::FieldDetailUri(QStringLiteral("DetailUri"));
const QString QContactDetail::FieldLinkedDetailUris(QStringLiteral("LinkedDetailUris"));
const QString QContactDetail::FieldContext(QStringLiteral("Context"));
const QString QContactDetail::ContextOther(QStringLiteral("Other"));
const QString QContactDetail::ContextHome(QStringLiteral("Home"));
const QString QContactDetail::ContextWork(QStringLiteral("Work"));


/*!
  \class QContactDetail

  \brief The QContactDetail class represents a single, complete detail about a contact.
  \inmodule QtContacts
  \ingroup contacts-main

  All of the information for a contact is stored in one or more QContactDetail objects.

  A detail is a group of logically related bits of data - for example, a street address is a single
  detail that has multiple fields (number, region, country etc).  Every QContactDetail has the name of an
  associated QContactDetailDefinition that describes the fields, their data type, and any
  restrictions on their values.  Different contact managers might have different detail definitions
  for the same name, depending on their capabilities.  For example, for the QContactName definition name,
  one manager might not support the middle name field, while a different manager may add an extra field for
  specific extra information not present in the default schema.

  Both the names of all the fields, and the name of the associated QContactDetailDefinition are stored
  as 8-bit strings encoded in Latin 1 for memory conservation.  Note, however, that the values stored
  in each field are not constrained in this way, and full unicode QStrings or QVariant data can be stored.

  One field which is common to all details is the context field.  This field is intended to store one or
  more contexts that this detail is associated with.  Commonly this will be something like
  "Home" and/or "Work", although no limitations are placed on which values may be stored in this field
  in the default schema.

  There are two other, related fields which are common to all details.  The first is
  \a QContactDetail::FieldDetailUri, which stores the unique URI of the detail if one exists.
  The field is not mandatory, and backends are not required to verify that the given URI is indeed
  unique within the contact.  The second field is \a QContactDetail::LinkedDetailUris, which stores
  a list of detail URIs to which this detail is linked.  The link is one-way, and can be used to show
  how or where a detail was derived.  This is useful for things like presence information and avatars,
  which are linked to a particular online account detail of the contact.

  When a QContactDetail has been retrieved in a QContact from a QContactManager, it may have certain
  access constraints provided with it, like \l ReadOnly or \l Irremovable.  This might mean that the
  supplied detail is calculated or otherwise not modifiable by the user - presence information is a
  good example.  Also, some details may be marked \l Irremovable.  These are typically things that
  a contact has to have - like a QContactDisplayLabel or a QContactType.

  It is possible to inherit from QContactDetail to provide convenience or
  standardized access to values.  For example, \l QContactPhoneNumber provides
  a convenient API for manipulating a QContactDetail as a phone number, according
  to the schema.

  In general, QContactDetail and the built in subclasses (like \l QContactPhoneNumber) provide
  constants for the names of fields (like \l QContactPhoneNumber::FieldNumber), and for predefined
  common values like \l QContactDetail::ContextHome.  Typically the constants for field names start
  with \c Field, and the constants for predefined values of a field start with the name of that field
  (e.g. \c ContextHome is a predefined constant for \c FieldContext).

  If you wish to create your own, customized contact detail, you should use
  the \l QContactExtendedDetail detail.
  QContactDetail objects act like type checked values.  In general, you can assign them
  to and from and have reasonable behaviour, like the following example.

  \code

  QContactPhoneNumber number;
  number.setNumber("555-1212");
  // number.value(QContactPhoneNumber::FieldNumber) == "555-1212";
  // number.definitionName() == QContactPhoneNumber::DefinitionName

  QContactDetail detail = number;
  // detail.value(QContactPhoneNumber::FieldNumber) == "555-1212";
  // detail.definitionName() == QContactPhoneNumber::DefinitionName

  QContactPhoneNumber otherNumber = detail;
  // otherNumber.number() == "555-1212";
  // otherNumber.definitionName() == QContactPhoneNumber::DefinitionName

  QContactAddress address = detail;
  // address is now a default constructed QContactAddress
  // address.value(QContactPhoneNumber::FieldNumber) is empty
  // address.definitionName() == QContactAddress::DefinitionName

  QContactAddress otherAddress = number;
  // otherAddress is now a default constructed QContactAddress
  // otherAddress.value(QContactPhoneNumber::FieldNumber) is empty
  // otherAddress.definitionName() == QContactAddress::DefinitionName
  \endcode

  \sa QContact, QContactDetailDefinition, QContactDetailFilter, QContactDetailRangeFilter, Q_DECLARE_CUSTOM_CONTACT_DETAIL
 */

/*!
  \macro Q_DECLARE_CUSTOM_CONTACT_DETAIL
  \relates QContactDetail

  Macro for simplifying declaring custom (leaf) detail classes.

  The first argument is the name of the class, and the second argument
  is a Latin-1 string literal naming the detail type.

  If you are creating a convenience class for a type of QContactDetail,
  you should use this macro when declaring your class to ensure that
  it interoperates with other contact functionality.

  Here is an example of a class (\l QContactPhoneNumber) using this macro.
  Note that the class provides some predefined constants
  and some convenience methods that return values associated with schema
  fields.

  \snippet ../../src/contacts/details/qcontactphonenumber.h 0
 */

/*!
  \fn QContactDetail::operator!=(const QContactDetail& other) const
  Returns true if the values or id of this detail is different to those of the \a other detail
 */

/*!
  Constructs a new, empty detail
 */
QContactDetail::QContactDetail()
    : d(new QContactDetailPrivate)
{
}

/*!
    Constructs a new, empty detail of the definition identified by \a thisDefinitionId.
    The definitionId must be restricted to the Latin 1 character set.
 */
QContactDetail::QContactDetail(const QString& thisDefinitionId)
    : d(new QContactDetailPrivate)
{
    d->m_definitionName = thisDefinitionId;
}

/*! Constructs a detail that is a copy of \a other
*/
QContactDetail::QContactDetail(const QContactDetail& other)
    : d(other.d)
{
}

/*!
    \internal

    Constructs a detail that is a copy of \a other if \a other is of the expected definition
    identified by \a expectedDefinitionId, else constructs a new, empty detail of the
    definition identified by the \a expectedDefinitionId
*/
QContactDetail::QContactDetail(const QContactDetail& other, const QString& expectedDefinitionId)
{
    if (other.d.constData()->m_definitionName == expectedDefinitionId) {
        d = other.d;
    } else {
        d = new QContactDetailPrivate;
        d->m_definitionName = expectedDefinitionId;
    }
}

/*! Assigns this detail to \a other */
QContactDetail& QContactDetail::operator=(const QContactDetail& other)
{
    if (this != &other)
        d = other.d;
    return *this;
}

/*!
    \internal

    Assigns this detail to \a other if the definition of \a other is that identified
    by the given \a expectedDefinitionId, else assigns this detail to be a new, empty
    detail of the definition identified by the given \a expectedDefinitionId
*/
QContactDetail& QContactDetail::assign(const QContactDetail& other, const QString& expectedDefinitionId)
{
    if (this != &other) {
        if (other.d.constData()->m_definitionName == expectedDefinitionId) {
            d = other.d;
        } else {
            d = new QContactDetailPrivate;
            d->m_definitionName = expectedDefinitionId;
        }
    }
    return *this;
}

/*! Frees the memory used by this detail */
QContactDetail::~QContactDetail()
{
}

/*!
    Returns the (unique) name of the definition which defines the semantics and structure of this detail.
    The actual QContactDetailDefinition should be retrieved from the relevant QContactManager using this name.
 */
QString QContactDetail::definitionName() const
{
    return d.constData()->m_definitionName;
}

/*!
    Compares this detail to \a other.  Returns true if the definition, access constraints and values of \a other are equal to those of this detail.
    The keys of each detail are not considered during the comparison, in order to allow details from different contacts to
    be compared according to their values.
 */
bool QContactDetail::operator==(const QContactDetail& other) const
{
    if (! (d.constData()->m_definitionName == other.d.constData()->m_definitionName))
        return false;

    if (d.constData()->m_access != other.d.constData()->m_access)
        return false;

    if (d.constData()->m_values != other.d.constData()->m_values)
        return false;

    return true;
}

/*! Returns the hash value for \a key.
*/
uint qHash(const QContactDetail &key)
{
    const QContactDetailPrivate* dptr= QContactDetailPrivate::detailPrivate(key);
    uint hash = qHash(dptr->m_definitionName)
                + QT_PREPEND_NAMESPACE(qHash)(dptr->m_access);
    QHash<QString, QVariant>::const_iterator it = dptr->m_values.constBegin();
    while(it != dptr->m_values.constEnd()) {
        hash += qHash(it.key())
                + QT_PREPEND_NAMESPACE(qHash)(it.value().toString());
        ++it;
    }
    return hash;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const QContactDetail& detail)
{
    dbg.nospace() << "QContactDetail(name=" << detail.definitionName() << ", key=" << detail.key();
    QVariantMap fields = detail.values();
    QVariantMap::const_iterator it;
    for (it = fields.constBegin(); it != fields.constEnd(); ++it) {
        dbg.nospace() << ", " << it.key() << '=' << it.value();
    }
    dbg.nospace() << ')';
    return dbg.maybeSpace();
}
#endif

#ifndef QT_NO_DATASTREAM
/*!
 * Writes \a detail to the stream \a out.
 */
QDataStream& operator<<(QDataStream& out, const QContactDetail& detail)
{
    quint8 formatVersion = 1; // Version of QDataStream format for QContactDetail
    return out << formatVersion
               << detail.definitionName()
               << static_cast<quint32>(detail.accessConstraints())
               << detail.values();
}

/*!
 * Reads a contact detail from stream \a in into \a detail.
 */
QDataStream& operator>>(QDataStream& in, QContactDetail& detail)
{
    detail = QContactDetail();
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        QString definitionName;
        quint32 accessConstraintsInt;
        QVariantMap values;
        in >> definitionName >> accessConstraintsInt >> values;

        detail = QContactDetail(definitionName);
        QContactDetail::AccessConstraints accessConstraints(accessConstraintsInt);
        detail.d->m_access = accessConstraints;

        QMapIterator<QString, QVariant> it(values);
        while (it.hasNext()) {
            it.next();
            detail.setValue(it.key(), it.value());
        }
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}
#endif

/*!
    Returns true if no values are contained in this detail.  Note that context
    is stored as a value; hence, if a context is set, this function will return false.

    An empty value (for example, the string "") is still a value contained in this
    detail, so this function will return false.
 */
bool QContactDetail::isEmpty() const
{
    if (!d.constData()->m_values.isEmpty())
        return false;
    return true;
}

/*!
 * Returns the key of this detail.
 *
 * Be aware that if a contact is retrieved (or reloaded) from the backend, the
 * keys of any details it contains may have been changed by the backend, or other
 * threads may have modified the contact details in the backend.  Therefore,
 * clients should reload the detail that they wish to save in or remove from a contact
 * after retrieving the contact from the backend, in order to ascertain the keys of
 * any such details.
 */
int QContactDetail::key() const
{
    return d.constData()->m_id;
}

/*! Causes the implicitly-shared detail to be detached from any other copies, and generates a new key for it.
    This ensures that calling QContact::saveDetail() will result in a new detail being saved, rather than
    another detail being updated.
*/
void QContactDetail::resetKey()
{
    d->m_id = QContactDetailPrivate::lastDetailKey.fetchAndAddOrdered(1);
}


/*!
    \fn T QContactDetail::value(const char* key) const
    \internal
    \overload
*/

/*! Returns the value stored in this detail for the given \a key as a QVariant, or an invalid QVariant if no value for the given \a key exists
*/
QVariant QContactDetail::value(const QString& key) const
{
    return d.constData()->m_values.value(key);
}

/*!
  Returns true if this detail has a field with the given \a key, or false otherwise.
 */
bool QContactDetail::hasValue(const QString& key) const
{
    return d.constData()->m_values.contains(key);
}

/*! Inserts \a value into the detail for the given \a key if \a value is valid.  If \a value is invalid,
    removes the field with the given \a key from the detail.  Returns true if the given \a value was set
    for the \a key (if the \a value was valid), or if the given \a key was removed from detail (if the
    \a value was invalid), and returns false if the key was unable to be removed (and the \a value was invalid)
*/
bool QContactDetail::setValue(const QString& key, const QVariant& value)
{
    if (!value.isValid())
        return removeValue(key);

    d->m_values.insert(key, value);
    return true;
}

/*!
    Removes the value stored in this detail for the given \a key.  Returns true if a value was stored
    for the given \a key and the operation succeeded, and false otherwise.
*/
bool QContactDetail::removeValue(const QString& key)
{
    if(d->m_values.remove(key))
        return true;
    return false;
}

/*!
  Returns the values stored in this detail as a map from value key to value
 */
QVariantMap QContactDetail::values() const
{
    QVariantMap ret;
    QHash<QString, QVariant>::const_iterator it = d.constData()->m_values.constBegin();
    while(it != d.constData()->m_values.constEnd()) {
        ret.insert(it.key(), it.value());
        ++it;
    }

    return ret;
}

/*!
  \enum QContactDetail::AccessConstraint

  This enum defines the access constraints for a detail.  This information is typically provided by
  the manager when a contact is retrieved.

  \value NoConstraint Users can read, write, and otherwise modify this detail in any manner.
  \value ReadOnly Users cannot write or modify values in this detail.
  \value Irremovable Users cannot remove this detail from a contact.
 */


/*!
  Returns the access constraints associated with the detail.

  Some details may not be written to, while other details may
  not be removed from a contact.

  \sa QContactDetail::AccessConstraints
 */
QContactDetail::AccessConstraints QContactDetail::accessConstraints() const
{
    return d.constData()->m_access;
}

/*!
  \fn void QContactDetail::setContexts(const QStringList& contexts)

  This is a convenience function that sets the \c Context field of this detail to the given \a contexts.

  It is equivalent to the following code:
  \code
  setValue(QContactDetail::FieldContext, contexts);
  \endcode

  \sa setValue()
 */

/*!
  \fn void QContactDetail::setContexts(const QString& context)

  This is a convenience function that sets the \c Context field of this detail to the given \a context.
  It is useful if the detail is only valid in a single context.

  It is equivalent to the following code:
  \code
  setValue(FieldContext, QStringList(context));
  \endcode

  \sa setValue()
 */

/*!
  \fn QStringList QContactDetail::contexts() const

  This is a convenience function to return the \c Context field of this detail.

  It is equivalent to the following code:
  \code
  value<QStringList>(QContactDetail::FieldContext);
  \endcode

  \sa value()
 */


/*!
  \fn void QContactDetail::setDetailUri(const QString& detailUri)

  This is a convenience function that sets the \c DetailUri field of this detail to the given \a detailUri.
  In order to be linked to, a detail must have a specific and (per-contact) unique detail URI set.

  It is equivalent to the following code:
  \code
  setValue(FieldDetailUri, detailUri);
  \endcode

  \sa setValue()
 */

/*!
  \fn QString QContactDetail::detailUri() const

  This is a convenience function to return the \c DetailUri field of this detail.

  It is equivalent to the following code:
  \code
  value(QContactDetail::FieldDetailUri);
  \endcode

  \sa value()
 */


/*!
  \fn void QContactDetail::setLinkedDetailUris(const QStringList& linkedDetailUris)

  This is a convenience function that sets the \c LinkedDetailUris field of this detail to the given \a linkedDetailUris.

  It is equivalent to the following code:
  \code
  setValue(QContactDetail::FieldLinkedDetailUris, linkedDetailUris);
  \endcode

  \sa setValue()
 */

/*!
  \fn void QContactDetail::setLinkedDetailUris(const QString& linkedDetailUri)

  This is a convenience function that sets the \c LinkedDetailUris field of this detail to the given \a linkedDetailUri.
  It is useful if the detail is linked to a single other detail in the contact.

  It is equivalent to the following code:
  \code
  setValue(FieldLinkedDetailUris, QStringList(linkedDetailUri));
  \endcode

  \sa setValue()
 */

/*!
  \fn QStringList QContactDetail::linkedDetailUris() const

  This is a convenience function to return the \c Context field of this detail.

  It is equivalent to the following code:
  \code
  value<QStringList>(QContactDetail::FieldLinkedDetailUris);
  \endcode

  \sa value()
 */

QTCONTACTS_END_NAMESPACE
