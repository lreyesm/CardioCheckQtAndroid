#include "plotpoint.h"

PlotPoint::PlotPoint(QCustomPlot *parentPlot, int halfSize, QString text)
    : QCPItemEllipse(parentPlot)
    , mText(new QCPItemText(parentPlot))
    , mText_Point_Volts(new QCPItemText(parentPlot))
    , mCenterTracer(new QCPItemTracer(parentPlot))
    , mGripDelta()
    , mInitialPos()
    , mLastWantedPos()
    , mMoveTimer(new QTimer(this))
    , mCurWantedPosPx()
{

    mCenterTracer->setStyle(QCPItemTracer::tsNone);

    topLeft->setParentAnchor(mCenterTracer->position);
    bottomRight->setParentAnchor(mCenterTracer->position);
    topLeft->setType(QCPItemPosition::ptAbsolute);
    bottomRight->setType(QCPItemPosition::ptAbsolute);

    topLeft->setCoords(-halfSize, -halfSize);
    bottomRight->setCoords(halfSize, halfSize);


    setSelectable(true); // plot moves only selectable points, see Plot::mouseMoveEvent
    setColor(QColor(qrand()%256, qrand()%256, qrand()%256, 255));
    setPen(QPen(Qt::black));
    setSelectedPen(QPen(Qt::black, 3));

    mMoveTimer->setInterval(40); // 25 FPS
    connect(mMoveTimer, SIGNAL(timeout()), this, SLOT(moveToWantedPos()));

    if(text != ""){
        mText->setText(text);
        mText->setVisible(true);
        mText->setColor(QColor(Qt::white));
        mText->setFont(QFont("Times",13,QFont::Bold));

        text = QString::number(  (int)( this->pos().y() )  )+ " %";

        mText_Point_Volts->setText(text);
        mText_Point_Volts->setVisible(true);
        mText_Point_Volts->setColor(QColor(Qt::white));
        mText_Point_Volts->setFont(QFont("Times",14,QFont::Bold));
    }
    else{
        mText->setVisible(false);
        mText_Point_Volts->setVisible(false);
    }
    mBracket_y_position = (int)(parentPlot->yAxis->range().upper / 5);
}

PlotPoint::~PlotPoint()
{
    mText_Point_Volts->deleteLater();
    mBracket_Text->deleteLater();
    mBracket->deleteLater();
    mText->deleteLater();
    this->deleteLater();

}

QPointF PlotPoint::pos() const
{
    return mCenterTracer->position->coords();
}

const QColor &PlotPoint::color() const
{
    return brush().color();
}

void PlotPoint::setColor(const QColor& color)
{
    setBrush(color);
    setSelectedBrush(color);
}


void PlotPoint::startMoving(const QPointF &mousePos, bool shiftIsPressed)
{
    mGripDelta.setX(parentPlot()->xAxis->coordToPixel(mCenterTracer->position->key()) - mousePos.x());
    mGripDelta.setY(parentPlot()->yAxis->coordToPixel(mCenterTracer->position->value()) - mousePos.y());

    mInitialPos = pos();
    mLastWantedPos = mInitialPos;
    mCurWantedPosPx = QPointF();
    mIsChangingOnlyOneCoordinate = shiftIsPressed;

    mMoveTimer->start();

    QCPItemStraightLine *horizontal = new QCPItemStraightLine(parentPlot());
    horizontal->setAntialiased(false);
    horizontal->point1->setCoords(mInitialPos.x(), mInitialPos.y());
    horizontal->point2->setCoords(mInitialPos.x() + 1, mInitialPos.y());
    parentPlot()->addItem(horizontal);

    QCPItemStraightLine *vertical = new QCPItemStraightLine(parentPlot());
    vertical->setAntialiased(false);
    vertical->point1->setCoords(mInitialPos.x(), mInitialPos.y());
    vertical->point2->setCoords(mInitialPos.x(), mInitialPos.y() + 1);
    parentPlot()->addItem(vertical);


    static const QPen linesPen(Qt::darkGray, 0, Qt::DashLine);
    horizontal->setPen(linesPen);
    vertical->setPen(linesPen);

    mHelperItems << vertical << horizontal;

    if (!mIsChangingOnlyOneCoordinate) {
        vertical->setVisible(false);
        horizontal->setVisible(false);
    }

    connect(parentPlot(), SIGNAL(mouseMove(QMouseEvent*)),
            this, SLOT(onMouseMove(QMouseEvent*)));

    connect(parentPlot(), SIGNAL(mouseRelease(QMouseEvent*)),
            this, SLOT(stopMoving()));

    connect(parentPlot(), SIGNAL(shiftStateChanged(bool)),
            this, SLOT(onShiftStateChanged(bool)));

    //parentPlot()->grabKeyboard(); //en android no soporta el teclado

    //QApplication::setOverrideCursor(Qt::ClosedHandCursor);
}

