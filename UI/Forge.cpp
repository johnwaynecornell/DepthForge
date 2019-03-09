//
// Created by jwc on 2/16/19.
//
#include <QtCore>
#include <QtWidgets/QFileDialog>
#include <QFile>
#include <QImageWriter>
#include <QStandardPaths>
#include <Image/PathAdapter.h>


#include "MainUI.h"
#include "Forge.h"
#include "DepthForgeWin.h"
#include "MainWnd.h"

extern QApplication *app;

bool bkgTilePixFunc(int index, double y, ARGB &p, float &z, void *arg)
{
        y = 1.0 - abs(y);

        if (y<0) y = 0;

        //if (y<0) y = 0;
        z = (1.0f- sinf((1.0f-(float) y) * M_PIf32 / 2.0f))*.125f;

        unsigned char v = (unsigned char) (y*0x80);

        p = {0xFF,v,v,v};

        return true;
}

Forge::Forge(UI *parent) : UI(parent)
{
    hasMouse = false;
    mouseDown &= Qt::MouseButton::NoButton;
    mouseX = mouseY = 0.0;

    QString fileName;

    drawInitial();

    previewLense = false;

    bkgTile = new Image(32,32);

    bkgTile->Line(8,8,24,8);
    bkgTile->LineTo(24,24);
    bkgTile->LineTo(8,24);
    bkgTile->LineTo(8,8);

    bkgTile->DrawPath(PixOp_SRC, ZOp_SRC, 1.0f / 8, bkgTilePixFunc, nullptr);

    bkgImage = nullptr;

    void *tmp;
/*
    {
      union
        {   void (Forge::*a)(void *);
            void *b;
        } c;

        c.a = Member
        *((void **)&Recipient) = c.b;
    }
  */
    MainWnd *w = (MainWnd *) ((MainUI *) rootElement())->owner->parent;

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::import, tmp);
    w->import_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_jps, tmp);
    w->export_jps_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_anaglyph, tmp);
    w->export_anaglyph_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
}

Forge::~Forge()
{
    delete src;
}

bool letters(int line, double y, ARGB &p, float &z, void *arg)
{
    //y -= 10;

    y = abs(y);

    if (y <= 6.0 && y>2.0)
    {
        z = -.2;
        p = {0xFF, 0xFF, 0xFF, 0xFF};
    } else
    {
        if (y>6) y -= 6.0;
        else if (y<2) y = 2.0-y;

        y /= 36.0;

        z = 0;
        p = {0xFF,0,0x0,0};

        ARGB wave[] = {
                {0xFF,0xFF,0x00,0xFF}, {0xFF,0x80,0x00,0x80},
                {0xFF,0xA0,0xA0,0xA0}, {0xFF,0x80,0xFF,0x00}
        };

        float zb = 0.0;

        for (int i=0; i<4; i++) {

            y -= .5;

            if (y < 0) goto ret;

            if (y < .5) {
                double q = (y - .5 * .5) / (.5*.5);

                double v = 1.0 - abs(q);

                unsigned char m = (unsigned char) ((v)*0xFF);

                ARGB mixColor = ARGB{0xFF, 0x00, 0x00, 0x00};

                //int i2;
                //if (q<0) i2 = i+1; else i2 = i-1;

                //if (i2>=0 && i2 < 4) mixColor = wave[i2];

                p = mixColor.interpolate(wave[i], m);
                z = zb + (1.0 - v) * .125;
            }

            zb += .125;

        }


    }
ret:
    return true;
}

void Forge::drawInitial()
{
    src = new Image(800,600);

    PathAdapter pth;

    pth.inputMatrix *= dMatrix2D::Translate({0,4});

    pth.Line({0,0},{0,-4});
    pth.LineTo({4,-2});
    pth.LineTo({0,0});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});

    pth.Line({3,-1}, {2,0});
    pth.LineTo({0,-2});
    pth.LineTo({2, -4});
    pth.LineTo({4,-2});
    pth.LineTo({0,-2});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});
    pth.Line({0,0},{0,-4});
    pth.LineTo({2,-3});
    pth.LineTo({0,-2});

    pth.inputMatrix *= dMatrix2D::Translate({4,0});
    pth.Line({0,-4},{4,-4});
    pth.Line({2,0},{2,-4});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});
    pth.Line({0,0},{0,-4});
    pth.Line({0,-2},{4,-2});
    pth.Line({4,-4},{4,0});

    pth.outputMatrix = dMatrix2D::Scale({.25,.25}) * dMatrix2D::Scale({64,64}) *
            dMatrix2D::Translate({200,150});

    pth.Apply(src);

    pth.ClearPath();
    pth.inputMatrix.Identity();
    pth.outputMatrix.Identity();

    pth.inputMatrix *= dMatrix2D::Translate({0,4});
    pth.Line({0,0},{0,-4});
    pth.LineTo({4,-4});
    pth.Line({0,-2},{2,-2});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});
    pth.Line({2,0},{0,-2});
    pth.LineTo({2,-4});
    pth.LineTo({4,-2});
    pth.LineTo({2, 0});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});
    pth.Line({0,0},{0,-4});
    pth.LineTo({2,-3});
    pth.LineTo({0,-2});
    pth.LineTo({2,0});

    pth.inputMatrix *= dMatrix2D::Translate({4,0});
    pth.Line({0,-1},{2,0});
    pth.LineTo({4,-1});
    pth.LineTo({4,-3});
    pth.LineTo({2,-4});
    pth.LineTo({0,-3});
    pth.LineTo({2,-2});
    pth.LineTo({4,-3});

    pth.inputMatrix *= dMatrix2D::Translate({6,0});

    pth.Line({3,-1}, {2,0});
    pth.LineTo({0,-2});
    pth.LineTo({2, -4});
    pth.LineTo({4,-2});
    pth.LineTo({0,-2});

    pth.outputMatrix = dMatrix2D::Scale({.25,.25}) * dMatrix2D::Scale({64,64});
    dPnt2D pivot = pth.outputMatrix * (pth.inputMatrix * dPnt2D{4,-4});

    pth.outputMatrix *=
            dMatrix2D::Translate(-pivot) * dMatrix2D::Rotate(M_PI/16) *
            dMatrix2D::Scale({1.25,1.25}) *
            dMatrix2D::Translate(pivot) * dMatrix2D::Translate({200+64,150+90});



    pth.Apply(src);





    src->DrawPath(PixOp_SRC, ZOp_SRC, 1.0, &letters, nullptr);
}

