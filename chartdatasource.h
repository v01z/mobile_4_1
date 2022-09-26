#ifndef CHARTDATASOURCE_H
#define CHARTDATASOURCE_H

#include <QObject>
#include <QColor>
#include <QPointF>

//-----------------------------------------------

constexpr int MAX_X_LIMIT{ 5 };
constexpr qreal MIN_X_VALUE{ 0.0 };
constexpr qreal STEP{ 0.1 };

//-----------------------------------------------

class ChartDataSource : public QObject
{
    Q_OBJECT
private:

    enum class Y_GETTING_WAY {
        SIN_WAY, EQUAL_WAY, TRICKY_MODULE_WAY, SQUARED_WAY, LOG_WAY
    };


    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged)
    QColor color_;

    Q_PROPERTY(QString parameter_name READ getParameterName WRITE
               setParameterName NOTIFY parameterNameChanged)
    QString parameter_name_;

    Q_PROPERTY(Y_GETTING_WAY y_getting_way READ getYGettingWay WRITE
               setYGettingWay NOTIFY yGettingWayChanged)
    Y_GETTING_WAY y_getting_way_;

    QVector<QPointF> pointers_;


    const QColor &getColor() const;
    void setColor(const QColor&);


    void fillPointers(const Y_GETTING_WAY y_getting_way = Y_GETTING_WAY::SIN_WAY);

    const QString createParameterName(const Y_GETTING_WAY);
    const QString &getParameterName()const;
    void setParameterName(const QString&);


    Y_GETTING_WAY getYGettingWay()const;
    void setYGettingWay(const Y_GETTING_WAY);

public:
    explicit ChartDataSource(QObject *parent = nullptr);

    Q_INVOKABLE void changeYGettingWay();
    Q_INVOKABLE int getPointersSize() const;
    Q_INVOKABLE qreal getX(const int);
    Q_INVOKABLE qreal getY(const int);

signals:
    void colorChanged();
    void parameterNameChanged();
    void yGettingWayChanged();
};

//-----------------------------------------------

#endif // CHARTDATASOURCE_H
