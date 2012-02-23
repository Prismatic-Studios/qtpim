/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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

#include <QtTest/QtTest>

#include "qorganizer.h"

//TESTED_COMPONENT=src/organizer

QTORGANIZER_USE_NAMESPACE
class tst_QOrganizerItemDetails : public QObject
{
Q_OBJECT

public:
    tst_QOrganizerItemDetails();
    virtual ~tst_QOrganizerItemDetails();

public slots:
    void init();
    void cleanup();

private slots:
    // leaf class testing
    void description();
    void displayLabel();
    void guid();
    void location();
    void parent();
    void priority();
    void recurrence();
    void tag();
    void timestamp();
    void type();

    void todoProgress();

    // time range
    void eventTime();
    void journalTime();
    void todoTime();

    // reminders
    void reminder();
    void audibleReminder();
    void emailReminder();
    void visualReminder();

    void attendee();
    void rsvp();
    void classification();
    void version();
};

tst_QOrganizerItemDetails::tst_QOrganizerItemDetails()
{
}

tst_QOrganizerItemDetails::~tst_QOrganizerItemDetails()
{
}

void tst_QOrganizerItemDetails::init()
{
}

void tst_QOrganizerItemDetails::cleanup()
{
}


void tst_QOrganizerItemDetails::description()
{
    QOrganizerItemDescription d1;
    QOrganizerItem oi;
    QVERIFY(d1.description().isEmpty());
    QVERIFY(d1.value(QOrganizerItemDescription::FieldDescription).isNull());
    d1.setValue(QOrganizerItemDescription::FieldDescription, "Test");
    QVERIFY(d1.value(QOrganizerItemDescription::FieldDescription) == QString("Test"));
    QVERIFY(d1.description() == QString("Test"));

    QOrganizerItemDescription d2;
    d2.setValue(QOrganizerItemDescription::FieldDescription, "Test 2");

    // test property add -- description is unique.
    QVERIFY(oi.saveDetail(&d2));
    QCOMPARE(oi.details(QOrganizerItemDescription::DefinitionName).count(), 1); // count should be 1
    QVERIFY(oi.saveDetail(&d1));
    QCOMPARE(oi.details(QOrganizerItemDescription::DefinitionName).count(), 1); // count should be 1

    // test property update
    d1.setDescription("Test 3");
    QVERIFY(oi.saveDetail(&d1));
    QCOMPARE(oi.details(QOrganizerItemDescription::DefinitionName).count(), 1); // count should be 1
    QVERIFY(oi.detail<QOrganizerItemDescription>().description() == QString("Test 3"));

    // test property remove
    QVERIFY(oi.removeDetail(&d1));
    QCOMPARE(oi.details<QOrganizerItemDescription>().count(), 0);
}

void tst_QOrganizerItemDetails::displayLabel()
{
    QOrganizerItemDisplayLabel d1;
    QOrganizerItem oi;

    QVERIFY(d1.label().isEmpty());
    QVERIFY(d1.value(QOrganizerItemDisplayLabel::FieldLabel).isNull());
    d1.setValue(QOrganizerItemDisplayLabel::FieldLabel, "Test");
    QVERIFY(d1.value(QOrganizerItemDisplayLabel::FieldLabel) == QString("Test"));
    QVERIFY(d1.label() == QString("Test"));

    QOrganizerItemDisplayLabel d2;
    d2.setValue(QOrganizerItemDisplayLabel::FieldLabel, "Test 2");

    // test property add - should update.
    QVERIFY(oi.saveDetail(&d2));
    QCOMPARE(oi.details(QOrganizerItemDisplayLabel::DefinitionName).count(), 1);
    QVERIFY(oi.saveDetail(&d1));
    QCOMPARE(oi.details(QOrganizerItemDisplayLabel::DefinitionName).count(), 1);

    // test property update - should update
    d1.setLabel("Test 3");
    QVERIFY(oi.saveDetail(&d1));
    QCOMPARE(oi.details(QOrganizerItemDisplayLabel::DefinitionName).count(), 1);
    QVERIFY(oi.detail<QOrganizerItemDisplayLabel>().label() == QString("Test 3"));

    // test property remove
    QVERIFY(oi.removeDetail(&d1)); // can remove display label.  it's unique but not required.
    QCOMPARE(oi.details<QOrganizerItemDisplayLabel>().count(), 0);
}


void tst_QOrganizerItemDetails::guid()
{
    QOrganizerItem oi;
    QOrganizerItemGuid g1, g2;

    // test property set
    g1.setGuid("1234");
    QCOMPARE(g1.guid(), QString("1234"));
    QCOMPARE(g1.value(QOrganizerItemGuid::FieldGuid).toString(), QString("1234"));

    // test property add
    QVERIFY(oi.saveDetail(&g1));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).count(), 1);
    QCOMPARE(QOrganizerItemGuid(oi.details(QOrganizerItemGuid::DefinitionName).value(0)).guid(), g1.guid());

    // test property update
    g1.setValue(101,"label1");
    g1.setGuid("12345");
    QVERIFY(oi.saveDetail(&g1));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).value(0).value(101).toString(), QString("label1"));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).value(0).value(QOrganizerItemGuid::FieldGuid).toString(), QString("12345"));

    // test property remove
    QVERIFY(oi.removeDetail(&g1));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).count(), 0);
    QVERIFY(oi.saveDetail(&g2));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).count(), 1);
    QVERIFY(oi.removeDetail(&g2));
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).count(), 0);
    QVERIFY(oi.removeDetail(&g2) == false);
    QCOMPARE(oi.details(QOrganizerItemGuid::DefinitionName).count(), 0);
}

