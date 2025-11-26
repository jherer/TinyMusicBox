Firmware to turn an ATtiny85 into an SPI polyphonic synthesizer module. Any microcontroller can tell it what notes to play, with up to 4 notes at once.

# Overview
Previously, I have used the [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) feature on the ATtiny to make piano synthesizer/instrument type projects.
The inspiration came from this great tutorial on [technoblogy.com](http://www.technoblogy.com/show?20W6) on making a function generator using the ATtiny's PWM.
By changing the PWM frequency and shape, you can create a whole range of retro/lofi notes (and chords, if polyphony is implemented).

I made simple instruments with buttons and potentiometers, but only having 5 GPIO pins limited what I could do with it. While I could put everything on a larger development board, I think
the move is to separate the frequency generation part from the music-controlling part. A "master" device should tell the ATtiny what notes to play, and the ATtiny should the PWM signal. By doing this
the frequency generator can be used in a variety of projects, from a simple button piano to a MIDI player.

# SPI
Currently, I have just figured out how to set up two-way SPI with a two-byte buffer. Since each SPI frame is one byte long, I have to store the previous and current bytes at once.
The first byte is the "command" byte that describes what setting to update (frequency, waveform, octave, etc.). The second byte is the "data" byte that has the new value for the setting.

So far the buffer works, but I just tested it by changing a chord. Next, I need to add the specific commands and make them change the appropriate settings on the ATtiny.
