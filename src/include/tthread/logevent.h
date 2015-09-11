#ifndef __TTHREAD_LOG_ENTRY_H__
#define __TTHREAD_LOG_ENTRY_H__

/*
 * @file   tthread/logentry.h
 * @brief  a memory event
 */

#include "visibility.h"

class xthread;

namespace tthread {
#pragma pack(push, 1)

typedef union EventData {
  struct {
    // synchronisation point within on thread
    int id;
  } thunk;
  struct {
    // memory address at which the first page fault was triggered
    const void *address;
  } memory;
  struct {} finish; // no data so far
} Data;

class _PUBLIC_ logevent {
public:

  enum Type {
    INVALID = 0,
    WRITE = 1,
    READ = 2,
    THUNK = 3,
    FINISH = 4
  };

private:

  // how memory was access (read/write)
  char _type;

  // return address, which issued the first page fault on this page
  const void *_returnAddress;

  // process id, which accessed the memory
  int _threadId;

  Data _data;

public:

  logevent(Type type, const void *returnAddress, Data data) :
    _type(type),
    _returnAddress(returnAddress),
    _threadId(0),
    _data(data)
  {}

  inline void setThreadId(int threadId) {
    _threadId = threadId;
  }

  inline const Data& getData() const {
    return _data;
  }

  inline const Type getType() const {
    return (Type)_type;
  }

  inline const void *getReturnAddress() const {
    return _returnAddress;
  }

  inline const int getThreadId() const {
    return _threadId;
  }
};
#pragma pack(pop)
}

#endif /* __TTHREAD_LOG_ENTRY_H__ */