void PlotPoint::add_Bracket(QPointF pos)
{
    mBracket = new QCPItemBracket(this->parentPlot());
    mBracket->left->setCoords(this->pos().x(), mBracket_y_position);
    mBracket->right->setCoords(pos.x(), mBracket_y_position);
    mBracket->setStyle(QCPItemBracket::bsSquare);
    mBracket->setLength(20);
    mBracket->setPen(QPen(Qt::white));

    mBracket_Text = new QCPItemText(this->parentPlot());
    mBracket_Text->setVisible(true);
    mBracket_Text->setFont(QFont("Times",10,QFont::Normal));
    mBracket_Text->position->setParentAnchor(mBracket->center);
    mBracket_Text->position->setCoords(0, 10);


    if(isEKG_Graph_point()){
        mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - pos.x() ) ) * 4 )) + " ms");
        mText_Point_Volts->setText(QString::number(  ( this->pos().y()/4096 )*3, 'g', 3  ) + " mV");
    }
    else{
        mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - pos.x() ) ) * 16 )) + " ms");
        mText_Point_Volts->setText(QString::number(  (int)( this->pos().y() )  )+ " %");
    }

    mBracket_Text->setColor(QColor(Qt::white));

    mBracket_last_left_position = pos;

}

void PlotPoint::set_Bracket_visible(bool on){

    if(mBracket != NULL && mBracket_Text != NULL){

        mBracket->setSelectable(on);
        mBracket->setVisible(on);

        mBracket_Text->setSelectable(on);
        mBracket_Text->setVisible(on);
    }
}

void PlotPoint::set_Point_visible(bool on){

    if(mText != NULL && mText_Point_Volts != NULL ){
        this->setVisible(false);
        mText->setVisible(false);
        mText_Point_Volts->setVisible(false);
        set_Bracket_visible(false);
    }
}

void PlotPoint::move_Bracket_right(QPointF pos)
{
    if(mBracket != NULL && mBracket_Text!= NULL && mText_Point_Volts!=NULL){
        mBracket->right->setCoords(pos.x(), mBracket_y_position);

        if(isEKG_Graph_point()){

            mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - pos.x() ) ) * 4 )) + " ms");
            mText_Point_Volts->setText(QString::number(  ( this->pos().y()/4096 )*3, 'g', 3   ) + " mV");
        }
        else{
            mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - pos.x() ) ) * 16 )) + " ms");
            mText_Point_Volts->setText(QString::number(  (int)( this->pos().y() )  )+ " %");
        }
        mBracket_last_left_position = pos;
    }
}

void PlotPoint::move_Bracket_left()
{
    if(mBracket != NULL && mBracket_Text!= NULL && mText_Point_Volts!=NULL){
        mBracket->left->setCoords(this->pos().x(), mBracket_y_position);

        if(isEKG_Graph_point()){

            mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - mBracket_last_left_position.x() ) ) * 4 )) + " ms");
            mText_Point_Volts->setText(QString::number(  ( this->pos().y()/4096 )*3, 'g', 3   ) + " mV");
        }
        else{
            mBracket_Text->setText(QString::number(  (int)((qAbs( this->pos().x() - mBracket_last_left_position.x() ) ) * 16 )) + " ms");
            mText_Point_Volts->setText(QString::number(  (int)( this->pos().y() )  )+ " %");

        }
    }
}

void PlotPoint::setVisible(bool on)
{
    if(this != NULL){
        setSelectable(on);  // we are movable only when visible
        QCPItemEllipse::setVisible(on);
    }


    if(mText != NULL){
        mText->setSelectable(on);
        mText->setVisible(on);
    }
    if(mText_Point_Volts != NULL){
        mText_Point_Volts->setSelectable(on);
        mText_Point_Volts->setVisible(on);
    }

    if(mBracket != NULL){
        mBracket->setSelectable(on);
        mBracket->setVisible(on);
    }

    if(mBracket_Text != NULL){
        mBracket_Text->setSelectable(on);
        mBracket_Text->setVisible(on);
    }

}

