#include "widget.h"


Widget::Widget(QWidget *parent)
    :QWidget (parent)
{
}

Widget::~Widget()
{
}

//鼠标移动
void Widget::mouseMoveEvent(QMouseEvent *event){
    endPt = event->pos();
    update();
}

//释放
void Widget::mouseReleaseEvent(QMouseEvent *event){
    endPt = event->pos();
    update();
}

//单击
void Widget::mousePressEvent(QMouseEvent *event){
    startPt = event->pos();
}

void drawLine(QImage &image,QPoint pt1,QPoint pt2){
    QPainter painter(&image);
    //DDA
    int x1=pt1.x();
    int y1=pt1.y();
    int x2=pt2.x();
    int y2=pt2.y();
    int a,b,n,dx,dy,x0,y0; //n为增量
    dx=x2-x1;
    dy =y2-y1;
    if(abs(dx)>abs(dy)){
        n=abs(dx);
    }
    else
        n=abs(dy);
    x0=(float)dx/n;
    y0=(float)dy/n;
    a=(float)x1;b=(float)y1;
    for(int k=1;k<=n;k++){
        painter.drawPoint(float(a+0.5),float(b+0.5));
        a+=x0;
        b+=y0;
    }
    /*
     * if(abs(dx)>abs(dy)){
        n=
    }
    */

    //界面设置
    int x =400,y=500;
    unsigned char *ptrRow= image.scanLine(y);
    ptrRow[x * 3 +0] = 0;
    ptrRow[x * 3 +1] = 0;
    ptrRow[x * 3 +2] = 0;

}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QImage image=QImage(800,600, QImage::Format_RGB888);
    image.fill(QColor(255,255,255));
    drawLine(image,startPt,endPt);
    painter.drawImage(0,0,image);
}
