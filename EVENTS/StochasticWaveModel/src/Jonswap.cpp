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
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDoubleValidator>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QLineEdit>
#include <QStringList>
// #include <QString>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <QScrollArea>
#include <QProcess>
#include <SimCenterPreferences.h>
#include <QJsonDocument>
#include <GeneralInformationWidget.h>

#include <RandomVariablesContainer.h>
#include <SC_ComboBox.h>
// #include <SC_DoubleSpinBox.h>
#include <SimCenterWidget.h>
// #include <SC_FileEdit.h>
#include <SC_IntLineEdit.h>
// #include <SC_DoubleLineEdit.h>
#include <SimCenterGraphPlot.h>
#include <LineEditRV.h>
#include <stdexcept>
#include <math.h>

#include <StochasticWaveModel/include/Jonswap.h>
#include "RunPythonInThread.h"
#include <QCoreApplication>
#include <QTimer>

Jonswap::Jonswap(RandomVariablesContainer* randomVariables,
                                   QWidget* parent)
: SimCenterAppWidget(parent)
{

  QPushButton *showPlotButton = NULL;
  QPushButton *showPlotButtonTimeSeries = NULL;

  // theDomainImageButton = NULL;
  thePlot = NULL;
  thePlotTimeSeries = NULL;

  modelDescription = new QLabel(tr(" Sample JONSWAP spectras (empirical sea-state) for stochastic loads on monopile-like structures. "
                                   "\n The welib Python package provides validated JONSWAP distributions and Wheeler-corrected Morison wave loads on simple monopile structures. "
                                   "\n Use-case: Quantify how sea-level rise (e.g., from climate-change, storm-surges, tides) influences stochastic structural loads. "));
  //fontsize 
  modelDescription->setStyleSheet("QLabel { font-size : 12px; }");
  


  // modelDescription->setStyleSheet("QLabel { color : gray; }");
  // Put modelDescription in a scroll area
  QScrollArea *scrollArea = new QScrollArea;
  scrollArea->setWidget(modelDescription);
  scrollArea->setWidgetResizable(true);
  scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


  // Initialize member variables
  waterDepth = new LineEditRV(randomVariables);
  waterDepth->setText("30.0");
  tidalSLR = new LineEditRV(randomVariables);
  tidalSLR->setText("3.0");
  stormSurgeSLR = new LineEditRV(randomVariables);
  stormSurgeSLR->setText("10.0");
  climateChangeSLR = new LineEditRV(randomVariables);
  climateChangeSLR->setText("4.0");

  significantWaveHeight = new LineEditRV(randomVariables);
  significantWaveHeight->setText("8.1");
  peakPeriod = new LineEditRV(randomVariables);
  peakPeriod->setText("12.0");

  timeStep = new LineEditRV(randomVariables);
  timeStep->setText("1.0");
  timeDuration = new LineEditRV(randomVariables);
  timeDuration->setText("300.0");

  recorderOriginX = new LineEditRV(randomVariables);
  recorderOriginX->setText("0.0");
  // Base off of stories in GI
  GeneralInformationWidget *theGI = GeneralInformationWidget::getInstance();
  // numFloors = theGI->getNumFloors() + 1;
  int numFloors = 2;
  recorderCountZ = new SC_IntLineEdit("recorderCountZ", numFloors);
  recorderCountZ->setToolTip("Number of load recorders on the structure, should be equal to the number of floors in the building (i.e., stories + 1).");

  // connect(theGI, &GeneralInformationWidget::floorsChanged, [=](int floors){
  //   recorderCountZ->setText(QString::number(floors));
  // });


  dragCoefficient = new LineEditRV(randomVariables);
  dragCoefficient->setText("2.1");
  dragArea = new LineEditRV(randomVariables);
  dragArea->setText("15.0");

  exposureCategory = new QComboBox();
  exposureCategory->addItem("NATO 5");
  exposureCategory->addItem("NATO 4");
  exposureCategory->addItem("NATO 3");
  exposureCategory->addItem("NATO 2");
  exposureCategory->addItem("NATO 1");

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

  parameters->addRow(new QLabel(tr("Significant Wave Height [ft]")), significantWaveHeight);
  parameters->addRow(new QLabel(tr("Peak Wave Period [s]")), peakPeriod);
  parameters->addRow(new QLabel(tr("Time Step [s]")), timeStep);
  parameters->addRow(new QLabel(tr("Time Duration [s]")), timeDuration);

  parameters->addRow(new QLabel(tr("Sea State Category")), exposureCategory);
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));
  parameters->addRow(new QLabel(tr("Load Recorder Origin [ft]")), recorderOriginX);
  parameters->addRow(new QLabel(tr("Load Recorder Count [#]")), recorderCountZ);

  parameters->addRow(new QLabel(tr("Drag Coefficient")), dragCoefficient);
  parameters->addRow(new QLabel(tr("Drag Area [ft^2]")), dragArea);
  parameters->addRow(new QLabel(tr("")), new QLabel(tr("")));


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

  //model_description_->setStyleSheet("QLabel { color : gray; }");


  // Construct required layouts
  QVBoxLayout* layout = new QVBoxLayout();
  // QVBoxLayout* graphLayout = new QVBoxLayout();
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
  // QVBoxLayout * plotLayout = new QVBoxLayout(this);
  // QWidget *plotWidget = new QWidget();
  // plotWidget->setLayout(plotLayout);

  thePlot = new SimCenterGraphPlot(QString("Frequency [Hz]"),QString("Power Spectral Density [ft^2 / Hz]"), 700, 350);
  thePlot->setMinimumSize(400,250);
  thePlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  thePlotTimeSeries = new SimCenterGraphPlot(QString("Time [s]"),QString("Surface Displacement [ft]"), 700, 350);
  thePlotTimeSeries->setMinimumSize(400,250);
  thePlotTimeSeries->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QHBoxLayout* fileFormLayout = new QHBoxLayout();
  dataDir = this->createTextEntry(tr("Wave Spectra (*.csv)"), fileFormLayout, 400, 100);
  dataDir->setMinimumWidth(200);

  QHBoxLayout* fileFormLayoutTimeSeries = new QHBoxLayout();
  timeSeriesDir = this->createTextEntry(tr("Wave Time Series (*.csv)"), fileFormLayoutTimeSeries, 400, 100);
  timeSeriesDir->setMinimumWidth(200);

  QPushButton *chooseFileButton = new QPushButton("Choose");
  chooseFileButton->setMinimumWidth(100);
  chooseFileButton->setMaximumWidth(100);

  QPushButton *chooseTimeSeriesFileButton = new QPushButton("Choose");
  chooseTimeSeriesFileButton->setMinimumWidth(100);
  chooseTimeSeriesFileButton->setMaximumWidth(100);


  fileFormLayout->addWidget(chooseFileButton, 1);
  showPlotButton = new QPushButton("Sample Wave Spectra");
  showPlotButton->setMinimumWidth(200);
  showPlotButton->setMaximumWidth(200);
  fileFormLayout->addWidget(showPlotButton, 2);

  fileFormLayoutTimeSeries->addWidget(chooseTimeSeriesFileButton, 1);
  showPlotButtonTimeSeries = new QPushButton("Sample Time Series");
  showPlotButtonTimeSeries->setMinimumWidth(200);
  showPlotButtonTimeSeries->setMaximumWidth(200);
  fileFormLayoutTimeSeries->addWidget(showPlotButtonTimeSeries, 2);

  // // For plotting the monopile loads image
  // QPushButton* thePileImageButton = new QPushButton("Plot Loads");
  // thePileImageButton->setMinimumWidth(150);
  // thePileImageButton->setMaximumWidth(150);
  QWidget* fileFormWidget = new QWidget();
  fileFormWidget->setLayout(fileFormLayout);

  QWidget* fileFormWidgetTimeSeries = new QWidget();
  fileFormWidgetTimeSeries->setLayout(fileFormLayoutTimeSeries);

  QVBoxLayout *spectraLayout = new QVBoxLayout();
  spectraLayout->addWidget(fileFormWidget);
  spectraLayout->addWidget(thePlot);

  QVBoxLayout *timeLayout = new QVBoxLayout();
  timeLayout->addWidget(fileFormWidgetTimeSeries);
  timeLayout->addWidget(thePlotTimeSeries);
  // fileSelectLayout->addWidget(fileFormWidgetTimeSeries);
  // fileSelectLayout->addWidget(fileFormWidget);


  parametersLayout->addLayout(spectraLayout);
  parametersLayout->addLayout(timeLayout);


  // parametersLayout->addWidget(fileFormWidget);
  // parametersLayout->addWidget(fileFormWidgetTimeSeries);
  // fileFormLayout->addWidget(thePileImageButton,3 );

  // // Show forces, etc. on monopile structure
  // QPixmap pixmapPile(":/icons/forces.png");
  // QPushButton* thePileFigure = new QPushButton();
  // thePileFigure->setIcon(pixmapPile);
  // thePileFigure->setIconSize(pixmapPile.rect().size()*1.0);
  // thePileFigure->setFixedSize(pixmapPile.rect().size()*1.0);

  // QHBoxLayout *pileFigureLayout = new QHBoxLayout();
  // pileFigureLayout->addWidget(thePileFigure);
  // thePileImageButton->setIcon(pixmapPile);

  // thePileImageButton->setIconSize(pixmapPile.rect().size()*0.5);
  // thePileImageButton->setFixedSize(pixmapPile.rect().size()*0.5);
  // parametersLayout->addWidget(thePileImageButton);
  

  // plotLayout->setStretch(5,1);


  // int plotNumRow = 12;
  // layout->addWidget(plotWidget, plotNumRow++, 0, 1, 5);

  /*
  theDomainImageButton = new QPushButton();
  QPixmap pixmapDomain(":/icons/HydroLoadPile.png");

  pixmapDomain.scaled(500, 250, Qt::KeepAspectRatio,Qt::SmoothTransformation);

  theDomainImageButton->setIcon(pixmapDomain);
  theDomainImageButton->setIconSize(pixmapDomain.rect().size()*1.00);
  theDomainImageButton->setFixedSize(pixmapDomain.rect().size()*1.00);
  */

  // thePileFigure->hide();
  // theDomainImageButton->hide();

  // parametersLayout->addWidget(plotWidget);
  // parametersLayout->addWidget(thePlot);
  // parametersLayout->addWidget(thePlotTimeSeries);

  

  parametersLayout->addLayout(spectraLayout);
  parametersLayout->addLayout(timeLayout);

  connect(chooseFileButton, &QPushButton::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"", "CSV Files (*.csv)");
        if (!fileName.isEmpty()) {
            dataDir->setText(fileName);
        }
    });

  connect(chooseTimeSeriesFileButton, &QPushButton::clicked, this, [=](){
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),"", "CSV Files (*.csv)");
        if (!fileName.isEmpty()) {
            timeSeriesDir->setText(fileName);
        }
    });

  // QString spectraFileString = "Examples/hdro-0005/data/WaveSpectra.csv";
  QString defaultSpectraFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveSpectra.csv";
  QString defaultTimeSeriesFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveTimeSeries.csv";
  dataDir->setText(defaultSpectraFile);
  timeSeriesDir->setText(defaultTimeSeriesFile);



  // parametersLayout->addWidget(plotWidget);
  // parametersLayout->addWidget(theDomainImageButton);

  parametersLayout->addStretch();
  // layout->addWidget(modelDescription);
  layout->addWidget(scrollArea);
  layout->addLayout(parametersLayout);
  layout->addLayout(seedLayout);
  // layout->addWidget(fileFormWidget);
  // layout->addWidget(fileFormWidgetTimeSeries);
  // layout->addWidget(theDomainImageButton);
  // layout->addWidget(thePileFigure);
  layout->addStretch();
  this->setLayout(layout);

  thePlot->hide();
  thePlot->clear();
  thePlotTimeSeries->hide();
  thePlotTimeSeries->clear();
  // updateDistributionPlot();
  this->updateDistributionPlot(); // show the plot when the widget is created
  thePlot->show();
  thePlotTimeSeries->show();
  // theDomainImageButton->show();
  // thePileFigure->show();



  // Place the plot in the layout
  connect(dataDir,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot())); 
  connect(timeSeriesDir,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
  // connect(a,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));
  // connect(b,SIGNAL(textEdited(QString)), this, SLOT(updateDistributionPlot()));

  connect(showPlotButton, &QPushButton::clicked, this, [=](){
        thePlot->hide();
        this->computeSpectra();
        // thePlot->show();
    });

  connect(showPlotButtonTimeSeries, &QPushButton::clicked, this, [=](){
        thePlotTimeSeries->hide();
        this->computeSpectra();
        // thePlotTimeSeries->show();
    });
  connect(showPlotButton, &QPushButton::clicked, this, [=](){ thePlot->hide(); this->updateDistributionPlot(); thePlot->show();});
  connect(showPlotButtonTimeSeries, &QPushButton::clicked, this, [=](){ thePlotTimeSeries->hide(); this->updateDistributionPlot(); thePlotTimeSeries->show();});
  // connect (spectraFile, &SC_FileEdit::fileChanged, this, [=](){
  //     QString fileName = spectraFile->getFilename();
  //     dataDir->setText(fileName);
  // });
  // Show the plot when the

  connect(dataDir, &QLineEdit::editingFinished, this, [=](){
      thePlot->hide();
      this->updateDistributionPlot();
      thePlot->show();
      // connect pythonProcessFinished
      // QTimer::singleShot(100, this, [=](){ thePlot->show(); });
  });

  connect(timeSeriesDir, &QLineEdit::editingFinished, this, [=](){
      thePlotTimeSeries->hide();
      this->updateDistributionPlot();
      thePlotTimeSeries->show();
      // QTimer::singleShot(100, this, [=](){ thePlotTimeSeries->show(); });
  });





  // Connect slots
  connect(useSeed, &QRadioButton::toggled, this,
          &Jonswap::provideSeed);
}

