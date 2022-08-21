#pragma once
#ifndef UI_H
#define UI_H

#include "block.h"

class Ui {
public:
	Ui();	//generate starting page
	int modeChooser();
	bool startNew();
	void loadOld();
	bool showGuide();
	~Ui() {
		delete win;
	}
private:
	WINDOW* win;
	Block block[16];
	bool terminateGame = 0;

	void showInitPage();
	void printGamingPlace();

	void initBlock();
	void save();
	void randomGenerate();
	void printBlock(int);
	void printAllBlock() {
		for (int i = 0; i < 16; i++) {
			printBlock(i);
		}
	}
	bool moveBlock(int);
	bool play();
};
#endif // !UI_H
