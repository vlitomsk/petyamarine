#ifndef TAPE_CPP_INCLUDED
#define TAPE_CPP_INCLUDED

#include "Tape.h"

template <typename T, typename TC>
Tape<T, TC>::Tape(TC from, TC to, TC defstart, TC definc) {
	this->from = from;
	this->to = to;
	this->defstart = defstart;
	this->definc = definc;
}

template <typename T, typename TC>
Tape<T, TC>::~Tape() { /* stub */ }

template <typename T, typename TC> 
std::vector<T> Tape<T, TC>::move() {
	return move(definc);
}

template <typename T, typename TC>
std::vector<T> Tape<T, TC>::move(TC k) {
	std::vector<T> popped;

	for (int i = 0; i < tape.size(); ++i) {
		tape[i].c -= k;
		if (tape[i].c < from) {
			popped.push_back(tape[i].val);
			tape.erase(tape.begin() + i);
			--i;			
			continue;
		}
	}

	return popped;
}

template <typename T, typename TC>
void Tape<T, TC>::push(T val) {
	push(val, defstart);
}

template <typename T, typename TC>
void Tape<T, TC>::push(T val, TC start) {
	tape.push_back(mk_tape_entry(start, val));
}

#endif

