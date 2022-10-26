#ifdef _WINDOWS
#	define DLL_CALL __cdecl
#else
#	define DLL_CALL
#endif

#ifdef C_QUEUE_EXPORTS
#	define DLL_EXPORT __declspec(dllexport)
#else
#	define DLL_EXPORT
#endif


#ifdef __cplusplus
#include <cstdint>
using std::uint64_t;
using std::int32_t;
extern "C" {
#else
#include <stdint.h>
#endif
typedef enum {
	kGood = 0, // all right
	kHandlerError, // bad handler
	kOutOfRange // queue is empty
} ErrorCode;
typedef uint64_t QueueHandler;
DLL_EXPORT ErrorCode DLL_CALL CreateQueue(QueueHandler* queue);
DLL_EXPORT ErrorCode DLL_CALL CloneQueue(QueueHandler source, QueueHandler* queue);
DLL_EXPORT ErrorCode DLL_CALL DestroyQueue(QueueHandler queue);
DLL_EXPORT ErrorCode DLL_CALL Pop(QueueHandler queue);
DLL_EXPORT ErrorCode DLL_CALL Push(QueueHandler queue, int32_t value);
DLL_EXPORT ErrorCode DLL_CALL IsEmpty(QueueHandler queue, int32_t* result);
DLL_EXPORT ErrorCode DLL_CALL Top(QueueHandler queue, int32_t* result);
DLL_EXPORT const char* DLL_CALL WhatIs(ErrorCode err);
#ifdef __cplusplus
};
#endif