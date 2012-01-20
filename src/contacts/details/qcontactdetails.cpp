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

#include <QByteArray>
#include <QUrl>
#include <QFile>

#include <qcontactmanager.h>
#include <qcontacts.h>
#include <qcontactdetails.h>

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


/* template docs:

   XXXX::FieldYYYY:
       The field key constant for the YYYY value.
       \sa yyyy(), setYyyy()

   XXXX::DefinitionName:
        The string constant for the definition name of QContactXXXX details.

   XXXX::FieldSubType
        The field key constant for the field that stores the sub type of a XXXX.
        \sa subType(), setSubType()

   XXXX::SubTypeYYYY
        The predefined string constant for a sub type value,
        indicating blah blah blah.
        \sa subTypes(), setSubTypes()
 */


/* ==================== QContactSyncTarget ======================= */

/*!
   \class QContactSyncTarget
   \brief The QContactSyncTarget class provides a sync target
   for a contact.

  \inmodule QtContacts

   \ingroup contacts-details
 */

/*!
    \variable QContactSyncTarget::DefinitionName
    The string constant for the definition name of QContactSyncTarget details.
*/
const QString QContactSyncTarget::DefinitionName(QStringLiteral("SyncTarget"));

/*!
    \variable QContactSyncTarget::FieldSyncTarget

   The field key constant for the sync target value.
   \sa syncTarget(), setSyncTarget()
 */
const QString QContactSyncTarget::FieldSyncTarget(QStringLiteral("SyncTarget"));

/*!
   \fn QContactSyncTarget::syncTarget() const

   Returns the identifier of the backend store to which the contact
   containing this detail should be synchronized.
 */

/*!
   \fn QContactSyncTarget::setSyncTarget(const QString& syncTarget)

   Sets the identifier of the backend store to which the contact
   containing this detail should be synchronized to \a syncTarget.
 */

/* ==================== QContactEmailAddress ======================= */


/*!
   \class QContactEmailAddress

   \brief The QContactEmailAddress class contains an email address of
   a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactEmailAddress::DefinitionName
   The string constant for the definition name of QContactEmailAddress details.
 */
const QString QContactEmailAddress::DefinitionName(QStringLiteral("EmailAddress"));

/*!
   \variable QContactEmailAddress::FieldEmailAddress

   The field key constant for the email address value.
   \sa emailAddress(), setEmailAddress()
 */
const QString QContactEmailAddress::FieldEmailAddress(QStringLiteral("EmailAddress"));

/*!
   \fn QContactEmailAddress::emailAddress() const
   Returns the email address of the contact which is stored in this detail.
 */

/*!
   \fn QContactEmailAddress::setEmailAddress(const QString& emailAddress)
   Sets the email address of the contact which is stored in this detail to \a emailAddress.
 */

/* ==================== QContactFamily ======================= */
/*!
   \class QContactFamily
   \brief The QContactFamily class contains names of
   family members of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactFamily::DefinitionName
   The string constant for the definition name of QContactFamily details.
 */
const QString QContactFamily::DefinitionName(QStringLiteral("Family"));

/*!
   \variable QContactFamily::FieldSpouse

   The field key constant for the value containing the name of a spouse.
   \sa spouse(), setSpouse()
 */
const QString QContactFamily::FieldSpouse(QStringLiteral("Spouse"));

/*!
   \variable QContactFamily::FieldChildren

   The field key constant for the value containing the names of children.
   \sa children(), setChildren()
 */
const QString QContactFamily::FieldChildren(QStringLiteral("Children"));

/*!
   \fn QContactFamily::spouse() const
   Returns the name of the spouse of the contact which is stored in this detail.
 */

/*!
   \fn QContactFamily::setSpouse(const QString& spouseName)
   Sets the name of the spouse of the contact which is stored in this detail to \a spouseName.
 */

/*!
   \fn QContactFamily::children() const
   Returns the names of the children of the contact which is stored in this detail.
 */

/*!
   \fn QContactFamily::setChildren(const QStringList& childrenNames)
   Sets the names of the children of the contact which is stored in this detail to \a childrenNames.
 */

/* ==================== QContactFavorite ======================= */
/*!
   \class QContactFavorite
   \brief The QContactFavorite class indicates if a contact is a favorite contact as well as the
   position it should appear in an ordered list of favorites.
   \ingroup contacts-details
 */

/*!
   \variable QContactFavorite::DefinitionName
   The string constant for the definition name of QContactFavorite details.
 */
const QString QContactFavorite::DefinitionName(QStringLiteral("Favorite"));

/*!
   \variable QContactFavorite::FieldFavorite

   The field key constant for the value that indicates whether a contact is a favorite.
   \sa index(), setIndex()
 */
const QString QContactFavorite::FieldFavorite(QStringLiteral("Favorite"));

/*!
   \variable QContactFavorite::FieldIndex

   The field key constant for the value containing the index of the favorite contact (which determines the order they appear)
   \sa index(), setIndex()
 */
const QString QContactFavorite::FieldIndex(QStringLiteral("Index"));

/*!
   \fn bool QContactFavorite::isFavorite() const
   Returns true if the contact is a favorite, false otherwise.
 */

/*!
   \fn QContactFavorite::setFavorite(bool isFavorite)
   If \a isFavorite is true, marks the contact as a favorite.  Otherwise, marks the contact as not a favorite.
 */

/*!
   \fn int QContactFavorite::index() const
   Returns the index of the favorite contact.
 */

/*!
   \fn QContactFavorite::setIndex(int index)
   Sets the index of the favorite contact to \a index.
 */

/*!
    Returns a filter suitable for finding contacts which are marked
    as favorite contacts.
*/
QContactFilter QContactFavorite::match()
{
    QContactDetailFilter f;
    f.setDetailDefinitionName(QContactFavorite::DefinitionName,
                              QContactFavorite::FieldFavorite);
    f.setValue(true);
    f.setMatchFlags(QContactFilter::MatchExactly);

    return f;
}

/* ==================== QContactAnniversary ======================= */

/*!
   \class QContactAnniversary
   \brief The QContactAnniversary class contains an anniversary of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactAnniversary::DefinitionName
   The string constant for the definition name of QContactAnniversary details.
 */
const QString QContactAnniversary::DefinitionName(QStringLiteral("Anniversary"));

/*!
   \variable QContactAnniversary::FieldOriginalDate

   The field key constant for the original anniversary date value.

   This field is either a date, or a date and time.  Some managers
   may support either type, while others may convert the value here
   to a specific type (either discarding the time if only a date is
   supported, or by using midnight if a time is not supplied).
   \sa originalDate(), setOriginalDate(), originalDateTime(), setOriginalDateTime()
 */
const QString QContactAnniversary::FieldOriginalDate(QStringLiteral("OriginalDate"));

/*!
   \variable QContactAnniversary::FieldEvent

   The field key constant for the name of the event value.
   \sa event(), setEvent()
 */
const QString QContactAnniversary::FieldEvent(QStringLiteral("Event"));

/*!
   \variable QContactAnniversary::FieldCalendarId

   The field key constant for the value containing the id of the calendar event.
   \sa calendarId(), setCalendarId()
 */
const QString QContactAnniversary::FieldCalendarId(QStringLiteral("CalendarId"));

/*!
   \variable QContactAnniversary::FieldSubType

   The field key constant for the field that stores the sub type of a QContactAnniversary.
   \sa subType(), setSubType()
 */
const QString QContactAnniversary::FieldSubType(QStringLiteral("SubType"));


/*!
   \variable QContactAnniversary::SubTypeWedding

    The predefined string constant for a sub type value,
    indicating this anniversary is a wedding anniversary.
    \sa subType(), setSubType()
 */
const QString QContactAnniversary::SubTypeWedding(QStringLiteral("Wedding"));

/*!
   \variable QContactAnniversary::SubTypeEngagement

    The predefined string constant for a sub type value,
    indicating this anniversary is the anniversary of an engagement.
    \sa subType(), setSubType()
 */
const QString QContactAnniversary::SubTypeEngagement(QStringLiteral("Engagement"));

/*!
   \variable QContactAnniversary::SubTypeHouse
   \internal

    The predefined string constant for a sub type value,
    indicating this anniversary is the anniversary of a new residence.
    \sa subType(), setSubType()
 */
const QString QContactAnniversary::SubTypeHouse(QStringLiteral("House"));

/*!
   \variable QContactAnniversary::SubTypeEmployment

    The predefined string constant for a sub type value,
    indicating this anniversary is the anniversary of a start of
    employment.
    \sa subType(), setSubType()
 */
const QString QContactAnniversary::SubTypeEmployment(QStringLiteral("Employment"));

/*!
   \variable QContactAnniversary::SubTypeMemorial

    The predefined string constant for a sub type value,
    indicating this anniversary is an anniversary of an event of sentimental significance.
    \sa subType(), setSubType()
 */
const QString QContactAnniversary::SubTypeMemorial(QStringLiteral("Memorial"));

/*!
   \fn QContactAnniversary::originalDate() const
   Returns the original date of the event stored in this detail.
   If the original event occurrence stored is a QDateTime, this returns the date portion.
 */

/*!
   \fn QContactAnniversary::setOriginalDate(const QDate& date)
   Sets the original date of the event stored in this detail to \a date.
 */

/*!
   \fn QContactAnniversary::originalDateTime() const
   Returns the original date and time of the event stored in this detail.
   If the original event occurrence stored is a QDate, this returns a QDateTime with the
   time set to midnight.
 */

/*!
   \fn QContactAnniversary::setOriginalDateTime(const QDateTime& dateTime)
   Sets the original date and time of the event stored in this detail to \a dateTime.
 */

/*!
   \fn QContactAnniversary::calendarId() const
 * Returns the identifier of the calendar entry associated with this anniversary.
 */

