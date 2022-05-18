#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <array>

#define					ROW_NUMBER 6
#define					COL_NUMBER 7
#define					MARGIN "\t\t\t\t\t\t\t\t\t"		
enum					color { E, R, W };
typedef					array <array <color, COL_NUMBER>, ROW_NUMBER> Grid;

const string			SPACES (" ");
const string			colors (".RW");


void					display_grid(Grid const& grid);
void					get_player_move(color &turn, short int &col);
short int				get_row(Grid const& grid, short int j);
void					play(Grid &grid, color& turn, short int& col);
bool					is_grid_filled(Grid const& grid);
color					check_winner_v(Grid const& grid);
color					check_winner_h(Grid const& grid);
color					check_winner_dl(Grid const& grid);
color					check_winner_dr(Grid const& grid);
color					check_winner(Grid const& grid);
void					display_winner(color winner);

#endif