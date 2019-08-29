#include "camera_capture.h"
#include <thread>
#include <Windows.h>

using namespace cv;

namespace camera {
	bool capture_cam::init(int width, int height, int fps) {
		if (!cap_.open(0))
			return start_;

		
		cap_.set(cv::CAP_PROP_FRAME_WIDTH, width);
		cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height);
		cap_.set(cv::CAP_PROP_FPS, fps);
		start_ = true;
				
		return start_;
	};

	void capture_cam::run(custom_capture::capture_callback* callback){
		while (start_) {
			Mat frame;
			cap_ >> frame;
			if (frame.empty()) break; // end of video stream

			cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);

			int size = frame.total() * frame.elemSize();
			custom_capture::frame_data frame_detail;
			
			int w = frame.size().width;
			int h = frame.size().height;

			frame_detail.buffer.resize(w * h * 3);
			
			memcpy(frame_detail.buffer.data(), frame.data, frame_detail.buffer.size());
			frame_detail.format = custom_capture::raw_format::RGB;
			frame_detail.w = w;
			frame_detail.h = h;

			callback->on_frame(frame_detail);
		}
	}

	void capture_cam::start(custom_capture::capture_callback* callback) {
		std::thread thread_object(&capture_cam::run, this, callback);
		thread_object.detach();
	}

	

	/*class mycapture : public custom_capture::capture_callback {
	public:
		FILE* fp_;
	public:
		mycapture() {
			fopen_s(&fp_, "Testcapture.rgb", "wb");
		}
		~mycapture() {
			fclose(fp_);
		}
		void on_frame(custom_capture::frame_data frame) override{
			fwrite(frame.buffer.data(), 1, frame.buffer.size(), fp_);
		}
	};*/
}

//int main() {
//	camera::capture_cam ob;
//	if (!ob.init(640, 480, 25))
//		return 0;
//
//	camera::mycapture cap;
//	ob.start(&cap);
//
//	while (1)
//		Sleep(2000);
//	
//	return 0;
//}