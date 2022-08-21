#include "curses.h"
#include <iostream>
#include <fstream>
#include <string>
#include "exception.h"
#include "ui.h"
using namespace std;

Ui::Ui() {
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);    //hide cursor
	refresh();
	win = newwin(20, 60, 4, 30);
	showInitPage();
}

void Ui::showInitPage() {
	wclear(win);
	box(win, '|', '-');
	mvwaddstr(win, 3, 10, "¢p¢p¢p     ¢p¢p¢p     ¢p  ¢p     ¢p¢p¢p");
	mvwaddstr(win, 4, 10, "    ¢p     ¢p  ¢p     ¢p  ¢p     ¢p  ¢p");
	mvwaddstr(win, 5, 10, "¢p¢p¢p     ¢p  ¢p     ¢p¢p¢p     ¢p¢p¢p");
	mvwaddstr(win, 6, 10, "¢p         ¢p  ¢p         ¢p     ¢p  ¢p");
	mvwaddstr(win, 7, 10, "¢p¢p¢p     ¢p¢p¢p         ¢p     ¢p¢p¢p");

	mvwaddstr(win, 11, 24, "start new game");
	mvwaddstr(win, 13, 23, "load from memory");
	mvwaddstr(win, 15, 26, "show guide");

	touchwin(win);
	wrefresh(win);
}

int Ui::modeChooser() {
	int result = 0;
	bool terminate = 0;

	mvwaddstr(win, 11, 22, "¡´");
	touchwin(win);
	wrefresh(win);

	while (!terminate) {
		int c = getch();
		switch (c) {
		case KEY_UP:
		case KEY_LEFT:
			if (result > 0)
				result--;
			break;
		case KEY_DOWN:
		case KEY_RIGHT:
			if (result < 2)
				result++;
			break;
		case 10:
		case 32:
			terminate = 1;
			return result;
			break;
		case 27:
			terminate = 1;
			return 4;
		default:
			break;
		}

		switch (result) {
		case 0:
			mvwaddstr(win, 11, 22, "¡´");
			mvwaddstr(win, 13, 21, "  ");
			mvwaddstr(win, 15, 24, "  ");
			break;
		case 1:
			mvwaddstr(win, 11, 22, "  ");
			mvwaddstr(win, 13, 21, "¡´");
			mvwaddstr(win, 15, 24, "  ");
			break;
		case 2:
			mvwaddstr(win, 11, 22, "  ");
			mvwaddstr(win, 13, 21, "  ");
			mvwaddstr(win, 15, 24, "¡´");
			break;
		default:
			break;
		}
		touchwin(win);
		wrefresh(win);
	}
	return 0;
}

bool Ui::showGuide() {
	wclear(win);
	box(win, '|', '-');
	mvwaddstr(win, 3, 15, "¡ø             ¡ô            ¡ù");
	mvwaddstr(win, 4, 15, "Q/7           W/8           E/9");
	mvwaddstr(win, 9, 15, "¡ö  A/4                 D/6  ¡÷");
	mvwaddstr(win, 14, 15, "Z/1           X/2           C/3");
	mvwaddstr(win, 15, 15, "¡ú            ¡õ            ¡û");
	mvwaddstr(win, 17, 17, "press ctrl + s to save game");
	mvwaddstr(win, 18, 16, "press any key to back to manu");

	touchwin(win);
	wrefresh(win);
	getch();
	showInitPage();
	return 0;
}

void Ui::printGamingPlace() {
	wclear(win);
	touchwin(win);
	wrefresh(win); 

	win = newwin(29, 53, 1, 33);
	box(win, '|', '-');
	touchwin(win);
	wrefresh(win);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 27; j++) {
			mvwaddch(win, j+1, 13 * i +13, '|');
		}
	}
	for (int i = 0; i < 3; i++) {
		mvwaddstr(win, 7*i+7, 1, "---------------------------------------------------");
	}
	touchwin(win);
	wrefresh(win);

}

void Ui::initBlock() {
	for (int i = 0; i < 16; i++) {
		block[i].setNumber(0);
	}
}

