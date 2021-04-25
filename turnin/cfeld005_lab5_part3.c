/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {init, p1, w1, p2, w2, p3, w3} state;

int main(void) {

    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    unsigned char tmpA = 0x00, tmpB = 0x00;
    state = init;
    while (1) {
    	tmpA = ~PINA;
	switch(state){
	    case init:
		if (tmpA) {
		    state = p1;
		}
		break;
	    case p1:
                if (!tmpA){ 
                    state = w1; 
                }
		break;
	    case w1:
		if (tmpA){
		    state = p2;
		}
		break;
	    case p2:
                if (!tmpA){ 
                    state = w2; 
                }
		break;
            case w2:
                if (tmpA){
                    state = p3;
                }
		break;
            case p3:
                if (!tmpA){ 
                    state = w3; 
                }
                break;
            case w3:
                if (tmpA){ 
                    state = p1; 
                }
                break;
	    default:
		state = init;
		break;
	}

	switch(state){
	    case p1:
		tmpB = 0x24;
		break;
	    case p2:
		tmpB = 0x12;
		break;
	    case p3:
		tmpB = 0x09;
		break;
	    default:
		break;
	}
    PORTB = tmpB;
    }
    return 1;
}
