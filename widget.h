#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>
#include "ui_widget.h"


class Widget : public QWidget, private Ui::Widget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void DimensionarArray(int mascara[50]);
    void GenerarRegistro(int mascara[50], QString leyenda[38],char tipo[2]);

private slots:
    void AbrirOrigen();
    void AbrirDestino();
    void Generar();


private:

    QString ficheroOrigen;
    QString ficheroDestino;
    int tam[2];
    char tipo[6][3]={"11","13","14","15","16","17"};
    QString leyendas[6][38]=
        {
            {
                "TIPO REGISTRO","COD.DELEGACION MEH","COD. MUNICIPIO","PARC. CATASTRAL","COD. PROVINCIA","NOMBRE PROVINCIA","COD. MUNICIPIO DGC",
                "COD. MUNICIPIO INE","NOMBRE MUNICIPIO","NOMBRE ENTID. MENOR","COD. VIA PUBLICA","TIPO VIA","NOMBRE VIA","PRIMER Nº POL","PRIMERA LETRA",
                "SEGUNDO Nº POL","SEGUNDA LETRA","KILOMETRO","BLOQUE","TEXTO DIRECC. NO ESTRUCT","CODIGO POSTAL","DIST. MUNICIP","COD. MUNICPIO ORIGEN C/AGREGACION",
                "CODIGO ZONA CONCENTRACION","CODIGO POLIGONO","CODIGO PARCELA","CODIGO PARAJE","NOMBRE PARAJE","SUPERFICIE PARCELA","SUP. CONSTRUIDA TOTAL",
                "SUP. S/RASANTE","SUP. BAJO RASANTE","SUP. CUBIERTA","COORD. X","COORD. Y","REF. CATASTRAL BICE","DENOM. BICE","HUSO GEOGRAFICO"
            },
            {        },
            {"TIPO DE REGISTRO","COD.DELEGACION MEH","COD. MUNICIPIO","PARC.CATASTRAL","NUM.ORDEN.ELEMENTO CONSTR.","NUM.ORDEN BIEN INM.FISCAL","COD.UD.CONSTRUC.","BLOQUE","ESC","PLANTA","PUERTA","COD. DEST. DGC","TIPO REF.","ANNO REF.","ANNO ANTIGUEDAD","LOCAL INTERIOR","SUP.TOTAL","SUP.TERRAZAS","SUP.OTRAS PLANTAS","TIPOLOGIA CONSTRUCT.","COD.MOD.REPARTO"},
            {        },
            {        },
            {
                "Tipo de Registro","Codigo Delegacion MEH","Codigo Municipio","Naturaleza Suelo","Parcela Catastral","Codigo SubParcela","N Orden Bien Inmueble Fiscal",
                "Tipo Subparcela","Sup Subparcela","Calificacion Catastral","Denomimacion Clase Cultivo","Intensidad Productiva","Modalidad Reparto"
            }
        };

        int mascara[6][50]=
        {
            {2,-21,2,3,-2,14,-6,2,25,3,3,40,30,5,5,25,4,1,4,1,5,4,-8,25,5,2,3,2,3,5,5,30,10,7,7,7,7,9,10,-229,20,65,10,0},
            {2,-21,2,3,2,14,4,-2,2,25,3,3,40,30,5,5,25,4,1,4,1,5,-12,25,-55,4,1,7,5,-97,4,0},
            {2,-21,2,3,-2,14,4,-2,4,4,4,2,3,3,3,1,4,4,1,7,7,7,5,-2,3,5,0},
            {2,-21,2,3,2,14,4,1,1,8,15,19,2,25,3,3,40,30,5,5,25,4,1,4,1,5,4,2,3,3,25,5,2,3,2,3,5,5,30,-30,4,4,-52,1,-13,10,10,9,0},
            {2,-21,2,3,2,14,4,2,4,4,6,0},
            {2,-21,2,3,2,14,4,-2,4,1,10,2,40,2,-18,3,0}
        };//tamaño de los campos según formato del Catastro
};

#endif // WIDGET_H
