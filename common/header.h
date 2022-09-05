#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CAFILE "/home/user/misc/mqtt/keys/ca.crt"
#define CAPATH "/home/user/misc/mqtt/keys"

#define IP_ADDR "localhost"
#define PORT 8883
typedef struct mosquitto MOSQ;

void clean_mosquitto(MOSQ *ptr);
MOSQ *createMosquitto(char *id);
int auth_and_encrypt(MOSQ *ptr, char *user, char *pw, char *cert, char *key);

