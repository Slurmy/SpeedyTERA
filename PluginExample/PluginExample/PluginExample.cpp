#include <windows.h>
#include <cstdio>

char * szPacketTpl = "[SpeedyTera][PluginExample] %s[%d]: ";

void printPacket(char * type, char * buffer, size_t size) {
  size_t sLen = strlen(szPacketTpl) + (size * 2) + 255;
  char *buf = (char *)malloc(sLen);
  snprintf(buf, sLen, szPacketTpl, type, size);

  char hexBuf[3] = { 0 };
  for (size_t i = 0; i < size; i++) {
    sprintf_s(hexBuf, "%02X", (unsigned char)buffer[i]);
    strcat_s(buf, sLen, hexBuf);
  }

  OutputDebugString(buf);
  free(buf);
}

extern "C" __declspec (dllexport) void __cdecl onBeforeEncrypt(char * buffer, size_t size) {
  printPacket("onBeforeEncrypt", buffer, size);
}
extern "C" __declspec (dllexport) void __cdecl onAfterEncrypt(char * buffer, size_t size) {
  printPacket("onAfterEncrypt", buffer, size);
}
extern "C" __declspec (dllexport) void __cdecl onBeforeDecrypt(char * buffer, size_t size) {
  printPacket("onBeforeDecrypt", buffer, size);
}
extern "C" __declspec (dllexport) void __cdecl onAfterDecrypt(char * buffer, size_t size) {
  printPacket("onAfterDecrypt", buffer, size);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    OutputDebugString("[SpeedyTera][PluginExample] Attached");
    break;
  }
  case DLL_PROCESS_DETACH:
    OutputDebugString("[SpeedyTera][PluginExample] Detached");
    break;
  }

  return TRUE;
}
