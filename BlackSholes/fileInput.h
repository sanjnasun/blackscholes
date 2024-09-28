#pragma once
#ifndef FILE_INPUT
#define FILE_INPUT

#include "options.h"
#include <queue>

class fileReader : public Options {

	fileReader();

	//needs a function to read int eh values
	//look at the edge cases that it's a valid input
	//make a vector/queue of options to slap it in
	//if you want to use that value, it will have to iterate through the function 

	std::queue<Options> fileInput();







};

















#endif // !FILE_INPUT

