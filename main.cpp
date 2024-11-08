#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>

using namespace std;


//GLOBAL VARIABLE

/* Gamestate:
   0 = menu
   1 = new game
   2 = main gameplay
   3 = Quit
 */
int gameState;
int night = 1;



//enableRawMode to change terminal settings, use disableRawMode to restore them.
void enableRawMode();
void disableRawMode();

//Read key press from stdin, and return it
char readKey();

//Main Menu for the game
void mainmenu();

int main(){
  enableRawMode();
  gameState = 0;

  if (gameState == 0){
    mainmenu();
  }

  if (gameState == 3){
    disableRawMode();
    return 0;
  }

}





void mainmenu(){
  int selection = 0;
  string menuOptions[] = {"New Game", "Continue", "Quit"};

  while (gameState == 0){
    printf("\033[H\033[J"); //clears the screen
    cout << "Five" << endl << "Nights" << endl << "in" << endl <<  "Terminal" << endl << endl;
    for (int i = 0; i < 3; i++){
      if (i == selection){
	if (i == 1){
	  cout << "> " << menuOptions[i] << " | Night: " << night << endl;
	} else {
	cout << "> " <<menuOptions[i] <<  endl;
	}
      } else {
	cout << menuOptions[i] << endl;
      }
    }
  char key = readKey();

  if (key == '\033'){ //check for escape sequence (arrow keys)
    readKey(); //skip [ char by reading it
    key = readKey(); //actual arrow key
    switch (key){ //Updates selection according to key
    case 'A': //Up arrow
      selection = (selection > 0) ? selection - 1 : 0; //if else statement: condition ? true : false
      break;
    case 'B': //Down arrow
      selection = (selection < 2) ? selection + 1 : 2; //read case A
      break;
    }
  } else if (key == '\n'){ //Enter key
 

    if (selection == 2){
      cout << endl << "See you later :)" << endl;
      gameState = 3;
    }
  }
  }
}







char readKey(){
  char ch;
  read(STDIN_FILENO, &ch, 1); //reads one byte from terminal input and stores in ch.
  return ch;
}



void enableRawMode(){
  struct termios term; // holds terminal settings
  tcgetattr(STDIN_FILENO, &term); //retrieves current terminal settings for stdin
  term.c_lflag &= ~(ICANON | ECHO); //Disables canonical mode and echo
  /*Canonical Mode: terminal waits for newline (entery key) before sending input to program.
    Disabling allows reading of each key AS it is pressed
    Echo: terminal automatically prints each character typed to the screen. disable this to  
    handle display manually*/
  term.c_cc[VMIN] = 1; //Stes min num of bytes to read at once. made to be one to read one at a time
  term.c_cc[VTIME] = 0; //disables timeout. set to 0 to ensure no specific wait time for input
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); //Apply new terminal settings immediately
}


void disableRawMode(){
  struct termios term;
  tcgetattr(STDIN_FILENO, &term); //Read enableRawMode function
  term.c_lflag |= (ICANON | ECHO); //Enable Canon mode and echo
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term); //Apply restored terminal settings immediately
}
