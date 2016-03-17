#ifndef QUIZ_H
#define QUIZ_H

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "QuizSet.h"
#include "Player.h"

class Quiz
{
	static const std::string DB_NAME;
	
	static const int QUESTION_SCORE;
	static const int BONUS_SCORE;
	static const int QUIZ_OUT_SCORE;
	
	static const int ERR_PENALTY;
	static const int FOUL_PENALTY;
	static const int ERR_OUT_PENALTY;
	static const int FOUL_OUT_PENALTY;
	
	static const int FREE_ERRORS;
	static const int LAST_FREE_ERROR_QUESTION;
	
	static const int TIMEOUTS;
	
	static const int QUIZ_OUT;
	static const int FOUL_OUT;
	static const int ERR_OUT;
	
	Database db;
	QuizSet questions;
	size_t questionIndex;
	std::string questionTypeAbbv;
	
	std::vector< std::vector<Player> > teams;
	std::vector< std::vector<size_t> > personalCorrects;
	std::vector< std::vector<size_t> > personalFouls;
	std::vector< std::vector<size_t> > personalErrors;
	std::vector<int> scores;
	std::vector<size_t> errors;
	std::vector<size_t> timeouts;
	
	std::vector<std::string> alerts;
	
	public:
		Quiz(std::string book, std::vector<int> chapters);
		
		std::map<int, std::string> getAllPlayers();
		int createPlayer(std::string name);
		void setPlayers(std::vector<int> players);
		
		bool hasAlert();
		std::string getAlert();
		
		void alertNoMoreFreeErrors();
		void alertNoMoreFreeErrors(size_t team);
		void alertNoMoreTimeouts(size_t team);
		void alertQuizOut(size_t team, size_t seat);
		void alertFoulOut(size_t team, size_t seat);
		void alertErrOut(size_t team, size_t seat);
		
		int getQuestionCount();
		int getScore(size_t team);
		size_t getErrors(size_t team);
		size_t getPersonalCorrects(size_t team, size_t seat);
		size_t getPersonalFouls(size_t team, size_t seat);
		size_t getPersonalErrors(size_t team, size_t seat);
		size_t getTimeouts(size_t team);
		
		std::vector<Player> &getTeam(size_t team);
		Player &getPlayer(size_t team, size_t seat);
		Question getQuestion(size_t index);
		Question getBonusQuestion();
		
		void foul(size_t team, size_t seat);
		void answerCorrectly(size_t team, size_t seat);
		void answerIncorrectly(size_t team, size_t seat);
		void answerBonusCorrectly(size_t team, size_t seat);
		void answerBonusIncorrectly(size_t team, size_t seat);
		
		void substitute(size_t team, size_t seat, int player);
		void timeout(size_t team);
		
		void overrideScore(size_t team, int score);
};

#endif