/*!
   \fn QContactAnniversary::setCalendarId(const QString& calendarId)
   Sets the identifier of the calendar entry associated with this anniversary to \a calendarId.
 */

/*!
   \fn QContactAnniversary::event() const
   Returns the name of the event for which this detail contains information.
 */

/*!
   \fn QContactAnniversary::setEvent(const QString& event)
   Sets the name of the event for which this detail contains information to \a event.
 */

/*!
   \fn QContactAnniversary::setSubType(const QString& subType)
   Sets the subtype which this detail implements to be the given \a subType.
 */

/*!
   \fn QContactAnniversary::subType() const
   Returns the subtype that this detail implements, if defined.
 */

/* ==================== QContactAvatar ======================= */

/*!
   \class QContactAvatar
   \ingroup contacts-details
   \brief The QContactAvatar class contains avatar URLs of a contact.

   Users can specify avatar URLs for a contact using this detail.
   Generally, a URL will specify the location of a full-sized
   image (or video) avatar.  Support for the detail is backend-specific;
   some managers will automatically load the URL and synthesize a
   (possibly scaled) thumbnail detail for the contact if no thumbnail
   was explicitly set, while others will not.

   The URLs which are contained in the detail may point to a file or
   resource whose content may dynamically change.  This is in contrast
   to the thumbnail detail which is static; once set it remains as
   that image until set to something else.  That is, the content of a
   QContactThumbnail detail is set by the user who has created the
   contact, but the content of a resource identified by a URL specified
   in a QContactAvatar detail is set by whoever owns the resource which
   the URL identifies.

   \sa QContactThumbnail
 */

/*!
   \variable QContactAvatar::DefinitionName
   The string constant for the definition name of QContactAvatar details.
 */
const QString QContactAvatar::DefinitionName(QStringLiteral("Avatar"));

/*!
   \variable QContactAvatar::FieldImageUrl

   The field key constant for the value containing the URL of the avatar image.
   \sa imageUrl(), setImageUrl()
 */
const QString QContactAvatar::FieldImageUrl(QStringLiteral("ImageUrl"));

/*!
   \variable QContactAvatar::FieldVideoUrl

   The field key constant for the value containing the URL of a video avatar.
   \sa videoUrl(), setVideoUrl()
 */
const QString QContactAvatar::FieldVideoUrl(QStringLiteral("VideoUrl"));

/*!
  \fn QContactAvatar::imageUrl() const
  Returns the url of an avatar image associated with the contact
 */

/*!
  \fn QContactAvatar::setImageUrl(const QUrl& imageUrl)
  Sets the url of an avatar image associated with the contact to \a imageUrl
 */

/*!
  \fn QContactAvatar::videoUrl() const
  Returns the url of an avatar video associated with the contact
 */

/*!
  \fn QContactAvatar::setVideoUrl(const QUrl& videoUrl)
  Sets the url of an avatar video associated with the contact to \a videoUrl
 */

/* ==================== QContactAddress ======================= */


/*!
   \class QContactAddress
   \brief The QContactAddress class contains an address of a contact.
   \ingroup contacts-details

   The fields in the QContactAddress class are based on the segments
   of the ADR property of a Versit vCard file.
   Versit \reg is a trademark of the Internet Mail Consortium.
 */

/*!
   \variable QContactAddress::DefinitionName
   The string constant for the definition name of QContactAddress details.
 */
const QString QContactAddress::DefinitionName(QStringLiteral("Address"));

/*!
   \variable QContactAddress::FieldStreet

   The field key constant for the value containing the street segment.
   The street segment contains the street number and street name of the address.
   \sa street(), setStreet()
 */
const QString QContactAddress::FieldStreet(QStringLiteral("Street"));

/*!
   \variable QContactAddress::FieldLocality

   The field key constant for the value containing the locality segment.
   The locality segment contains the name of the city, town or suburb of the address.
   \sa locality(), setLocality()
 */
const QString QContactAddress::FieldLocality(QStringLiteral("Locality"));


/*!
   \variable QContactAddress::FieldRegion

   The field key constant for the value containing the region segment.
   The region segment contains the name or identifier of the state,
   province or region of the address.
   \sa region(), setRegion()
 */
const QString QContactAddress::FieldRegion(QStringLiteral("Region"));

/*!
   \variable QContactAddress::FieldPostcode

   The field key constant for the value containing the postcode segment.
   The postcode segment contains the postal code for the address.
   \sa postcode(), setPostcode()
 */
const QString QContactAddress::FieldPostcode(QStringLiteral("Postcode"));

/*!
   \variable QContactAddress::FieldCountry

   The field key constant for the value containing the country segment.
   The country segment contains the name of the country of the address.
   \sa country(), setCountry()
 */
const QString QContactAddress::FieldCountry(QStringLiteral("Country"));

/*!
   \variable QContactAddress::FieldPostOfficeBox

   The field key constant for the value containing the post office box segment.
   The post office box segment contains the post office box identifier of the
   mailing address.
   \sa postOfficeBox(), setPostOfficeBox()
 */
const QString QContactAddress::FieldPostOfficeBox(QStringLiteral("PostOfficeBox"));

/*!
   \variable QContactAddress::FieldSubTypes

   The field key constant for the field that stores the sub types of a QContactAddress.
   \sa subTypes(), setSubTypes()
 */
const QString QContactAddress::FieldSubTypes(QStringLiteral("SubTypes"));

/*!
   \variable QContactAddress::SubTypeParcel

    The predefined string constant for a sub type value,
    indicating this address is an address for parcel delivery.
    \sa subTypes(), setSubTypes()
 */
const QString QContactAddress::SubTypeParcel(QStringLiteral("Parcel"));

/*!
   \variable QContactAddress::SubTypePostal

    The predefined string constant for a sub type value,
    indicating this address is an address for postal delivery.
    \sa subTypes(), setSubTypes()
 */
const QString QContactAddress::SubTypePostal(QStringLiteral("Postal"));

/*!
   \variable QContactAddress::SubTypeDomestic

    The predefined string constant for a sub type value,
    indicating this address is an address for domestic mail delivery.
    \sa subTypes(), setSubTypes()
 */
const QString QContactAddress::SubTypeDomestic(QStringLiteral("Domestic"));

/*!
   \variable QContactAddress::SubTypeInternational

    The predefined string constant for a sub type value,
    indicating this address is an address for international mail delivery.
    \sa subTypes(), setSubTypes()
 */
const QString QContactAddress::SubTypeInternational(QStringLiteral("International"));

/*!
   \fn QContactAddress::postOfficeBox() const
   Returns the post office box segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setPostOfficeBox(const QString& postOfficeBox)
   Sets the post office box segment of the address stored in this detail to \a postOfficeBox.
 */

/*!
   \fn QContactAddress::street() const
   Returns the street segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setStreet(const QString& street)
   Sets the street segment of the address stored in this detail to \a street.
 */

/*!
   \fn QContactAddress::locality() const
   Returns the locality segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setLocality(const QString& locality)
   Sets the locality segment of the address stored in this detail to \a locality.
 */

/*!
   \fn QContactAddress::region() const
   Returns the region segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setRegion(const QString& region)
   Sets the region segment of the address stored in this detail to \a region.
 */

/*!
   \fn QContactAddress::postcode() const
   Returns the postcode segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setPostcode(const QString& postcode)
   Sets the postcode segment of the address stored in this detail to \a postcode.
 */

/*!
   \fn QContactAddress::country() const
   Returns the country segment of the address stored in this detail.
 */

/*!
   \fn QContactAddress::setCountry(const QString& country)
   Sets the country segment of the address stored in this detail to \a country.
 */

/*!
   \fn QContactAddress::setSubTypes(const QStringList& subTypes)
   Sets the subtypes which this detail implements to be those contained in the list of given \a subTypes.
 */

/*!
   \fn QContactAddress::setSubTypes(const QString& subType)
   Sets the subtypes which this detail implements to be just the given \a subType.
 */

/*!
   \fn QContactAddress::subTypes() const
   Returns the list of subtypes that this detail implements.
 */

/*!
    Returns a filter suitable for finding contacts with an address which
    contains the given \a subString in any of its fields.
*/
QContactFilter QContactAddress::match(const QString &subString)
{
    QContactDetailFilter f1;
    f1.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldStreet);
    f1.setValue(subString);
    f1.setMatchFlags(QContactFilter::MatchContains);

    QContactDetailFilter f2;
    f2.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldLocality);
    f2.setValue(subString);
    f2.setMatchFlags(QContactFilter::MatchContains);

    QContactDetailFilter f3;
    f3.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldRegion);
    f3.setValue(subString);
    f3.setMatchFlags(QContactFilter::MatchContains);

    QContactDetailFilter f4;
    f4.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldPostcode);
    f4.setValue(subString);
    f4.setMatchFlags(QContactFilter::MatchContains);

    QContactDetailFilter f5;
    f5.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldCountry);
    f5.setValue(subString);
    f5.setMatchFlags(QContactFilter::MatchContains);

    QContactDetailFilter f6;
    f6.setDetailDefinitionName(QContactAddress::DefinitionName,
                               QContactAddress::FieldPostOfficeBox);
    f6.setValue(subString);
    f6.setMatchFlags(QContactFilter::MatchContains);

    return (f1 | f2 | f3 | f4 | f5 | f6);
}

/* ==================== QContactUrl ======================= */

/*!
   \class QContactUrl
   \brief The QContactUrl class contains a url associated with
   a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactUrl::DefinitionName
   The string constant for the definition name of QContactUrl details.
 */
const QString QContactUrl::DefinitionName(QStringLiteral("Url"));

/*!
   \variable QContactUrl::FieldUrl

   The field key constant for the value containing the URL.
   \sa url(), setUrl()
 */
const QString QContactUrl::FieldUrl(QStringLiteral("Url"));

/*!
   \variable QContactUrl::FieldSubType

   The field key constant for the field that stores the sub type of a QContactUrl.
   \sa subType(), setSubType()
 */
