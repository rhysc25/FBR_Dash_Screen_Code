#include <mcp_can.h>
#include <SPI.h>



bool startCan(MCP_CAN CAN0){
    #define CAN0_INT 2

    if(!(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ)==CAN_OK)){
        return 0;
    }
    else{
        CAN0.setMode(MCP_NORMAL);
        pinMode(CAN0_INT, INPUT);
        return 1;
    };
}



void set_data(int data_buffer[48],unsigned char rxBuf[8], long unsigned int rxID){
    
    int pointer_offset = (rxID - 1512)*8;
    int * pointer_start = data_buffer+pointer_offset;
    
    int byte_in_buf = 0;
     
    while (byte_in_buf<8){
        *(pointer_start+byte_in_buf) = *(rxBuf+byte_in_buf);
        
        byte_in_buf++;
    }
}


void readCanDataInBuffer(int data_buffer[48],MCP_CAN CAN0){
    long unsigned int rxID;
    unsigned char len=0;
    unsigned char rxBuf[8];

    #define CAN0_INT 2

    if (!digitalRead(CAN0_INT)){
        CAN0.readMsgBuf(&rxID, &len, rxBuf);
        set_data(data_buffer,rxBuf, rxID); 
    }
    
    
}
int getFromBuffer(int pointer_offset,int num_bytes,int data_buffer[48]){
    int data_from_buffer = 0;
    double scale_factor_list[48] = {0.1,0,1,0,0.1,0,0.1,0,0.001,0,0.001,0,10,0,10,0,10,10,10,0,10,0,0.001,0,10,0,10,0,10,0,10,10,0,10,0,10,0,1,1,1,1};

    for (int byte=0;byte==num_bytes; byte ++){
    data_from_buffer += data_buffer[pointer_offset] << 8*byte;
    }

    data_from_buffer = data_from_buffer * scale_factor_list[pointer_offset];
    return data_from_buffer;
}
