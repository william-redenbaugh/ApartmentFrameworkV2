#include "Pcars.hpp"

/**************************************************************************/
/*!
    @brief Sets up communication with the project CARs UDP client
*/
/**************************************************************************/
void ProjectCARSParser::begin(void){
    udp_server.open(PROJECT_CARS_DEFAULT_UDP_PORT, 2048);
}

/**************************************************************************/
/*!
    @brief Reads and parses data from  Project CARs
*/
/**************************************************************************/
void ProjectCARSParser::parse_data(void){
    uint16_t packet_size = udp_server.receive_blocking(packet);     

    // If there is data in the packet. 
    if(packet_size){
        
        // Temp space that we will use for importing data. 
        uint8_t temp[2];

        // Participant Information character arrays coppied into class. 
        if(packet_size == 1347){
            memcpy(&car_name, &packet[3], 64);
            memcpy(&car_class_name, &packet[67], 64);
            memcpy(&track_location, &packet[131], 64);
            memcpy(&track_variation, &packet[195], 64);
        }

        if(packet_size == 1367){
            // Get the current status of the race
            memcpy(&race_state, &packet[10], 1);
            
            // gear data
            uint8_t gear;
            // Copy over the gear information
            memcpy(&gear, &packet[128], 1);
            
            gear = gear & 0x0f;
            // translate gear information into human readable information
            if (gear == 0xf)
                gear_field = 'R';
            else if (gear == 0)
                gear_field = 'N';
            else
                gear_field = (char) gear + '0';

            // current rpm
            memcpy(&temp, &packet[124], 2);
            rpm = (temp[1] << 8) + temp[0];
            sprintf(rpm_field, "%5u", rpm);

            // max rpm
            memcpy(&temp, &packet[126], 2);
            max_rpm = (temp[1] << 8) + temp[0];

            // speed
            memcpy(&spd, &packet[120], 4);
            spd *= 3.6; // telemetry speed is in meter per second
            sprintf(spd_field, "%3u", (int)spd);

            // fuel
            memcpy(&fuel_capacity, &packet[111], 1);
            memcpy(&fuel_level, &packet[116], 4);
            fuel_amount = fuel_level * (float)fuel_capacity;
            if (fuel_amount >= 100)
            {
                sprintf(fuel_amount_field, "%4u", (int) fuel_amount);
            }
            else
            {
                sprintf(fuel_amount_field, "%4.1f", fuel_amount);
            }

            // odometer
            memcpy(&odometer, &packet[132], 4);
            if (odometer < 10000)
            {
                sprintf(odometer_field, "%6.1f", odometer);
            }
            else
            {
                sprintf(odometer_field, "%6u", (int) odometer);
            }

            // lap time
            memcpy(&best_lap_time, &packet[12], 4);
            memcpy(&last_lap_time, &packet[16], 4);
            memcpy(&current_time, &packet[20], 4);
            if (last_lap_time >= 60.)
            {
                minutes = (uint8_t) (last_lap_time / 60);
                sprintf(last_lap_field, "%2u:%06.3f", minutes, last_lap_time - 60 * (float)minutes);
            }
            else if (last_lap_time > 0.)
            {
                sprintf(last_lap_field, "   %06.3f", last_lap_time);
            }
            else
            {
                sprintf(last_lap_field, "%9s", "   n/v   ");
            }

            // current lap
            memcpy(&current_lap, &packet[464 + 10], 1);
            sprintf(current_lap_field, "%2u", current_lap);

            // sector
            memcpy(&sector, &packet[464 + 11], 1);

            // current lap distance
            memcpy(&temp, &packet[464 + 6], 2);
            current_lapDistance = (temp[1] << 8) + temp[0];

            // joy_pad + dpad
            memcpy(&temp, &packet[96], 2);
            joy_pad = (temp[1] << 8) + temp[0];
            button_status = (joy_pad & 4096) | (joy_pad & 4);  // X button on PS4, A on PC and XBox

            // tyres
            // Order of tyres is _lf, _rf, _lr, _rr
            memcpy(&temp, &packet[336], 2);
            tyre_tread_temp_lf = (temp[1] << 8) + temp[0] - 273;
            if (tyre_tread_temp_lf > 9999) tyre_tread_temp_lf = 0;
            sprintf(tyre_tread_temp_lf_field, "%4d", tyre_tread_temp_lf);
            memcpy(&temp, &packet[338], 2);
            tyre_tread_temp_rf = (temp[1] << 8) + temp[0] - 273;
            if (tyre_tread_temp_rf > 9999) tyre_tread_temp_rf = 0;
            sprintf(tyre_tread_temp_rf_field, "%4d", tyre_tread_temp_rf);
            memcpy(&temp, &packet[340], 2);
            tyre_tread_temp_lr = (temp[1] << 8) + temp[0] - 273;
            if (tyre_tread_temp_lr > 9999) tyre_tread_temp_lr = 0;
            sprintf(tyre_tread_temp_lr_field, "%4d", tyre_tread_temp_lr);
            memcpy(&temp, &packet[342], 2);
            tyre_tread_temp_rr = (temp[1] << 8) + temp[0] - 273;
            if (tyre_tread_temp_rr > 9999) tyre_tread_temp_rr = 0;
            sprintf(tyre_tread_temp_rr_field, "%4d", tyre_tread_temp_rr);

            // brakes
            memcpy(&temp, &packet[328], 2);
            break_temp_lf = (temp[1] << 8) + temp[0];
            if (break_temp_lf > 9999) break_temp_lf = 0;
            sprintf(break_temp_lf_field, "%4d", break_temp_lf);
            memcpy(&temp, &packet[330], 2);
            break_temp_rf = (temp[1] << 8) + temp[0];
            if (break_temp_rf > 9999) break_temp_rf = 0;
            sprintf(break_temp_rf_field, "%4d", break_temp_rf);
            memcpy(&temp, &packet[332], 2);
            break_temp_lr = (temp[1] << 8) + temp[0];
            if (break_temp_lr > 9999) break_temp_lr = 0;
            sprintf(break_temp_lr_field, "%4d", break_temp_lr);
            memcpy(&temp, &packet[334], 2);
            break_temp_rr = (temp[1] << 8) + temp[0];
            if (break_temp_rr > 9999) break_temp_rr = 0;
            sprintf(break_temp_rr_field, "%4d", break_temp_rr);

            if (max_rpm)
            {
                rpm_ratio = (float)rpm / (float)max_rpm;
            }
            else
            {
                rpm_ratio = 0.0;
            }
        }
    }
}