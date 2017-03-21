#ifndef DATABASE_HH
#define DATABASE_HH

#include "amazonproduct.h"
#include <QSqlQueryModel>
#include <QDebug>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

class Database {
 public:
  Database();
  bool SetDatabase(QString, QString, QString, QString);
  bool LoadDatabase();
  bool AddProductToDatabase(QString);
  bool DeleteProductFromDatabase(QString);
  bool UpdateProduct(AmazonProduct);
  void SetCurrentTable(QString);
  QSqlQueryModel *GetTableModel(QString /*table*/);
  QList<QString> GetTableNames();
  QStringList GetAllProducts();
 private:
  QString hostname;
  QString database_name;
  QString username;
  QString password;
  QString current_table;

  QSqlDatabase database;
};

#endif // DATABASE_HH
