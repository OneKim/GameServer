#pragma once
#include "stdafx.h"
#include "ADODatabase.h"

typedef enum
{
	QUERY_NOT_RETURN,				//리턴 없는 쿼리
	QUERY_WAIT_RETURN,				//DB 응답을 꼭 기다린 뒤 처리하는 쿼리
	QUERY_CALL_BACK,				//DB 응답을 기다리지 않지만 뒤처리 있는 쿼리
}QUERY_TYPE;

class QueryStatement
{
	ADODB::_CommandPtr			command_;
	QUERY_TYPE					type_;

	wstr_t						query_;
	int							paramCount_;

public:
	QueryStatement();
	~QueryStatement();

	void	setQuery(WCHAR *query, QUERY_TYPE type = QUERY_NOT_RETURN);

	const WCHAR *query();
	QUERY_TYPE type();

	//-------------------------------- 파라 미터 추가 ---------------------------------//
	template<typename T>
	void	addArg(WCHAR *fmt, T value);
	
	void	addParam(CHAR *value);
	void	addParam(WCHAR *value);
	void	addParam(INT32 value);
	void	addParam(UINT32 value);
	void	addParam(INT64 value);
	void	addParam(UINT64 value);
	void	addParam(FLOAT value);
	void	addParam(DOUBLE value);
};
