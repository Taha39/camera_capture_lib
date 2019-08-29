#ifndef __CAMERA_CAPTURE__
#define __CAMERA_CAPTURE__
#include "Capturer.h"
#include "opencv2/opencv.hpp"

namespace camera {
	class capture_cam :public custom_capture::capturer {
	public:
		bool init(int width, int height, int fps) override;
		void start(custom_capture::capture_callback* callback) override;
	
	private:
		void run(custom_capture::capture_callback* callback);

	public:
		cv::VideoCapture cap_;
		bool start_{ false };
	};

}
#endif	//__CAMERA_CAPTURE__
