#include <stdio.h>
#include <vector>
#include <iostream>

#define x_min 0
#define x_max 8
#define y_min 0
#define y_max 8
#define x_start 5
#define y_start 5

int x ,y;
struct imove
{
    int x ;
    int y;
};
std::vector<imove> path;
std::vector<imove> moves;
int passed;
bool pos[x_max][y_max];

bool checkNext(std::string prefix)
{
    if (passed == (x_max * y_max)) return true;
    bool ok = false;
    prefix.append("-");
    for (auto i = moves.begin() ; i != moves.end() ; i++)
    {

        int tempx, tempy;
        tempx = x + (*i).x;
        tempy = y + (*i).y;


        if( tempx < x_min || tempx > x_max || tempy < y_min || tempy > y_max )
        {
            //std::cout << "out of boundary " << std::endl;
            continue;
        }

        std::cout << prefix << "checking " << "x: " << tempx << " y: " << tempy << std::endl;

        if (pos[tempx][tempy] == true)
        {
            //std::cout << "already visited " << std::endl;
            continue;
        }
        x = tempx;
        y = tempy;
        path.push_back(imove{.x=x, .y = y});
        passed++;
        pos[x][y] = true;

        if(checkNext(prefix) == false)
        {
            path.pop_back();
            passed--;
            pos[x][y] = false;
            x = path.back().x;
            y = path.back().y;

        }
        else
        {
            ok = true;
            return true;
        }

    }
    return false;
}

int main() {

    passed = 0;
    for (int i = 0 ; i < x_max ; i++)
    {
        for (int j = 0 ; j < y_max ; j++)
            pos[i][j] = false;
    }
    moves.push_back(imove{.x = 1, .y = 2});
    moves.push_back(imove{.x = 1, .y = -2});
    moves.push_back(imove{.x = -1, .y = 2});
    moves.push_back(imove{.x = -1, .y = -2});
    moves.push_back(imove{.x = 2, .y = 1});
    moves.push_back(imove{.x = 2, .y = -1});
    moves.push_back(imove{.x = -2, .y = 1});
    moves.push_back(imove{.x = -2, .y = -1});
    //diagonal move
//    moves.push_back(imove{.x = 1, .y = 0});
//    moves.push_back(imove{.x = -1, .y = 0});
//    moves.push_back(imove{.x = 0, .y = 1});
//    moves.push_back(imove{.x = 0, .y = -1});

    bool found = false;
    for (int i = 0 ; i != x_max ; i++)
    {
        if(found ) break;
        for (int j = 0 ; j < y_max ; j++)
        {
            std::string pre = "";
            passed = 1;

            x = (i+x_start)%x_max;
            y = (j+y_start)%y_max;
            path.push_back(imove{.x=x ,
                                 .y=y});
            if(checkNext(pre) == true)
            {
                std::cout << "passed \n";
                for (auto p = path.begin() ; p != path.end() ; p++)
                    std::cout << "the move is x:" << p->x << " and y: " << p->y << std::endl;
                found = true;
                break;
            }
            path.pop_back();
        }
    }

   return 0;
}
