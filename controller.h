#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "database.h"
#include <QSqlQueryModel>
#include <QList>
#include <QString>

class Controller{
 public:
  Controller();
  void SetDatabase(QString, QString, QString, QString);
  void SetCurrentTable(QString);
  bool LoadDatabase();
  bool AddProductToDatabase(QString);

  QSqlQueryModel *GetTableModel (QString /*table*/);
  QList<QString> GetTableNames();
 private:
  Database *database;
};

#endif // CONTROLLER_HH
