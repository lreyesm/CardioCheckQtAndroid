#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>

#include "plot.h"

#include <QDesktopWidget>
#include "bebe_data_class.h"

#define DELAY_LOOKING_BLUETOOTH 2000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupBluetooth();

    void hide_all();

    void conectar_senales_de_botones();

    void setupGraph_Oxy1();
    void setupGraph_Oxy2();
    void setupGraph_EKG();

    void setup_Plot_Interactions();

    enum state_of_app{IDLE, BUSCANDO_DISPOSITIVO, NO_ENCONTRADO, ESTABLECIENDO_CONEXION, CONECTADO, GUARDANDO_DATOS, GUARDADO, REINICIANDO, ERROR, DESCONECTADO};

    enum state_of_app app_state = IDLE;

    void show_cartel_buscando_dispositivo_bluetooth();
    void show_cartel_no_encontrado_dispositivo_bluetooth();
    void show_cartel_estableciendo_conexion();
    void show_cartel_conectado();
    void show_cartel_guardando_datos();
    void show_cartel_datos_guardados_correctamente();
    void show_cartel_Desconectado();
    void show_cartel_Error_de_conexion();

    void show_pantalla_base_de_datos();
    void show_pantalla_test();
    void show_pantalla_paciente();
    void show_pantalla_ajustes();

    void show_widget_paciente_datos();
    void show_widget_pantalla_ajustes_widget_colores();

    void show_menu();

    int paint_now = 0;
protected:

//    void paintEvent(QPaintEvent *event){  ///divide la cantidad de repaints del widget

//        if(paint_now >= 10){
//            QWidget::paintEvent(event);
//            paint_now = 0;
//        }
//        else{
//            paint_now++;
//        }
//    }

    void mousePressEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
        emit mouse_pressed();
    }
    void mouseDoubleClickEvent(QMouseEvent *e){

        emit mouse_DoubleClick();
    }
    void mouseReleaseEvent(QMouseEvent *e) ///al reimplementar esta funcion deja de funcionar el evento pressed
    {
        emit mouse_Release();
    }


private slots:


    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void socketError(QBluetoothSocket::SocketError error);
    void socketConnected();
    void socketDisconnected();
    void socketStateChanged();

    void readSerial();

    void on_data_received(QByteArray serialData);

    void readSerial_initilization();

    void afterUpdateGraph();

    void on_time_out_Ver_registro();

    void timeOut_Delay_Not_Found_Device();

    void timeOut_Delay_PowerOn();

    void timeOut_Delay_Guardar();

    void timeOut_Delay_ReInit_Discovery();

signals:

    void mouse_pressed();
    void mouse_Release();
    void mouse_DoubleClick();
    void data_Received(QByteArray);

private slots:

    void on_drag_screen();
    void on_start_scrolling_screen_test_timeout();
    void on_start_scrolling_screen_ajustes_timeout();
    void on_drag_screen_released();
    void on_mouse_DoubleClick();


    void on_pb_pant_paciente_conectar();
    void on_pb_pant_paciente_descartar();
    void on_pb_pant_paciente_test();
    void on_pb_pant_paciente_nuevo();
    void on_pb_pant_paciente_base_de_datos();
    void on_pb_pant_paciente_menu();
    void on_pb_pant_paciente_fecha_de_nacimiento();
    void on_pb_pant_paciente_radioB_femenino();
    void on_pb_pant_paciente_radioB_masculino();
    void on_le_pant_paciente_ID_textChanged(const QString &arg1);

    void on_le_pant_base_de_datos_buscar_textChanged(const QString &arg1);
    void on_lw_pant_base_de_datos_pacientes_itemClicked(QListWidgetItem *item);
    void on_pb_pant_base_de_datos_nuevo();

    void on_pb_menu_salir();
    void on_pb_menu_ayuda();
    void on_pb_menu_acerca_de();

    void on_pb_pant_test_Graficar_Iniciar();
    void on_pb_pant_test_Ver_Registro_Guardar();
    void on_pb_pant_test_pause_play();
    void on_pb_pant_test_atras();

    void on_pb_widget_paciente_datos_Nuevo_Test();
    void on_pb_widget_paciente_datos_Ver_Registro();
    void on_pb_pant_test_ajustes();

    void on_pb_pant_ajustes_atras();
    void on_pb_pant_ajustes_Generales();
    void on_le_widget_ajustes_generales_tiempo_de_ventana_textChanged(const QString &arg1);
    void on_pb_pant_ajustes_Visualizacion();
    void on_pb_pant_ajustes_ECG();
    void on_pb_pant_ajustes_Oxymetria();


    void on_pb_widget_ajustes_generales_color_ECG_Curva();
    void on_pb_widget_ajustes_generales_color_ECG_fondo();
    void on_pb_widget_ajustes_generales_color_Oxy1_Curva();
    void on_pb_widget_ajustes_generales_color_Oxy1_fondo();
    void on_pb_widget_ajustes_generales_color_Oxy2_Curva();
    void on_pb_widget_ajustes_generales_color_Oxy2_fondo();

    void on_pb_widget_colores_aceptar_ECG_Curva();
    void on_pb_widget_colores_aceptar_ECG_fondo();
    void on_pb_widget_colores_aceptar_Oxy1_Curva();
    void on_pb_widget_colores_aceptar_Oxy1_fondo();
    void on_pb_widget_colores_aceptar_Oxy2_Curva();
    void on_pb_widget_colores_aceptar_Oxy2_fondo();

    void on_pb_widget_colores_cancelar();
    void on_pb_widget_colores_amarillo();
    void on_pb_widget_colores_azul();
    void on_pb_widget_colores_naranja();
    void on_pb_widget_colores_verde();
    void on_pb_widget_colores_rojo();
    void on_pb_widget_colores_negro();
    void on_pb_widget_colores_violeta();
    void on_pb_widget_colores_rosado();
    void on_pb_widget_colores_gris();

    void on_pb_pant_gris_blur_plus();
    void on_pb_pant_gris_blur();

    void update_fecha_y_hora();