void tst_QOrganizerItemDetails::location()
{
    QOrganizerItemLocation l1;
    QOrganizerItem oi;

    QVERIFY(l1.isEmpty());
    l1.setLatitude(0.12345);
    QVERIFY(!l1.isEmpty());
    QVERIFY(l1.latitude() == 0.12345);
    l1.setValue(QOrganizerItemLocation::FieldLongitude, 0.54321);
    QVERIFY(l1.longitude() == 0.54321);
    l1.setLabel("test");
    QVERIFY(l1.label() == QString("test"));

    QVERIFY(oi.details<QOrganizerItemLocation>().size() == 0);
    QVERIFY(oi.saveDetail(&l1));
    QVERIFY(oi.details<QOrganizerItemLocation>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemLocation>() == l1);

    l1.setLabel("test 2");
    QVERIFY(oi.detail<QOrganizerItemLocation>() != l1);
    QVERIFY(oi.saveDetail(&l1)); // update.
    QVERIFY(oi.details<QOrganizerItemLocation>().size() == 1); // should update, not add another.
    QVERIFY(oi.detail<QOrganizerItemLocation>() == l1);

    oi.removeDetail(&l1);
    QVERIFY(oi.details<QOrganizerItemLocation>().size() == 0);
}

void tst_QOrganizerItemDetails::parent()
{
    QOrganizerItemParent p;
    QOrganizerItem oi;

    // hrm, how to test parent local id?

    QVERIFY(p.isEmpty());
    p.setOriginalDate(QDate(2010, 10, 13));
    QVERIFY(p.originalDate() == QDate(2010, 10, 13));
    QVERIFY(!p.isEmpty());

    QVERIFY(oi.saveDetail(&p));
    QVERIFY(oi.details<QOrganizerItemParent>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemParent>() == p);

    p.setOriginalDate(QDate(2010, 10, 14));
    QVERIFY(oi.detail<QOrganizerItemParent>() != p);
    QVERIFY(oi.saveDetail(&p)); // update
    QVERIFY(oi.detail<QOrganizerItemParent>() == p);

    QVERIFY(oi.removeDetail(&p));
    QVERIFY(oi.details<QOrganizerItemParent>().size() == 0);
}

void tst_QOrganizerItemDetails::priority()
{
    QOrganizerItemPriority p;
    QOrganizerItem oi;

    QVERIFY(p.isEmpty());
    p.setValue(QOrganizerItemPriority::FieldPriority, QOrganizerItemPriority::VeryHighPriority);
    QVERIFY(p.priority() == QOrganizerItemPriority::VeryHighPriority);
    QVERIFY(oi.saveDetail(&p));
    QVERIFY(oi.details<QOrganizerItemPriority>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemPriority>() == p);

    p.setPriority(QOrganizerItemPriority::VeryLowPriority);
    QVERIFY(oi.detail<QOrganizerItemPriority>() != p);
    QVERIFY(oi.saveDetail(&p));
    QVERIFY(oi.details<QOrganizerItemPriority>().size() == 1); // update shouldn't add another detail.
    QVERIFY(oi.detail<QOrganizerItemPriority>() == p);

    QVERIFY(oi.removeDetail(&p));
    QVERIFY(oi.details<QOrganizerItemPriority>().size() == 0);
}

