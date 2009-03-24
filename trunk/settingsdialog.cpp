#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::SettingsDialog)
{
    m_ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}

void SettingsDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SettingsDialog::on_btInsert_clicked()
{
    m_ui->twCopyCommands->insertRow(m_ui->twCopyCommands->rowCount());

}

void SettingsDialog::on_btRemove_clicked()
{
    m_ui->twCopyCommands->removeRow(m_ui->twCopyCommands->currentRow());
}

QStringList SettingsDialog::extensions()
{
    QStringList result;
    for(int i=0; i<m_ui->twCopyCommands->rowCount();++i)
        if(m_ui->twCopyCommands->item(i,0)!=NULL && m_ui->twCopyCommands->item(i,1)!=NULL)
            if(!m_ui->twCopyCommands->item(i,0)->text().isEmpty() && !m_ui->twCopyCommands->item(i,1)->text().isEmpty())
                result.append(m_ui->twCopyCommands->item(i,0)->text());
    return result;
}

QStringList SettingsDialog::actions()
{
    QStringList result;
    for(int i=0; i<m_ui->twCopyCommands->rowCount();++i)
        if(m_ui->twCopyCommands->item(i,0)!=NULL && m_ui->twCopyCommands->item(i,1)!=NULL)
            if(!m_ui->twCopyCommands->item(i,0)->text().isEmpty() && !m_ui->twCopyCommands->item(i,1)->text().isEmpty())
            result.append(m_ui->twCopyCommands->item(i,1)->text());
    return result;
}

void SettingsDialog::setActions(QStringList extensions, QStringList actions)
{
    int count = extensions.count();

    if(count!=actions.count())
        throw tr("Actions and Excensions count mismatch");

    m_ui->twCopyCommands->setRowCount(count);

    for(int i=0;i<count;++i)
    {
        QTableWidgetItem *ext=new QTableWidgetItem(extensions.at(i));
        QTableWidgetItem *act=new QTableWidgetItem(actions.at(i));
        m_ui->twCopyCommands->setItem(i,0,ext);
        m_ui->twCopyCommands->setItem(i,1,act);
    }
}

QStringList SettingsDialog::fstypes()
{
    QStringList result;
    for(int i=0; i<m_ui->twMountOptions->rowCount();++i)
        if(m_ui->twMountOptions->item(i,0)!=NULL && m_ui->twMountOptions->item(i,1)!=NULL)
            if(!m_ui->twMountOptions->item(i,0)->text().isEmpty() && !m_ui->twMountOptions->item(i,1)->text().isEmpty())
                result.append(m_ui->twMountOptions->item(i,0)->text());
    return result;
}

QStringList SettingsDialog::moptions()
{
    QStringList result;
    for(int i=0; i<m_ui->twMountOptions->rowCount();++i)
        if(m_ui->twMountOptions->item(i,0)!=NULL && m_ui->twMountOptions->item(i,1)!=NULL)
            if(!m_ui->twMountOptions->item(i,0)->text().isEmpty() && !m_ui->twMountOptions->item(i,1)->text().isEmpty())
            result.append(m_ui->twMountOptions->item(i,1)->text());
    return result;
}

void SettingsDialog::setMOptions(QStringList fstypes,QStringList options)
{
    int count = fstypes.count();

    if(count!=options.count())
        throw tr("Actions and Excensions count mismatch");

    m_ui->twMountOptions->setRowCount(count);

    for(int i=0;i<count;++i)
    {
        QTableWidgetItem *fst=new QTableWidgetItem(fstypes.at(i));
        QTableWidgetItem *opt=new QTableWidgetItem(options.at(i));
        m_ui->twMountOptions->setItem(i,0,fst);
        m_ui->twMountOptions->setItem(i,1,opt);
    }
}

void SettingsDialog::on_btInsert_2_clicked()
{
    m_ui->twMountOptions->insertRow(m_ui->twMountOptions->rowCount());
}

void SettingsDialog::on_btRemove_2_clicked()
{
    m_ui->twMountOptions->removeRow(m_ui->twMountOptions->currentRow());
}