const QString QContactUrl::FieldSubType(QStringLiteral("SubType"));

/*!
   \variable QContactUrl::SubTypeHomePage

    The predefined string constant for a sub type value,
    indicating this url is a contact's home page.
    \sa subType(), setSubType()
 */
const QString QContactUrl::SubTypeHomePage(QStringLiteral("HomePage"));

/*!
   \variable QContactUrl::SubTypeFavourite

    The predefined string constant for a sub type value,
    indicating this url is one of the contact's favourite URLs (or bookmarks).
    \sa subType(), setSubType()
 */
const QString QContactUrl::SubTypeFavourite(QStringLiteral("Favourite"));

/*!
   \variable QContactUrl::SubTypeBlog

    The predefined string constant for a sub type value,
    indicating this url refers to one of the contact's blogs.
    \sa subType(), setSubType()
 */
const QString QContactUrl::SubTypeBlog(QStringLiteral("Blog"));

/*!
   \fn QContactUrl::url() const
   Returns the url stored in this detail.
 */

/*!
   \fn QContactUrl::setUrl(const QString& url)
   Sets the url stored in this detail to \a url.
 */

/*!
   \fn QContactUrl::setUrl(const QUrl& url)
   Sets the url stored in this detail to the string representation
   of the given \a url.
 */

/*!
   \fn QContactUrl::setSubType(const QString& subType)
   Sets the subtype which this detail implements to be the given \a subType.
 */

/*!
   \fn QContactUrl::subType() const
   Returns the subtype that this detail implements, if defined.
 */

/* ==================== QContactPhonenumber ======================= */

/*!
    \class QContactPhoneNumber
    \brief The QContactPhoneNumber class provides a phone number
    of a contact.
    \ingroup contacts-details
*/


/*!
    \variable QContactPhoneNumber::DefinitionName
    The string constant for the definition name of QContactPhoneNumber details.
*/
const QString QContactPhoneNumber::DefinitionName(QStringLiteral("PhoneNumber"));

/*!
   \variable QContactPhoneNumber::FieldNumber

   The field key constant for the value containing the phone number.
   \sa number(), setNumber()
 */
const QString QContactPhoneNumber::FieldNumber(QStringLiteral("PhoneNumber"));

/*!
   \variable QContactPhoneNumber::FieldSubTypes

   The field key constant for the field that stores the sub types of a QContactPhoneNumber.
   \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::FieldSubTypes(QStringLiteral("SubTypes"));

/*!
   \variable QContactPhoneNumber::SubTypeLandline

    The predefined string constant for a sub type value,
    indicating this phone number is a landline number.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeLandline(QStringLiteral("Landline"));

/*!
   \variable QContactPhoneNumber::SubTypeMobile

    The predefined string constant for a sub type value,
    indicating this phone number is a mobile (cellular) number.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeMobile(QStringLiteral("Mobile"));

/*!
   \variable QContactPhoneNumber::SubTypeFax

    The predefined string constant for a sub type value,
    indicating this phone number is a fax number.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeFax(QStringLiteral("Fax"));

/*!
   \variable QContactPhoneNumber::SubTypePager

    The predefined string constant for a sub type value,
    indicating this phone number is a pager number.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypePager(QStringLiteral("Pager"));

/*!
   \variable QContactPhoneNumber::SubTypeCar

    The predefined string constant for a sub type value,
    indicating this phone number is a car phone.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeCar(QStringLiteral("Car"));

/*!
   \variable QContactPhoneNumber::SubTypeBulletinBoardSystem

    The predefined string constant for a sub type value,
    indicating this phone number is a bulletin board system.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeBulletinBoardSystem(QStringLiteral("BulletinBoardSystem"));

/*!
   \variable QContactPhoneNumber::SubTypeVoice

    The predefined string constant for a sub type value,
    indicating this phone number supports voice transmission.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeVoice(QStringLiteral("Voice"));

/*!
   \variable QContactPhoneNumber::SubTypeModem

    The predefined string constant for a sub type value,
    indicating this phone number supports data transmission.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeModem(QStringLiteral("Modem"));

/*!
   \variable QContactPhoneNumber::SubTypeVideo

    The predefined string constant for a sub type value,
    indicating this phone number supports video transmission.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeVideo(QStringLiteral("Video"));

/*!
   \variable QContactPhoneNumber::SubTypeMessagingCapable

    The predefined string constant for a sub type value,
    indicating this phone number supports messaging services.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeMessagingCapable(QStringLiteral("MessagingCapable"));

/*!
   \variable QContactPhoneNumber::SubTypeAssistant

    The predefined string constant for a sub type value,
    indicating this phone number is the number of an assistant.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeAssistant(QStringLiteral("Assistant"));

/*!
   \variable QContactPhoneNumber::SubTypeDtmfMenu

    The predefined string constant for a sub type value,
    indicating this phone number supports DTMF-controlled voice menu navigation.
    \sa subTypes(), setSubTypes()
 */
const QString QContactPhoneNumber::SubTypeDtmfMenu(QStringLiteral("DtmfMenu"));


/*!
   \fn QContactPhoneNumber::number() const
   Returns the phone number stored in this detail.
 */

/*!
   \fn QContactPhoneNumber::setNumber(const QString& number)
   Sets the phone number stored in this detail to \a number.
 */

/*!
   \fn QContactPhoneNumber::setSubTypes(const QStringList& subTypes)
   Sets the subtypes which this detail implements to be those contained in the list of given \a subTypes
 */

/*!
   \fn QContactPhoneNumber::setSubTypes(const QString& subType)
   Sets the subtypes which this detail implements to be just the given \a subType.
 */

/*!
   \fn QContactPhoneNumber::subTypes() const
   Returns the list of subtypes that this detail implements.
 */

/* ==================== QContactBirthday ======================= */

/*!
   \class QContactBirthday
   \brief The QContactBirthday class contains a birthday of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactBirthday::DefinitionName
   The string constant for the definition name of QContactBirthday details.
 */
const QString QContactBirthday::DefinitionName(QStringLiteral("Birthday"));

/*!
   \variable QContactBirthday::FieldBirthday

   The field key constant for the value containing the birthday date.

   This field is either a date, or a date and time.  Some managers
   may support either type, while others may convert the value here
   to a specific type (either discarding the time if only a date is
   supported, or by using midnight if a time is not supplied).

   \sa date(), setDate(), dateTime(), setDateTime()
 */
const QString QContactBirthday::FieldBirthday(QStringLiteral("Birthday"));

/*!
   \variable QContactBirthday::FieldCalendarId

   The field key constant for the value containing the id of the calendar event.
   \sa calendarId(), setCalendarId()
 */
const QString QContactBirthday::FieldCalendarId(QStringLiteral("CalendarId"));

/*!
   \fn QContactBirthday::date() const
   Returns the date of the birthday which is stored in this detail.
   If the birthday stored is a QDateTime, this returns the date portion.
 */

/*!
   \fn QContactBirthday::setDate(const QDate& date)
   Sets the date of the birthday which is stored in this detail to \a date.
 */

/*!
   \fn QContactBirthday::dateTime() const
   Returns the date and time of the birthday which is stored in this detail.
   If the birthday stored is a QDate, this returns a QDateTime with the
   time set to midnight.
 */

/*!
   \fn QContactBirthday::setDateTime(const QDateTime& dateTime)
   Sets the date and time of the birthday which is stored in this detail to \a dateTime.
 */


/*!
   \fn QContactBirthday::calendarId() const
 * Returns the identifier of the calendar entry associated with this birthday.
 */

/*!
   \fn QContactBirthday::setCalendarId(const QString& calendarId)
   Sets the identifier of the calendar entry associated with this birthday to \a calendarId.
 */

/* ==================== QContactGender ======================= */

/*!
   \class QContactGender
   \brief The QContactGender class contains the gender of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactGender::DefinitionName
   The string constant for the definition name of QContactGender details.
 */
const QString QContactGender::DefinitionName(QStringLiteral("Gender"));

/*!
   \variable QContactGender::FieldGender

   The field key constant for the value containing the gender.
   \sa gender(), setGender()
 */
const QString QContactGender::FieldGender(QStringLiteral("Gender"));

/*!
   \variable QContactGender::GenderMale
   The value that identifies this contact as being male.
 */
const QString QContactGender::GenderMale(QStringLiteral("Male"));

/*!
   \variable QContactGender::GenderFemale
   The value that identifies this contact as being female.
 */
const QString QContactGender::GenderFemale(QStringLiteral("Female"));

/*!
   \variable QContactGender::GenderUnspecified
   The value that identifies this contact as being of unspecified gender.
 */
const QString QContactGender::GenderUnspecified(QStringLiteral("Unspecified"));

/*!
   \fn QContactGender::gender() const

   Returns the gender of the contact, as stored in this detail.  The
   possible values for the value stored are "Male", "Female" and
   "Unspecified".
 */

/*!
   \fn QContactGender::setGender(const QString& gender)

   Sets the gender of the contact (as stored in this detail) to \a
   gender, if \a gender is either "Male" or "Female", otherwise sets
   it to "Unspecified".
 */

/* ==================== QContactGeolocation ======================= */

/*!
   \class QContactGeoLocation
   \brief The QContactGeoLocation class contains a global location
   coordinate associated with a contact.
   \ingroup contacts-details
*/

/*!
   \variable QContactGeoLocation::DefinitionName
   The string constant for the definition name of QContactGeoLocation details.
 */
const QString QContactGeoLocation::DefinitionName(QStringLiteral("GeoLocation"));

/*!
   \variable QContactGeoLocation::FieldLabel

   The field key constant for the value containing the location label.
   \sa label(), setLabel()
 */
const QString QContactGeoLocation::FieldLabel(QStringLiteral("Label"));

