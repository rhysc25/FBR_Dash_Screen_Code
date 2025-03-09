#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <can_manager.h>

/*
int convertToGraphValue(int min, int max, int value){
    int max_return_value = 5*256/6;

    max -= min;



    value = value * (max_return_value/max);
    value += min;
    return value;
}
void sendValueToGraph(String variable_name, int value, EasyNex myNex){
    myNex.writeNum(variable_name,value);
}
void updateBatteryGraph(int data_buffer[48],EasyNex myNex){
    int batt_volts = getFromBuffer(24,2,data_buffer);
    int max = 13;
    int min = 11;
    int graph_value = convertToGraphValue(min,max,batt_volts);
    sendValueToGraph("bat_volts.val",graph_value,myNex);
}
void updateRevsGraph(int data_buffer[48],EasyNex myNex){
    int revs = getFromBuffer(2,2,data_buffer);
    int max = 16000;
    int min = 0;
    int graph_value = convertToGraphValue(min,max,revs);
    sendValueToGraph("revs_var.val",graph_value,myNex);
}
void updateEngineTempGraph(int data_buffer[48],EasyNex myNex){
    int temp = getFromBuffer(4,2,data_buffer);
    int max = 200;
    int min = 0;
    int graph_value = convertToGraphValue(min,max,temp);
    sendValueToGraph("temp_var.val",graph_value,myNex);
}
void updateVelocityGraph(int data_buffer[48],EasyNex myNex){
    int revs = getFromBuffer(0,2,data_buffer);
    int max = 255;
    int min = 0;
    int graph_value = convertToGraphValue(min,max,revs);
    sendValueToGraph("vel_var.val",graph_value, myNex);
}
void updateGraphs(int data_buffer[48],EasyNex myNex){
    updateBatteryGraph(data_buffer,myNex);
    updateRevsGraph(data_buffer,myNex);
    updateEngineTempGraph(data_buffer,myNex);
    updateVelocityGraph(data_buffer,myNex);
}
*/