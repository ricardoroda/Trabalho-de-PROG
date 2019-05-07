#include "Client.h"
#include "Address.h" //NOTA: adress_header � usado no client_header

  // ADDING CLIENTS INFO  to a new class object

// creating a new client (USER -> CLASS OBJECT)
Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address){
  
	this->name = name;
	this->VATnumber = VATnumber; 
	this->familySize = familySize; 
	this->address = address; 
	//packets - inicialization = empty
	this->totalPurchased = 0;
}

// reading client from file (FILE -> CLASS OBJECT) --- NOTA: N�O ESTA A SER USADO (client_data function)
Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet> & packets, unsigned totalPurchased){
  
	this->name = name;
	this->VATnumber = VATnumber;
	this->familySize = familySize;
	this->address = address;
	this->packets = packets;
	this->totalPurchased = totalPurchased;
}

// Fun��o que cria um vetor (de objectos da class client) com todos os clientes presentes no texto;
vector<Client> client_data(string tmp_client_data) {
	cout << "i started" << endl;
	vector<Client> client_info;
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

  // GET methods - functions that return the class object elements

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

vector<Packet> Client::getPacketList() const{
  
	return packets;
}

unsigned Client::getTotalPurchased() const{
  
	return totalPurchased;
}
  
  // metodos SET - function that sets its parameter has the class object element
	  
void Client::setName(string name){
  
	this->name = name;
}

void Client::setVATnumber(unsigned VATnumber){
  
	this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize){
  
	this->familySize = familySize;
}

void Client::setAddress(Address address){
  
	this->address = address;
}

void Client::setPacketList(vector<Packet> & packets){
  
	this->packets = packets;
}

unsigned Client::setTotalPurchased(unsigned totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
  
  // outros metodos

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

// displayes the client info in a nice format
ostream& operator<<(ostream& out, const Client & client){

	out << "::::::::::" << endl;
	out << "Name: " << Client::getName << endl;
	out << "NIF: " << Client::getVATnumber << endl;
	out << "Family members: " << Client::getFamilySize << endl;
	out << "----Address--- \n" << Client::getAddress << endl;
	out << "Packages: " << Client::getPacketList << endl;
	return out;

}

//Function responsible to handle with my Clients data from the file of my clients.
Client client_handler(vector<string> clients) {
	Client client;
	client.setName = clients.at(0);
	client.setVATnumber = clients.at(1);
	istringstream teste(clients.at(2)); //??? teste? - � necess�rio definir aqui (ao lado do tokenize)
	teste >> client.setFamilySize;
	client.setAddress = address_handler(clients.at(3));
	client.setPacketList = clients.at(4);
	client.setTotalPurchased = count(clients.at(4).begin(), clients.at(4).end(), ';') + 1;
	return client;
}



//-------------------------------------------- Clients functions TO ADD -----------------------------------

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
	vector<string> nClient_questions = { "Client name: ","NIF number: ","N� family members: ","Address: ","Package list: " };
	cout << endl;
	vector<string> new_client = clientQuestionHandler(nClient_questions);
	return new_client;
}

//Add new client
vector<Client> add_client(vector<Client> &vec) {
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
	//cout << "Ponto na posi��o : " << pos;
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