/*!
   \variable QContactGeoLocation::FieldLatitude

   The field key constant for the value containing the latitude.
   \sa latitude(), setLatitude()
 */
const QString QContactGeoLocation::FieldLatitude(QStringLiteral("Latitude"));

/*!
   \variable QContactGeoLocation::FieldLongitude

   The field key constant for the value containing the longitude.
   \sa longitude(), setLongitude()
 */
const QString QContactGeoLocation::FieldLongitude(QStringLiteral("Longitude"));

/*!
   \variable QContactGeoLocation::FieldAccuracy

   The field key constant for the value containing the location (latitude/longitude) accuracy.
   \sa accuracy(), setAccuracy()
 */
const QString QContactGeoLocation::FieldAccuracy(QStringLiteral("Accuracy"));

/*!
   \variable QContactGeoLocation::FieldAltitude

   The field key constant for the value containing the altitude.
   \sa altitude(), setAltitude()
 */
const QString QContactGeoLocation::FieldAltitude(QStringLiteral("Altitude"));


/*!
   \variable QContactGeoLocation::FieldAltitudeAccuracy

   The field key constant for the value containing the accuracy of the altitude.
   \sa altitudeAccuracy(), setAltitudeAccuracy()
 */
const QString QContactGeoLocation::FieldAltitudeAccuracy(QStringLiteral("AltitudeAccuracy"));

/*!
   \variable QContactGeoLocation::FieldHeading

   The field key constant for the value containing the heading.
   \sa heading(), setHeading()
 */
const QString QContactGeoLocation::FieldHeading(QStringLiteral("Heading"));

/*!
   \variable QContactGeoLocation::FieldSpeed

   The field key constant for the value containing the speed.
   \sa speed(), setSpeed()
 */
const QString QContactGeoLocation::FieldSpeed(QStringLiteral("Speed"));

/*!
   \variable QContactGeoLocation::FieldTimestamp

   The field key constant for the value containing the timestamp of the location information.
   \sa timestamp(), setTimestamp()
 */
const QString QContactGeoLocation::FieldTimestamp(QStringLiteral("Timestamp"));

/*!
   \fn QContactGeoLocation::setLabel(const QString& label)
   Sets the label of the location stored in the detail to \a label.
 */

/*!
   \fn QContactGeoLocation::label() const
   Returns the label of the location stored in the detail.
 */

/*!
   \fn QContactGeoLocation::setLatitude(double latitude)

   Sets the latitude portion of the coordinate (in decimal degrees) of
   the location stored in the detail to \a latitude.
 */

/*!
   \fn QContactGeoLocation::latitude() const

   Returns the latitude portion of the coordinate (specified in
   decimal degrees) of the location stored in the detail.
 */

/*!
   \fn QContactGeoLocation::setLongitude(double longitude)

   Sets the longitude portion of the coordinate (in decimal degrees)
   of the location stored in the detail to \a longitude.
 */

/*!
   \fn QContactGeoLocation::longitude() const

   Returns the longitude portion of the coordinate (specified in
   decimal degrees) of the location stored in the detail.
 */

/*!
   \fn QContactGeoLocation::setAccuracy(double accuracy)

   Specifies that the latitude and longitude portions of the location
   stored in the detail are accurate to within \a accuracy metres.
 */

/*!
   \fn QContactGeoLocation::accuracy() const

   Returns the accuracy (in metres) of the latitude and longitude of
   the location stored in the detail.
 */

/*!
   \fn QContactGeoLocation::setAltitude(double altitude)

   Sets the altitude portion of the coordinate (in metres above the
   ellipsoid) of the location stored in the detail to \a altitude.
 */

/*!
   \fn QContactGeoLocation::altitude() const
   Returns the altitude (in metres) of the location stored in the detail.
 */

/*!
   \fn QContactGeoLocation::setAltitudeAccuracy(double altitudeAccuracy)

   Sets the altitude-accuracy portion of the coordinate (in metres) of
   the location stored in the detail to \a altitudeAccuracy.
 */

/*!
   \fn QContactGeoLocation::altitudeAccuracy() const

   Returns the accuracy of the altitude portion of the location stored
   in the detail.
 */

/*!
   \fn QContactGeoLocation::setHeading(double heading)

   Sets the heading portion of the coordinate (in decimal degrees
   clockwise relative to true north) of the location-aware device at
   the time of measurement to \a heading.
 */

/*!
   \fn QContactGeoLocation::heading() const

   Returns the heading (at the time of measurement) of the
   location-aware device that recorded (or was provided) the
   measurement.
 */

/*!
   \fn QContactGeoLocation::setSpeed(double speed)

   Sets the speed portion of the coordinate (in metres per second) of
   the location-aware device at the time of measurement to \a speed.
 */

/*!
   \fn QContactGeoLocation::speed() const

   Returns the speed (at the time of measurement) of the
   location-aware device that recorded (or was provided) the
   measurement.
 */

/*!
   \fn QContactGeoLocation::setTimestamp(const QDateTime& timestamp)

   Sets the creation (or first-valid) timestamp of the location
   information to \a timestamp.
 */

/*!
   \fn QContactGeoLocation::timestamp() const

   Returns the timestamp associated with the location stored in the
   detail.
 */

/* ==================== QContactGuid ======================= */

/*!
   \class QContactGuid
   \brief The QContactGuid class contains a globally unique
   Id of a contact, for use in synchronization with other datastores.
   \ingroup contacts-details
 */

/*!
   \variable QContactGuid::DefinitionName
   The string constant for the definition name of QContactGuid details.
 */
const QString QContactGuid::DefinitionName(QStringLiteral("Guid"));

/*!
   \variable QContactGuid::FieldGuid

   The field key constant for the value containing the GUID.
   \sa guid(), setGuid()
 */
const QString QContactGuid::FieldGuid(QStringLiteral("Guid"));

/*!
   \fn QContactGuid::guid() const

   Returns the globally unique identifier which is stored in this
   detail.
 */

/*!
   \fn QContactGuid::setGuid(const QString& guid)
   Sets the globally unique identifier which is stored in this detail to \a guid.
 */

/* ==================== QContactHobby ======================= */

/*!
   \class QContactHobby
   \brief The QContactHobby class contains a hobby of the contact.
   \ingroup contacts-details

   A contact may have one or more hobbies.  Each QContactHobby
   detail contains information about a single hobby of the contact.
 */

/*!
   \variable QContactHobby::DefinitionName
   The string constant for the definition name of QContactHobby details.
 */
const QString QContactHobby::DefinitionName(QStringLiteral("Hobby"));

/*!
   \variable QContactHobby::FieldHobby

    The field key constant for the value containing the name
    of the hobby.
   \sa hobby(), setHobby()
 */
const QString QContactHobby::FieldHobby(QStringLiteral("Hobby"));

/*!
   \fn QContactHobby::setHobby(const QString& hobby)
   Sets the hobby associated with a contact which is stored in this detail to \a hobby.
 */

/*!
   \fn QContactHobby::hobby() const
   Returns the hobby associated with a contact which is stored in this detail.
 */


/* ==================== QContactName ======================= */

/*!
   \class QContactName
   \brief The QContactName class contains a name of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactName::DefinitionName
   The string constant for the definition name of QContactName details.
 */
const QString QContactName::DefinitionName(QStringLiteral("Name"));

/*!
   \variable QContactName::FieldPrefix

   The field key constant for the value containing the prefix part of the name.
   \sa prefix(), setPrefix()
 */
const QString QContactName::FieldPrefix(QStringLiteral("Prefix"));

/*!
   \variable QContactName::FieldFirstName

   The field key constant for the value containing the first name part of the name.
   \sa firstName(), setFirstName()
 */
const QString QContactName::FieldFirstName(QStringLiteral("FirstName"));

/*!
   \variable QContactName::FieldMiddleName

   The field key constant for the value containing the middle name part of the name.
   \sa middleName(), setMiddleName()
 */
const QString QContactName::FieldMiddleName(QStringLiteral("MiddleName"));

/*!
   \variable QContactName::FieldLastName

   The field key constant for the value containing the last name part of the name.
   \sa lastName(), setLastName()
 */
const QString QContactName::FieldLastName(QStringLiteral("LastName"));

/*!
   \variable QContactName::FieldSuffix

   The field key constant for the value containing the suffix part of the name.
   \sa suffix(), setSuffix()
 */
const QString QContactName::FieldSuffix(QStringLiteral("Suffix"));

/*!
   \variable QContactName::FieldCustomLabel

   The field key constant for the value containing a custom formatted label.
   \sa customLabel(), setCustomLabel()
 */
const QString QContactName::FieldCustomLabel(QStringLiteral("CustomLabel"));

/*!
   \fn QContactName::prefix() const
   Returns the prefix segment of the name stored in this detail.
 */

/*!
   \fn QContactName::setPrefix(const QString& prefix)
   Sets the prefix segment of the name stored in this detail to \a prefix.
 */

/*!
   \fn QContactName::firstName() const
   Returns the first (given) name segment of the name stored in this detail.
 */

/*!
   \fn QContactName::setFirstName(const QString& firstName)
   Sets the first name segment of the name stored in this detail to \a firstName.
 */

/*!
   \fn QContactName::middleName() const

   Returns the middle (additional, or other) name segment of the name
   stored in this detail.
 */

/*!
   \fn QContactName::setMiddleName(const QString& middleName)
   Sets the middle name segment of the name stored in this detail to \a middleName.
 */

/*!
   \fn QContactName::lastName() const

   Returns the last (family, or surname) name segment of the name
   stored in this detail.
 */

/*!
   \fn QContactName::setLastName(const QString& lastName)
   Sets the last name segment of the name stored in this detail to \a lastName.
 */

/*!
   \fn QContactName::suffix() const
   Returns the suffix segment of the name stored in this detail.
 */

/*!
   \fn QContactName::setSuffix(const QString& suffix)
   Sets the suffix segment of the name stored in this detail to \a suffix.
 */

