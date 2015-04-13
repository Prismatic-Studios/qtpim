/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd and/or its subsidiary(-ies).
** Contact: http://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
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

#ifndef tst_QVCARD21WRITER_H
#define tst_QVCARD21WRITER_H

#include <QObject>
#include <QtVersit/qversitglobal.h>

QT_BEGIN_NAMESPACE_VERSIT
class QVCard21Writer;
QT_END_NAMESPACE_VERSIT

QTVERSIT_USE_NAMESPACE

class tst_QVCard21Writer : public QObject
{
     Q_OBJECT

private slots: // Tests
#ifdef QT_BUILD_INTERNAL
    void init();
    void cleanup();
    void testEncodeVersitProperty();
    void testEncodeVersitProperty_data();
    void testEncodeParameters();
    void testEncodeParameters_data();
    void testEncodeGroupsAndName();
    void testQuotedPrintableEncode();
#endif

private: // Data
    QVCard21Writer* mWriter;
};

#endif // tst_QVCARD21WRITER_H
