#ifndef QUIZ_SET_H
#define QUIZ_SET_H

<<<<<<< HEAD
#include <sstream>
=======
>>>>>>> master
#include <string>
#include <vector>
#include "Bible.h"
#include "Database.h"
#include "Random.h"

struct Question
{
	int chapter, verse, endVerse;
	std::string type, typeAbbv, question, answer, reference, text;
};

class QuizSet
{
	Bible bible;
	Database &db;
	std::vector<int> questions, chapters, indices;
	std::string book, chapterList;
	int bookId;
	
	char query[1024];
	std::vector< std::map<std::string, std::string> > result;
	
	public:
		QuizSet(Database &db, std::string book, std::vector<int> chapters);
		Question question(int index);
		Question bonus(std::string typeAbbv);
		
		std::string getBook() const;
		int getQuestionCount() const;
	
	protected:
		void addQuestions(int questionCount);
		void addQuestions(std::string abbvs, int count);
		std::vector<int> getQuestions(std::string abbvs, int count);
		Question loadQuestion(int id);
};

#endif
