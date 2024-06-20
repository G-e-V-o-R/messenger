#ifndef SEPARATOR_H
#define SEPARATOR_H
#include<QWidget>

class Separator : public QWidget
{
public:
    Separator()
    {
        setMaximumHeight(1);
        setStyleSheet("QWidget{background-color:lightgray;}");
    }

    ~Separator()
    {
    }
};

#endif // SEPARATOR_H
