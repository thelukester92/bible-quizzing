#include "Quiz.h"
using namespace std;

const string Quiz::DB_NAME					= "resources/db.sqlite";

const int Quiz::QUESTION_SCORE				= 20;
const int Quiz::BONUS_SCORE					= 10;
const int Quiz::QUIZ_OUT_SCORE				= 10;

const int Quiz::ERR_PENALTY					= 10;
<<<<<<< HEAD
const int Quiz::FOUL_PENALTY				= 0;
const int Quiz::ERR_OUT_PENALTY				= 10;
const int Quiz::FOUL_OUT_PENALTY			= 10;

const int Quiz::FREE_ERRORS					= 2;
=======
const int Quiz::FOUL_PENALTY				= 10;
const int Quiz::ERR_OUT_PENALTY				= 10;
const int Quiz::FOUL_OUT_PENALTY			= 10;

const int Quiz::FREE_ERRORS					= 3;
>>>>>>> master
const int Quiz::LAST_FREE_ERROR_QUESTION	= 16;

const int Quiz::TIMEOUTS					= 2;

const int Quiz::QUIZ_OUT					= 4;
const int Quiz::FOUL_OUT					= 3;
const int Quiz::ERR_OUT						= 3;

Quiz::Quiz(string book, vector<int> chapters)
: db(DB_NAME.c_str()), questions(db, book, chapters), scores(2, 0), errors(2, 0), timeouts(2, TIMEOUTS)
{
	
}

map<int, string> Quiz::getAllPlayers()
{
	map<int, string> output;
	vector< map<string, string> > result;
	char query[1024];
	
	sprintf(query, "SELECT id, name FROM players");
	db.query(query, result);
	
	for(size_t i = 0; i < result.size(); i++)
	{
		output[ atoi(result[i]["id"].c_str()) ] = result[i]["name"];
	}
	
	return output;
}

int Quiz::createPlayer(string name)
{
	Player p(db);
	return p.createPlayer(name);
}

void Quiz::setPlayers(vector<int> players)
{
	vector<Player> teamA, teamB;
	
	for(size_t i = 0; i < players.size() / 2; i++)
	{
		teamA.push_back( Player(db, players[i]) );
		teamB.push_back( Player(db, players[i + players.size() / 2]) );
	}
	
	teams.push_back(teamA);
	teams.push_back(teamB);
	
	personalCorrects.push_back( vector<size_t>(teamA.size(), 0) );
	personalCorrects.push_back( vector<size_t>(teamB.size(), 0) );
	
	personalFouls.push_back( vector<size_t>(teamA.size(), 0) );
	personalFouls.push_back( vector<size_t>(teamB.size(), 0) );
	
	personalErrors.push_back( vector<size_t>(teamA.size(), 0) );
	personalErrors.push_back( vector<size_t>(teamB.size(), 0) );
}

bool Quiz::hasAlert()
{
	return alerts.size() > 0;
}

string Quiz::getAlert()
{
	if(hasAlert())
	{
		string output = alerts[0];
		alerts.erase( alerts.begin() );
<<<<<<< HEAD
=======
		return output;
>>>>>>> master
	}
	return "";
}

void Quiz::alertNoMoreFreeErrors()
{
	stringstream ss;
	ss << "The quiz has reached question " << LAST_FREE_ERROR_QUESTION + 1 << ". All errors, regardless of total team errors, will result in a " << ERR_PENALTY << " point deduction.";
	
	alerts.push_back(ss.str());
}

void Quiz::alertNoMoreFreeErrors(size_t team)
{
	stringstream ss;
	ss << "Team " << team + 1 << " has reached the maximum number of errors. Additional errors will result in a " << ERR_PENALTY << " point deduction.";
	
	alerts.push_back(ss.str());
}

void Quiz::alertNoMoreTimeouts(size_t team)
{
	stringstream ss;
	ss << "Team " << team + 1 << " has used all of its timeouts.";
	
	alerts.push_back(ss.str());
}

void Quiz::alertQuizOut(size_t team, size_t seat)
{
	stringstream ss;
	ss << teams[team][seat].getName() << " has quizzed out! Team " << team + 1 << " Seat " << seat + 1 << " will need a substitute.";
	
	alerts.push_back(ss.str());
}

