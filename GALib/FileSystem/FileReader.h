#pragma once
#include <cstdlib>
#include <functional>

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**
	
	*	@brief	ファイルシステム関連の名前空間
	
	*/
	namespace FileSystem{
		using AllocFunctionPtr = std::function < void*(std::size_t, int) > ;
		using FreeFunctionPtr = std::function < void(void*) > ;

		/**
		
		*	@brief	読み込んだリソースを表す構造体
		
		*/
		struct S_ResourceData{
			
			void*	m_p_buffer = nullptr;
			std::size_t m_length = 0;
			FreeFunctionPtr	m_p_free_function;
			void Destroy();
		};


		/**
		
		*	@brief	ファイル読み込みを行うためのクラス
					この読み込みはバイナリモード前提となっているため注意
		
		*/
		class C_FileReader{
		public:
			C_FileReader(){};
			C_FileReader(const char* p_file_path){ this->Open(p_file_path); }
			~C_FileReader(){ this->Close(); }
			void Open(const char* p_file_path);

			//Read関数に引数を指定しない場合、内部で自動でメモリを確保し
			//スコープを抜けた時点でメモリを破棄する

			//Read関数に引数を指定した場合、指定された関数でメモリを確保する
			//スコープを抜けた時点で明示的に破棄することは不可能で、S_ResourceData::Destroyを呼び出す必要がある
			//また、nullptrを指定した場合の動作は保障しない 
			S_ResourceData Read();
			S_ResourceData Read(AllocFunctionPtr p_alloc_function, FreeFunctionPtr p_free_function);

			void Close();
		private:
			void* m_p_buffer = nullptr;
			std::size_t m_length = 0;
			FILE*	m_file_info = nullptr;
			unsigned int	m_archive_point = 0;		//アーカイブのファイル位置
			bool	m_archive_read_flag = false;	//アーカイブから読み取るかどうかのフラグ
			bool	m_close_flag = true;
		};
	}
}