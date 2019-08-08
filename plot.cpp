#include "plot.h"
#include <QDebug>

Plot::Plot(QWidget *parent, int radio_point)
    :QCustomPlot(parent)
{

    this->setParent(parent);

    mRadio_points = radio_point;

    setSelectionTolerance(radio_point*2);
}

Plot::~Plot()
{
    this->deleteLater();
}

void Plot::testing(){

    this->setFixedSize(1000, 300);
}

void Plot::setup_Graph(){

    button_maximized_help = new QLabel_Button((QOpenGLWidget*)this);
    button_maximized_help->setFixedSize(100,100);
    button_maximized_help->move(500,5);
    button_maximized_help->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_maximized_help->setPixmap(QPixmap(":/icons/maximize_graph.png"));
    button_maximized_help->setAlignment(Qt::AlignTop| Qt::AlignRight);
    button_maximized_help->show();

    button_maximized = new QLabel_Button((QOpenGLWidget*)this);
    button_maximized->setFixedSize(100,100);
    button_maximized->move(625,5);
    button_maximized->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_maximized->setPixmap(QPixmap(":/icons/maximize_graph.png"));
    button_maximized->setAlignment(Qt::AlignTop| Qt::AlignRight);
    button_maximized->hide();
    //button_maximized->show();

    button_minimized = new QLabel_Button((QOpenGLWidget*)this);
    button_minimized->setFixedSize(100,100);
    button_minimized->move(980,10);
    //button_minimized->move(525,10);
    button_minimized->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_minimized->setPixmap(QPixmap(":/icons/minimize_graph.png"));
    button_minimized->setAlignment(Qt::AlignTop | Qt::AlignRight);
    button_minimized->hide();

    button_fix_Axis = new QLabel_Button((QOpenGLWidget*)this);
    button_fix_Axis->setFixedSize(100,100);
    button_fix_Axis->move(980,190);
    //button_fix_Axis->move(625,40);
    button_fix_Axis->setStyleSheet(QStringLiteral("border-image: url(:/icons/fondo_transparente.png); background-image: url(:/icons/fondo_transparente.png);"));
    button_fix_Axis->setPixmap(QPixmap(":/icons/fix_graph_zoom.png"));
    button_fix_Axis->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    button_fix_Axis->hide();
    //button_maximized->show();

    //QObject::connect(button_maximized_help,SIGNAL(leftClicked()),this,SLOT(testing()));
    QObject::connect(button_maximized,SIGNAL(leftClicked()),this,SLOT(maximizar_graph()));
    QObject::connect(button_minimized,SIGNAL(leftClicked()),this,SLOT(minimize()));
    QObject::connect(button_fix_Axis,SIGNAL(leftClicked()),this,SLOT(fix_Axis()));


    QVector<double> time_x_axis(100),concentration_y_axis(100);

    for(int i=0; i< 100; i++){
        time_x_axis[i]=0;
        concentration_y_axis[i]=0;

    }
    this->addGraph();
    this->graph(0)->setData(time_x_axis,concentration_y_axis);

    this->xAxis->setVisible(false);
    this->yAxis->setVisible(false);

    this->xAxis->setTickLabelRotation(60);

    this->xAxis->setTickLength(0, 4);

    this->setBackground(QBrush(QColor(Qt::black)));
    //this->setBackground(QBrush(QColor(Qt::white)));

    this->setAutoFillBackground(true);

    this->setPlottingHints(QCP::phFastPolylines | QCP::phCacheLabels /*|QCP::phForceRepaint*/);
    this->setAntialiasedElements(QCP::aeNone);

    //Con esto se puede modificar el zoom vertical u horizontal
    //this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);

    this->setInteractions(QCP::iRangeZoom);
}

void Plot::enable_maximize_button(bool on){ //muestra boton para maximizar

    if(on){

        button_maximized->show();
        button_fix_Axis->hide();
        button_minimized->hide();
    }
    else{

        button_maximized->hide();
        button_fix_Axis->show();
        button_minimized->show();
    }
}

