#pragma once
#include "../Utility/GASTL.h"
#include "../Math/Vector/Vector2.h"
/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	���\�[�X�֘A�̖��O���
	
	*/
	namespace Resource{
		/**

		*	@brief	�e�N�X�`���Ǘ��̖��O���

		*/
		namespace TextureManager{

			/**

			*	@brief	�e�N�X�`���n���h���̃C���^�[�t�F�[�X�N���X

			*/
			class IC_TextureHandle{
			public:
				virtual ~IC_TextureHandle(){}

				virtual int GetTextureWidth() const  = 0;
				virtual int GetTextureHeight()const  = 0;
				virtual Math::Vector2 GetTextureUV(int index)const = 0;
				virtual void* GetTextureAPIPtr()const = 0;
			protected:
				IC_TextureHandle(){}
			};
			using GHANDLE = Utility::C_SharedPtr < IC_TextureHandle > ;


			GHANDLE LoadGraph(const char* file_path);
			GHANDLE DerivationGraph(int tx, int ty, int tw, int th, GHANDLE& base_handle);
			void LoadDivGraph(GHANDLE& base_graph, int tx, int ty, int tw, int th, int x_num, int y_num, int div_num, GHANDLE* out);
		}

		using GHANDLE = TextureManager::GHANDLE;
	}
	
}