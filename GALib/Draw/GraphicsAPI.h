/* 二重インクルード防止 */
#pragma once


/* ヘッダファイル */
#include "../ShaderManager/ShaderManager.h"
#include "../SamplerManager/SamplerManager.h"
#include "../ResourceManager/TextureManager.h"
#include "../Math/Vector/Vector4.h"
#include "../Math/Matrix/Matrix3x3.h"
#include "../Math/Matrix/Matrix4x4.h"


/**

 @brief GALib
        GAライブラリ関連の名前空間

*/
namespace GALib
{
    /**

     @brief Draw 
            描画関連の名前空間

    */
    namespace Draw
    {
        /* 別名 */
        typedef Resource::SHADERHANDLE SHADERHANDLE;
        typedef Draw::SAMPLERHANDLE SAMPLERHANDLE;
        typedef Resource::GHANDLE GHANDLE;
        typedef Math::S_Vector3<float> Vector3;
        typedef Math::S_Vector4<float> Vector4;
        typedef Math::S_Matrix3x3<float> Matrix3x3;
        typedef Math::S_Matrix4x4<float> Matrix4x4;

        /**

         @brief eCullingType 
                カリングの種類を表す列挙型

        */
        enum eCullingType
        {
            CULLING_FRONT,      ///< 前面
            CULLING_BACK,       ///< 後面
            CULLING_NONE,       ///< なし
        };

		/**
		
		@brief	ブレンドの列挙型
		
		*/
		enum eBlendMode{
			BLEND_NORMAL,		//通常のα合成
			BLEND_ADD,			//加算合成
			BLEND_SUBTRACT,		//減産合成
			BLEND_MULTIPLE		//乗算合成
		};

        /**

         @brief S_MatrixDesc 
                行列の設定のための情報を表す構造体

        */
        struct S_MatrixDesc
        {
            // メンバ変数
            Matrix4x4* m_p_worlds;
            Matrix4x4* m_p_views;
            Matrix4x4* m_p_projections;
            UINT m_world_count;
			UINT m_view_count;
			UINT m_projection_count;

            // コンストラクタ
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


        // 関数
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