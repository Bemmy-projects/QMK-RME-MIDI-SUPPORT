/* Copyright 2023 Bratzel & Fernández Larrubia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef USERMIDI_H
#define USERMIDI_H
#include "midi.h"

struct MidiVal {
    int ccNumber;
    int channel;
    int value;
};

struct MidiVal* currentDevice;

/**
 * @brief Change the used MIDI channel and CC number used to send MIDI_CC messages with the encoders
 * aka change the output channels on the RME interface
 * 
 */
void changeDevice(void);

/**
 * @brief Called by QMK when an encoder is turned
 * Sends the MIDI_CC messages with the current values changed by the encoders (changes the value in the MIDIVal struct)
 * 
 * @param index Enumeration for the encoder that is turned, as defined in config.h (list of encoders)
 * @param clockwise rotation direction
 * @return true if the enconder has been updated,
 * @return false otherwise
 */
bool encoder_update_kb(uint8_t index, bool clockwise);

/**
 * @brief Gets called by QMK when a pitchbend message is received
 * Changes the value of mainout.value according to the pitchbend value
 *
 * The 7 LSB of the first and the 7 MSB of the second byte are combined to a 14 bit value that is the actual pitchbend value
 * 
 * @param midi_device Used (virtual) MIDI device. Automatically opened by QMK
 * @param byte0 First Byte of the MIDI message
 * @param byte1 Second Byte of the MIDI message
 * @param byte2 Third Byte of the MIDI message
 */
void midi_pitchbend_user(MidiDevice *midi_device, uint8_t byte0, uint8_t byte1, uint8_t byte2);


#endif // USERMIDI_H