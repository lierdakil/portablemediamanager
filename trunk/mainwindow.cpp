#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    fsmLocalMusicDir = new QFileSystemModel;
    ui->tvLocalMusicDir->setModel(fsmLocalMusicDir);

    ui->btUnmount->setVisible(false);

    for(int i=1;i<=4;i++)
        ui->tvLocalMusicDir->setColumnHidden(i,true);
    ui->tvLocalMusicDir->sortByColumn(0,Qt::AscendingOrder);

    QSettings s("livid.pp.ru","MediaMan");
    ui->leLocalMusicDir->setText(s.value("LocalMusicDir",QDir::homePath()).toString());
    extensions=s.value("Extensions",QStringList()).toStringList();
    actions=s.value("Actions",QStringList()).toStringList();
    fstypes=s.value("FSTypes",QStringList()).toStringList();
    moptions=s.value("MOptions",QStringList()).toStringList();
}

MainWindow::~MainWindow()
{
    QSettings s("livid.pp.ru","MediaMan");
    s.setValue("LocalMusicDir",ui->leLocalMusicDir->text());
    s.setValue("Extensions",extensions);
    s.setValue("Actions",actions);
    s.setValue("FSTypes",fstypes);
    s.setValue("MOptions",moptions);

    delete fsmLocalMusicDir;
    delete fsmRemoteMusicDir;
    delete ui;
}

void MainWindow::on_leLocalMusicDir_textChanged(QString newDir)
{
    ui->tvLocalMusicDir->setRootIndex(fsmLocalMusicDir->setRootPath(newDir));
}

void MainWindow::on_leRemoteMusicDir_textChanged(QString newDir)
{
    ui->tvRemoteMusicDir->setRootIndex(fsmRemoteMusicDir->setRootPath(newDir));
}

void MainWindow::setMounted(bool state)
{
    ui->btUnmount->setVisible(state);
    ui->btMount->setVisible(!state);
    ui->btDownload->setEnabled(state);
    ui->btUpload->setEnabled(state);
    ui->btRemoteDel->setEnabled(state);
    mounted=state;
}

