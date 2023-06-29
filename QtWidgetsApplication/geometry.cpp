#include "geometry.h"
//#include <GL/glu.h>


Geometry::Geometry()
{

}

Geometry::~Geometry()
{

}

void Geometry::prepareTriangle(const int &w, const int &h)
{
	mesh = false;
	width = w;
	height = h;

	//去除离群点
	auto tempMasks = masks;
	for (int j = 1; j < h - 1; ++j)
		for (int i = 1; i < w - 1; ++i)
		{
			if (masks[j * w + i] == 0)
			{
				int index = 0;
				for (int y = -1; y <= 1; ++y)
					for (int x = -1; x <= 1; ++x)
					{
						index = (j + y) * w + i + x;
						if (masks[index] == 0 &&
							fabs(points[index].z - points[j * w + i].z) > 1.0f)
							tempMasks[j * w + i] = 5;
					}
			}

		}
	//masks.swap(tempMasks);

	triangles.resize((w - 1) * (h - 1) * 2);
	int count = 0;
	//根据图像邻域关系生成三角网格索引
	for (int j = 0; j < h - 1; ++j)
		for (int i = 0; i < w - 1; ++i)
			if (tempMasks[j * w + i] + tempMasks[j * w + i + 1] +
				tempMasks[(j + 1) * w + i] + tempMasks[(j + 1) * w + i + 1] == 0)
			{
				triangles[count].x = j * w + i;
				triangles[count].y = j * w + i + 1;
				triangles[count].z = (j + 1) * w + i;
				++count;
				triangles[count].x = j * w + i + 1;
				triangles[count].y = (j + 1) * w + i + 1;
				triangles[count].z = (j + 1) * w + i;
				++count;


			}
	triangles.resize(count);
}

void Geometry::prepare(const int &w, const int &h, const bool &_mesh)
{
	mesh = _mesh;

	width = w;
	height = h;

	//计算包围盒 较耗时
	//computeBound();

	//if (!mesh)
	//{
	//	//去除离群点
	//	auto tempMasks = masks;
	//	for (int j = 1; j < h - 1; ++j)
	//		for (int i = 1; i < w - 1; ++i)
	//		{
	//			if (masks[j * w + i] == 0)
	//			{
	//				int index = 0;
	//				for (int y = -1; y <= 1; ++y)
	//					for (int x = -1; x <= 1; ++x)
	//					{
	//						index = (j + y) * w + i + x;
	//						if (masks[index] == 0 &&
	//							fabs(points[index].z - points[j * w + i].z) > 1.0f)
	//							tempMasks[j * w + i] = 5;
	//					}
	//			}

	//		}
	//	//masks.swap(tempMasks);

	//	triangles.resize((w - 1) * (h - 1) * 2);
	//	int count = 0;
	//	//根据图像邻域关系生成三角网格索引
	//	for (int j = 0; j < h - 1; ++j)
	//		for (int i = 0; i < w - 1; ++i)
	//			if (tempMasks[j * w + i] + tempMasks[j * w + i + 1] +
	//				tempMasks[(j + 1) * w + i] + tempMasks[(j + 1) * w + i + 1] == 0)
	//			{
	//				triangles[count].x = j * w + i;
	//				triangles[count].y = j * w + i + 1;
	//				triangles[count].z = (j + 1) * w + i;
	//				++count;
	//				triangles[count].x = j * w + i + 1;
	//				triangles[count].y = (j + 1) * w + i + 1;
	//				triangles[count].z = (j + 1) * w + i;
	//				++count;

	//			
	//			}
	//	triangles.resize(count);
	//}
	
	//TODO：计算法线 耗时 光照用
	//computeNormals();
	//TODO：每个VBO的作用
	//生成顶点VBO
	glDeleteBuffers(1, &pointsBuffer);
	glGenBuffers(1, &pointsBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), 
		&points[0], GL_STATIC_DRAW);

	//生成法线VBO
	glDeleteBuffers(1, &normalsBuffer);
	if (!normals.empty())
	{
		glGenBuffers(1, &normalsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
			&normals[0], GL_STATIC_DRAW);
	}

	//生成三角形索引VBO
	if (trianglesBuffer)
	{
	//delete两次非零的就会无法生成（有效-无效-有效）
		glDeleteBuffers(1, &trianglesBuffer);
		trianglesBuffer = 0;
	}
	
	if (!triangles.empty())
	{
		glGenBuffers(1, &trianglesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, trianglesBuffer);
		glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(glm::ivec3),
			&triangles[0], GL_STATIC_DRAW);
	}

	//生成灰度VBO
	glDeleteBuffers(1, &graysBuffer);
	if (!grays.empty())
	{
		glGenBuffers(1, &graysBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, graysBuffer);
		glBufferData(GL_ARRAY_BUFFER, grays.size(),
			&grays[0], GL_STATIC_DRAW);
	}

	//生成掩模VBO
	glDeleteBuffers(1, &masksBuffer);
	if (!masks.empty())
	{
		glGenBuffers(1, &masksBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, masksBuffer);
		glBufferData(GL_ARRAY_BUFFER, masks.size(),
			&masks[0], GL_STATIC_DRAW);
	}

	//生成索引VBO
	glDeleteBuffers(1, &indicesBuffer);
	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, indicesBuffer);
	std::vector<float> indices(points.size());
	for (int i = 0; i < indices.size(); ++i)
		indices[i] = i + 1;
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(float),
		&indices[0], GL_STATIC_DRAW);
}

