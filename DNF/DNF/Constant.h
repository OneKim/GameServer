#pragma once

//�ػ�
const _ushort WINSIZEX = 800;
const _ushort WINSIZEY = 600;

//â ��ġ
const _ushort WINPOSITIONX = 300;
const _ushort WINPOSITIONY = 30;

//���� ����
const _vec3 g_vLook = _vec3(0.0f, 0.0f, 1.0f);

//���� �ּ�
const char g_LoginServerName[16]	= "127.0.0.1";
const char g_ChattingServerName[16]	= "127.0.0.1";

const _int	g_LoginServerPort		= 9000;
const _int	g_ChattingServerPort	= 9200;

#define	SOCKET_BUF_SIZE		1024 * 10
#define CHARCTER_BUF_SIZE	32