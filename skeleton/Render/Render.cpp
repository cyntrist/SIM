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

#include "Render.h"
#include <assert.h>
#include <../../../../skeleton/Global.h>

using namespace physx;

static float gCylinderData[] = {
	1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.866025f, 0.500000f, 1.0f, 0.866025f, 0.500000f, 1.0f, 0.866025f, 0.500000f, 0.0f, 0.866025f, 0.500000f, 0.0f,
	0.500000f, 0.866025f, 1.0f, 0.500000f, 0.866025f, 1.0f, 0.500000f, 0.866025f, 0.0f, 0.500000f, 0.866025f, 0.0f,
	-0.0f, 1.0f, 1.0f, -0.0f, 1.0f, 1.0f, -0.0f, 1.0f, 0.0f, -0.0f, 1.0f, 0.0f,
	-0.500000f, 0.866025f, 1.0f, -0.500000f, 0.866025f, 1.0f, -0.500000f, 0.866025f, 0.0f, -0.500000f, 0.866025f, 0.0f,
	-0.866025f, 0.500000f, 1.0f, -0.866025f, 0.500000f, 1.0f, -0.866025f, 0.500000f, 0.0f, -0.866025f, 0.500000f, 0.0f,
	-1.0f, -0.0f, 1.0f, -1.0f, -0.0f, 1.0f, -1.0f, -0.0f, 0.0f, -1.0f, -0.0f, 0.0f,
	-0.866025f, -0.500000f, 1.0f, -0.866025f, -0.500000f, 1.0f, -0.866025f, -0.500000f, 0.0f, -0.866025f, -0.500000f,
	0.0f,
	-0.500000f, -0.866025f, 1.0f, -0.500000f, -0.866025f, 1.0f, -0.500000f, -0.866025f, 0.0f, -0.500000f, -0.866025f,
	0.0f,
	0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	0.500000f, -0.866025f, 1.0f, 0.500000f, -0.866025f, 1.0f, 0.500000f, -0.866025f, 0.0f, 0.500000f, -0.866025f, 0.0f,
	0.866026f, -0.500000f, 1.0f, 0.866026f, -0.500000f, 1.0f, 0.866026f, -0.500000f, 0.0f, 0.866026f, -0.500000f, 0.0f,
	1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
};

#define MAX_NUM_MESH_VEC3S  1024
static PxVec3 gVertexBuffer[MAX_NUM_MESH_VEC3S];

