/****************************************************************************

Creator: liyangyao@gmail.com
Date: 2015/2/14

****************************************************************************/
#pragma execution_character_set("utf-8")

#include <QCoreApplication>
#include <QDebug>
#include "sqlitedatabase.h"

SqliteDatabase db;

bool init()
{
    QString fileName = qApp->applicationDirPath() + "/world.db3";
    return db.open((wchar_t *)fileName.utf16());
}

void test_select()
{
    SqliteQuery q(&db, L"select ID,Name from Countries where Name like 'C%'");
    while (q.next())
    {
        qDebug()<<QString::fromWCharArray(q.value(0)->data()) <<"," << QString::fromWCharArray(q.value(1)->data());
    }
}

void test_bind()
{
    db.prepare(L"insert into Countries(Name, Area)values(?, ?)");
    db.bindString(1, L"C_Yangzhou");
    db.bindString(2, L"532");
    db.step();
}

void test_exec()
{
    db.exec(L"delete from Countries where Name = 'C_Yangzhou'");
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    init();

//    test_bind();
//    test_exec();
    test_select();

    return a.exec();
}
