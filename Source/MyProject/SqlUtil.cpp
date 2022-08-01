// Fill out your copyright notice in the Description page of Project Settings.


#include "SqlUtil.h"
#include <iostream>
#include <algorithm>
const std::string ASqlUtil::DirectoryDB = "../../data.db";
const std::string fullpath = std::string(TCHAR_TO_ANSI(*(FPaths::ProjectDir() + "data.db")));
int ASqlUtil::OpenConnection() {
	char* error;
	sqlite3* ppdb;
	UE_LOG(LogTemp, Display, TEXT("SQL result: %s"), *FString(fullpath.c_str()));
	sqlite3_open(fullpath.c_str(), &ppdb);
	std::cout<< (std::filesystem::current_path().string() + "/data.db").c_str() <<std::endl;
	int result = sqlite3_exec(ppdb, "CREATE TABLE IF NOT EXISTS character(id INTEGER PRIMARY KEY, name TEXT, damage REAL);"
		, NULL, NULL, &error);
	sqlite3_close(ppdb);
	return result;
}

int ASqlUtil::AddToDB(std::string TableName, ASqlUtil::Character* Character) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	sqlite3_open(fullpath.c_str(), &db);
	UE_LOG(LogTemp, Display, TEXT("damage: %f"), Character->damage);
	UE_LOG(LogTemp, Display, TEXT("name: %d"), Character->id);
	sqlite3_prepare_v2(db, "INSERT INTO character (id, name, damage) VALUES(?, ?, ?);", -1, &stmt, NULL);
	UE_LOG(LogTemp, Display, TEXT("first int: %d"), sqlite3_bind_int(stmt, 1, Character->id));
	UE_LOG(LogTemp, Display, TEXT("first text: %d"), sqlite3_bind_text(stmt, 2, Character->name.c_str(), -1, nullptr));
	UE_LOG(LogTemp, Display, TEXT("first real: %d"), sqlite3_bind_double(stmt, 3, Character->damage));
	int result = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return result;
}
