/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2001-2003
 *	Sleepycat Software.  All rights reserved.
 *
 * $Id: ex_repquote.h,v 1.2 2004/03/30 01:23:18 jtownsen Exp $
 */

#ifndef _EX_REPQUOTE_H_
#define	_EX_REPQUOTE_H_

#define	SELF_EID	1

typedef struct {
	char *host;		/* Host name. */
	u_int32_t port;		/* Port on which to connect to this site. */
} repsite_t;

/* Globals */
extern int master_eid;
extern char *myaddr;
extern unsigned short myport;

struct __member;	typedef struct __member member_t;
struct __machtab;	typedef struct __machtab machtab_t;

/* Arguments for the connect_all thread. */
typedef struct {
	DB_ENV *dbenv;
	const char *progname;
	const char *home;
	machtab_t *machtab;
	repsite_t *sites;
	int nsites;
} all_args;

/* Arguments for the connect_loop thread. */
typedef struct {
	DB_ENV *dbenv;
	const char * home;
	const char * progname;
	machtab_t *machtab;
	int port;
} connect_args;

#define	CACHESIZE	(10 * 1024 * 1024)
#define	DATABASE	"quote.db"
#define	MAX_THREADS	25
#define	SLEEPTIME	3

void *connect_all __P((void *args));
void *connect_thread __P((void *args));
int   doclient __P((DB_ENV *, const char *, machtab_t *));
int   domaster __P((DB_ENV *, const char *));
int   get_accepted_socket __P((const char *, int));
int   get_connected_socket
	__P((machtab_t *, const char *, const char *, int, int *, int *));
int   get_next_message __P((int, DBT *, DBT *));
int   listen_socket_init __P((const char *, int));
int   listen_socket_accept __P((machtab_t *, const char *, int, int *));
int   machtab_getinfo __P((machtab_t *, int, u_int32_t *, int *));
int   machtab_init __P((machtab_t **, int, int));
void  machtab_parm __P((machtab_t *, int *, int *, u_int32_t *));
int   machtab_rem __P((machtab_t *, int, int));
int   quote_send __P((DB_ENV *, const DBT *, const DBT *, const DB_LSN *,
    int, u_int32_t));

#ifndef COMPQUIET
#define	COMPQUIET(x,y)	x = (y)
#endif

/* Portability macros for basic threading and networking */
#ifdef _WIN32

#include <windows.h>

extern int getopt(int, char * const *, const char *);

typedef HANDLE thread;
#define	thread_create(thrp, attr, func, arg)				   \
    (((*(thrp) = CreateThread(NULL, 0,					   \
	(LPTHREAD_START_ROUTINE)(func), (arg), 0, NULL)) == NULL) ? -1 : 0)
#define	thread_join(thr, statusp)					   \
    ((WaitForSingleObject((thr), INFINITE) == WAIT_OBJECT_0) &&		   \
    GetExitCodeThread((thr), (LPDWORD)(statusp)) ? 0 : -1)

typedef HANDLE mutex_t;
#define	mutex_init(m, attr)						   \
    (((*(m) = CreateMutex(NULL, FALSE, NULL)) != NULL) ? 0 : -1)
#define	mutex_lock(m)							   \
    ((WaitForSingleObject(*(m), INFINITE) == WAIT_OBJECT_0) ? 0 : -1)
#define	mutex_unlock(m)		(ReleaseMutex(*(m)) ? 0 : -1)
#define	sleep(s)		Sleep(1000 * (s))

#define	readsocket(s, buf, sz)	recv((s), (buf), (sz), 0)
#define	writesocket(s, buf, sz)	send((s), (buf), (sz), 0)
#define	net_errno		WSAGetLastError()

#else /* !_WIN32 */

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

typedef pthread_t thread;
#define	thread_create(thrp, attr, func, arg)				   \
    pthread_create((thrp), (attr), (func), (arg))
#define	thread_join(thr, statusp) pthread_join((thr), (statusp))
#define	closesocket(fd)	close(fd)

typedef pthread_mutex_t mutex_t;
#define	mutex_init(m, attr)	pthread_mutex_init((m), (attr))
#define	mutex_lock(m)		pthread_mutex_lock(m)
#define	mutex_unlock(m)		pthread_mutex_unlock(m)

#define	readsocket(s, buf, sz)	read((s), (buf), (sz))
#define	writesocket(s, buf, sz)	write((s), (buf), (sz))
#define	closesocket(fd)		close(fd)
#define	net_errno		errno

#endif

#endif /* !_EX_REPQUOTE_H_ */
