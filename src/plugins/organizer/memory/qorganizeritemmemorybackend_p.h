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

#ifndef QCONTACTMEMORYBACKEND_P_H
#define QCONTACTMEMORYBACKEND_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <qorganizeritemengineid.h>
#include <qorganizercollectionengineid.h>
#include <qorganizermanagerengine.h>
#include <qorganizermanagerenginefactory.h>
#include <qorganizeritemchangeset.h>
#include <qorganizerrecurrencerule.h>

#ifdef QT_SIMULATOR
#define Q_ORGANIZER_MEMORYENGINE_EXPORT Q_ORGANIZER_EXPORT
#else
#define Q_ORGANIZER_MEMORYENGINE_EXPORT
#endif

QTORGANIZER_BEGIN_NAMESPACE

class Q_ORGANIZER_MEMORYENGINE_EXPORT QOrganizerItemMemoryFactory : public QObject, public QOrganizerManagerEngineFactory
{
    Q_OBJECT
    Q_INTERFACES(QtOrganizer::QOrganizerManagerEngineFactory)
public:
    QOrganizerManagerEngine* engine(const QMap<QString, QString>& parameters, QOrganizerManager::Error*);
    QOrganizerItemEngineId* createItemEngineId(const QMap<QString, QString>& parameters, const QString& idString) const;
    QOrganizerCollectionEngineId* createCollectionEngineId(const QMap<QString, QString>& parameters, const QString& idString) const;
    QString managerName() const;
};

class Q_ORGANIZER_MEMORYENGINE_EXPORT QOrganizerItemMemoryEngineId : public QOrganizerItemEngineId
{
public:
    QOrganizerItemMemoryEngineId();
    QOrganizerItemMemoryEngineId(quint32 collectionId, quint32 itemId, const QString& managerUri);
    ~QOrganizerItemMemoryEngineId();
    QOrganizerItemMemoryEngineId(const QOrganizerItemMemoryEngineId& other);
    QOrganizerItemMemoryEngineId(const QString& idString);

    bool isEqualTo(const QOrganizerItemEngineId* other) const;
    bool isLessThan(const QOrganizerItemEngineId* other) const;

    QString managerUri() const;
    QOrganizerItemEngineId* clone() const;

    QString toString() const;

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const;
#endif
    uint hash() const;

private:
    quint32 m_collectionId;
    quint32 m_itemId;
    QString m_managerUri;
    friend class QOrganizerItemMemoryEngine;
};

class Q_ORGANIZER_MEMORYENGINE_EXPORT QOrganizerCollectionMemoryEngineId : public QOrganizerCollectionEngineId
{
public:
    QOrganizerCollectionMemoryEngineId();
    QOrganizerCollectionMemoryEngineId(quint32 collectionId, const QString& managerUri);
    ~QOrganizerCollectionMemoryEngineId();
    QOrganizerCollectionMemoryEngineId(const QOrganizerCollectionMemoryEngineId& other);
    QOrganizerCollectionMemoryEngineId(const QString& idString);

    bool isEqualTo(const QOrganizerCollectionEngineId* other) const;
    bool isLessThan(const QOrganizerCollectionEngineId* other) const;

    QString managerUri() const;
    QOrganizerCollectionEngineId* clone() const;

    QString toString() const;

#ifndef QT_NO_DEBUG_STREAM
    QDebug& debugStreamOut(QDebug& dbg) const;
#endif
    uint hash() const;

private:
    quint32 m_collectionId;
    QString m_managerUri;
    friend class QOrganizerItemMemoryEngine;
};

class QOrganizerAbstractRequest;
class QOrganizerManagerEngine;
class Q_ORGANIZER_MEMORYENGINE_EXPORT QOrganizerItemMemoryEngineData : public QSharedData
{
public:
    QOrganizerItemMemoryEngineData();
    ~QOrganizerItemMemoryEngineData()
    {
    }

    QAtomicInt m_refCount;
    QString m_id;                                  // the id parameter value

    QHash<QOrganizerItemId, QOrganizerItem> m_idToItemHash; // hash of id to the item identified by that id
    QMultiHash<QOrganizerItemId, QOrganizerItemId> m_parentIdToChildIdHash; // hash of id to that item's children's ids

