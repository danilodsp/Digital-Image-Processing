#include "pdi.h"
#include "ui_pdi.h"

PDI::PDI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PDI)
{
    ui->setupUi(this);
    this->setMinimumSize(861,573);
    this->setMaximumSize(861,573);

    init();
}

PDI::~PDI()
{
    delete ui;
}

void PDI::init()
{
    // Connect's
    connect(ui->actionAbrir,SIGNAL(triggered(bool)),this,SLOT(abrir()));
    connect(ui->actionSalvar,SIGNAL(triggered(bool)),this,SLOT(salvar()));
    connect(ui->actionSobre,SIGNAL(triggered(bool)),this,SLOT(openSobre()));
    connect(ui->actionAjuda,SIGNAL(triggered(bool)),this,SLOT(openAjuda()));
    connect(ui->actionEqlHist,SIGNAL(triggered(bool)),this,SLOT(eqlHist()));
    connect(ui->actionNegativa,SIGNAL(triggered(bool)),this,SLOT(negativa()));
    connect(ui->actionLog,SIGNAL(triggered(bool)),this,SLOT(openLog()));
    connect(ui->actionPotencia,SIGNAL(triggered(bool)),this,SLOT(openPot()));
    connect(ui->visImg1,SIGNAL(clicked()),this,SLOT(openImgGrd1()));
    connect(ui->visImg2,SIGNAL(clicked()),this,SLOT(openImgGrd2()));
    connect(ui->remImg1,SIGNAL(clicked()),this,SLOT(removerImg()));
    connect(ui->actionSubtracao,SIGNAL(triggered(bool)),this,SLOT(openSub()));
    connect(ui->actionMedia,SIGNAL(triggered(bool)),this,SLOT(openMedia()));
    connect(ui->actionMediaVC,SIGNAL(triggered(bool)),this,SLOT(openMediaImgs()));
    connect(ui->actionMediana,SIGNAL(triggered(bool)),this,SLOT(openMediana()));
    connect(ui->actionRoberts,SIGNAL(triggered()),this,SLOT(roberts()));
    connect(ui->actionSobel,SIGNAL(triggered()),this,SLOT(sobel()));
    connect(ui->actionLaplaciano,SIGNAL(triggered()),this,SLOT(laplaciano()));
    connect(ui->actionCam,SIGNAL(triggered()),this,SLOT(cam()));
    connect(ui->actionButterworth,SIGNAL(triggered()),this,SLOT(butterworth()));

    // Variáveis
    showHistConsole = false;
    hasImage = false;
    imagemGrande = false;
    isCam = false;
    divisorHist = 8192;
    ui->slider_t1->setEnabled(false);
    ui->slider_t2->setEnabled(false);
}

void PDI::abrir()
{
    // Abrir imagem
    fn = QFileDialog::getOpenFileName(this, tr("Abrir imagem"), "C:\\", "Imagens (*.jpg *.png *.pgm)", NULL);
    imagem.load(fn);

    // Verifica se foi aberto alguma imagem
    if(!imagem.isNull()){
        ui->console->appendPlainText("Imagem carregada: " + fn);
        hasImage = true;
        //imagem = imagem.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);
        L = imagem.numColors(); // Números de cores
        M = imagem.width(); // Largura da imagem
        N = imagem.height(); // Altura da imagem
        tam = M*N; // Tamanho da imagem
        ui->remImg1->setEnabled(true);
        ui->visHist1->setEnabled(true);
        int contador;
        int valorPixel;

        if(imagem.format()!=QImage::Format_Indexed8){
            ui->console->appendPlainText("Passando imagem para tons de cinza, com porpiredade de 256 cores, 8 bits.");
            for(int y=0;y<N;y++){
                for(int x=0;x<M;x++){
                    //valorPixel = (imagem.pixelIndex(x,y)); // Pega o nível de cinza do pixel
                    valorPixel = (imagem.pixel(x,y)); // Pega o nível de cinza do pixel
                    imagem.setPixel(x,y,qRgb(valorPixel,valorPixel,valorPixel));
                }
            }
            imagem = imagem.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);
            fn.remove(fn.size()-4,4);
            imagem.save(fn+"_grayscale.jpg","JPG");
            imagem.load(fn+"_grayscale.jpg");
        }
        imagem = imagem.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);

        QString string0;
        string0.setNum(N);
        ui->label_alt->setText(string0);
        string0.setNum(M);
        ui->label_larg->setText(string0);
        string0.setNum(imagem.depth());
        ui->label_depth->setText(string0);
        string0.setNum(L);
        ui->label_numCores->setText(string0);
        ui->tab->setFocus();

        QString string1;
        QString string2;
        if(showHistConsole){
            ui->console->appendPlainText("Nível de cinza - Quantidade");
        }

        // Desenho do histograma
        QPixmap pixHist(256,256);
        pixHist.fill(QColor("white"));
        QPainter painter(&pixHist);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
        painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));

        // Zera vetor
        for(int x=0;x<256;x++){
            hist[x] = 0;
        }

        // Calculo do histograma
        for(int y=0;y<N;y++){
            for(int x=0;x<M;x++){
                valorPixel = (imagem.pixelIndex(x,y)); // Pega o nível de cinza do pixel
                //valorPixel = (imagem.pixel(x,y)); // Pega o nível de cinza do pixel
                //imagem.setPixel(x,y,qRgb(valorPixel,valorPixel,valorPixel));
                //valorPixel = (qRed(imagem.pixel(x,y))+qGreen(imagem.pixel(x,y))+qBlue(imagem.pixel(x,y)))/3; // Pega o nível de cinza do pixel
                valorPixel = floor(valorPixel); // Arredonda
                contador = hist[valorPixel] + 1; // Conta a quantidade que ocorre
                if(showHistConsole){ // Mostra no console
                    string1.setNum(valorPixel);
                    string2.setNum(hist[valorPixel]+1);
                    ui->console->appendPlainText(string1 + " - " + string2);
                }
                hist[valorPixel] = contador; // Carrega no vetor
            }
        }

        // Desenhando o histograma
        for(int x=0;x<256;x++){
            painter.drawLine(x,255,x,(255-floor((hist[x])/(tam/divisorHist)))); // Com um divisor de 8
        }

        pixHistS = pixHist; // Salvando histograma

        ui->imagem->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->imagem,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(clickDireitoImg(QPoint)));

        if((M>256)|(N>256)){
            imagemGrande = true;
            ui->visImg1->setEnabled(true);
            ui->imagem->setText("Para visualizar esta imagem deve \nclicar em Visualizar Imagem.");
        }
        else{
            imagemGrande = false;
            ui->imagem->setPixmap(QPixmap::fromImage(imagem)); // Mostra a imagem no label
            ui->visImg1->setEnabled(false);
        }
    }
}

