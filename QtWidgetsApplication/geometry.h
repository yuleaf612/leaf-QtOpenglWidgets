#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT Geometry
{
public:
	Geometry();
	~Geometry();
	void prepareTriangle(const int &w, const int &h);
	void prepare(const int &w, const int &h, const bool &_mesh = false);
	std::vector<glm::vec3> &getPoints();
	std::vector<glm::vec3> &getNormals();
	std::vector<glm::ivec3> &getTriangles();
	std::vector<unsigned char> &getGrays();
	std::vector<unsigned char> &getMasks();
	void draw(const GLuint &shader, const bool &lighting = true, 
		const bool &drawPoints = true);
	void drawIndices(const GLuint &shader);
	const glm::vec3 &getRange() const;
	const glm::vec3 &getCenter() const;
	int getWidth() const;
	int getHeight() const;
	float getm_fColorSpectrumRangeMaxVal();//自动色谱最大值
	float getm_fColorSpectrumRangeMinVal();//自动色谱最小值
	bool isMesh() const;
	void computeBound();

protected:
	void computeNormals();
	int width = 0;
	int height = 0;
	std::vector<glm::vec3> points;//顶点数据
	float *pointsZ = NULL;//Z数据
	float m_fColorSpectrumRangeMaxVal = 10.0f;
	float m_fColorSpectrumRangeMinVal = -10.0f;
	std::vector<glm::vec3> normals;//法线数据
	std::vector<glm::ivec3> triangles;//三角形索引数据
	std::vector<unsigned char> grays;//灰度数据
	std::vector<unsigned char> masks;//掩模数据
	glm::vec3 minPoint;//包围盒最小点
	glm::vec3 maxPoint;//包围盒最大点
	glm::vec3 range;//包围盒对角线向量
	glm::vec3 center;//包围盒中心
	GLuint pointsBuffer = 0;//顶点VBO
	GLuint normalsBuffer = 0;//法线VBO
	GLuint trianglesBuffer = 0;//三角形索引VBO
	GLuint graysBuffer = 0;//灰度VBO
	GLuint masksBuffer = 0;//掩模VBO
	GLuint indicesBuffer = 0;//索引VBO，用于拾取
	bool mesh = false;//是否是网格
};

