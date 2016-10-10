#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "database.h"
#include <QList>
#include <QString>

class Controller{
 public:
  Controller();
  void SetDatabase(QString, QString, QString, QString);
  bool LoadDatabase();
  QList<QString> GetTableNames();
 private:
  Database *database;
};

#endif // CONTROLLER_HH
