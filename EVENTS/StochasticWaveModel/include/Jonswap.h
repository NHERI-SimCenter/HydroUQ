#ifndef _JONSWAP_H
#define _JONSWAP_H

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

// Written: mhgardner
#include <SimCenterAppWidget.h>
#include <QPushButton>
#include <QJsonObject>
#include <QString>

// #include <LineEditRV.h>
// #include <QFormLayout>
// #include <QLabel>
// #include <QLineEdit>
// #include <QRadioButton>
// #include <QSpinBox>
// #include <QWidget>
// #include <RandomVariablesContainer.h>
// Forward declarations
class SimCenterGraphPlot;
class SC_ComboBox;
class LineEditRV;
class QJsonObject;
class QLabel;
class QLineEdit;
class QRadioButton;
class QSpinBox;

class QPushButton;
class QComboBox;
class RandomVariablesContainer;
class SC_IntLineEdit;
// class SC_FileEdit;
class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;
class QWidget;
class QScrollArea;
// class QFormLayout;

/**
 * Widget for inputting parameters for stochastic earthquake time history
 * generation model
 */
class Jonswap : public SimCenterAppWidget {
  Q_OBJECT

  public:
    /**
     * @constructor Construct new stochastic model input widget
     * @param[in, out] random_variables Widget to store random variables to
     * @param[in, out] parent Pointer to parent widget. Defaults to nullptr.
     */
    explicit Jonswap(RandomVariablesContainer* random_variables,
          QWidget* parent = nullptr);

    /**
     * @destructor Virtual desctructor for stochastic model input widget
     */
    virtual ~Jonswap() {};

    /**
     * Instantiate stochastic motion input widget from input JSON object
     * @param[in] jsonObject JSON object containing input information
     * @return Returns true if successful, false otherwise
     */
    bool inputFromJSON(QJsonObject& jsonObject);

    /**
     * Write all current class data to JSON required to reconstruct class
     * @param[in, out] jsonObject JSON object to write output to
     * @return Returns true if successful, false otherwise
     */
    bool outputToJSON(QJsonObject& jsonObject);

    bool inputAppDataFromJSON(QJsonObject& jsonObject);

    /**
     * Write application name to object and add a black ApplicationData
     * @param[in, out] jsonObject JSON object to write output to
     * @return Returns true if successful, false otherwise
     */

    bool outputAppDataToJSON(QJsonObject& jsonObject);

    /**
     * Read application specific data
     * @param[in, out] jsonObject JSON object to write output to
     * @return Returns true if successful, false otherwise
     */

    bool copyFiles(QString &dirName);

    QString getAbbreviatedName(void);

    QLineEdit *createTextEntry(QString text,
                    QHBoxLayout *theLayout,
                    int minL=100,
                    int maxL=100);

    QLineEdit *createTextEntry(QString text,
                    QGridLayout *theLayout,
                    int col,
                    int minL=100,
                    int maxL=100);


  public slots:
    void computeSpectra(void);

    void updateJSON(void);
  
    void clear(void);

    void updateDistributionPlot(); 

    /**
     * Update ability to provide seed based on changed status of radio button
     * @param[in] checked Current status of radio button for providing seed
     */
    void provideSeed(const bool& checked);

  protected:  

    QLabel *modelDescription; /**< Brief description of model indicating relevant
          paper where more information can be found describing
          model in greater detail */

    LineEditRV *waterDepth; /**< water depth (ft) */
    LineEditRV *tidalSLR; /**< tidal sea level rise (ft) */
    LineEditRV *stormSurgeSLR; /**< storm surge sea level rise (ft) */
    LineEditRV *climateChangeSLR; /**< climate change sea level rise (ft) */
    LineEditRV *significantWaveHeight; /**< significant wave height (ft) */
    LineEditRV *peakPeriod; /**< peak period (s) */
    LineEditRV *recorderOriginX; /**< x-coordinate of recorder origin */
    SC_IntLineEdit *recorderCountZ; /**< number of recorders in z-direction */
    LineEditRV *timeStep; /**< time step (s) */
    LineEditRV *timeDuration; /**< time duration (s) */
    LineEditRV *dragCoefficient; /**< drag Coefficient */
    LineEditRV *dragArea; /**< drag Area */
    QComboBox *exposureCategory; /**< type of wave spectrum */
    QSpinBox *seed; /**< Value to use as seed for motion generation */
    QRadioButton *useSeed; /**< Radio button to indicate whether specific seed
                              value should be used */
    //  SC_FileEdit *spectraFile; /**< file containing wave spectra */
    //  SC_FileEdit *kinematicsFile; /**< file containing bathymetry data */
    SimCenterGraphPlot *thePlot;
    SimCenterGraphPlot *thePlotTimeSeries;
    // QPushButton *theDomainImageButton;
    QLineEdit *dataDir;
    QLineEdit *timeSeriesDir;
    QString inpty;

    // QLineEdit *mean;
    // QLineEdit *standardDev;
    // QLineEdit *alpha;
    // QLineEdit *beta; 
    // QLineEdit *a;
    // QLineEdit *b;
};

#endif  // _KWON_KAREEM_2006_MODEL_H