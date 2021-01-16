#include "configuracion.h"
#include "ui_configuracion.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>

Configuracion::Configuracion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Configuracion)
{
    ui->setupUi(this);

    connect(ui->btnGuardar, SIGNAL(sliderPressed()),
            this, SLOT(cambiarCursor()));

    connect(ui->btnGuardar, SIGNAL(sliderReleased()),
            this, SLOT(botonRelajado()));
}

Configuracion::~Configuracion()
{
    delete ui;
}


void Configuracion::on_btnGuardar_clicked()
{
    // Obtener la informacion de la GUI
    QString direccion = ui->inDireccion->text();
    int puerto = ui->inPuerto->value();
    bool caja1 = ui->chkCaja1->isChecked();
    bool caja2 = ui->chkCaja2->isChecked();
    bool caja3 = ui->chkCaja3->isChecked();
    bool caja4 = ui->chkCaja4->isChecked();

    // Verificamos si la informacion recopilada es correcta
    // qDebug() << direccion << puerto << caja1 << caja2 << caja3 << caja4;

    // Establecer un nombre de archibo temporañ e el directorio "HOME" del usuario
    QString temporal = QDir::home().absolutePath() + "/sin_titulo";
    qDebug() << temporal;

    // Abrir cuadro de dialogo para colocar el nombre del archivo
    QString nombreArchivo = QFileDialog::getOpenFileName(this, "Informacion Guardada",
                                                         temporal, "Archivo de configuracion (*.txt)");

    // Crear el objeto QFile
        QFile archivo(nombreArchivo);

        // Verificar si se puede escribir sobre el archivo
        if (archivo.open(QFile::WriteOnly | QFile::Truncate)) {
            // Crear el objeto QTextStream
            QTextStream out(&archivo);
            // Escribiendo datos en el archivo
            out << "Servidor = " << direccion << '\n';
            out << "Puerto = " << puerto << '\n';
            out << "Caja 1 = " << caja1 << '\n';
            out << "Caja 2 = " << caja2 << '\n';
            out << "Caja 3 = " << caja3 << '\n';
            out << "Caja 4 = " << caja4 << '\n';
            // Cerrar archivo
            archivo.close();
        }
}

void Configuracion::cambiarCursor()
{
    ui->btnGuardar->setCursor(Qt::ClosedHandCursor);
}

void Configuracion::botonRelajado()
{
    ui->btnGuardar->setCursor(Qt::OpenHandCursor);
}

