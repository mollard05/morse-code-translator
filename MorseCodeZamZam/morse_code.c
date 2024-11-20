
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include "hardware/pwm.h"
#include "includes/buzzer.h"
//#include "includes/poteniometer.h"

#define BUTTON_PIN  		15	// Pin 21 (GPIO 15)
#define BUTTON_PIN_TWO        14           
#define BUZZER_PIN            17   // Pin 22 (GPIO 17)

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
char wordString[4];

// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder(int pressed);

// check if the button press is a dot or a dash
void checkButton(int notPressed);

void welcomeMessage();
int countElements();
void printArray();
void resetArray(int decision);
void addToArray(int value);//1 is dot 2 is dash
void angelasIfStatement();
void outputEight();
void setUpRGB();
void showRGB(int r, int g);
//void buzzer_init();
void playNote(unsigned int frequency, unsigned int length);
int countElementWord();
void addToWord(char value);
//void setPotentiometer();

void setUpRGB() {
    gpio_set_function(R, GPIO_FUNC_PWM);
    gpio_set_function(G, GPIO_FUNC_PWM);
    gpio_set_function(B, GPIO_FUNC_PWM);
    //tell LED pins that PWM in charge of value

    uint slice_num = pwm_gpio_to_slice_num(R);
    pwm_config config = pwm_get_default_config();

    pwm_init(slice_num, &config, true);

    slice_num = pwm_gpio_to_slice_num(G);
    pwm_init(slice_num, &config, true);

    slice_num = pwm_gpio_to_slice_num(B);
    pwm_init(slice_num, &config, true);
}

