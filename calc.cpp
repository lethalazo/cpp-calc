/**
Implementation of a basic string evaluator/calculator.
Works on the DMAS principle, supports negative numbers and powers. Parentheses not supported.

@author Arsalan Azmi
@version 1.1, 17th Feb 2019
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Calculator
{
	private:
		string digits = ""; //initialized empty string to store and combine digits of multi-digit numbers
		vector<string> toCalc; //to store the parsed elements of the string i.e operators and numbers
		string input;
		string operators[5] = {"^", "/", "*", "+", "-"};
		int opIndex = 0;

	public:

		/**
		Sets the input string of calculator
		@param the user input expression string
		*/
		void setInput(string calculation){
			input = calculation; 
		}

		/**
		Checks if given char is an operator
		@param character to be evaluated
		@return true or false
		*/
		bool isOperator(char input){
			return input == '+' || input == '-' || input == '*' || input == '/' ||  input == '^';
		}

		/**
		Removes white spaces, parses multi-digit numbers and stores numbers and operators seperately in a vector.
		*/
		void parseInput(){
			input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end()); //to remove whitespaces
			for(unsigned int i = 0; i < input.size(); i++){
				//check if the number is negative
				if(input[i] == '-' && (i == 0 || isOperator(input[i-1]))){
					digits.push_back(input[i]); //push the negative sign as a digit
				}
				else if(isOperator(input[i]))
				{
					toCalc.push_back(digits); //store the combined number before the operator
					toCalc.push_back({1, input[i]}); //store the operator
					digits.clear(); //clear the digit string for the next digit

				}
				else {
					digits.push_back(input[i]); //to store and combine each digit of a number
				}
			}
			toCalc.push_back(digits); //push the combined number after the operator to the vector
		}

		/**
		Applies DMAS (Division then Multiplicatoin then Addition then Subtraction)
		@return evaluated string
		*/
		string applyDMAS(){
			if(opIndex < 5){ //runs until the last operator is evaluated
				for(int i = 0; i < toCalc.size(); i++){
					//finds the operator using priority index provided (implemented in order to prioritize operators)
					if(toCalc.at(i) == operators[opIndex]){
						if (toCalc.at(i) == "^")//the <0x01> is used after several testcases to avoid comparison errors
						{
							//converts the previous and succeding element to a double, evaluates them and replaces the next element after converting it back to a string
							toCalc.at(i+1) = to_string(pow(stod(toCalc.at(i-1)), stod(toCalc.at(i+1))));
						}
						else if (toCalc.at(i) == "+")
						{
							toCalc.at(i+1) = to_string(stod(toCalc.at(i-1)) + stod(toCalc.at(i+1)));
						}
						else if (toCalc.at(i) == "-")
						{
							toCalc.at(i+1) =  to_string(stod(toCalc.at(i-1)) - stod(toCalc.at(i+1)));
						}
						else if (toCalc.at(i) == "/")
						{
							toCalc.at(i+1) =  to_string(stod(toCalc.at(i-1)) / stod(toCalc.at(i+1)));
						}
						else if (toCalc.at(i) == "*")
						{
							toCalc.at(i+1) =  to_string(stod(toCalc.at(i-1)) * stod(toCalc.at(i+1)));
						}
						toCalc.erase(toCalc.begin()+i); //erases the current and previous strings so that only the evluated result is left
						toCalc.erase(toCalc.begin()+(i-1));
						i--; //decrement the loop counter to compensate the vector size
					}
				}
				opIndex++; //increments the operator priority index and recurs
				applyDMAS();
			}
			return toCalc.at(0); //returns the evaluated result
		}

		/**
		Returns the result of the DMAS operation
		@return Evaluated string
		*/
		string getCalc(){
			return applyDMAS();
		}
};

int main()
{
	string userInput; //initialize string to store user input
	
	cout << "Welcome to the basic c++ calculator.\n\nPlease enter the expression:\n";
	getline(cin,userInput); //gets user input i.e the expression string
	Calculator basicCalc;
	basicCalc.setInput(userInput); //set calculator input as the user input
	basicCalc.parseInput(); //parse the input

	try {
		//try to get the calculation and print the result
		cout << "= " + basicCalc.getCalc() + "\n";
	} catch(std::invalid_argument) {
		//print an error statement if the input is invalid (i.e parentheses used)
		cout << "\nInvalid input!\nonly '+', '-', '/' and '*' operations\nwithout parentheses supported.\n\n";
	}
}