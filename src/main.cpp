#include <stdio.h>
#include <tchar.h>
#include <nan.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#define WINDOWS_TICK 10000000
#define SEC_TO_UNIX_EPOCH 11644473600LL

using namespace Nan;
using namespace v8;
using namespace std;

typedef LONG NTSTATUS;
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define NT_STATUS(x)((NTSTATUS) { x })
#define STATUS_SUCCESS            ((NTSTATUS)0x00000000L)
#define STATUS_NO_MORE_FILES      ((NTSTATUS)0x80000006L)
#define STATUS_INVALID_INFO_CLASS ((NTSTATUS)0xC0000003L)

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _IO_STATUS_BLOCK {
    union {
        NTSTATUS Status;
        PVOID Pointer;
    } DUMMYUNIONNAME;

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef VOID (NTAPI *PIO_APC_ROUTINE) (PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock, ULONG Reserved);

typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation         = 1,
    FileFullDirectoryInformation,   // 2
    FileBothDirectoryInformation,   // 3
    FileBasicInformation,           // 4
    FileStandardInformation,        // 5
    FileInternalInformation,        // 6
    FileEaInformation,              // 7
    FileAccessInformation,          // 8
    FileNameInformation,            // 9
    FileRenameInformation,          // 10
    FileLinkInformation,            // 11
    FileNamesInformation,           // 12
    FileDispositionInformation,     // 13
    FilePositionInformation,        // 14
    FileFullEaInformation,          // 15
    FileModeInformation,            // 16
    FileAlignmentInformation,       // 17
    FileAllInformation,             // 18
    FileAllocationInformation,      // 19
    FileEndOfFileInformation,       // 20
    FileAlternateNameInformation,   // 21
    FileStreamInformation,          // 22
    FilePipeInformation,            // 23
    FilePipeLocalInformation,       // 24
    FilePipeRemoteInformation,      // 25
    FileMailslotQueryInformation,   // 26
    FileMailslotSetInformation,     // 27
    FileCompressionInformation,     // 28
    FileObjectIdInformation,        // 29
    FileCompletionInformation,      // 30
    FileMoveClusterInformation,     // 31
    FileQuotaInformation,           // 32
    FileReparsePointInformation,    // 33
    FileNetworkOpenInformation,     // 34
    FileAttributeTagInformation,    // 35
    FileTrackingInformation,        // 36
    FileIdBothDirectoryInformation, // 37
    FileIdFullDirectoryInformation, // 38
    FileValidDataLengthInformation, // 39
    FileShortNameInformation,       // 40
    FileIoCompletionNotificationInformation, // 41
    FileIoStatusBlockRangeInformation,       // 42
    FileIoPriorityHintInformation,           // 43
    FileSfioReserveInformation,              // 44
    FileSfioVolumeInformation,               // 45
    FileHardLinkInformation,                 // 46
    FileProcessIdsUsingFileInformation,      // 47
    FileNormalizedNameInformation,           // 48
    FileNetworkPhysicalNameInformation,      // 49
    FileIdGlobalTxDirectoryInformation,      // 50
    FileIsRemoteDeviceInformation,           // 51
    FileAttributeCacheInformation,           // 52
    FileNumaNodeInformation,                 // 53
    FileStandardLinkInformation,             // 54
    FileRemoteProtocolInformation,           // 55
    FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;

typedef struct _FILE_ID_FULL_DIR_INFORMATION {
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    LARGE_INTEGER FileId;
    WCHAR FileName[1];
} FILE_ID_FULL_DIR_INFORMATION, *PFILE_ID_FULL_DIR_INFORMATION;

typedef struct _FILE_ID_BOTH_DIR_INFORMATION {
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    ULONG EaSize;
    CCHAR ShortNameLength;
    WCHAR ShortName[12];
    LARGE_INTEGER FileId;
    WCHAR FileName[1];
} FILE_ID_BOTH_DIR_INFORMATION, *PFILE_ID_BOTH_DIR_INFORMATION;

typedef struct _FILE_ID_GLOBAL_TX_DIR_INFORMATION {
    ULONG NextEntryOffset;
    ULONG FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    ULONG FileAttributes;
    ULONG FileNameLength;
    LARGE_INTEGER FileId;
    GUID LockingTransactionId;
    ULONG TxInfoFlags;
    WCHAR FileName[1];
} FILE_ID_GLOBAL_TX_DIR_INFORMATION, *PFILE_ID_GLOBAL_TX_DIR_INFORMATION;

#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_WRITELOCKED         0x00000001
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_TO_TX       0x00000002
#define FILE_ID_GLOBAL_TX_DIR_INFO_FLAG_VISIBLE_OUTSIDE_TX  0x00000004

typedef struct _FILE_OBJECTID_INFORMATION {
    LONGLONG FileReference;
    UCHAR ObjectId[16];
    union {
        struct {
            UCHAR BirthVolumeId[16];
            UCHAR BirthObjectId[16];
            UCHAR DomainId[16];
        } DUMMYSTRUCTNAME;
        UCHAR ExtendedInfo[48];
    } DUMMYUNIONNAME;
} FILE_OBJECTID_INFORMATION, *PFILE_OBJECTID_INFORMATION;

typedef NTSTATUS (WINAPI *PZW_QUERY_DIRECTORY_FILE) (HANDLE FileHandle,
    HANDLE Event, PIO_APC_ROUTINE ApcRoutine, PVOID ApcContext, PIO_STATUS_BLOCK IoStatusBlock,
    PVOID FileInformation, ULONG Length, FILE_INFORMATION_CLASS FileInformationClass,
    BOOLEAN ReturnSingleEntry, PUNICODE_STRING FileName, BOOLEAN RestartScan);

//https://stackoverflow.com/questions/3878517/how-to-get-fileindex-without-using-file-handle
PFILE_ID_FULL_DIR_INFORMATION DumpFileInformation (LPCWSTR pszDirName, LPCWSTR pszFileName)
{
    WCHAR szFileName[32767];
    
    UNICODE_STRING fn;
    IO_STATUS_BLOCK iosb;
    NTSTATUS status;
    LONGLONG byBuffer[(32767+sizeof(FILE_ID_FULL_DIR_INFORMATION))/sizeof(LONGLONG)];
    PFILE_ID_FULL_DIR_INFORMATION pFullInfo = (PFILE_ID_FULL_DIR_INFORMATION)byBuffer;
    //PFILE_ID_GLOBAL_TX_DIR_INFORMATION pGlobalTxDirInfo = (PFILE_ID_GLOBAL_TX_DIR_INFORMATION)byBuffer;
    HANDLE hDir = INVALID_HANDLE_VALUE;
    PZW_QUERY_DIRECTORY_FILE ZwQueryDirectoryFile = (PZW_QUERY_DIRECTORY_FILE)
        GetProcAddress(GetModuleHandle("ntdll.dll"),"ZwQueryDirectoryFile");

    __try {
        hDir = CreateFileW (pszDirName, FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                            OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
        if (hDir == INVALID_HANDLE_VALUE) {
			throw std::exception("ENOENT: no such file or directory");
        }

        lstrcpyW (szFileName, pszFileName);
        fn.Buffer = (LPWSTR) szFileName;
        fn.Length = wcslen(szFileName)*sizeof(WCHAR);
        fn.MaximumLength = sizeof(szFileName);
        RtlZeroMemory ((PVOID)&iosb, sizeof(iosb));
        status =  ZwQueryDirectoryFile (hDir, NULL, NULL, NULL, &iosb, byBuffer, sizeof(byBuffer),
                                        FileIdFullDirectoryInformation, TRUE, &fn, FALSE);
        if (NT_SUCCESS(status)) {
            return pFullInfo;
        } else {
			throw std::exception("ENOENT: no such file or directory");
		}
    }
    __finally {
        if (hDir != INVALID_HANDLE_VALUE)
            CloseHandle (hDir);
    }
}

//https://stackoverflow.com/questions/215963/how-do-you-properly-use-widechartomultibyte
std::wstring utf8Decode(const std::string &str)
{
    if( str.empty() ) return std::wstring();
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar                  (CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

long double WindowsTickToUnixSeconds(long long windowsTicks)
{
     return (windowsTicks / WINDOWS_TICK - SEC_TO_UNIX_EPOCH);
}


double hexToDouble(const std::string& hex)
{
    long long d = 0;
    std::stringstream ss(hex);
    ss >> std::hex >> reinterpret_cast<uint64_t&>(d);
    return d;
}

long double largeIntegerToLongDouble(LARGE_INTEGER number)
{
    char buffer [50];
    sprintf(buffer, "%08X%08X", number.HighPart, number.LowPart);
    long double dec = hexToDouble(buffer);
    return dec;                 
}

long double getMiliTimestamp(LARGE_INTEGER ts)
{
    long double mili = WindowsTickToUnixSeconds(largeIntegerToLongDouble(ts)) * 1000;
    return mili;
}

NAN_METHOD(lstatSync) {
    Nan:: HandleScope scope;
    v8::String::Utf8Value param1(info[0]->ToString());
    std::string from = std::string(*param1);
    
    string directory;
    string node;
    string path = from.c_str();
    const size_t last_slash_idx = path.rfind('\\');

    if (std::string::npos != last_slash_idx) {
        directory = path.substr(0, last_slash_idx)+'\\'+'\\';
        node = path.substr(last_slash_idx+1);
    }

    std::wstring tmp_directory = utf8Decode(directory);
    LPCWSTR w_directory = tmp_directory.c_str();

    std::wstring tmp_node = utf8Decode(node);
    LPCWSTR w_node = tmp_node.c_str();
    	
	  v8::Isolate* isolate = v8::Isolate::GetCurrent();

	  try {
        PFILE_ID_FULL_DIR_INFORMATION stats = DumpFileInformation (w_directory, w_node);
        Local<Object> obj = Object::New(isolate);

        char fileId [50];
        sprintf(fileId, "0x%08X%08X", stats->FileId.HighPart, stats->FileId.LowPart);

        obj->Set(String::NewFromUtf8(isolate, "fileid"), 
          String::NewFromUtf8(isolate, fileId));
        obj->Set(String::NewFromUtf8(isolate, "ino"), 
          Number::New(isolate, largeIntegerToLongDouble(stats->FileId)));
        obj->Set(String::NewFromUtf8(isolate, "size"), 
          Number::New(isolate, largeIntegerToLongDouble(stats->EndOfFile)));
        obj->Set(String::NewFromUtf8(isolate, "atime"), 
          Date::New(isolate, getMiliTimestamp(stats->LastAccessTime)));
        obj->Set(String::NewFromUtf8(isolate, "mtime"), 
          Date::New(isolate, getMiliTimestamp(stats->LastWriteTime)));
        obj->Set(String::NewFromUtf8(isolate, "ctime"), 
          Date::New(isolate, getMiliTimestamp(stats->CreationTime)));
        obj->Set(String::NewFromUtf8(isolate, "directory"), 
          Boolean::New(isolate, (stats->FileAttributes & FILE_ATTRIBUTE_DIRECTORY)));
        obj->Set(String::NewFromUtf8(isolate, "symbolicLink"), 
          Boolean::New(isolate, (stats->FileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)));        
			
        info.GetReturnValue().Set(obj);
    } catch(std::exception& e) {
        isolate->ThrowException(String::NewFromUtf8(isolate, "Error: ENOENT: No such file or directory"));
        return info.GetReturnValue().Set(Undefined());
    } 
}

NAN_MODULE_INIT(Initialize) {
    NAN_EXPORT(target, lstatSync);
}

NODE_MODULE(addon, Initialize);
