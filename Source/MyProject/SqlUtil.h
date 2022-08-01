// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "string.h"
#include "../../sqlite-library/sqlite3.h"
/**
 * 
 */
class MYPROJECT_API SqlUtil
{
public:
	SqlUtil();
	~SqlUtil();
	static int OpenConnection();
	static int AddToDB(std::string TableName);
};
