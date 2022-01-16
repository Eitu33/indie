/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <string>

class ServerError : public std::exception
{
      public:
		~ServerError() = default;
		ServerError(std::string function, std::string message)
		{
			_function = function;
			_message = message;
		};
		char const *what() const noexcept
		{
			return _message.c_str();
		};
		char const *where() const noexcept
		{
			return _function.c_str();
		};

      private:
		std::string _function;
		std::string _message;
};

#endif /* !ERRORS_HPP_ */