void Quiz::alertFoulOut(size_t team, size_t seat)
{
	stringstream ss;
	ss << teams[team][seat].getName() << " has fouled out! Team " << team + 1 << " Seat " << seat + 1 << " will need a substitute.";
	
	alerts.push_back(ss.str());
}

void Quiz::alertErrOut(size_t team, size_t seat)
{
	stringstream ss;
	ss << teams[team][seat].getName() << " has erred out! Team " << team + 1 << " Seat " << seat + 1 << " will need a substitute.";
	
	alerts.push_back(ss.str());
}

int Quiz::getQuestionCount()
{
	return questions.getQuestionCount();
}

int Quiz::getScore(size_t team)
{
	return scores[team];
}

size_t Quiz::getErrors(size_t team)
{
	return errors[team];
}

size_t Quiz::getPersonalCorrects(size_t team, size_t seat)
{
	return personalCorrects[team][seat];
}

size_t Quiz::getPersonalFouls(size_t team, size_t seat)
{
	return personalFouls[team][seat];
}

size_t Quiz::getPersonalErrors(size_t team, size_t seat)
{
	return personalErrors[team][seat];
}

size_t Quiz::getTimeouts(size_t team)
{
	return timeouts[team];
}

<<<<<<< HEAD
=======
vector<Player> &Quiz::getTeam(size_t team)
{
	return teams[team];
}

Player &Quiz::getPlayer(size_t team, size_t seat)
{
	return teams[team][seat];
}

>>>>>>> master
Question Quiz::getQuestion(size_t index)
{
	Question q = questions.question(index);
	
	questionIndex = index;
	questionTypeAbbv = q.typeAbbv;
	
<<<<<<< HEAD
	if(index == LAST_FREE_ERROR_QUESTION + 1)
=======
	if(index == LAST_FREE_ERROR_QUESTION)
>>>>>>> master
	{
		alertNoMoreFreeErrors();
	}
	
	return q;
}

Question Quiz::getBonusQuestion()
{
	return questions.bonus(questionTypeAbbv);
}

void Quiz::foul(size_t team, size_t seat)
{
	scores[team] -= FOUL_PENALTY;
	if(++personalFouls[team][seat] >= FOUL_OUT)
	{
		scores[team] -= FOUL_OUT_PENALTY;
		teams[team][seat].addFoulOut();
		alertFoulOut(team, seat);
	}
	teams[team][seat].addFoul();
}

void Quiz::answerCorrectly(size_t team, size_t seat)
{
	scores[team] += QUESTION_SCORE;
	if(++personalCorrects[team][seat] >= QUIZ_OUT)
	{
		scores[team] += QUIZ_OUT_SCORE;
		teams[team][seat].addQuizOut();
		alertQuizOut(team, seat);
	}
	teams[team][seat].addBuzzCorrect();
}

void Quiz::answerIncorrectly(size_t team, size_t seat)
{
	if(++errors[team] > FREE_ERRORS || questionIndex > LAST_FREE_ERROR_QUESTION)
	{
		scores[team] -= ERR_PENALTY;
	}
	else if(errors[team] == FREE_ERRORS)
	{
		alertNoMoreFreeErrors(team);
	}
	
	if(++personalErrors[team][seat] >= ERR_OUT)
	{
		scores[team] -= ERR_OUT_PENALTY;
		teams[team][seat].addErrOut();
		alertErrOut(team, seat);
	}
	teams[team][seat].addBuzzIncorrect();
}

void Quiz::answerBonusCorrectly(size_t team, size_t seat)
{
	scores[team] += BONUS_SCORE;
	teams[team][seat].addBonusCorrect();
}

void Quiz::answerBonusIncorrectly(size_t team, size_t seat)
{
	teams[team][seat].addBonusIncorrect();
}

void Quiz::substitute(size_t team, size_t seat, int player)
{
	teams[team][seat].loadPlayer(player);
<<<<<<< HEAD
=======
	
	personalCorrects[team][seat] = 0;
	personalFouls[team][seat] = 0;
	personalErrors[team][seat] = 0;
>>>>>>> master
}

void Quiz::timeout(size_t team)
{
	if(--timeouts[team] <= 0)
	{
		alertNoMoreTimeouts(team);
	}
}
<<<<<<< HEAD
=======

void Quiz::overrideScore(size_t team, int score)
{
	scores[team] = score;
}
>>>>>>> master
