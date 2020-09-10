#include "mainwindow.h"

#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QIcon>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>
#include <QFileDialog>
#include <QDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Notes");
    //    this->setFixedSize(640, 360); // 设置大小，且不可改变
    this->setGeometry(0, 0, 960, 640); // 设置窗口默认大小

    QDesktopWidget *desktop = QApplication::desktop();
    this->move((desktop->width() - this->width()) / 2, (desktop->height() - this->height()) / 2); // 居中显示

    //===============================file
    is_untitled = false;    // 默认未保存
    current_opened_filename = tr("未命名.txt");
    setWindowTitle(current_opened_filename);
    //=================================

    /*************************************/
    main_menubar = new QMenuBar(this);
    this->setMenuBar(main_menubar); // 添加菜单条

    // main menubar add menu
    file_menu = new QMenu(this);
    file_menu->setTitle(tr("文件(&F)"));
    this->main_menubar->addMenu(file_menu); // 添加菜单

    edit_menu = new QMenu(this);
    edit_menu->setTitle(tr("编辑(&E)"));
    this->main_menubar->addMenu(edit_menu);

    help_menu = new QMenu(this);
    help_menu->setTitle(tr("帮助(&H)"));
    this->main_menubar->addMenu(help_menu);

    // file menu add action
    filenew_action = new QAction(this);
    filenew_action->setText(tr("新建(&New)"));
    filenew_action->setIcon(QIcon(":/images/filenew.png")); // 设置图标
    filenew_action->setShortcut(QKeySequence(tr("Ctrl+N"))); // 设置快捷键
    this->file_menu->addAction(filenew_action); // 添加（子菜单）动作

    fileopen_action = new QAction(QIcon(":/images/fileopen.png"), tr("打开(&Q)"), this);
    fileopen_action->setShortcut(QKeySequence(tr("Ctrl+O")));
    file_menu->addAction(fileopen_action);

    fileclose_action = new QAction(QIcon(":/images/fileclose.png"), tr("关闭(&C)"), this);
    fileclose_action->setShortcut(QKeySequence(tr("Ctrl+W")));
    file_menu->addAction(fileclose_action);

    file_menu->addSeparator(); // 增加分隔符

    filesave_action = new QAction(QIcon(":/images/filesave.png"), tr("保存(&S)"), this);
    filesave_action->setShortcut(QKeySequence(tr("Ctrl+S")));
    file_menu->addAction(filesave_action);

    filesaveas_action = new QAction(QIcon(":/images/filesaveas.png"), tr("另存为(&A)"), this);
    filesaveas_action->setShortcut(QKeySequence(tr("Ctrl+Shift+S")));
    file_menu->addAction(filesaveas_action);

    file_menu->addSeparator(); // 增加分隔符

    quit_action = new QAction(this);
    quit_action->setText(tr("退出(&Q)"));
    quit_action->setIcon(QIcon(":images/quit.png"));
    quit_action->setShortcut(QKeySequence(tr("Ctrl+Q")));
    this->file_menu->addAction(quit_action);

    // edit menu add action
    revoke_action = new QAction(QIcon(":/images/revoke.png"), tr("撤销(&Z)"), this);
    revoke_action->setShortcut(QKeySequence(tr("Ctrl+Z")));
    edit_menu->addAction(revoke_action);

    edit_menu->addSeparator(); // 分隔符

    cut_action = new QAction(QIcon(":/images/cut.png"), tr("剪切(&X)"), this);
    cut_action->setShortcut(QKeySequence(tr("Ctrl+X")));
    edit_menu->addAction(cut_action);

    copy_action = new QAction(QIcon(":/images/copy.png"), tr("复制(&C)"), this);
    copy_action->setShortcut(QKeySequence(tr("Ctrl+C")));
    edit_menu->addAction(copy_action);

    paste_action = new QAction(QIcon(":/images/paste.png"), tr("粘贴(&V)"), this);
    paste_action->setShortcut(QKeySequence(tr("Ctrl+V")));
    edit_menu->addAction(paste_action);

    edit_menu->addSeparator(); // 分隔符

    find_action = new QAction(this);
    find_action->setText(tr("查找(&F)"));
    find_action->setIcon(QIcon(":/images/find.png"));
    find_action->setShortcut(QKeySequence(tr("Ctrl+F")));
    this->edit_menu->addAction(find_action);

    // help menu add action
    imprint_action = new QAction(this);
    imprint_action->setText(tr("版本说明"));
    imprint_action->setIcon(QIcon(":/images/help.png"));
    imprint_action->setShortcut(QKeySequence(tr("Ctrl+I")));
    this->help_menu->addAction(imprint_action);

    // 添加工具栏
    main_toolbar = new QToolBar(tr("main_toolbar"), this);
    main_toolbar->setMovable(false); // 不可移动
    this->addToolBar(main_toolbar);

    // toolbar add actions
    main_toolbar->addAction(filenew_action);
    main_toolbar->addAction(fileopen_action);
    main_toolbar->addAction(filesave_action);
    main_toolbar->addSeparator(); // 分隔符
    main_toolbar->addAction(revoke_action);
    main_toolbar->addAction(cut_action);
    main_toolbar->addAction(copy_action);
    main_toolbar->addAction(paste_action);
    main_toolbar->addSeparator(); // 分隔符
    main_toolbar->addAction(find_action);

    //======================================================
    // main_gridlayout
    main_gridlayout = new QGridLayout(this);
    find_pushbutton = new QPushButton(tr("搜索"), this);
    find_pushbutton->setFixedSize(QSize(80, 32));
    main_gridlayout->addWidget(find_pushbutton, 0, 0, 1, 1);
    find_lineedit = new QLineEdit(this);
    find_lineedit->setFixedHeight(30);
    main_gridlayout->addWidget(find_lineedit, 0, 1, 1, 2);
    main_textedit = new QTextEdit(this);
    main_gridlayout->addWidget(main_textedit, 1, 0, 1, 3);
    main_wideght = new QWidget;
    main_wideght->setLayout(main_gridlayout); // layout必须通过wideght加入到mainwindow
    setCentralWidget(main_wideght);

    //====================================================

    find_count = 0;

    //=========================
    search_dialog = new QDialog(this);
    search_dialog->setWindowTitle("查找");
    search_lineedit = new QLineEdit(search_dialog);
    search_button = new QPushButton(tr("查找下一个"), search_dialog);

    box_layout = new QVBoxLayout(search_dialog);
    box_layout->addWidget(search_lineedit);
    box_layout->addWidget(search_button);
    /*************************************/

    // 信号槽绑定
    connect(filenew_action, &QAction::triggered, this, &MainWindow::is_filenew_action_triggered);
    connect(fileopen_action, &QAction::triggered, this, &MainWindow::is_fileopen_action_triggered);
    connect(fileclose_action, &QAction::triggered, this, &MainWindow::is_fileclose_action_triggered);
    connect(filesave_action, &QAction::triggered, this, &MainWindow::is_filesave_action_triggered);
    connect(filesaveas_action, &QAction::triggered, this, &MainWindow::is_filesaveas_action_triggered);
    connect(find_action, &QAction::triggered, this, [this]{
        qDebug() << "find action";
        search_dialog->show();
    });

    connect(find_pushbutton, &QPushButton::clicked, this, [this]{
        qDebug() << "find_pushbutton";
        if (current_opened_filename == "未命名.txt") {
            QMessageBox::warning(this, "警告", "没有文件在工作区被打开，\r\n请先打开或创建一个文件。", QMessageBox::Ok);
        } else {
            find();
        }
    });
    connect(quit_action, &QAction::triggered, this, &MainWindow::is_quit_action_triggered);
    connect(revoke_action, &QAction::triggered, this, [this](){
        qDebug() << "撤销";
        main_textedit->undo();
    }); // lambda表达式
    connect(cut_action, &QAction::triggered, this, [this]{
        qDebug() << "剪切";
        main_textedit->cut();
    });
    connect(copy_action, &QAction::triggered, this, [this]{
        qDebug() << "复制";
        main_textedit->copy();
    });
    connect(paste_action, &QAction::triggered, this, [this]{
        qDebug() << "粘贴";
        main_textedit->paste();
    });
    connect(imprint_action, &QAction::triggered, this, [this]{
        qDebug() << "版本说明";
        QMessageBox::information(this, "版本说明", "V0.01\r\nBy:YuXin\t", QMessageBox::Ok);
    });

    connect(search_button, &QPushButton::clicked, this, [this]{
        qDebug() << "搜索";
        QString str = search_lineedit->text();
        qDebug() << str;
        if (!main_textedit->find(str, QTextDocument::FindBackward))
        {
            QMessageBox::warning(this, tr("查找"), tr("找不到%1").arg(str));
        }
    });
}

