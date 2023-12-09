/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:40:25 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/08 03:58:01 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"

int main (int argc, char **argv) {
    if (argc > 2 || argc < 2)
        return (std::cerr << "Error: Input count is wrong" << std::endl, 0);
    
   // std::istringstream ss(argv[1]);
    // std::string date;
    // double inputValue;

	// const char* datetimeString0 = "2011-01-03";
	// const char* datetimeString1 = "2011-01-04";
	// const char* datetimeString2 = "2011-01-05";
    // const char* format = "%d-%d-%d";
    //time_t result = parseDateTime(datetimeString0, format);

    // std::cout << result << std::endl;
    // std::cout << parseDateTime(datetimeString1, format) << std::endl;
    // std::cout << parseDateTime(datetimeString2, format) << std::endl;
    
	// if (ss >> date >> inputValue) {
	// 	std::cout << date << ", " << inputValue << std::endl;
	// }
	// else
	// 	std::cout << "Error" << std::endl;
    
    BitcoinExchange k;

    k.BaseFilling();
    k.ReadInput(argv[1]); 
}