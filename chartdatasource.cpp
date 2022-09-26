#include "chartdatasource.h"
#include <QtMath>
#include <limits>

//-----------------------------------------------

void ChartDataSource::fillPointers(const Y_GETTING_WAY y_getting_way){

    pointers_.clear();

    for (int i{}; i < MAX_X_LIMIT; ++i)
    {
        qreal delim{ MIN_X_VALUE};
        while(delim < 1.0)
        {
            qreal x{ static_cast<qreal>(i) + delim };
            qreal y{};

            switch(y_getting_way)
            {
            case(Y_GETTING_WAY::SIN_WAY):
            {
               y = qSin(x);
               break;
            }
            case(Y_GETTING_WAY::EQUAL_WAY):
            {
                y = x;
                break;
            }
            case(Y_GETTING_WAY::TRICKY_MODULE_WAY):
            {
                y = qFabs(x - 2.5);
                break;
            }
            case(Y_GETTING_WAY::SQUARED_WAY):
            {
                y = x * x;
                break;
            }
            case(Y_GETTING_WAY::LOG_WAY):
            {
                y = qLn(x);
                break;
            }
            default: //never happens
                y = qSin(x); //let it be as default
            }

            pointers_.push_back({ x, y });
            delim += STEP;
        }
    }

    setParameterName(createParameterName(y_getting_way));

}

//-----------------------------------------------

const QString ChartDataSource::createParameterName(const Y_GETTING_WAY y_getting_way){

    QString ret_val{};

    switch(y_getting_way)
            {
            case(Y_GETTING_WAY::SIN_WAY):
            {
               ret_val = tr("синусоиды");
               break;
            }
            case(Y_GETTING_WAY::EQUAL_WAY):
            {
                ret_val = tr("равнозначных X и Y");
                break;
            }
            case(Y_GETTING_WAY::TRICKY_MODULE_WAY):
            {
                ret_val = tr("хитрого выражения");
                break;
            }
            case(Y_GETTING_WAY::SQUARED_WAY):
            {
                ret_val = tr("зависимости Y от X в квадратной степени");
                break;
            }
            case(Y_GETTING_WAY::LOG_WAY):
            {
                ret_val = tr("логарифмичeской зависимости Y от X");
                break;
            }
            default: //never happens
                ret_val = tr("сюда не попасть");
            }

    return ret_val;
}

//-----------------------------------------------

ChartDataSource::ChartDataSource(QObject *parent)
    : QObject{ parent },
      color_{ "red" },
      parameter_name_{ tr("простой зависимости Y от X") },
      y_getting_way_{ Y_GETTING_WAY::SIN_WAY }
{
    fillPointers();
}

//-----------------------------------------------

const QColor &ChartDataSource::getColor()const{
    return color_;
}

//-----------------------------------------------

void ChartDataSource::setColor(const QColor &color){
    color_ = color;

    emit colorChanged();
}


//-----------------------------------------------

const QString &ChartDataSource::getParameterName()const{
    return parameter_name_;
}

//-----------------------------------------------

void ChartDataSource::setParameterName(const QString& name){
    parameter_name_ = name;

    emit parameterNameChanged();
}

//-----------------------------------------------

ChartDataSource::Y_GETTING_WAY ChartDataSource::getYGettingWay()const{
    return y_getting_way_;
}

//-----------------------------------------------

void ChartDataSource::setYGettingWay(const Y_GETTING_WAY y_getting_way){
    y_getting_way_ = y_getting_way;
    fillPointers(y_getting_way_);

    emit yGettingWayChanged();
}

//-----------------------------------------------

void ChartDataSource::changeYGettingWay(){
    int current_way = static_cast<int>(y_getting_way_);

    current_way++;
    if (current_way > 4)
        current_way = 0;

    Y_GETTING_WAY new_way = static_cast<Y_GETTING_WAY>(current_way);
    setYGettingWay(new_way);
}

//-----------------------------------------------

int ChartDataSource::getPointersSize()const{
    return pointers_.size();
}

//-----------------------------------------------

qreal ChartDataSource::getX(const int index){
    return pointers_[index].rx();
}

//-----------------------------------------------

qreal ChartDataSource::getY(const int index){
    return pointers_[index].ry();
}

//-----------------------------------------------

