/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:25:29 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 01:32:14 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() { result  = 0; };
RPN::RPN(std::string arguments) : argument(arguments) { result = evaluate(); }

RPN::RPN(const RPN& other) : numbers(other.numbers), argument(other.argument), result(other.result) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other)
	{
		numbers = other.numbers;
		argument = other.argument;
		result = other.result;
	}
	return *this;
}


// Utils.
bool RPN::isOperator(char op) const {
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

int RPN::calculate(int number1, int number2, char op) const {
	switch (op) {
		case '+': return number1 + number2;
		case '-': return number1 - number2;
		case '*': return number1 * number2;
		case '/':
			if (number2 == 0) {
			throw std::runtime_error("Error: division by zero");
			}
			return number1 / number2;
		default: return 0;  // Invalid operator
	}
}

//
int RPN::evaluate () {
	for (int i = 0; argument[i]; i++) {
		char c = argument[i];
		// if (numbers.size() != 2 && isOperator(c))
		// {
		// 	throw std::runtime_error ("Error");
		// }
		if (isdigit(c)) {
			int number = c - '0';
			numbers.push(number);
		}
		else if (isOperator (c)) {
			try {
				if (numbers.size() < 2)
					throw std::runtime_error("Error: Insufficient operands for operator ");
				int number1 = numbers.top();
				numbers.pop();
				int number2 = numbers.top();
				numbers.pop();
				
				int result = calculate(number2, number1, c);
				numbers.push(result);
			} catch (std::exception &e) {
				std::cout << e.what() << "'" << c << "'";
				throw std::runtime_error (".");
			}
		}
		else if (c != ' ') {
			std::string err = "Error: Invalid character ";
			err.push_back(c);
			throw std::runtime_error (err);
		}
	}
	if (numbers.size() != 1)
		throw std::runtime_error("Error: Too much operands for operator ");
	int r = numbers.top();
	numbers.pop();
	return r;
}

int RPN::getResult() const
{
	return result;
}

RPN::~RPN() {}