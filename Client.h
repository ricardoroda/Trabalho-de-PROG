#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<Packet> packets; // vector to store client's packets bought
  unsigned  totalPurchased; // total value spent by the client

 public:
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet> & packets, unsigned totalPurchased);  // client read from file

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet> getPacketList() const;
  unsigned getTotalPurchased() const;
  
  // SET methods
  
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(vector<Packet> & packets);
  unsigned setTotalPurchased(unsigned totalPurchased);
  
  // other methods

  friend ostream& operator<<(ostream& out, const Client & client);
};

//FUNÇOES ANTIGAS
//Function responsible to handle with my Clients data to the file of my clients.
Cliente client_handler(vector<string> clients) {
	Cliente client;
	client.nome = clients.at(0);
	client.nif = clients.at(1);
	istringstream teste(clients.at(2));
	teste >> client.number_agregado;
	client.morada = address_handler(clients.at(3));
	client.pacotes = clients.at(4);
	client.total_compras = count(clients.at(4).begin(), clients.at(4).end(), ';') + 1;
	return client;
}
//Função que me cria um vetor com todos os clientes presentes no texto;
vector<Cliente> client_data(string tmp_client_data) {
	cout << "i started" << endl;
	vector<Cliente> client_info;
	ifstream file;
	string lines;
	vector<string> clients_lines;
	file.open(tmp_client_data);
	while (getline(file, lines, '\n')) {
		if (lines == "::::::::::") {
			client_info.push_back(client_handler(clients_lines));
			clients_lines.clear();
		}
		else {
			clients_lines.push_back(lines);
		}
	}
	client_info.push_back(client_handler(clients_lines));
	file.close();
	cout << "im working";
	return client_info;
}
//it will automate de clients_question job
vector<string> clientQuestionHandler(vector<string> vec) {
	string line;
	vector<string> new_client;
	cout << "::::::::::" << endl;
	cin.ignore();
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec.at(i);
		getline(cin, line);
		new_client.push_back(line);
	}
	cout << "::::::::::" << endl;
	return new_client;
}
//creates a new vector<string> with the data needed to create my new client
vector<string> clients_questions() {
	string line;
	vector<string> nClient_questions = { "Client name: ","NIF number: ","Nº family members: ","Address: ","Package list: " };
	cout << endl;
	vector<string> new_client = clientQuestionHandler(nClient_questions);
	return new_client;
}

