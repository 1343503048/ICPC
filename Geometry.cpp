
/***********************************************************
   
        FileName：Geometry.cpp
          Author：zQ
           Email: zq216991@foxmail.com
          Create：2017-10-15 22:25:35
    Descripttion：计算几何模板
   
*************************************************************/
#define debug printf("%s: %d\n", __FUNCTION__, __LINE__);

#include <bits/stdc++.h>
using namespace std;

struct Point{
    int x,y;
    Point operator -(const Point &b)const {
        return Point(x - b.x,y - b.y);
    }
    int operator *(const Point &b)const {
        return x*b.x + y*b.y;
    }
    int operator ^(const Point &b)const {
        return x*b.y - y*b.x;
    }
};

struct Line {
    Point s,e;
};

int xmult(Point p0,Point p1,Point p2) //计算p0p1 X p0p2
{
    return (p1-p0)^(p2-p0);
}

int main() {

    return 0;
}
