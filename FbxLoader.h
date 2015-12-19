#pragma once
#include "common.h"
#include "Skeleton.h"
#include "Mesh.h"

namespace Fbx {
	using MeshesAndSkeleton = std::pair<MeshesPtr, SkeletonPtr>;
	using AnimationSkeltonList = std::list<std::pair<std::string, SkeletonPtr>>;

	MeshesAndSkeleton LoadMeshesAndSkeleton(const char* file_path);
	AnimationSkeltonList LoadAnimation(const char* file_path,SkeletonPtr p_base_skeleton);
	SkeletonPtr LoadSkeleton(const char* file_path);

};