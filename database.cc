#include "database.h"

Database::Database() {}

bool Database::SetDatabase(QString _hostname,
                   QString _database_name,
                   QString _username,
                   QString _password) {
  const QString kDriver = "QMYSQL";
  if (database.isDriverAvailable(kDriver)) {
    if (!database.isOpen() && !database.isOpenError()) {
      database = QSqlDatabase::addDatabase(kDriver);
    }
    hostname      = _hostname;
    database_name = _database_name;
    username      = _username;
    password      = _password;
    return true;
  } else {
    return false;
  }
}

bool Database::LoadDatabase() {
  database.setHostName(hostname);
  database.setDatabaseName(database_name);
  database.setUserName(username);
  database.setPassword(password);
  if (database.isOpen()) database.close();
  if (database.open()) {
    qDebug() << "Database successful opened" << hostname << database_name <<
                username << password;
    return true;
  } else {
    database.close();
    qDebug() << "Database failed to open";
    return false;
  }
}

QList<QString> Database::GetTableNames() {
  QList<QString> table_names;
  QString query_command = "SELECT table_name FROM information_schema.tables where table_schema='" + database_name + "';";
  QSqlQuery sql_query;
  sql_query.exec(query_command);
  qDebug() << sql_query.lastQuery();
  while (sql_query.next()) {
    table_names.push_back(sql_query.value("table_name").toString());
  }
  return table_names;
}
