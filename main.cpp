#include <iostream>
#include <vector>
#include "unistd.h"
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;
#define sqrt (int)sqrt(n)
#define north(x, y) (x + (y - 1) * sqrt)
#define south(x, y) (x + (y + 1) * sqrt)
#define east(x, y) ((x + 1) + y * sqrt)
#define west(x, y) ((x - 1) + y * sqrt)

// we hash each node into a specific number and put it into the queue
int hash_function(vector<int> board)
{
    int hashed = 0;
    int size = board.size();
    for (int i = 0; i < size; i++)
    {
        hashed += pow(board.size(), size - i - 1) * board.at(i);
    }
    return hashed;
}

// we anti-hash each hashed node into vector
void anti_hash_function(vector<int> &anti_hash, int node, int n)
{
    int ratio = node;
    int reminder = -INT_MAX;
    while (ratio > 0)
    {
        reminder = ratio % n;
        ratio = ratio / n;
        anti_hash.insert(anti_hash.begin(), reminder);
    }
    if (anti_hash.size() < n)
    {
        anti_hash.insert(anti_hash.begin(), 0);
    }
}

int Uniform_Cost_Search(vector<pair<int, int>> &queue)
{
    // we do not need to do anything for Uniform Cost Search
    return 0;
}

static bool cmp(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{
    return a.first < b.first;
}

int A_star_with_the_Misplaced_Tile(vector<pair<int, int>> &queue, int n)
{
    // we do not need to do anything for Uniform Cost Search
    vector<pair<int, pair<int, int>>> paired;
    vector<int> anti_hash;
    vector<int> goal_vector;
    vector<pair<int, int>> sorted;
    int misplaced;
    for (int i = 1; i < n; i++)
    {
        goal_vector.push_back(i);
    }
    goal_vector.push_back(0);
    for (int i = 0; i < queue.size(); i++)
    {
        misplaced = 0;
        anti_hash.clear();
        anti_hash_function(anti_hash, queue[i].first, n);
        for (int j = 0; j < anti_hash.size(); j++)
        {
            if (anti_hash[j] > 0 && anti_hash[j] != goal_vector[j])
            {
                misplaced++;
            }
        }
        paired.push_back(make_pair(misplaced + queue[i].second, queue[i]));
    }
    sort(paired.begin(), paired.end(), cmp);
    for (int i = 0; i < paired.size(); i++)
    {
        sorted.push_back(paired[i].second);
    }
    queue = sorted;
    return 0;
}

int A_star_with_the_Manhattan_distance(vector<pair<int, int>> &queue, int n)
{
    // we do not need to do anything for Uniform Cost Search
    vector<pair<int, pair<int, int>>> paired;
    vector<int> anti_hash;
    vector<int> goal_vector;
    vector<pair<int, int>> sorted;
    int misplaced;
    int goal_x, goal_y, x, y;
    for (int i = 1; i < n; i++)
    {
        goal_vector.push_back(i);
    }
    goal_vector.push_back(0);
    for (int i = 0; i < queue.size(); i++)
    {
        misplaced = 0;
        anti_hash.clear();
        anti_hash_function(anti_hash, queue[i].first, n);
        for (int j = 0; j < anti_hash.size(); j++)
        {
            for (int k = 0; k < goal_vector.size(); k++)
            {
                if (anti_hash[j] > 0 && anti_hash[j] == goal_vector[k])
                {
                    x = j % sqrt;
                    y = j / sqrt;
                    goal_x = k % sqrt;
                    goal_y = k / sqrt;
                    misplaced += (abs(x - goal_x) + abs(y - goal_y));
                }
            }
        }
        paired.push_back(make_pair(misplaced + queue[i].second, queue[i]));
    }
    sort(paired.begin(), paired.end(), cmp);
    for (int i = 0; i < paired.size(); i++)
    {
        sorted.push_back(paired[i].second);
    }
    queue = sorted;
    return 0;
}

bool not_find_node(vector<int> queue, int node)
{
    bool not_find = true;
    for (int i = 0; i < queue.size(); i++)
    {
        if (queue.at(i) == node)
        {
            not_find = false;
        }
    }
    return not_find;
}

void expand(vector<pair<int, int>> &queue, vector<int> &global_queue, int node, int n, int &expanded_size, int depth)
{
    vector<int> anti_hash, north_node, south_node, east_node, west_node;
    anti_hash_function(anti_hash, node, n);
    int temp;
    north_node = anti_hash;
    south_node = anti_hash;
    east_node = anti_hash;
    west_node = anti_hash;
    int x, y;
    for (int i = 0; i < anti_hash.size(); i++)
    {
        if (anti_hash.at(i) == 0)
        {
            x = i % sqrt;
            y = i / sqrt;
            if (0 <= north(x, y) && north(x, y) < anti_hash.size())
            {
                north_node.at(i) = north_node[north(x, y)];
                north_node[north(x, y)] = 0;
                if (not_find_node(global_queue, hash_function(north_node)))
                {
                    queue.push_back(make_pair(hash_function(north_node), depth + 1));
                    global_queue.push_back(hash_function(north_node));
                    expanded_size++;
                }
            }
            if (0 <= south(x, y) && south(x, y) < anti_hash.size())
            {
                south_node.at(i) = south_node[south(x, y)];
                south_node[south(x, y)] = 0;
                if (not_find_node(global_queue, hash_function(south_node)))
                {
                    queue.push_back(make_pair(hash_function(south_node), depth + 1));
                    global_queue.push_back(hash_function(south_node));
                    expanded_size++;
                }
            }
            if ((0 <= east(x, y) && east(x, y) < anti_hash.size()) && ((x + 1) < sqrt))
            {
                east_node.at(i) = east_node[east(x, y)];
                east_node[east(x, y)] = 0;
                if (not_find_node(global_queue, hash_function(east_node)))
                {
                    queue.push_back(make_pair(hash_function(east_node), depth + 1));
                    global_queue.push_back(hash_function(east_node));
                    expanded_size++;
                }
            }
            if ((0 <= west(x, y) && west(x, y) < anti_hash.size()) && (0 <= (x - 1)))
            {
                west_node.at(i) = west_node[west(x, y)];
                west_node[west(x, y)] = 0;
                if (not_find_node(global_queue, hash_function(west_node)))
                {
                    queue.push_back(make_pair(hash_function(west_node), depth + 1));
                    global_queue.push_back(hash_function(west_node));
                    expanded_size++;
                }
            }

            queue.erase(queue.begin());
        }
    }
}

int main(int argc, char *argv[])
{
    // the default setting
    int opt, t = 0, n = 9, m = 0, hashed, temp_node = -INT_MAX;
    // record the largest size of queue for space complexity
    int queue_size = 1;
    // record expanded node size for time complexity
    int expanded_size = 0;
    // create goal vector
    vector<int> goal_vector;
    int goal_state = -INT_MAX;
    // create a queue
    vector<pair<int, int>> queue;
    vector<int> global_queue;
    // create the initial state
    vector<int> board;
    while ((opt = getopt(argc, argv, "t:n:m:")) != EOF)
        switch (opt)
        {
        case 't':
            t = atoi(optarg);
            break;
        case 'n':
            n = atoi(optarg);
            break;
        case 'm':
            m = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, " usuage is ./8_puzzle -t -n -m \n where -t follows by test number (0-7 for sample puzzles, 8 for your own puzzle),"
                            " -n follows by size of puzzle (9 for 8-puzzle),\n -m follows by method (0 for Uniform Cost Search, 1 for A* with the Misplaced Tile heuristic, "
                            "2 for A* with the Manhattan Distance heuristic)\n");
        default:
            cout << endl;
            abort();
        }
    // Initialize goal vector and hash goal vector
    for (int i = 1; i < n; i++)
    {
        goal_vector.push_back(i);
    }
    goal_vector.push_back(0);
    goal_state = hash_function(goal_vector);
    // your own puzzle
    if (t == 8)
    {
        int temp;
        cout << "Please input your puzzle in a row based order\n";
        for (int iter = 0; iter < n / sqrt; iter++)
        {
            printf("Input the row %d of your own puzzle:\n", iter + 1);
            for (int i = 0; i < sqrt; i++)
            {
                cin >> temp;
                board.push_back(temp);
            }
        }
    }
    // depth 0
    if (t == 0)
    {
        vector<int> test1 = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        board = test1;
    }
    // depth 2
    if (t == 1)
    {
        vector<int> test2 = {1, 2, 3, 4, 5, 6, 0, 7, 8};
        board = test2;
    }
    // depth 4
    if (t == 2)
    {
        vector<int> test3 = {1, 2, 3, 5, 0, 6, 4, 7, 8};
        board = test3;
    }
    // depth 8
    if (t == 3)
    {
        vector<int> test4 = {1, 3, 6, 5, 0, 2, 4, 7, 8};
        board = test4;
    }
    // depth 12
    if (t == 4)
    {
        vector<int> test5 = {1, 3, 6, 5, 0, 7, 4, 8, 2};
        board = test5;
    }
    // depth 16
    if (t == 5)
    {
        vector<int> test6 = {1, 6, 7, 5, 0, 3, 4, 8, 2};
        board = test6;
    }
    // depth 20
    if (t == 6)
    {
        vector<int> test7 = {7, 1, 2, 4, 8, 5, 6, 3, 0};
        board = test7;
    }
    // depth 24
    if (t == 7)
    {
        vector<int> test8 = {0, 7, 2, 4, 6, 1, 3, 5, 8};
        board = test8;
    }
    std::cout << "The initial puzzle is:\n";
    for (int iter = 0; iter < n / sqrt; iter++)
    {
        for (int i = 0; i < sqrt; i++)
        {
            std::cout << board.at(i + iter * sqrt) << ", ";
        }
        cout << "\n";
    }
    // we put the hashed initial node into the queue
    hashed = hash_function(board);
    queue.push_back(make_pair(hashed, 0));
    global_queue.push_back(hashed);

    while (queue.size() > 0)
    {

        // get the begin node and remove it from the queue
        temp_node = queue.at(0).first;

        if (temp_node == goal_state)
        {
            printf("\nsuccess!\nThe maximum queue size is %d\nThe size of expanded nodes is %d\n", queue_size, expanded_size);
            return 0;
        }
        printf("The best state to expand has a f(n) = g(n) + h(n) value of %d:\n", queue.at(0).second);
        board.clear();
        anti_hash_function(board, temp_node, n);
        for (int iter = 0; iter < n / sqrt; iter++)
        {
            for (int i = 0; i < sqrt; i++)
            {
                std::cout << board.at(i + iter * sqrt) << ", ";
            }
            cout << "\n";
        }
        expand(queue, global_queue, temp_node, n, expanded_size, queue.at(0).second);

        if (queue.size() > queue_size)
        {
            queue_size = queue.size();
        }
        if (m == 0)
        {
            Uniform_Cost_Search(queue);
        }
        if (m == 1)
        {
            A_star_with_the_Misplaced_Tile(queue, n);
        }
        if (m == 2)
        {
            A_star_with_the_Manhattan_distance(queue, n);
        }
    }
    if (queue.size() == 0)
    {
        cout << "The puzzle has no solution" << endl;
    }
}