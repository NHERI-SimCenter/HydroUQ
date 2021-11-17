#include "buildings.h"
#include "ui_buildings.h"

//*********************************************************************************
// Building settings
//*********************************************************************************
buildings::buildings(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::buildings)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);

    // Set the simulation type
    simtype = type;
}

//*********************************************************************************
// Delete building settings
//*********************************************************************************
buildings::~buildings()
{
    delete ui;
}

//*********************************************************************************
// Refresh building settings
//*********************************************************************************
void buildings::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);

    // Set the simulation type
    simtype = type;
}

//*********************************************************************************
// Reset data
//*********************************************************************************
void buildings::resetData()
{
    ui->CmB_BuildData->setCurrentIndex(0);
    ui->Tbl_Building->setRowCount(0);
    ui->PText_CustomBuild->clear();
    STLfilenames.removeAll(QString(""));
    ui->DSpBx_CoastDist->clear();
    ui->DSpBx_NumBuildX->clear();
    ui->DSpBx_NumBuildY->clear();
    ui->DSpBx_BuildDistX->clear();
    ui->DSpBx_BuildDistY->clear();
    ui->DSpBx_BuildSize01->clear();
    ui->DSpBx_BuildSize02->clear();
    ui->DSpBx_BuildSize03->clear();
    ui->DSpBx_OffsetX->clear();
    ui->DSpBx_OffsetY->clear();
    ui->CmB_BuildDist->setCurrentIndex(0);
    ui->CmB_BuildShape->setCurrentIndex(0);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void buildings::hideshowelems(int type)
{
    // Set the Combo box
    simtype = type;
    on_CmB_BuildData_currentIndexChanged(ui->CmB_BuildData->currentIndex());
}

//*********************************************************************************
// Get data from buildings
//*********************************************************************************
bool buildings::getData(QMap<QString, QString>& map,int type)
{
    bool hasData=false;
    (void) type; // Variable is unused

    // Initialize simulation type
    simtype = type;

    // Define type of building definition
    if(ui->CmB_BuildData->currentIndex() == 0) //Manual by table
    {
        map.insert("BuildData","Manual");

        int numbuilding = ui->Tbl_Building->rowCount();

        // Write data from the table
        //map.insert("NumBuild",QString::number(ui->Tbl_Building->rowCount()));
        if(ui->Tbl_Building->rowCount() > 0)
        {
            int buildnum = 0;
            for(int ii=0; ii<ui->Tbl_Building->rowCount(); ++ii)
            {

                // Get the current building type
                QComboBox *myCB = qobject_cast<QComboBox*>(ui->Tbl_Building->cellWidget(ii,0));
                int InputComboData = myCB->currentIndex();

                // Create flags
                int buildflag = 0;

                // Check if items in the table are empty
                QTableWidgetItem* item02 = ui->Tbl_Building->item(ii,1);
                QTableWidgetItem* item03 = ui->Tbl_Building->item(ii,2);

                // Initialize the string
                QString segdata = "";
                // Column 01
                int buildcode = getbuildcode(InputComboData);
                segdata = QString::number(buildcode);
                segdata += ",";

                // Check for missing data to ignore building
                if(buildcode == -2)
                {
                    if(!item03)
                    {
                        buildflag = 1;
                    }
                }
                else if(buildcode == 1)
                {
                    if(!item03)
                    {
                        buildflag = 1;
                    }
                }
                if( (!item02) && (!item03))
                {
                    buildflag = 1;
                }

                // If critical data missing ignore building
                if (buildflag == 1)
                {
                    // Reduce number of building
                    numbuilding -=1;
                }
                else
                {
                    // Column 02
                    if(!item02)
                    {
                        segdata += "0,0,0";
                    }
                    else
                    {
                        QStringList segtemp = ui->Tbl_Building->item(ii,1)->text().split(',');
                        if (segtemp.size() == 3)
                        {
                            segdata += ui->Tbl_Building->item(ii,1)->text();
                        }
                        else if(segtemp.size() == 1)
                        {
                            if(segtemp[0].isEmpty())
                                segdata += "0,0,0";
                            else
                                buildflag = 1;
                        }
                        else
                        {
                            buildflag = 1;
                        }
                    }

                    // Add separator
                    segdata += ",";

                    // Column 03
                    if(!item03)
                    {
                        segdata += "0,0,0";
                    }
                    else
                    {
                        QStringList segtemp = ui->Tbl_Building->item(ii,2)->text().split(',');
                        if (segtemp.size() == 3)
                        {
                            segdata += ui->Tbl_Building->item(ii,2)->text();
                        }
                        else if(segtemp.size() == 1)
                        {
                            if(segtemp[0].isEmpty())
                                segdata += "0,0,0";
                            else
                                buildflag = 1;
                        }
                        else
                        {
                            buildflag = 1;
                        }
                    }

                    // Check if there were any errors created
                    // If errors ignore the building
                    // Else add it
                    if (buildflag == 1)
                    {
                        numbuilding -= 1;
                    }
                    else
                    {
                        // Insert building into the map
                        map.insert("BuildingTable"+QString::number(buildnum),segdata);

                        // Increment building number
                        buildnum += 1;
                    }
                }
            }

            // Insert number of buildings to map
            map.insert("NumBuild",QString::number(numbuilding));
        }
    }
    else if(ui->CmB_BuildData->currentIndex() == 1) //From parameters
    {
        map.insert("BuildData","Parameters");
        map.insert("BuildDist",QString::number(ui->CmB_BuildDist->currentIndex()));
        map.insert("BuildShape",QString::number(ui->CmB_BuildShape->currentIndex()));
        map.insert("NumBuildX",ui->DSpBx_NumBuildX->textFromValue(ui->DSpBx_NumBuildX->value()));
        map.insert("NumBuildY",ui->DSpBx_NumBuildY->textFromValue(ui->DSpBx_NumBuildY->value()));
        map.insert("DistBuildX",ui->DSpBx_BuildDistX->textFromValue(ui->DSpBx_BuildDistX->value()));
        map.insert("DistBuildY",ui->DSpBx_BuildDistY->textFromValue(ui->DSpBx_BuildDistY->value()));
        map.insert("DistCoast",ui->DSpBx_CoastDist->textFromValue(ui->DSpBx_CoastDist->value()));
        map.insert("CoastX",ui->DSpBx_OffsetX->textFromValue(ui->DSpBx_OffsetX->value()));
        map.insert("CoastY",ui->DSpBx_OffsetY->textFromValue(ui->DSpBx_OffsetY->value()));
        map.insert("BuildSizePara01",ui->DSpBx_BuildSize01->textFromValue(ui->DSpBx_BuildSize01->value()));
        map.insert("BuildSizePara02",ui->DSpBx_BuildSize02->textFromValue(ui->DSpBx_BuildSize02->value()));
        map.insert("BuildSizePara03",ui->DSpBx_BuildSize03->textFromValue(ui->DSpBx_BuildSize03->value()));
    }

    // Upload only the first STL file
    if(STLfilenames.size() > 0)
    {
        QFile f(STLfilenames[0]);
        QFileInfo fileInfo(f.fileName());
        QString filename(fileInfo.fileName());
        map.insert("BuildingSTLFile",filename);
    }

    // Change hasData to be true
    hasData = true;

    // Return the bool
    return hasData;
}

//*********************************************************************************
// Get building code
//*********************************************************************************
int buildings::getbuildcode(int index)
{
    // Initialize code
    int code = 0;

    // Get a building code
    if (index == 0)
        code = -2; // Res + Cuboid
    else if (index == 1)
        code = -1; // Res + STL
    else if (index == 2)
        code = 1; // No-Res + Cuboid
    else if (index == 3)
        code = 2; // No-Res + STL

    // Return the building code
    return code;
}

//*********************************************************************************
// Put building code: Get combobox index from code
//*********************************************************************************
int buildings::putbuildcode(int code)
{
    // Initialize index
    int index = 0;

    // Get a building code
    if (code == -2) // Res + Cuboid
        index = 0;
    else if (code == -1) // Res + STL
        index = 1;
    else if (code == 1) // No-Res + Cuboid
        index = 2;
    else if (code == 2) // No-Res + STL
        index = 3;

    // Return the combo box index
    return index;
}

//*********************************************************************************
// Put data into buildings from the JSON file
//*********************************************************************************
bool buildings::putData(QJsonObject &jsonObject,int stype, QString workpath)
{
    // Suppress warnings
    (void) stype;

    // Reset the data
    resetData();

    // Get the type of building definition
    int buildindex = -1;
    if(jsonObject.contains("BuildData"))
    {
        // Get the type of building definition
        QString builddatatype = jsonObject["BuildData"].toString();

        // Set if it is manual or parameters
        if(QString::compare(builddatatype, "Manual", Qt::CaseInsensitive) == 0)
        {
            ui->CmB_BuildData->setCurrentIndex(0);
            buildindex = 0;
        }
        else if (QString::compare(builddatatype, "Parameters", Qt::CaseInsensitive) == 0)
        {
            ui->CmB_BuildData->setCurrentIndex(1);
            buildindex = 1;
        }
    }

    // Set up the building table
    if(buildindex == 0) // Manual
    {
        int numbuildings = jsonObject["NumBuild"].toString().toInt();
        if(numbuildings > 0)
        {
            for(int ii=0; ii<numbuildings; ++ii)
            {
//              Add a row for the building
//                ui->Tbl_Building->insertRow(ui->Tbl_Building->rowCount());

//              Add the particular building parameters
                if(jsonObject.contains("BuildingTable"+QString::number(ii)))
                {
//                  Get the parameters for each building / building table row
                    QString building = jsonObject["BuildingTable"+QString::number(ii)].toString();

                    QStringList buildingdata = building.split(',');
                    if (buildingdata.size() == 7)
                    {
//                        QTableWidgetItem* itemtoAdd = new QTableWidgetItem();
                        QTableWidgetItem* itemtoAdd2 = new QTableWidgetItem();
                        QTableWidgetItem* itemtoAdd3 = new QTableWidgetItem();
                        int tempindex = putbuildcode(buildingdata[0].toInt());
                        addBuildRow(tempindex);
                        itemtoAdd2->setText(buildingdata[1]+","+buildingdata[2]+","+buildingdata[3]);
                        ui->Tbl_Building->setItem(ii,1,itemtoAdd2);
                        itemtoAdd3->setText(buildingdata[4]+","+buildingdata[5]+","+buildingdata[6]);
                        ui->Tbl_Building->setItem(ii,2,itemtoAdd3);

                    }
//                    if(buildingdata.size() == 4)
//                    {
//                        QTableWidgetItem* itemtoAdd = new QTableWidgetItem();
//                        QTableWidgetItem* itemtoAdd2 = new QTableWidgetItem();
//                        QTableWidgetItem* itemtoAdd3 = new QTableWidgetItem();
//                        itemtoAdd->setText(buildingdata[0]);
//                        ui->Tbl_Building->setItem(ii,0,itemtoAdd);
//                        itemtoAdd2->setText(buildingdata[1]+","+buildingdata[2]);
//                        ui->Tbl_Building->setItem(ii,1,itemtoAdd2);
//                        itemtoAdd3->setText(buildingdata[3]);
//                        ui->Tbl_Building->setItem(ii,2,itemtoAdd3);
//                    }
                }
            }
        }
    }
    else if(buildindex == 1) // Parameters
    {
        // Set building distribution
        if(jsonObject.contains("BuildDist"))
            ui->CmB_BuildDist->setCurrentIndex(jsonObject["BuildDist"].toString().toInt());
        // Set building shape
        if(jsonObject.contains("BuildShape"))
            ui->CmB_BuildShape->setCurrentIndex(jsonObject["BuildShape"].toString().toInt());
        // Number of buildings in X-Y direction
        if(jsonObject.contains("NumBuildX"))
            ui->DSpBx_NumBuildX->setValue(jsonObject["NumBuildX"].toString().toDouble());
        if(jsonObject.contains("NumBuildY"))
            ui->DSpBx_NumBuildX->setValue(jsonObject["NumBuildY"].toString().toDouble());
        // Number of buildings in X-Y direction
        if(jsonObject.contains("DistBuildX"))
            ui->DSpBx_BuildDistX->setValue(jsonObject["DistBuildX"].toString().toDouble());
        if(jsonObject.contains("DistBuildY"))
            ui->DSpBx_BuildDistY->setValue(jsonObject["DistBuildY"].toString().toDouble());
        // Coordinate of coast in X-Y direction
        if(jsonObject.contains("CoastX"))
            ui->DSpBx_OffsetX->setValue(jsonObject["CoastX"].toString().toDouble());
        if(jsonObject.contains("CoastY"))
            ui->DSpBx_OffsetY->setValue(jsonObject["CoastY"].toString().toDouble());
        // Building size parameter 1 / 2/ 3
        if(jsonObject.contains("BuildSizePara01"))
            ui->DSpBx_BuildSize01->setValue(jsonObject["BuildSizePara01"].toString().toDouble());
        if(jsonObject.contains("BuildSizePara02"))
            ui->DSpBx_BuildSize02->setValue(jsonObject["BuildSizePara02"].toString().toDouble());
        if(jsonObject.contains("BuildSizePara03"))
            ui->DSpBx_BuildSize03->setValue(jsonObject["BuildSizePara03"].toString().toDouble());
    }

    // Get the custom STL file
    if(!workpath.isEmpty())
    {
        if(jsonObject.contains("BuildingSTLFile"))
        {
            // Set the STL file if exists
            QString filename = jsonObject["BuildingSTLFile"].toString();
            QFileInfo fi(QDir(workpath),filename);
            STLfilenames.append(fi.canonicalFilePath());
            ui->PText_CustomBuild->setText(STLfilenames.join(";\n\n"));
        }
    }

    // Return true
    return true;
}

//*********************************************************************************
// Add building
//*********************************************************************************
void buildings::on_Btn_AddBuild_clicked()
{
    // Create a row
    ui->Tbl_Building->insertRow(ui->Tbl_Building->rowCount());

    // Add the combo box
    QComboBox *combo;
    combo = new QComboBox;
    QStringList comboitems = {"Response (Yes): Cuboid shape building", "Response (Yes): STL", "Response (No): Cuboid shape building", "Response (No): STL"};
    combo->addItems(comboitems);
    combo->setObjectName("BuiltTypeCombo"+QString::number(ui->Tbl_Building->rowCount()-1));

    // Add the combobox
    ui->Tbl_Building->setCellWidget(ui->Tbl_Building->rowCount()-1,0,combo);

    // Adjust the size
    ui->Tbl_Building->resizeColumnsToContents();
}

//*********************************************************************************
// Add building
//*********************************************************************************
void buildings::addBuildRow(int index)
{
    // Create a row
    ui->Tbl_Building->insertRow(ui->Tbl_Building->rowCount());

    // Add the combo box
    QComboBox *combo;
    combo = new QComboBox;
    QStringList comboitems = {"Response (Yes): Cuboid shape building", "Response (Yes): STL", "Response (No): Cuboid shape building", "Response (No): STL"};
    combo->addItems(comboitems);
    combo->setCurrentIndex(index);
    combo->setObjectName("BuiltTypeCombo"+QString::number(ui->Tbl_Building->rowCount()-1));

    // Add the combobox
    ui->Tbl_Building->setCellWidget(ui->Tbl_Building->rowCount()-1,0,combo);

    // Adjust the size
    ui->Tbl_Building->resizeColumnsToContents();
}

//*********************************************************************************
// Delete building
//*********************************************************************************
void buildings::on_Btn_RemBuild_clicked()
{
    ui->Tbl_Building->removeRow(ui->Tbl_Building->currentRow());
}

//*********************************************************************************
// Combo box for building data
//*********************************************************************************
void buildings::on_CmB_BuildData_currentIndexChanged(int index)
{

    // Hide items by detault
    ui->GroupNonpara->hide();
    ui->GroupPara->hide();
    ui->Lbl_Notice->hide();
    ui->Btn_CustomBuild->hide();
    ui->PText_CustomBuild->hide();

    // Manually add buildings using table
    if(index == 0)
    {
        ui->GroupNonpara->show();
        ui->Tbl_Building->setHorizontalHeaderItem(0,new QTableWidgetItem("Type"));
        if((simtype == 3) || (simtype == 4))
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (x,y,z)"));
        }
        else
        {
            ui->Tbl_Building->setHorizontalHeaderItem(1,new QTableWidgetItem("Center (Lat,Long,Elevation)"));
        }
        ui->Btn_AddBuild->setText("Add building");
        ui->Btn_RemBuild->setText("Remove building");
        ui->Lbl_Building->setText("Building table");
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("Check the documentation to prepare the STL files for custom building shapes");
        ui->Btn_CustomBuild->show();
        ui->PText_CustomBuild->show();
        // Adjust the size
        ui->Tbl_Building->resizeColumnsToContents();
    }
    // Add buildings using parametric
    else if(index == 1)
    {
        ui->GroupPara->show();
        on_CmB_BuildShape_currentIndexChanged(ui->CmB_BuildShape->currentIndex());
    }
}

