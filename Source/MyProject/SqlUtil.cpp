// Fill out your copyright notice in the Description page of Project Settings.


#include "SqlUtil.h"

int SqlUtil::OpenConnection() {
	char* error;
	sqlite3* ppdb;
	sqlite3_open("D:/unrealprojects/MyProject/data.db", &ppdb);
	int result = sqlite3_exec(ppdb, "CREATE TABLE IF NOT EXISTS character(id INTEGER PRIMARY KEY, name TEXT, damage INTEGER);"
		, NULL, NULL, &error);
	return result;
}

int SqlUtil::AddToDB(std::string TableName) {
}

SqlUtil::SqlUtil()
{
}

SqlUtil::~SqlUtil()
{
}
