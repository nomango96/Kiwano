#pragma once
#include "emacros.h"
#include <set>
#include <stack>
#include <vector>
#include <functional>
#include <sstream>

namespace e2d
{


// 函数对象
typedef std::function<void()> Function;

// 创建函数对象
template<typename Object, typename Func>
inline Function CreateFunc(Object&& obj, Func&& func)
{
	return std::bind(func, obj);
}


#if HIGHER_THAN_VS2012

// 初始化列表
template <typename T>
using InitList = std::initializer_list<T>;

#endif


struct Size;

// 表示坐标的结构体
struct Point
{
	double x;	// X 坐标
	double y;	// Y 坐标

	/* 构造函数 */
	Point();

	Point(double x, double y);

	Point operator + (Point const & p);
	Point operator - (Point const & p);
	Point operator * (double const & value);
	Point operator / (double const & value);

	operator e2d::Size() const;
};

// 二维向量
typedef Point Vector;

// 表示大小的结构体
struct Size
{
	double width;	// 宽度
	double height;	// 高度

	/* 构造函数 */
	Size();

	Size(double width, double height);

	Size operator + (Size const & size);
	Size operator - (Size const & size);
	Size operator * (double const & value);
	Size operator / (double const & value);

	operator e2d::Point() const;
};


// 字符串
class String
{
public:
	String();
	String(const String &);
	String(const char *);
	String(const wchar_t *);
	String(String &&);

	~String();

	// 判断字符串是否为空
	bool isEmpty() const;

	// 获取字符串长度
	int getLength() const;

	// 获取该字符串的散列值
	unsigned int getHashCode() const;

	// 获取 Unicode 字符串
	std::wstring getWString() const;

	// 获取 ANSI 字符串
	std::string getCString() const;

	// 获取裁剪字符串
	String subtract(
		int offset,		/* 偏移量 */
		int count = -1	/* 截取字符数量 */
	) const;

	// 获取字符串中第一个特定字符的下标
	int findFirstOf(
		const wchar_t ch
	) const;

	// 获取字符串中最后一个特定字符的下标
	int findLastOf(
		const wchar_t ch
	) const;

	// 清空字符串
	void clear();

	// 获取大写字符串
	String toUpper() const;

	// 获取小写字符串
	String toLower() const;

	// 将字符串转化为 int 型
	int toInt() const;

	// 将字符串转化为 double 型
	double toDouble() const;

	// 将字符串转化为 bool 型
	bool toBool() const;

	// 数字类型转字符串
	static String parse(int value);
	static String parse(unsigned int value);
	static String parse(float value);
	static String parse(double value);

	// 格式化字符串
	String& format(const char * format, ...);
	String& format(const wchar_t * format, ...);

	// 赋值运算符
	String& operator= (const String &);
	String& operator= (const char *);
	String& operator= (const wchar_t *);

	// 运算符
	String& operator+= (const String &);
	String& operator+= (const char *);
	String& operator+= (const wchar_t *);
	String operator+ (const String &);
	String operator+ (const char *);
	String operator+ (const wchar_t *);

	// 友元运算符
	friend String operator+ (const char *, const String &);
	friend String operator+ (const wchar_t*, const String &);

	// 类型转换操作符
	operator const wchar_t* () const;
	operator wchar_t* () const;

	// 比较运算符
	bool operator== (const String &);
	bool operator== (const char *);
	bool operator== (const wchar_t *);
	bool operator!= (const String &);
	bool operator!= (const char *);
	bool operator!= (const wchar_t *);
	bool operator> (const String &) const;
	bool operator>= (const String &) const;
	bool operator< (const String &) const;
	bool operator<= (const String &) const;

	// << 运算符（后接字符串）
	String& operator<< (const String &);
	String& operator<< (const char *);
	String& operator<< (char *);
	String& operator<< (const wchar_t *);
	String& operator<< (wchar_t *);
	String& operator<< (int value);
	String& operator<< (unsigned int value);
	String& operator<< (float value);
	String& operator<< (double value);

