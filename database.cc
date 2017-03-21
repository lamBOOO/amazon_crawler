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
  if (database.isOpen()) {
    QSqlQuery *search_query = new QSqlQuery();
    search_query->prepare("SELECT * FROM " + current_table + " WHERE asin = :asin");
    search_query->bindValue(":asin", _asin);
    search_query->exec();
    if(search_query->next()){
      QSqlQuery *delete_query = new QSqlQuery();
      delete_query->prepare("DELETE FROM " + current_table + " WHERE asin = :asin");
      delete_query->bindValue(":asin", _asin);
      if (delete_query->exec()) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Database::UpdateProduct(AmazonProduct _prd)
{
  QSqlQuery query;
  query.prepare("SELECT name,amazon_price1,whd_price1 FROM " + current_table +
                " WHERE asin = '" + _prd.GetAsin() + "'");
  if (!query.exec()) return false;
  bool has_to_be_updated = false;;
  if (query.next()) {
    if (QString::number(_prd.GetAmazonPrice()) != query.value(1).toString()) {
      has_to_be_updated = true;
      QSqlQuery query2;
      query2.prepare("UPDATE " + current_table +
                    " SET amazon_price2 = :amazon_price2" +
                    " WHERE asin = '" + _prd.GetAsin() + "'");
      query2.bindValue(":amazon_price2", query.value(0));
      query2.exec();
    }
    if (QString::number(_prd.GetWhdPrice()) != query.value(2).toString()) {
      has_to_be_updated = true;
      QSqlQuery query2;
      query2.prepare("UPDATE " + current_table +
                    " SET whd_price2 = :whd_price2" +
                    " WHERE asin = '" + _prd.GetAsin() + "'");
      query2.bindValue(":whd_price2", query.value(1));
      query2.exec();
    }
  } else {
    return false;
  }
  if (has_to_be_updated) {
    query.prepare("UPDATE " + current_table +
                  " SET name = :name, " + "amazon_price1 = :amazon_price1, " +
                  "whd_price1 = :whd_price1 WHERE asin = '" + _prd.GetAsin() + "'");
    query.bindValue(":name", _prd.GetName());
    query.bindValue(":amazon_price1", _prd.GetAmazonPrice());
    query.bindValue(":whd_price1", _prd.GetWhdPrice());
    if (query.exec()) {
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
  const QString kInformationConstant = "information_schema.tables";
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

QStringList Database::GetAllProducts()
{
  QSqlQuery query;
  query.prepare("SELECT asin FROM " + current_table);
  query.exec();
  QStringList all_products;
  while (query.next()) {
    QString asin = query.value(0).toString();
    all_products.append(asin);
  }
  return  all_products;
}
