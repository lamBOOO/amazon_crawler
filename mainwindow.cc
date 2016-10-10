#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  central     = new QWidget(this);
  main_layout = new QGridLayout(central);

  this->setWindowTitle("Amazon Crawler");
  this->setCentralWidget(central);

  main_layout->addWidget(SetupDatabaseBox(), 0, 0);
  main_layout->addWidget(SetupTabView(), 0, 1);

  controller = new Controller();
}

MainWindow::~MainWindow() {
  delete central;
}

QTabWidget *MainWindow::SetupTabView() {
  tab_view = new QTabWidget();
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
  connect(load_database_button, SIGNAL(clicked()), this, SLOT(HandleLoadDatabase()));
  load_table_button    = new QPushButton("load table");
  load_table_button->setDisabled(true);

  database_layout->addLayout(database_input_formlayout, 0, 0);
  database_layout->addWidget(load_database_button, 1, 0);
  database_layout->addWidget(load_table_button, 2, 0);

  return database_box;
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
