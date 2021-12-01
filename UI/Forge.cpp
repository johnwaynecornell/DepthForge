//
// Created by jwc on 2/16/19.
//
#include <QtCore>
#include <QtWidgets/QFileDialog>
#include <QFile>
#include <QImageWriter>
#include <QStandardPaths>
#include <QMessageBox>
#include <Image/PathAdapter.h>


#include "MainUI.h"
#include "MainWnd.h"
#include "Forge.h"

extern QApplication *app;

const char VERSION[]="0.0.44";

bool bkgTilePixFunc(int index, double y, ARGB &p, float &z, void *arg)
{
        y = 1.0 - abs(y);

        if (y<0) y = 0;

        //if (y<0) y = 0;
        z = (1.0f- sinf((1.0f-(float) y) * (float) M_PI / 2.0f))*.125f;

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

    bkgTile = new Image(32,32);


    bkgTile->Line(8,8,24,8);
    bkgTile->LineTo(24,24);
    bkgTile->LineTo(8,24);
    bkgTile->LineTo(8,8);

    bkgTile->DrawPath(PixOp_SRC, ZOp_SRC, 1.0f / 8, bkgTilePixFunc, nullptr);

    bkgImage = nullptr;

    lastPath1 = lastPath2 = QStandardPaths::locate(QStandardPaths::PicturesLocation, QString::null,
                                          QStandardPaths::LocateOption::LocateDirectory);

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
    MainWnd *w =wnd();
    
    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::file_new, tmp);
    w->file_new_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::file_open, tmp);
    w->file_open_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::file_reopen, tmp);
    w->file_reopen_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::file_save, tmp);
    w->file_save_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::file_save_as, tmp);
    w->file_save_as_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::import, tmp);
    w->import_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_jps, tmp);
    w->export_jps_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_SBS_Parallel, tmp);
    w->export_SBS_Parallel_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_SBS_ParallelHalf, tmp);
    w->export_SBS_ParallelHalf_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_SBS_Cross, tmp);
    w->export_SBS_Cross_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_SBS_CrossHalf, tmp);
    w->export_SBS_CrossHalf_proc = {this, nullptr, (void (*)(void *, UI *,void *))tmp, nullptr};


    /*
export_SBS_Parallel;
export_SBS_ParallelHalf;
export_SBS_Cross;
export_SBS_CrossHalf;

     */

    get_member_pointer(void (Forge::*a)(UI *, void *), &Forge::export_anaglyph, tmp);
    w->export_anaglyph_proc = {this, nullptr, (void (*)(void *,UI *, void *))tmp, nullptr};
}

MainWnd *Forge::wnd()
{
    return (MainWnd *) ((MainUI *) rootElement())->owner->parent;
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

    QImage *i = new QImage(100, 100, QImage::Format_ARGB32);

    QPainter *p = new QPainter(i);

    p->fillRect(0,0,i->width(), i->height(), QBrush(QColor(0,0,0)));

    double osz = 1;
    double sz;

    int w;

    char t[1024];

    sprintf(t,"v%s", VERSION);

    QString txt = QApplication::tr(t);

    do {
        sz = osz;

        QFont f;
        f = p->font();

        f.setPointSizeF(osz);

        p->setFont(f);

        w = p->fontMetrics().width(txt);

        osz += .1;
    } while (w < i->width());

    QFont f;
    f = p->font();

    f.setPointSizeF(sz);

    p->setFont(f);

    int width = p->fontMetrics().width(txt);
    int height = p->fontMetrics().height();

    if (width>i->width()) width = i->width();

    p->setPen(QColor(0xFF, 0xFF, 0xFF, 0xFF));
    p->drawText(0, height, txt);

    p->end();
    delete p;

    for (int y=0; y<height; y++)
    {
        for (int x=0; x<width; x++)
        {
            unsigned char V = ((BGRA *)i->bits())[y*i->width()+x].r;

            float d = .15 * V / 0xFF;

            if (V>0)
            {
                int xx,yy;
                xx = src->Width-width+x-16;
                yy = src->Height-height+y-16;

                src->pix[yy][xx] = {0xFF,V,V,V};
                src->z[yy][xx] -= d;
            }
        }
    }

    delete i;
}

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
                int xx = x % bkgTile->Width;

                bkgImage->pix[y][x] = bkgTile->pix[yy][xx];
                bkgImage->z[y][x] = bkgTile->z[yy][xx];
            }
        }
    }

    target->DrawImage(xReal,yReal, w, h, PixOp_SRC, ZOp_SRC_ADD,
            bkgImage, 0, 0, w, h);
}

