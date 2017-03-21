#include "controller.h"

Controller::Controller() {
  database = new Database();
  crawler  = new AmazonProductCrawler();
}

void Controller::SetDatabase(QString _hostname,
                             QString _database_name,
                             QString _username,
                             QString _password) {
  database->SetDatabase(_hostname, _database_name, _username, _password);
}

void Controller::SetCurrentTable(QString _table)
{
  database->SetCurrentTable(_table);
}

bool Controller::LoadDatabase()
{
  if (database) {
    return database->LoadDatabase();
  } else {
    return false;
  }
}

bool Controller::AddProductToDatabase(QString _asin)
{
  bool worked = true;
  while (_asin.indexOf(",")!=-1) {
    QString prd = _asin.left(_asin.indexOf(","));
    worked = database->AddProductToDatabase(prd) && worked;
    _asin = _asin.right(_asin.length()-_asin.indexOf(",")-1);
  }
  return worked && database->AddProductToDatabase(_asin);
}

bool Controller::DeleteProductFromDatabase(QString _asin)
{
  return database->DeleteProductFromDatabase(_asin);
}

void Controller::StartCrawling()
{
  crawler_is_active = true;
  QStringList all_products = database->GetAllProducts();
  int n = all_products.length();
  for (int i=0; i<n; i++) {
    if (!crawler_is_active) break;
    AmazonProduct tmp = this->crawler->GetProductInfo(all_products.at(i));
    if (database->UpdateProduct(tmp)) {
      qDebug() << QString::number(i+1) + "/" + QString::number(n) + " ok: " +
                                                  ": " + tmp.GetInfo();
    } else {
      qDebug() << QString::number(i+1) + "/" + QString::number(n) + " nok: " +
                                                  ": " + tmp.GetInfo();
    }
  }
}

void Controller::StopCrawling()
{
  this->crawler_is_active = false;
}

QSqlQueryModel *Controller::GetTableModel(QString _table) {
  return database->GetTableModel(_table);
}

QList<QString> Controller::GetTableNames()
{
  return database->GetTableNames();
}
