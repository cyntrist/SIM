// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2018 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  


#ifndef PHYSX_SNIPPET_RENDER_H
#define PHYSX_SNIPPET_RENDER_H

#include "PxPhysicsAPI.h"
#include "foundation/PxPreprocessor.h"

#if PX_WINDOWS
#include <windows.h>
#pragma warning(disable: 4505)
#include <glut.h>
#elif PX_LINUX_FAMILY
#include <GL/glut.h>
#elif PX_OSX
#include <GLUT/glut.h>
#else
#error platform not supported.
#endif
#include <string>

extern std::string display_text;
extern std::string level_won_1_text;
extern std::string level_won_2_text;
extern std::string controls_1_text;
extern std::string controls_2_text;
extern std::string controls_3_text;
extern std::string controls_4_text;
extern int sentido;
extern double hsvColor;
extern bool won;


namespace Snippets
{
	void setupDefaultWindow(const char* name);
	void setupDefaultRenderState();

	void startRender(const physx::PxVec3& cameraEye, const physx::PxVec3& cameraDir, physx::PxReal nearClip = 1.f,
	                 physx::PxReal farClip = 10000.f);
	void renderShape(const physx::PxShape& shape, const physx::PxTransform& transform, const physx::PxVec4& color);
	void renderActors(physx::PxRigidActor** actors, physx::PxU32 numActors, bool shadows = false,
	                  const physx::PxVec4& color = physx::PxVec4(0.0f, 0.75f, 0.0f, 1.0f));
	void finishRender();
	void drawText(const std::string& text, int x, int y);
}

#define MAX_NUM_ACTOR_SHAPES 128

#endif //PHYSX_SNIPPET_RENDER_H
