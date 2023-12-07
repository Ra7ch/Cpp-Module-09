/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:25:12 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 00:58:04 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No expression provided." << std::endl;
        return 1;
    }

	try {
		std::string expression(argv[1]);
		RPN rpn(expression);

		int r = rpn.getResult();
		std::cout << r << std::endl;
	//	int result = rpn.evaluate();
	//	std::cout << "result = " << result << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

    return 0;
}