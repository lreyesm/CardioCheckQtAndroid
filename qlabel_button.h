#ifndef QLABEL_BUTTON_H
#define QLABEL_BUTTON_H

#include <QLabel>
#include <QMouseEvent>

class QLabel_Button : public QLabel
{
    Q_OBJECT
public:
    explicit QLabel_Button(QWidget *parent = nullptr);
    ~QLabel_Button();


signals:

    void doubleClicked();
    void rightClicked();
    void leftClicked();

protected:

    void mouseDoubleClickEvent(QMouseEvent *)
    {
        emit doubleClicked();
    }

private slots:

    void mousePressEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
        if(e->buttons()==Qt::RightButton)
            emit rightClicked();

        if(e->buttons()==Qt::LeftButton)
            emit leftClicked();
    }
};

#endif // QLABEL_BUTTON_H