// Salvar imagem de saída
void PDI::salvar()
{
    if(!imagem2.isNull()){
        QString fnSave = QFileDialog::getSaveFileName(this, tr("Salvar imagem de saída"), "C:\\", "Imagens (*.jpg)", NULL);

        imagem2.save(fnSave);
    }
}

void PDI::openSobre()
{
    janelaSobre = new sobre();

    janelaSobre->show();
}

void PDI::openAjuda()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile("./help.chm"))){
        if(!QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Program Files (x86)/PDI/help.chm"))){
            if(!QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Program Files/PDI/help.chm"))){
                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Arquivos de programas/PDI/help.chm"));
            }
        }
    }
}

// Clique direito do mouse
void PDI::clickDireitoImg(QPoint)
{
    if(hasImage&(!imagemGrande)){
        // Criando menu para quando clicar do lado direito na imagem
        QMenu menu(ui->imagem);

        QAction *remover = menu.addAction("Remover imagem");
        QObject::connect(remover,SIGNAL(triggered(bool)),this,SLOT(removerImg()));

        menu.exec(ui->imagem->mapTo(ui->imagem,QCursor::pos()));
    }
}

// Remover imagem
void PDI::removerImg()
{
    hasImage = false;
    ui->imagem->clear();
    ui->imagem2->clear();
    ui->visHist1->setEnabled(false);
    ui->visHist2->setEnabled(false);
    ui->visImg1->setEnabled(false);
    ui->visImg2->setEnabled(false);
    ui->remImg1->setEnabled(false);
    ui->console->appendPlainText("Imagem removida.");
}

// Visulizar imagem de entrada grande
void PDI::openImgGrd1()
{
    imagemMaior1 = new QDialog(this);
    imagemMaior1->setWindowTitle("Imagem de entrada");

    QLabel *imagemM1 = new QLabel(imagemMaior1);
    imagemM1->resize(M,N);
    imagemM1->setPixmap(QPixmap::fromImage(imagem));

    QScrollArea *area = new QScrollArea(imagemMaior1);
    area->setBackgroundRole(QPalette::Dark);
    area->setWidget(imagemM1);

    imagemMaior1->showMaximized();
    area->setMinimumSize(imagemMaior1->size());
}

// Visulizar imagem de saída grande
void PDI::openImgGrd2()
{
    imagemMaior2 = new QDialog(this);
    imagemMaior2->setWindowTitle("Imagem de saída");

    QLabel *imagemM2 = new QLabel(imagemMaior2);
    imagemM2->resize(M,N);
    imagemM2->setPixmap(QPixmap::fromImage(imagem2));

    QScrollArea *area = new QScrollArea(imagemMaior2);
    area->setBackgroundRole(QPalette::Dark);
    area->setWidget(imagemM2);

    imagemMaior2->showMaximized();
    area->setMinimumSize(imagemMaior2->size());
}

// Visualização do histograma
void PDI::on_visHist1_clicked()
{
    // Mostrando o histograma em uma janela
    visHist = new QDialog(this);
    visHist->setMinimumSize(256,256);
    visHist->setMaximumSize(256,256);
    visHist->setWindowTitle("Histograma");

    QLabel *imagemHist = new QLabel(visHist);
    imagemHist->setPixmap(pixHistS);
    imagemHist->resize(256,256);

    visHist->show();
}

// Equalização do histograma
void PDI::eqlHist()
{
    if(hasImage){
        imagem2 = imagem;
        float pr;
        int valorPixel;
        QString valorVetorS;
        ui->console->appendPlainText("Operação equalização do histograma.");

        // Calculando o histograma equalizado
        for(int i=0;i<256;i++){
            for(int x=0;x<=i;x++){
                pr += (hist[x])/(tam);
            }
            histEql[i] = pr*255;
            if(showHistConsole){
                valorVetorS.setNum(histEql[i]);
                ui->console->appendPlainText("Valor - " + valorVetorS);
            }
            pr = 0;
        }

        // Setando pixels da imagem equalizada
        for(int y=0;y<N;y++){
            for(int x=0;x<M;x++){
                valorPixel = (imagem.pixelIndex(x,y));
                valorPixel = floor(valorPixel);
                imagem2.setPixel(x,y,floor(histEql[valorPixel]));
            }
        }

        // Desenhando o histograma equalizado
        QPixmap pixHistEql(256, 256);
        pixHistEql.fill(QColor("white"));
        QPainter painter(&pixHistEql);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
        painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
        for(int w=0;w<256;w++){
            painter.drawLine(w,255,w,(255-floor((histEql[w])/8)));
        }

        pixHistEqlS = pixHistEql; // Salvando histograma equalizado
        ui->visHist2->setEnabled(true); // Habilitando botão de visualizar

        // Mostrando imagem de saída
        mostrarImg2();
    }
}

void PDI::on_visHist2_clicked()
{
    // Mostrando o histograma equalizado em uma janela
    visHistEql = new QDialog(this);
    visHistEql->setMinimumSize(256,256);
    visHistEql->setMaximumSize(256,256);
    visHistEql->setWindowTitle("Histograma Equalizado");

    QLabel *imagemHistEql = new QLabel(visHistEql);
    imagemHistEql->setPixmap(pixHistEqlS);
    imagemHistEql->resize(256,256);

    visHistEql->show();
}

