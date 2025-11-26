#include "theory.hpp"

Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
	Chord_t chord;
	chord.beats = beats;
	chord.n0 = n0;
	chord.n1 = n1;
	chord.n2 = n2;
	chord.n3 = n3;
	return chord;
}

Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1, uint8_t n2) {
	return play(beats, n0, n1, n2, 0);
}

Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1) {
	return play(beats, n0, n1, 0, 0);
}

Chord_t play(uint8_t beats, uint8_t n0) {
	return play(beats, n0, 0, 0, 0);
}

Chord_t rest(uint8_t beats) {
	return play(beats, 0, 0, 0, 0);
}

