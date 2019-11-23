#ifndef __CAPTURER__
#define __CAPTURER__
#include <vector>
#include <iostream>


namespace custom_capture {
	enum class raw_format
	{
		RGB,
		BGR,
		RGBA,
		BGRA,
		YV12
	};

	struct frame_data {
		raw_format format{raw_format::RGB};
		std::vector<unsigned char> buffer;
		int w{ 0 };
		int h{ 0 };
	};

	class capture_callback {
	public:
		virtual void on_frame(frame_data frame) = 0;
	};

	class capturer {
	public:
		virtual ~capturer() {}
		virtual bool init(int width, int height, int fps) = 0;
		virtual void start(capture_callback* callback) = 0;
		virtual void stop() = 0;
	};
}

#endif//__CAPTURER__