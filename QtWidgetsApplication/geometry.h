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
	float getm_fColorSpectrumRangeMaxVal();//�Զ�ɫ�����ֵ
	float getm_fColorSpectrumRangeMinVal();//�Զ�ɫ����Сֵ
	bool isMesh() const;
	void computeBound();

protected:
	void computeNormals();
	int width = 0;
	int height = 0;
	std::vector<glm::vec3> points;//��������
	float *pointsZ = NULL;//Z����
	float m_fColorSpectrumRangeMaxVal = 10.0f;
	float m_fColorSpectrumRangeMinVal = -10.0f;
	std::vector<glm::vec3> normals;//��������
	std::vector<glm::ivec3> triangles;//��������������
	std::vector<unsigned char> grays;//�Ҷ�����
	std::vector<unsigned char> masks;//��ģ����
	glm::vec3 minPoint;//��Χ����С��
	glm::vec3 maxPoint;//��Χ������
	glm::vec3 range;//��Χ�жԽ�������
	glm::vec3 center;//��Χ������
	GLuint pointsBuffer = 0;//����VBO
	GLuint normalsBuffer = 0;//����VBO
	GLuint trianglesBuffer = 0;//����������VBO
	GLuint graysBuffer = 0;//�Ҷ�VBO
	GLuint masksBuffer = 0;//��ģVBO
	GLuint indicesBuffer = 0;//����VBO������ʰȡ
	bool mesh = false;//�Ƿ�������
};