void Ui::printBlock(int k) {
	if (block[k].getNumber() != 0) {
		mvwaddstr(win, k / 4 * 7 + 1, k % 4 * 13 + 1, "¢p¢p¢p¢p¢p¢p");
		mvwaddstr(win, k / 4 * 7 + 2, k % 4 * 13 + 1, "¢p        ¢p");
		mvwaddstr(win, k / 4 * 7 + 3, k % 4 * 13 + 1, "¢p        ¢p");
		mvwaddstr(win, k / 4 * 7 + 4, k % 4 * 13 + 1, "¢p        ¢p");
		mvwaddstr(win, k / 4 * 7 + 5, k % 4 * 13 + 1, "¢p        ¢p");
		mvwaddstr(win, k / 4 * 7 + 6, k % 4 * 13 + 1, "¢p¢p¢p¢p¢p¢p");

		string temp = to_string(block[k].getNumber());
		mvwaddstr(win, k / 4 * 7 + 3, k % 4 * 13 + 5, temp.c_str());
	}
	else {
		mvwaddstr(win, k / 4 * 7 + 1, k % 4 * 13 + 1, "            ");
		mvwaddstr(win, k / 4 * 7 + 2, k % 4 * 13 + 1, "            ");
		mvwaddstr(win, k / 4 * 7 + 3, k % 4 * 13 + 1, "            ");
		mvwaddstr(win, k / 4 * 7 + 4, k % 4 * 13 + 1, "            ");
		mvwaddstr(win, k / 4 * 7 + 5, k % 4 * 13 + 1, "            ");
		mvwaddstr(win, k / 4 * 7 + 6, k % 4 * 13 + 1, "            ");
	}

	touchwin(win);
	wrefresh(win);
}

void Ui::randomGenerate() {
	int k;
	while (1) {
		k = rand() % 16;
		if (!block[k].getNumber()) {
			break;
		}
	}
	//Block::occupy[k] = 1;
	block[k].setNumber((rand() % 2 + 1) * 2);
	//block[k].setExist(1);
	printBlock(k);

}

