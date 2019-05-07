#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

using namespace std;

class Address {
private:
	string street; // street name
	int doorNumber; // dor number
	string floor; // floor number ("-" is not applicable)
	string zipCode; // postal code
	string location; // site

public:
	Address();
	Address(string street, int doorNumber, string floor, string postalCode, string location);

	// metodos GET
	string getStreet() const;
	int getDoorNumber() const;
	string getFloor() const;
	string getZipCode() const;
	string getLocation() const;

	// metodos SET
	void setStreet(string street);
	void setDoorNumber(int doorNumber);
	void setFloor(string floor);
	void setZipCode(string postalCode);
	void setLocation(string  location);

	// outros
	friend ostream& operator<<(ostream& out, const Address & address);
	//-----------------
	//NOTA: Adicionar como friend???
	friend Address address_handler(string line);
	//---------------
};
//NOTA: Não sei se é preciso ter o tokenize aqui e no address.h
void tokenize(string const &str, const char delim, vector<string> &out);


