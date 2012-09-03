#ifndef TAPE_H_INCLUDED
#define TAPE_H_INCLUDED

#include <deque>
#include <vector>

template <typename T, typename TC>
class Tape {
public:
	Tape(TC from, TC to, TC defstart, TC definc);
	~Tape();
	std::vector<T> move();
	std::vector<T> move(TC k);
	void push(T val);
	void push(T val, TC start);
private:
	TC from, to, defstart, definc;
	struct tape_entry {
		TC c;
		T val;
	};
	tape_entry mk_tape_entry(TC c, T val);
	std::deque<tape_entry> tape;
};

#endif
#include "Tape.cpp"