void Plot::set_Interactions_in_graph(bool on){

    if(on){

        //Solo para version android-----------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------------------------------------
        this->grabGesture(Qt::TapGesture);
        this->grabGesture(Qt::TapAndHoldGesture);
        //this->grabGesture(Qt::SwipeGesture);
        this->grabGesture(Qt::PinchGesture);
        //this->grabGesture(Qt::PanGesture);
        //------------------------------------------------------------------------------------------------------------------------

        PlotPoint *point = new PlotPoint(this,2,"");
        point->setColor(QColor(255,255,255));

        point->set_Item_index_in_list(0);

        point->setSelectable(false);

        points.append(point);
        this->addItem(point);

        points.first()->setVisible(true);
        //this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

        QObject::connect(&drag_Timer,SIGNAL(timeout()),this,SLOT(on_Drag_timer_timeout()));
        QObject::connect(&zoom_Timer,SIGNAL(timeout()),this,SLOT(on_Zoom_timer_timeout()));

    }
    else{

        //Solo para version android-----------------------------------------------------------------------------------------------
        //------------------------------------------------------------------------------------------------------------------------
        this->ungrabGesture(Qt::TapGesture);
        this->ungrabGesture(Qt::TapAndHoldGesture);
        //this->ungrabGesture(Qt::SwipeGesture);
        this->ungrabGesture(Qt::PinchGesture);
        //this->ungrabGesture(Qt::PanGesture);
        //------------------------------------------------------------------------------------------------------------------------

        this->setInteractions(0);
    }
}

void Plot::clear_Data(){

    for(qint16 i=0; i<this->graphCount(); i++){
        this->graph(i)->data()->clear();
    }
    this->xAxis->setRange(x_axis_initial_range);
    graph_count=0;
    graph_points.clear();
    this->replot();///*QCustomPlot::rpHint*/);
}

void Plot::add_Data(quint8 graph_i, quint32 x, quint32 y)
{
    if(graph_points.length() > x_axis_Range().upper){
        graph_points.clear();
    }
    if(graph_i==0){
        graph_count = x;
        graph_points.append(y);
    }
    this->graph(graph_i)->addData(x,y);
}

void Plot::add_Data(quint8 graph_i, QVector<double> x_vector, QVector<double> y_vector)
{
    if(graph_points.length() > x_axis_Range().upper){
        graph_points.clear();
    }
    if(graph_i==0){
        graph_count = x_vector.first();

        for(quint16 i=0; i< y_vector.length();i++){
            graph_points.append(y_vector[i]);
        }
    }
    this->graph(graph_i)->addData(x_vector,y_vector);
}

void Plot::add_Data(quint8 graph_i, QVector<double> y_vector)
{
    clear_Data();

    if(graph_i==0){

        QVector<double> x_vector;
        x_vector.clear();
        for(quint16 i=0; i< y_vector.length();i++){
            x_vector.append(i+1);
        }
        graph_points.append(y_vector.toList());
        graph_count = x_vector.last();

        this->graph(graph_i)->addData(x_vector,y_vector);
    }
}

void Plot::show_button_maximize(bool on){ //muestra el boton plus de maximizar

    if(on){
        button_maximized_with_other->show();
        button_maximized_with_other->raise();

//        //button_maximized->show();
//        button_minimized->hide();
//        button_fix_Axis->hide();
    }
    else{

//        //button_maximized->hide();
//        button_minimized->show();
//        button_fix_Axis->show();

        button_maximized_with_other->hide();
    }
}

void Plot::set_button_maximize_pos(bool up)
{
    if(up){
        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 200);
    }
    else{
        button_maximized_with_other->move(button_maximized_with_other->pos().x(), 500);
    }
}

void Plot::fix_Axis(){

    is_Zooming = false;
    is_Zoom = false;

    if(x_axis_range.upper <= x_axis_initial_range.upper){

        this->set_Range_x_axis(x_axis_initial_Range());
    }
    else{
        this->set_Range_x_axis(x_axis_Range());
    }
    this->set_Range_y_axis(y_axis_initial_Range());
    this->replot();///*QCustomPlot::rpHint*/);
}

void Plot::minimizar_graph(){

    isMaximized = false;
    isFirtsPos=false;

    enable_maximize_button(true);

    show_button_maximize(false);

    setFixedSize(m_size);
    move(m_pos);
    show();

    replot();
}

