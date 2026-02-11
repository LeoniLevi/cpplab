#include "IntKeyValueDbMap.h"

#include "sqlite3.h"
#include <string>
#include <vector>



bool checkSqliteResult(int rc, sqlite3* db, const char* action)
{
    if (rc != SQLITE_OK && rc != SQLITE_DONE && rc != SQLITE_ROW) {
        printf("!! [%s] - SQLite Error(rc=%d)\n", action, rc);
        sqlite3_close(db);
        return false;
    }
    return true;
}

sqlite3* activate_kvdb(const char* dbName)
{
    int res = remove(dbName);
    sqlite3* db = NULL;
    int rc = sqlite3_open(dbName, &db);
    if (!checkSqliteResult(rc, db, "IntKeyValueDbMap - Opening database"))
        return NULL;

    char* errMsg = NULL;
    const char* createTableSql =
        "CREATE TABLE ikv_recs ("
        "ikey INTEGER PRIMARY KEY, "
        "ival INTEGER);";
    rc = sqlite3_exec(db, createTableSql, NULL, NULL, &errMsg);
    if (!checkSqliteResult(rc, db, "IntKeyValueDbMap - Createing table"))
        return NULL;
    return db;
}

IntKeyValueDbMap::IntKeyValueDbMap() : db_(NULL) {}

IntKeyValueDbMap::~IntKeyValueDbMap()
{
    Close();
}

bool IntKeyValueDbMap::Open(const char* dbname)
{
    Close();
    db_ = activate_kvdb(dbname);
    if (!db_)
        return false;
    return true;
}

void IntKeyValueDbMap::Close()
{
    if (db_) {
        sqlite3_close(db_);
        db_ = NULL;
    }
}

bool IntKeyValueDbMap::BeginTransaction()
{
    if (!db_)
        return false;
    char* errMsg = NULL;
    int rc = sqlite3_exec(db_, "BEGIN TRANSACTION", NULL, NULL, &errMsg);
    if (!checkSqliteResult(rc, db_, "IntKeyValueDbMap::BeginTransaction"))
        return NULL;
    return true;
}


bool IntKeyValueDbMap::EndTransaction()
{
    if (!db_)
        return false;
    char* errMsg = NULL;
    int rc = sqlite3_exec(db_, "END TRANSACTION", NULL, NULL, &errMsg);
    if (!checkSqliteResult(rc, db_, "IntKeyValueDbMap::EndTransaction"))
        return NULL;
    return true;
}

bool IntKeyValueDbMap::AddRecord(KVItem item)
{
    if (!db_)
        return false;

    char* errMsg = NULL;
    char sqlBuf[128];
    snprintf(sqlBuf, sizeof sqlBuf, "INSERT INTO ikv_recs(ikey, ival) VALUES (%lld, %lld);",
             (long long)item.key, (long long)item.value);
    int rc = sqlite3_exec(db_, sqlBuf, NULL, NULL, &errMsg);
    if (!checkSqliteResult(rc, db_, "IntKeyValueDbMap::AddRecord"))
        return false;
    return true;
}

int selectItemCallback(void* data, int argc, char** argv, char** colNames)
{
    IntKeyValueDbMap::KVItem* item = (IntKeyValueDbMap::KVItem*)data;

    const char* sikey = argv[0];
    const char* sival = argv[1];

    uint32_t* resultVal = (uint32_t*)data;
    char* endptr;
    item->key = strtol(sikey, &endptr, 10);
    item->value = strtol(sival, &endptr, 10);
    return 0; //??
}

IntKeyValueDbMap::FindResult IntKeyValueDbMap::FindAfterValue(int64_t value, KVItem& foundItem)
{
    if (!db_)
        return FindResult::Error;
    char* errMsg = NULL;
    char sqlBuf[128];

    snprintf(sqlBuf, sizeof sqlBuf,
             "SELECT ikey, ival FROM ikv_recs WHERE ival > %lld ORDER BY ival ASC LIMIT 1;",
             (long long)value);
    KVItem item;
    int rc = sqlite3_exec(db_, sqlBuf, selectItemCallback, &item, &errMsg);
    if (!checkSqliteResult(rc, db_, "IntKeyValueDbMap::FindAfterValue"))
        return FindResult::Error;
    if (item.key == INVALID_VALUE)
        return FindResult::NotFound;
    foundItem = item;
    return FindResult::Found;
}

//------------------

