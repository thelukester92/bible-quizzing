#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Database.h"

class Player
{
	static const int INVALID_ID;
	
	Database &db;
	
	std::string name;
	int id, buzzCorrectCount, buzzIncorrectCount, bonusCorrectCount, bonusIncorrectCount, quizOutCount, foulCount, foulOutCount, errOutCount;
	
	char query[1024];
	std::vector< std::map<std::string, std::string> > result;
	
	void save();
	
	public:
		Player(Database &db);
		Player(Database &db, int id);
		Player(Database &db, std::string name);
		
		std::string getName() const;
		int getId() const;
		int getBuzzCorrectCount() const;
		int getBuzzIncorrectCount() const;
		int getBonusCorrectCount() const;
		int getBonusIncorrectCount() const;
		int getQuizOutCount() const;
		int getFoulCount() const;
		int getFoulOutCount() const;
		int getErrOutCount() const;
		
		int getBuzzCount() const;
		int getBonusCount() const;
		
<<<<<<< HEAD
=======
		void setName(std::string name);
>>>>>>> master
		void addBuzzCorrect();
		void addBuzzIncorrect();
		void addBonusCorrect();
		void addBonusIncorrect();
		void addQuizOut();
		void addFoul();
		void addFoulOut();
		void addErrOut();
		
		void clear();
		void loadPlayer(int id);
		int createPlayer(std::string name);
<<<<<<< HEAD
=======
		void deletePlayer();
>>>>>>> master
};

#endif
