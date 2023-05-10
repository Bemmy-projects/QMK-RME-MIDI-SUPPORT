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

#ifndef USERMIDI_C
#define USERMIDI_C

#include QMK_KEYBOARD_H
#include "usermidi.h"
#include "midi.h"

extern MidiDevice midi_device;

/*
 * To handle incoming MIDI messages the quantum/midi/process_midi.c needs to be modified. 
 * The appropriate function (in this case midi_register_pitchbend_callback(&midi_device, midi_pitchbend_user);) needs to be put into the midi_task() function, before the midi_device_process() function, which gets called when there is an incoming message.
 * Remember to include the usermidi.h in process_midi.c!
 * Note: this example only handles incoming pitch bend messages. If other types of messages are needed, further functions need to be added in the same manner.
 * Also add the usermidi.h to keymap.c if you need to use the changeDevice() function
 * Furthermore: Do not forget to add the following to your rules.mk (we just added it under the SRC += matrix.c in our case)):
 * SRC += usermidi.c
 * 
 * For simple outgoing midi handling the inclusion in the process_midi.c is not required.
 */


struct MidiVal headphones = { 108, 8, 64 }; //HW outs on channel 9 //channel numbers need to be given as n-1
struct MidiVal mainout = { 102, 8, 64 }; //64 corresponds to about -12dB
struct MidiVal* currentDevice = &headphones;


void midi_pitchbend_user(MidiDevice *midi_device, uint8_t byte0, uint8_t byte1, uint8_t byte2) {
    //handle Pitchbend messages
    if ((byte0 & 0x0F) == 8) { //MIDI Channel is contained in the 4 LSB of the first byte, upper 4 bits denote it as a pitchbend message
        uint16_t pitch_bend_value = ((uint16_t)byte2 << 7) | byte1; // Combine the two data bytes into a 14-bit integer
        mainout.value = (int) (pitch_bend_value*127)/16383; //convert pitchbend value into range of 0-127, then store as the updated value for the mainout
    }
}


bool encoder_update_kb(uint8_t index, bool clockwise) {

    if (!encoder_update_user(index, clockwise)) return false;
    /* top left encoder */
    if (index == 0) {
        if (clockwise && currentDevice->value < 127) {
            currentDevice->value++;
        } if (!clockwise && currentDevice->value > 0){
            currentDevice->value--;
        }
        midi_send_cc(&midi_device, currentDevice->channel, currentDevice->ccNumber, currentDevice->value);
    }
    
    /* top right encoder */
    else if (index == 1) {
        if (clockwise && currentDevice->value < 127) {
            currentDevice->value++;
        } if (!clockwise && currentDevice->value > 0){
            currentDevice->value--;
        }
        midi_send_cc(&midi_device, currentDevice->channel, currentDevice->ccNumber, currentDevice->value);
    }
    return true;
}


void changeDevice(void) {
    
    if (currentDevice == &headphones) {
        currentDevice = &mainout;
    }
    else {
        currentDevice = &headphones;
    }
}


#endif // USERMIDI_C