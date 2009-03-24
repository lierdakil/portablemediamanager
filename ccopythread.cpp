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