    QList<QOrganizerCollection> m_organizerCollections;          // list of collections
    QList<QOrganizerCollectionId> m_organizerCollectionIds; // list of collection ids
    QMultiMap<QOrganizerCollectionId, QOrganizerItemId> m_itemsInCollections; // map of collection ids to the ids of items the collection contains.
    QList<QString> m_definitionIds;                // list of definition types (id's)
    quint32 m_nextOrganizerItemId; // the m_itemId portion of a QOrganizerItemMemoryEngineId.
    quint32 m_nextOrganizerCollectionId; // the m_collectionId portion of a QOrganizerCollectionMemoryEngineId.
    bool m_anonymous;                              // Is this backend ever shared?
    QString m_managerUri;                        // for faster lookup.

    void emitSharedSignals(QOrganizerItemChangeSet* cs)
    {
        foreach(QOrganizerManagerEngine* engine, m_sharedEngines)
            cs->emitSignals(engine);
    }

    QList<QOrganizerManagerEngine*> m_sharedEngines;   // The list of engines that share this data
};

class Q_ORGANIZER_MEMORYENGINE_EXPORT QOrganizerItemMemoryEngine : public QOrganizerManagerEngine
{
    Q_OBJECT

public:
    static QOrganizerItemMemoryEngine *createMemoryEngine(const QMap<QString, QString>& parameters);

    ~QOrganizerItemMemoryEngine();

    /* URI reporting */
    QString managerName() const;
    QMap<QString, QString> managerParameters() const;
    /*! \reimp */
    int managerVersion() const {return 1;}

    virtual QList<QOrganizerItem> itemOccurrences(const QOrganizerItem& parentItem, const QDateTime& periodStart, const QDateTime& periodEnd, int maxCount, const QOrganizerItemFetchHint& fetchHint, QOrganizerManager::Error* error) const;

    virtual QList<QOrganizerItemId> itemIds(const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, QOrganizerManager::Error* error) const;
    virtual QList<QOrganizerItem> items(const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, const QOrganizerItemFetchHint& fetchHint, QOrganizerManager::Error* error) const;
    virtual QList<QOrganizerItem> items(const QDateTime &startDate, const QDateTime &endDate, int maxCount, const QOrganizerItemFilter &filter, const QOrganizerItemFetchHint &fetchHint, QOrganizerManager::Error *error) const;
    virtual QList<QOrganizerItem> itemsForExport(const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, const QOrganizerItemFetchHint& fetchHint, QOrganizerManager::Error* error) const;
    virtual QList<QOrganizerItem> itemsForExport(const QList<QOrganizerItemId> &itemIds, const QOrganizerItemFetchHint &fetchHint, QMap<int, QOrganizerManager::Error> *errorMap, QOrganizerManager::Error *error) const;
    virtual QOrganizerItem item(const QOrganizerItemId& organizeritemId, const QOrganizerItemFetchHint& fetchHint, QOrganizerManager::Error* error) const;

    virtual bool saveItems(QList<QOrganizerItem>* organizeritems, QMap<int, QOrganizerManager::Error>* errorMap, QOrganizerManager::Error* error);
    virtual bool saveItems(QList<QOrganizerItem> *items, const QList<QOrganizerItemDetail::DetailType> &definitionMask, QMap<int, QOrganizerManager::Error> *errorMap, QOrganizerManager::Error *error);
    virtual bool removeItems(const QList<QOrganizerItemId>& organizeritemIds, QMap<int, QOrganizerManager::Error>* errorMap, QOrganizerManager::Error* error);

    virtual QOrganizerCollection defaultCollection(QOrganizerManager::Error* error) const;
    virtual QOrganizerCollection collection(const QOrganizerCollectionId &collectionId, QOrganizerManager::Error *error) const;
    virtual QList<QOrganizerCollection> collections(QOrganizerManager::Error* error) const;
    virtual bool saveCollection(QOrganizerCollection* collection, QOrganizerManager::Error* error);
    virtual bool removeCollection(const QOrganizerCollectionId& collectionId, QOrganizerManager::Error* error);

    /* Asynchronous Request Support */
    virtual void requestDestroyed(QOrganizerAbstractRequest* req);
    virtual bool startRequest(QOrganizerAbstractRequest* req);
    virtual bool cancelRequest(QOrganizerAbstractRequest* req);
    virtual bool waitForRequestFinished(QOrganizerAbstractRequest* req, int msecs);