bool zoomVars(double xo, double yo, double scale,
              int &srcX, int &srcY, int &srcW, int &srcH,
              int &destX, int &destY, int &destW, int &destH)
{
    bool rc;
    double a1 = destW / (double) destH;
    double a2 = srcW / (double) srcH;

    int sx,sy,sw,sh;
    int scx, scy;

    sw = srcW;
    sh = srcH;

    scx = sw / 2.0;
    scy = sh / 2.0;

    int sox = scx ,soy = scy;

    sox = (int)(xo * srcW);
    soy = (int)(yo * srcH);

    if (a2<a1)
    {
        sh = srcH / scale;
        sw = destW * sh / destH;
        rc = false;
    } else
    {
        sw = srcW / scale;
        sh = destH * sw / destW;
        rc = true;
    }

    sx = (int)(xo * (srcW - sw));
    sy = (int)(yo * (srcH - sh));

    int i;
    int d;

    if (sx<0)
    {
        i = destW * -sx / (double) sw;

        destX += i;
        destW -= i;

        sw += sx;
        sx = 0;
    }

    int sx2 = sx + sw;
    int osx2 = srcW + srcX;

    if (sx2>osx2)
    {
        d = sx2 - osx2;
        i = destW * d / (double) sw;
        destW -= i;
        sw -= d;
    }

    if (sy<0)
    {
        i = destH * -sy / (double) sh;

        destY += i;
        destH -= i;

        sh += sy;
        sy = 0;
    }

    int sy2 = sy + sh;
    int osy2 = srcH + srcY;

    if (sy2>osy2)
    {
        d = sy2 - osy2;
        i = destH * d / (double) sh;
        destH -= i;
        sh -= d;
    }

    srcX = sx;
    srcY = sy;
    srcW = sw;
    srcH = sh;

    return rc;
}

bool ForgeDrawPixFunc(Image *image, int x, int y, ARGB &p, float &z, void *arg)
{
    p = image->pix[y][x];
    z = image->z[y][x] * *((double *)arg);

    return false;
}

bool depthPixFunc(Image *I, int x, int y, ARGB &p, float &z, void *arg)
{
    Image *src = ((Forge *)arg)->src;

    int xx = x*src->Width/I->Width;
    int yy = y*src->Height/I->Height;

    float _z = -src->z[yy][xx];

    _z = (_z+1)/2.0;
    if (_z<0) _z = 0; else if (_z>1) _z = 1;

    unsigned char G = (unsigned char)(_z*0xFF);

    p = {0xFF,G,G,G};
    z = 0.0;

    return true;
}

void Forge::updateGreyMap()
{
    Image *g = ((MainUI *)rootElement())->forgeContainer->forge->greyMap;

    if (g->Width != src->Width || g->Height != src->Height)
    {
        delete g;
        g = ((MainUI *)rootElement())->forgeContainer->forge->greyMap = new Image(src->Width, src->Height);
    }

    g->FillRect(0,0,g->Width,g->Height, PixOp_SRC, ZOp_SRC, depthPixFunc, this);

}

