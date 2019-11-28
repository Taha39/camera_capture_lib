#ifndef __CAMERA_CAPTURE__
#define __CAMERA_CAPTURE__
#include "Capturer.h"
#include "opencv2/opencv.hpp"

namespace camera {
	class capture_cam :public custom_capture::capturer {
	public:
		bool init(int width, int height, int fps, custom_capture::raw_format format) override;
		void start(custom_capture::capture_callback* callback) override;
		void stop() override;
	
	private:
		void run(custom_capture::capture_callback* callback);
		std::thread t_;

	public:
		cv::VideoCapture cap_;
		bool start_{ false };
		custom_capture::raw_format format_{ custom_capture::raw_format::YV12 };
	};

}
#endif	//__CAMERA_CAPTURE__
