#include "NodeTree.h"
#include <string>
#include <vector>
static int shift = 1;

NodeTree::NodeTree() {
	this->root = new Node();
}
NodeTree::~NodeTree() {
	delete this->root;
}
void NodeTree::InOrderWalk() {
	InOrderInner(*this->root);
	std::cout << std::endl;
}
const std::vector<std::string>& NodeTree::getvariables() const{
	return this->variables;
}
Node* NodeTree::getRoot() const {
	return this->root;
}
void NodeTree::put(std::vector<std::string> sequence) {
	this->root = new Node(sequence[0]);
	this->root->setNumberOfChilds(sequence[0]);
	if (isalpha(sequence[0][0]) && sequence[0] != "sin" && sequence[0] != "cos") {
		variables.push_back(sequence[0]);
	}
	recAdding(*root, sequence);
	shift = 1;
}
void NodeTree::recAdding(Node& next, std::vector<std::string> sequence) {
	if (next.getNumberOfChilds() > next.getChilds()->size()) {
		if (shift < sequence.size()) {
			next.getChilds()->push_back(*(new Node(sequence[shift])));
			next.getChilds()->at(0).setNumberOfChilds(sequence[shift]);
			if (isalpha(sequence[shift][0]) && indexof(variables, sequence[shift]) == -1) {
				variables.push_back(sequence[shift]);
			}
		}
		for (int i = 0;i < next.getNumberOfChilds();i++) {
			if (i >= next.getChilds()->size()) {
				if (shift < sequence.size()) {
					next.getChilds()->push_back(*(new Node(sequence[shift])));
					next.getChilds()->at(i).setNumberOfChilds(sequence[shift]);
					if (isalpha(sequence[shift][0]) && indexof(variables, sequence[shift])==-1 && sequence[shift]!="sin" && sequence[shift]!="cos") {
						variables.push_back(sequence[shift]);
					}
				}
				else {
					for (int j = 0;j < next.getNumberOfChilds();j++) {
						next.getChilds()->push_back(*(new Node("1")));
						next.getChilds()->at(j).setNumberOfChilds("1");
					}
						std::cout << "blad, poprawiono\n";
				}
			}
			shift++;
			recAdding(next.getChilds()->at(i), sequence);
		}
	}
	validate(*root);
}
void NodeTree::validate(Node& node) {
	for (int i = 0;i < node.getNumberOfChilds() - node.getChilds()->size();i++) {
		node.getChilds()->push_back(*new Node("1"));
	}
	for (int i = 0;i < node.getNumberOfChilds();i++) {
		validate(node.getChilds()->at(i));
	}
}
int NodeTree::CalcVal(const Node& node,const std::vector<std::string>& values) const{
	switch (node.getValue()[0])
	{
	case '+':
		return CalcVal(node.getChilds()->at(0), values) + CalcVal(node.getChilds()->at(1), values);
	case '-':
		return CalcVal(node.getChilds()->at(0), values) - CalcVal(node.getChilds()->at(1), values);
	case '*':
		return CalcVal(node.getChilds()->at(0), values) * CalcVal(node.getChilds()->at(1), values);
	case '/':
		return CalcVal(node.getChilds()->at(0), values) / CalcVal(node.getChilds()->at(1), values);
	case 's':
		if (node.getValue() == "sin")
			return sin(CalcVal(node.getChilds()->at(0), values));
		else
			std::stoi(values.at(indexof(variables, node.getValue())));
	case 'c':
		if(node.getValue()=="cos")
			return cos(CalcVal(node.getChilds()->at(0), values));
		else
			std::stoi(values.at(indexof(variables, node.getValue())));
	default:
		if(isalpha(node.getValue()[0])){
			return std::stoi(values.at(indexof(variables, node.getValue())));
		}
		return std::stoi(node.getValue());
	}
}
void NodeTree::join(const NodeTree& node) {
    Node* toConnect = this->root;
    while (toConnect->getNumberOfChilds()!=0) {
        toConnect = &(toConnect->getChilds()->at(toConnect->getNumberOfChilds() - 1));
    }
	if (isalpha((*toConnect).getValue()[0])) {
		variables.erase(variables.begin()+indexof(variables,toConnect->getValue()));
	}
	for (int i = 0;i < node.getvariables().size();i++) {
		if(indexof(variables, node.getvariables().at(i))==-1)
			variables.push_back(node.getvariables().at(i));
	}
    *toConnect = *node.getRoot();
}
void NodeTree::InOrderInner(Node& node) {
	std::cout << node.getValue() << " ";
	if (node.getNumberOfChilds() > 0) {
		for (int i = 0;i < node.getNumberOfChilds();i++) {
			InOrderInner(node.getChilds()->at(i));
		}
	}
	else {
		return;
	}
}
int NodeTree::indexof(const std::vector<std::string>& vec,const std::string& szukana) const {
	for (int i = 0;i < vec.size();i++) {
		if (vec.at(i) == szukana) {
			return i;
		}
	}
	return -1;
}
NodeTree* NodeTree::operator+(const NodeTree& tojoin) {
	NodeTree copy = *this;
	copy.join(tojoin);
	return &copy;
}
NodeTree* NodeTree::operator=(NodeTree toequal) {
	std::swap(this->root, toequal.root);
	this->variables.clear();
	for (std::string variable : toequal.variables) {
		variables.push_back(variable);
	}
	return this;
}
