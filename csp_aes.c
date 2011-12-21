/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2011 GomSpace ApS (http://www.gomspace.com)
Copyright (C) 2011 AAUSAT3 Project (http://aausat3.space.aau.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* Simple implementation of XTEA in CTR mode */

#include <stdint.h>
#include <string.h>

/* CSP includes */
#include "minimized.h"
#include "aes/aes.h"

#define CSP_ENABLE_AES	1


#if CSP_ENABLE_AES

#define AES_BLOCKSIZE 	8
#define AES_KEY_LENGTH	16
#define AES_KEY_BITS	128
#define AES_BUFFER_SIZE	1024
#define AES_IV_SIZE		20
#define AES_IV_ACTUAL	8


unsigned char ckey[] =  "thiskeyisverybad"; // It is 128bits though..
AES_KEY encrypt_key;
AES_KEY decrypt_key;


int csp_aes_set_key(char * k, uint32_t keylen) {
	if (AES_set_encrypt_key(ckey, AES_KEY_BITS, &encrypt_key)) {
		return -1;
	}

	if (AES_set_decrypt_key(ckey, AES_KEY_BITS, &decrypt_key)) {
		return -1;
	}

	return 0;
}

int csp_aes_encrypt(unsigned char * plain,  uint32_t len, unsigned char* iv) {
	unsigned char iv2[AES_IV_SIZE];
	unsigned char buffer[AES_BUFFER_SIZE];

	// Construct IV from the byte array passed
	int ii;
	for (ii = 0; ii < AES_IV_SIZE; ii++) {
		iv2[ii] = iv[ii % AES_IV_ACTUAL];
	}

	//AES_cbc_encrypt((unsigned char*) plain, &buffer, rlen, &encrypt_key, iv2, AES_ENCRYPT);
	int num = 0;
	AES_ofb128_encrypt((unsigned char*) plain, &buffer, len, &encrypt_key, iv2, &num);

	// Copy result of encryption and append IV at the end
	memcpy(plain + 0, &buffer, len);
	memcpy(plain + len, &iv2, AES_IV_SIZE);

	// Added IV
	return len + AES_IV_SIZE;
}

int csp_aes_decrypt(uint8_t * cipher, const uint32_t len, unsigned char* iv) {
	unsigned char iv2[AES_IV_SIZE] = {1};
	unsigned char buffer[AES_BUFFER_SIZE];

	//AES_cbc_encrypt((unsigned char*) cipher, buffer, len, &decrypt_key, iv2, AES_DECRYPT);

	// Create IV from the byte array passed
	int ii;
	for (ii = 0; ii < AES_IV_SIZE; ii++) {
		iv2[ii] = iv[ii % AES_IV_ACTUAL];
	}

	int actual_length = len - AES_IV_SIZE;

	int num = 0;
	AES_ofb128_encrypt((unsigned char*) cipher, buffer, actual_length, &encrypt_key, iv2, &num);

	memcpy(cipher, buffer, actual_length);
	return 0;
}

#endif // CSP_ENABLE_AES
