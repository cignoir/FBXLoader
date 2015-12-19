#pragma once
#include <iostream>
#include "../NullPointer/NullPointer.h"

/**

*	@brief	GA���C�u�����̖��O���

*/
namespace GALib{
	/**

	*	@brief	�������֘A�̖��O���

	*/
	namespace Utility{
		/**

		*	@brief	�f�t�H���g�f���[�^�̋K��\����

		*/
		struct S_DefaultDeleterBase{
			void operator()(void* ptr){
				this->Delete(ptr);
			}
			virtual void Delete(void *ptr) = 0;
		};

		/**

		*	@brief	type erasure�����������f�t�H���g�f���[�^
		�ێ������^�Ƀ|�C���^���L���X�g���Ă���f���[�g���Ă�

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

			*	@brief	�|�C���^�ƃf���[�^�ƎQ�ƃJ�E���g��ێ�����z���_�[�N���X�̊��N���X

			*/
			class C_PtrDeleterHolderBase{
			public:
				C_PtrDeleterHolderBase() :m_ref_count(0){}
				virtual void* GetPtr() const {
					return (void*)(0);
				};
				virtual void Destroy() = 0;

				/**

				*	@brief	���݂̎Q�ƃJ�E���^���擾

				*/
				int GetRefCount() const {
					return this->m_ref_count;
				}

				/**

				*	@brief	�Q�ƃJ�E���g�����Z

				*/
				void AddRef() {
					++this->m_ref_count;
				}

				/**

				*	@brief	�Q�ƃJ�E���g�����Z

				*/
				void DeclRef() {
					--this->m_ref_count;
				}
			private:
				int m_ref_count;

			};
			/**

			*	@brief	�A���C�����g�������L�����ǂ����̓��ꉻ�N���X

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

			*	@brief	����T�C�Y�̃A���C�����g�����������X�g���[�W�N���X

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

			*	@brief	�|�C���^�ƃf���[�^�ƎQ�ƃJ�E���g��ێ�����N���X

			*/

			template<class _Type, class _Del, class _Allocator>
			class C_PtrDeleterHolder : public C_PtrDeleterHolderBase{
				typedef typename _Allocator::template rebind<C_PtrDeleterHolder>::other MyAllocator;
			public:
				C_PtrDeleterHolder(_Type* ptr, const _Del& del) : m_ptr(ptr), m_deleter(del)
				{}

				/**

				*	@brief	�ێ����Ă���|�C���^��j��

				*/
				virtual void Destroy() {
					this->m_deleter(this->m_ptr);
					MyAllocator().deallocate(this, 0);
				}

				/**

				*	@brief	�ێ����Ă���|�C���^��void*�Ŏ擾

				*/
				virtual void* GetPtr()const { return this->m_ptr; }

			private:
				_Del m_deleter;
				_Type* m_ptr;

			};

			/**

			*	@brief	�I�u�W�F�N�g�Ƃ��̃A���P�[�^�[�̕ێ��N���X

			*/
			template<class _Type, class _Allocator >
			class C_ObjectAllocatorHolder : public C_PtrDeleterHolderBase{
				typedef typename _Allocator::template rebind<C_ObjectAllocatorHolder>::other MyAllocator;
			public:
				C_ObjectAllocatorHolder(){
					this->m_p_storage_ref = reinterpret_cast<_Type*>(this->m_storage.data());
				}

				/**

				*	@brief	�ێ����Ă���|�C���^��j��

				*/
				virtual void Destroy() {
					((_Type*)(this->GetPtr()))->~_Type();
					MyAllocator().deallocate(this, 0);
				}

				/**

				*	@brief	�ێ����Ă���|�C���^��void*�Ŏ擾

				*/
				virtual void* GetPtr()const { return this->m_storage.data(); }


			private:
				_Type*	m_p_storage_ref;
				mutable S_AlignedStorage<sizeof(_Type)> m_storage;
			};
		};


		/**

		*	@brief	shared_ptr

		*	@param[temp]	_Type	�ێ�����I�u�W�F�N�g�̌^
		*	@param[temp]	_Deleter	�f���[�^�֐��I�u�W�F�N�g�̌^
		�f�t�H���g�ł�type erasure���g�����f���[�^���g�p����

		*/
		template < class _Type >
		class C_SharedPtr{
			typedef C_SharedPtr<_Type> ThisType;

		public:

			/**

			*	@brief	�R���X�g���N�^
			���Ɏ��̂������m�ۂ��Ȃ�null������

			*	@param	�Ȃ�

			*/
			C_SharedPtr() : m_holder(GA_NULL)
			{
			}

			/**

			*	@brief	�R���X�g���N�^�A�����œn�����|�C���^��ێ�����
			new�Ŋm�ۂ������݂̂̂��Ǘ����邱��

			*	@param[in]	ptr	�Ǘ��������|�C���^
			*	@param[in]	deleter	�f���[�^

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
				//�d�l��ʂ̌^�ł�����ł��Ă��܂��̂ŃR���p�C���G���[�𖳗��������N�����R�[�h
				//�|�����[�t�B�b�N�ȓ��삪�\�Ȃ�Ζ��Ȃ��ʂ�
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
				//�d�l��ʂ̌^�ł�����ł��Ă��܂��̂ŃR���p�C���G���[�𖳗��������N�����R�[�h
				//�|�����[�t�B�b�N�ȓ��삪�\�Ȃ�Ζ��Ȃ��ʂ�
				_Type* t = ((_T*)(0));
#endif
			}

			/**

			*	@brief	allocator�ɂ��holder�m�ۏ����p�R���X�g���N�^

			*	@param[in]	ptr	�z���_�[�̃|�C���^

			*/
			template<class _T, class _A>
			explicit C_SharedPtr(Detail::C_ObjectAllocatorHolder< _T, _A> * ptr) : m_holder(GA_NULL){
				this->m_holder = ptr;
				this->m_holder->AddRef();
			}

