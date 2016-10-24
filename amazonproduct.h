#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QWebEnginePage>

struct AmazonProduct {
  QString name;
  QString asin;
  double amazon_price;
  double warehousedeal_price;
  double idealo_price;
};

#endif // PRODUCT_H
