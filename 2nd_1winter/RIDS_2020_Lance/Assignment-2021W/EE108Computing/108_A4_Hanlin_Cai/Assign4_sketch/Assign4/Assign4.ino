//EE108_Assignment4_AverageDirection
//20122161
//Email:HANLIN.CAI.2021@MUMAIL.IE
//Hanlin Cai


/**
 * This is an example of using serial input from the console
 *
 * The console window has two dropdown boxes in the bottom right.
 * The first of these controls the line ending and should be changed
 * to "Newline". This will ensure that as soon as you hit the enter key
 * any text you enter in the console gets sent directly to the arduino.
 *
 * You enter text in the edit box at the top of the console window.
 *
 * In this sketch, you can type any alphabetic text you want.
 *
 * When you hit enter on the computer keyboard or press the send button,
 * the text you entered gets sent to the arduino.
 *
 * It is processd character by character. Anynon-alphabetic text (e.g.
 * numbers or punctuation) is skipped/ignored. The accepted characters
 * are then printed.
 *
 * Characters are not added to a buffer so there is no limit (other
 * than that of Arduino's serial read buffer) to the number of characters
 * that can be processed
 */



#include <ee108_switches.h>
#include <ee108_printf.h>
#include <ee108_constants.h>
#include <ee108.h>



//initialization parameter
char q[1000];
int head = 0, tail = 0, posx = 0, posy = 0;
int xx[26], yy[26];

void setup() {
    // set up serial
    Serial.begin(9600);
    Serial.println("\n\nA4_ExampleSerialEchoNoBuffer starting.");
    Serial.println("[Ensure that you have line ending to newline on console window]\n");
    
    xx['j' - 'a'] = -1;
    xx['k' - 'a'] = 0;
    xx['l' - 'a'] = 1;
    xx['i' - 'a'] = 0;
    yy['j' - 'a'] = 0;
    yy['k' - 'a'] = -1;
    yy['l' - 'a'] = 0;
    yy['i' - 'a'] = 1;
}

void loop() {
    
    Serial.println("\nType direction characters: J, K, L, or I (upper or lower case) and hit return");

    // we don't limit the number of characters read in here, so there is
    // no condition to evaluate here
    
    //initialization parameter
    char input[1000];
    int len = 0;
    while (true) {
        char c;

        // wait until at least one character has been entered
        while (Serial.available() == 0)
            continue;

        // OK, we now have at least 1 character
        c = Serial.read(); // read 1 character

        // a newline or space indicates the end of the word
        // so we'll break out to process it
        if ((c == '\n') || (c == '\r') || (c ==  isspace(c))) {
            break;
        }
        input[len++] = c;
    }

    // once we get here, we encountered a newline or space and broke out
    // of the loop. Display a newline and then we're ready to do it all again
    
    input[len] = '\0';
    Serial.print("Received: ");
    Serial.println(input);

    for (int i = 0; input[i]; i++) {
        char temp = input[i];
        if (temp < 'a') {
            temp += 'a' - 'A';
        }
        if (temp == 'j' || temp == 'k' || temp == 'l' || temp == 'i') {
            if (tail - head >= 8) {
                posx -= xx[q[head] - 'a'];
                posy -= yy[q[head] - 'a'];
                head++;
            }
            posx += xx[temp - 'a'];
            posy += yy[temp - 'a'];
            q[tail++] = temp;
        }
    }
    Serial.print("Buffer contents: ");
    Serial.println(q + head);

    Serial.print("resultant: x=");
    Serial.print(posx);
    Serial.print(", y=");
    Serial.println(posy);

    Serial.print("direction: ");
    if (posx < 0) {
        Serial.print("LHS");
    } else {
        Serial.print("RHS");
    }
    Serial.print(", 1000*slope=");
    Serial.print(1000 * posy / posx);
    Serial.print(", compass=");
    if (posx == 0 && posy > 0) Serial.println("North");
    else if (posx == 0 && posy < 0) Serial.println("South");
    else if (posx > 0 && posy == 0) Serial.println("East");
    else if (posx < 0 && posy == 0) Serial.println("West");
    else if (posx > 0 && posy > 0) Serial.println("NorthEast");
    else if (posx > 0 && posy < 0) Serial.println("SouthEast");
    else if (posx < 0 && posy > 0) Serial.println("NorthWest");
    else if (posx < 0 && posy < 0) Serial.println("SouthWest");


    // no need for any superloop delay since we wait for characters to
    // be received in the while loop above
}
