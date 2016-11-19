#ifndef _SHA256_H_
#define _SHA256_H_

#ifdef __cplusplus
extern "C" 
{
#endif

#if defined(__LP64__) || defined(__LLP64__)
	#define uint unsigned int
#else
	#define uint unsigned long
#endif

typedef struct {
   unsigned char data[64];
   uint datalen;
   uint bitlen[2];
   uint state[8];
} SHA256_CTX;

void sha256_transform(SHA256_CTX *ctx, unsigned char data[]);
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, unsigned char data[], unsigned int len);
void sha256_final(SHA256_CTX *ctx, unsigned char hash[]);

#ifdef __cplusplus
}
#endif

#endif

