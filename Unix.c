/* voc  1.0  [2013/09/23] xtspkaPS */
#include "SYSTEM.h"

typedef
	struct Unix_Dirent {
		LONGINT ino, off;
		INTEGER reclen;
		CHAR name[256];
	} Unix_Dirent;

typedef
	SET Unix_FdSet[8];

typedef
	struct Unix_Hostent *Unix_HostEntry;

typedef
	struct Unix_Hostent {
		LONGINT name, aliases, addrtype, length, addrlist;
	} Unix_Hostent;

typedef
	struct Unix_Iovec {
		LONGINT base, len;
	} Unix_Iovec;

typedef
	struct Unix_Timeval {
		LONGINT sec, usec;
	} Unix_Timeval;

typedef
	struct Unix_Itimerval {
		Unix_Timeval interval, value;
	} Unix_Itimerval;

typedef
	struct Unix_sigsett {
		LONGINT val[16];
	} Unix_sigsett;

typedef
	struct Unix_JmpBuf {
		LONGINT bx, si, di, bp, sp, pc, ki, ku;
		INTEGER maskWasSaved;
		Unix_sigsett savedMask;
	} Unix_JmpBuf;

typedef
	CHAR *Unix_Name;

typedef
	struct Unix_Pollfd {
		LONGINT fd;
		INTEGER events, revents;
	} Unix_Pollfd;

typedef
	struct Unix_Rusage {
		Unix_Timeval utime, stime;
		LONGINT maxrss, ixrss, idrss, isrss, minflt, majflt, nswap, inblock, oublock, msgsnd, msgrcv, nsignals, nvcsw, nivcsw;
	} Unix_Rusage;

typedef
	struct Unix_SigContext {
		char _prvt0[1];
	} Unix_SigContext;

typedef
	Unix_SigContext *Unix_SigCtxPtr;

typedef
	void (*Unix_SignalHandler)(LONGINT, LONGINT, Unix_SigCtxPtr);

typedef
	struct Unix_Sockaddr {
		INTEGER family, port;
		LONGINT internetAddr;
		CHAR pad[8];
	} Unix_Sockaddr;

typedef
	LONGINT Unix_SocketPair[2];

typedef
	struct Unix_Status {
		LONGINT dev, ino, nlink;
		INTEGER mode, uid, gid, pad0;
		LONGINT rdev, size, blksize, blocks, atime, atimences, mtime, mtimensec, ctime, ctimensec, unused0, unused1, unused2;
	} Unix_Status;

typedef
	struct Unix_Timezone {
		INTEGER minuteswest, dsttime;
	} Unix_Timezone;



export LONGINT *Unix_sigsett__typ;
export LONGINT *Unix_JmpBuf__typ;
export LONGINT *Unix_Status__typ;
export LONGINT *Unix_Timeval__typ;
export LONGINT *Unix_Timezone__typ;
export LONGINT *Unix_Itimerval__typ;
export LONGINT *Unix_SigContext__typ;
export LONGINT *Unix_Dirent__typ;
export LONGINT *Unix_Rusage__typ;
export LONGINT *Unix_Iovec__typ;
export LONGINT *Unix_Pollfd__typ;
export LONGINT *Unix_Sockaddr__typ;
export LONGINT *Unix_Hostent__typ;

export LONGINT Unix_Fstat (LONGINT fd, Unix_Status *statbuf, LONGINT *statbuf__typ);
export LONGINT Unix_Stat (CHAR *name, LONGINT name__len, Unix_Status *statbuf, LONGINT *statbuf__typ);
export INTEGER Unix_System (CHAR *cmd, LONGINT cmd__len);
export LONGINT Unix_errno (void);
export void Unix_system (CHAR *cmd, LONGINT cmd__len);

#define Unix_Accept(socket, addr, addr__typ, addrlen)	accept(socket, addr, addrlen)
#define Unix_Bind(socket, name, namelen)	bind(socket, &(name), namelen)
#define Unix_Chdir(path, path__len)	chdir(path)
#define Unix_Chmod(path, path__len, mode)	chmod(path, mode)
#define Unix_Close(fd)	close(fd)
#define Unix_Connect(socket, name, namelen)	connect(socket, &(name), namelen)
#define Unix_Dup(fd)	dup(fd)
#define Unix_Dup2(fd1, fd2)	dup(fd1, fd2)
#define Unix_Exit(n)	exit(n)
#define Unix_Fchmod(fd, mode)	fchmod(fd, mode)
#define Unix_Fcntl(fd, cmd, arg)	fcntl(fd, cmd, arg)
#define Unix_Flock(fd, operation)	flock(fd, operation)
#define Unix_Fork()	fork()
#define Unix_Fsync(fd)	fsync(fd)
#define Unix_Ftruncate(fd, length)	ftruncate(fd, length)
#define Unix_Getegid()	getegid()
#define Unix_Geteuid()	geteuid()
#define Unix_Getgid()	getgid()
#define Unix_Gethostbyname(name, name__len)	(Unix_HostEntry)gethostbyname(name)
#define Unix_Gethostname(name, name__len)	gethostname(name, name__len)
#define Unix_Getpid()	getpid()
#define Unix_Getsockname(socket, name, name__typ, namelen)	getsockname(socket, name, namelen)
#define Unix_Gettimeofday(tv, tv__typ, tz, tz__typ)	gettimeofday(tv, tz)
#define Unix_Getuid()	getuid()
#define Unix_Ioctl(fd, request, arg)	ioctl(fd, request, arg)
#define Unix_Kill(pid, sig)	kill(pid, sig)
#define Unix_Listen(socket, backlog)	listen(socket, backlog)
#define Unix_Lseek(fd, offset, origin)	lseek(fd, offset, origin)
#define Unix_Nanosleep(req, req__typ, rem, rem__typ)	nanosleep(req, rem)
#define Unix_Open(name, name__len, flag, mode)	open(name, flag, mode)
#define Unix_Pipe(fds)	pipe(fds)
#define Unix_Read(fd, buf, nbyte)	read(fd, buf, nbyte)
#define Unix_ReadBlk(fd, buf, buf__len)	read(fd, buf, buf__len)
#define Unix_Readblk(fd, buf, buf__len, len)	read(fd, buf, len)
#define Unix_Recv(socket, bufadr, buflen, flags)	recv(socket, bufadr, buflen, flags)
#define Unix_Rename(old, old__len, new, new__len)	rename(old, new)
#define Unix_Select(width, readfds, writefds, exceptfds, timeout, timeout__typ)	select(width, readfds, writefds, exceptfds, timeout)
#define Unix_Send(socket, bufadr, buflen, flags)	send(socket, bufadr, buflen, flags)
#define Unix_Sigsetmask(mask)	sigsetmask(mask)
#define Unix_Sleep(ms)	sleep(ms)
#define Unix_Socket(af, type, protocol)	socket(af, type, protocol)
#define Unix_Unlink(name, name__len)	unlink(name)
#define Unix_Wait(status)	wait(status)
#define Unix_Write(fd, buf, nbyte)	write(fd, buf, nbyte)
#define Unix_WriteBlk(fd, buf, buf__len)	write(fd, buf, buf__len)
#define Unix_err()	errno
#define Unix_fstat(fd, statbuf, statbuf__typ)	fstat(fd, (struct stat*)statbuf)
#include <errno.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define Unix_stat(name, name__len, statbuf, statbuf__typ)	stat((const char*)name, (struct stat*)statbuf)
#define Unix_sys(str, str__len)	system(str)

