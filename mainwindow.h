#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *bg[2];
    QWidget *elem[20][10];
    QWidget *ekox[4][4];

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void NewGame();
    void CreateCar();
    void Step();
    void Update();
    void Test();
    void TimeSet();
    void GameOver();
    void Pause();
    void Left();
    void Right();
    void SpeedUp();
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
    QTimer *tmr;
};

#endif // MAINWINDOW_H
