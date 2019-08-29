/**
 * @file main.cpp
 * @date Oct 16, 2018
 * @author <b>Ing. Luis Alejandro Reyes Morales.</b>
 *
 * @brief
 *
 * This class implements the Bebe_Data_Class. This a data type that keeps the information of one pacient.
 * The Database keeps the data save with this format
 */
#include "bebe_data_class.h"
#include <QDebug>

//Constructor de la clase recibe el nombre de la madre y el del bebe como parametros-------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
Bebe_Data_Class::Bebe_Data_Class(QString b, QString m){

    posicion_en_archivo =0;
    cantidad_de_pacientes =0;
    numero_de_paciente=0;
    size_of_pacient_data =0;
    size_of_pacient_info =0;
    size_of_pacient_signals =0;

    ID = 12345678910;
    sexo = "unknow";
    cantidad_de_pruebas = 0;
    state = "INICIO";
    birth_date = date.currentDate();

    this->baby_name = b;
    this->mother_name = m;

    time = time.currentTime();
    date = date.currentDate();

    this->SPO2_bebe_value_average_OXY1 = 127;
    this->SPO2_bebe_value_average_OXY2 = 127;
    this->beats_per_minute_value_average_OXY1 = 301;
    this->beats_per_minute_value_average_OXY2 = 301;
    this->PI_value_average_OXY1 = 0;
    this->PI_value_average_OXY2 = 0;
    this->data_function_size = 0;
    this->SPO2_data_function_OXY1_size = 0;
    this->SPO2_data_function_OXY2_size = 0;
    this->BPM_data_function_OXY1_size = 0;
    this->BPM_data_function_OXY2_size = 0;
    this->PI_data_function_OXY1_size = 0;
    this->PI_data_function_OXY2_size = 0;

    for(quint32 i=0; i < DATA_ADC_BUFFER_SIZE; i++){

        this->HR_data_bebe[i]= 0;
        if(i < DATA_FUNCTION_SIZE){
            this->function_0_data_bebe[i]= 0;
            this->function_0_data_bebe[i]= 0;
        }
    }

    for(quint32 i=0; i < SPO2_FUNCTION_BUFFER_SIZE; i++){
        this->SPO2_function_OXY1_data_bebe[i]= 0;
        this->SPO2_function_OXY2_data_bebe[i]= 0;
        this->BPM_function_OXY1_data_bebe[i]= 0;
        this->BPM_function_OXY2_data_bebe[i]= 0;
        this->PI_function_OXY1_data_bebe[i]= 0;
        this->PI_function_OXY2_data_bebe[i]= 0;
    }
}
//-----------------------------------------------------------------------------------------------------------------------




//Esta funcion me escribe en un dataStream los datos de bebe para luego guardarlo en archivos----------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::write_file(QDataStream &out){

    out<<this->ID;
    out<<this->sexo;
    out<<this->cantidad_de_pruebas;
    out<<this->state;
    out<<this->birth_date;
    out<<this->baby_name;
    out<<this->mother_name;
    out<<this->date;
    out<<this->time;
    out<<this->SPO2_bebe_value_average_OXY1;
    out<<this->SPO2_bebe_value_average_OXY2;
    out<<this->beats_per_minute_value_average_OXY1;
    out<<this->beats_per_minute_value_average_OXY2;
    out<<this->PI_value_average_OXY1;
    out<<this->PI_value_average_OXY2;
    out<<this->data_function_size;
    out<<this->data_adc_buffer_size;
    out<<this->SPO2_data_function_OXY1_size;
    out<<this->SPO2_data_function_OXY2_size;
    out<<this->BPM_data_function_OXY1_size;
    out<<this->BPM_data_function_OXY2_size;
    out<<this->PI_data_function_OXY1_size;
    out<<this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        out<<this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        out<<this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        out<<this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        out<<this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        out<<this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        out<<this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        out<<this->PI_function_OXY2_data_bebe[i];
    }

}
//-----------------------------------------------------------------------------------------------------------------------


//Esta funcion me lee desde un dataStream los datos de bebe guardados en un archivo--------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::read_file(QDataStream &in){

    in>>this->ID;
    in>>this->sexo;
    in>>this->cantidad_de_pruebas;
    in>>this->state;
    in>>this->birth_date;
    in>>this->baby_name;
    in>>this->mother_name;
    in>>this->date;
    in>>this->time;
    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

