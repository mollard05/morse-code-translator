# Morse Code Translator
Using a raspberry pi pico board, this is the code for a morse code translator. Inputs on the button in specific timings will produce specific letters using a dash or a dot and then output it to the 8-bit screen.

<img src="https://github.com/mollard05/mollard05/blob/main/morsecodegif.gif">

## How we made it:
Used: C, Raspberry Pi Pico
Pico Components: Buzzer, Buttons, 7-Segment Display, RGB Leds

By using a simple time counter, we calculated whether the button imput recorded a dash or a dot. A sequence of these, as long as they were done within the time frame to be counted as one letter, would cause a green light rgb to be shown, a short buzzer of the letter imputted and the visual letter would be outputted onto the 7-segment screen. If the input went wrong, e.g. waited too long to get a full letter/not correct morse code, then the rgb would display red and the buzzer would play a large "incorrect" sound.

## Authors and acknowledgment
This was made in a team of 3 with coursemates Angela Melbourne and Zoe Weston.

## Project status
As this was for a university project and I no longer have access to the pico boards, this project has been fully completed.
