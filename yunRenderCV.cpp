#include "yunRenderCV.h"

	YunRenderCV::YunRenderCV() {
		// 获取桌面窗口句柄,拿来截整个屏幕
		/*HWND desktopWnd = GetDesktopWindow();
		getWindow(desktopWnd);*/
	}
	//通过句柄得到图片，展示在窗口上
	std::string YunRenderCV::getWindow(HWND windowHandle) {
		// 将窗口标题替换为目标窗口的实际标题
		if (windowHandle == nullptr) {
			std::cerr << "Failed to find the specified window." << std::endl;
			return "1";
		}

		cv::Mat screenshot = CaptureWindow(windowHandle);
		if (screenshot.empty()) {
			std::cerr << "Failed to capture the window." << std::endl;
			return "1";
		}
		//使用这个前缀字符加上后，浏览器展示不出来，不加，让浏览器再手动加这个前缀就可以，传输过程报错
		//"data:image/jpeg;base64," +
		std::string base64_image = getBaseFromMat(screenshot);

		//引入依赖问题，下面代码报错???
		/*std::ofstream writeFile;
		writeFile.open("./base64.txt");
		if (writeFile.is_open()) {
			writeFile << base64_image;
			writeFile.close();
		}*/
		/*cv::imshow("Screenshot", screenshot);*/
		cv::waitKey(0);
		return base64_image;
	}
	cv::Mat YunRenderCV::CaptureWindow(HWND windowHandle) {
		// 获取窗口的设备上下文
		HDC windowDC = GetDC(windowHandle);

		// 获取窗口的尺寸
		RECT windowRect;
		//检索窗口坐标
		GetClientRect(windowHandle, &windowRect);
		int width = windowRect.right - windowRect.left;
		int height = windowRect.bottom - windowRect.top;

		// 创建一个与窗口尺寸相匹配的内存设备上下文
		HDC memoryDC = CreateCompatibleDC(windowDC);
		//创建位图
		HBITMAP bitmap = CreateCompatibleBitmap(windowDC, width, height);
		//用位图替换设备上下文的图形对象，就是把二者关联起来。
		SelectObject(memoryDC, bitmap);

		// 将源窗口内容绘制到内存设备上下文中
		BitBlt(memoryDC, 0, 0, width, height, windowDC, 0, 0, SRCCOPY);

		// 创建 OpenCV Mat 对象，并将内存设备上下文中的图像数据拷贝到 Mat 对象中
		BITMAPINFOHEADER bi;
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height;  // 负值表示从顶部开始扫描
		bi.biPlanes = 1;
		bi.biBitCount = 24;  // 可根据需要调整位深度
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		cv::Mat screenshot(height, width, CV_8UC3);
		GetDIBits(memoryDC, bitmap, 0, height, screenshot.data, (BITMAPINFO*)& bi, DIB_RGB_COLORS);

		// 释放资源
		DeleteObject(bitmap);
		DeleteDC(memoryDC);
		ReleaseDC(windowHandle, windowDC);

		return screenshot;
	}

	//Mat图片数据转base64
	std::string YunRenderCV::getBaseFromMat(cv::Mat data) {
		std::vector<uchar> buffer;
		imencode(".jpg", data, buffer);
		std::string base64_image = base64_encode(buffer.data(), buffer.size());
		return base64_image;
	}
	std::string YunRenderCV::base64_encode(const unsigned char* data, size_t length) {
		const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		std::string base64;
		int padding = (3 - length % 3) % 3;

		for (size_t i = 0; i < length; i += 3) {
			int triplet = (data[i] << 16) + (data[i + 1] << 8) + data[i + 2];

			for (int j = 0; j < 4; j++) {
				if (i + j * 3 <= length) {
					int index = (triplet >> (18 - j * 6)) & 0x3F;
					base64 += chars[index];
				}
				else {
					base64 += '=';
				}
			}
		}
		return base64;
	}