bool Ui::moveBlock(int k) {
	int ctr = 0;
	switch (k) {
	case 1:
		for (int i = 0; i < 3; i++) {
			for (int j = 1; j < 4; j++) {
				if (block[j * 5].getNumber() == block[(j - 1) * 5].getNumber() && block[j * 5].getNumber() != 0) {
					block[(j - 1) * 5].merge(block[j * 5]);
					ctr++;
				}
				else if (block[(j - 1) * 5].getNumber() == 0&&block[j*5].getNumber()!=0) {
					block[j * 5].move(block[(j - 1) * 5]);
					ctr++;
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j < 3; j++) {
				if (block[j * 5 + 4].getNumber() == block[(j - 1) * 5 + 4].getNumber() && block[j * 5 + 4].getNumber() != 0) {
					block[(j - 1) * 5 + 4].merge(block[j * 5 + 4]);
					ctr++;
				}
				else if (block[(j - 1) * 5 + 4].getNumber() == 0&&block[j*5+4].getNumber()!=0) {
					block[(j * 5) + 4].move(block[(j - 1) * 5 + 4]);
					ctr++;
				}

				if (block[j * 5 + 1].getNumber() == block[(j - 1) * 5 + 1].getNumber() && block[j * 5 + 1].getNumber() != 0) {
					block[(j - 1) * 5 + 1].merge(block[j * 5 + 1]);
					ctr++;
				}
				else if (block[(j - 1) * 5 + 1].getNumber() == 0&&block[j*5+1].getNumber()!=0) {
					block[(j * 5) + 1].move(block[(j - 1) * 5 + 1]);
					ctr++;
				}
			}
		}
		if (block[2].getNumber() == block[7].getNumber()&&block[2].getNumber()!=0) {
			block[2].merge(block[7]);
			ctr++;
		}
		else if (block[2].getNumber() == 0&&block[7].getNumber()!=0) {
			block[7].move(block[2]);
			ctr++;
		}
		if (block[8].getNumber() == block[13].getNumber() && block[8].getNumber() != 0) {
			block[8].merge(block[13]);
			ctr++;
		}
		else if (block[8].getNumber() == 0&&block[13].getNumber()!=0) {
			block[13].move(block[8]);
			ctr++;
		}
		break;

	case 2:
		for (int i = 0; i < 12; i++) {
			if (block[i].getNumber() == block[i + 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i + 4]);
				ctr++;
			}
			else if (block[i].getNumber() == 0 && block[i + 4].getNumber() != 0) {
				block[i + 4].move(block[i]);
				ctr++;
			}
		}
		for (int i = 0; i < 8; i++) {
			if (block[i].getNumber() == block[i + 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i + 4]);
				ctr++;
			}
			else if (block[i].getNumber() == 0 && block[i + 4].getNumber() != 0) {
				block[i + 4].move(block[i]);
				ctr++;
			}
		}
		for (int i = 0; i < 4; i++) {
			if (block[i].getNumber() == block[i + 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i + 4]);
				ctr++;
			}
			else if (block[i].getNumber() == 0 && block[i + 4].getNumber() != 0) {
				block[i + 4].move(block[i]);
				ctr++;
			}
		}
		break;
		
	case 3:
		for (int i = 0; i < 3; i++) {
			for (int j = 2; j < 5; j++) {
				if (block[j * 3].getNumber() == block[(j - 1) * 3].getNumber() && block[j * 3].getNumber() != 0) {
					block[(j - 1) * 3].merge(block[j * 3]);
					ctr++;
				}
				else if (block[(j - 1) * 3].getNumber() == 0 && block[j * 3].getNumber() != 0) {
					block[j * 3].move(block[(j - 1) * 3]);
					ctr++;
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 1; j < 3; j++) {
				if (block[j * 3 + 2].getNumber() == block[(j - 1) * 3 + 2].getNumber() && block[j * 3 + 2].getNumber() != 0) {
					block[(j - 1) * 3 + 2].merge(block[j * 3 + 2]);
					ctr++;
				}
				else if (block[(j - 1) * 3 + 2].getNumber() == 0 && block[j * 3 + 2].getNumber() != 0) {
					block[(j * 3) + 2].move(block[(j - 1) * 3 + 2]);
					ctr++;
				}

				if (block[j * 3 + 7].getNumber() == block[(j - 1) * 3 + 7].getNumber() && block[j * 3 + 7].getNumber() != 0) {
					block[(j - 1) * 3 + 7].merge(block[j * 3 + 7]);
					ctr++;
				}
				else if (block[(j - 1) * 3 + 7].getNumber() == 0 && block[j * 3 + 7].getNumber() != 0) {
					block[(j * 3) + 7].move(block[(j - 1) * 3 + 7]);
					ctr++;
				}
			}
		}
		if (block[1].getNumber() == block[4].getNumber() && block[1].getNumber() != 0) {
			block[1].merge(block[4]);
			ctr++;
		}
		else if (block[1].getNumber() == 0 && block[4].getNumber() != 0) {
			block[4].move(block[1]);
			ctr++;
		}
		if (block[11].getNumber() == block[14].getNumber() && block[11].getNumber() != 0) {
			block[11].merge(block[14]);
			ctr++;
		}
		else if (block[11].getNumber() == 0 && block[14].getNumber() != 0) {
			block[14].move(block[11]);
			ctr++;
		}
		break;
		
	case 4:
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[j * 4 + i].getNumber() == block[j * 4+i+1].getNumber() && block[j * 4+i].getNumber() != 0) {
					block[j * 4 + i].merge(block[j * 4 + i + 1]);
					ctr++;
				}
				else if (block[j * 4 + i].getNumber() == 0 && block[j * 4 + i + 1].getNumber() != 0) {
					block[j * 4 + i + 1].move(block[j * 4 + i]);
					ctr++;
				}
			}
		}
		for (int i = 1; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[j * 4 + i].getNumber() == block[j * 4 + i + 1].getNumber() && block[j * 4 + i].getNumber() != 0) {
					block[j * 4 + i].merge(block[j * 4 + i + 1]);
					ctr++;
				}
				else if (block[j * 4 + i].getNumber() == 0 && block[j * 4 + i + 1].getNumber() != 0) {
					block[j * 4 + i + 1].move(block[j * 4 + i]);
					ctr++;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			if (block[j * 4].getNumber() == block[j * 4  + 1].getNumber() && block[j * 4 ].getNumber() != 0) {
				block[j * 4 ].merge(block[j * 4  + 1]);
				ctr++;
			}
			else if (block[j * 4 ].getNumber() == 0 && block[j * 4  + 1].getNumber() != 0) {
				block[j * 4  + 1].move(block[j * 4 ]);
				ctr++;
			}
		}
		break;

	case 5:
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[j * 4 +3- i].getNumber() == block[j * 4 + 2 - i].getNumber() && block[j * 4 + 3 - i].getNumber() != 0) {
					block[j * 4 + 3 - i].merge(block[j * 4 + 2 - i]);
					ctr++;
				}
				else if (block[j * 4 + 3 - i].getNumber() == 0 && block[j * 4 + 2 - i].getNumber() != 0) {
					block[j * 4 + 2 - i].move(block[j * 4 + 3 - i]);
					ctr++;
				}
			}
		}
		for (int i = 1; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[j * 4 + 3 - i].getNumber() == block[j * 4 + 2 - i].getNumber() && block[j * 4 + 3 - i].getNumber() != 0) {
					block[j * 4 + 3 - i].merge(block[j * 4 + 2 - i]);
					ctr++;
				}
				else if (block[j * 4 + 3 - i].getNumber() == 0 && block[j * 4 + 2 - i].getNumber() != 0) {
					block[j * 4 + 2 - i].move(block[j * 4 + 3 - i]);
					ctr++;
				}
			}
		}
		for (int j = 0; j < 4; j++) {
			if (block[j * 4 + 3 ].getNumber() == block[j * 4 + 2 ].getNumber() && block[j * 4 + 3 ].getNumber() != 0) {
				block[j * 4 + 3 ].merge(block[j * 4 + 2 ]);
				ctr++;
			}
			else if (block[j * 4 + 3 ].getNumber() == 0 && block[j * 4 + 2 ].getNumber() != 0) {
				block[j * 4 + 2 ].move(block[j * 4 + 3 ]);
				ctr++;
			}
		}
		break;
	case 6:
		for (int i = 1; i < 3; i++) {
			for (int j = 4; j > 1; j--) {
				if (block[j * 3].getNumber() == block[(j - 1) * 3].getNumber() && block[j * 3].getNumber() != 0) {
					block[j * 3].merge(block[(j-1) * 3]);
					ctr++;
				}
				else if (block[j * 3].getNumber() == 0 && block[(j - 1) * 3].getNumber() != 0) {
					block[(j - 1) * 3].move(block[j*3]);
					ctr++;
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 3; j > 1; j--) {
				if (block[j*3-1].getNumber() == block[(j - 1) * 3-1].getNumber() && block[j * 3 - 1].getNumber() != 0) {
					block[j * 3 - 1].merge(block[(j - 1) * 3 - 1]);
					ctr++;
				}
				else if (block[j * 3 - 1].getNumber() == 0 && block[(j - 1) * 3 - 1].getNumber() != 0) {
					block[(j - 1) * 3 - 1].move(block[j * 3 - 1]);
					ctr++;
				}

				if (block[j * 3 + 4].getNumber() == block[(j - 1) * 3 + 4].getNumber() && block[j * 3 + 4].getNumber() != 0) {
					block[j * 3 + 4].merge(block[(j - 1) * 3 + 4]);
					ctr++;
				}
				else if (block[j * 3 + 4].getNumber() == 0 && block[(j - 1) * 3 + 4].getNumber() != 0) {
					block[(j - 1) * 3 + 4].move(block[j * 3 + 4]);
					ctr++;
				}
			}
		}
		if (block[4].getNumber() == block[1].getNumber() && block[4].getNumber() != 0) {
			block[4].merge(block[1]);
			ctr++;
		}
		else if (block[4].getNumber() == 0 && block[1].getNumber() != 0) {
			block[1].move(block[4]);
			ctr++;
		}
		if (block[14].getNumber() == block[11].getNumber() && block[14].getNumber() != 0) {
			block[14].merge(block[11]);
			ctr++;
		}
		else if (block[14].getNumber() == 0 && block[11].getNumber() != 0) {
			block[11].move(block[14]);
			ctr++;
		}
		break;

	case 7:
		for (int i = 15; i >= 4; i--) {
			if (block[i].getNumber() == block[i - 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i - 4]);
				ctr--;
			}
			else if (block[i].getNumber() == 0 && block[i - 4].getNumber() != 0) {
				block[i - 4].move(block[i]);
				ctr--;
			}
		}
		for (int i = 15; i >= 8; i--) {
			if (block[i].getNumber() == block[i - 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i - 4]);
				ctr--;
			}
			else if (block[i].getNumber() == 0 && block[i - 4].getNumber() != 0) {
				block[i - 4].move(block[i]);
				ctr--;
			}
		}
		for (int i = 15; i >= 12; i--) {
			if (block[i].getNumber() == block[i - 4].getNumber() && block[i].getNumber() != 0) {
				block[i].merge(block[i - 4]);
				ctr--;
			}
			else if (block[i].getNumber() == 0 && block[i - 4].getNumber() != 0) {
				block[i - 4].move(block[i]);
				ctr--;
			}
		}
		break;

	case 8:
		for (int i = 1; i < 3; i++) {
			for (int j = 3; j > 0; j--) {
				if (block[j * 5].getNumber() == block[(j - 1) * 5].getNumber() && block[j * 5].getNumber() != 0) {
					block[j * 5].merge(block[(j - 1) * 5]);
					ctr++;
				}
				else if (block[j * 5].getNumber() == 0 && block[(j - 1) * 5].getNumber() != 0) {
					block[(j - 1) * 5].move(block[j * 5]);
					ctr++;
				}
			}
		}
		for (int i = 0; i < 2; i++) {
			for (int j = 2; j >= 1; j--) {
				if (block[j * 5 + 1].getNumber() == block[(j - 1) * 5 + 1].getNumber() && block[j * 5 + 1].getNumber() != 0) {
					block[j * 5 + 1].merge(block[(j - 1) * 5 + 1]);
					ctr++;
				}
				else if (block[j * 5 + 1].getNumber() == 0 && block[(j - 1) * 5 + 1].getNumber() != 0) {
					block[(j - 1) * 5 + 1].move(block[j * 5 + 1]);
					ctr++;
				}

				if (block[j * 5 + 4].getNumber() == block[(j - 1) * 5 + 4].getNumber() && block[j * 5 + 4].getNumber() != 0) {
					block[j * 5 + 4].merge(block[(j - 1) * 5 + 4]);
					ctr++;
				}
				else if (block[j * 5 + 4].getNumber() == 0 && block[(j - 1) * 5 + 4].getNumber() != 0) {
					block[(j - 1) * 5 + 4].move(block[j * 5 + 4]);
					ctr++;
				}
			}
		}
		if (block[7].getNumber() == block[2].getNumber() && block[7].getNumber() != 0) {
			block[7].merge(block[2]);
			ctr++;
		}
		else if (block[7].getNumber() == 0 && block[2].getNumber() != 0) {
			block[2].move(block[7]);
			ctr++;
		}
		if (block[4].getNumber() == block[9].getNumber() && block[4].getNumber() != 0) {
			block[4].merge(block[9]);
			ctr++;
		}
		else if (block[4].getNumber() == 0 && block[9].getNumber() != 0) {
			block[9].move(block[4]);
			ctr++;
		}
		break;
	}
	
	if (ctr != 0) {
		randomGenerate();
		printAllBlock();
		return 0;
	}
	else
		return 1;
}