void tst_QOrganizerItemDetails::recurrence()
{
    QOrganizerItemRecurrence r;
    QOrganizerEvent e;

    QOrganizerRecurrenceRule testRule;
    testRule.setFrequency(QOrganizerRecurrenceRule::Weekly);
    testRule.setLimit(4);
    QSet<QOrganizerRecurrenceRule> rrules;
    rrules << testRule;

    QOrganizerRecurrenceRule exrule;
    exrule.setFrequency(QOrganizerRecurrenceRule::Daily);
    testRule.setLimit(12);
    QSet<QOrganizerRecurrenceRule> exrules;
    exrules << exrule;

    QSet<QDate> rdates, exdates;
    rdates << QDate(2010, 10, 13);
    exdates << QDate(2010, 11, 17) << QDate(2010, 11, 20);

    QVERIFY(e.details<QOrganizerItemRecurrence>().size() == 0);
    r.setRecurrenceRules(rrules);
    QVERIFY(r.recurrenceRules() == rrules);
    QVERIFY(r.recurrenceDates().isEmpty());
    QVERIFY(r.exceptionRules().isEmpty());

    r.setExceptionRules(exrules);
    QVERIFY(r.recurrenceRules() == rrules);
    QVERIFY(r.exceptionRules() == exrules);
    QVERIFY(r.exceptionDates().isEmpty());

    r.setRecurrenceDates(rdates);
    QVERIFY(r.recurrenceDates() == rdates);
    QVERIFY(r.exceptionDates().isEmpty());
    QVERIFY(r.recurrenceRules() == rrules);
    QVERIFY(r.exceptionRules() == exrules);

    r.setExceptionDates(exdates);
    QVERIFY(r.recurrenceDates() == rdates);
    QVERIFY(r.exceptionDates() == exdates);
    QVERIFY(r.recurrenceRules() == rrules);
    QVERIFY(r.exceptionRules() == exrules);

    // now save.
    QVERIFY(e.saveDetail(&r));
    QVERIFY(e.details<QOrganizerItemRecurrence>().size() == 1);
    QVERIFY(e.detail<QOrganizerItemRecurrence>() == r);

    // update
    exdates << QDate(2010, 10, 17);
    r.setExceptionDates(exdates);
    QVERIFY(e.detail<QOrganizerItemRecurrence>() != r);
    QVERIFY(e.saveDetail(&r));
    QVERIFY(e.detail<QOrganizerItemRecurrence>() == r);
    QVERIFY(e.details<QOrganizerItemRecurrence>().size() == 1); // should update, not add another.

    // remove.
    QVERIFY(e.removeDetail(&r));
    QVERIFY(e.details<QOrganizerItemRecurrence>().size() == 0);
}

void tst_QOrganizerItemDetails::tag()
{
    QOrganizerItem oi;
    QOrganizerItemTag t1, t2;

    // test property set
    t1.setTag("red");
    QCOMPARE(t1.tag(), QString("red"));
    QCOMPARE(t1.value(QOrganizerItemTag::FieldTag).toString(), QString("red"));

    // test property add
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).count(), 1);
    QCOMPARE(QOrganizerItemTag(oi.details(QOrganizerItemTag::DefinitionName).value(0)).tag(), t1.tag());
    QVERIFY(oi.saveDetail(&t2));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).count(), 2);

    // test property update
    t1.setValue(101,"label1");
    t1.setTag("green");
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).value(0).value(101).toString(), QString("label1"));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).value(0).value(QOrganizerItemTag::FieldTag).toString(), QString("green"));

    // test property remove
    QVERIFY(oi.removeDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).count(), 1);
    QVERIFY(oi.removeDetail(&t2));
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).count(), 0);
    QVERIFY(oi.removeDetail(&t2) == false);
    QCOMPARE(oi.details(QOrganizerItemTag::DefinitionName).count(), 0);
}


void tst_QOrganizerItemDetails::timestamp()
{
    QOrganizerItem oi;
    QOrganizerItemTimestamp t1, t2;
    QDateTime modified = QDateTime::currentDateTime();
    QDateTime created = modified.addSecs(-43);

    // test property set
    t1.setCreated(created);
    QCOMPARE(t1.created(), created);
    QCOMPARE(t1.value(QOrganizerItemTimestamp::FieldCreated).toDateTime(), created);

    // test property add
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).count(), 1);
    QCOMPARE(QOrganizerItemTimestamp(oi.details(QOrganizerItemTimestamp::DefinitionName).value(0)).created(), t1.created());

    // test property update
    t1.setValue(101,"label1");
    t1.setLastModified(modified);
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).value(0).value(101).toString(), QString("label1"));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).value(0).value(QOrganizerItemTimestamp::FieldCreated).toDateTime(), created);
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).value(0).value(QOrganizerItemTimestamp::FieldLastModified).toDateTime(), modified);

    // test property remove
    QVERIFY(oi.removeDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).count(), 0);
    t2.setCreated(created.addSecs(15));
    QVERIFY(oi.saveDetail(&t2));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).count(), 1);
    QVERIFY(oi.removeDetail(&t2));
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).count(), 0);
    QVERIFY(oi.removeDetail(&t2) == false);
    QCOMPARE(oi.details(QOrganizerItemTimestamp::DefinitionName).count(), 0);
}

void tst_QOrganizerItemDetails::todoProgress()
{
    QOrganizerTodoProgress p;
    QOrganizerTodo t;

    QVERIFY(p.status() == QOrganizerTodoProgress::StatusNotStarted);
    QVERIFY(p.isEmpty());
    p.setStatus(QOrganizerTodoProgress::StatusInProgress);
    QVERIFY(!p.isEmpty());
    QVERIFY(p.status() == QOrganizerTodoProgress::StatusInProgress);

    p.setPercentageComplete(50);
    QVERIFY(p.percentageComplete() == 50);
    p.setPercentageComplete(200); // this should fail
    QVERIFY(p.percentageComplete() == 50); // value should remain unchanged.

    p.setFinishedDateTime(QDateTime(QDate(2010, 10, 13)));
    QVERIFY(p.finishedDateTime() == QDateTime(QDate(2010, 10, 13)));
    QVERIFY(p.status() != QOrganizerTodoProgress::StatusComplete); // XXX TODO: should this be automatic?
    p.setPercentageComplete(100);
    QVERIFY(p.percentageComplete() == 100);
    QVERIFY(p.status() != QOrganizerTodoProgress::StatusComplete); // XXX TODO: should this be automatic?

    // add
    QVERIFY(t.saveDetail(&p));
    QVERIFY(t.details<QOrganizerTodoProgress>().size() == 1);
    QVERIFY(t.detail<QOrganizerTodoProgress>() == p);

    // update
    p.setStatus(QOrganizerTodoProgress::StatusComplete);
    QVERIFY(p.status() == QOrganizerTodoProgress::StatusComplete);
    QVERIFY(t.detail<QOrganizerTodoProgress>() != p);
    QVERIFY(t.saveDetail(&p));
    QVERIFY(t.details<QOrganizerTodoProgress>().size() == 1); // update, not add another
    QVERIFY(t.detail<QOrganizerTodoProgress>() == p);

    // remove
    QVERIFY(t.removeDetail(&p));
    QVERIFY(t.details<QOrganizerTodoProgress>().size() == 0);
}