void renderGeometry(const PxGeometryHolder& h, bool wireframe = false)
{
	auto geoType = h.getType();
	switch (geoType)
	{
	case PxGeometryType::eBOX:
		{
			glScalef(h.box().halfExtents.x, h.box().halfExtents.y, h.box().halfExtents.z);
			glutSolidCube(2.0);
		}
		break;
	case PxGeometryType::eSPHERE:
		{
			if (wireframe)
				glutWireSphere(h.sphere().radius, 10, 10);
			else
				glutSolidSphere(h.sphere().radius, 10, 10);
		}
		break;
	case PxGeometryType::eCAPSULE:
		{
			const PxF32 radius = h.capsule().radius;
			const PxF32 halfHeight = h.capsule().halfHeight;

			//Sphere
			glPushMatrix();
			glTranslatef(halfHeight, 0.0f, 0.0f);
			glScalef(radius, radius, radius);
			glutSolidSphere(1, 10, 10);
			glPopMatrix();

			//Sphere
			glPushMatrix();
			glTranslatef(-halfHeight, 0.0f, 0.0f);
			glScalef(radius, radius, radius);
			glutSolidSphere(1, 10, 10);
			glPopMatrix();

			//Cylinder
			glPushMatrix();
			glTranslatef(-halfHeight, 0.0f, 0.0f);
			glScalef(2.0f * halfHeight, radius, radius);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glVertexPointer(3, GL_FLOAT, 2 * 3 * sizeof(float), gCylinderData);
			glNormalPointer(GL_FLOAT, 2 * 3 * sizeof(float), gCylinderData + 3);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 13 * 2);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glPopMatrix();
		}
		break;
	case PxGeometryType::eCONVEXMESH:
		{
			//Compute triangles for each polygon.
			const PxVec3 scale = h.convexMesh().scale.scale;
			PxConvexMesh* mesh = h.convexMesh().convexMesh;
			const PxU32 nbPolys = mesh->getNbPolygons();
			const PxU8* polygons = mesh->getIndexBuffer();
			const PxVec3* verts = mesh->getVertices();
			PxU32 nbVerts = mesh->getNbVertices();
			PX_UNUSED(nbVerts);

			PxU32 numTotalTriangles = 0;
			for (PxU32 i = 0; i < nbPolys; i++)
			{
				PxHullPolygon data;
				mesh->getPolygonData(i, data);

				const PxU32 nbTris = data.mNbVerts - 2;
				const PxU8 vref0 = polygons[data.mIndexBase + 0];
				PX_ASSERT(vref0 < nbVerts);
				for (PxU32 j = 0; j < nbTris; j++)
				{
					const PxU32 vref1 = polygons[data.mIndexBase + 0 + j + 1];
					const PxU32 vref2 = polygons[data.mIndexBase + 0 + j + 2];

					//generate face normal:
					PxVec3 e0 = verts[vref1] - verts[vref0];
					PxVec3 e1 = verts[vref2] - verts[vref0];

					PX_ASSERT(vref1 < nbVerts);
					PX_ASSERT(vref2 < nbVerts);

					PxVec3 fnormal = e0.cross(e1);
					fnormal.normalize();

					if (numTotalTriangles * 6 < MAX_NUM_MESH_VEC3S)
					{
						gVertexBuffer[numTotalTriangles * 6 + 0] = fnormal;
						gVertexBuffer[numTotalTriangles * 6 + 1] = verts[vref0];
						gVertexBuffer[numTotalTriangles * 6 + 2] = fnormal;
						gVertexBuffer[numTotalTriangles * 6 + 3] = verts[vref1];
						gVertexBuffer[numTotalTriangles * 6 + 4] = fnormal;
						gVertexBuffer[numTotalTriangles * 6 + 5] = verts[vref2];
						numTotalTriangles++;
					}
				}
			}
			glPushMatrix();
			glScalef(scale.x, scale.y, scale.z);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glNormalPointer(GL_FLOAT, 2 * 3 * sizeof(float), gVertexBuffer);
			glVertexPointer(3, GL_FLOAT, 2 * 3 * sizeof(float), gVertexBuffer + 1);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(numTotalTriangles * 3));
			glPopMatrix();
		}
		break;
	case PxGeometryType::eTRIANGLEMESH:
		{
			const PxTriangleMeshGeometry& triGeom = h.triangleMesh();
			const PxTriangleMesh& mesh = *triGeom.triangleMesh;
			const PxVec3 scale = triGeom.scale.scale;

			const PxU32 triangleCount = mesh.getNbTriangles();
			const PxU32 has16BitIndices = mesh.getTriangleMeshFlags() & PxTriangleMeshFlag::e16_BIT_INDICES;
			const void* indexBuffer = mesh.getTriangles();

			const PxVec3* vertexBuffer = mesh.getVertices();

			auto intIndices = reinterpret_cast<const PxU32*>(indexBuffer);
			auto shortIndices = reinterpret_cast<const PxU16*>(indexBuffer);
			PxU32 numTotalTriangles = 0;
			for (PxU32 i = 0; i < triangleCount; ++i)
			{
				PxVec3 triVert[3];

				if (has16BitIndices)
				{
					triVert[0] = vertexBuffer[*shortIndices++];
					triVert[1] = vertexBuffer[*shortIndices++];
					triVert[2] = vertexBuffer[*shortIndices++];
				}
				else
				{
					triVert[0] = vertexBuffer[*intIndices++];
					triVert[1] = vertexBuffer[*intIndices++];
					triVert[2] = vertexBuffer[*intIndices++];
				}

				PxVec3 fnormal = (triVert[1] - triVert[0]).cross(triVert[2] - triVert[0]);
				fnormal.normalize();

				if (numTotalTriangles * 6 < MAX_NUM_MESH_VEC3S)
				{
					gVertexBuffer[numTotalTriangles * 6 + 0] = fnormal;
					gVertexBuffer[numTotalTriangles * 6 + 1] = triVert[0];
					gVertexBuffer[numTotalTriangles * 6 + 2] = fnormal;
					gVertexBuffer[numTotalTriangles * 6 + 3] = triVert[1];
					gVertexBuffer[numTotalTriangles * 6 + 4] = fnormal;
					gVertexBuffer[numTotalTriangles * 6 + 5] = triVert[2];
					numTotalTriangles++;
				}
			}
			glPushMatrix();
			glScalef(scale.x, scale.y, scale.z);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_VERTEX_ARRAY);
			glNormalPointer(GL_FLOAT, 2 * 3 * sizeof(float), gVertexBuffer);
			glVertexPointer(3, GL_FLOAT, 2 * 3 * sizeof(float), gVertexBuffer + 1);
			glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(numTotalTriangles * 3));
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glPopMatrix();
		}
		break;
	case PxGeometryType::eINVALID:
	case PxGeometryType::eHEIGHTFIELD:
	case PxGeometryType::eGEOMETRY_COUNT:
	case PxGeometryType::ePLANE:
		break;
	}
}