	// 其他运算符
	wchar_t& operator[] (int);

	friend std::ostream& operator<< (std::ostream &, const String &);
	friend std::wostream& operator<< (std::wostream &, const String &);

	friend std::istream& operator>> (std::istream &, String &);
	friend std::wistream& operator>> (std::wistream &, String &);

private:
	std::wstring m_str;
};


// 颜色
class Color
{
public:
	enum : UINT32
	{
		ALICE_BLUE = 0xF0F8FF,
		AQUA = 0x00FFFF,
		AZURE = 0xF0FFFF,
		BEIGE = 0xF5F5DC,
		BLACK = 0x000000,
		BLUE = 0x0000FF,
		BLUE_VIOLET = 0x8A2BE2,
		BROWN = 0xA52A2A,
		CHOCOLATE = 0xD2691E,
		CYAN = 0x00FFFF,
		DARK_BLUE = 0x00008B,
		DARK_CYAN = 0x008B8B,
		DARK_GOLDENROD = 0xB8860B,
		DARK_GRAY = 0xA9A9A9,
		DARK_GREEN = 0x006400,
		DARK_ORANGE = 0xFF8C00,
		DARK_RED = 0x8B0000,
		DARK_SEA_GREEN = 0x8FBC8F,
		DARK_VIOLET = 0x9400D3,
		DEEP_PINK = 0xFF1493,
		DEEP_SKY_BLUE = 0x00BFFF,
		FOREST_GREEN = 0x228B22,
		GOLD = 0xFFD700,
		GOLDENROD = 0xDAA520,
		GRAY = 0x808080,
		GREEN = 0x008000,
		GREEN_YELLOW = 0xADFF2F,
		LIGHT_BLUE = 0xADD8E6,
		LIGHT_CYAN = 0xE0FFFF,
		LIGHT_GOLDENROD_YELLOW = 0xFAFAD2,
		LIGHT_GREEN = 0x90EE90,
		LIGHT_GRAY = 0xD3D3D3,
		LIGHT_PINK = 0xFFB6C1,
		LIGHT_SEA_GREEN = 0x20B2AA,
		LIGHT_SKY_BLUE = 0x87CEFA,
		LIGHT_SLATE_GRAY = 0x778899,
		LIGHT_YELLOW = 0xFFFFE0,
		MEDIUM_BLUE = 0x0000CD,
		MEDIUM_PURPLE = 0x9370DB,
		MEDIUM_SEA_GREEN = 0x3CB371,
		MEDIUM_SPRING_GREEN = 0x00FA9A,
		MEDUIM_VIOLET_RED = 0xC71585,
		MIDNIGHT_BLUE = 0x191970,
		ORANGE = 0xFFA500,
		ORANGE_RED = 0xFF4500,
		PINK = 0xFFC0CB,
		PURPLE = 0x800080,
		RED = 0xFF0000,
		SEA_GREEN = 0x2E8B57,
		SEA_SHELL = 0xFFF5EE,
		SILVER = 0xC0C0C0,
		SKY_BLUE = 0x87CEEB,
		SNOW = 0xFFFAFA,
		SPRING_GREEN = 0x00FF7F,
		TOMATO = 0xFF6347,
		VIOLET = 0xEE82EE,
		WHEAT = 0xF5DEB3,
		WHITE = 0xFFFFFF,
		WHITE_SMOKE = 0xF5F5F5,
		WOOD = 0xDEB887,
		YELLOW = 0xFFFF00,
		YELLOW_GREEN = 0x9ACD32
	};
};


// 字体粗细值
class FontWeight
{
public:
	enum : UINT32
	{
		THIN = 100,
		EXTRA_LIGHT = 200,
		ULTRA_LIGHT = 200,
		LIGHT = 300,
		SEMI_LIGHT = 350,
		NORMAL = 400,
		REGULAR = 400,
		MEDIUM = 500,
		DEMI_BOLD = 600,
		SEMI_BOLD = 600,
		BOLD = 700,
		EXTRA_BOLD = 800,
		ULTRA_BOLD = 800,
		BLACK = 900,
		HEAVY = 900,
		EXTRA_BLACK = 950,
		ULTRA_BLACK = 950
	};
};


// 文本对齐方式
class TextAlign
{
public:
	enum : int
	{
		LEFT,		/* 左对齐 */
		RIGHT,		/* 右对齐 */
		CENTER		/* 居中对齐 */
	};
};


// 键值集合
class KeyCode
{
public:
	enum : int
	{
		UP = 0xC8,
		LEFT = 0xCB,
		RIGHT = 0xCD,
		DOWN = 0xD0,
		ENTER = 0x1C,
		SPACE = 0x39,
		ESC = 0x01,
		BACK = 0x0E,
		TAB = 0x0F,
		PAUSE = 0xC5,
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,
		NUM1 = 0x02,
		NUM2 = 0x03,
		NUM3 = 0x04,
		NUM4 = 0x05,
		NUM5 = 0x06,
		NUM6 = 0x07,
		NUM7 = 0x08,
		NUM8 = 0x09,
		NUM9 = 0x0A,
		NUM0 = 0x0B,
		NUMPAD7 = 0x47,
		NUMPAD8 = 0x48,
		NUMPAD9 = 0x49,
		NUMPAD4 = 0x4B,
		NUMPAD5 = 0x4C,
		NUMPAD6 = 0x4D,
		NUMPAD1 = 0x4F,
		NUMPAD2 = 0x50,
		NUMPAD3 = 0x51,
		NUMPAD0 = 0x52
	};
};


// 碰撞体交集关系
class Relation
{
public:
	enum : int
	{
		UNKNOWN = 0,		/* 关系不确定 */
		DISJOINT = 1,		/* 没有交集 */
		IS_CONTAINED = 2,	/* 完全被包含 */
		CONTAINS = 3,		/* 完全包含 */
		OVERLAP = 4			/* 部分重叠 */
	};
};


// 形状样式
class ShapeStyle
{
public:
	enum : int
	{
		SOLID,		/* 填充 */
		ROUND,		/* 轮廓 */
		FILL,		/* 轮廓 + 填充 */
	};
};


// 碰撞体类别
class ColliderType
{
public:
	enum : int
	{
		RECT,		/* 矩形 */
		CIRCLE,		/* 圆形 */
		ELLIPSE		/* 椭圆形 */
	};
};


// 文本样式
struct Font
{
	String	fontFamily;		// 字体
	double	size;			// 字号
	UINT32	color;			// 颜色
	UINT32	weight;			// 粗细值
	bool	italic;			// 斜体
	bool	underline;		// 下划线
	bool	strikethrough;	// 删除线