void tst_QOrganizerItemDetails::type()
{
    QOrganizerItem oi;
    QOrganizerItemType t1, t2;

    QOrganizerEvent e;
    QOrganizerNote n;
    QOrganizerTodo t;
    QOrganizerJournal j;
    QOrganizerEventOccurrence eo;
    QOrganizerTodoOccurrence to;
    QVERIFY(e.type() == QOrganizerItemType::TypeEvent);
    QVERIFY(n.type() == QOrganizerItemType::TypeNote);
    QVERIFY(t.type() == QOrganizerItemType::TypeTodo);
    QVERIFY(j.type() == QOrganizerItemType::TypeJournal);
    QVERIFY(eo.type() == QOrganizerItemType::TypeEventOccurrence);
    QVERIFY(to.type() == QOrganizerItemType::TypeTodoOccurrence);

    // test property set
    t1.setType(QOrganizerItemType::TypeEvent);
    QCOMPARE(t1.type(), QOrganizerItemType::TypeEvent);
    QCOMPARE(static_cast<QOrganizerItemType::ItemType>(t1.value(QOrganizerItemType::FieldType).toInt()), QOrganizerItemType::TypeEvent);

    // test property add
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(oi.details(QOrganizerItemType::DefinitionName).count(), 1);
    QCOMPARE(QOrganizerItemType(oi.details(QOrganizerItemType::DefinitionName).value(0)).type(), t1.type());

    // test property update
    t1.setType(QOrganizerItemType::TypeTodo);
    QVERIFY(oi.saveDetail(&t1));
    QCOMPARE(static_cast<QOrganizerItemType::ItemType>(oi.details(QOrganizerItemType::DefinitionName).value(0).value(QOrganizerItemType::FieldType).toInt()), QOrganizerItemType::TypeTodo);

    // test property remove
    QVERIFY(!oi.removeDetail(&t1)); // cannot remove type
    QCOMPARE(oi.details(QOrganizerItemType::DefinitionName).count(), 1);
    t2.setType(QOrganizerItemType::TypeNote);
    QVERIFY(oi.saveDetail(&t2)); // overwrites t1
    QCOMPARE(oi.details(QOrganizerItemType::DefinitionName).count(), 1);
    QVERIFY(!oi.removeDetail(&t2)); // cannot remove type - "succeeds" but count remains unchanged
    QCOMPARE(oi.details(QOrganizerItemType::DefinitionName).count(), 1);
    QVERIFY(!oi.removeDetail(&t2));
    QCOMPARE(oi.details(QOrganizerItemType::DefinitionName).count(), 1);
}


void tst_QOrganizerItemDetails::eventTime()
{
    QOrganizerEventTime r;
    QOrganizerEvent e;

    QVERIFY(r.isEmpty());
    QVERIFY(!r.isAllDay());

    r.setStartDateTime(QDateTime(QDate(2010, 10, 13)));
    QVERIFY(r.startDateTime() == QDateTime(QDate(2010, 10, 13)));
    QVERIFY(!r.isAllDay());
    r.setAllDay(true);
    QVERIFY(r.isAllDay());

    r.setEndDateTime(QDateTime(QDate(2010, 10, 14)));
    QVERIFY(r.endDateTime() == QDateTime(QDate(2010, 10, 14)));

    // add
    QOrganizerEventTime r2;
    r2.setStartDateTime(QDateTime(QDate(2010, 10, 23)));
    r2.setEndDateTime(QDateTime(QDate(2010, 10, 24)));
    QVERIFY(e.saveDetail(&r));
    QVERIFY(e.details<QOrganizerEventTime>().size() == 1);
    QVERIFY(e.detail<QOrganizerEventTime>() == r);
    QVERIFY(e.saveDetail(&r2)); // note that we don't enforce uniqueness in organizeritem; that's done by the manager!
    QVERIFY(e.details<QOrganizerEventTime>().size() == 2);
    QVERIFY(e.removeDetail(&r2));
    QVERIFY(e.details<QOrganizerEventTime>().size() == 1);
    QVERIFY(e.detail<QOrganizerEventTime>() == r);

    // update
    r.setAllDay(false);
    QVERIFY(e.detail<QOrganizerEventTime>() != r);
    QVERIFY(e.saveDetail(&r));
    QVERIFY(e.detail<QOrganizerEventTime>() == r);
    QVERIFY(e.details<QOrganizerEventTime>().size() == 1);

    // remove
    QVERIFY(e.removeDetail(&r));
    QVERIFY(e.details<QOrganizerEventTime>().size() == 0);
}

