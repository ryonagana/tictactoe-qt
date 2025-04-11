#include "mainwindow.h"
#include "ui_main.h"
#include "newgamedialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->Init();

}

void MainWindow::Init()
{
    TButton *btn[9];
    QString title;

    title = "Not So Original Tic-Tac-Toe v%1";
    this->setWindowTitle(title.arg(this->getVersion()));

    for(int i = 0; i < 9; i++){
        btn[i] = new TButton(this);
        btn[i]->setIndex(i);

        this->buttonList.push_back(qMove(btn[i]));

        int col = i % 3;
        int row = i / 3;

        this->ui->gameGrid->addWidget(this->buttonList[i], row, col,
                                      Qt::AlignmentFlag::AlignHCenter |  Qt::AlignmentFlag::AlignCenter |
                                      Qt::AlignmentFlag::AlignVCenter
                                      );
    }


    this->ttt = new TicTacToe(this);

    this->ttt->Init();
    //this->ttt->setVictory(false);
    //this->ttt->setGameOver(true);
    //this->ttt->disableAllCells();
    this->ttt->StartNewGame();
    this->ttt->SetStarterRandom();


    connect(this->ui->acNewGame, &QAction::triggered, this, &MainWindow::menuClick_NewGame);
    connect(this->ui->acAboutQT, &QAction::triggered, this, &QApplication::aboutQt);
    connect(this->ui->acQuit, &QAction::triggered, this, &QApplication::quit);


    connect(this->ui->acCross_Wins, &QAction::triggered, this, &MainWindow::debugCrossWin);
    connect(this->ui->acCircle_Wins, &QAction::triggered, this, &MainWindow::debugCircleWin);
    connect(this->ui->acNo_Wins, &QAction::triggered, this, &MainWindow::debugNoWin);

    this->ui->lcdPlayer1->setDigitCount(6);
    this->ui->lcdPlayer2->setDigitCount(6);
    this->ui->menuDebug->hide();
#ifdef TTT_DEBUG
    this->ui->menuDebug->show();
#endif

}

MainWindow::~MainWindow()
{
    for(auto& btn : this->buttonList){
        delete btn;
    }

    this->buttonList.clear();

    delete ui;
}

QVector<TButton *>& MainWindow::getButtonList()
{
    return this->buttonList;
}

QString MainWindow::getVersion() const
{

    QString ver;
    ver.append(QString::number(GAME_VERSION_MAJ)).append(".").append(QString::number(GAME_VERSION_MIN)).append(".").append(QString::number(GAME_VERSION_BUILD));
    return ver;
}

void MainWindow::debugCrossWin()
{
    QVector<TButton::ButtonType>& grid =  this->ttt->getButtonGrid();

    this->ttt->setDebug(true);
    this->ttt->setStarter( TButton::ButtonType::CROSS);
    grid[0] = TButton::ButtonType::CROSS;
    grid[4] = TButton::ButtonType::CROSS;
    grid[8] = TButton::ButtonType::CROSS;

    this->buttonList[0]->setButtonType(TButton::ButtonType::CROSS);
    this->buttonList[0]->click();
    this->buttonList[4]->setButtonType(TButton::ButtonType::CROSS);
    this->buttonList[4]->click();
    this->buttonList[8]->setButtonType(TButton::ButtonType::CROSS);
    this->buttonList[8]->click();
    this->ttt->setDebug(false);


}

void MainWindow::debugCircleWin()
{
    this->ttt->StartNewGame();
    QVector<TButton::ButtonType>& grid =  this->ttt->getButtonGrid();

    this->ttt->setDebug(true);
    this->ttt->setStarter( TButton::ButtonType::CIRCLE);
    grid[0] = TButton::ButtonType::CIRCLE;
    grid[4] = TButton::ButtonType::CIRCLE;
    grid[8] = TButton::ButtonType::CIRCLE;

    this->buttonList[0]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[0]->click();
    this->buttonList[4]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[4]->click();
    this->buttonList[8]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[8]->click();
    this->ttt->setDebug(false);


}

void MainWindow::debugNoWin()
{
    QVector<TButton::ButtonType>& grid =  this->ttt->getButtonGrid();

    this->ttt->setDebug(true);
    this->ttt->setStarter( TButton::ButtonType::CIRCLE);
    grid[0] = TButton::ButtonType::CIRCLE;
    grid[1] = TButton::ButtonType::CROSS;
    grid[2] = TButton::ButtonType::CIRCLE;
    grid[3] = TButton::ButtonType::CIRCLE;
    grid[4] = TButton::ButtonType::CROSS;
    grid[5] = TButton::ButtonType::CIRCLE;
    grid[6] = TButton::ButtonType::CROSS;
    grid[7] = TButton::ButtonType::CROSS;
    grid[8] = TButton::ButtonType::CIRCLE;

    this->buttonList[0]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[0]->click();
    this->buttonList[4]->setButtonType(TButton::ButtonType::CROSS);
    this->buttonList[4]->click();
    this->buttonList[8]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[8]->click();

    this->buttonList[2]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[2]->click();
    this->buttonList[4]->setButtonType(TButton::ButtonType::CROSS);
    this->buttonList[4]->click();
    this->buttonList[6]->setButtonType(TButton::ButtonType::CIRCLE);
    this->buttonList[6]->click();
    this->ttt->setDebug(false);
}

void MainWindow::menuClick_NewGame()
{
    qDebug() << "NEW GAME CLICKED!";
    //this->ttt->StartNewGame();
    NewGameDialog *dialog = new NewGameDialog(this);
    int result =  dialog->exec();

    switch(result){
        case QDialog::Accepted:
            {
                QButtonGroup *group = dialog->getGroup();
                QAbstractButton *checked = group->checkedButton();

                if(checked){

                    int id = group->id(checked);


                    switch(id){
                        case 1:
                            this->ttt->setStarter(TButton::ButtonType::CROSS);
                            ttt->StartNewGame();;
                            break;
                        case 2:
                            this->ttt->setStarter(TButton::ButtonType::CIRCLE);
                            ttt->StartNewGame();;
                            break;
                        case 3:
                            this->ttt->SetStarterRandom();
                            ttt->StartNewGame();;
                            break;
                        default:
                            QMessageBox::critical(dialog, "Error", "Please Choose One Starter");
                            break;

                    }

                }
            }


        break;

        case QDialog::Rejected:
        break;
    }

    delete dialog;
}