	/* 构造函数 */
	Font();

	Font(
		String fontFamily,
		double fontSize = 22,
		UINT32 color = Color::WHITE,
		UINT32 fontWeight = FontWeight::NORMAL,
		bool italic = false,
		bool hasUnderline = false,
		bool hasStrikethrough = false
	);
};


class ObjectManager;

// 基础对象
class Object
{
	friend ObjectManager;

public:
	Object();

	virtual ~Object();

	// 引用计数加一
	void retain();

	// 引用计数减一
	void release();

	// 获取引用计数
	int getReferenceCount() const;

private:
	int m_nRefCount;
	bool m_bManaged;
};


// 图片
class Image :
	public Object
{
public:
	// 创建一个空的图片
	Image();

	// 从本地文件中读取资源
	Image(
		String strFilePath	/* 图片文件路径 */
	);

	// 从本地文件中读取资源
	Image(
		String strFilePath,	/* 图片文件路径 */
		double nCropX,		/* 裁剪位置 X 坐标 */
		double nCropY,		/* 裁剪位置 Y 坐标 */
		double nCropWidth,	/* 裁剪宽度 */
		double nCropHeight	/* 裁剪高度 */
	);

	virtual ~Image();

	// 从本地文件中读取图片
	void open(
		String strFilePath
	);

	// 将图片裁剪为矩形
	void crop(
		double nCropX,		/* 裁剪位置 X 坐标 */
		double nCropY,		/* 裁剪位置 Y 坐标 */
		double nCropWidth,	/* 裁剪宽度 */
		double nCropHeight	/* 裁剪高度 */
	);

	// 获取宽度
	virtual double getWidth() const;

	// 获取高度
	virtual double getHeight() const;

	// 获取大小
	virtual Size getSize() const;

	// 获取源图片宽度
	virtual double getSourceWidth() const;

	// 获取源图片高度
	virtual double getSourceHeight() const;

	// 获取源图片大小
	virtual Size getSourceSize() const;
	
	// 获取裁剪位置 X 坐标
	virtual double getCropX() const;

	// 获取裁剪位置 Y 坐标
	virtual double getCropY() const;

	// 获取裁剪位置
	virtual Point getCropPos() const;

	// 获取 ID2D1Bitmap 对象
	ID2D1Bitmap * getBitmap();

	// 预加载资源
	static bool preload(
		String strFileName	/* 图片文件路径 */
	);

	// 清空缓存
	static void clearCache();

protected:
	double	m_fSourceCropX;
	double	m_fSourceCropY;
	double	m_fSourceCropWidth;
	double	m_fSourceCropHeight;
	ID2D1Bitmap * m_pBitmap;
};


class Node;
class SceneManager;

// 场景
class Scene :
	public Object
{
	friend SceneManager;

public:
	Scene();

	virtual ~Scene();

	// 重写这个函数，它将在进入这个场景时自动执行
	virtual void onEnter() {}

	// 重写这个函数，它将在离开这个场景时自动执行
	virtual void onExit() {}

	// 重写这个函数，它将在碰撞发生时自动执行
	virtual void onCollide(
		Node* pActiveNode,	/* 碰撞发生时的主动体 */
		Node* pPassiveNode	/* 碰撞发生时的被动体 */
	) {}

	// 重写这个函数，它将在关闭窗口时执行（返回 false 将阻止窗口关闭）
	virtual bool onCloseWindow() { return true; }

	// 重写这个函数，它将在每一帧画面刷新时执行
	virtual void onUpdate() {}

	// 开启或禁用 onUpdate 函数
	void setAutoUpdate(
		bool bAutoUpdate
	);

	// 添加节点到场景
	void add(
		Node * child,	/* 要添加的节点 */
		int zOrder = 0	/* 渲染顺序 */
	);

#if HIGHER_THAN_VS2012
	// 添加多个节点到场景
	virtual void add(
		const InitList<Node*>& vNodes,	/* 节点数组 */
		int order = 0					/* 渲染顺序 */
	);
#endif

	// 删除子节点
	bool remove(
		Node * child
	);

	// 获取根节点
	Node * getRoot() const;

	// 开启或关闭节点轮廓渲染
	void showCollider(
		bool visiable = true
	);

protected:
	// 渲染场景画面
	void _render();

	// 更新场景内容
	void _update();

protected:
	bool m_bAutoUpdate;
	bool m_bSortNeeded;
	bool m_bWillSave;
	bool m_bColliderVisiable;
	Node * m_pRoot;
};


template<typename T>
inline void SafeDelete(T** p) { if (*p) { delete *p; *p = nullptr; } }

template<typename Object>
inline void SafeRelease(Object** p) { if (*p) { (*p)->release(); *p = nullptr; } }

template<class Interface>
inline void SafeReleaseInterface(Interface **pp) { if (*pp != nullptr) { (*pp)->Release(); (*pp) = nullptr; } }

}