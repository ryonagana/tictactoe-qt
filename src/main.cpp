#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <memory>


void initTranslate(QApplication& app){
    QString system_lang = QLocale::system().name();
    QTranslator* translator = new QTranslator();

    if(translator->load("tictactoe_" + system_lang,":/i18n")){
        app.installTranslator(translator);
    }


}

int main(int argc, char *argv[])
{
    QApplication program(argc, argv);

    QApplication::setApplicationName("tic-tac-toe QT");
    QApplication::setApplicationDisplayName("TicTacToe");

    QStringList version_str;

    version_str << QString::number(GAME_VERSION_MAJ)
                << QString::number(GAME_VERSION_MIN)
                << QString::number(GAME_VERSION_BUILD);

    QApplication::setApplicationVersion(version_str.join('.'));

    initTranslate(program);

    std::shared_ptr<MainWindow> w = std::make_shared<MainWindow>();
    w->show();
    return program.exec();
}
