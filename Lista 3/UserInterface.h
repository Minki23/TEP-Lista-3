#pragma once
#include <iostream>
#include <vector>
#include "NodeTree.h"
static class UserInterface
{
public:
	UserInterface();
	~UserInterface();
	std::vector<std::string> getwords();
	std::vector<std::string> splitString(std::string sequence);
private:
	void activate();
	NodeTree* mytree;
	std::vector<std::string> words;
	void takeCommand(std::string command);
};