int main() {
	timer_hw->dbgpause = 0;
	stdio_init_all();
     buzzer_init();
    // potentiometer_init();

	// Initialise the seven segment display.
	seven_segment_init();

	// Turn the seven segment display off when the program starts.
	seven_segment_off();

	// Initialise the button's GPIO pin.
	gpio_init(BUTTON_PIN);
     gpio_init(BUTTON_PIN_TWO);
	gpio_set_dir(BUTTON_PIN, GPIO_IN);
	gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).
     gpio_set_dir(BUTTON_PIN_TWO, GPIO_IN);
	gpio_pull_down(BUTTON_PIN_TWO); // Pull the button pin towards ground (with an internal pull-down resistor).


    setUpRGB();

    //outputs welcome message and 8 to seven segment display
    welcomeMessage();
    resetArray(2);

    //setPotentiometer();

	while (true) {
		// printArray();
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

void welcomeMessage() {
     showRGB(0,0);
     //display welcome message
	printf("\nWelcome!\n");
     //display 8 to seven segment display
     seven_segment_show(26);
	sleep_ms(500);
	seven_segment_off();
}

// void setPotentiometer() {
//      int value = potentiometer_read(3);
//      printf("Potentiometer set to %d", value);
// }

void decoder(int pressed){
    if (pressed > 0){
		if (pressed < 5){
			//dot or dash loop
//			printf("\nThis is a dot!");
			addToArray(1);
		} else if (pressed < 14){
//			printf("\nThis is a dash!");
			addToArray(2);
		} else {
            outputEight();
            showRGB(255,0);
            printf("\nError! - signal pressed for too long!");
            resetArray(1);
            //if button pressed for too long, outputs an error
        }
	}
	// a function to be implemented
}

void checkButton(int notPressed){
	if (notPressed > 8){
//		printf("\nThis is an inter-letter gap!");
		angelasIfStatement();
          // printArray();
		// resetArray();
        //removes all values of array
	} else {
//		printf("\nThis is a inter_signal gap!");
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

int countElementWord() {
	//return the last free value
	int count = 0;
	while (wordString[count] != 0 && count < 4) {
		count++;
	}
	return count;
}

void printArray() {
	//print the array in form 0 0 0 0
	//printf("\n");
	for (int i = 0; i < 4; i++) {
          if (letterArray[i] == 1) {
               playNote(255, 75);
          } else if (letterArray[i] == 2) {
               playNote(150, 200);
          }
		//printf("%d ",wordString[i]);
	}
}

void resetArray(int decision) {
	//resets array to 0 0 0 0
     if (decision == 1){
     	for (int j = 0; j < 4; j++) {
	     	letterArray[j] = 0;
	     }
     } else if (decision == 2){
          for (int j = 0; j < 4; j++) {
	     	wordString[j] = 0;
	     }
     }
}

void addToArray(int value) {
	//adds parameter value into array
	//might need to add some validation incase its a 1 or a 2
	letterArray[countElement()] = value;
}
void addToWord(char value) {
	//adds parameter value into array
	//might need to add some validation incase its a 1 or a 2
	wordString[countElementWord()] = value;
}

void outputEight() {
     seven_segment_show(26);
     showRGB(255,0);
     playNote(31, 500);
     playNote(150, 400);
	seven_segment_off();
}

void showRGB(int r, int g) {
    pwm_set_gpio_level(R, ~(MAX_PWM_LEVEL * r / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
    pwm_set_gpio_level(G, ~(MAX_PWM_LEVEL * g / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
    pwm_set_gpio_level(B, ~(MAX_PWM_LEVEL * 0 / MAX_COLOUR_VALUE * BRIGHTNESS / 100));
 //   printf("\nShowing rgb: %u %u %u",r, g, 0);
}

void playNote(unsigned int frequency, unsigned int length) {
	// Play the specified frequency for 1 second.
     buzzer_init();
	buzzer_enable(frequency);
	sleep_ms(length);
     buzzer_disable();
     sleep_ms(50);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Angela's if statement++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void angelasIfStatement() {
	//Angela's if statements 
     bool isCorrect = false;
     bool isEmpty = false;
	int count = countElement();
//	printf("%d ",count);
  	
     if (count == 1) {
//        printf("\nzoe");
 //       printf("\n%d",letterArray[0]);
  	    if (letterArray[0] == 1) {
            isCorrect = true; 
            seven_segment_show(4);
            addToWord('E');
            // calls E
  	    } else if (letterArray[0] == 2) {
            isCorrect = true;
            seven_segment_show(19);
            addToWord('T');
            // calls T
       }
   }
   else if (count == 2) {
       if (letterArray[0] == 1 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(0);
            addToWord('A');
            // calls A
       }
       if (letterArray[0] == 1 && letterArray[1] == 1) {
            isCorrect = true;
		    seven_segment_show(8);
              addToWord('I');
            // calls I
       }
       if (letterArray[0] == 2 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(12);
            addToWord('M');
            // calls M
       }
       if (letterArray[0] == 2 && letterArray[1] == 1) {
            isCorrect = true;
            seven_segment_show(13);
            addToWord('N');
            // calls N
       }
    }
    else if (count == 3){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(3);
            addToWord('D');
            // calls D
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(6);
            addToWord('G');
            // calls G
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(10);
            addToWord('K');
            // calls K
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(14);
            addToWord('O');
            // calls O
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(17);
            addToWord('R');
            // calls R
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(18);
            addToWord('S');
            // calls S
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(20);
            addToWord('U');
            // calls U
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(22);
            addToWord('W');
            // calls W
       }
    }
    else if (count == 4){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(1);
            addToWord('B');
            // calls B
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(2);
            addToWord('C');
            // calls C
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(5);
            addToWord('F');
            // calls F
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(7);
            addToWord('H');
            // calls H
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(9);
            addToWord('J');
            // calls J
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(11);
            addToWord('L');
            // calls L
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(15);
            addToWord('P');
            // calls P
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(16);
            addToWord('Q');
            // calls Q
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(21);
            addToWord('V');
            // calls V
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(23);
            addToWord('X');
            // calls X
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(24);
            addToWord('Y');
            // calls Y
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(25);
            addToWord('Z');
            // calls Z
       }
   } else if (letterArray[0] == 0 && letterArray[1] == 0 && letterArray[2] == 0 && letterArray[3] == 0) {
//	     printf("\nNothing has been inputted right now!");
          isCorrect = true;
          isEmpty = true;
          //if nothing is inputted
     } 

     if (isCorrect == false && isEmpty == false) {
       printf("\nError! - invalid input");
       resetArray(2);
       outputEight();
       showRGB(255,0);
       // displays error
     } else if (isCorrect == true && isEmpty == false) {
       showRGB(0,255);
       printArray();
     }
	   
     if (letterArray[0] != 0){
          sleep_ms(500); 
          //displays letter for longer if something has been inputted
     }

     // printArray();
     resetArray(1);

     if (wordString[3] != 0) {
          for (int i = 0; i < 4; i++) {
               printf("%c", wordString[i]);
               // printf("%d", i);
          }
          resetArray(2);
          printf("\n");
          for (int i = 0; i < 5; i++){     
               playNote(500,100);
               playNote(400,100);
          }
          printf("To continue, press left button\n");
          printf("To exit, press the right button >> \n");
          bool p = false;
          while (p == false) {
               showRGB(0,0);
               seven_segment_off();
               if (gpio_get(BUTTON_PIN)) {
                    p = true;
                    showRGB(0, 255);
                    sleep_ms(300);
                    showRGB(0,0);
               } else if (gpio_get(BUTTON_PIN_TWO)){
                    p = true;
                    showRGB(255,0);
                    sleep_ms(300);
                    showRGB(0,0);
                    exit(1);
               }
          }
     }
     
     sleep_ms(50);
     showRGB(0,0);
     seven_segment_off();
}