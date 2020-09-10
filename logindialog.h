#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QWidget>

/* 类前置声明 */
class QLabel;
class QLineEdit;
class QPushButton;

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~ LoginDialog();

public slots:
    void is_login_pushbutton_clicked();
    void is_exit_pushbutton_clicked();

private:
    QLabel *user_label;
    QLabel *passwd_label;
    QLineEdit *user_lineedit;
    QLineEdit *passwd_lineedit;
    QPushButton *login_pushbutton;
    QPushButton *exit_pushbutton;
};

#endif // LOGINDIALOG_H
