#include "logindialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QtDebug>

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent)
{
	// 实例化
	user_label = new QLabel(this);
	passwd_label = new QLabel(this);
	user_lineedit = new QLineEdit(this);
	passwd_lineedit = new QLineEdit(this);

	login_pushbutton = new QPushButton(this);
	exit_pushbutton = new QPushButton(this);

	// 设置
	user_label->move(80, 70);
	user_label->setText(tr("用户名："));

	passwd_label->move(80, 140);
	passwd_label->setText(tr("密码："));

	user_lineedit->move(130, 70);
	user_lineedit->setPlaceholderText(tr("请输入用户名"));

	passwd_lineedit->move(130, 140);
	passwd_lineedit->setPlaceholderText(tr("请输入密码"));
	passwd_lineedit->setEchoMode(QLineEdit::Password);

	login_pushbutton->move(50, 200);
	login_pushbutton->setText(tr("登录"));

	exit_pushbutton->move(210, 200);
	exit_pushbutton->setText(tr("退出"));

	// dialog setting
	this->setWindowTitle(tr("Login"));
	this->setFixedSize(320, 240);

	// 设置槽函数
	connect(login_pushbutton, &QPushButton::clicked, this, &LoginDialog::is_login_pushbutton_clicked);
	connect(exit_pushbutton, &QPushButton::clicked, this, &LoginDialog::is_exit_pushbutton_clicked);
}

void LoginDialog::is_login_pushbutton_clicked()
{
	if (user_lineedit->text().trimmed() == tr("fishercloud") && passwd_lineedit->text().trimmed() == tr("woshiyuxin"))
	{
		accept();
	}
	else
	{
		QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误"), QMessageBox::Yes);

		user_lineedit->clear(); // 清除文字
		passwd_lineedit->clear();
		user_lineedit->setFocus(); // 光标
	}
}

void LoginDialog::is_exit_pushbutton_clicked()
{
	reject(); // 关闭当前dialog
}

LoginDialog::~LoginDialog()
{
	delete user_label;
	delete user_lineedit;
	delete passwd_label;
	delete passwd_lineedit;
	delete login_pushbutton;
	delete exit_pushbutton;
	qDebug() << "quit logindialog class";
}
