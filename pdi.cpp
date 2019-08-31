#include "pdi.h"
#include "ui_pdi.h"

pdi::pdi(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::pdi)
{
    ui->setupUi(this);
    label = new QLabel();
    label_2 = new QLabel();
    label_3 = new QLabel();
    //movie = new QMovie("C:\\Documents and Settings\\Danilo\\My Documents\\esti\\anime.gif");


}

pdi::~pdi()
{
    delete ui;
}

// Sair
void pdi::on_actionSair_activated()
{
    delete ui;
}

// Abrir
void pdi::on_actionAbrir_activated()
{
    QString fn = QFileDialog::getOpenFileName( this, tr("Abrir gif"), "C:\\", "Movies (*.gif)", NULL  );
    movie = new QMovie(fn);

    movie->start();
    ui->label->setMovie(movie);
}

// Pause
void pdi::on_pushButton_clicked()
{
    movie->stop();
}

// Play
void pdi::on_pushButton_2_clicked()
{
    movie->start();
}

// Next
void pdi::on_pushButton_3_clicked()
{
    movie->jumpToNextFrame();
}

// Image1
void pdi::on_pushButton_4_clicked()
{
    movie->jumpToNextFrame();
    image3 = movie->currentImage();

    ui->label_2->setPixmap(QPixmap::fromImage(image3));
}

// Image2
void pdi::on_pushButton_5_clicked()
{
    movie->jumpToNextFrame();
    image2 = movie->currentImage();

    ui->label_3->setPixmap(QPixmap::fromImage(image2));
}

// Estimar
void pdi::on_pushButton_6_clicked()
{
    int x=1, y=1;

//    bloco = image1.copy(x, y, 8, 8);
//    for(int w=100;w<40;w++)
//        for(int g=100;g<40;g++)
//        image1.setPixel(g,w,0);

    int numBloco;
    numBloco = floor((image1.height()/8)*(image1.width()/8));

    for(x=0;x<8;x++){
        for(y=0;y<8;y++){
        //int matrizBloco[] = image1.pixel(x,y);
        }
    }

    //ui->label_2->setPixmap(QPixmap::fromImage(image1));
    ui->statusBar->showMessage(QString("Informações(image1): height=") + QString().setNum(image1.height()) + QString(", width=") +
                               QString().setNum(image1.width()) + QString(", depth=") + QString().setNum(image1.depth()));



}
