
#include <SDL.h>
#include <stdio.h>
#include <array>
#include <iostream>
//#include <minimax.h>

using namespace std;

//Connect Four Array
#define COLUMN 6
#define ROW 7

//Screen dimension constants
const int SCREEN_WIDTH = 364;
const int SCREEN_HEIGHT = 312;

enum Color {red, black, nothing};

typedef array<array<Color, ROW>, COLUMN> Grid;


void initialize(Grid& grid) {
    for (auto &line : grid){
        for(auto &kase : line){ //use kase since case is a reserved keyword
            kase = nothing;
        }
    }
}

void _print(const Grid& grid)
{
    for(auto line : grid) {
        cout << "|";
        for(auto kase : line) {
            if(kase == nothing){
                cout << ' ';
            } else if (kase == red){
                cout << 'O';
            } else {
                cout << 'X';
            }
            cout << "|";
        }
        cout << endl;
    }
    cout << endl << endl;
}

bool play(Grid& grid,size_t column, Color color)
{
    if(column >= grid[0].size()) {
        return false;
    }
    size_t line(grid.size() - 1);
    bool full(false);
    while ((not full) and (grid[line][column] != nothing)){
            if(line == 0)
            {
                full = true;
            } else
            {
                --line;
            }
    }
    if(not full){
        grid[line][column] = color;
        return true;
    } else {
        return false;
    }
}

void get_the_play(Grid& grid, Color color_player)
{
        bool valid;
        if (color_player == black){
            cout << "Player X: enter number of column!" << endl;
        } else {
            cout << "Player O: enter number of column!" << endl;
        }

        do {
            size_t column;
            cin >> column;
            --column;
            valid = play(grid, column, color_player);

            if(not valid)
            {
                cout << "Move was not valid!" << endl;
            }
        } while (not valid);
}

unsigned int Connect(const Grid& grid, size_t line_start, size_t column_start, int dir_line, int dir_column)
{
    unsigned int counter(0);

    size_t line(line_start);
    size_t column(column_start);

    while( grid[line][column] == grid[line_start][column_start])
    {
        ++counter;
        line = line+dir_line;
        column = column+dir_column;
    }
    return counter;

}

bool is_it_won(const Grid& grid, Color color_player)
{
    for (size_t line(0); line < grid.size(); ++line){
        for(size_t column(0); column < grid[line].size(); ++column){
            Color color_case(grid[line][column]);
            if(color_case == color_player) {

                const size_t line_max(grid.size() - 4);
                const size_t column_max(grid[line].size() - 4);
                if (
                    (line >= 3 and column <= column_max and
                    Connect(grid, line, column, -1, +1) >= 4) or

                    (column <= column_max and
                    Connect(grid, line, column, 0, +1) >= 4) or

                    (line <= line_max and column <= column_max and
                    Connect(grid, line, column, +1, +1) >= 4) or

                    (line <= line_max and
                    Connect(grid, line, column, +1, 0) >= 4)) {

                    return true;
                }
            }
        }
    }
    return false;
}

bool full(const Grid& grid)
{
    for (auto kase: grid[0]) {
    if (kase == nothing) {
            return false;
        }
    }

    return true;
}

int main( int argc, char* args[] )
{
    Grid grid;

    initialize(grid);
    _print(grid);
    Color color_player(black);
    bool won;
    do {
        get_the_play(grid, color_player);
        won = is_it_won(grid, color_player);
        _print(grid);
        if (color_player == black) {
            color_player = red;
        }
        else {
            color_player = black;
        }
        /*
        if(color_player == red )
        {
            minimax(grid, color_player)
        }
        */

    } while (not won and not full(grid));
    return 0;
}
