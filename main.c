#include "langdonsant.h"

int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	initscr();

	WINDOW* step_win = newwin(1, 19, 0, 2);
	WINDOW* draw_win = newwin(getmaxy(stdscr) - 2, getmaxx(stdscr) - 2, 1, 1);

	int step = 1;
	int step_end = 11500;
	int pause = 1000;

	if (argc > 1) {
		step_end = atoi(argv[1]);
	}

	if (argc > 2) {
		pause = atoi(argv[2]);
	}

	int width = getmaxx(draw_win);
	int height = getmaxy(draw_win);

	int v_spd = 1;
	int h_spd = 2;

	int pos_x = width / 2;
	int pos_y = height / 2;

	char direction = 'n';

	wchar_t black_field[] = L"██";
	wchar_t white_field[] = L"  ";

	box(stdscr, 0, 0);
	refresh();

	while (step <= step_end) {
		if (pos_y <= 0) pos_y += height;
		if (pos_y >= height) pos_y -= height;
		if (pos_x <= 0) pos_x += width;
		if (pos_x >= width) pos_x -= width;

		if (mvwinch(draw_win, pos_y, pos_x) == 32) {
			mvwprintw(draw_win, pos_y, pos_x, "%ls", black_field);

			switch (direction) {
				case 'n':
					direction = 'e';
					pos_x += h_spd;
					break;
				case 'e':
					direction = 's';
					pos_y += v_spd;
					break;
				case 's':
					direction = 'w';
					pos_x -= h_spd;
					break;
				case 'w':
					direction = 'n';
					pos_y -= v_spd;
					break;
			}
		} else {
			mvwprintw(draw_win, pos_y, pos_x, "%ls", white_field);

			switch (direction) {
				case 'n':
					direction = 'w';
					pos_x -= h_spd;
					break;
				case 'w':
					direction = 's';
					pos_y += v_spd;
					break;
				case 's':
					direction = 'e';
					pos_x += h_spd;
					break;
				case 'e':
					direction = 'n';
					pos_y -= v_spd;
					break;
			}
		}

		mvwprintw(step_win, 0, 0, " [ step : %6d ] ", step);

		wrefresh(step_win);
		wrefresh(draw_win);
		usleep(pause);
		++step;
	}

	wgetch(draw_win);

	delwin(step_win);
	delwin(draw_win);
	endwin();

	return 0;
}
