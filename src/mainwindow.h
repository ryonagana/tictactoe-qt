#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QVector>
#include <QDebug>
#include <QtCore/qalgorithms.h>
#include "tbutton.h"
#include "tictactoe.h"


#define GAME_VERSION_MAJ   0
#define GAME_VERSION_MIN   0
#define GAME_VERSION_BUILD 5

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Init();
    ~MainWindow();

    QVector<TButton*>& getButtonList();
    QString getVersion() const;

    //debug functions
    void debugCrossWin();
    void debugCircleWin();
    void debugNoWin();

private slots:
    void menuClick_NewGame();

private:
    Ui::MainWindow *ui;
    QVector<TButton*> buttonList;
    TicTacToe *ttt;
};
#endif // MAINWINDOW_H
