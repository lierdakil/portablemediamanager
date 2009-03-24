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
