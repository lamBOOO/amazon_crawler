#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  central     = new QWidget(this);
  main_layout = new QGridLayout(central);

  this->setWindowTitle("Amazon Crawler");
  this->setCentralWidget(central);

  main_layout->addWidget(SetupDatabaseBox(), 0, 0);
  main_layout->addWidget(SetupTabView(), 0, 1);
  main_layout->addWidget(SetupProductBox(), 0, 2);
  main_layout->addWidget(SetupControlBox(), 0, 3);
  main_layout->setColumnStretch(0, 0);
  main_layout->setColumnStretch(1, 1);

  controller = new Controller();
}

MainWindow::~MainWindow() {
  delete central;
}

QTabWidget *MainWindow::SetupTabView() {
  table_view   = new QTableView();
  tab_view = new QTabWidget();
  tab_view->addTab(table_view, "Table");
  return tab_view;
}

QGroupBox *MainWindow::SetupDatabaseBox() {
  database_box              = new QGroupBox("MySQL Database");
  database_layout           = new QGridLayout(database_box);
  database_input_formlayout = new QFormLayout();

  hostname_label      = new QLabel("hostname:");
  database_name_label = new QLabel("database name:");
  username_label      = new QLabel("username:");
  password_label      = new QLabel("password:");
  table_label         = new QLabel("table:");

  hostname_edit       = new QLineEdit();
  database_name_edit  = new QLineEdit();
  username_edit       = new QLineEdit();
  password_edit       = new QLineEdit();
  table_combobox      = new QComboBox();

  hostname_edit->setText(kHostname);
  database_name_edit->setText(kDatabaseName);
  username_edit->setText(kUsername);
  password_edit->setText(kPassword);
  table_combobox->setDisabled(true);

  database_input_formlayout->addRow(hostname_label, hostname_edit);
  database_input_formlayout->addRow(database_name_label, database_name_edit);
  database_input_formlayout->addRow(username_label, username_edit);
  database_input_formlayout->addRow(password_label, password_edit);
  database_input_formlayout->addRow(table_label, table_combobox);

  load_database_button = new QPushButton("load database");
  connect(load_database_button, SIGNAL(clicked()), this,
          SLOT(HandleLoadDatabase()));
  load_table_button    = new QPushButton("load table");
  load_table_button->setDisabled(true);
  connect(load_table_button, SIGNAL(clicked()), this,
          SLOT(HandleDatabaseTableLoad()));

  database_layout->addLayout(database_input_formlayout, 0, 0);
  database_layout->addWidget(load_database_button, 1, 0);
  database_layout->addWidget(load_table_button, 2, 0);

  return database_box;
}

QGroupBox *MainWindow::SetupProductBox()
{
  product_box           = new QGroupBox("Product Management");
  product_layout        = new QGridLayout(product_box);
  product_box->setEnabled(false);

  product_link_edit     = new QLineEdit("ASIN or ASIN-list (ABC,DEF,GHI,..)");
  add_product_button    = new QPushButton("add product");
  connect(add_product_button, SIGNAL(clicked()), this,
          SLOT(HandleAddProductToDatabase()));
  delete_product_button = new QPushButton("delete product");
  connect(delete_product_button, SIGNAL(clicked()), this,
          SLOT(HandleDeleteProductFromDatabase()));

  product_layout->addWidget(product_link_edit);
  product_layout->addWidget(add_product_button);
  product_layout->addWidget(delete_product_button);

  return product_box;
}

QGroupBox *MainWindow::SetupControlBox()
{
  control_box         = new QGroupBox("Control");
  control_layout      = new QGridLayout(control_box);
  control_box->setEnabled(false);

  crawl_button_start        = new QPushButton("start crawling");
  connect(crawl_button_start, SIGNAL(clicked()), this, SLOT(HandleStartCrawling()));
  crawl_button_stop         = new QPushButton("stop crawling");
  connect(crawl_button_stop, SIGNAL(clicked()), this, SLOT(HandleStopCrawling()));

  control_layout->addWidget(crawl_button_start);
  control_layout->addWidget(crawl_button_stop);

  return control_box;
}

void MainWindow::HandleLoadDatabase()
{
  controller->SetDatabase(hostname_edit->text(), database_name_edit->text(),
                          username_edit->text(), password_edit->text());
  bool load_ok = controller->LoadDatabase();
  if (load_ok) {
    load_table_button->setEnabled(true);
    QList<QString> table_names = controller->GetTableNames();
    if (table_names.size()>0) {
      table_combobox->clear();
      for (int i=0; i<table_names.size(); i++) {
        table_combobox->addItem(table_names.at(i));
        qDebug() << table_names.at(i);
        table_combobox->setEnabled(true);
      }
    } else {
      table_combobox->addItem("unable to load tables");
      table_combobox->setDisabled(true);
    }

  } else {
    load_table_button->setDisabled(true);
    table_combobox->setDisabled(true);
  }
}

void MainWindow::HandleDatabaseTableLoad() {
  table_view->setModel(controller->GetTableModel(table_combobox->
                                                 currentText()));
  controller->SetCurrentTable(table_combobox->currentText());
  control_box->setEnabled(true);
  product_box->setEnabled(true);
}

void MainWindow::HandleAddProductToDatabase()
{
  if (controller->AddProductToDatabase(product_link_edit->text())) {
    product_link_edit->setText("worked");
  } else {
    product_link_edit->setText("failed");
  }
  HandleDatabaseTableLoad();
}

void MainWindow::HandleDeleteProductFromDatabase()
{
  if (controller->DeleteProductFromDatabase(product_link_edit->text())) {
    product_link_edit->setText("worked");
  } else {
    product_link_edit->setText("failed");
  }
  HandleDatabaseTableLoad();
}

void MainWindow::HandleStartCrawling()
{
  controller->StartCrawling();
  HandleDatabaseTableLoad();
}

void MainWindow::HandleStopCrawling()
{
  controller->StopCrawling();
  HandleDatabaseTableLoad();
}