void MainWindow::new_file()
{
    if (maybe_save())
    {
        is_untitled = true;
        current_opened_filename = tr("未命名.txt");
        setWindowTitle(current_opened_filename);
        this->main_textedit->clear();
        this->main_textedit->setVisible(true);
    }
}

bool MainWindow::maybe_save()
{
    // 如果文档被更改
    if (this->main_textedit->document()->isModified())
    {
        // 自定义一个警告对话框
        QMessageBox box(QMessageBox::Warning, tr("警告"), current_opened_filename + tr("还未保存，是否保存？"));
        QPushButton *yes_pushbutton = box.addButton(tr("是(&Y)"), QMessageBox::YesRole);
        QPushButton *cancel_pushbutton = box.addButton(tr("取消"), QMessageBox::RejectRole);
        box.exec();
        return box.clickedButton() == yes_pushbutton ? save() : box.clickedButton() == cancel_pushbutton ? false : true;
    }
    // 没有修改文档
    return true;
}

bool MainWindow::save()
{
    return is_untitled ? saveas() : save_file(current_opened_filename);
}

bool MainWindow::saveas()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("另存为"), current_opened_filename);
    return filename.isEmpty() ? false : save_file(current_opened_filename);
}

bool MainWindow::save_file(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("多文档编辑器"), tr("无法写入文件 %1: /n %2").arg(filename).arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    // 鼠标指针变为等待状态
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << main_textedit->toPlainText();
    // 鼠标指针恢复为原来的状态
    QApplication::restoreOverrideCursor();
    is_untitled = false;
    // 获取文件的标准路径
    current_opened_filename = QFileInfo(filename).canonicalFilePath();
    setWindowTitle(current_opened_filename);
    return true;
}

