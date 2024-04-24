#pragma once
#include "Node.h"
class NodeTree
{
public:

	NodeTree();
	~NodeTree();

	Node* getRoot() const;
	const std::vector<std::string>& getvariables() const;

	void PrintTree();
	void put(std::vector<std::string> sequence);
	void InOrderWalk();
	void join(const NodeTree& node);
	int CalcVal(const Node& next, const std::vector<std::string>& values) const;

	NodeTree* operator+(const NodeTree& tojoin);
	NodeTree* operator=(NodeTree toequal);
private:
	Node* root;
	std::vector<std::string> variables;
	void validate(Node& node);
	int indexof(const std::vector<std::string>& vec,const std::string&szukana) const;
	void InOrderInner(Node& node);
	void recAdding(Node& next, std::vector<std::string> sequence);
	void setRoot(Node root);
};

