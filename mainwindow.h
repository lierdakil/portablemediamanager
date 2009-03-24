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