void Jonswap::updateJSON()
{
    // Write most recent EVT state to JSON becase it is needed for pre-processing steps / mesh generation before the final simulation is run.
    // In future only one JSON file in temp.SimCenter directory might be enough
    QString inputFileName = "Jonswap.json";
    auto prefs = SimCenterPreferences::getInstance();
    QString localWorkDirectoryString = prefs->getLocalWorkDir();
    QDir localWorkDir(localWorkDirectoryString);
    if (!localWorkDir.exists()) {
        localWorkDir.mkpath(".");
    }

    QString tmpDirName = "tmp.SimCenter";
    localWorkDir.mkdir(tmpDirName);
    QDir tmpDir = QDir(localWorkDir.absoluteFilePath(tmpDirName));
    if (!tmpDir.exists()) {
        tmpDir.mkpath(".");
    }

    QString subDirName = "stochasticWave"; // "tmp.SimCenter"; "templatedir";
    localWorkDir.mkdir(subDirName);
    QDir workingDir = QDir(localWorkDir.absoluteFilePath(subDirName));
    if (!workingDir.exists()) {
        workingDir.mkpath(".");
    }
    QString workingDirPath = localWorkDir.absoluteFilePath(subDirName);
    qDebug() << "workingDirPath: " << workingDirPath;
    // QDir workingDir = QDir(localWorkDir.absoluteFilePath(subDirName));
    // workingDirPath = localWorkDir.absoluteFilePath(subDirName);

    QString inputFilePath  = localWorkDir.absoluteFilePath(tmpDirName) + QDir::separator() + inputFileName;
    QString outputFilePath = localWorkDir.absoluteFilePath(tmpDirName) + QDir::separator() + inputFileName;

    qDebug() << "inputFilePath: " << inputFilePath;
    qDebug() << "outputFilePath: " << outputFilePath;


    QFile jsonFile(inputFilePath);
    // if it exists, remove it
    if (jsonFile.exists()) {
        jsonFile.remove();
    }
    
    if (!jsonFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Cannot find the path: " << inputFilePath;
    } 

    

    QJsonObject eventObject;
    this->outputToJSON(eventObject);


    QJsonArray eventsArray;
    eventsArray.append(eventObject);
    QJsonObject pseudoObject;
    pseudoObject["Events"] = eventsArray;

    QJsonDocument jsonDoc(pseudoObject);
    jsonFile.write(jsonDoc.toJson());
    jsonFile.close();

    // while open(jsonFile, 'w') as f:
    //     json.dump(pseudoObject, f, indent=4)

    // QJsonDocument jsonDoc(pseudoObject);
    // jsonFile.write(jsonDoc.toJson());
    // jsonFile.close();
    return;
}
// Function that runs a python script to generate the wave spectra and time series
// Saves the wave spectra and time series to csv files. 
// Plots the wave spectra and time series
void Jonswap::computeSpectra() {
  // Get the input parameters
  this->updateJSON();


  auto prefs = SimCenterPreferences::getInstance();
  
  //
  //  Update JSON input file and then pass arguments to a python script. Runs script to prepare case directory.
  //  Python scripts hosted remotely by SimCenterBackendApplications/modules/createEVENT/*
  // 


  QString inputFileName = "Jonswap.json";
  QString localWorkDirectoryString = prefs->getLocalWorkDir();
  QDir localWorkDir(localWorkDirectoryString);
  if (!localWorkDir.exists()) {
      localWorkDir.mkpath(".");
  }

  QString tmpDirName = "tmp.SimCenter";
  // localWorkDir.mkdir(tmpDirName);
  // QDir tmpDir = QDir(localWorkDir.absoluteFilePath(tmpDirName));
  // if (!tmpDir.exists()) {
  //     tmpDir.mkpath(".");
  // }

  QString subDirName = "stochasticWave"; // "tmp.SimCenter"; "templatedir";
  // localWorkDir.mkdir(subDirName);
  // QDir workingDir = QDir(localWorkDir.absoluteFilePath(subDirName));
  // if (!workingDir.exists()) {
  //     workingDir.mkpath(".");
  // }
  // QString workingDirPath = localWorkDir.absoluteFilePath(subDirName);
  // workingDirPath = localWorkDir.absoluteFilePath(subDirName);
  // qDebug() << "workingDirPath: " << workingDirPath;
  QString inputFilePath  = localWorkDir.absoluteFilePath(tmpDirName) + QDir::separator() + inputFileName;

  // QString outputFilePath = caseDir() + QDir::separator() + inputFileName;

  // QFile jsonFile(inputFilePath);
  // if (!jsonFile.open(QFile::WriteOnly | QFile::Text))
  // {
  //     qDebug() << "Cannot find the path: " << inputFilePath;
  // }
  // QString inputFilePath = caseDir() + QDir::separator() + "inputData" + QDir::separator() + inputFileName;

  // updateJSON(); 
  QString scriptName = "Jonswap.py"; // "setup_case.py";
  QString scriptPath = SimCenterPreferences::getInstance()->getAppDir() + QDir::separator()
            + QString("applications") + QDir::separator() + QString("createEVENT") + QDir::separator()
            + QString("stochasticWave") + QDir::separator() + scriptName; 


  QString outputPath = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker";

  qDebug() << "scriptPath: " << scriptPath;
  qDebug() << "inputFilePath: " << inputFilePath;

  // QString outputPath = caseDir();
  if (QFileInfo(scriptPath).exists() )
  {
    qDebug() << "Running the script: " << scriptPath << " with input file: " << inputFilePath << " and output path: " << outputPath;
    QString program = SimCenterPreferences::getInstance()->getPython();
    
    QStringList arguments;
    arguments << inputFilePath << outputPath;
    QString workingDir = QCoreApplication::applicationDirPath() + QDir::separator() + QString("Examples") + QDir::separator() + QString("WaveMaker");
    RunPythonInThread *pythonThread = new RunPythonInThread(scriptPath, arguments, workingDir);
    pythonThread->runProcess();
    connect(pythonThread, &RunPythonInThread::processFinished, this, [=](int exitCode) {
        qDebug() << "Python script finished with exit code: " << exitCode;
        this->updateDistributionPlot();
        thePlot->show();
        thePlotTimeSeries->show();
    });

    // QStringList arguments; arguments << scriptPath << inputFilePath << outputPath;
    // QProcess *process = new QProcess();

    // // process->setWorkingDirectory(workingDirPath);
    // process->start(program, arguments);
    
    // process->waitForFinished(-1);
    // process->close();


    // process->deleteLater();

  } 
  else 
  {
    qDebug() << "Cannot find the script path: " << scriptPath;
    return;
  }


  // Plot the wave spectra
  thePlot->hide();
  thePlotTimeSeries->hide();

  dataDir->setText(outputPath + QDir::separator() + "WaveSpectraGenerated.csv");
  timeSeriesDir->setText(outputPath + QDir::separator() + "WaveTimeSeries.csv");

  this->updateDistributionPlot();

  thePlot->show();
  thePlotTimeSeries->show();


  // QString 

  // // Run the python script
  // QString command = "python3 -m StochasticWaveModel.generate_wave_spectra ";
  // command += waterDepthString + " ";
  // command += tidalSLRString + " ";
  // command += stormSurgeSLRString + " ";
  // command += climateChangeSLRString + " ";
  // command += significantWaveHeightString + " ";
  // command += peakPeriodString + " ";
  // command += recorderOriginXString + " ";
  // command += recorderCountZString + " ";
  // command += timeStepString + " ";
  // command += timeDurationString + " ";
  // command += dragCoefficientString + " ";
  // command += dragAreaString + " ";
  // command += exposureCategoryString + " ";
  // command += seedString + " ";
  // command += dataDirString + " ";
  // command += timeSeriesDirString;

  // // Run the command
  // system(command.toStdString().c_str());

  // // Plot the wave spectra
  // thePlot->clear();
  // thePlot->addGraph();
  // thePlot->setAxisLabels("Time [s]", "Power Spectral Density [m^2 / Hz]");
  // thePlot->plotFile(dataDirString);

  // // Plot the time series
  // thePlotTimeSeries->clear();
  // thePlotTimeSeries->addGraph();
  // thePlotTimeSeries->setAxisLabels("Time [s]", "
  // Displacement [m]");
  // thePlotTimeSeries->plotFile(timeSeriesDirString);
}


