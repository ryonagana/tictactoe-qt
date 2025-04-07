#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QRadioButton>
#include <QLabel>
#include <QToolButton>
#include <QButtonGroup>
#include <QVBoxLayout>

class NewGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDialog(QWidget *parent = nullptr);
    QButtonGroup *getGroup();

signals:

private:
    QRadioButton *startCrossOption;
    QRadioButton *startCircleOption;
    QRadioButton *startRandomOption;
    QButtonGroup *group;
    QWidget *parent;

};

#endif // NEWGAMEDIALOG_H
