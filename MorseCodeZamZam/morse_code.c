
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"
#include "hardware/pwm.h"
#include "includes/buzzer.h"

#define BUTTON_PIN  		16	// Pin 21 (GPIO 15)
#define BUTTON_PIN_TWO        14   // Pin 19 (GPIO 14)
#define BUZZER_PIN            17   // Pin 22 (GPIO 17)

// RGB LED colours plugged in
#define R 13
#define G 12
#define B 11
// RGB Levels
#define BRIGHTNESS 25
#define MAX_COLOUR_VALUE 255
#define MAX_PWM_LEVEL 65535


// declare global variables e.g., the time when the button is pressed 
int pressed = 0;
int notPressed = 0;
int notPressedCounter = 0;

int maxTime = 4;
int totalTime = 0;

unsigned int potValue = 0;
unsigned int potValue1 = 0;

int letterArray[4]; //counts dots and dashes of each letter
char wordString[4]; //counts each letter of a 4 letter input

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
void playNote(unsigned int frequency, unsigned int length);
int countElementWord();
void addToWord(char value);

void potential();

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

	// Initialise the seven segment display.
	seven_segment_init();

     // Initialise the potentiometer.
     potentiometer_init();

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
    potential();

	while (true) {
		notPressedCounter = 0;

		while (gpio_get(BUTTON_PIN) == false) { //loop continues until button is pressed again 
			notPressed = notPressed + 1;
			pressed = 0;
			notPressedCounter += 1;
			if (notPressedCounter > 8){
				//set array to be 0 so the if statements work
                    totalTime += 1;
				break;
			}
			sleep_ms(50);
               totalTime += 1; //adds to total time for letter when not pressed
		}

		checkButton(notPressed); 		
 
		while (gpio_get(BUTTON_PIN)) {
			pressed = pressed + 1;
			notPressed = 0;
			sleep_ms(50);
               totalTime += 1; //adds to total time for letter when pressed
		}

		decoder(pressed);

          if (totalTime >= maxTime * 20){
               printf("\nError! - too long to input letter\n");
               outputEight();
               totalTime = 0;
               resetArray(1);
          }
          totalTime += 1;
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


void decoder(int pressed){
    if (pressed > 0){
		if (pressed < 5){
			//dot or dash loop
			addToArray(1);
		} else if (pressed < 14){
			addToArray(2);
		} else {
            outputEight();
            showRGB(255,0);
            printf("\nError! - signal pressed for too long!");
            resetArray(1);
            totalTime = 0;
            //if button pressed for too long, outputs an error
        }
	}
}

void checkButton(int notPressed){
	if (notPressed > 8){
          //totalTime = 0;
		angelasIfStatement();
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
	for (int i = 0; i < 4; i++) {
          if (letterArray[i] == 1) {
               playNote(255, 75);
          } else if (letterArray[i] == 2) {
               playNote(150, 200);
          }
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
     if (countElement() == 4){
          printf("\nError - too many inputs");
          outputEight();
          resetArray(1);
          totalTime = 0;
     } else{
     	letterArray[countElement()] = value;
     }
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
}

void playNote(unsigned int frequency, unsigned int length) {
	// Play the specified frequency for 1 second.
     buzzer_init();
	buzzer_enable(frequency);
	sleep_ms(length);
     buzzer_disable();
     sleep_ms(50);
}

void potential(){
     potValue1 = potValue;
     printf("\nPick a value for the number of seconds to input each letter");
     printf("\nPress right button to confirm time");
     
     // Read the potentiometer (numers between 2-4).
     while (gpio_get(BUTTON_PIN_TWO) == false) {
          potValue1 = potValue;
          potValue = potentiometer_read(2) + 2;
          if (potValue != potValue1){
		     	printf("\nNumber of seconds: %d", potValue);
	     }
          sleep_ms(50);
     }
     printf("\nYou may now input morse code!");
     maxTime = potValue;

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++Angela's if statement++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void angelasIfStatement() {
	//Angela's if statements 
     bool isCorrect = false;
     bool isEmpty = false;
	int count = countElement();

     if (count == 1) {
  	    if (letterArray[0] == 1) {
            isCorrect = true; 
            seven_segment_show(4);
            addToWord('E');
            printf("\nE");
            // calls E
  	    } else if (letterArray[0] == 2) {
            isCorrect = true;
            seven_segment_show(19);
            addToWord('T');
            printf("\nT");
            // calls T
       }
   }
   else if (count == 2) {
       if (letterArray[0] == 1 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(0);
            addToWord('A');
            printf("\nA");
            // calls A
       }
       if (letterArray[0] == 1 && letterArray[1] == 1) {
          isCorrect = true;
		seven_segment_show(8);
          addToWord('I');
          printf("\nI");
          // calls I
       }
       if (letterArray[0] == 2 && letterArray[1] == 2) {
            isCorrect = true;
            seven_segment_show(12);
            addToWord('M');
            printf("\nM");
            // calls M
       }
       if (letterArray[0] == 2 && letterArray[1] == 1) {
            isCorrect = true;
            seven_segment_show(13);
            addToWord('N');
            printf("\nN");
            // calls N
       }
    }
    else if (count == 3){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(3);
            addToWord('D');
            printf("\nD");
            // calls D
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(6);
            addToWord('G');
            printf("\nG");
            // calls G
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(10);
            addToWord('K');
            printf("\nK");
            // calls K
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(14);
            addToWord('O');
            printf("\nO");
            // calls O
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(17);
            addToWord('R');
            printf("\nR");
            // calls R
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1) {
            isCorrect = true;
            seven_segment_show(18);
            addToWord('S');
            printf("\nS");
            // calls S
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(20);
            addToWord('U');
            printf("\nU");
            // calls U
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2) {
            isCorrect = true;
            seven_segment_show(22);
            addToWord('W');
            printf("\nW");
            // calls W
       }
    }
    else if (count == 4){
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(1);
            addToWord('B');
            printf("\nB");
            // calls B
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(2);
            addToWord('C');
            printf("\nC");
            // calls C
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(5);
            addToWord('F');
            printf("\nF");
            // calls F
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(7);
            addToWord('H');
            printf("\nH");
            // calls H
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(9);
            addToWord('J');
            printf("\nJ");
            // calls J
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(11);
            addToWord('L');
            printf("\nL");
            // calls L
       }
       if (letterArray[0] == 1 && letterArray[1] == 2 && letterArray[2] == 2 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(15);
            addToWord('P');
            printf("\nP");
            // calls P
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(16);
            addToWord('Q');
            printf("\nQ");
            // calls Q
       }
       if (letterArray[0] == 1 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(21);
            addToWord('V');
            printf("\nV");
            // calls V
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 1 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(23);
            addToWord('X');
            printf("\nX");
            // calls X
       }
       if (letterArray[0] == 2 && letterArray[1] == 1 && letterArray[2] == 2 && letterArray[3] == 2) {
            isCorrect = true;
            seven_segment_show(24);
            addToWord('Y');
            printf("\nY");
            // calls Y
       }
       if (letterArray[0] == 2 && letterArray[1] == 2 && letterArray[2] == 1 && letterArray[3] == 1) {
            isCorrect = true;
            seven_segment_show(25);
            addToWord('Z');
            printf("\nZ");
            // calls Z
       }
   } else if (letterArray[0] == 0 && letterArray[1] == 0 && letterArray[2] == 0 && letterArray[3] == 0) {
          isCorrect = true;
          isEmpty = true;
          //if nothing is inputted
     } 

     if (isCorrect == false && isEmpty == false) {
       printf("\nError! - invalid input");
       totalTime = 0;
       outputEight();
       showRGB(255,0);
       // displays error
     } else if (isCorrect == true && isEmpty == false) {
       showRGB(0,255);
       totalTime = 0;
       printArray();
     }
	   
     if (letterArray[0] != 0){
          sleep_ms(500); 
          //displays letter for longer if something has been inputted
     }

     resetArray(1);

     if (wordString[3] != 0) {
          printf("\n");
          for (int i = 0; i < 4; i++) {
               printf("%c", wordString[i]);
          }
          resetArray(2);
          printf("\n");
          for (int i = 0; i < 4; i++){     
               playNote(500,100);
               playNote(400,100);
          }
          printf("To continue, press the left button << \n");
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
                    totalTime = 0;
                    printf("\nYou may now input morse code!");
               } else if (gpio_get(BUTTON_PIN_TWO)){
                    p = true;
                    showRGB(255,0);
                    sleep_ms(300);
                    showRGB(0,0);
                    printf("\nProgram terminated");
                    exit(1);
               }
          }
     }
     
     sleep_ms(50);
     showRGB(0,0);
     seven_segment_off();
}
