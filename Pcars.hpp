#ifndef _PCARS_HPP
#define _PCARS_HPP

// Includes all of our UDP stuff!
#include "UDPLow.hpp"

// Default port of the project cars stuff. 
#define PROJECT_CARS_DEFAULT_UDP_PORT 5606

// Credit for the UDP parsing goes to this guy --> https://github.com/binweg/pcars_display/blob/master/display.ino
// I took a bunch of his code and added my own stuff to it for the scope of this project. 

/**************************************************************************/
/*!
    @brief Project car UDP communication parsing class. 
*/
/**************************************************************************/
class ProjectCARSParser{
    public: 
        void begin(void);
        void read_parse_data(void);

        // Car and track information.
        char car_name[64];
        char car_class_name[64];
        char track_location[64];
        char track_variation[64];

        uint16_t rpm;
        uint16_t max_rpm;

        float rpm_ratio;
        uint8_t fuel_capacity;
        float fuel_level;
        float fuel_amount;
        float fuel_consumption;
        float fuel_lapsRemaining;
        float odometer;
        float spd;
        uint8_t minutes;
        float best_lap_time;
        float last_lap_time;
        float current_time;
        float oldcurrent_time;

        uint16_t tyre_tread_temp_lf;
        uint16_t tyre_tread_temp_rf;
        uint16_t tyre_tread_temp_lr;
        uint16_t tyre_tread_temp_rr;
        
        int16_t break_temp_lf;
        int16_t break_temp_rf;
        int16_t break_temp_lr;
        int16_t break_temp_rr;

        uint8_t current_lap;
        uint8_t oldcurrent_lap;

        // Gear information
        char gear_field;
                
    private: 
        UDPWrapper udp_server; 
        uint8_t packet[2048];

        // State of the race
        uint8_t race_state;

        bool button_status;
        
        char current_lap_field[3];
        uint8_t sector;

        uint16_t current_lapDistance;

        uint16_t joy_pad;
        uint8_t dPad;


        char rpm_field[6];

        char fuel_amount_field[5];
        char fuel_consumption_field[5];
        char fuel_laps_remaining_field[5];
        char fuel_lap;
        char odometer_field[7];
        char spd_field[4];
        char last_lap_field[10];

        char tyre_tread_temp_lf_field[5];
        char tyre_tread_temp_rf_field[5];
        char tyre_tread_temp_lr_field[5];
        char tyre_tread_temp_rr_field[5];

        char break_temp_lf_field[5];
        char break_temp_rf_field[5];
        char break_temp_lr_field[5];
        char break_temp_rr_field[5];
};

#endif