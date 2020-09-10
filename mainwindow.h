#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class QPushButton;
class QMenuBar;
class QToolBar;
class QAction;
class QMenu;
class QTextEdit;
class QLineEdit;
class QGridLayout;
class QString;
class QDialog;
class QVBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void new_file();// 新建文件
    bool maybe_save();// 是否需要保存
    bool save();    // 保存操作
    bool saveas();  // 另存为操作
    bool save_file(const QString &filename);    // 保存文件
    bool load_file(const QString &filename);    // 加载文件
    void find(); // 查找

private:
    bool is_untitled;   // 未命名，即未保存
    QString current_opened_filename; // 当前打开的文件名
    int find_count;

public slots:
    void is_filenew_action_triggered();
    void is_fileopen_action_triggered();
    void is_fileclose_action_triggered();
    void is_filesave_action_triggered();
    void is_filesaveas_action_triggered();
    void is_quit_action_triggered();

private:
    // 菜单条
    QMenuBar *main_menubar;

    // 菜单
    QMenu *file_menu;
    QMenu *edit_menu;
    QMenu *help_menu;

    // 文件
    QAction *filenew_action;
    QAction *fileopen_action;
    QAction *fileclose_action;
    QAction *filesave_action;
    QAction *filesaveas_action;
    QAction *quit_action;

    // 编辑
    QAction *revoke_action; // 撤销
    QAction *cut_action; // 剪切
    QAction *copy_action;
    QAction *paste_action;
    QAction *find_action;

    // 帮助
    QAction *imprint_action;// 版本说明

    // Toolbar
    QToolBar *main_toolbar;

    // 栅格布局
    QGridLayout *main_gridlayout;

    // pushbutton
    QPushButton *find_pushbutton;

    // 文本行编辑框
    QLineEdit *find_lineedit;

    // 文本编辑框
    QTextEdit *main_textedit;

    // wideght
    QWidget *main_wideght;

    // dialog
    QDialog *search_dialog;
    // lineedit
    QLineEdit *search_lineedit;

    QPushButton *search_button;
    QVBoxLayout *box_layout;
};
#endif // MAINWINDOW_H
