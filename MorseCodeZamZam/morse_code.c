
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <time.h>

#define BUTTON_PIN			15	// Pin 21 (GPIO 16)
#define R 13
#define G 12
#define B 11

#define BRIGHTNESS 25
#define MAX_COLOUR_VALUE 255
#define MAX_PWM_LEVEL 65535

// declare global variables e.g., the time when the button is pressed 
int pressed = 0;
int notPressed = 0;
int notPressedCounter = 0;

int letterArray[4]; //can be changed to 4 if Angela's if statement works with count

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder(int pressed);

// check if the button press is a dot or a dash
void checkButton(int notPressed);

int countElements();
void printArray();
void resetArray();
void addToArray(int value);//1 is dot 2 is dash
void angelasIfStatement();
void outputEight();

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

    outputEight();
	// seven_segment_show(26);
	// sleep_ms(500);
	// seven_segment_off();

	//display welcome message
	printf("\nWelcome!\n");
	
	while (true) {
		printArray();
		notPressedCounter = 0;
		while (gpio_get(BUTTON_PIN) == false) { //loop continues until button is pressed again 
			notPressed = notPressed + 1;
			pressed = 0;
			notPressedCounter += 1;
			if (notPressedCounter > 8){
				//set array to be 0 so the if statements work
				break;
			}
			sleep_ms(50);
		}

		checkButton(notPressed); 		
 
		while (gpio_get(BUTTON_PIN)) {
			pressed = pressed + 1;
			notPressed = 0;
			sleep_ms(50);
		}

		decoder(pressed);
	}
	
}

void decoder(int pressed){
    if (pressed > 0){
		if (pressed < 5){
			//dot or dash loop
			printf("\nThis is a dot!");
			addToArray(1);
		} else if (pressed < 14){
			printf("\nThis is a dash!");
			addToArray(2);
		} else {
            outputEight();
            printf("\nSignal not recognised - too long!");
            resetArray();
            //if button pressed for too long, outputs an error
        }
	}
	// a function to be implemented
}

void checkButton(int notPressed){
	if (notPressed > 8){
		printf("\nThis is an inter-letter gap!");
		angelasIfStatement();
		resetArray();
        //removes all values of array
	} else {
		printf("\nThis is a inter_signal gap!");
	}

}

int countElement() {
	//return the last free value
	int count = 0;
	while (letterArray[count] != 0 && count < 4) {
		count++;
	}
	return count;
}

void printArray() {
	//print the array in form 0 0 0 0
	printf("\n");
	for (int i = 0; i < 4; i++) {
		printf("%d ",letterArray[i]);
	}
}

void resetArray() {
	//resets array to 0 0 0 0
	for (int j = 0; j < 4; j++) {
		letterArray[j] = 0;
	}
}

void addToArray(int value) {
	//adds parameter value into array
	//might need to add some validation incase its a 1 or a 2
	letterArray[countElement()] = value;
}

void outputEight() {
    seven_segment_show(26);
	sleep_ms(500);
	seven_segment_off();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Angela's if statement++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void angelasIfStatement() {
	//Angela's if statements 
    bool isCorrect = false;
	int count = countElement();
	printf("%d ",count);
  	
    if (count == 1) {
        printf("\nzoe");
        printf("\n%d",letterArray[0]);
  	    if (letterArray[0] == 1) {
            isCorrect = true; 
            seven_segment_show(4);
            // calls E
  	    } else if (letterArray[0] == 2) {
            isCorrect = true;
            seven_segment_show(19);
            // calls T
       }
   }
   else if (count == 2) {
       if (letterArray[0] == 1 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(0);
            // calls A
       }
       if (letterArray[0] == 1 && letterArray[1] == 1) {
            isCorrect = true;
		    seven_segment_show(8);
            // calls I
       }
       if (letterArray[0] == 2 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(12);
            // calls M
       }
       if (letterArray[0] == 2 && letterArray[1] == 1) {
            isCorrect = true;
            seven_segment_show(13);
            // calls N
       }
    }
    else if (count == 3){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(3);
            // calls D
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(6);
            // calls G
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(10);
            // calls K
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(14);
            // calls O
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(17);
            // calls R
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(18);
            // calls S
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(20);
            // calls U
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(22);
            // calls W
       }
    }
    else if (count == 4){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(1);
            // calls B
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(2);
            // calls C
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(5);
            // calls F
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(7);
            // calls H
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(9);
            // calls J
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(11);
            // calls L
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(15);
            // calls P
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(16);
            // calls Q
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(21);
            // calls V
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(23);
            // calls X
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(24);
            // calls Y
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(25);
            // calls Z
       }
   } else if (letterArray[0] == 0 && letterArray[1] == 0 && letterArray[2] == 0 && letterArray[3] == 0) {
	    printf("\nNothing has been inputted right now!");
        isCorrect = true;
   } 

   if (isCorrect == false) {
       printf("\nError - invalid input");
       outputEight();
       // displays error
   }
	   
   if (letterArray[0] != 0){
    sleep_ms(500); 
    //displays letter for longer if something has been inputted
   }
   sleep_ms(50);
   seven_segment_off();
}