void MainWindow::on_btMount_clicked()
{
    QDBusConnection c = QDBusConnection::systemBus();
    QDBusInterface iManager("org.freedesktop.Hal","/org/freedesktop/Hal/Manager","org.freedesktop.Hal.Manager",c,this);
    QDBusReply<QStringList> devices=iManager.call("FindDeviceByCapability","portable_audio_player");
    if(devices.isValid())
    {
        QString device;

        if(devices.value().count()>1)
            device=QInputDialog::getItem(this,trUtf8("Select your player device"), trUtf8("Available devices:"), devices.value(), 0, false);
        else if(devices.value().count()==1)
            device=devices.value().at(0);
        else
            return;

        QDBusReply<QStringList> volumes = iManager.call("FindDeviceStringMatch","info.parent",device);
        if(volumes.isValid())
        {
            if(volumes.value().count()>1)
                volume=QInputDialog::getItem(this,trUtf8("Select volume to mount"), trUtf8("Available volumes:"), volumes.value(), 0, false);
            else if(volumes.value().count()==1)
                volume=volumes.value().at(0);
            else
                return;

            QDBusInterface iVolumeDevice("org.freedesktop.Hal",volume,"org.freedesktop.Hal.Device",c,this);
            QDBusReply<bool> is_mounted = iVolumeDevice.call("GetPropertyBoolean","volume.is_mounted");
            if(is_mounted.isValid())
            {
                QDBusInterface iVolume("org.freedesktop.Hal",volume,"org.freedesktop.Hal.Device.Volume",c,this);
                if(iVolume.isValid())
                {
                    //QStringList extra_options=QString("uid=%1,iocharset=utf8").arg(uid).split(",");
                    QDBusReply<int> r;
                    if(!is_mounted.value())
                    {
                        QDBusReply<QString> fstype = iVolumeDevice.call("GetPropertyBoolean","volume.fstype");
                        if(fstype.isValid())
                        {
                            QStringList extra_options;
                            if(fstypes.indexOf(fstype.value())>=0)
                                extra_options=moptions.at(fstypes.indexOf(fstype.value())).split(",");
                            else
                                extra_options=QStringList();
                            extra_options.append(QString("uid=%1").arg(getuid()));
                            r = iVolume.call("Mount","player",fstype.value(), extra_options);
                        }
                    }

                    if(is_mounted.value() || (r.isValid() && r.value()==0))
                    {
                        QDBusReply<QString> mp=iVolumeDevice.call("GetPropertyString","volume.mount_point");
                        if(mp.isValid())
                        {
                            fsmRemoteMusicDir = new QFileSystemModel;
                            ui->tvRemoteMusicDir->setModel(fsmRemoteMusicDir);
                            for(int i=1;i<=4;i++)
                                ui->tvRemoteMusicDir->setColumnHidden(i,true);
                            ui->leRemoteMusicDir->setText(mp.value());
                            setMounted(true);
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::on_btUnmount_clicked()
{
    QDBusReply<int> r;
    QDBusConnection c = QDBusConnection::systemBus();
    QDBusInterface iVolume("org.freedesktop.Hal",volume,"org.freedesktop.Hal.Device.Volume",c,this);
    QDBusInterface iVolumeDevice("org.freedesktop.Hal",volume,"org.freedesktop.Hal.Device",c,this);
    do{
        r=iVolume.call("Unmount",QStringList());
        QDBusReply<bool> is_mounted = iVolumeDevice.call("GetPropertyBoolean","volume.is_mounted");
        if((r.isValid() && r.value()==0) || (is_mounted.isValid() && !is_mounted.value()))
        {
            ui->leRemoteMusicDir->setText("");
            ui->tvRemoteMusicDir->setModel(0);
            delete fsmRemoteMusicDir;
            setMounted(false);
        }
    } while(mounted &&
            QMessageBox::warning(this,tr("There was an error"),
                                 tr("Unable to unmount volume"),
                                 QMessageBox::Ok | QMessageBox::Retry)==QMessageBox::Retry);
}

void MainWindow::on_btUpload_clicked()
{
    if(ui->tvLocalMusicDir->currentIndex().isValid() && ui->tvRemoteMusicDir->currentIndex().isValid())
    {
        QModelIndex root=ui->tvLocalMusicDir->currentIndex();
        QModelIndex remoteroot=ui->tvRemoteMusicDir->currentIndex();

        if(! fsmRemoteMusicDir->isDir(remoteroot))
            remoteroot=remoteroot.parent();

        th=new CCopyThread();
        th->local=ui->leLocalMusicDir->text();
        th->from=fsmLocalMusicDir->filePath(root);
        th->to=fsmRemoteMusicDir->filePath(remoteroot);
        th->isDir=fsmLocalMusicDir->isDir(root);
        th->extensions=extensions;
        th->actions=actions;

        pr=new QProgressDialog(tr("Copying from %1 to %2").arg(th->from,th->to),QString(),0,th->maximum(),this);
        pr->setModal(true);
        connect(th,SIGNAL(prog(int)),pr,SLOT(setValue(int)));
        connect(th,SIGNAL(finished()),SLOT(th_finished()));
        ui->btUpload->setEnabled(false);
        th->start();
    } else {
        QMessageBox::information(this,
                                 tr("Source or destination not selected"),
                                 tr("Please, select directory to upload "
                                    "on left panel and directory to upload "
                                    "to (or any file in that directory) on right panel"));
    }
}

void MainWindow::th_finished()
{
    delete th;
    delete pr;
    ui->btUpload->setEnabled(true);
}

void MainWindow::on_btSettings_clicked()
{
    SettingsDialog sd;
    sd.setActions(extensions,actions);
    sd.setMOptions(fstypes,moptions);

    if(sd.exec()==SettingsDialog::Accepted)
    {
        extensions=sd.extensions();
        actions=sd.actions();
        fstypes=sd.fstypes();
        moptions=sd.moptions();
    }
}

void MainWindow::on_btRemoteDel_clicked()
{
    if(     ui->tvRemoteMusicDir->currentIndex().isValid() &&
            QMessageBox::question(this,
                                  tr("Remove file"),
                                  tr("Are you sure? Selected files will be removed permanently!\n"
                                     "Shall I remove all files in %1?").arg(fsmRemoteMusicDir->filePath(ui->tvRemoteMusicDir->currentIndex())),
                                  QMessageBox::Yes, QMessageBox::No)==QMessageBox::Yes)
        fsmRemoteMusicDir->remove(ui->tvRemoteMusicDir->currentIndex());
}

void MainWindow::on_btDownload_clicked()
{
    if(ui->tvLocalMusicDir->currentIndex().isValid() && ui->tvRemoteMusicDir->currentIndex().isValid())
    {
        QModelIndex localroot=ui->tvLocalMusicDir->currentIndex();
        QModelIndex remoteroot=ui->tvRemoteMusicDir->currentIndex();

        if(! fsmLocalMusicDir->isDir(localroot))
            localroot=localroot.parent();

        th=new CCopyThread();
        th->local=ui->leRemoteMusicDir->text();
        th->from=fsmRemoteMusicDir->filePath(remoteroot);
        th->to=fsmLocalMusicDir->filePath(localroot);
        th->isDir=fsmRemoteMusicDir->isDir(remoteroot);
        th->extensions=QStringList();
        th->actions=QStringList();

        pr=new QProgressDialog(tr("Copying from %1 to %2").arg(th->from,th->to),QString(),0,th->maximum(),this);
        pr->setModal(true);
        connect(th,SIGNAL(prog(int)),pr,SLOT(setValue(int)));
        connect(th,SIGNAL(finished()),SLOT(th_finished()));
        ui->btUpload->setEnabled(false);
        th->start();
    } else {
        QMessageBox::information(this,tr("Source or destination not selected"),tr("Please, select directory to download on riht panel and directory to download to (or any file in that directory) on left panel"));
    }
}