void Plot::maximizar_graph(){

    if(other_graph1->is_graph_Maximized() && other_graph2->is_graph_Maximized()){
        return;
    }

    isMaximized = true;

    if(other_graph1->is_graph_Maximized() || other_graph2->is_graph_Maximized()){

        if(other_graph1->pos() != maximized_pos && other_graph2->pos() != maximized_pos){
            maximize(maximized_pos);
            isFirtsPos=true;
            //this->button_fix_Axis->show();
        }
        else{
            maximize(maximized_pos_with_other_maximize);
            isFirtsPos=false;
        }
        this->show();
    }
    else{

        maximize(maximized_pos);
        other_graph1->show_button_maximize(true); //si es el primero maximizado enseño los 2 botones para maximizar otras graficas
        other_graph2->show_button_maximize(true);
    }

    if(!other_graph1->is_graph_Maximized()){

        other_graph1->setFixedSize(maximize_size);
        other_graph1->hide();

    }
    if(!other_graph2->is_graph_Maximized()){

        other_graph2->setFixedSize(maximize_size);
        other_graph2->hide();
    }

    this->parentWidget()->move(0,0);

    background_blur->setParent(this->parentWidget());

    background_blur->move(0,0);
    background_blur->stackUnder(this);

    if(other_graph1->is_graph_Maximized())
        background_blur->stackUnder(other_graph1);

    if(other_graph2->is_graph_Maximized())
        background_blur->stackUnder(other_graph2);

    background_blur->show();

    this->replot(/*QCustomPlot::rpHint*/);

}


void Plot::maximizar_graph_with_other_button(){

    maximizar_graph();
}

