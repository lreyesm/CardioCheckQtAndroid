#ifndef PLOTPOINT_H
#define PLOTPOINT_H

#include <QtCore>
#include "qcustomplot.h"

class PlotPoint : public QCPItemEllipse
{
    Q_OBJECT
public:
    explicit PlotPoint(QCustomPlot *parentPlot, int halfSize = 5, QString text="0");

    ~PlotPoint();

    QPointF pos() const;
    const QColor &color() const;
    void setColor(const QColor &color);
    void set_Selected(bool on){ if(on){setText_Color(QColor(241, 90, 36)); is_selected=true;} else {setText_Color(QColor(255, 255, 255)); is_selected=false;}}
    bool is_Selected(){return is_selected;}
    void setText_Color(const QColor &color){ if(mText_Point_Volts!=NULL)mText_Point_Volts->setColor(color);}
    void startMoving(const QPointF &mousePos, bool shiftIsPressed = false);

    void set_Point_Text(QString n){ mText->setText(n);}
    QString point_text(){return mText->text();}

    void set_Point_visible(bool on);

    void add_Bracket(QPointF pos); //añadir llave entre 2 puntos
    void set_Bracket_visible(bool on);
    void move_Bracket_right(QPointF pos);
    void move_Bracket_left();
    QPointF Bracket_last_left_position(){return mBracket_last_left_position;}  //posicion del punto anterior (donde empieza el bracket)
    QCPItemBracket* bracket(){ return mBracket;} //añadir llave entre 2 puntos

    void set_Item_index_in_list(quint32 index){ mItem_index_in_list = index;}
    quint32 item_index_in_list(){ return mItem_index_in_list;}
    void set_Position(QPointF pos);
    void set_Position(double x, double y);
    void set_Is_EKG_graph_point(bool on);
    bool isEKG_Graph_point(){ return mIs_EKG_graph_point;}

public slots:
    void setVisible(bool on);

signals:
    void activated(); ///< emitted on mouse over
    void disactivated(); ///< emitted when cursor leave us

    void moved(const QPointF &pos);
    void stoppedMoving(const QPointF &pos);

public slots:
    void move(double x, double y, bool signalNeeded = true);
    void movePx(double x, double y);
    void setActive(bool isActive);

    void stopMoving();

private slots:
    void onMouseMove(QMouseEvent *event);
    void moveToWantedPos();
    void onShiftStateChanged(bool shiftPressed);


private:

    QCPItemTracer *mCenterTracer;
    QPointF mGripDelta;
    QPointF mInitialPos;
    bool mIsChangingOnlyOneCoordinate;
    QList<QCPAbstractItem *> mHelperItems;
    QPointF mLastWantedPos;
    QTimer *mMoveTimer;
    QPointF mCurWantedPosPx;
    QCPItemText *mText = NULL;
    QCPItemText *mText_Point_Volts = NULL;
    qint16 mText_Point_Volts_plus_y_pos = -10;
    QCPItemBracket *mBracket = NULL; //llave
    QCPItemText *mBracket_Text = NULL; //tiempo entre dos puntos
    QPointF mBracket_last_left_position;  //posicion del punto anterior (donde empieza el bracket)
    quint16 mBracket_y_position = 1100;

    QPointF last_position;
    quint32 mItem_index_in_list;
    bool mIs_EKG_graph_point = false;
    bool is_selected = false;
};

#endif // PLOTPOINT_H
