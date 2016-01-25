#ifndef BATTLECITYMAP_H
#define BATTLECITYMAP_H

#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QThread>

#include "tankforplayer.h"
#include "parsing.h"
#include "redwall.h"
#include <tankbot.h>
#include "udpclient.h"

class BattleCityMap: public QGraphicsScene {
    Q_OBJECT
public:
    explicit BattleCityMap(int regimeGame, UdpClient*& client);
            ~BattleCityMap();

    int n_Map[CNT_ROWS_MAP][CNT_COLS_MAP];      // розмер карты
    QList <QGraphicsItem *> listObjectAtBase;   // Елементы что розмещены вокруг базы

private:
    QTimer *timerMoveTank1;                 // Таймер для переміщення танку плеєра 1
    QTimer *timerMoveTank2;                 // та плеєра 2
    QTimer *timerMoveBot;
    QTimer *timerMoveBot_2;
    QTimer *timerMoveBot_3;
    QTimer *timerMoveBot_4;
    QTimer *timerMoveBots;
    QTimer *timerAuditBots;

    QTimer *timerForShowBonus;              // Таймер для відображення та знищення бонусів
    QTimer *timerRemoveStar;

    QTimer *timerForShowProtectionBase;
    QTimer *timerRemoveProtectionBase;

    QTimer *timerForShowTimeBonus;
    QTimer *timerForSearchTimerBonus;
    QTimer *timerRemoveTimerBonus;

    QTimer *timerForShowExplosionBonus;
    QTimer *timerRemoveExplosionBonus;

    TankForPlayer *TankForPlay1;            // Танк первого и
    TankForPlayer *TankForPlay2;            // в второго игрока

    TankBot       *bot;
    TankBot       *bot_2;
    TankBot       *bot_3;
    TankBot       *bot_4;

    QGraphicsTextItem* textGameOver;

    bool runOneBot;     // розрешает добавление первого бота на карту
    bool runTwoBot;
    bool runThreeBot;
    bool runFourBot;
    bool updateOnlyTwoBots; // переместить в данный момент только 2 бота(что-бы все боти одновременно не обновлялисьs)
    int  updateOnlyOneBots; // переместить в данный момень только 1 бота(когда все боты уже на карте)

    int _regimeGame;

    QGraphicsPixmapItem *pixmapForStar;     // Тут зберігається картинка бонуса
    QGraphicsPixmapItem *pixmapForBase;
    QGraphicsPixmapItem *pixmapForBuildBase;
    QGraphicsPixmapItem *pixmapForRemoveBase;
    QGraphicsPixmapItem *pixmapForTime;
    QGraphicsPixmapItem *pixmapForExplosion;

    QList <QGraphicsPixmapItem *> listItems;    // обьекты белой стенки для защиты базы(если взят бонус защитить базу)

    Parsing *p_ReadFromFile;                // Клас для парсингу карти

    /* /// Сеть /// */

    UdpClient *_client;
    QTimer    *timerForSendPosPlayer;
    bool       shot;

protected:
    virtual void keyPressEvent(QKeyEvent *event);       // Обробка нажаття клавіші та
    virtual void keyReleaseEvent(QKeyEvent *event);     // відпущення


signals:
    void signalTimeoutForOneBot   (                        ); // вызывается когда нужно переместить бота
    void signalTimeoutForTwoBot   (                        );
    void signalTimeoutForThreeBot (int xPlayer, int yPlayer);
    void signalTimeoutForFourBot  (int xPlayer, int yPlayer);

    void signalMoveOneBot   ();
    void signalMoveTwoBot   ();
    void signalMoveThreeBot ();
    void signalMoveFourBot  ();

    void signalUpdateBase(QString typeWall);

    void signalGameOver(int numberKillsOnePlayer, int numberKillsTwoPlayer);

public slots:
    void slotAddBot_1 ();           // появление бота на карте после уничтожения
    void slotAddBot_2 ();
    void slotAddBot_3 ();
    void slotAddBot_4 ();

    void slotShowBonus   ();        // отображение бонусов
    void slotRemoveBonus ();        // удаление бонусов

    void slotShowProtectionBase      ();    // показать бонус защиты базы
    void slotBuildProtectionForBase  ();    // построить защуиту вокруг базы
    void slotRemoveBonusForBase      ();    // удалить защиту вокруг базы

    void slotShowTimeBonus           ();    // показать бонус остановки танков
    void slotStopAllBots             ();    // остановить всех танков
    void slotRemoveBonusForTimeBonus ();    // завести всех танков

    void slotShowExplosionBonus        ();
    void slotRemoveExplosionBonus      ();
    void slotRemoveExplosionBonusTimer ();

    void slotTimeout     ();        // определяет какой бот должен быть перемещён
    void slotMoveBots    ();        // вызывает слот который вызывает слот который определяет какой бот должен быть перемещён
    void slotRunOneBot   ();        // первоначальное помещение бота на карту
    void slotRunTwoBot   ();
    void slotRunThreeBot ();
    void slotRunFourBot  ();

    void slotGameOver    ();

    void slotSetPosPlayerForSend();
    void slotMoveOpponent(int x, int y, int rotate, bool shot2);
    void slotShotTank();
};

#endif // BATTLECITYMAP_H
