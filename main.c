#include <stdio.h>
#include "csp_hmac.h"
#include "csp_cipher.h"
#include <time.h>
//#include "csp_xtea.h"

void debug_packet(csp_packet_t* packet) {
	char* msg = (char*) packet;
	int sz = sizeof(csp_packet_t);
	printf("Debugging packet\n");
	printf("Dport: %s\n", msg);

	int j;

	for (j = 0; j < sz; j++) {
		printf("%d: %d\n", j, msg[j]);
	}


}


void set_msg(csp_packet_t* packet, char* msg) {
	strcpy((char*) packet->data, msg);
	packet->length = strlen(msg);
}

main() {
	char* msg = "0123456789011";
	csp_packet_t* packet = malloc(sizeof(csp_packet_t));

	packet->id.dport = 1;
	packet->id.sport = 2;
	set_msg(packet, msg);

	csp_hmac_set_key("bar", 3);
    if (csp_hmac_append(packet) != 0) {
	   printf("Error appending HMAC\n");
    }


	csp_aes_set_key("SomeKey", 2);

    /* Create initialization vector */
    uint32_t nonce = (uint32_t) rand();
    uint32_t iv[2] = {nonce, packet->length};

    /* Encrypt data */
    int ll = csp_encrypt(packet->data, packet->length, (uint8_t*) &iv);
    if (ll < 0) {
    	printf("Encryption failed!\n");
    }
    else {
    	packet->length = ll;
    }

    /* Decrypt data */
    if (csp_decrypt(packet->data, packet->length, (uint8_t*) &iv) != 0) {
    	printf("Decryption failed!\n");
    }
}
