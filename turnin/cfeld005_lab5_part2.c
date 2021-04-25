/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {init, press1, press2, wait1, wait2, wait, reset} state;

int main(void) {

    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char tmpA = 0x00;
    short tmpC = 0x07;
    state = init;
    while (1) {
    	tmpA = PINA;
	switch(state){
	    case init:
		if (!tmpA){
		    state = wait;
		} else if (tmpA == 0x01) {
		    state = press1;
		} else if (tmpA == 0x02) {
		    state = press2;
		} else {
		    state = reset;
		}
		break;
	    case press1:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = wait1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
		break;
	    case wait1:
		if (!tmpA){
		    state = wait;
		} else if (tmpA == 0x01){
		    state = wait1;
		} else if (tmpA == 0x02){
		    state = press2;
		} else {
		    state = reset;
		}
	    case press2:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = wait2;
                } else {
                    state = reset;
                }
		break;
            case wait2:
                if (!tmpA){
                    state = wait;
                } else if (tmpA == 0x01){
                    state = press1;
                } else if (tmpA == 0x02){
                    state = wait2;
                } else {
                    state = reset;
                }
            case wait:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
                break;
            case reset:
                if (!tmpA){ 
                    state = wait; 
                } else if (tmpA == 0x01) {
                    state = press1;
                } else if (tmpA == 0x02) {
                    state = press2;
                } else {
                    state = reset;
                }
                break;
	    default:
		state = reset;
		break;
	}

	switch(state){
	    case press1:
		if (tmpC < 9){
		    tmpC += 1;
		}
		break;
	    case press2:
		if (tmpC > 0){
		    tmpC -= 1;
		}
		break;
	    case reset:
		tmpC = 0x00;
		break;
	    default:
		break;
	}
    PORTC = tmpC;
    }
    return 1;
}