void Forge::draw(Image *target, QImage *qImage)
{
    ((MainUI *)rootElement())->mode_Current->updateSrc(this);
    UI::draw(target, qImage);

    int _x1,_y1,_w1,_h1;

    _x = _x1 = xReal;
    _y = _y1 = yReal;

    _w = _w1 = width.get();
    _h = _h1 = height.get();

    _srcW = src->Width;
    _srcH = src->Height;
    _srcX = 0;
    _srcY = 0;

    Image *g = greyMap;

    bool horz = zoomVars(scrollX, scrollY, scale, _srcX, _srcY, _srcW, _srcH, _x, _y, _w, _h);


    if (!swapViews) {
        target->DrawImage(_x, _y, _w, _h, PixOp_SRC, ZOp_SRC, src, _srcX, _srcY, _srcW, _srcH);

        //a->DrawImage(0, 0, a->Width, a->Height, PixOp_SRC, ZOp_SRC, g, 0, 0,g->Width, g->Height);
    } else
    {
        target->DrawImage(_x, _y, _w, _h, PixOp_SRC, ZOp_SRC, g, _srcX, _srcY, _srcW, _srcH);
    }

    target->FillRect(_x, _y, _w, _h, PixOp_SRC, ZOp_SRC, ForgeDrawPixFunc, &scale);
    target->setBound(_x,_y,_w,_h);
    ((MainUI *)rootElement())->mode_Current->drawForge(this, target, qImage);
    target->resetBound();
}



/*
void draw(Image *target, QImage *qImage)
{
    ((MainUI *)rootElement())->mode_Current->updateSrc(this);
    UI::draw(target, qImage);

    int _x1,_y1,_w1,_h1;

    _x = _x1 = xReal;
    _y = _y1 = yReal;

    _w = _w1 = width.get();
    _h = _h1 = height.get();

    double scale = 3.0;

    int _cx = _w / 2;
    int _cy = _h / 2;

    int targX = -_cx;
    int targY = -_cy;

    double a1;
    double a2 = (double)src->Width / (double) src->Height;

    double srcX, srcY;
    double srcW, srcH;

    int _srcX, _srcY;
    int _srcW, _srcH;

    int w = _w;
    int h = _h;

    srcX = -1;
    srcW = 2;

    srcH = 2;// / a2;
    srcY = -1;// * srcH / 2.0;

    if (a2<1)
    {
        /*
        srcX = -1.0;
        srcW = 2.0;

        srcH = 2.0;// / a2;
        srcY = -1.0;// * srcH / 2.0;

        _x = _x + _w / 2 - _w / 2 * a2;
        _w *= a2;

    } else
    {
  /*
        srcW = 2.0;// * a2;
        srcX = -1.0;// * srcW / 2;

        srcH = 2.0;
        srcY = -1.0;

        _y = _y + _h /2 - _h / 2 / a2;
        _h /= a2;
    }

    a2 = (double) srcW / (double) srcH;
    a1 = (double)_w/(double)_h;
/*
    if (a2 <= a1)
    {
//        _h = *h;
        _w = (int)(_h * a1);
    }
    else
    {
//        _w = *w;
        _h = (int)(_w / a1);
    }

    _x = _x + (w - _w) / 2;// - (toFit.X / toFit.Width * This.Width);
    _y = _y + (h - _h) / 2;// - (toFit.Y / toFit.Height * This.Height);

    int Cx = src->Width>>1;
    int Cy = src->Height>>1;

    _srcX = Cx + (int) (srcX * Cx);
    _srcY = Cy + (int) (srcY * Cy);

    _srcW = (int)( src->Width * srcW / 2.0);
    _srcH = (int) (src->Height * srcH / 2.0);

/*
    if (_srcY<0)
    {

    }

    if (_srcX<0)
    {

    }
    */

    /*
    double a1 = *w / (double) *h;
    double a2 = toFitW / (double) toFitH;

    int _w, _h, _x, _y;

    if (a2 <= a1)
    {
        _h = *h;
        _w = (int)(_h * a2);
    }
    else
    {
        _w = *w;
        _h = (int)(_w / a2);
    }

    _x = *x + (*w - _w) / 2;// - (toFit.X / toFit.Width * This.Width);
    _y = *y + (*h - _h) / 2;// - (toFit.Y / toFit.Height * This.Height);
*/





