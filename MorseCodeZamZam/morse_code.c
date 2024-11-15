
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include <time.h>

#define BUTTON_PIN			15	// Pin 21 (GPIO 16)
//#define CLOCKS_PER_SEC CLOCKS_PER_SEC 100

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
		//checkButton(notPressed);   
		while (gpio_get(BUTTON_PIN)) {
			pressed = pressed + 1;
			notPressed = 0;
			sleep_ms(50);

			// pressed = 2;
			// //count++;
            // // record how long the button is pressed
            // // .....
			// printf("This line is a test\n");  // you can remove this line
			// //sleep_ms(150); // adjust the sleep_ms as required
		}
		// decoder(pressed);

		decoder(pressed);
 		
		//checkButton(notPressed);        
		// check if the button press is a dot or a dash
		// if (pressed == 2) {
		// 	checkButton();
		// }
	}
	
}

void decoder(int pressed){
    if (pressed > 0){
		if (pressed < 5){
			//dot or dash loop

			printf("\nThis is a dot!");
			addToArray(1);
		} else {
			printf("\nThis is a dash!");
			addToArray(2);
		}
	}
	// a function to be implemented
}

// void checkButton(int count){
// 	double timeTaken = count / CLOCKS_PER_SEC;
// 	printf("%f",timeTaken);
//     // a function to be implemented
// }

void checkButton(int notPressed){
	if (notPressed > 8){
		printf("\nThis is an inter-letter gap!");
		//make array all entities 0
		angelasIfStatement();
		resetArray();
	} else {
		


		printf("\nThis is a inter_signal gap!");
	}

	// clock_t start;
	// clock_t end;
	// if (pressed == 2){
	// 	start = clock();
	// 	printf("%f \n",(double)start);
	// }
	// if (pressed == 1){
	// 	end = clock();
	// 	printf("%f \n",(double)end);
	// }
	// double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
	// printf("The time taken was %f \n",timeTaken);
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


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Angela's if statement++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void angelasIfStatement() {
	//Angela's if statements 
	int count = countElement();
	printf("%d ",count);
  	if (letterArray[0] = 0){
       printf("Array empty :((()))");
       //pass to subroutine to reset
  	}
  	if (count == 1) {
  	    if (letterArray[0] == 1) {
           seven_segment_show(4);
           // calls E
		   printf("This is an E");
  	    } else if (letterArray[0] == 2) {
           seven_segment_show(19);
           // calls T
       }
   }
   if (count == 2) {
//       if (letterArray == [1,2]) {
       if (letterArray[0] == 1 && letterArray[1] == 2) {
           seven_segment_show(0);
           // calls A
       }
       if (letterArray[0] == 1 && letterArray[1] == 1) {
           printf("Dis is an I");
		   seven_segment_show(8);
           // calls I
       }
       if (letterArray[0] == 2 && letterArray[1] == 2) {
           seven_segment_show(12);
           // calls M
       }
       if (letterArray[0] == 2 && letterArray[1] == 1) {
           seven_segment_show(13);
           // calls N
       }
   }
   if (count == 3){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1) {
           seven_segment_show(3);
           // calls D
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1) {
           seven_segment_show(6);
           // calls G
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2) {
           seven_segment_show(10);
           // calls K
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 2) {
           seven_segment_show(14);
           // calls O
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1) {
           seven_segment_show(17);
           // calls R
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1) {
           seven_segment_show(18);
           // calls S
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2) {
           seven_segment_show(20);
           // calls U
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2) {
           seven_segment_show(22);
           // calls W
       }
   }
   if (count == 4){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
           seven_segment_show(1);
           // calls B
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
           seven_segment_show(2);
           // calls C
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
           seven_segment_show(5);
           // calls F
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
           seven_segment_show(7);
           // calls H
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 2) {
           seven_segment_show(9);
           // calls J
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
           seven_segment_show(11);
           // calls L
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 1) {
           seven_segment_show(15);
           // calls P
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 2) {
           seven_segment_show(16);
           // calls Q
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
           seven_segment_show(21);
           // calls V
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
           seven_segment_show(23);
           // calls X
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 2) {
           seven_segment_show(24);
           // calls Y
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
           seven_segment_show(25);
           // calls Z
       }
   } else if (letterArray[0] == 0 && letterArray[1] == 0 && letterArray[2] == 0 && letterArray[3] == 0) {
	printf("\nNothing has been inputted right now!");
   } else {
       printf("\nError - invalid input");
       seven_segment_show(26);
       // displays error
	   
   }
   sleep_ms(50);
   seven_segment_off();
}
