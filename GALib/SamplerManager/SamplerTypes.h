#pragma once


namespace GALib{
	namespace Draw{
		namespace SamplerManager{
			class C_ClampTypes{
			public:
				static const int CLAMP_CLAMP;
				static const int CLAMP_MIRROR;
				static const int CLAMP_WRAP;
			};


			class C_FilterTypes{
			public:
				static const int FILTER_POINT;
				static const int FILTER_BILINEAR;
			};
		}
	}
}