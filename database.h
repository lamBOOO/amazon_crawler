#ifndef DATABASE_HH
#define DATABASE_HH

#include <QDebug>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>

class Database {
 public:
  Database();
  bool SetDatabase(QString, QString, QString, QString);
  bool LoadDatabase();
  QList<QString> GetTableNames();
 private:
  QString hostname;
  QString database_name;
  QString username;
  QString password;
  QString table;

  QSqlDatabase database;
};

#endif // DATABASE_HH
