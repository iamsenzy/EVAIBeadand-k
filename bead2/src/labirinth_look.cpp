#include "labirinth_look.h"
#include <QMessageBox>
#include <QApplication>

Labirinth_Look::Labirinth_Look(QWidget *parent)
    : QWidget(parent)
{

        setFixedSize(600,400);
        setWindowTitle(trUtf8("Labirintus"));
        modell = new Labirinth_Modell;
        connect(modell, SIGNAL(gameEnd()), this, SLOT(End()));

        _smallGameButton = new QPushButton(trUtf8("7x7"));
        connect(_smallGameButton, SIGNAL(clicked()), this, SLOT(new_Game()));
        _middleGameButton = new QPushButton(trUtf8("8x8"));
        connect(_middleGameButton, SIGNAL(clicked()), this, SLOT(new_Game()));
        _largeGameButton = new QPushButton(trUtf8("10x10"));
        connect(_largeGameButton, SIGNAL(clicked()), this, SLOT(new_Game()));

        _pauseButton = new QPushButton(trUtf8("Szünet/folytatás"));
        _pauseButton->setEnabled(false);
        connect(_pauseButton, SIGNAL(clicked()), modell, SLOT(pauseGame()));

        _messageLabel = new QLabel(trUtf8("Játék kezdéséhez válassz pályát!"));
        connect(modell, SIGNAL(messageChanged(QString)), _messageLabel, SLOT(setText(QString)));


        _hBoxLayout = new QHBoxLayout();
        _hBoxLayout->addWidget(_smallGameButton);
        _hBoxLayout->addWidget(_middleGameButton);
        _hBoxLayout->addWidget(_largeGameButton);
        _hBoxLayout->addWidget(_pauseButton);
        _vBoxLayout = new QVBoxLayout();
         _vBoxLayout->setSpacing(0);
        _vBoxLayout->addLayout(_hBoxLayout);
        _vBoxLayout->addWidget(_messageLabel, 0, Qt::AlignHCenter);
         _gridLayout = new QGridLayout();
        _vBoxLayout->addLayout(_gridLayout, Qt::AlignCenter);

        setLayout(_vBoxLayout);

}

Labirinth_Look::~Labirinth_Look()
{
     delete modell;
}


void Labirinth_Look::new_Game()
{

    foreach(GridPushButton* button, _buttonGrid)
    {
       _gridLayout->removeWidget(button);
       modell->removeMap();
       delete button;
    }
    _buttonGrid.clear();

    if (QObject::sender() == _smallGameButton) // attól függ, melyik gombra kattintottunk
    {

        modell->creatMap("/Users/gesztibence/Desktop/labirintusos/3palya.txt");
        size = modell->get_Size();
        _gridLayout->setContentsMargins(171, 65, 173, 30);
    }
    else if (QObject::sender() == _middleGameButton)
    {

        modell->creatMap("/Users/gesztibence/Desktop/labirintusos/2palya.txt");
        size = modell->get_Size();
        _gridLayout->setContentsMargins(156, 35, 156, 30);

    }
    else
    {

        modell->creatMap("/Users/gesztibence/Desktop/Labirintusos/1palya.txt");
        size = modell->get_Size();
         _gridLayout->setContentsMargins(125, 1, 125, 1);


    }

     //_gridLayout->setColumnStretch(size,1);
    for (int i = 0; i < size;++i) {

           for (int j = 0; j < size; ++j){

                GridPushButton* button = new GridPushButton(Coordinate(i,j));


                //button->setText(QString::number(modell->Getter(i*size+j)));
                button->setStyleSheet("GridPushButton{background-image:url(/Users/gesztibence/Desktop/Labirintusos/dark.jpg)}");
                button->setFixedSize(32,32);
                button->setIconSize(QSize(32, 32));

                if(modell->Getter(i*size+j) != 2)
                button->setDisabled(true);
                button->setFlat(true);

                _gridLayout->addWidget(button, i, j);
                _buttonGrid.append(button);
                if(modell->Getter(i*size+j) != 1) {
                QObject::connect(button, SIGNAL(clicked()), this, SLOT(changePosition()));
                }

          }
     }
    _pauseButton->setEnabled(true);
    update();
}
void Labirinth_Look::changePosition()
{
    GridPushButton* senderButton = qobject_cast<GridPushButton*>(sender());

    modell->swap(senderButton->coordinate().x() * size + senderButton->coordinate().y() );
    update();
}

