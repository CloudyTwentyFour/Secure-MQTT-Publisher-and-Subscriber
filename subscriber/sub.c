#include "header.h"

MOSQ *sub;
char will[] = "bye from subscriber";
char user[] = "bjnpr8";
char pw[] = "trail@123";
char cert[] = "/home/user/misc/mqtt/keys/client.crt";
char key[] = "/home/user/misc/mqtt/keys/client.key";

void on_connect(struct mosquitto *sub, void *ptr, int rc)
{
	if(rc != 0)
	{
		printf("on_connect: %s\n",mosquitto_connack_string(rc));
		clean_mosquitto(sub);
		exit(1);
	}
}

void on_subscribe(struct mosquitto *pub, void *ptr, int mid, int qoscnt, const int *qosptr)
{
	printf("on_subscribe %d:%d\n", mid,qoscnt);
}

void on_message(struct mosquitto *sub, void *ptr, const struct mosquitto_message *msg)
{
	printf("Topic %s, QOS %d, Message %s\n",msg->topic, msg->qos, (char *)msg->payload);
}

int main(void)
{
	int ret;

	sub = createMosquitto(NULL);
	if(sub != NULL)
	{
		mosquitto_connect_callback_set(sub, on_connect);
		ret = mosquitto_will_set(sub, "sunil/t1", strlen(will), will, 2, true);
                printf("will setting %d\n",ret);

		ret = auth_and_encrypt(sub, user, pw, cert, key);
		ret = mosquitto_connect(sub, IP_ADDR, PORT, 60);
		if(ret == MOSQ_ERR_SUCCESS)
		{
			mosquitto_message_callback_set(sub, on_message);
			mosquitto_subscribe(sub, NULL, "sunil/t1", 2);
			mosquitto_loop_forever(sub, -1, 1);
		}
		else
		{
			printf("connect failure %d\n",ret);
			goto ret;
		}
	}
ret:
	clean_mosquitto(sub);
	return 0;

}


