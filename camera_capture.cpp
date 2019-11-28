#include "camera_capture.h"
#include <thread>
#include <Windows.h>

using namespace cv;

namespace camera {
	bool capture_cam::init(int width, int height, int fps, custom_capture::raw_format format) {
		if (!cap_.open(0))
			return false;

		format_ = format;

		bool ret = true;
		ret &= cap_.set(cv::CAP_PROP_FRAME_WIDTH, width);
		assert(ret);
		ret &= cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height);
		assert(ret);
		ret &= cap_.set(cv::CAP_PROP_FPS, fps);
		assert(ret);
		return ret;
	};

	void capture_cam::run(custom_capture::capture_callback* callback){
		while (start_) {
			Mat frame;
			cap_ >> frame;
			if (frame.empty()) break; // end of video stream

			int w = frame.size().width;
			int h = frame.size().height;

			int buf_size{ 0 };
			if (format_ == custom_capture::raw_format::YV12) {
				cv::cvtColor(frame, frame, cv::COLOR_BGR2YUV_I420);
				buf_size = (w * h * 3) / 2;
			}
			else if (format_ == custom_capture::raw_format::RGB) {
				cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
				buf_size = (w * h * 3);
			}
			
			custom_capture::frame_data frame_detail;
			frame_detail.buffer.resize(buf_size);
			
			memcpy(frame_detail.buffer.data(), frame.data, frame_detail.buffer.size());
			frame_detail.format = format_;
			frame_detail.w = w;
			frame_detail.h = h;

			callback->on_frame(frame_detail);
		}
	}

	void capture_cam::start(custom_capture::capture_callback* callback) {
		assert(t_.joinable() == false);
		assert(start_ == false);
		start_ = true;
	
		t_ = std::thread{ &capture_cam::run, this, callback };
		
	}

	
	void capture_cam::stop() {
		assert(start_);
		assert(t_.joinable());
		start_ = false;

		t_.join();
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