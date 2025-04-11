#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include "tbutton.h"
#include <QVector>
#include <QObject>
#include <QMap>

class MainWindow;

class TicTacToe : public QObject
{


public:
    static constexpr int GRID_W = 3;
    static constexpr int GRID_H = 3;

    enum GameState {
        PLAY = 1,
        END  = 2
    };

    TicTacToe(QWidget* parent);
    ~TicTacToe();
    void Init();
    void StartNewGame();
    void setButtonContent(TButton *button);
    void updateGrid();
    void setStarter(TButton::ButtonType tp);
    TButton::ButtonType isPlayingNow() const;
    void SetStarterRandom();

    int countUnusedCells();
    void enableAllCells();
    void disableAllCells();
    void switchPlayer();
    bool checkGridVictory(TButton::ButtonType player);
    void clearAllCells();
    QString buttonTypeToStr(TButton::ButtonType player);
    void setVictory(bool value);
    bool getVictory() const;
    void setGameOver(bool value);
    bool getGameOver() const;
    void setDebug(bool value);
    QVector<TButton::ButtonType>& getButtonGrid();
    GameState playAgainMessageBox();
    void loadImages();
private slots:
    void buttonClick();



 signals:
    void isButtonClicked(int i, QToolButton *button);


 private:
   MainWindow* parent;
   uint32_t p1_score;
   uint32_t p2_score;
   TButton::ButtonType startPlayer;
    TButton::ButtonType lastPlayer;
   int game_count;
   QVector<TButton::ButtonType> buttonGrid;
   QVector<TButton*>& buttonList;
   QTimer *timer;
   bool gameover;
   bool victory;
   GameState gameState;
   bool debug_mode;
   QMap<QString,QIcon*> imageList;

};

#endif // TICTACTOE_H