void tst_QOrganizerItemDetails::journalTime()
{
    QOrganizerJournalTime r;
    QOrganizerJournal j;

    QVERIFY(r.isEmpty());
    r.setEntryDateTime(QDateTime(QDate(2010, 10, 13)));
    QVERIFY(r.entryDateTime() == QDateTime(QDate(2010, 10, 13)));

    // add
    QOrganizerJournalTime r2;
    r2.setEntryDateTime(QDateTime(QDate(2010, 10, 23)));
    QVERIFY(j.saveDetail(&r));
    QVERIFY(j.details<QOrganizerJournalTime>().size() == 1);
    QVERIFY(j.detail<QOrganizerJournalTime>() == r);
    QVERIFY(j.saveDetail(&r2)); // note that we don't enforce uniqueness in organizeritem; that's done by the manager!
    QVERIFY(j.details<QOrganizerJournalTime>().size() == 2);
    QVERIFY(j.removeDetail(&r2));
    QVERIFY(j.details<QOrganizerJournalTime>().size() == 1);
    QVERIFY(j.detail<QOrganizerJournalTime>() == r);

    // update
    r.setEntryDateTime(QDateTime(QDate(2010, 11, 05)));
    QVERIFY(j.detail<QOrganizerJournalTime>() != r);
    QVERIFY(j.saveDetail(&r));
    QVERIFY(j.detail<QOrganizerJournalTime>() == r);
    QVERIFY(j.details<QOrganizerJournalTime>().size() == 1);

    // remove
    QVERIFY(j.removeDetail(&r));
    QVERIFY(j.details<QOrganizerJournalTime>().size() == 0);
}

void tst_QOrganizerItemDetails::todoTime()
{
    QOrganizerTodoTime r;
    QOrganizerTodo t;

    QVERIFY(r.isEmpty());
    QVERIFY(!r.isAllDay());

    r.setStartDateTime(QDateTime(QDate(2010, 10, 13)));
    QVERIFY(r.startDateTime() == QDateTime(QDate(2010, 10, 13)));
    QVERIFY(!r.isAllDay());
    r.setAllDay(true);
    QVERIFY(r.isAllDay());

    r.setDueDateTime(QDateTime(QDate(2010, 10, 14)));
    QVERIFY(r.dueDateTime() == QDateTime(QDate(2010, 10, 14)));

    // add
    QOrganizerTodoTime r2;
    r2.setStartDateTime(QDateTime(QDate(2010, 10, 23)));
    r2.setDueDateTime(QDateTime(QDate(2010, 10, 24)));
    QVERIFY(t.saveDetail(&r));
    QVERIFY(t.details<QOrganizerTodoTime>().size() == 1);
    QVERIFY(t.detail<QOrganizerTodoTime>() == r);
    QVERIFY(t.saveDetail(&r2)); // note that we don't enforce uniqueness in organizeritem; that's done by the manager!
    QVERIFY(t.details<QOrganizerTodoTime>().size() == 2);
    QVERIFY(t.removeDetail(&r2));
    QVERIFY(t.details<QOrganizerTodoTime>().size() == 1);
    QVERIFY(t.detail<QOrganizerTodoTime>() == r);

    // update
    r.setAllDay(false);
    QVERIFY(t.detail<QOrganizerTodoTime>() != r);
    QVERIFY(t.saveDetail(&r));
    QVERIFY(t.detail<QOrganizerTodoTime>() == r);
    QVERIFY(t.details<QOrganizerTodoTime>().size() == 1);

    // remove
    QVERIFY(t.removeDetail(&r));
    QVERIFY(t.details<QOrganizerTodoTime>().size() == 0);
}

void tst_QOrganizerItemDetails::reminder()
{
    QOrganizerItemReminder r;
    QOrganizerItem oi;

    QVERIFY(r.isEmpty());
    QVERIFY(r.reminderType() == QOrganizerItemReminder::NoReminder);

    QVERIFY(r.secondsBeforeStart() == 0);
    QVERIFY(r.repetitionCount() == 0);
    QVERIFY(r.repetitionDelay() == 0);

    r.setSecondsBeforeStart(45);
    QVERIFY(!r.isEmpty());
    r.removeValue(QOrganizerItemReminder::FieldSecondsBeforeStart);
    QVERIFY(r.isEmpty());

    r.setRepetition(3, 100);
    QVERIFY(r.repetitionCount() == 3);
    QVERIFY(r.repetitionDelay() == 100);
    QVERIFY(!r.isEmpty());

    r.setSecondsBeforeStart(30); // reminder, 30 seconds before the item is due to start.
    QVERIFY(r.secondsBeforeStart() == 30);

    // add
    QVERIFY(oi.details<QOrganizerItemReminder>().size() == 0);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemReminder>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemReminder>() == r);

    // update
    r.setSecondsBeforeStart(300);
    QVERIFY(oi.detail<QOrganizerItemReminder>() != r);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemReminder>().size() == 1); // should update, not add another
    QVERIFY(oi.detail<QOrganizerItemReminder>() == r);

    // remove
    QVERIFY(oi.removeDetail(&r));
    QVERIFY(oi.details<QOrganizerItemReminder>().size() == 0);
}

