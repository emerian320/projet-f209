#include "client.h"

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <string>


#include "socketlib.h"

//using namespace std;

Client::Client() {}

void Client::run(string pseudo, string ip, int port) {
  //Le client se connecte au serveur, et créé un thread pour gérer la reception de messages.
  this->socket = this->handshake(ip, port, pseudo);
  pthread_t tid;
  pthread_create(&tid, nullptr, Client::manageInputs, this);
  this->manageSocketTraffic();
  close(this->socket);
}

void *Client::manageInputs(void *instance) {
  //Version void* de manage input pour pouvoir creer le thread
  Client *c = (Client *)instance;
  c->manageInputs();
  return nullptr;
}

void Client::manageInputs() {
  // Le client peut ecrire et envoyer ses messages
  char buffer[1024];
  write(STDOUT_FILENO, ">> ", 3);
  while (fgets(buffer, 1024, stdin) != NULL) {
    buffer[strlen(buffer) - 1] = '\0';
    message_t msg = {.timestamp = time(NULL), .message = string(buffer)};
    if (ssend(this->socket, &msg) <= 0) {
      exit(0);
    }
    write(STDOUT_FILENO, ">> ", 3);
    printf("\033[A\33[2KT\r");
  }
  close(this->socket);
  exit(0);
}

void Client::manageSocketTraffic() {
  //Reception des messages via le serveur
  while (true) {
    message_t msg;
    size_t nbytes = receive(this->socket, &msg);
    if (nbytes <= 0) {
      exit(0);
    }
    printf("%s\n", msg.message.c_str());
  }
}

int Client::handshake(string ip, int port, string pseudo) {
  int socket = checked(create_socket());
  if (connect_socket(socket, "127.0.0.1", port) < 0) {
    exit(1);
  }
  // Send username
  if (safe_write(socket, pseudo.c_str(), pseudo.length()) <= 0) {
    exit(1);
  }
  // Receive acknowledgement
  int ack;
  if (safe_read(socket, &ack, sizeof(int)) <= 0) {
    exit(1);
  }
  if (ack != 0) {
    std::cout<<"Connection rejected by server\n";
    exit(1);
  }
  return socket;
}

int main(int argc, char const *argv[]) {
 std::string inputFile = DatabaseHandler::askFile();
 if (inputFile=="") exit(0);
 DatabaseHandler dbh(inputFile);

  //if (argc < 2) {
  //  fprintf(stderr, "Utilisation: ./client <port> [<ip>]\n");
  //  exit(0);
  //}
  const int port = atoi(argv[1]);
  if (port < 1024) {
    fprintf(stderr, "Le port doit être supérieur à 1023.\n");
    exit(0);
  }
  const std::string ip = "127.0.0.1";
  //if (argc > 2) {
  //  ip = argv[2];
  //}
  Client client = Client();
  std::string pseudo = dbh.getPlayerName();
  client.run(pseudo, ip.c_str(), port);
  return 0;
}