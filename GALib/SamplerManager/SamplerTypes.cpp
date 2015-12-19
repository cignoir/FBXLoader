#include "SamplerTypes.h"
#include "../D3D11/D3D11Manager.h"


using namespace GALib::Draw::SamplerManager;

const int C_ClampTypes::CLAMP_CLAMP = D3D11_TEXTURE_ADDRESS_CLAMP;
const int C_ClampTypes::CLAMP_MIRROR = D3D11_TEXTURE_ADDRESS_MIRROR;
const int C_ClampTypes::CLAMP_WRAP = D3D11_TEXTURE_ADDRESS_WRAP;

const int C_FilterTypes::FILTER_BILINEAR = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
const int C_FilterTypes::FILTER_POINT = D3D11_FILTER_MIN_MAG_MIP_POINT;