private:

    Ui::MainWindow *ui;

    Plot *customPlot_graph_Oxy1;
    Plot *customPlot_graph_Oxy2;
    Plot *customPlot_graph_EKG;

    QTimer timer_graph;
    QTime tiempo_de_Prueba = QTime(0,0,0);

    bool pausado = false;
    QTimer start_moving_screen;
    int init_pos_x;
    int init_pos_y;
    int delta_y_constant_scrolling_ajustes = 0;
    int delta_y_constant_scrolling_test = 0;


    QBluetoothDeviceDiscoveryAgent *agent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;

    QString bluetooth_adress_hc_rene;
    QString bluetooth_adress_hc_jaime;

    quint8 receive_bytes[UART_SEND_TOTAL_SIZE*3];
    quint8 function_values_graph_0[DATA_FUNCTION_SIZE];
    quint8 function_values_graph_1[DATA_FUNCTION_SIZE];
    quint16 function_values_graph_HR_16bits[DATA_ADC_BUFFER_SIZE];
    quint32 function_value_count =0;
    quint32 function_value_pos=0;
    quint32 HR_value_pos=0;
    quint32 x_axis_count=0;
    quint32 HR_value_count=0;

    quint8 SPO2_Oxy1_function_values[SPO2_FUNCTION_BUFFER_SIZE];
    quint8 SPO2_Oxy2_function_values[SPO2_FUNCTION_BUFFER_SIZE];
    quint16 BPM_Oxy1_function_values[BPM_FUNCTION_BUFFER_SIZE];
    quint16 BPM_Oxy2_function_values[BPM_FUNCTION_BUFFER_SIZE];
    quint16 PI_Oxy1_function_values[PI_FUNCTION_BUFFER_SIZE];
    quint16 PI_Oxy2_function_values[PI_FUNCTION_BUFFER_SIZE];
    quint32 function_value_count_SPO2_BPM_PI=0;

    quint64 SPO2_bebe_value_average_OXY1 = 0;
    quint64 SPO2_bebe_value_average_OXY2 = 0;
    quint64 beats_per_minute_value_average_OXY1 = 0;
    quint64 beats_per_minute_value_average_OXY2 = 0;
    quint16 PI_value_average_OXY1 = 0;
    quint16 PI_value_average_OXY2 = 0;

    bool valid_receive_data = false;
    quint32 last_bad_receive_pos=0;
    bool first_receive=true;
    int errores=0;

    qint8 picar_frec=0;
    qint8 picar_frec_act_data=0;
    qint16 actualizar_porciento_counter=0;



    QString database_name = "/CardioCheck_database/base_datos_oximetria.dat";
    QString beat_sound_name = "/CardioCheck_database/beat_sound.wav";

    bool cargar_base_de_datos();
    QString ordenar_para_lista_de_paciente(Bebe_Data_Class &bebe_object_copia);

    Bebe_Data_Class *bebe_object = new Bebe_Data_Class("mama", "bebe");//funciona con un puntero a la clase pero con un objeto de la clase no

    bool primera_vuelta=true;
    bool ver_registro_activated = false;
    quint32 ver_registro_counter=0;
    quint32 x_axis_count_recorded=0;

    float porciento_de_adquirido=0;
    quint32 porciento_de_adquirido_ver_registro=0;



    void update_data_pacient_in_labels(bool desde_pantalla_principal);
    QString sexo_de_paciente="masculino";
    QDate birth_date_paciente = QDate(1991,7,16);

    QTimer timer_time;
    QStringList lista_de_pacientes;


    QByteArray QString_to_QByte_Array(QString string);
    QByteArray quint16_to_QByte_Array(quint16 integer);
    QByteArray quint32_to_QByte_Array(quint32 integer);
    QByteArray quint64_to_QByte_Array(quint64 integer);

    QTimer timer_delay;

    bool reinit_done = false;
    bool founded_device = false;
    bool comunication_established = false;

    void reinit_graph_values();
    void clear_graphs(bool clear_data = true, bool replot = true);


    void process_received_buffer(quint8 *);

    quint32 ancho_de_ventana_EKG = EKG_GRAPH_RANGE;
    quint32 ancho_de_ventana_OXY = OXY_GRAPH_RANGE;


    void check_message_crc32();
    void check_message(qint64 bytes_size);
    uint32_t crc32(const void *buf, size_t size);

};

#endif // MAINWINDOW_H
