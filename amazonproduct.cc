#include "amazonproduct.h"

AmazonProduct::AmazonProduct(QString _asin, QString _name, float _amz_price, float _whd_price) {
  this->asin          = _asin;
  this->name          = _name;
  this->amazon_price  = _amz_price;
  this->whd_price     = _whd_price;
}

float AmazonProduct::GetAmazonPrice()
{
  return this->amazon_price;
}

float AmazonProduct::GetWhdPrice()
{
  return this->whd_price;
}

QString AmazonProduct::GetName()
{
  return this->name;
}

QString AmazonProduct::GetInfo()
{
  return this->asin + " " + this->name + " " + QString::number(this->amazon_price)
      + " " + QString::number(this->whd_price);
}

QString AmazonProduct::GetAsin()
{
  return this->asin;
}

AmazonProduct::AmazonProduct() {}