// Negativa
void PDI::negativa()
{
    if(hasImage){
        imagem2 = imagem;
        ui->console->appendPlainText("Operação negativa.");

        // Calculando a negativa
        for(int x=0;x<imagem.width();x++){
            for(int y=0;y<imagem.height();y++){
                imagem2.setPixel(x,y,floor(255 - (imagem.pixelIndex(x,y))));
            }
        }

        // Mostrando imagem de saída
        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Abrir janela do Log
void PDI::openLog()
{
    if(hasImage){
        // Solicitando uma constante
        dialogLog = new QDialog(this);
        dialogLog->setMinimumSize(200,100);
        dialogLog->setMaximumSize(200,100);
        dialogLog->setWindowTitle("Função Log");


        QLabel *constante = new QLabel("Constante (c):", dialogLog);
        textoConstLog = new QLineEdit(dialogLog);
        QLabel *formula = new QLabel("f = c * log(1+i)", dialogLog);
        QPushButton *ok = new QPushButton("Ok", dialogLog);

        QHBoxLayout *layout1 = new QHBoxLayout;
        layout1->addWidget(constante);
        layout1->addWidget(textoConstLog);

        QVBoxLayout *layout2 = new QVBoxLayout;
        layout2->addLayout(layout1);
        layout2->addWidget(formula);
        layout2->addWidget(ok);

        dialogLog->setLayout(layout2);

        dialogLog->show();

        connect(ok,SIGNAL(clicked()),this,SLOT(logaritmo()));
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Função log
void PDI::logaritmo()
{
    dialogLog->close();
    float valorConst;
    float maxValor = 0;
    valorConst = textoConstLog->text().toFloat();
    ui->console->appendPlainText("Operação logaritmo. Parâmetros: c = " + textoConstLog->text());

    if(hasImage){
        imagem2 = imagem;

        // Encontrando o valor máximo
        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){
                if(valorConst * log(1 + (imagem.pixelIndex(x,y))) > maxValor)
                    maxValor = valorConst * log(1 + (imagem.pixelIndex(x,y)));
            }
        }

        // Calculando o log e normalizando
        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){
                imagem2.setPixel(x,y, floor(((valorConst * log(1 + (imagem.pixelIndex(x,y))))/maxValor)*255) );
            }
        }

        // Mostrando imagem de saída
        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Abrir janela da Potência
void PDI::openPot()
{
    if(hasImage){
        // Solicitando duas constantes
        dialogPot = new QDialog(this);
        dialogPot->setMinimumSize(200,140);
        dialogPot->setMaximumSize(200,140);
        dialogPot->setWindowTitle("Função Potência");


        QLabel *constante = new QLabel("Constante (c):", dialogPot);
        textoConstPot = new QLineEdit(dialogPot);

        QHBoxLayout *layout1 = new QHBoxLayout;
        layout1->addWidget(constante);
        layout1->addWidget(textoConstPot);

        QLabel *constante2 = new QLabel("Constante (a):", dialogPot);
        textoConstPotA = new QLineEdit(dialogPot);

        QHBoxLayout *layout2 = new QHBoxLayout;
        layout2->addWidget(constante2);
        layout2->addWidget(textoConstPotA);

        QLabel *formula = new QLabel("s = c * r^a", dialogPot);
        QPushButton *ok = new QPushButton("Ok", dialogPot);

        QVBoxLayout *layout3 = new QVBoxLayout;
        layout3->addLayout(layout1);
        layout3->addLayout(layout2);
        layout3->addWidget(formula);
        layout3->addWidget(ok);

        dialogPot->setLayout(layout3);

        dialogPot->show();

        connect(ok,SIGNAL(clicked()),this,SLOT(potencia()));
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Funçao Potência
void PDI::potencia()
{
    dialogPot->close();
    float valorConst;
    float valorConstA;
    float maxValor = 0;
    valorConst = textoConstPot->text().toFloat(); // Constante (c)
    valorConstA = textoConstPotA->text().toFloat(); // Constante (a)
    ui->console->appendPlainText("Operação potência. Parâmetros: c = " + textoConstPot->text() + ", a = " + textoConstPotA->text());

    if(hasImage){
        imagem2 = imagem;

        // Encontrando o valor máximo
        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){
                if(valorConst * pow((imagem.pixelIndex(x,y)),valorConstA) > maxValor)
                    maxValor = valorConst * pow((imagem.pixelIndex(x,y)),valorConstA);
            }
        }

        // Calculando a potência e normalizando
        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){
                imagem2.setPixel(x,y, floor(((valorConst * pow((imagem.pixelIndex(x,y)),valorConstA))/maxValor)*255) );
            }
        }

        // Mostrar imagem de saída
        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Habilita mostrar no console dados
void PDI::on_checkBox_showHistCons_clicked()
{
    if(ui->checkBox_showHistCons->isChecked()){
        showHistConsole = true;
    }
    else{
        showHistConsole = false;
    }
}

// Mostrar imagem de saída
void PDI::mostrarImg2()
{
    if(isCam){
        //ui->imagem2->setPixmap(QPixmap::fromImage(imagem2));
    }
    else if(imagemGrande){
        ui->visImg2->setEnabled(true);
        ui->imagem2->setText("Para visualizar esta imagem deve \nclicar em Visualizar Imagem.");
    }
    else{
        ui->imagem2->setPixmap(QPixmap::fromImage(imagem2));
    }
}

// Mostrar janela da subtração
void PDI::openSub()
{
    dialogSub = new QDialog(this);
    dialogSub->setMinimumSize(300,140);
    dialogSub->setMaximumSize(300,140);
    dialogSub->setWindowTitle("Função Subtração");

    QLabel *fileNome1 = new QLabel("Imagem 1:", dialogSub);
    fn1 = new QLineEdit(dialogSub);
    fn1->setReadOnly(true);
    QPushButton *inserir1 = new QPushButton("Abrir...", dialogSub);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(fileNome1);
    layout1->addWidget(fn1);
    layout1->addWidget(inserir1);

    QLabel *fileNome2 = new QLabel("Imagem 2:", dialogSub);
    fn2 = new QLineEdit(dialogSub);
    fn2->setReadOnly(true);
    QPushButton *inserir2 = new QPushButton("Abrir...", dialogSub);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(fileNome2);
    layout2->addWidget(fn2);
    layout2->addWidget(inserir2);

    QPushButton *ok = new QPushButton("Ok", dialogSub);

    QVBoxLayout *layout3 = new QVBoxLayout;
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    layout3->addWidget(ok);

    dialogSub->setLayout(layout3);

    dialogSub->show();

    connect(inserir1,SIGNAL(clicked()),this,SLOT(openFileSub1()));
    connect(inserir2,SIGNAL(clicked()),this,SLOT(openFileSub2()));
    connect(ok,SIGNAL(clicked()),this,SLOT(subtracao()));
}

// Abrir imagem 1 da subtração
void PDI::openFileSub1()
{
    QImage imagemTest;
    QString fn = QFileDialog::getOpenFileName(this, tr("Abrir imagem"), "C:\\", "Imagens (*.jpg *.png *.pgm)", NULL);
    imagemTest.load(fn);

    // Verifica se a imagem foi carregada
    if(!imagemTest.isNull()){
        fn1->setText(fn);
    }
}

// Abrir imagem 2 da subtração
void PDI::openFileSub2()
{
    QImage imagemTest;
    QString fn = QFileDialog::getOpenFileName(this, tr("Abrir imagem"), "C:\\", "Imagens (*.jpg *.png *.pgm)", NULL);
    imagemTest.load(fn);

    // Verifica se a imagem foi carregada
    if(!imagemTest.isNull()){
        fn2->setText(fn);
    }
}

// Operação de subtração
void PDI::subtracao()
{
    dialogSub->close();
    QImage imagemSub1;
    QImage imagemSub2;
    imagemSub1.load(fn1->text());
    imagemSub2.load(fn2->text());
    imagem2 = imagemSub1;

    if((imagemSub1.width()==imagemSub2.width())&(imagemSub1.height()==imagemSub2.height())){

        for(int y=0;y<imagemSub1.height();y++){
            for(int x=0;x<imagemSub1.width();x++){
                if((imagemSub1.pixelIndex(x,y)-imagemSub2.pixelIndex(x,y)) > 0)
                    imagem2.setPixel(x,y,(imagemSub1.pixelIndex(x,y)-imagemSub2.pixelIndex(x,y)));
                else
                    imagem2.setPixel(x,y,(imagemSub2.pixelIndex(x,y)-imagemSub1.pixelIndex(x,y)));
            }
        }

        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Tentativa de subtrair imagens de tamanho diferentes.",QMessageBox::Ok);
    }
}

// ********************** FILTROS **********************

// Janela do filtro da mediana
void PDI::openMediana()
{
    dialogMediana = new QDialog(this);
    dialogMediana->setMinimumSize(200,140);
    dialogMediana->setMaximumSize(200,140);
    dialogMediana->setWindowTitle("Filtro da Mediana");

    QLabel *label = new QLabel("Largura do filtro:",dialogMediana);
    textoConstMediana = new QLineEdit(dialogMediana);
    QPushButton *ok = new QPushButton("Ok", dialogMediana);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(label);
    layout->addWidget(textoConstMediana);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addLayout(layout);
    layout2->addWidget(ok);

    dialogMediana->setLayout(layout2);
    dialogMediana->show();

    connect(ok,SIGNAL(clicked()),this,SLOT(mediana()));
}

// Método do filtro da Mediana
void PDI::mediana()
{
    dialogMediana->close();

    if(hasImage){
        imagem2 = imagem;

        int tamMaskMediana;
        int indiceMask = 0;
        tamMaskMediana = textoConstMediana->text().toInt();
        if(tamMaskMediana%2==0)
            tamMaskMediana--;
        ui->console->appendPlainText("Aplicando a mediana.");
        QString string0;
        string0.setNum(tamMaskMediana);
        ui->console->appendPlainText("Tamanho da máscara: " + string0);
        //float mascara[tamMaskMediana][tamMaskMediana];
        std::vector<float> mascara(tamMaskMediana*tamMaskMediana);
        float mediana = 0;

        // Aplicando o filtro da mediana
        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){
                // Encontrar a mediana

                for(int q=(-(tamMaskMediana-1)/2);q<=((tamMaskMediana-1)/2);q++){ // X
                    for(int w=(-(tamMaskMediana-1)/2);w<=((tamMaskMediana-1)/2);w++){ // Y
                        if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                            mascara.at(indiceMask) = imagem.pixelIndex(x+q,y+w);
                        }
                        else{
                            mascara.at(indiceMask) = 0;
                        }
                        indiceMask++;
                    }
                }

                indiceMask = 0;
                sort(mascara.begin(), mascara.end());
                mediana = mascara.at(((tamMaskMediana*tamMaskMediana)-1)/2);

                if(mediana>=0&&mediana<256)
                    imagem2.setPixel(x,y,mediana);
                else
                    imagem2.setPixel(x,y,0);

            }
        }

        ui->imagem2->setPixmap(QPixmap::fromImage(imagem2));

    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Janela da Média
void PDI::openMedia()
{
    janelaMedia = new dialogMedia();

    janelaMedia->show();

    connect(janelaMedia,SIGNAL(terminou()),this,SLOT(filtroMedia()));
}

// Filtro da Média
void PDI::filtroMedia()
{
    janelaMedia->close();
    ui->console->appendPlainText("Aplicando filtro com máscara pré-configurado.");

    if(hasImage){
        imagem2 = imagem;
        tamMask = janelaMedia->tamMask;
        //mascara[tamMask*tamMask];

        QString string0;
        ganho = janelaMedia->ganho;

        string0.setNum(ganho);
        ui->console->appendPlainText("Ganho: "+string0);

        for(int x=0;x<(tamMask*tamMask);x++){
            mascara[x] = janelaMedia->indice[x];
        }

        filtro();
        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }

}

// Filtro genérico
void PDI::filtro()
{
    int indiceMask = 0;
    coeficiente = 0;

    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){


            for(int q=(-(tamMask-1)/2);q<=((tamMask-1)/2);q++){ // X
                for(int w=(-(tamMask-1)/2);w<=((tamMask-1)/2);w++){ // Y
                    if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                        coeficiente += imagem.pixelIndex(x+q,y+w)*mascara[indiceMask];
                    }
                    indiceMask++;
                }
            }

            coeficiente = coeficiente*ganho;
            if((coeficiente<256)&&(coeficiente>=0))
                imagem2.setPixel(x,y,coeficiente);
            else if(coeficiente<256)
                imagem2.setPixel(x,y,0);
            else
                imagem2.setPixel(x,y,255);

            coeficiente = 0;
            indiceMask = 0;
        }
    }

    /*QString string0;
    for(int x=0;x<9;x++){
        string0.setNum(mascara[x]);
        ui->console->appendPlainText(string0);
    }*/

    hasImage = true;
}

