#include <assert.h>
#include "FileReader.h"
/**

*	@brief	���\�[�X�̔j�����s���֐�

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::FileSystem::S_ResourceData::Destroy(){
	this->m_p_free_function(this->m_p_buffer);
}

/**

*	@brief	�t�@�C���̓ǂݍ��݂��s��

*	@param[in]	p_file_path	�t�@�C���p�X

*	@return	�Ȃ�

*/
void GALib::FileSystem::C_FileReader::Open(const char* p_file_path){
	this->Close();

	if (fopen_s(&this->m_file_info, p_file_path, "rb")){
		assert(false);
	}
}

/**

*	@brief	�t�@�C���̐��f�[�^��ǂݍ���

*	@param	�Ȃ�

*	@return	���\�[�X�f�[�^

*/
GALib::FileSystem::S_ResourceData GALib::FileSystem::C_FileReader::Read(){
	//���ɓǂݍ���ł���ꍇ�A���̃�����������Ԃ�
	if (this->m_p_buffer){
		S_ResourceData resource;
		resource.m_p_buffer = this->m_p_buffer;
		resource.m_length = this->m_length;
		resource.m_p_free_function = nullptr;
		return resource;
	}

	
		fseek(this->m_file_info, 0, SEEK_END);
		fpos_t pos;
		fgetpos(this->m_file_info, &pos);
		this->m_length = static_cast<std::size_t>(pos);

		fseek(this->m_file_info, 0, SEEK_SET);


		this->m_p_buffer = std::malloc(this->m_length);
		fread_s(this->m_p_buffer, this->m_length, this->m_length, 1, this->m_file_info);
	

	S_ResourceData resource;
	resource.m_p_buffer = this->m_p_buffer;
	resource.m_length = this->m_length;
	resource.m_p_free_function = nullptr;

	return resource;
}




/**

*	@brief�@�֐��𗘗p���t�@�C����ǂݍ���

*	@param	�Ȃ�

*	@return	���\�[�X�f�[�^

*/
GALib::FileSystem::S_ResourceData GALib::FileSystem::C_FileReader::Read(AllocFunctionPtr p_alloc_function, FreeFunctionPtr p_free_function){


	fseek(this->m_file_info, 0, SEEK_END);
	fpos_t pos;
	fgetpos(this->m_file_info, &pos);
	std::size_t size = static_cast<std::size_t>(pos);

	fseek(this->m_file_info, 0, SEEK_SET);


	void* buffer = p_alloc_function(size, 1);
	fread_s(buffer, size, size, 1, this->m_file_info);

	S_ResourceData resource;
	resource.m_p_buffer = buffer;
	resource.m_length = size;
	resource.m_p_free_function = p_free_function;

	return resource;
}

/**

*	@brief	�t�@�C���̃N���[�Y����

*	@param	�Ȃ�

*	@return	�Ȃ�

*/
void GALib::FileSystem::C_FileReader::Close(){
	if (this->m_close_flag) return;
	//close���s��
	if (this->m_file_info) fclose(this->m_file_info);
	if (this->m_p_buffer) std::free(this->m_p_buffer);

	this->m_file_info = nullptr;
	this->m_p_buffer = nullptr;
	this->m_close_flag = true;
}