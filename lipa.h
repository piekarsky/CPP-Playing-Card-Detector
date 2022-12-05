#include <string>
extern "C"
{
#ifdef LIPA_EXPORT
#define LIPA_API __declspec(dllexport)
#else
#define LIPA_API __declspec(dllimport)
#endif
}

struct imData;
enum LPL_LOAD_TYPE
{
	LPL_LOAD_ORIGINAL = 0,
	LPL_LOAD_FITTED = 1,
};
struct LIPA_API PointRGB
{
private:
	double *RedChannel;
	double *GreenChannel;
	double *BlueChannel;
public:
	PointRGB()
	{
		RedChannel = nullptr;
		GreenChannel = nullptr;
		BlueChannel = nullptr;

	}
	PointRGB(double *_r, double*_g, double*_b)
	{
		RedChannel = _r;
		GreenChannel = _g;
		BlueChannel = _b;

	}
	double& Red(){ return *RedChannel; }
	double& Green(){ return *GreenChannel; }
	double& Blue(){ return *BlueChannel; }

	double& R(){ return *RedChannel; }
	double& G(){ return *GreenChannel; }
	double& B(){ return *BlueChannel; }

	double& CH1(){ return *RedChannel; }
	double& CH2(){ return *GreenChannel; }
	double& CH3(){ return *BlueChannel; }

};

struct LIPA_API PointGray
{
private:
	double * intensity;
public:
	PointGray()
	{
		intensity = nullptr;
	}
	PointGray(double*_i)
	{
		intensity = _i;
	}
	double& Intensity(){ return *intensity; }
	double& Value(){ return *intensity; }
	double& Val(){ return *intensity; }
	double& I(){ return *intensity; }
};

class LIPA_API Image1CH
{
private:
	imData *data;
	PointGray currentPoint;
	int _w;
	int _h;
public:
	int width();
	int height();
	void getAccess(char* password);
	Image1CH(int width, int height);
	PointGray & operator()(int u, int v);
	void LoadImage(char* path, LPL_LOAD_TYPE T = LPL_LOAD_FITTED);
	void ShowImage(char* _windowName);
	void SaveImage(char* __path);
	void ShowHistogram();
	void DrawPoint(int x_coord, int y_coord, double _intensity = 1);
	void DrawLine(int x1_coord, int y1_coord, int x2_coord, int y2_coord, double _intensity = 1);
};
class LIPA_API Image3CH
{
private:
	imData *data;
	PointRGB currentPoint;
	int _w;
	int _h;
public:
	int width();
	int height();
	void getAccess(char* password);
	Image3CH(int width, int height);
	PointRGB & operator()(int u, int v);
	void LoadImage(char* path, LPL_LOAD_TYPE T = LPL_LOAD_FITTED);
	void ShowImage(char* _windowName);
	void SaveImage(char* _path);
	void ShowHistogram();
	void DrawPoint(int x_coord, int y_coord, double _red = 1, double _green = 1, double _blue = 1);
	void DrawLine(int x1_coord, int y1_coord, int x2_coord, int y2_coord, double _red = 1, double _green = 1, double _blue = 1);
};



#ifdef _DEBUG
#pragma comment (lib, "../LipaLibd.lib")
#endif
#ifdef _NDEBUG
#pragma comment (lib, "../LipaLib.lib")
#endif