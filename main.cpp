#include <iostream>
#include <array>
using namespace			std;

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


int						main(void)
{
	Grid grid = {
		E,E,E,E,E,E,E,
		E,E,E,E,E,E,E,
		E,E,E,E,E,E,E,
		E,E,E,E,E,E,E,
		E,E,E,E,E,E,E,
		E,E,E,E,E,E,E
	};
	short int col(-1);
	color turn(R);
	color winner(E);

	cout << MARGIN << "--------- Puissance 4 Game ---------\n\n";
	while (winner == E && !is_grid_filled(grid)){
		display_grid(grid);
		play(grid, turn, col);
		winner = check_winner(grid);
	}
	display_grid(grid);
	display_winner(winner);
	return 0;
}



void					display_grid(Grid const& grid){
	cout << "\n";
	for(short int i(0); i < ROW_NUMBER; ++i)
	{
		cout << MARGIN ;
		for(short int j(0); j < COL_NUMBER; ++j)
			if (j > 0)
				cout << SPACES << colors[grid[i][j]] << SPACES;
			else
				cout << colors[grid[i][j]] << SPACES;
		cout << "\n";
	}
	cout << "\n";
	cout << MARGIN ;
	for(short int i(0); i < COL_NUMBER; ++i)
		if (i > 0)
			cout << SPACES <<(i + 1) << SPACES;
		else
			cout <<(i + 1) << SPACES;
	cout << "\n";
}


void					get_player_move(color &turn, short int &col)
{

	cout << "\n" << MARGIN << colors[turn] << "'s turn: Enter column: "; 
	cin >> col;
	--col;
}


short int				get_row(Grid const& grid, short int j){
	short int row(ROW_NUMBER - 1);

	if (j < 0 || j >= COL_NUMBER) return -1;
	while (grid[row][j] != E && row >= 0) --row;
	return row;
}


void					play(Grid &grid, color& turn, short int& col){
	short int row(get_row(grid, col));
	while (row < 0){
		get_player_move(turn, col);
		row = get_row(grid, col);
	}
	grid[row][col] = turn;
	if (turn == R)
		turn = W;
	else
		turn = R;
	col = -1;
}


bool					is_grid_filled(Grid const& grid){
	for (short int i(0); i < ROW_NUMBER; ++i)
		for (short int j(0); j < COL_NUMBER; ++j)
			if (grid[i][j] == E)
				return false;
	return true;
}


color					check_winner_v(Grid const& grid)
{
	short int player_R_score(0);
	short int player_W_score(0);

	for (short int j(0); j < COL_NUMBER; ++j)
	{
		short int i(0);
		while (i < ROW_NUMBER)
		{
			if (grid[i][j] == E){
				++i;
				continue;
			}
			if (i == 0)
			{
				if (grid[i][j] == R)
					++player_R_score;
				else
					++player_W_score;
			}
			else if (grid[i - 1][j] == W && grid[i][j] == W)
				++player_W_score;
			else if (grid[i - 1][j] == R && grid[i][j] == R)
				++player_R_score;
			else if (grid[i][j] == R){
				player_R_score = 1;
				player_W_score = 0;
			}
			else{
				player_R_score = 0;
				player_W_score = 1;	
			}
			if (player_W_score == 4)
				return W;
			if (player_R_score == 4)
				return R;
			++i;
		}
	}
	return E;
}


color					check_winner_h(Grid const& grid){
	short int player_R_score(0);
	short int player_W_score(0);

	for (short int i(0); i < ROW_NUMBER; ++i)
	{
		short int j(0);
		while (j < COL_NUMBER)
		{
			if (grid[i][j] == E){
				++j;
				player_R_score = 0;
				player_W_score = 0;
				continue;
			}
			if (j == 0)
			{
				if (grid[i][j] == R)
					++player_R_score;
				else
					++player_W_score;
			}
			else if (grid[i][j - 1] == W && grid[i][j] == W)
				++player_W_score;
			else if (grid[i][j - 1] == R && grid[i][j] == R)
				++player_R_score;
			else if (grid[i][j] == R){
				player_R_score = 1;
				player_W_score = 0;
			}
			else{
				player_R_score = 0;
				player_W_score = 1;	
			}
			if (player_W_score == 4)
				return W;
			if (player_R_score == 4)
				return R;
			++j;
		}
	}
	return E;
}


color					check_winner_dl(Grid const& grid){
	short int i(0);
	short int j(0);
	short int row(i);
	short int player_R_score(0);
	short int player_W_score(0);

	while ( i <= COL_NUMBER + ROW_NUMBER - 6 - 1)
	{
		row = i < 3 ? i : 0; 
		j = i < 3 ? 0 : (i % 3) + 1; 
		
		while (row < ROW_NUMBER && j < COL_NUMBER)
		{
			if (grid[row][j] == E){
				++j;
				++row;
				player_R_score = 0;
				player_W_score = 0;
				continue;
			}
			if (j == 0 || row ==  0){
				if (grid[row][j] == W)
					++player_W_score;
				else if (grid[row][j] == R)
					++player_R_score;
			}
			else if (grid[row - 1][j - 1] == W && grid[row][j] == W)
				++player_W_score;
			else if (grid[row - 1][j - 1] == R && grid[row][j] == R)
				++player_R_score;
			else if (grid[row][j] == R){
				player_R_score = 1;
				player_W_score = 0;
			}
			else{
				player_R_score = 0;
				player_W_score = 1;	
			}
			if (player_W_score == 4)
				return W;
			if (player_R_score == 4)
				return R;
			++j;
			++row;
		}
		++i;		
	}
	return E;
}


color					check_winner_dr(Grid const& grid){
	short int i(3);
	short int j(0);
	short int row(i);
	short int player_R_score(0);
	short int player_W_score(0);

	while ( i <= COL_NUMBER + ROW_NUMBER - 3 - 1)
	{
		row = i < ROW_NUMBER  ? i : ROW_NUMBER - 1; 
		j = i < ROW_NUMBER ? 0 : i % ROW_NUMBER - 1; 
		
		while (row >= 0 && j < COL_NUMBER)
		{
			if (grid[row][j] == E){
				++j;
				--row;
				player_R_score = 0;
				player_W_score = 0;
				continue;
			}
			if (j == 0 || (row == ROW_NUMBER - 1 && j > 0)){
				if (grid[row][j] == W)
					++player_W_score;
				else if (grid[row][j] == R)
					++player_R_score;
			}
			else if (grid[row + 1][j - 1] == W && grid[row][j] == W)
				++player_W_score;
			else if (grid[row + 1][j - 1] == R && grid[row][j] == R)
				++player_R_score;
			else if (grid[row][j] == R){
				player_R_score = 1;
				player_W_score = 0;
			}
			else{
				player_R_score = 0;
				player_W_score = 1;	
			}
			if (player_W_score == 4)
				return W;
			if (player_R_score == 4)
				return R;
			++j;
			--row;
		}
		++i;		
	}
	return E;
}


color					check_winner(Grid const& grid)
{
	color winner(E);

	winner  = check_winner_h(grid);
	if (winner == E)
		winner = check_winner_v(grid);
	if (winner == E)
		winner = check_winner_dr(grid);
	if (winner == E)
		winner = check_winner_dl(grid);
	return winner;
}


void					display_winner(color winner)
{
	if (winner != E)
		cout << "\n\n" << MARGIN << "***** Winner is: Player " << colors[winner] << " *****" << "\n\n";
	else
		cout << "\n\n" << MARGIN << "No winner for this party!" << "\n\n";
}