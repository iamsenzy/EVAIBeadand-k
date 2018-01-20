#ifndef LABIRINTH_MODELL_H
#define LABIRINTH_MODELL_H

#include <QObject>
#include <iostream>
#include <fstream>
#include <QVector>
#include <QTimer>
#include <QTime>

struct player
{
    int x;
    int y;
};

class Labirinth_Modell : public QObject
{
    Q_OBJECT
public:
    Labirinth_Modell();
    ~Labirinth_Modell();
    int get_Size() { return Map_Size;}
    player Gamer_Position(){return Gamer;}
    int Getter(int index );

signals:
    void messageChanged(QString message);
    void gameEnd();

public slots:
    void creatMap(std::string map_path );
    void swap(int a);
    void pauseGame();
    void removeMap();

private slots:
    void showTime();

private:
    std::ifstream map_file;
    QVector<char> Map;
    int Map_Size;
    player Finish;
    player Gamer;
    QTimer* _timer;
    int gameTime;
};

#endif // LABIRINTH_MODELL_H
