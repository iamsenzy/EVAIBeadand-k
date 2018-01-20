#include "tili_toli.h"
#include <QTime>
#include <QVector>

bool operator!=(Coordinate a, Coordinate b)
  {
    return a.x() != b.x() || a.y() != b.y();
  }

Tili_Toli::Tili_Toli(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(trUtf8("Tili-Toli"));
    setFixedSize(300,300);

    _sizeButton = new QPushButton(trUtf8("Átméretezés"));
    _gridLayout = new QGridLayout();

    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_sizeButton);
    _vBoxLayout->addLayout(_gridLayout);

    setLayout(_vBoxLayout);

    _gridSizeDialog = new GridSizeDialog();
    connect(_sizeButton, SIGNAL(clicked()), _gridSizeDialog, SLOT(exec()));
    connect(_gridSizeDialog, SIGNAL(accepted()), this, SLOT(resizeGrid()));


    qsrand(QTime::currentTime().msec());
}


Tili_Toli::~Tili_Toli()
{
    delete _gridSizeDialog;
}

void Tili_Toli::setNumber()
{
    ++lepesek;
    GridPushButton* senderButton = qobject_cast<GridPushButton*>(sender());
    int x =senderButton->coordinate().x();
    int y = senderButton->coordinate().y();
    int u =search(Coordinate(ures.x(),ures.y()));
    _buttonGrid[u]->setText(senderButton->text());
    //_sizeButton->setText(QString::number(lepesek));
    senderButton->setText("");
    ures=Coordinate(x,y);
    if(end())
    {
    _endDialog= new endDialog(lepesek);
    _endDialog->show();
    connect(_endDialog, SIGNAL(accepted()), this, SLOT(resizeGrid()));
    connect(_endDialog, SIGNAL(rejected()), this, SLOT(close()));
    lepesek=0;
    }
    else
    {
    disableButtons();
    }
}

bool Tili_Toli::end()
{
    int i=0;
    while (_buttonGrid[i]->text()==QString::number(i+1))
    {
        ++i;
    }
    return i==(_gridSizeDialog->gridSize()*_gridSizeDialog->gridSize())-1;
}

int Tili_Toli::search(Coordinate coordinate)
{
    int i=0;
    while(coordinate != _buttonGrid[i]->coordinate() || i>_gridSizeDialog->gridSize()*_gridSizeDialog->gridSize())
    {
        ++i;
    }
    return i;
}

void Tili_Toli::disableButtons()
{
    for(int i=0;i<_gridSizeDialog->gridSize()*_gridSizeDialog->gridSize();++i)
    {
        _buttonGrid[i]->setDisabled(true);
    }
    activateButtons();
}

void Tili_Toli::activateButtons()
{
    int x = ures.x();
    int y = ures.y();
    //_buttonGrid[search(Coordinate(x,y))]->setEnabled(true);

    if(x>0 && x<_gridSizeDialog->gridSize()-1 && y>0 && y <_gridSizeDialog->gridSize()-1)
    {
        _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
        _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
        _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
        _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);
    }
    else
    {
       if(x==0 && y<_gridSizeDialog->gridSize()-1 && y>0)
       {
        _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
        _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
        _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);

       }
       else
       {
           if(x==_gridSizeDialog->gridSize()-1 && y<_gridSizeDialog->gridSize()-1 && y>0)
           {
               _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
               _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
               _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);
           }
           else
           {
               if(y==0 && x>0 && x<_gridSizeDialog->gridSize()-1)
               {
                   _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
                   _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
                   _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
               }
               else
               {
                   if(y==_gridSizeDialog->gridSize()-1 && x>0 && x<_gridSizeDialog->gridSize()-1)
                   {
                       _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
                       _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
                       _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);
                   }
                   else
                   {
                       if(x==0 && y==0)
                       {
                           _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
                           _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
                       }
                       else
                       {
                           if(x==_gridSizeDialog->gridSize()-1 && y==0)
                           {
                               _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
                               _buttonGrid[search(Coordinate(x,y+1))]->setEnabled(true);
                           }
                           else
                           {
                               if(x==0 && y==_gridSizeDialog->gridSize()-1)
                               {
                                    _buttonGrid[search(Coordinate(x+1,y))]->setEnabled(true);
                                    _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);
                               }
                               else
                               {
                                   _buttonGrid[search(Coordinate(x,y-1))]->setEnabled(true);
                                   _buttonGrid[search(Coordinate(x-1,y))]->setEnabled(true);
                               }
                           }
                       }
                   }
               }
           }

       }
    }

}

void Tili_Toli::resizeGrid()
{
    foreach(GridPushButton* button, _buttonGrid)
    {
        _gridLayout->removeWidget(button);
        delete button;
    }
    _buttonGrid.clear();

    int size=(_gridSizeDialog->gridSize()*_gridSizeDialog->gridSize());
    QVector<int> t;
    for(int i=0; i<size;++i)
    {
        t.push_back(i+1);
    }
    qsrand((unsigned)time(NULL));
    int a;
    for (int i = 0; i < _gridSizeDialog->gridSize(); ++i) {

        for (int j = 0; j < _gridSizeDialog->gridSize(); ++j){

             GridPushButton* button = new GridPushButton(Coordinate(i,j));

             do
             {
             a=qrand() % size;
             }while(t[a]==0 || t.empty());

             if(t[a]==size) {ures=Coordinate(i,j);}
             else
             {
             button->setText(QString::number(t[a]));
             }

             button->setDisabled(true);
             t[a]=0;
             _gridLayout->addWidget(button, i, j);
             _buttonGrid.append(button);
             QObject::connect(button, SIGNAL(clicked()), this, SLOT(setNumber()));
        }
    }
    activateButtons();
}
