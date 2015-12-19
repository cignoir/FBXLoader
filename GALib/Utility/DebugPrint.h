#pragma once
#include <Windows.h>
#include <stdio.h>

// ---------------------------------------------------------
//�f�o�b�O�E�B���h�E�ɕ�����o��
// ---------------------------------------------------------
//�ϒ�����
static void DebugPrint(const char *str, ...){
	const int DEBUG_BUFFER_SIZE = 512;
	char debug_buf[DEBUG_BUFFER_SIZE];

	//�������X�g�̕ϐ���錾
	//va_start�Ń��X�g�̎擾
	va_list ap;
	va_start(ap, str);

	//�������X�g�ւ̃|�C���^�𗘗p���āA�����t�o�͂���������
	if (!vsprintf_s(debug_buf, DEBUG_BUFFER_SIZE, str, ap)){
		//�G���[���Ԃ��Ă����̂ŃG���[�o��
		OutputDebugStringA("error");
	}
	va_end(ap);
	OutputDebugStringA(debug_buf);

}
