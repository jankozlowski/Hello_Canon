#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canon.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void actions();
    void menus();

private:

    canon *main_canon;
    QMenu *plik_menu, *o_programie_menu;
    QAction *nowy,*wyjdz, *op;

    Ui::MainWindow *ui;

public slots:
    void nowe();
    void oProgramie();

};

#endif // MAINWINDOW_H
