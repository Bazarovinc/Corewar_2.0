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

void init_drow()
{
	initscr();
	//noecho();
	//curs_set(0);
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

void draw_frame()
{
	int i;
	int j;
	int     col;
	int     row;

	getmaxyx(stdscr, row, col);
	i = 0;
	while (i < row)
	{
		j = 0;
		while (j < col)
		{
			move(i, j);
			if (i == 0 && j == 0)
				waddch(stdscr, 108 | A_ALTCHARSET);
			else if (i == 0 && j == col - 25)
				waddch(stdscr, 119 | A_ALTCHARSET);
			else if (i == 0 && j == col - 1)
                                waddch(stdscr, 107 | A_ALTCHARSET);
                        else if (i == row - 1 && j == 0)
                                waddch(stdscr, 109 | A_ALTCHARSET);
                        else if (i == row - 1 && j == col - 25)
                                waddch(stdscr, 118 | A_ALTCHARSET);
                        else if (i == row - 1 && j == col - 1)
                                waddch(stdscr, 106 | A_ALTCHARSET);
			else if (i == 0 || i == row - 1)
				waddch(stdscr, 113 | A_ALTCHARSET);
			else if (j == 0 || j == col - 1 || j == col - 25)
                                waddch(stdscr, 120 | A_ALTCHARSET);
		j++;
		}
	i++;
	}
}

void drow_arena(t_vm *vm)
{
	int i;
	int j;
	int k;
	//int size[2]; //size[0] = row; size[1] = col;
	int	row, col;
	u_int8_t *arena;

	arena = vm->arena;
	getmaxyx(stdscr, row, col);
        clear();
	draw_frame();
	k = 0;
        i = 2;
	col-=25;
        while (i < row - 2 && k < MEM_SIZE)
        {
                if (col % 2 == 0)
                        j = 2;
                else
                        j = 3;
                while (j < col - 3 && k < MEM_SIZE)
                {
			ft_start_color(vm, k);
                        mvwprintw(stdscr, i, j, "%02X", arena[k]);
			stop_color();
                        k++;
                        j+=3;
                }
                i++;
        }
	mvwprintw(stdscr, 2, col + 2, "cycles_to_die = %i", vm->cycles_to_die);
	mvwprintw(stdscr, 3, col + 2, "cur_cycle = %i", vm->cur_cycle);
	refresh();
	napms(500);
}

void stop_drow()
{
	curs_set(1);
        clear();
        refresh();
        resetty();
        endwin();
}
