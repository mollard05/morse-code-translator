/**
 * The given template is a guideline for your coursework only.
 * You are free to edit/create any functions and variables.
 * You can add extra C files if required.
*/
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <time.h>

#define BUTTON_PIN			15	// Pin 21 (GPIO 16)
//#define CLOCKS_PER_SEC CLOCKS_PER_SEC 100

// declare global variables e.g., the time when the button is pressed 
int pressed ;

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder();

// check if the button press is a dot or a dash
void checkButton(clock_t start, clock_t end);

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

	while (true) {
		clock_t start;
		clock_t end;

		if (gpio_get(BUTTON_PIN)) {
			start = clock();
		} else if (gpio_get(BUTTON_PIN) == false){
			end = clock();
		}
















		//bool buttonPressed = gpio_get(BUTTON_PIN);
		/*if (buttonPressed) {
		*	printf("The button has been pressed");
		*}
		*/
		//int count = 0;
		// pressed = 0;
		// while (gpio_get(BUTTON_PIN)){	
		// 	pressed = 2;
		// 	//count++;
        //     // record how long the button is pressed
        //     // .....
		// 	printf("This line is a test\n");  // you can remove this line
		// 	//sleep_ms(150); // adjust the sleep_ms as required


		// }
        // check if the button press is a dot or a dash
		checkButton(start, end);
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

void checkButton(clock_t start, clock_t end){
	 clock_t startv = start;
	 clock_t endv = end;

	// if (pressed == 1){
	// 	start = clock();
	// 	printf("%f \n",(double)start);
	// }
	// if (pressed == 0){
	// 	end = clock();
	// 	printf("%f \n",(double)end);
	// }
	double timeTaken = (double)(endv - startv) / CLOCKS_PER_SEC;
	printf("%f \n",timeTaken);
}

