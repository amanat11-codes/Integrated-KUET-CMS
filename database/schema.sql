CREATE TABLE "notices" (
	"notice_id"	INTEGER NOT NULL,
	"date"	TEXT NOT NULL,
	"title"	TEXT NOT NULL,
	"intro"	TEXT NOT NULL,
	"details"	TEXT NOT NULL,
	PRIMARY KEY("notice_id" AUTOINCREMENT)
);