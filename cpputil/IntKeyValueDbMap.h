#pragma once

#include <stdint.h>

struct sqlite3_stmt;
struct sqlite3;

class IntKeyValueDbMap {
public:
	struct KVItem { int64_t key; int64_t value; };
	
	IntKeyValueDbMap();
	~IntKeyValueDbMap();
	
	bool Open(const char* dbname);
	bool IsOpen() { return db_; }
	void Close();
	
	bool BeginTransaction();
	bool EndTransaction();
	
	bool AddRecord(KVItem item);
	
	enum class FindResult { Found=1, NotFound=0, Error=-1};
	FindResult FindAfterValue(int64_t value, KVItem& foundItem);
	
	class Iter {
	public:
		Iter(sqlite3_stmt* stmt);
		~Iter();
		bool Valid() const;
		bool Next(KVItem& foundItem);
	private:
		struct sqlite3_stmt* stmt_;
	};
	Iter StartIterateFromValue(int64_t value, bool backward = false);
	
private:
	struct sqlite3* db_;
	enum { INVALID_VALUE=0xFFFFFFFF };
};

void TryIterateFromVal(IntKeyValueDbMap& ivmap, int64_t value, bool backward=false);
bool TestIntKeyValueDbMap();

	