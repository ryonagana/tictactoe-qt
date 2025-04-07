#include "tbutton.h"
#include <QDebug>

TButton::TButton(QWidget *parent)
    : QToolButton(parent)
{
    this->parent = parent;
    this->Start();

}

TButton::~TButton(){

}

void TButton::Start()
{
    this->buttonType = TButton::ButtonType::NONE;
    this->setFixedSize(200,200);

}

void TButton::setButtonType(ButtonType type)
{
    this->buttonType = type;
}

TButton::ButtonType TButton::getButtonType() const
{
    return buttonType;
}

void TButton::setIndex(int index)
{
    this->index = index;
}

int TButton::getIndex() const
{
    return index;
}

