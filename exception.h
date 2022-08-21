#pragma once
#include <stdexcept>
using namespace std;

class loadEmpty :public runtime_error {
public:
	loadEmpty() :runtime_error("no log file exist, start new game") {};
};

class invalidFile :public runtime_error {
public:
	invalidFile() :runtime_error("file damaged, start new game") {};
};