void tst_QOrganizerItemDetails::audibleReminder()
{
    QOrganizerItemAudibleReminder r;
    QOrganizerItem oi;

    QVERIFY(r.isEmpty());
    QVERIFY(r.reminderType() == QOrganizerItemReminder::AudibleReminder);

    QVERIFY(r.secondsBeforeStart() == 0);
    QVERIFY(r.repetitionCount() == 0);
    QVERIFY(r.repetitionDelay() == 0);

    r.setSecondsBeforeStart(45);
    QVERIFY(!r.isEmpty());
    r.removeValue(QOrganizerItemReminder::FieldSecondsBeforeStart);
    QVERIFY(r.isEmpty());

    QOrganizerItemReminder baseR;
    baseR = r;
    QVERIFY(baseR.isEmpty());
    baseR.setSecondsBeforeStart(50);
    QVERIFY(baseR.secondsBeforeStart() == 50);
    QVERIFY(r.secondsBeforeStart() == 0);
    QVERIFY(!baseR.isEmpty());
    QVERIFY(r.isEmpty());

    r.setRepetition(3, 100);
    QVERIFY(r.repetitionCount() == 3);
    QVERIFY(r.repetitionDelay() == 100);
    QVERIFY(!r.isEmpty());

    r.setSecondsBeforeStart(30); // reminder, 30 seconds before the item is due to start.
    QVERIFY(r.secondsBeforeStart() == 30);

    // add
    QVERIFY(oi.details<QOrganizerItemAudibleReminder>().size() == 0);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemAudibleReminder>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemAudibleReminder>() == r);

    // update
    r.setSecondsBeforeStart(300);
    r.setDataUrl(QUrl("http://www.test.com"));
    QVERIFY(r.dataUrl() == QUrl("http://www.test.com"));
    QVERIFY(oi.detail<QOrganizerItemAudibleReminder>() != r);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemAudibleReminder>().size() == 1); // should update, not add another
    QVERIFY(oi.detail<QOrganizerItemAudibleReminder>() == r);

    // remove
    QVERIFY(oi.removeDetail(&r));
    QVERIFY(oi.details<QOrganizerItemAudibleReminder>().size() == 0);
}

void tst_QOrganizerItemDetails::emailReminder()
{
    QOrganizerItemEmailReminder r;
    QOrganizerItem oi;

    QVERIFY(r.isEmpty());
    QVERIFY(r.reminderType() == QOrganizerItemReminder::EmailReminder);

    QVERIFY(r.secondsBeforeStart() == 0);
    QVERIFY(r.repetitionCount() == 0);
    QVERIFY(r.repetitionDelay() == 0);

    r.setRepetition(3, 100);
    QVERIFY(r.repetitionCount() == 3);
    QVERIFY(r.repetitionDelay() == 100);
    QVERIFY(!r.isEmpty());

    r.setSecondsBeforeStart(30); // reminder, 30 seconds before the item is due to start.
    QVERIFY(r.secondsBeforeStart() == 30);

    // add
    QVERIFY(oi.details<QOrganizerItemEmailReminder>().size() == 0);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemEmailReminder>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemEmailReminder>() == r);

    // update
    r.setSecondsBeforeStart(300);
    r.setContents("subject", "body", QVariantList());
    r.setRecipients(QStringList() << "recipient" << "other recipient");
    QVERIFY(r.subject() == QString("subject"));
    QVERIFY(r.body() == QString("body"));
    QVERIFY(r.attachments() == QVariantList());
    QVERIFY(r.recipients() == (QStringList() << "recipient" << "other recipient"));
    QVERIFY(oi.detail<QOrganizerItemEmailReminder>() != r);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemEmailReminder>().size() == 1); // should update, not add another
    QVERIFY(oi.detail<QOrganizerItemEmailReminder>() == r);

    // remove
    QVERIFY(oi.removeDetail(&r));
    QVERIFY(oi.details<QOrganizerItemEmailReminder>().size() == 0);
}