void Labirinth_Look::update()
{
    int x = modell->Gamer_Position().x;
    int y = modell->Gamer_Position().y;

    for(int i=0;i<size*size;++i)
    {
           _buttonGrid[i]->setDisabled(true);
    }
    activateButtons();
    for( int i=0; i< size; ++i)
    {
        for (int j = 0; j < size; ++j){

            QPixmap wall("/Users/gesztibence/Desktop/Labirintusos/wall.jpg");
            QPixmap carpet("/Users/gesztibence/Desktop/Labirintusos/carpet.jpg");
            QPixmap figure("/Users/gesztibence/Desktop/Labirintusos/figura.jpg");
            QPixmap dark("/Users/gesztibence/Desktop/Labirintusos/dark.jpg");
            QPixmap finish("/Users/gesztibence/Desktop/Labirintusos/cel.jpg");

            if( _buttonGrid[i*size+j]->isEnabled() ){

              switch(modell->Getter(i*size+j))
              {
                 case 0: _buttonGrid[i*size+j]->setIcon(QIcon(carpet));

                          break;
                 case 1:  _buttonGrid[i*size+j]->setIcon(QIcon(wall));

                          break;
                 case 2:  _buttonGrid[i*size+j]->setIcon(QIcon(figure));
                          break;
                 case 3:  _buttonGrid[i*size+j]->setIcon(QIcon(finish));
                          break;

              }

              _buttonGrid[i*size+j]->setDisabled(true);
              if ((i*size+j)==x*size+y) _buttonGrid[x*size+y]->setEnabled(true);
              if ((i*size+j)==(x+1)*size+y) _buttonGrid[(x+1)*size+y]->setEnabled(true);
              if ((i*size+j)==(x-1)*size+y) _buttonGrid[(x-1)*size+y]->setEnabled(true);
              if ((i*size+j)==x*size+y-1)   _buttonGrid[x*size+y-1]->setEnabled(true);
              if ((i*size+j)==x*size+y+1)   _buttonGrid[x*size+y+1]->setEnabled(true);



             if (modell->Getter(i*size+j) == 1) _buttonGrid[i*size+j]->setEnabled(false);
            }
            else

            _buttonGrid[i*size+j]->setIcon(QIcon(dark));


        }
    }


}

void Labirinth_Look::End()
{
    QMessageBox::information( this, "Gratulálok Nyertél!",
                                "Kijutottál a labirintusból!"
                                "Pórbálj meg kijutni a többi labirintusból is!" );
    _pauseButton->setEnabled(false);

}

