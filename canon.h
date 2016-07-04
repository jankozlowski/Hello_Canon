#ifndef CANON_H
#define CANON_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QLCDNumber>
#include <vector>


class canon : public QWidget
{

     Q_OBJECT

public:
    explicit canon(QWidget *parent = 0);

    void zasieg();
    void czas(double d);
    double length();
    double length(int time);
    double height();
    double height(int time);
    double maxheight();
    void wyczysc();
    void predkosc_x();
    void predkosc_y();
    void punkty();
    void paintEvent(QPaintEvent *e);

private:

    QSlider *moc, *predkosc, *animacja;
    QSpinBox *kat;
    QLCDNumber *result, *result2,*result3, *result4, *result5, *result6, *result7, *result8;
    QTimer *przedzial;
    double wynik1,wynik2,wynik3;
    double pr,rads;
    std::vector<std::vector< int > > path;
    int pathnum;
    bool dodaj;

public slots:
        void start();
        void kontynuj();
        void zatrzymaj();
        void zmienanimacje(int time);
        void update();

};

#endif // CANON_H
