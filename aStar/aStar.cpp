#include <stdio.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <vector>

#define X_LIMIT 8
#define Y_LIMIT 6

#define START_X 2
#define START_Y 2

#define DEST_X 6
#define DEST_Y 2


/* ------------------------------------------
   -                                        -
   -            node struct                 -
   -                                        -
   ------------------------------------------
   #    fn = gn + hn
*/
typedef struct st_node
{
    int x,y;
    struct st_node* parent_node = 0;
    int fn = 0;
    int gn = 0;
    int hn = 0;
    bool is_blocked = false;
    bool is_closed_node = false;
    bool operator<(const st_node s) const 
    {
        return this->fn > s.fn;
    }
}node;


/* ------------------------------------------
   -                                        -
   -                map                     -
   -                                        -
   ------------------------------------------
*/
static node map[Y_LIMIT][X_LIMIT] = {node{.fn = 0, .gn = 0, .hn = 0}};

static std::priority_queue<node> open_node;


/* ------------------------------------------
   -                                        -
   -       print map on console             -
   -                                        -
   ------------------------------------------
*/
void print_map()
{
    
    for(auto& i : map)
    {
        
        for(auto& j : i)
        {
            if(!j.is_blocked)
                {
                    if(j.y == DEST_Y && j.x == DEST_X)
                        std::cout << "|OOOOOOO";
                    else if(j.is_closed_node)
                        std::cout << "|" << j.fn << "C\t";
                    else
                        std::cout << "|" << j.fn << "\t";
                }
            else
                std::cout << "|XXXXXXX";
        }
        

        std::cout << "|" << std::endl;

        for(auto& j : i)
        {
            if(j.y == DEST_Y && j.x == DEST_X)
                std::cout << "|OOOOOOO";
            else if(!j.is_blocked)
                std::cout << "|" << j.gn << "  " << j.hn << "\t";
            else
                std::cout << "|XXXXXXX";
        }

        std::cout << "|" << std::endl;

        std::cout << "---------------------------------------------------------------------------------" << std::endl;
    }

    std::cout << "==================================================================================" << std::endl;
}

/* ------------------------------------------
   -                                        -
   -          blocked road setting          -
   -                                        -
   ------------------------------------------
*/
void setting_blocked_road()
{
    map[1][4].is_blocked = true;
    map[2][4].is_blocked = true;
    map[3][4].is_blocked = true;
    
}

/* ------------------------------------------
   -                                        -
   -             init node's hn             -
   -                                        -
   ------------------------------------------
*/
void init_hueristic()
{
    for(int i = 0 ; i < Y_LIMIT ; i++)
    {
        for(int j = 0 ; j < X_LIMIT ; j++)
        {
            map[i][j].x = j;
            map[i][j].y = i;

            if( (i == DEST_Y && j == DEST_X) ||
                (i == START_Y && j == START_X) ||
                (map[i][j].is_blocked))
            {
                continue;
            }
            else
            {
                map[i][j].hn = 10*abs(i-DEST_Y) + 10*abs(j-DEST_X);
            }
        }
    }
}


void add_open_node(int current_point[])
{
    int y,x = 0;
    int new_y, new_x = 0;
    y = current_point[0];
    x = current_point[1];

    if(y - 1 >= 0)  // 12
    {
        new_y = y-1;
        new_x = x;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 10;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 10))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(y - 1 >= 0 && x + 1 < X_LIMIT)  // 1
    {
        new_y = y-1;
        new_x = x+1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 14;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 14))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(x + 1 < X_LIMIT)  // 3
    {
        new_y = y;
        new_x = x+1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn +10;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 10))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(y + 1 < Y_LIMIT && x + 1 < X_LIMIT)  // 5
    {
        new_y = y+1;
        new_x = x+1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 14;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 14))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(y + 1 < Y_LIMIT)  // 6
    {
        new_y = y+1;
        new_x = x;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 10;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 10))
                {
                    map[new_y][new_x].gn = map[y][x].gn + 10;
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(y + 1 < Y_LIMIT && x - 1 >= 0)  // 7
    {
        new_y = y+1;
        new_x = x-1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 14;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 14))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(x - 1 < X_LIMIT)  // 9
    {
        new_y = y;
        new_x = x-1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 10;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 10))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    if(y - 1 >= 0 && x - 1 >= 0)  // 11
    {
        new_y = y-1;
        new_x = x-1;
        if(!map[new_y][new_x].is_blocked && !map[new_y][new_x].is_closed_node)
        {
            if(map[new_y][new_x].gn == 0)
            {
                map[new_y][new_x].gn = map[y][x].gn + 14;
                map[new_y][new_x].parent_node = &(map[y][x]);
            }
            else
            {
                if(map[new_y][new_x].gn > (map[y][x].gn + 14))
                {
                    map[new_y][new_x].parent_node = &(map[y][x]);
                }
            }
            map[new_y][new_x].fn = map[new_y][new_x].gn + map[new_y][new_x].hn;
            open_node.push(map[new_y][new_x]);
        }
    }

    map[y][x].is_closed_node = true;

    // int open_node_size = open_node.size();
    // for(int i = 0 ; i < open_node_size; i++)
    // {
    //     printf("index %d ::: gn=%d, hn=%d, fn=%d\n", i, open_node.top()->gn,open_node.top()->hn, open_node.top()->fn);
    //     open_node.pop();
    // }

    print_map();
}

/*
    -----------------------------------------
    -                                       -
    -         pop min fn node               -
    -                                       -
    -----------------------------------------
*/
bool pop_open_node(int current_point[])
{
    while(map[open_node.top().y][open_node.top().x].is_closed_node)
    {
        open_node.pop();
    }

    if( open_node.size() == 0)
    {
        return true; //unconnected, from start to destination
    }
    else
    {
        current_point[0] = open_node.top().y;
        current_point[1] = open_node.top().x;

        open_node.pop();

        return false;
    }
}


/* ------------------------------------------
   -                                        -
   -             find best route            -
   -                                        -
   ------------------------------------------
*/
void find_route()
{
    map[START_Y][START_X].is_closed_node = true;

    int current_point[2] ={START_Y,START_X};
    
    while(true)
    {
        if(current_point[0] == DEST_Y && current_point[1] == DEST_X)
        {

            node* route = &map[current_point[0]][current_point[1]];

            printf("------------------------\n");
            printf("-   found rute         -\n");
            printf("------------------------\n");
            printf("-\n");
            printf("-");
            while(route)
            {
                if(route->parent_node)
                    printf("[%d,%d] -> ", route->x,route->y);
                else
                    printf("[%d,%d]\n", route->x,route->y);


                route = route->parent_node;
            }



            printf("-");
            printf("------------------------------------------------------------------------------------------------\n");


            break;
        }

        add_open_node(current_point);

        bool is_unconnected = pop_open_node(current_point);

        if(is_unconnected)
        {
            std::cout << "unconnected" << std::endl;
        }
    }
}

/* ------------------------------------------
   -                                        -
   -             algorithm                  -
   -                                        -
   ------------------------------------------
*/
void do_astar_algorithm()
{
    setting_blocked_road();     //blocked road setting

    init_hueristic();

    print_map();                

    find_route();

}


/* ------------------------------------------
   -                                        -
   -                main                    -
   -                                        -
   ------------------------------------------
*/
int main(int argc, char** argv)
{
    do_astar_algorithm();
    return 0;
}
