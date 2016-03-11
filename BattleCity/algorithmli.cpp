#include <QtDebug>
#include <QException>
#include "algorithmli.h"

algorithmLI::algorithmLI()
{
    p_ReadFromFile = new Parsing();
    p_ReadFromFile->ParsTextFile(":/log_parsing.txt", n_map);   // Завантаження карти з файлу
}

bool algorithmLI::SearchWay(int x, int y, int end_x, int end_y)
{
    _begin_x  = x;
    _begin_y  = y;
    _end_x    = end_x;
    _end_y    = end_y;

    int numberAllPassableElement = 0; // счётчик по всем елементам вектора
    int distance = 10;
    int tempNumberPassable = 0;

    bool added = false;
    bool size  = true;

    point begin;
    begin.x     = x;
    begin.y     = y;
    begin.index = 9;

    vectorPassableElement.push_back(begin); // добавляем начало в список

    n_map[x][y] = 9;

    while (added || size)
    {
        // получаем текущие координаты
        x = vectorPassableElement[numberAllPassableElement].x;
        y = vectorPassableElement[numberAllPassableElement].y;

        added = false;
        size  = false;

        if (x == end_x && y == end_y) // если текущие координаты есть конечными выйти из функции
        {
            vectorFoundWay.push_back(vectorPassableElement[numberAllPassableElement]);
            return true;
        }

        ++numberAllPassableElement;

        if (x != 0) // если не на границе матрицы
        {
            if (
                (n_map[x-1][y] == 0) ||
                (n_map[x-1][y] == 2) ||
                (n_map[x-1][y] == 3) ||
                (n_map[x-1][y] == 4)
               )  // если проходимый елемент
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index) // если предыдущий индекс такой же как и этот
                {
                    ++distance;                                                  // увеличиваем индекс
                }

                n_map[x-1][y] = distance;               // установливаем индекс в матрицу
                begin.x = x-1;                          // координаты
                begin.y = y;                            // индекса
                begin.index = distance;                 // индекс
                vectorPassableElement.push_back(begin); // добавляем текущую точку в вектор проходимых
                added = true;                           // есть возможность подальшего продвижения
            }
        }
        if (y < CNT_COLS_MAP-1)
        {
            if (
                (n_map[x][y+1] == 0) ||
                (n_map[x][y+1] == 2) ||
                (n_map[x][y+1] == 3) ||
                (n_map[x][y+1] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x][y+1] = distance;
                begin.x = x;
                begin.y = y+1;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }

        if (x < CNT_COLS_MAP - 1)
        {
            if (
                (n_map[x+1][y] == 0) ||
                (n_map[x+1][y] == 2) ||
                (n_map[x+1][y] == 3) ||
                (n_map[x+1][y] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x+1][y] = distance;
                begin.x = x+1;
                begin.y = y;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }
        if (y > 0)
        {
            if (
                (n_map[x][y-1] == 0) ||
                (n_map[x][y-1] == 2) ||
                (n_map[x][y-1] == 3) ||
                (n_map[x][y-1] == 4)
               )
            {
                tempNumberPassable = numberAllPassableElement;
                --tempNumberPassable;

                if (distance == vectorPassableElement[tempNumberPassable].index)
                {
                    ++distance;
                }

                n_map[x][y-1] = distance;
                begin.x = x;
                begin.y = y-1;
                begin.index = distance;
                vectorPassableElement.push_back(begin);
                added = true;
            }
        }

        if (distance == 10) // если первый проход
        {
            ++distance;
        }

        if (numberAllPassableElement >= vectorPassableElement.size()) // если елементов для проверки нет
        {
            return false;                                             // выходим из  функции
        }
        else
        {
            size = true;
        }
    }
    return false; // если пути не нашли
}

bool algorithmLI::AuditSearchWay(int x_begin, int y_begin, int x_end, int y_end, QString nameBot)
{
    _nameBot = nameBot;

    int _i = 0;
    if (SearchWay(x_begin, y_begin, x_end, y_end))
    {
        int rows;
        int cols;
        int index;
        point tempPoint;

        rows = vectorPassableElement[vectorPassableElement.size()-1].x;
        cols = vectorPassableElement[vectorPassableElement.size()-1].y;
        index = vectorPassableElement[vectorPassableElement.size()-1].index;

        while (index >= 9) // пока не достигли начала
        {
            --index;

            if (n_map[rows+1][cols] == index)
            {
                tempPoint.x = rows+1;
                tempPoint.y = cols;
                tempPoint.index = index;
                vectorFoundWay.push_back(tempPoint);
            }
            else if (n_map[rows][cols-1] == index)
            {
                tempPoint.x = rows;
                tempPoint.y = cols-1;
                tempPoint.index = index;
                vectorFoundWay.push_back(tempPoint);
            }
            else if (n_map[rows-1][cols] == index)
            {
                tempPoint.x = rows-1;
                tempPoint.y = cols;
                tempPoint.index = index;
                vectorFoundWay.push_back(tempPoint);
            }
            else if (n_map[rows][cols+1] == index)
            {
                tempPoint.x = rows;
                tempPoint.y = cols+1;
                tempPoint.index = index;
                vectorFoundWay.push_back(tempPoint);
            }

            rows = tempPoint.x;
            cols = tempPoint.y;
        }
    }
    else
    {
        qDebug() << "Path not found(((";
    }
}

void algorithmLI::setBadWay(int y, int x)
{
    qDebug() << "bad position";
    n_map[x][y] = 7;
}
