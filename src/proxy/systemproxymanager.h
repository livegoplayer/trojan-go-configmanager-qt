#ifndef SYSTEMPROXYMANAGER_H
#define SYSTEMPROXYMANAGER_H
#include <QString>

#if defined (Q_OS_WIN)
#include <Windows.h>
#include <Wininet.h>

#include <tchar.h>
#include <ras.h>
#include <raserror.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <ras.h>
#include <raserror.h>
#endif

class SystemProxyManager
{
public:
    SystemProxyManager();

    int SetProxy(QString local_addr, int local_port);
    int ReSetProxy();
private:
#if defined (Q_OS_WIN)

    void reportWindowsError(LPCTSTR action);
    void reportError(LPCTSTR action);
    void do_initialize(INTERNET_PER_CONN_OPTION_LIST *options, int option_count);
    int apply_connect(INTERNET_PER_CONN_OPTION_LIST *options, LPTSTR conn);
    int apply(INTERNET_PER_CONN_OPTION_LIST *options);
    int setProxy(int method, LPTSTR server);
    int SetWindowsProxy(QString local_addr, int local_port);
    int ReSetWindowsProxy();
#endif
};

#endif // SYSTEMPROXYMANAGER_H