struct LenseData
{
    float **map;
    Image *lenseImage[10];
};

void Forge::drawBackground(UI *member, Image *target, QImage *qImage)
{
    int w = width.get();
    int h = height.get();

    if (bkgImage == nullptr || bkgImage->Width < w || bkgImage->Height < h)
    {
        if (bkgImage != nullptr) delete  bkgImage;

        bkgImage = new Image(w+256,h+256);

        for (int y=0; y<bkgImage->Height; y++)
        {
            int yy = y % bkgTile->Height;
            for (int x=0; x<bkgImage->Width; x++)
            {
                int xx = x % bkgTile->Height;

                bkgImage->pix[y][x] = bkgTile->pix[yy][xx];
                bkgImage->z[y][x] = bkgTile->z[yy][xx];
            }
        }
    }

    target->DrawImage(xReal,yReal, w, h, PixOp_SRC, ZOp_SRC_ADD,
            bkgImage, 0, 0, w, h);
}

void Forge::draw(Image *target, QImage *qImage)
{
    UI::draw(target, qImage);

    double time = getTimeInSeconds();
    time = time - trunc(time);

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

    if (hasMouse || previewLense)
    {
        int xx;
        int yy;

        if (hasMouse)
        {
            xx = (int) (mouseX * _w + _x);
            yy = (int) (mouseY * _h + _y);
        } else
        {
            xx = (int) (.5 * _w + _x);
            yy = (int) (.5 * _h + _y);
        }

        Lense *lense = ((MainUI *) rootElement())->lense;

        int sz = (int) (lense->size * fmax(_w,_h));

        Lense::Cache * dta;

        LenseData *d;

        if (!lense->getData(0, sz, &dta))
        {
            if (dta->dta != nullptr)
            {
                d = (LenseData *)dta->dta;

                lense->freeMap(d->map, dta->s);

                for (int i =0; i<10; i++) {
                    if (d->lenseImage[i] != nullptr) {
                        delete d->lenseImage[i];
                        d->lenseImage[i] = nullptr;
                    }
                }
            } else
            {
                dta->dta = d = new LenseData();
                for (int i =0; i<10; i++)
                {
                    d->lenseImage[i] = nullptr;
                }
            }

            d->map = lense->map(sz);
            dta->s = sz;

            dta->needUpdate = true;
        }

        d = ((LenseData *)dta->dta);

        float **map = d->map;

        if (dta->needUpdate)
        {
            lense->updateMap(map, sz);

            for (int i=0; i<10; i++)
            {
                if (d->lenseImage[i] != nullptr)
                {
                    d->lenseImage[i]->needUpdate = true;
                }
            }
            
            dta->needUpdate = false;
        }

        int i = (int) (abs(time-.5)*2*9);

        int q = (sz << 1) + 1;

        if (d->lenseImage[i] == nullptr) {

            d->lenseImage[i] = new Image(q, q);
        }

        Image *img = d->lenseImage[i];

        if (img->needUpdate)
        {

            for (int yp = -sz; yp <= sz; yp++) {
                int y = sz + yp;

                for (int xp = -sz; xp <= sz; xp++) {
                    int x = sz + xp;

                    float l = map[yp][xp];

                    unsigned char g = (unsigned char) (i * 0xFF / 9);

                    ARGB p = {(unsigned char) (0x80 * l), 0xFF, g, 0xFF};

                    img->pix[y][x] = p;
                }
            }
            img->needUpdate = false;
        }

        target->DrawImage(_x1, _y1, _w1, _h1,
                xx-sz, yy-sz, q, q, PixOp_SRC_ALPHA, ZOp_SRC_ADD,
                img, 0,0, q, q);


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

void Forge::import(UI *sender, void *arg)
{
    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
            QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getOpenFileName(
            ((MainUI *)rootElement())->owner->parent, ("Open Image File"),
            path,
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

void Forge::export_anaglyph(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            path,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        save_ana(fileName, ImageLeft, ImageRight);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;

}

void Forge::export_jps(UI *sender, void *arg)
{
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    const bool SideBySide = true;

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            path,
            ("Images (*.jps)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        save_jps(fileName, ImageLeft, ImageRight);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}