//Esta funcion me escribe en un dataStream los datos de bebe para luego guardarlo en archivos todo en formato QString e Int----------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::write_file_all_String_and_int_format(QDataStream &out)
{
    out<<this->ID;
    out<<this->sexo;
    out<<this->cantidad_de_pruebas;
    out<<this->state;
    out<<(this->birth_date.toString());
    out<<this->baby_name;
    out<<this->mother_name;
    out<<(this->date.toString());
    out<<(this->time.toString());
    out<<this->SPO2_bebe_value_average_OXY1;
    out<<this->SPO2_bebe_value_average_OXY2;
    out<<this->beats_per_minute_value_average_OXY1;
    out<<this->beats_per_minute_value_average_OXY2;
    out<<this->PI_value_average_OXY1;
    out<<this->PI_value_average_OXY2;
    out<<this->data_function_size;
    out<<this->data_adc_buffer_size;
    out<<this->SPO2_data_function_OXY1_size;
    out<<this->SPO2_data_function_OXY2_size;
    out<<this->BPM_data_function_OXY1_size;
    out<<this->BPM_data_function_OXY2_size;
    out<<this->PI_data_function_OXY1_size;
    out<<this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        out<<this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        out<<this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        out<<this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        out<<this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        out<<this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        out<<this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        out<<this->PI_function_OXY2_data_bebe[i];
    }
}

//Esta funcion me lee desde un dataStream los datos de bebe guardados en un archivo todo en formato QString e Int--------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::read_file_all_String_and_int_format(QDataStream &in)
{
    QString temp_string;

    in>>this->ID;
    in>>this->sexo;
    in>>this->cantidad_de_pruebas;
    in>>this->state;

    in>>temp_string;
    birth_date = QDate::fromString(temp_string);

    in>>this->baby_name;
    in>>this->mother_name;

    in>>temp_string;
    date = QDate::fromString(temp_string);

    in>>temp_string;
    time = QTime::fromString(temp_string);

    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}
//-----------------------------------------------------------------------------------------------------------------------

//Esta funcion me escribe en un dataStream los datos de bebe para luego guardarlo en archivos con tamaños de archivo----------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::write_file_with_size_data(QDataStream &out)
{
    out<<this->posicion_en_archivo;    ///8
    out<<this->cantidad_de_pacientes;  ///4
    out<<this->numero_de_paciente;     ///4
    out<<this->size_of_pacient_data;   ///4
    out<<this->size_of_pacient_info;   ///4
    out<<this->size_of_pacient_signals;///4

    out<<this->ID;                     ///8
    out<<this->sexo;                   ///4+lentgh*2 total -> 24 de max
    out<<this->cantidad_de_pruebas;    ///4
    out<<this->state;                  ///30
    out<<(this->birth_date.toString());
    out<<this->baby_name;
    out<<this->mother_name;
    out<<(this->date.toString());
    out<<(this->time.toString());
    out<<this->SPO2_bebe_value_average_OXY1;
    out<<this->SPO2_bebe_value_average_OXY2;
    out<<this->beats_per_minute_value_average_OXY1;
    out<<this->beats_per_minute_value_average_OXY2;
    out<<this->PI_value_average_OXY1;
    out<<this->PI_value_average_OXY2;
    out<<this->data_function_size;
    out<<this->data_adc_buffer_size;
    out<<this->SPO2_data_function_OXY1_size;
    out<<this->SPO2_data_function_OXY2_size;
    out<<this->BPM_data_function_OXY1_size;
    out<<this->BPM_data_function_OXY2_size;
    out<<this->PI_data_function_OXY1_size;
    out<<this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        out<<this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        out<<this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        out<<this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        out<<this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        out<<this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        out<<this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        out<<this->PI_function_OXY2_data_bebe[i];
    }
}

