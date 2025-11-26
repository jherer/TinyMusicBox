#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include "mySPI.hpp"
#include "synth.hpp"
#include "theory.hpp"

#define CHECK_BIT(var,pos) (((var) & (1<<(pos))) > 0)




int main () {
	//float BPM = 100;
	//uint8_t deltaTimeMS = 1 / (BPM/60000.0);
	
	/*Chord_t sequence[] = {
		play(1, TONIC, FIFTH),
		rest(1),	
		play(1, TONIC, FIFTH),
		play(3, TONIC, MAJ_SIXTH),
		play(3, TONIC, FIFTH),
		play(3, MAJ_THIRD, TONIC),
		play(6, FIFTH, MAJ_SEVENTH),
		play(1, FIFTH, FIFTH),
		rest(1),	
		play(1, MAJ_SECOND, FIFTH),
		play(3, FIFTH, MAJ_SIXTH),
		play(3, FIFTH, FIFTH),
		play(3, FIFTH, MAJ_SECOND),
		play(6, MAJ_THIRD, TONIC),
	};
	uint16_t step = 0;
*/
	initSynth();
	initSPI();
	sei();

	uint8_t currCmd = 0;
	uint8_t currData = 0;
	setJump(0, noteToFreq[TONIC]);
	setJump(1, noteToFreq[MAJ_THIRD]);
	setJump(3, noteToFreq[FIFTH]);

	while (1) {
		/*Chord_t currChord = sequence[step];
		setJump(0, noteToFreq[currChord.n0]);
		setJump(1, noteToFreq[currChord.n1]);
		//setJump(2, noteToFreq[currChord.n2]);
		//setJump(3, noteToFreq[currChord.n3]);
		for (int i = 0; i < currChord.beats; i++) {
			_delay_ms(BEAT_MS);
		}

		step++;
		step = step % STEPS;*/

		updateSPI();

		
		//uint8_t numBytes = getSPINumBytes();
		if (isSPIReady()) {
			currCmd = getSPIIn(0);
			currData = getSPIIn(1);
			if (currCmd == 0x55) {
				if (currData == 0xaa) {
					setJump(0, noteToFreq[TONIC]);
					setJump(1, noteToFreq[MAJ_THIRD]);
					setJump(2, noteToFreq[FIFTH]);
				} else if (currData == 0xcc) {
					setJump(0, noteToFreq[MAJ_SECOND]);
					setJump(1, noteToFreq[FOURTH]);
					setJump(2, noteToFreq[MAJ_SIXTH]);
				}
			}
			clearSPIBuffer();
		}
		
	}

}