// ********************** DETECÇÃO DE BORDAS **********************

// Método de Roberts
void PDI::roberts()
{
    if(hasImage){
        imagem2 = imagem;
        ui->console->appendPlainText("Utilizando operador de Roberts.");

        float gr1, gr2, gr = 0;

        for(int y=0;y<N;y++){
            for(int x=0;x<M;x++){
                gr1 = imagem.pixelIndex(x,y);
                if(x+1<M&&y+1<N)
                    gr1 += (-(imagem.pixelIndex(x+1,y+1)));

                if(y+1<N)
                    gr2 = (-(imagem.pixelIndex(x,y+1)));
                if(x+1<M)
                    gr2 += imagem.pixelIndex(x+1,y);

                //gr = sqrt(pow(gr1,2)+pow(gr2,2));
                gr = 0.9*(fabs(gr1)+fabs(gr2));

                if(gr>0&&gr<256)
                    imagem2.setPixel(x,y,gr);
                else
                    imagem2.setPixel(x,y,0);
            }
        }

        mostrarImg2();

    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Método de Sobel
void PDI::sobel()
{
    if(hasImage){
        imagem2 = imagem;
        ui->console->appendPlainText("Utilizando o operador de Sobel.");

        tamMask = 3;
        float coef1, coef2 = 0; // Coeficientes
        int indiceMask = 0;
        float mascara1[9] = {1, 0, -1 ,2, 0, -2, 1, 0, -1};
        float mascara2[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){


                for(int q=(-(tamMask-1)/2);q<=((tamMask-1)/2);q++){ // X
                    for(int w=(-(tamMask-1)/2);w<=((tamMask-1)/2);w++){ // Y
                        if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                            coef1 += imagem.pixelIndex(x+q,y+w)*mascara1[indiceMask];
                            coef2 += imagem.pixelIndex(x+q,y+w)*mascara2[indiceMask];
                        }
                        indiceMask++;
                    }
                }

                coeficiente = 0.9*(fabs(coef1)+fabs(coef2));
                //coeficiente = sqrt(pow(coef1,2)+pow(coef2,2));

                if((coeficiente<256)&&(coeficiente>=0))
                    imagem2.setPixel(x,y,coeficiente);
                else if(coeficiente<256)
                    imagem2.setPixel(x,y,0);
                else
                    imagem2.setPixel(x,y,255);

                indiceMask = 0;
                coef1 = 0;
                coef2 = 0;
            }
        }

        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// Método Laplaciano
void PDI::laplaciano()
{
    if(hasImage)
    {
        imagem2 = imagem;
        ui->console->appendPlainText("Utilizando o método Laplaciano.");

        tamMask = 3;
        mascara[9];
        ganho = 1;
        mascara[0] = 0;
        mascara[1] = -1;
        mascara[2] = 0;
        mascara[3] = -1;
        mascara[4] = 4;
        mascara[5] = -1;
        mascara[6] = 0;
        mascara[7] = -1;
        mascara[8] = 0;
        float mascara1[9] = {0, -1, 0 ,-1, 4, -1, 0, -1, 0};

        int indiceMask = 0;
        coeficiente = 0;

        for(int x=0;x<M;x++){
            for(int y=0;y<N;y++){


                for(int q=(-(tamMask-1)/2);q<=((tamMask-1)/2);q++){ // X
                    for(int w=(-(tamMask-1)/2);w<=((tamMask-1)/2);w++){ // Y
                        if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                            coeficiente += imagem.pixelIndex(x+q,y+w)*mascara1[indiceMask];
                        }
                        indiceMask++;
                    }
                }

                coeficiente = coeficiente*ganho;
                if((coeficiente<256)&&(coeficiente>=0)){
                    if(coeficiente>200)
                        imagem2.setPixel(x,y,qRgb(200,0,0));
                    else
                        imagem2.setPixel(x,y,coeficiente);
                }
                else if(coeficiente<256)
                    imagem2.setPixel(x,y,0);
                else
                    imagem2.setPixel(x,y,255);

                coeficiente = 0;
                indiceMask = 0;
            }
        }

        /*QString string0;
        for(int x=0;x<9;x++){
            string0.setNum(mascara[x]);
            ui->console->appendPlainText(string0);
        }*/

        hasImage = true;
        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}

// ********************** VISÃO COMPUTACIONAL **********************

// Janela da Média
void PDI::openMediaImgs()
{
    janelaMediaImg = new MediaImg();

    janelaMediaImg->show();

    connect(janelaMediaImg,SIGNAL(terminou()),this,SLOT(mediaImgs()));
}

void PDI::mediaImgs()
{
    janelaMediaImg->close();

    int numImgs = janelaMediaImg->numImgs;
    float variancia = 0; // Variância
    float dPadrao = 0; // Desvio Padrão
    float mediaVariancia = 0;
    float mediaDPadrao = 0;

    if(numImgs>=2){
        QImage imagemMedia[numImgs];
        QString string0;
        float media = 0;
        int cont = 0;

        // Carregando imagens
        for(int n=0;n<numImgs;n++){
            imagemMedia[n].load(janelaMediaImg->fileNames[n]);
            string0.setNum(n+1);
            ui->console->appendPlainText("Carregando imagem " + string0 + " : " + janelaMediaImg->fileNames[n]);
        }
        string0.setNum(janelaMediaImg->M[0]*janelaMediaImg->N[0]);
        ui->console->appendPlainText("Tamanho das imagens: " + string0);

        // Desenhando Média
        QPixmap pixMed(janelaMediaImg->M[0]*janelaMediaImg->N[0],256);
        pixMed.fill(QColor("white"));
        QPainter painter(&pixMed);
        /*QPainter painterVar(&pixMed);
        painterVar.setRenderHint(QPainter::Antialiasing, true);
        painterVar.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::SquareCap));
        painterVar.setBrush(QBrush(Qt::red, Qt::SolidPattern));*/

        QImage var = imagemMedia[0];
        QImage dp = imagemMedia[0];
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::SquareCap));
        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        for(int y=0;y<janelaMediaImg->N[0];y++){ // Calculando a Média
            for(int x=0;x<janelaMediaImg->M[0];x++){

                for(int n=0;n<numImgs;n++){
                    media += imagemMedia[n].pixelIndex(x,y);
                }
                media = media/numImgs;
                //painter.drawPoint(cont,floor(255-media));
                painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::SquareCap));
                painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
                painter.drawLine(cont,255,cont,floor(255-media));

                painter.setPen(QPen(Qt::red, 2, Qt::SolidLine, Qt::SquareCap));
                painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
                painter.drawPoint(cont,floor(255-imagemMedia[0].pixelIndex(x,y)));
                //painterVar.drawPoint(cont,floor(255-imagemMedia[0].pixelIndex(x,y)));
                media = 0;
                cont++;

                for(int i=0;i<numImgs;i++){
                    variancia += pow((imagemMedia[i].pixelIndex(x,y) - media),2);
                }
                variancia = variancia/numImgs;
                dPadrao = sqrt(variancia);
                mediaVariancia += variancia;
                mediaDPadrao += dPadrao;

                variancia = (variancia/2000)*255; // Escala
                if(variancia>=0&&variancia<256)
                    var.setPixel(x,y,floor(variancia));
                else
                    var.setPixel(x,y,255);

                if(dPadrao>=0&&dPadrao<256)
                    dp.setPixel(x,y,floor(dPadrao));
                else
                    dp.setPixel(x,y,0);

                variancia = 0;
                dPadrao = 0;
            }
        }

        if(!var.save("variancia.jpg"))
            ui->console->appendPlainText("Erro ao salvar variancia.jpg.");
        if(!dp.save("desvio_padrao.jpg"))
            ui->console->appendPlainText("Erro ao salvar desvio_padrao.jpg.");

        mediaVariancia = mediaVariancia/(janelaMediaImg->M[0]*janelaMediaImg->N[0]);
        mediaDPadrao = mediaDPadrao/(janelaMediaImg->M[0]*janelaMediaImg->N[0]);
        string0.setNum(mediaVariancia);
        ui->console->appendPlainText("Média da Variância: " + string0);
        string0.setNum(mediaDPadrao);
        ui->console->appendPlainText("Média do Desvio Padrão: " + string0);

        // Mostrando Média
        janelaImgMedia = new QDialog(this);
        janelaImgMedia->setWindowTitle("Média das imagens");
        janelaImgMedia->setMinimumSize(512,256);
        janelaImgMedia->setMaximumSize(512,256);

        QLabel *imagemM = new QLabel(janelaImgMedia);
        imagemM->resize(janelaMediaImg->M[0]*janelaMediaImg->N[0],256);
        imagemM->setPixmap(pixMed);

        QScrollArea *area = new QScrollArea(janelaImgMedia);
        area->setBackgroundRole(QPalette::Dark);
        area->setWidget(imagemM);


        janelaImgMedia->show();
        area->setMinimumSize(janelaImgMedia->size());

    }
    else{
        QMessageBox::critical(this,"Erro","Existem menos que 2 imagens carregadas.",QMessageBox::Ok);
    }

}

