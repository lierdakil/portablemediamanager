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

#include "ccopythread.h"
#include <stdlib.h>

void CCopyThread::run()
{
    progress_count=0;
    if(isDir)
        UploadDir(from);
    else
        UploadFile(from);
}

void CCopyThread::UploadDir(QString path)
{
    QDir dir(path);

    foreach(QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name))
        UploadDir(path+"/"+subdir);

    foreach(QString file, dir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name))
        UploadFile(path+"/"+file);
}

void CCopyThread::UploadFile(QString path)
{
    QDir d;
    QString dest=path;
    dest.replace(local,to);

    d.mkpath(dest.left(dest.lastIndexOf("/")));

    int i = extensions.indexOf(path.right(path.length()-path.lastIndexOf('.')-1));
    if(i!=-1)
    {
        system(actions.at(i).arg(path,dest).toLocal8Bit().data());
    }
    else
    {
        QFile::copy(path,dest);
    }

    progress_count+=1;
    emit prog(progress_count);
}

int CCopyThread::CountFiles(QString path)
{
    QDir d(path);
    int count=d.entryList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name).count();

    foreach(QString subdir, d.entryList(QDir::NoDotAndDotDot | QDir::Dirs, QDir::Name))
        count+=CountFiles(path+"/"+subdir);

    return count;
}

int CCopyThread::maximum()
{
    if(isDir)
    {
        return CountFiles(from);
    }
    else
        return 1;
}
