#include "yunRenderCV.h"

	YunRenderCV::YunRenderCV() {
		// ��ȡ���洰�ھ��,������������Ļ
		/*HWND desktopWnd = GetDesktopWindow();
		getWindow(desktopWnd);*/
	}
	//ͨ������õ�ͼƬ��չʾ�ڴ�����
	std::string YunRenderCV::getWindow(HWND windowHandle) {
		// �����ڱ����滻ΪĿ�괰�ڵ�ʵ�ʱ���
		if (windowHandle == nullptr) {
			std::cerr << "Failed to find the specified window." << std::endl;
			return "1";
		}

		cv::Mat screenshot = CaptureWindow(windowHandle);
		if (screenshot.empty()) {
			std::cerr << "Failed to capture the window." << std::endl;
			return "1";
		}
		//ʹ�����ǰ׺�ַ����Ϻ������չʾ�����������ӣ�����������ֶ������ǰ׺�Ϳ��ԣ�������̱���
		//"data:image/jpeg;base64," +
		std::string base64_image = getBaseFromMat(screenshot);

		//�����������⣬������뱨��???
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
		// ��ȡ���ڵ��豸������
		HDC windowDC = GetDC(windowHandle);

		// ��ȡ���ڵĳߴ�
		RECT windowRect;
		//������������
		GetClientRect(windowHandle, &windowRect);
		int width = windowRect.right - windowRect.left;
		int height = windowRect.bottom - windowRect.top;

		// ����һ���봰�ڳߴ���ƥ����ڴ��豸������
		HDC memoryDC = CreateCompatibleDC(windowDC);
		//����λͼ
		HBITMAP bitmap = CreateCompatibleBitmap(windowDC, width, height);
		//��λͼ�滻�豸�����ĵ�ͼ�ζ��󣬾��ǰѶ��߹���������
		SelectObject(memoryDC, bitmap);

		// ��Դ�������ݻ��Ƶ��ڴ��豸��������
		BitBlt(memoryDC, 0, 0, width, height, windowDC, 0, 0, SRCCOPY);

		// ���� OpenCV Mat ���󣬲����ڴ��豸�������е�ͼ�����ݿ����� Mat ������
		BITMAPINFOHEADER bi;
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height;  // ��ֵ��ʾ�Ӷ�����ʼɨ��
		bi.biPlanes = 1;
		bi.biBitCount = 24;  // �ɸ�����Ҫ����λ���
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		cv::Mat screenshot(height, width, CV_8UC3);
		GetDIBits(memoryDC, bitmap, 0, height, screenshot.data, (BITMAPINFO*)& bi, DIB_RGB_COLORS);

		// �ͷ���Դ
		DeleteObject(bitmap);
		DeleteDC(memoryDC);
		ReleaseDC(windowHandle, windowDC);

		return screenshot;
	}

	//MatͼƬ����תbase64
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
