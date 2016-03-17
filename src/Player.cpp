#include "Player.h"
using namespace std;

const int Player::INVALID_ID = -1;

Player::Player(Database &db) : db(db)
{
	clear();
}

Player::Player(Database &db, int id) : db(db)
{
	loadPlayer(id);
}

Player::Player(Database &db, string name) : db(db)
{
	createPlayer(name);
}

string Player::getName() const
{
	return name;
}

int Player::getId() const
{
	return id;
}

int Player::getBuzzCorrectCount() const
{
	return buzzCorrectCount;
}

int Player::getBuzzIncorrectCount() const
{
	return buzzIncorrectCount;
}

int Player::getBonusCorrectCount() const
{
	return bonusCorrectCount;
}

int Player::getBonusIncorrectCount() const
{
	return bonusIncorrectCount;
}

int Player::getQuizOutCount() const
{
	return quizOutCount;
}

int Player::getFoulCount() const
{
	return foulCount;
}

int Player::getFoulOutCount() const
{
	return foulOutCount;
}

int Player::getErrOutCount() const
{
	return errOutCount;
}

int Player::getBuzzCount() const
{
	return buzzCorrectCount + buzzIncorrectCount;
}

int Player::getBonusCount() const
{
	return bonusCorrectCount + bonusIncorrectCount;
}

void Player::addBuzzCorrect()
{
	buzzCorrectCount++;
	save();
}

void Player::addBuzzIncorrect()
{
	buzzIncorrectCount++;
	save();
}

void Player::addBonusCorrect()
{
	bonusCorrectCount++;
	save();
}

void Player::addBonusIncorrect()
{
	bonusIncorrectCount++;
	save();
}

void Player::addQuizOut()
{
	quizOutCount++;
	save();
}

void Player::addFoul()
{
	foulCount++;
	save();
}

void Player::addFoulOut()
{
	foulOutCount++;
	save();
}

void Player::addErrOut()
{
	errOutCount++;
	save();
}

void Player::clear()
{
	name				= "";
	id					= INVALID_ID;
	buzzCorrectCount	= 0;
	buzzIncorrectCount	= 0;
	bonusCorrectCount	= 0;
	bonusIncorrectCount	= 0;
	quizOutCount		= 0;
	foulCount			= 0;
	foulOutCount		= 0;
	errOutCount			= 0;
}

void Player::loadPlayer(int id)
{
	sprintf(query, "\
		SELECT\
			name, buzzCorrectCount, buzzIncorrectCount, bonusCorrectCount, bonusIncorrectCount, quizOutCount, foulCount, foulOutCount, errOutCount\
		FROM\
			players\
		WHERE\
			id = %d", id);
	db.query(query, result);
	
	if(result.size() == 1)
	{
		name				= result[0]["name"];
		this->id			= id;
		buzzCorrectCount	= atoi(result[0]["buzzCorrectCount"].c_str());
		buzzIncorrectCount	= atoi(result[0]["buzzIncorrectCount"].c_str());
		bonusCorrectCount	= atoi(result[0]["bonusCorrectCount"].c_str());
		bonusIncorrectCount	= atoi(result[0]["bonusIncorrectCount"].c_str());
		quizOutCount		= atoi(result[0]["quizOutCount"].c_str());
		foulCount			= atoi(result[0]["foulCount"].c_str());
		foulOutCount		= atoi(result[0]["foulOutCount"].c_str());
		errOutCount			= atoi(result[0]["errOutCount"].c_str());
	}
	else
	{
		clear();
	}
}

void Player::save()
{
	sprintf(query, "\
		UPDATE\
			players\
		SET\
			buzzCorrectCount = %d,\
			buzzIncorrectCount = %d,\
			bonusCorrectCount = %d,\
			bonusIncorrectCount = %d,\
			quizOutCount = %d,\
			foulCount = %d,\
			foulOutCount = %d,\
			errOutCount = %d\
		WHERE\
			id = %d\
	", buzzCorrectCount, buzzIncorrectCount, bonusCorrectCount, bonusIncorrectCount, quizOutCount, foulCount, foulOutCount, errOutCount, id);
	db.query(query);
}

int Player::createPlayer(string name)
{
	sprintf(query, "\
		SELECT id FROM players WHERE name = '%s'\
	", name.c_str());
	db.query(query, result);
	
	if(result.size() > 0)
	{
		int id = atoi( result[0]["id"].c_str() );
		loadPlayer(id);
		return id;
	}
	
	sprintf(query, "\
		INSERT INTO players (name) VALUES ('%s')\
	", name.c_str());
	db.query(query);
	
	sprintf(query, "\
		SELECT id FROM players WHERE name = '%s'\
	", name.c_str());
	db.query(query, result);
	
	if(result.size() > 0)
	{
		int id = atoi( result[0]["id"].c_str() );
		loadPlayer(id);
		return id;
	}
	
	return INVALID_ID;
}
