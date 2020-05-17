/*********************************************************************************
**
** Copyright (c) 2020 The University of Notre Dame
**
** Redistribution and use in source and binary forms, with or without modification,
** are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice, this
** list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice, this
** list of conditions and the following disclaimer in the documentation and/or other
** materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors may
** be used to endorse or promote products derived from this software without specific
** prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
** EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
** SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
** TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
** BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
** IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
**
***********************************************************************************/

// Contributors:
// Written by Ajay B Harish, for SimCenter @ UC Berkeley, director: Sanjay GOvindjee at UC Berkeley

#include <QMouseEvent>
#include <QString>
#include <QGLWidget>
#include <OpenGL/glu.h>
#include <iostream>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    : QOpenGLWidget (parent)
{

}

//*********************************************************************************
// Initialize OpenGL
//*********************************************************************************
void MyOpenGLWidget::initializeGL()
{
    flag = 0;
    float r, g, b;
    float a = normaliza_0_1(255.0f, RGB_MIN, RGB_MAX);
    initializeOpenGLFunctions();
    qColorToRGB(Qt::lightGray,r,g,b);
    glClearColor(r, g, b, a);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

//*********************************************************************************
// Resize OpenGL widget
//*********************************************************************************
void MyOpenGLWidget::resizeGL(int w, int h)
{

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//*********************************************************************************
// PaintGL: To draw on the OpenGL widget
//*********************************************************************************
void MyOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resizeGL(SCREENWIDTH,SCREENHEIGHT);
    glLoadIdentity();

    // Load the object that will be plotted
    void defineobject();
}

//*********************************************************************************
// MOUSE CLICK ROUTINES
//*********************************************************************************

//*********************************************************************************
// Mouse event: Double click
//*********************************************************************************
void MyOpenGLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    onMouseEvent("Double click", event->pos());
}

//*********************************************************************************
// Mouse event: movement of mouse after a single click
//*********************************************************************************
void MyOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    onMouseEvent("Move", event->pos());
}

//*********************************************************************************
// Mouse event: mouse pressed for single click
//*********************************************************************************
void MyOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    onMouseEvent("Press", event->pos());
}

//*********************************************************************************
// Mouse event: mouse released from single click
//*********************************************************************************
void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    onMouseEvent("Release", event->pos());
}

//*********************************************************************************
// What to do on mouse click
//*********************************************************************************
void MyOpenGLWidget::onMouseEvent(const QString &eventName, const QPoint &pos)
{
    if(eventName.toStdString() == "Double click")
    {
        std::cout << "Event is: " << eventName.toStdString() << "\n";
        std::cout << "X-point is: " << pos.x() << "\n";
        std::cout << "Y-point is: " << pos.y() << "\n";
        std::cout << "Flag is: " << flag << "\n";
        flag = 10;
        std::cout << "Flag is: " << flag << "\n";
        update();
    }

}

//*********************************************************************************
// OPENGL HELPER ROUTINES
//*********************************************************************************

//*********************************************************************************
// Routine to change qColor to RGB
//*********************************************************************************
void MyOpenGLWidget::qColorToRGB(const QColor &C, float &r, float &g, float &b) const
{
    r = normaliza_0_1(C.red(), RGB_MIN, RGB_MAX);
    g = normaliza_0_1(C.green(), RGB_MIN, RGB_MAX);
    b = normaliza_0_1(C.blue(), RGB_MIN, RGB_MAX);
}

//*********************************************************************************
// Normalization of values
//*********************************************************************************
float MyOpenGLWidget::normaliza_0_1(float val, float min, float max) const
{
    return (val - min)/(max - min);
}

//*********************************************************************************
// Routine to define the object that needs to be plotted with OpenGL
//*********************************************************************************
void MyOpenGLWidget::defineobject()
{
    float r, g, b;
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    qColorToRGB(Qt::red,r,g,b);
    glColor3f(r, g, b);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    qColorToRGB(Qt::blue,r,g,b);
    glColor3f(r, g, b);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    qColorToRGB(Qt::green,r,g,b);
    glColor3f(r, g, b);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();


    if(flag == 0)
    {
        glColor3f(1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 0, 0);
            glVertex3f(1, 0, 0);
            glVertex3f(0, 0.5, 0);
        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(-1,0,0);
            glVertex3f(0,0.5,0);
        glEnd();

        glColor3f(0, 0, 1);
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(-1,0,0);
            glVertex3f(0,0.5,0);
        glEnd();
    }
}