//*********************************************************************************
// Copyfiles
//*********************************************************************************
bool buildings::copyFiles(QString dirName,int type)
{

    // Void type
    (void) type;

    // If files are selected, then copy the STL files
    if(STLfilenames.size() > 0)
    {
        QFile fileToCopy(STLfilenames[0]);
        QFileInfo fileInfo(STLfilenames[0]);
        QString theFile = fileInfo.fileName();
        fileToCopy.copy(dirName + QDir::separator() + theFile);
    }

    // Return if data exists
    return true;
}

//*********************************************************************************
// Building shape for parametric definition
//*********************************************************************************
void buildings::on_CmB_BuildShape_currentIndexChanged(int index)
{

    // Show for custom build
    if(index == 0)
    {
        // Hide about STL file
        ui->Btn_CustomBuild->hide();
        ui->PText_CustomBuild->hide();
        ui->Lbl_Notice->hide();

        // Hide building sizes
        ui->Lbl_BuildSize->hide();
        ui->DSpBx_BuildSize01->hide();
        ui->DSpBx_BuildSize02->hide();
        ui->DSpBx_BuildSize03->hide();
    }
    else if (index == 1)
    {
        // Hide about STL file
        ui->Btn_CustomBuild->hide();
        ui->PText_CustomBuild->hide();
        ui->Lbl_Notice->hide();

        // Show building sizes
        ui->Lbl_BuildSize->show();
        ui->DSpBx_BuildSize01->show();
        ui->DSpBx_BuildSize02->show();
        ui->DSpBx_BuildSize03->show();
    }
    else if(index == 2)
    {
        // Show about STL file
        ui->Btn_CustomBuild->show();
        ui->PText_CustomBuild->show();
        ui->Lbl_Notice->show();
        ui->Lbl_Notice->setText("Check the documentation to prepare the STL files for custom building shapes");

        // Hide building sizes
        ui->Lbl_BuildSize->hide();
        ui->DSpBx_BuildSize01->hide();
        ui->DSpBx_BuildSize02->hide();
        ui->DSpBx_BuildSize03->hide();
    }
}

//*********************************************************************************
// Button click to upload STL file for custom building
//*********************************************************************************
void buildings::on_Btn_CustomBuild_clicked()
{
    // Open a dialog window to select the files
    // Here one can select multiple files
    // The selected files are stored in the String list STLfilenames
    QFileDialog selectfilesdialog(this);
    selectfilesdialog.setFileMode(QFileDialog::ExistingFiles);
    selectfilesdialog.setNameFilter(tr("All files (*.stl)"));
    if(selectfilesdialog.exec()) STLfilenames = selectfilesdialog.selectedFiles();
    if(STLfilenames.size() == 0)
    {
        //error.warnerrormessage("No files selected!");
    }
    else
    {
        ui->PText_CustomBuild->setText(STLfilenames[0]);
    }
}
