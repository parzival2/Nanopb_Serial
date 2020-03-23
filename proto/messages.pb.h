/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.2-dev */

#ifndef PB_PROTO_MESSAGES_PB_H_INCLUDED
#define PB_PROTO_MESSAGES_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _MessageID {
    MessageID_Message1ID = 0,
    MessageID_Message2ID = 1,
    MessageID_Message3ID = 2
} MessageID;

/* Struct definitions */
typedef struct _Message1 {
    MessageID id;
    int32_t intvalue;
} Message1;

typedef struct _Message2 {
    MessageID id;
    int32_t intvalue;
    char strvalue[50];
} Message2;

typedef struct _Message3 {
    MessageID id;
    bool boolvalue;
} Message3;


/* Helper constants for enums */
#define _MessageID_MIN MessageID_Message1ID
#define _MessageID_MAX MessageID_Message3ID
#define _MessageID_ARRAYSIZE ((MessageID)(MessageID_Message3ID+1))


/* Initializer values for message structs */
#define Message1_init_default                    {_MessageID_MIN, 0}
#define Message2_init_default                    {_MessageID_MIN, 0, ""}
#define Message3_init_default                    {_MessageID_MIN, 0}
#define Message1_init_zero                       {_MessageID_MIN, 0}
#define Message2_init_zero                       {_MessageID_MIN, 0, ""}
#define Message3_init_zero                       {_MessageID_MIN, 0}

/* Field tags (for use in manual encoding/decoding) */
#define Message1_id_tag                          1
#define Message1_intvalue_tag                    2
#define Message2_id_tag                          1
#define Message2_intvalue_tag                    2
#define Message2_strvalue_tag                    3
#define Message3_id_tag                          1
#define Message3_boolvalue_tag                   2

/* Struct field encoding specification for nanopb */
#define Message1_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    id,                1) \
X(a, STATIC,   SINGULAR, INT32,    intvalue,          2)
#define Message1_CALLBACK NULL
#define Message1_DEFAULT NULL

#define Message2_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    id,                1) \
X(a, STATIC,   SINGULAR, INT32,    intvalue,          2) \
X(a, STATIC,   SINGULAR, STRING,   strvalue,          3)
#define Message2_CALLBACK NULL
#define Message2_DEFAULT NULL

#define Message3_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    id,                1) \
X(a, STATIC,   SINGULAR, BOOL,     boolvalue,         2)
#define Message3_CALLBACK NULL
#define Message3_DEFAULT NULL

extern const pb_msgdesc_t Message1_msg;
extern const pb_msgdesc_t Message2_msg;
extern const pb_msgdesc_t Message3_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define Message1_fields &Message1_msg
#define Message2_fields &Message2_msg
#define Message3_fields &Message3_msg

/* Maximum encoded size of messages (where known) */
#define Message1_size                            13
#define Message2_size                            64
#define Message3_size                            4

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif