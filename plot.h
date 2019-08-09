#ifndef PLOT_H
#define PLOT_H

#include <QtCore/QObject>
#include <QtGui/QScreen>
#include <QtGui/QWindow>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLFunctions_3_0>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QSurfaceFormat>

#include "plotpoint.h"
#include "qlabel_button.h"

class Plot: public QCustomPlot , protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Plot(QWidget *parent  = 0, int radio_point = 15);

    ~Plot();

protected:

    virtual void initializeGL() override
    {
        initializeOpenGLFunctions();
    }

    virtual void paintGL() override
    {
        //glClearColor(0.f, 0.15f, 0.05f, 0.f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width()/2, height()/2); //works!!
    }
    virtual void resizeGL(int w, int h) override
    {
        glViewport(0, 0, w/2, h/2); //doesn't work
    }

public:

    void setup_Graph();

    void setup_Plot_variables();

    void set_Background_blur(QWidget* blur){background_blur = blur;}

    void enable_maximize_button(bool on);

    void set_Interactions_in_graph(bool on);

    void clear_Data();

    void add_Data(quint8 graph_i=0, quint32 x =0, quint32 y =0);
    void add_Data(quint8 graph_i, QVector<double> x_vector, QVector<double> y_vector);
    void add_Data(quint8 graph_i, QVector<double> y_vector);

    void set_Range_x_axis_initial(int min, int max){ x_axis_initial_range = QCPRange(min, max); this->xAxis->setRange(min, max);}
    void set_Range_x_axis(QCPRange range){ x_axis_range = range; this->xAxis->setRange(range);}
    void set_Range_x_axis(int min, int max){ x_axis_range = QCPRange(min, max); this->xAxis->setRange(min, max);}
    void set_Range_y_axis_initial(int min, int max){ y_axis_initial_range = QCPRange(min, max); this->yAxis->setRange(min, max);}
    void set_Range_y_axis(QCPRange range){ y_axis_range = range; this->yAxis->setRange(range);}
    void set_Range_y_axis(int min, int max){ y_axis_range = QCPRange(min, max); this->yAxis->setRange(min, max);}

    void set_Size(QSize size){ m_size = size; this->setFixedSize(m_size);}
    void set_maximize_Size(QSize size){ maximize_size = size; /*this->setFixedSize(maximize_size);*/}
    void set_is_Maximized(bool on){ isMaximized = on;}

    void set_position(QPoint position){ m_pos = position; move(m_pos);}
    void set_maximize_position(QPoint position){ maximized_pos = position;}
    void set_Maximized_position_whit_other_maximize(QPoint position){ maximized_pos_with_other_maximize = position;}

    void set_button_maximize(QLabel_Button* button){ button_maximized_with_other = (QLabel_Button*)button; button_maximized_with_other->hide();
                                                     QObject::connect(button_maximized_with_other,SIGNAL(leftClicked()),this,SLOT(maximizar_graph_with_other_button()));}
    void show_button_maximize(bool on);

    void set_other_graph1(Plot* graph){ other_graph1 = (Plot*)graph;}
    void set_other_graph2(Plot* graph){ other_graph2 = (Plot*)graph;}


    QCPRange x_axis_Range(){ return x_axis_range;}
    QCPRange y_axis_Range(){ return y_axis_range;}
    QCPRange x_axis_initial_Range(){ return x_axis_initial_range;}
    QCPRange y_axis_initial_Range(){ return y_axis_initial_range;}

    bool is_graph_Maximized(){return isMaximized;}

    QPointF last_Point_After_Moving(){return last_point_after_moving;}
    bool isEKG_Graph(){ return mIsEKG_Graph;}
    void set_IsEKG_Graph(bool on){ mIsEKG_Graph = on;}

    void move_Bracket_right_to_this_pos(int index, QPointF pos);

    void set_Point_Selected(bool on, int index);

    void set_Brackets_Visibles(bool on, int index);

    void set_button_maximize_pos(bool up = false); //up o down position

    bool is_first_pos(){return isFirtsPos;}

    void set_graph_number(int i=0){ graph_number = i;}
    int graph_Number(int i=0){ return graph_number;}

    void erase_point(int index);

    QList<PlotPoint *> points;
    quint32 graph_count=0;
    QList<double> graph_points;

public slots:

    void on_button_erase_point();
    void minimizar_graph();
    void maximizar_graph();
    void maximizar_graph_with_other_button();
    void fix_Axis();

    void maximize(QPoint maximized_pos);
    void minimize();

signals:

    void shiftStateChanged(bool);
    void maximize_graph_signal(int);
    void minimize_graph_signal(int);

protected:

    bool event(QEvent *event);

private slots:

    void stop_Moving_Point_Event(QPointF pos);

    void on_Drag_timer_timeout();

    void on_Zoom_timer_timeout();

private:

    bool gestureEvent(QGestureEvent *event);
    bool moveGestureEvent(QMouseEvent *event);
    bool releaseGestureEvent(QMouseEvent *event);

    void tap_Triggered(QTapGesture *gesture);
    void tap_hold_Triggered(QTapAndHoldGesture *gesture);
    void pinch_Triggered(QPinchGesture *gesture);

private:

    //PlotPoint *mPointUnderCursor;
    QWidget *background_blur;
    QTimer drag_Timer;
    QTimer zoom_Timer;

    bool is_First_Move = true;
    bool is_First_Pinch = true;

    QPointF last_tap_hold_pos = QPoint(0,0);
    QPointF first_pinch_center_pos = QPoint(0,0);
    qreal scaleFactor_in_Pinch = 0;
    QPoint first_move_center_pos = QPoint(0,0);

    QPoint drag_delta = QPoint(0,0);

    bool is_Draging = false;
    bool is_Zooming = false;

    bool is_Zoom = false;

    quint8 mRadio_points = 10;

    QLabel_Button *button_maximized_erase_point;
    QLabel_Button *button_maximized;
    QLabel_Button *button_minimized;
    QLabel_Button *button_fix_Axis;
    QLabel_Button *button_maximized_with_other;

    bool isMaximized = false;

    QCPRange x_axis_initial_range;
    QCPRange y_axis_initial_range;

    QCPRange x_axis_range;
    QCPRange y_axis_range;

    bool isFirtsPos = false;

    QPoint m_pos;
    QPoint maximized_pos;
    QPoint maximized_pos_with_other_maximize;

    QSize m_size;
    QSize maximize_size;

    Plot *other_graph1;
    Plot *other_graph2;
    bool is_moving_point = false;
    qint32 last_moving_point_pos_in_list=-1;
    QPointF last_point_after_moving;
    bool mIsEKG_Graph = false;

    int graph_number=0;
};

#endif // PLOT_H
