#include "header.h"

void clean_mosquitto(MOSQ *ptr)
{
	mosquitto_disconnect(ptr);
	mosquitto_destroy(ptr);
	mosquitto_lib_cleanup();
}

MOSQ *createMosquitto(char *id)
{
	MOSQ *ptr = NULL;
	mosquitto_lib_init();

	ptr = mosquitto_new(id, true, NULL);
	if(ptr == NULL)
	{
		printf("mosquitto session creation failed\n");
	}
	return ptr;
}

int auth_and_encrypt(MOSQ *ptr, char *user, char *pw, char *cert, char *key)
{
	int ret = -1;
	if(user != NULL && pw != NULL)
	{
		ret = mosquitto_username_pw_set(ptr, user, pw);
		if(ret != MOSQ_ERR_SUCCESS)
		{
			printf("Invalid User and Password %d\n",ret);
			clean_mosquitto(ptr);
			exit(1);
		}
		else
		{
			printf("Username : %s\n Password : %s\nSet successfully\n",user, pw);
			ret = mosquitto_tls_set(ptr, CAFILE, NULL, cert, key, NULL);
			if(ret != MOSQ_ERR_SUCCESS)
			{
				printf("Error in Setting TLS parameters %d\ncacert:%s\ncert:%s\nkey:%s\n",ret,CAFILE,cert,key);
				clean_mosquitto(ptr);
				exit(1);
			}
			else
			{
				printf("TLS keys set\n");
				ret = mosquitto_tls_opts_set(ptr, SSL_VERIFY_PEER, "tlsv1.2", NULL);
				if(ret != MOSQ_ERR_SUCCESS)
				{
					printf("Error in setting TLS version details %d\n",ret);
					clean_mosquitto(ptr);
					exit(1);
				}
				else
				{
					printf("TLS version set\n");
					mosquitto_tls_insecure_set(ptr, true);
				}
			}
		}
	}
	else
	{
		printf("NULL user and password sent\n");
	}
	return ret;
}