/*!
   \fn QContactName::customLabel() const
   Returns the custom label of the name stored in this detail.
 */

/*!
   \fn QContactName::setCustomLabel(const QString& customLabel)
   Sets the custom label of the name stored in this detail to \a customLabel.
 */

/* ==================== QContactNickname ======================= */

/*!
   \class QContactNickname
   \brief The QContactNickname class contains a nickname of a contact.
   \ingroup contacts-details
 */

/*!
\variable QContactNickname::DefinitionName
The string constant for the definition name of QContactNickname details.
*/
const QString QContactNickname::DefinitionName(QStringLiteral("Nickname"));

/*!
   \variable QContactNickname::FieldNickname

   The field key constant for the value containing the nickname.
   \sa nickname(), setNickname()
 */
const QString QContactNickname::FieldNickname(QStringLiteral("Nickname"));

/*!
   \fn QContactNickname::setNickname(const QString& nickname)
   Sets the nickname of the contact which is stored in this detail to \a nickname.
 */

/*!
   \fn QContactNickname::nickname() const
   Returns the nickname of the contact which is stored in this detail.
 */

/* ==================== QContactNote ======================= */

/*!
   \class QContactNote
   \brief The QContactNote class contains a note associated
   with a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactNote::DefinitionName
   The string constant for the definition name of QContactNote details.
*/
const QString QContactNote::DefinitionName(QStringLiteral("Note"));

/*!
   \variable QContactNote::FieldNote

   The field key constant for the value containing the note.
   \sa note(), setNote()
 */
const QString QContactNote::FieldNote(QStringLiteral("Note"));


/*!
   \fn QContactNote::setNote(const QString& note)
   Sets a note associated with a contact to \a note.
 */

/*!
   \fn QContactNote::note() const
   Returns a string for a note associated with a contact.
 */

/* ==================== QContactTag ======================= */

/*!
   \class QContactTag
   \brief The QContactTag class contains a tag associated with a
   contact.
   \ingroup contacts-details

   Typically the tags associated with a contact will be distinct,
   although this is usually only enforced when the contact is saved
   in the manager.

   Here is an example of retrieving all the tags for a contact:
   \snippet doc/src/snippets/qtcontactsdocsample/qtcontactsdocsample.cpp Getting all tags

   Here is an example of checking for a specific tag value:
   \snippet doc/src/snippets/qtcontactsdocsample/qtcontactsdocsample.cpp Checking for a specific tag
 */

/*!
   \variable QContactTag::DefinitionName
   The string constant for the definition name of QContactTag details.
 */
const QString QContactTag::DefinitionName(QStringLiteral("Tag"));

/*!
   \variable QContactTag::FieldTag

    The field key constant for the value containing the tag.
   \sa tag(), setTag()
 */
const QString QContactTag::FieldTag(QStringLiteral("Tag"));

/*!
   \fn QContactTag::setTag(const QString& tag)
   Sets the tag associated with a contact which is stored in this detail to \a tag.
 */

/*!
   \fn QContactTag::tag() const
   Returns the tag associated with a contact which is stored in this detail.
 */

/*!
    Returns a filter suitable for finding contacts which have a tag which
    contains the specified \a subString.
*/
QContactFilter QContactTag::match(const QString &subString)
{
    QContactDetailFilter f;
    f.setDetailDefinitionName(QContactTag::DefinitionName,
                              QContactTag::FieldTag);
    f.setValue(subString);
    f.setMatchFlags(QContactFilter::MatchContains);

    return f;
}

/* ==================== QContactThumbnail ======================= */

/*!
   \class QContactThumbnail
   \ingroup contacts-details
   \brief The QContactThumbnail class contains a thumbnail used
   in display lists to represent the contact.

   Users can specify a thumbnail image for a contact via this detail.
   Support for this detail is backend specific; some managers will save
   the image as given, no matter how big it is, while other managers
   will scale the image prior to save in order to reduce memory overhead.
   Some managers will automatically synthesize a thumbnail detail for
   each contact if an avatar image url is specified but no thumbnail
   detail is specified.

   The content of the thumbnail detail is static once set.  That is,
   in order to change the thumbnail of a particular contact, the user
   must modify the detail and update the contact.  This is in contrast
   to the QContactAvatar detail, which contains URLs to resources;
   the actual content of the resource might be changed dynamically by
   person, group or organization for which the QContact is a digital
   representation.  That is, the content of a QContactThumbnail detail
   is set by the user who has created the contact, but the content of
   a resource identified by a URL specified in a QContactAvatar detail
   is set by whoever owns the resource which the URL identifies.

   \sa QContactAvatar
 */

/*!
   \variable QContactThumbnail::DefinitionName
   The string constant for the definition name of QContactThumbnail details.
 */
const QString QContactThumbnail::DefinitionName(QStringLiteral("Thumbnail"));

/*!
   \variable QContactThumbnail::FieldThumbnail

   The field key constant for the value containing the thumbnail image.
   \sa thumbnail(), setThumbnail()
 */
const QString QContactThumbnail::FieldThumbnail(QStringLiteral("Thumbnail"));

/*!
  \fn QContactThumbnail::thumbnail() const
  Returns the thumbnail image of the contact
 */

/*!
  \fn QContactThumbnail::setThumbnail(const QImage& thumbnail)
  Sets the thumbnail image of the contact to be \a thumbnail
 */

/* ==================== QContactTimestamp ======================= */

/*!
   \class QContactTimestamp
   \brief The QContactTimestamp class contains the creation and
   last-modified timestamp associated with the contact.
   \ingroup contacts-details
 */

/*!
\variable QContactTimestamp::DefinitionName
The string constant for the definition name of QContactTimestamp details.
*/
const QString QContactTimestamp::DefinitionName(QStringLiteral("Timestamp"));

/*!
   \variable QContactTimestamp::FieldModificationTimestamp

   The field key constant for the value of the last modified timestamp.
   \sa lastModified(), setLastModified()
 */
const QString QContactTimestamp::FieldModificationTimestamp(QStringLiteral("ModificationTimestamp"));

/*!
   \variable QContactTimestamp::FieldCreationTimestamp

   The field key constant for the value of the timestamp a contact was created.
   \sa created(), setCreated()
 */
const QString QContactTimestamp::FieldCreationTimestamp(QStringLiteral("CreationTimestamp"));

/*!
   \fn QContactTimestamp::created() const
   Returns the creation timestamp saved in this detail.
 */

/*!
   \fn QContactTimestamp::lastModified() const
   Returns the last-modified timestamp saved in this detail.
 */

/*!
   \fn QContactTimestamp::setCreated(const QDateTime& dateTime)
   Sets the creation timestamp saved in this detail to \a dateTime.
 */

/*!
   \fn QContactTimestamp::setLastModified(const QDateTime& dateTime)
   Sets the last-modified timestamp saved in this detail to \a dateTime.
 */

/* ==================== QContactType ======================= */

/*!
   \class QContactType
   \brief The QContactType class describes the type of the contact.
   \ingroup contacts-details
 */

/*!
\variable QContactType::DefinitionName
The string constant for the definition name of QContactType details.
*/
const QString QContactType::DefinitionName(QStringLiteral("Type"));

/*!
   \variable QContactType::FieldType

   The field key constant for the type value which is stored in details of
   the QContactType definition.
 */
const QString QContactType::FieldType(QStringLiteral("Type"));


/*!
   \variable QContactType::TypeContact

    The predefined string constant for a type value,
    indicating this contact is an ordinary contact.
    \sa setType(), type()
 */
const QString QContactType::TypeContact(QStringLiteral("Contact"));

/*!
   \variable QContactType::TypeGroup

    The predefined string constant for a type value,
    indicating this contact is a group contact.

    Contacts of this type are able to be the first contact in
    relationships of the \c QContactRelationship::HasMember type.

    To enumerate the ids of members of a group, the client should
    retrieve the relationships which involve the group from the manager
    in which the group is saved.

    \sa setType(), type()
 */
const QString QContactType::TypeGroup(QStringLiteral("Group"));

/*!
   \fn QContactType::type() const
   Returns the contact type value stored in this detail.
 */

/*!
   \fn QContactType::setType(const QString& type)
   Sets the type of the contact to be the give \a type.
 */

/* ==================== QContactDisplayLabel ======================= */

// XXX TODO make this better
/*!
   \class QContactDisplayLabel
   \brief The QContactDisplayLabel class is the (possibly synthesized)
   display label of a contact.
   \ingroup contacts-details
 */

/*!
   \variable QContactDisplayLabel::DefinitionName

   The string constant for the definition name of QContactDisplayLabel details.
 */
const QString QContactDisplayLabel::DefinitionName(QStringLiteral("DisplayLabel"));


/*!
   \variable QContactDisplayLabel::FieldLabel

   The field key constant for the value of the display label.
   \sa label()
 */
const QString QContactDisplayLabel::FieldLabel(QStringLiteral("Label"));

/*!
   \fn QContactDisplayLabel::label() const
   Returns the display label of the contact.
 */

/* ==================== QContactOnlineAccount ======================= */

// XXX TODO explain link to QContactPresence

/*!
   \class QContactOnlineAccount
   \brief The QContactOnlineAccount class provides an online account,
   which the contact uses to communicate with friends and family.

   A QContactOnlineAccount consists of the account details required to
   communicate with the contact, including the account URI, the capabilities
   of the account, the service provider of the account, and the type of the account.

   Presence information for a particular QContactOnlineAccount detail is provided
   in a QContactPresence detail which is linked (via linkedDetailUris()) to the
   account detail.  This information is generally provided by the backend, and is
   not modifiable by clients.

   \sa QContactPresence

   \ingroup contacts-details
 */

/*!
   \variable QContactOnlineAccount::DefinitionName
   The string constant for the definition name of QContactOnlineAccount details.
 */
