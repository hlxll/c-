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

class RemoteControl {
public:
	RemoteControl();
	std::string getWindow(HWND val);
	cv::Mat CaptureWindow(HWND val);
	std::string getBaseFromMat(cv::Mat val);
	std::string base64_encode(const unsigned char* data, size_t length);
};