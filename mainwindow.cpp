//   Copyright 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com   // 



#include <QtGui>
#include <QWidget>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"

const int N = 20, M = 10;
int scars[N+4][M];
int car_x;

int car[4][3] = {
    {0, 1, 0},
    {1, 1, 1},
    {0, 1, 0},
    {1, 0, 1}};

int score, counter;
bool pause;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bg[0] = new QWidget(this);
    bg[0]->setGeometry(0,0,311,620);
    bg[0]->setStyleSheet("background-color:gray;");

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            elem[i][j] = new QWidget(this);
            elem[i][j]->setGeometry(1+j*31,i*31,30,30);
            elem[i][j]->setStyleSheet("background-color:lightgray;");
        }
    }

    bg[1] = new QWidget(this);
    bg[1]->setGeometry(311,0,120,620);
    bg[1]->setStyleSheet("background-color:lightgray;");

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            ekox[i][j] = new QWidget(this);
            ekox[i][j]->setGeometry(311+20+j*20,150+i*20,19,19);
            ekox[i][j]->setStyleSheet("background-color:gray;");
        }
    }

    tmr = new QTimer;
    connect(tmr, SIGNAL(timeout()), this, SLOT(Step()));
    tmr->start();

    MainWindow::NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::NewGame() {
    score = counter = 0;
    pause = false;
    car_x = 1;
    for (int i = 0; i < N+4; i++) {
        for(int j = 0; j < M; j++) {
            scars[i][j] = 0;
        }
    }

    MainWindow::CreateCar();
    MainWindow::TimeSet();
}

void MainWindow::CreateCar() {
    int coin = rand() % 3;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            if (car[i][j]) scars[i][1 + j + 3*coin] = 1;
        }
    }
}

void MainWindow::Step() {
    if(!pause) {
        for (int i = N+3; i > 0; i--) {
            for(int j = 0; j < M; j++) {
                scars[i][j] = scars[i-1][j];
                if (i == 1) scars[i-1][j] = 0;
                if (j == 0 && i == 1 && !(counter % 2)) scars[i][j] = 1;
            }
        }
        if (counter == 9) {
            counter = 0;
            score += 100;
            MainWindow::CreateCar();
        }
        else counter++;

        MainWindow::Update();
    }
}


void MainWindow::Update() {
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if (scars[i+4][j]) elem[i][j]->setStyleSheet("background-color:black;");
            else elem[i][j]->setStyleSheet("background-color:lightgray;");
        }
    }

    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            if (car[i][j]) elem[16 + i][1+j + car_x*3]->setStyleSheet("background-color:black;");
        }
    }
    MainWindow::Test();
    MainWindow::TimeSet();
}

void MainWindow::Test() {
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 3; j++) {
            sum += (car[i][j] * scars[20][j+1 + car_x*3]);
        }
    }
    if (sum != 0) MainWindow::GameOver();
}

void MainWindow::TimeSet() {
    if (score < 500) tmr->setInterval(300);
    else if (score >= 500 && score < 1000) tmr->setInterval(250);
    else if (score >= 1000) tmr->setInterval(200);
}

void MainWindow::GameOver() {
    MainWindow::NewGame();
}

void MainWindow::Pause() {
    pause = !pause;
}

void MainWindow::Left() {
    if(!pause) {
        if (car_x != 0) car_x--;
        MainWindow::Test();
    }
    else MainWindow::Pause();
}

void MainWindow::Right() {
    if(!pause) {
        if (car_x != 2) car_x++;
        MainWindow::Test();
    }
    else MainWindow::Pause();
}

void MainWindow::SpeedUp() {
    if (!pause) {
        tmr->setInterval(1);
    }
    else MainWindow::Pause();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_8 || event->key() == Qt::Key_W) {MainWindow::SpeedUp();}
    else if(event->key() == Qt::Key_6 || event->key() == Qt::Key_D) {MainWindow::Right();}
    else if(event->key() == Qt::Key_4 || event->key() == Qt::Key_A) {MainWindow::Left();}
    else if(event->key() == Qt::Key_P) {MainWindow::Pause();}
    QMainWindow::keyPressEvent(event);
}
