#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canon.h"
#include <QpushButton>
#include <QGridLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Hello Cannon"));
    main_canon = new canon;
    setCentralWidget(main_canon);
    removeToolBar(ui->mainToolBar);
    setFixedSize(1100, 600);

    actions();
    menus();
}

void MainWindow::nowe(){
    main_canon->wyczysc();
}

void MainWindow::actions(){

    nowy = new QAction(tr("Nowy"),this);
    nowy->setShortcut(QKeySequence::New);
    connect(nowy,SIGNAL(triggered()),this,SLOT(nowe()));

    wyjdz = new QAction(tr("Wyjdz"),this);
    wyjdz->setShortcut(QKeySequence(tr("Ctrl+Q")));
    connect(wyjdz,SIGNAL(triggered()), qApp, SLOT(quit()));

    op = new QAction(tr("O Programie"),this);
    connect(op,SIGNAL(triggered()),this,SLOT(oProgramie()));

}

void MainWindow::menus(){

    plik_menu = menuBar()->addMenu(tr("Plik"));
    plik_menu -> addAction(nowy);
    plik_menu -> addAction(wyjdz);

    o_programie_menu = menuBar()->addMenu((tr("O programie")));
    o_programie_menu -> addAction(op);

}

void MainWindow::oProgramie(){
    QWidget *programie = new QWidget();
    programie->setWindowTitle(tr("O programie"));

    QGridLayout *places = new QGridLayout;

    QLabel *canonimage= new QLabel(programie);
    canonimage->setPixmap(QPixmap("canon.jpg"));
    places->addWidget(canonimage,0,0,4,1);

    QPushButton *OK = new QPushButton("OK",programie);
    places->addWidget(OK,2,3);

    QLabel *version = new QLabel(tr("Hello Canon 1.0"),programie);
    places->addWidget(version,0,1,Qt::AlignCenter);
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    version->setFont(font);

    QLabel *opis = new QLabel(tr("Program umozliwia wyliczanie trajektoriów lotu wystrzelonych\npocisków pod dowolnym kątem z pominieciem oporu powietrza.\n\n"
                              "Autor: Jan Kozłowski\n\nTelefon: 514393032\n\nE-mail: jankozlowsk@gmail.com"),programie);
    places->addWidget(opis,1,1);

    programie->setLayout(places);
    programie->show();
    connect(OK, SIGNAL(clicked()),programie,SLOT(close()));
}


MainWindow::~MainWindow()
{
    delete ui;
}