QLineEdit *
Jonswap::createTextEntry(QString text,
                                            QHBoxLayout *theLayout,
                                            int minL,
                                            int maxL)
{
    QVBoxLayout *entryLayout = new QVBoxLayout();
    QLabel *entryLabel = new QLabel(text);

    QLineEdit *res = new QLineEdit();
    res->setMinimumWidth(minL);
    res->setMaximumWidth(maxL);
    res->setValidator(new QDoubleValidator);

    entryLayout->addWidget(entryLabel);
    entryLayout->addWidget(res);

    entryLayout->setSpacing(0);

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
    QString defaultFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveSpectra.csv";
    dataDir->setText(defaultFile);
    this->errorMessage("WARNING: StochasticWave - spectra ideal filename had not been set when trying to call copyFiles(), using default file: " + dataDir->text());
    QFile::copy(dataDir->text(), destDir);
    return true;
  }
  else 
    QFile::copy(dataDir->text(), destDir);


  // QString spectraFileName = dataDir->text();
  // QString timeSeriesFileName = timeSeriesDir->text();
  // timeSeriesFileName.replace("WaveSpectra.csv", "WaveSpectraGenerated.csv"); // temp fix assuming spectra file name
  // if (dataDir->text().isEmpty()) {
  //   dataDir->setText(":Examples/hdro-0005/data/WaveTimeSeries.csv");
  //   this->errorMessage("WARNING: StochasticWave - spectra generated filename had not been set when trying to call copyFiles(), using default file: " + dataDir->text());
  //   QFile::copy(dataDir->text(), destDir);
  //   return true;
  // }

  if (timeSeriesDir->text().isEmpty()) {
    QString defaultFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveTimeSeries.csv";
    timeSeriesDir->setText(defaultFile);
    this->errorMessage("WARNING: StochasticWave - time series filename had not been set when trying to call copyFiles(), using default file: " + timeSeriesDir->text());
    QFile::copy(timeSeriesDir->text(), destDir);
    return true;
  }
  else 
    QFile::copy(timeSeriesDir->text(), destDir);

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
  thePlotTimeSeries->hide();
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


  // seed->setEnabled(false);
  seed->setValue(500);
  useSeed->setChecked(false);
  dataDir->setText("");
  timeSeriesDir->setText("");
  thePlot->clear();
  thePlotTimeSeries->clear();
  // exposureCategory->setCurrentIndex(0);
}