			/**

			*	@brief	�R�s�[�R���X�g���N�^

			*	@param[in]	ref	�R�s�[��

			*/
			template<class _T>
			C_SharedPtr(const  C_SharedPtr<_T>& ref) : m_holder(GA_NULL){
				this->Assign(ref);
			}

			/**

			*	@brief	�R�s�[�R���X�g���N�^

			*	@param[in]	ref	�R�s�[��

			*/
			C_SharedPtr(const ThisType& ref) : m_holder(GA_NULL){
				this->Assign(ref);
			}


			/**

			*	@brief	�f�X�g���N�^

			*	@param	�Ȃ�
			*/
			~C_SharedPtr(){
				//�Q�ƃJ�E���g���f�N�������g�����l��0�Ȃ�Δj������
				if (this->m_holder){
					this->m_holder->DeclRef();
					if (this->m_holder->GetRefCount() == 0){
						this->m_holder->Destroy();
						this->m_holder = GA_NULL;
					}
				}
			}

			/**

			*	@brief	�R�s�[������Z�q

			*	@param[in] ref	�R�s�[��

			*	@return �Ȃ�

			*/
			template<class _T>
			void operator=(const  C_SharedPtr<_T>& ref) {
				this->Assign(ref);
			}

			/**

			*	@brief	�R�s�[������Z�q

			*	@param[in] ref	�R�s�[��

			*	@return �Ȃ�

			*/
			void operator=(const ThisType& ref){
				this->Assign(ref);
			}

			/**

			*	@brief	�|�C���^�̑�����Z�q
			�Ǘ����Ă���Q�Ƃ�j�����A�V�����Q�Ƃ𐶐�����

			*	@param	�Ȃ�

			*	@return	�Ȃ�

			*/
			template<class _T>
			void operator=(_T* ptr){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr);
			}

			/**

			*	@brief	bool�L���X�g���Z�q

			*	@param	�Ȃ�

			*	@return	�Ȃ�

			*/
			operator bool() const{
				return (this->m_holder != GA_NULL);
			}


			/**

			*	@brief	���Z�b�g�֐�
			����shared_ptr�̊Ǘ����Ă���I�u�W�F�N�g�̎Q�Ƃ�j������
			�j���������Ƃ�null�ŏ��������A�Ǘ��Ώۂ������Ȃ�

			*	@param	�Ȃ�

			*	@return�@�Ȃ�

			*/
			void Reset(){
				this->~C_SharedPtr();
				new(this) C_SharedPtr();
			}

			/**

			*	@brief	���Z�b�g�֐�
			����shared_ptr�̊Ǘ����Ă���I�u�W�F�N�g�̎Q�Ƃ�j����
			�V���ȃI�u�W�F�N�g�̊Ď����J�n����

			*	@param[in]	ptr	�V���ȊĎ��Ώۂ̃I�u�W�F�N�g�̃|�C���^

			*	@return	�Ȃ�

			*/
			template<class _T>
			void Reset(_T* ptr){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr);
			}

			/**

			*	@brief	���Z�b�g�֐�
			����shared_ptr�̊Ǘ����Ă���I�u�W�F�N�g�̎Q�Ƃ�j����
			�V���ȃI�u�W�F�N�g�̊Ď����J�n����

			*	@param[in]	ptr	�V���ȊĎ��Ώۂ̃I�u�W�F�N�g�̃|�C���^
			*	@param[in]	del	�V���ȃf���[�^

			*	@return	�Ȃ�

			*/
			template<class _T, class _Del>
			void Reset(_T* ptr, _Del del){
				this->~C_SharedPtr();
				new(this) C_SharedPtr(ptr, del);
			}
			/**

			*	@brief	�Ǘ����Ă���I�u�W�F�N�g�̃|�C���^���擾����

			*	@param	�Ȃ�

			*	@return	�I�u�W�F�N�g�̃|�C���^

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

			*	@brief	�A���[���Z�q

			*	@param	�Ȃ�

			*	@return	�I�u�W�F�N�g�̃|�C���^

			*/
			_Type*	operator->() const{ return this->Get(); }


			/**

			*	@brief	�R�s�[�p�̃z���_�[�擾�֐�

			*	@param	�Ȃ�

			*	@return	�z���_�[�̃|�C���^

			*/
			Detail::C_PtrDeleterHolderBase* _GetHolder() const { return this->m_holder; }

			Detail::C_PtrDeleterHolderBase* _GetHolder()  { return this->m_holder; }

		private:
			template<class _T>
			void Assign(const C_SharedPtr<_T>& ref){
#ifdef GA_LIB_DEBUG_MODE
				//�d�l��ʂ̌^�ł�����ł��Ă��܂��̂ŃR���p�C���G���[�𖳗��������N�����R�[�h
				//�|�����[�t�B�b�N�ȓ��삪�\�Ȃ�Ζ��Ȃ��ʂ�
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


