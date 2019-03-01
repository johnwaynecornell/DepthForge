//
// Created by jwc on 2/16/19.
//
#include <QtCore>
#include <QtWidgets/QFileDialog>
#include <QImageWriter>
#include <QStandardPaths>

#include "MainUI.h"
#include "Forge.h"
#include "DepthForgeWin.h"
#include "MainWnd.h"

extern QApplication *app;

#define get_member_pointer(Type, Member, Recipient) \
    {\
      union \
        {   Type; \
            void *b;    \
        } c; \
                \
        c.a = Member; \
        *((void **)&Recipient) = c.b;   \
    }

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

    src = new Image(1,1);

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

    get_member_pointer(void (Forge::*a)(void *), &Forge::import, tmp);
    w->import_proc = {this, (void (*)(UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(void *), &Forge::export_jps, tmp);
    w->export_jps_proc = {this, (void (*)(UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(void *), &Forge::export_anaglyph, tmp);
    w->export_anaglyph_proc = {this, (void (*)(UI *,void *))tmp, nullptr};
}

Forge::~Forge()
{
    delete src;
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

void Forge::import(void *arg)
{
    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
            QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getOpenFileName(
            ((MainUI *)rootElement())->owner, ("Open Image File"),
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

void Forge::export_anaglyph(void *arg) {
    Image *ImageLeft;
    Image *ImageRight;
    Image *ImageOut;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);
    ImageOut = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);
    ImageOut->AnaglyphFrom(ImageLeft, ImageRight);


    QImage *tmp = new QImage(w,h, QImage::Format_RGBA8888);

    GfxBlt(PixType_ARGB, ImageOut->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 0, 0, w, h, w);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner, ("Save Image File"),
            path,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        tmp->save(fileName);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
    delete ImageOut;
    //delete qImageOut;
    delete tmp;

}

void Forge::export_jps(void *arg)
{
    Image *ImageLeft;
    Image *ImageRight;
    Image *ImageOut;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);
    ImageOut = new Image(w<<1, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);
    GfxBlt(PixType_ARGB, ImageLeft->imageMemory, 0,0,w,h,w,
            PixType_RGBA, ImageOut->imageMemory, 0, 0, w, h, w<<1);
    GfxBlt(PixType_ARGB, ImageRight->imageMemory, w,0,w,h,w,
           PixType_RGBA, ImageOut->imageMemory, 0, 0, w, h, w<<1);

    QImage *tmp = new QImage((uchar *)
            ImageOut->imageMemory, w<<1,h, QImage::Format_RGBA8888);

    QString path = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner, ("Save Image File"),
            path,
            ("Images (*.jps)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        QImageWriter W(fileName, "JPG");


        tmp->save(fileName, "JPG");
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
    delete ImageOut;
    //delete qImageOut;
    delete tmp;


}