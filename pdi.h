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
    int L; // N�meros de n�veis (ou cores)
    int M, N; // Largura e altura da imagem
    int tam; // Tamanho da imagem MxN
    QImage imagem; // Imagem de entrada
    QImage imagem2; // Imagem de sa�da
    QPixmap pixHistS; // Imagem do histograma
    QPixmap pixHistEqlS; // Imagem do histograma equalizado
    float hist[256]; // Histograma
    float histEql[256]; // Histograma equalizado
    float divisorHist; // Divisor para histograma
    // Par�metros de filtro
    float ganho;
    float coeficiente;
    int tamMask;
    float mascara[256];
    // Flags
    bool showHistConsole; // Mostrar no console resultados de pixels
    bool hasImage; // Tem imagem
    bool imagemGrande; // Imagem maior que 256x256
    bool isCam; // Se � imagem da camera
    QTime tempo;

public:
    void init(); // M�todo para inicializa��es

public slots:
    void abrir();
    void salvar();
    void clickDireitoImg(QPoint);
    void openSobre(); // Abri o sobre
    void openAjuda(); // Abri ajuda
    void openImgGrd1(); // Abri imagem grande de entrada
    void openImgGrd2(); // Abri imagem grande de sa�da
    void mostrarImg2(); // Mostrar imagem de Sa�da
    void eqlHist(); // M�todo para equaliza��o de histograma
    void negativa(); // M�todo para a negativa
    void openLog(); // M�todo para abrir a janela Log
    void openPot(); // M�todo para abrir a janela Pot�ncia
    void logaritmo(); // M�todo para o log
    void potencia(); // M�todo para a potencia
    // Aritm�tica
    void openSub(); // M�todo para abrir a janela Subtra��o
    void openFileSub1(); // M�todo para abrir imagem 1 da subtra��o
    void openFileSub2(); // M�todo para abrir imagem 2 da subtra��o
    void subtracao(); // Opera��o aritm�tica de subtra��o
    // Filtros
    void openMedia(); // M�todo para abrir a janela M�dia
    void filtroMedia(); // Filtro da m�dia
    void filtro(); // M�todo para filtro gen�rico (sem m�scara definido), Par�metros para filtro(): tamMask, mascara[], ganho
    void openMediana(); // M�todo para abrir a janela Mediana
    void mediana(); // M�todo da mediana
    // Filtros Frequ�ncia
    void butterworth(); // M�todo do Butterworth
    // Detec��o de bordas
    void roberts();
    void sobel();
    void laplaciano();
    // Vis�o Computacional
    void openMediaImgs(); // M�todo para abirr janela da m�dia imagens
    void mediaImgs(); // M�dia de pixels de imagens
    // Camera
    void cam();
    void mostrarCam();

public:
    QDialog *visHist; // Janela para visualizar histograma
    QDialog *visHistEql; // Janela para visualizar histograma equalizado
    QDialog *imagemMaior1; // Janela para visualizar imagens de entrada acima de 256x256
    QDialog *imagemMaior2; // Janela para visualizar imagens de sa�da acima de 256x256
    QDialog *dialogLog; // Janela que solicita par�metros
    QDialog *dialogPot; // Janela que solicita par�metros
    QDialog *dialogSub; // Janela que solicita par�metros
    QLineEdit *textoConstLog; // Constante c da fun�ao log
    QLineEdit *textoConstPot; // Constante c da fun�ao potencia
    QLineEdit *textoConstPotA; // Constante a da fun�ao potencia
    QLineEdit *fn1; // File name da imagem 1 da subtra��o
    QLineEdit *fn2; // File name da imagem 2 da subtra��o
    QDialog *janelaImgMedia; // Abrir imagem media VC
    MediaImg *janelaMediaImg; // Media VC
    QDialog *dialogMediana; // Janela que solicita par�metros
    QLineEdit *textoConstMediana; // Tamanho da m�scara da mediana
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
