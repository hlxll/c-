#pragma once
#include <iostream>
#include <Windows.h>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/flann.hpp>
#include <opencv2/features2d.hpp>
#include  <psapi.h>
#include  <tchar.h>
#include <TlHelp32.h>
#include <vector>
class WinApi {
public:
	void SaveBitmapToFile(HBITMAP bitmap, const char* filename)
	{
		BITMAP bmp;
		GetObject(bitmap, sizeof(BITMAP), &bmp);

		BITMAPINFOHEADER bi;
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = bmp.bmWidth;
		bi.biHeight = bmp.bmHeight;
		bi.biPlanes = 1;
		bi.biBitCount = bmp.bmBitsPixel;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		BITMAPFILEHEADER bmfHeader;
		bmfHeader.bfType = 0x4D42; // "BM" �ַ�
		bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
		bmfHeader.bfReserved1 = 0;
		bmfHeader.bfReserved2 = 0;
		bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		std::ofstream fileStream(filename, std::ios::binary);
		if (!fileStream) {
			std::cerr << "Failed to open file for writing: " << filename << std::endl;
			return;
		}

		fileStream.write(reinterpret_cast<const char*>(&bmfHeader), sizeof(BITMAPFILEHEADER));
		fileStream.write(reinterpret_cast<const char*>(&bi), sizeof(BITMAPINFOHEADER));

		// ��ȡλͼ����
		int bufferSize = bmp.bmWidthBytes * bmp.bmHeight;
		char* buffer = new char[bufferSize];
		GetBitmapBits(bitmap, bufferSize, buffer);

		fileStream.write(buffer, bufferSize);
		delete[] buffer;

		fileStream.close();
	}

	struct EnumWindowsData
	{
		DWORD processId;
		std::vector<HWND> windowHandles;
	};

	static BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
	{
		EnumWindowsData* data = reinterpret_cast<EnumWindowsData*>(lParam);
		DWORD windowProcessId;
		GetWindowThreadProcessId(hwnd, &windowProcessId);

		if (data->processId == windowProcessId) {
			data->windowHandles.push_back(hwnd);
		}

		return TRUE;
	}

