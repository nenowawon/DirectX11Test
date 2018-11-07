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
	float4x4 world;         //���[���h�ϊ��s��
	float4x4 view;          //�r���[�ϊ��s��
	float4x4 projection;    //�����ˉe�ϊ��s��
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