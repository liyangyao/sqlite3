/****************************************************************************

Creator: liyangyao@gmail.com
Date: 2015/2/12

****************************************************************************/
#pragma execution_character_set("utf-8")

#include "sqlitedatabase.h"
#include "sqlite3.h"
#include "windows.h"

SqliteDatabase::SqliteDatabase():
    m_opened(false),
    m_stmt(NULL)
{
}

SqliteDatabase::~SqliteDatabase()
{
    if (m_opened)
    {
        sqlite3_close(m_handle);
    }
}


bool SqliteDatabase::open(const wchar_t *fileName , const wchar_t *password)
{
    if (m_opened)
    {
        return true;
    }

    Utf8String s(fileName);
    m_opened = sqlite3_open_v2(s.data(),
                               &m_handle,
                               SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE,
                               NULL) == SQLITE_OK;
    if (m_opened && password)
    {
        Utf8String key(password);
        sqlite3_key(m_handle, key.data(), strlen(key.data()));
    }
    return m_opened;
}

bool SqliteDatabase::exec(const wchar_t *sql)
{
    Utf8String s(sql);
    return sqlite3_exec(m_handle, s.data(), NULL, NULL, NULL) == SQLITE_OK;
}

bool SqliteDatabase::prepare(const wchar_t *sql)
{
    Utf8String uSql(sql);
    return SQLITE_OK == sqlite3_prepare_v2(m_handle, uSql.data(), -1, &m_stmt, 0);
}

bool SqliteDatabase::bindString(int index, const wchar_t *text)
{
    return SQLITE_OK == sqlite3_bind_text16(m_stmt, index, text, -1, 0);
}

bool SqliteDatabase::step()
{
    int ret = sqlite3_step(m_stmt);
    sqlite3_finalize(m_stmt);
    m_stmt = NULL;
    return SQLITE_OK == ret;
}

SqliteQuery::SqliteQuery(SqliteDatabase *db, const wchar_t *sql):
    m_result(NULL),
    m_rowCount(0),
    m_colCount(0),
    m_currentRow(0)
{
    Utf8String uSql(sql);
    sqlite3_get_table(db->handle(), uSql.data(), &m_result, &m_rowCount, &m_colCount, NULL);
}

SqliteQuery::~SqliteQuery()
{
    sqlite3_free_table(m_result);
}

bool SqliteQuery::next()
{
    m_currentRow++;
    return m_currentRow<=m_rowCount;
}

WideString::Ptr SqliteQuery::value(int index)
{
    WideString::Ptr s(new WideString(m_result[m_currentRow*m_colCount + index]));
    return s;
}
