#include "pch.h"
#include <iostream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/serialization.hpp"

class SerializableTest
{
public:
	int a;
	std::string str;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & a;
		ar & str;
	}
};

int main(int argc, char** argv)
{
	std::cout << "This is the server!\n" << std::endl;

	// Test the Boost library before creating a window.
	// This requires that boost::serialization was fixed manually.
	boost::archive::text_oarchive archive(std::cout);
	SerializableTest st;
	st.a = 25;
	st.str = "Hello, Tina!";
	archive & st;

	return 0;
}