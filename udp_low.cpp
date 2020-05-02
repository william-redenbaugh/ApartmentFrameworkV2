#include "udp_low.hpp"

#define BUFFER_SIZE 32768
#define MAXLINE 32768

// Address handler that we use to manage our ports. 
struct sockaddr_in server_address; 
struct sockaddr_in client_address; 

// Socket ID Handlers
int server_socket_fd = 0;

/*
Function: udp_server_socket_open(uint16_t port) 
Description: Allows us to setup/host a udp server with a specified port. 
Parameters: uint16_t port(port that we want to use for our server)
Returns: none
*/
void udp_server_socket_open(uint16_t port){
    server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_socket_fd < 0){
        std::cout << "An error has been triggered during setup of udp server socket\n";
    }
    // Clearing out the Struct. 
    bzero(&server_address, sizeof(server_address)); 
    bzero(&client_address, sizeof(client_address)); 
    
    // Set to IPv4.
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY; 
    server_address.sin_port = htons(port);
    
    // Bind the socket with the server address. 
    bind(server_socket_fd, (struct sockaddr*) &server_address, sizeof(server_address));
}

/*
Function: udp_server_receive_blocking(uint8_t *array)
Description: allows to check data we received from the UDP clients.  
Parameters: uint8_t *array
Returns: none
*/
uint16_t udp_server_receive_blocking(uint8_t *array){
    socklen_t len = 0;     
    uint16_t n = recvfrom(server_socket_fd, (char*)array, MAXLINE, MSG_WAITALL, (struct sockaddr*)&client_address, &len);
    return n;
}

/*
Function: 
Description: 
Parameters: 
Return: 
*/
void udp_server_send(uint16_t packet_size, uint8_t *array){
    sendto(server_socket_fd, array, packet_size, 0, (struct sockaddr*) &client_address, sizeof(client_address));
}

void udp_server_sendto(uint16_t packet_size, uint8_t* array, struct sockaddr_in *rec_sock){
    sendto(server_socket_fd, array, packet_size, 0, (struct sockaddr*) rec_sock, sizeof(client_address));
}
