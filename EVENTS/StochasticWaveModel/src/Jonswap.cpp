/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: JustinBonus
// Adapted from work of: mhgardner
// #include <Jonswap.h>
#include <QComboBox>
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QComboBox>
#include <QHBoxLayout>
#include <SC_DoubleLineEdit.h>
#include <QFormLayout>

#include <RandomVariablesContainer.h>
#include <SimCenterWidget.h>
#include <SC_FileEdit.h>
#include <SC_IntLineEdit.h>
#include <QDoubleValidator>
#include <SimCenterGraphPlot.h>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>

#include <stdexcept>

#include <QLineEdit>
#include <QDoubleValidator>
#include <QFormLayout>
#include <QGridLayout>
#include <SC_ComboBox.h>
#include <QString>


#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <StochasticWaveModel/include/Jonswap.h>
#include <math.h>

Jonswap::Jonswap(RandomVariablesContainer* randomVariables,
                                   QWidget* parent)
: SimCenterAppWidget(parent)
{

  QPushButton *showPlotButton = NULL;
//     // Initialize member variables
  dragCoefficient = new LineEditRV(randomVariables);
  dragCoefficient->setText("2.1");

  dragArea = new LineEditRV(randomVariables);
  dragArea->setText("15.0");

  peakPeriod = new LineEditRV(randomVariables);
  peakPeriod->setText("12.0");

  significantWaveHeight = new LineEditRV(randomVariables);
  significantWaveHeight->setText("8.1");

  waterDepth = new LineEditRV(randomVariables);
  waterDepth->setText("30.0");

  tidalSLR = new LineEditRV(randomVariables);
  tidalSLR->setText("3.0");

  stormSurgeSLR = new LineEditRV(randomVariables);
  stormSurgeSLR->setText("10.0");

  climateChangeSLR = new LineEditRV(randomVariables);
  climateChangeSLR->setText("4.0");

  recorderOriginX = new LineEditRV(randomVariables);
  recorderOriginX->setText("0.0");

  recorderCountZ = new SC_IntLineEdit("recorderCountZ", 2);

  timeStep = new LineEditRV(randomVariables);
  timeStep->setText("0.1");

  timeDuration = new LineEditRV(randomVariables);
  timeDuration->setText("3600.0");

//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");

//   seed = new QSpinBox();
//   seed->setMinimum(1);
//   seed->setMaximum(2147483647);
//   seed->setValue(500);  
//   seed->setEnabled(false);
//   useSeed = new QRadioButton("Provide seed value");
//   useSeed->setChecked(false);


//   exposureCategory = new QComboBox();
//   exposureCategory->addItem("JONSWAP");
// //   exposureCategory->addItem("Pierson-Moskowitz");
  QFormLayout *parameters = new QFormLayout();

  parameters->addRow(new QLabel(tr("Median Sea Level [ft]")), waterDepth);
  parameters->addRow(new QLabel(tr("Tidal Sea Level Rise [ft]")), tidalSLR);
  parameters->addRow(new QLabel(tr("Storm-Surge Sea Level Rise [ft]")), stormSurgeSLR);
  parameters->addRow(new QLabel(tr("Climate Change Sea Level Rise [ft]")), climateChangeSLR);



  exposureCategory = new QComboBox();
  exposureCategory->addItem("NATO 5");
  exposureCategory->addItem("NATO 4");
  exposureCategory->addItem("NATO 3");
  exposureCategory->addItem("NATO 2");
  exposureCategory->addItem("NATO 1");

  // parameters->addRow(new QLabel(tr("Drag Coefficient")), dragCoefficient);
  parameters->addRow(new QLabel(tr("Sea State Category")), exposureCategory);
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));


  parameters->addRow(new QLabel(tr("Significant Wave Height [ft]")), significantWaveHeight);
  parameters->addRow(new QLabel(tr("Peak Wave Period [s]")), peakPeriod);
  parameters->addRow(new QLabel(tr("Time Step [s]")), timeStep);
  parameters->addRow(new QLabel(tr("Time Duration [s]")), timeDuration);
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));
  parameters->addRow(new QLabel(tr("Load Recorder Origin [ft]")), recorderOriginX);
  parameters->addRow(new QLabel(tr("Load Recorder Count [#]")), recorderCountZ);
  // parameters->addRow(new QLabel(tr("Wave Spectrum")), exposureCategory);
  parameters->addRow(new QLabel(tr("Drag Coefficient")), dragCoefficient);
  parameters->addRow(new QLabel(tr("Drag Area [ft^2]")), dragArea);
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));




  // Initialize member variables
  // dragCoefficient = new LineEditRV(randomVariables);
  // dragCoefficient->setText("1.5");

  // gustWindSpeed = new LineEditRV(randomVariables);
  // gustWindSpeed->setText("50.0");

  // exposureCategory = new QComboBox();
  // exposureCategory->addItem("B");
  // exposureCategory->addItem("C");
  // exposureCategory->addItem("D");

  seed = new QSpinBox();
  seed->setMinimum(1);
  seed->setMaximum(2147483647);
  seed->setValue(500);  
  seed->setEnabled(false);
  useSeed = new QRadioButton("Set Random Seed");
  useSeed->setChecked(false);

  // Align the labels to the right
  // for (int i = 0; i < parameters->rowCount(); i++) {
  //   QLabel* label = qobject_cast<QLabel*>(parameters->itemAt(i, QFormLayout::LabelRole)->widget());
  //   label->setAlignment(Qt::AlignRight);
  // }
  // parameters->addRow(new QLabel(tr("Gust Wind Speed (mph)")), gustWindSpeed);
  // gustWindSpeed->setToolTip("3 sec gust speed at height of 10m (33ft)");
  // Add description label
  modelDescription =
      new QLabel(tr("This model provides wave spectra using a "
                    "JONSWAP empirical distribution. "
                    "The open-source welib library computes JONSWAP-"
                    "sampled wave's Morison loads on the structure."));
  //model_description_->setStyleSheet("QLabel { color : gray; }");



  // Construct required layouts
  QVBoxLayout* layout = new QVBoxLayout();
  QHBoxLayout* seedLayout = new QHBoxLayout();
  QHBoxLayout* parametersLayout = new QHBoxLayout();


  // Add widgets to layouts and layouts to this
  seedLayout->addWidget(useSeed);
  seedLayout->addWidget(seed);
  seedLayout->addStretch();
  parametersLayout->addLayout(parameters);

  // mainLayout->setColumnStretch(4,1);

  // parametersWidget = new QWidget();
  // parametersWidget->setLayout(parametersLayout);
  QVBoxLayout * plotLayout = new QVBoxLayout(this);
  QWidget *plotWidget = new QWidget();
  plotWidget->setLayout(plotLayout);

  thePlot = new SimCenterGraphPlot(QString("Time [s]"),QString("Power Spectral Density [m^2 / Hz]"), 700, 350);
  // Maintain aspect ratio but allow resizing
  thePlot->setMinimumSize(650,400);
  thePlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QHBoxLayout* fileFormLayout = new QHBoxLayout();



  dataDir = this->createTextEntry(tr("Wave Spectra (*.csv)"), fileFormLayout, 400, 100);
  dataDir->setMinimumWidth(200);
  // dataDir->setMaximumWidth(700);
  // plotLayout->addWidget(dataDir, 0);
  QPushButton *chooseFileButton = new QPushButton("Choose");
  chooseFileButton->setMinimumWidth(100);
  chooseFileButton->setMaximumWidth(100);
  fileFormLayout->addWidget(chooseFileButton, 1);
  // a = this->createTextEntry(tr("Min"), plotLayout, 100, 100);
  // b = this->createTextEntry(tr("Max"), plotLayout, 100, 100);
  showPlotButton = new QPushButton("Sample Wave Spectra");
  showPlotButton->setMinimumWidth(200);
  showPlotButton->setMaximumWidth(200);

  QPushButton* thePileImageButton = new QPushButton("Plot Loads");
  thePileImageButton->setMinimumWidth(150);
  thePileImageButton->setMaximumWidth(150);
  QWidget* fileFormWidget = new QWidget();
  fileFormWidget->setLayout(fileFormLayout);

  fileFormLayout->addWidget(showPlotButton, 2);


  fileFormLayout->addWidget(thePileImageButton,3 );

  // add empty 

  QPixmap pixmapPile(":/icons/forces.png");
  QPushButton* thePileFigure = new QPushButton();
  thePileFigure->setIcon(pixmapPile);
  thePileFigure->setIconSize(pixmapPile.rect().size()*1.0);
  thePileFigure->setFixedSize(pixmapPile.rect().size()*1.0);

  // QHBoxLayout *pileFigureLayout = new QHBoxLayout();
  // pileFigureLayout->addWidget(thePileFigure);
  // thePileImageButton->setIcon(pixmapPile);

  // thePileImageButton->setIconSize(pixmapPile.rect().size()*0.5);
  // thePileImageButton->setFixedSize(pixmapPile.rect().size()*0.5);
  // parametersLayout->addWidget(thePileImageButton);
  

  // plotLayout->setStretch(5,1);



  int plotNumRow = 12;
  // layout->addWidget(plotWidget, plotNumRow++, 0, 1, 5);

  theDomainImageButton = new QPushButton();
  QPixmap pixmapDomain(":/icons/HydroLoadPile.png");

  pixmapDomain.scaled(800, 400, Qt::KeepAspectRatio,Qt::SmoothTransformation);

  theDomainImageButton->setIcon(pixmapDomain);
  theDomainImageButton->setIconSize(pixmapDomain.rect().size()*1.00);
  theDomainImageButton->setFixedSize(pixmapDomain.rect().size()*1.00);
  parametersLayout->addWidget(theDomainImageButton);




  thePlot->hide();
  thePlot->clear();
  // thePileFigure->hide();
  // theDomainImageButton->hide();

  parametersLayout->addWidget(plotWidget);
  parametersLayout->addWidget(thePlot);
  connect(chooseFileButton, &QPushButton::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"", "CSV File (*.csv)");
        if (!fileName.isEmpty()) {
            dataDir->setText(fileName);
        }
    });

  dataDir->setText(QString(":/WaveSpectra.csv"));


  updateDistributionPlot();


  // parametersLayout->addWidget(plotWidget);
  // parametersLayout->addWidget(theDomainImageButton);
  parametersLayout->addStretch();
  this->updateDistributionPlot();
  layout->addWidget(modelDescription);
  layout->addLayout(parametersLayout);
  layout->addLayout(seedLayout);
  layout->addWidget(fileFormWidget);
  layout->addWidget(thePileFigure);
  layout->addStretch();
  this->setLayout(layout);

  thePlot->show();
  theDomainImageButton->show();
  thePileFigure->show();


  // Place the plot in the layout
  connect(dataDir,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
  connect(a,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
  connect(b,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
  connect(showPlotButton, &QPushButton::clicked, this, [=](){ thePlot->hide(); this->updateDistributionPlot(); thePlot->show();});
  // connect (spectraFile, &SC_FileEdit::fileChanged, this, [=](){
  //     QString fileName = spectraFile->getFilename();
  //     dataDir->setText(fileName);
  // });
  // Show the plot when the

  connect(dataDir, &QLineEdit::editingFinished, this, [=](){
      thePlot->hide();
      this->updateDistributionPlot();
      thePlot->show();
  });


  // Connect slots
  connect(useSeed, &QRadioButton::toggled, this,
          &Jonswap::provideSeed);
}


QLineEdit *
Jonswap::createTextEntry(QString text,
                                            QHBoxLayout *theLayout,
                                            int minL,
                                            int maxL)
{
    QVBoxLayout *entryLayout = new QVBoxLayout();
    //QHBoxLayout *entryLayout = new QHBoxLayout();
    QLabel *entryLabel = new QLabel(text);

    QLineEdit *res = new QLineEdit();
    res->setMinimumWidth(minL);
    res->setMaximumWidth(maxL);
    res->setValidator(new QDoubleValidator);

    entryLayout->addWidget(entryLabel);
    entryLayout->addWidget(res);

    entryLayout->setSpacing(0);
    //    entryLayout->setMargin(0);

    theLayout->addLayout(entryLayout);

    return res;
}

QLineEdit *
Jonswap::createTextEntry(QString text,
                                            QGridLayout *theLayout,
                                            int col,
                                            int minL,
                                            int maxL)
{
    //QVBoxLayout *entryLayout = new QVBoxLayout();
    // //QHBoxLayout *entryLayout = new QHBoxLayout();
    QLabel *entryLabel = new QLabel(text);

    QLineEdit *res = new QLineEdit();
    res->setMinimumWidth(minL);
    res->setMaximumWidth(maxL);
    res->setValidator(new QDoubleValidator);
    //entryLayout->addWidget(entryLabel);
    //entryLayout->addWidget(res);

    //entryLayout->setSpacing(0);
    //entryLayout->setMargin(0);

    //theLayout->addLayout(entryLayout,0,col,2,1);

    theLayout->addWidget(entryLabel,0,col);
    theLayout->addWidget(res,1,col);

    return res;
}


bool
Jonswap::copyFiles(QString &destDir)
{
  if (dataDir->text().isEmpty()) {
    dataDir->setText(":Examples/hdro-0005/data/WaveSpectra.csv");
    this->errorMessage("WARNING: StochasticWave - spectra ideal filename had not been set when trying to call copyFiles(), using default file: " + dataDir->text());
    QFile::copy(dataDir->text(), destDir);
    return true;
  }
  else 
    QFile::copy(dataDir->text(), destDir);


  QString timeSeriesFileName = dataDir->text();
  timeSeriesFileName.replace("WaveSpectra.csv", "WaveSpectraGenerated.csv"); // temp fix assuming spectra file name
  if (dataDir->text().isEmpty()) {
    dataDir->setText(":Examples/hdro-0005/data/WaveSpectraGenerated.csv");
    this->errorMessage("WARNING: StochasticWave - spectra generated filename had not been set when trying to call copyFiles(), using default file: " + dataDir->text());
    QFile::copy(dataDir->text(), destDir);
    return true;
  }

  // if (spectraFile->getFilename() != nullptr) {
  //   if (!spectraFile->copyFile(destDir))
  //     qDebug() << "Error copying paddle displacement file: " << spectraFile->getFilename();
  // }


  return true;    
}



QString
Jonswap::getAbbreviatedName(void) {
  return QString("JONSWAP");
}

bool readCSVRowSpectra (QTextStream &in, QStringList *row) {

    static const int delta[][5] = {
        //  ,    "   \n    ?  eof
        {   1,   2,  -1,   0,  -1  }, // 0: parsing (store char)
        {   1,   2,  -1,   0,  -1  }, // 1: parsing (store column)
        {   3,   4,   3,   3,  -2  }, // 2: quote entered (no-op)
        {   3,   4,   3,   3,  -2  }, // 3: parsing inside quotes (store char)
        {   1,   3,  -1,   0,  -1  }, // 4: quote exited (no-op)
        // -1: end of row, store column, success
        // -2: eof inside quotes
    };

    row->clear();

    if (in.atEnd())
        return false;

    int state = 0, t;
    char ch;
    QString cell;

    while (state >= 0) {

        if (in.atEnd())
            t = 4;
        else {
            in >> ch;
            if (ch == ',') t = 0;
            else if (ch == '\"') t = 1;
            else if (ch == '\n') t = 2;
            else t = 3;
        }

        state = delta[state][t];

        if (state == 0 || state == 3) {
            cell += ch;
        } else if (state == -1 || state == 1) {
            row->append(cell);
            cell = "";
        }

    }

    if (state == -2)
        throw std::runtime_error("End-of-file found while inside quotes.");

    return true;

}

void Jonswap::clear() {
  thePlot->hide();
  // theDomainImageButton->hide();
  waterDepth->clear();
  tidalSLR->clear();
  stormSurgeSLR->clear();
  climateChangeSLR->clear();
  significantWaveHeight->clear();
  peakPeriod->clear();
  recorderOriginX->clear();
  recorderCountZ->clear();
  timeStep->clear();
  timeDuration->clear();
  dragCoefficient->clear();
  dragArea->clear();
  // gustWindSpeed->clear();
  seed->setValue(500);
  useSeed->setChecked(false);
  dataDir->setText("");
  thePlot->clear();

}

void
Jonswap::updateDistributionPlot() {
    int numSteps = 100;
    int numStepsTimeSeries = 100;
    if (dataDir->text().isEmpty()) {
        dataDir->setText(":Examples/hdro-0005/data/WaveSpectra.csv"); // hardcoded for quick fix
        this->errorMessage("ERROR: StochasticWave - data has not been set, using default");
        // return;
    }
    QString csvFileName = dataDir->text();
    QFile csv(csvFileName);
    csv.open(QFile::ReadOnly | QFile::Text);

    QTextStream in(&csv);
    QStringList row;
    QStringList firstColumn;
    QStringList secondColumn;

    numSteps = 0; // reset

    // Assume no header lines
    while (readCSVRowSpectra(in, &row)) {
        firstColumn.append(row[0]);
        secondColumn.append(row[1]);
        numSteps++;
    }

    csv.close();

    QVector<double> x(numSteps); // time
    QVector<double> y(numSteps); // displacement
    for (int i=0; i<numSteps; i++) {
        x[i] = firstColumn[i].toDouble();
        y[i] = secondColumn[i].toDouble();
    }

    // look for the file WaveTimeSeries.csv adjacent to the WaveSpectra.csv
    QString timeSeriesFileName = csvFileName;
    // timeSeriesFileName.replace("WaveSpectra.csv", "WaveTimeSeries.csv");
    // timeSeriesFileName.replace("WaveSpectra.csv", "WaveTimeSeries.csv");
    timeSeriesFileName.replace("WaveSpectra.csv", "WaveSpectraGenerated.csv");
    QFile timeSeriesFile(timeSeriesFileName);
    timeSeriesFile.open(QFile::ReadOnly | QFile::Text);

    QTextStream inTimeSeries(&timeSeriesFile);
    QStringList rowTimeSeries;
    QStringList firstColumnTimeSeries;
    QStringList secondColumnTimeSeries;

    numStepsTimeSeries = 0; // reset

    


    // Assume no header lines

    while (readCSVRowSpectra(inTimeSeries, &rowTimeSeries)) {
        firstColumnTimeSeries.append(rowTimeSeries[0]);
        secondColumnTimeSeries.append(rowTimeSeries[1]);
        numStepsTimeSeries++;
    }

    timeSeriesFile.close();

    QVector<double> xG(numStepsTimeSeries); // time
    QVector<double> yG(numStepsTimeSeries); // displacement
    for (int i=0; i<numStepsTimeSeries; i++) {
        xG[i] = firstColumnTimeSeries[i].toDouble();
        yG[i] = secondColumnTimeSeries[i].toDouble();
    }

    // plot
    thePlot->clear();
    thePlot->drawPDF(x,y);
    // thePlot->addLine(xG,yG, 1, 65, 74, 82);
    thePlot->drawPDF(xG,yG);
    thePlot->show();
    return;

    
    


//        else {
//            QVector<double> x(100);
//            QVector<double> y(100);
//            QVector<double> x1(100);
//            QVector<double> y1(100);
//            for (int i=0; i<100; i++) {
//                x[i] =  aa+1;
//                y[i] =  bb+10;
//                x1[i] =  me+1;
//                y1[i] =  st+10;
//            }
//            thePlot->clear();
//            thePlot->drawPDF(x,y);
//            thePlot->drawPDF(x1,y1);
//        }
}

bool Jonswap::outputAppDataToJSON(QJsonObject& jsonObject) {
  bool result = true;

  jsonObject["Application"] = "StochasticWave";
  jsonObject["EventClassification"] = "Hydro";

  // jsonObject["Application"] = "StochasticWindWittigSinha";
  // jsonObject["EventClassification"] = "Wind";

  // squirel in the application data selection text
  QJsonObject appData;
  jsonObject["ApplicationData"] = appData;

  return result;
}

bool Jonswap::inputAppDataFromJSON(QJsonObject& jsonObject) {
  Q_UNUSED(jsonObject);
  return true;
}

bool Jonswap::outputToJSON(QJsonObject& jsonObject) {
  bool result = true;

  jsonObject["type"] = "StochasticWave";
  jsonObject["EventClassification"] = "Hydro";

  // jsonObject["type"] = "StochasticWindWittigSinha";
  // jsonObject["EventClassification"] = "Wind";

  waterDepth->outputToJSON(jsonObject, QString("waterDepth"));
  tidalSLR->outputToJSON(jsonObject, QString("tidalSLR"));
  stormSurgeSLR->outputToJSON(jsonObject, QString("stormSurgeSLR"));
  climateChangeSLR->outputToJSON(jsonObject, QString("climateChangeSLR"));
  significantWaveHeight->outputToJSON(jsonObject, QString("significantWaveHeight"));
  peakPeriod->outputToJSON(jsonObject, QString("peakPeriod"));
  recorderOriginX->outputToJSON(jsonObject, QString("recorderOriginX"));
  recorderCountZ->outputToJSON(jsonObject);
  timeStep->outputToJSON(jsonObject, QString("timeStep"));
  timeDuration->outputToJSON(jsonObject, QString("timeDuration"));
  dragCoefficient->outputToJSON(jsonObject, QString("dragCoefficient"));
  dragArea->outputToJSON(jsonObject, QString("dragArea"));


  // gustWindSpeed->outputToJSON(jsonObject, QString("gustSpeed"));
  jsonObject.insert("exposureCategory",exposureCategory->currentText());

  if (useSeed->isChecked()) {
    jsonObject.insert("seed", seed->value());
  } else {
    jsonObject.insert("seed", "None");
  }
  
  return result;
}

bool Jonswap::inputFromJSON(QJsonObject& jsonObject) {
  bool result = true;

  // theDomainImageButton->hide();
  thePlot->hide();



  waterDepth->inputFromJSON(jsonObject, QString("waterDepth"));
  tidalSLR->inputFromJSON(jsonObject, QString("tidalSLR"));
  stormSurgeSLR->inputFromJSON(jsonObject, QString("stormSurgeSLR"));
  climateChangeSLR->inputFromJSON(jsonObject, QString("climateChangeSLR"));
  significantWaveHeight->inputFromJSON(jsonObject, QString("significantWaveHeight"));
  peakPeriod->inputFromJSON(jsonObject, QString("peakPeriod"));
  recorderOriginX->inputFromJSON(jsonObject, QString("recorderOriginX"));
  recorderCountZ->inputFromJSON(jsonObject);
  timeStep->inputFromJSON(jsonObject, QString("timeStep"));
  timeDuration->inputFromJSON(jsonObject, QString("timeDuration"));
  dragCoefficient->inputFromJSON(jsonObject, QString("dragCoefficient"));
  dragArea->inputFromJSON(jsonObject, QString("dragArea"));



  // gustWindSpeed->inputFromJSON(jsonObject, QString("gustSpeed"));

  if (jsonObject.contains("exposureCategory")) {

      QJsonValue theValue = jsonObject["exposureCategory"];
      if (theValue.isString()) {
        QString exposure  = theValue.toString();
        exposureCategory->setCurrentText(exposure);
      }
  }

  if (jsonObject.value("seed").isString()) {
    useSeed->setChecked(false);    
  } else {
    useSeed->setChecked(true);
    seed->setValue(jsonObject.value("seed").toInt());    
  }

  theDomainImageButton->show();

  thePlot->clear();
  updateDistributionPlot();
  thePlot->show();


  return result;
}

void Jonswap::provideSeed(const bool& checked) {
  if (checked) {
    seed->setEnabled(true);
  } else {
    seed->setEnabled(false);
    seed->setValue(500);
  }
}