namespace Snippets
{
	namespace
	{
		void reshapeCallback(int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}

	void setupDefaultWindow(const char* name)
	{
		auto namestr = new char[strlen(name) + 1];
		strcpy(namestr, name);
		int argc = 1;
		char* argv[1] = {namestr};

		glutInit(&argc, argv);

		glutInitWindowSize(1280, 720);
		//glutInitWindowSize(512, 512);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		int mainHandle = glutCreateWindow(name);

		//SetWindowLong(
		//	(HWND)mainHandle, 
		//	GWL_STYLE, 
		//	GetWindowLong((HWND)mainHandle, GWL_STYLE) | WS_MAXIMIZE
		//);
		//ShowWindowAsync((HWND)mainHandle, SW_SHOWMAXIMIZED);

		glutSetWindow(mainHandle);
		glutReshapeFunc(reshapeCallback);

		delete[] namestr;
	}

	void setupDefaultRenderState()
	{
		// Setup default render states
		glClearColor(0.0f, 0.0f, 0.0f, 1.0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		//glEnable(GL_BLEND);

		// Setup lighting
		glEnable(GL_LIGHTING);
		PxReal ambientColor[] = {0.0f, 0.1f, 0.2f, 0.0f};
		PxReal diffuseColor[] = {1.0f, 1.0f, 1.0f, 0.0f};
		PxReal specularColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
		PxReal position[] = {100.0f, 100.0f, 400.0f, 1.0f};
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glEnable(GL_LIGHT0);
	}


	void startRender(const PxVec3& cameraEye, const PxVec3& cameraDir, PxReal clipNear, PxReal clipFar)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Display text
		//glColor4f(1.0f, 0.2f, 0.2f, 1.0f);
		Vector4 color = { 1.0f, 1.0f, 0.0f, 1.0f };
		if (won)
		{
			if (hsvColor >= 360)
				sentido = -1;
			if (hsvColor <= 0)
				sentido = 1;
			hsvColor = hsvColor + 0.25 * sentido;
			color = hsvToRgb(hsvColor);
		}

		glColor4f(color.x, color.y, color.z, color.w);
		drawText(display_text, 10, 10);
		drawText(controls_1_text, 10, 500 - 10);
		drawText(controls_2_text, 10, 500 - 25);
		drawText(controls_3_text, 10, 500 - 40);
		drawText(controls_4_text, 10, 500 - 55);
		drawText(level_won_1_text, 230, 250);
		drawText(level_won_2_text, 212, 230);

		// Setup camera
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(
			60.0, static_cast<GLdouble>(glutGet(GLUT_WINDOW_WIDTH)) / static_cast<GLdouble>(
				glutGet(GLUT_WINDOW_HEIGHT)), clipNear, clipFar);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(cameraEye.x, cameraEye.y,
		          cameraEye.z, cameraEye.x + cameraDir.x,
		          cameraEye.y + cameraDir.y, cameraEye.z + cameraDir.z,
		          0.0, 1.0, 0.0);

		glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

		assert(glGetError() == GL_NO_ERROR);
	}

