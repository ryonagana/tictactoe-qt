
#include "tictactoe.h"
#include "mainwindow.h"
#include <random>
#include <QMessageBox>
#include <QTimer>
TicTacToe::TicTacToe(QWidget* parent):
    buttonList(static_cast<MainWindow*>(parent)->getButtonList())
{
    this->parent = static_cast<MainWindow*>(parent);



}

void TicTacToe::Init()
{
    timer = new QTimer(parent);
    QObject::connect(timer, &QTimer::timeout, this, &TicTacToe::updateGrid);
    timer->start(50);

    for(auto& btn : this->buttonList){
        QObject::connect(btn, &QToolButton::clicked, this, &TicTacToe::buttonClick);
    }
}

void TicTacToe::StartNewGame()
{

    for(auto& btn : this->buttonList){
        btn->setButtonType(TButton::ButtonType::NONE);
        this->setButtonContent(btn);
        this->buttonGrid.push_back(TButton::ButtonType::NONE);
    }


    game_count = 0;
    victory = false;
    gameover = false;
    enableAllCells();
    clearAllCells();
    updateGrid();

}

void TicTacToe::setButtonContent(TButton *button)
{
    switch(button->getButtonType()){
        case TButton::ButtonType::CROSS:
            button->setText("X");
            break;

        case TButton::ButtonType::CIRCLE:
            button->setText("O");
            break;

        case TButton::ButtonType::NONE:
            button->setText("N");
            break;
    }
}

void TicTacToe::updateGrid()
{
    for(auto& btn : this->buttonList){
       this->setButtonContent(btn);
    }

    if(!gameover){
        if(countUnusedCells() <= 0){
            QMessageBox::warning(nullptr, "Game Over", "Game Over Baby!");
            gameover = true;
            disableAllCells();
            clearAllCells();
            return;
        }

        /*
        if(checkGridVictory(lastPlayer) && !victory ){
            QString message;

            message.append(buttonTypeToStr(lastPlayer).append(" WON!!"));
            QMessageBox::warning(nullptr, "Victory", message);
            victory = true;
            gameover = true;
            disableAllCells();
            clearAllCells();
            return;
        }
        */

        if(checkGridVictory(lastPlayer) && !victory && lastPlayer != TButton::ButtonType::NONE){
            QString message;
            message.append(buttonTypeToStr(lastPlayer).append(" WON!!"));
            QMessageBox::warning(nullptr, "Victory", message);
            victory = true;
            gameover = true;
            disableAllCells();
            clearAllCells();
            return;
        }

    }


}

void TicTacToe::setStarter(TButton::ButtonType tp)
{
    this->startPlayer = tp;
}

TButton::ButtonType TicTacToe::isPlayingNow() const
{
    return this->startPlayer;
}

void TicTacToe::SetStarterRandom()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distribInt(1, 2);
    int rnd = distribInt(gen);

    if( (rnd%2) == 0){
        this->setStarter(TButton::ButtonType::CROSS);
        return;
    }

    this->setStarter(TButton::ButtonType::CIRCLE);
    return;
}

int TicTacToe::countUnusedCells()
{
    int count = this->buttonGrid.size();

    for(auto& b : this->buttonList){
        if(!b->isEnabled()){
            count--;
        }
    }

    return count;
}

void TicTacToe::enableAllCells()
{

    for(auto& btn : this->buttonList){
        btn->setEnabled(true);
    }

}

void TicTacToe::disableAllCells()
{

    for(auto& btn : this->buttonList){
        btn->setEnabled(false);
    }

}

void TicTacToe::switchPlayer()
{

    if( (game_count % 1) == 0){
        lastPlayer = startPlayer;
        startPlayer =  startPlayer == TButton::ButtonType::CIRCLE ? TButton::ButtonType::CROSS : TButton::ButtonType::CIRCLE;

    }
}

bool TicTacToe::checkGridVictory(TButton::ButtonType player)
{

    for(int line = 0; line < GRID_W; line++){


        if(player != TButton::ButtonType::NONE && this->buttonGrid[line * 3] == player && this->buttonGrid[line * 3 + 1] == player && this->buttonGrid[line * 3 + 2] == player){
            return true;
        }

    }

    for(int column = 0; column < GRID_H; column++){

        if(player != TButton::ButtonType::NONE && this->buttonGrid[column] == player && this->buttonGrid[column + 3] == player && this->buttonGrid[column + 6] == player){
            return true;
        }
    }

    //diagonals
    if(this->buttonGrid[0] == player && this->buttonGrid[4] == player && this->buttonGrid[8] == player){
        return true;
    }

    if(this->buttonGrid[2] == player && this->buttonGrid[4] == player && this->buttonGrid[6] == player){
        return true;
    }


    return false;
}

void TicTacToe::clearAllCells()
{
    for(auto& btn : this->buttonGrid){
        btn = TButton::ButtonType::NONE;
    }
}

QString TicTacToe::buttonTypeToStr(TButton::ButtonType player)
{
    QString txt;
    switch(player){
        default:
        case TButton::ButtonType::NONE:
            txt = "None (empty)";
            break;
        case TButton::ButtonType::CROSS:
            txt = "Cross";
            break;

        case TButton::ButtonType::CIRCLE:
            txt = "Circle";
            break;
    }

    return txt;
}



void TicTacToe::buttonClick()
{
    QObject *senderObject = sender();
    TButton *button = static_cast<TButton*>(senderObject);
    qDebug() << countUnusedCells();




    if(button){
        int x =  button->getIndex() % GRID_W;
        int y =  button->getIndex() / GRID_H;



        buttonGrid[x * GRID_W + y] = this->startPlayer;
        button->setButtonType(this->startPlayer);


        if(button->isEnabled()){
            button->setEnabled(false);
        }

        game_count++;
        switchPlayer();
        this->updateGrid();

    }
}