const QString QContactOnlineAccount::DefinitionName(QStringLiteral("OnlineAccount"));

/*!
   \variable QContactOnlineAccount::FieldCapabilities

   The field key constant for the account capabilities value.
   \sa capabilities(), setCapabilities()
 */
const QString QContactOnlineAccount::FieldCapabilities(QStringLiteral("Capabilities"));

/*!
   \variable QContactOnlineAccount::FieldAccountUri

   The field key constant for the account uri value.
   \sa accountUri(), setAccountUri()
 */
const QString QContactOnlineAccount::FieldAccountUri(QStringLiteral("AccountUri"));

/*!
   \variable QContactOnlineAccount::FieldServiceProvider

   The field key constant for the account service provider name.
   \sa serviceProvider(), setServiceProvider()
 */
const QString QContactOnlineAccount::FieldServiceProvider(QStringLiteral("ServiceProvider"));

/*!
   \variable QContactOnlineAccount::FieldProtocol

   The field key constant for the account service provider name.
   \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::FieldProtocol(QStringLiteral("Protocol"));

/*!
   \variable QContactOnlineAccount::FieldSubTypes

   The field key constant for the field that stores the sub types of a QContactOnlineAccount.
   \sa subTypes(), setSubTypes()
 */
const QString QContactOnlineAccount::FieldSubTypes(QStringLiteral("SubTypes"));

/*!
   \variable QContactOnlineAccount::SubTypeSip

    The predefined string constant for a sub type value,
    indicating this online account supports SIP.
    \sa subTypes(), setSubTypes()
 */
const QString QContactOnlineAccount::SubTypeSip(QStringLiteral("Sip"));

/*!
   \variable QContactOnlineAccount::SubTypeSipVoip

    The predefined string constant for a sub type value,
    indicating this online account supports SIP based VOIP.
    \sa subTypes(), setSubTypes()
 */
const QString QContactOnlineAccount::SubTypeSipVoip(QStringLiteral("SipVoip"));

/*!
   \variable QContactOnlineAccount::SubTypeImpp

    The predefined string constant for a sub type value,
    indicating this online account supports IMPP.
    \sa subTypes(), setSubTypes()
 */
const QString QContactOnlineAccount::SubTypeImpp(QStringLiteral("Impp"));

/*!
   \variable QContactOnlineAccount::SubTypeVideoShare

    The predefined string constant for a sub type value,
    indicating this online account supports VideoShare.
    \sa subTypes(), setSubTypes()
 */
const QString QContactOnlineAccount::SubTypeVideoShare(QStringLiteral("VideoShare"));

/*!
   \variable QContactOnlineAccount::ProtocolAim

    The predefined string constant for a protocol value,
    indicating this online account is for the AIM protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolAim(QStringLiteral("aim"));

/*!
   \variable QContactOnlineAccount::ProtocolIcq

    The predefined string constant for a protocol value,
    indicating this online account is for the ICQ protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolIcq(QStringLiteral("icq"));

/*!
   \variable QContactOnlineAccount::ProtocolIrc

    The predefined string constant for a protocol value,
    indicating this online account is for the IRC protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolIrc(QStringLiteral("irc"));

/*!
   \variable QContactOnlineAccount::ProtocolJabber

    The predefined string constant for a protocol value,
    indicating this online account is for the Jabber protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolJabber(QStringLiteral("jabber"));

/*!
   \variable QContactOnlineAccount::ProtocolMsn

    The predefined string constant for a protocol value,
    indicating this online account is for the MSN protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolMsn(QStringLiteral("msn"));

/*!
   \variable QContactOnlineAccount::ProtocolQq

    The predefined string constant for a protocol value,
    indicating this online account is for the Tecent QQ protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolQq(QStringLiteral("qq"));

/*!
   \variable QContactOnlineAccount::ProtocolSkype

    The predefined string constant for a protocol value,
    indicating this online account is for the Skype protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolSkype(QStringLiteral("skype"));

/*!
   \variable QContactOnlineAccount::ProtocolYahoo

    The predefined string constant for a protocol value,
    indicating this online account is for the Yahoo chat protocol.
    \sa protocol(), setProtocol()
 */
const QString QContactOnlineAccount::ProtocolYahoo(QStringLiteral("yahoo"));


/*!
   \fn QContactOnlineAccount::setAccountUri(const QString& accountUri)

   Sets the universal resource identifier of the contact's online
   account to \a accountUri.
 */

/*!
   \fn QContactOnlineAccount::accountUri() const

   Returns the universal resource identifier of the online account of
   the contact.
 */

/*!
   \fn QContactOnlineAccount::setServiceProvider(const QString& serviceProvider)

   Sets the service provider of the contact's online account to \a
   serviceProvider.
 */

/*!
   \fn QContactOnlineAccount::serviceProvider() const
   Returns the service provider of the online account of the contact.
 */

/*!
    \fn QContactOnlineAccount::protocol() const
    Returns the protocol value.
 */

/*!
    \fn QContactOnlineAccount::setProtocol(const QString &protocol)
    Set the protocol to \a protocol.
 */

/*!
   \fn QContactOnlineAccount::setSubTypes(const QStringList& subTypes)

   Sets the subtypes which this detail implements to be those
   contained in the list of given \a subTypes.
 */

/*!
   \fn QContactOnlineAccount::setSubTypes(const QString& subType)
   Sets the subtypes which this detail implements to be just the given \a subType.
 */

/*!
   \fn QContactOnlineAccount::subTypes() const
   Returns the list of subtypes that this detail implements.
 */

/*!
   \fn QContactOnlineAccount::setCapabilities(const QStringList& capabilities)

   Sets the capabilities of the online account about which this detail stores
   presence information to \a capabilities.  The \a capabilities list is a
   list of service-provider specified strings which together identify the
   types of communication which may be possible.
 */

/*!
   \fn QContactOnlineAccount::capabilities() const

   Returns the capabilities of the online account about which this detail stores
   presence information.
 */

/* ==================== QContactOrganization ======================= */

/*!
   \class QContactOrganization
   \brief The QContactOrganization class provides details about an
   organization that the contact is either a part of, or stands for.
   \ingroup contacts-details
 */

/*!
   \variable QContactOrganization::DefinitionName
   The string constant for the definition name of QContactOrganization details.
 */
const QString QContactOrganization::DefinitionName(QStringLiteral("Organization"));

/*!
   \variable QContactOrganization::FieldName

   The field key constant for the value of the organization name.
   \sa name(), setName()
 */
const QString QContactOrganization::FieldName(QStringLiteral("Name"));

/*!
   \variable QContactOrganization::FieldLogoUrl

   The field key constant for the URL of the organization logo image.
   \sa logoUrl(), setLogoUrl()
 */
const QString QContactOrganization::FieldLogoUrl(QStringLiteral("LogoUrl"));

/*!
   \variable QContactOrganization::FieldDepartment

   The field key constant for the value of the department name.
   \sa department(), setDepartment()
 */
const QString QContactOrganization::FieldDepartment(QStringLiteral("Department"));

/*!
   \variable QContactOrganization::FieldLocation

   The field key constant for the value of the location of the organization.
   \sa location(), setLocation()
 */
const QString QContactOrganization::FieldLocation(QStringLiteral("Location"));

/*!
   \variable QContactOrganization::FieldRole

   The field key constant for the value of the contact's role in the organization.
   \sa role(), setRole()
 */
const QString QContactOrganization::FieldRole(QStringLiteral("Role"));

/*!
   \variable QContactOrganization::FieldTitle

   The field key constant for the value of the contact's title in the organization.
   \sa title(), setTitle()
 */
const QString QContactOrganization::FieldTitle(QStringLiteral("Title"));

/*!
   \variable QContactOrganization::FieldAssistantName

   The field key constant for the value of the name of the contact's assistant.
   \sa assistantName(), setAssistantName()
 */
const QString QContactOrganization::FieldAssistantName(QStringLiteral("AssistantName"));

/*!
   \variable QContactOrganization::FieldStartDate

   The field key constant for the value of the contact's startdate in organization.
   \sa startDate(), setStartDate()
 */

const QString QContactOrganization::FieldStartDate(QStringLiteral("StartDate"));

/*!
   \variable QContactOrganization::FieldEndDate
   The field key constant for the value of the contact's end date in organization.
   \sa endDate(), setEndDate()
 */

const QString QContactOrganization::FieldEndDate(QStringLiteral("EndDate"));

/*!
   \fn QContactOrganization::setName(const QString& name)
   Sets the name of the organization stored in this detail to \a name.
 */

/*!
   \fn QContactOrganization::name() const
   Returns the name of the organization stored in this detail.
 */

/*!
   \fn QContactOrganization::setLogoUrl(const QUrl& logo)
   Sets the url of the logo of the organization stored in this detail to \a logo.
 */

/*!
   \fn QContactOrganization::logoUrl() const
   Returns the url of the logo of the organization stored in this detail.
 */


/*!
   \fn QContactOrganization::setDepartment(const QStringList& department)

   Sets the contact's department of the organization stored in this
   detail to \a department.  The department is a list of progressively
   finer-grained information.
 */

/*!
   \fn QContactOrganization::department() const
   Returns the contact's department stored in this detail.
 */


/*!
   \fn QContactOrganization::setLocation(const QString& location)

   Sets the location (e.g. city or suburb) of the organization stored
   in this detail to \a location.
 */

/*!
   \fn QContactOrganization::location() const
   Returns the location of the organization stored in this detail.
 */


/*!
   \fn QContactOrganization::setRole(const QString& role)
   Sets the contact's role within the organization stored in this detail to \a role.
 */

/*!
   \fn QContactOrganization::role() const
   Returns the contact's role within the organization stored in this detail.
 */


/*!
   \fn QContactOrganization::setTitle(const QString& title)
   Sets the contact's title within the organization stored in this detail to \a title.
 */

