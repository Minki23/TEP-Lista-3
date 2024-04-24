#pragma once
#include <iostream>
#include <vector>
class Node
{
public:
	Node();
	Node(const Node& node);
	~Node();
	Node(std::string value);
	std::string getValue() const;
	void setValue(std::string value);
	void setNumberOfChilds(std::string operation);
	int getNumberOfChilds() const;
	std::vector<Node>* getChilds() const;
private:
	std::string value;
	std::vector<Node>* childs;
	int numberOfChilds;
};

