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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtDBus>

#include "ccopythread.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    QFileSystemModel *fsmLocalMusicDir;
    QFileSystemModel *fsmRemoteMusicDir;
    QStringList extensions;
    QStringList actions;
    QStringList fstypes;
    QStringList moptions;
    QString volume;
    CCopyThread* th;
    QProgressDialog *pr;
    bool mounted;
    void setMounted(bool state);

private slots:
    void on_btDownload_clicked();
    void on_btRemoteDel_clicked();
    void on_btUnmount_clicked();
    void on_btSettings_clicked();
    void on_leLocalMusicDir_textChanged(QString);
    void on_leRemoteMusicDir_textChanged(QString);
    void on_btMount_clicked();
    void on_btUpload_clicked();

public slots:
    void th_finished();
};

#endif // MAINWINDOW_H
