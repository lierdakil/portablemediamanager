#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class LicenseDialog;
}

class LicenseDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(LicenseDialog)
public:
    explicit LicenseDialog(QWidget *parent = 0);
    virtual ~LicenseDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::LicenseDialog *m_ui;
};

#endif // LICENSEDIALOG_H