LONGINT Unix_errno (void)
{
	return Unix_err();
}

LONGINT Unix_Stat (CHAR *name, LONGINT name__len, Unix_Status *statbuf, LONGINT *statbuf__typ)
{
	LONGINT res;
	__DUP(name, name__len, CHAR);
	res = Unix_stat(name, name__len, &*statbuf, statbuf__typ);
	__DEL(name);
	return res;
}

LONGINT Unix_Fstat (LONGINT fd, Unix_Status *statbuf, LONGINT *statbuf__typ)
{
	LONGINT res;
	res = Unix_fstat(fd, &*statbuf, statbuf__typ);
	return res;
}

void Unix_system (CHAR *cmd, LONGINT cmd__len)
{
	INTEGER r;
	__DUP(cmd, cmd__len, CHAR);
	r = Unix_sys(cmd, cmd__len);
	__DEL(cmd);
}

INTEGER Unix_System (CHAR *cmd, LONGINT cmd__len)
{
	INTEGER r;
	__DUP(cmd, cmd__len, CHAR);
	r = Unix_sys(cmd, cmd__len);
	__DEL(cmd);
	return r;
}

__TDESC(Unix_sigsett, 1, 0) = {__TDFLDS("sigsett", 128), {-8}};
__TDESC(Unix_JmpBuf, 1, 0) = {__TDFLDS("JmpBuf", 200), {-8}};
__TDESC(Unix_Status, 1, 0) = {__TDFLDS("Status", 144), {-8}};
__TDESC(Unix_Timeval, 1, 0) = {__TDFLDS("Timeval", 16), {-8}};
__TDESC(Unix_Timezone, 1, 0) = {__TDFLDS("Timezone", 8), {-8}};
__TDESC(Unix_Itimerval, 1, 0) = {__TDFLDS("Itimerval", 32), {-8}};
__TDESC(Unix_SigContext, 1, 0) = {__TDFLDS("SigContext", 1), {-8}};
__TDESC(Unix_Dirent, 1, 0) = {__TDFLDS("Dirent", 280), {-8}};
__TDESC(Unix_Rusage, 1, 0) = {__TDFLDS("Rusage", 144), {-8}};
__TDESC(Unix_Iovec, 1, 0) = {__TDFLDS("Iovec", 16), {-8}};
__TDESC(Unix_Pollfd, 1, 0) = {__TDFLDS("Pollfd", 16), {-8}};
__TDESC(Unix_Sockaddr, 1, 0) = {__TDFLDS("Sockaddr", 24), {-8}};
__TDESC(Unix_Hostent, 1, 0) = {__TDFLDS("Hostent", 40), {-8}};

export void *Unix__init(void)
{
	__DEFMOD;
	__REGMOD("Unix", 0);
	__INITYP(Unix_sigsett, Unix_sigsett, 0);
	__INITYP(Unix_JmpBuf, Unix_JmpBuf, 0);
	__INITYP(Unix_Status, Unix_Status, 0);
	__INITYP(Unix_Timeval, Unix_Timeval, 0);
	__INITYP(Unix_Timezone, Unix_Timezone, 0);
	__INITYP(Unix_Itimerval, Unix_Itimerval, 0);
	__INITYP(Unix_SigContext, Unix_SigContext, 0);
	__INITYP(Unix_Dirent, Unix_Dirent, 0);
	__INITYP(Unix_Rusage, Unix_Rusage, 0);
	__INITYP(Unix_Iovec, Unix_Iovec, 0);
	__INITYP(Unix_Pollfd, Unix_Pollfd, 0);
	__INITYP(Unix_Sockaddr, Unix_Sockaddr, 0);
	__INITYP(Unix_Hostent, Unix_Hostent, 0);
/* BEGIN */
	__ENDMOD;
}
