#include "mainwindow.h"

#include "logindialog.h"

#include <QApplication>

#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/notes.png"));
    MainWindow w;
    LoginDialog login_dialog;

    qDebug() << "Launch";

    if (login_dialog.exec() == QDialog::Accepted) {
        w.show();
        return a.exec();
    } else
        exit(EXIT_FAILURE);
}