void tst_QOrganizerItemDetails::visualReminder()
{
    QOrganizerItemVisualReminder r;
    QOrganizerItem oi;

    QVERIFY(r.isEmpty());
    QVERIFY(r.reminderType() == QOrganizerItemReminder::VisualReminder);

    QVERIFY(r.secondsBeforeStart() == 0);
    QVERIFY(r.repetitionCount() == 0);
    QVERIFY(r.repetitionDelay() == 0);

    r.setRepetition(3, 100);
    QVERIFY(r.repetitionCount() == 3);
    QVERIFY(r.repetitionDelay() == 100);
    QVERIFY(!r.isEmpty());

    r.setSecondsBeforeStart(30); // reminder, 30 seconds before the item is due to start.
    QVERIFY(r.secondsBeforeStart() == 30);

    // add
    QVERIFY(oi.details<QOrganizerItemVisualReminder>().size() == 0);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemVisualReminder>().size() == 1);
    QVERIFY(oi.detail<QOrganizerItemVisualReminder>() == r);

    // update
    r.setSecondsBeforeStart(300);
    r.setMessage("test");
    r.setDataUrl(QUrl("http://www.test.com"));
    QVERIFY(r.message() == QString("test"));
    QVERIFY(r.dataUrl() == QUrl("http://www.test.com"));
    QVERIFY(oi.detail<QOrganizerItemVisualReminder>() != r);
    QVERIFY(oi.saveDetail(&r));
    QVERIFY(oi.details<QOrganizerItemVisualReminder>().size() == 1); // should update, not add another
    QVERIFY(oi.detail<QOrganizerItemVisualReminder>() == r);

    // remove
    QVERIFY(oi.removeDetail(&r));
    QVERIFY(oi.details<QOrganizerItemVisualReminder>().size() == 0);
}

void tst_QOrganizerItemDetails::attendee()
{
    QOrganizerEventAttendee a;
    QOrganizerItem oi;

    QVERIFY(a.isEmpty());
    QVERIFY(a.name().isEmpty());
    QVERIFY(a.emailAddress().isEmpty());
    QVERIFY(a.attendeeId().isEmpty());
    QVERIFY(a.participationRole() == 0);
    QVERIFY(a.participationStatus() == 0);

    a.setAttendeeId("123456");
    QVERIFY(a.attendeeId() == QString("123456"));
    a.setEmailAddress("people@nokia.com");
    QVERIFY(a.emailAddress() == QString("people@nokia.com"));
    a.setName("people");
    QVERIFY(a.name() == QString("people"));
    a.setParticipationRole(QOrganizerEventAttendee::RoleRequiredParticipant);
    QVERIFY(a.participationRole() == QOrganizerEventAttendee::RoleRequiredParticipant);
    a.setParticipationStatus(QOrganizerEventAttendee::StatusAccepted);
    QVERIFY(a.participationStatus() == QOrganizerEventAttendee::StatusAccepted);
    // add
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 0);
    QVERIFY(oi.saveDetail(&a));
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 1);
    QVERIFY(oi.detail<QOrganizerEventAttendee>() == a);
    // update
    a.setAttendeeId("54321");
    a.setName("newpeople");
    a.setEmailAddress("newpeople@nokia.com");
    QVERIFY(oi.detail<QOrganizerEventAttendee>() != a);
    QVERIFY(oi.saveDetail(&a));
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 1);
    QVERIFY(oi.detail<QOrganizerEventAttendee>() == a);

    // add one more attendee
    QOrganizerEventAttendee a1;
    a1.setAttendeeId("777777");
    a1.setName("people1");
    a1.setEmailAddress("people1@nokia.com");
    QVERIFY(oi.saveDetail(&a1));
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 2);

    // remove
    QVERIFY(oi.removeDetail(&a));
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 1);
    QVERIFY(oi.removeDetail(&a1));
    QVERIFY(oi.details<QOrganizerEventAttendee>().size() == 0);
}

