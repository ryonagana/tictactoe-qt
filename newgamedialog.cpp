#include "newgamedialog.h"

NewGameDialog::NewGameDialog(QWidget *parent):
    parent(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *checksLayout = new QHBoxLayout(this);
    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);

    startCrossOption = new QRadioButton("Start With Crosses");
    startCircleOption = new QRadioButton("Start With Circle");
    startRandomOption = new QRadioButton("Random");

    startRandomOption->setChecked(true);

    QToolButton *confirm = new QToolButton(this);
    QToolButton *cancel = new QToolButton(this);



    group = new QButtonGroup(this);
    group->addButton(startCrossOption,  1);
    group->addButton(startCircleOption, 2);
    group->addButton(startRandomOption, 3);



    checksLayout->addStretch(1);
    checksLayout->addWidget(startCrossOption);
    checksLayout->addWidget(startCircleOption);
    checksLayout->addWidget(startRandomOption);

    QButtonGroup *buttonsGroup  = new QButtonGroup(this);
    buttonsGroup->addButton(confirm,1);
    buttonsGroup->addButton(cancel,1);

    buttonsLayout->addWidget(confirm);
    buttonsLayout->addWidget(cancel);

    confirm->setText("OK");
    cancel->setText("Cancel");

    layout->addLayout(checksLayout);
    layout->addLayout(buttonsLayout);

    this->setLayout(layout);

    connect(confirm, &QToolButton::clicked, this, &QDialog::accept);
    connect(cancel, &QToolButton::clicked, this, &QDialog::reject);
}

QButtonGroup *NewGameDialog::getGroup()
{
    return this->group;
}
