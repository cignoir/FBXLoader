#pragma once
#include <cstdlib>
#include <functional>

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	�t�@�C���V�X�e���֘A�̖��O���
	
	*/
	namespace FileSystem{
		using AllocFunctionPtr = std::function < void*(std::size_t, int) > ;
		using FreeFunctionPtr = std::function < void(void*) > ;

		/**
		
		*	@brief	�ǂݍ��񂾃��\�[�X��\���\����
		
		*/
		struct S_ResourceData{
			
			void*	m_p_buffer = nullptr;
			std::size_t m_length = 0;
			FreeFunctionPtr	m_p_free_function;
			void Destroy();
		};


		/**
		
		*	@brief	�t�@�C���ǂݍ��݂��s�����߂̃N���X
					���̓ǂݍ��݂̓o�C�i�����[�h�O��ƂȂ��Ă��邽�ߒ���
		
		*/
		class C_FileReader{
		public:
			C_FileReader(){};
			C_FileReader(const char* p_file_path){ this->Open(p_file_path); }
			~C_FileReader(){ this->Close(); }
			void Open(const char* p_file_path);

			//Read�֐��Ɉ������w�肵�Ȃ��ꍇ�A�����Ŏ����Ń��������m�ۂ�
			//�X�R�[�v�𔲂������_�Ń�������j������

			//Read�֐��Ɉ������w�肵���ꍇ�A�w�肳�ꂽ�֐��Ń��������m�ۂ���
			//�X�R�[�v�𔲂������_�Ŗ����I�ɔj�����邱�Ƃ͕s�\�ŁAS_ResourceData::Destroy���Ăяo���K�v������
			//�܂��Anullptr���w�肵���ꍇ�̓���͕ۏႵ�Ȃ� 
			S_ResourceData Read();
			S_ResourceData Read(AllocFunctionPtr p_alloc_function, FreeFunctionPtr p_free_function);

			void Close();
		private:
			void* m_p_buffer = nullptr;
			std::size_t m_length = 0;
			FILE*	m_file_info = nullptr;
			unsigned int	m_archive_point = 0;		//�A�[�J�C�u�̃t�@�C���ʒu
			bool	m_archive_read_flag = false;	//�A�[�J�C�u����ǂݎ�邩�ǂ����̃t���O
			bool	m_close_flag = true;
		};
	}
}