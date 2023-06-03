# KeyPad-and-4x20-LCD-WS2815-stand-alone-controllor
KeyPad and 4x20 LCD WS2815 stand alone controllor
 I own Pittsburgh Event Lighting (https://www.pittsburgheventlighting.com). I have been designing, testing, and refining a WS2815 project using FastLED and need some advice. I need someone to design and program an Arduino program.
My close friend produces hard cider and opened a new location/bar. I installed a sound system and placed WS2815 on the display shelves. I am working on the controller. My goals for the controller are:
•	Reliability
•	Stand-alone operation
•	Simple control with ease of use
•	Custom scenes and chases
Details:
•	1-99 keypad custom for selecting scenes/programs.
•	LCD display
o	Scene # and description i.e. "Rainbow Chase"
o	Dimmer level 1-100
o	Chase speed 1-100
•	Four Hardware debounced tactical switches
o	Dimmer / Brightness control
o	Speed control for active (chase) scenes

I have been using FastLED and a repurposed and gutted ADJ LED Controller (RGBW4C-IR) for testing and prototyping. 24-scene buttons are not enough scenes to cover all the holiday scenes and other static and active/chase scenes I require.

https://github.com/Frank-PittsburghEventLighting/LED-Arsenal-2023/blob/main/LED-Arsenal-2023
https://www.reddit.com/r/FastLED/comments/ta0ipv/24keypad_plus_4x4_matrix_16keypad_two_1602lcd_to/

A keypad and display are my best options to simplify operation and flexibility. WLED will not work, FastLED is my best choice. If possible.
LED pixel number future Bluetooth & network support