bool Plot::event(QEvent *event)
{
    if(!isMaximized){
        return QOpenGLWidget::event(event);
    }

    if (event->type() == QEvent::Gesture){
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    else if (event->type() == QEvent::MouseMove){
        if( !is_Zooming && !is_moving_point)
            return moveGestureEvent(static_cast<QMouseEvent*>(event));
        return QOpenGLWidget::event(event);
    }
    else if(event->type() == QEvent::MouseButtonRelease){
        if( !is_Zooming && !is_moving_point)
            return releaseGestureEvent(static_cast<QMouseEvent*>(event));
        return QOpenGLWidget::event(event);
    }
    return QOpenGLWidget::event(event);
}

bool Plot::releaseGestureEvent(QMouseEvent *event){

    if(!is_Zoom){
        is_Draging = false;
        drag_Timer.stop();
        return true;
    }

    if(!is_First_Move){

        drag_Timer.stop();

        is_First_Move = true;

        QPoint last_move_center_pos = QPoint((int)this->xAxis->pixelToCoord(event->localPos().x()), (int)this->yAxis->pixelToCoord(event->localPos().y()));

        this->xAxis->moveRange((double)(first_move_center_pos.x() - last_move_center_pos.x()));
        this->yAxis->moveRange((double)(first_move_center_pos.y() - last_move_center_pos.y()));//entre 3 para reducir el desplazamiento

        is_Draging = false;
        replot(/*QCustomPlot::rpHint*/);
    }
    return true;
}

bool Plot::moveGestureEvent(QMouseEvent *event){

    if(!is_Zoom){
        is_Draging = false;
        drag_Timer.stop();
        return true;
    }
    if(is_First_Move){
        is_First_Move=false;
        first_move_center_pos = QPoint((int)this->xAxis->pixelToCoord(event->localPos().x()), (int)this->yAxis->pixelToCoord(event->localPos().y()));

        is_Draging = true;
        drag_Timer.setInterval(40);
        drag_Timer.start();

        return true;
    }
    QPoint actual_move_center_pos = QPoint((int)this->xAxis->pixelToCoord(event->localPos().x()), (int)this->yAxis->pixelToCoord(event->localPos().y()));
    drag_delta = QPoint(first_move_center_pos.x() - actual_move_center_pos.x(), first_move_center_pos.y() - actual_move_center_pos.y());
    first_move_center_pos = actual_move_center_pos;

    return true;
}

void Plot::on_Drag_timer_timeout(){

    if(abs(drag_delta.x()) > x_axis_initial_Range().upper || abs(drag_delta.y()) > y_axis_initial_Range().upper){
        drag_Timer.stop();
        return;
    }

    this->xAxis->moveRange((double)(drag_delta.x()));
    this->yAxis->moveRange((double)(drag_delta.y()));//entre 3 para reducir el desplazamiento

    replot(/*QCustomPlot::rpHint*/);
}

bool Plot::gestureEvent(QGestureEvent *event)
{
    if (QGesture *pinch = event->gesture(Qt::PinchGesture)){
        //if(!is_Draging){
        drag_Timer.stop();
        is_Draging = false;
        is_Zooming = true;
        is_Zoom = true;
        pinch_Triggered(static_cast<QPinchGesture *>(pinch));
        //}
    }

    if (QGesture *tap = event->gesture(Qt::TapGesture)){

        if(!is_Zooming){
            tap_Triggered(static_cast<QTapGesture *>(tap));
        }
    }

    if (QGesture *tap_hold = event->gesture(Qt::TapAndHoldGesture)){

        drag_Timer.stop();
        is_Draging = false;
        tap_hold_Triggered(static_cast<QTapAndHoldGesture *>(tap_hold));
    }


    return true;
}

//expandir o contraer (zoom) //mouseWheel
void Plot::pinch_Triggered(QPinchGesture *gesture){

    QPoint centerPoint = this->mapFromGlobal(QPoint(gesture->centerPoint().x(), gesture->centerPoint().y()));

    int coord_x = (int)this->xAxis->pixelToCoord(centerPoint.x());
    int coord_y = (int)this->yAxis->pixelToCoord(centerPoint.y());

    scaleFactor_in_Pinch = 1/(gesture->lastScaleFactor());

    if(is_First_Pinch){

        first_pinch_center_pos = QPoint(coord_x, coord_y);

        is_First_Pinch=false;

        zoom_Timer.setInterval(40);
        zoom_Timer.start();
    }

    if (gesture->state() == Qt::GestureFinished){

        zoom_Timer.stop();

        is_Zooming = false;
        this->xAxis->scaleRange(scaleFactor_in_Pinch, first_pinch_center_pos.x());
        this->yAxis->scaleRange(scaleFactor_in_Pinch, first_pinch_center_pos.y());

        this->replot(/*QCustomPlot::rpHint*/);
        is_First_Pinch=true;
    }
}

void Plot::on_Zoom_timer_timeout(){

    this->xAxis->scaleRange(scaleFactor_in_Pinch, first_pinch_center_pos.x());
    this->yAxis->scaleRange(scaleFactor_in_Pinch, first_pinch_center_pos.y());

    replot(/*QCustomPlot::rpHint*/);
}

//mouse doubleclick
void Plot::tap_hold_Triggered(QTapAndHoldGesture *gesture)
{
    is_moving_point = false;

    //QPointF actual_tap_pos = QPointF(this->mapFromGlobal(QPoint((int)gesture->hotSpot().x(),(int)gesture->hotSpot().y())));
    QPointF actual_tap_pos = gesture->position() - QPointF(this->pos()); //misma funcion que mapFromGlobal

    if(last_tap_hold_pos != actual_tap_pos){
        last_tap_hold_pos = actual_tap_pos;
    }
    else{ return;}

    PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(last_tap_hold_pos, true));

    if(plotPoint == 0){

        PlotPoint *point = new PlotPoint(this, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );
        PlotPoint *point_other_graph1 = new PlotPoint(other_graph1, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );
        PlotPoint *point_other_graph2 = new PlotPoint(other_graph2, mRadio_points, QString::number(points.isEmpty()? 0:points.last()->point_text().toInt() + 1) );

        point_other_graph1->setColor(point->color());
        point_other_graph2->setColor(point->color());

        if(isEKG_Graph()){

            point->set_Is_EKG_graph_point(true);
        }
        else if(other_graph2->isEKG_Graph()){

            point_other_graph2->set_Is_EKG_graph_point(true);
        }

        point->set_Item_index_in_list(points.length());
        point_other_graph1->set_Item_index_in_list(other_graph1->points.length());
        point_other_graph2->set_Item_index_in_list(other_graph2->points.length());

        last_moving_point_pos_in_list = points.length();

        points.append(point);
        this->addItem(point);

        other_graph1->points.append(point_other_graph1);
        other_graph1->addItem(point_other_graph1);
        other_graph2->points.append(point_other_graph2);
        other_graph2->addItem(point_other_graph2);

        set_Point_Selected(true, points.length()-1);

        double coord_x_this = this->xAxis->pixelToCoord(last_tap_hold_pos.x());
        double coord_x_other_graph1;
        double coord_x_other_graph2;

        if(isEKG_Graph()){
            coord_x_other_graph1 = coord_x_this/4;
            coord_x_other_graph2 = coord_x_this/4;
        }
        else{
            coord_x_other_graph1 = coord_x_this;
            if(other_graph2->isEKG_Graph()){
                coord_x_other_graph2 = coord_x_this*4;
            }
        }

        if(graph_points.length() > (int)coord_x_this){

            points.last()->set_Position(coord_x_this, graph_points[(int)coord_x_this]);
            other_graph1->points.last()->set_Position(coord_x_other_graph1, other_graph1->graph_points[(int)coord_x_other_graph1]);
            other_graph2->points.last()->set_Position(coord_x_other_graph2, other_graph2->graph_points[(int)coord_x_other_graph2]);
        }
        else{
            (qobject_cast<PlotPoint*>(this->item()))->movePx(last_tap_hold_pos.x(), last_tap_hold_pos.y()); //mueve el ultimo item de la lista a la posicion requerida
            (qobject_cast<PlotPoint*>(other_graph1->item()))->movePx(last_tap_hold_pos.x(), last_tap_hold_pos.y()); //mueve el ultimo item de la lista a la posicion requerida
            (qobject_cast<PlotPoint*>(other_graph2->item()))->movePx(last_tap_hold_pos.x(), last_tap_hold_pos.y()); //mueve el ultimo item de la lista a la posicion requerida
        }


        if(points.length()>1){ //si hay mas de un punto mostrar bracket

            point->add_Bracket(points.at(points.length()-2)->pos());
            points.at(points.length()-2)->set_Bracket_visible(false);

            if(isEKG_Graph()){

                point_other_graph1->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()/4,
                                                        points.at(points.length()-2)->pos().y()/40.96));
                point_other_graph2->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()/4,
                                                        points.at(points.length()-2)->pos().y()/40.96));
                other_graph1->points.at(other_graph1->points.length()-2)->set_Bracket_visible(false);
                other_graph2->points.at(other_graph2->points.length()-2)->set_Bracket_visible(false);
            }
            else{
                point_other_graph1->add_Bracket(other_graph1->points.at(other_graph1->points.length()-2)->pos());
                other_graph1->points.at(other_graph1->points.length()-2)->set_Bracket_visible(false);

                if(other_graph2->isEKG_Graph()){
                    point_other_graph2->add_Bracket(QPointF(points.at(points.length()-2)->pos().x()*4,
                                                            points.at(points.length()-2)->pos().y()*40.96));
                }
                else{
                    point_other_graph2->add_Bracket(other_graph2->points.at(other_graph2->points.length()-2)->pos());
                }
                other_graph2->points.at(other_graph2->points.length()-2)->set_Bracket_visible(false);
            }
        }

        replot();///*QCustomPlot::rpHint*/);
        other_graph1->replot();///*QCustomPlot::rpHint*/);
        other_graph2->replot();///*QCustomPlot::rpHint*/);
    }
    ///remover si dobleclick sobre punto
    else if (points.contains(plotPoint)){  //eliminar punto

        plotPoint->stopMoving();

        int index = points.indexOf(plotPoint);

        if(index +1  < points.length()){ //esconde brackets de punto siguiente

            set_Brackets_Visibles(false, index +1);
        }

        if(points.last() != points.at(index) && points.length()>1){ //Al eliminar un punto modificar la llave del siguiente con el anterior punto

            if(points.first() != points.at(index)){

                points.at(index+1)->move_Bracket_right(points.at(index-1)->pos());

                if(isEKG_Graph()){
                    other_graph1->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()/4,
                                                                                 points.at(index-1)->pos().y()/40.96));
                    other_graph2->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()/4,
                                                                                 points.at(index-1)->pos().y()/40.96));
                }
                else{
                    other_graph1->points.at(index+1)->move_Bracket_right(other_graph1->points.at(index-1)->pos());
                    if(other_graph2->isEKG_Graph()){
                        other_graph2->points.at(index+1)->move_Bracket_right(QPointF(points.at(index-1)->pos().x()*4,
                                                                                     points.at(index-1)->pos().y()*40.96));
                    }
                    else{
                        other_graph2->points.at(index+1)->move_Bracket_right(other_graph2->points.at(index-1)->pos());
                    }
                }
            }
        }
        last_moving_point_pos_in_list=-1;

        points.at(index)->set_Point_visible(false);
        other_graph1->points.at(index)->set_Point_visible(false);
        other_graph2->points.at(index)->set_Point_visible(false);


        points.removeAt(index);
        this->removeItem(index);

        other_graph1->points.removeAt(index);
        other_graph1->removeItem(index);
        other_graph2->points.removeAt(index);
        other_graph2->removeItem(index);

        for(quint32 i =index; i< points.length(); i++){

            points[i]->set_Item_index_in_list(i);
            other_graph1->points[i]->set_Item_index_in_list(i);
            other_graph2->points[i]->set_Item_index_in_list(i);
        }

        if(points.length()==1){  //Si hay un solo punto esconder brackets
            set_Brackets_Visibles(false,0);
        }
        replot();///*QCustomPlot::rpHint*/);
        other_graph1->replot();///*QCustomPlot::rpHint*/);
        other_graph2->replot();///*QCustomPlot::rpHint*/);
    }

}

