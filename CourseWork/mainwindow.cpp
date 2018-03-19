#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->shuffleBtn->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    mStream.setMatrixSize(arg1);
}


void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    mStream.setMatrix_2Size(arg1);
}

void MainWindow::on_genRandomGraphBtn_clicked()
{
    mStream.setRandomMatrix();
    ui->outputEdit->clear();
    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    ui->matrixEdit->setPlainText(mStream.matrixText);
    ui->matrix_2Edit->setPlainText(mStream.matrixText);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    vector<int> score = morphism.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}



void MainWindow::on_automorphismBtn_clicked()
{
    ui->outputLabel->setText("Автоморфизмы:");
    mStream.setMatrix(ui->matrixEdit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    vector<int> score = morphism.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}


void MainWindow::on_shuffleBtn_clicked()
{
    QString shuffleString;
    shuffleString.clear();
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    Morphism am(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    am.shuffleMatrix(mStream.matrixText);
    ui->matrixEdit->setPlainText(mStream.matrixText);
}



void MainWindow::on_isomorphismBtn_clicked()
{
    ui->outputLabel->setText("Изоморфизмы:");
    mStream.resultText.clear();
    ui->outputEdit->clear();

    //message.Simple(stroka);
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix(ui->matrix_2Edit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    vector<int> score = morphism.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}

void MainWindow::on_gomomorphismBtn_clicked()
{
    ui->outputLabel->setText("Гомоморфизмы:");
    mStream.resultText.clear();
    ui->outputEdit->clear();

    //message.Simple(stroka);
    mStream.setMatrix(ui->matrixEdit->toPlainText());
    mStream.setMatrix(ui->matrix_2Edit->toPlainText());

    Morphism morphism(mStream.matrixSize, mStream.matrixSize, mStream.matrix, mStream.matrix);
    morphism.getAutomorphism(ui->progressBar, mStream.resultText);
    ui->outputEdit->setPlainText(mStream.resultText);

    vector<int> score = morphism.getScore();

    //ui->setupUi(this);

    int N = score.size(); //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N + 1), y(N + 1); //Массивы координат точек

    x[0] = y[0] = 0;
    for (int i=0; i < N; ++i)//Пробегаем по всем точкам
    {
        x[i + 1] = i + 1;
        y[i + 1] = score[i];
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);
    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("N");
    ui->widget->yAxis->setLabel("Size |Mn|");

    //Установим область, которая будет показываться на графике
    if (N >= 50) {
        ui->widget->xAxis->setRange(0, 30);//Для оси Ox
    }
    else {
        ui->widget->xAxis->setRange(0, N);//Для оси Ox
    }

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    int minY = 0, maxY = static_cast<int>((*max_element(score.begin(), score.end())) * 1.2);

    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy

    ui->widget->replot();
}



void MainWindow::on_matrixEdit_textChanged()
{
    ui->matrixEdit->toPlainText().isEmpty() ?
        ui->shuffleBtn->setDisabled(true):
        ui->shuffleBtn->setEnabled(true);
}

void MainWindow::on_matrix_2Edit_textChanged()
{

}
