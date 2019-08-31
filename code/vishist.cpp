#include "vishist.h"
#include "ui_vishist.h"

visHist::visHist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::visHist)
{
    ui->setupUi(this);

    init();
}

visHist::~visHist()
{
    delete ui;
}

void visHist::init()
{
    // Seta tamanho e inicializa variáveis
    //this->setMinimumSize(300,300);
    //this->setMaximumSize(300,300);
    //ui->imagemHist->resize(256,256);

    QString abc;
    abc.setNum(pixHist.width());
    ui->imagemHist->setText(teste);
    //ui->imagemHist->setPixmap(pixHist);
}
