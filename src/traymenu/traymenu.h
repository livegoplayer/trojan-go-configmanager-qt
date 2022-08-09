#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QMenu>

class TrayMenu : public QMenu
{
public:
    explicit TrayMenu(QWidget *parent = 0);
    ~TrayMenu();

signals:
    // 自定义信号
    void showWindow();

private:
    // 添加菜单项
    void initActions();

private:
};

#endif // TRAYMENU_H
