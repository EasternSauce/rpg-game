#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <string>
#include <vector>

class Dialogue
{
private:
	std::string question;
	std::vector<std::string> answers;
public:
	std::string getQuestion();
	std::vector<std::string> getAnswers();
};


#endif
