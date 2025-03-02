#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <home_page.h>
EasyNex myNex(Serial);
int data_buffer[48] = { 0 };
MCP_CAN CAN0(10);




void sendChartData(const char * id, const char * units,int num_bytes,int location_in_buffer,char data_string_buffer[20],char units_buffer[18]){
  String id_as_string = id;
  int data_from_buffer = getFromBuffer(location_in_buffer,num_bytes,data_buffer);
  itoa(data_from_buffer, data_string_buffer, 10);
  units_buffer[0] = *units;
  data_string_buffer[2] = *units_buffer;
  String data_string = data_string_buffer;
  myNex.writeStr(id_as_string,data_string);

}

void updateDataChart(){
  char data_string_buffer[20];
  char units[18];


  sendChartData("map.txt"," kPa",2, 0, data_string_buffer, units);
  sendChartData("rpm.txt"," RPM", 2,2, data_string_buffer, units);
  sendChartData("clt.txt"," deg F",2, 4, data_string_buffer, units);
  sendChartData("tps.txt"," deg BTDC",2, 6, data_string_buffer, units);
  sendChartData("pw1.txt"," AFR",2, 8, data_string_buffer, units);
  sendChartData("pw2.txt"," AFR",2, 10, data_string_buffer, units);
  sendChartData("mat.txt"," %",2, 12, data_string_buffer, units);
  sendChartData("adv_deg.txt"," deg F",2, 14, data_string_buffer, units);
  sendChartData("afrtg1.txt"," ms",1, 16, data_string_buffer, units);
  sendChartData("afr1.txt"," V",1, 17, data_string_buffer, units);
  sendChartData("egocor1.txt"," deg",2, 18, data_string_buffer, units);
  sendChartData("egt1.txt"," m/s",2, 20, data_string_buffer, units);
  sendChartData("pwseq1.txt"," deg",2, 22, data_string_buffer, units);
  sendChartData("batt.txt"," deg",2, 24, data_string_buffer, units);
  sendChartData("knk_rtd.txt"," ",1, 30, data_string_buffer, units);
  sendChartData("vss1.txt"," ",2, 32, data_string_buffer, units);
  sendChartData("tc_retard.txt"," ",2, 34, data_string_buffer, units);
  sendChartData("launch_timing.txt"," ",2, 36, data_string_buffer, units);
  sendChartData("sw.txt"," ",1, 40, data_string_buffer, units);
  sendChartData("tp.txt"," ",2, 41, data_string_buffer, units);
  sendChartData("nsl1.txt"," ",2, 43, data_string_buffer, units);
  sendChartData("gp.txt"," ",2, 45, data_string_buffer, units);

}


void setup(){
  
  while (!startCan(CAN0)){
    Serial.begin(10);
    Serial.println("Waiting for CAN");
  };
  delay(500);
  myNex.begin(9600);

}

void loop(){
  myNex.NextionListen();
  int page = myNex.readNumber("dp");
  readCanDataInBuffer(data_buffer,CAN0);

  if (page == 1){
    updateHomePage(myNex,data_buffer);
  }
  else if (page == 7 || page == 8 || page == 9){
    updateDataChart();
  }
  else if (!(page == 0)) {
    updateGraphs(data_buffer,myNex);
  }

}
