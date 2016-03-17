#include <map>
#include <vector>
#include "Bible.h"
using namespace std;

Bible::Bible(const char *filename) : db(filename)
{

}

string Bible::getVerse(int book, int chapter, int verse)
{
	sprintf(query, "\
		SELECT text FROM verses \
		WHERE book = '%d' \
		AND chapter = '%d' \
		AND verse = '%d' \
	", book, chapter, verse);
	
	db.query(query, result);
	
	if(result.size() == 1)
	{
		return result[0]["text"];
	}
	else
	{
		return "No verse found!";
	}
}

string Bible::getVerse(string book, int chapter, int verse)
{
	return getVerse(getBookId(book), chapter, verse);
}

int Bible::getBookId(string book)
{
	sprintf(query, "SELECT id FROM books WHERE name = '%s'", book.c_str());
	db.query(query, result);
	
	if(result.size() == 1)
	{
		return atoi(result[0]["id"].c_str());
	}
	else
	{
		sprintf(query, "SELECT book FROM book_aliases WHERE alias = '%s'", book.c_str());
		db.query(query, result);
		
		if(result.size() == 1)
		{
			return atoi(result[0]["book"].c_str());
		}
	}
	
	return -1;
}
