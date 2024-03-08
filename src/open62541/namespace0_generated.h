/* WARNING: This is a generated file.
 * Any manual changes will be overwritten. */

#ifndef NAMESPACE0_GENERATED_H_
#define NAMESPACE0_GENERATED_H_


#ifdef UA_ENABLE_AMALGAMATION
# include "open62541.h"

/* The following declarations are in the open62541.c file so here's needed when compiling nodesets externally */

# ifndef UA_INTERNAL //this definition is needed to hide this code in the amalgamated .c file

typedef UA_StatusCode (*UA_exchangeEncodeBuffer)(void *handle, UA_Byte **bufPos,
                                                 const UA_Byte **bufEnd);

UA_StatusCode
UA_encodeBinary(const void *src, const UA_DataType *type,
                UA_Byte **bufPos, const UA_Byte **bufEnd,
                UA_exchangeEncodeBuffer exchangeCallback,
                void *exchangeHandle) UA_FUNC_ATTR_WARN_UNUSED_RESULT;

UA_StatusCode
UA_decodeBinary(const UA_ByteString *src, size_t *offset, void *dst,
                const UA_DataType *type, size_t customTypesSize,
                const UA_DataType *customTypes) UA_FUNC_ATTR_WARN_UNUSED_RESULT;

size_t
UA_calcSizeBinary(void *p, const UA_DataType *type);

const UA_DataType *
UA_findDataTypeByBinary(const UA_NodeId *typeId);

# endif // UA_INTERNAL

#else // UA_ENABLE_AMALGAMATION
# include <open62541/server.h>
#endif




_UA_BEGIN_DECLS

extern UA_StatusCode namespace0_generated(UA_Server *server);

_UA_END_DECLS

#endif /* NAMESPACE0_GENERATED_H_ */
