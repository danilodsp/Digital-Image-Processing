#ifndef PDI_H
#define PDI_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QObject>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QScrollArea>
#include <QVector>
#include <math.h>
#include <sobre.h>
#include <VC/mediaimg.h>
#include <dialogmedia.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <QThread>
#include <QTime>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

#define PI 3.14159265

using namespace cv;

namespace Ui {
    class PDI;
}

class execThread : public QThread
{
    Q_OBJECT

public:
    void run();

signals:
    void terminouCam();

public:
    QImage imagemSaida1;
    QImage imagemSaida2;
    float ganho;
    float coeficiente;
    int tamMask;
    int M, N; // Largura e altura da imagem
    float mascara[256];
    float tempo;
    float t1;
    float t2;
};

class PDI : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDI(QWidget *parent = 0);
    ~PDI();

public:
    QString fn; // Filename da imagem de entrada
    int L; // Números de níveis (ou cores)
    int M, N; // Largura e altura da imagem
    int tam; // Tamanho da imagem MxN
    QImage imagem; // Imagem de entrada
    QImage imagem2; // Imagem de saída
    QPixmap pixHistS; // Imagem do histograma
    QPixmap pixHistEqlS; // Imagem do histograma equalizado
    float hist[256]; // Histograma
    float histEql[256]; // Histograma equalizado
    float divisorHist; // Divisor para histograma
    // Parâmetros de filtro
    float ganho;
    float coeficiente;
    int tamMask;
    float mascara[256];
    // Flags
    bool showHistConsole; // Mostrar no console resultados de pixels
    bool hasImage; // Tem imagem
    bool imagemGrande; // Imagem maior que 256x256
    bool isCam; // Se é imagem da camera
    QTime tempo;

public:
    void init(); // Método para inicializações

public slots:
    void abrir();
    void salvar();
    void clickDireitoImg(QPoint);
    void openSobre(); // Abri o sobre
    void openAjuda(); // Abri ajuda
    void openImgGrd1(); // Abri imagem grande de entrada
    void openImgGrd2(); // Abri imagem grande de saída
    void mostrarImg2(); // Mostrar imagem de Saída
    void eqlHist(); // Método para equalização de histograma
    void negativa(); // Método para a negativa
    void openLog(); // Método para abrir a janela Log
    void openPot(); // Método para abrir a janela Potência
    void logaritmo(); // Método para o log
    void potencia(); // Método para a potencia
    // Aritmética
    void openSub(); // Método para abrir a janela Subtração
    void openFileSub1(); // Método para abrir imagem 1 da subtração
    void openFileSub2(); // Método para abrir imagem 2 da subtração
    void subtracao(); // Operação aritmética de subtração
    // Filtros
    void openMedia(); // Método para abrir a janela Média
    void filtroMedia(); // Filtro da média
    void filtro(); // Método para filtro genérico (sem máscara definido), Parâmetros para filtro(): tamMask, mascara[], ganho
    void openMediana(); // Método para abrir a janela Mediana
    void mediana(); // Método da mediana
    // Filtros Frequência
    void butterworth(); // Método do Butterworth
    // Detecção de bordas
    void roberts();
    void sobel();
    void laplaciano();
    // Visão Computacional
    void openMediaImgs(); // Método para abirr janela da média imagens
    void mediaImgs(); // Média de pixels de imagens
    // Camera
    void cam();
    void mostrarCam();

public:
    QDialog *visHist; // Janela para visualizar histograma
    QDialog *visHistEql; // Janela para visualizar histograma equalizado
    QDialog *imagemMaior1; // Janela para visualizar imagens de entrada acima de 256x256
    QDialog *imagemMaior2; // Janela para visualizar imagens de saída acima de 256x256
    QDialog *dialogLog; // Janela que solicita parâmetros
    QDialog *dialogPot; // Janela que solicita parâmetros
    QDialog *dialogSub; // Janela que solicita parâmetros
    QLineEdit *textoConstLog; // Constante c da funçao log
    QLineEdit *textoConstPot; // Constante c da funçao potencia
    QLineEdit *textoConstPotA; // Constante a da funçao potencia
    QLineEdit *fn1; // File name da imagem 1 da subtração
    QLineEdit *fn2; // File name da imagem 2 da subtração
    QDialog *janelaImgMedia; // Abrir imagem media VC
    MediaImg *janelaMediaImg; // Media VC
    QDialog *dialogMediana; // Janela que solicita parâmetros
    QLineEdit *textoConstMediana; // Tamanho da máscara da mediana
    sobre *janelaSobre; // Janela do Sobre
    dialogMedia *janelaMedia;
    QDialog *CamF; // Janela WebCam
    execThread *threadCam;

public slots:
    void removerImg();

private:
    Ui::PDI *ui;

private slots:
    void on_checkBox_showHistCons_clicked();
    void on_visHist2_clicked();
    void on_visHist1_clicked();
    void on_slider_t1_valueChanged(int value);
    void on_slider_t2_valueChanged(int value);
};

#endif // PDI_H
