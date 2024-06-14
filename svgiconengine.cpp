#include "svgiconengine.h"

#include <QFile>
#include <QPainter>
#include<QtSvg/qsvgrenderer.h>

SVGIconEngine::SVGIconEngine()
{

}

void SVGIconEngine::paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state)
{

}

QIconEngine *SVGIconEngine::clone() const
{

}

QIcon SVGIconEngine::icon(QString filePath, const QSize &size)
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return QIcon();
    }
    std::string data=file.readAll().toStdString();
    return QIcon(pixmap(data,size));
}

QPixmap SVGIconEngine::pixmap(const std::string &data, const QSize &size)
{
    //创建一个指定大小和格式的QImage对象
    QImage img(size,QImage::Format_ARGB32);
    //用透明色填充
    img.fill(qRgba(0,0,0,0));
    //使用QImage创建一个QPixmap对象
    QPixmap pix=QPixmap::fromImage(img,Qt::NoFormatConversion);
    //创建一个QPainter对象，关联到QPixmap
    QPainter painter(&pix);
    //创建一个矩形
    QRect r(QPoint(0.0,0.0),size);
    //使用SVG数据创建一个QSvgRenderer对象
    QSvgRenderer renderer(QByteArray::fromStdString(data));
    //使用QSvgRenderer将SVG渲染到QPainter，绘制到QPoxmap上
    renderer.render(&painter,r);
    return pix;
}


SVGIconEngine* SVGIconEngine::instance()
{
    static SVGIconEngine engine;
    return &engine;
}