std::vector<glm::vec3> &Geometry::getPoints()
{
	return points;
}

std::vector<glm::vec3> &Geometry::getNormals()
{
	return normals;
}

std::vector<glm::ivec3> &Geometry::getTriangles()
{
	return triangles;
}

std::vector<unsigned char> &Geometry::getGrays()
{
	return grays;
}

std::vector<unsigned char> &Geometry::getMasks()
{
	return masks;
}

void Geometry::draw(const GLuint &shader, const bool &lighting,
	const bool &drawPoints)
{
	if (points.empty())
		return;

	//绑定顶点VBO
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, 0);

	if (lighting && !normals.empty())
	{
		//绑定法线VBO
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		//glEnableClientState(GL_NORMAL_ARRAY);
		//glNormalPointer(GL_FLOAT, 0, 0);
	}

	if (!grays.empty())
	{
		//绑定灰度VBO
		glBindBuffer(GL_ARRAY_BUFFER, graysBuffer);
		glEnableVertexAttribArray(glGetAttribLocation(shader, "gray"));
		glVertexAttribPointer(glGetAttribLocation(shader, "gray"), 
			1, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
	}

	if (!masks.empty())
	{
		//绑定掩模VBO
		glBindBuffer(GL_ARRAY_BUFFER, masksBuffer);
		glEnableVertexAttribArray(glGetAttribLocation(shader, "mask"));
		glVertexAttribPointer(glGetAttribLocation(shader, "mask"),
			1, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
	}

	glUniform1i(glGetUniformLocation(shader, "mesh"), mesh);
	if (drawPoints)
		//绘制点
		glDrawArrays(GL_POINTS, 0, points.size());
	else
	{
		//绑定三角形索引VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, trianglesBuffer);
		//绘制三角形
		glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);
	}

//	glDisableClientState(GL_VERTEX_ARRAY);
	if (lighting && !normals.empty())
		//glDisableClientState(GL_NORMAL_ARRAY);
	if (!grays.empty())
		glDisableVertexAttribArray(glGetAttribLocation(shader, "gray"));
	if (!masks.empty())
		glDisableVertexAttribArray(glGetAttribLocation(shader, "mask"));
}

void Geometry::drawIndices(const GLuint &shader)
{
	if (points.empty())
		return;

	//绑定顶点VBO
	glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, 0);

	if (!masks.empty())
	{
		//绑定掩模VBO
		glBindBuffer(GL_ARRAY_BUFFER, masksBuffer);
		glEnableVertexAttribArray(glGetAttribLocation(shader, "mask"));
		glVertexAttribPointer(glGetAttribLocation(shader, "mask"),
			1, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
	}

	//绑定索引VBO
	glBindBuffer(GL_ARRAY_BUFFER, indicesBuffer);
	glEnableVertexAttribArray(glGetAttribLocation(shader, "index"));
	glVertexAttribPointer(glGetAttribLocation(shader, "index"),
		1, GL_FLOAT, 0, 0, 0);

	glUniform1i(glGetUniformLocation(shader, "mesh"), mesh);

	//绘制点
	glDrawArrays(GL_POINTS, 0, points.size());

	//glDisableClientState(GL_VERTEX_ARRAY);
	if (!masks.empty())
		glDisableVertexAttribArray(glGetAttribLocation(shader, "mask"));
	glDisableVertexAttribArray(glGetAttribLocation(shader, "index"));
}

