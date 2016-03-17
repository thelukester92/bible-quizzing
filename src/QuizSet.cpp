#include "QuizSet.h"
#include "Random.h"
using namespace std;

QuizSet::QuizSet(Database &db, string book, vector<int> chapters)
: db(db), book(book), chapters(chapters)
{
	const int QUESTION_COUNT = 20;
	
	bookId = bible.getBookId(book);
	if(bookId >= 0 && chapters.size() > 0)
	{
		chapterList = "";
		for(int i = 0; i < chapters.size(); i++)
		{
			if(i > 0)
			{
				chapterList += ",";
			}
			
			std::stringstream ss;
			ss << chapters[i];
			chapterList += ss.str();
		}
		
		addQuestions(QUESTION_COUNT);
	}
}

Question QuizSet::question(int index)
{
	if(index >= 0 && index < questions.size())
	{
		return loadQuestion(questions[indices[index]]);
	}
	
	return Question();
}

Question QuizSet::bonus(string typeAbbv)
{
	vector<int> q = getQuestions("'" + typeAbbv + "'", 1);
	
	if(q.size() > 0)
	{
		return loadQuestion(q[0]);
	}
	
	return Question();
}

string QuizSet::getBook() const
{
	return book;
}

int QuizSet::getQuestionCount() const
{
	return questions.size();
}

// MARK: Protected Methods

void QuizSet::addQuestions(int questionCount)
{
	Random r;
	
	// Distribution of the questions
	int quote				= 3;
	int finish				= r.nextInt(3, 5);
	int multipleAnswer		= r.nextInt(2, 4);
	int reverseReference	= r.nextInt(2, 4);
	int interrogative		= questionCount - multipleAnswer - finish - quote - reverseReference;
	
	// Abbreviations for question types
	string qAbbv	= "'Q'";
	string fAbbv	= "'F', 'FC'";
	string mAbbv	= "'MA', 'MC', 'MV'";
	string iAbbv	= "'I', 'IC', 'IV'";
	string rAbbv	= "'R', 'RC'";
	
	// Add questions
	addQuestions(qAbbv, quote);
	addQuestions(fAbbv, finish);
	addQuestions(mAbbv, multipleAnswer);
	addQuestions(iAbbv, interrogative);
	addQuestions(rAbbv, reverseReference);
	
	// Shuffle questions
	indices.resize(questions.size());
	for(int i = 0; i < indices.size(); i++)
	{
		indices[i] = i;
	}
	for(int i = indices.size(); i > 1; i--)
	{
		swap(indices[i - 1], indices[r.nextInt(0, indices.size() - 1)]);
	}
}

void QuizSet::addQuestions(string abbvs, int count)
{
	vector<int> q = getQuestions(abbvs, count);
	questions.insert( questions.end(), q.begin(), q.end() );
}

vector<int> QuizSet::getQuestions(string abbvs, int count)
{
	vector<int> output;
	
	// Select all ids, ordered
	
	sprintf(query, "\
		SELECT questions.id AS id \
		FROM questions LEFT OUTER JOIN timestamps ON timestamps.question = questions.id \
		WHERE type IN \
		( \
			SELECT id FROM questionTypes WHERE abbv IN (%s) \
		) \
		AND chapter IN (%s) \
		and book = %d \
		ORDER BY time \
	", abbvs.c_str(), chapterList.c_str(), bookId);
	
	db.query(query, result);
	
	// Use a normal distribution to select the appropriate count
	
	Random r;
	double range = 0.8;
	int resultCount = result.size();
	int index;
	
	for(int i = 0; i < count; i++)
	{
		index = int( floor( fabs( r.normal() * resultCount * range ) ) );
		output.push_back( atoi( result[index]["id"].c_str() ) );
		result.erase( result.begin() + index );
		resultCount--;
		
		sprintf(query, "INSERT OR REPLACE INTO timestamps (question, time) VALUES (%s, CURRENT_TIMESTAMP)", result[index]["id"].c_str());
		db.query(query);
	}
	
	return output;
}

Question QuizSet::loadQuestion(int id)
{
	sprintf(query, "SELECT questionTypes.name AS type, questionTypes.abbv AS typeAbbv, book, chapter, verse, endVerse, question, answer FROM questions LEFT JOIN questionTypes ON questionTypes.id = questions.type WHERE questions.id = %d", id);
	db.query(query, result);
	
	Question q;
	
	if(result.size() == 1)
	{
		q.type		= result[0]["type"];
		q.typeAbbv	= result[0]["typeAbbv"];
		q.chapter	= atoi(result[0]["chapter"].c_str());
		q.verse		= atoi(result[0]["verse"].c_str());
		q.endVerse	= result[0]["endVerse"] != "" ? atoi(result[0]["endVerse"].c_str()) : q.verse;
		q.question	= result[0]["question"];
		q.answer	= result[0]["answer"];
		q.reference = book + " " + result[0]["chapter"] + ":" + result[0]["verse"];
		
		if(q.endVerse > q.verse)
		{
			q.reference += " - " + result[0]["chapter"] + ":" + result[0]["endVerse"];
		}
		
		q.text = bible.getVerse(bookId, q.chapter, q.verse);
		for(int v = q.verse + 1; v <= q.endVerse; v++)
		{
			q.text += " " + bible.getVerse(bookId, q.chapter, v);
		}
		
		if(q.type == "Quote")
		{
			q.question = "Quote " + q.reference;
		}
		
		if(q.typeAbbv == "FC" || q.typeAbbv == "MC" || q.typeAbbv == "IC" || q.typeAbbv == "RC")
		{
			q.question = "According to " + book + " " + result[0]["chapter"] + ", " + q.question;
		}
		
		if(q.typeAbbv == "MV" || q.typeAbbv == "IV")
		{
			q.question = "According to " + q.reference + ", " + q.question;
		}
		
		sprintf(query, "INSERT OR REPLACE INTO timestamps (question, time) VALUES (%d, CURRENT_TIMESTAMP)", id);
		db.query(query);
	}
	
	return q;
}
