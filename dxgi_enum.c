//#include <d3d11.h>
//#include <d3dcommon.h>

#include <stdint.h>
#include <stdio.h>
#include <stdatomic.h>
#include <unistd.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_5.h>
//#include <d3d11.h>
//#include <d3dcommon.h>
//#include <versionhelpers.h>
#include <dwmapi.h>
//#include <winresrc.h>
#include <windows.h>

#include <wchar.h>
static const char *ws(const WCHAR *w) {
	static char buf[1024];
	memset(buf,0,sizeof buf);
	wcstombs(buf, w, sizeof buf);
	buf[sizeof(buf)-1] = '\0';
	return buf;
}

//int main(int argc, char **argv)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HRESULT          status;
  DXGI_OUTPUT_DESC outputDesc;
  IDXGIFactory1            * factory=NULL;
  IDXGIAdapter1            * adapter =NULL;

 //status = CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, &IID_IDXGIFactory1, (void **)&factory);
  status = CreateDXGIFactory1(&IID_IDXGIFactory1, (void **)&factory);
  if (FAILED(status))
  {
    printf("Failed to create DXGIFactory1\n");
    return 1;
  }

  for(int i = 0; IDXGIFactory1_EnumAdapters1(factory, i, &adapter) != DXGI_ERROR_NOT_FOUND; ++i)
  {
    printf("Adapter %d\n", i);

    DXGI_ADAPTER_DESC1 adapterDesc;
    status = IDXGIAdapter1_GetDesc1(adapter, &adapterDesc);
    if (FAILED(status)) {
      printf("Failed to get the device description\n");
      continue;
    }

	printf("Device Name       : \"%.200s\"\n"    , ws(outputDesc.DeviceName));
	printf("Device Description: \"%.200s\"\n"    , ws(adapterDesc.Description));
	printf("Device Vendor ID  : 0x%x\n"   , adapterDesc.VendorId);
	printf("Device Device ID  : 0x%x\n"   , adapterDesc.DeviceId);
	printf("Device Video Mem  : %u MiB\n" , (unsigned)(adapterDesc.DedicatedVideoMemory  / 1048576));
	printf("Device Sys Mem    : %u MiB\n" , (unsigned)(adapterDesc.DedicatedSystemMemory / 1048576));
	printf("Shared Sys Mem    : %u MiB\n" , (unsigned)(adapterDesc.SharedSystemMemory    / 1048576));

  	 IDXGIOutput              * output=NULL;
    for(int n = 0; IDXGIAdapter1_EnumOutputs(adapter, n, &output) != DXGI_ERROR_NOT_FOUND; ++n)
    {
      IDXGIOutput_GetDesc(output, &outputDesc);

      printf("  Output %d: ", n);
      printf("\"%.200s\" (AttachedToDesktop=%d)", ws(outputDesc.DeviceName), (int) outputDesc.AttachedToDesktop);
      printf("\n");

      IDXGIOutput_Release(output);
      output=NULL;
    }

    IDXGIAdapter1_Release(adapter);
    adapter = NULL;
    printf("\n");
  }

  if (factory) {
    IDXGIFactory1_Release(factory);
  }

  return 0;
}