	std::vector<HWND> GetProcessWindowHandles(DWORD processId)
	{
		EnumWindowsData data;
		data.processId = processId;

		EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&data));

		return data.windowHandles;
	}

	cv::Mat CaptureWindow(HWND windowHandle) {
		// ��ȡ���ڵ��豸������
		HDC windowDC = GetDC(windowHandle);

		// ��ȡ���ڵĳߴ�
		RECT windowRect;
		GetClientRect(windowHandle, &windowRect);
		int width = windowRect.right - windowRect.left;
		int height = windowRect.bottom - windowRect.top;

		// ����һ���봰�ڳߴ���ƥ����ڴ��豸������
		HDC memoryDC = CreateCompatibleDC(windowDC);
		HBITMAP bitmap = CreateCompatibleBitmap(windowDC, width, height);
		SelectObject(memoryDC, bitmap);

		// ���������ݻ��Ƶ��ڴ��豸��������
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
	int GetImagePath(HWND windowHandle, int index) {
		

		//!IsWindow�жϾ���Ƿ���һ����Ч���ڵľ��
		if (windowHandle && IsWindow(windowHandle)) {
			std::cout << "Window Handle: " << windowHandle << std::endl;
			

			//bpmFromRect(windowHandle, index)
			//bpmFromDC(windowHandle, index);
		}
		return -1;
	}
	//ͨ�����ڱ��⣬����ֱ�ӵõ����̴���ͼƬ
	//HWND windowHandle = FindWindow(nullptr, "TimeSync");
	int getWindow(HWND windowHandle) {
		  // �����ڱ����滻ΪĿ�괰�ڵ�ʵ�ʱ���
		if (windowHandle == nullptr) {
			std::cerr << "Failed to find the specified window." << std::endl;
			return 1;
		}

		cv::Mat screenshot = CaptureWindow(windowHandle);
		if (screenshot.empty()) {
			std::cerr << "Failed to capture the window." << std::endl;
			return 1;
		}

		cv::imshow("Screenshot", screenshot);
		cv::waitKey(0);
		return 0;
	}
	//ʹ�þ����index���֣�ͨ��GetDC�õ���ͼ��
	//FindWindow���Եõ����������ʹ������ķ������Խ�ͼ
		/*HWND windowHandle = FindWindow(nullptr, "�е��Ʊʼ�");
		if (windowHandle == nullptr) {
			std::cerr << "Failed to find window." << std::endl;
			return 1;
		}*/
	void bpmFromRect(HWND windowHandle, int index) {
		// ��ȡ������ʽ��Ϣ
		RECT windowRect;
		GetClientRect(windowHandle, &windowRect);

		HDC windowDC = GetDC(windowHandle);
		HDC memDC = CreateCompatibleDC(windowDC);
		HBITMAP bitmap = CreateCompatibleBitmap(windowDC, windowRect.right, windowRect.bottom);
		SelectObject(memDC, bitmap);

		// �Ӵ��ڻ��Ƶ��ڴ�DC
		PrintWindow(windowHandle, memDC, PW_CLIENTONLY);

		// ��λͼ����Ϊ�ļ���������BMP��ʽΪ����
		std::string url = std::to_string(index) + "screenshot.bmp";
		const char* filename = url.c_str();
		SaveBitmapToFile(bitmap, filename);

		DeleteDC(memDC);
		ReleaseDC(windowHandle, windowDC);
	}
	void bpmFromDC(HWND windowHandle, int index) {
		//���±���ͼƬ��ʽ��ȷ�����Ǿ�����ܲ�����
			//����NULL�����ʾ��ȡ������Ļ���豸�����ġ��豸�������ͼ�λ���
		HDC windowDC = GetDC(windowHandle);
		//����������豸�����ļ��ݵ�
		HDC memDC = CreateCompatibleDC(windowDC);
		RECT windowRect;
		//��ȡָ�����ڿͻ����ĳߴ�
		GetClientRect(windowHandle, &windowRect);
		std::cout << windowRect.left << std::endl;
		std::cout << windowRect.right << std::endl;
		HBITMAP bitmap = CreateCompatibleBitmap(windowDC, windowRect.right, windowRect.bottom);
		SelectObject(memDC, bitmap);
		PrintWindow(windowHandle, memDC, PW_CLIENTONLY);
		std::string url = std::to_string(index) + "screenshot.bmp";
		const char* filename = url.c_str();
		SaveBitmapToFile(bitmap, filename);

		DeleteDC(memDC);
		ReleaseDC(windowHandle, windowDC);
	}

	/*����id�õ��������ھ��
	�÷���ֻ���ҵ��������ڵľ�����޷��ҵ��Ӵ��ڡ���Ϣ������͵Ĵ��ڡ�
	��ˣ����Ŀ�괰����һ���Ӵ��ڻ��ɶ��������ɵĸ��ӽ��棬�����޷��ҵ������Ĵ��ھ��
	��ЩӦ�ó������ʹ������ļ����򱣻���ʩ�����ػ򱣻��䴰�ڣ�ʹ���޷�ͨ������Ĵ��ڱ���������ȡ�����ھ����
	���ݲ�ͬ�Ĳ���ϵͳ�汾�Ͱ�ȫ���ã��Դ��ڵķ���Ȩ�޿��ܻ������ƣ����̼�ͨ�ţ�IPC�����Ƶ�����Ҳ����Ӱ�촰�ھ���Ŀɼ��Ժͻ�ȡ��ʽ*/

	HWND GetWindowHandleFromProcessID(DWORD processID) {
		// ��ȡ���洰�ھ��,������������Ļ
		HWND desktopWnd = GetDesktopWindow();

		// �������ж������ڣ���������ָ�����̵Ĵ���
		HWND windowHandle = NULL;
		do {
			windowHandle = FindWindowEx(desktopWnd, windowHandle, nullptr, nullptr);
			DWORD windowProcessID;
			GetWindowThreadProcessId(windowHandle, &windowProcessID);
			if (windowProcessID == processID) {
				return windowHandle;  // �ҵ�ƥ�����ID�Ĵ��ھ��
			}
		} while (windowHandle != NULL);

		return NULL;  // û���ҵ�ƥ�����ID�Ĵ��ھ��
	}
	int GetWin() {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (hSnapshot == INVALID_HANDLE_VALUE) {
			std::cout << "Failed to create snapshot." << std::endl;
			return 1;
		}

		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hSnapshot, &processEntry)) {
			std::cout << "��ѯʧ��" << std::endl;
			CloseHandle(hSnapshot);
			return 1;
		}
		int index = 1;
		do {
			if (std::string(processEntry.szExeFile).find("E-Mobile") != std::string::npos) {
				//std::cout << processEntry.th32ProcessID << std::endl;

				HWND windowHandle = GetWindowHandleFromProcessID(processEntry.th32ProcessID);
				getWindow(windowHandle);

				/*if (windowHandle == NULL) {
					std::cout << "Failed to find window handle for the specified process ID." << std::endl;
					return 1;
				}
				else {
					GetImagePath(windowHandle, index);
					index++;
				}*/


				//GetProcessWindowHandles�õ��ľ���Ǹý�����ӵ�еĴ��ھ���б����������ڣ����жԻ���ȣ���һ���ɼ�
				/*std::vector<HWND> windowHandles = GetProcessWindowHandles(processEntry.th32ProcessID);
				for (HWND hwnd : windowHandles) {
					
					GetImagePath(hwnd, index);
					index++;
				}*/
				
			}
			

		} while (Process32Next(hSnapshot, &processEntry));

		CloseHandle(hSnapshot);
		return 0;
	}


	struct ThreadInfo {
		DWORD threadId;
		DWORD processId;
	};
	std::vector<ThreadInfo> EnumerateChildThreads(DWORD parentProcessId)
	{
		std::vector<ThreadInfo> threads;

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
		if (snapshot != INVALID_HANDLE_VALUE) {
			THREADENTRY32 threadEntry;
			threadEntry.dwSize = sizeof(THREADENTRY32);

			if (Thread32First(snapshot, &threadEntry)) {
				do {
					if (threadEntry.th32OwnerProcessID == parentProcessId) {
						ThreadInfo threadInfo;
						threadInfo.threadId = threadEntry.th32ThreadID;
						threadInfo.processId = threadEntry.th32OwnerProcessID;
						threads.push_back(threadInfo);
					}
				} while (Thread32Next(snapshot, &threadEntry));
			}

			CloseHandle(snapshot);
		}

		return threads;
	}




	//!=====================================================================ѧϰ����=================================
	void LearnApi() {
		std::string imageUrl = "static/2.jpg";
		cv::Mat image = cv::imread(imageUrl);
		if (image.empty()) {
			std::cout << "Failed to load image." << std::endl;
		}else {
			//cv::imwrite("static/copy.jpg", image);

			/*std::string windowName = "Image Viewer";
			cv::namedWindow(windowName, cv::WINDOW_NORMAL);
			cv::imshow(windowName, image);
			cv::waitKey(0);
			cv::destroyWindow(windowName);*/

			int width = 400;
			int height = 400;
			cv::Mat resizeImage;
			cv::resize(image, resizeImage, cv::Size(width, height));
			//cv::imshow("input Image", resizeImage);
			cv::Mat outputImage;
			cv::cvtColor(resizeImage, outputImage, cv::COLOR_BGR2GRAY);
			//cv::imshow("output Image", outputImage);

			/*int kernelSize = 5;
			cv::Mat blurImage;
			cv::blur(resizeImage, blurImage, cv::Size(kernelSize, kernelSize));
			cv::imshow("blur Image", blurImage);*/

			cv::Mat kernel = cv::Mat::ones(3, 3, CV_32F) / 9.0;

			cv::Mat filteredImage;
			cv::filter2D(resizeImage, filteredImage, -1, kernel); // ������ͼ����о���˲�����

			/*cv::imshow("Input Image", resizeImage);
			cv::imshow("Filtered Image", filteredImage);*/
			//cv::waitKey(0);
		}

		cv::Mat twoImage = cv::imread(imageUrl, cv::IMREAD_GRAYSCALE);
		if (twoImage.empty()) {
			std::cout << "read error" << std::endl;
		}else {
			cv::Mat resizeImage;
			cv::resize(twoImage, resizeImage, cv::Size(400, 400));




			/*int thresholdVal = 128;
			cv::Mat binaryImage;
			cv::threshold(resizeImage, binaryImage, thresholdVal, 255, cv::THRESH_BINARY);
			cv::imshow("input image", resizeImage);
			cv::imshow("binary iamge", binaryImage);
			cv::imwrite("static/tomatoKit.png", binaryImage);*/

			//cv::Ptr<cv::ORB> orb = cv::ORB::create(); // ���� ORB ����
			//cv::Ptr<cv::BRISK> brisk = cv::BRISK::create(); // ���� BRISK ����

			//std::vector<cv::KeyPoint> keypointsORB, keypointsBRISK;
			//cv::Mat descriptorsORB, descriptorsBRISK;

			//orb->detectAndCompute(resizeImage, cv::noArray(), keypointsORB, descriptorsORB); // ʹ�� ORB ��ȡ�������������
			//brisk->detectAndCompute(resizeImage, cv::noArray(), keypointsBRISK, descriptorsBRISK); // ʹ�� BRISK ��ȡ�������������

			//// ��ͼ���ϻ���������
			//cv::Mat outputImageORB, outputImageBRISK;
			//cv::drawKeypoints(resizeImage, keypointsORB, outputImageORB);
			//cv::drawKeypoints(resizeImage, keypointsBRISK, outputImageBRISK);

			//cv::imshow("Input Image", resizeImage);
			//cv::imshow("ORB Features", outputImageORB);
			//cv::imshow("BRISK Features", outputImageBRISK);
			//cv::waitKey(0);

			cv::waitKey(0);
		}
	}

	//����ͼƬ���Ʋ���
	void flannImg() {
		cv::Mat img1 = cv::imread("static/copy.jpg", cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = cv::imread("static/2.jpg", cv::IMREAD_GRAYSCALE);
		cv::Mat image1, image2;
		cv::resize(img1, image1, cv::Size(400, 400));
		cv::resize(img2, image2, cv::Size(400, 400));
		cv::Ptr<cv::ORB> orb = cv::ORB::create();
		std::vector<cv::KeyPoint> keypoints1, keypoints2;
		cv::Mat descriptors1, descriptors2;
		orb->detectAndCompute(image1, cv::noArray(), keypoints1, descriptors1);
		orb->detectAndCompute(image2, cv::noArray(), keypoints2, descriptors2);

		descriptors1.convertTo(descriptors1, CV_32F);
		descriptors2.convertTo(descriptors2, CV_32F);

		// ����FLANN����
		cv::flann::Index flannIndex(descriptors2, cv::flann::KDTreeIndexParams(4));
		// �������������
		int knn = 2; // �趨���������
		cv::Mat indices, distances;
		flannIndex.knnSearch(descriptors1, indices, distances, knn);

		// ƥ�������ֵ
		double threshold = 0.7;

		// ʹ�ñ��ʲ���ɸѡ���ƥ��
		std::vector<cv::DMatch> matches;
		for (int i = 0; i < indices.rows; ++i) {
			if (distances.at<float>(i, 0) < threshold * distances.at<float>(i, 1)) {
				cv::DMatch match(i, indices.at<int>(i, 0), distances.at<float>(i, 0));
				matches.push_back(match);
			}
		}
		std::cout << "ɸѡ�������" << matches.size() << std::endl;
		// ����ƥ����
		cv::Mat outputImage;
		cv::drawMatches(image1, keypoints1, image2, keypoints2, matches, outputImage);

		// ��ʾ���
		cv::imshow("Matches", outputImage);
		cv::waitKey(0);
	}

	//ɨ������
	int cascadeFace() {
		cv::CascadeClassifier cascade;
		cascade.load("static/decasd.xml");

		cv::Mat img = cv::imread("static/2.jpg");
		cv::Mat image;
		cv::resize(img, image, cv::Size(500, 400));
		if (image.empty()) {
			std::cout << "Failed to load image!" << std::endl;
			return -1;
		}
		std::vector<cv::Rect> objects;
		double scaleFactor = 1.1;
		int minNeighbors = 3;
		int flags = 0;
		cascade.detectMultiScale(image, objects, scaleFactor, minNeighbors, flags, cv::Size(30, 30));
		for (const cv::Rect& rect : objects) {
			cv::rectangle(image, rect, cv::Scalar(255, 0, 0), 2);
		}
		cv::imshow("detected", image);
		cv::waitKey(0);
		return 1;
	}

	int DescripPeople() {
		cv::HOGDescriptor hog;
		hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
		cv::Mat img = cv::imread("static/people.jpg");
		if (img.empty()) {
			std::cout << "failed load" << std::endl;
			return -1;
		}
		cv::Mat image;
		cv::resize(img, image, cv::Size(400, 400));
		std::vector<cv::Rect> detections;//�����⵽����������
		hog.detectMultiScale(image, detections);

		// ��ͼ���ϻ��Ƽ�⵽�����˾��ο�
		for (const cv::Rect& detection : detections) {
			cv::rectangle(image, detection, cv::Scalar(0, 255, 0), 2);
		}

		// ��ʾ���
		cv::imshow("Pedestrian Detection", image);
		cv::waitKey(0);
		return 1;
	}

	int readVideo() {
		std::string video_path = "static/video.mp4";
		cv::VideoCapture cap(video_path);
		if (!cap.isOpened()) {
			std::cout << "Failed read Video" << std::endl;
			return -1;
		}
		while (true) {
			cv::Mat frame;
			bool ret = cap.read(frame);
			if (!ret)
				break;
			cv::imshow("Video", frame);
			if (cv::waitKey(1) == 'q')
				break;
		}
		cap.release();
		cv::destroyAllWindows();

		return 0;
	}
	int videoWrite() {
		std::string imageBaseUrl = "static/";
		std::string outputFile = "static/newVideo.MP4";
		cv::Mat firstImage = cv::imread("static/1.jpg");
		if (firstImage.empty()) {
			std::cout << "read image Failed" << std::endl;
			return -1;
		}
		//����ļ�������Ƶ������FourCC�롢֡�ʺ�ͼ��ߴ�
		cv::VideoWriter videoWriter(outputFile, cv::VideoWriter::fourcc('H', '2', '6', '4'), 25, firstImage.size());
		if (!videoWriter.isOpened()) {
			std::cout << "video Writer Create error" << std::endl;
			return -1;
		}
		int index = 1;
		std::string imagePath;
		while (true) {
			imagePath = imageBaseUrl + std::to_string(index) + ".px";
			cv::Mat frame = cv::imread(imagePath);
			if (frame.empty()) {
				return -1;
			}
			videoWriter.write(frame);
			index++;
		}
		videoWriter.release();
		return 1;



	}

	int backDelete() {
		cv::Ptr<cv::BackgroundSubtractorMOG2> bgSubtractor = cv::createBackgroundSubtractorMOG2();
		// ����Ƶ�ļ�
		std::string videoPath = "static/video.mp4";  // �滻Ϊʵ�ʵ���Ƶ�ļ�·��
		cv::VideoCapture cap(videoPath);
		// ����Ƿ�ɹ�����Ƶ�ļ�
		if (!cap.isOpened()) {
			std::cout << "Failed to open video file!" << std::endl;
			return -1;
		}
		cv::Mat frame;
		while (cap.read(frame)) {
			// ������ģ��ǰ����ȡ
			cv::Mat fgMask;
			bgSubtractor->apply(frame, fgMask);
			// ��ʾǰ��ͼ��
			cv::imshow("Foreground", fgMask);
			// ���� 'q' ���˳�ѭ��
			if (cv::waitKey(1) == 'q')
				break;
		}
		// �ͷ���Դ���رմ���
		cap.release();
		cv::destroyAllWindows();
		return 0;
	}
	void imageDrawLine() {
		cv::Mat img = cv::imread("static/1.jpg");
		if (img.empty()) {
			std::cout << "read Failed" << std::endl;
		}
		else {
			cv::Mat image;
			cv::resize(img, image, cv::Size(400, 400));
			std::string drawText = "huanglin";
			cv::Point org(100, 100);
			int fontFace = cv::FONT_HERSHEY_SIMPLEX;
			double fontScale = 1.5;
			cv::Scalar color(0, 255, 0);
			int thickness = 2;
			cv::putText(image, drawText, org, fontFace, fontScale, color, thickness);
			cv::imshow("draw Text", image);

			cv::Mat addImage = cv::imread("static/2.jpg");
			cv::add(image, image, addImage);
			cv::imshow("addImage Text", addImage);
			cv::waitKey(0);
		}
	}


	static void onMouse(int event, int x, int y, int flags, void* userdata) {
		if (event == cv::EVENT_LBUTTONDOWN) {
			std::cout << "Left button clicked at position (" << x << ", " << y << ")" << std::endl;
		}
	}
	static void onChange(int value, void *userdata) {

	}
	void mouseFun() {
		cv::Mat image(300, 400, CV_8UC3, cv::Scalar(255, 255, 255));
		cv::namedWindow("Image");
		int value = 0;
		int maxValue = 100;
		cv::createTrackbar("trackbar", "Image", &value, maxValue, onChange);
		cv::imshow("Image", image);
		cv::setMouseCallback("Image", onMouse, 0);
		cv::waitKey(0);
	}
};


