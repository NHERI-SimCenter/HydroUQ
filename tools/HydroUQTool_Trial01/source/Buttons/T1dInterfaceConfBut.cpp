//*****************************************************************************
// Button to accept the interface data
//*****************************************************************************

#include "../mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QMessageBox>
#include <QFileDialog>
#include <QUrl>

void MainWindow::on_InterfaceConfBut_clicked()
{
    if(ui->Interface_type->currentIndex() == 0) //Title selected
    {
        QMessageBox msgbox;
        msgbox.setText("Error! File format type not selected!");
        msgbox.exec();
    }
    else if(ui->Interface_type->currentIndex() == 1) //SimCenter format selected
    {
        QMessageBox msgbox;
        msgbox.setText("Sorry! This option is not available yet");
        msgbox.exec();
    }
    else if(ui->Interface_type->currentIndex() == 2) //Two points selected
    {
        QMessageBox msgbox;
        msgbox.setText("Sorry! This option is not available yet");
        msgbox.exec();
    }
    else if(ui->Interface_type->currentIndex() == 3) //Slope and interface selected
    {
        // Get the value of slope
        QString slope = ui->Slope_textEdit->toPlainText();
        QStringList slopeSL = slope.split(" ");
        slopeval = QString(slopeSL[0]).toDouble();

        // Get the value of the intercept
        QString intercept = ui->Intercept_textEdit->toPlainText();
        QStringList interceptSL = intercept.split(" ");
        interceptval = QString(interceptSL[0]).toDouble();

        // Get the two end points
        QVector<double> x1(2),y1(2);
        x1[0] = xmin; x1[1] = xmax;
        y1[0] = slopeval*x1[0]+interceptval;
        y1[1] = slopeval*x1[1]+interceptval;

        //QTextStream out(stdout);
        //out << "Arrived here-x"<< slopeval << "," << intercept << endl;

        // Mid point
        double xmid = xmin + 0.5*abs(xmax-xmin);
        double ymid = slopeval*xmid+interceptval;
        //double ymid = ymin + 0.5*abs(ymax-ymin);
        double x75 = xmin + 0.55*abs(xmax-xmin);
        double y75rel = ymin;
        if(abs(slopeval) > 1e-6)
        {
            y75rel = (1/slopeval)*(slopeval*ymid - x75 + xmid);
        }
        else
        {
            x75 = xmid;
            y75rel = ymid - 0.2*abs(ymid-ymin);
        }

        if(ui->FlipDomain->isChecked())
        {
            // Plot the line
            ui->Bathymetry->addGraph();
            ui->Bathymetry->graph(0)->setData(x1,y1);
            QPen blueDotPen;
            blueDotPen.setColor(QColor(30, 40, 255, 150));
            blueDotPen.setStyle(Qt::DotLine);
            blueDotPen.setWidthF(8);
            ui->Bathymetry->graph(0)->setPen(blueDotPen);
            ui->Bathymetry->replot();

            // Add the arrow
            QCPItemLine *arrow = new QCPItemLine(ui->Bathymetry);
            arrow->start->setCoords(xmid,ymid);
            arrow->end->setCoords(x75,y75rel);
            arrow->setHead(QCPLineEnding::esSpikeArrow);
            ui->Bathymetry->replot();
        }
        else
        {
            // Plot the line
            ui->Bathymetry->addGraph();
            ui->Bathymetry->graph(0)->setData(x1,y1);
            QPen blueDotPen;
            blueDotPen.setColor(QColor(30, 40, 255, 150));
            blueDotPen.setStyle(Qt::DotLine);
            blueDotPen.setWidthF(8);
            ui->Bathymetry->graph(0)->setPen(blueDotPen);
            ui->Bathymetry->replot();

            // Add the arrow
            QCPItemLine *arrow = new QCPItemLine(ui->Bathymetry);
            arrow->start->setCoords(xmid,ymid);
            arrow->end->setCoords(x75,ymax-y75rel);
            arrow->setHead(QCPLineEnding::esSpikeArrow);
            ui->Bathymetry->replot();
        }

        //QTextStream out(stdout);
        //out << "Current index: "<< ui->BathType->currentIndex() << endl;

        // FInally, lock all items
        ui->Interface_box->setEnabled(false);
        ui->Tab1Accept->setEnabled(true);
    }
}
