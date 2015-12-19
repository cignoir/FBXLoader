

struct S_VertexOut {
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD;
	float3 normal : NORMAL;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;


};

Texture2D tex : register(t0);
SamplerState sam : register(s0);
float4 main(S_VertexOut IN) : SV_TARGET
{
	//return float4(1,1,1,1);
	//return float4(IN.bone_weight.xy,(float)IN.bone_index.x / 3,1.0f);
	//return float4(IN.bone_weight.xyz,1);
	IN.uv.y = 1 - IN.uv.y;
	return tex.Sample(sam,IN.uv);
	//return  float4(IN.uv,1,1);
}