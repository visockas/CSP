
#include "aes.h"
#include "modes.h"

/* Get padded block size if total length is l */
int blocksize(int l) {
	return ((l - 1) / 16 + 1) * 16;
}

/* Pad by adding extra bytes */
char* padded(char* src, int l) {
  int newl = blocksize(l);
  char* temp = (char*) malloc(newl);
  memcpy(temp, src, l);
  return temp;
}


void AES_ofb128_encrypt(const unsigned char *in, unsigned char *out,
	size_t length, const AES_KEY *key,
	unsigned char *ivec, int *num)
{

	int sz = blocksize(length);
	char* pd = padded(in, length);

	memset( out, 0, sz);


	//CRYPTO_ofb128_encrypt(in,out,length,key,ivec,num,(block128_f)AES_encrypt);
	CRYPTO_ofb128_encrypt(pd,out,sz,key,ivec,num,(block128_f)AES_encrypt);
}
