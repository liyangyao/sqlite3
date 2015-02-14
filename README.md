# sqlite3
Qt api like sqlite3 c++ wrapper

SqliteDatabase db;
db.open(L"db.db3");

SqliteQuery q(&db, L"select ID,Name from Countries");
while (q.next())
{
    qDebug()<<QString::fromWCharArray(q.value(0)->data()) <<"," << QString::fromWCharArray(q.value(1)->data());
}

