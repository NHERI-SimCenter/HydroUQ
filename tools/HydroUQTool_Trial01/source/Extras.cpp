    /*QFile SCbathfile(bathfilename);
    if(SCbathfile.open(QIODevice::ReadOnly))
    {

        // Create file streams
        QTextStream inp(&bathfilename);

        // Get total number of points and data at no-value
        //inp >> tpoints >> nodatavalue;

        QString line = inp.readLine();
        QString line2 = inp.readLine();

        // Resize to total number of points
        //Zdata.resize(tpoints);

        // Temporary: Remove later
        QTextStream out(stdout);
        out << QString::number(tpoints) << "," << QString::number(nodatavalue) << bathfilename << line << line2 << endl;


        while (!inp.atEnd())
        {
            QString line = inp.readLine();
            out << line << endl;
        }

        SCbathfile.close();
    }*/

    /*
    // Read the file with the topography data
        nx = 50;
        ny = 50;
        xmin = -1;
        xmax = 1;
        ymin = -1;
        ymax = 1;

        std::vector<double> xd(9),yd(9);
        xd[0] = -1; xd[1] = -0.75; xd[2] = -0.5;xd[3] = -0.25;xd[4] = 0;xd[5] = 0.25;xd[6] = 0.5;xd[7] = 0.75;xd[8] = 1;
        yd[0] = -1; yd[1] = -0.75; yd[2] = -0.5;yd[3] = -0.25;yd[4] = 0;yd[5] = 0.25;yd[6] = 0.5;yd[7] = 0.75;yd[8] = 1;

        // Plot this in the graphics window
        //ui->Bathymetry->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom);
        ui->Bathymetry->axisRect()->setupFullAxesBox(true);
        ui->Bathymetry->xAxis->setTickLabelFont(QFont(QFont().family(), 20));
        ui->Bathymetry->yAxis->setTickLabelFont(QFont(QFont().family(), 20));
        ui->Bathymetry->xAxis->setLabel("x-direction");
        ui->Bathymetry->xAxis->setLabelFont(QFont(QFont().family(), 20));
        ui->Bathymetry->yAxis->setLabel("y-direction");
        ui->Bathymetry->yAxis->setLabelFont(QFont(QFont().family(), 20));

        QCPColorMap *colorMap = new QCPColorMap(ui->Bathymetry->xAxis, ui->Bathymetry->yAxis);
        colorMap->data()->setSize(nx,ny);
        colorMap->data()->setRange(QCPRange(xmin,xmax), QCPRange(ymin,ymax));
        for (int ii=0; ii<nx; ii++)
            for (int jj=0; jj<ny; jj++)
                colorMap->data()->setCell(ii, jj, qCos(ii/10.0)+qSin(jj/10.0));
        colorMap->setGradient(QCPColorGradient::gpPolar);
        colorMap->rescaleDataRange(true);
        ui->Bathymetry->rescaleAxes();
        ui->Bathymetry->replot(); */


            /*//Temporary - remove later
    QTextStream out(stdout);
    out << QString::number(nx) << "," << QString::number(ny) << endl;
    out << QString::number(dx) << "," << QString::number(dy) << endl;
    out << QString::number(xlower) << "," << QString::number(ylower) << endl;
    out << QString::number(nodatavalue) << endl;
    for (int ii = 0;ii<nx; ii++)
    {
        for(int jj = 0; jj<ny; jj++)
        {
            out << QString::number(Zdata(ii,jj)) << endl;
        }
    }*/