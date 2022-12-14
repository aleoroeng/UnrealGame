// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include <filesystem>
#include "CoreMinimal.h"
#include "../../sqlite-library/sqlite3.h"

/**
 * 
 */
class MYPROJECT_API ASqlUtil
{

public:
	static const std::string DirectoryDB;
	struct Character {
		std::string name;
		int id;
		double damage;
	};
	static int OpenConnection();
	static int AddToDB(std::string TableName, ASqlUtil::Character* Character);
};