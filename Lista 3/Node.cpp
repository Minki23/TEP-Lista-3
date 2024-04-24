#include "Node.h"
#include <vector>

Node::Node() {
	this->value = "0";
	this->numberOfChilds = 0;
	this->childs = new std::vector<Node>();
}
Node::Node(std::string value)
{
	this->value = value;
	this->childs = new std::vector<Node>();
}
Node::Node(const Node& node) {
	this->value = node.value;
	this->numberOfChilds = node.numberOfChilds;
	this->childs = new std::vector<Node>();
	for (const Node& child : *node.childs) {
		childs->push_back(child);
	}
}
Node::~Node() {
	delete childs;
}
std::string Node::getValue() const {
	return this->value;
}
void Node::setValue(std::string value) {
	this->value = value;
}
std::vector<Node>* Node::getChilds() const{
	return this->childs;
}
int Node::getNumberOfChilds() const {
	return this->numberOfChilds;
}
void Node::setNumberOfChilds(std::string operation) {
	int number = 0;
	if (operation == "+" || operation == "-" || operation == "*" || operation == "/") {
		number = 2;
	}
	else if (operation == "sin" || operation == "cos") {
		number = 1;
	}
	this->numberOfChilds = number;
}