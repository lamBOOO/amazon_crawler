#ifndef AMAZONPRODUCTCRAWLER_H
#define AMAZONPRODUCTCRAWLER_H

#include "amazonproduct.h"
#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QWebEnginePage>

class AmazonProductCrawler {
 public:
  AmazonProductCrawler();
  AmazonProduct GetProductInfo(QString /*asin*/);
private:
  const QString kAmazonPriceOfferLink = "https://www.amazon.de/gp/offer-listing/";/*asin*/
  void WaitForLoad();
  QWebEnginePage web_page;
};

#endif // AMAZONPRODUCTCRAWLER_H
