#include "vm.h"

void init_colors()
{
	start_color();
	init_color(COLOR_GREY, 500, 500, 500);
	init_pair(p0, COLOR_GREY, COLOR_BLACK);
	init_pair(p1, COLOR_RED, COLOR_BLACK);
        init_pair(p2, COLOR_GREEN, COLOR_BLACK);
        init_pair(p3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(p4, COLOR_BLUE, COLOR_BLACK);
	init_pair(p0b, COLOR_BLACK, COLOR_GREY);
        init_pair(p1b, COLOR_BLACK, COLOR_RED);
        init_pair(p2b, COLOR_BLACK, COLOR_GREEN);
        init_pair(p3b, COLOR_BLACK, COLOR_YELLOW);
        init_pair(p4b, COLOR_BLACK, COLOR_BLUE);
	init_pair(p0w, COLOR_WHITE, COLOR_GREY);
        init_pair(p1w, COLOR_WHITE, COLOR_RED);
        init_pair(p2w, COLOR_WHITE, COLOR_GREEN);
        init_pair(p3w, COLOR_WHITE, COLOR_YELLOW);
        init_pair(p4w, COLOR_WHITE, COLOR_BLUE);
}

void rebild(t_vm *vm)
{
	u_int8_t        *master;
        u_int8_t        *slave;
	int i;

	master = vm->arena;
        slave = vm->vis.arena;
        i = 0;
        while (i < MEM_SIZE)
        {
                slave[i] = master[i];
                i++;
        }
}

void init_drow(t_vm *vm)
{
	int row;
	int col;
	
	rebild(vm);
	getmaxyx(stdscr, row, col);
	vm->vis.row = row;
	vm->vis.col = col;
	vm->vis.ctd = 1;
	vm->vis.add = 25;
	vm->vis.line = 5;
	vm->vis.speed = 500;
	initscr();
	//noecho();
	curs_set(0);
	timeout(0);
	init_colors();
	//start_color();
}

void color_select(int is_curs, int playerno)
{
	if (is_curs == 0)
	{
		if (playerno == -1)
			attron(COLOR_PAIR(p0));
		if (playerno == 1)
                        attron(COLOR_PAIR(p1));
                if (playerno == 2)
                        attron(COLOR_PAIR(p2));
                if (playerno == 3)
                        attron(COLOR_PAIR(p3));
                if (playerno == 4)
                        attron(COLOR_PAIR(p4));
	}
	else if (is_curs == 1)
	{
		if (playerno == -1)
                        attron(COLOR_PAIR(p0b));
                if (playerno == 1)
                        attron(COLOR_PAIR(p1b));
                if (playerno == 2)
                        attron(COLOR_PAIR(p2b));
                if (playerno == 3)
                        attron(COLOR_PAIR(p3b));
                if (playerno == 4)
                        attron(COLOR_PAIR(p4b));
	}
}

void ft_start_color(t_vm *vm, int pose)
{
	t_cursor                        *cursor;
	int				is_curs;
	int				playerno;

	is_curs = 0;
	playerno = -1;
	if (vm->cursors != NULL)
	{
		cursor = vm->cursors;
		while (cursor != NULL && is_curs == 0)
		{
			if (cursor->carry == pose)
				is_curs = 1;
			if (is_curs == 0)
				cursor = cursor->next;
		}
	}
	if (is_curs == 1)
		playerno = cursor->player->id;
	color_select(is_curs, playerno);
}

void stop_color()
{
	attroff(COLOR_PAIR(p0));
        attroff(COLOR_PAIR(p1));
        attroff(COLOR_PAIR(p2));
        attroff(COLOR_PAIR(p3));
        attroff(COLOR_PAIR(p4));
        attroff(COLOR_PAIR(p0w));
        attroff(COLOR_PAIR(p1w));
        attroff(COLOR_PAIR(p2w));
        attroff(COLOR_PAIR(p3w));
        attroff(COLOR_PAIR(p4w));
        attroff(COLOR_PAIR(p0b));
        attroff(COLOR_PAIR(p1b));
        attroff(COLOR_PAIR(p2b));
        attroff(COLOR_PAIR(p3b));
        attroff(COLOR_PAIR(p4b));
}

void draw_frame(t_vm *vm)
{
	int i;
	int j;
	int     col;
	int     row;

	getmaxyx(stdscr, row, col);
	i = 0;
	while (i < row )
	{
		j = 0;
		while (j < col)
		{
			move(i, j);
			if (i == 0 && j == 0)
				waddch(stdscr, 108 | A_ALTCHARSET);
			else if (i == 0 && j == col - 1 - vm->vis.add)
				waddch(stdscr, 119 | A_ALTCHARSET);
			else if (i == 0 && j == col - 1)
                                waddch(stdscr, 107 | A_ALTCHARSET);
                        else if (i == row - 1 && j == 0)
                                waddch(stdscr, 109 | A_ALTCHARSET);
                        else if (i == row - 1 - vm->vis.line && j == col - 1 - vm->vis.add)
                                waddch(stdscr, 118 | A_ALTCHARSET);
                        else if (i == row - 1 && j == col - 1)
                                waddch(stdscr, 106 | A_ALTCHARSET);
			else if (i == row - 1 - vm->vis.line && j == 0)
				waddch(stdscr, 116 | A_ALTCHARSET);
			else if (i == row - 1 - vm->vis.line && j == col - 1)
                                waddch(stdscr, 117 | A_ALTCHARSET);
			else if (i == 0 || i == row - 1 || i == row - 1 - vm->vis.line)
				waddch(stdscr, 113 | A_ALTCHARSET);
			else if (j == 0 || j == col - 1)
                                waddch(stdscr, 120 | A_ALTCHARSET);
			else if (j == col - 1 - vm->vis.add && i < row - 1 - vm->vis.line)
                                waddch(stdscr, 120 | A_ALTCHARSET);
		j++;
		}
	i++;
	}
	mvwprintw(stdscr, row - vm->vis.line, 2, "\"q\" - exit visual mod");
	mvwprintw(stdscr, row - vm->vis.line + 1, 2, "\"+\" - more speed");
	mvwprintw(stdscr, row - vm->vis.line + 2, 2, "\"-\" - less speed");
	if (vm->vis.speed == 0)
		mvwprintw(stdscr, row - vm->vis.line + 3, 2, "unlimited speed");
	else
		mvwprintw(stdscr, row - vm->vis.line + 3, 2, "speed 1/%i fps", vm->vis.speed);
}

int find_ctd(t_vm *vm)
{
	int i;
	u_int8_t	*master;
	u_int8_t        *slave;

	master = vm->arena;
	slave = vm->vis.arena;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (master[i] != slave[i])
		//if (vm->vis.arena[i] != vm->arena[i])
			return (1);
		i++;
	}
	return (0);
}


