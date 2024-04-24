#include "UserInterface.h"
#include "NodeTree.h"
#include <string>
UserInterface::UserInterface() {
	mytree = new NodeTree();
	activate();
}
UserInterface::~UserInterface() {
	delete mytree;
}
std::vector<std::string> UserInterface::splitString(std::string sequence) {
	std::string word;
	std::vector<std::string>words;
	if (sequence[sequence.size() - 1] != ' ') {
		sequence += " ";
	}
	for (int i = 0;i < sequence.size();i++) {
		if (sequence[i] != ' ') {
			if (std::isalnum(sequence[i])||sequence[i]=='+' || sequence[i] == '-' || sequence[i] == '*' || sequence[i] == '/') {
				word.push_back(sequence[i]);
			}
			else {
				std::cout << "pominieto znak: " << sequence[i] << " \n";
			}
		}
		else {
			if (!word.empty()) {
				words.push_back(word);
				word.clear();
			}
		}
	}
	return words;
}
void UserInterface::activate() {
	std::string wybor="1";
	std::cout << "Wpisz `enter [sekwencja]` aby stworzyc drzewo\n";
	std::cout << "Wpisz `join [sekwencja]` aby dodac sekwencje do drzewa\n";
	std::cout << "Wpisz `print` aby pokazac obecne drzewo\n";
	std::cout << "Wpisz `comp [wartosci]` aby obliczyc sekwencje na drzewie z podanymi wartosciami zmiennych\n";
	std::cout << "Wpisz `quit` aby wyjsc\n\n";
	do {
		std::cout << "Podaj komende> ";
		std::getline(std::cin, wybor);
		takeCommand(wybor);
	} while (wybor != "quit");
	std::cout << "Do widzenia";
}
void UserInterface::takeCommand(std::string command) {
	if (command.size() > 0) {
		std::vector<std::string> data = splitString(command);
		std::string toinvoke = data.at(0);
		data.erase(data.begin());
		if (toinvoke == "enter") {
			mytree->put(data);
		}
		else if (toinvoke == "print") {
			mytree->InOrderWalk();
		}
		else if (toinvoke == "comp") {
			if (data.size() != mytree->getvariables().size())
				std::cout << "bledna ilosc wartosci, spodziewano sie " << mytree->getvariables().size() << " wartosci a otrzymano: " << data.size() << "\n";
			else {
				bool poprawna = true;
				for (std::string dataitem : data) {
					for (char datachar : dataitem) {
						if (isalpha(datachar))
							poprawna = false;
					}
					if (!poprawna)
						std::cout << "bledna wartosc zmiennej, podano: " << dataitem << "\n";
				}
				if (poprawna)
					std::cout << mytree->CalcVal(*((*mytree).getRoot()), data) << "\n";
			}
		}
		else if (toinvoke == "join") {
			if (mytree != nullptr) {
				NodeTree* toadd = new NodeTree();
				(*toadd).put(data);
				mytree->join(*toadd);
			}
			else {
				mytree->put(data);
			}
		}
		else if (toinvoke == "vars") {
			for (std::string variable : mytree->getvariables()) {
				std::cout << variable << " ";
			}
			std::cout << "\n";
		}
		else
			std::cout << "Nierozpoznano komendy\n";
	}
}