//Add new client
vector<Cliente> add_client(vector<Cliente> &vec) {
	vector<string> new_client = clients_questions();
	Cliente aux = client_handler(new_client);
	vec.push_back(aux);
	return vec;
}
//remove a client (remove all data of that client)
void remove_client(vector<Cliente> &vec) {
	string nif;
	cout << "What's the nif of the client you want to remove?" << endl;
	cin >> nif;
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i).nif == nif) {
			auto it = vec.begin() + i;
			rotate(it, it + 1, vec.end());
			cout << "The client with the NIF: " << vec.back().nif << " it's being deleted! " << endl;
			vec.pop_back();
		}
	}
}
//Vector of Integers with the ID of the packages that a client have bought, the idea here is to be able to modify each element of this vector
void clients_packs(string line, vector<int> &aux) {
	line = regex_replace(line, regex(";"), " ");
	istringstream test(line);
	int i;
	while (test >> i) {
		aux.push_back(i);
	}
}
//update/change the information of a client;
void update_client(vector<Cliente> &vec) {
	print_all_clients(vec);
	int op;
	string line;
	string nif;
	cout << "What's the nif of the client you want to update? " << endl;
	cin >> nif;
	cin.ignore();
	vector<string> menu = { "Name","NIF","Family Number","Address","Package" };
	for (size_t i = 0; i < vec.size(); i++) {
		if (vec.at(i).nif == nif) {
			op = readOptions(menu);
			if (op == 1) {
				cout << "New Name: ";
				cin.ignore();
				getline(cin, line);
				vec.at(i).nome = line;
			}
			if (op == 2) {
				cout << "New NIF: ";
				cin.ignore();
				getline(cin, line);
				vec.at(i).nif = line;
			}
			if (op == 3) {
				cout << "New family number: ";
				cin.ignore();
				getline(cin, line);
				istringstream transform(line);
				transform >> vec.at(i).number_agregado;
			}
			if (op == 4) {
				cout << "New address: ";
				cin.ignore();
				getline(cin, line);
				vec.at(i).morada = address_handler(line);
			}
			if (op == 5) {
				cout << "New package: ";
				cin.ignore();
				getline(cin, line);
				vec.at(i).pacotes = line;
			}
		}
	}
}
//print a specifi client
void printClient(vector<Cliente> &vec) {
	cout << ":::::Please provide us with the client Name or NIF:::::";
	cout << "Wich information suits you?  ";
	vector<string> menu = { "Name","NIF" };
	int op = readOptions(menu);
	string line;
	if (op == 1) {
		cout << "Whats the name of the client?" << endl;
		cin.ignore();
		getline(cin, line);
		for (size_t i = 0; i < vec.size(); i++) {
			if (line == vec.at(i).nome) {
				cout << "::::::::::" << endl;
				cout << "Name: " << vec.at(i).nome << endl;
				cout << "NIF: " << vec.at(i).nif << endl;
				cout << "Family members: " << vec.at(i).number_agregado << endl;
				cout << "----Address--- \n" << return_addres(vec.at(i).morada);
				cout << "Packages: " << vec.at(i).pacotes << endl;
			}
		}
	}
	if (op == 2) {
		cin.ignore();
		cout << "Whats the NIF of the client?" << endl;
		getline(cin, line);
		for (size_t i = 0; i < vec.size(); i++) {
			if (line == vec.at(i).nif) {
				cout << "::::::::::" << endl;
				cout << "Name: " << vec.at(i).nome << endl;
				cout << "NIF: " << vec.at(i).nif << endl;
				cout << "Family members: " << vec.at(i).number_agregado << endl;
				cout << "----Address--- \n" << return_addres(vec.at(i).morada);
				cout << "Packages: " << vec.at(i).pacotes << endl;
			}
		}
	}
}
//Print all my clients.
void print_all_clients(vector<Cliente> &vec) {
	cout << ":::::The current clients in our database are:::::";
	for (size_t i = 0; i < vec.size(); i++) {
		cout << "::::::::::" << endl;
		cout << "Name: " << vec.at(i).nome << endl;
		cout << "NIF: " << vec.at(i).nif << endl;
		cout << "Family members: " << vec.at(i).number_agregado << endl;
		cout << "----Address--- \n" << return_addres(vec.at(i).morada);
		cout << "Packages: " << vec.at(i).pacotes << endl;
	}
}
void makeCopy(string filename) {
	ifstream ifile;
	string line;
	vector<string> file;
	tokenize(filename, '.', file);

	ifile.open(filename);
	string outname = file.at(0) + "_copy.txt";
	ofstream ofile;
	ofile.open(outname);
	while (getline(ifile, line)) {
		ofile << line << endl;
	}
	//cout << "Ponto na posição : " << pos;
	ifile.close();
	ofile.close();
}
void writeClients(string file_name, vector<Cliente> &vec) {
	makeCopy(file_name);
	cout << "A copy of the previous file have been made in case of data lost!";
	ofstream file;
	file.open(file_name);
	if (file.is_open()) {
		for (size_t i = 0; i < vec.size(); i++) {
			file << vec.at(i).nome << endl;
			file << vec.at(i).nif << endl;
			file << vec.at(i).number_agregado << endl;
			file << vec.at(i).morada.rua_nome << " / " << vec.at(i).morada.porta_number << " / " << vec.at(i).morada.andar_number << " / " << vec.at(i).morada.zip_code << " / " << vec.at(i).morada.localidade << endl;
			if (i < vec.size() - 1) {
				file << "::::::::::" << endl;
			}
		}
	}
	file.close();
}
