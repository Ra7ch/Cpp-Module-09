/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 09:34:58 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/06 10:19:08 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>


class RPN {
	private :
		std::stack<int> numbers;
		std::string argument;
		int result;

	public :
		RPN();
		RPN(std::string arguments);

		RPN(const RPN& other);

		RPN& operator=(const RPN& other);


		// Utils.
		bool isOperator(char op) const;

		int calculate(int number1, int number2, char op) const;

		//
		int evaluate ();

        // Geter
        int getResult() const;
		
		~RPN();
};
