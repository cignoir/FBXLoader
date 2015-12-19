/* ��d�C���N���[�h�h�~ */
#pragma once


/* �w�b�_�t�@�C�� */
#include "../ShaderManager/ShaderManager.h"
#include "../SamplerManager/SamplerManager.h"
#include "../ResourceManager/TextureManager.h"
#include "../Math/Vector/Vector4.h"
#include "../Math/Matrix/Matrix3x3.h"
#include "../Math/Matrix/Matrix4x4.h"


/**

 @brief GALib
        GA���C�u�����֘A�̖��O���

*/
namespace GALib
{
    /**

     @brief Draw 
            �`��֘A�̖��O���

    */
    namespace Draw
    {
        /* �ʖ� */
        typedef Resource::SHADERHANDLE SHADERHANDLE;
        typedef Draw::SAMPLERHANDLE SAMPLERHANDLE;
        typedef Resource::GHANDLE GHANDLE;
        typedef Math::S_Vector3<float> Vector3;
        typedef Math::S_Vector4<float> Vector4;
        typedef Math::S_Matrix3x3<float> Matrix3x3;
        typedef Math::S_Matrix4x4<float> Matrix4x4;

        /**

         @brief eCullingType 
                �J�����O�̎�ނ�\���񋓌^

        */
        enum eCullingType
        {
            CULLING_FRONT,      ///< �O��
            CULLING_BACK,       ///< ���
            CULLING_NONE,       ///< �Ȃ�
        };

		/**
		
		@brief	�u�����h�̗񋓌^
		
		*/
		enum eBlendMode{
			BLEND_NORMAL,		//�ʏ�̃�����
			BLEND_ADD,			//���Z����
			BLEND_SUBTRACT,		//���Y����
			BLEND_MULTIPLE		//��Z����
		};

        /**

         @brief S_MatrixDesc 
                �s��̐ݒ�̂��߂̏���\���\����

        */
        struct S_MatrixDesc
        {
            // �����o�ϐ�
            Matrix4x4* m_p_worlds;
            Matrix4x4* m_p_views;
            Matrix4x4* m_p_projections;
            UINT m_world_count;
			UINT m_view_count;
			UINT m_projection_count;

            // �R���X�g���N�^
            S_MatrixDesc() :
            
                m_p_worlds(nullptr),
				m_p_views(nullptr),
				m_p_projections(nullptr),
                
                m_world_count(1),
                m_view_count(1),
                m_projection_count(1)
            
            {
            }
        };

		void GraphicsAPIInitialize();
		void GraphicsAPIFinalize();


        // �֐�
		UINT GetSamplerLocation(const SHADERHANDLE& r_PIXEL_SHADER_HANDLE, UINT slot_number);
		void SetSampler(const SAMPLERHANDLE& r_HANDLE, UINT location);
		void SetTexture(const GHANDLE& r_HANDLE, UINT location);
		void SetMatricesInVertexShader(const SHADERHANDLE& r_HANDLE,
                                       const Matrix4x4& r_WORLD, 
                                       const Matrix4x4& r_VIEW,
                                       const Matrix4x4& r_PROJECTION);
        void SetMatricesInVertexShader(const SHADERHANDLE& r_HANDLE,
                                       const Matrix4x4& r_WORLD,
                                       const Matrix4x4& r_VIEW,
                                       const Matrix4x4& r_PROJECTION,
                                       const Matrix3x3& r_NORMAL);
        void SetMaterialsInPixelShader(const SHADERHANDLE& r_HANDLE,
                                       const Vector3& r_DIFFUSE,
                                       const Vector3& r_AMBIENT,
                                       const Vector3& r_SPECULAR,
                                       float specular_power);
        void SetLightInPixelShader(const SHADERHANDLE& r_HANDLE,
                                   const Vector4& r_LIGHT_POSITION_OF_VIEW);
        void SetCulling(eCullingType type);
		void SetBlendMode(eBlendMode mode);
		void SetDepth(bool check, bool write);
    }
}