void
Jonswap::updateDistributionPlot() {
    int numSteps = 100;
    int numStepsTimeSeries = 100;
    if (dataDir->text().isEmpty()) {
        QString defaultFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveSpectra.csv";
        dataDir->setText(defaultFile);
        this->errorMessage("ERROR: StochasticWave - wave-spectra data has not been set, using default");
        // return;
    }
    if (timeSeriesDir->text().isEmpty()) {
        QString defaultFile = QCoreApplication::applicationDirPath() + QDir::separator() + "Examples" + QDir::separator() + "WaveMaker" + QDir::separator() + "WaveTimeSeries.csv";
        timeSeriesDir->setText(defaultFile);
        this->errorMessage("ERROR: StochasticWave - time-series data has not been set, using default");
        // return;
    }

    QString csvFileName = dataDir->text();
    QFile csv(csvFileName);
    csv.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&csv);

    QString csvFileNameTimeSeries = timeSeriesDir->text();
    QFile csvTimeSeries(csvFileNameTimeSeries);
    csvTimeSeries.open(QFile::ReadOnly | QFile::Text);
    QTextStream inTimeSeries(&csvTimeSeries);

    QStringList row;
    QStringList firstColumn;
    QStringList secondColumn;

    QStringList rowTimeSeries;
    QStringList firstColumnTimeSeries;
    QStringList secondColumnTimeSeries;

    numSteps = 0; // reset
    numStepsTimeSeries = 0; // reset

    // Assume no header lines
    while (readCSVRowSpectra(in, &row)) {
        firstColumn.append(row[0]);
        secondColumn.append(row[1]);
        numSteps++;
    }
    csv.close();

    while (readCSVRowSpectra(inTimeSeries, &rowTimeSeries)) {
        firstColumnTimeSeries.append(rowTimeSeries[0]);
        secondColumnTimeSeries.append(rowTimeSeries[1]);
        numStepsTimeSeries++;
    }
    csvTimeSeries.close();
    
    
    QVector<double> x(numSteps); // time
    QVector<double> y(numSteps); // displacement
    for (int i=0; i<numSteps; i++) {
        x[i] = firstColumn[i].toDouble();
        y[i] = secondColumn[i].toDouble();
    }

    QVector<double> xG(numStepsTimeSeries); // time
    QVector<double> yG(numStepsTimeSeries); // displacement
    for (int i=0; i<numStepsTimeSeries; i++) {
        xG[i] = firstColumnTimeSeries[i].toDouble();
        yG[i] = secondColumnTimeSeries[i].toDouble();
    }
    thePlot->clear();
    thePlot->drawPDF(x,y);
    thePlot->show();




    // look for the file WaveTimeSeries.csv adjacent to the WaveSpectra.csv
    // QString spectraFileName = csvFileName;
    // QString timeSeriesFileName = csvTimeSeries;//.fileName();

    // spectraFileName.replace("WaveSpectra.csv", "WaveSpectraGenerated.csv");
    // QFile spectraFile(spectraFileName);
    // spectraFile.open(QFile::ReadOnly | QFile::Text);

    // QFile timeSeriesFile(timeSeriesFileName);
    // timeSeriesFile.open(QFile::ReadOnly | QFile::Text);


    // QTextStream inSpectra(&spectraFile);
    // QTextStream inTimeSeries(&timeSeriesFile);

    // plot
    // thePlot->addLine(xG,yG, 1, 65, 74, 82);
    thePlotTimeSeries->clear();
    thePlotTimeSeries->drawPDF(xG,yG);
    thePlotTimeSeries->show();
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
  thePlotTimeSeries->hide();


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
        // exposureCategory->setCurrentIndex(exposureCategory->findText(exposure));
      }
  }

  if (jsonObject.contains("seed")) {
    QJsonValue theValue = jsonObject["seed"];
    if (theValue.isString()) {
      useSeed->setChecked(false);
    } else if (theValue.isDouble()) {
      useSeed->setChecked(true);
      seed->setValue(theValue.toInt());
    }
  }
  else { 
    if (jsonObject.value("seed").isString()) {
      seed->setEnabled(false);    
    } else {
      seed->setEnabled(true);
      seed->setValue(jsonObject.value("seed").toInt());    
    }
  }
  // theDomainImageButton->show();

  thePlot->clear();
  thePlotTimeSeries->clear();
  updateDistributionPlot();
  thePlot->show();
  thePlotTimeSeries->show();


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