void drow_arena(t_vm *vm)
{
	int i;
	int j;
	int k;
	u_int8_t        *master;
        u_int8_t        *slave;
	int		key;

        master = vm->arena;
        slave = vm->vis.arena;
	//int size[2]; //size[0] = row; size[1] = col;
	int	row, col;
	u_int8_t *arena;

	vm->vis.ctd = find_ctd(vm);
	if (vm->vis.ctd == 0)
		return ;
	key = getch();
	arena = vm->arena;
	getmaxyx(stdscr, row, col);
	if (vm->vis.col != col || vm->vis.row != row)
	{
		clear();
		vm->vis.col = col;
		vm->vis.row = row;
	}
	draw_frame(vm);
	k = 0;
        i = 2;
	col-=vm->vis.add;
	row-=vm->vis.line;
        while (i < row - 2 && k < MEM_SIZE)
        {
                if (col % 2 == 0)
                        j = 2;
                else
                        j = 3;
                while (j < col - 3 && k < MEM_SIZE)
                {
			if (master[k] != slave[k])
				attron(A_UNDERLINE);
			else
				ft_start_color(vm, k);
			mvwprintw(stdscr, i, j, "  ");
                        mvwprintw(stdscr, i, j, "%02X", arena[k]);
			refresh();
			attroff(A_UNDERLINE);
			stop_color();
                        k++;
                        j+=3;
                }
                i++;
        }
	i = row - 2;
	if (k < MEM_SIZE)
	{
		if (col % 2 == 0)
                        j = 2;
                else
                        j = 3;
		while (j < col - 3)
		{
			move(i, j);
			waddch(stdscr, 46 | A_ALTCHARSET);
			j++;
		}
	}
	mvwprintw(stdscr, 2, col + 2, "cycles_to_die = %i", vm->cycles_to_die);
	mvwprintw(stdscr, 3, col + 2, "cur_cycle = %i", vm->cur_cycle);
	if (key == 113)
		vm->vis_fl = 0;
	if (key == 61)
		vm->vis.speed = vm->vis.speed - 100;
	if (vm->vis.speed < 0)
		vm->vis.speed = 0;
	if (key == 45)
		vm->vis.speed = vm->vis.speed + 100;
	//mvwprintw(stdscr, row - 1, 2, "%i", key);
	refresh();
	//getch();
	napms(vm->vis.speed);
	vm->vis.ctd = 0;
	rebild(vm);
}

void stop_drow()
{
	curs_set(1);
        clear();
        refresh();
        resetty();
        endwin();
}
