#include "block.h"
using namespace std;

void Block::merge(Block& right) {
	right.number = 0;
	number *= 2;
}

void Block::move(Block& right) {
	right.number = number;
	number = 0;
}

