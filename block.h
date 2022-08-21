#pragma once


#ifndef BLOCK_H
#define BLOCK_H

class Block {
public:
	Block() : number(0) {};

	void merge(Block&);
	void move(Block&);
	void setNumber(int k) { number = k; }
	int getNumber() { return number; }

private:
	int number{};
};

#endif // !BLOCK_H

