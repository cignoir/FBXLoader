#pragma once
#include <iostream>
#include "../NullPointer/NullPointer.h"

/**

*	@brief	GAライブラリの名前空間

*/
namespace GALib{
	/**

	*	@brief	メモリ関連の名前空間

	*/
	namespace Utility{
		/**

		*	@brief	デフォルトデリータの規定構造体

		*/
		struct S_DefaultDeleterBase{
			void operator()(void* ptr){
				this->Delete(ptr);
			}
			virtual void Delete(void *ptr) = 0;
		};

		/**

		*	@brief	type erasureを実装したデフォルトデリータ
		保持した型にポインタをキャストしてからデリートを呼ぶ

		*/
		template<class _Type>
		struct S_DefaultDeleter : public S_DefaultDeleterBase{
			void Delete(void* ptr){
				_Type* p = static_cast<_Type*>(ptr);
				delete p;
			}
		};

		namespace Detail{
			/**

			*	@brief	ポインタとデリータと参照カウントを保持するホルダークラスの基底クラス

			*/
			class C_PtrDeleterHolderBase{
			public:
				C_PtrDeleterHolderBase() :m_ref_count(0){}
				virtual void* GetPtr() const {
					return (void*)(0);
				};
				virtual void Destroy() = 0;

				/**

				*	@brief	現在の参照カウンタを取得

				*/
				int GetRefCount() const {
					return this->m_ref_count;
				}

				/**

				*	@brief	参照カウントを加算

				*/
				void AddRef() {
					++this->m_ref_count;
				}

				/**

				*	@brief	参照カウントを減算

				*/
				void DeclRef() {
					--this->m_ref_count;
				}
			private:
				int m_ref_count;

			};
			/**

			*	@brief	アライメント調整が有効かどうかの特殊化クラス

			*/
			template<bool aligned>
			struct S_Aligned{
			};

			template<>
			struct S_Aligned < true > {
				static const bool value = true;
			};

			template<>
			struct S_Aligned < false > {
				static const bool value = false;
			};

			template<int size, int align>
			struct S_AlignedStorageSize{
				static const int value = ((size / align) + S_Aligned<size % align>::value) * align + align;
			};

			/**

			*	@brief	特定サイズのアライメント調整をしたストレージクラス

			*/
			template<int size, int align = 4 >
			class S_AlignedStorage{
			public:
				S_AlignedStorage(){
					this->m_storage_ptr = (void*)((int)this->m_storage + (align - ((int)this->m_storage % align)));
				}
				void* data(){
					return this->m_storage_ptr;
				}
			private:
				char m_storage[S_AlignedStorageSize<size, align>::value];
				void* m_storage_ptr;
			};

			/**

			*	@brief	ポインタとデリータと参照カウントを保持するクラス

			*/

			template<class _Type, class _Del, class _Allocator>
			class C_PtrDeleterHolder : public C_PtrDeleterHolderBase{
				typedef typename _Allocator::template rebind<C_PtrDeleterHolder>::other MyAllocator;
			public:
				C_PtrDeleterHolder(_Type* ptr, const _Del& del) : m_ptr(ptr), m_deleter(del)
				{}

				/**

				*	@brief	保持しているポインタを破棄

				*/
				virtual void Destroy() {
					this->m_deleter(this->m_ptr);
					MyAllocator().deallocate(this, 0);
				}

				/**

				*	@brief	保持しているポインタをvoid*で取得

				*/
				virtual void* GetPtr()const { return this->m_ptr; }

			private:
				_Del m_deleter;
				_Type* m_ptr;

			};

			/**

			*	@brief	オブジェクトとそのアロケーターの保持クラス

			*/
			template<class _Type, class _Allocator >
			class C_ObjectAllocatorHolder : public C_PtrDeleterHolderBase{
				typedef typename _Allocator::template rebind<C_ObjectAllocatorHolder>::other MyAllocator;
			public:
				C_ObjectAllocatorHolder(){
					this->m_p_storage_ref = reinterpret_cast<_Type*>(this->m_storage.data());
				}

				/**

				*	@brief	保持しているポインタを破棄

				*/
				virtual void Destroy() {
					((_Type*)(this->GetPtr()))->~_Type();
					MyAllocator().deallocate(this, 0);
				}

				/**

				*	@brief	保持しているポインタをvoid*で取得

				*/
				virtual void* GetPtr()const { return this->m_storage.data(); }


