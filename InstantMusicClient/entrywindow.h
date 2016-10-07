#ifndef ENTRYWINDOW_H
#define ENTRYWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

class ServerInfo {
    void test() {
        qDebug() << "Test working";
    }

public:
    ServerInfo() {

    }
};

namespace Ui {
    class EntryWindow;
}

class EntryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EntryWindow(QWidget *parent = 0);
    ~EntryWindow();

private slots:
    void button_handle();

private:
    Ui::EntryWindow *ui;
    QPushButton *p_btn;

};

#endif // ENTRYWINDOW_H
