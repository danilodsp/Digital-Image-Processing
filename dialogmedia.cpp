#include "dialogmedia.h"
#include "ui_dialogmedia.h"

dialogMedia::dialogMedia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialogMedia)
{
    ui->setupUi(this);

    stringTamMask = "1";
    tamMask = 1;
    ui->lineEdit_tamMask->setText(stringTamMask);
    ui->lineEdit_ganho->setText("1");

    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowHeight(0, 20);
    ui->tableWidget->setColumnWidth(0, 40);
}

dialogMedia::~dialogMedia()
{
    delete ui;
}

void dialogMedia::on_lineEdit_tamMask_editingFinished()
{
    if((ui->lineEdit_tamMask->text().toInt())%2==0){
        QMessageBox::critical(this,"Erro","Necessario que seja um número ímpar.",QMessageBox::Ok);
    }
    else{
        if((ui->lineEdit_tamMask->text().toInt())>tamMask){
            for(int i=0;i<((ui->lineEdit_tamMask->text().toInt())-tamMask);i++){
                ui->tableWidget->insertRow(tamMask);
                ui->tableWidget->insertColumn(tamMask);
                ui->tableWidget->setRowHeight(tamMask, 20);
                ui->tableWidget->setColumnWidth(tamMask, 40);
            }
            tamMask = (ui->lineEdit_tamMask->text().toInt());
        }
        else{
            for(int i=0;i<=(tamMask-(ui->lineEdit_tamMask->text().toInt()));i++){
                tamMask--;
                ui->tableWidget->removeRow(tamMask);
                ui->tableWidget->removeColumn(tamMask);
            }
        }
    }
}

void dialogMedia::on_pushButton_cancelar_clicked()
{
    this->close();
}

void dialogMedia::on_pushButton_ok_clicked()
{
    //indice[tamMask] = new float;

    int linha=0;
    int coluna=0;
    for(int i=0;i<(tamMask*tamMask);i++){
        if(coluna<tamMask){
            indice[i] = ui->tableWidget->item(linha,coluna)->text().toFloat();
            coluna++;
        }
        else{
            if(linha<tamMask){
                linha++;
            }
            else{
                linha = 0;
            }

            coluna = 0;
            indice[i] = ui->tableWidget->item(linha,coluna)->text().toFloat();
            coluna++;
        }
    }

    ganho = ui->lineEdit_ganho->text().toFloat();
    emit terminou();
}

