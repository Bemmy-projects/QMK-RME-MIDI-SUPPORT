# QMK-RME-MIDI-SUPPORT

MIDI code for QMK to:  
1. control the values of the faders in a RME audio interface via MIDI and a rotary encoder of the keyboard  
2. sync those values (where possible) to the ones in the interface, should they have changed. (Note: This is not possible for the headphone output)

This is just a simple implementation written to suit our needs. Implemented are the following feautures:
Control Headphone and Mainout levels with a rotary encoder
Change between the two with the Encoder acting as a button by calling a function in the QMK keyboard.c
Sync the fader values of the mainout in the audio interface with the rotary encoder, so that changes can be done with the encoder, the interface directly, or with in the interface software.

Levels are sent via Control Change messages, while the feedback (here only implemented for the mainout) is provided via Pitch Bend messages.

For further options please refer to this thread on the RME forums to gain insight into further possibilities: https://forum.rme-audio.de/viewtopic.php?id=24437

We hope that these files provide a useful starting point for anyone who wants to implement MIDI within QMK, especially for reading MIDI, which is, at the point of publishing, not well documented at all. 
There are a lot of comments within the code, in the hope that they provide useful insights.
