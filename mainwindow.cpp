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
    this->ttt->StartNewGame();
    this->ttt->SetStarterRandom();


    connect(this->ui->acNewGame, &QAction::triggered, this, &MainWindow::menuClick_NewGame);
    connect(this->ui->acAboutQT, &QAction::triggered, this, &QApplication::aboutQt);
    connect(this->ui->acQuit, &QAction::triggered, this, &QApplication::quit);

    this->ui->lcdPlayer1->setDigitCount(6);
    this->ui->lcdPlayer2->setDigitCount(6);

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

                    if(id <= 0){
                        QMessageBox::critical(dialog, "Error", "Please Choose One Starter");
                        return;
                    }

                    switch(id){
                        case 1:
                            this->ttt->setStarter(TButton::ButtonType::CROSS);
                            break;
                        case 2:
                            this->ttt->setStarter(TButton::ButtonType::CIRCLE);
                            break;
                        case 3:
                            this->ttt->SetStarterRandom();
                            break;
                    }

                }
            }

            ttt->StartNewGame();;
        break;

        case QDialog::Rejected:
        break;
    }

    delete dialog;
}