void Bebe_Data_Class::write_file_with_size_data_fix_strings(QDataStream &out)
{
    out<<this->posicion_en_archivo;    ///8
    out<<this->cantidad_de_pacientes;  ///4
    out<<this->numero_de_paciente;     ///4
    out<<this->size_of_pacient_data;   ///4
    out<<this->size_of_pacient_info;   ///4
    out<<this->size_of_pacient_signals;///4

    out<<this->ID;                     ///8
    for(quint16 i=0; sexo.length() < SEX_STRING_LENGTH; i++){
        sexo.append('&');
    }
    out<<this->sexo;                   ///4+lentgh*2 total -> 24 de max
    out<<this->cantidad_de_pruebas;    ///4
    for(quint16 i=0; state.length() < STATE_STRING_LENGTH; i++){
        state.append('&');
    }
    out<<this->state;                  ///30

    QString temp_string = this->birth_date.toString();
    for(quint16 i=0; temp_string.length() < DATE_STRING_LENGTH; i++){
        temp_string.append('&');
    }
    out<<(temp_string);

    for(quint16 i=0; baby_name.length() < NAMES_STRING_LENGTH; i++){
        baby_name.append('&');
    }
    out<<this->baby_name;
    for(quint16 i=0; mother_name.length() < NAMES_STRING_LENGTH; i++){
        mother_name.append('&');
    }
    out<<this->mother_name;

    temp_string = this->date.toString();
    for(quint16 i=0; temp_string.length() < DATE_STRING_LENGTH; i++){
        temp_string.append('&');
    }
    out<<(temp_string);

    temp_string = this->time.toString();
    for(quint16 i=0; temp_string.length() < TIME_STRING_LENGTH; i++){
        temp_string.append('&');
    }
    out<<(temp_string);


    out<<this->SPO2_bebe_value_average_OXY1;
    out<<this->SPO2_bebe_value_average_OXY2;
    out<<this->beats_per_minute_value_average_OXY1;
    out<<this->beats_per_minute_value_average_OXY2;
    out<<this->PI_value_average_OXY1;
    out<<this->PI_value_average_OXY2;
    out<<this->data_function_size;
    out<<this->data_adc_buffer_size;
    out<<this->SPO2_data_function_OXY1_size;
    out<<this->SPO2_data_function_OXY2_size;
    out<<this->BPM_data_function_OXY1_size;
    out<<this->BPM_data_function_OXY2_size;
    out<<this->PI_data_function_OXY1_size;
    out<<this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        out<<this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        out<<this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        out<<this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        out<<this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        out<<this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        out<<this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        out<<this->PI_function_OXY2_data_bebe[i];
    }
}