/*
    double windX = 0;
    double windY = 0;
    int Cx = src->Width>>1;
    int Cy = src->Height>>1;

    srcX = (int) (Cx - Cx / scale);
    srcY = (int) (Cy - Cy / scale);

    srcW = src->Width / scale;
    srcH = src->Height / scale;
*/





/*

    GfxFitRect(_srcX, _srcY, _srcW, _srcH, &_x, &_y, &_w, &_h);

    target->DrawImage(_x,_y,_w,_h, PixOp_SRC, ZOp_SRC, src, _srcX, _srcY, _srcW, _srcH);

    ((MainUI *)rootElement())->mode_Current->drawForge(this, target, qImage);
}
*/
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

void Forge::setMouseXY(int x, int y)
{
    //double _x = (x - (_x-xReal)) / (double) _w;
    //double _y = (y - (_y-yReal)) / (double) _h;

    double _x = (x - (this->_x-xReal)) / (double) _w;
    double _y = (y - (this->_y-yReal)) / (double) _h;

    double sx = _srcX + _srcW * _x;
    double sy = _srcY + _srcH * _y;

    mouseX = sx / (double) src->Width;
    mouseY = sy / (double) src->Height;
}

bool Forge::mouseMove(int x, int y)
{
    //mouseX = (x - (_x-xReal)) / (double) _w;
    //mouseY = (y - (_y-yReal)) / (double) _h;

    bool rc = UI::mouseMove(x,y);

    if (!rc)
    {
        setMouseXY(x,y);
        ((MainUI *)rootElement())->mode_Current->mouseMoveForge(this, x, y);
    }

    return true;
}

bool Forge::mouseButtonPress(int x, int y, Qt::MouseButton button)
{
    //mouseX = (x - (_x-xReal)) / (double) _w;
    //mouseY = (y - (_y-yReal)) / (double) _h;

    bool rc = UI::mouseButtonPress(x,y,button);

    if (!rc) {
        setMouseXY(x, y);
        mouseDown.setFlag(button, true);
    }

    return ((MainUI *)rootElement())->mode_Current->mouseButtonPressForge(this, x, y, button);
}

bool Forge::mouseButtonRelease(int x, int y, Qt::MouseButton button)
{
    bool rc = UI::mouseButtonRelease(x,y,button);

    if (!rc) {
        mouseDown.setFlag(button, false);

        ((MainUI *) rootElement())->mode_Current->mouseButtonReleaseForge(this, x, y, button);
    }

    return true;
}