	void renderShape(const PxShape& shape, const PxTransform& transform, const PxVec4& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		PxGeometryHolder h = shape.getGeometry();

		if (shape.getFlags() & PxShapeFlag::eTRIGGER_SHAPE)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// render object
		glPushMatrix();
		PxMat44 mtx(transform);
		glMultMatrixf(reinterpret_cast<const float*>(&mtx));
		assert(glGetError() == GL_NO_ERROR);
		glColor4f(color.x, color.y, color.z, color.w);
		assert(glGetError() == GL_NO_ERROR);
		renderGeometry(h, color.w < 0.5);
		assert(glGetError() == GL_NO_ERROR);
		glPopMatrix();
		assert(glGetError() == GL_NO_ERROR);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		assert(glGetError() == GL_NO_ERROR);

		glDisable(GL_BLEND);
	}

	void renderActors(PxRigidActor** actors, const PxU32 numActors, bool shadows, const PxVec4& color)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		PxShape* shapes[MAX_NUM_ACTOR_SHAPES];
		for (PxU32 i = 0; i < numActors; i++)
		{
			const PxU32 nbShapes = actors[i]->getNbShapes();
			PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);
			actors[i]->getShapes(shapes, nbShapes);
			bool sleeping = actors[i]->is<PxRigidDynamic>() ? actors[i]->is<PxRigidDynamic>()->isSleeping() : false;

			for (PxU32 j = 0; j < nbShapes; j++)
			{
				const PxMat44 shapePose(PxShapeExt::getGlobalPose(*shapes[j], *actors[i]));
				PxGeometryHolder h = shapes[j]->getGeometry();

				if (shapes[j]->getFlags() & PxShapeFlag::eTRIGGER_SHAPE)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

				// render object
				glPushMatrix();
				glMultMatrixf(reinterpret_cast<const float*>(&shapePose));
				if (sleeping)
				{
					PxVec4 darkColor = color * 0.25f;
					glColor4f(darkColor.x, darkColor.y, darkColor.z, 1.0f);
				}
				else
					glColor4f(color.x, color.y, color.z, 1.0f);
				renderGeometry(h, color.w < 0.999f);
				glPopMatrix();

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				if (shadows)
				{
					const PxVec3 shadowDir(0.0f, -0.7071067f, -0.7071067f);
					const PxReal shadowMat[] = {
						1, 0, 0, 0, -shadowDir.x / shadowDir.y, 0, -shadowDir.z / shadowDir.y, 0, 0, 0, 1, 0, 0, 0, 0, 1
					};
					glPushMatrix();
					glMultMatrixf(shadowMat);
					glMultMatrixf(reinterpret_cast<const float*>(&shapePose));
					glDisable(GL_LIGHTING);
					glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
					renderGeometry(h);
					glEnable(GL_LIGHTING);
					glPopMatrix();
				}
			}
		}

		glDisable(GL_BLEND);
	}

	void finishRender()
	{
		glutSwapBuffers();
	}

	void drawText(const std::string& text, int x, int y)
	{
		glMatrixMode(GL_PROJECTION);
		auto matrix = new double[16];
		glGetDoublev(GL_PROJECTION_MATRIX, matrix);
		glLoadIdentity();
		glOrtho(0, 512, 0, 512, -5, 5);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		//glLoadIdentity();
		glRasterPos2i(x, y);

		int length = text.length();

		for (int i = 0; i < length; i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
			//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
			//glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
		}
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(matrix);
		glMatrixMode(GL_MODELVIEW);
	}
} //namespace Snippets
