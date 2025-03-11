#include <Arduino.h>
#include <EasyNextionLibrary.h>
#include <graphs.h>
#include <math.h> 

/*
void updateTachometer(int data_buffer[48],EasyNex &myNex){
    
    uint16_t value = getFromBuffer(2,2,data_buffer);

    uint32_t number_of_images = 208;     //There are actually 209 but the 0th image doesnt count

    uint32_t offset = 2;
    uint32_t image_number;
    if (value>16000.0){
        image_number = number_of_images;
    }else{
        image_number = value * (number_of_images/16000.0);
    }
    image_number += offset;

    myNex.writeNum("tachometer.pic",image_number);
}
*/

void updateSpeedometer(int data_buffer[48],EasyNex &myNex){

    uint16_t value = getFromBuffer(32, 2, data_buffer);


    uint32_t number_of_images = 270;     //There are actually 271 but the 0th image doesnt count
    uint32_t offset = 211;
    uint32_t image_number;
     
    if (value>120){
        image_number = number_of_images;
    }else{
        image_number = value * (number_of_images/120.0);
    }
    image_number += offset;

    myNex.writeNum("speedometer.pic",image_number);
}


void updateTemp(int data_buffer[48], EasyNex &myNex){

    uint16_t value = getFromBuffer(4,2,data_buffer);


    const uint16_t in_red_bound = 90; //change this is not temp but value on progress bar
    const uint16_t in_orange_band = 80; //"" ""
    const uint16_t max_val = 200; // The maximum value of temperature to be 100 on the progress bar

    int scaled_for_bar_value = (value * 100) / max_val;
    if (scaled_for_bar_value > 100){
        scaled_for_bar_value = 100;
    };
    myNex.writeNum("temp_guage.val",scaled_for_bar_value);
    
    uint16_t colour = 1024;  //Colour value for a visual warning on the guage -inital = green
    if (scaled_for_bar_value > in_red_bound){
        colour = 40960; //red
    }else if (scaled_for_bar_value > in_orange_band){
        colour = 45504; //orange
    };
    myNex.writeNum("temp_guage.pco",colour);
}

void updateTachometer(int data_buffer[48], EasyNex &myNex){

    uint16_t value = getFromBuffer(2,2,data_buffer);


    const uint16_t in_red_bound = 80; //change this is not temp but value on progress bar
    const uint16_t in_orange_band = 70; //"" ""
    const uint16_t max_val = 16000; // The maximum value of temperature to be 100 on the progress bar

    int scaled_for_bar_value = (value * 100) / max_val;
    if (scaled_for_bar_value > 100){
        scaled_for_bar_value = 100;
    };
    myNex.writeNum("tachometer.val",scaled_for_bar_value);
    
    uint16_t colour = 1024;  //Colour value for a visual warning on the guage -inital = green
    if (scaled_for_bar_value > in_red_bound){
        colour = 40960; //red
    }else if (scaled_for_bar_value > in_orange_band){
        colour = 45504; //orange
    };
    myNex.writeNum("tachometer.pco",colour);
}

void updateManifoldAirTemperature(int data_buffer[48],EasyNex &myNex){ //Turns warning light on/off

    int temp = getFromBuffer(12,2,data_buffer);

    int max_safe_val = 100;
    int min_safe_val = 0;
    int colour = 1024; //green
    if ((temp> max_safe_val)||(temp < min_safe_val)){
        colour = 40960; //red
    }
    myNex.writeNum("cool_light.bco", colour);  // Change background color
    delay(10);
    myNex.writeNum("cool_light.val", (colour == 40960) ? 1 : 0); // Toggle checkbox

}

void updateAirPressure(int data_buffer[48], EasyNex &myNex){ //Turns warning light on/of 

    uint16_t pressure = getFromBuffer(0,2,data_buffer);

    uint16_t max_safe_val = 120;
    uint16_t min_safe_val = 50;
    int colour = 1024; //green
    if ((pressure> max_safe_val)||(pressure < min_safe_val)){
        colour = 40960; //red
    }
    myNex.writeNum("air_pres_light.bco", colour);  // Change background color
    delay(10);
    myNex.writeNum("air_pres_light.val", (colour == 40960) ? 1 : 0); // Toggle checkbox

}

void updateBatteryVoltage(int data_buffer[48], EasyNex &myNex){ //Turns warning light on/off

    uint16_t voltage = getFromBuffer(24,2,data_buffer);

    float max_safe_val = 12.5;
    float min_safe_val = 11.5;
    int colour = 1024; //green
    if ((voltage> max_safe_val)||(voltage < min_safe_val)){
        colour = 40960; //red
    }
    myNex.writeNum("battery_light.bco", colour);  // Change background color
    delay(10);
    myNex.writeNum("battery_light.val", (colour == 40960) ? 1 : 0); // Toggle checkbox
}
void setWarningLights(int data_buffer[48],EasyNex &myNex){ //Just runs the updates only for simplification
    updateAirPressure(data_buffer, myNex);
    updateManifoldAirTemperature(data_buffer, myNex);
    updateBatteryVoltage(data_buffer,myNex);
}

void updateGear(int data_buffer[48], EasyNex &myNex) { // Calculates and displays the gear 
    int rpm = getFromBuffer(2,2,data_buffer);
    int speed = getFromBuffer(32,2,data_buffer);
    
    if (speed == 0) { // Ensures no zero errors
        return;
    }
    
    float wheel_dia = 0.4;
    float wheel_rpm = (26.82*speed)/(3.142*wheel_dia); // Convert speed to metres per minute and divide by wheel circumference
    float ratio = rpm/wheel_rpm;
    
    float gear_ratios[7] = {5, 12, 20, 33, 45, 50, 60}; // These are arbitrary, need to change once I know the actual values
    int closest = gear_ratios[0];  // Assume first number is closest
    int minDiff = fabs(ratio - closest);
    
    int gear_number = 1;  // Initialize gear_number outside the loop
    static int i = 0;
    i = 0;  // Reset i at each function call
    
    for (int num : gear_ratios) { // Finds the gear whose gear ratio matches the ratio of crankshaft rpm to wheel rpm
        i++;
        int diff = fabs(ratio - num);
        if (diff < minDiff) {
            minDiff = diff;
            gear_number = i;  
        }
    }
    
    char intStr[8];  // Sufficient for int (-2147483648 to 2147483647)
    itoa(gear_number, intStr, 10);  // Convert integer to string (base 10)
    
    myNex.writeStr("gear.txt", intStr);  // Pass the string to the Nextion
}



void updateHomePage(EasyNex &myNex,int data_buffer[48]){



        setWarningLights(data_buffer, myNex);
        updateTachometer(data_buffer, myNex);
        updateSpeedometer(data_buffer, myNex);
        updateTemp(data_buffer,myNex);
        updateGear(data_buffer, myNex);


}