void Ui::save() {
	fstream file("log.txt", ios::out);
	for (int i = 0; i < 16; i++){
		file << block[i].getNumber() << ' ';
	}
	file.close();
	cout << "progress saved !\n";
}

bool Ui::play() {
	static int k;
	int c = getch();
	switch (c) {
	case 'q':
	case 55:
		k = (!moveBlock(1)?0:k+1);
		break;
	case 'w':
	case 56:
		k = (!moveBlock(2) ? 0 : k + 1);
		break;
	case 'e':
	case 57:
		k = (!moveBlock(3) ? 0 : k + 1);
		break;
	case 'a':
	case 52:
		k = (!moveBlock(4) ? 0 : k + 1);
		break;
	case 'd':
	case 54:
		k = (!moveBlock(5) ? 0 : k + 1);
		break;
	case 'z':
	case 49:
		k = (!moveBlock(6) ? 0 : k + 1);
		break;
	case 'x':
	case 50:
		k = (!moveBlock(7) ? 0 : k + 1);
		break;
	case 'c':
	case 51:
		k = (!moveBlock(8) ? 0 : k + 1);
		break;
	case 19:
		save();
		return 1;
	case 27:
		return 1;
	}
	if (k < 8)
		return 0;
	else
		cout << "GAME OVER !!";
		return 1;
}

bool Ui::startNew() {
	bool terminate = 0;

	initBlock();
	printGamingPlace();
	randomGenerate();
	
	while (!terminate) {
		terminate = play();
	}
	
	return 0;
}

void Ui::loadOld() {
	bool terminate = 0;

	try {
		fstream file("log.txt", ios::in);
		if (!file)
			throw loadEmpty();

		for (int i = 0; i < 16; i++) {
			int k;
			file >> k;
			if (((k & (k - 1))==0) || k == 0) 
				block[i].setNumber(k);
			else {
				throw invalidFile();				
			}
		}
		printGamingPlace();
		printAllBlock();
	}
	catch(loadEmpty& e){
		cerr << e.what();
		startNew();
	}
	catch (invalidFile& e) {
		cerr << e.what();
		startNew();
	}

	while (!terminate) {
		terminate = play();
	}
}