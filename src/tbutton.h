#ifndef TBUTTON_H
#define TBUTTON_H

#include <QObject>
#include <QToolButton>

class TButton : public QToolButton
{


    Q_OBJECT
public:

    typedef enum {
        NONE,
        CROSS,
        CIRCLE
    }ButtonType;

    explicit TButton(QWidget *parent = nullptr);
    ~TButton() override;

    void Start();
    void setButtonType(ButtonType type);
    ButtonType getButtonType() const;
    void setIndex(int index);
    int getIndex() const;

private:
    int index;
    QWidget *parent;
    ButtonType buttonType;



signals:

};

#endif // TBUTTON_H