void tst_QOrganizerItemDetails::rsvp()
{
    QOrganizerEventRsvp rsvp;
    QOrganizerItem oi;

    QVERIFY(rsvp.isEmpty());
    QVERIFY(rsvp.organizerName().isEmpty());
    QVERIFY(rsvp.organizerEmail().isEmpty());
    QVERIFY(rsvp.responseDate().isNull());
    QVERIFY(!rsvp.responseDate().isValid());
    QVERIFY(rsvp.responseDeadline().isNull());
    QVERIFY(!rsvp.responseDeadline().isValid());
    QVERIFY(rsvp.participationRole() == 0);
    QVERIFY(rsvp.participationStatus() == 0);
    QVERIFY(rsvp.responseRequirement() == 0);

    rsvp.setOrganizerName("Donald Duck");
    QVERIFY(rsvp.organizerName() == QString("Donald Duck"));
    rsvp.setOrganizerEmail("don@duck.com");
    QVERIFY(rsvp.organizerEmail() == QString("don@duck.com"));
    QDate testDate(2010, 10, 10);
    rsvp.setResponseDate(testDate);
    QVERIFY(!rsvp.responseDate().isNull());
    QVERIFY(rsvp.responseDate().isValid());
    QCOMPARE(testDate, rsvp.responseDate());
    rsvp.setResponseDeadline(testDate);
    QVERIFY(!rsvp.responseDeadline().isNull());
    QVERIFY(rsvp.responseDeadline().isValid());
    QCOMPARE(testDate, rsvp.responseDeadline());
    rsvp.setParticipationRole(QOrganizerEventAttendee::RoleOrganizer);
    QVERIFY(rsvp.participationRole() == QOrganizerEventAttendee::RoleOrganizer);
    rsvp.setParticipationStatus(QOrganizerEventAttendee::StatusAccepted);
    QVERIFY(rsvp.participationStatus() == QOrganizerEventAttendee::StatusAccepted);
    rsvp.setResponseRequirement(QOrganizerEventRsvp::ResponseRequired);
    QVERIFY(rsvp.responseRequirement() == QOrganizerEventRsvp::ResponseRequired);

    // add
    QCOMPARE(0, oi.details<QOrganizerEventRsvp>().size());
    QVERIFY(oi.saveDetail(&rsvp));
    QCOMPARE(1, oi.details<QOrganizerEventRsvp>().size());
    QCOMPARE(rsvp, oi.detail<QOrganizerEventRsvp>());

    // update
    rsvp.setOrganizerName("Mickey Mouse");
    rsvp.setOrganizerEmail("mick@mouse.com");
    QDate testDate2(2011, 11, 11);
    rsvp.setResponseDate(testDate2);
    rsvp.setResponseDeadline(testDate2);
    rsvp.setParticipationRole(QOrganizerEventAttendee::RoleChairperson);
    rsvp.setParticipationStatus(QOrganizerEventAttendee::StatusDelegated);
    rsvp.setResponseRequirement(QOrganizerEventRsvp::ResponseNotRequired);
    QVERIFY(oi.detail<QOrganizerEventRsvp>() != rsvp);
    QVERIFY(oi.saveDetail(&rsvp));
    QCOMPARE(1, oi.details<QOrganizerEventRsvp>().size());
    QVERIFY(oi.detail<QOrganizerEventRsvp>() == rsvp);

    // add another rsvp - not supported by all the backends
    QOrganizerEventRsvp rsvp2;
    rsvp2.setOrganizerName("Goofy");
    QVERIFY(oi.saveDetail(&rsvp2));
    QCOMPARE(2, oi.details<QOrganizerEventRsvp>().size());

    // remove
    QVERIFY(oi.removeDetail(&rsvp2));
    QCOMPARE(1, oi.details<QOrganizerEventRsvp>().size());
    QVERIFY(oi.removeDetail(&rsvp));
    QCOMPARE(0, oi.details<QOrganizerEventRsvp>().size());
}

void tst_QOrganizerItemDetails::classification()
{
    QOrganizerItemClassification classification;
    QOrganizerItem oi;

    QVERIFY(classification.classification().isEmpty());

    // setters/getters
    classification.setClassification(QOrganizerItemClassification::Public);
    QVERIFY(classification.classification() == QOrganizerItemClassification::Public);
    classification.setClassification(QOrganizerItemClassification::Private);
    QVERIFY(classification.classification() == QOrganizerItemClassification::Private);
    classification.setClassification(QOrganizerItemClassification::Confidential);
    QVERIFY(classification.classification() == QOrganizerItemClassification::Confidential);
    classification.setClassification("secret custom string");
    QVERIFY(classification.classification() == QString("secret custom string"));

    // add
    QCOMPARE(0, oi.details<QOrganizerItemClassification>().size());
    QVERIFY(oi.saveDetail(&classification));
    QCOMPARE(1, oi.details<QOrganizerItemClassification>().size());
    QCOMPARE(classification, oi.detail<QOrganizerItemClassification>());

    // update
    classification.setValue(QOrganizerItemClassification::FieldClassification, "very secret custom string");
    QVERIFY(oi.detail<QOrganizerItemClassification>() != classification);
    QVERIFY(oi.saveDetail(&classification));
    QCOMPARE(1, oi.details<QOrganizerItemClassification>().size());
    QVERIFY(oi.detail<QOrganizerItemClassification>() == classification);

    // try adding another, amount of details should stay the same
    QOrganizerItemClassification classification2;
    classification2.setClassification("2nd classification");
    QVERIFY(oi.saveDetail(&classification2));
    QCOMPARE(oi.details<QOrganizerItemClassification>().size(), 1);

    // remove
    QVERIFY(oi.removeDetail(&classification2));
    QCOMPARE(oi.details<QOrganizerItemClassification>().size(), 0);
}

void tst_QOrganizerItemDetails::version()
{
    QOrganizerItemVersion version;
    QCOMPARE(version.type(), QOrganizerItemDetail::TypeVersion);
    QVERIFY(!version.hasValue(QOrganizerItemVersion::FieldVersion));
    QVERIFY(!version.hasValue(QOrganizerItemVersion::FieldExtendedVersion));

    version.setVersion(64);
    QCOMPARE(version.version(), 64);
    QVERIFY(version.hasValue(QOrganizerItemVersion::FieldVersion));
    QVERIFY(!version.hasValue(QOrganizerItemVersion::FieldExtendedVersion));

    QByteArray extendedVersion("Qt rules!");
    version.setExtendedVersion(extendedVersion);
    QCOMPARE(version.extendedVersion(), extendedVersion);
    QVERIFY(version.hasValue(QOrganizerItemVersion::FieldVersion));
    QVERIFY(version.hasValue(QOrganizerItemVersion::FieldExtendedVersion));
}

QTEST_MAIN(tst_QOrganizerItemDetails)
#include "tst_qorganizeritemdetails.moc"