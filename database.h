#ifndef DATABASE_HH
#define DATABASE_HH

#include <QSqlQueryModel>
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
  bool AddProductToDatabase(QString);
  void SetCurrentTable(QString);
  QSqlQueryModel *GetTableModel(QString /*table*/);
  QList<QString> GetTableNames();
 private:
  QString hostname;
  QString database_name;
  QString username;
  QString password;
  QString current_table;

  QSqlDatabase database;
};

#endif // DATABASE_HH
