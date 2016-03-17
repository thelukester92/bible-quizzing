#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Bible.h"
#include "Database.h"
#include "Random.h"
#include "Quiz.h"
using namespace std;

int main(int argc, char *argv[])
{
	vector<int> chapters;
	chapters.push_back(1);
	chapters.push_back(2);
	
	Quiz quiz("1 Peter", chapters);
	for(int i = 0; i < quiz.getQuestionCount(); i++)
	{
		if(quiz.hasAlert())
		{
			cout << quiz.getAlert() << endl;
		}
		
		cout << "Question " << (i + 1) << ", " << quiz.getQuestion(i).type << endl
			 << "Question: " << quiz.getQuestion(i).question << endl
			 << "Answer: " << quiz.getQuestion(i).answer << endl
			 << "Reference: " << quiz.getQuestion(i).reference << endl
			 << "Verse: " << quiz.getQuestion(i).text << endl;
		
		string foo;
		getline(cin, foo);
	}
	
	return 0;
}
