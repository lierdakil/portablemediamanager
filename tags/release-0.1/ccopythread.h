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

#ifndef CCOPYTHREAD_H
#define CCOPYTHREAD_H

#include <QtCore>

class CCopyThread : public QThread
{
    Q_OBJECT

public:
    QString local;
    QString from;
    QString to;
    bool isDir;
    QStringList extensions;
    QStringList actions;

private:
    int progress_count;

    void UploadDir(QString path);
    void UploadFile(QString path);
    int CountFiles(QString path);

    void run();

public:
    int maximum();

signals:
    void prog(int count);
};

#endif // CCOPYTHREAD_H