//mouse click
void Plot::tap_Triggered(QTapGesture * gesture)
{
    QPoint event_pos = this->mapFromGlobal(QPoint((int)gesture->hotSpot().x(),(int)gesture->hotSpot().y()));

    PlotPoint *plotPoint = qobject_cast<PlotPoint*>(itemAt(event_pos, true));
    if(plotPoint ==0){

        //QCustomPlot::mousePressEvent(event);
    }
    else{  //mover punto seleccionado si el boton izquierdo esta apretado

        if(points.contains(plotPoint)){

            plotPoint->startMoving(event_pos,
                                   false); //falso para decir que no esta apretado el shift
            is_moving_point = true;

            int index = points.indexOf(plotPoint);

            last_moving_point_pos_in_list = index;
            last_point_after_moving = plotPoint->pos();

            QObject::connect(plotPoint, SIGNAL(stoppedMoving(QPointF)),this,SLOT(stop_Moving_Point_Event(QPointF)));
        }
    }
}

void Plot::stop_Moving_Point_Event(QPointF pos)
{
    if(is_moving_point){

        is_moving_point = false;


        if(points.length() > last_moving_point_pos_in_list && last_moving_point_pos_in_list > 0){

            set_Point_Selected(true, last_moving_point_pos_in_list);
            set_Brackets_Visibles(true, last_moving_point_pos_in_list);

            int coord_x = (int)pos.x();

            if(coord_x < graph_points.length()){
                points.at(last_moving_point_pos_in_list)->set_Position(pos.x(), graph_points[coord_x]);
            }
            else{
                points.at(last_moving_point_pos_in_list)->set_Position(pos);
            }

            if(isEKG_Graph()){

                if(other_graph1->graph_points.length() > pos.x()/4){

                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, other_graph1->graph_points[(int)(pos.x()/4)]);
                    other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, other_graph2->graph_points[(int)(pos.x()/4)]);
                }
                else{
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, pos.y()/40.96);
                    other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()/4, pos.y()/40.96);
                }
            }
            else{
                if(other_graph1->graph_points.length() > pos.x()){
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos.x(), other_graph1->graph_points[coord_x]);
                }
                else{
                    other_graph1->points[last_moving_point_pos_in_list]->set_Position(pos);
                }

                if(other_graph2->isEKG_Graph()){

                    if(other_graph2->graph_points.length() > pos.x()*4){
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()*4, other_graph2->graph_points[(int)(pos.x()*4)]);
                    }
                    else{
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x()*4, pos.y()*40.96);
                    }
                }
                else{
                    if(other_graph2->graph_points.length() > pos.x()){
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos.x(), other_graph2->graph_points[coord_x]);
                    }
                    else{
                        other_graph2->points[last_moving_point_pos_in_list]->set_Position(pos);
                    }
                }
            }

            move_Bracket_right_to_this_pos(last_moving_point_pos_in_list, pos);

            replot();///*QCustomPlot::rpHint*/);
            other_graph1->replot();///*QCustomPlot::rpHint*/);
            other_graph2->replot();///*QCustomPlot::rpHint*/);
        }
    }

}

