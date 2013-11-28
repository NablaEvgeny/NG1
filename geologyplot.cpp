#include "geologyplot.h"

#include <qapplication.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QMessageBox>

class CurveData: public QwtArraySeriesData<QPointF>
{
public:
    CurveData()
    {
    }

    virtual QRectF boundingRect() const
    {
        if (d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this);
        return d_boundingRect;
    }

    inline void appendDataPoint( const QPointF &point)
    {
        d_samples += point;
    }

    void clear ()
    {
        d_samples.clear();
        d_samples.squeeze();
        d_boundingRect = QRectF(0.0, 0.0, -1.0, -1.0);

    }
};


GeologyPlot::GeologyPlot( QWidget *parent ):
    QwtPlot( parent )
{
    counter = 0;
    painter = new QwtPlotDirectPainter(this);

    setTitle( "Plot Demo" );
    setCanvasBackground( Qt::white );
    this->setAxisScale(QwtPlot::xBottom, -1, 1);
    this->setAxisScale(QwtPlot::yLeft, 0, 1);
//    setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
 //   setAxisScale( QwtPlot::xBottom, 0.0, 10.0 );
    insertLegend( new QwtLegend() );

   // grid = new QwtPlotGrid();
   // grid->attach( this );

    curve = new QwtPlotCurve();
    curve->setTitle( "Some Points" );
   // curve->setPen( Qt::blue, 4 ),
   // curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    /*
    symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve->setSymbol( symbol );
    */

    curve->setStyle(QwtPlotCurve::NoCurve);
    curve->setData( new CurveData());
    curve->setSymbol( new QwtSymbol(QwtSymbol::Ellipse, Qt::NoBrush,
                                    QPen(Qt::red,2),QSize(8,8)));

    curve->attach(this);
    setAutoReplot(false);
    setData();
}

void GeologyPlot::setData()
{
    const int n = 1000;
    double h = 2.0/n;

    for (int i = 0; i < n; i++)
    {
        x[i] = -1 + i * h;
        y[i] = qAbs(x[i]);
    }
}
GeologyPlot::~GeologyPlot()
{
    delete painter;
    delete curve;
}

void GeologyPlot::timerHandle()
{
    QPointF newPoint = QPointF( this->x[this->counter],this->y[this->counter]);
    this->counter++;
    GeologyPlot::appendGraphPoint(newPoint);
}

void GeologyPlot::appendGraphPoint(QPointF point)
{
    CurveData *data = static_cast<CurveData *> ( curve->data());
    data->appendDataPoint(point);
    painter->drawSeries(curve, 0, data->size() - 1);
}

void GeologyPlot::drawPlot( )
{

    points << QPointF( 0.0, 4.4 ) << QPointF( 1.0, 3.0 )
        << QPointF( 2.0, 4.5 ) << QPointF( 3.0, 6.8 )
        << QPointF( 4.0, 7.9 ) << QPointF( 5.0, 7.1 );

    curve->setSamples( points );
    curve->attach( this );

   // resize( 600, 400 );

    return ;
}

void GeologyPlot::SetTmpfile(const QString &f)
{
   tmpfile = f;
   file.setFileName(tmpfile);
}
QString GeologyPlot::GetTmpfile()
{
   return tmpfile;
}

void GeologyPlot::resizeEvent( QResizeEvent *event )
{
    QwtPlot::resizeEvent( event );

    // Qt 4.7.1: QGradient::StretchToDeviceMode is buggy on X11
//    updateGradient();
}

