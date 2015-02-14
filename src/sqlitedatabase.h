/****************************************************************************

Creator: liyangyao@gmail.com
Date: 2015/2/12

****************************************************************************/

#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include <windows.h>
#include <memory>

class Utf8String
{
public:
    explicit Utf8String(const wchar_t *s)
    {
        m_length = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, NULL, NULL, NULL);
        m_buff = new char[m_length + 1];
        memset(m_buff, 0, m_length + 1);
        WideCharToMultiByte(CP_UTF8, 0, s, -1, m_buff, m_length, NULL, NULL);
    }
    ~Utf8String()
    {
        delete[] m_buff;
    }

    const char *data()
    {
        return m_buff;
    }

    int length()
    {
        return m_length;
    }

private:
    char *m_buff;
    int m_length;
    Utf8String(const Utf8String &);
    Utf8String &operator=(const Utf8String &);
};

class WideString
{
public:
    typedef std::shared_ptr<WideString> Ptr;
    explicit WideString(const char *s):
        m_ref(NULL)
    {
        int nLen = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, NULL) ;
        m_buff = new wchar_t[nLen + 1];
        memset(m_buff, 0, nLen + 1);
        MultiByteToWideChar(CP_UTF8, 0, s, -1, m_buff, nLen);
    }
    WideString(const wchar_t *s):
        m_buff(NULL)
    {
        m_ref = s;
    }

    ~WideString()
    {
        if (m_buff)
        {
            delete[] m_buff;
        }
    }

    const wchar_t *data()
    {
        if (m_ref)
        {
            return m_ref;
        }
        else{
            return m_buff;
        }
    }

private:
    wchar_t *m_buff;
    const wchar_t *m_ref;
    WideString(const WideString &);
    WideString &operator=(const WideString &);
};

class SqliteDatabase
{
public:
    explicit SqliteDatabase();
    ~SqliteDatabase();
    bool open(const wchar_t *fileName, const wchar_t *password = NULL);
    bool exec(const wchar_t *sql);
    struct sqlite3 *handle()
    {
        return m_handle;
    }
    bool prepare(const wchar_t *sql);
    bool bindString(int index, const wchar_t * text);
    bool step();

private:
    bool m_opened;
    struct sqlite3 *m_handle;
    struct sqlite3_stmt *m_stmt;
    SqliteDatabase(const SqliteDatabase &);
    SqliteDatabase &operator=(const SqliteDatabase &);
};

class SqliteQuery
{
public:
    explicit SqliteQuery(SqliteDatabase *db, const wchar_t *sql);
    ~SqliteQuery();
    bool next();
    WideString::Ptr value(int index);

private:
    SqliteDatabase* m_db;
    char **m_result;
    int m_rowCount;
    int m_colCount;
    int m_currentRow;
    SqliteQuery(const SqliteQuery &);
    SqliteQuery &operator=(const SqliteQuery &);
};

#endif // SQLITEDATABASE_H