bool MainWindow::load_file(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("多文档编辑器"), tr("无法读取文件 %1: /n %2").arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream in(&file); // 文件输入流
    QApplication::setOverrideCursor(Qt::WaitCursor); // 鼠标光标等待
    main_textedit->setPlainText(in.readAll()); // 读取文件并显示到textedit
    QApplication::restoreOverrideCursor(); // 恢复鼠标光标

    // 当前文件操作
    current_opened_filename = QFileInfo(file).canonicalFilePath();
    setWindowTitle(current_opened_filename);
    return true;
}

void MainWindow::find(){
    qDebug() << "find";
    QString text = find_lineedit->text();
    qDebug() << text;
    if (!text.isEmpty()) { // 不为空
        if (!main_textedit->find(text, QTextDocument::FindBackward)) { //未找到
            find_count ? QMessageBox::warning(this, "警告", "找不到更多符合的文字", QMessageBox::Ok) :QMessageBox::warning(this, "警告", "未找到符合的文字", QMessageBox::Ok);
            main_textedit->moveCursor(QTextCursor::Start);
        } else { // 文字背景
            QTextCursor find_cursor=main_textedit->textCursor();
            QTextCharFormat plain_format(find_cursor.charFormat());
            plain_format.setForeground(Qt::red);
            main_textedit->mergeCurrentCharFormat(plain_format);
        }
    } else {
        QMessageBox::warning(this, "警告", "搜索的文字不能为空", QMessageBox::Ok, QMessageBox::Cancel);
    }
}

void MainWindow::is_filenew_action_triggered()
{
    qDebug() << "新建";
    new_file();
}

void MainWindow::is_fileopen_action_triggered()
{
    qDebug() << "打开";
    if (maybe_save())
    {
        QString filename = QFileDialog::getOpenFileName(this);
        // 文件存在
        if (!filename.isEmpty())
        {
            load_file(filename);    // 加载文件
            main_textedit->setVisible(true);
        }
    }
}

void MainWindow::is_fileclose_action_triggered()
{
    qDebug() << "关闭";
    if (maybe_save())
    {
        main_textedit->setVisible(false);
    }
}

void MainWindow::is_filesave_action_triggered()
{
    qDebug() << "保存";
    save();
}

void MainWindow::is_filesaveas_action_triggered()
{
    qDebug() << "另存为";
    saveas();
}

void MainWindow::is_quit_action_triggered()
{
    qDebug() << "退出";
    close();// close this widget
}

MainWindow::~MainWindow()
{
    qDebug() << "main window exit";
    // 菜单条
    delete main_menubar;

    // 菜单
    delete file_menu;
    delete edit_menu;
    delete help_menu;

    // 文件
    delete filenew_action;
    delete fileopen_action;
    delete fileclose_action;
    delete filesave_action;
    delete filesaveas_action;
    delete quit_action;

    // 编辑
    delete revoke_action; // 撤销
    delete cut_action; // 剪切
    delete copy_action;
    delete paste_action;
    delete find_action;

    // 帮助
    delete imprint_action;// 版本说明

    // Toolbar
    delete main_toolbar;

    // 栅格布局
    delete main_gridlayout;

    // pushbutton
    delete find_pushbutton;

    // 文本行编辑框
    delete find_lineedit;

    // 文本编辑框
    delete main_textedit;

    // wideght
    delete main_wideght;

    // dialog
    delete search_dialog;

    // lineedit
    delete search_lineedit;
    delete search_button;
    delete box_layout;
}
