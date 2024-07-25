#include "../eventloop_posix.h"
#include "mbed.h"
#include "mbed_tcp.h"

UA_StatusCode
UA_EventLoopPOSIX_setNonBlocking(UA_FD sockfd) {
    ((Socket*)sockfd)->set_blocking(false);
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
UA_EventLoopPOSIX_setNoSigPipe(UA_FD sockfd) {
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
UA_EventLoopPOSIX_setReusable(UA_FD sockfd) {
    int optval = 1;
    UA_setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT,
                     (const char *)&optval, sizeof(optval));
    return UA_setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                     (const char *)&optval, sizeof(optval));
}

UA_StatusCode
UA_EventLoopPOSIX_registerFD(UA_EventLoopPOSIX *el, UA_RegisteredFD *rfd) {
    UA_LOCK_ASSERT(&el->elMutex, 1);
    UA_LOG_DEBUG(el->eventLoop.logger, UA_LOGCATEGORY_EVENTLOOP,
                 "Registering fd: %u", (unsigned)rfd->fd);

    /* Realloc */
    UA_RegisteredFD **fds_tmp = (UA_RegisteredFD**)
        UA_realloc(el->fds, sizeof(UA_RegisteredFD*) * (el->fdsSize + 1));
    if(!fds_tmp) {
        return UA_STATUSCODE_BADOUTOFMEMORY;
    }
    el->fds = fds_tmp;

    /* Add to the last entry */
    el->fds[el->fdsSize] = rfd;
    el->fdsSize++;
    return UA_STATUSCODE_GOOD;
}

UA_StatusCode
UA_EventLoopPOSIX_modifyFD(UA_EventLoopPOSIX *el, UA_RegisteredFD *rfd) {
    /* Do nothing, it is enough if the data was changed in the rfd */
    UA_LOCK_ASSERT(&el->elMutex, 1);
    return UA_STATUSCODE_GOOD;
}

void
UA_EventLoopPOSIX_deregisterFD(UA_EventLoopPOSIX *el, UA_RegisteredFD *rfd) {
    UA_LOCK_ASSERT(&el->elMutex, 1);
    UA_LOG_DEBUG(el->eventLoop.logger, UA_LOGCATEGORY_EVENTLOOP,
                 "Unregistering fd: %u", (unsigned)rfd->fd);

    /* Find the entry */
    size_t i = 0;
    for(; i < el->fdsSize; i++) {
        if(el->fds[i] == rfd)
            break;
    }

    /* Not found? */
    if(i == el->fdsSize)
        return;

    if(el->fdsSize > 1) {
        /* Move the last entry in the ith slot and realloc. */
        el->fdsSize--;
        el->fds[i] = el->fds[el->fdsSize];
        UA_RegisteredFD **fds_tmp = (UA_RegisteredFD**)
            UA_realloc(el->fds, sizeof(UA_RegisteredFD*) * el->fdsSize);
        /* if realloc fails the fds are still in a correct state with
         * possibly lost memory, so failing silently here is ok */
        if(fds_tmp)
            el->fds = fds_tmp;
    } else {
        /* Remove the last entry */
        UA_free(el->fds);
        el->fds = NULL;
        el->fdsSize = 0;
    }
}

rtos::EventFlags _events;
#include "../../util/o1heap/o1heap.h"

UA_StatusCode
UA_EventLoopPOSIX_pollFDs(UA_EventLoopPOSIX *el, UA_DateTime listenTimeout) {
    UA_assert(listenTimeout >= 0);
    UA_LOCK_ASSERT(&el->elMutex, 1);


    auto flag = _events.wait_any(0x7fffffff, 10);
    if (flag & 0x80000000) {
        yield();
        return UA_STATUSCODE_GOOD;
    }
    UA_FD ev_sock = flag;

    /* Loop over all registered FD to see if an event arrived. Yes, this is why
     * select is slow for many open sockets. */
    for(size_t i = 0; i < el->fdsSize; i++) {
        UA_RegisteredFD *rfd = el->fds[i];

        if (el->fds[i]->fd != (UA_FD)ev_sock) {
            // TODO: find out why we don't receive the first accepted socket event
            //continue;
        }

        /* The rfd is already registered for removal. Don't process incoming
         * events any longer. */
        if(rfd->dc.callback)
            continue;

        /* Event signaled for the fd? */
        short event = rfd->listenEvents;

        extern rtos::Thread opc_ua_server_thread;
        extern O1HeapInstance * o1heap_ins;

        UA_LOG_DEBUG(
          el->eventLoop.logger,
          UA_LOGCATEGORY_EVENTLOOP,
          "Processing event %u on fd %u (stack: size = %d, free = %d, used = %d) (heap: capacity = %d, allocated = %d, peak_allocated = %d)",
          (unsigned)event,
          (unsigned)rfd->fd,
          opc_ua_server_thread.stack_size(),
          opc_ua_server_thread.free_stack(),
          opc_ua_server_thread.used_stack(),
          o1heapGetDiagnostics(o1heap_ins).capacity,
          o1heapGetDiagnostics(o1heap_ins).allocated,
          o1heapGetDiagnostics(o1heap_ins).peak_allocated);

        /* Call the EventSource callback */
        rfd->eventSourceCB(rfd->es, rfd, event);
    }
    return UA_STATUSCODE_GOOD;
}
