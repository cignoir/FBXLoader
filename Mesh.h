#pragma once
#include "common.h"

#include "Material.h"
#include "Vertex.h"

class C_Mesh;
class C_Meshes;
class C_ShapeMesh;
using MeshPtr = std::shared_ptr<C_Mesh>;
using MeshPtrArray = std::vector<MeshPtr>;
using MeshesPtr = std::shared_ptr<C_Meshes>;
using ShapeMeshPtr = std::shared_ptr<C_ShapeMesh>;
/**

*	@brief	シェイプ用メッシュをあらわすクラス
			インデックスなどは親であるC_Meshクラスに依存する

*/
class C_ShapeMesh {
public:
	void* GetVertexBufferPtr() { return this->m_vertices_buffer.data(); }
	template<class _VertexType>
	_VertexType GetVertex(int index) {
		auto data = this->m_vertices_buffer.data();
		auto v = (_VertexType*)data + index;
		return *v;
	}
	template<class _Vector>
	void CopyVertices(_Vector& vertices) {
		auto count = vertices.size();
		auto size = sizeof(_Vector::value_type);
		this->m_vertices_buffer.resize(size * count);
		std::memcpy(this->m_vertices_buffer.data(), vertices.data(), this->m_vertices_buffer.size());
	}

	void SetMeshName(const char* p_mesh_name) { this->m_mesh_name = std::string(p_mesh_name); }
	const char* GetMeshName() { return this->m_mesh_name.c_str(); }

	void SetVertexType(eVertexType type) { this->m_vertex_type = type; }
	eVertexType GetVertexType() { return this->m_vertex_type; }
	void SetWriteVertexType(eVertexType type) { this->m_write_vertex_type = type; }
	eVertexType GetWriteVertexType() { return this->m_write_vertex_type; }

	void CopyBufferToVertices(void* buffer, int size) {
		this->m_vertices_buffer.resize(size);
		std::memcpy(this->m_vertices_buffer.data(), buffer, size);
	}
	int GetVertexBufferSize() { return this->m_vertices_buffer.size(); }
private:
	std::string m_mesh_name;
	ByteArray	m_vertices_buffer;
	eVertexType m_vertex_type = eVertexType::TYPE_NONE;		//頂点タイプ
	eVertexType	m_write_vertex_type = eVertexType::TYPE_NONE;
};

/**

*	@brief	メッシュ情報をあらわすクラス
			頂点データは型が変わるためバイト配列で保持する
			型情報はC_Meshesがenumclassで保持、適宜キャストして使用する
*/
class C_Mesh {
public:

	void* GetVertexBufferPtr() { return this->m_vertices_buffer.data(); }
	void* GetIndexBufferPtr() { return this->m_indices_buffer.data(); }

	template<class _VertexType>
	_VertexType GetVertex(int index) {
		auto data = this->m_vertices.data();
		auto v = (_VertexType*)data + index;
		return *v;
	}
	int GetVertexCount() { return this->m_vertex_count; }
	int GetIndexCount() { return this->m_indices_buffer.size(); }
	void SetVertexCount(int count) { this->m_vertex_count = count; }
	template<class _Vector>
	void CopyVertices(_Vector& vertices) {
		this->m_vertex_count = vertices.size();
		auto size = sizeof(_Vector::value_type);
		this->m_vertices_buffer.resize(size * this->m_vertex_count);
		std::memcpy(this->m_vertices_buffer.data(), vertices.data(), this->m_vertices_buffer.size());
	}
	void CopyIndices(std::vector<unsigned short>& indices) { this->m_indices_buffer = indices; }

	void SetMeshName(const char* p_mesh_name) { this->m_mesh_name = std::string(p_mesh_name); }
	const char* GetMeshName() { return this->m_mesh_name.c_str(); }

	void SetMaterialIndex(int index) { this->m_material_index = index; }
	int GetMaterialIndex() { return this->m_material_index; }


	void SetVertexType(eVertexType type) { this->m_vertex_type = type; }
	eVertexType GetVertexType() { return this->m_vertex_type; }

	void CopyBufferToVertices(void* buffer, int size) {
		this->m_vertices_buffer.resize(size);
		std::memcpy(this->m_vertices_buffer.data(), buffer, size);
	}
	void CopyBufferToIndices(void* buffer, int size) {
		this->m_indices_buffer.resize(size / 2);
		std::memcpy(this->m_indices_buffer.data(), buffer, size);
	}

	void AddBlendShapeMesh(ShapeMeshPtr ptr) { this->m_blend_shape_meshes.push_back(ptr); }
	ShapeMeshPtr GetBlendShapeMesh(int index) { return this->m_blend_shape_meshes[index]; }
	int GetBlendShapeMeshCount() { return this->m_blend_shape_meshes.size(); }
	void ReserveBlendShapeMeshArray(int count) { this->m_blend_shape_meshes.reserve(count); }
	int GetVertexBufferSize() { return this->m_vertices_buffer.size(); }

private:
	std::string	m_mesh_name;		//メッシュの名前
	std::vector<ShapeMeshPtr>	m_blend_shape_meshes;
	ByteArray m_vertices_buffer;
	Indices m_indices_buffer;
	int m_vertex_count = 0;			//頂点数
	int m_material_index = -1;		//参照するマテリアルのインデックス
	eVertexType m_vertex_type = eVertexType::TYPE_NONE;		//頂点タイプ
};

/**

*	@brief	モデルデータ表すクラス
			マテルアル情報を保持する
			メッシュはここからマテリアルを参照する
*/
class C_Meshes {
public:

	void AddMesh(MeshPtr ptr) { this->m_mesh_ptr_array.push_back(ptr); }
	int GetMeshCount() { return this->m_mesh_ptr_array.size(); }
	MeshPtr GetMesh(int index) { return this->m_mesh_ptr_array[index]; }
	void ReserveMeshArray(int count) { this->m_mesh_ptr_array.reserve(count); }

	void AddMaterialPtr(MaterialPtr ptr) {
		ptr->SetMaterialIndex(this->m_material_ptr_array.size());
		this->m_material_ptr_array.push_back(ptr);
	}
	int FindMaterialIndex(const char* mat_name) {
		for (auto &it : this->m_material_ptr_array) {
			if (!strcmp(it->GetMaterialName(), mat_name)) {
				return it->GetMaterialIndex();
			}
		}

		return -1;
	}
	MaterialPtr GetMaterial(int index) {
		return this->m_material_ptr_array[index];
	}
	MaterialPtr GetMaterial(const char* name) {
		return this->m_material_ptr_array[this->FindMaterialIndex(name)];
	}
	int GetMaterialCount() { return this->m_material_ptr_array.size(); }
	void ReserveMaterialArray(int count) { this->m_material_ptr_array.reserve(count); }

private:
	MeshPtrArray m_mesh_ptr_array;
	MaterialPtrArray m_material_ptr_array;
};

