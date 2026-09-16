#include <assert.h>
#include "File.h"
#include "Model.h"
#include "ModelTools.h"
#include "d3dUtil.h"
#include "AzulFileHdr.h"
#include "MeshSeparator.h"
#include "../Finalsprint/Polliwog Engine/Visualizer.h"

#include "../Finalsprint/RenderAttorney.h"

Model::Model(StandardVertex *pVerts, int nverts, TriangleByIndex *ptlist, int ntri)
{
	assert(nverts > 0);
	assert(ntri > 0);

	mDevice = RenderAttorney::GetDevice();

	// Copy Data
	numVerts = nverts;
	pStdVerts = new StandardVertex[numVerts];
	for (int i = 0; i < numVerts; i++)
	{
		pStdVerts[i] = pVerts[i];
	}
	numTris = ntri;
	pTriList = new TriangleByIndex[numTris];
	for (int i = 0; i < numTris; i++)
	{
		pTriList[i] = ptlist[i];
	}

	privLoadDataToGPU();
}

Model::Model(const char * const _modelName)
{
	mDevice = RenderAttorney::GetDevice();
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	privLoadDataFromFile(_modelName, pStdVerts, numVerts, pTriList, numTris);
	privLoadDataToGPU();
}

Model::Model(Model::PreMadeModels pm)
{
	mDevice = RenderAttorney::GetDevice();
	pStdVerts = nullptr;
	pTriList = nullptr;
	numVerts = 0;
	numTris = 0;

	switch (pm)
	{
	case UnitBox:
		ModelTools::CreateUnitBox(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitBoxRepeatedTexture:
		ModelTools::CreateUnitBoxRepTexture(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitBoxSixFacesTexture:
		ModelTools::CreateUnitBoxSixFacesTexture(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitPyramid:
		ModelTools::CreateUnitPyramid(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitPyramidRepeatedTexture:
		ModelTools::CreateUnitPyramidRepTexture(pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitSphere:
		ModelTools::CreateUnitSphere(12, 12, pStdVerts, numVerts, pTriList, numTris);
		break;
	case UnitSphereRepeatedTexture:
		ModelTools::CreateUnitSphereRepTexture(200, 200, pStdVerts, numVerts, pTriList, numTris);
		break;
	default:
		assert(false && "Invalid option");
	}

	privLoadDataToGPU();
}



Model::~Model()
{
	delete[] pTriList;
	delete[] pStdVerts;

	delete meshes;
	delete[] VectList;
	delete AABBmax;
	delete AABBmin;
	delete center;

	ReleaseAndDeleteCOMobject(mpVertexBuffer);
	ReleaseAndDeleteCOMobject(mpIndexBuffer);
}

void Model::privLoadDataFromFile(const char * const _modelName, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& ptlist, int& ntri)
{
	// Read from file
	FileHandle fh;
	FileError  ferror;

	ferror = File::open(fh, _modelName, FILE_READ);
	assert(ferror == FILE_SUCCESS);

	// Get the file format for the data
	AzulFileHdr  azulFileHdr;

	// **** Overly complicated detour Part 1:  The vertex data in the file is packed efficiently
	// whereas our StandardVertex is not. Something I shall fix form the start next time.
	// For time time: we will read in the data into a temp array and then manually copy the data into
	// the StandardVertex array. 

	struct VertexStride_VUN
	{
		float x;    // Vert - V
		float y;
		float z;

		float u;    // UV tex coor - U
		float v;

		float txt;	// texture trickery 

		float nx;   // Norm verts - N
		float ny;
		float nz;

		float r;
		float g;
		float b;

		void set(float _x, float _y, float _z,
			float _u, float _v,
			float _nx, float _ny, float _nz,
			float _txt = 0,
			float _r = 1, float _g = 1, float _b = 1)
		{
			x = _x;
			y = _y;
			z = _z;
			u = _u;
			v = _v;
			nx = _nx;
			ny = _ny;
			nz = _nz;

			txt = _txt;
			r = _r;
			g = _g;
			b = _b;
		}

	};

	// ******************


	// Read the header
	ferror = File::read(fh, &azulFileHdr, sizeof(AzulFileHdr));
	assert(ferror == FILE_SUCCESS);

	// create the vertex buffer
	nverts = azulFileHdr.numVerts;
	VertexStride_VUN* pTmpVerts = new VertexStride_VUN[nverts];

	// load the verts
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.vertBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, pTmpVerts, nverts * sizeof(VertexStride_VUN));
	assert(ferror == FILE_SUCCESS);

	// create the triLists buffer
	ntri = azulFileHdr.numTriangles;
	ptlist = new TriangleByIndex[ntri];

	// load the triList
	// seek to the location
	ferror = File::seek(fh, FILE_SEEK_BEGIN, azulFileHdr.triangleListBufferOffset);
	assert(ferror == FILE_SUCCESS);

	// read it
	ferror = File::read(fh, ptlist, ntri * sizeof(TriangleByIndex));
	assert(ferror == FILE_SUCCESS);

	// close
	ferror = File::close(fh);
	assert(ferror == FILE_SUCCESS);

	// **** Overly complicated detour Part 2: now we copy the vertex data into our StandardVertex
	pVerts = new StandardVertex[nverts];
	StandardVertex* v;
	VertexStride_VUN* tmp;
	for (int i = 0; i < nverts; i++)
	{
		tmp = &(pTmpVerts[i]);
		v = &(pVerts[i]);
		v->set(tmp->x, tmp->y, tmp->z, tmp->u, tmp->v, tmp->nx, tmp->ny, tmp->nz, tmp->r, tmp->g, tmp->b, (int) tmp->txt);
	}

	delete[] pTmpVerts;
	// *************************

}

void  Model::privLoadDataToGPU()
{
	// Extract mesh information
	meshes = new MeshSeparator(pStdVerts, numVerts, pTriList, numTris);

	// Vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(StandardVertex) * numVerts;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = pStdVerts;
	HRESULT hr = mDevice->CreateBuffer(&bd, &InitData, &mpVertexBuffer);
	assert(SUCCEEDED(hr));

	// Index buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(TriangleByIndex) * numTris;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = pTriList;
	hr = mDevice->CreateBuffer(&bd, &InitData, &mpIndexBuffer);
	assert(SUCCEEDED(hr));

	//This should be a seperate method... doesn't belong here
	VectList = new Vect[numVerts];
	Vect max = pStdVerts[0].Pos;
	Vect min = pStdVerts[0].Pos;

	for (int x = 0; x < numVerts; x++)
	{
		VectList[x] = Vect(pStdVerts[x].Pos);

		Vect Curr = VectList[x];

		// X
		if (Curr.X() > max.X())
			max.X() = Curr.X();

		else if (Curr.X() < min.X())
			min.X() = Curr.X();

		// Y
		if (Curr.Y() > max.Y())
			max.Y() = Curr.Y();

		else if (Curr.Y() < min.Y())
			min.Y() = Curr.Y();

		// Z
		if (Curr.Z() > max.Z())
			max.Z() = Curr.Z();

		else if (Curr.Z() < min.Z())
			min.Z() = Curr.Z();


	}

	// Not gonna lie I had to look up how to find the center and radius for a BSphere
	// I kept trying to calculatie it using min and max values... which wasn't exactly working
	Vect testCenter;
	for (int x = 0; x < numVerts; x++)
	{
		Vect Curr = VectList[x];

		testCenter.X() += Curr.X();
		testCenter.Y() += Curr.Y();
		testCenter.Z() += Curr.Z();

	}

	testCenter.X() /= numVerts;
	testCenter.Y() /= numVerts;
	testCenter.Z() /= numVerts;

	float maxRadiusSq = 0.0f;
	for (int x = 0; x < numVerts; x++) 
	{
		Vect Curr = VectList[x];

		float dx = Curr.X() - testCenter.X();
		float dy = Curr.Y() - testCenter.Y();
		float dz = Curr.Z() - testCenter.Z();

		float distanceSq = (dx * dx) + (dy * dy) + (dz * dz);
		if (distanceSq > maxRadiusSq) {
			maxRadiusSq = distanceSq;
		}
	}

	AABBmax = new Vect();
	AABBmin = new Vect();
	center = new Vect();

	*AABBmax = max;
	*AABBmin = min;

	*center = testCenter;
	radius = std::sqrt(maxRadiusSq);

}

bool Model::ValidMeshNum(int meshnum)
{
	return (meshnum >= 0) && (meshnum < GetMeshCount());
}

int Model::GetMeshCount()
{
	return meshes->GetMeshCount();
}

void Model::SetToContext()
{
	UINT stride = sizeof(StandardVertex);
	UINT offset = 0;
	RenderAttorney::GetContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	RenderAttorney::GetContext()->IASetIndexBuffer(mpIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	RenderAttorney::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Model::Render()
{
	RenderAttorney::GetContext()->DrawIndexed(numTris * 3, 0, 0);
}

void Model::RenderMesh(int meshnum)
{
	assert(ValidMeshNum(meshnum));

	int tricount, trioffset;
	meshes->GetMeshTriCountAndOffset(meshnum, tricount, trioffset);

	RenderAttorney::GetContext()->DrawIndexed(tricount * 3, trioffset * 3, 0);
}


Vect& Model::getCenter() const
{
	return *center;
}
float Model::getRadius() const
{
	return radius;
}

Vect* Model::getVectList(void) const
{
	return VectList;
}

int Model::getVectNum() const
{
	return numVerts;
}

Vect& Model::getMinAABB() const
{
	return *AABBmin;
}

Vect& Model::getMaxAABB() const
{
	return *AABBmax;
}


