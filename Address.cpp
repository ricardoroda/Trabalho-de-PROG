#include "Address.h"

  // ADDING ADDRESS INFO  to a new class object

//function that sets the adress object elements has empty/zero
Address::Address()
{
	street = ""; 
	doorNumber = 0; 
	floor = ""; // NOTA: o prof indicou: "floor number ("-" is not applicable)"
	zipCode = ""; 
	location = ""; 
}

//function that sets its parameters has the class object elements
Address::Address(string street, int doorNumber, string floor, string zipCode, string location) : street(street), doorNumber(doorNumber), floor(floor), zipCode(zipCode), location(location)
{
	this->street = street;
	this->doorNumber = doorNumber;
	this->floor = floor; // NOTA: o prof indicou: "floor number ("-" is not applicable)"
	this->zipCode = zipCode;
	this->location = location;
}

// metodos GET - functions that return the class object elements

string Address::getStreet() const
{
	return street;
}

int Address::getDoorNumber() const
{

	return doorNumber;
}

string Address::getFloor() const
{

	return floor;
}

string Address::getZipCode() const
{

	return zipCode;
}

string Address::getLocation() const
{

	return location;
}

// metodos SET - function that sets its parameter has the class object element

void Address::setStreet(string street)
{

	this->street = street;
}

void Address::setDoorNumber(int doorNumber)
{

	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor)
{

	this->floor = floor;
}

void Address::setZipCode(string postalCode)
{

	this->zipCode = zipCode;
}

void Address::setLocation(string location)
{

	this->location = location;
}

//other functions

//fill a string vector with informations separated by a certain delimiter
void tokenize(string const &str, const char delim, vector<string> &out)
{
	stringstream ss(str);
	string s;
	while (getline(ss, s, delim))
	{
		out.push_back(s);
	}
}

//function that process my addresses removing the '/', making a plan line with spaces, so i can use it with my stringstream
Address address_handler(string line)
{
	Address address;
	vector<string> addres_vec;
	tokenize(line, '/', addres_vec);
	for (int i = 0; i < addres_vec.size(); i++)
	{
		if (i == 0)
		{
			address.setStreet(addres_vec.at(0));
		}
		else if (i == 1)
		{
			int number;
			istringstream teste(addres_vec.at(1));
			teste >> number;
			address.setDoorNumber(number);
		}
		else if (i == 2)
		{
			address.setFloor(addres_vec.at(2));
		}
		else if (i == 3)
		{
			address.setZipCode(addres_vec.at(3));
		}
		else if (i == 4)
		{
			address.setLocation(addres_vec.at(4));
		}
	}
	return address;
}


/*********************************
 * Mostrar Address
 ********************************/

 // displayes an address in a nice format
ostream &operator<<(ostream &out, const Address &address)
{
	out << "Rua: " << Address::getStreet() << endl;
	out << "Nº porta/prédio: " << Address::getDoorNumber << endl;
	out << "Andar: " << Address::getFloor << endl;
	out << "Código postal: " << Address::getZipCode << endl;
	out << "Localidade: " << Address::getLocation << endl;
	return out;
}
//--------------------------------------------------------------------
//NOTA: versão antiga da mesma operação anterior SUBSTITUIR
string return_addres(Address endereco) {
	stringstream ss;
	string address_output;
	ss << "Rua: " << endereco.rua_nome << endl;
	ss << "Nº porta/prédio: " << endereco.porta_number << endl;
	ss << "Andar: " << endereco.andar_number << endl;
	ss << "Código postal: " << endereco.zip_code << endl;
	ss << "Localidade: " << endereco.localidade << endl;
	address_output = ss.str();
	return address_output;
}
//--------------------------------------------------------------------