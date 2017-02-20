#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}

void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTop);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//3--2
	//|  |
	//0--1
	//array to hold points
	std::vector<vector3> point;
	point.push_back(vector3(0.0f, 0.0f, -a_fHeight / 2)); //middle point connecting bottom planes together
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	//generate bottom plane points
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * a_fRadius,
			sin(theta)* a_fRadius, -a_fHeight / 2));
		theta += steps; 
	}
	//all tris on bottom plane
	for (int i = 0; i < a_nSubdivisions; ++i) {
		AddTri(point[0], point[i + 1], point[i]);
	}
	//extra weird tri
	AddTri(point[a_nSubdivisions], point[0], point[1]);

	//change beginning point z value from -a_fHeight / 2 to a_fHeight / 2
	point[0] = (vector3(0.0f, 0.0f, a_fHeight/2));
	//then generate all tris connecting to the top of the cone
	for (int i = 0; i < a_nSubdivisions; ++i) {
		AddTri(point[0], point[i], point[i + 1]);
	}
	//extra weird tri again
	AddTri(point[a_nSubdivisions], point[1], point[0]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//3--2
	//|  |
	//0--1
	//generate bottom of cylinder
	std::vector<vector3> pointsBottom;
	pointsBottom.push_back(vector3(0.0f, 0.0f, -a_fHeight / 2));
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsBottom.push_back(vector3(cos(theta) * a_fRadius,
			sin(theta) * a_fRadius, -a_fHeight / 2));
		theta += steps;
	}
	//create the bottom planes
	for (int i = 0; i < a_nSubdivisions; ++i) {
		AddTri(pointsBottom[0], pointsBottom[i + 1], pointsBottom[i]);
	}
	AddTri(pointsBottom[a_nSubdivisions], pointsBottom[0], pointsBottom[1]);
	//generate top of cylinder by adding height to Z of the point
	std::vector<vector3> pointsTop;
	pointsTop.push_back(vector3(0.0f, 0.0f, a_fHeight / 2));
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsTop.push_back(vector3(cos(theta) * a_fRadius,
			sin(theta) * a_fRadius, a_fHeight / 2));
		theta += steps;
	}
	//create top planes
	for (int i = 0; i < a_nSubdivisions; ++i) {
		AddTri(pointsTop[0], pointsTop[i], pointsTop[i + 1]);
	}
	AddTri(pointsTop[a_nSubdivisions], pointsTop[1], pointsTop[0]);

	//add the quads to fill the sides
	for (int i = 0; i < a_nSubdivisions; ++i) {
		AddQuad(pointsBottom[i], pointsBottom[i+1], pointsTop[i], pointsTop[i + 1]);
	}
	AddQuad(pointsBottom[a_nSubdivisions], pointsBottom[1], pointsTop[a_nSubdivisions], pointsTop[1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//BOTTOM SIDE POINTS AND QUADS
	//generate bottom outer points of tube
	std::vector<vector3> pointsBottomOuter;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsBottomOuter.push_back(vector3(cos(theta) * a_fOuterRadius,
			sin(theta) * a_fOuterRadius, -a_fHeight / 2));
		theta += steps;
	}	

	//generate bottom inner points of the tube
	std::vector<vector3> pointsBottomInner;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsBottomInner.push_back(vector3(cos(theta) * a_fInnerRadius,
			sin(theta) * a_fInnerRadius, -a_fHeight / 2));
		theta += steps;
	}

	//generate bottom planes
	for (int i = 0; i < a_nSubdivisions-1; ++i) {
		AddQuad(pointsBottomOuter[i + 1],  pointsBottomOuter[i], pointsBottomInner[i + 1], pointsBottomInner[i]);
	}
	AddQuad( pointsBottomOuter[0], pointsBottomOuter[a_nSubdivisions - 1], pointsBottomInner[0], pointsBottomInner[a_nSubdivisions-1]);


	//TOP SIDE POINTS AND QUADS
	//generate top outer points of cylinder by adding height to Z of the points
	std::vector<vector3> pointsTopOuter;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsTopOuter.push_back(vector3(cos(theta) * a_fOuterRadius,
			sin(theta) * a_fOuterRadius, a_fHeight / 2));
		theta += steps;
	}

	//generate top inner points of the tube
	std::vector<vector3> pointsTopInner;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) {
		pointsTopInner.push_back(vector3(cos(theta) * a_fInnerRadius,
			sin(theta) * a_fInnerRadius, a_fHeight/2));
		theta += steps;
	}

	//generate top planes
	for (int i = 0; i < a_nSubdivisions - 1; ++i) {
		AddQuad(pointsTopOuter[i], pointsTopOuter[i + 1], pointsTopInner[i], pointsTopInner[i + 1]);
	}
	AddQuad(pointsTopOuter[a_nSubdivisions - 1], pointsTopOuter[0], pointsTopInner[a_nSubdivisions - 1], pointsTopInner[0]);


	//OUTSIDE
	//add the quads to fill the outside sides
	for (int i = 0; i < a_nSubdivisions-1; ++i) {
		AddQuad(pointsBottomOuter[i], pointsBottomOuter[i + 1], pointsTopOuter[i], pointsTopOuter[i + 1]);
	}
	AddQuad(pointsBottomOuter[a_nSubdivisions-1], pointsBottomOuter[0], pointsTopOuter[a_nSubdivisions-1], pointsTopOuter[0]);

	//INNER
	//add the quads to fill the inner sides
	for (int i = 0; i < a_nSubdivisions - 1; ++i) {
		AddQuad(pointsBottomInner[i + 1], pointsBottomInner[i], pointsTopInner[i + 1], pointsTopInner[i]);
	}
	AddQuad(pointsBottomInner[0], pointsBottomInner[a_nSubdivisions - 1], pointsTopInner[0], pointsTopInner[a_nSubdivisions - 1]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}

//I couldn't think of a good way to generate the sphere, I could only try work arounds involving increasing and decreasing the height and width of the points by multipling the "sphereStep" variable
//surely I just overlooked an easier way to do it...
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	//changed this temporarily, unsure how to generate sphere with 6 subdivisions
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	//generate points around radius
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);
	float height = a_fRadius;
	float sphereStep = (static_cast<float>(a_nSubdivisions) / 2) * a_fRadius;
	//generate bottom plane points
	for (int i = 0; i < a_nSubdivisions; i++) {
		point.push_back(vector3(cos(theta) * sphereStep,
			sin(theta)* sphereStep, -height/ sphereStep));
		theta += steps;
	}

	//all tris on bottom plane
	for (int i = 0; i < a_nSubdivisions-1; ++i) {
		AddTri(vector3(0.0f, 0.0f, -height), point[i + 1], point[i]);
	}
	AddTri(point[a_nSubdivisions-1], vector3(0.0f, 0.0f, -height), point[0]);

	//std::vector<vector3> pointSet2;
	//theta = 0;
	////generate bottom plane points
	//for (int i = 0; i < a_nSubdivisions; i++) {
	//	point.push_back(vector3(cos(theta) * (sphereStep * 2),
	//		sin(theta)* (sphereStep * 2), -height / (sphereStep* 2)));
	//	theta += steps;
	//}

	//for (int i = 0; i < a_nSubdivisions - 1; ++i) {
	//	AddQuad(pointSet2[i], pointSet2[i + 1], point[i], point[i + 1]);
	//}
	//AddQuad(pointSet2[a_nSubdivisions - 1], pointSet2[0], point[a_nSubdivisions - 1], point[0]);

	//Your code ends here
	CompileObject(a_v3Color);
}