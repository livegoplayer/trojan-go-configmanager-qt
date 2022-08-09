#include "systemproxymanager.h"

#include <QString>
#if defined (Q_OS_WIN)
#include <tchar.h>
#include <Wininet.h>
#include <ras.h>
#include <raserror.h>
#include <array>
#include <stdio.h>
#include <regex>
#endif


// copy from trojan-qt5
SystemProxyManager::SystemProxyManager()
{
    this->ReSetProxy();
}

int SystemProxyManager::SetProxy(QString local_addr, int local_port) {
#if defined (Q_OS_WIN)
    return this->SetWindowsProxy(local_addr, local_port);
#else
return 0;
#endif
}

int SystemProxyManager::ReSetProxy() {
#if defined (Q_OS_WIN)
    return this->ReSetWindowsProxy();
#else
    return 0;
#endif
}

/****************************************************************************************** 以下是windows代码 ****************************************************************************/
#if defined (Q_OS_WIN)

// 目前永远是全局模式todo 实现mac和linux相关代理设置
int SystemProxyManager::SetWindowsProxy(QString local_addr, int local_port) {
    QString server = local_addr + ":" + QString::number(local_port);
    LPTSTR serverString = (LPTSTR) server.utf16();
    int status = setProxy(1, serverString);
    return status;
}

int SystemProxyManager::ReSetWindowsProxy() {
    int status = setProxy(0, NULL);
    return status;
}


enum RET_ERRORS
{
    RET_NO_ERROR = 0,
    INVALID_FORMAT = 1,
    NO_PERMISSION = 2,
    SYSCALL_FAILED = 3,
    NO_MEMORY = 4,
    INVAILD_OPTION_COUNT = 5,
};

void SystemProxyManager::reportWindowsError(LPCTSTR action)
{
    LPTSTR pErrMsg = NULL;
    DWORD errCode = GetLastError();
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                                FORMAT_MESSAGE_FROM_SYSTEM |
                                                FORMAT_MESSAGE_ARGUMENT_ARRAY,
                                                NULL,
                                                errCode,
                                                LANG_NEUTRAL,
                                                (LPTSTR)&pErrMsg,
                                                0,
                                                NULL);
    _ftprintf(stdin, _T("Error %s: %lu %s\n"), action, errCode, pErrMsg);
}

void SystemProxyManager::reportError(LPCTSTR action)
{
    _ftprintf(stderr, _T("Error %s\n"), action);
}

void SystemProxyManager::do_initialize(INTERNET_PER_CONN_OPTION_LIST* options, int option_count)
{
    if (option_count < 1)
    {
        exit(INVAILD_OPTION_COUNT);
    }

    DWORD dwBufferSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
    options->dwSize = dwBufferSize;

    options->dwOptionCount = option_count;
    options->dwOptionError = 0;

    options->pOptions = (INTERNET_PER_CONN_OPTION*)calloc(option_count, sizeof(INTERNET_PER_CONN_OPTION));

    if (!options->pOptions)
    {
        exit(NO_MEMORY);
    }

    options->pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
}

int SystemProxyManager::apply_connect(INTERNET_PER_CONN_OPTION_LIST* options, LPTSTR conn)
{
    options->pszConnection = conn;

    BOOL result = InternetSetOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, options, sizeof(INTERNET_PER_CONN_OPTION_LIST));
    if (!result)
    {
        reportWindowsError(_T("setting options"));
        return SYSCALL_FAILED;
    }

    result = InternetSetOption(NULL, INTERNET_OPTION_PROXY_SETTINGS_CHANGED, NULL, 0);
    if (!result)
    {
        reportWindowsError(_T("propagating changes"));
        return SYSCALL_FAILED;
    }

    result = InternetSetOption(NULL, INTERNET_OPTION_REFRESH, NULL, 0);
    if (!result)
    {
        reportWindowsError(_T("refreshing"));
        return SYSCALL_FAILED;
    }

    return RET_NO_ERROR;
}

int SystemProxyManager::apply(INTERNET_PER_CONN_OPTION_LIST* options)
{
    DWORD dwCb = 0;
    DWORD dwRet;
    DWORD dwEntries = 0;

    dwRet = RasEnumEntries(NULL, NULL, NULL, &dwCb, &dwEntries);

    if (dwRet == ERROR_BUFFER_TOO_SMALL)
    {
        LPRASENTRYNAME lpRasEntryName = (LPRASENTRYNAME)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwCb);

        if (lpRasEntryName == NULL)
        {
            reportError(_T("HeapAlloc"));
            return NO_MEMORY;
        }

        for (DWORD i = 0; i < dwEntries; i++)
        {
            lpRasEntryName[i].dwSize = sizeof(RASENTRYNAME);
        }

        dwRet = RasEnumEntries(NULL, NULL, lpRasEntryName, &dwCb, &dwEntries);

        int ret;

        if (ERROR_SUCCESS != dwRet)
        {
            _ftprintf(stderr, _T("Error RasEnumEntries: %d\n"), dwRet);

            ret = SYSCALL_FAILED;
        }
        else
        {
            // First set default connection.
            ret = apply_connect(options, NULL);

            for (DWORD i = 0; i < dwEntries && ret == RET_NO_ERROR; i++)
            {
                ret = apply_connect(options, lpRasEntryName[i].szEntryName);
            }
        }

        HeapFree(GetProcessHeap(), 0, lpRasEntryName);

        return ret;
    }

    if (dwEntries >= 1)
    {
        reportError(_T("acquire buffer size"));
        return SYSCALL_FAILED;
    }

    // No ras entry, set default only.
    return apply_connect(options, NULL);
}


/**
 * Set the server proxy in Windows.
 *
 * @param method 0: off 1: global 2: pac
 * @param server a LPTSTR value which contain the server address
 */
int SystemProxyManager::setProxy(int method, LPTSTR server)
{
    INTERNET_PER_CONN_OPTION_LIST options;
    if (method == 0) {
        this->do_initialize(&options, 1);

        options.pOptions[0].Value.dwValue = PROXY_TYPE_AUTO_DETECT | PROXY_TYPE_DIRECT;

    } else if (method == 1) {

        do_initialize(&options, 3);

        options.pOptions[0].Value.dwValue = PROXY_TYPE_PROXY;

        options.pOptions[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
        options.pOptions[1].Value.pszValue = server;

        options.pOptions[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
        options.pOptions[2].Value.pszValue = _T("localhost;127.*;10.*;172.16.*;172.17.*;172.18.*;172.19.*;172.20.*;172.21.*;172.22.*;172.23.*;172.24.*;172.25.*;172.26.*;172.27.*;172.28.*;172.29.*;172.30.*;172.31.*;192.168.*");

    } else if (method == 2) {
        do_initialize(&options, 2);

        options.pOptions[0].Value.dwValue = PROXY_TYPE_AUTO_PROXY_URL | PROXY_TYPE_DIRECT;

        options.pOptions[1].dwOption = INTERNET_PER_CONN_AUTOCONFIG_URL;
        options.pOptions[1].Value.pszValue = server;
    }

    int ret = apply(&options);

    free(options.pOptions);

    return ret;
}
#endif

