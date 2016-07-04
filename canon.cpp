#include "canon.h"
#include <math.h>
#include <QpushButton>
#include <QPainter>
#include <QTimer>


canon::canon(QWidget *parent) :
    QWidget(parent)
{

    wynik1=0;
    pathnum=0;
    pr=0;
    dodaj=false;

    QLabel *lkat = new QLabel(tr("Kąt"),this);
    lkat->setGeometry(10,10,60,20);
    QLabel *lmoc = new QLabel(tr("Prędkość początkowa"),this);
    lmoc->setGeometry(10,70,120,20);
    QLabel *lanimacja = new QLabel(tr("Moment animacji"),this);
    lanimacja->setGeometry(110,470,120,20);
    QLabel *lpredkosc = new QLabel(tr("Szybkość odtwarzania"),this);
    lpredkosc->setGeometry(10,125,120,20);

    kat = new QSpinBox(this);
    kat->setMinimum(0);
    kat->setMaximum(90);
    kat->setGeometry(10,40,50,20);

    moc = new QSlider(Qt::Horizontal,this);
    moc->setGeometry(10,100,100,15);
    moc->setMinimum(0);
    moc->setMaximum(1000);

    predkosc = new QSlider(Qt::Horizontal,this);
    predkosc->setGeometry(10,150,100,15);
    predkosc->setMinimum(-10);
    predkosc->setMaximum(10);

    animacja = new QSlider(Qt::Horizontal,this);
    animacja->setGeometry(30,500,240,15);
    animacja->setMinimum(0);
    animacja->setMaximum(0);

    QLCDNumber *power = new QLCDNumber(this);
    power->setGeometry(130,95,50,20);
    QLCDNumber *speed = new QLCDNumber(this);
    speed->setGeometry(130,145,50,20);

    QPushButton *oblicz = new QPushButton(tr("Oblicz"),this);
    oblicz->setGeometry(200,100,100,60);

    QLabel *lzasieg = new QLabel(tr("Zasięg (m)"),this);
    lzasieg->setGeometry(10,175,120,20);
    QLabel *lczas = new QLabel(tr("Czas lotu (s)"),this);
    lczas->setGeometry(10,230,120,20);
    QLabel *lx = new QLabel(tr("Położenie x (m)"),this);
    lx->setGeometry(10,285,120,20);
    QLabel *ly = new QLabel(tr("Położenie y (m)"),this);
    ly->setGeometry(10,340,120,20);
    QLabel *lt = new QLabel(tr("Aktualny czas (s)"),this);
    lt->setGeometry(10,395,120,20);
    QLabel *lmaxh = new QLabel(tr("Wysokość maksymalna (m)"),this);
    lmaxh->setGeometry(170,175,130,20);
    QLabel *lpredkoscx = new QLabel(tr("Prędkość dla x (m/s)"),this);
    lpredkoscx->setGeometry(170,230,120,20);
    QLabel *lpredkoscy = new QLabel(tr("Prędkość dla y (m/s)"),this);
    lpredkoscy->setGeometry(170,285,120,20);

    result = new QLCDNumber(this);
    result->setGeometry(10,200,130,25);
    result->setDigitCount(6);
    result2 = new QLCDNumber(this);
    result2->setGeometry(10,255,130,25);
    result2->setDigitCount(6);
    result3 = new QLCDNumber(this);
    result3->setGeometry(10,310,130,25);
    result3->setDigitCount(6);
    result4 = new QLCDNumber(this);
    result4->setGeometry(10,365,130,25);
    result4->setDigitCount(6);
    result5 = new QLCDNumber(this);
    result5->setGeometry(10,420,130,25);
    result5->setDigitCount(6);
    result6 = new QLCDNumber(this);
    result6->setGeometry(170,200,130,25);
    result6->setDigitCount(6);
    result7 = new QLCDNumber(this);
    result7->setGeometry(170,255,130,25);
    result7->setDigitCount(6);
    result8 = new QLCDNumber(this);
    result8->setGeometry(170,310,130,25);
    result8->setDigitCount(6);

    QPushButton *play = new QPushButton(tr("Play"),this);
    play->setGeometry(40,530,100,30);
    QPushButton *stop = new QPushButton(tr("Stop"),this);
    stop->setGeometry(160,530,100,30);

    przedzial = new QTimer(this);
    przedzial->setInterval(1);

    connect(moc, SIGNAL(valueChanged(int)), power, SLOT(display(int)));
    connect(predkosc, SIGNAL(valueChanged(int)), speed, SLOT(display(int)));
    connect(oblicz, SIGNAL(clicked()), this, SLOT(start()));
    connect(przedzial, SIGNAL(timeout()), this, SLOT(update()));
    connect(animacja, SIGNAL(valueChanged(int)), this, SLOT(zmienanimacje(int)));
    connect(play, SIGNAL(clicked()), this, SLOT(kontynuj()));
    connect(stop, SIGNAL(clicked()), this, SLOT(zatrzymaj()));

    predkosc->setValue(1);
}


void canon::kontynuj(){
   przedzial->start();

}

void canon::zatrzymaj(){
    przedzial->stop();
}

void canon::wyczysc(){
    result->display(0);
    result2->display(0);
    result3->display(0);
    result4->display(0);
    result5->display(0);
    result6->display(0);
    result7->display(0);
    result8->display(0);
    pr=0;
    path.clear();
    pathnum=0;
    wynik1=0;
    wynik2=0;
    wynik3=0;
    dodaj=false;
    moc->setValue(0);
    predkosc->setValue(1);
    animacja->setValue(0);
    animacja->setMaximum(0);
    animacja->setMinimum(0);
    kat->setValue(0);
    repaint();
}


