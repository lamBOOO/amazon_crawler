#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QWebEnginePage>

class AmazonProduct {
 public:
  AmazonProduct(QString, QString, float, float);
  float GetAmazonPrice();
  float GetWhdPrice();
  QString GetName();
  QString GetInfo();
  QString GetAsin();
 private:
  AmazonProduct();
  QString name;
  QString asin;
  float amazon_price;
  float whd_price;
};

#endif // PRODUCT_H
