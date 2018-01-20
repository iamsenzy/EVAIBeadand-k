#include "labirinth_modell.h"

Labirinth_Modell::Labirinth_Modell()
{
    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(showTime()));
    gameTime=0;
    qsrand(QTime::currentTime().msec());

}

Labirinth_Modell::~Labirinth_Modell()
{
    delete _timer;
}

void Labirinth_Modell::pauseGame()
{
        if (_timer->isActive())
        {
            messageChanged(trUtf8("Piheno"));
            _timer->stop();
        }
        else
            _timer->start();

}

void Labirinth_Modell::creatMap(std::string map_path)
{

    if (!_timer->isActive())
           _timer->start();

    gameTime=0;

    map_file.open(map_path.c_str());
    map_file >> Map_Size;
    for(int i=0;i<Map_Size;++i)
    {

        for(int j=0;j<Map_Size;++j)
        {
            int x;
            map_file>>x;
            if(x==2) { Gamer.x=i; Gamer.y=j; }
            if(x==3) { Finish.x=i; Finish.y=j; }
            Map.push_back((x));
        }
    }
    map_file.close();
}

void Labirinth_Modell::removeMap()
{
    Map.erase(Map.begin(),Map.end());
}


void Labirinth_Modell::swap(int a)
{
    if(_timer->isActive())
    {
    if(a==Finish.x*Map_Size+Finish.y) {
        messageChanged("vege");
        _timer->stop();
        emit gameEnd();
    }
    else

    {

         int tmp=Map[Gamer.x*Map_Size+Gamer.y];
         Map[Gamer.x*Map_Size+Gamer.y]=Map[a];
         Map[a]= tmp;
         Gamer.x=a/Map_Size;
         Gamer.y=a % Map_Size;
    }
    }

}

int Labirinth_Modell::Getter(int index )
{
    return Map[index];
}

void Labirinth_Modell::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm:ss");
    gameTime++;
    messageChanged(QString::number(gameTime/(18000)) + " masodperc telt el eddig.");
}
