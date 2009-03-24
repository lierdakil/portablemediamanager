#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtGui>

namespace Ui {
    class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SettingsDialog)
public:
    explicit SettingsDialog(QWidget *parent = 0);
    virtual ~SettingsDialog();
    QStringList extensions();
    QStringList actions();
    QStringList fstypes();
    QStringList moptions();
    void setActions(QStringList extensions,QStringList actions);
    void setMOptions(QStringList fstypes,QStringList options);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::SettingsDialog *m_ui;

private slots:
    void on_btRemove_2_clicked();
    void on_btInsert_2_clicked();
    void on_btRemove_clicked();
    void on_btInsert_clicked();
};

#endif // SETTINGSDIALOG_H