void Forge::open(QString &fileName)
{
    QFile *F = new QFile(fileName);
    unsigned int verMin;
    unsigned int verMaj;
    int q;

    int w;
    int h;

    QImage *tmp;

    QBuffer *b;

    qint64 len_pos;

    QString t;

    QImage A;

    if (!F->open(QIODevice::OpenModeFlag::ReadOnly))
    {
        goto Error;
    }

    char TBuf[1024];
    TBuf[1023] = '\0';

    if (F->read(TBuf, 10) != 10) goto  Error;
    TBuf[10] = 0;

    if (strcmp(TBuf,"DepthForge") != 0) goto Error;

    if (F->read((char *) &verMaj, 4) != 4) goto Error;
    if (F->read((char *) &verMin, 4) != 4) goto Error;

    if (verMaj == 0) goto Error;
    if (verMaj > 1)
    {
        QMessageBox *mb = new QMessageBox(wnd());
        mb->setWindowTitle(QApplication::tr("PROBLEM"));
        mb->setText(QApplication::tr("this file appears to be from a newer version, please upgrade"));

        mb->show();
        return;
    }

    if (F->read(TBuf, 4) != 4) goto  Error;
    TBuf[4] = 0;
    if (strcmp(TBuf,"HEAD") != 0) goto Error;

    if (F->read((char *) &q, 4) != 4) goto Error;

    if (q != 12) goto Error;

    if (F->read((char *) &q, 4) != 4) goto Error;
    len_pos = q;

    if (F->read((char *) &w, 4) != 4) goto Error;
    if (F->read((char *) &h, 4) != 4) goto Error;

    if (F->read(TBuf, 4) != 4) goto  Error;
    TBuf[4] = 0;
    if (strcmp(TBuf,"IMAG") != 0) goto Error;

    if (F->read((char *) &q, 4) != 4) goto Error1;
    if (q != 8) goto Error1;

    if (F->read((char *) &q, 4) != 4) goto Error1;
    if (q != 0) goto Error1;

    if (F->read((char *) &q, 4) != 4) goto Error1; //image bytes

    A.load(F, "PNG");

    if (A.width() != w || A.height() != h) goto Error1;

/*
    QImage::Format f = A.format();

    if (!A.hasAlphaChannel() && A.format() == QImage::Format_RGB32) {
        QImage B = QImage(A.width(), A.height(), QImage::Format_ARGB32);

        GfxBlt(PixType_BGRA, A.bits(), 0, 0, A.width(), A.height(), A.width(),
               PixType_ARGB, B.bits(), 0, 0, B.width(), B.height(), B.width());

        A = B;
    }
*/
    src = new Image(A.width(), A.height());

    GfxBlt(PixType_BGRA, A.bits(), 0, 0, A.width(), A.height(), A.width(),
            PixType_ARGB, src->imageMemory, 0, 0, src->Width, src->Height, src->stride);


    if (F->read(TBuf, 4) != 4) goto  Error;
    TBuf[4] = 0;
    if (strcmp(TBuf,"DPTH") != 0) goto Error;

    if (F->read((char *) &q, 4) != 4) goto Error1;
    if (q != 8) goto Error1;

    if (F->read((char *) &q, 4) != 4) goto Error1;
    if (q != 0) goto Error1;

    if (F->read((char *) &q, 4) != 4) goto Error1; //image bytes
    if (q != w*h*4) goto Error1;

    if (F->read((char *) src->zMemory, q) != q) goto Error1;

    F->close();

    lastPath1 = QFileInfo(fileName).filePath();

    t = QFileInfo(fileName).fileName();
    wnd()->setFileName(t);

    this->fileName = fileName;

    return;

    Error1:
    delete b;
    delete tmp;
    Error:
    QMessageBox *mb = new QMessageBox(wnd());
    mb->setWindowTitle(QApplication::tr("ERROR"));
    mb->setText(QApplication::tr("Unable to load file"));

    mb->show();
}

void Forge::save(QString &fileName)
{
    QFile *F = new QFile(fileName);
    unsigned int verMin = 0;
    unsigned int verMaj = 1;
    int q;

    int w;
    int h;

    QImage *tmp;

    QBuffer *b;

    qint64 len_pos;

    QString t;

    if (!F->open(QIODevice::OpenModeFlag::WriteOnly))
    {
        goto Error;
    }

    if (F->write("DepthForge", 10) != 10) goto  Error;

    if (F->write((const char *) &verMaj, 4) != 4) goto Error;
    if (F->write((const char *) &verMin, 4) != 4) goto Error;

    if (F->write("HEAD", 4) != 4) goto  Error;
    q = 12;
    if (F->write((const char *) &q, 4) != 4) goto Error;

    len_pos = F->pos();
    q = -1;
    if (F->write((const char *) &q, 4) != 4) goto Error;


    w = src->Width;
    h = src->Height;

    if (F->write((const char *) &w, 4) != 4) goto Error;
    if (F->write((const char *) &h, 4) != 4) goto Error;

    tmp = new QImage(src->Width,src->Height, QImage::Format_RGBA8888);

    GfxBlt(PixType_ARGB, src->imageMemory, 0, 0, w, h, w,
           PixType_RGBA, tmp->bits(), 0, 0, w, h, w);

    b = new QBuffer();
    b->open(QBuffer::ReadWrite);

    tmp->save(b, "PNG");

    if (F->write("IMAG", 4) != 4) goto  Error1;
    q = 8;
    if (F->write((const char *) &q, 4) != 4) goto Error1;
    q = 0;
    if (F->write((const char *) &q, 4) != 4) goto Error1;
    q = b->data().length();
    if (F->write((const char *) &q, 4) != 4) goto Error1;

    if (F->write(b->data().data(), q) != q) goto Error1;

    if (F->write("DPTH", 4) != 4) goto  Error1;
    q = 8;
    if (F->write((const char *) &q, 4) != 4) goto Error1;
    q = 0;
    if (F->write((const char *) &q, 4) != 4) goto Error1;
    q = 4*w*h;
    if (F->write((const char *) &q, 4) != 4) goto Error1;

    if (F->write((const char *) src->zMemory, q) != q) goto Error1;

    q = (int) F->pos();
    F->seek(len_pos);

    if (F->write((const char *) &q, 4) != 4) goto Error1;

    F->close();

    lastPath1 = QFileInfo(fileName).filePath();

    t = QFileInfo(fileName).fileName();
    wnd()->setFileName(t);

    this->fileName = fileName;

    return;
Error1:
    delete b;
    delete tmp;
Error:
    QMessageBox *mb = new QMessageBox(wnd());
    mb->setWindowTitle(QApplication::tr("ERROR"));
    mb->setText(QApplication::tr("Unable to save file"));

    mb->show();
}

