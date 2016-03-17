#!/usr/bin/python

from __future__ import print_function

with open("tmp.txt") as f:
	for line in f:
		pieces = line.split("\t")
		type = "(SELECT id FROM questionTypes WHERE abbv = '{}')".format(pieces[0])
		book = 60
		chapter = pieces[1].split(":")[0]
		verse = pieces[1].split(":")[1].split("-")
		if len(verse) == 2:
			endVerse = verse[1]
		verse = verse[0]
		question = pieces[2].replace("\n", "").replace("'", "''")
		answer = pieces[3].replace("\n", "").replace("'", "''")
		print("INSERT INTO questions(type, book, chapter, verse, question, answer) VALUES ({}, {}, {}, {}, '{}', '{}');".format(type, book, chapter, verse, question, answer))