    /* Capabilities reporting */
    /*! \reimp */
    virtual QList<QOrganizerItemFilter::FilterType> supportedFilters() const
    {
        QList<QOrganizerItemFilter::FilterType> supported;

        supported << QOrganizerItemFilter::InvalidFilter
                  << QOrganizerItemFilter::DetailFilter
                  << QOrganizerItemFilter::DetailRangeFilter
                  << QOrganizerItemFilter::ChangeLogFilter
                  << QOrganizerItemFilter::IntersectionFilter
                  << QOrganizerItemFilter::UnionFilter
                  << QOrganizerItemFilter::IdFilter
                  << QOrganizerItemFilter::CollectionFilter
                  << QOrganizerItemFilter::DefaultFilter;

        return supported;
    }
    /*! \reimp */
    virtual QList<QOrganizerItemDetail::DetailType> supportedItemDetails(QOrganizerItemType::ItemType itemType) const;

    /*! \reimp */
    virtual QList<QOrganizerItemType::ItemType> supportedItemTypes() const
    {
        return QList<QOrganizerItemType::ItemType>() << QOrganizerItemType::TypeEvent
                             << QOrganizerItemType::TypeEventOccurrence
                             << QOrganizerItemType::TypeJournal
                             << QOrganizerItemType::TypeNote
                             << QOrganizerItemType::TypeTodo
                             << QOrganizerItemType::TypeTodoOccurrence;
    }

protected:
    QOrganizerItemMemoryEngine(QOrganizerItemMemoryEngineData* data);

protected:
    /* Implement "signal coalescing" for batch functions via change set */
    virtual bool saveItem(QOrganizerItem* theOrganizerItem, QOrganizerItemChangeSet& changeSet, QOrganizerManager::Error* error);
    virtual bool removeItem(const QOrganizerItemId& organizeritemId, QOrganizerItemChangeSet& changeSet, QOrganizerManager::Error* error);

private:
    QOrganizerItem item(const QOrganizerItemId& organizeritemId) const;
    QList<QOrganizerItem> internalItems(const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, const QOrganizerItemFetchHint& fetchHint, QOrganizerManager::Error* error, bool forExport) const;
    QList<QOrganizerItem> internalItemOccurrences(const QOrganizerItem& parentItem, const QDateTime& periodStart, const QDateTime& periodEnd, int maxCount, bool includeExceptions, QOrganizerManager::Error* error) const;
    void addItemRecurrences(QList<QOrganizerItem>& sorted, const QOrganizerItem& c, const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, bool forExport, QSet<QOrganizerItemId>* parentsAdded) const;

    bool fixOccurrenceReferences(QOrganizerItem* item, QOrganizerManager::Error* error);
    bool typesAreRelated(QOrganizerItemType::ItemType occurrenceType, QOrganizerItemType::ItemType parentType);

    void performAsynchronousOperation(QOrganizerAbstractRequest* request);

    static QOrganizerItem generateOccurrence(const QOrganizerItem& parentItem, const QDateTime& rdate);

    QList<QDateTime> generateDateTimes(const QDateTime& initialDateTime, QOrganizerRecurrenceRule rrule, const QDateTime& periodStart, const QDateTime& periodEnd, int maxCount) const;
    void inferMissingCriteria(QOrganizerRecurrenceRule* rrule, const QDate& initialDate) const;
    bool inMultipleOfInterval(const QDate& date, const QDate& initialDate, QOrganizerRecurrenceRule::Frequency frequency, int interval, Qt::DayOfWeek firstDayOfWeek, int maxCount) const;
    QDate firstDateInPeriod(const QDate& date, QOrganizerRecurrenceRule::Frequency frequency, Qt::DayOfWeek firstDayOfWeek) const;
    QDate firstDateInNextPeriod(const QDate& date, QOrganizerRecurrenceRule::Frequency frequency, Qt::DayOfWeek firstDayOfWeek) const;
    QList<QDate> matchingDates(const QDate& periodStart, const QDate& periodEnd, const QOrganizerRecurrenceRule& rrule) const;
    QList<QDate> filterByPosition(const QList<QDate>& dates, const QSet<int> positions) const;
    bool itemHasReccurence(const QOrganizerItem& oi) const;

    QOrganizerItemMemoryEngineData* d;
    static QMap<QString, QOrganizerItemMemoryEngineData*> engineDatas;
};

QTORGANIZER_END_NAMESPACE

#endif