/*!
   \fn QContactOrganization::title() const
   Returns the contact's title within the organization stored in this detail.
 */

/*!
   \fn QContactOrganization::setAssistantName(const QString& assistantName)

   Sets the name of the default assistant of contacts belonging to
   this organization to \a assistantName.
 */

/*!
   \fn QContactOrganization::assistantName() const

   Returns the name of the default assistant of contacts belonging to
   this organization.
 */

/*!
   \fn QContactOrganization::setStartDate(const QDateTime& dateTime)
   Sets the start date and time of the organization  which is stored in this detail to \a startDate.
 */
/*!
   \fn QContactOrganization::startDate() const
    Returns the start date and time of the organization which is stored in this detail.
 */
/*!
   \fn QContactOrganization::setEndDate(const QDateTime& dateTime)
   Sets the end date and time of the organization  which is stored in this detail to \a endDate.
 */
/*!
   \fn QContactOrganization::endDate() const
   Returns the end date and time of the organization which is stored in this detail.
 */

/* ==================== QContactRingtone ======================= */

/*!
   \class QContactRingtone
   \brief The QContactRingtone class provides a ringtone associated
   with a contact
   \ingroup contacts-details
 */

/*!
\variable QContactRingtone::DefinitionName
The string constant for the definition name of QContactRingtone details.
*/
const QString QContactRingtone::DefinitionName(QStringLiteral("Ringtone"));

/*!
   \variable QContactRingtone::FieldAudioRingtoneUrl

   The field key constant for the value of the URL for an audio ringtone.
   \sa setAudioRingtoneUrl(), audioRingtoneUrl()
 */
const QString QContactRingtone::FieldAudioRingtoneUrl(QStringLiteral("AudioRingtoneUrl"));

/*!
   \variable QContactRingtone::FieldVideoRingtoneUrl

   The field key constant for the value of the URL for a video ringtone.
   \sa setVideoRingtoneUrl(), videoRingtoneUrl()
 */
const QString QContactRingtone::FieldVideoRingtoneUrl(QStringLiteral("VideoRingtoneUrl"));

/*!
   \variable QContactRingtone::FieldVibrationRingtoneUrl
   \internal

   The field key constant for the value of the URL for a vibration ringtone.
   \sa setVibrationRingtoneUrl(), vibrationRingtoneUrl()
 */
const QString QContactRingtone::FieldVibrationRingtoneUrl(QStringLiteral("VibrationRingtoneUrl"));

/*!
  \fn QContactRingtone::audioRingtoneUrl() const

  Returns the uri of the audio ringtone stored in the ringtone detail.
 */

/*!
  \fn QContactRingtone::setAudioRingtoneUrl(const QUrl& audioRingtoneUrl)

  Sets the uri of the audio ringtone stored in the ringtone detail
  to \a audioRingtoneUrl.
 */

/*!
  \fn QContactRingtone::videoRingtoneUrl() const

  Returns the uri of the video ringtone stored in the ringtone detail.
 */

/*!
  \fn QContactRingtone::setVideoRingtoneUrl(const QUrl& videoRingtoneUrl)

  Sets the uri of the video ringtone stored in the ringtone detail
  to \a videoRingtoneUrl.
 */

/*!
  \fn QContactRingtone::vibrationRingtoneUrl() const
  \internal

  Returns the uri of the vibration ringtone stored in the ringtone detail.
 */

/*!
  \fn QContactRingtone::setVibrationRingtoneUrl(const QUrl& vibrationRingtoneUrl)
  \internal

  Sets the uri of the vibration ringtone stored in the ringtone detail
  to \a vibrationRingtoneUrl.
 */

/* ==================== QContactPresence ======================= */

// XXX TODO add more stuff here
/*!
   \class QContactPresence
   \brief The QContactPresence class provides presence information
   for an online account of a contact.

   Presence information for a particular QContactOnlineAccount detail is provided
   in a QContactPresence detail which is linked (via linkedDetailUris()) to the
   account detail.  This information is generally provided by the backend, and is
   not modifiable by clients.

   Presence information can include update timestamp, screen name,
   and the status icon, status value, and status text provided by
   the service provider, as well as user defined status message.

   \sa QContactOnlineAccount

   \ingroup contacts-details
 */

/*!
   \variable QContactPresence::DefinitionName
   The string constant for the definition name of QContactPresence details.
 */
const QString QContactPresence::DefinitionName(QStringLiteral("Presence"));

/*!
   \variable QContactPresence::FieldTimestamp
   The field key constant for the timestamp value.
   \sa setTimestamp(), timestamp()
 */
const QString QContactPresence::FieldTimestamp(QStringLiteral("Timestamp"));

/*!
   \variable QContactPresence::FieldNickname
   The field key constant for the nickname value.
   \sa setNickname(), nickname()
 */
const QString QContactPresence::FieldNickname(QStringLiteral("Nickname"));

/*!
   \variable QContactPresence::FieldPresenceState
   The field key constant for the presence state enumeration value.
   \sa setPresenceState(), presenceState()
 */
const QString QContactPresence::FieldPresenceState(QStringLiteral("PresenceState"));

/*!
   \variable QContactPresence::FieldPresenceStateText
   The field key constant for the presence state description value.
   \sa setPresenceStateText(), presenceStateText()
 */
const QString QContactPresence::FieldPresenceStateText(QStringLiteral("PresenceStateText"));

/*!
   \variable QContactPresence::FieldPresenceStateImageUrl
   The field key constant for the presence state image URL.
   \sa setPresenceStateImageUrl(), presenceStateImageUrl()
 */
const QString QContactPresence::FieldPresenceStateImageUrl(QStringLiteral("PresenceStateImageUrl"));

/*!
   \variable QContactPresence::FieldCustomMessage
   The field key constant for the user-entered custom presence message.
   \sa setCustomMessage(), customMessage()
 */
const QString QContactPresence::FieldCustomMessage(QStringLiteral("CustomMessage"));

/*!
   \fn QContactPresence::setTimestamp(const QDateTime& updateTimestamp)

   Sets the timestamp for the last update of the presence detail to be
   \a updateTimestamp.
 */

/*!
   \fn QContactPresence::timestamp() const

    Returns the timestamp at which the data in the presence detail was valid.
 */

/*!
   \fn QContactPresence::setNickname(const QString& nickname)

   Sets the last-known nickname used by the contact during
   communications via the online account about which this detail
   stores presence information to \a nickname.
 */

/*!
   \fn QContactPresence::nickname() const

   Returns the last-known nickname used by the contact during
   communications via the online account.
 */

/*!
  \enum QContactPresence::PresenceState

  This enum defines the possible presence states supported by the default schema.
  Not all presence providers support all of these states.

  \value PresenceUnknown Signifies that the presence state of the contact is not currently known
  \value PresenceAvailable Signifies that the contact is available
  \value PresenceHidden Signifies that the contact is hidden
  \value PresenceBusy Signifies that the contact is busy
  \value PresenceAway Signifies that the contact is away
  \value PresenceExtendedAway Signifies that the contact is away for an extended period of time
  \value PresenceOffline Signifies that the contact is offline
 */

/*!
   \fn QContactPresence::setPresenceState(QContactPresence::PresenceState presenceState)

   Sets the presence state of the online account according to the presence
   information provider to the given \a presenceState.
 */

/*!
   \fn QContactPresence::presenceState() const

   Returns the presence state of the online account according to the
   presence provider.
 */

/*!
   \fn QContactPresence::setPresenceStateText(const QString& presenceStateText)

   Sets the text corresponding to the presence state to \a presenceStateText.
   This function is generally called by presence providers to allow custom
   naming of states, or to allow finer grained state reporting than is
   provided by the presence state API.
 */

/*!
   \fn QContactPresence::presenceStateText() const

   Returns the text corresponding to the current presence state.
 */

/*!
  \fn QContactPresence::setCustomMessage(const QString& customMessage)

   Sets the custom status message from the contact for the online account
   about which this detail stores presence information, to \a customMessage.
   This custom message would have been set by the contact,
   and does not necessarily correspond to a particular presence state.
 */

/*!
   \fn QContactPresence::customMessage() const

   Returns the custom status message from the contact for the online account
   about which this detail stores presence information.
 */

/*!
   \fn QContactPresence::setPresenceStateImageUrl(const QUrl& presenceStateImageUrl)

   Sets the last-known status image url of the contact for the online account
   about which this detail stores presence information, to \a presenceStateImageUrl.
 */

/*!
   \fn QContactPresence::presenceStateImageUrl() const

   Returns the last-known status image url of the contact for the online account
   about which this detail stores presence information.
 */

/* ==================== QContactGlobalPresence ======================= */

/*!
   \class QContactGlobalPresence
   \brief The QContactGlobalPresence class provides aggregated presence information
   for a contact, synthesized or supplied by the backend.
   \ingroup contacts-details
 */

/*!
   \variable QContactGlobalPresence::DefinitionName
   The string constant for the definition name of QContactGlobalPresence details.
 */
const QString QContactGlobalPresence::DefinitionName(QStringLiteral("GlobalPresence"));

/*!
   \variable QContactGlobalPresence::FieldTimestamp
   The field key constant for the timestamp value.
   \sa setTimestamp(), timestamp()
 */
const QString QContactGlobalPresence::FieldTimestamp(QStringLiteral("Timestamp"));

/*!
   \variable QContactGlobalPresence::FieldNickname
   The field key constant for the nickname value.
   \sa setNickname(), nickname()
 */
const QString QContactGlobalPresence::FieldNickname(QStringLiteral("Nickname"));

/*!
   \variable QContactGlobalPresence::FieldPresenceState
   The field key constant for the presence state enumeration value.
   \sa setPresenceState(), presenceState()
 */
const QString QContactGlobalPresence::FieldPresenceState(QStringLiteral("PresenceState"));

