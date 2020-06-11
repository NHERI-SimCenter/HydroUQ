#include "optionsframe.h"
#include "ui_optionsframe.h"
#include <dependencies/rapidjson/document.h>
#include <dependencies/rapidjson/prettywriter.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <sys/stat.h>


OptionsFrame::OptionsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OptionsFrame)
{
    ui->setupUi(this);
}

OptionsFrame::~OptionsFrame()
{
    delete ui;
}


void OptionsFrame::on_But_GenFiles_clicked()
{
    std::stringstream ss_date;
    time_t t = time(0);
    struct tm * now = localtime(&t);
    ss_date << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-'
            << now->tm_mday;
    rapidjson::StringBuffer s;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("version");
    writer.String("1.0");
    writer.Key("data");
    writer.String(ss_date.str().c_str());
    writer.EndObject();
    std::ofstream of("/Users/ajaybh/Desktop/trial.txt");
    of << s.GetString();
}
