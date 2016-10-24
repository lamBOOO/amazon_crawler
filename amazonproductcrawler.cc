#include "amazonproductcrawler.h"

AmazonProductCrawler::AmazonProductCrawler() {

}

AmazonProduct AmazonProductCrawler::GetProductInfo(QString _asin) {
  web_page.load(kAmazonPriceOfferLink + _asin);
  AmazonProduct product;
  return product;
}

void AmazonProductCrawler::WaitForLoad() {
  QEventLoop loop_waiter;
  QObject::connect(&web_page, SIGNAL(loadFinished(bool)), &loop_waiter,
                   SLOT(quit()));
  loop_waiter.exec();
  qDebug() << "load finished";
}
