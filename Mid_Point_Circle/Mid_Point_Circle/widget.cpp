#include "widget.h"
#include "math.h"

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

void drawCircle(QImage &image,QPoint pt1,QPoint pt2){
    QPainter painter(&image);
    //DDA
    int x1=pt1.x(); //圆心
    int y1=pt1.y();
    int x2=pt2.x(); //控制R
    int y2=pt2.y();
    int R=(y2-y1)*(y2-y1)+(x2-x1)*(x2-x1);  //R
    int a=0;
    int b=R;
    int d=1.25- R;
    //对称性
    while(a <= b){
        painter.drawPoint(x1+a,y1+b);
        painter.drawPoint(x1-a,y1+b);
        painter.drawPoint(x1+a,y1-b);
        painter.drawPoint(x1-a,y1-b);
        painter.drawPoint(x1+b,y1+a);
        painter.drawPoint(x1+b,y1-a);
        painter.drawPoint(x1-b,y1+a);
        painter.drawPoint(x1-b,y1-a);
        if(d < 0){
            d +=2 * a +3;
        }
    else{
        d += 2*(a - b)+5;
        b--;
        }
     a++;
    }
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
    drawCircle(image,startPt,endPt);
    painter.drawImage(0,0,image);
}