void Plot::set_Point_Selected(bool on, int index){

    for(int i=1; i< points.length(); i++){
        points.at(i)->set_Selected(false);
        other_graph1->points.at(i)->set_Selected(false);
        other_graph2->points.at(i)->set_Selected(false);
    }
    if(points.length() > index && index > 0){

        points.at(index)->set_Selected(on);
        other_graph1->points.at(index)->set_Selected(on);
        other_graph2->points.at(index)->set_Selected(on);
    }
}


void Plot::set_Brackets_Visibles(bool on, int index){

    for(int i=1; i < points.length() ;i++){

        points.at(i)->set_Bracket_visible(false);
        other_graph1->points.at(i)->set_Bracket_visible(false);
        other_graph2->points.at(i)->set_Bracket_visible(false);
    }
    if(points.length() > index && index > 0){
        points.at(index)->set_Bracket_visible(on);
        other_graph1->points.at(index)->set_Bracket_visible(on);
        other_graph2->points.at(index)->set_Bracket_visible(on);
    }
}

//mover el estremo derecho del bracket del punto siguiente a la posicion de este
void Plot::move_Bracket_right_to_this_pos(int index, QPointF pos){

    if(points.last() != points.at(index)){  //si no el ultimo punto mover la derecha de llave del siguiente a posicion de este punto

        //set_Brackets_Visibles(true, index);

        points.at(index + 1)->move_Bracket_right(pos);

        if(isEKG_Graph()){

            other_graph1->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()/4,
                                                                           pos.y()/40.96));
            other_graph2->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()/4,
                                                                           pos.y()/40.96));
        }
        else{

            other_graph1->points.at(index + 1)->move_Bracket_right(pos);

            if(other_graph2->isEKG_Graph()){
                other_graph2->points.at(index + 1)->move_Bracket_right(QPointF(pos.x()*4,
                                                                               pos.y()*40.96));
            }
            else{
                other_graph2->points.at(index + 1)->move_Bracket_right(pos);
            }
        }
    }
}


