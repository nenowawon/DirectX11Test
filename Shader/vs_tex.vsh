struct VS_IN
{
	float4 pos : POSITION0;
	float4 col : COLOR0;
	float2 tex : TEXCOORD0;
};

struct VS_OUT
{
	float4 pos  : SV_POSITION;
	float2 tex  : TEXCOORD0;
};

cbuffer ConstantBuffer
{
	float4x4 world;         //ワールド変換行列
	float4x4 view;          //ビュー変換行列
	float4x4 projection;    //透視射影変換行列
}

VS_OUT vs_main(VS_IN input)
{
	VS_OUT output;

	output.pos = mul(input.pos, world);
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);

	output.tex = input.tex;

	return output;
}