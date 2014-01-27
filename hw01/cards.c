/*
Evan Dorsky

Software Systems Assignment 1
//================================--------------------------------
cards.c

This program prompts the user to input the name of a card
and uses the card value to perform some simple card counting.
\\================================--------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

/* 	Prompts the user for input and puts the reply in the given buffer.
	
	If user input is longer than two characters it breaks.

	name: buffer where the result is stored
*/
void get_name(char* name) {
	puts("Enter the card_name: ");
	scanf("%2s", name);
}

/*	Increments the counter based on the given card value.

	cnt: The pointer to the counter that will be incremented
	value: The value of the card
*/
void new_count(int* cnt, int value) {
	if ((value > 2) && (value < 7))
		(*cnt)++;
	else if (value == 10)
		(*cnt)--;
}

/*	Returns the corresponding numerical value for the given card name.

	name: A character representing the name of the card
*/
int card_value(char name) {
	int retVal = 0;
	switch(name) {
	case 'K':
	case 'Q':
	case 'J':
		retVal = 10;
		break;
	case 'A':
		retVal = 11;
		break;
	case 'X':
		break;
	default:
		retVal = atoi(&name);
		if ((retVal < 1) || (retVal > 10))
			puts("I don't understand that value!");
	}
	return retVal;
}

int main() {
	char card_name[3];
	int count = 0, val = 0;
	while (card_name[0] != 'X') {
		get_name(card_name);
		val = card_value(card_name[0]);

		new_count(&count, val);
		printf("Current count: %i\n", count);
	}
	return 0;
}
