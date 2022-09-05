#include "header.h"

MOSQ *pub;
char message[] = "publihsed message from publisher";
char will[] = "bye from publisher";
char user[] = "bjnpr7";
char passwd[] = "sunil@24";
char cert[] = "/home/user/misc/mqtt/keys/client.crt";
char key[] = "/home/user/misc/mqtt/keys/client.key";

void on_connect(struct mosquitto *pub, void *ptr, int rc)
{
	printf("on connect %d\n",rc);
        if(rc != 0)
        {
                printf("Disconnected due to bad reason %s\n",mosquitto_connack_string(rc));
                mosquitto_disconnect(pub);
        }


}
void on_publish(struct mosquitto *pub, void *ptr, int mid)
{
	printf("publihsed a message %d\n",mid);
}

int main(void)
{
	int ret;
	pub = createMosquitto(NULL);
	if(pub != NULL)
	{
		mosquitto_connect_callback_set(pub, on_connect);
		mosquitto_publish_callback_set(pub, on_publish);
		ret = mosquitto_will_set(pub, "sunil/t1", strlen(will), will, 2, true);
		printf("will setting %d\n",ret);

		ret = auth_and_encrypt(pub, user, passwd, cert, key);
		
		ret = mosquitto_connect(pub, IP_ADDR, PORT, 60);
		if(ret == MOSQ_ERR_SUCCESS)
		{
			if(mosquitto_loop_start(pub) != MOSQ_ERR_SUCCESS)
			{
				printf("loop start\n");
				goto ret;
			}
			else
			{
				while(1)
				{
					mosquitto_publish(pub, NULL, "sunil/t1", strlen(message), message, 2, false);
					sleep(1);
				}

			}
		}
		else
		{
			printf("connect failure %d\n",ret);
			goto ret;
		}
	}
ret:
	clean_mosquitto(pub);
	return 0;

}