IntKeyValueDbMap::Iter IntKeyValueDbMap::StartIterateFromValue(int64_t value, bool backward)
{
    if (!db_)
        return IntKeyValueDbMap::Iter(0);

    char sqlBuf[128];
    if (backward)
    {
        snprintf(sqlBuf, sizeof sqlBuf,
                 "SELECT ikey, ival FROM ikv_recs WHERE ival <= %lld ORDER BY ival DESC", 
                 (long long) value);
    }
    else
    {
        snprintf(sqlBuf, sizeof sqlBuf,
                 "SELECT ikey, ival FROM ikv_recs WHERE ival <= %lld ORDER BY ival ASC", 
                 (long long) value);
    }

    sqlite3_stmt* stmt = NULL;
    int rc = sqlite3_prepare_v2(db_, sqlBuf, -1, &stmt, NULL);
    if (!checkSqliteResult(rc, db_, "IntKeyValueDbMap::StartIterateFromValue"))
       return IntKeyValueDbMap::Iter(0);
    return IntKeyValueDbMap::Iter(stmt);
}

IntKeyValueDbMap::Iter::Iter(sqlite3_stmt* stmt)
{
    stmt_ = stmt;
}

IntKeyValueDbMap::Iter::~Iter()
{
    if (stmt_)
        sqlite3_finalize(stmt_);
}

bool IntKeyValueDbMap::Iter::Valid() const
{
    return stmt_ != 0;
}

bool IntKeyValueDbMap::Iter::Next(KVItem& item)
{
    if (!stmt_)
        return false;
    int rc = sqlite3_step(stmt_);
    if (rc == SQLITE_ROW) {
        item.key = sqlite3_column_int64(stmt_, 0);
        item.value = sqlite3_column_int64(stmt_, 1);
        return true;
    }
    if (rc != SQLITE_DONE)
        printf(" !! Iter::Next ERROR(rc=%d)\n", rc);

    sqlite3_finalize(stmt_);
    stmt_ = NULL;
    return false;
}   

//-------------------

void TryIterateFromVal(IntKeyValueDbMap& ivmap, int64_t value, bool backward)
{
    auto iter = ivmap.StartIterateFromValue(value, backward);
    if (!iter.Valid()) {
        printf(" !! StartIterateFromValue<%lld, %s> failed\n", 
               (long long)value, backward ? "bw" : "fw");
        return;
    }

    printf(" -- Iterate <%s> from value %lld:\n", backward ? "bw" : "fw", (long long)value);
    IntKeyValueDbMap::KVItem item;
    int count = 0;
    while (iter.Next(item)) {
        printf(" --~~-- %d. {%lld, %lld}\n", ++count, (long long)item.key, (long long)item.value);
    }
}

bool tryFindAfterValue(IntKeyValueDbMap& ivmap, int64_t value)
{
    IntKeyValueDbMap::KVItem item;
    auto res = ivmap.FindAfterValue(value, item);
    switch (res) {
        case IntKeyValueDbMap::FindResult::Error:
            printf(" !! FindAfterValue (%lld) - failed(res=%d) !!\n", (long long)value, (int)res);
            return false;
        case IntKeyValueDbMap::FindResult::NotFound:
            printf(" -- FindAfterValue (%lld) - Not Found!\n", (long long)value);
            return true;
    }
    printf(" -- FindAfterValue (%lld) - Found {%llu, %llu}\n", 
           (long long)value, (long long)item.key, (long long)item.value);
    return true;
}

bool TestIntKeyValueDbMap()
{
    printf(" == TestIntKeyValueDbMap started ...\n");

    IntKeyValueDbMap ivmap;
    const char* dbfname = "my_stest.db";
    if (!ivmap.Open(dbfname)) {
        printf(" !! IntKeyValueDbMap::Open failed: %s\n", dbfname);
        return false;
    }

    std::vector<int64_t> values = {25, 27, 27, 28, 16, 22, 3, 30};
    for (unsigned i = 0; i < values.size(); ++i) {
        int64_t key = i + 1;
        int64_t val = values[i];
        if (ivmap.AddRecord(IntKeyValueDbMap::KVItem{ key, val }))
            printf(" -- AddRecord {%lld, %lld} OK\n", (long long)key, (long long)val);
        else
            printf(" -- !! AddRecord {%lld, %lld} failed!!\n", (long long)key, (long long)val);
    }

    tryFindAfterValue(ivmap, 15);
    tryFindAfterValue(ivmap, 27);
    tryFindAfterValue(ivmap, 25);
    tryFindAfterValue(ivmap, 30);
    tryFindAfterValue(ivmap, 35);
    tryFindAfterValue(ivmap, 1);
    tryFindAfterValue(ivmap, 3);
    
    TryIterateFromVal(ivmap, 16);
    TryIterateFromVal(ivmap, 16, true);
    TryIterateFromVal(ivmap, 27);
    TryIterateFromVal(ivmap, 27, true);
    
    printf(" == TestIntKeyValueDbMap completed!\n");
    return true;
}

