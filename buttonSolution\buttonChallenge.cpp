#include <stdio.h>
#include <stdlib.h>  
#include <cstring>
#include <string>
#include <iostream>
// High level Stack implementation that handles data of any type, will hold operands and operators
// Note: implemented class within main file only for a quick implementation, ease of developing, and ease of testing
class Stack {
public:
	char *data = NULL;
	int size, top, itemSize;
	// Allocate 100 items of any type to Stack and keep track of the size and the top of Stack
	// itemSize is how we are able to handle any data type
	Stack(int itemSize) {
		top = 0;
		size = 100 * itemSize;
		this->itemSize = itemSize;
		data = (char*)malloc(size);
	};
	// Prevent memory leaks
	~Stack() {
		if (data != NULL)
			free(data);
	}
	// Push an item to the top of stack and allocate more memory if top is reached
	void push(void *item) {
		if (top > size) {
			size <<= 1;
			data = (char*)realloc(data, size);
			printf("Size Of Stack Doubled\n");
		}
		memcpy(data + top, item, itemSize);
		top += itemSize;
	};
	// Pop from the stack to item and decrement top, also print error and return false if pop
	// not possible for easy error handling
	bool pop(void *item) {
		if (top <= 0) {
			printf("Invalid Pop\n");
			return false;
		}
		top -= itemSize;
		memcpy(item, data + top, itemSize);
		return true;
	};
	// Return true if top is 0, otherwise return false
	bool isEmpty(void) {
		if (top == 0)
			return true;
		return false;
	}
	// Print Stack to screen in order items were pushed
	// If my itemSize is 4, meaning it is an int Stack, then print out using %d, otherwise 
	// print out %c since it is a char Stack that holds operators
	void print(void) {
		for (int i = top - itemSize; i >= 0; i -= itemSize) {
			if (itemSize == 4) {
				printf("%d ", data[i]);
			} else {
				printf("%c ", data[i]);
			}
		}
		printf("\n");
	}
};

using namespace std;
// Fill up Stacks using the expression, handles + and - operands and positive and negative
//  number (ints, floats, etc.) types in O(n) time
void fillUpStacks(Stack &operandStack, Stack &operatorStack, string expression) {
	// Iterate from end of expression by 2 to store data correctly to perform operations
	for (int i = expression.size() - 1; i >= 0; i -= 2) {
		// If character is an operator, push it to operatorStack and end iteration
		if (expression[i] == '+' || expression[i] == '-') {
			operatorStack.push(&expression[i]);
			continue;
		}
		// Iterate through string until a space is found
		int j = i;
		while (j >= 0 && expression[j] != ' ')
			j--;
		// Get the substring which represents the number, including negative numbers
		string number = expression.substr(j, i - j + 1);
		// Convert string number to int num using atoi and push onto operandStack
		int num = atoi(number.c_str());
		operandStack.push(&num);
		// Update i to skip the number
		i = j + 1;
	}
}
// Pop from operatorStack and perform operation on top two items in operandStack and push back
// to operandStack until there are no more operators in O(operations) time
int performCalculationsOnStacks(Stack &operandStack, Stack &operatorStack) {
	// Temporary operands, result, and operator
	char tempOperator;
	int tempResult, operand1, operand2;
	// Perform operations until no more operators
	while (!operatorStack.isEmpty()) {
		// Pop top operator and top two operands
		operatorStack.pop(&tempOperator);
		operandStack.pop(&operand1);
		operandStack.pop(&operand2);
		// If operator is +, add operands and store into tempResult
		if (tempOperator == '+')
			tempResult = operand1 + operand2;
		// Else if operator is '-', subtract operand2 from operand1
		else if(tempOperator == '-')
			tempResult = operand1 - operand2;
		// Push tempResult back onto operandStack
		operandStack.push(&tempResult);
		// Un-comment code below if you would like to see the Stacks as we perform operations
		// operatorStack.print();
		// operandStack.print();
	}
	// Return tempResult, which is the final result of all of the operations
	return tempResult;
}
// Take in expression and return result of operations
int solveExpression(string expression) {
	// Create operandStack to hold ints and operatorStack to hold chars
	Stack operandStack(sizeof(int));
	Stack operatorStack(sizeof(char));
	// Call fillUpStacks to fill Stacks with proper values
	fillUpStacks(operandStack, operatorStack, expression);
	// Calculate result from performCalculationsOnStacks and return result
	int result = performCalculationsOnStacks(operandStack, operatorStack);
	return result;
}
// Test result of expression with expected result
void testAlgorithm(string expression, int result) {
	if (solveExpression(expression) == result)
		cout << "Test Passed\n\n";
	else 
		cout << "Test Failed\n\n";
}

int main() {
	cout << "Howdy!\n\n";
	cout << "In a high level description, my algorithm uses 2 different Stack instances to hold operators and operands and then performs all of the operations that have been stored.\n";
	cout << "Below are some test cases for my algorithm.\n\n";
	
	string expression1 = "- 5 + -3 - 2 - 3 + -4 - -3 4";
	int expression1Answer = 5 - (-3) + 2 - 3 - (-4) + (-3) - 4;
	cout << "The expression '" << expression1 << "' should be " << expression1Answer << "\n";
	testAlgorithm(expression1,expression1Answer);

	string expression2 = "- 10 - -14 - 1 + 35 + 40 4";
	int expression2Answer = 10 - (-14) - 1 - 35 + 40 + 4;
	cout << "The expression '" << expression2 << "' should be " << expression2Answer << "\n";
	testAlgorithm(expression2,expression2Answer);
	
	string expression3 = "+ 1 + 2 3";
	int expression3Answer = 1 + 2 + 3;
	cout << "The expression '" << expression3 << "' should be " << expression3Answer << "\n";
	testAlgorithm(expression3,expression3Answer);

	string expression4 = "- 1 0";
	int expression4Answer = 1 - 0;
	cout << "The expression '" << expression4 << "' should be " << expression4Answer << "\n";
	testAlgorithm(expression4,expression4Answer);

	string expression5 = "+ 983 - 142 12";
	int expression5Answer = 983 + 142 - 12;
	cout << "The expression '" << expression5 << "' should be " << expression5Answer << "\n";
	testAlgorithm(expression5,expression5Answer);

	cout << "Looking forward to hearing from Button soon.\nHave a great day!\n";
	
	return 0;
}