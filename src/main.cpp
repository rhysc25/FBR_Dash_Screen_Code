#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <home_page.h>
EasyNex myNex(Serial);
int data_buffer[48] = { 0 };
MCP_CAN CAN0(10);

void sendChartData(const char * id, int num_bytes,int location_in_buffer){
  String id_as_string = id;

  int int_from_buffer = getFromBuffer(location_in_buffer, num_bytes, data_buffer);

  char intStr[8];  // Sufficient for int (-2147483648 to 2147483647)
  itoa(int_from_buffer, intStr, 10);  // Convert integer to string (base 10)

  myNex.writeStr(id_as_string,intStr);
}

void updateDataChart(){

  sendChartData("map.txt",2, 0);
  sendChartData("rpm.txt",2,2);
  sendChartData("clt.txt",2, 4);
  sendChartData("tps.txt",2, 6);
  sendChartData("pw1.txt",2, 8);
  sendChartData("pw2.txt",2, 10);
  sendChartData("mat.txt",2, 12);
  sendChartData("adv_deg.txt",2, 14);
  sendChartData("afrtg1.txt",1, 16);
  sendChartData("afr1.txt",1, 17);
  sendChartData("egocor1.txt",2, 18);
  sendChartData("egt1.txt",2, 20);
  sendChartData("pwseq1.txt",2, 22);
  sendChartData("batt.txt",2, 24);
  sendChartData("knk_rtd.txt",1, 30);
  sendChartData("vss1.txt",2, 32);
  sendChartData("tc_retard.txt",2, 34);
  sendChartData("launch_timing.txt",2, 36);
  sendChartData("sw.txt",1, 40);
  sendChartData("tp.txt",2, 41);
  sendChartData("nsl1.txt",2, 43);
  sendChartData("gp.txt",2, 45);

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
    sendChartData("rpm.txt",2,2);
    sendChartData("vss1.txt",2,32);
  }
  else if (!(page == 0)) {
    updateDataChart();
  }

}
