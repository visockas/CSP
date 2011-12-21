#ifndef CSP_PADDING_BYTES
#define CSP_PADDING_BYTES 8
#endif

#define CSP_ENABLE_HMAC					1

#define _CSP_BIG_ENDIAN					1
#define CSP_ID_PROTOCOL_SIZE            3
#define CSP_ID_PRIO_SIZE                3
#define CSP_ID_HOST_SIZE                4
#define CSP_ID_PORT_SIZE                5
#define CSP_ID_FLAGS_SIZE               8


typedef union {
	int ext;
	struct __attribute__((__packed__)) {
//#if defined(_CSP_BIG_ENDIAN_) && !defined(_CSP_LITTLE_ENDIAN_)
		unsigned int protocol : CSP_ID_PROTOCOL_SIZE;
		unsigned int pri : CSP_ID_PRIO_SIZE;
		unsigned int src : CSP_ID_HOST_SIZE;
		unsigned int dst : CSP_ID_HOST_SIZE;
		unsigned int dport : CSP_ID_PORT_SIZE;
		unsigned int sport : CSP_ID_PORT_SIZE;
		unsigned int flags : CSP_ID_FLAGS_SIZE;

/*
#elif defined(_CSP_LITTLE_ENDIAN_) && !defined(_CSP_BIG_ENDIAN_)
		unsigned int flags : CSP_ID_FLAGS_SIZE;
		unsigned int sport : CSP_ID_PORT_SIZE;
		unsigned int dport : CSP_ID_PORT_SIZE;
		unsigned int dst : CSP_ID_HOST_SIZE;
		unsigned int src : CSP_ID_HOST_SIZE;
		unsigned int pri : CSP_ID_PRIO_SIZE;
		unsigned int protocol : CSP_ID_PROTOCOL_SIZE;

#endif
*/
	};
}csp_id_t;


typedef struct __attribute__((__packed__)) {
	uint8_t padding[CSP_PADDING_BYTES];   	// Interface dependent padding
	uint16_t length;			// Length field must be just before CSP ID
	csp_id_t id;				// CSP id must be just before data
	union {
		uint8_t data[0];		// This just points to the rest of the buffer, without a size indication.
		uint16_t data16[0];		// The data 16 and 32 types makes it easy to reference an integer (properly aligned)
		uint32_t data32[0];		// - without the compiler warning about strict aliasing rules.
	};
} csp_packet_t;
