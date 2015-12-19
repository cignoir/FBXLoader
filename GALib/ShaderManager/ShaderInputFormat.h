#pragma once

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	���\�[�X�֘A�̖��O���

	*/
	namespace Resource{
		/**
		
		*	@brief	�V�F�[�_�֘A�̖��O���
		
		*/
		namespace ShaderManager{
			/**
			
			*	@brief	���̓��C�A�E�g�t�H�[�}�b�g�p�ɍĒ�`����N���X
			
			*/
			class C_ShaderInputFormat{
			public:
				static const int FORMAT_RGBA32_FLOAT;
				static const int FORMAT_RGB32_FLOAT;
				static const int FORMAT_RG32_FLOAT;
				static const int FORMAT_R32_FLOAT;
				static const int FORMAT_RGBA32_UINT;
			};

			int GetFormatByteSize(int format);
		}
	}
}