void Plot::maximize(QPoint maximized_pos){

    set_Interactions_in_graph(true);

    enable_maximize_button(false);

    this->setFixedSize(maximize_size);
    this->move(maximized_pos);
    this->raise();

    show_button_maximize(false);

    for(int i=0; i< this->itemCount();i++){

        points[i]->setVisible(true);
        points[i]->set_Bracket_visible(false);
    }
    if(last_moving_point_pos_in_list!=-1 && last_moving_point_pos_in_list < points.length()){
        points[last_moving_point_pos_in_list]->set_Bracket_visible(true);
    }
}


void Plot::minimize(){

    isMaximized = false;

    set_Interactions_in_graph(false);

    enable_maximize_button(true);

    this->setFixedSize(m_size);
    this->move(m_pos);

    if(other_graph1->is_graph_Maximized() || other_graph2->is_graph_Maximized()){ //si hay alguno maximizado

        show_button_maximize(true);

        if(isFirtsPos){
            set_button_maximize_pos(true);
        }
        else{
            set_button_maximize_pos(false);
        }

        if(other_graph1->is_graph_Maximized()){//si esta maximizado muestro boton del otro
            other_graph2->show_button_maximize(true);
        }
        else if(other_graph2->is_graph_Maximized()){
            other_graph1->show_button_maximize(true);
        }
    }
    else{ //si no hay ninguno maximizado

        background_blur->hide();
        other_graph1->minimizar_graph();
        other_graph2->minimizar_graph();
        set_button_maximize_pos(false);
    }

    for(int i=0; i< this->itemCount();i++){

        points[i]->setVisible(false);
    }
    this->lower();
    this->stackUnder(background_blur);
}