/*!
   \variable QContactGlobalPresence::FieldPresenceStateText
   The field key constant for the presence state description value.
   \sa setPresenceStateText(), presenceStateText()
 */
const QString QContactGlobalPresence::FieldPresenceStateText(QStringLiteral("PresenceStateText"));

/*!
   \variable QContactGlobalPresence::FieldPresenceStateImageUrl
   The field key constant for the presence state image URL.
   \sa setPresenceStateImageUrl(), presenceStateImageUrl()
 */
const QString QContactGlobalPresence::FieldPresenceStateImageUrl(QStringLiteral("PresenceStateImageUrl"));

/*!
   \variable QContactGlobalPresence::FieldCustomMessage

   The field key constant for the user-entered custom presence message.
   \sa setCustomMessage(), customMessage()
 */
const QString QContactGlobalPresence::FieldCustomMessage(QStringLiteral("CustomMessage"));

/*!
   \fn QContactGlobalPresence::setTimestamp(const QDateTime& updateTimestamp)

   Sets the update timestamp of the global presence detail to be
   \a updateTimestamp.
 */

/*!
   \fn QContactGlobalPresence::timestamp() const

    Returns the timestamp at which the data in the global presence detail was valid.
 */

/*!
   \fn QContactGlobalPresence::setNickname(const QString& nickname)

   Sets the last-known nickname used by the contact during
   communications via any online account about which this detail
   aggregates presence information to \a nickname.
 */

/*!
   \fn QContactGlobalPresence::nickname() const

   Returns the last-known nickname used by the contact during
   communications via any online account about which this detail
   aggregates presence information.
 */

/*!
   \fn QContactGlobalPresence::setPresenceState(QContactPresence::PresenceState presenceState)

   Sets the presence state of this aggregate detail according to the presence
   information available from the presence providers which this detail aggregates
   to the given \a presenceState.
 */

/*!
   \fn QContactGlobalPresence::presenceState() const

   Returns the aggregate presence state of any online accounts about which this detail
   aggregates presence information.
 */

/*!
   \fn QContactGlobalPresence::setPresenceStateText(const QString& presenceStateText)

   Sets the text corresponding to the presence state to \a presenceStateText.
   This function is generally called by presence providers to allow custom
   naming of states, or to allow finer grained state reporting than is
   provided by the presence state API.
 */

/*!
   \fn QContactGlobalPresence::presenceStateText() const

   Returns the text corresponding to the current presence state.
 */

/*!
  \fn QContactGlobalPresence::setCustomMessage(const QString& customMessage)

   Sets the custom status message from the contact for the aggregate presence
   detail, to \a customMessage.
 */

/*!
   \fn QContactGlobalPresence::customMessage() const

   Returns the custom status message from the contact for the aggregate presence
   detail.
 */

/*!
   \fn QContactGlobalPresence::setPresenceStateImageUrl(const QUrl& presenceStateImageUrl)

   Sets the last-known status image url of the contact to \a presenceStateImageUrl.
 */

/*!
   \fn QContactGlobalPresence::presenceStateImageUrl() const

   Returns the last-known status image url of the contact.
 */

/*!
  Returns a filter which matches any contact whose global presence state
  is listed as \a state.
 */
QContactFilter QContactGlobalPresence::match(QContactPresence::PresenceState state)
{
    QContactDetailFilter f;
    f.setDetailDefinitionName(QContactGlobalPresence::DefinitionName,
                              QContactGlobalPresence::FieldPresenceState);
    f.setValue(state);
    f.setMatchFlags(QContactFilter::MatchExactly);

    return f;
}

/* ==================== QContactPersonId ======================= */

/*!
   \class QContactPersonId
   \brief The QContactPersonId class contains the personid of a contact.This groups all together a persons contact details.
   \ingroup contacts-details
 */

/*!
   \variable QContactPersonId::DefinitionName
   The string constant for the definition name of QContactPersonId details.
 */
const QString QContactPersonId::DefinitionName(QStringLiteral("Personid"));

/*!
   \variable QContactPersonId::FieldPersonId

   The field key constant for the value containing the personid.
   \sa personId(), setPersonId()
 */
const QString QContactPersonId::FieldPersonId(QStringLiteral("Personid"));

/*!
   \fn QContactPersonId::personId() const

   Returns the personid of the contact, as stored in this detail.This groups all together a persons contact details.
 */

/*!
   \fn QContactPersonId::setPersonId(const QString& personid)

   Sets the personid of the contact (as stored in this detail) to personid.
 */


/* ==================== QContactExtendedDetail ======================= */
/*!
    \class QContactExtendedDetail
    \brief The QContactExtendedDetail class provides the possibility to save extended details to QContact objects.
    \inmodule QtContacts
    \ingroup contacts-details

    Different back-end engines may or may not support extended details for different contact types. Even
    if supported, they may accept different QVariant types as the data.
 */

/*!
    \variable QContactExtendedDetail::DefinitionName

    The constant string which identifies the definition of details which are extended details.
 */
const QString QContactExtendedDetail::DefinitionName(QStringLiteral("ExtendedDetail"));

/*!
    \variable QContactExtendedDetail::FieldName

    Contains the name of the extended detail.
 */
const QString QContactExtendedDetail::FieldName(QStringLiteral("Name"));

/*!
    \variable QContactExtendedDetail::FieldData

    Contains the data this extended detail.
 */
const QString QContactExtendedDetail::FieldData(QStringLiteral("Data"));

/*!
    \fn void QContactExtendedDetail::setName(const QString &name)

    Sets the \a name of this extended detail.
 */

/*!
    \fn QString QContactExtendedDetail::name() const

    Gets the name of this extended detail.
 */

/*!
    \fn void QContactExtendedDetail::setDetailData(const QVariant &data)

    Sets the \a data of the extended detail.
 */

/*!
    \fn QVariant QContactExtendedDetail::data() const

    Gets the data of this extended detail.
 */

/* ==================== Convenience Filters ======================= */

/*!
    Returns a filter suitable for finding contacts with a display label containing the specified
    \a label.
*/
QContactFilter QContactDisplayLabel::match(const QString &label)
{
    QContactDetailFilter f;
    f.setDetailDefinitionName(QContactDisplayLabel::DefinitionName,
                              QContactDisplayLabel::FieldLabel);
    f.setValue(label);
    f.setMatchFlags(QContactFilter::MatchContains);

    return f;
}

/*!
    Returns a filter suitable for finding contacts with a name with a first name containing the
    specified \a firstName and a last name containing the specified \a lastName.  If either
    parameter is empty, any value will match that component.
*/
QContactFilter QContactName::match(const QString &firstName, const QString &lastName)
{
    if (firstName.isEmpty()) {
        if (lastName.isEmpty()) {
            // Matches contacts that have a name
            QContactDetailFilter f;
            f.setDetailDefinitionName(QContactName::DefinitionName);
            return f;
        } else {
            // Contact with matching lastname
            QContactDetailFilter f;
            f.setDetailDefinitionName(QContactName::DefinitionName, QContactName::FieldLastName);
            f.setValue(lastName);
            f.setMatchFlags(QContactFilter::MatchContains);
            return f;
        }
    } else {
        if (lastName.isEmpty()) {
            // Contact with matching firstName
            QContactDetailFilter f;
            f.setDetailDefinitionName(QContactName::DefinitionName, QContactName::FieldFirstName);
            f.setValue(firstName);
            f.setMatchFlags(QContactFilter::MatchContains);
            return f;
        } else {
            // Match a contact with the specified first and last names
            // XXX This needs multi detail filter!

            // Best we can currently do is "and" and assume there's only one name per contact
            QContactDetailFilter f;
            f.setDetailDefinitionName(QContactName::DefinitionName, QContactName::FieldFirstName);
            f.setValue(firstName);
            f.setMatchFlags(QContactFilter::MatchContains);
            QContactDetailFilter l;
            l.setDetailDefinitionName(QContactName::DefinitionName, QContactName::FieldLastName);
            l.setValue(lastName);
            l.setMatchFlags(QContactFilter::MatchContains);

            return f & l;
        }
    }
}

/*!
    Returns a filter suitable for finding contacts with any name field (e.g. first, last) that
    contains the supplied \a name.
*/
QContactFilter QContactName::match(const QString &name)
{
    QContactUnionFilter nameFilter;
    QStringList nameFields;
    nameFields << QContactName::FieldCustomLabel
            << QContactName::FieldFirstName
            << QContactName::FieldLastName
            << QContactName::FieldMiddleName
            << QContactName::FieldPrefix
            << QContactName::FieldSuffix;
    foreach (const QString& fieldName, nameFields) {
        QContactDetailFilter subFilter;
        subFilter.setDetailDefinitionName(QContactName::DefinitionName, fieldName);
        subFilter.setValue(name);
        subFilter.setMatchFlags(QContactFilter::MatchContains);
        nameFilter.append(subFilter);
    }
    return nameFilter;
}

/*!
    Returns a filter suitable for finding contacts with an email address containing the specified
    \a emailAddress.
*/
QContactFilter QContactEmailAddress::match(const QString &emailAddress)
{
    QContactDetailFilter l;
    l.setDetailDefinitionName(QContactEmailAddress::DefinitionName, QContactEmailAddress::FieldEmailAddress);
    l.setValue(emailAddress);
    l.setMatchFlags(QContactFilter::MatchContains);
    return l;
}

/*!
    Returns a filter suitable for finding contacts with a phone number containing the specified
    \a number.
*/
QContactFilter QContactPhoneNumber::match(const QString &number)
{
    QContactDetailFilter l;
    l.setDetailDefinitionName(QContactPhoneNumber::DefinitionName, QContactPhoneNumber::FieldNumber);
    l.setValue(number);
    l.setMatchFlags(QContactFilter::MatchPhoneNumber);
    return l;
}


QTCONTACTS_END_NAMESPACE
