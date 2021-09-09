//CS311 Yoshii
//INSTRUCTION:
//Look for ** to complete this program (Use control-S)
//The output should match my hw1stackDemo.out 

//=========================================================
//HW#: HW1P1 stack application (post-fix evaluation)
//Your name: Olaf Zielinski
//Complier:  g++
//File type: client program client1.cpp
//===========================================================

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "stack.h"

//Purpose of the program: evaluating expressions written in post-fix notation
//assuming that expressions are no longer than 12 characters.
//Algorithm: using a stack, the program stores integers in a stack, 
//and when encounters an expression sign, after validation, perfoms the calculation
//on the last two integers of the stack (the first integer is the second operand)
//in case there is a problem, the algorithm provides user with an error message
//stating what is wrong. 

int main()
{
  stack postfixstack;  // integer stack
  string expression;   // user entered expression
  
  cout << "type a postfix expression: " ;
  cin >> expression;
  
  int i = 0;  // character position within expression
  char item;  // one char out of the expression
  
  int box1;  // receive things from pop
  int box2;  // receive things from pop
  
  while (expression[i] != '\0')
    {
     try
	 // ** do all the steps in the algorithm given in Notes-1
       {
	 item = expression[i];  // current char 

	 if ((item <= '9') && (item >= '0')){ //check if it's a number (operand)
	     item = int(item)-48; // convert to integer and store in item
	     postfixstack.push(item);} //push into the stack.

	 //if it's not a number, check if it's a valid operand */+/-, and if so
	 else if((item == '*') || (item == '+') || (item == '-')){ 
	   postfixstack.pop(box1); postfixstack.pop(box2); // get values from stack

	   //perform the operations and store resut in a temp. Box2 is the 2nd operand.
	   int tmp; //temporary variable to store the result
	   if(item == '*') tmp = box2 * box1; //multiplication
	   else if(item == '+') tmp = box2 + box1; //addiction 
	   else tmp = box2 - box1; //subtraction
 
	   postfixstack.push(tmp); //push the result back to the stack
	 }
	 else cout << "This is an invalid input." << endl; 
	 
       } // this closes try
      // Catch exceptions and report problems and quit the program now (exit(1)). 
      // Error messages describe what is wrong with the expression.
      catch (stack::Overflow) 
	{ cerr << "An Error has occured. There is too many characters.\n"; exit(1); }
      catch (stack::Underflow)
	{ cerr << "An Error has occured. There is too few characters.\n"; exit(1); }
      catch (char const* errormsg ) // for invalid item case
	{ cerr << "An Error has occured. Invalid entry.\n"; exit(1); }

      // go back to the loop after incrementing i
     i++;
    }// end of while
  
 // After the loop successfully completes: 
 // Pop the result and show it.
  postfixstack.pop(box1);
  cout << "The result: " <<  box1 << endl;
 // If anything is left on the stack, an incomplete expression 
 // was found so inform the user.
     if(!postfixstack.isEmpty()) cout << ",but the expression is incomplete." << endl;

}// end of the program
