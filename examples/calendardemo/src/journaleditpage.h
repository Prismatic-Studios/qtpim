/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the examples of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef JOURNALEDITPAGE_H_
#define JOURNALEDITPAGE_H_

#include <QWidget>
#include <QDate>
#include <qorganizeritemid.h>
#include <qorganizerjournal.h>

QTORGANIZER_BEGIN_NAMESPACE
class QOrganizerManager;
class QOrganizerEvent;
class QOrganizerItem;
QTORGANIZER_END_NAMESPACE

QTORGANIZER_USE_NAMESPACE

QT_BEGIN_NAMESPACE
class QComboBox;
class QLineEdit;
class QDateTimeEdit;
QT_END_NAMESPACE

class JournalEditPage : public QWidget
{
    Q_OBJECT

public:
    JournalEditPage(QWidget *parent = 0);
    ~JournalEditPage();

public Q_SLOTS:
    void cancelClicked();
    void saveClicked();
    void journalChanged(QOrganizerManager *manager, const QOrganizerJournal &journal);
    void handleAlarmIndexChanged(const QString);

Q_SIGNALS:
    void showDayPage();

protected: // from QWidget
    void showEvent(QShowEvent *event);

private:
    QOrganizerManager *m_manager;
    QOrganizerJournal m_organizerJournal;
    QLineEdit *m_subjectEdit;
    QDateTimeEdit *m_timeEdit;
    QComboBox *m_alarmComboBox;
    QComboBox *m_calendarComboBox;
    QList<QOrganizerCollection> m_collections;
};

#endif // JOURNALEDITPAGE_H_
