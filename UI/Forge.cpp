//
// Created by jwc on 2/16/19.
//

#include "MainUI.h"
#include "Forge.h"
#include <QtCore>
#include <QtWidgets/QFileDialog>
#include <DepthForgeWin.h>

Forge::Forge(UI *parent) : UI(parent)
{
    hasMouse = false;
    mouseDown &= Qt::MouseButton::NoButton;
    mouseX = mouseY = 0.0;

    QString fileName = QFileDialog::getOpenFileName(
            ((MainUI *)rootElement())->owner, ("Open Image File"),
                                                   "/home/Pictures",
                                                    ("Images (*.png *.jpg)"));

    if (fileName.isNull())
    {
        src = new Image(1,1);
    } else {
        QImage A;
        //A.load(QCoreApplication::tr("/home/jwc/Pictures/Danielle.jpg"));
        A.load(fileName);

        QImage::Format f = A.format();

        if (!A.hasAlphaChannel() && A.format() == QImage::Format_RGB32) {
            QImage B = QImage(A.width(), A.height(), QImage::Format_ARGB32);

            GfxBlt(PixType_BGRA, A.bits(), 0, 0, A.width(), A.height(), A.width(),
                   PixType_ARGB, B.bits(), 0, 0, B.width(), B.height(), B.width());

            A = B;
        }

        src = new Image(A.width(), A.height());

        GfxBlt(PixType_ARGB, A.bits(), 0, 0, A.width(), A.height(), A.width(),
               PixType_ARGB, src->imageMemory, 0, 0, src->Width, src->Height, src->stride);
    }

}

Forge::~Forge()
{
    delete src;
}

void Forge::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    _x = xReal;
    _y = yReal;

    _w = width.get();
    _h = height.get();

    int _x1 = xReal;
    int _y1 = yReal;

    int _w1 = width.get();
    int _h1 = height.get();

    GfxFitRect(0, 0, src->Width, src->Height, &_x, &_y, &_w, &_h);

    target->DrawImage(_x,_y,_w,_h, PixOp_SRC, ZOp_SRC, src, 0, 0, src->Width, src->Height);

    if (hasMouse)
    {
        int xx = mouseX * _w + _x;
        int yy = mouseY * _h + _y;

        Lense *lense = ((MainUI *) rootElement())->lense;

        int sz = lense->size * fmax(_w,_h);

        for (int y=yy-sz; y<yy+sz; y++) {
            for (int x = xx - sz; x < xx + sz; x++) {
                if (y>=_y1 && y < (_y1+_h1)) {
                    if (x >= _x1 && x < (_x1 + _w1)) {
                        double lx = (y-yy) / (double) sz;
                        double ly = (x-xx) / (double) sz;

                        float l = lense->get(lx,ly);

                        ARGB p = {(unsigned char) (0x80*l), 0xFF,0xFF,0xFF };

                        ARGB dest = target->pix[y][x];
                        dest.r = valValAlpha(dest.r, p.r, p.a);
                        dest.g = valValAlpha(dest.g, p.g, p.a);
                        dest.b = valValAlpha(dest.b, p.b, p.a);
                        dest.a = valValAlpha(dest.a, p.a, p.a);
                        target->pix[y][x] = dest;

                    }
                }
            }
        }

    }
}

void Forge::applyLense()
{
    int xx = mouseX * src->Width;
    int yy = mouseY * src->Height;

    Lense *lense = ((MainUI *) rootElement())->lense;

    int sz = lense->size * fmax(src->Width,src->Height);

    Qt::MouseButtons l;
    l.setFlag(Qt::MouseButton::LeftButton);

    Qt::MouseButtons r;
    r.setFlag(Qt::MouseButton::RightButton);

    double dir;

    if (mouseDown == l) dir = -1; else if (mouseDown == r) dir = 1; else return;

    for (int y=yy-sz; y<yy+sz; y++) {
        for (int x = xx - sz; x < xx + sz; x++) {
            if (y >= 0 && y < (src->Height)) {
                if (x >= 0 && x < (src->Width)) {
                    double lx = (y - yy) / (double) sz;
                    double ly = (x - xx) / (double) sz;

                    float l = lense->get(lx, ly);

                    src->z[y][x] += l * .01 * dir;

                }
            }

        }
    }

}

void Forge::mouseEnter()
{
    hasMouse = true;
    UI::mouseEnter();
}

void Forge::mouseLeave()
{
    hasMouse = false;
    UI::mouseLeave();
}

bool Forge::mouseMove(int x, int y)
{
    mouseX = (x - (_x-xReal)) / (double) _w;
    mouseY = (y - (_y-yReal)) / (double) _h;

    applyLense();

    bool rc = UI::mouseMove(x,y);

    return rc;
}

bool Forge::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    mouseX = (x - (_x-xReal)) / (double) _w;
    mouseY = (y - (_y-yReal)) / (double) _h;

    mouseDown.setFlag(button, true);

    applyLense();

    bool rc = UI::mouseButtonPress(x,y,button);

    return rc;
}

bool Forge::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    mouseDown.setFlag(button, false);

    bool rc = UI::mouseButtonRelease(x,y,button);

    return rc;
}
