//
// Created by jwc on 3/26/19.
//

#ifndef DEPTHFORGE_GENBUTTONS_H
#define DEPTHFORGE_GENBUTTONS_H

#include <QApplication>
#include <QMainWindow>

#include "Image/Image.h"

class Wij : public QWidget
{
public:
    Wij(QWidget *parent);

    virtual void paintEvent(QPaintEvent *evt);
};


#endif //DEPTHFORGE_GENBUTTONS_H
