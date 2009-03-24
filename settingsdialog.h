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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SettingsDialog)
public:
    explicit SettingsDialog(QWidget *parent = 0);
    virtual ~SettingsDialog();
    QStringList extensions();
    QStringList actions();
    QStringList fstypes();
    QStringList moptions();
    void setActions(QStringList extensions,QStringList actions);
    void setMOptions(QStringList fstypes,QStringList options);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *m_ui;

private slots:
    void on_btRemove_2_clicked();
    void on_btInsert_2_clicked();
    void on_btRemove_clicked();
    void on_btInsert_clicked();
};

#endif // SETTINGSDIALOG_H
