#include "barspainter.h"
#include <painters/painterutils.h>
#include <iostream>
BarsPainter::BarsPainter(QPaintDevice * widget) :
    PerformancePainter(widget)

{
    // Initializing colors
    m_color1 =(QColor(0,255,0,255));
    m_color2 = (QColor(255,0,0,255));
}

void BarsPainter::paint()
{
    //Create a new painter
    QPainter qpN(m_widget);
    //Draw gird and BG
    drawBackground(qpN);
    drawGrid(qpN);

    //Set a white color for the main rectangle
    qpN.setPen(QColor(255,255,255,255));


    //Compute size of the data and step size
    int size = m_cache.size();
    if (size <= 0)
    {
        std::cout<<"ERROR : NO DATA PROVIDED, CACHE SIZE IS 0"<<std::endl;
        return;
    }
    float steps = (m_width-size ) / (size);

    int subSize = m_cache[0].size();
    //Lets loop for each bar needed to be drawn
    for(int i = 0 ; i < size;i++)
    {
        //Let set the background color (zero alpha is transparent)
        qpN.setBrush(QColor(255,100,100,0));




        //int y = ((m_height/size)*(i))+(i*i*50);
        int padding = 10;
        int sub_rect_height = ((m_height-(padding*(size-1)))/size);
        int y = sub_rect_height*i+padding*i;
    float max = 400.f;

        //float value = m_cache[i][subSize-1]*sub_rect_height/100.0f;
float value = ((float)sub_rect_height)/max*320.f;
        std::cout << "y: " << y << std::endl;
        std::cout << "height: " << m_height << std::endl;
        std::cout << "-----------------------"<< std::endl;
        //Lets draw the container rectangle
        //drawRoundedRect(int x, int y, int w, int h, qreal xRadius, qreal yRadius, Qt::SizeMode mode)
        qpN.drawRoundedRect(0, y , m_width-1, sub_rect_height-1, 3, 3, Qt::AbsoluteSize);
        //qpN.drawRoundedRect((steps*(i))+(i*2) ,0,(steps),m_height-1, 3,3,Qt::AbsoluteSize);

        //Lets theck if the size is big enough to contain the percentage value
        //Then lets draw the actual rectangle
        if (steps > 80)
//            painterUtils::drawRectangleBar(qpN ,(i*steps+3 + i*2)+10,steps,
//                                           m_height,m_cache[i][subSize-1], true,
//                                           m_color1,
//                                           m_color2);
            painterUtils::drawRectangleBar(qpN ,10,m_width,
                                           sub_rect_height*(i+1)+padding*i, value, true,
                                           m_color1,
                                           m_color2);
        else
//            drawRectangleBar(QPainter &qp ,int const &startPos,int const &width,
//                                                int const &height
//                                             ,const float value, bool drawText ,
//                                                QColor &color1 , QColor &color2)

            /** PER SCRIVERE TESTO QUANDO VORREMO INSERIRE SCALA ASSE X (TIMELINE)*/

            //Lets draw the text in the center of the triangle if needed
        //    if (drawText == true)
        //        qp.drawText(startPos + (width/2),height/2,QString::number(int(value)) + " %");

            painterUtils::drawRectangleBar(qpN ,10,m_width,
                                           sub_rect_height*(i+1)+padding*i, value, false,
                                           m_color1,
                                           m_color2);
//            painterUtils::drawRectangleBar(qpN ,i*steps+3 + i*2,steps,
//                                           m_height,m_cache[i][subSize-1], false,
//                                           m_color1,
//                                           m_color2);
    }
}