// Camera
void PDI::cam()
{
    hasImage = true;
    isCam = true;
    ui->slider_t1->setEnabled(true);
    ui->slider_t2->setEnabled(true);

    threadCam = new execThread;

    connect(threadCam,SIGNAL(terminouCam()),this,SLOT(mostrarCam()));

    threadCam->t1 = ui->slider_t1->value();
    threadCam->t2 = ui->slider_t2->value();

    threadCam->start();

    if(threadCam->isRunning())
        ui->console->appendPlainText("Aplicando Algoritmo de Canny.");
}

void PDI::mostrarCam()
{
    imagem = threadCam->imagemSaida1;
    imagem2 = threadCam->imagemSaida2;

    //laplaciano();

    ui->imagem->setPixmap(QPixmap::fromImage(imagem));
    ui->imagem2->setPixmap(QPixmap::fromImage(imagem2));
    QString texto;
    texto.setNum(threadCam->tempo);
    //ui->console->appendPlainText(texto);
    ui->statusBar->showMessage(texto + "ms");
}

void execThread::run()
{
    // Variáveis
    QTime t;
    t.start();
    tamMask = 3;
    ganho = 1;
//    float mascara1[9] = {0, -1, 0 ,-1, 4, -1, 0, -1, 0};
//    float mascara2[25] = {0, 0, 1, 0, 0,
//                          0, 1, 2, 1, 0,
//                          1, 2, -16, 2, 1,
//                          0, 1, 2, 1, 0,
//                          0, 0, 1, 0, 0};
//    float mascara3[25] = {2, 4, 5, 4, 2,
//                          4, 9, 12, 9, 4,
//                          5, 12, 15, 12, 5,
//                          4, 9, 12, 9, 4,
//                          2, 4, 5, 4, 2};
    float mascara3[9] = {1, 2, 1,
                         2, 4, 2,
                         1, 2, 1};
    int indiceMask = 0;
    float maxValor = 0;
    float minValor = 0;
    float valorTmp = 0;
    coeficiente = 0;
    QImage imagemTmp;
    float teta;

    // Loop
    while(1){
    CvCapture *capture = cvCaptureFromCAM(CV_CAP_ANY);

    IplImage *frame = cvQueryFrame(capture);

    int h = frame->height;
    int w = frame->width;
    int channels = frame->nChannels;
    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = frame->imageData;

    for (int y = 0; y < h; y++, data += frame->widthStep)
    {
        for (int x = 0; x < w; x++)
        {
            char r, g, b, a = 0;
            if (channels == 1){
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            }
            else if (channels == 3 || channels == 4){
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4){
                a = data[x * channels + 3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            }
            else{
                qimg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }

    imagemSaida1 = *qimg;

    imagemSaida2 = imagemSaida1;
    imagemTmp = imagemSaida1;

    M = imagemSaida1.width(); // Largura da imagem
    N = imagemSaida1.height(); // Altura da imagem

    for(int y=0;y<N;y++){
        for(int x=0;x<M;x++){
            //valorPixel = (imagem.pixelIndex(x,y)); // Pega o nível de cinza do pixel
            valorTmp = qGray(imagemSaida1.pixel(x,y)); // Pega o nível de cinza do pixel
            imagemTmp.setPixel(x,y,qRgb(valorTmp,valorTmp,valorTmp));
        }
    }


//    // Equalizando histograma
//    float hist[256];
//    float histEql[256];
//    float pr;
//    int valorPixel;
//    int contador;
//    int tam = M*N;
//    for(int n=0;n<256;n++){
//        hist[n] = 0;
//    }
//    for(int y=0;y<N;y++){
//        for(int x=0;x<M;x++){
//            valorPixel = floor(qGray(imagemTmp.pixel(x,y))); // Pega o nível de cinza do pixel
//            contador = hist[valorPixel] + 1; // Conta a quantidade que ocorre
//            hist[valorPixel] = contador; // Carrega no vetor
//        }
//    }
//    for(int i=0;i<256;i++){
//        for(int x=0;x<=i;x++){
//            pr += (hist[x])/(tam);
//        }
//        histEql[i] = pr*255;
//        pr = 0;
//    }
//    for(int y=0;y<N;y++){
//        for(int x=0;x<M;x++){
//            valorPixel = floor(qGray(imagemTmp.pixel(x,y)));
//            imagemSaida2.setPixel(x,y,qRgb(floor(histEql[valorPixel]),floor(histEql[valorPixel]),floor(histEql[valorPixel])));
//        }
//    }


    // Aplicando o filtro Gaussiano
    //ganho = 0.0063;
    ganho = 0.0625;

    imagemTmp = imagemSaida2;

    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){

            for(int q=(-(tamMask-1)/2);q<=((tamMask-1)/2);q++){ // X
                for(int w=(-(tamMask-1)/2);w<=((tamMask-1)/2);w++){ // Y
                    if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                        coeficiente += (qGray(imagemTmp.pixel(x+q,y+w)))*mascara3[indiceMask];
                    }
                    indiceMask++;
                }
            }

            coeficiente = floor(coeficiente*ganho);
            if((coeficiente<256)&&(coeficiente>=0))
                imagemSaida2.setPixel(x,y,qRgb(coeficiente,coeficiente,coeficiente));
            else if(coeficiente<256)
                imagemSaida2.setPixel(x,y,qRgb(0,0,0));
            else
                imagemSaida2.setPixel(x,y,qRgb(255,255,255));

            coeficiente = 0;
            indiceMask = 0;
        }
    }
    imagemTmp = imagemSaida2;

    // Aplicando Sobel
    float imagemX[M][N];
    float imagemY[M][N];
    tamMask = 3;
    float coef1, coef2 = 0; // Coeficientes
    int indiceMask = 0;
    float mascara1[9] = {-1, 0, 1 , -2, 0, 2, -1, 0, 1};
    float mascara2[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){


            for(int q=(-(tamMask-1)/2);q<=((tamMask-1)/2);q++){ // X
                for(int w=(-(tamMask-1)/2);w<=((tamMask-1)/2);w++){ // Y
                    if((x+q>=0)&&(x+q<M)&&(y+w>=0)&&(y+w<N)){
                        coef1 += (qGray(imagemTmp.pixel(x+q,y+w)))*mascara1[indiceMask];
                        coef2 += (qGray(imagemTmp.pixel(x+q,y+w)))*mascara2[indiceMask];
                    }
                    indiceMask++;
                }
            }

            imagemX[x][y] = coef1;
            imagemY[x][y] = coef2;

            //coeficiente = floor(0.9*(fabs(coef1)+fabs(coef2)));
            coeficiente = floor(sqrt(pow(coef1,2)+pow(coef2,2)));

            if((coeficiente<256)&&(coeficiente>=0))
                imagemSaida2.setPixel(x,y,qRgb(coeficiente,coeficiente,coeficiente));
            else if(coeficiente<256)
                imagemSaida2.setPixel(x,y,qRgb(0,0,0));
            else
                imagemSaida2.setPixel(x,y,qRgb(255,255,255));

            indiceMask = 0;
            coef1 = 0;
            coef2 = 0;
        }
    }
    imagemTmp = imagemSaida2;
    M = imagemTmp.width();
    N = imagemTmp.height();

    // Non-Maximum Suppression
    float imagemTeta[M][N];
    for(int x=0;x<M;x++){ // x=1 a M-1
        for(int y=0;y<N;y++){ // y=1 a N-1
            if((x==0)||(y==0)||(x==(M-1))||(y==(N-1))){
                imagemTeta[x][y] = 0;
                imagemSaida2.setPixel(x,y,qRgb(0,0,0));
            }
            else{
                if ((imagemX[x][y]) == 0)
                    imagemX[x][y] = 1;

                teta = floor(((atan2((imagemY[x][y]),(imagemX[x][y])))*180)/PI);
                valorTmp = (qGray(imagemTmp.pixel(x,y))); // Pixel
                imagemTeta[x][y] = teta;

                if(((teta>(-22))&&(teta<22))||((teta>157)||(teta<(-157)))){ // 0º
                    if((valorTmp<(qGray(imagemTmp.pixel(x,y-1))))||(valorTmp<(qGray(imagemTmp.pixel(x,y+1)))))
                        imagemSaida2.setPixel(x,y,qRgb(0,0,0));
                    else
                        imagemSaida2.setPixel(x,y,qRgb(valorTmp,valorTmp,valorTmp));
                }
                else if(((teta>=22)&&(teta<67))||((teta<(-112))&&(teta>=(-157)))){ // 45º
                    if((valorTmp<(qGray(imagemTmp.pixel(x+1,y-1))))||(valorTmp<(qGray(imagemTmp.pixel(x-1,y+1)))))
                        imagemSaida2.setPixel(x,y,qRgb(0,0,0));
                    else
                        imagemSaida2.setPixel(x,y,qRgb(valorTmp,valorTmp,valorTmp));
                }
                else if(((teta>=67)&&(teta<112))||((teta<(-67))&&(teta>=(-112)))){ // 90º
                    if((valorTmp<(qGray(imagemTmp.pixel(x-1,y))))||(valorTmp<(qGray(imagemTmp.pixel(x+1,y)))))
                        imagemSaida2.setPixel(x,y,qRgb(0,0,0));
                    else
                        imagemSaida2.setPixel(x,y,qRgb(valorTmp,valorTmp,valorTmp));
                }
                else{ // 135 º
                    if((valorTmp<(qGray(imagemTmp.pixel(x+1,y+1))))||(valorTmp<(qGray(imagemTmp.pixel(x-1,y-1)))))
                        imagemSaida2.setPixel(x,y,qRgb(0,0,0));
                    else
                        imagemSaida2.setPixel(x,y,qRgb(valorTmp,valorTmp,valorTmp));
                }

            }
        }
    }
    imagemTmp = imagemSaida2;
    M = imagemTmp.width();
    N = imagemTmp.height();

    // Threshoulding
    int xTmp, yTmp;
    int n = 0;
    float valorTmp2;
    for(int x=0;x<M;x++){
        for(int y=0;y<N;y++){
            valorTmp = (qGray(imagemTmp.pixel(x,y)));
            xTmp = x;
            yTmp = y;

            if(valorTmp>t1){

//                while(n<8){
//                    if(((imagemTeta[x][y]>(-22))&&(imagemTeta[x][y]<22))||((imagemTeta[x][y]>157)||(imagemTeta[x][y]<(-157)))){ // 0º
//                        if((x+1<M)&&((qGray(imagemTmp.pixel(x+1,y)))>t2))
//                            x++;
//                        else
//                            n=10;
//                    }
//                    else if(((imagemTeta[x][y]>=22)&&(imagemTeta[x][y]<67))||((imagemTeta[x][y]<(-112))&&(imagemTeta[x][y]>=(-157)))){ // 45º
//                        if(((x+1<M)&&(y+1<N))&&((qGray(imagemTmp.pixel(x+1,y+1)))>t2)){
//                            x++;
//                            y++;
//                        }
//                        else{
//                            n=10;
//                        }
//                    }
//                    else if(((imagemTeta[x][y]>=67)&&(imagemTeta[x][y]<112))||((imagemTeta[x][y]<(-67))&&(imagemTeta[x][y]>=(-112)))){ // 90º
//                        if((y+1<N)&&((qGray(imagemTmp.pixel(x,y+1)))>t2))
//                            y++;
//                        else
//                            n=10;
//                    }
//                    else{ // 135º
//                        if(((x-1>=0)&&(y+1<N))&&((qGray(imagemTmp.pixel(x-1,y+1)))>t2)){
//                            x--;
//                            y++;
//                        }
//                        else{
//                            n=10;
//                        }
//                    }

//                    n++;
//                }

//                x = xTmp;
//                y = yTmp;
//                if(n>9)
//                    imagemSaida2.setPixel(x,y,qRgb(255,0,0));
//                else
//                    imagemSaida2.setPixel(x,y,qRgb(255,255,255));

                if(((qGray(imagemTmp.pixel(x+1,y-1)))>t2)||((qGray(imagemTmp.pixel(x+1,y)))>t2)||((qGray(imagemTmp.pixel(x+1,y+1)))>t2)||((qGray(imagemTmp.pixel(x,y+1)))>t2))
                    imagemSaida2.setPixel(x,y,qRgb(255,255,255));
                else
                    imagemSaida2.setPixel(x,y,qRgb(255,0,0));
            }
            else{
                imagemSaida2.setPixel(x,y,qRgb(0,0,0));
            }
        }
    }

    tempo = t.elapsed();
    t.restart();

    emit terminouCam();
    }
    //exec();
}