void PlotPoint::stopMoving()
{
    disconnect(parentPlot(), SIGNAL(mouseMove(QMouseEvent*)),
               this, SLOT(onMouseMove(QMouseEvent*)));

    disconnect(parentPlot(), SIGNAL(mouseRelease(QMouseEvent*)),
               this, SLOT(stopMoving()));

    disconnect(parentPlot(), SIGNAL(shiftStateChanged(bool)),
               this, SLOT(onShiftStateChanged(bool)));

    mMoveTimer->stop();
    moveToWantedPos();

    if (!mHelperItems.isEmpty()) {
        while (!mHelperItems.isEmpty()) {
            QCPAbstractItem *item = mHelperItems.takeFirst();
            mParentPlot->removeItem(item);
        }

        mParentPlot->replot();
    }

    //parentPlot()->releaseKeyboard(); //en android no soporta el teclado
    //QApplication::restoreOverrideCursor(); //en android no soporta el cursor

    last_position = pos();

    if (!mIsChangingOnlyOneCoordinate) {
        emit stoppedMoving(pos());
    }
}

void PlotPoint::move(double x, double y, bool signalNeeded)
{
    mLastWantedPos.setX(x);
    mLastWantedPos.setY(y);
    if (mIsChangingOnlyOneCoordinate) {
        double x1 = parentPlot()->xAxis->coordToPixel(x);
        double x2 = parentPlot()->xAxis->coordToPixel(mInitialPos.x());
        double y1 = parentPlot()->yAxis->coordToPixel(y);
        double y2 = parentPlot()->yAxis->coordToPixel(mInitialPos.y());
        if (qAbs(x1 - x2) < qAbs(y1 - y2)) {
            x = mInitialPos.x();
        } else {
            y = mInitialPos.y();
        }
    }

    //mCenterTracer->position->setCoords(x, y);

    //parentPlot()->replot();

    if(signalNeeded) {
        emit moved(QPointF(x, y));
        last_position = QPointF(x, y);
    }
}

void PlotPoint::movePx(double x, double y)
{
    move(parentPlot()->xAxis->pixelToCoord(x),
         parentPlot()->yAxis->pixelToCoord(y));
    mText->position->setCoords(parentPlot()->xAxis->pixelToCoord(x),
                               parentPlot()->yAxis->pixelToCoord(y));

    mText_Point_Volts->position->setCoords(parentPlot()->xAxis->pixelToCoord(x),
                                           parentPlot()->yAxis->pixelToCoord(y)+ mText_Point_Volts_plus_y_pos);

    mCenterTracer->position->setCoords( mText->position->coords());

    move_Bracket_left();

    parentPlot()->replot();
}

void PlotPoint::set_Position(QPointF pos) //pone la posicion con las coordenadas recibidas(no los pixeles)
{
    move(pos.x(),pos.y());

    mText->position->setCoords(pos.x(),pos.y());

    mText_Point_Volts->position->setCoords(pos.x(),pos.y() + mText_Point_Volts_plus_y_pos);

    mCenterTracer->position->setCoords( mText->position->coords());

    move_Bracket_left();

    last_position = pos;
}

void PlotPoint::set_Position(double x, double y) //pone la posicion con las coordenadas recibidas(no los pixeles)
{
    move(x,y);

    mText->position->setCoords(x,y);

    mText_Point_Volts->position->setCoords(x, y + mText_Point_Volts_plus_y_pos);

    mCenterTracer->position->setCoords( mText->position->coords());

    move_Bracket_left();

    last_position = QPointF(x,y);
}

void PlotPoint::set_Is_EKG_graph_point(bool on)
{
    QPointF pos = this->pos();
    mIs_EKG_graph_point = on;

    mText_Point_Volts_plus_y_pos = -400;

    mText_Point_Volts->setText(QString::number(  ( pos.y()/4096 )*3, 'g', 3) + " mV");

    mText_Point_Volts->position->setCoords(pos.x(), pos.y() + mText_Point_Volts_plus_y_pos);
}

void PlotPoint::setActive(bool isActive)
{
    setSelected(isActive);
    emit (isActive ? activated() : disactivated());
}

void PlotPoint::onMouseMove(QMouseEvent *event)
{
    mCurWantedPosPx = QPointF(event->localPos().x() + mGripDelta.x(),
                              event->localPos().y() + mGripDelta.y());
}

void PlotPoint::moveToWantedPos()
{
    if (!mCurWantedPosPx.isNull()) {
        movePx(mCurWantedPosPx.x(), mCurWantedPosPx.y());
        mCurWantedPosPx = QPointF();
    }
}

void PlotPoint::onShiftStateChanged(bool shiftPressed)
{
    if (shiftPressed != mIsChangingOnlyOneCoordinate) {
        mIsChangingOnlyOneCoordinate = shiftPressed;
        foreach (QCPAbstractItem *item, mHelperItems) {
            item->setVisible(shiftPressed);
        }
        move(mLastWantedPos.x(), mLastWantedPos.y());
    }
}

