/*
 *  portablemediamanager Simple and minimalistic portable audio/video player manager for Linux
 *  Copyright (C) 2009  Nikolay "Livid" Yakimov
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/********************************************************************************
** Form generated from reading ui file 'copydialog.ui'
**
** Created: Mon Mar 23 19:21:47 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_COPYDIALOG_H
#define UI_COPYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CopyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lbDirLabel;
    QLabel *lbDirName;
    QProgressBar *pbDir;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbFileLabel;
    QLabel *lbFileName;
    QProgressBar *pbFile;

    void setupUi(QDialog *CopyDialog)
    {
        if (CopyDialog->objectName().isEmpty())
            CopyDialog->setObjectName(QString::fromUtf8("CopyDialog"));
        CopyDialog->resize(400, 112);
        verticalLayout = new QVBoxLayout(CopyDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lbDirLabel = new QLabel(CopyDialog);
        lbDirLabel->setObjectName(QString::fromUtf8("lbDirLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lbDirLabel->sizePolicy().hasHeightForWidth());
        lbDirLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lbDirLabel);

        lbDirName = new QLabel(CopyDialog);
        lbDirName->setObjectName(QString::fromUtf8("lbDirName"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbDirName->sizePolicy().hasHeightForWidth());
        lbDirName->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(lbDirName);


        verticalLayout->addLayout(horizontalLayout);

        pbDir = new QProgressBar(CopyDialog);
        pbDir->setObjectName(QString::fromUtf8("pbDir"));
        pbDir->setValue(24);

        verticalLayout->addWidget(pbDir);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lbFileLabel = new QLabel(CopyDialog);
        lbFileLabel->setObjectName(QString::fromUtf8("lbFileLabel"));
        sizePolicy.setHeightForWidth(lbFileLabel->sizePolicy().hasHeightForWidth());
        lbFileLabel->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lbFileLabel);

        lbFileName = new QLabel(CopyDialog);
        lbFileName->setObjectName(QString::fromUtf8("lbFileName"));
        sizePolicy1.setHeightForWidth(lbFileName->sizePolicy().hasHeightForWidth());
        lbFileName->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(lbFileName);


        verticalLayout->addLayout(horizontalLayout_2);

        pbFile = new QProgressBar(CopyDialog);
        pbFile->setObjectName(QString::fromUtf8("pbFile"));
        pbFile->setValue(24);

        verticalLayout->addWidget(pbFile);


        retranslateUi(CopyDialog);

        QMetaObject::connectSlotsByName(CopyDialog);
    } // setupUi

    void retranslateUi(QDialog *CopyDialog)
    {
        CopyDialog->setWindowTitle(QApplication::translate("CopyDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        lbDirLabel->setText(QApplication::translate("CopyDialog", "Copying directory", 0, QApplication::UnicodeUTF8));
        lbDirName->setText(QApplication::translate("CopyDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        lbFileLabel->setText(QApplication::translate("CopyDialog", "Copying file", 0, QApplication::UnicodeUTF8));
        lbFileName->setText(QApplication::translate("CopyDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CopyDialog);
    } // retranslateUi

};

namespace Ui {
    class CopyDialog: public Ui_CopyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COPYDIALOG_H