void PDI::on_slider_t1_valueChanged(int value)
{
    threadCam->t1 = value;
}

void PDI::on_slider_t2_valueChanged(int value)
{
    threadCam->t2 = value;
}

// ********************** FILTROS FREQUÊNCIA **********************
void PDI::butterworth()
{
    if(hasImage){
        IplImage *imagemMat = cvLoadImage(fn.toAscii().constData()); //imread(fn.toAscii().constData());
        Mat matriz = imagemMat;
        //matriz cvCreateMat(imagemMat->height - 1, imagemMat->width - 1, CV_64FC2);
        //matriz = imagemMat;
        dft(matriz,matriz,DFT_REAL_OUTPUT,0);
        IplImage imagemMat2 = matriz;
        *imagemMat = imagemMat2;

        int h = imagemMat->height;
        int w = imagemMat->width;
        int channels = imagemMat->nChannels;
        QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
        char *data = imagemMat->imageData;

        for (int y = 0; y < h; y++, data += imagemMat->widthStep)
        {
            for (int x = 0; x < w; x++)
            {
                char r, g, b, a = 0;
                if (channels == 1){
                    r = data[x * channels];
                    g = data[x * channels];
                    b = data[x * channels];
                }
                else if (channels == 3 || channels == 4){
                    r = data[x * channels + 2];
                    g = data[x * channels + 1];
                    b = data[x * channels];
                }

                if (channels == 4){
                    a = data[x * channels + 3];
                    qimg->setPixel(x, y, qRgba(r, g, b, a));
                }
                else{
                    qimg->setPixel(x, y, qRgb(r, g, b));
                }
            }
        }

        imagem2 = *qimg;

        mostrarImg2();
    }
    else{
        QMessageBox::critical(this,"Erro","Necessario abrir uma imagem antes.",QMessageBox::Ok);
    }
}
