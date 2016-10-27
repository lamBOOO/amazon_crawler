#include "database.h"

Database::Database() {}

bool Database::SetDatabase(QString _hostname,
                           QString _database_name,
                           QString _username,
                           QString _password) {
  const QString kDriver = "QMYSQL";
  if (database.isDriverAvailable(kDriver)) {
    if (!database.isOpen() && !database.isOpenError())
      database = QSqlDatabase::addDatabase(kDriver);
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

bool Database::AddProductToDatabase(QString _asin)
{
  if (_asin.size()!=10) return false;
  if (database.isOpen()) {
    QSqlQuery *query = new QSqlQuery();
    query->prepare("INSERT INTO " + current_table + " (asin) VALUES (:asin);");
    query->bindValue(":asin", _asin);
    if (query->exec()) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Database::DeleteProductFromDatabase(QString _asin)
{
  //if (_asin.size()!=10) return false;
  if (database.isOpen()) {
    QSqlQuery *query = new QSqlQuery();
    query->prepare("DELETE FROM " + current_table + " WHERE asin = :asin");
    query->bindValue(":asin", _asin);
    if (query->exec()) {
      query->prepare("SELECT * FROM " + current_table + " WHERE asin = :asin");
      query->bindValue(":asin", _asin);
      query->exec();
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void Database::SetCurrentTable(QString _table)
{
  current_table = _table;
}

QSqlQueryModel *Database::GetTableModel(QString _table) {
  QSqlQueryModel *model = new QSqlQueryModel();
  QSqlQuery *query = new QSqlQuery();
  query->prepare("SELECT * FROM " + _table);
  query->exec();
  model->setQuery(*query);
  return model;
}

QList<QString> Database::GetTableNames() {
  QString kInformationConstant = "information_schema.tables";
  QList<QString> table_names;
  QString query_command = "SELECT table_name FROM " + kInformationConstant +
                          " where table_schema='" + database_name + "';";
  QSqlQuery sql_query;
  sql_query.exec(query_command);
  qDebug() << sql_query.lastQuery();
  while (sql_query.next()) {
    table_names.push_back(sql_query.value("table_name").toString());
  }
  return table_names;
}
