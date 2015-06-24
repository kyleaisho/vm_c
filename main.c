/*
	A virtual machine built in C
	By Kyle Aisho
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 256
bool running = true;

// ALU values
int valA = 0;
int valB = 0;

// Program Stack
int stack[STACK_SIZE];

// Stack pointer
int sp = -1;

// Program counter
int ip = 0;


typedef enum {
	PSH,
	POP,
	ADD,
	SET,
	HLT,	
} InstructionSet;

typedef enum
{
	A, B, C, D, E, F, PC, SP, NUM_OF_REGISTERS
} Registers;

// Test program
const int program [] = {
	PSH, 6,
	PSH, 2,
	ADD,
	POP,
	HLT
};


int fetch() {
	return program[ip];
}

void eval(int cur_ins) {
	switch (cur_ins) {
		case HLT:
			printf("Halting...\n");
			running = false;
			break;
		case PSH:
			stack[++sp] = program[++ip];
			printf("Pushing %d\n", program[ip]);
			break;
		case POP:
			printf("Popped %d\n", stack[sp--]);
			break;
		case ADD:
			valA = stack[sp--];
			valB = stack[sp--];
			stack[++sp] = valA + valB;
			break;
	}
}

int main() {
	while (running) {
		int cur_ins = fetch();
		if (cur_ins == HLT) running = false;
		ip++;
	}
	return 0;
}

