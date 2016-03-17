#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Bible.h"
#include "Database.h"
#include "Random.h"
#include "QuizSet.h"
using namespace std;

void printQuestion(Question &q, int num, bool bonus)
{
	if(!bonus)
		cout << "\033[35m\033[1mQuestion #" << num << "\033[0m\n";
	else
		cout << "\033[35m\033[1mBonus Question\033[0m\n";
	cout << "\033[32m\033[1m" << q.type << " Question\033[0m\n";
	cout << "\033[36m\033[1mReference:\033[0m "   << q.reference << "\n";
	cout << "\033[36m\033[1mQuestion:\033[33m  " << q.question  << "\n";
	cout << "\033[36m\033[1mAnswer:\033[0m    "   << q.answer    << "\n";
	cout << "\033[36m\033[1mVerse:\033[0m     "   << q.text      << "\n";
}

int getPlayer()
{
	int player;
	cout << "Enter player number that buzzed in:\n";
	cin >> player;
	return player;
}

bool getCorrect()
{
	int correct;
	cout << "Enter 0 for incorrect or 1 for correct:\n";
	cin >> correct;
	return correct != 0;
}

void doQuestion(QuizSet &quiz, int index, int &scoreA, int &scoreB, int &missA, int &missB)
{
	Question q = quiz.question(index);
	
	printQuestion(q, index + 1, false);
	
	int player = getPlayer();
	if(getCorrect())
	{
		if(player == 1)
		{
			scoreA += 20;
		}
		else
		{
			scoreB += 20;
		}
	}
	else
	{
		Question b = quiz.bonus(q.typeAbbv);
		printQuestion(b, 0, true);
		
		if(getCorrect())
		{
			if(player == 1)
			{
				if(missA >= 3 || index + 1 >= 17)
					scoreA -= 10;
				else
					missA++;
				scoreB += 10;
			}
			else
			{	if(missB >= 3 || index + 1 >= 17)
					scoreB -= 10;
				else
					missB++;
				scoreA += 10;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	Database db("resources/db.sqlite");
	
	vector<int> chapters;
	chapters.push_back(1);
	chapters.push_back(2);
	chapters.push_back(3);
	
	QuizSet quiz(db, "1 Peter", chapters);
	Random r;
	
	int missA = 0, missB = 0;
	int scoreA = 0, scoreB = 0;
	
	for(int i = 0; i < quiz.getQuestionCount(); i++)
	{
		cout << "The score is " << scoreA << " to " << scoreB << "\n\n";
		doQuestion(quiz, i, scoreA, scoreB, missA, missB);
	}
	
	cout << "\nThe score is " << scoreA << " to " << scoreB << "\n\n";

	srand(time(NULL));
	cout << "\033[35mCandy questions are: ";
	int rr[20] = {0};
	for(int i = 0; i < 4; i++) {
		int t = 0;
		do {
			t = (rand() % 20 + 1);
		}while(rr[t] != 0);
		rr[t] = 1;
		cout << t << " ";
	}
	cout << "\033[0m" << endl;

	return 0;
}
