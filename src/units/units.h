#ifndef UNITS_H_
#define UNITS_H_

#include <exception>
#include <string>

/// Namespace containing unit conversion functions
namespace units
{
	
	class UnitsException : public std::exception
	{
		public:
			UnitsException(const std::string& message) { this->message = std::string("UnitsException: ") + message; }
		~UnitsException() throw() {}
		virtual const char* what() const throw()
		{
			return message.c_str();
		}
		std::string message;
	};

	/// Initialize unit conversion using the specified data file
	void initialize(const std::string& userfile);
	/// Convert between two units
	double convert(const double value, const std::string& havestr, const std::string& wantstr);
}

#endif /*UNITS_H_*/
