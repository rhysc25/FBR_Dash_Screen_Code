#include <iostream>
using namespace std;

void set_data(int data_buffer[48],unsigned char rxBuf[8], long unsigned int rxID){
    
    int pointer_offset = (rxID - 1512)*8;
    int * pointer_start = data_buffer+pointer_offset;
    
    int byte_in_buf = 0;
     
    while (byte_in_buf<8){
        *(pointer_start+byte_in_buf) = *(rxBuf+byte_in_buf);
        
        byte_in_buf++;
    }
}

int getFromBuffer(int pointer_offset,int num_bytes,int data_buffer[48]){
    int data_from_buffer = 0;
    double scale_factor_list[48] = {0.1,0,1,0,0.1,0,0.1,0,0.001,0,0.001,0,0.1,0,0.1,0,0.1,0.1,0,0.1,0,0.001,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0,0.1,0};

    for (int byte=0; byte < num_bytes; byte++) {
        data_from_buffer += data_buffer[pointer_offset + byte] << (8*byte);
    }

    data_from_buffer = data_from_buffer * scale_factor_list[pointer_offset];
    return data_from_buffer;
}


// RPM = 1000
unsigned char rxBuf1[8] = {0x00, 0x00, 0xE8, 0x03, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxID1 = 1512;  // Base CAN ID for MS-CAN broadcast

// RPM = 3000
unsigned char rxBuf2[8] = {0x00, 0x00, 0xB8, 0x0B, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxID2 = 1512;

// RPM = 5000
unsigned char rxBuf3[8] = {0x00, 0x00, 0x88, 0x13, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxID3 = 1512;

// RPM = 8000
unsigned char rxBuf4[8] = {0x00, 0x00, 0x40, 0x1F,0x00, 0x00, 0x00, 0x00};
long unsigned int rxID4 = 1512;

// RPM = 10000
unsigned char rxBuf5[8] = {0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxID5 = 1512;

// RPM = 14000
unsigned char rxBuf6[8] = {0x00, 0x00, 0xB0, 0x36, 0x00, 0x00, 0x00, 0x00};
long unsigned int rxID6 = 1512;


void testFunctions() {
    // Create test buffer
    int data_buffer[48] = {0};  // Initialize all to zero
    
    // Test set_data with test case 1
    set_data(data_buffer, rxBuf1, rxID1);
    
    // Print values to verify
    cout << ("After setting Test Case 1:") << "\n";
    for (int i = 0; i < 8; i++) {
      cout << "data_buffer[";
      cout << i;
      cout << "] = " << "\n";
      cout << data_buffer[i] << "\n";
    }
    
    
    // Test getFromBuffer
    int value = getFromBuffer(2, 2, data_buffer);
    cout << "Value from offset 2, 2 bytes: " << "\n";
    cout << value << "\n";
    
    // Additional tests can be added for other test cases
  }

  int main() {
    testFunctions();
  }