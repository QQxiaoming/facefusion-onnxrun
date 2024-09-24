# ifndef FACERECOGNIZER
# define FACERECOGNIZER
#include "config.h"
#include <fstream>
#include <sstream>
#if defined(CUDA_BUILD)
#include <cuda_provider_factory.h>
#endif
#include <onnxruntime_cxx_api.h>
#include"utils.h"


class FaceEmbdding
{
public:
	FaceEmbdding(std::string modelpath);
	std::vector<float> detect(cv::Mat srcimg, const std::vector<cv::Point2f> face_landmark_5);
private:
	void preprocess(cv::Mat img, const std::vector<cv::Point2f> face_landmark_5);
	std::vector<float> input_image;
	int input_height;
	int input_width;
    std::vector<cv::Point2f> normed_template;

	Ort::Env env = Ort::Env(ORT_LOGGING_LEVEL_ERROR, "Face Feature Extract");
	Ort::Session *ort_session = nullptr;
	Ort::SessionOptions sessionOptions = Ort::SessionOptions();
	std::vector<char*> input_names;
	std::vector<char*> output_names;
#if defined(USE_HIGHER_ONNX_RUNTIME_API_1_13_X)
	std::vector<Ort::AllocatedStringPtr> input_names_ptrs;
    std::vector<Ort::AllocatedStringPtr> output_names_ptrs;
#endif
	std::vector<std::vector<int64_t>> input_node_dims; // >=1 outputs
	std::vector<std::vector<int64_t>> output_node_dims; // >=1 outputs
	Ort::MemoryInfo memory_info_handler = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
};
#endif