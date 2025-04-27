#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); //opens window
    setWindowTitle("Text Editor");
    this->setCentralWidget(ui->textEdit); //Sets the Text Edit widget as central widget
}

MainWindow::~MainWindow()
{
    delete ui; //destroys window
}




void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->setText("");
    file_path="";
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name_to_open = QFileDialog::getOpenFileName(this, "Open File");
    QFile file(file_name_to_open);
    file_path = file_name_to_open;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Title", "Unable to open file");
        return ;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionSave_triggered()
{
    QString file_to_open = file_path;
    QFile file(file_to_open);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Title", "Unable to save file");
        return ;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush(); file.close();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file_to_open = QFileDialog::getSaveFileName(this, "Save File");
    QFile file(file_to_open);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::critical(this, "Title", "Unable to save file");
        return ;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush(); file.close();
}


void MainWindow::on_actionFInd_triggered()
{
    bool ok;
    QString find_text = QInputDialog::getText(this, "Find", "Enter word to find",QLineEdit::Normal,"", &ok);
    if(ok && !find_text.isEmpty()){
        ui->textEdit->moveCursor(QTextCursor::Start); //Cursor moves to the start of the text
        bool is_found = ui->textEdit->find(find_text);
        if(!is_found){
            QMessageBox::warning(this,"Title","Not Found");
        }
    }
    else{
        QMessageBox::warning(this,"Title","Not Found");
    }
}

