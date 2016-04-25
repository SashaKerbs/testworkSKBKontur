#include "childmap.h"
#include <fstream>
#include <stdexcept>

#include <iostream>


#define FileChild "ChildFile_version_1_0"
#define FileLike  "LikeFile_version_1_0"

#define nothappy 1
#define happy1 2
#define happy2 4

childmap::childmap()
{

}

/// Функция добавляет ребенка в список детей и создает пустую связь с ребенком
/// name - имя ребенка
void childmap::addChild(string name)
{
    this->childrenNames.push_back(name);
    this->likesMap[childrenNames.size()-1];
}

/// функция загружает список детей из файла
/// fileName - имя файла
void childmap::addChildrenFromFile(string fileName)
{
    string str;
    ifstream fin(fileName);
    if(!fin.is_open())
    {
        throw invalid_argument("file error in function addChildOfFile");
    }
    fin >> str;
    if( str.compare(FileChild) )
    {
        throw invalid_argument("Error file: not current version in function addChildOfFile");
    }

    while( !fin.eof() )
    {
        string child;
        fin >> child;
        addChild(child);
    }
    fin.close();
}
/// Приватная функция ищущая Id ребенка по имени
/// Если ребенок не найден возвращает -1
int childmap::findName(string str)
{
    const int size = childrenNames.size();
    for(int i=0 ; i<size ; ++i)
    {
        if( childrenNames[i] == str )
            return i;
    }
    return -1;
}
/// Функция добавляет связь между детьми
/// child - ребенок которому нравиться likeChild
/// likeChild - нравящийся ребенок
void childmap::addLike(string child, string likeChild)
{
    int idChild, idLikeChild;
    idChild = findName(child);
    idLikeChild = findName(likeChild);
    if(idChild < 0)
    {
        throw invalid_argument("invalid first argument " + child );
    }
    if(idLikeChild < 0)
    {
        throw invalid_argument("invalid second argument " + likeChild );
    }
    if( idChild != idLikeChild )
        (likesMap.operator [](idLikeChild)).insert(idChild);
}
/// Функция загружает из файла связи между детьми
/// fileName имя файла
void childmap::addLikesFromFile(string fileName)
{
    string str;
    ifstream fin(fileName);
    if(!fin.is_open())
    {
        throw invalid_argument("file error in function addLikeOfFile");
    }
    fin >> str;
    if( str.compare(FileLike) )
    {
        throw invalid_argument("Error file: not current version in function addLikeOfFile");
    }

    while(!fin.eof() )
    {
        string child, childLike;
        fin >> child >> childLike;
        addLike(child, childLike);
    }
    fin.close();
}

/// Функция возвращающая список детей которые никому не нравятся.
/// list <string> - список имен детей, которые никому не нравятся.
list <string> childmap::getUnlikeList()
{
    map < int , set < int > >::iterator it =likesMap.begin();
    map < int , set < int > >::const_iterator it_end( likesMap.cend() );
    int i=0;
    //cout << "list of not beliked children:" << endl;
    list <string> result;
    for(; it != it_end ; ++it, ++i )
    {
        if( (it->second).empty())
        {
            result.push_back(childrenNames[it->first]);
            //cout << Name[it->first] << endl;
        }
    }
    return result;
}

/// Функция getListNotHappyChild находит несчастливых детей, у которых нет пары,
/// не включая тех кому никто не нравиться
/// list <string> - возвращает список несчастных детей.
list <string> childmap::getUnhappyList()
{

    //nothappy 1 -несчастный ребенок
    //happy1 2 -счастливый ребенок совзаимной симпатией
    //happy2 4 -ребенок без симпатии
    vector <char> happy;
    happy.resize(childrenNames.size(),happy2);

    //cout << "list of not happy children:" << endl;

    //
    map < int , set < int > >::iterator it =likesMap.begin();
    map < int , set < int > >::const_iterator it_end( likesMap.cend() );
    set< int >::iterator it1;
    set< int >::const_iterator it1_end;


    //Изначально все дети не имют симпатий
    //Если у ребенка появляется симпатия переводим его в несчасливого ребенка
    //из детей которые не счастливы ищется пары со взаимной симпатией
    for(; it != it_end ; ++it )
    {

        if( !(it->second).empty())
        {
            it1 = ((it->second).begin());
            it1_end = ((it->second).end());

            for(; it1 != it1_end; ++it1)
            {
                if(happy[*it1] == happy2)
                    happy[*it1] = nothappy;
                set <int> &listLike =  likesMap[*it1];
                if( listLike.find(it->first) != listLike.end() )
                {
                    happy[*it1] = happy1;
                    happy[it->first] = happy1;
                }
            }
        }
    }

    list <string> result;
    for(int i = 0; i < happy.size(); ++i)
    {
        if(happy[i] == nothappy)
            result.push_back(childrenNames[i]);
    }
    return result;
}

/// Функция ищущая самых популярных детей
/// numberChild - показатель популярности если больше то ребенок считается популярным.
list <string> childmap::getPopularList(unsigned int numberChild)
{
    map < int , set < int > >::iterator it =likesMap.begin();
    map < int , set < int > >::const_iterator it_end( likesMap.cend() );
    int i=0;

    list <string> result;
    //cout << "list of popular children:" << endl;
    for(; it != it_end ; ++it, ++i )
    {
        if( (it->second).size() >= numberChild)
        {
            result.push_back(childrenNames[it->first]);
        }
    }
    return result;
}
