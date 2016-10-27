#include "controller.h"

Controller::Controller() {
  database = new Database();
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
  return database->AddProductToDatabase(_asin);
}

bool Controller::DeleteProductFromDatabase(QString _asin)
{
  return database->DeleteProductFromDatabase(_asin);
}

void Controller::StartCrawling()
{

}

QSqlQueryModel *Controller::GetTableModel(QString _table) {
  return database->GetTableModel(_table);
}

QList<QString> Controller::GetTableNames()
{
  return database->GetTableNames();
}
