#ifndef BEBE_DATA_CLASS_H
#define BEBE_DATA_CLASS_H

#include <QString>
#include <QDataStream>
#include <QDate>
#include <QTime>

#define FUNCTION_BUFFER_SIZE 25
#define FUNCTION_BUFFER_STORAGE_SIZE FUNCTION_BUFFER_SIZE*4

#define ADC_BUFFER_SIZE 100
#define ADC_BUFFER_STORAGE_SIZE ADC_BUFFER_SIZE*4
#define TIMER_TIMEOUT_ADC_READ 4 ////en milisegundos

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define HEADER_ID 0x0FA
//#define TAIL_ID 0x0FA
#define HEADER_START_POS 0
//#define TAIL_START_POS 162
#define HEADER_SIZE 2
//#define TAIL_SIZE 2
#define CHECK_SUM_SIZE 4 //32bits

#define DATA_INIT_BUFFER_POS HEADER_START_POS + HEADER_SIZE  //2
//#define DATA_INIT_BUFFER_ID 0x09B
#define DATA_BUFFER_TRANSMIT_0 0x011
#define DATA_BUFFER_TRANSMIT_1 0x022
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OXYMETER_1  1 //UART2
#define OXYMETER_2  2 //UART3
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SPO2_BUFFER_OXY1_POS DATA_INIT_BUFFER_POS //2
#define BPM_BUFFER_OXY1_POS SPO2_BUFFER_OXY1_POS+1 //3
#define PI_BUFFER_OXY1_POS SPO2_BUFFER_OXY1_POS+3 //5
#define SPO2_BUFFER_OXY2_POS PI_BUFFER_OXY1_POS+2 //7
#define BPM_BUFFER_OXY2_POS SPO2_BUFFER_OXY2_POS+1 //8
#define PI_BUFFER_OXY2_POS SPO2_BUFFER_OXY2_POS+3 //10

#define DESPLAZAMIENTO_EN_ENVIO_DE_PROMEDIOS 5

#define DATA_GRAPH_HR_INIT_BUFFER_POS DATA_INIT_BUFFER_POS+10 //12
#define DATA_GRAPH_FT_INIT_BUFFER_POS DATA_GRAPH_HR_INIT_BUFFER_POS + ADC_BUFFER_SIZE*2 //210 //por 2 porque adc buffer es de 16bits
#define DATA_GRAPH_FT_2_INIT_BUFFER_POS DATA_GRAPH_FT_INIT_BUFFER_POS+FUNCTION_BUFFER_SIZE //235

#define CHECKING_CONNECTION  0x0AC ////Chequeando conexion solo para android
#define ACKNOWLEDGE_END_OF_RECORDING  0x0AF ////acknowledge de fin de grabacion y salvar en BD
#define INIT_PROG_ID 0x0AA   ////Inicio de Programa
#define INIT_SEND_ID 0x0FE  ////Inicio de Envio de informacion
#define INIT_SAVE_TO_SD 0x0FD  ////Inicio de salva de informacion en SD
#define STOP_SAVE_TO_SD 0x0FC  ////Fin de salva de informacion en SD
#define ERROR_ID 0x0F  ////Envio de Error de recivo

//#define HEADER_END_POS 160

//#define CURRENT_OXYMETER_OXY1_POS DATA_INIT_BUFFER_POS+1 //3
#define STATUS_CHECK_ADC DATA_GRAPH_FT_2_INIT_BUFFER_POS+FUNCTION_BUFFER_SIZE //262 ----------Enviar aqui status de electrodos -------------------
#define STATUS_CHECK_BEAT STATUS_CHECK_ADC + 1 //263
#define STATUS_CHECK_OXY1_POS STATUS_CHECK_BEAT + 1//264
#define STATUS_CHECK_OXY2_POS STATUS_CHECK_OXY1_POS+1 //265

//#define CURRENT_OXYMETER_OXY2_POS DATA_GRAPH_FT_INIT_BUFFER_POS+(FUNCTION_BUFFER_SIZE*2) //260
//#define SPO2_BUFFER_OXY2_POS CURRENT_OXYMETER_OXY2_POS //260

#define UART_SEND_BUFFER_SIZE STATUS_CHECK_OXY2_POS + 1 //266
#define UART_SEND_TOTAL_SIZE UART_SEND_BUFFER_SIZE + CHECK_SUM_SIZE //270
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define MAX_TIME_RECORDING 300////en segundos (solo valores pares) //300 son 5 minutos
#define DATA_FUNCTION_SIZE  (int)(FUNCTION_BUFFER_SIZE*MAX_TIME_RECORDING*2.5)  ////FUNCTION_BUFFER_SIZE * 150
#define DATA_ADC_BUFFER_SIZE  (int)(ADC_BUFFER_SIZE*MAX_TIME_RECORDING*2.5)  ////
#define SPO2_TIME_RECORDING MAX_TIME_RECORDING //en segundos
#define SPO2_FUNCTION_BUFFER_SIZE int(SPO2_TIME_RECORDING*2.5)
#define BPM_FUNCTION_BUFFER_SIZE SPO2_FUNCTION_BUFFER_SIZE
#define PI_FUNCTION_BUFFER_SIZE SPO2_FUNCTION_BUFFER_SIZE


