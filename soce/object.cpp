#include"object.h"
#include<DxLib.h>
#include"config.h"
namespace {
	struct Vec2 {
		float x, y;
	};
	struct Color {
		float h, s, v;
	};
	Color col;
	int color;
	int r, g, b;
	int h, s, v;
	float count;
	int one = 1;
}
Vec2 GetMinMax(int s,int v) {
	Vec2 sv;
	sv.x = v;
	sv.y = v-((s/255)*v);
	return sv;
}
Color ChangeHSVtoRGB(Color c) {
	float h=0;
	Vec2 col=GetMinMax(c.s,c.v);
	if (c.h >= 0 && c.h <= 60) {
		h = (c.h/60)*(col.x-col.y)+col.y;
		return {col.x,h,col.y};
	}
	return {0,0,0};
}
void Init() {
	color = 0;
	r = 0;
	g = 0;
	b = 0;
	color = 0xe0de94;
	count = 0.f;
}
namespace not {
	void GetRGB(int color, int& r, int& g, int& b) {
		int tempnum[3] = { 0,0,0 };
		int count = 0;
		for (int i = 0x10000; i != 0; i /= 0x100) {
			tempnum[count] = (color - (tempnum[0] * 0x10000 + tempnum[1] * 0x100)) / i;
			count++;
		}
		r = tempnum[0];
		g = tempnum[1];
		b = tempnum[2];
	}
}
namespace imai{

	constexpr void GetRGB(int color, int& r, int& g, int& b)noexcept {
		r = color / 0x10000;
		g = (color - r * 0x10000) / 0x100;
		b = (color - (r * 0x10000 + g * 0x100)) / 0x1;
	}
	constexpr int GetColor(int r, int g, int b)noexcept {
		int color = (r << 16) + (g << 8) + b;
		return color;
	}
}

//int GetColorHSV(int h,int s,int v) {
//	
//	float hr=h, sg=s, vb=v;
//	float r=0.f, g=0.f, b=0.f;
//	float max=0.f, min=0.f;
//	max = vb;
//	min = vb - ((sg / 255) * vb);
//	if (hr>=0&&hr<60) {
//		r = max;
//		g = (hr/60)*(max-min)+min;
//		b = min;
//	}
//	else if (hr>=60&&hr<120) {
//		r = ((120 - hr) / 60) * (max - min) + min;
//		g = max;
//		b = min;
//	}
//	else if (hr>=120&&hr<180) {
//		r = min;
//		g = max;
//		b=((hr-120)/60)*(max-min)+min;
//	}
//	else if (hr>=180&&hr<240) {
//		r = min;
//		g = ((240-hr)/60)*(max-min)+min;
//		b = max;
//	}
//	else if (hr>=240&&hr<300) {
//		r = ((hr-240)/60)*(max-min)+min;
//		g = min;
//		b = max;
//	}
//	else if (hr>=300&&hr<=360) {
//		r = max;
//		g = min;
//		b = ((360-hr)/60)*(max-min)+min;
//	}
//	int color = ((int)r << 16) + ((int)g << 8) + (int)b;
//	return color;
//}
int GetColorHSV(int h, int s, int v) {

	float hr = h, sg = s, vb = v;
	float r = 0.f, g = 0.f, b = 0.f;
	float max = 0.f, min = 0.f;
	max = vb;
	min = vb - ((sg / 255) * vb);

	float num[6];
	num[0] = hr / 60;
	num[1] = (120-hr)/60;
	num[2] = (hr-120)/60;
	num[3] = (240-hr)/60;
	num[4] = (hr-240)/60;
	num[5] = (360-hr)/60;
	float mid = max - min;
	bool flag[6];
	flag[0]=hr >= 0 && hr < 60;
	flag[1]=hr >= 60 && hr < 120;
	flag[2]=hr >= 120 && hr < 180;
	flag[3]=hr >= 180 && hr < 240;
	flag[4]=hr >= 240 && hr < 300;
	flag[5]=hr >= 300 && hr <= 360;
	for (int i = 0; i < 6; i++) {
		if (!flag[i])continue;
		switch (i) {
		case 0:
		r = max;
		g =  num[i]* mid+ min;
		b = min;
			break;
		case 1:
			r = num[i]*mid + min;
			g = max;
			b = min;
			break;
		case 2:
			r = min;
			g = max;
			b = num[i] * mid + min;
			break;
		case 3:
			r = min;
			g = num[i] * mid+ min;
			b = max;
			break;
		case 4:
			r = num[i] * mid+ min;
			g = min;
			b = max;
			break;
		case 5:
			r = max;
			g = min;
			b = num[i] * mid+ min;
			break;
		default:
			break;
		}
	}
	
	int color = ((int)r << 16) + ((int)g << 8) + (int)b;
	return color;
}
void Update() {
	bool key = CheckHitKey(KEY_INPUT_SPACE);
	!key?
	imai::GetRGB(color,r,g,b)
	:
	not::GetRGB(color,r,g,b);
	count+=one;
	/*if (count >= 360)count = 0;
	if (count >= 360) {
		one *= -1;
	}
	else if (count<=0) {
		one *= -1;
	}*/
	Color num = ChangeHSVtoRGB({ count,255,255 });
	color = GetColor(num.h,num.s,num.v);
}
void Draw() {
	printfDx("rgb= %d,%d,%d\n",r,g,b);
	Color num = ChangeHSVtoRGB({ count,255,255 });
	printfDx("hsv= %f,%f,%f\n",num.h,num.s,num.v);
	printfDx("count= %f\n",count);
	SetFontSize(64);
	DrawFormatString(400,300,GetColorHSV((int)count%360,255,255),"mozi");
}
void Delete() {

}