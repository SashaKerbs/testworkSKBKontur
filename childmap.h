#ifndef CHILDMAP_H
#define CHILDMAP_H
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

/// класс childmap реализует тестовое задание для фирмы СКБ Контур
/// класс содержит функции добавления имен и соединений
/// так же функции поиска среди детей:
/// список всех не любимчиков, то есть детей которые никому не симпатичны
/// список всех несчастных детей, то есть тех, которые не симпатичны ни одному ребенку из тех, кто симпатичен им самим. За исключением тех детей, которым никто не симпатичен.
/// список любимчиков, то есть всех детей, которые симпатичны максимальному количеству других детей.
class childmap
{
    // массив Имен детей
    // Id ребенка = номер имени в векторе name
    vector < string > childrenNames;
    // map хранящий в качестве первого парраметра Id ребенка
    // в качестве второго множество Id детей, которым нравиться этот ребенок
    map < int , set < int > > likesMap;
public:
    childmap();
    void addChildrenFromFile(string);
    void addLikesFromFile(string);
    void addChild(string);
    void addLike(string child, string likeChild);
    list <string> getUnlikeList();
    list <string> getUnhappyList();
    list <string> getPopularList(unsigned int numberChild);
private:
    int findName(string);
};

#endif // CHILDMAP_H
