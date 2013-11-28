#ifndef SIMPLEPLOT_H
#define SIMPLEPLOT_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_plot_directpainter.h>
#include <QFile>

namespace Ui {
class SimplePlot;
}


class SimplePlot : public QwtPlot
{
public:
    SimplePlot( QWidget *parent = NULL );
    ~SimplePlot();

    void SetTmpfile(const QString &f);
    QString GetTmpfile();

public slots:
    void timerHandle();
    void drawPlot();
    void addPoint();

private:
    QwtPlotCurve *curve;
    QwtPlotDirectPainter *painter;

    QwtPlotGrid *grid;

    QwtSymbol *symbol;
    QPolygonF points;


    QString tmpfile;
    QFile file;

    void setData();
    void appendGraphPoint(QPointF point);
    int counter;

    double x[1000];
    double y[1000];

protected:
    virtual void resizeEvent( QResizeEvent * );




};

#endif // SIMPLEPLOT_H