			private:
				_Type*	m_p_storage_ref;
				mutable S_AlignedStorage<sizeof(_Type)> m_storage;
			};
		};


		/**

		*	@brief	shared_ptr

		*	@param[temp]	_Type	保持するオブジェクトの型
		*	@param[temp]	_Deleter	デリータ関数オブジェクトの型
		デフォルトではtype erasureを使ったデリータを使用する

		*/
		template < class _Type >
		class C_SharedPtr{
			typedef C_SharedPtr<_Type> ThisType;

		public:

			/**

			*	@brief	コンストラクタ
			特に実体も何も確保しないnull初期化

			*	@param	なし

			*/
			C_SharedPtr() : m_holder(GA_NULL)
			{
			}

			/**

			*	@brief	コンストラクタ、引数で渡したポインタを保持する
			newで確保したもののみを管理すること

			*	@param[in]	ptr	管理したいポインタ
			*	@param[in]	deleter	デリータ

			*/
			template<class _T, class _Deleter >
			C_SharedPtr(_T* ptr, _Deleter deleter) : m_holder(GA_NULL)
			{
				typedef Detail::C_PtrDeleterHolder<_T, _Deleter, GALib::Memory::C_Allocator<_T> > HolderType;
				typedef GALib::Memory::C_Allocator<HolderType> HolderAllocator;
				HolderAllocator allocator;
				this->m_holder = allocator.allocate(1);
				new(this->m_holder) HolderType(ptr, deleter);
				this->m_holder->AddRef();
#ifdef GA_LIB_DEBUG_MODE
				//仕様上別の型でも代入できてしまうのでコンパイルエラーを無理やり引き起こすコード
				//ポリモーフィックな動作が可能ならば問題なく通る
				_Type* t = ((_T*)(0));
#endif
			}

			template<class _T>
			C_SharedPtr(_T* ptr) : m_holder(GA_NULL)
			{
				typedef Detail::C_PtrDeleterHolder<_T, S_DefaultDeleter<_T>, GALib::Memory::C_Allocator<_T> > HolderType;
				typedef GALib::Memory::C_Allocator<HolderType> HolderAllocator;
				HolderAllocator allocator;
				this->m_holder = allocator.allocate(1);
				new(this->m_holder) HolderType(ptr, S_DefaultDeleter<_T>());
				this->m_holder->AddRef();
#ifdef GA_LIB_DEBUG_MODE
				//仕様上別の型でも代入できてしまうのでコンパイルエラーを無理やり引き起こすコード
				//ポリモーフィックな動作が可能ならば問題なく通る
				_Type* t = ((_T*)(0));
#endif
			}

			/**

			*	@brief	allocatorによるholder確保処理用コンストラクタ

			*	@param[in]	ptr	ホルダーのポインタ

			*/
			template<class _T, class _A>
			explicit C_SharedPtr(Detail::C_ObjectAllocatorHolder< _T, _A> * ptr) : m_holder(GA_NULL){
				this->m_holder = ptr;
				this->m_holder->AddRef();
			}

			/**

			*	@brief	コピーコンストラクタ

			*	@param[in]	ref	コピー元

			*/
			template<class _T>
			C_SharedPtr(const  C_SharedPtr<_T>& ref) : m_holder(GA_NULL){
				this->Assign(ref);
			}

			/**

			*	@brief	コピーコンストラクタ

			*	@param[in]	ref	コピー元

			*/
			C_SharedPtr(const ThisType& ref) : m_holder(GA_NULL){
				this->Assign(ref);
			}


			/**

			*	@brief	デストラクタ

			*	@param	なし
			*/
			~C_SharedPtr(){
				//参照カウントをデクリメントした値が0ならば破棄する
				if (this->m_holder){
					this->m_holder->DeclRef();
					if (this->m_holder->GetRefCount() == 0){
						this->m_holder->Destroy();
						this->m_holder = GA_NULL;
					}
				}
			}

			/**

			*	@brief	コピー代入演算子

			*	@param[in] ref	コピー元

			*	@return なし

			*/
			template<class _T>
			void operator=(const  C_SharedPtr<_T>& ref) {
				this->Assign(ref);
			}

			/**

			*	@brief	コピー代入演算子

			*	@param[in] ref	コピー元

			*	@return なし

			*/
			void operator=(const ThisType& ref){
				this->Assign(ref);
			}

