/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:17:45 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 00:41:12 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iomanip>

std::string trim(const std::string& str);

struct BitcoinExchange {
	private:
		std::map<std::string, double> dataBase;

	public:
		BitcoinExchange();

		BitcoinExchange(const BitcoinExchange& other);

		BitcoinExchange& operator= (const BitcoinExchange& other);


		void BaseFilling();

		void ReadInput(const std::string& inputFile);

		bool validateDate(const std::string& date);

		~BitcoinExchange ();
};