double canon::length(){

    double wynik;
    wynik=moc->sliderPosition()*(pr)*cos(rads);
    result3->display(wynik);
    return wynik;
}

double canon::height(){

    double wynik;
    wynik = (moc->sliderPosition()*(pr)*sin(rads))-(9.81*(pr)*(pr))/2;
    if(pr==wynik2){
        wynik=0;
    }
    result4->display(wynik);
    return wynik;

}

double canon::length(int time){

    double wynik;
    wynik=moc->sliderPosition()*(time)*cos(rads);
    result3->display(wynik);
    return wynik;
}

double canon::height(int time){

    double wynik;
    wynik = (moc->sliderPosition()*(time)*sin(rads))-(9.81*(time)*(time))/2;
    result4->display(wynik);
    return wynik;

}

double canon::maxheight(){
    double mh = ((moc->sliderPosition()*moc->sliderPosition()*sin(rads)*sin(rads))/((2*9.81)));
    return mh;
}

void canon::predkosc_x(){
    int vx = moc->sliderPosition()*cos(rads);
    result7->display(vx);
}

void canon::predkosc_y(){
    int vy = (moc->sliderPosition()*sin(kat->value() * atan(1)*4/180.0))-(9.81*pr);
    result8->display(vy);
}

void canon::zasieg(){

    wynik1=((moc->sliderPosition()*moc->sliderPosition())/9.81)*sin(2*rads);
    result->display(wynik1);

}

void canon::czas(double d){

    if(moc->sliderPosition()!=0)
        wynik2=d/(moc->sliderPosition()*cos(rads));
    else
        wynik2=0;
    result2->display(wynik2);
}

void canon::punkty(){
    double skala = ceil(wynik1/140);
    skala = ceil(skala/10)*10;

    double skala2 = maxheight();
    skala2 = ceil(skala2/90);
    skala2 = ceil(skala2/10)*10;

    for(int a=0; a<wynik2; a++){
        path.push_back(std::vector <int> ());
        path[a].push_back(345+(length(a)*5)/skala);
        path[a].push_back(505-(height(a)*5)/skala2);
    }
}

void canon::start(){

    path.clear();
    animacja->setSliderPosition(0);
    pathnum=0;
    pr=0;
    rads=kat->value() * atan(1)*4/180.0;

    predkosc_x();
    zasieg();
    czas(wynik1);
    animacja->setMaximum(ceil(wynik2));
    punkty();
    result6->display(maxheight());
    przedzial->start();

}

void canon::update(){

    if(pr<=wynik2 && pr>=0){
        if(dodaj==true){
            pr-=(0.1*predkosc->sliderPosition());
            dodaj=false;
        }
        double sp = predkosc->sliderPosition()*0.1;
        pr+=sp;
        if(pr>=wynik2)
            pr=wynik2;
        else
            animacja->setSliderPosition(pr);
        result5->display(pr);
        predkosc_y();
        repaint();
    }

    else if(pr<0){
        pr=0;
        repaint();
        result5->display(0);
        przedzial->stop();
    }
    else{
        przedzial->stop();
    }

}

void canon::zmienanimacje(int time){

    Q_UNUSED(time);
    predkosc_x();

    if(animacja->sliderPosition()>wynik2){
        pr=wynik2-(0.1*predkosc->sliderPosition());
    }
    else{
        pr = animacja->sliderPosition()-(0.1*predkosc->sliderPosition());
        if(pr<0){
            dodaj=true;
            pr=0;
        }
        else{
            dodaj=false;
        }
    }
    update();


}

void canon::paintEvent(QPaintEvent *e){

    Q_UNUSED(e);
    QPainter painter(this);

    painter.drawLine(350,510,350,50);
    painter.drawLine(350,510,1050,510);

    painter.drawLine(1050,510,1045,505);
    painter.drawLine(1050,510,1045,515);
    painter.drawLine(350,50,355,55);
    painter.drawLine(350,50,345,55);

    for(int a=0; a<=45; a++){
        if(a%5==0){
            painter.drawLine(345,510-(a*10),355,510-(a*10));
        }
        else{
            painter.drawLine(348,510-(a*10),352,510-(a*10));
        }
    }
    for(int b=0; b<70; b++){
        if(b%5==0){
           painter.drawLine(350+(b*10),505,350+(b*10),515);
        }
        else{
           painter.drawLine(350+(b*10),508,350+(b*10),512);
        }
    }

    double skala = ceil(wynik1/140);
    skala = ceil(skala/10)*10;

    double skala2 = maxheight();
    skala2 = ceil(skala2/90);
    skala2 = ceil(skala2/10)*10;


    int value1 = 10*skala;
    int value2 = 10*skala2;

    if(wynik1>0){

        for(int a=0; a<9; a++){
            QPoint point = QPoint(315,465-(a*50));
            painter.drawText(point, QString::number(value2*(a+1)));
        }

        for(int b=0; b<14; b++){
            QPoint point = QPoint(391+(b*50),530);
            painter.drawText(point, QString::number(value1*(b+1)));
        }
    }

    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(345+(length()*5)/skala,505-(height()*5)/skala2,10,10);

    for(int a=0; a<pr; a++){
        painter.drawEllipse(path[a][0]+5,path[a][1]+5,1,1);
    }
}