#define UART_READ_BUFFER_SIZE 350


#define TIME_GRAPH_RANGE 8 //tiempo de actualizacion de ventana de graficas en segundos
                           //debe ser par para que el valor de OXY_GRAPH_RANGE sea entero
#define EKG_GRAPH_RANGE TIME_GRAPH_RANGE*250
#define OXY_GRAPH_RANGE (int)(EKG_GRAPH_RANGE/4)


#define SUMA_DE_PORCIENTO_RECIBIDO (((float)ADC_BUFFER_SIZE/DATA_ADC_BUFFER_SIZE)*100)


#define  SIZEOF_SEX_STRING         24
#define  SEX_STRING_LENGTH         (int)((SIZEOF_SEX_STRING-4)/2)
#define  SIZEOF_STATE_STRING       30
#define  STATE_STRING_LENGTH       (int)((SIZEOF_STATE_STRING-4)/2)
#define  SIZEOF_DATE_STRING        40
#define  DATE_STRING_LENGTH       (int)((SIZEOF_DATE_STRING-4)/2)
#define  SIZEOF_NAMES_STRING       80
#define  NAMES_STRING_LENGTH       (int)((SIZEOF_NAMES_STRING-4)/2)
#define  SIZEOF_TIME_STRING        24
#define  TIME_STRING_LENGTH       (int)((SIZEOF_TIME_STRING-4)/2)
#define  SIZEOF_PACIENT_DATA       195500

class Bebe_Data_Class
{
public:
    Bebe_Data_Class(QString b="unknow",QString m= "unknow");

    void operator_equal(Bebe_Data_Class);
    bool is_equal(Bebe_Data_Class);
    /*
    QDataStream& operator <<(Bebe_Data_Class);
    QDataStream& operator >>(Bebe_Data_Class);
    */
    void write_file(QDataStream &);
    void read_file(QDataStream &);

    void write_file_all_String_and_int_format(QDataStream &);
    void read_file_all_String_and_int_format(QDataStream &);

    void write_file_with_size_data(QDataStream &);
    void read_file_with_size_data(QDataStream &);

    void write_file_with_fix_size(QDataStream &);
    void read_file_with_fix_size(QDataStream &);
    void read_file_with_fix_size_pacient_info(QDataStream &);
    void read_file_with_fix_size_pacient_signals(QDataStream &);

    void read_file_with_size_data_only_pacient_info(QDataStream &);
    void read_file_with_size_data_only_pacient_size(QDataStream &);

    void read_file_with_size_data_fix_strings(QDataStream &in);
    void write_file_with_size_data_fix_strings(QDataStream &out);

    void read_file_with_size_data_only_pacient_info_fix_strings(QDataStream &in);
    void read_file_with_size_data_only_pacient_signals_fix_strings(QDataStream &in);

    void print_bebe_data();

    quint64 posicion_en_archivo;
    quint32 cantidad_de_pacientes;
    quint32 numero_de_paciente;
    quint32 size_of_pacient_data = SIZEOF_PACIENT_DATA;
    quint32 size_of_pacient_info;
    quint32 size_of_pacient_signals;
    quint64 ID;
    QString baby_name;
    QString mother_name;
    QString sexo;
    quint32 cantidad_de_pruebas;
    QString state;
    QDate birth_date;
    QDate date;
    QTime time;
    quint8 SPO2_bebe_value_average_OXY1;
    quint8 SPO2_bebe_value_average_OXY2;
    qint16 beats_per_minute_value_average_OXY1;
    qint16 beats_per_minute_value_average_OXY2;
    quint16 PI_value_average_OXY1;
    quint16 PI_value_average_OXY2;
    quint8 SPO2_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];
    quint8 SPO2_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 BPM_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 BPM_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 PI_function_OXY1_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 PI_function_OXY2_data_bebe[SPO2_FUNCTION_BUFFER_SIZE];

    quint8 function_0_data_bebe[DATA_FUNCTION_SIZE];
    quint8 function_1_data_bebe[DATA_FUNCTION_SIZE];
    quint16 HR_data_bebe[DATA_ADC_BUFFER_SIZE];
    quint32 data_function_size;
    quint32 data_adc_buffer_size;
    quint32 SPO2_data_function_OXY1_size;
    quint32 SPO2_data_function_OXY2_size;
    quint32 BPM_data_function_OXY1_size;
    quint32 BPM_data_function_OXY2_size;
    quint32 PI_data_function_OXY1_size;
    quint32 PI_data_function_OXY2_size;



};



#endif // BEBE_DATA_CLASS_H
