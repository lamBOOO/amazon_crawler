#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "amazonproduct.h"
#include "amazonproductcrawler.h"
#include "database.h"
#include <QSqlQueryModel>
#include <QList>
#include <QString>
#include <QStringList>

/*Searching: SELECT * FROM amazon.products WHERE name LIKE CONCAT('%', 'iPhone' ,'%');*/

class Controller{
 public:
  Controller();
  void SetDatabase(QString, QString, QString, QString);
  void SetCurrentTable(QString);
  bool LoadDatabase();
  bool AddProductToDatabase(QString);
  bool DeleteProductFromDatabase(QString);
  void StartCrawling();
  void StopCrawling();

  QSqlQueryModel *GetTableModel (QString /*table*/);
  QList<QString> GetTableNames();
 private:
  Database *database;
  AmazonProductCrawler *crawler;
  bool crawler_is_active;
};

#endif // CONTROLLER_HH
