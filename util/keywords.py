#!/usr/bin/python

from __future__ import print_function
import sqlite3

con = sqlite3.connect("../Documents/Projects/bible-quizzing/resources/bible.sqlite")
c = con.cursor()

refs = {}
rows = []

for row in c.execute("SELECT chapter, verse, text FROM verses WHERE book = 60"):
	# key words
	c = int(row[0])
	v = int(row[1])
	rows.append((filter(None, [ filter(str.isalnum, str(x)).lower() for x in row[2].split(" ") ]), c, v))
	for w in rows[-1][0]:
		if not w in refs:
			refs[w] = [ "%d:%d" % (c, v) ]
		else:
			refs[w].append("%d:%d" % (c, v))

for words, c, v in rows:
	# key phrases (2 words)
	for w1, w2 in zip(words[:-1], words[1:]):
		# only check for key phrase if either component wasn't a key word already
		if len(refs[w1]) > 1 and len(refs[w2]) > 1:
			p = w1 + " " + w2
			if not p in refs:
				refs[p] = [ "%d:%d" % (c, v) ]
			else:
				refs[p].append("%d:%d" % (c, v))

for row in rows:
	# key phrases (3 words)
	for w1, w2, w3 in zip(words[:-2], words[1:-1], words[2:]):
		# only check for key phrase if either component wasn't a key word already
		if len(refs[w1]) > 1 and len(refs[w2]) > 1 and len(refs[w3]) > 1 and len(refs[w1 + " " + w2]) > 1 and len(refs[w2 + " " + w3]) > 1:
			p = w1 + " " + w2 + " " + w3
			if not p in refs:
				refs[p] = [ "%d:%d" % (c, v) ]
			else:
				refs[p].append("%d:%d" % (c, v))

print("Key,Key Length,Count,Reference(s)")
for key, val in sorted(refs.items(), key=lambda (k, v): (len(v), k)):
	if any([ x.startswith("5:") for x in refs[key] ]):
		print("%s,%d,%d,%s" % (key, key.count(" ") + 1, len(val), ";".join(refs[key])))