void Bebe_Data_Class::write_file_with_fix_size(QDataStream &out)
{
    quint8 uchar_empty =0;

    quint32 temp_size_of_pacient_data = size_of_pacient_data;
    size_of_pacient_data = SIZEOF_PACIENT_DATA;

    out<<this->posicion_en_archivo;    ///8
    out<<this->cantidad_de_pacientes;  ///4
    out<<this->numero_de_paciente;     ///4
    out<<this->size_of_pacient_data;   ///4
    out<<this->size_of_pacient_info;   ///4
    out<<this->size_of_pacient_signals;///4

    out<<this->ID;                     ///8
    out<<this->sexo;                   ///4+lentgh*2 total -> 24 de max
    for (quint16  i=0;i < SIZEOF_SEX_STRING - ((sexo.length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<this->cantidad_de_pruebas;    ///4
    out<<this->state;                  ///30
    for (quint16  i=0;i < SIZEOF_STATE_STRING - ((state.length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<(this->birth_date.toString());///40
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((birth_date.toString().length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<this->baby_name;              ///80
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((baby_name.length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<this->mother_name;            ///80
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((mother_name.length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<(this->date.toString());      ///40
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((date.toString().length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<(this->time.toString());      ///24
    for (quint16  i=0;i < SIZEOF_TIME_STRING - ((time.toString().length()*2)+4); i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
    out<<this->SPO2_bebe_value_average_OXY1; ///1
    out<<this->SPO2_bebe_value_average_OXY2; ///1
    out<<this->beats_per_minute_value_average_OXY1; ///2
    out<<this->beats_per_minute_value_average_OXY2; ///2
    out<<this->PI_value_average_OXY1;  ///2
    out<<this->PI_value_average_OXY2;  ///2
    out<<this->data_function_size;     ///4
    out<<this->data_adc_buffer_size;   ///4
    out<<this->SPO2_data_function_OXY1_size; ///4
    out<<this->SPO2_data_function_OXY2_size; ///4
    out<<this->BPM_data_function_OXY1_size;  ///4
    out<<this->BPM_data_function_OXY2_size;  ///4
    out<<this->PI_data_function_OXY1_size;   ///4
    out<<this->PI_data_function_OXY2_size;   ///4

    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        out<<this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        out<<this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        out<<this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        out<<this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        out<<this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        out<<this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        out<<this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        out<<this->PI_function_OXY2_data_bebe[i];
    }

    for (quint16  i=0;i < SIZEOF_PACIENT_DATA - temp_size_of_pacient_data; i++) {
        out<<uchar_empty;///rellenando con caracter vacio
    }
}
//Esta funcion me lee en un dataStream los datos de bebe para luego guardarlo en archivos con tamaños de archivo----------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::read_file_with_size_data(QDataStream &in)
{
    QString temp_string;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    in>>this->cantidad_de_pruebas;
    in>>this->state;

    in>>temp_string;
    birth_date = QDate::fromString(temp_string);

    in>>this->baby_name;
    in>>this->mother_name;

    in>>temp_string;
    date = QDate::fromString(temp_string);

    in>>temp_string;
    time = QTime::fromString(temp_string);

    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

void Bebe_Data_Class::read_file_with_size_data_fix_strings(QDataStream &in){
    QString temp_string;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    sexo.remove(QChar('&'));

    in>>this->cantidad_de_pruebas;

    in>>this->state;
    state.remove(QChar('&'));

    in>>temp_string;
    temp_string.remove(QChar('&'));
    birth_date = QDate::fromString(temp_string);

    in>>this->baby_name;
    baby_name.remove(QChar('&'));
    in>>this->mother_name;
    mother_name.remove(QChar('&'));

    in>>temp_string;
    temp_string.remove(QChar('&'));
    date = QDate::fromString(temp_string);

    in>>temp_string;
    temp_string.remove(QChar('&'));
    time = QTime::fromString(temp_string);

    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

void Bebe_Data_Class::read_file_with_fix_size(QDataStream &in)
{
    QString temp_string;
    quint8 uchar_empty =0;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    for (quint16  i=0;i < SIZEOF_SEX_STRING - ((sexo.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->cantidad_de_pruebas;
    in>>this->state;
    for (quint16  i=0;i < SIZEOF_STATE_STRING - ((state.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    birth_date = QDate::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((birth_date.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->baby_name;
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((baby_name.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->mother_name;
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((mother_name.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    date = QDate::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((date.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    time = QTime::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_TIME_STRING - ((time.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

void Bebe_Data_Class::read_file_with_fix_size_pacient_info(QDataStream &in)
{
    QString temp_string;
    quint8 uchar_empty =0;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    for (quint16  i=0;i < SIZEOF_SEX_STRING - ((sexo.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->cantidad_de_pruebas;
    in>>this->state;
    for (quint16  i=0;i < SIZEOF_STATE_STRING - ((state.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    birth_date = QDate::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((birth_date.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->baby_name;
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((baby_name.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->mother_name;
    for (quint16  i=0;i < SIZEOF_NAMES_STRING - ((mother_name.length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    date = QDate::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_DATE_STRING - ((date.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>temp_string;
    time = QTime::fromString(temp_string);
    for (quint16  i=0;i < SIZEOF_TIME_STRING - ((time.toString().length()*2)+4); i++) {
        in>>uchar_empty;///rellenando con caracter vacio
    }
    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
}

void Bebe_Data_Class::read_file_with_fix_size_pacient_signals(QDataStream &in)
{
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

//Esta funcion me lee en un dataStream los datos de bebe para luego guardarlo en archivos con tamaños de archivo----------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::read_file_with_size_data_only_pacient_info(QDataStream &in)
{
    QString temp_string;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    in>>this->cantidad_de_pruebas;
    in>>this->state;

    in>>temp_string;
    birth_date = QDate::fromString(temp_string);

    in>>this->baby_name;
    in>>this->mother_name;

    in>>temp_string;
    date = QDate::fromString(temp_string);

    in>>temp_string;
    time = QTime::fromString(temp_string);

    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;
}

void Bebe_Data_Class::read_file_with_size_data_only_pacient_info_fix_strings(QDataStream &in)
{
    QString temp_string;

    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;

    in>>this->ID;
    in>>this->sexo;
    sexo.remove(QChar('&'));

    in>>this->cantidad_de_pruebas;

    in>>this->state;
    state.remove(QChar('&'));

    in>>temp_string;
    temp_string.remove(QChar('&'));
    birth_date = QDate::fromString(temp_string);

    in>>this->baby_name;
    baby_name.remove(QChar('&'));
    in>>this->mother_name;
    mother_name.remove(QChar('&'));

    in>>temp_string;
    temp_string.remove(QChar('&'));
    date = QDate::fromString(temp_string);

    in>>temp_string;
    temp_string.remove(QChar('&'));
    time = QTime::fromString(temp_string);

    in>>this->SPO2_bebe_value_average_OXY1;
    in>>this->SPO2_bebe_value_average_OXY2;
    in>>this->beats_per_minute_value_average_OXY1;
    in>>this->beats_per_minute_value_average_OXY2;
    in>>this->PI_value_average_OXY1;
    in>>this->PI_value_average_OXY2;
}

void Bebe_Data_Class::read_file_with_size_data_only_pacient_signals_fix_strings(QDataStream &in){

    in>>this->data_function_size;
    in>>this->data_adc_buffer_size;
    in>>this->SPO2_data_function_OXY1_size;
    in>>this->SPO2_data_function_OXY2_size;
    in>>this->BPM_data_function_OXY1_size;
    in>>this->BPM_data_function_OXY2_size;
    in>>this->PI_data_function_OXY1_size;
    in>>this->PI_data_function_OXY2_size;

    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_0_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_function_size; i++){

        in>>this->function_1_data_bebe[i];
    }
    for(quint32 i=0; i < this->data_adc_buffer_size; i++){

        in>>this->HR_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY1_size; i++){

        in>>this->SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->SPO2_data_function_OXY2_size; i++){

        in>>this->SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY1_size; i++){

        in>>this->BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->BPM_data_function_OXY2_size; i++){

        in>>this->BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY1_size; i++){

        in>>this->PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < this->PI_data_function_OXY2_size; i++){

        in>>this->PI_function_OXY2_data_bebe[i];
    }
}

void Bebe_Data_Class::read_file_with_size_data_only_pacient_size(QDataStream &in)
{
    in>>this->posicion_en_archivo;
    in>>this->cantidad_de_pacientes;
    in>>this->numero_de_paciente;
    in>>this->size_of_pacient_data;
    in>>this->size_of_pacient_info;
    in>>this->size_of_pacient_signals;
}



//Esta funcion imprime en consola datos de bebe-------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::print_bebe_data(){

    qDebug()<<"nombre bebe :  "+this->baby_name;
    qDebug()<<"nombre mama :  "+this->mother_name;
    qDebug()<<"fecha  test :  "+this->date.toString();
    qDebug()<<"hora   test :  "+this->time.toString();
    qDebug()<<"SPO2 Oxy1  value :  "+QString::number(this->SPO2_bebe_value_average_OXY1);
    qDebug()<<"SPO2 Oxy2  value :  "+QString::number(this->SPO2_bebe_value_average_OXY2);
    qDebug()<<"BPM Oxy1   value :  "+QString::number(this->beats_per_minute_value_average_OXY1);
    qDebug()<<"BPM Oxy2   value :  "+QString::number(this->beats_per_minute_value_average_OXY2);
    qDebug()<<"cant de dat :  "+QString::number(this->data_function_size);

    for(quint32 i=0; i < data_function_size; i++){

        qDebug()<<"i :"+QString::number(i)+" dato func 1: "+QString::number(this->function_0_data_bebe[i]);
    }
    for(quint32 i=0; i < data_function_size; i++){

        qDebug()<<"i :"+QString::number(i)+" dato func 2: "+QString::number(this->function_1_data_bebe[i]);
    }
    for(quint32 i=0; i < data_adc_buffer_size; i++){

        qDebug()<<"i :"+QString::number(i)+" dato ADC funct: "+QString::number(this->function_0_data_bebe[i]);
    }
    for(quint32 i=0; i < SPO2_data_function_OXY1_size; i++){

        qDebug()<<"i :"+QString::number(i)+" dato OXY 1: "+QString::number(this->SPO2_function_OXY1_data_bebe[i]);
    }
    for(quint32 i=0; i < SPO2_data_function_OXY2_size; i++){

        qDebug()<<"i :"+QString::number(i)+" dato OXY 2: "+QString::number(this->SPO2_function_OXY2_data_bebe[i]);
    }
}
//-----------------------------------------------------------------------------------------------------------------------


//Esta funcion iguala dos objetos bebe-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
void Bebe_Data_Class::operator_equal(Bebe_Data_Class bebe){

    this->cantidad_de_pacientes = bebe.cantidad_de_pacientes;
    this->numero_de_paciente = bebe.numero_de_paciente;
    this->size_of_pacient_data = bebe.size_of_pacient_data;
    this->size_of_pacient_info = bebe.size_of_pacient_info;
    this->size_of_pacient_signals = bebe.size_of_pacient_signals;

    this->ID = bebe.ID;
    this->sexo = bebe.sexo;
    this->cantidad_de_pruebas = bebe.cantidad_de_pruebas;
    this->state = bebe.state;
    this->birth_date = bebe.birth_date;
    this->baby_name = bebe.baby_name;
    this->mother_name = bebe.mother_name;
    this->date = bebe.date;
    this->time = bebe.time;
    this->SPO2_bebe_value_average_OXY1 = bebe.SPO2_bebe_value_average_OXY1;
    this->SPO2_bebe_value_average_OXY2 = bebe.SPO2_bebe_value_average_OXY2;
    this->beats_per_minute_value_average_OXY1 = bebe.beats_per_minute_value_average_OXY1;
    this->beats_per_minute_value_average_OXY2 = bebe.beats_per_minute_value_average_OXY2;
    this->PI_value_average_OXY1 = bebe.PI_value_average_OXY1;
    this->PI_value_average_OXY2 = bebe.PI_value_average_OXY2;
    this->data_function_size = bebe.data_function_size;
    this->data_adc_buffer_size = bebe.data_adc_buffer_size;
    this->SPO2_data_function_OXY1_size = bebe.SPO2_data_function_OXY1_size;
    this->SPO2_data_function_OXY2_size = bebe.SPO2_data_function_OXY2_size;
    this->BPM_data_function_OXY1_size = bebe.BPM_data_function_OXY1_size;
    this->BPM_data_function_OXY2_size = bebe.BPM_data_function_OXY2_size;
    this->PI_data_function_OXY1_size = bebe.PI_data_function_OXY1_size;
    this->PI_data_function_OXY2_size = bebe.PI_data_function_OXY2_size;

    for(quint32 i=0; i < bebe.data_function_size; i++){

        this->function_0_data_bebe[i] = bebe.function_0_data_bebe[i];
        this->function_1_data_bebe[i] = bebe.function_1_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.data_adc_buffer_size; i++){

        this->HR_data_bebe[i] = bebe.HR_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.SPO2_data_function_OXY1_size; i++){

        this->SPO2_function_OXY1_data_bebe[i] = bebe.SPO2_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.SPO2_data_function_OXY2_size; i++){

        this->SPO2_function_OXY2_data_bebe[i] = bebe.SPO2_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.BPM_data_function_OXY1_size; i++){

        this->BPM_function_OXY1_data_bebe[i] = bebe.BPM_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.BPM_data_function_OXY2_size; i++){

        this->BPM_function_OXY2_data_bebe[i] = bebe.BPM_function_OXY2_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.PI_data_function_OXY1_size; i++){

        this->PI_function_OXY1_data_bebe[i] = bebe.PI_function_OXY1_data_bebe[i];
    }
    for(quint32 i=0; i < bebe.PI_data_function_OXY2_size; i++){

        this->PI_function_OXY2_data_bebe[i] = bebe.PI_function_OXY2_data_bebe[i];
    }


}
//-----------------------------------------------------------------------------------------------------------------------


//Esta funcion me devuelve un booleano true si son dos bebes iguales-----------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
bool Bebe_Data_Class::is_equal(Bebe_Data_Class bebe){

    if(this->mother_name == bebe.mother_name && this->baby_name == bebe.baby_name)
        return true;
    else
        return false;
}
//-----------------------------------------------------------------------------------------------------------------------
