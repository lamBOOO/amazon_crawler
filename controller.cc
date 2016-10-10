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

bool Controller::LoadDatabase()
{
  if (database) {
    return database->LoadDatabase();
  } else {
    return false;
  }
}

QList<QString> Controller::GetTableNames()
{
  return database->GetTableNames();
}