//计算包围盒
void Geometry::computeBound()
{
	minPoint = glm::vec3(FLT_MAX);
	maxPoint = -minPoint;
	int iNumPoints = points.size();
	pointsZ = new float[iNumPoints];
	int iPointCnt = 0;

//#pragma omp parallel for   //cpu并行计算
	for (int i = 0; i < iNumPoints; ++i)
	{
		if (mesh)
		{		
			minPoint = glm::min(minPoint, points[i]);
			maxPoint = glm::max(maxPoint, points[i]);
		}
		else if (masks[i] == 0)
		{
			pointsZ[iPointCnt] = points[i].z;
			minPoint = glm::min(minPoint, points[i]);
			maxPoint = glm::max(maxPoint, points[i]);
			iPointCnt++;
		}
	}
	//固定包围盒
	/*if (mesh)
	{
		range = maxPoint - minPoint;
		center = minPoint + 0.5f * range;
	}
	else
	{
		range.x = 38.0f;
		range.y = 50.0f;
		range.z = 20.0f;
		center.x = 16.5f;
		center.y = 23.0f;
		center.z = 10.0f;
	}*/
	if (mesh)
	{
		range = maxPoint - minPoint;
		center = minPoint + 0.5f * range;
		m_fColorSpectrumRangeMinVal = minPoint.z;
		m_fColorSpectrumRangeMaxVal = maxPoint.z;
	}
	else
	{
		std::sort(pointsZ, pointsZ + iPointCnt);
		int MinIdx = (int)floor(((float)(iPointCnt - 1)) * 0.002f);//返回一个小于传入参数的最大整数
		int MaxIdx = (int)floor(((float)(iPointCnt - 1)) * 0.998f);
		if ((MinIdx < 0) || (MaxIdx > iPointCnt - 1) || (MinIdx > MaxIdx))
		{
			return;
		}

		float MinMax = pointsZ[MaxIdx] - pointsZ[MinIdx];
		m_fColorSpectrumRangeMinVal = pointsZ[MinIdx] - MinMax * 0.05;
		m_fColorSpectrumRangeMaxVal = pointsZ[MaxIdx] + MinMax * 0.05;

		maxPoint.z = pointsZ[MaxIdx];
		minPoint.z = pointsZ[MinIdx];
		range = maxPoint - minPoint;
		center = minPoint + 0.5f * range;
	}

	if (pointsZ != NULL)
	{
		delete[] pointsZ;
		pointsZ = NULL;
	}
}

const glm::vec3 &Geometry::getRange() const
{
	return range;
}

const glm::vec3 &Geometry::getCenter() const
{
	return center;
}

int Geometry::getWidth() const
{
	return width;
}

int Geometry::getHeight() const
{
	return height;
}

float Geometry::getm_fColorSpectrumRangeMaxVal()
{
	return m_fColorSpectrumRangeMaxVal;
}

float Geometry::getm_fColorSpectrumRangeMinVal()
{
	return m_fColorSpectrumRangeMinVal;
}

bool Geometry::isMesh() const
{
	return mesh;
}

void Geometry::computeNormals()
{
	glm::vec3 zero;
	normals.assign(points.size(), zero);
	//计算网格顶点法线
	for (int i = 0; i < triangles.size(); ++i)
	{
		glm::ivec3 &triangle = triangles[i];
		glm::vec3 v0 = points[triangle.x];
		glm::vec3 v1 = points[triangle.y];
		glm::vec3 v2 = points[triangle.z];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v0, v1 - v0));
		normals[triangle.x] += glm::acos(glm::dot(glm::normalize(v2 - v0),
			glm::normalize(v1 - v0))) * normal;
		normals[triangle.y] += glm::acos(glm::dot(glm::normalize(v2 - v1),
			glm::normalize(v0 - v1))) * normal;
		normals[triangle.z] += glm::acos(glm::dot(glm::normalize(v0 - v2),
			glm::normalize(v1 - v2))) * normal;


	}
	for (int i = 0; i < normals.size(); ++i)
		normals[i] = -glm::normalize(normals[i]);
}
