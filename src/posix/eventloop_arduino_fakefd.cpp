/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 *    Copyright 2021 (c) Fraunhofer IOSB (Author: Julius Pfrommer)
 */

#include "eventloop_posix.h"

#if !defined(UA_HAVE_EPOLL)

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

#define sleep __sleep
#include "mbed.h"
#undef sleep

Socket* ev_sock = nullptr;

UA_StatusCode
UA_EventLoopPOSIX_pollFDs(UA_EventLoopPOSIX *el, UA_DateTime listenTimeout) {
    UA_assert(listenTimeout >= 0);
    UA_LOCK_ASSERT(&el->elMutex, 1);
        
    /* Loop over all registered FD to see if an event arrived. Yes, this is why
     * select is slow for many open sockets. */
    for(size_t i = 0; i < el->fdsSize; i++) {
        UA_RegisteredFD *rfd = el->fds[i];

        if (el->fds[i]->fd != (UA_FD)ev_sock) {
            continue;
        }
        ev_sock = nullptr;

        /* The rfd is already registered for removal. Don't process incoming
         * events any longer. */
        if(rfd->dc.callback)
            continue;

        /* Event signaled for the fd? */
        short event = rfd->listenEvents;

        UA_LOG_INFO(el->eventLoop.logger, UA_LOGCATEGORY_EVENTLOOP,
                     "Processing event %u on fd %u", (unsigned)event,
                     (unsigned)rfd->fd);

        /* Call the EventSource callback */
        rfd->eventSourceCB(rfd->es, rfd, event);
    }
    yield();
    return UA_STATUSCODE_GOOD;
}

#endif /* !defined(UA_HAVE_EPOLL) */
