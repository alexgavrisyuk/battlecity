#ifndef TANKBOT_H
#define TANKBOT_H

#include "tank.h"
#include "constants.h"
#include <vector>       // vector<T>
#include "algorithmli.h"

using std::vector;

struct QPoint2D {
    int x;
    int y;

    QPoint2D() {
        x = y = 0;
    }

    QPoint2D(int x, int y) {
        this->x  = x;
        this->y  = y;
    }
};

class TankBot: public Tank
{
    Q_OBJECT
public:
    explicit TankBot(const QList<QString> fileNames);
    void setMap(int map[CNT_ROWS_MAP][CNT_COLS_MAP]);
    ~TankBot();

private:
    enum MODE_ATACK {FREE, KILL_PLAYER, KILL_FLAG};
    MODE_ATACK MODE_OF_ATACK;
    void setModeOfAtack(MODE_ATACK M_A);

    int  map[CNT_ROWS_MAP][CNT_COLS_MAP];
    void outMap();

    vector <QPoint2D> path;
    vector <QPoint2D> shortPath;

    bool searchWay; // был ли поиск пути
    int  indexWay;   // в какой точке сейчас находимся

    algorithmLI    *algorithmSearchWay;
    QVector<point> vectorFoundWay;

    int    mapSearchWay[CNT_ROWS_MAP][CNT_COLS_MAP];
    QTimer *timerFoundNewWay;

    point _previousPoint;

public:
    int x_end;
    int y_end;
    int _xPlayer;
    int _yPlayer;

    bool addTank;       // розрешение добавлени бота на карту
    int numberDeaths;   // количевство смертей

signals:
    void signalOneSearchWay(int x_begin, int y_begin, int x_end, int y_end);

public slots:
    void slotForStartSearchPath();
    void slotSearchPath(int x_begin, int y_begin, int x_end, int y_end);
    void Atack(int xPlayer, int yPlayer);   // поиск пути для игроков
    void Atack();                           // поиск пути для ботов
};

#endif // TANKBOT_H