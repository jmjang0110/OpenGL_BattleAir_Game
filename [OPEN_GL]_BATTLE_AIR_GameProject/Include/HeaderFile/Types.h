

#define WINDOW_SIZE_WIDTH 1240
#define WINDOW_SIZE_HEIGHT 800



// 해상도 ( 화면 크기 )
typedef struct _tagResolution
{
	float iW;
	float iH;

}RESOLUTION, * PRESOLUTION;


typedef enum RENDER_TYPE
{
	LINE,
	LINE_LOOP,
	TRIANGLES
}RENDER_TYPE, * PRENDER_TYPE;

typedef enum SCENE_TYPE
{
	NONE,
	BEGIN,
	MAIN_STAGE,
	END
}SCENE_TYPE, * PSCENE_TYPE;

typedef struct BoomInfo
{
	GLfloat dir = 1.0f;
	GLfloat angle = rand() % 360;
	GLfloat angle2 = rand() % 360;

	glm::vec3 pivot;


}BOOM_INFO;
