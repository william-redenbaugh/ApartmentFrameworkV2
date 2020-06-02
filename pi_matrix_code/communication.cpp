#include "communication.h"

// Global variables for our udp server. 
// Preprocessor
#define MAXLINE 7000

// All of our udp server info stuff!
struct {
    const uint16_t SERVER_PORT = 4040; 
    // Socket ID. 
    int sockfd; 
    // Socket address information
    struct sockaddr_in servaddr, cliaddr; 
    // UDP array that saves receive information
    uint8_t udp_arr[7000];
}udp_server_info; 

void setup_udp_server(void);  
int read_udp_dat(void);
_MessageData_MessageType unpack_information(int len);
uint8_t* get_udp_arr_dat();

void setup_udp_server(void){
	// Creating socket file descriptor 
    if ( (udp_server_info.sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
	memset(&udp_server_info.servaddr, 0, sizeof(udp_server_info.servaddr)); 
    memset(&udp_server_info.cliaddr, 0, sizeof(udp_server_info.cliaddr));
	// Filling server information 
    udp_server_info.servaddr.sin_family    = AF_INET; // IPv4 
    udp_server_info.servaddr.sin_addr.s_addr = INADDR_ANY; 
    udp_server_info.servaddr.sin_port = htons(udp_server_info.SERVER_PORT);
	// Bind the socket with the server address 
    if ( bind(udp_server_info.sockfd, (const struct sockaddr *)&udp_server_info.servaddr,  
            sizeof(udp_server_info.servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
}

int read_udp_dat(void){
    int n; 
    socklen_t len;
    len = sizeof(udp_server_info.cliaddr);  //len is value/resuslt 
    n = recvfrom(udp_server_info.sockfd, (char *)udp_server_info.udp_arr, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &udp_server_info.cliaddr, 
                &len);
    // add null terminator at the end. 
    udp_server_info.udp_arr[n] = '\0';
    return len;
}

_MessageData_MessageType unpack_information(int len){
	if(len >= 16){
		// Message Decoding. 
		MessageData latest_message_data;
		//latest_message_data.message_type = 2;
		
		{
			uint8_t message_raw_dta[16]; 
			for(uint8_t i = 0; i < 16; i++)
				message_raw_dta[i] = udp_server_info.udp_arr[i];
			pb_istream_t msg_in = pb_istream_from_buffer(message_raw_dta, 16);
			pb_decode(&msg_in, MessageData_fields, &latest_message_data);
		}
        return latest_message_data.message_type;
	}
    MessageData latest_message_data; 
    return latest_message_data.message_type; 
}

uint8_t* get_udp_arr_dat(){
    return udp_server_info.udp_arr;
}