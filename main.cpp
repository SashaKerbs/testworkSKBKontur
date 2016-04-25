#include <iostream>
#include <algorithm>
#include "childmap.h"
using namespace std;
void printList(list <string>& liststr,string title = "")
{
    cout << title << endl;
    list <string>::iterator it = liststr.begin();
    list <string>::const_iterator it_end = liststr.end();
    for(;it != it_end; ++it)
    {
        cout << *it << endl;
    }
    cout << " " << endl;
}

int main(int argc, char *argv[])
{
    try
    {
        childmap A;
        /*A.addChild("Ivan1");
        A.addChild("Ksenia1");
        A.addChild("Roman1");
        A.addChild("Efim1");
        A.addChild("Ivan2");
        A.addChild("Ksenia2");
        A.addChild("Roman2");
        A.addChild("Efim2");
        A.addChild("Ivan3");
        A.addChild("Ksenia3");
        A.addChild("Roman3");
        A.addChild("Efim3");
        A.addChild("Ivan4");
        A.addChild("Ksenia4");
        A.addChild("Roman4");
        A.addChild("Efim4");

        A.addLike("Ivan1","Ksenia2");
        A.addLike("Roman4","Ivan3");
        A.addLike("Ivan1","Ksenia1");
        A.addLike("Ksenia2","Ivan1");
        A.addLike("Roman4","Ksenia2");
        A.addLike("Ksenia2","Ivan3");*/
        A.addChildrenFromFile("Name.txt");
        A.addLikesFromFile("Like.txt");

        list <string>  liststr1;
        liststr1 = A.getUnlikeList();
        printList(liststr1,"list of not beliked children:");
        list <string>  liststr;
        liststr = A.getUnhappyList();
        printList(liststr,"list of not happy children:");
        liststr = A.getPopularList(1);
        printList(liststr,"list of popular children:");
    }
    catch(invalid_argument& e)
    {
        cerr << e.what()<<endl;
        return -1;
    }

    return 0;
}