void Forge::file_new(UI *sender, void *arg)
{
    fileName = QString::null;
    src = new Image(1,1);

    wnd()->setFileName(fileName);
}
void Forge::file_open(UI *sender, void *arg)
{
    QString fileName = QFileDialog::getOpenFileName(
            ((MainUI *)rootElement())->owner->parent, ("Open DepthForge File"),
            lastPath1,
            ("DepthForge Image (*.dfg)"));

    if (fileName.isNull())
    {
        //src = new Image(1,1);
    } else {
        open(fileName);
    }
    
}
void Forge::file_reopen(UI *sender, void *arg)
{
    open(fileName);
}
void Forge::file_save(UI *sender, void *arg)
{
    if (fileName.isNull()) file_save_as(sender, arg);
    else save(fileName);
}
void Forge::file_save_as(UI *sender, void *arg)
{
    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *)rootElement())->owner->parent, ("Save DepthForge File"),
            lastPath1,
            ("DepthForge Image (*.dfg)"));

    if (fileName.isNull())
    {
        //src = new Image(1,1);
    } else {
        save(fileName);
    }
    
}


void Forge::import(UI *sender, void *arg)
{
    QString fileName = QFileDialog::getOpenFileName(
            ((MainUI *)rootElement())->owner->parent, ("Open Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull())
    {
        //src = new Image(1,1);
    } else {
        QImage A;
        lastPath2 = QFileInfo(fileName).filePath();

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

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();

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

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.jps)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();
        save_jps(fileName, ImageLeft, ImageRight);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}

void Forge::export_SBS_Parallel(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();

        save_parallel(fileName, ImageLeft, ImageRight, false);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}

void Forge::export_SBS_ParallelHalf(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();

        save_parallel(fileName, ImageLeft, ImageRight, true);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}

void Forge::export_SBS_Cross(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();

        save_parallel(fileName, ImageRight, ImageLeft, false);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;
}

void Forge::export_SBS_CrossHalf(UI *sender, void *arg) {
    Image *ImageLeft;
    Image *ImageRight;

    int w = src->Width;
    int h = src->Height;

    ImageLeft = new Image(w, h);
    ImageRight = new Image(w, h);

    src->Artif3d(src->Width / 30, ImageLeft, ImageRight);

    QString fileName = QFileDialog::getSaveFileName(
            ((MainUI *) rootElement())->owner->parent, ("Save Image File"),
            lastPath2,
            ("Images (*.png *.jpg)"));

    if (fileName.isNull()) {
        goto cleanup;
    } else
    {
        lastPath2 = QFileInfo(fileName).filePath();

        save_parallel(fileName, ImageRight, ImageLeft, true);
    }

    cleanup:
    delete ImageLeft;
    delete ImageRight;

}