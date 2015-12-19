#pragma once
#include "SamplerTypes.h"
#include "../Utility/GASTL.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**
	
	*	@brief	�`��֘A�̖��O���
	
	*/
	namespace Draw{
		/**
		
		*	@brief	�T���v���Ǘ��̖��O���
		
		*/
		namespace SamplerManager{
			/**
			
			*	@brief	�T���v���[�n���h���̃C���^�[�t�F�[�X
			
			*/
			class IC_SamplerHandle{
			public:
				virtual ~IC_SamplerHandle(){}
				virtual void* GetSampler() const = 0;
			protected:
				IC_SamplerHandle(){}
			};

			using SAMPLERHANDLE = Utility::C_SharedPtr < IC_SamplerHandle > ;

			
			SAMPLERHANDLE CreateSampler(int filter, int clamp);
		}
		using SAMPLERHANDLE = SamplerManager::SAMPLERHANDLE;
	}
}
