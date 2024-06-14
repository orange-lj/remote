#ifndef SVGICONENGINE_H
#define SVGICONENGINE_H
#include<QtSvg/qsvgrenderer.h>
#include <QIconEngine>
//QIconEngine提供了一种可以创建自定义图标引擎的机制
class SVGIconEngine : public QIconEngine
{
public:
    static SVGIconEngine* instance();
private:
    SVGIconEngine();

    // QIconEngine interface
public:
    void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state);
    QIconEngine *clone() const;
    QIcon icon(QString filePath,const QSize& size);
    QPixmap pixmap(const std::string &data,const QSize& size);
};

#endif // SVGICONENGINE_H
