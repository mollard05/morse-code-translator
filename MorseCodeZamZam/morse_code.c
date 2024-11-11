
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <time.h>

#define BUTTON_PIN			15	// Pin 21 (GPIO 16)
//#define CLOCKS_PER_SEC CLOCKS_PER_SEC 100

// declare global variables e.g., the time when the button is pressed 
int pressed = 0;

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder();

// check if the button press is a dot or a dash
void checkButton();

int main() {
	timer_hw->dbgpause = 0;
	stdio_init_all();

	// Initialise the seven segment display.
	seven_segment_init();

	// Turn the seven segment display off when the program starts.
	seven_segment_off();

	// Initialise the button's GPIO pin.
	gpio_init(BUTTON_PIN);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

	seven_segment_show(26);
	sleep_ms(500);
	seven_segment_off();
	//display welcome message
	printf("Welcome!\n");

	while (true) {
		
		
		
		pressed = 1;
		while (gpio_get(BUTTON_PIN)){	
			pressed = 2;
			//count++;
            // record how long the button is pressed
            // .....
			printf("This line is a test\n");  // you can remove this line
			//sleep_ms(150); // adjust the sleep_ms as required
		}
        // check if the button press is a dot or a dash
		if (pressed == 2) {
			checkButton();
		}
	}
	
}

void decoder(){
    // a function to be implemented
}

// void checkButton(int count){
// 	double timeTaken = count / CLOCKS_PER_SEC;
// 	printf("%f",timeTaken);
//     // a function to be implemented
// }

void checkButton(){
	clock_t start;
	clock_t end;
	if (pressed == 2){
		start = clock();
		printf("%f \n",(double)start);
	}
	if (pressed == 1){
		end = clock();
		printf("%f \n",(double)end);
	}
	double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time taken was %f \n",timeTaken);
}

/*
int pressed;
int not_pressed;
need a letter array to add the dots and dashes
string word to put letters into

while (true) {
  
  while (gpio_get(BUTTON_PIN)){
      // record how long the button is pressed
      pressed = pressed +1;
      not_pressed = 0;
      sleep_ms(50); // adjust the sleep_ms as required
      // .....
  }
// ....... 
// more to be done ...
	not pressed = 1
	addsignal to letter array
	pressed = 0 
	sleep(50) 
	..
	if slept for 700ms pass to letter function

*/