

struct S_VertexIn {
	float3 pos : POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	//float3 binormal : BINORMAL;
	//float3 tangent : TANGENT;
	uint4 bone_index:BONE_INDEX;
	float4 bone_weight:BONE_WEIGHT;

};

struct S_VertexOut {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;

};




cbuffer Matrix : register(b0)
{
	float4x4 m_world_matrix;
	float4x4 m_view_matrix;
	float4x4 m_projection_matrix;
	float4x4 m_normal_matrix;
};

cbuffer CB0 : register(b1)
{
	float4x4 InverseBoneMatrix[2] :  packoffset(c0);
	float4x4 InverseBoneMatrixEnd :  packoffset(c1024);
}

cbuffer CB1 : register(b2)
{
	float4x4 PoseBoneMatrix[2] :  packoffset(c0);
	float4x4 PoseBoneMatrixEnd : packoffset(c1024);
}
//cbuffer CB0 : register(b1)
//{
//	float4x4 InverseBoneMatrix[256];
//}
//
//cbuffer CB1 : register(b2)
//{
//	float4x4 PoseBoneMatrix[256];
//}

float4x4 GetBoneMatrix(uint index) {
	//return PoseBoneMatrix[index];
	//return mul(InverseBoneMatrix[index], PoseBoneMatrix[index]);
	return mul(PoseBoneMatrix[index], InverseBoneMatrix[index]);
}
S_VertexOut main(S_VertexIn IN)
{

	float4x4 mat1 = mul(GetBoneMatrix(IN.bone_index.x), IN.bone_weight.x);
	float4x4 mat2 = mul(GetBoneMatrix(IN.bone_index.y), IN.bone_weight.y);
	float4x4 mat3 = mul(GetBoneMatrix(IN.bone_index.z), IN.bone_weight.z);
	float4x4 mat4 = mul(GetBoneMatrix(IN.bone_index.w), IN.bone_weight.w);



	float4x4 mat = mat1 + mat2 + mat3 + mat4;
	 //mat[0] = float4(1, 0, 0, 0);
	 //mat[1] = float4(0, 1, 0, 0);
	 //mat[2] = float4(0, 0, 1, 0);
	 //mat[3] = float4(0, 0, 0, 1);

	float4 out_pos = mul(float4(IN.pos, 1.0f), m_world_matrix);
	//out_pos = float4(IN.shape_pos, 1.0f);
	//out_pos = mul(out_pos, mat);
	out_pos = mul(mat, out_pos);

	out_pos = mul(out_pos,              m_view_matrix);
	out_pos = mul(out_pos,              m_projection_matrix);

	S_VertexOut Out;
	Out.pos = out_pos;
	Out.uv = IN.uv;
	Out.normal = IN.normal;
	//Out.binormal = IN.binormal;
	//Out.tangent = IN.tangent;


	return Out;
}