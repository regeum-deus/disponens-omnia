#pragma once
namespace TYPES {
	class int8 {
		signed char value;
		int8(int x);
		int get();
		void set(int x);
	};
	class uint8 {
		unsigned char value;
		uint8(unsigned int x);
		unsigned int get();
		void set(unsigned int x);
	};


	class Color {
	public:
		float r;
		float g;
		float b;
		Color();
		Color(float r, float g, float b);
	};


	class point {
	public:
		int x;
		int y;
		point();
		point(int x, int y);
		bool operator==(const point &a);
		bool operator!=(const point &a);
	};
	class pointf {
	public:
		float x;
		float y;
		pointf();
		pointf(float x, float y);
		bool operator==(const pointf &a);
		bool operator!=(const pointf &a);
	};
}