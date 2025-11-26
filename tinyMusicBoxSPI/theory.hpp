  
#include <avr/io.h>

// NOTES

// Frequencies for one octave of notes
const uint16_t noteToFreq[12] = {440*2, 466*2, 494, 523, 554, 587, 622, 660, 698, 740, 784, 831};

// Define indexes of the array as scale steps
#define TONIC 0
#define MIN_SECOND 1
#define MAJ_SECOND 2
#define MIN_THIRD 3
#define MAJ_THIRD 4
#define FOURTH 5
#define DIM_FIFTH 6
#define FIFTH 7
#define MIN_SIXTH 8
#define MAJ_SIXTH 9
#define MIN_SEVENTH 10
#define MAJ_SEVENTH 11

// Create chords with scale steps
// Provide the default (diatonic) steps for a major scale
const uint8_t defaultNotes[7][4] = {
	{TONIC, MAJ_THIRD, FIFTH, MAJ_SEVENTH},
	{MAJ_SECOND, FOURTH, MAJ_SIXTH, TONIC},
	{MAJ_THIRD, FIFTH, MAJ_SEVENTH, MAJ_SECOND},
	{FOURTH, MAJ_SIXTH, TONIC, MAJ_THIRD},
	{FIFTH, MAJ_SEVENTH, MAJ_SECOND, FOURTH},
	{MAJ_SIXTH, TONIC, MAJ_THIRD, FIFTH},
	{MAJ_SEVENTH, MAJ_SECOND, FOURTH, MAJ_SIXTH},
};



// TIMING AND CHORD STRUCTURE

#define STEPS 14
#define BEAT_MS 100

typedef struct Chord {
	uint8_t beats;
	uint8_t n0;
	uint8_t n1;
	uint8_t n2;
	uint8_t n3;
} Chord_t;


Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3);
Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1, uint8_t n2);
Chord_t play(uint8_t beats, uint8_t n0, uint8_t n1);
Chord_t play(uint8_t beats, uint8_t n0);
Chord_t rest(uint8_t beats);

