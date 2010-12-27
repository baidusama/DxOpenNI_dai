// DxOpenNI.cpp
//  Dinamic link library of OpenNI for DirectX named DxOpenNI.dll
//
//   This program is modified from OpenNI driver.
//   OpenNI is written and distributed under the GNU Lesser General Public License,
//  so this program(dll) is redistributed under the terms of the GNU Lesser General Public License
//  as published by the Free Software Foundation, either version 3 of the License.
//   See the GNU General Public License for more details: <http://www.gnu.org/licenses/>.
// 
//   ���̃v���O������OpenNI�h���C�o���g�p���Ă��܂��BOpenNI��GNU LGPL���C�Z���X�ł��B
//   ����āA���̃v���O������LGPL���C�Z���X�ɏ]���A�\�[�X�R�[�h�����J���邱�ƂƂ��܂��B
//   �Ȃ��A���̃v���O�����̓_�C�i�~�b�N�����N(dll)�Ƃ��Ďg�p����ꍇ�A����dll�𗘗p����
//  ���̃v���O������LGPL���C�Z���X�ɏ]���K�v�͂���܂���B


// DxOpenNI 1.10 �̉��ϔ�
//  - �R�[�h�S�̂̃N���X��
//  - GUI�ɂ��Θb�@�\�̒ǉ�
//  - ���R���I�v�V�����̒ǉ�
// by Dai.K (twitter: @dai197x)

// include files
#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnCppWrapper.h>
#include <XnCppWrapper.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "NISystem.h"

// export functions
__declspec(dllexport) bool __stdcall OpenNIInit(HWND,bool,LPDIRECT3DDEVICE9,WCHAR*);
__declspec(dllexport) void __stdcall OpenNIClean();
__declspec(dllexport) void __stdcall OpenNIDrawDepthMap(bool);
__declspec(dllexport) void __stdcall OpenNIDepthTexture(IDirect3DTexture9**);
__declspec(dllexport) void __stdcall OpenNIGetSkeltonJointPosition(int,D3DXVECTOR3*);
__declspec(dllexport) void __stdcall OpenNIIsTracking(bool*);
__declspec(dllexport) void __stdcall OpenNIGetVersion(float*);



// include libraries
#pragma comment(lib, "openNI.lib")

// global variables
NISystem g_system;

// DllMain
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch( fdwReason )
	{
	case DLL_PROCESS_ATTACH: //1
		g_system.OnAttach(hinstDLL);
		break;

	case DLL_PROCESS_DETACH: //0
		g_system.OnDetach(hinstDLL);
		OpenNIClean();
		break;

	case DLL_THREAD_ATTACH: //2
		break;

	case DLL_THREAD_DETACH: //3
		break;
	}

	return TRUE;
}



// EXPORT FUNCTION:Clean()
__declspec(dllexport) void __stdcall OpenNIClean()
{
	g_system.Clean();
}

// EXPORT FUNCTION:Init()
__declspec(dllexport) bool __stdcall OpenNIInit(HWND hWnd,bool EngFlag,LPDIRECT3DDEVICE9 lpDevice,WCHAR* f_path)
{
//	TrackingF=false;
//	for(int i=0;i<15;i++) TrCount[i]=0;

	SetCurrentDirectoryW(f_path);

	char* file = "Data\\SamplesConfig.xml";
	if (! g_system.Setup(hWnd, EngFlag, lpDevice, file)) {
		return false;
	}
	return true;
}

__declspec(dllexport) void __stdcall OpenNIDrawDepthMap(bool waitflag)
{
	g_system.Turn(waitflag);
}

__declspec(dllexport) void __stdcall OpenNIDepthTexture(IDirect3DTexture9** lpTex)
{
	g_system.GetDepthTexture(lpTex);
}

__declspec(dllexport) void __stdcall OpenNIGetSkeltonJointPosition(int num,D3DXVECTOR3* vec)
{
	g_system.GetJointPosition(num, vec);
}

__declspec(dllexport) void __stdcall OpenNIIsTracking(bool* lpb)
{
	g_system.IsTracking(lpb);
}

// GetVersion()
__declspec(dllexport) void __stdcall OpenNIGetVersion(float* ver)
{
	*ver = 1.10f;
}