void Labirinth_Look::activateButtons()
{
    int x = modell->Gamer_Position().x;
    int y = modell->Gamer_Position().y;

    _buttonGrid[x*size+y]->setEnabled(true);

    if(x>0 && x< size-1 && y>0 && y < size-1)
    {
        _buttonGrid[(x+1)*size+y]->setEnabled(true);
        _buttonGrid[(x-1)*size+y]->setEnabled(true);
        _buttonGrid[x*size+y+1]->setEnabled(true);
        _buttonGrid[x*size+y-1]->setEnabled(true);

        if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);
        if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
        if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x-1)*size+y+1]->setEnabled(true);
        if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x-1)*size+y-1]->setEnabled(true);



           if(modell->Getter((x+1)*size+y) != 1 && x<size-2) _buttonGrid[(x+2)*size+y]->setEnabled(true);
           if(modell->Getter((x-1)*size+y) != 1 && x>1) _buttonGrid[(x-2)*size+y]->setEnabled(true);
           if(modell->Getter(x*size+y+1) != 1 && y<size-2) _buttonGrid[x*size+y+2]->setEnabled(true);
           if(modell->Getter(x*size+y-1) != 1 && y>1) _buttonGrid[x*size+y-2]->setEnabled(true);

           if (x>1 && x< size-2 && y>1 && y < size-2)
           {
           if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                 if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                 if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                 if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
           }

           if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
               if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
               if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
               if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
           }

           if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                 if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                 if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                 if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
           }

             if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
               if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
               if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);

              }

        }

        if(y==1 && x==1)
        {

            if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
              if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
              if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
              if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
             }
             if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
             if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
        }

        if(x==1 && y==size-2)
        {

            if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                  if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
            }
            if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
            if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
        }
        if(x==size-2 && y==size-2)
        {
            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                  if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
            }
            if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
            if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
        }

        if(x==size-2 && y==1)
        {
            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
            }
            if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
            if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
        }

        if(y==1 && x>1 && x<size-2)
        {
            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
            }

              if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);

               }
            if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
            if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
        }

        if(y>1 && y<size-2 && x==size-2)
        {
            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
            }

            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                  if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
            }
            if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
            if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
        }

        if(y>1 && y<size-2 && x==1)
        {
            if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                  if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
            }

            if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
              if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
              if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
              if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
             }

            if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
            if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
        }

        if(y==size-2 && x>1 && x<size-2)
        {
            if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                  if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
            }

            if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                  if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                  if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                  if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
            }
            if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
            if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);

        }

    }
    else
        {
           if(x==0 && y<size-1 && y>0)
           {
           _buttonGrid[(x+1)*size+y]->setEnabled(true);
           _buttonGrid[x*size+y+1]->setEnabled(true);
           _buttonGrid[x*size+y-1]->setEnabled(true);



           if(y==1 ){
               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                 if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                 if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                 if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
                }
               if(modell->Getter(x*size+y+1) != 1 ) _buttonGrid[x*size+y+2]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1) _buttonGrid[(x+2)*size+y]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
           }

           if(y==size-2 ){
               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                     if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                     if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
               }
                if(modell->Getter(x*size+y-1) != 1 ) _buttonGrid[x*size+y-2]->setEnabled(true);
                if(modell->Getter((x+1)*size+y) != 1) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);
                if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
           }


           if(x==0 && y<size-2 && y>1)
           {
               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                     if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                     if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
               }

               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                 if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                 if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                 if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
                }
               if(modell->Getter(x*size+y-1) != 1 ) _buttonGrid[x*size+y-2]->setEnabled(true);
               if(modell->Getter(x*size+y+1) != 1 ) _buttonGrid[x*size+y+2]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
               if(modell->Getter((x+1)*size+y) != 1) _buttonGrid[(x+2)*size+y]->setEnabled(true);


           }

           }
           else
           {
               if(x==size-1 && y<size-1 && y>0)
               {
                   _buttonGrid[(x-1)*size+y]->setEnabled(true);
                   _buttonGrid[x*size+y+1]->setEnabled(true);
                   _buttonGrid[x*size+y-1]->setEnabled(true);

                   if(modell->Getter((x-1)*size+y) != 1 && x>1) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                   if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x-1)*size+y+1]->setEnabled(true);
                   if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x-1)*size+y-1]->setEnabled(true);

                   if(y==1 ){

                       if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                           if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                           if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                           if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                       }
                       if(modell->Getter(x*size+y+1) != 1 ) _buttonGrid[x*size+y+2]->setEnabled(true);
                       if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                   }

                   if(y==size-2 ){
                       if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                             if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                             if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                             if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                       }
                       if(modell->Getter(x*size+y-1) != 1 ) _buttonGrid[x*size+y-2]->setEnabled(true);
                       if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                   }

                   if(x==size-1 && y<size-2 && y>1)
                   {

                       if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                           if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                           if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                           if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                       }

                       if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                             if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                             if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                             if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                       }

                       if(modell->Getter(x*size+y+1) != 1 ) _buttonGrid[x*size+y+2]->setEnabled(true);
                       if(modell->Getter(x*size+y-1) != 1 ) _buttonGrid[x*size+y-2]->setEnabled(true);

                   }


               }
               else
               {
                   if(y==0 && x>0 && x<size-1)
                   {
                       _buttonGrid[(x+1)*size+y]->setEnabled(true);
                       _buttonGrid[(x-1)*size+y]->setEnabled(true);
                       _buttonGrid[x*size+y+1]->setEnabled(true);

                       if(modell->Getter(x*size+y+1) != 1 ) _buttonGrid[x*size+y+2]->setEnabled(true);
                       if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);
                       if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x-1)*size+y+1]->setEnabled(true);

                       if(x==1 ){
                           if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                             if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                             if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                             if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
                            }
                            if(modell->Getter((x+1)*size+y) != 1 && x<size-2) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                            if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                       }

                       if(x==size-2 ){
                           if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                               if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                               if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                               if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                           }
                           if(modell->Getter((x-1)*size+y) != 1 && x>1) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                           if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                       }

                       if(y==0 && x>1 && x<size-2)
                       {
                           if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                               if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                               if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                               if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                           }

                           if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                             if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                             if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                             if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
                            }

                           if(modell->Getter((x+1)*size+y) != 1 && x<size-2) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                           if(modell->Getter((x-1)*size+y) != 1 && x>1) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                       }


                   }
                   else
                   {
                       if(y==size-1 && x>0 && x<size-1)
                       {
                           _buttonGrid[(x+1)*size+y]->setEnabled(true);
                           _buttonGrid[(x-1)*size+y]->setEnabled(true);
                           _buttonGrid[x*size+y-1]->setEnabled(true);

                           if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
                           if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x-1)*size+y-1]->setEnabled(true);
                           if(modell->Getter(x*size+y-1) != 1 && y>1) _buttonGrid[x*size+y-2]->setEnabled(true);

                           if(x==1 ){
                               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                                     if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                                     if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
                               }
                               if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                               if(modell->Getter((x+1)*size+y) != 1 && x<size-2) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                           }

                           if(x==size-2 ){
                               if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                                     if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                                     if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                               }
                               if(modell->Getter((x-1)*size+y) != 1 ) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                               if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
                           }

                           if(y==size-1 && x>1 && x<size-2)
                           {

                               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                                     if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                                     if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
                               }

                               if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                                     if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                                     if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                                     if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                               }
                               if(modell->Getter((x+1)*size+y) != 1 ) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                               if(modell->Getter((x-1)*size+y) != 1 ) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                           }

                       }
                       else
                       {
                           if(x==0 && y==0)
                           {
                               _buttonGrid[(x+1)*size+y]->setEnabled(true);
                               _buttonGrid[x*size+y+1]->setEnabled(true);

                               if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.a.
                                 if(modell->Getter((x+1)*size+y+1) != 1 && (modell->Getter((x+2)*size+y+1) != 1 || modell->Getter((x+1)*size+y+2) != 1 )) _buttonGrid[(x+2)*size+y+2]->setEnabled(true);
                                 if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x+1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x+1)*size+y+2]->setEnabled(true);
                                 if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y+1) != 1 )) _buttonGrid[(x+2)*size+y+1]->setEnabled(true);
                                }

                               if(modell->Getter((x+1)*size+y) != 1 && x<size-2) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                               if(modell->Getter(x*size+y+1) != 1 && y<size-2) _buttonGrid[x*size+y+2]->setEnabled(true);
                               if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x+1)*size+y+1]->setEnabled(true);

                           }
                           else
                           {
                               if(x==size-1 && y==0)
                               {
                                   _buttonGrid[(x-1)*size+y]->setEnabled(true);
                                   _buttonGrid[x*size+y+1]->setEnabled(true);
                                   if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y+1) !=1){ //j.f
                                       if(modell->Getter((x-1)*size+y+1) != 1 && (modell->Getter((x-2)*size+y+1) != 1 || modell->Getter((x-1)*size+y+2) != 1 )) _buttonGrid[(x-2)*size+y+2]->setEnabled(true);
                                       if(modell->Getter((x)*size+y+1) != 1 && (modell->Getter((x-1)*size+y+1) != 1 || modell->Getter((x)*size+y+2) != 1 )) _buttonGrid[(x-1)*size+y+2]->setEnabled(true);
                                       if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y+1) != 1 )) _buttonGrid[(x-2)*size+y+1]->setEnabled(true);
                                   }

                                   if(modell->Getter((x-1)*size+y) != 1) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                                   if(modell->Getter(x*size+y+1) != 1) _buttonGrid[x*size+y+2]->setEnabled(true);
                                   if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y+1) != 1 ) _buttonGrid[(x-1)*size+y+1]->setEnabled(true);
                               }
                               else
                               {
                                   if(x==0 && y==size-1)
                                   {
                                       _buttonGrid[(x+1)*size+y]->setEnabled(true);
                                       _buttonGrid[x*size+y-1]->setEnabled(true);

                                       if(modell->Getter((x+1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1 ){ //b.a.
                                             if(modell->Getter((x+1)*size+y) != 1 && (modell->Getter((x+2)*size+y) != 1 || modell->Getter((x+1)*size+y-1) != 1 )) _buttonGrid[(x+2)*size+y-1]->setEnabled(true);
                                             if(modell->Getter((x+1)*size+y-1) != 1 && (modell->Getter((x+2)*size+y-1) != 1 || modell->Getter((x+1)*size+y-2) != 1 )) _buttonGrid[(x+2)*size+y-2]->setEnabled(true);
                                             if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x+1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x+1)*size+y-2]->setEnabled(true);
                                       }
                                       if(modell->Getter((x+1)*size+y) != 1) _buttonGrid[(x+2)*size+y]->setEnabled(true);
                                       if(modell->Getter(x*size+y-1) != 1) _buttonGrid[x*size+y-2]->setEnabled(true);
                                       if(modell->Getter((x+1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x+1)*size+y-1]->setEnabled(true);
                                   }
                                   else
                                   {
                                       _buttonGrid[x*size+y-1]->setEnabled(true);
                                       _buttonGrid[(x-1)*size+y]->setEnabled(true);

                                       if(modell->Getter((x-1)*size+y) !=1 || modell->Getter((x)*size+y-1) !=1){ //b.f.
                                             if(modell->Getter((x-1)*size+y-1) != 1 && (modell->Getter((x-2)*size+y-1) != 1 || modell->Getter((x-1)*size+y-2) != 1 )) _buttonGrid[(x-2)*size+y-2]->setEnabled(true);
                                             if(modell->Getter((x-1)*size+y) != 1 && (modell->Getter((x-2)*size+y) != 1 || modell->Getter((x-1)*size+y-1) != 1 )) _buttonGrid[(x-2)*size+y-1]->setEnabled(true);
                                             if(modell->Getter((x)*size+y-1) != 1 && (modell->Getter((x-1)*size+y-1) != 1 || modell->Getter((x)*size+y-2) != 1 )) _buttonGrid[(x-1)*size+y-2]->setEnabled(true);
                                       }
                                       if(modell->Getter(x*size+y-1) != 1) _buttonGrid[x*size+y-2]->setEnabled(true);
                                       if(modell->Getter((x-1)*size+y) != 1 ) _buttonGrid[(x-2)*size+y]->setEnabled(true);
                                       if(modell->Getter((x-1)*size+y) != 1 || modell->Getter(x*size+y-1) != 1 ) _buttonGrid[(x-1)*size+y-1]->setEnabled(true);
                                   }
                               }
                           }
                       }
                   }
               }

           }
        }



}



