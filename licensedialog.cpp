#include "licensedialog.h"
#include "ui_licensedialog.h"
#include <QFile>

LicenseDialog::LicenseDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::LicenseDialog)
{
    m_ui->setupUi(this);
    QFile f(":/text/agpl.txt");
    f.open(QIODevice::ReadOnly);
    m_ui->plainTextEdit->setPlainText(f.readAll());
    f.close();
}

LicenseDialog::~LicenseDialog()
{
    delete m_ui;
}

void LicenseDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
