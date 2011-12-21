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

/* Chiper wrapper (either AES or XTEA) */



#include "csp_aes.h"
#include "csp_xtea.h"

//#define CSP_CHIPER_XTEA 	1
#define CSP_CHIPER_AES		1



// XTEA chiper implementation
#ifdef CSP_CHIPER_XTEA

int csp_encrypt(uint8_t* plain, const uint32_t len, uint8_t * buffer) {
	uint32_t iv[2];
	iv[0] = (uint32_t) *buffer;
	iv[1] = (uint32_t) *(buffer + 4);
	return csp_xtea_encrypt(plain, len, iv);
}

int csp_decrypt(uint8_t * cipher, const uint32_t len, uint8_t * buffer) {
	uint32_t iv[2];
	iv[0] = (uint32_t) *buffer;
	iv[1] = (uint32_t) *(buffer + 4);
	return csp_xtea_decrypt(cipher, len, iv);
}
#endif

// AES Chiper implementation
#ifdef CSP_CHIPER_AES

int csp_encrypt(unsigned char * plain, const uint32_t len, uint8_t * buffer) {
	return csp_aes_encrypt(plain, len, (unsigned char*) buffer);
}

int csp_decrypt(unsigned char * cipher, const uint32_t len, uint8_t * buffer) {
	return csp_aes_decrypt(cipher, len, (unsigned char*) buffer);

}
#endif