			/**

			*	@brief	ポインタの代入演算子
			管理している参照を破棄し、新しい参照を生成する

			*	@param	なし

			*	@return	なし

			*/
			template<class _T>
			void operator=(_T* ptr){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr);
			}

			/**

			*	@brief	boolキャスト演算子

			*	@param	なし

			*	@return	なし

			*/
			operator bool() const{
				return (this->m_holder != GA_NULL);
			}


			/**

			*	@brief	リセット関数
			このshared_ptrの管理しているオブジェクトの参照を破棄する
			破棄したあとはnullで初期化し、管理対象を持たない

			*	@param	なし

			*	@return　なし

			*/
			void Reset(){
				this->~C_SharedPtr();
				new(this) C_SharedPtr();
			}

			/**

			*	@brief	リセット関数
			このshared_ptrの管理しているオブジェクトの参照を破棄し
			新たなオブジェクトの監視を開始する

			*	@param[in]	ptr	新たな監視対象のオブジェクトのポインタ

			*	@return	なし

			*/
			template<class _T>
			void Reset(_T* ptr){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr);
			}

			/**

			*	@brief	リセット関数
			このshared_ptrの管理しているオブジェクトの参照を破棄し
			新たなオブジェクトの監視を開始する

			*	@param[in]	ptr	新たな監視対象のオブジェクトのポインタ
			*	@param[in]	del	新たなデリータ

			*	@return	なし

			*/
			template<class _T, class _Del>
			void Reset(_T* ptr, _Del del){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr, del);
			}
			/**

			*	@brief	管理しているオブジェクトのポインタを取得する

			*	@param	なし

			*	@return	オブジェクトのポインタ

			*/
			_Type* Get() const {
				if (this->m_holder){
					return static_cast<_Type*>(this->m_holder->GetPtr());
				}
				else{
					return GA_NULL;
				}
			}

			/**

			*	@brief	アロー演算子

			*	@param	なし

			*	@return	オブジェクトのポインタ

			*/
			_Type*	operator->() const{ return this->Get(); }


			/**

			*	@brief	コピー用のホルダー取得関数

			*	@param	なし

			*	@return	ホルダーのポインタ

			*/
			Detail::C_PtrDeleterHolderBase* _GetHolder() const { return this->m_holder; }

			Detail::C_PtrDeleterHolderBase* _GetHolder()  { return this->m_holder; }

		private:
			template<class _T>
			void Assign(const C_SharedPtr<_T>& ref){
#ifdef GA_LIB_DEBUG_MODE
				//仕様上別の型でも代入できてしまうのでコンパイルエラーを無理やり引き起こすコード
				//ポリモーフィックな動作が可能ならば問題なく通る
				_Type* ptr = ((_T*)(0));
#endif
				if (this->m_holder != ref._GetHolder()){
					this->~C_SharedPtr();

					this->m_holder = ref._GetHolder();
					if (this->m_holder){
						this->m_holder->AddRef();
					}
				}
			}
			Detail::C_PtrDeleterHolderBase*	m_holder;
		};


#define GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(...) \
	typedef Detail::C_ObjectAllocatorHolder<_Type, _Allocator>  MyType; \
	typedef typename _Allocator::template rebind<MyType>::other other_alloc; \
	MyType* holder = other_alloc().allocate(1); \
	new((void*)holder) MyType(); \
	new(holder->GetPtr()) _Type(__VA_ARGS__); \
	return C_SharedPtr<_Type>(holder);


		template<class _Type, class _Allocator>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL()
		}

		template<class _Type, class _Allocator, class _0>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a)
		}
		template<class _Type, class _Allocator, class _0, class _1>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4, class _5>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e, _5 f){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e, f)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4, class _5, class _6>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e, _5 f, _6 g){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e, f, g)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4, class _5, class _6, class _7>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e, _5 f, _6 g, _7 h){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e, f, g, h)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4, class _5, class _6, class _7, class _8>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e, _5 f, _6 g, _7 h, _8 i){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e, f, g, h, i)
		}
		template<class _Type, class _Allocator, class _0, class _1, class _2, class _3, class _4, class _5, class _6, class _7, class _8, class _9>
		C_SharedPtr<_Type> AllocateShared(const _Allocator& alloc, _0 a, _1 b, _2 c, _3 d, _4 e, _5 f, _6 g, _7 h, _8 i, _9 j){
			GA_LIB_ALLOCATE_SHARED_FUNCTION_IMPL(a, b, c, d, e, f, g, h, i, j)
		}
	}
}


