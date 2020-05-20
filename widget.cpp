#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    ficheroOrigen="";
    ficheroDestino="";
    botonEscribir->setEnabled(false);
    m_lista_extensiones.insert(tr("All Files (*.*)"),".*");
    m_lista_extensiones.insert(tr("CSV Files (*.csv)"),".csv");
    m_lista_extensiones.insert(tr("Text Files (*.txt)"),".txt");
}

void Widget::AbrirOrigen()
{
    QString selectedFilter;
    ficheroOrigen = QFileDialog::getOpenFileName(this,
                                                 "getOpenFileName",
                                                 "",
                                                 "Cat Files(*.cat);;All Files (*)",
                                                 &selectedFilter
                                                 /*options*/);
    if (!ficheroOrigen.isEmpty())
    {
        LabelFicheroOrigen->setText(ficheroOrigen);
        if (!ficheroDestino.isEmpty())
        {
            botonEscribir->setEnabled(true);
        }
    }
    LabelStatus->setText("");//reseteo el mensaje de abajo
}

void Widget::AbrirDestino()
{
    QString selectedFilter;
    QHashIterator<QString, QString> i(m_lista_extensiones);
    QString extensiones;
    while (i.hasNext())
    {
        i.next();
        extensiones += i.key();
        if (i.hasNext())
            extensiones += ";;";
    }
    QString extension;
    ficheroDestino = QFileDialog::getSaveFileName(this,
                                                  tr("Guardar archivo"),
                                                  "",
                                                  extensiones,
                                                  &extension,
                                                  QFileDialog::DontUseNativeDialog
                                                  );

#if not defined(Q_OS_WIN) || not defined(Q_OS_MAC)
    ficheroDestino += m_lista_extensiones[extension];
#endif

    qDebug()<<"filtro "<<selectedFilter;
    if (!ficheroDestino.isEmpty())
    {
        LabelFicheroDestino->setText(ficheroDestino);
        if (!ficheroOrigen.isEmpty())
        {
            botonEscribir->setEnabled(true);
        }
    }
    LabelStatus->setText("");//reseteo el mensaje de abajo
}

void Widget::Generar()
{
    int opcion=listaOpciones->currentIndex();
    GenerarRegistro(mascara[opcion],leyendas[opcion],tipo[opcion]);
}

void Widget::DimensionarArray(int mascara[50])
{
    int i=0;
    int contador1=0,contador2=0;
    while (mascara[i]!=0)
    {
        contador1++;
        if (mascara[i]>0)
        {
            contador2++;
        }
        i++;
    }
    tam[0]=contador1;
    tam[1]=contador2;
}

void Widget::GenerarRegistro(int mascara[50], QString leyenda[38],char tipo[2])
{
    QFile fEntrada(ficheroOrigen);
    QFile fSalida(ficheroDestino);

    if (fEntrada.open(QIODevice::ReadOnly | QIODevice::Text) && fSalida.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        DimensionarArray(mascara);
        char buffer[1000];

        //qDebug()<<"Generando registro..."<<tipo;

        QTextStream texto(&fSalida);
        texto.setCodec("UTF-8");
        for (int i=0; i<tam[1]; i++)
        {
            //qDebug()<<leyenda[i];
            texto<<leyenda[i];
            if (i<tam[1]-1)
            {
                texto<<"#";
            }
        }
        texto<<"\n";
        while (!fEntrada.atEnd())
        {
            int tamlinea=1000;
            int tamregistro;
            fEntrada.readLine(buffer,tamlinea);
            if (buffer[0]==tipo[0] && buffer[1]==tipo[1])
            {
                QString linea= QString::fromLatin1(buffer);
                QString registro;
                bool grabar=true;
                for (int i=0; i<tam[0]; i++)
                {
                    if (mascara[i]<0)
                    {
                        tamregistro=mascara[i]*-1;//pongo la cantidad en positivo
                        grabar=false;
                    }
                    else
                    {
                        tamregistro=mascara[i];
                        grabar=true;
                    }
                    registro=linea.left(tamregistro);
                    linea=linea.right(tamlinea-tamregistro-1);
                    tamlinea=tamlinea-tamregistro;
                    if (grabar)//solo paso los registros que no son espacios
                    {
                        texto<<registro;
                        texto<<"#";
                    }
                }
                texto<<"\n";
            }
        }
        LabelStatus->setText(tr("¡¡¡Generado archivo!!!"));
    }
    fEntrada.close();
    fSalida.close();
}
