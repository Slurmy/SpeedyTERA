#include <windows.h>
#include <cstdio>

void printPacket(char *type, char *buffer, size_t size) {
  size_t sLen = (size * 2) + 1;
  char *buf = (char *)malloc(sLen);
  buf[0] = '\0';
  buf[sLen - 1] = '\0';

  char hexBuf[3] = { 0 };
  for (size_t i = 0; i < size; i++) {
    sprintf_s(hexBuf, "%02X", (unsigned char)buffer[i]);
    strcat_s(buf, sLen, hexBuf);
  }

  printf("[PluginExample] %s[%d]: %s\n", type, size, buf);
  free(buf);
}

extern "C" __declspec (dllexport) void __cdecl onBeforeEncrypt(char *buffer, size_t size) {
  printPacket("onBeforeEncrypt", buffer, size);
}
/*extern "C" __declspec (dllexport) void __cdecl onAfterEncrypt(char *buffer, size_t size) {
  printPacket("onAfterEncrypt", buffer, size);
}
extern "C" __declspec (dllexport) void __cdecl onBeforeDecrypt(char *buffer, size_t size) {
  printPacket("onBeforeDecrypt", buffer, size);
}*/
extern "C" __declspec (dllexport) void __cdecl onAfterDecrypt(char *buffer, size_t size) {
  printPacket("onAfterDecrypt", buffer, size);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved) {
  switch (ulReason) {
  case DLL_PROCESS_ATTACH: {
    printf("[PluginExample] Attached\n");
    break;
  }
  case DLL_PROCESS_DETACH:
    printf("[PluginExample] Detached\n");
    break;
  }

  return TRUE;
}
